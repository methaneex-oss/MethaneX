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


## 5. Expanded repository-wide documentation lineage and current snapshots — 2026-11-08

This addendum expands the earlier bounded register. It supersedes the earlier 68-path total as a completeness statement for the documentation PR set below; the earlier tables remain valid historical snapshots at their stated heads.

### 5.1 Paginated repository discovery scope

The repository's paginated GitHub REST listings were read to completion during this pass:

- **Branches:** 245 current branch refs across three pages (100 + 100 + 45), with 203 distinct tip SHAs.
- **Documentation-family branch prefixes:** 37 refs beginning `docs/`, `architecture/`, `research/`, `plan/`, `review/` or `spec/`; all 37 have distinct tip SHAs.
- **JARVIS-name branch search:** 37 refs and 11 distinct tips. The 27-ref alias group at `16abca97caf77ce65d5ac901513eb2790f04c68c` is one PR #96 tree tip, not 27 distinct content revisions. The two previously unmatched refs are mapped by ancestry in §2.1/§2.2 and audit §31.3.
- **Pull requests:** 184 PRs across two pages (100 + 84).
- **Documentation PR lineage:** 28 PRs — #160, #164, #166–#175, and #178–#193 — with **108 changed documentation paths** at their exact PR heads. PR #176 is source/test-only and is not counted as a documentation PR. PR #177 was not present in the complete current PR listing.

The 37 documentation-family branch refs and exact tips are:

| Branch | Exact tip SHA |
|---|---|
| `architecture/brain-foundation-planning-20261103` | `97191111bc2573c14d391c0af9628db7b11f194b` |
| `docs/brain-constitution-planning-readiness-20261031` | `abf3303c04638a89146a4161b91a439910235add` |
| `docs/brain-identity-behavioral-spec-20261031` | `39ca36eb66d20fe7ded0d891aad7a153c59628a0` |
| `docs/brain-layer-language-ownership-map-20261031` | `e7227919c13cc65c0e3915fdc7b6491465be1921` |
| `docs/brain-polyglot-engineering-governance-20261031` | `004e8753d01c9b18bb243b257591657f9b19d7db` |
| `docs/brain-polyglot-foundation-audit-20261031` | `5433b0d0ae6ea7ff9d0991e84c8a6a8a2506c1cb` |
| `docs/jarvis-affective-plan` | `16abca97caf77ce65d5ac901513eb2790f04c68c` |
| `docs/jarvis-mcu-brain-target-analysis-20261031` | `bdc980f3dcf322541556c0756aeee4eb1ff955a1` |
| `docs/jarvis-phase2-human-mcu-comparison-20261106` | `609d38ede50bbdd98a93dfed112781eacabee9fd` |
| `docs/jarvis-phase-1-preservation-inventory-20261104` | `ebbda074957e0f9fb0d0f04dd9b03fe58b270a0a` |
| `docs/jarvis-phase-2-whole-brain-integration-map-20261105` | `61311fe5b44c81c4409c8ba8dc581a83bdd5dd2c` |
| `docs/jarvis-project-command-governance-20261031` | `c803e9873df1c22111156d894853ef2d8832a8ea` |
| `docs/jarvis-project-governance-rules-20261105` | `39fe09dcf13496f5f0005ccf3f00739303e29f88` |
| `docs/jarvis-system-architecture-foundation-20261101` | `b05434758ad4fe72815503f89bd5d2990ccb658b` |
| `docs/phase-2-closeout-evidence-20261106` | `53278d5918163b286247f608efcadd5ef0afd232` |
| `docs/phase-2-closeout-preparation-20261106` | `cb7b0877bcdd82b88dd387c99a9442997e0220ce` |
| `docs/phase-2-ir02-ir04-ir03-followthrough-20261106` | `8e18f5eb2f8921e4bcd5d8441d432b5923d28da8` |
| `docs/priority-one-trust-boundary-contract-20261031` | `cfbcbdd29839f062851d3ca7da63ab2ae3a8f4f1` |
| `docs/reviewer-records-foundation-20261108` | `185712526ebbe34232e9e95acb738b464b35b486` |
| `docs/whole-brain-planning-roadmap-hold-20261107` | `65220543416da9b368f24e226aefe24bcdbc7870` |
| `docs/whole-brain-planning-scope-correction-20261107` | `8b6c257bc40748e3d96a0fdf2272b774f54d7a17` |
| `plan/brain-implementation-roadmap-20261103` | `874c732973b6ab303d65a503f5a215b0af8e1153` |
| `research/brain-capability-investigation-20261103` | `d7d676b79dbf3269f7fd3ebdb4363a6df19f255d` |
| `research/phase-2-brain-integration-map-20261105` | `6ca140300b914ed981a50301bbf1d82a5bfe4d8b` |
| `research/phase-2-whole-brain-integration-map-20261105` | `cf3f8db7e5e5ca5eb1c0345bafdb704e92d70f25` |
| `research/phase-2-whole-brain-integration-mapping-20261105` | `1273ddbcd0087d189e01388ded2d362fb1e058d2` |
| `review/builder-response-review-2026-11-08` | `43733ae997f61aa6f2e0f59e61b2dc6d8f566f6c` |
| `review/documentation-foundation-rereview-2026-11-08` | `b2ca8c4ce6cab3f508987a51caf4ec65a085a374` |
| `review/independent-documentation-foundation-2026-11-08` | `07202eb5adeb729695951bf8ce41a1b51a95e07c` |
| `review/phase-2-independent-review-20261106` | `30eaefe3bee02e2038f66fb18c907673026ebe76` |
| `review/phase-2-independent-review-followup-20261106` | `36b843f6959628a689d81bc1e12e523e17227073` |
| `review/phase-2-second-independent-review-20261106` | `8ba6dfcb17f2aab409f58cbd8bc57898edd60405` |
| `review/phase-2-source-challenge-20261105` | `1ffc2d66c3c0b389eaddae992318d53eeab8416b` |
| `review/phase-2-third-independent-review-20261106` | `a1df22531765b7022f6bfbcfd9f3f5251cf5adf5` |
| `review/phase-2-whole-brain-map-independent-review-20261106` | `46796725fd656628f7b6e47a57929b87f79a6d8d` |
| `review/whole-brain-builder-report-rereview-2026-11-08` | `11c3bc2802e390cffc7b8b08de96d1f7fe352c4d` |
| `spec/brain-mechanism-specification-20261103` | `922912283d173e24df891ba23d0e2dfc17e0f4b4` |

