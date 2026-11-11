# Documentation Foundation — Historical Preservation and Cross-Revision Comparison

**Date:** 2026-11-08  
**Repository:** `methaneex-oss/MethaneX`  
**Status:** Builder evidence report; preservation discovery and selected duplicate-document comparisons completed; archive/supersession decisions and exhaustive historical reconciliation remain open.  
**Scope:** Historical JARVIS branch discovery, branch-to-PR matching, selected document-revision comparisons, and current preservation disposition.  
**Authority boundary:** No branch deletion, file movement, archive relocation, PR retarget, rebase, merge, cherry-pick, or acceptance decision is performed or implied.

## 1. Executive result

This report closes a material portion of the Phase 1 historical-preservation follow-up with direct repository evidence.

- A GitHub branch search for `jarvis` returned **37 current branch refs**, representing **11 distinct commit tips**.
- **27 branch refs** point to the same commit, `16abca97caf77ce65d5ac901513eb2790f04c68c`. They are aliases at the same tip, not 27 distinct content revisions.
- Direct PR metadata maps the principal architecture/documentation branches to PRs #96, #97, #99, #166, #169, #171, #178, #179 and #191. Two other branch refs have no matching PR head among the 63 results returned by the repository-scoped JARVIS PR search; they are retained and not treated as disposable.
- PR #96 and PR #97 share 12 Markdown paths, and all 12 have identical blob SHAs. PR #97 adds three Markdown paths; PR #96 adds no Markdown path absent from PR #97.
- PR #97 and PR #156 share 15 Markdown paths, all byte-identical at the inspected heads. PR #156 additionally contains `docs/DEVELOPMENTAL_BRAIN_PLAN.md`.
- PR #148 and PR #156 share 16 Markdown paths; 15 are byte-identical. The sole differing path is `docs/DEVELOPMENTAL_BRAIN_PLAN.md`.
- PR #97 and PR #170 share 15 Markdown paths; 13 are byte-identical. `README.md` and `docs/JARVIS_BRAIN_MASTER_BLUEPRINT.md` differ. PR #170 adds nine Markdown documents not present in PR #97.

These comparisons establish which copies are byte-identical and which are separate revisions. They do not establish that every historical document is authoritative, accepted, or safe to move.

## 2. Branch discovery and branch-to-PR register

### 2.1 Method and snapshot

The branch search query was `jarvis`; it returned 37 branch names. Branch refs were then retrieved from the repository's paginated branch API. The following grouped register records every matching branch name and its exact current tip SHA at this snapshot.

| Current branch tip | Branch refs at that exact tip | PR relationship / disposition |
|---|---|---|
| `16abca97caf77ce65d5ac901513eb2790f04c68c` | `docs/jarvis-affective-plan`; `feat/jarvis-affective-impl`; `feat/jarvis-affective-plan`; `feat/jarvis-affective-state-impl`; `feat/jarvis-affective-state-plan`; `feat/jarvis-affective-state-plan2` through `feat/jarvis-affective-state-plan20`; `feat/jarvis-affective-state-plan-final`; `feat/jarvis-affective-state-work`; `feat/jarvis-cognitive-action-loop` | PR #96 uses `feat/jarvis-cognitive-action-loop` at this SHA. The other 26 refs are aliases at the same commit tip; do not count them as independent content revisions or delete them without an explicit branch-retention decision. |
| `c1da222e6c94aeb3f2ad000392c21fe4fc81ab25` | `feat/jarvis-affective-state` | PR #97. |
| `9ae1a3f92ccdca846074d1433734851d9483f190` | `feat/jarvis-learning-mechanisms-probe` | PR #99. |
| `04a441676c1d41833f64bc0f20f5320af6f10855` | `feat/jarvis-build-agents-clean` | No matching PR head found in the repository-scoped JARVIS PR search results inspected. Retain pending provenance confirmation. |
| `c803e9873df1c22111156d894853ef2d8832a8ea` | `docs/jarvis-project-command-governance-20261031` | PR #166. |
| `bdc980f3dcf322541556c0756aeee4eb1ff955a1` | `docs/jarvis-mcu-brain-target-analysis-20261031` | PR #169. |
| `b05434758ad4fe72815503f89bd5d2990ccb658b` | `docs/jarvis-system-architecture-foundation-20261101` | PR #171. |
| `39fe09dcf13496f5f0005ccf3f00739303e29f88` | `docs/jarvis-project-governance-rules-20261105` | PR #178; governance proposal remains proposed/unaccepted. |
| `61311fe5b44c81c4409c8ba8dc581a83bdd5dd2c` | `docs/jarvis-phase-2-whole-brain-integration-map-20261105` | PR #179. |
| `609d38ede50bbdd98a93dfed112781eacabee9fd` | `docs/jarvis-phase2-human-mcu-comparison-20261106` | PR #191; its base/dependency disposition remains unresolved. |
| `ebbda074957e0f9fb0d0f04dd9b03fe58b270a0a` | `docs/jarvis-phase-1-preservation-inventory-20261104` | No matching PR head found in the repository-scoped JARVIS PR search results inspected. Retain pending provenance confirmation. |

The grouped register accounts for all 37 branch refs returned by the `jarvis` branch search. The 63-result PR search also returned JARVIS-related PRs whose branch names do not contain `jarvis`; those are separate PR-lineage evidence and must not be omitted from future source/donor reviews.

### 2.2 Interpretation

The 27 aliases at `16abca97...` all point to the exact PR #96 head commit. They do not represent 27 different versions of the code or documentation. They are duplicate refs to one tree tip.

The two unmatched refs (`feat/jarvis-build-agents-clean` and `docs/jarvis-phase-1-preservation-inventory-20261104`) are not proven orphaned or obsolete merely because the inspected PR search did not return a matching head. They remain preserved pending a deliberate owner decision.

No branch was deleted, renamed, force-updated, or merged.

## 3. PR #96 and PR #97 duplicated-document comparison

### 3.1 Exact comparison

Trees were fetched recursively at:

- PR #96 HEAD: `16abca97caf77ce65d5ac901513eb2790f04c68c`
- PR #97 HEAD: `c1da222e6c94aeb3f2ad000392c21fe4fc81ab25`

Both trees were complete (`truncated=false`). Each contained 12 shared Markdown paths with identical blob SHAs. PR #97 had three additional Markdown paths; PR #96 had no Markdown-only path absent from PR #97.

