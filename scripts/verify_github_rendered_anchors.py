#!/usr/bin/env python3
"""Verify GitHub anchor targets using initial HTML and canonical issue-comment API fallback."""
from __future__ import annotations

import argparse
import base64
import concurrent.futures
import json
import os
import re
import time
from html.parser import HTMLParser
from pathlib import Path
from urllib.error import HTTPError, URLError
from urllib.parse import quote, urlsplit, urlunsplit
from urllib.request import Request, urlopen


ROOT = Path.cwd()
TIMEOUT = 30
MAX_PAGE_BYTES = 25 * 1024 * 1024
USER_AGENT = "MethaneX-GitHub-Anchor-Audit/1.1"


class IdCollector(HTMLParser):
    def __init__(self) -> None:
        super().__init__(convert_charrefs=True)
        self.ids: set[str] = set()

    def handle_starttag(self, tag: str, attrs: list[tuple[str, str | None]]) -> None:
        for key, value in attrs:
            if key.lower() == "id" and value:
                self.ids.add(value)


def page_url(url: str) -> str:
    parts = urlsplit(url)
    return urlunsplit((parts.scheme, parts.netloc, parts.path, parts.query, ""))


def expected_anchor_ids(fragment: str) -> set[str]:
    line = re.fullmatch(r"L(\d+)(?:-L(\d+))?", fragment)
    if line:
        first = int(line.group(1))
        last = int(line.group(2) or first)
        return {
            f"L{first}", f"LC{first}", f"L{last}", f"LC{last}",
            f"L{first}-L{last}", f"LC{first}-LC{last}",
        }
    return {fragment, f"user-content-{fragment}"}


def anchor_is_present(fragment: str, ids: set[str]) -> tuple[bool, list[str]]:
    expected = expected_anchor_ids(fragment)
    line = re.fullmatch(r"L(\d+)(?:-L(\d+))?", fragment)
    if line:
        first = int(line.group(1))
        last = int(line.group(2) or first)
        first_ok = any(x in ids for x in (f"L{first}", f"LC{first}"))
        last_ok = any(x in ids for x in (f"L{last}", f"LC{last}"))
        range_ok = any(x in ids for x in (f"L{first}-L{last}", f"LC{first}-LC{last}"))
        matched = sorted(expected.intersection(ids))
        return (first_ok and last_ok) or range_ok, matched
    matched = sorted(expected.intersection(ids))
    return bool(matched), matched


def issue_comment_api_url(base: str, fragment: str) -> str | None:
    match = re.fullmatch(r"issuecomment-(\d+)", fragment)
    if not match:
        return None
    parts = urlsplit(base)
    segments = parts.path.strip("/").split("/")
    if len(segments) < 4 or segments[2] not in {"pull", "issues"}:
        return None
    owner, repository = segments[0], segments[1]
    return f"https://api.github.com/repos/{owner}/{repository}/issues/comments/{match.group(1)}"


def verify_issue_comment_api(url: str, base: str, fragment: str, token: str) -> dict:
    api_url = issue_comment_api_url(base, fragment)
    if not api_url:
        return {"verified": False, "error": "unsupported_comment_anchor"}
    request = Request(
        api_url,
        headers={
            "User-Agent": USER_AGENT,
            "Accept": "application/vnd.github+json",
            "Authorization": f"Bearer {token}",
            "X-GitHub-Api-Version": "2022-11-28",
        },
        method="GET",
    )
    last_error = None
    for attempt in range(3):
        try:
            with urlopen(request, timeout=TIMEOUT) as response:
                status = response.status
                payload = json.loads(response.read(1024 * 1024).decode("utf-8"))
            canonical = payload.get("html_url", "")
            canonical_parts = urlsplit(canonical)
            base_parts = urlsplit(base)
            target_matches = (
                canonical_parts.scheme == base_parts.scheme
                and canonical_parts.netloc.lower() == base_parts.netloc.lower()
                and canonical_parts.path == base_parts.path
                and canonical_parts.fragment == fragment
            )
            return {
                "verified": bool(status == 200 and target_matches),
                "status": status,
                "api_url": api_url,
                "html_url": canonical,
                "error": None if target_matches else "canonical_html_url_mismatch",
            }
        except HTTPError as error:
            last_error = f"http_{error.code}"
            if error.code in {429, 500, 502, 503, 504} and attempt < 2:
                time.sleep(1 + attempt)
                continue
            return {"verified": False, "status": error.code, "api_url": api_url, "error": last_error}
        except (URLError, TimeoutError, OSError, ValueError, json.JSONDecodeError) as error:
            last_error = type(error).__name__
            if attempt < 2:
                time.sleep(1 + attempt)
    return {"verified": False, "status": None, "api_url": api_url, "error": last_error or "unreachable"}

