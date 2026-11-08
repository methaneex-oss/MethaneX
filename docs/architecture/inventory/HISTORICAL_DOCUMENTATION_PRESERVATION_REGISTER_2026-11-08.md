# Historical Documentation Preservation Register — 2026-11-08

**Purpose:** Record the documentation artifacts contributed by the relevant JARVIS planning PR lineages, with immutable commit and blob identities, so later contributors can locate historical evidence without relying on chat history or mutable branch names.

**Scope:** Documentation artifacts in PRs #171, #172, #173, #174, #175, #178, #179, #191, #192 and #193. This is a preservation and discoverability register, not an acceptance decision, a claim that every artifact is authoritative, or permission to integrate the PRs.

**Verification method:** Each listed path was returned by the corresponding PR changed-file listing and fetched from the exact PR head stated in its group. The blob SHA identifies the fetched file content at that revision. A later branch update does not change the historical identity recorded here.

## 1. PR lineage and authority classification

| PR | Exact head | Base | State at 2026-11-08 check | Classification |
|---:|---|---|---|---|
| #171 | `b05434758ad4fe72815503f89bd5d2990ccb658b` | `main` | Open, draft, unmerged | Whole-system architecture foundation; later records cite this revision as reviewed, but its historical decision trail must be read with its evidence record |
| #172 | `d7d676b79dbf3269f7fd3ebdb4363a6df19f255d` | `main` | Open, draft, unmerged | Foundational capability investigation; Project Director acceptance is recorded in PR #172 discussion |
| #173 | `97191111bc2573c14d391c0af9628db7b11f194b` | `main` | Open, draft, unmerged | Brain Foundation Architecture; downstream documents state it was accepted, but a primary exact-revision Project Director decision was not recovered from PR #173 discussion |
| #174 | `0811a59e46bf934e32e794f90e4e7d18d4e2bd97` | PR #173 | Open, draft, unmerged | Brain Mechanism Specification; exact planning-baseline acceptance is recorded by Project Director discussion comment `6604790481`; follow-on F-02/F-03 remain separate open obligations |
| #175 | `874c732973b6ab303d65a503f5a215b0af8e1153` | PR #174 | Open, draft, unmerged | Deferred implementation plan, continuity handoff and Gate A/Gate B evidence; Gate A remains not cleared and no implementation baseline is selected |
| #178 | `39fe09dcf13496f5f0005ccf3f00739303e29f88` | `main` | Open, draft, unmerged | Phase 1 inventory/preservation work and proposed governance rules; governance proposal remains unaccepted |
| #179 | `61311fe5b44c81c4409c8ba8dc581a83bdd5dd2c` | PR #178 | Open, draft, unmerged | Phase 2 BM-01–BM-12 integration map and closure evidence; not proof of whole-Brain completeness or Phase 2 acceptance |
| #191 | `609d38ede50bbdd98a93dfed112781eacabee9fd` | PR #179 at `f6267456560a08054d69f7960d2951452b14017c` | Open, draft, unmerged | Human/MCU comparison scoped to BM-01–BM-12; separate branch, not independently reviewed or accepted |
| #192 | `e8cd17277ab5c08d1f6dd6f267120f356ce28666` | PR #179 at `61311fe5b44c81c4409c8ba8dc581a83bdd5dd2c` | Open, draft, unmerged | Documentation-foundation corrections, index, portal, inventory and templates; gate not cleared |
| #193 | `976aa33f89cc02225296f59246f47982300f5b39` | PR #175 at `874c732973b6ab303d65a503f5a215b0af8e1153` | Open, draft, unmerged | Separate roadmap/handoff hold lineage; does not include the PR #192 documentation package |

## 2. Verified artifact register

### PR #171 — whole-system architecture foundation

Exact head: `b05434758ad4fe72815503f89bd5d2990ccb658b`

