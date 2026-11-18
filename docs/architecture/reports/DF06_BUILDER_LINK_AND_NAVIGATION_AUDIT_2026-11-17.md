# DF-06 Builder Link and Navigation Audit — 2026-11-17

**Repository:** `methaneex-oss/MethaneX`  
**PR:** #192 — Documentation Foundation  
**Branch:** `docs/whole-brain-planning-scope-correction-20261107`  
**Exact source revision audited:** `3d44626cb30169790019f20409b107811217b58f`  
**PR state at source snapshot:** open, non-draft, unmerged; 41 changed files.  
**Audit role:** Builder-side static and repository-evidence audit. This is not an Independent Reviewer verdict, DF-09 fresh-reader result, DF-12 Project Director acceptance, or gate-closure decision.

## 1. Scope and method

The live PR metadata, complete changed-filename listing, and recursive Git tree were retrieved for the exact source revision above. GitHub reported 41 changed files; the changed-filename listing contained 41 unique paths. The recursive tree contained 271 entries (242 blobs and 29 tree entries) and was not truncated. All 41 changed paths were present in that tree.

All 39 Markdown changed files were fetched directly at the exact audit source revision `3d44626cb30169790019f20409b107811217b58f`. Both JSON fresh-reader evidence artifacts were also fetched directly at that exact revision. This binds all 41 changed files to one exact source snapshot; no parent-to-source substitution was used for this repeat pass. A static scan covered inline Markdown links, reference-style link definitions, HTML `href`/`src` attributes, and autolinks, excluding fenced code blocks. The repeat scan extracted 331 link occurrences: 125 repository-relative/local destinations and 206 external destinations. Local destinations were normalized against each source file's directory and checked against the complete exact-revision tree, including repository-root paths and common Markdown index conventions. **All 125 local destinations extracted by this pass resolved; no missing local target was found.**

The two fresh-reader JSON artifacts were fetched and confirmed present, but were not parsed for URLs as part of the Markdown-link scan. Inventory §107 records the exact 41-path parent manifest at `e6138c3a790c86e7844385e6d002effba0cd36de`; its 41 blob identities match that exact parent tree, and successor `3d44626...` changes only the inventory file. This confirms the parent-manifest/one-file-successor relationship for the current audit source snapshot. Because this report is now being refreshed, a new final inventory parent manifest must be written after the audit and controlling index updates. Link counts are syntactic occurrences, not unique destinations or rendered-link counts. External destinations were enumerated but not all live-HTTP revalidated in this run.

## 2. Exact-revision inventory

- Changed paths: 41 unique.
- Changed paths present in the exact revision tree: 41/41.
- Recursive tree: 271 entries; 242 blobs; 29 tree entries; `truncated=false`.
- Changed paths verified: 41/41.
- Markdown files scanned: 39/39 directly fetched at the exact audit source revision.
- JSON evidence artifacts fetched directly at source revision: 2/2.
- Link occurrences extracted by this repeat pass: 331.
- Repository-relative/local destinations extracted: 125; missing targets among those extracted: 0.
- External destinations extracted: 206 occurrences; exhaustive live-status and semantic-relevance validation was not completed.
- A prior audit snapshot recorded 332 total / 131 local / 201 external occurrences. This repeat pass differs by one total occurrence and by six local/five external classifications. The earlier parser's per-file output or executable is not preserved in the report, so the discrepancy is unresolved. Do not treat the counts as reconciled or claim parser equivalence.

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

The repeat scan extracted 206 external-link occurrences at the exact source revision. It did not perform a fresh live-status, redirect-chain, or semantic-relevance check for every unique external destination. Targeted retrieval of the two exact-revision xAI reports succeeded and their blob identities matched. Targeted historical decision-comment retrieval performed in prior work remains limited to those specific URLs and revisions; it is not exhaustive current external-link validation.

The Phase 2 map's commit-pinned source links are intentionally historical source evidence. Their exact commit references must remain immutable; the audit must check that each referenced path and line range exists at the referenced commit, and that the surrounding claim is supported. Do not “repair” historical evidence by retargeting it to a mutable branch or a different commit.

## 6. Disposition