The 12 identical shared paths are:

1. `README.md`
2. `core/cpp/tests/phase4_notes.md`
3. `docs/ARCHITECTURE.md`
4. `docs/JARVIS_BRAIN_MASTER_BLUEPRINT.md`
5. `docs/JARVIS_PHASE_2_COMPLETION.md`
6. `docs/superpowers/plans/2026-09-25-cognitive-action-feedback-loop.md`
7. `docs/superpowers/plans/2026-09-26-concept-context-prediction.md`
8. `docs/superpowers/plans/2026-09-30-developmental-cognition.md`
9. `docs/superpowers/specs/2026-09-25-cognitive-action-feedback-loop-design.md`
10. `docs/superpowers/specs/2026-09-26-concept-context-prediction-design.md`
11. `docs/superpowers/specs/2026-09-30-developmental-cognition.md`
12. `docs/superpowers/specs/2026-10-01-affective-state.md`

PR #97-only Markdown paths:

- `core/cpp/examples/README.md`
- `docs/developmental-training-environment.md`
- `docs/superpowers/plans/2026-10-01-affective-state.md`

**Disposition:** These 12 shared files do not need duplicate archive copies merely to preserve PR #96 and PR #97. Their identical blob identity is sufficient to record the shared content, while both PR histories remain preserved. PR #97's three additional documents remain associated with its own branch history.

## 4. PR #97, PR #148, PR #156 and PR #170 revision comparison

### 4.1 PR #97 versus PR #156

- Shared Markdown paths: 15.
- Identical shared blobs: 15.
- PR #156-only Markdown path: `docs/DEVELOPMENTAL_BRAIN_PLAN.md`.
- PR #97-only Markdown paths: none.

**Disposition:** For the 15 shared Markdown files, PR #156 does not contain a different document revision at the inspected heads. The additional developmental plan is a distinct artifact and must retain its PR #156 provenance.

### 4.2 PR #148 versus PR #156

- Shared Markdown paths: 16.
- Identical shared blobs: 15.
- Different shared blob: `docs/DEVELOPMENTAL_BRAIN_PLAN.md`.
- PR #148 blob: `6b447faa668c2c4a559e55fb40dbd301f53e1704`.
- PR #156 blob: `1db14e73ecc4ff4fded2791df17f34d20958c329`.

**Disposition:** The Developmental Brain Plan has two distinct revisions across these lineages. They must not be collapsed into one canonical copy without a content/authority comparison. The other 15 shared Markdown documents are byte-identical at the inspected heads.

### 4.3 PR #97 versus PR #170

- Shared Markdown paths: 15.
- Identical shared blobs: 13.
- Different shared blobs: `README.md` and `docs/JARVIS_BRAIN_MASTER_BLUEPRINT.md`.
- PR #97 blueprint blob: `9958b8a596e172488b21fce1cdc256ccde419cfe`.
- PR #170 blueprint blob: `11eb3d3abbba94116e5f4d1288856495ea0ac9e4`.
- PR #170-only Markdown documents: nine, including the Layer 0–19 traceability, language-ownership, planning-reconciliation, polyglot-governance, developmental-plan, foundation-constitution, MCU target, project-governance and Priority One trust-boundary documents.
- PR #97-only Markdown paths: none.

**Disposition:** PR #170's blueprint is a distinct later proposal, not an automatically accepted replacement for the PR #97 revision or the main-branch file. The nine additional PR #170 documents remain preserved on their source lineage and retain their own authority status. No PR #170 proposal is promoted to accepted architecture by this comparison.

## 5. Preservation disposition register

| Artifact / lineage | Evidence-based disposition |
|---|---|
| PR #96 and PR #97 shared Markdown files | Record one identical content revision with both source lineages; do not create duplicate archive copies solely because both PRs contain them. |
| PR #97-only documents | Preserve under PR #97 provenance. |
| PR #148 / PR #156 shared documents | Record 15 identical documents as shared content; preserve the distinct Developmental Brain Plan revisions separately until authority/content reconciliation. |
| PR #156 Developmental Brain Plan | Preserve exact PR #156 revision as a distinct donor/planning artifact; do not infer acceptance. |
| PR #170 Layer 0–19 and governance/planning documents | Preserve on PR #170 lineage; proposed/historical status remains subject to exact decision records. |
| PR #170 master blueprint | Preserve as a distinct revision; do not silently substitute it for main, PR #97 or the corrected PR #192 legacy-status banner. |
| PR #191 comparison | Preserve as draft bounded BM-01–BM-12 evidence; its stale-base relationship requires an authorized disposition before integration. |
| 27 branch aliases at PR #96 HEAD | Record as multiple refs to one exact tip, not 27 independent content histories. Do not delete or consolidate refs without authorization. |
| Two formerly unmatched branch refs | Ancestry is now resolved: `feat/jarvis-build-agents-clean` is an ancestor of PR #179; `docs/jarvis-phase-1-preservation-inventory-20261104` is an ancestor of PR #178. Retain the refs; no deletion or consolidation is authorized. |
| PR #178 governance proposal | Preserve as proposed/unaccepted; it is not a binding project-wide governance baseline. |
| Legacy `docs/JARVIS_BRAIN_MASTER_BLUEPRINT.md` and `docs/JARVIS_PHASE_2_COMPLETION.md` | Preserve their history and current authority labels. Do not move or delete during this gate. Their historical/proposed status must remain distinct from accepted architecture/specification decisions. |

## 6. What this closes and what remains

### Closed by this report

- Current branch discovery for the 37 refs returned by the `jarvis` branch search.
- Grouping of branch refs by exact tip SHA, exposing 27 aliases to one PR #96 commit.
- Direct PR mapping for the principal JARVIS architecture and documentation branches.
- Exact duplicate-document comparison for PR #96 versus PR #97.
- Exact shared-document comparison for PR #97 versus PR #148, PR #156 and PR #170.
- Evidence-based distinction between identical copies and genuinely different document revisions.

### Still open