| Repository path | Blob SHA |
|---|---|
| `docs/architecture/00_JARVIS_SYSTEM_ARCHITECTURE_FOUNDATION.md` | `db0f136b3aaa338fb7d06d7be9e50bb42fc82821` |
| `docs/architecture/01_JARVIS_WHOLE_SYSTEM_ANATOMY_AND_RESPONSIBILITY_MAP.md` | `2b595af4fefb54c7f8dc81fb997d4d391f2250e0` |
| `docs/architecture/research/00_BRAIN_FOUNDATION_COMPARATIVE_RESEARCH_AND_DECISION_LOG.md` | `f84077179f9fa8e151b5faca39940e43a13db2a2` |
| `docs/architecture/research/01_BRAIN_FOUNDATION_MECHANISM_GAP_ANALYSIS.md` | `a90204f28c09dd9c1e2e0e1b24d108a58dc82b46` |
| `docs/review-records/brain-foundation/2026-11-02_REVIEW_CORRECTION_EVIDENCE.md` | `b5d5758623351a1c4ba5b4bd8f0b5bd17b771c0c` |

### PR #172 — foundational capability investigation

Exact head: `d7d676b79dbf3269f7fd3ebdb4363a6df19f255d`

| Repository path | Blob SHA |
|---|---|
| `docs/architecture/research/02_BRAIN_FOUNDATIONAL_CAPABILITY_INVESTIGATION_2026-11-03.md` | `410edf234f79d9a370fb63deffaaf22cfed9ec9c` |
| `docs/architecture/research/reviews/02_BRAIN_FOUNDATIONAL_CAPABILITY_INVESTIGATION_REVIEW_CORRECTIONS_2026-11-03.md` | `1cafe9b69f6820dc2cbd342929b06a9b847341fd` |

### PR #173 — Brain Foundation Architecture

Exact head: `97191111bc2573c14d391c0af9628db7b11f194b`

| Repository path | Blob SHA |
|---|---|
| `docs/architecture/02_BRAIN_FOUNDATION_ARCHITECTURE.md` | `364aa3b5fabdab527c169ab170dd72e23c502438` |
| `docs/architecture/reviews/02_BRAIN_FOUNDATION_ARCHITECTURE_REVIEW_CORRECTIONS_2026-11-03.md` | `fa6a5baaa4226dc7b845f4da6e07c5635ccc6ad8` |

### PR #174 — Brain Mechanism Specification

Exact head: `0811a59e46bf934e32e794f90e4e7d18d4e2bd97`

| Repository path | Blob SHA |
|---|---|
| `docs/architecture/specifications/00_BRAIN_MECHANISM_SPECIFICATION.md` | `3b6a53c8a295fa0d9fc29bbb6c7688b61d1dcdb1` |
| `docs/architecture/specifications/research/00_BRAIN_EXISTING_MECHANISM_SOURCE_AUDIT_2026-11-03.md` | `4479874476715fd59a4c3ba6c908f06c43a1c6c2` |
| `docs/architecture/specifications/reviews/00_BRAIN_MECHANISM_SPECIFICATION_REVIEW_CORRECTIONS_2026-11-03.md` | `518522e5f222ee9fa7efe771c458adc08bd09a19` |

### PR #175 — deferred implementation planning and Gate A/Gate B evidence

Exact head: `874c732973b6ab303d65a503f5a215b0af8e1153`

