# DF-06 Builder Link and Navigation Audit — 2026-11-17

**Repository:** `methaneex-oss/MethaneX`  
**PR:** #192 — Documentation Foundation  
**Branch:** `docs/whole-brain-planning-scope-correction-20261107`  
**Exact source revision audited:** `d065e8b60f192be165953e89f248d343bc698380`  
**PR state at source snapshot:** open, non-draft, unmerged; 41 changed files.  
**Audit role:** Builder-side static and repository-evidence audit. This is not an Independent Reviewer verdict, DF-09 fresh-reader result, DF-12 Project Director acceptance, or gate-closure decision.

## 1. Scope and method

The live PR metadata, complete changed-filename listing, and recursive Git tree were retrieved for the exact source revision above. GitHub reported 41 changed files; the changed-filename listing contained 41 unique paths. The recursive tree contained 271 entries (242 blobs and 29 tree entries) and was not truncated. All 41 changed paths were present in that tree.

All 41 changed files were fetched at the exact source revision: 39 Markdown files and two JSON fresh-reader evidence artifacts. A static scan of the 39 Markdown files covered inline Markdown links, reference-style link definitions, HTML `href`/`src` attributes, and autolinks, excluding fenced code blocks. The scan counted 332 link occurrences: 131 repository-relative/local destinations and 201 external destinations. Local destinations were normalized against each source file's directory and checked against the complete exact-revision tree, including repository-root paths and common Markdown index conventions. **All 131 local destinations resolved; no missing local target was found.**

The two fresh-reader JSON artifacts were fetched and confirmed present, but were not parsed for URLs as part of the Markdown-link scan. The synchronized inventory now includes §101, a 41-path parent manifest captured at `2ab51755b9b9e907aacb282020305bd012dbb395`; its 41 recorded blob identities match that exact parent tree. At post-write verification on `d065e8b60f192be165953e89f248d343bc698380`, all 41 changed paths remained present in the non-truncated tree. The inventory row intentionally records its own pre-update parent blob at the manifest snapshot; after the manifest append, the inventory blob changed, so that one self-entry is not expected to equal the successor tree's inventory blob. Link counts are syntactic occurrences, not unique destinations or rendered-link counts. External destinations were enumerated but not all live-HTTP revalidated in this run.

## 2. Exact-revision inventory

- Changed paths: 41 unique.
- Changed paths present in the exact revision tree: 41/41.
- Recursive tree: 271 entries; 242 blobs; 29 tree entries; `truncated=false`.
- Changed files fetched: 41/41.
- Markdown files scanned: 39/39.
- JSON evidence artifacts fetched: 2/2.
- Link occurrences counted: 332.
- Repository-relative/local destinations: 131; missing targets: 0.
- External destinations: 201 occurrences; exhaustive live-status and semantic-relevance validation was not completed.
- The two principal navigation documents were scanned at this revision: `docs/README.md` had 35 local occurrences and the planning index had 43 local occurrences; all 78 resolved.

The prior preservation report's source citations and line-range checks remain historical evidence bound to its own recorded revision and method. They are not upgraded to current-HEAD source-blob or rendered-anchor verification by this audit.

## 3. Navigation and inventory corrections

### DF06-01 — Assignment reference

The planning index §99 contains a relative Markdown link to the canonical Builder-to-xAI assignment:

`reports/BUILDER_TO_XAI_EXACT_REVISION_RE_REVIEW_REQUEST_PR173_PR195_2026-11-17.md`

The target exists in the exact source tree. The wording in inventory §100 now says the assignment is “referenced from the controlling index,” rather than claiming the inventory itself contains a direct link.

### DF06-02 — Exact-revision xAI reports

The planning index §100 contains immutable commit-pinned GitHub links:
- PR #173 report at successor commit `a96af5b18d3a1d580ff56cff6191240893bceeb5`; expected report blob `7bd31a709ec8015a1ec5441e52af7c1e28c495f6`.
- PR #195 report at successor commit `89385d3165e8c5b895fee6453247f4d732047dc0`; expected report blob `d7933ece34775e5b5a09435a01c290b99ba5c895`.

Both report files were re-fetched at their immutable successor commits and their blob identities matched the index.

### DF06-03 — Historical manifest count is explicitly qualified

Inventory §100 described a 40-path manifest created at parent commit `60b4f49953ac6a33e1f8ecfda66e8b3854dc8f87`. The current PR has 41 changed paths. The inventory wording has been corrected to identify the 40-path table as a historical parent manifest and to direct readers to fetch the live PR inventory for current state. This avoids silently presenting a stale count as current.

## 4. Rendered GitHub line/fragment navigation — not verified

The Phase 2 integration map contains commit-pinned GitHub source links with line fragments. Static existence of source lines and successful repository-API retrieval do not prove that GitHub's rendered page loads and scrolls to the intended line.

A headless-browser screenshot attempt was made for one representative commit-pinned blob line-range URL and one PR issue-comment anchor. The browser session was not authenticated to the repository, and the screenshot output was not independently inspected for the target element or viewport position. Therefore these attempts are **not counted as rendered-navigation evidence**. The GitHub connector's normalized source response also strips URL fragments.

**Result:** rendered GitHub line/fragment navigation remains unverified. No claim is made that the tested URLs landed on the intended line or comment.

## 5. External and historical destinations

The scan enumerated 201 external-link occurrences at the exact source revision. It did not perform a fresh live-status, redirect-chain, or semantic-relevance check for every unique external destination. Targeted retrieval of the two exact-revision xAI reports succeeded and their blob identities matched. Targeted historical decision-comment retrieval performed in prior work remains limited to those specific URLs and revisions; it is not exhaustive current external-link validation.

