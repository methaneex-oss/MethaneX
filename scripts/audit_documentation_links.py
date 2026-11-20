#!/usr/bin/env python3
"""Exact-revision CommonMark/GFM-style documentation link audit.

Checks tracked Markdown links, local destinations and heading fragments, and
records HTTP status plus redirect destinations for unique external URLs.
Rendered GitHub anchor landing and semantic relevance remain manual checks.
"""
from __future__ import annotations

import concurrent.futures
import html
import json
import os
import re
import subprocess
import sys
import time
from pathlib import Path, PurePosixPath
from urllib.error import HTTPError, URLError
from urllib.parse import unquote, urldefrag, urlsplit
from urllib.request import HTTPRedirectHandler, Request, build_opener

from markdown_it import MarkdownIt

ROOT = Path.cwd()
TIMEOUT = 12
RETRIES = 2
MAX_WORKERS = 6
USER_AGENT = "MethaneX-Documentation-Link-Audit/1.0"


def tracked_markdown() -> list[str]:
    raw = subprocess.check_output(
        ["git", "ls-files", "-z", "--", "*.md", "*.markdown"], cwd=ROOT
    )
    return sorted(p.decode("utf-8") for p in raw.split(b"\0") if p)


def slugify(text: str) -> str:
    text = html.unescape(re.sub(r"<[^>]+>", "", text)).lower()
    text = re.sub(r"[^\w\- ]", "", text, flags=re.UNICODE)
    return re.sub(r"\s+", "-", text.strip())


def parse_document(path: str, content: str, parser: MarkdownIt) -> tuple[list[dict], set[str]]:
    tokens = parser.parse(content)
    links: list[dict] = []
    anchors: set[str] = set()
    duplicate_counts: dict[str, int] = {}

    for index, token in enumerate(tokens):
        if token.type == "heading_open" and index + 1 < len(tokens):
            inline = tokens[index + 1]
            if inline.type == "inline":
                parts = []
                for child in inline.children or []:
                    if child.type in {"text", "code_inline", "html_inline"}:
                        parts.append(child.content)
                    elif child.type == "image":
                        parts.append(child.attrGet("alt") or child.content)
                base = slugify("".join(parts))
                if base:
                    occurrence = duplicate_counts.get(base, 0)
                    duplicate_counts[base] = occurrence + 1
                    anchors.add(base if occurrence == 0 else f"{base}-{occurrence}")

        if token.type in {"html_inline", "html_block"}:
            for match in re.finditer(r"\bid\s*=\s*['\"]([^'\"]+)['\"]", token.content, re.I):
                anchors.add(html.unescape(match.group(1)))
            for match in re.finditer(r"\b(href|src)\s*=\s*['\"]([^'\"]+)['\"]", token.content, re.I):
                links.append({"source": path, "destination": html.unescape(match.group(2)), "kind": "html"})

        if token.type == "inline":
            for child in token.children or []:
                if child.type == "link_open":
                    href = child.attrGet("href")
                    if href:
                        links.append({"source": path, "destination": href, "kind": "markdown"})
                elif child.type == "image":
                    src = child.attrGet("src")
                    if src:
                        links.append({"source": path, "destination": src, "kind": "image"})

    return links, anchors


def resolve_local(source: str, destination: str, tree_paths: set[str], anchors_by_path: dict[str, set[str]]) -> dict:
    clean, fragment = urldefrag(destination)
    clean = unquote(clean.split("?", 1)[0])
    fragment = unquote(fragment)
    if not clean:
        target = source
    elif clean.startswith("/"):
        target = clean.lstrip("/")
    else:
        target = str(PurePosixPath(source).parent / clean)
    parts = []
    for part in PurePosixPath(target).parts:
        if part in {"", "."}:
            continue
        if part == "..":
            if parts:
                parts.pop()
        else:
            parts.append(part)
    target = "/".join(parts)

    candidates = [target]
    suffix = PurePosixPath(target).suffix
    if not suffix:
        candidates.extend([target + ".md", target + ".markdown", target + "/README.md", target + "/index.md"])
    actual = next((item for item in candidates if item in tree_paths), None)
    if actual is None:
        return {"source": source, "destination": destination, "target": target, "status": "missing"}
    if fragment and actual in anchors_by_path and fragment not in anchors_by_path[actual]:
        return {"source": source, "destination": destination, "target": actual, "fragment": fragment, "status": "missing_fragment"}
    return {"source": source, "destination": destination, "target": actual, "fragment": fragment or None, "status": "ok"}


class RedirectRecorder(HTTPRedirectHandler):
    def __init__(self):
        super().__init__()
        self.chain: list[str] = []

    def redirect_request(self, req, fp, code, msg, headers, newurl):
        self.chain.append(newurl)
        return super().redirect_request(req, fp, code, msg, headers, newurl)