| Repository path | Blob SHA |
|---|---|
| `docs/architecture/plans/00_BRAIN_IMPLEMENTATION_PLAN.md` | `9511cda1389e47c94dcaf9373423570d8177a3c7` |
| `docs/architecture/plans/JARVIS_PROJECT_CONTINUITY_AND_RECOVERY_HANDOFF.md` | `23d7ebf2a287b8d1c4cd049dce2f96181fdd0ae6` |
| `docs/architecture/plans/reviews/00_BRAIN_IMPLEMENTATION_PLANNING_RUN_01_CHECKPOINTS_2026-11-03.md` | `0766324ada3fba689187119190bc53f78cb3e525` |
| `docs/architecture/plans/reviews/01_BRAIN_IMPLEMENTATION_PLANNING_RUN_02_FINDINGS_2026-11-03.md` | `df220f0c0726910cd5415151c7148156aecd5043` |
| `docs/architecture/plans/reviews/02_GATE_A_REPOSITORY_BASELINE_RECONCILIATION_2026-11-03.md` | `f7970aa0c29882696fcc0f75ccffb0929d13e419` |
| `docs/architecture/plans/reviews/03_GATE_A_FINAL_DISPOSITION_2026-11-03.md` | `e7c23678b1c9a4ec940b123474e0ec01f52a0c65` |
| `docs/architecture/plans/reviews/04_GATE_A_BUILDER_TECHNICAL_REREVIEW_2026-11-03.md` | `dc003a9a0701c264123d94ec8a84fcc0e8f3f34b` |
| `docs/architecture/plans/reviews/05_GATE_B_MECHANISM_TRACEABILITY_AUDIT_2026-11-03.md` | `7d23c5ad8a1c1cc9e37dacc7bd581e11fb0fcb64` |
| `docs/architecture/plans/reviews/06_GATE_A_SEMANTIC_RECONCILIATION_ADDENDUM_2026-11-04.md` | `e7dff67082bb5b40d6fc78866946df2c9a60c257` |
| `docs/architecture/plans/reviews/07_GATE_A_CLOSURE_ASSIGNMENT_2026-11-04.md` | `0778257df592cd19c5774db2231ad79ed06187eb` |
| `docs/architecture/plans/reviews/08_GATE_A_RISK_BASED_PROVENANCE_MATRIX_2026-11-04.md` | `8f8dd2c73cdce8ea7aee530b992bb70d9f73a04e` |
| `docs/architecture/plans/reviews/09_GATE_A_API_COMPATIBILITY_MATRIX_2026-11-04.md` | `7163f9a080fc17c07c5b79b6f27e9c7d98ecd536` |
| `docs/architecture/plans/reviews/10_GATE_A_WORKFLOW_CONTINUITY_MATRIX_2026-11-04.md` | `10839a6c47c4f6506a14d883ef8cda0e391cff0a` |
| `docs/architecture/plans/reviews/11_GATE_A_CANDIDATE_DEFECT_DISPOSITION_2026-11-04.md` | `23d2b1d23b9f95d4786703ec9129ccd9a4cf36db` |
| `docs/architecture/plans/reviews/12_GATE_A_INDEPENDENT_REVIEW_PACKET_2026-11-04.md` | `faba1b728cb4f5a09494ff7431a4b5c8c2f3fee9` |
| `docs/architecture/plans/reviews/13_GATE_A_COMPILED_SOURCE_BASELINE_CORRECTION_2026-11-04.md` | `1ef8ff0359602ffcaea23265edf9764336caf5e4` |
| `docs/architecture/plans/reviews/13_GATE_A_FINAL_BASELINE_RECOMMENDATION_2026-11-04.md` | `bc44e8d7c570e1804014d37801c4587e6f1005c1` |
| `docs/architecture/plans/reviews/14_GATE_A_INDEPENDENT_TECHNICAL_REVIEW_2026-11-04.md` | `f9a9ff406842362a481a30b8ecbbbd4e58cfaaf6` |
| `docs/architecture/plans/reviews/15_GATE_A_BUILDER_REVIEWER_RECONCILIATION_2026-11-04.md` | `52924d22e356303d643e8e8fab2b7d5dde321405` |
| `docs/architecture/plans/reviews/16_GATE_A_CLOSURE_EVIDENCE_UPDATE_2026-11-04.md` | `6a8276deff9c4560daee7a665193f3e8ea16ce7c` |

### PR #178 — Phase 1 inventory and proposed governance

Exact head: `39fe09dcf13496f5f0005ccf3f00739303e29f88`

| Repository path | Blob SHA |
|---|---|
| `docs/architecture/inventory/00_JARVIS_DOCUMENTATION_AND_ARTIFACT_INVENTORY_2026-11-04.md` | `dd528b8a491114e8382712f3521b9410b767b323` |
| `docs/architecture/inventory/PHASE_1_PR97_DONOR_CAPABILITY_TRACEABILITY_2026-11-05.md` | `0b54de626cc6bd5dff049ac60dbec14cee756144` |
| `docs/architecture/inventory/PHASE_1_TRACKED_FILE_INVENTORY_2026-11-05.md` | `f199526e81c462a9855f1a3fe02ae76edc19c4f1` |
| `docs/architecture/reports/PHASE_1_REVIEW_CORRECTIONS_AND_SCOPE_RECONCILIATION_2026-11-05.md` | `bf74bd94bf37d2aca3a598e59a60e594bb20bc4f` |
| `docs/architecture/reports/PHASE_1_WHOLE_REPOSITORY_INVESTIGATION_AND_REUSE_AUDIT_2026-11-04.md` | `925eb079b6c26578b64ee69caadb97b90143afb6` |
| `docs/governance/JARVIS_PROJECT_GOVERNANCE_AND_BUILDER_RULES.md` | `e4315956cfb1ed075b508af3053601fed345f0a5` |