1. Confirm the ownership/purpose and intended retention of the two branch refs with no matching PR head in the inspected JARVIS PR search.
2. Complete the broader PR/branch lineage map for JARVIS-related PRs whose branch names do not contain `jarvis`; the 63-result search is a discovery aid, not a proof that every historical PR has been classified.
3. Reconcile the two distinct `DEVELOPMENTAL_BRAIN_PLAN.md` revisions in PR #148 and PR #156 against their respective PR history and authority records.
4. Compare the remaining dated planning/specification artifacts across the other relevant PRs, including the PR #170 lineage, where their contents are not covered by the exact blob comparisons above.
5. Complete historical README, relative-link, fragment and external-link validation across the full preserved document set.
6. Prepare a curated archive/supersession proposal with per-artifact rationale and dependency checks. No move, copy, deletion or branch consolidation is authorized by this report.
7. Obtain the required Project Director decisions for disputed provenance/status and integration questions; do not convert Builder recommendations into accepted decisions.

**Conclusion:** The historical-preservation follow-up is materially advanced but not complete. The technical repository inventory remains complete within its original bounded scope. This report does not clear DF-08, accept any architecture proposal, select a baseline, authorize Stage A, or authorize implementation.

**End of report.**


## 7. PR #191 dependency graph — exact divergence check

The PR #191 dependency was rechecked using both relevant comparisons:

- PR #191 base `f6267456560a08054d69f7960d2951452b14017c` to PR #191 head `609d38ede50bbdd98a93dfed112781eacabee9fd`: **1 commit ahead, 0 behind**. The unique change is the addition of `docs/architecture/reports/PHASE_2_HUMAN_AND_MCU_REFERENCE_COMPARISON_2026-11-06.md`.
- PR #179 head `61311fe5b44c81c4409c8ba8dc581a83bdd5dd2c` to PR #191 head `609d38ede50bbdd98a93dfed112781eacabee9fd`: **diverged**; PR #191 is 1 commit ahead and 22 commits behind, with merge base `f6267456560a08054d69f7960d2951452b14017c`.

This distinction matters. PR #191 is a clean one-commit addition on its historical base, but it is not a descendant of the current PR #179 head. Simply retargeting the PR would not incorporate the 22 intervening commits. A current-line revision would require an explicit history-preserving rebase/cherry-pick or a new dependent branch. The Builder does not choose or execute that operation without the Project Director's explicit disposition.

**Recommendation for decision:** keep PR #191 as a historical-base review target if the immediate purpose is to review the comparison artifact in isolation; if the purpose is to integrate it into the current PR #179 line, authorize a new revision that replays its single unique document commit onto the current PR #179 head, then independently review that new exact revision. This is a recommendation, not an executed operation or acceptance decision.



## 8. Developmental Brain Plan — exact PR #148 / PR #156 content comparison

The two distinct `docs/DEVELOPMENTAL_BRAIN_PLAN.md` blobs identified in §4.2 were fetched directly:

| Source | Exact commit | Blob | Lines |
|---|---|---|---:|
| PR #148 | `be848d35d575dc0a6d48052ad1ac5265039c879e` | `6b447faa668c2c4a559e55fb40dbd301f53e1704` | 352 |
| PR #156 | `7fe212bbb0bd61116ea56581435e03b06c69b673` | `1db14e73ecc4ff4fded2791df17f34d20958c329` | 399 |

**Exact content relationship:** all 352 lines of the PR #148 file are an exact, line-for-line prefix of the PR #156 file. PR #156 adds 47 lines at the end as a new §15, “Integrated Priority-One audit checkpoint — 2026-10-31.” No earlier line was modified or removed.

The added §15 records:
- two additional adversarial corrections (mismatched evolution rollback target and feedback attestation source binding);
- a claim that four exact-head workflows passed on code-bearing commit `15d49e5fdeb5723c475922ab78fb92f97c4b3b84`, including two CTest-bearing jobs reporting 73/73 tests;
- explicit remaining Priority-One acceptance work, including production cryptographic verification, journal integrity, independent ground-truth adjudication, calibration policy and independent tester/reviewer clearance;
- a warning that factual source calibration still lacks an end-to-end demonstration of changing belief/world-model weighting and downstream planning/action selection.

The workflow results above are recorded as statements in the PR #156 document; this content comparison did not independently rerun or revalidate those workflows.

**Disposition:** The PR #156 revision is an append-only extension of the PR #148 revision, not a conflicting rewrite. The content relationship is now resolved. PR #148 and PR #156 remain separate open, draft, unmerged lineages; neither document is promoted to an accepted canonical plan by this comparison. Preserve PR #148 as the earlier exact version and PR #156 as the later extended version. Any authority/canonical-selection decision remains with the Project Director.


## 9. Expanded branch ancestry verification — 2026-11-08