def line_range_api_url(base: str, fragment: str) -> tuple[str, str, str] | None:
    match = re.fullmatch(r"L(\d+)(?:-L(\d+))?", fragment)
    if not match:
        return None
    parts = urlsplit(base)
    segments = parts.path.strip("/").split("/")
    if len(segments) < 5 or segments[2] != "blob":
        return None
    owner, repository, _, ref = segments[:4]
    path = "/".join(segments[4:])
    if not path:
        return None
    api_path = quote(path, safe="/")
    api_url = f"https://api.github.com/repos/{owner}/{repository}/contents/{api_path}?ref={quote(ref, safe='')}"
    return api_url, path, ref


def line_range_fits(fragment: str, line_count: int) -> bool:
    match = re.fullmatch(r"L(\d+)(?:-L(\d+))?", fragment)
    if not match:
        return False
    first = int(match.group(1))
    last = int(match.group(2) or first)
    return 1 <= first <= last <= line_count


def verify_line_range_api(base: str, fragment: str, token: str) -> dict:
    target = line_range_api_url(base, fragment)
    if not target:
        return {"verified": False, "error": "unsupported_line_anchor"}
    api_url, path, ref = target
    request = Request(
        api_url,
        headers={
            "User-Agent": USER_AGENT,
            "Accept": "application/vnd.github+json",
            "Authorization": f"Bearer {token}",
            "X-GitHub-Api-Version": "2022-11-28",
        },
        method="GET",
    )
    last_error = None
    for attempt in range(3):
        try:
            with urlopen(request, timeout=TIMEOUT) as response:
                status = response.status
                payload = json.loads(response.read(2 * 1024 * 1024).decode("utf-8"))
            content = payload.get("content", "")
            encoding = payload.get("encoding")
            if status != 200 or encoding != "base64" or not content:
                return {
                    "verified": False,
                    "status": status,
                    "api_url": api_url,
                    "html_url": payload.get("html_url"),
                    "path": path,
                    "ref": ref,
                    "error": "file_content_unavailable",
                }
            raw = base64.b64decode(content)
            line_count = len(raw.decode("utf-8", errors="replace").splitlines())
            canonical = payload.get("html_url", "")
            canonical_path = urlsplit(canonical).path
            base_segments = urlsplit(base).path.strip("/").split("/")
            expected_path = f"/{base_segments[0]}/{base_segments[1]}/blob/{ref}/{path}"
            path_matches = canonical_path == expected_path and payload.get("path") == path
            range_valid = line_range_fits(fragment, line_count)
            return {
                "verified": bool(status == 200 and path_matches and range_valid),
                "status": status,
                "api_url": api_url,
                "html_url": canonical,
                "path": path,
                "ref": ref,
                "line_count": line_count,
                "error": None if path_matches and range_valid else ("canonical_path_mismatch" if not path_matches else "line_range_out_of_bounds"),
            }
        except HTTPError as error:
            last_error = f"http_{error.code}"
            if error.code in {429, 500, 502, 503, 504} and attempt < 2:
                time.sleep(1 + attempt)
                continue
            return {"verified": False, "status": error.code, "api_url": api_url, "path": path, "ref": ref, "error": last_error}
        except (URLError, TimeoutError, OSError, ValueError, json.JSONDecodeError) as error:
            last_error = type(error).__name__
            if attempt < 2:
                time.sleep(1 + attempt)
    return {"verified": False, "status": None, "api_url": api_url, "path": path, "ref": ref, "error": last_error or "unreachable"}