### PR #179 — Phase 2 integration and closure evidence

Exact head: `61311fe5b44c81c4409c8ba8dc581a83bdd5dd2c`

| Repository path | Blob SHA |
|---|---|
| `README.md` | `4952c7d2c407706fb69e3cdb3731f21c96b14611` |
| `docs/JARVIS_BRAIN_MASTER_BLUEPRINT.md` | `7ee8b5a399cda312d2c0be15d8244e9260d3b828` |
| `docs/JARVIS_PHASE_2_COMPLETION.md` | `faa5cace14d13179d717438be61f533ac5b8ef97` |
| `docs/architecture/reports/PHASE_2_DONOR_RUNTIME_RELIABILITY_ACCEPTANCE_CONTRACT_2026-11-06.md` | `3abf1fb93009a1de79942bea5aad4d8ff2f037e3` |
| `docs/architecture/reports/PHASE_2_PROJECT_DIRECTOR_CLOSURE_DECISION_PACKET_2026-11-06.md` | `715b123fe09e4b33f2e8fb2e23b3cf04680b44d2` |
| `docs/architecture/reports/PHASE_2_WHOLE_BRAIN_CAPABILITY_TO_SOURCE_INTEGRATION_MAP_2026-11-05.md` | `e7c85d74a1051a40a10b0318da739c6b1b0c2ad7` |
| `docs/architecture/reports/PR_174_FOLLOW_ON_REVIEW_PROVENANCE_RECOVERY_2026-11-06.md` | `41ae1599ce824471635439b2a991acc79c449407` |

### PR #191 — human/MCU reference comparison

Exact head: `609d38ede50bbdd98a93dfed112781eacabee9fd`

| Repository path | Blob SHA |
|---|---|
| `docs/architecture/reports/PHASE_2_HUMAN_AND_MCU_REFERENCE_COMPARISON_2026-11-06.md` | `eac3cb443b5c6a2b9c0d9ad9f5fd552b79d8a0e2` |

### PR #192 — documentation foundation correction package

Exact head at preservation check: `e8cd17277ab5c08d1f6dd6f267120f356ce28666`