A fresh repository-scoped \`jarvis\` branch search returned 37 refs, grouped into 11 exact commit tips. A fresh repository-scoped PR search for \`JARVIS\` returned 63 results. The two refs previously left without a matching PR head were checked by exact commit and ancestry comparison:

| Branch | Exact tip | Commit content | Ancestry evidence | Result |
|---|---|---|---|---|
| \`feat/jarvis-build-agents-clean\` | \`04a441676c1d41833f64bc0f20f5320af6f10855\` | Evolution orchestration header, controller/orchestrator source and orchestration test | PR #179 HEAD \`61311fe5b44c81c4409c8ba8dc581a83bdd5dd2c\` is 170 commits ahead and 0 behind | Tip is an ancestor of PR #179; prior unmatched classification resolved |
| \`docs/jarvis-phase-1-preservation-inventory-20261104\` | \`ebbda074957e0f9fb0d0f04dd9b03fe58b270a0a\` | Phase 1 whole-repository investigation report | PR #178 HEAD \`39fe09dcf13496f5f0005ccf3f00739303e29f88\` is 11 commits ahead and 0 behind | Tip is an ancestor of PR #178; prior unmatched classification resolved |

The first tip also compares as an ancestor of PR #96's exact tip. The 27 branch refs at \`16abca97caf77ce65d5ac901513eb2790f04c68c\` remain aliases to one commit, not 27 independent content revisions.

**Updated preservation disposition:** the two previously unmatched refs are no longer unresolved ancestry cases. They remain existing refs and are retained. No branch deletion or consolidation is authorized. Broader non-JARVIS-named PR/branch lineage, archive/supersession decisions and remaining historical revision classification are still open; this report does not claim repository-wide preservation completeness.


## 10. Builder correction — branch ancestry disposition — 2026-11-08

Section 5 and the earlier §6 list predate the expanded ancestry checks in §9 of this report. The two formerly unmatched refs are now mapped by exact ancestry: `feat/jarvis-build-agents-clean` tip `04a441676c1d41833f64bc0f20f5320af6f10855` is an ancestor of PR #179 HEAD `61311fe5b44c81c4409c8ba8dc581a83bdd5dd2c` (170 commits); `docs/jarvis-phase-1-preservation-inventory-20261104` tip `ebbda074957e0f9fb0d0f04dd9b03fe58b270a0a` is an ancestor of PR #178 HEAD `39fe09dcf13496f5f0005ccf3f00739303e29f88` (11 commits). The prior unmatched-ref item is closed. The 27 branch aliases at tip `16abca97caf77ce65d5ac901513eb2790f04c68c` remain aliases to one commit. No refs are deleted or consolidated.

This closes only those ancestry questions. Broader non-JARVIS-named lineage, remaining historical revision comparisons and archive/supersession disposition remain open. DF-08 remains PARTIAL.


## 11. Expanded repository lineage and link-integrity verification — 2026-11-08

This addendum records the broader bounded discovery and validation work completed after §10. Earlier snapshots remain historical; the exact parent revision for this addendum is PR #192 HEAD `93eb06e2e244518a3b86df1f3add4aba038f461c`, base `61311fe5b44c81c4409c8ba8dc581a83bdd5dd2c`, open/draft/unmerged, with 26 changed paths.

### 11.1 Repository-wide discovery scope

- Paginated branch listing: 245 branch refs across three pages; 203 distinct tip SHAs.
- Documentation-family branch prefixes (`docs/`, `architecture/`, `research/`, `plan/`, `review/`, `spec/`): 37 refs and 37 distinct tips.
- JARVIS-name branch search: 37 refs and 11 distinct tips; 27 refs are aliases at the PR #96 tip `16abca97caf77ce65d5ac901513eb2790f04c68c`. The two formerly unmatched refs are now mapped by ancestry: `feat/jarvis-build-agents-clean` is an ancestor of PR #179, and `docs/jarvis-phase-1-preservation-inventory-20261104` is an ancestor of PR #178.
- Paginated PR listing: 184 PRs across two pages.
- Documentation PR lineage: 28 PRs (#160, #164, #166–#175, #178–#193) with 108 changed documentation paths. PR #176 was source/test-only and excluded from this documentation-path total.
- The 34 additional paths across PRs #160, #164, #166–#170 and #180–#190 were fetched at exact PR heads; each returned blob SHA matched the PR-files API. The expanded 108-path register is in `docs/architecture/inventory/HISTORICAL_DOCUMENTATION_PRESERVATION_REGISTER_2026-11-08.md` §5.

### 11.2 Current PR #192 relative-link validation

At PR #192 HEAD `8b6c257bc40748e3d96a0fdf2272b774f54d7a17`, all 26 changed paths were fetched and their returned blob SHAs matched the PR-files API. The recursive tree contained 255 entries / 227 blobs and was not truncated. The Markdown scan found 84 repository-relative link occurrences across the 26 changed documents; all 84 target paths exist. No missing repository-relative target or local Markdown fragment was found.

This check establishes path existence. It is not, by itself, proof of semantic suitability or external reachability.

### 11.3 Historical source links and line anchors

The Phase 2 capability-to-source map contains 89 immutable GitHub blob links across 45 unique commit/path pairs and five pinned commits. All 45 exact commit/path pairs were fetched. Every fetched blob SHA matched the SHA recorded alongside its source link. Of the 89 links, 76 carry line anchors and 13 do not. All 76 anchored ranges were within the exact fetched file lengths after one verified correction:

- `core/cpp/tests/cognitive_runtime_goal_feedback_suite.cpp` at commit `c1da222e6c94aeb3f2ad000392c21fe4fc81ab25` contains 84 lines, not 90. The map link was corrected from `#L1-L90` to `#L1-L84`.

The Phase 1 repository-investigation evidence index was also corrected to use immutable commit SHAs instead of mutable branch names for the three PR #175 Gate A report links, the Phase 1 inventory tree link, and the Priority-One trust-boundary contract. All target paths were fetched at those exact immutable revisions. The historical PR #173 evidence label was corrected to state that its acceptance provenance remains UNVERIFIED/PROPOSED; PR #174 is explicitly scoped to planning-baseline acceptance only.

### 11.4 External URL verification

The 26 changed documents contain 189 raw external URL occurrences. All GitHub PR references resolve to PRs present in the complete 184-PR listing. The five linked Actions runs were retrievable and completed successfully. The three artifact IDs referenced from run `40565468650` were present in that run's artifact listing and were not expired. The pinned GitHub blob/tree targets and the comparison link were checked against exact commits and API metadata; the comparison from `82c49a75bd30de2962879f044776f4bf2391970a` to `c1da222e6c94aeb3f2ad000392c21fe4fc81ab25` reports 18 commits ahead and 0 behind.

One non-GitHub URL is a ChatGPT shared-conversation pointer in the PR #174 recovery record. It could not be fetched by the available external retrieval endpoint (disabled access). It is retained as a historical pointer and is classified **ACCESS-LIMITED / NOT INDEPENDENTLY VERIFIED**, not as a confirmed broken URL. No other non-GitHub external destination was found in the 26-file scan.

### 11.5 Authority and preservation boundaries

- PR #173 remains UNVERIFIED/PROPOSED for acceptance provenance: its discussion contains two Builder-authored comments, with zero formal reviews and zero inline review comments. PR #174's later decision does not replace a primary PR #173 decision.
- PR #174's accepted planning-baseline event is present at comment `6604790481`; current specification HEAD `922912283d173e24df891ba23d0e2dfc17e0f4b4` correctly scopes that acceptance and keeps F-02/F-03 open. The original F-02/F-03 review report and inline annotations were not recoverable from the PR review endpoints.
- PR #191 remains diverged from PR #179: 1 unique commit ahead / 22 behind; no ancestry operation is authorized.
- PR #178 governance remains proposed/unaccepted. PR #193 remains a separate deferred/non-operative roadmap lineage.
- Review-labelled reports from the same repository account do not establish a separate reviewer identity. The same GPT-6 identity is explicitly disclosed in several reports; another report lacks an identity/independence disclosure. None qualifies for DF-11.
- No branch was deleted, no artifact moved or archived, and no PR was merged, rebased, retargeted or cherry-picked. Archive/supersession and disputed authority decisions remain with the Project Director.