def verify_github_artifact(url: str) -> dict | None:
    token = os.environ.get("GITHUB_TOKEN")
    parts = urlsplit(url)
    match = re.fullmatch(r"/([^/]+/[^/]+)/actions/runs/\\d+/artifacts/(\\d+)", parts.path)
    if not token or not match:
        return None
    repository, artifact_id = match.groups()
    api_url = f"https://api.github.com/repos/{repository}/actions/artifacts/{artifact_id}"
    request = Request(api_url, headers={
        "Authorization": f"Bearer {token}",
        "Accept": "application/vnd.github+json",
        "X-GitHub-Api-Version": "2022-11-28",
        "User-Agent": USER_AGENT,
    })
    try:
        with build_opener().open(request, timeout=TIMEOUT) as response:
            artifact = json.loads(response.read().decode("utf-8"))
        if artifact.get("id") == int(artifact_id) and not artifact.get("expired", True):
            return {
                "url": url, "status": 200, "final_url": api_url, "redirects": [],
                "result": "verified_via_api", "artifact_id": int(artifact_id),
                "artifact_name": artifact.get("name"),
            }
        return {"url": url, "status": 410, "final_url": api_url, "redirects": [], "result": "not_found"}
    except HTTPError as error:
        return {
            "url": url, "status": error.code, "final_url": api_url, "redirects": [],
            "result": "access_limited" if error.code in {401, 403, 429} else "not_found" if error.code in {404, 410} else "http_error",
        }
    except (URLError, TimeoutError, OSError, ValueError) as error:
        return {"url": url, "status": None, "final_url": api_url, "redirects": [], "result": "unreachable", "error": str(error)}


def check_external(url: str) -> dict:
    fetch_url, _ = urldefrag(url)
    last_error = None
    for attempt in range(RETRIES + 1):
        recorder = RedirectRecorder()
        opener = build_opener(recorder)
        request = Request(fetch_url, headers={"User-Agent": USER_AGENT, "Range": "bytes=0-0"}, method="GET")
        try:
            with opener.open(request, timeout=TIMEOUT) as response:
                return {
                    "url": url,
                    "status": response.status,
                    "final_url": response.geturl(),
                    "redirects": recorder.chain,
                    "result": "ok" if response.status < 400 else "http_error",
                }
        except HTTPError as error:
            if error.code in {500, 502, 503, 504, 429} and attempt < RETRIES:
                time.sleep(1 + attempt)
                continue
            if error.code in {404, 410}:
                artifact_result = verify_github_artifact(url)
                if artifact_result is not None:
                    return artifact_result
            return {
                "url": url,
                "status": error.code,
                "final_url": error.geturl(),
                "redirects": recorder.chain,
                "result": "not_found" if error.code in {404, 410} else "access_limited" if error.code in {401, 403, 429} else "http_error",
            }
        except (URLError, TimeoutError, OSError) as error:
            last_error = str(error)
            if attempt < RETRIES:
                time.sleep(1 + attempt)
    return {"url": url, "status": None, "final_url": None, "redirects": [], "result": "unreachable", "error": last_error}


def main() -> int:
    parser = MarkdownIt("commonmark", {"html": True, "linkify": True}).enable(
        ["table", "strikethrough", "linkify"]
    )
    paths = tracked_markdown()
    tree_paths = {
        line.decode("utf-8")
        for line in subprocess.check_output(["git", "ls-tree", "-r", "--name-only", "HEAD", "-z"], cwd=ROOT).split(b"\0")
        if line
    }
    all_links: list[dict] = []
    anchors_by_path: dict[str, set[str]] = {}

    for path in paths:
        content = (ROOT / path).read_text(encoding="utf-8")
        links, anchors = parse_document(path, content, parser)
        all_links.extend(links)
        anchors_by_path[path] = anchors

    local_results = []
    external_urls = set()
    for link in all_links:
        destination = link["destination"].strip()
        if not destination or destination.startswith(("mailto:", "tel:", "data:")):
            continue
        if destination.startswith("//"):
            destination = "https:" + destination
        scheme = urlsplit(destination).scheme.lower()
        if scheme in {"http", "https"}:
            external_urls.add(destination)
        else:
            local_results.append(resolve_local(link["source"], destination, tree_paths, anchors_by_path))

    with concurrent.futures.ThreadPoolExecutor(max_workers=MAX_WORKERS) as pool:
        external_results = list(pool.map(check_external, sorted(external_urls)))

    missing_local = [item for item in local_results if item["status"] != "ok"]
    hard_external = [item for item in external_results if item["result"] == "not_found"]
    report = {
        "revision": subprocess.check_output(["git", "rev-parse", "HEAD"], text=True).strip(),
        "markdown_files": len(paths),
        "markdown_destinations": len(all_links),
        "local_destinations": len(local_results),
        "external_unique_urls": len(external_urls),
        "local_results": local_results,
        "external_results": external_results,
        "rendered_github_anchor_verification": "not_performed",
        "semantic_relevance_review": "not_automated",
    }
    Path("documentation-link-audit.json").write_text(json.dumps(report, indent=2) + "\n", encoding="utf-8")
    print(json.dumps({
        "revision": report["revision"],
        "markdown_files": report["markdown_files"],
        "markdown_destinations": report["markdown_destinations"],
        "local_destinations": report["local_destinations"],
        "local_failures": len(missing_local),
        "external_unique_urls": len(external_urls),
        "external_404_or_410": len(hard_external),
        "external_access_limited": sum(item["result"] == "access_limited" for item in external_results),
        "external_http_errors": sum(item["result"] == "http_error" for item in external_results),
        "external_artifacts_verified_via_api": sum(item["result"] == "verified_via_api" for item in external_results),
        "external_unreachable": sum(item["result"] == "unreachable" for item in external_results),
        "rendered_github_anchor_verification": report["rendered_github_anchor_verification"],
        "semantic_relevance_review": report["semantic_relevance_review"],
    }, indent=2))
    return 1 if missing_local or hard_external else 0


if __name__ == "__main__":
    sys.exit(main())