| Repository path | Blob SHA |
|---|---|
| `README.md` | `780651b804b491781fdcac8e248eaca9243797a4` |
| `docs/ARCHITECTURE.md` | `3c6692b52059e43947d1fd2e7e84debb2362023f` |
| `docs/JARVIS_BRAIN_MASTER_BLUEPRINT.md` | `0e49d313bf3929aa30140cb7149ebab038918378` |
| `docs/JARVIS_PHASE_2_COMPLETION.md` | `e0e57a44216fc36c52d469a79abfc8df058515a3` |
| `docs/README.md` | `00d6a5996b1f76aeefc7fcda5e07a95de4c77288` |
| `docs/architecture/00_JARVIS_PLANNING_DOCUMENTATION_INDEX_2026-11-07.md` | `b963c9cea549feca0353b2d48e7eb307930f2dcf` |
| `docs/architecture/inventory/00_JARVIS_DOCUMENTATION_AND_ARTIFACT_INVENTORY_2026-11-04.md` | `9e41f1fc457515166734234da0f78f98494468b6` |
| `docs/architecture/reports/INDEPENDENT_DOCUMENTATION_FOUNDATION_REVIEW_2026-11-08.md` | `ecd11354a858eb6e46cbd85b816836a2f88973c9` |
| `docs/architecture/reports/INDEPENDENT_REVIEWER_HANDOFF_2026-11-08.md` | `b452855b39580abd4439a5e1b2a69a7e2e772513` |
| `docs/architecture/reports/INDEPENDENT_RE_REVIEW_BUILDER_FOLLOW_UP_2026-11-08.md` | `2d63ed93344a7081dcedb44247536c416322c793` |
| `docs/architecture/reports/INITIAL_DOCUMENTATION_FOUNDATION_AUDIT_AND_COMPLETION_GATE_2026-11-07.md` | `3a2324cfaab48adbeb677f37eb78471fe8d5e31d` |
| `docs/architecture/reports/PHASE_1_REVIEW_CORRECTIONS_AND_SCOPE_RECONCILIATION_2026-11-05.md` | `a459cdfd02d850d455ca526e6823e68525776ba3` |
| `docs/architecture/reports/PHASE_1_WHOLE_REPOSITORY_INVESTIGATION_AND_REUSE_AUDIT_2026-11-04.md` | `f725eda1e23d6558d90f6f7c87302019ef3a0dfc` |
| `docs/architecture/reports/PHASE_2_WHOLE_BRAIN_CAPABILITY_TO_SOURCE_INTEGRATION_MAP_2026-11-05.md` | `7cf312f6cc6fd880473a0b6ccc86cf53bf3b3533` |
| `docs/architecture/reports/WHOLE_BRAIN_DOCUMENTATION_PHASE_BUILDER_SELF_REVIEW_2026-11-07.md` | `f340170b00c55b5c452e98431a37e07c7cde1746` |
| `docs/architecture/reports/WHOLE_BRAIN_PLANNING_SCOPE_AND_BUILDER_CORRECTION_2026-11-07.md` | `0187a0ac71bd0c95e94beb3bf006da9cc7c3605f` |
| `docs/templates/INDEPENDENT_REVIEW_REPORT_TEMPLATE.md` | `f3176cf1a1f45735a3ad62fa4a865806edc24e08` |
| `docs/templates/PLANNING_DOCUMENT_TEMPLATE.md` | `b9f71a923b0d717a3b29655574c89c10e0801115` |
| `docs/templates/README.md` | `7209fd0fcda239349af602490d26b8c708b743da` |
| `docs/templates/TEST_EVIDENCE_REPORT_TEMPLATE.md` | `9c6bbae48a22beb7c4e95858282d7d8d7b2159c2` |

### PR #193 — separate roadmap/handoff hold package

Exact head at preservation check: `976aa33f89cc02225296f59246f47982300f5b39`

| Repository path | Blob SHA |
|---|---|
| `docs/architecture/plans/00_BRAIN_IMPLEMENTATION_PLAN.md` | `d065e833d2211753985784d9de6e562e0f72bc2b` |
| `docs/architecture/plans/JARVIS_PROJECT_CONTINUITY_AND_RECOVERY_HANDOFF.md` | `9eae4ffc1e4cc1f4673abecb880aa37558935026` |

## 3. Preservation findings and limits

1. **Path preservation verified:** all 68 changed paths listed above were returned by their respective PR changed-file endpoints and successfully fetched at the exact stated PR head. This demonstrates that the registered artifacts remain retrievable at those immutable revisions.
2. **Historical status is not uniform:** the register intentionally does not label every artifact accepted. PR #172 has an explicit Project Director acceptance record; PR #174 has an exact planning-baseline acceptance record; PR #173's primary acceptance record was not recovered; PR #178 governance remains proposed; PR #191 remains proposed/unreviewed; PR #175 Gate A remains not cleared; PR #179 Phase 2 is not established as complete.
3. **Separate lineages remain separate:** PR #192 is based on PR #179; PR #193 is based on PR #175; PR #191 was created from an older PR #179 base. No ancestry operation is implied.
4. **PR #191 requires an explicit dependency decision:** comparing its base `f6267456560a08054d69f7960d2951452b14017c` to PR #179 head `61311fe5b44c81c4409c8ba8dc581a83bdd5dd2c` gives 22 commits ahead and 0 behind. Comparing PR #179 head to PR #191 head `609d38ede50bbdd98a93dfed112781eacabee9fd` gives a diverged result: PR #191 has 1 unique commit and is 22 commits behind the PR #179 line. Retargeting alone would not reconcile the histories; a rebase/cherry-pick or other explicit integration choice would be required. No such operation was performed.
5. **Preservation is bounded to the listed PR artifact sets:** this is not a claim that every historical file ever referenced by the repository has been exhaustively inventoried, nor that all superseded documents have correct in-file status labels. A broader repository-wide historical scan remains a reviewer/Project Director acceptance question if the current inventory does not cover it.
6. **No gate or authority changes:** this register is a Builder-produced preservation record. It does not accept PRs, resolve missing Project Director decisions, clear review findings, approve governance, close Gate A/Gate B, or authorize Stage A or implementation.

