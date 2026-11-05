# Phase 1 Review Corrections and Scope Reconciliation — 2026-11-05

**Repository:** `methaneex-oss/MethaneX`  
**Audited source baseline:** `1273ddbcd0087d189e01388ded2d362fb1e058d2`  
**Phase 1 report:** `docs/architecture/reports/PHASE_1_WHOLE_REPOSITORY_INVESTIGATION_AND_REUSE_AUDIT_2026-11-04.md`  
**Governance proposal:** `docs/governance/JARVIS_PROJECT_GOVERNANCE_AND_BUILDER_RULES.md`  
**Purpose:** Address the five findings (F1–F5) and three governance refinements (G1–G3) from the 2026-11-05 review without restarting Phase 1 or changing runtime code.

## 1. Disposition summary

| Finding | Disposition | Evidence / remaining boundary |
|---|---|---|
| F1 — PR #174 authority chronology | **Reconciled with a qualification** | The Project Director's formal acceptance comment is confirmed in PR #174 issue comment #6604790481 for exact HEAD `0811a59e46bf934e32e794f90e4e7d18d4e2bd97`. Later F-02/F-03 findings were supplied in a subsequent review report in this conversation. They do not erase the historical acceptance; they create current specification-correction obligations. The later report is not present as a submitted GitHub PR review; the PR review-list endpoint returned an empty array. |
| F2 — Reproducible full tracked-file inventory | **Completed for the pinned tree** | Added `PHASE_1_TRACKED_FILE_INVENTORY_2026-11-05.md`, generated from the exact recursive Git tree. It lists all 200 blob paths, sizes and blob SHAs, records the procedure and classification rules, and records `truncated=false`. |
| F3 — Donor implementation traceability | **Completed as a bounded first-pass matrix; not exhaustive** | Added `PHASE_1_PR97_DONOR_CAPABILITY_TRACEABILITY_2026-11-05.md`. It traces seven major PR #97 pathways to exact source blobs, inputs, outputs/consumers, test sources, persistence claims and limitations. It is not a line-by-line audit of all 159 PR #97 changed paths or all donor PRs. |
| F4 — Mutable source links | **Corrected in the Phase 1 report** | Source links that previously used `blob/main/` are now pinned to the exact audited main commit `1273ddbcd0087d189e01388ded2d362fb1e058d2`. PR links and separately pinned donor/CI links remain unchanged. |
| F5 — Completion boundary | **Clarified; historical preservation work remains open** | The technical repository inventory and reuse/conflict assessment is complete within the static-investigation scope stated in the report. Full historical branch-to-PR mapping, duplicated-document comparison, README/cross-link checks and archive curation remain separate preservation work. They are not represented as complete and do not require restarting the technical audit. |

## 2. F1 — PR #174 acceptance and later findings

The evidence establishes this chronology:

1. On 2026-11-03, the specification was resubmitted at exact HEAD `0811a59e46bf934e32e794f90e4e7d18d4e2bd97` after the F-01 correction.
2. PR #174 issue comment [#6604790481](https://github.com/methaneex-oss/MethaneX/pull/174#issuecomment-6604790481), dated 2026-11-03 13:14:28 UTC, records the Project Director's explicit acceptance of that exact head as the approved Brain Mechanism Specification planning baseline. The comment states F-01 was cleared and the BM-07/SYS-05/SYS-08 clarification was non-blocking, with no implementation authorization.
3. The subsequent review report supplied in the conversation identifies F-02 (contextual language/operator-intent grounding) and F-03 (downstream reasoning integration) as unresolved. This later evidence requires targeted specification correction before implementation relies on those requirements.
4. PR #175's description continues to call PR #174 accepted. That wording accurately records the historical acceptance event but is incomplete as a description of the later F-02/F-03 review state.
5. The GitHub PR #174 review-list endpoint returned no submitted review objects at the time of this correction. The formal Project Director acceptance is independently visible in the issue discussion; the later F-02/F-03 review report has not been mirrored as a submitted GitHub review artifact.

**Current authority statement:** PR #174 was formally accepted as a planning baseline at the exact recorded head. Its acceptance is not retroactively erased. However, the subsequent F-02/F-03 findings are open specification-correction obligations. PR #174 may continue to guide traceability and investigation, but affected requirements must not be treated as implementation-ready until the findings are resolved and the required authority/review decision is recorded. No implementation is authorized by this addendum.