| Check | Result |
|---|---|
| Exact PR changed-path inventory | 41 unique paths |
| Changed paths present in tree | 41/41 |
| Changed files fetched | 41/41 |
| Markdown files scanned | 39/39 |
| JSON evidence artifacts fetched | 2/2 |
| Link occurrences extracted by repeat pass | 331 |
| Local destinations extracted | 125 |
| Missing among extracted local destinations | 0 |
| External destinations extracted | 206 occurrences |
| Prior-vs-repeat parser count discrepancy | Unresolved; see §2 |
| All external destinations live-rechecked | No |
| Assignment/report navigation defects | Corrected and statically resolved |
| Inventory's historical 40-path wording | Corrected and qualified |
| Rendered GitHub line/fragment behavior | Unverified |
| DF-06 overall | **NOT MET — rendered/external checks remain open** |

Builder-side local-path integrity passes for the 125 local destinations extracted by the repeat parser pass; the count discrepancy against the prior audit remains unresolved. The known assignment/report navigation defects are corrected. DF-06 is not declared clear because (1) rendered GitHub line/comment navigation was not verified in an authenticated interactive browser; and (2) external/historical destinations have not received exhaustive current status and semantic-relevance checks. DF-11's independent-review requirement is waived by the Project Director's recorded decision and is not treated as a DF-06 prerequisite here.

## 7. Reproducibility and boundaries

At the audited source revision `3d44626...`, the exact tree and all 41 changed paths were retrieved. All 39 Markdown files and both JSON evidence artifacts were fetched directly at that exact revision. Inventory §107's 41-row parent manifest was compared against parent tree `e6138c3...`; all 41 blob identities matched, and the source revision was exactly one commit ahead with only the inventory file changed. This refresh changes the audit report itself; the final Builder manifest must therefore be regenerated after the audit and controlling-index updates. To reproduce, fetch the live PR metadata and changed-path list, pin the resulting HEAD SHA, fetch its recursive tree, and re-run the link parser over every changed Markdown file. Do not mix results across commits.

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


## 8. Live PR #192 exact-HEAD repeat scan — 2026-11-18

**Exact source revision:** `5a8dafb5ae8d5b31952a90846704a935a29b4421`  
**PR #192 state at scan:** open, non-draft, unmerged; 43 changed paths (41 Markdown, 2 JSON).  
**Repository tree:** 274 entries, `truncated=false`.  
**Fetched Markdown coverage:** 41/41 changed Markdown files fetched directly at the exact source revision; the two JSON artifacts remain part of the 43-path inventory but were not included in Markdown link parsing.

A bounded repeat parser scanned Markdown inline link/image destinations using the pattern `!?\[[^\]]*\]\(([^)]+)\)`, stripped optional titles, classified HTTP(S)/protocol-relative destinations as external, and resolved relative local destinations against the complete repository tree after normalizing `.` and `..` path segments.

| Measure | Result |
|---|---:|
| Markdown files fetched | 41 / 41 |
| Inline Markdown link/image occurrences | 348 |
| Local destinations | 129 |
| External HTTP(S)/protocol-relative destinations | 219 |
| Local destinations absent from the complete repository tree | 0 |

All 129 local destinations identified by this repeat parser resolve to paths present in the complete tree at the exact source revision. This is a path-existence result only; it does not prove fragment/heading-anchor validity, rendered GitHub line/comment-anchor validity, or the semantic correctness of the destination.

**Parser reconciliation remains OPEN.** This repeat parser's 348/129/219 result does not reconcile the previously recorded 331/125/206 repeat-scan result or the earlier 332/131/201 result. The parser expressions and inclusion rules are not yet demonstrated to be equivalent; the difference must not be represented as a confirmed regression or as a clean parser reconciliation. The old report sections remain historical evidence for their pinned revisions.

**External and rendered-anchor verification remain incomplete.** The 219 external occurrences were classified but not individually fetched or semantically verified in this scan. GitHub-rendered headings, line anchors, comment anchors and fragment targets were not authenticated. No claim of exhaustive external reachability or rendered navigation correctness is made.

### 8.1 Current disposition

