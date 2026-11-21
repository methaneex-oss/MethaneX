#!/usr/bin/env python3
"""Verify GitHub's rendered HTML anchors for every external fragment in the link audit."""
from __future__ import annotations

import argparse
import concurrent.futures
import json
import os
import re
import time
from html.parser import HTMLParser
from pathlib import Path
from urllib.error import HTTPError, URLError
from urllib.parse import urlsplit, urlunsplit
from urllib.request import Request, urlopen


ROOT = Path.cwd()
TIMEOUT = 30
MAX_PAGE_BYTES = 25 * 1024 * 1024
USER_AGENT = "MethaneX-Rendered-Anchor-Audit/1.0"


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
    print("Rendered-anchor verifier self-test: PASS")


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
        raise SystemExit("GITHUB_TOKEN is required for authenticated rendered-anchor verification.")

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
        verified, matched = anchor_is_present(fragment, ids)
        results.append({
            "url": url,
            "page_url": base,
            "fragment": fragment,
            "http_status": page.get("status"),
            "final_url": page.get("final_url"),
            "verified": bool(verified and page.get("status") == 200),
            "matched_ids": matched,
            "rendered_id_count": page.get("id_count", 0),
            "error": page.get("error"),
        })

    failed = [item for item in results if not item["verified"]]
    summary = {
        "status": "passed" if not failed else "failed",
        "checked_anchors": len(results),
        "verified_anchors": len(results) - len(failed),
        "failed_anchors": len(failed),
        "rendered_pages": len(pages),
        "results": results,
        "page_results": [
            {k: v for k, v in item.items() if k != "ids"}
            for item in fetched
        ],
    }
    Path("rendered-github-anchors.json").write_text(json.dumps(summary, indent=2) + "\n", encoding="utf-8")
    audit["rendered_github_anchor_verification"] = {
        "status": summary["status"],
        "checked_anchors": summary["checked_anchors"],
        "verified_anchors": summary["verified_anchors"],
        "failed_anchors": summary["failed_anchors"],
        "rendered_pages": summary["rendered_pages"],
        "evidence_file": "rendered-github-anchors.json",
    }
    audit_path.write_text(json.dumps(audit, indent=2) + "\n", encoding="utf-8")
    print(json.dumps({k: summary[k] for k in ("status", "checked_anchors", "verified_anchors", "failed_anchors", "rendered_pages")}, indent=2))
    if failed:
        for item in failed:
            print(f"RENDERED ANCHOR FAILURE: {item['url']} ({item.get('http_status')}, {item.get('error')})")
        return 1
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