### 5.2 Newly registered historical documentation paths — 34 paths across 18 PRs

Each path below was fetched at the exact PR head and its returned blob SHA matched the GitHub PR-files API entry. PR state and branch/head/base metadata were separately retrieved from the paginated PR listing.

| PR | Exact PR head | Repository path | Blob SHA |
|---:|---|---|---|
| #160 | `cfbcbdd29839f062851d3ca7da63ab2ae3a8f4f1` | `docs/PRIORITY_ONE_TRUST_BOUNDARY_CONTRACT.md` | `772cd3834bd94993f4fa917e394e6763bc44a01a` |
| #164 | `5433b0d0ae6ea7ff9d0991e84c8a6a8a2506c1cb` | `docs/BRAIN_POLYGLOT_FOUNDATION_TECHNOLOGY_AUDIT.md` | `f8e509d63553fcca29500caabb8e8186de9a7608` |
| #166 | `c803e9873df1c22111156d894853ef2d8832a8ea` | `README.md` | `d34cc477f12e85576fc14aac6780d807a42fe13e` |
| #166 | `c803e9873df1c22111156d894853ef2d8832a8ea` | `docs/JARVIS_PROJECT_GOVERNANCE.md` | `a02befaffdbbd7cabee1ce4fa0bc2342e3409ecf` |
| #167 | `e7227919c13cc65c0e3915fdc7b6491465be1921` | `README.md` | `2d98fe0123bffb1751a5adc60b9b2666e6a26c55` |
| #167 | `e7227919c13cc65c0e3915fdc7b6491465be1921` | `docs/BRAIN_LAYER_LANGUAGE_OWNERSHIP_MAP.md` | `003915f52d778e5374af2566958469e50710d617` |
| #168 | `004e8753d01c9b18bb243b257591657f9b19d7db` | `README.md` | `e7c71d115dc761425f8cf317ed2ad2a30246c67b` |
| #168 | `004e8753d01c9b18bb243b257591657f9b19d7db` | `docs/BRAIN_POLYGLOT_ENGINEERING_GOVERNANCE.md` | `3c7c72a6e70c93fad76068d989ff2bb4d882c129` |
| #169 | `bdc980f3dcf322541556c0756aeee4eb1ff955a1` | `README.md` | `bf20aca59ae42ebc07d8bbe97f2ebb1e4a6f2102` |
| #169 | `bdc980f3dcf322541556c0756aeee4eb1ff955a1` | `docs/JARVIS_MCU_BEHAVIORAL_REFERENCE_AND_BRAIN_TARGET.md` | `4d3d45f63e2cf5b231e94f4684867654d59db0ed` |
| #170 | `abf3303c04638a89146a4161b91a439910235add` | `README.md` | `fe92ae7f3e22f66197f078dd66eac5e73f7255d9` |
| #170 | `abf3303c04638a89146a4161b91a439910235add` | `docs/BRAIN_LAYER_0_19_TRACEABILITY_MATRIX.md` | `e354332be06d17dba87fcf85deb5868aa2277f74` |
| #170 | `abf3303c04638a89146a4161b91a439910235add` | `docs/BRAIN_PLANNING_REVIEW_RECONCILIATION.md` | `64d62c3f70290d583bab5467b09ecf6a44a8925b` |
| #170 | `abf3303c04638a89146a4161b91a439910235add` | `docs/JARVIS_BRAIN_FOUNDATION_CONSTITUTION_AND_PLANNING_READINESS.md` | `fe0488878a305346538a71b5c2bad3c5fd225cdb` |
| #170 | `abf3303c04638a89146a4161b91a439910235add` | `docs/JARVIS_BRAIN_MASTER_BLUEPRINT.md` | `11eb3d3abbba94116e5f4d1288856495ea0ac9e4` |
| #180 | `6ca140300b914ed981a50301bbf1d82a5bfe4d8b` | `docs/architecture/reports/PHASE_2_WHOLE_BRAIN_CAPABILITY_TO_SOURCE_INTEGRATION_MAP_2026-11-05.md` | `ebbbdb264091c11ec3724e0f73b7fbe56d69f0d6` |
| #181 | `cf3f8db7e5e5ca5eb1c0345bafdb704e92d70f25` | `docs/architecture/research/PHASE_2_WHOLE_BRAIN_CAPABILITY_TO_SOURCE_INTEGRATION_MAP_2026-11-05.md` | `82f7479bc0bc9170932b7b6e8d0eb989d94d965b` |
| #182 | `1ffc2d66c3c0b389eaddae992318d53eeab8416b` | `docs/architecture/research/reviews/PHASE_2_SOURCE_CHALLENGE_REVIEW_2026-11-05.md` | `7eeea7907e8bf79bfccc9e0871568e6a55ab8558` |
| #183 | `30eaefe3bee02e2038f66fb18c907673026ebe76` | `docs/architecture/reviews/PHASE_2_INDEPENDENT_REVIEW_2026-11-06.md` | `8f82c3a4a1e4457ff4c65d2c86e7e42be8e3397d` |
| #184 | `8ba6dfcb17f2aab409f58cbd8bc57898edd60405` | `docs/architecture/reviews/PHASE_2_SECOND_INDEPENDENT_REVIEW_2026-11-06.md` | `8340a149206a92a7060c61931adfb4d27f80e636` |
| #185 | `cb7b0877bcdd82b88dd387c99a9442997e0220ce` | `docs/architecture/reports/PHASE_2_DONOR_RUNTIME_RELIABILITY_ACCEPTANCE_CONTRACT_2026-11-06.md` | `377952cc08d2e16e89e420290180628c24827232` |
| #185 | `cb7b0877bcdd82b88dd387c99a9442997e0220ce` | `docs/architecture/reports/PHASE_2_HUMAN_AND_MCU_REFERENCE_COMPARISON_2026-11-06.md` | `d7a1f6c7ad52bae4b89c34dd8a3c0b9540a91f9f` |
| #185 | `cb7b0877bcdd82b88dd387c99a9442997e0220ce` | `docs/architecture/reports/PHASE_2_WHOLE_BRAIN_CAPABILITY_TO_SOURCE_INTEGRATION_MAP_2026-11-05.md` | `427a7095e761c84f5d094ce9386e6d1964fdf57f` |
| #186 | `53278d5918163b286247f608efcadd5ef0afd232` | `docs/architecture/reports/PHASE_2_DONOR_RUNTIME_RELIABILITY_CONTRACT_2026-11-06.md` | `a5ec880b6ec2c856bc5a3085eddce618abcc6dc9` |
| #186 | `53278d5918163b286247f608efcadd5ef0afd232` | `docs/architecture/reports/PHASE_2_HUMAN_AND_MCU_REFERENCE_COMPARISON_2026-11-06.md` | `4e568e89cfefc4c7dab05ad941afb32025bcafa5` |
| #186 | `53278d5918163b286247f608efcadd5ef0afd232` | `docs/architecture/reports/PHASE_2_WHOLE_BRAIN_CAPABILITY_TO_SOURCE_INTEGRATION_MAP_2026-11-05.md` | `fd7f0cfdf7f65ef06df000edc48b62d7088ac317` |
| #186 | `53278d5918163b286247f608efcadd5ef0afd232` | `docs/architecture/reports/PR_174_FOLLOW_ON_REVIEW_PROVENANCE_RECOVERY_2026-11-06.md` | `41ae1599ce824471635439b2a991acc79c449407` |
| #186 | `53278d5918163b286247f608efcadd5ef0afd232` | `docs/architecture/reviews/PHASE_2_CLOSEOUT_BUILDER_HANDOFF_2026-11-06.md` | `0296d07f14343c384a28184a21083f7308d3fbef` |
| #187 | `8e18f5eb2f8921e4bcd5d8441d432b5923d28da8` | `docs/architecture/reports/PHASE_2_DONOR_RUNTIME_FAIRNESS_AND_RECOVERY_TEST_CONTRACT_2026-11-06.md` | `4dcb63afc3db9e7a10ffee97e6ffb399ca4154de` |
| #187 | `8e18f5eb2f8921e4bcd5d8441d432b5923d28da8` | `docs/architecture/reports/PHASE_2_HUMAN_AND_MCU_REFERENCE_COMPARISON_2026-11-06.md` | `3755020c5e43d2cbc6b064e2b82b873d7f2f3db8` |
| #187 | `8e18f5eb2f8921e4bcd5d8441d432b5923d28da8` | `docs/architecture/reports/PHASE_2_WHOLE_BRAIN_CAPABILITY_TO_SOURCE_INTEGRATION_MAP_2026-11-05.md` | `0997100b91fe9f1dc658b6bacd3e0ca0a84975f9` |
| #188 | `36b843f6959628a689d81bc1e12e523e17227073` | `docs/architecture/reviews/PHASE_2_INDEPENDENT_REVIEW_FOLLOWUP_2026-11-06.md` | `1b9c691d80a315e2d13bf95975644e895c8495da` |
| #189 | `46796725fd656628f7b6e47a57929b87f79a6d8d` | `docs/architecture/reviews/PHASE_2_WHOLE_BRAIN_MAP_INDEPENDENT_REVIEW_2026-11-06.md` | `870481186434027414ba35a90cf8833810b1e527` |
| #190 | `a1df22531765b7022f6bfbcfd9f3f5251cf5adf5` | `docs/architecture/reviews/PHASE_2_THIRD_INDEPENDENT_REVIEW_2026-11-06.md` | `d3c3e79f38e90a86968261578eaebaf3194d2387` |