DF-06 remains **NOT MET**. The live exact-HEAD scan improves the local-path evidence to 129/129 resolving under the stated parser, but the parser discrepancy, external destination checks, and authenticated rendered-anchor checks remain open. A later PR #192 write changes the target SHA and requires a new exact-revision scan.


## 9. Full changed-Markdown re-scan — exact PR #192 source HEAD 5bc0cfa (2026-11-18)

**Exact source revision:** `5bc0cfa4266ee387bccf26f6b0e6f95c6a1a6509`  
**PR state at source:** open, non-draft, unmerged; 45 changed paths.  
**Changed Markdown coverage:** 43/43 fetched directly at the exact source revision; the remaining two changed paths are JSON evidence artifacts and are not Markdown navigation inputs.  
**Repository tree:** 277 entries; recursive tree complete (`truncated=false`).

The Builder repeated the link scan across all 43 changed Markdown files at one exact SHA. The strict pass removed fenced code blocks and inline-code spans before parsing Markdown links, reference definitions, HTML `href`/`src` and autolinks. No reference-style definitions, HTML link attributes or autolinks were found. The raw occurrence count is retained separately because Markdown-looking syntax inside code examples is not a rendered navigation link.

| Measure | Result |
|---|---:|
| Markdown files fetched | 43 / 43 |
| Raw inline-link/image regex occurrences (including code examples) | 350 |
| Raw local / HTTP(S) external occurrences | 131 / 219 |
| Strict rendered-Markdown candidate occurrences (code examples excluded) | 341 |
| Strict local / HTTP(S) external occurrences | 128 / 213 |
| Reference definitions / HTML href-src / autolinks | 0 / 0 / 0 |
| Strict local targets absent from the exact repository tree before correction | 1 |

The sole missing local destination was in the controlling planning index: its relative path resolved to `docs/architecture/reviews/DF02_HISTORICAL_COGNITIVE_LEARNING_LINEAGE_INDEPENDENT_REVIEW_REQUEST_2026-11-18.md`, while the actual artifact resides at `docs/architecture/reports/reviews/DF02_HISTORICAL_COGNITIVE_LEARNING_LINEAGE_INDEPENDENT_REVIEW_REQUEST_2026-11-18.md`. The index was corrected in commit `3f19557274e7129774ce41e61a386d11a0d10757`. The corrected target was subsequently fetched from the current branch; final post-inventory verification must re-run local-path validation against the final exact PR HEAD.

### 9.1 Historical parser-count reconciliation

The prior live source scan at `5a8dafb5ae8d5b31952a90846704a935a29b4421` reported 348 raw occurrences (129 local, 219 external) across 41 Markdown files. The current exact-source raw scan reports 350 (131 local, 219 external) across 43 Markdown files. The branch comparison from the prior scan source to this source is 22 commits ahead and changes six documentation paths. The index contributes two additional local navigation occurrences; the other additions are the two new Markdown documents and report corrections. The older 331/125/206 and 332/131/201 snapshots cannot be fully replayed because their original parser implementations, per-file outputs and complete input manifests were not preserved. They remain historical measurements, not reconciled equivalent results.

The strict current pass removes nine raw matches found only in fenced or inline-code examples (three local-looking and six external-looking). It is therefore the better current estimate of actual Markdown navigation links, but it is not represented as byte-for-byte reproduction of the missing historical parser runs.

### 9.2 Final disposition and residuals

The Builder corrected the one broken local path and verified the corrected link text points to the actual repository location. The current strict local set therefore has a concrete correction; the final inventory-stage re-scan must establish that all 128/128 strict local targets resolve in the final exact tree. This is path resolution only. It does not validate heading fragments, commit-pinned line anchors, pull-request comment anchors, external availability, redirect identity, or whether a destination is semantically the right source for its link text.

DF-06 remains **NOT MET**. The remaining work is exhaustive live-status/redirect/semantic validation of the external destinations and authenticated interactive GitHub verification of rendered fragment, line-range and issue-comment anchors. The current GitHub connection does not expose an authenticated interactive browser session, so those claims are not made. A future file write changes the PR target SHA and requires a final exact-revision scan; the terminal inventory update must remain the final branch file write.