def fetch_page(url: str, token: str) -> dict:
    request = Request(
        url,
        headers={
            "User-Agent": USER_AGENT,
            "Accept": "text/html,application/xhtml+xml",
            "Authorization": f"Bearer {token}",
        },
        method="GET",
    )
    last_error = None
    for attempt in range(3):
        try:
            with urlopen(request, timeout=TIMEOUT) as response:
                status = response.status
                final_url = response.geturl()
                body = response.read(MAX_PAGE_BYTES + 1)
            if len(body) > MAX_PAGE_BYTES:
                return {"page_url": url, "status": status, "final_url": final_url, "error": "page_exceeded_size_limit"}
            parser = IdCollector()
            parser.feed(body.decode("utf-8", errors="replace"))
            return {
                "page_url": url,
                "status": status,
                "final_url": final_url,
                "ids": parser.ids,
                "id_count": len(parser.ids),
            }
        except HTTPError as error:
            last_error = f"http_{error.code}"
            if error.code in {429, 500, 502, 503, 504} and attempt < 2:
                time.sleep(1 + attempt)
                continue
            return {"page_url": url, "status": error.code, "final_url": error.geturl(), "error": last_error}
        except (URLError, TimeoutError, OSError, ValueError) as error:
            last_error = type(error).__name__
            if attempt < 2:
                time.sleep(1 + attempt)
    return {"page_url": url, "status": None, "final_url": None, "error": last_error or "unreachable"}


def self_test() -> None:
    parser = IdCollector()
    parser.feed('<a id="L10"></a><span id="LC20"></span><div id="issuecomment-12345"></div>')
    assert anchor_is_present("L10-L20", parser.ids)[0]
    assert anchor_is_present("issuecomment-12345", parser.ids)[0]
    assert not anchor_is_present("issuecomment-99999", parser.ids)[0]
    assert issue_comment_api_url(
        "https://github.com/methaneex-oss/MethaneX/pull/173",
        "issuecomment-12345",
    ) == "https://api.github.com/repos/methaneex-oss/MethaneX/issues/comments/12345"
    assert issue_comment_api_url(
        "https://github.com/methaneex-oss/MethaneX/pull/173",
        "L10-L20",
    ) is None
    assert line_range_api_url(
        "https://github.com/methaneex-oss/MethaneX/blob/abc123/core/cpp/src/action_execution.cpp",
        "L10-L20",
    ) == (
        "https://api.github.com/repos/methaneex-oss/MethaneX/contents/core/cpp/src/action_execution.cpp?ref=abc123",
        "core/cpp/src/action_execution.cpp",
        "abc123",
    )
    assert line_range_fits("L10-L20", 20)
    assert not line_range_fits("L10-L21", 20)
    print("GitHub anchor-target verifier self-test: PASS")


