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