PR #180 is closed but unmerged; its single map artifact remains preserved as a historical revision. PRs #160, #164, #166–#170 and #181–#190 are open at this snapshot; the PR listing identifies their authors as `methaneex-oss`. In particular, the PRs titled as independent Phase 2 reviews (#183, #184, #188, #189, #190) were authored by that same repository account and have no formal GitHub review submissions. Their titles and report contents do not establish an independent reviewer identity or satisfy DF-11.

### 5.3 Exact PR #192 parent snapshot immediately before this register expansion — 26 paths

At exact PR #192 parent HEAD `8b6c257bc40748e3d96a0fdf2272b774f54d7a17`, immediately before this register expansion commit `9a8c12eb238dd5cd1b223497583dcd39bc492aea`, base `61311fe5b44c81c4409c8ba8dc581a83bdd5dd2c`, state open/draft/unmerged, all 26 changed paths were fetched. Each fetched blob matched the GitHub PR-files API. The complete recursive tree contained 255 entries / 227 blobs and was not truncated. This is a historical parent snapshot; later control-document commits are covered by the final Builder closure report and inventory.

| Repository path | Blob SHA |
|---|---|
| `README.md` | `780651b804b491781fdcac8e248eaca9243797a4` |
| `docs/ARCHITECTURE.md` | `3c6692b52059e43947d1fd2e7e84debb2362023f` |
| `docs/JARVIS_BRAIN_MASTER_BLUEPRINT.md` | `0e49d313bf3929aa30140cb7149ebab038918378` |
| `docs/JARVIS_PHASE_2_COMPLETION.md` | `e0e57a44216fc36c52d469a79abfc8df058515a3` |
| `docs/README.md` | `da0d9c834e8a5b2e67519ee5e0a2927bcec96374` |
| `docs/architecture/00_JARVIS_PLANNING_DOCUMENTATION_INDEX_2026-11-07.md` | `55460e51488777adffd5ff5d8536ce9aa5b03cab` |
| `docs/architecture/inventory/00_JARVIS_DOCUMENTATION_AND_ARTIFACT_INVENTORY_2026-11-04.md` | `1ce4914b2a84acb1b6bfbd8f9ca035cb1784ad66` |
| `docs/architecture/inventory/HISTORICAL_DOCUMENTATION_PRESERVATION_REGISTER_2026-11-08.md` | `96539183fab3a2b630a8e9154f183b0bfada9016` |
| `docs/architecture/reports/BUILDER_FINAL_DOCUMENTATION_FOUNDATION_RECONCILIATION_2026-11-08.md` | `f4687a09bac754f7d7cc8d59543ac2f6e08c28df` |
| `docs/architecture/reports/BUILDER_TO_INDEPENDENT_REVIEWER_REQUEST_2026-11-08.md` | `c458f689ccbcd1e1d54242e38648ca151d70c250` |
| `docs/architecture/reports/DOCUMENTATION_FOUNDATION_OUTSTANDING_WORK_CLOSURE_AND_AUTHORITY_REGISTER_2026-11-08.md` | `e833e9df4db78e5bb486a2b0e328d3cd4452977b` |
| `docs/architecture/reports/DOCUMENTATION_FOUNDATION_PRESERVATION_AND_LINK_VALIDATION_2026-11-08.md` | `ca176064543336ddf7d2e038ba3ee6d0c822c283` |
| `docs/architecture/reports/INDEPENDENT_DOCUMENTATION_FOUNDATION_REVIEW_2026-11-08.md` | `c43d82ba18ff89de226d2268cf72e724b222a5bd` |
| `docs/architecture/reports/INDEPENDENT_REVIEWER_HANDOFF_2026-11-08.md` | `60d096d174a5e03312886ad1ea5d6c01750e7f41` |
| `docs/architecture/reports/INDEPENDENT_RE_REVIEW_BUILDER_FOLLOW_UP_2026-11-08.md` | `2d63ed93344a7081dcedb44247536c416322c793` |
| `docs/architecture/reports/INITIAL_DOCUMENTATION_FOUNDATION_AUDIT_AND_COMPLETION_GATE_2026-11-07.md` | `955a6c953cdf539a6f478a2d472a327666845e4c` |
| `docs/architecture/reports/PHASE_1_REVIEW_CORRECTIONS_AND_SCOPE_RECONCILIATION_2026-11-05.md` | `a459cdfd02d850d455ca526e6823e68525776ba3` |
| `docs/architecture/reports/PHASE_1_WHOLE_REPOSITORY_INVESTIGATION_AND_REUSE_AUDIT_2026-11-04.md` | `7dc1a246486abfb13169c89365289fcc8134a6ea` |
| `docs/architecture/reports/PHASE_2_WHOLE_BRAIN_CAPABILITY_TO_SOURCE_INTEGRATION_MAP_2026-11-05.md` | `9dd776920d0a479a9d7275acc821e12c266623d9` |
| `docs/architecture/reports/PR_174_FOLLOW_ON_REVIEW_PROVENANCE_RECOVERY_2026-11-06.md` | `d01fa6170b87254619d469d276ba57e813c08ff3` |
| `docs/architecture/reports/WHOLE_BRAIN_DOCUMENTATION_PHASE_BUILDER_SELF_REVIEW_2026-11-07.md` | `db10fd69d25cf09fce6df2caabe164fc9314ad00` |
| `docs/architecture/reports/WHOLE_BRAIN_PLANNING_SCOPE_AND_BUILDER_CORRECTION_2026-11-07.md` | `0187a0ac71bd0c95e94beb3bf006da9cc7c3605f` |
| `docs/templates/INDEPENDENT_REVIEW_REPORT_TEMPLATE.md` | `f3176cf1a1f45735a3ad62fa4a865806edc24e08` |
| `docs/templates/PLANNING_DOCUMENT_TEMPLATE.md` | `b9f71a923b0d717a3b29655574c89c10e0801115` |
| `docs/templates/README.md` | `7209fd0fcda239349af602490d26b8c708b743da` |
| `docs/templates/TEST_EVIDENCE_REPORT_TEMPLATE.md` | `9c6bbae48a22beb7c4e95858282d7d8d7b2159c2` |