**Updated Builder evidence disposition:** The bounded link, anchor, external-reference and documentation-lineage discovery work is now complete for the current PR #192 package and the enumerated historical PR set. The one access-limited ChatGPT pointer remains disclosed. This does not satisfy DF-09 fresh-reader execution, DF-11 qualifying independent review, or DF-12 Project Director acceptance. Stage A remains held and implementation remains unauthorized.


## 12. Phase 2 map revision delta — 2026-11-09

A final exact-HEAD fetch found that the Phase 2 integration map's blob had advanced since §11. The prior blob recorded in the earlier inventory was `b1c203121879aa50ecad30e71e2e1800456bcd9c`; the current blob at PR #192 closeout-start HEAD `5031fb9348dd10664023df5338125acf4b8ef676` is `9dd776920d0a479a9d7275acc821e12c266623d9`.

The two map contents were compared directly after normalizing the two line-anchor corrections below; the normalized contents are identical. The 89 immutable source-link occurrences and 45 unique commit/path pairs are unchanged, as are their source blob identity annotations. The only differences are:

- `core/cpp/src/action_execution.cpp` at commit `1273ddbcd0087d189e01388ded2d362fb1e058d2`: anchor corrected from `#L18-L78` to `#L18-L77`. The exact pinned file was previously fetched as 100 lines; the revised range is within the file.
- `core/cpp/tests/cognitive_runtime_goal_feedback_suite.cpp` at commit `c1da222e6c94aeb3f2ad000392c21fe4fc81ab25`: anchor corrected from `#L1-L90` to `#L1-L84`. The exact pinned file was previously fetched as 84 lines; the revised range matches its full length.

Because the normalized map contents are identical, the previously recorded verification of all 45 pinned source blobs and the other 74 anchor ranges carries forward unchanged; the two revised ranges above are valid against their exact pinned file lengths. The current map therefore retains 89 links, 45 unique commit/path pairs, 76 anchored ranges and 13 links without anchors. This is a bounded source-map validation, not a claim that every prose statement in the map has been independently re-audited.

**Disposition:** the Phase 2 map revision delta is reconciled. The historical source-link evidence in §11 applies to the current map blob after these two explicit anchor corrections. The separate access-limited ChatGPT shared-conversation pointer remains unverified as previously disclosed.


---

## 13. Exact-current-HEAD changed-file link validation after reviewer corrections — 2026-11-10

**Validated PR #192 HEAD:** `b246ffbac96b770b0a16efd14c29f8f6a8ec3c28`  
**Base:** `61311fe5b44c81c4409c8ba8dc581a83bdd5dd2c`  
**PR state:** open, non-draft, unmerged.  
**Changed files:** 33.  
**Repository tree:** 263 entries, recursive response not truncated.

The complete 33-path PR-files list was reconciled against the recursive Git tree at the exact HEAD. All 33 paths existed and all 33 PR-file blob SHAs matched the corresponding tree blob SHAs. There were zero missing changed paths and zero blob mismatches.

A bounded scan of inline Markdown links in all 33 changed files found:
- 98 repository-relative inline Markdown link occurrences;
- zero missing repository-relative targets in the exact tree;
- zero inline Markdown heading-fragment or line-anchor links in the scanned changed files;
- 111 external HTTP(S) inline Markdown link occurrences identified but not fetched or reachability-tested.

**Scope limitations:** This scan does not establish correctness of reference-style Markdown links, raw HTML `href` attributes, semantic relevance of destinations, renderer-specific anchor behavior, all historical links outside the 33 changed files, or external destination reachability. Therefore DF-06 remains **PARTIAL**. Do not describe this as exhaustive link validation.

The scan is a direct response to the Grok review's recommendation to refresh link/path validation at the exact reviewed revision and to synchronize the inventory after the final write. The inventory must now record this 33-path parent snapshot. Any subsequent document write invalidates this snapshot and requires a new parent manifest.

**Gate disposition:** DF-06 PARTIAL; DF-08 PARTIAL; DF-09 OPEN pending repeat CLEAR Nemotron assessment; DF-11 current-head review/qualification unresolved; DF-12 outstanding; Stage A HELD; implementation NOT AUTHORIZED.


## 14. Historical retention and supersession disposition — 2026-11-11

### 14.1 Controlling retention rule

The Project Director's standing instruction is that historical material must be preserved and must not be deleted or silently superseded merely to clean the documentation tree. The disposition for the initial foundation is therefore **retain in place**:

- No historical file is deleted, moved, renamed, overwritten, or relocated to an archive by this work.
- No branch is deleted, renamed, force-updated, or consolidated.
- No PR is merged, closed, rebased, retargeted, cherry-picked or replayed as an archive operation.
- “Superseded” is an interpretive/status label only. It means “not the current controlling document for this specific question”; it never means that the original artifact is removed, its historical content rewritten, or its exact source identity discarded.
- Where authority or revision status is disputed, the artifact remains **UNRESOLVED / PRESERVED**, not silently demoted.
- Identical copies are recorded by shared blob identity; distinct blob revisions remain separate records. No duplicate-copy deletion is authorized.

### 14.2 Completed discovery scope and retained evidence

The repository-wide discovery already recorded in §11.1 is the bounded census used for this disposition: 245 branch refs across three pages / 203 distinct tips; 37 documentation-family refs; 37 JARVIS-name refs / 11 distinct tips; 184 PRs across two pages; and 28 documentation PRs with 108 changed documentation paths. The two JARVIS-name refs initially unmatched to a PR head were mapped by ancestry: `feat/jarvis-build-agents-clean` is an ancestor of PR #179 and `docs/jarvis-phase-1-preservation-inventory-20261104` is an ancestor of PR #178. The 27 branch aliases at the PR #96 tip are aliases, not 27 distinct content versions.

