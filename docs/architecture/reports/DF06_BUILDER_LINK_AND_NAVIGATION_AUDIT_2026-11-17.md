# DF-06 Builder Link and Navigation Audit — 2026-11-17

**Repository:** `methaneex-oss/MethaneX`  
**PR:** #192 — Documentation Foundation  
**Branch:** `docs/whole-brain-planning-scope-correction-20261107`  
**Exact source revision audited:** `2df41432b83f1f627a049c0b9c1fe2a03b661ace`  
**PR state at audit start:** open, non-draft, unmerged; 40 changed files.  
**Audit role:** Builder-side static and repository-evidence audit. This is not an Independent Reviewer verdict, DF-09 fresh-reader result, DF-12 Project Director acceptance, or gate-closure decision.

## 1. Scope and method

The live PR metadata, complete paginated changed-file list, PR patch inventory, and recursive Git tree were retrieved at the exact revision above. GitHub reported 40 changed files; the paginated filename listing contained 40 unique paths; the recursive tree was not truncated and contained 241 blobs. All 40 changed paths were confirmed present in the tree.

All 40 changed files were fetched by exact commit SHA. This included Markdown documents, templates, and the three JSON fresh-reader evidence artifacts. A static parser inspected Markdown inline links, reference-link definitions, and HTML `href`/`src` attributes. Relative paths were normalized against each source file and checked against the exact revision's complete repository tree, including `.md`, `README.md`, and `index.md` resolution conventions.

The four batches produced 118 relative/local link occurrences. All 118 targets resolved to an existing repository path. No missing relative target was found in this sweep.

The current PR's two navigation documents were separately checked: `docs/README.md` (35 local links) and the planning index (41 local links), for 76 local-link occurrences with zero missing targets. These counts are subsets of the 118-occurrence whole-PR sweep, not additional occurrences.

## 2. Current-revision inventory

- Changed paths: 40 unique.
- Changed paths present in the exact revision tree: 40/40.
- Recursive tree: 241 blobs; `truncated=false`.
- Changed files successfully fetched: 40/40.
- Relative/local link occurrences parsed: 118.
- Missing relative/local targets: 0.
- Exact-commit source files for historical Phase 2 citations: the prior preservation audit records 89 source citations across 45 exact commit/path pairs and 76 checked line ranges. That earlier evidence is preserved in `DOCUMENTATION_FOUNDATION_PRESERVATION_AND_LINK_VALIDATION_2026-11-08.md`; it is not re-labelled as a new 2026-11-17 run.

## 3. Corrected navigation defects

### DF06-01 — Assignment reference was not a clickable link

The planning index §99 previously rendered the canonical Builder-to-xAI assignment path as inline code. The inventory §100.0 then said it was “linked from the controlling index,” which was inaccurate.

Correction required/applied in the follow-up revision: convert the index path to a relative Markdown link and change the inventory description to say “referenced” unless it links directly.

Canonical assignment:
`docs/architecture/reports/BUILDER_TO_XAI_EXACT_REVISION_RE_REVIEW_REQUEST_PR173_PR195_2026-11-17.md`

### DF06-02 — Exact-revision xAI reports lacked direct index navigation

The planning index §100 identified the two report paths and blob SHAs but did not provide clickable destinations. Because the reports live on separate PR branches, relative paths from PR #192 would be invalid.

Correction required/applied in the follow-up revision: use immutable commit-pinned GitHub blob links:
- PR #173 report: `a96af5b18d3a1d580ff56cff6191240893bceeb5`, report blob `7bd31a709ec8015a1ec5441e52af7c1e28c495f6`.
- PR #195 report: `89385d3165e8c5b895fee6453247f4d732047dc0`, report blob `d7933ece34775e5b5a09435a01c290b99ba5c895`.

Both report files were fetched at those immutable commits and their blob SHAs matched the planning index.

## 4. Rendered GitHub anchors — still blocked

The historical Phase 2 integration map contains many commit-pinned GitHub source links with line fragments, for example `#L155-L223`, `#L140-L158`, and other line ranges. The preservation report's source-identity and line-range checks establish that the referenced files and line ranges existed at the reviewed commits. They do not establish that GitHub's rendered blob page scrolls to the intended fragment.

A direct browser retrieval attempt for a representative GitHub blob URL with `#L155-L223` returned a fetch-level `DisabledError`. The GitHub repository connector returns normalized source content and strips the URL fragment; it therefore cannot establish browser scroll behavior. No browser-capable GitHub session was available in this Builder audit.

**Result:** actual rendered line/fragment navigation remains unverified. Static source checks must not be represented as rendered-browser verification. DF-06 cannot be marked MET on the evidence currently available.

## 5. External and historical destinations

The existing preservation/link-validation report records the prior Builder checks of semantic relevance, enumerated external destinations, historical/cross-branch references, relative-path integrity, 89 source citations, and 76 line ranges. Those historical results remain bound to the source revision and coverage documented in that report.

This audit re-fetched the two current xAI report targets, confirmed their exact report blobs, and checked all current-PR relative paths. It did not re-run a live HTTP status check against every external URL or every historical Actions artifact URL. Such destinations must be reported as historically checked or not freshly revalidated, not silently upgraded to current-live verification.

## 6. Disposition

- DF06-01: corrected by making the assignment destination clickable and reconciling the inventory wording.
- DF06-02: corrected by making both exact-revision xAI reports directly navigable from the index.
- Relative/local path integrity: **PASS** for the 118 parsed occurrences at the exact source revision.
- Rendered GitHub line/fragment behavior: **UNVERIFIED / BLOCKED**.
- Exhaustive live external URL revalidation: **NOT PERFORMED in this run**; prior documented checks remain historical evidence.
- DF-06 overall: **NOT MET pending rendered-anchor evidence and any required fresh external-destination recheck**.

## 7. Reproducibility and boundaries

Repeat the static path check against the final PR #192 HEAD, not the source SHA recorded above, after the Builder corrections are committed. Re-fetch the 40/41-file inventory and verify the changed-file count and blob identities. A reviewer with an authenticated normal GitHub browser must open representative line-fragment links from the final exact revision, confirm that the target file loads and the viewport lands at the cited line range, and record the tested URLs and outcomes. Expand this to every distinct line-anchor pattern/target family identified in the preservation register.

DF-09 must be independently assessed against the final frozen PR #192 HEAD. DF-12 remains a Project Director decision. DF-10 inventory closeout is separate. PR #173 architecture acceptance, CF-26/CF-27, PR #195 F-195-07, Stage A, implementation, source-baseline selection, integration, merge, and deployment remain outside this audit and unchanged.