This exact parent snapshot supersedes the earlier PR #192 live-state rows in §1/§2/§4, which remain historical. The final live HEAD is recorded by the Builder closure report and the final inventory parent-snapshot manifest. It also corrects the earlier 68-path total: six PR #192 artifacts omitted from that earlier table are now present above, and the broader 18-PR set in §5.2 adds 34 more paths. Together with the 68 previously registered paths, the expanded documentation lineage contains 108 paths across 28 PRs.

### 5.4 Corrected current PR #193 snapshot — 2 paths

PR #193 remains open/draft/unmerged, separate from PR #192, at HEAD `65220543416da9b368f24e226aefe24bcdbc7870`, base `874c732973b6ab303d65a503f5a215b0af8e1153`:

| Repository path | Blob SHA |
|---|---|
| `docs/architecture/plans/00_BRAIN_IMPLEMENTATION_PLAN.md` | `3a07b45f85dd540c3b39c2150723cf983bb218c6` |
| `docs/architecture/plans/JARVIS_PROJECT_CONTINUITY_AND_RECOVERY_HANDOFF.md` | `77bb207efb26e71345138901a8027dfe3525edf1` |

### 5.5 Reviewer-identity and preservation boundary

The repository contains several review-labelled branches and reports. The reviewed records disclose GPT-6 as the same model identity as Builder in the Builder Response Re-review, Documentation Foundation Re-review and Independent Documentation Foundation Review. The Independent Builder Report Re-review does not disclose a reviewer identity or independence basis. The report in `docs/review-records/documentation-foundation/2026-11-08_DOCUMENTATION_FOUNDATION_REVIEW_REPORT.md` also explicitly identifies GPT-6 as both Builder and reviewer. None of these records qualifies as DF-11 independent review. No reviewer is assigned, and the previously posted PR #192 review request has been withdrawn/suspended as premature.