The older lineage comparisons remain part of the preservation evidence:
- PR #96/#97: 12 shared Markdown paths are byte-identical; PR #97 contributes three additional Markdown paths.
- PR #97/#156: 15 shared Markdown paths are byte-identical; PR #156 adds the separate `docs/DEVELOPMENTAL_BRAIN_PLAN.md` artifact.
- PR #148/#156: 15 of 16 shared Markdown paths are identical; the Developmental Brain Plan is a distinct revision and both versions are retained.
- PR #97/#170: 13 of 15 shared Markdown paths are identical; README and the master blueprint differ, and PR #170 contributes nine additional Markdown documents.

The 108-path / 28-PR register and exact source blob identities remain the canonical preservation locator. This report does not claim that all repository content outside the enumerated documentation-family and PR discovery scope has been semantically reviewed.

### 14.3 Per-lineage status and retention rationale

| Lineage | Retained artifact class | Current interpretation | Retention rationale |
|---|---|---|---|
| #160, #164 | Trust-boundary and technology-audit inputs | Historical research/contract inputs; not a current technology decision | Preserve design rationale and security constraints without activating old technology choices |
| #166–#168 | Governance and language-ownership proposals | Historical proposals; not binding governance or current technology selection | Preserve alternatives and rejected/unaccepted governance history |
| #169 | MCU behavioral reference | Fictional functional inspiration only | Preserve as a product-vision lens, not empirical or implementation evidence |
| #170 | Layer 0–19 blueprint, traceability, planning reconciliation and foundation constitution | Historical/superseded planning inputs; not current whole-Brain architecture or implementation order | Preserve original content and exact revisions so later planning can compare rather than erase prior reasoning |
| #171 | Whole-system foundation and research | Documents 00/01 have separate exact-scope approval records; research is not blanket-approved | Preserve scope-specific decisions and the wider research context separately |
| #172 | Foundational capability investigation and corrections | Accepted planning input at exact recorded revision; not a whole-Brain completeness proof | Preserve the accepted input and its correction history |
| #173 | Brain Foundation Architecture and review correction | Accepted planning baseline at exact HEAD `97191111bc2573c14d391c0af9628db7b11f194b`; authorization limited to the detailed mechanism specification stage | Preserve the exact accepted revision, primary conversation evidence extract and later GitHub transcription as distinct evidence classes |
| #174 | Brain Mechanism Specification, source audit and corrections | Accepted specification baseline at exact HEAD `0811a59e46bf934e32e794f90e4e7d18d4e2bd97`; F-02/F-03 remain open | Preserve accepted baseline and follow-on obligations without rewriting the accepted content |
| #175 | Implementation plan and Gate A/Gate B evidence | Deferred proposal; Gate A not cleared; no implementation baseline selected | Preserve the plan and no-go evidence; do not execute its proposed sequence before whole-Brain planning |
| #178 | Phase 1 inventory and governance proposal | Inventory/preservation evidence retained; governance proposal remains unaccepted | Preserve both the evidence and the proposal's unaccepted status |
| #179 | BM-01–BM-12 source integration map and closure evidence | Bounded source-mapping work; not whole-Brain completeness or acceptance | Preserve exact mapping and its scope limits |
| #180–#190 | Historical map revisions, reliability contracts and review reports | Retain each exact PR revision; closed PR #180 remains preserved; reviewer identity and acceptance are determined by evidence, not titles | Preserve divergent analyses and reviewer provenance, including same-account limitations |
| #191 | Human-cognition / MCU reference comparison | Draft, not accepted; read-only content review completed; disposition still pending | Retain because it is useful bounded reference evidence and no disposition decision has been made |
| #192 | Documentation foundation correction and current navigation package | Current open, non-draft PR; not merged or accepted | Preserve the current working foundation package on its own lineage |
| #193 | Deferred implementation plan and continuity handoff | Open draft, separate #175-derived lineage; implementation plan remains non-operative | Preserve its separate history and current hold; do not integrate it into #192 yet |

### 14.4 DF-08 disposition

**Builder evidence status: RESOLVED within the defined historical-discovery scope.** The required preservation controls are now explicit and actionable: the bounded repository census and 108-path/28-PR register are retained; selected cross-revision comparisons are recorded; ambiguous provenance remains qualified; all historical material is retained in place; and supersession is non-destructive and visible-only. No archive relocation or deletion is required to satisfy the user's preservation constraint, and none is performed.

This is not a claim that every historical document has been independently accepted, nor that every line of every old report has been semantically re-reviewed. It is not DF-12 foundation acceptance. The remaining DF-06 external-link/semantic/anchor closure and DF-09 CLEAR reader result remain separate gates. PR #191 disposition and PR #192/#193 integration remain unchanged and unauthorized.


## 15. Exact-current PR #192 link and destination revalidation — 2026-11-11

### 15.1 Exact snapshot and changed-file delta

The live PR #192 HEAD at the start of this revalidation was `9a669d2545862d76b3935dfc9555cac278765169` (open, non-draft, unmerged). A GitHub commit comparison from the previously audited parent `c0778822b201197be2ddc34057ec7259afbab1f7` to that HEAD reports 11 commits ahead, 0 behind, and exactly three changed files:

| File | Exact current blob SHA | Lines |
|---|---|---:|
| `docs/architecture/00_JARVIS_PLANNING_DOCUMENTATION_INDEX_2026-11-07.md` | `44ce84e18a9252f2fee73ea3c665303b53cf8765` | 633 |
| `docs/architecture/inventory/00_JARVIS_DOCUMENTATION_AND_ARTIFACT_INVENTORY_2026-11-04.md` | `c294e770f7cf0e3d289ee70a21a58787a4010691` | 2357 |
| `docs/architecture/reports/DOCUMENTATION_FOUNDATION_OUTSTANDING_WORK_CLOSURE_AND_AUTHORITY_REGISTER_2026-11-08.md` | `27bafb7d7d6aec1a7386628ec179b7ffb5b5f885` | 878 |

The other 34 files in PR #192's 37-file package are unchanged from the previously audited parent. The earlier §28.1 audit fetched all 37 files and resolved all discovered repository-relative targets. The current recheck therefore repeated the full validation on the three changed files and retained the exact unchanged-file comparison as the basis for the other 34.

### 15.2 Repository-relative paths and Markdown forms

The three changed files contain 45 repository-relative inline Markdown link occurrences and 24 unique repository-relative target paths. Every unique target was fetched successfully from the exact current PR #192 branch. No missing target was found.

