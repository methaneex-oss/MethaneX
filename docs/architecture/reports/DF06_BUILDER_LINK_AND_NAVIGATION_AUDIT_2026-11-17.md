# DF-06 Builder Link and Navigation Audit — 2026-11-17

**Repository:** `methaneex-oss/MethaneX`  
**PR:** #192 — Documentation Foundation  
**Branch:** `docs/whole-brain-planning-scope-correction-20261107`  
**Exact source revision audited:** `1d5526afdfaf6056c3a0263c08f5cc405a8d81b9`  
**PR state at source snapshot:** open, non-draft, unmerged; 41 changed files.  
**Audit role:** Builder-side static and repository-evidence audit. This is not an Independent Reviewer verdict, DF-09 fresh-reader result, DF-12 Project Director acceptance, or gate-closure decision.

## 1. Scope and method

The live PR metadata, complete changed-filename listing, PR patch inventory, and recursive Git tree were retrieved for the exact source revision above. GitHub reported 41 changed files; the paginated filename listing contained 41 unique paths. The recursive tree contained 271 entries (242 blobs and 29 tree entries) and was not truncated. The changed-path inventory was fetched at the exact revision. All listed changed paths are represented in the repository tree.

All 41 changed files were fetched at the exact commit. The package contains 39 Markdown files and two JSON fresh-reader evidence artifacts. A static scan of Markdown inline-link syntax was performed across the Markdown files. It counted 332 inline link occurrences: 125 repository-relative/local destinations and 207 external destinations. The 125 local destinations were normalized against the source file directory and checked against the complete exact-revision tree, including repository-root paths, `.md`, `README.md`, and `index.md` conventions. **All 125 local destinations resolved; no missing relative target was found.**

The scan did not identify reference-style link definitions or HTML `href`/`src` destinations in the inspected files. The parser did not treat the 332 count as a rendered-link count. The two principal navigation documents remain a subset of the full-package scan: `docs/README.md` contains 35 local-link occurrences and the planning index contains 41, for 76 local-link occurrences with zero missing targets.

## 2. Exact-revision inventory

- Changed paths: 41 unique.
- Changed paths present in the exact revision tree: 41/41.
- Recursive tree: 271 entries; 242 blobs; 29 tree entries; `truncated=false`.
- Changed files successfully fetched: 41/41.
- Markdown files statically scanned: 39.
- JSON evidence artifacts fetched: 2.
- Inline Markdown link occurrences counted: 332.
- Repository-relative/local destinations: 125; missing targets: 0.
- External destinations: 207 occurrences. These were enumerated by the scan but were **not all live-HTTP revalidated in this run**.
- Fragment-bearing destinations: 92 occurrences in the scanned Markdown links. This includes source line fragments and GitHub issue-comment fragments; repeated occurrences are not necessarily distinct targets.

The prior preservation report's 89 source citations across 45 exact commit/path pairs and 76 checked line ranges remain historical evidence bound to the revision and method documented there. They are not represented as a new complete source-blob or line-range validation run at this revision.

## 3. Navigation corrections present at this revision

### DF06-01 — Assignment reference is now clickable

The planning index §99 now uses a relative Markdown link to the canonical Builder-to-xAI assignment:

`reports/BUILDER_TO_XAI_EXACT_REVISION_RE_REVIEW_REQUEST_PR173_PR195_2026-11-17.md`

The destination resolves in the exact revision tree. The earlier inventory wording that said it was “linked from the controlling index” is still inaccurate if it refers to a separate direct link from the inventory; it should say “referenced from the controlling index” unless the inventory itself is given a direct link. This wording correction is required in the next inventory synchronization.

### DF06-02 — Exact-revision xAI reports are directly navigable

The planning index §100 now contains immutable commit-pinned GitHub links:
- PR #173 report at successor commit `a96af5b18d3a1d580ff56cff6191240893bceeb5`; expected report blob `7bd31a709ec8015a1ec5441e52af7c1e28c495f6`.
- PR #195 report at successor commit `89385d3165e8c5b895fee6453247f4d732047dc0`; expected report blob `d7933ece34775e5b5a09435a01c290b99ba5c895`.

Both report files were fetched at their immutable successor commits and their blob identities matched the index. The navigation defects identified in the earlier source-snapshot audit are therefore corrected in this source revision.

## 4. Rendered GitHub line/fragment navigation — blocked

The Phase 2 integration map contains commit-pinned GitHub source links with line fragments. The prior preservation report records validation of 76 line-anchor ranges against exact fetched source-file lengths. This is evidence that the cited line ranges existed in those source files at the recorded commits. It does **not** establish that GitHub's rendered blob page loads and scrolls to the intended line range.

A direct attempt to open a representative GitHub blob URL with a line fragment was rejected by the browser retrieval layer with `DisabledError`. The GitHub repository connector returns normalized source content and strips the URL fragment, so it cannot prove browser scroll behavior. No authenticated interactive GitHub browser session was available in this Builder audit.

**Result:** actual rendered GitHub line/fragment navigation remains unverified. Do not mark this criterion passed based on static source-line existence.

## 5. External and historical destinations