def main() -> int:
    cli = argparse.ArgumentParser()
    cli.add_argument("--self-test", action="store_true")
    cli.add_argument("--audit", default="documentation-link-audit.json")
    args = cli.parse_args()
    if args.self_test:
        self_test()
        return 0

    token = os.environ.get("GITHUB_TOKEN")
    if not token:
        raise SystemExit("GITHUB_TOKEN is required for authenticated GitHub anchor-target verification.")

    audit_path = Path(args.audit)
    audit = json.loads(audit_path.read_text(encoding="utf-8"))
    fragment_urls = []
    for item in audit.get("external_results", []):
        parts = urlsplit(item.get("url", ""))
        if parts.hostname not in {"github.com", "www.github.com"} or not parts.fragment:
            continue
        fragment_urls.append((item["url"], parts.fragment, page_url(item["url"])))

    pages = sorted({item[2] for item in fragment_urls})
    with concurrent.futures.ThreadPoolExecutor(max_workers=4) as pool:
        fetched = list(pool.map(lambda url: fetch_page(url, token), pages))
    page_results = {item["page_url"]: item for item in fetched}

    results = []
    for url, fragment, base in fragment_urls:
        page = page_results[base]
        ids = page.get("ids", set())
        html_verified, matched = anchor_is_present(fragment, ids)
        html_verified = bool(html_verified and page.get("status") == 200)
        api_result = {"verified": False}
        method = "initial_html" if html_verified else None

        # GitHub may omit older timeline comments from initial HTML, and some
        # historical blob line-range pages can return 503 even when the exact
        # commit/path/line range is valid. Use the matching authenticated API
        # fallback for each anchor type; report it separately from rendered HTML.
        if not method and re.fullmatch(r"issuecomment-\d+", fragment):
            api_result = verify_issue_comment_api(url, base, fragment, token)
            if api_result.get("verified"):
                method = "github_issue_comment_api"
        elif not method and re.fullmatch(r"L\d+(?:-L\d+)?", fragment):
            api_result = verify_line_range_api(base, fragment, token)
            if api_result.get("verified"):
                method = "github_contents_line_range_api"

        results.append({
            "url": url,
            "page_url": base,
            "fragment": fragment,
            "http_status": page.get("status"),
            "final_url": page.get("final_url"),
            "verified": bool(method),
            "verification_method": method,
            "rendered_html_verified": html_verified,
            "api_verified": bool(api_result.get("verified")),
            "api_status": api_result.get("status"),
            "api_html_url": api_result.get("html_url"),
            "api_line_count": api_result.get("line_count"),
            "api_target_path": api_result.get("path"),
            "api_target_ref": api_result.get("ref"),
            "matched_ids": matched,
            "rendered_id_count": page.get("id_count", 0),
            "error": None if method else (api_result.get("error") or page.get("error") or "anchor_not_found"),
        })

    failed = [item for item in results if not item["verified"]]
    html_count = sum(1 for item in results if item["rendered_html_verified"])
    api_count = sum(1 for item in results if item["api_verified"])
    summary = {
        "status": "passed" if not failed else "failed",
        "checked_anchors": len(results),
        "verified_anchors": len(results) - len(failed),
        "html_verified_anchors": html_count,
        "api_verified_anchors": api_count,
        "failed_anchors": len(failed),
        "rendered_pages": len(pages),
        "results": results,
        "page_results": [
            {k: v for k, v in item.items() if k != "ids"}
            for item in fetched
        ],
    }
    Path("rendered-github-anchors.json").write_text(json.dumps(summary, indent=2) + "\n", encoding="utf-8")
    audit["github_anchor_target_verification"] = {
        "status": summary["status"],
        "checked_anchors": summary["checked_anchors"],
        "verified_anchors": summary["verified_anchors"],
        "html_verified_anchors": summary["html_verified_anchors"],
        "api_verified_anchors": summary["api_verified_anchors"],
        "failed_anchors": summary["failed_anchors"],
        "rendered_pages": summary["rendered_pages"],
        "evidence_file": "rendered-github-anchors.json",
        "note": "API verification confirms canonical comment existence and URL; it is not browser-rendering evidence.",
    }
    audit_path.write_text(json.dumps(audit, indent=2) + "\n", encoding="utf-8")
    print(json.dumps({
        k: summary[k] for k in (
            "status", "checked_anchors", "verified_anchors",
            "html_verified_anchors", "api_verified_anchors",
            "failed_anchors", "rendered_pages",
        )
    }, indent=2))
    if failed:
        for item in failed:
            print(f"GITHUB ANCHOR TARGET FAILURE: {item['url']} ({item.get('http_status')}, {item.get('error')})")
        return 1
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