The three changed files were also checked for reference-style Markdown link definitions, raw HTML `href` attributes and autolink URL forms. None were present. This avoids treating the inline-link scan as if it had covered syntax that the documents do not use.

### 15.3 Cross-branch source pointers and line anchors

The current index's immutable cross-branch links were fetched at their exact commit/path pairs, including the PR #171, #172, historical accepted PR #173, current status-clarified PR #174, PR #191, PR #175 and governance/source-audit references. All 13 explicit pinned paths checked in the current index/inventory set resolve.

The Phase 2 source-integration map remains at blob `9dd776920d0a479a9d7275acc821e12c266623d9`, unchanged from the prior exact-parent audit. Its 89 immutable source references resolve to 45 unique commit/path pairs; all 45 source files were fetched, and all 76 cited line-anchor ranges were checked against exact source-file line counts. The two stale ranges previously found were already corrected in the map and in PR #179. The Phase 1 source-audit report's 18 additional immutable file references were also fetched successfully. This verifies path existence and line-bound validity; it does not claim that GitHub's rendered anchor UI was manually inspected for every anchor.

### 15.4 GitHub PR, Actions and artifact destinations

Every distinct GitHub PR destination discovered in the package was fetched successfully: PRs #96, #97, #99, #148, #150, #151, #155, #156, #171, #172, #173, #174, #175, #176, #178, #179, #191, #192 and #193. Their live open/closed/merged states were recorded separately from historical claims.

Every distinct GitHub Actions run destination discovered in the package was fetched successfully and returned completed jobs. The checked run IDs were: `40243557728`, `40419118694`, `40565468650`, `40788714686`, `40788714735`, `41808525486`, `41808525492`, `41808525499`, `41808525557`, `42080973918`, `42834248124`, `42879721340`, `42909224258`, `42970930733`, `42976840057`, `43016629593`, `43018312917` and `43019119856`. The three linked DLT-002 artifacts on run `40565468650` (IDs `12764655498`, `12763543000` and `12763204259`) were confirmed present and unexpired. The historical ChatGPT shared-conversation pointer remains literal inline text with an explicit access-limited qualification; it is not a clickable navigation dependency and is not represented as reachable.

### 15.5 DF-06 criterion disposition

DF-06 requires durable cross-document links: exact commit-pinned paths for document/source references, with PR links retained for discussion context. The checks above cover the current PR #192 package, all changed-file relative targets, the unchanged-file comparison, the enumerated pinned source files, the source-map references/line ranges, and the GitHub PR/Actions destinations. The only inaccessible external historical pointer is explicitly non-clickable and access-qualified.

**Historical Builder disposition (2026-11-11; superseded):** At the time of this bounded audit, the Builder assessed DF-06 as resolved within the Initial Documentation Foundation package and its enumerated immutable source/link scope. This was a bounded technical disposition, not proof of complete semantic relevance, all applicable external destination reachability, renderer-specific behavior, or every applicable historical/cross-branch link. The Project Director subsequently selected the full-resolution requirement (decision B), and the controlling register §32.2 records **DF-06 NOT MET**. This historical bounded result must not be presented as current gate clearance. The evidence above remains valid for the checks it actually performed.

## 16. DF-08 criterion-to-evidence reconciliation — 2026-11-11

The governing DF-08 exit criterion is: **“Historical work is preserved — No historical evidence is deleted or silently superseded; open preservation follow-up is visible.”** It does not require every historical artifact to be semantically re-reviewed, every source branch to be merged, or a destructive archive relocation. The initial gate explicitly defers full historical branch-to-PR/archive curation beyond the bounded foundational-document map (§7).

| Criterion element | Evidence | Result |
|---|---|---|
| No historical file or branch is deleted, moved, renamed, overwritten or archive-relocated by this work | Retain-in-place policy in §14.1; PR/branch operations explicitly prohibited; no destructive operation performed | Satisfied |
| Supersession is visible and non-destructive | §14.1 defines superseded as an interpretive label only; original artifact and exact revision remain preserved | Satisfied |
| Current foundational lineage is discoverable | Paginated census of 245 branch refs / 203 distinct tips and 184 PRs; 28 documentation PRs and 108 changed documentation paths; exact PR heads/blobs in the inventory | Satisfied within declared foundational scope |
| Ambiguous ancestry and duplicate content are not silently collapsed | Two unmatched refs mapped by ancestry; 27 aliases identified as one tip; selected #96/#97/#148/#156/#170 comparisons; distinct Developmental Brain Plan revisions retained | Satisfied within enumerated comparisons |
| Unresolved or unaccepted historical items remain visible | PR #191, #192/#193, governance proposal, PR #173 sufficiency supersession and other open dispositions remain labelled proposed/open/unresolved; no artifact is promoted by retention | Satisfied |
| Broader repository-wide semantic archive curation | Explicitly deferred by the initial gate §7; outside DF-08's stated exit criterion | Deferred, not a DF-08 defect |

**Builder disposition: DF-08 RESOLVED against the exact stated exit criterion and bounded foundational-document scope.** The census is not inflated into a claim that every repository document has been semantically audited. Open preservation questions outside this gate remain visible and are not silently marked complete.

## 17. Current PR #191 dependency recheck — 2026-11-11

PR #191 remains open, draft and unmerged at `609d38ede50bbdd98a93dfed112781eacabee9fd`. Its sole changed file remains the 219-line human/MCU reference comparison. A fresh comparison against the current PR #179 head `d30237b81c3695f2a7cb980144b221bbd42ce548` returns **diverged: 1 commit ahead, 23 commits behind**, with merge base `f6267456560a08054d69f7960d2951452b14017c`. The one unique commit adds only the comparison document.

The read-only content review remains valid: the report is a bounded BM-01–BM-12 reference comparison, not whole-Brain completeness evidence. Its nine human-cognition citations were checked against publisher/PubMed/official sources. The Marvel AI guide is a general Marvel fictional-AI reference, not a direct source for the MCU film portrayal; the report must not overstate that citation. No content defect requiring deletion was identified.

**Builder recommendation for Project Director:** retain PR #191 as a separate, clearly bounded reference artifact; do not retarget it alone or rebase/cherry-pick it without an explicit integration decision. Its current base is stale, but its unique document can be linked and reviewed at its immutable head. This recommendation is not a PR disposition or integration authorization. The Project Director's decision remains pending.