**Current disposition:** DF-08 is materially advanced for the enumerated planning lineage: the PR artifact paths are mapped to immutable heads and blobs. It remains **PARTIAL** until an independent reviewer confirms the map is sufficient and the remaining repository-wide historical-status questions are resolved.

## 4. Live-state and PR #191 divergence correction — 2026-11-08

This addendum supersedes the PR #192 / PR #193 current-head values in §1 and §2 only for the later snapshot recorded here. The original artifact/blob register remains an immutable historical snapshot.

At the time of this addendum:

| Item | Live state |
|---|---|
| PR #192 | Open, draft, unmerged; HEAD `d8a92f9cf09d792311764077dc28c24034054ae2`; base `61311fe5b44c81c4409c8ba8dc581a83bdd5dd2c`; 22 changed paths |
| PR #193 | Open, draft, unmerged; HEAD `714142a24ed1ba286291bba8ccfc8a81f2f9115a`; base `874c732973b6ab303d65a503f5a215b0af8e1153`; 2 changed paths |
| PR #192 formal reviews / inline threads / conversation comments | 0 / 0 / 0 returned at this refresh |

### 4.1 PR #191 graph clarification

The exact comparisons are:

- PR #191 base `f6267456560a08054d69f7960d2951452b14017c` → PR #191 head `609d38ede50bbdd98a93dfed112781eacabee9fd`: 1 ahead, 0 behind; one unique document commit.
- PR #179 head `61311fe5b44c81c4409c8ba8dc581a83bdd5dd2c` → PR #191 head `609d38ede50bbdd98a93dfed112781eacabee9fd`: diverged; 1 ahead, 22 behind; merge base `f6267456560a08054d69f7960d2951452b14017c`.

Therefore PR #191 is a one-commit document addition on its historical base, not a current descendant of PR #179. Retargeting alone would not reconcile the histories. The Project Director must choose between reviewing it as a historical-base artifact or authorizing a new dependent revision that replays its single document commit onto the current PR #179 head. No such operation has been performed.

### 4.2 Authority and scope reminder

The PR #173 primary acceptance record remains unrecovered; do not infer acceptance. PR #174's exact specification-baseline acceptance remains recorded, but its draft header and F-02/F-03 follow-on obligations remain distinct. PR #178 governance remains proposed/unaccepted. This register is evidence only; it does not make any Project Director decision or clear a gate.

**Current disposition:** The PR #171–#193 artifact map remains a bounded preservation register. Its original path/blob table is tied to the immutable heads named in those sections; the live state above is a later status snapshot. The broader 37-branch and PR #96/#97/#148/#156/#170 comparisons are documented separately in the [Historical Preservation and Cross-Revision Comparison Report](../reports/DOCUMENTATION_FOUNDATION_PRESERVATION_AND_LINK_VALIDATION_2026-11-08.md).


### PR #174 — subsequent administrative status clarification

The 68-path register above preserves PR #174's exact accepted planning-baseline snapshot at HEAD `0811a59e46bf934e32e794f90e4e7d18d4e2bd97`. The PR #174 branch subsequently advanced to administrative/status-clarification HEAD `922912283d173e24df891ba23d0e2dfc17e0f4b4`; the specification blob at that revision is `ac1621c43d60b2a556438371287c07ab2b20c8aa`. The change clarifies the accepted PR #174 baseline and qualifies PR #173's unresolved parent-acceptance provenance. It does not change the substantive mechanism specification or create a new acceptance decision. The new administrative revision itself remains subject to independent review and any required authority decision. The accepted baseline remains the exact earlier revision `0811a59...` recorded by Project Director comment `6604790481`.