The scan enumerated 207 external-link occurrences at the exact source revision. This run did not perform a live status check for every unique external destination. Earlier preservation-report checks of 189 external URL occurrences remain historical evidence for the exact scope and revision recorded in that report; they must not be silently upgraded to current-live verification.

The exact-revision xAI report destinations were independently re-fetched and their expected blobs matched. Historical decision-comment URLs referenced in the portal and index were also fetched and their returned comment bodies inspected. These targeted checks do not constitute a fresh exhaustive validation of all external destinations.

## 6. Disposition

| Check | Result |
|---|---|
| Exact PR changed-path inventory | 41 unique paths |
| Changed paths present in tree | 41/41 |
| Changed files fetched | 41/41 |
| Local/relative link destinations | 125 |
| Missing local/relative destinations | 0 |
| External destinations enumerated | 207 occurrences |
| All external destinations live-rechecked | No |
| Historical line-range source existence | Prior evidence: 76 ranges, exact scope in preservation report |
| Rendered GitHub line/fragment behavior | Unverified / blocked |
| DF-06 overall | **NOT MET** |

DF06-01 and DF06-02 are corrected in this source revision. Local path integrity passes for the 125 parsed destinations. Two evidence requirements remain before DF-06 can be declared met: (1) rendered GitHub navigation for the distinct line/fragment target families must be checked in a normal interactive GitHub browser; and (2) the external/historical destination inventory must receive a fresh exact-revision status and semantic-relevance check, or each item not verifiable must be explicitly dispositioned as historical/access-limited with a primary-source alternative where applicable.

## 7. Reproducibility and boundaries

Reproduce the local-path scan against the final PR #192 HEAD after all closeout writes. Re-fetch live PR metadata, the complete changed-path list, the exact tree, and all changed-file blobs. For browser verification, open representative line-fragment links from the final exact revision in a normal authenticated GitHub browser, confirm both destination resolution and viewport position, and record the exact tested URLs and outcomes. Cover every distinct target family, not merely one arbitrary link. Repeat the external-destination classification at the final exact revision and retain a list of any status failures, redirects, access limitations, and semantically stale destinations.

DF-09 must be independently assessed against the final frozen PR #192 HEAD. DF-12 remains a Project Director decision. DF-10 inventory closeout is separate. PR #173 architecture acceptance, CF-26/CF-27, PR #195 F-195-07, Stage A, implementation, source-baseline selection, integration, merge, and deployment remain outside this audit and unchanged.


## 8. Independent closeout handoff — not yet executed

This section is the complete Builder-to-Independent-Reviewer handoff. It does not claim that xAI has been notified, that the review has run, or that DF-06/DF-09 is cleared.

### 8.1 Exact-revision acquisition

1. Fetch the live PR #192 page at review start. Record repository, PR number, branch, base SHA, exact HEAD SHA, state, draft state, changed-file count, and all changed paths.
2. Review only that exact HEAD. If the branch advances during review, stop and restart against the new exact revision; do not mix evidence across SHAs.
3. Fetch every changed file at that exact SHA and record its blob identity. Read the complete PR diff and the current audit report.

### 8.2 DF-06 rendered-link and external-destination challenge

Independently challenge the Builder results rather than relying on them:
- Re-run the local-path inventory and confirm the 125 destinations recorded for source snapshot `1d5526afdfaf6056c3a0263c08f5cc405a8d81b9` still resolve at the exact review HEAD.
- Enumerate and live-check every external destination at the exact review HEAD. Record HTTP/status result, redirects, destination identity, semantic relevance, and whether the destination is current, historical, access-limited, or unavailable. Do not infer a successful destination from a URL's appearance.
- Inspect all fragment-bearing destinations, including the commit-pinned source line links in the Phase 2 map and issue-comment anchors. Use a normal interactive GitHub browser. For each distinct target family, record the exact URL, whether the page loads, whether GitHub lands on the intended line/comment, and the observed result. Static source-line existence is not rendered-navigation proof.
- Check semantic link text against the actual destination content. Identify stale branch URLs, wrong-file targets, superseded evidence, and destinations whose content does not support the surrounding claim.
- Return a DF-06 verdict of CLEAR, PARTIALLY CLEAR, or NOT CLEAR. Every finding must include stable ID, severity, exact path/line, destination, evidence, required correction, and objective recheck criterion. Disclose any browser or access limitation explicitly.

### 8.3 Separate DF-09 blind fresh-reader assessment

DF-09 is a separate gate and must receive a separate result against the final exact PR #192 HEAD. Use only the established approved fresh-reader protocol/workflow and its documented inputs. Do not treat this link audit as a fresh-reader run. Do not infer a CLEAR result from a successful workflow wrapper or static checks. If the approved workflow cannot be executed because its required runtime/failure-path evidence is unavailable (including the open F-195-07 boundary), report DF-09 as blocked rather than substituting an informal review.

### 8.4 Required publication and authority limits

Publish the complete review report in the established repository review location and post a concise PR comment linking it. State reviewer identity and independence basis. Keep DF-06, DF-09, DF-12 Project Director acceptance, PR #173 architecture acceptance, CF-26/CF-27, F-195-07, Stage A, implementation and merge authority separate. This assignment authorizes no implementation, branch-history operation, PR integration, merge, draft exit or deployment.