## 3. F2 — Tracked-file inventory reproducibility

The new full inventory document records:
- the exact tree commit and tree object;
- the recursive Git Trees API procedure and a local Git reproduction command;
- all 200 tracked blob paths;
- each file's category, byte size and blob SHA;
- the deterministic path/extension classification rules;
- the distinction between file presence and CMake test registration;
- the API's `truncated=false` result.

This makes the file-count and path inventory reproducible. It does not prove every file was semantically reviewed, compiled or executed.

## 4. F3 — Donor traceability boundary

The new PR #97 matrix covers:
- continuous affective-state update and decay;
- affective appraisal adaptation and downstream planning consumption;
- Brain-owned action execution and observed-consequence feedback;
- developmental strategy learning and contextual transfer;
- contextual prediction and prediction feedback;
- event-journal persistence and reconstruction;
- evolution evaluation and adoption control.

For each pathway it records source blob identities, inputs, processing, outputs/consumers, test-source identities, persistence claims and limits. It deliberately distinguishes a test file from a verified test run and a persisted journal from a complete trusted-memory system.

The matrix is a first-pass trace of selected high-impact donor capabilities. Broader donor review remains part of Phase 2's source-to-capability integration map, where each donor pathway must be compared against the exact accepted requirement, current main implementation, event/state ownership, and actual test evidence.

## 5. F4 — Immutable source references

All Phase 1 report links that previously referenced mutable `blob/main/` source paths now point to the audited tree commit `1273ddbcd0087d189e01388ded2d362fb1e058d2`. The path inventory separately records each blob SHA. Later changes to main cannot silently change the source revision being cited by the Phase 1 report.

## 6. F5 — Phase 1 completion scope

The following two scopes must remain distinct:

**Completed:** Phase 1's declared technical repository inventory and reuse/conflict investigation at the pinned main baseline, including the full tracked-file count, critical cognitive-path inspection, build/test-registration inspection, donor-line assessment, polyglot boundary assessment, architecture comparison and Gate A status documentation.

**Still open as preservation/documentation work:** mapping all 33 JARVIS-related branches to PRs and relevance; comparing duplicated historical plans/specifications across PR #96/#97 and later donor PRs; reconciling historical document revisions across PR #97/#148/#156/#170; verifying README and cross-document links; and deciding a curated archive/supersession index.

The second scope is a bounded follow-on documentation task. It does not invalidate the completed technical inventory, but it must remain visible as an open carry-forward item. No historical file or branch is deleted or moved by this correction.

## 7. Governance refinements G1–G3

The governance proposal has been updated as follows:

- **G1 / Rule 3.2:** Phase-level continuity assessment remains full. Substantial tasks identify relevant inherited findings. Small subtasks may inherit parent traceability when they introduce no new material architectural, state, safety, persistence, integration or implementation risk.
- **G2 / Rule 6.3:** Learning evidence now distinguishes observational/evidence-based learning from action-outcome learning. Learning does not require the Brain to act first; both pathways require justified evidence, persistent state change and testable future effects.
- **G3 / Rule 8.3:** A defect requires a regression test or an equivalent repeatable verification appropriate to the defect type, including documentation consistency checks, schema validation, reproducible inventory procedures or independent review.

The governance document remains a proposed baseline until explicit Project Director acceptance of an exact revision. This correction does not silently make PR #178 binding.

## 8. Unchanged boundaries

- No runtime code, tests, build configuration or dependencies were changed.
- No donor PR was merged or selected as the implementation baseline.
- No historical document or branch was deleted, moved or rewritten.
- Gate A remains **NOT CLEARED** unless a later exact-evidence decision explicitly changes it.
- PR #174's historical acceptance remains recorded; F-02/F-03 remain targeted open obligations.
- No implementation authorization is granted.
- Phase 2 remains the recommended next investigation: source-backed, whole-system integration mapping, carrying forward every open item above.

**Conclusion:** These are bounded corrections to the Phase 1 evidence and governance package. They do not restart Phase 1, discard its conclusions or authorize implementation.