**Scope boundary:** DF-06 and DF-08 Builder closure evidence does not close DF-09, waive/reinstate DF-11, decide PR #191, accept DF-12, or authorize PR integration or Stage A.

## 18. PR #192 full changed-path inline-link sweep — 2026-11-11

A bounded static sweep was performed against all 38 paths in the PR #192 changed-file list at the pre-sweep tree revision `8c5e688e3f83c582cde7ab0190d9d748edc3e967`. All 38 files were fetched from that exact revision. The sweep extracted Markdown inline links and HTTP(S) autolinks from those files and resolved repository-relative paths against the exact recursive Git tree (268 entries; not truncated).

| Check | Result |
|---|---:|
| Changed paths fetched | 38 / 38 |
| Recursive tree entries | 268 (complete, not truncated) |
| Inline Markdown links and HTTP(S) autolinks extracted | 316 |
| External HTTP(S) destinations | 199 |
| Repository-relative targets | 117 |
| Repository-relative targets present in the tree after correction | 117 / 117 |
| Standalone same-file fragment links | 0 |

**Correction made:** the sweep found one cross-branch relative link in `docs/README.md` to the PR #173 inherited-mechanism audit. That target does not exist on the PR #192 tree because it belongs to the separate PR #173 branch. The link is now pinned to the exact PR #173 HEAD `756724b95e093ac48fcd95c5587117c0a4d8f3c0`; the target was fetched successfully and its blob is `037dc71df9e508c0cc08e96a42b41aa7ba5bc041`. This removes the only missing repository-relative target found by the sweep.

**Limits:** this extraction is not a complete Markdown parser and does not claim to enumerate reference-style links, every raw URL form, or all link semantics. The 199 external URLs were inventoried, not individually re-fetched in this sweep. Existing exact-revision checks remain as recorded in §§10–15, including the 45 unique Phase 2 source files and 76 cited line ranges, and the enumerated GitHub PR/Actions/artifact destinations. Renderer-specific behavior for GitHub line anchors and rendered fragments has not been established by this static pass. Therefore this section does **not** close DF-06; DF-06 remains **NOT MET** until the remaining full-resolution criteria are evidenced.


## 19. Exact-current PR #192 Builder link revalidation — 2026-11-11

### 19.1 Exact revision and changed-file coverage

The live PR #192 head was re-fetched as `c060ad15e8e5bf86d9b359b88e696cc1fe995a54`, open/non-draft/unmerged, with 38 changed paths. All 38 paths were fetched at that exact revision. The recursive tree contains 268 entries and reports `truncated=false`.

A bounded scan of inline Markdown links, image links, reference definitions and HTTP(S) autolinks in those 38 files found:

| Item | Result |
|---|---:|
| Changed files fetched at exact HEAD | 38 / 38 |
| Recursive tree entries | 268 (complete) |
| Extracted link occurrences | 316 |
| Repository-relative targets | 116 |
| Missing repository-relative targets | 0 |
| GitHub HTTP(S) link occurrences | 200 |
| Local relative heading-fragment links found | 0 |

All 116 relative targets resolve against the exact `c060ad1` tree. This count differs from §18's earlier 117 relative / 199 external split because the cross-branch PR #173 source reference is now an explicit immutable GitHub blob URL rather than a relative path. The total extracted occurrence count remains 316.

The historical ChatGPT shared-conversation pointer is retained as literal text in the PR #174 provenance-recovery record, outside the Markdown-link extraction above. It remains ACCESS-LIMITED / NOT INDEPENDENTLY VERIFIED and is not represented as a clickable navigation dependency.

### 19.2 External GitHub destination checks

The following previously enumerated destination classes were rechecked against the current repository state:

- 18 linked GitHub Actions run IDs: all resolved and returned `status=completed`, `conclusion=success`.
- PR metadata links for #96, #97, #164, #171, #172, #173, #174, #175, #178, #179, #191, #192 and #193: all resolved.
- Project Director provenance comments #6752144835 and #6604790481: both fetched successfully; their contents continue to support the exact-scope distinctions recorded in the index.
- DLT-002 artifact IDs #12764655498, #12763543000 and #12763204259 on run #40565468650: all remain present and unexpired.
- The Phase 2 map remains blob `9dd776920d0a479a9d7275acc821e12c266623d9`; its 89 immutable source links map to 45 exact commit/path pairs. The previously recorded exact-blob checks and 76 in-range line-anchor checks remain applicable to those immutable source revisions.
- The PR #192 copy contains the two corrected source line ranges from PR #179's latest correction: `action_execution.cpp#L18-L77` and `cognitive_runtime_goal_feedback_suite.cpp#L1-L84`.

These checks establish destination metadata/path availability for the enumerated GitHub resources. They do not by themselves establish that every destination is semantically relevant to the sentence or requirement that cites it.

### 19.3 Semantic and renderer-specific limits

The current pass does not claim a complete link-by-link semantic audit of every source citation. The source-map descriptions and adjacent analysis provide a traceable rationale, but a full DF-06 semantic-relevance determination requires examining each cited source passage against the specific claim it is intended to support, not merely confirming its blob identity and line range.

The available GitHub connector returns source-file text for blob URLs; it does not expose GitHub's rendered Markdown/file viewer. A browser retrieval attempt for a representative line-anchor URL returned a cache miss. Therefore GitHub's rendered fragment/line-anchor behavior has not been verified in the rendered UI. Static line-range validity is not a substitute for that check.

### 19.4 Current DF-06 disposition

**DF-06 remains NOT MET.** The current exact-head relative-path check is complete with zero missing targets; the enumerated GitHub destinations and source identities have bounded verification evidence; the two stale source anchors are corrected in the current PR #192 map copy. Remaining full-resolution work is:

1. Complete the semantic relevance review of every applicable link in the in-scope documentation package.
2. Verify rendered GitHub fragment/line-anchor behavior through an actual rendered UI or an explicitly accepted renderer test.
3. Resolve the access-limited historical ChatGPT pointer's status with primary-source access, or obtain an explicit Project Director determination that its disclosed non-clickable historical-pointer treatment satisfies the criterion.
4. Reconcile any remaining applicable historical/cross-branch links not covered by the enumerated immutable source set.

No full DF-06 closure is claimed. This addendum is Builder technical evidence only; it is not an independent review or Project Director gate decision.