The Phase 2 map's commit-pinned source links are intentionally historical source evidence. Their exact commit references must remain immutable; the audit must check that each referenced path and line range exists at the referenced commit, and that the surrounding claim is supported. Do not “repair” historical evidence by retargeting it to a mutable branch or a different commit.

## 6. Disposition

| Check | Result |
|---|---|
| Exact PR changed-path inventory | 41 unique paths |
| Changed paths present in tree | 41/41 |
| Changed files fetched | 41/41 |
| Markdown files scanned | 39/39 |
| JSON evidence artifacts fetched | 2/2 |
| Link occurrences enumerated | 332 |
| Local destinations | 131 |
| Missing local destinations | 0 |
| External destinations enumerated | 201 occurrences |
| All external destinations live-rechecked | No |
| Assignment/report navigation defects | Corrected and statically resolved |
| Inventory's historical 40-path wording | Corrected and qualified |
| Rendered GitHub line/fragment behavior | Unverified |
| DF-06 overall | **NOT MET — independent challenge and rendered/external checks remain open** |

Builder-side local-path integrity passes for the 131 parsed local destinations. The known assignment/report navigation defects are corrected. DF-06 is not declared clear because (1) rendered GitHub line/comment navigation was not verified in an authenticated interactive browser; and (2) external/historical destinations have not received exhaustive current status and semantic-relevance checks. DF-11's independent-review requirement is waived by the Project Director's recorded decision and is not treated as a DF-06 prerequisite here.

## 7. Reproducibility and boundaries

At the audited source revision, the exact tree and all 41 changed paths were retrieved. All 39 Markdown changed files were fetched and scanned; both JSON evidence files were fetched. The 41-row inventory parent manifest was compared against its exact snapshot tree (all 41 blob identities matched), and the post-write tree at the audited revision again contained all 41 changed paths. The only intentional parent/current blob difference is the inventory file itself, which changed when the manifest was appended. To reproduce, fetch the live PR metadata and changed-path list, pin the resulting HEAD SHA, fetch its recursive tree, and re-run the link parser over every changed Markdown file. Do not mix results across commits.

For rendered-browser verification, use an authenticated GitHub browser session on the final frozen HEAD. Open representative examples from every distinct fragment target family, including commit-pinned blob line ranges and PR issue-comment anchors. Record exact URLs, destination status, target element identity, viewport position, and observed result. A screenshot without target inspection is insufficient.

For external destinations, enumerate unique URLs from the final exact revision, follow redirects, record HTTP status and final destination, inspect semantic relevance, and classify unavailable or historical links explicitly. Do not assume success from URL syntax or a single prior fetch.

DF-09 requires its own approved blind fresh-reader assessment against the final frozen PR #192 HEAD. DF-10 inventory closeout is separate. DF-12 remains a Project Director decision. PR #173 architecture acceptance, CF-26/CF-27, PR #195 F-195-07, Stage A, implementation, source-baseline selection, integration, merge, and deployment remain outside this audit and unchanged.

## 8. Optional independent challenge protocol — not a DF-11 prerequisite

The Project Director's recorded decision waives DF-11. This section is retained only as an optional technical challenge protocol if a separate reviewer is engaged to scrutinize DF-06 evidence; it is not a required gate and does not delay closure on account of DF-11. No claim is made that xAI has been notified or that an optional challenge has run.

### 8.1 Exact-revision acquisition

1. Fetch live PR #192 metadata at review start. Record repository, PR number, branch, base SHA, exact HEAD SHA, state, draft state, changed-file count, and all changed paths.
2. Review only that exact HEAD. If the branch advances during review, stop and restart against the new exact revision; do not mix evidence across SHAs.
3. Fetch every changed file at that exact SHA and record its blob identity. Read the complete PR diff and this audit.

### 8.2 DF-06 independent challenge

- Re-run the local-path inventory and confirm every local destination resolves at the exact review HEAD.
- Enumerate every unique external destination. Record HTTP/status result, redirects, final destination identity, semantic relevance, and whether the destination is current, historical, access-limited, or unavailable.
- Inspect fragment-bearing destinations, including commit-pinned source line links and issue-comment anchors, in a normal authenticated GitHub browser. For every distinct target family, record the exact URL, whether the page loads, whether GitHub lands on the intended line/comment, and the observed result.
- Check semantic link text against destination content. Identify stale branch URLs, wrong-file targets, superseded evidence, and destinations that do not support the surrounding claim.
- Return CLEAR, PARTIALLY CLEAR, or NOT CLEAR. Every finding must include stable ID, severity, exact path/line, destination, evidence, required correction, and objective recheck criterion. Disclose browser/access limitations.

### 8.3 Separate DF-09 blind fresh-reader assessment

DF-09 is a separate gate and must receive a separate result against the final exact PR #192 HEAD. Use only the established approved fresh-reader protocol/workflow and its documented inputs. Do not treat this link audit as a fresh-reader run. Do not infer CLEAR from a successful workflow wrapper or static checks. If required runtime/failure-path evidence is unavailable (including the open F-195-07 boundary), report DF-09 as blocked rather than substituting an informal review.

### 8.4 Publication and authority limits

If an optional challenge is commissioned, publish the complete report in the established repository review location and post a concise PR comment linking it. State reviewer identity and independence basis. Keep DF-06, DF-09, DF-12 Project Director acceptance, PR #173 architecture acceptance, CF-26/CF-27, F-195-07, Stage A, implementation and merge authority separate. This optional protocol authorizes no implementation, branch-history operation, PR integration, merge, draft exit or deployment.
