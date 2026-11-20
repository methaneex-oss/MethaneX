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
from urllib.parse import quote, unquote, urldefrag, urlsplit
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


def github_api_request(api_url: str, token: str, accept: str = "application/vnd.github+json") -> tuple[int, bytes, str]:
    request = Request(api_url, headers={
        "Authorization": f"Bearer {token}",
        "Accept": accept,
        "X-GitHub-Api-Version": "2022-11-28",
        "User-Agent": USER_AGENT,
    })
    with build_opener().open(request, timeout=TIMEOUT) as response:
        return response.status, response.read(), response.geturl()


def verify_github_resource(url: str) -> dict | None:
    token = os.environ.get("GITHUB_TOKEN")
    parts = urlsplit(url)
    if parts.hostname not in {"github.com", "www.github.com"} or not token:
        return None
    segments = [unquote(item) for item in parts.path.strip("/").split("/") if item]
    if len(segments) < 2:
        return None
    repository = "/".join(segments[:2])
    fragment = unquote(parts.fragment)
    try:
        if len(segments) >= 4 and segments[2] == "blob":
            revision = segments[3]
            file_path = "/".join(segments[4:])
            if not file_path:
                return None
            api_url = (
                f"https://api.github.com/repos/{repository}/contents/"
                f"{quote(file_path, safe='/')}?ref={quote(revision, safe='')}"
            )
            status, body, final_url = github_api_request(
                api_url, token, "application/vnd.github.raw+json"
            )
            line_count = len(body.decode("utf-8", errors="replace").splitlines())
            line_match = re.fullmatch(r"L(\d+)(?:-L(\d+))?", fragment)
            line_valid = None
            if line_match:
                first = int(line_match.group(1))
                last = int(line_match.group(2) or first)
                line_valid = first >= 1 and last >= first and last <= line_count
            return {
                "url": url, "status": status, "final_url": final_url, "redirects": [],
                "result": "verified_via_api" if status < 400 and line_valid is not False else "not_found",
                "source_revision": revision, "source_path": file_path,
                "source_line_count": line_count, "line_range_valid": line_valid,
                "rendered_anchor_verified": False,
            }

        if len(segments) >= 4 and segments[2] == "pull":
            number = segments[3]
            api_url = f"https://api.github.com/repos/{repository}/pulls/{number}"
            status, body, final_url = github_api_request(api_url, token)
            if status >= 400:
                return {"url": url, "status": status, "final_url": final_url, "redirects": [], "result": "not_found"}
            resource = json.loads(body.decode("utf-8"))
            result = {
                "url": url, "status": status, "final_url": final_url, "redirects": [],
                "result": "verified_via_api", "pull_request": int(number),
                "pull_request_state": resource.get("state"),
            }
            comment_match = re.fullmatch(r"issuecomment-(\d+)", fragment)
            if comment_match:
                comment_url = f"https://api.github.com/repos/{repository}/issues/comments/{comment_match.group(1)}"
                comment_status, comment_body, comment_final = github_api_request(comment_url, token)
                result["comment_status"] = comment_status
                result["comment_final_url"] = comment_final
                if comment_status >= 400:
                    result["result"] = "not_found"
            return result

        if len(segments) >= 4 and segments[2] == "actions" and segments[3] == "runs":
            if len(segments) >= 6 and segments[5] == "artifacts":
                artifact_id = segments[6] if len(segments) >= 7 else ""
                if not artifact_id:
                    return None
                api_url = f"https://api.github.com/repos/{repository}/actions/artifacts/{artifact_id}"
                status, body, final_url = github_api_request(api_url, token)
                artifact = json.loads(body.decode("utf-8")) if status < 400 else {}
                valid = status < 400 and artifact.get("id") == int(artifact_id) and not artifact.get("expired", True)
                return {
                    "url": url, "status": status, "final_url": final_url, "redirects": [],
                    "result": "verified_via_api" if valid else "not_found",
                    "artifact_id": int(artifact_id), "artifact_name": artifact.get("name"),
                    "artifact_expired": artifact.get("expired"),
                }
            run_id = segments[4]
            api_url = f"https://api.github.com/repos/{repository}/actions/runs/{run_id}"
            status, body, final_url = github_api_request(api_url, token)
            return {
                "url": url, "status": status, "final_url": final_url, "redirects": [],
                "result": "verified_via_api" if status < 400 else "not_found",
                "workflow_run": int(run_id),
            }

        if len(segments) >= 4 and segments[2] == "commit":
            api_url = f"https://api.github.com/repos/{repository}/commits/{segments[3]}"
            status, _, final_url = github_api_request(api_url, token)
            return {"url": url, "status": status, "final_url": final_url, "redirects": [], "result": "verified_via_api" if status < 400 else "not_found"}

        if len(segments) >= 4 and segments[2] == "compare":
            comparison = "/".join(segments[3:])
            api_url = f"https://api.github.com/repos/{repository}/compare/{comparison}"
            status, _, final_url = github_api_request(api_url, token)
            return {"url": url, "status": status, "final_url": final_url, "redirects": [], "result": "verified_via_api" if status < 400 else "not_found"}

    except HTTPError as error:
        return {
            "url": url, "status": error.code, "final_url": error.geturl(), "redirects": [],
            "result": "access_limited" if error.code in {401, 403, 429} else "not_found" if error.code in {404, 410} else "http_error",
        }
    except (URLError, TimeoutError, OSError, ValueError, json.JSONDecodeError) as error:
        return {"url": url, "status": None, "final_url": None, "redirects": [], "result": "unreachable", "error": str(error)}
    return None


def check_external(url: str) -> dict:
    github_result = verify_github_resource(url)
    if github_result is not None:
        return github_result
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
        "external_github_resources_verified_via_api": sum(item["result"] == "verified_via_api" for item in external_results),
        "external_artifacts_verified_via_api": sum(item.get("artifact_id") is not None and item["result"] == "verified_via_api" for item in external_results),
        "external_line_ranges_verified": sum(item.get("line_range_valid") is True for item in external_results),
        "external_line_ranges_invalid": sum(item.get("line_range_valid") is False for item in external_results),
        "external_comment_anchors_verified": sum(item.get("comment_status", 999) < 400 for item in external_results),
        "external_unreachable": sum(item["result"] == "unreachable" for item in external_results),
        "rendered_github_anchor_verification": report["rendered_github_anchor_verification"],
        "semantic_relevance_review": report["semantic_relevance_review"],
    }, indent=2))
    return 1 if missing_local or any(item["result"] not in {"ok", "verified_via_api"} for item in external_results) else 0


if __name__ == "__main__":
    sys.exit(main())