The original PR #174 formal review list and inline review-comment endpoint both returned zero records; PR #173 likewise returned zero formal reviews and zero inline review comments. PR #173's two conversation comments are Builder-authored handoff/resubmission comments, not a direct Project Director acceptance decision. PR #174's conversation contains the Project Director decision comment `6604790481`, accepting exact HEAD `0811a59e46bf934e32e794f90e4e7d18d4e2bd97` as the Brain Mechanism Specification planning baseline only. F-02/F-03 remain open; no missing review content is invented.

No branch was deleted or moved, no historical file was relocated, and no PR was merged, rebased, retargeted or cherry-picked. The register closes the Builder's bounded current branch/PR discovery and path/blob mapping work. Any archive relocation, disputed historical acceptance disposition, PR #191 integration choice, and PR #192/#193 order remain Project Director decisions.


### 5.6 Final Builder closeout parent snapshot — 2026-11-08

At the start of the final Builder closeout pass, PR #192 was open/draft/unmerged at parent HEAD `5fb1e15c38c4fb4e3a117f960c7d491217fdc2d8`, base `61311fe5b44c81c4409c8ba8dc581a83bdd5dd2c`, with 26 changed paths. This is a parent snapshot, not a claim that the PR remains at this SHA after the closeout commits.

The current package's 26 paths and exact parent blob identities are recorded in the detailed inventory's final §41 manifest. The final closeout pass re-fetched the 26 changed files at this parent revision, confirmed the changed-path set, and verified that the 22 unique repository-relative Markdown target paths used by the package exist at this exact revision. The current PR #192 and PR #193 lineages remain separate. PR #193 remains open/draft/unmerged at HEAD `65220543416da9b368f24e226aefe24bcdbc7870`, base `874c732973b6ab303d65a503f5a215b0af8e1153`, with two changed paths.

The 108-path / 28-documentation-PR register remains a bounded preservation map, not a claim that every historical file in the repository has been archived or that any artifact is accepted. Branch/file relocation, deletion, consolidation, disputed authority and archive/supersession policy remain outside Builder authority. No such operation was performed.
