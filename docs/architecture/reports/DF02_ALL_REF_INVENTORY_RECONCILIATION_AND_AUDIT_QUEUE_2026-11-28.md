# DF-02 All-Ref Inventory Reconciliation and Semantic Audit Queue — 2026-11-28

**Evidence:** frozen discovery artifact #14956148301, workflow #45470173876. Candidate PR #192 frozen SHA `caf87986dfea7aca75728818651c8687e9f5faf0`; donor PR #97 HEAD `c1da222e6c94aeb3f2ad000392c21fe4fc81ab25`.  
**Integrity:** downloaded archive SHA-256 reverified: `9902957475c76f4840d1d280c7d4f50537941e9445810afb805132374a328f38`.  
**Purpose:** inventory reconciliation and audit ordering only. This is not semantic closure, ownership authority, source selection or retirement evidence.

## 1. Reconciled scan totals

- 254 refs scanned; 213 unique tips; eight duplicate-tip groups.
- 159 donor paths; candidate same-path statuses: 95 divergent, 63 absent, one identical.
- 1,416 unique text blobs scanned; no binary blobs skipped in this artifact.
- 798 path/blob ownership rows.
- 1,946 exact-path reference candidates across 159 donor paths, 76 consumer paths and 101 consumer blobs. Categories: 1,930 documentation, 15 workflow, one other.
- 40,048 symbol-match candidates across 502 identifiers, 346 consumer paths and 1,135 consumer blobs. Categories: source 23,948; test 14,974; workflow 861; build 237; other 28. Symbol/path hits are discovery candidates and can include comments, strings, tests, incidental references or false positives.
- Unique blob versions per donor path: median 3; mean 5.02; range 1–40. The source CSV totals 23,978 tip-presence rows and 9,889 tip-absence rows. Presence/absence is occurrence metadata, not independent implementation count.

## 2. Prioritized path cohort queue

Priority uses **version dispersion + lexical consumer-match volume + exact-path reference volume** to order further manual source/consumer work. This heuristic is not a semantic risk score. Paths already covered by exact cohort reports still need consumer, owner/authority and retention closure.

| Rank | Donor path | Candidate status | Distinct blobs | Tips present / absent | Exact refs | Symbol matches |
|---:|---|---|---:|---:|---:|---:|
| 1 | core/cpp/tests/CMakeLists.txt | DIVERGENT | 40 | 212 / 1 | 36 | 124 |
| 2 | core/cpp/src/brain.cpp | DIVERGENT | 35 | 212 / 1 | 34 | 665 |
| 3 | engineering/cpp/CMakeLists.txt | DIVERGENT | 35 | 185 / 28 | 7 | 0 |
| 4 | core/cpp/tests/evolution_brain_integration_suite.cpp | DIVERGENT | 24 | 196 / 17 | 19 | 615 |
| 5 | core/cpp/CMakeLists.txt | DIVERGENT | 22 | 212 / 1 | 31 | 42 |
| 6 | core/cpp/include/jarvis/core/brain.hpp | DIVERGENT | 21 | 212 / 1 | 32 | 1,063 |
| 7 | core/cpp/src/brain_restored_api.cpp | DIVERGENT | 20 | 116 / 97 | 23 | 3,616 |
| 8 | core/cpp/src/evolution_controller.cpp | DIVERGENT | 19 | 196 / 17 | 18 | 968 |
| 9 | core/cpp/tests/evolution_experiment_runner_suite.cpp | DIVERGENT | 18 | 197 / 16 | 8 | 115 |
| 10 | core/cpp/tests/evolution_canary_controller_suite.cpp | DIVERGENT | 17 | 196 / 17 | 15 | 363 |
| 11 | core/cpp/src/evolution_experiment_runner.cpp | DIVERGENT | 17 | 197 / 16 | 8 | 222 |
| 12 | core/cpp/include/jarvis/core/evolution_experiment.hpp | DIVERGENT | 15 | 197 / 16 | 9 | 1,120 |
| 13 | core/cpp/src/process_isolation.cpp | DIVERGENT | 15 | 193 / 20 | 8 | 139 |
| 14 | core/cpp/tests/evolution_opportunity_orchestration_suite.cpp | DIVERGENT | 14 | 195 / 18 | 6 | 0 |
| 15 | core/cpp/include/jarvis/core/evolution_experiment_runner.hpp | DIVERGENT | 13 | 197 / 16 | 7 | 190 |
| 16 | core/cpp/src/evolution_experiment_coordinator.cpp | DIVERGENT | 13 | 196 / 17 | 8 | 188 |
| 17 | core/cpp/tests/evolution_experiment_coordinator_suite.cpp | DIVERGENT | 13 | 196 / 17 | 6 | 0 |
| 18 | core/cpp/tests/memory_learning_evolution_persistence_suite.cpp | CANDIDATE_ABSENT | 12 | 63 / 150 | 7 | 252 |
| 19 | core/cpp/src/evolution_adoption_journal.cpp | DIVERGENT | 11 | 192 / 21 | 16 | 565 |
| 20 | core/cpp/include/jarvis/core/evolution_adoption_journal.hpp | DIVERGENT | 10 | 192 / 21 | 7 | 686 |
| 21 | core/cpp/src/evolution_orchestrator.cpp | DIVERGENT | 10 | 195 / 18 | 8 | 223 |
| 22 | core/cpp/src/cognitive_cycle.cpp | DIVERGENT | 10 | 212 / 1 | 34 | 141 |
| 23 | core/cpp/tests/developmental_brain_integration_suite.cpp | CANDIDATE_ABSENT | 9 | 77 / 136 | 16 | 794 |
| 24 | engineering/cpp/src/message_bus.cpp | DIVERGENT | 9 | 161 / 52 | 6 | 788 |
| 25 | core/cpp/src/memory.cpp | DIVERGENT | 9 | 212 / 1 | 30 | 754 |
| 26 | engineering/cpp/include/jarvis/engineering/agent.hpp | DIVERGENT | 9 | 185 / 28 | 6 | 428 |
| 27 | engineering/cpp/include/jarvis/engineering/message_bus.hpp | DIVERGENT | 9 | 161 / 52 | 6 | 423 |
| 28 | core/cpp/tests/memory_architecture_suite.cpp | DIVERGENT | 8 | 212 / 1 | 9 | 436 |
| 29 | core/cpp/src/knowledge.cpp | DIVERGENT | 8 | 212 / 1 | 29 | 159 |
| 30 | engineering/cpp/src/coordinator.cpp | DIVERGENT | 8 | 185 / 28 | 15 | 70 |
| 31 | core/cpp/src/cognitive_runtime.cpp | DIVERGENT | 7 | 212 / 1 | 28 | 435 |
| 32 | core/cpp/tests/cognitive_cycle_suite.cpp | DIVERGENT | 7 | 212 / 1 | 9 | 194 |
| 33 | core/cpp/tests/learning_adaptation_phase8_suite.cpp | DIVERGENT | 7 | 205 / 8 | 9 | 133 |
| 34 | core/cpp/include/jarvis/core/evolution_experiment_coordinator.hpp | DIVERGENT | 7 | 196 / 17 | 7 | 111 |
| 35 | core/cpp/tests/knowledge_memory_phase3_suite.cpp | DIVERGENT | 7 | 210 / 3 | 15 | 0 |
| 36 | core/cpp/src/developmental_learning.cpp | CANDIDATE_ABSENT | 6 | 77 / 136 | 21 | 476 |
| 37 | core/cpp/include/jarvis/core/cognitive_runtime.hpp | DIVERGENT | 6 | 212 / 1 | 25 | 438 |
| 38 | core/cpp/include/jarvis/core/cognitive_cycle.hpp | DIVERGENT | 6 | 212 / 1 | 22 | 433 |
| 39 | core/cpp/include/jarvis/core/knowledge.hpp | DIVERGENT | 6 | 212 / 1 | 15 | 298 |
| 40 | core/cpp/src/evolution_safety.cpp | DIVERGENT | 6 | 196 / 17 | 8 | 57 |

## 3. Interpretation and queue policy

- High dispersion is a warning that the path has many historical content states; it is not proof of many independent implementations or a defect.
- Large symbol-match counts (especially restored Brain API) require exact consumer context filtering and reverse-dependency analysis before conclusions.
- Candidate-absent paths need alternate successor search outside same-path comparison. Their absence from frozen candidate is not evidence of non-use or retirement authorization.
- CMake and integration tests should be reconciled with production source ownership first because they determine actual compile/test reachability. This does not replace behavior review.
- Reports already added for restored Brain API, process isolation, cognitive runtime/cycle and several evolution/memory cohorts provide bounded evidence; use those as source material and continue remaining path cohorts in this queue without duplicating their claims.
- Every eventual ledger row must distinguish: source blobs inspected; semantic variants grouped; exact declaration/definition; compiled/test/workflow reachability; real consumer context; owner-tip provenance; authority; retention/retirement; verification performed; unresolved issues; and independent scrutiny. No row is CLOSED merely because its source was fetched or compared.

## 4. Current disposition

This queue establishes reproducible priorities and exact counts only. DF-02 Phase 2 remains PARTIAL; Phases 3 and 4 remain NOT COMPLETE; no 159-path semantic/authority closure ledger is complete. No implementation selected, adopted, retired, deleted or baseline-authorized. Stage A remains HELD.

## New completed bounded source cohort

- `core/cpp/src/cognitive_runtime.cpp` / `core/cpp/include/jarvis/core/cognitive_runtime.hpp`: [Cognitive Runtime Feedback/Action Adjudication](DF02_COGNITIVE_RUNTIME_FEEDBACK_ACTION_VARIANT_ADJUDICATION_2026-11-28.md), blob SHA `54108cd05bec044050be5d6e6f55a748ddae0cf2`. Exact candidate/donor and CMake/test comparison. Donor feedback/action/perception additions and fairness/shutdown/callback risks identified. Source inspection only; no tests. The path remains OPEN.

## New completed bounded source cohort

- `core/cpp/src/memory.cpp` and `core/cpp/include/jarvis/core/memory.hpp`: [Memory Retrieval/Consolidation Adjudication](DF02_MEMORY_RETRIEVAL_CONSOLIDATION_VARIANT_ADJUDICATION_2026-11-28.md), SHA `e844e219fe292255a8f2d87c7136708086e46470`. Exact candidate/donor/test/CMake review. Donor retrieval/consolidation improvements and durability/migration risks recorded. Source-only; no path closure.

 
## Reconciled 159-path inventory table — 2026-11-28

A repository-resident path-level inventory has now been created from the SHA-verified discovery artifact:
- File: docs/architecture/ledgers/DF02_159_PATH_INVENTORY_2026-11-28.csv
- Verified Git blob SHA: 61e0d6c572e6d27a24f2f1cb29d3614f7284ed0a
- 159 data rows, 159 unique donor paths, no duplicate paths.
- Same-path candidate statuses: 95 DIVERGENT, 63 CANDIDATE_ABSENT, one IDENTICAL.
- 96 rows have a candidate blob SHA (95 divergent + one identical); all 159 donor blob SHAs are syntactically valid 40-character Git blob identifiers.
- Each row carries donor/candidate blob SHA where present, same-path status, distinct blob-version count across tips, present/absent tip counts, donor-identical/divergent tip counts, symbol-match count and exact-path-reference count.

The ledger is a reconciled **path inventory**, not the completed semantic/authority closure ledger. It does not include every alternate blob SHA or every branch name inline; the original artifact's 798 path/blob ownership rows and full branch/tip provenance remain the source for those details. All 159 paths remain semantically OPEN until exact variants, declarations/definitions, compiled/test/workflow reachability, reverse consumers, owner/authority, provenance and retention are individually adjudicated. Candidate absence is not retirement authority; same-path identity is not semantic equivalence.

The 159-row CSV was fetched back and validated after writing: 160 lines including header, 159 unique data paths, expected status counts, valid donor SHA shape and no duplicate paths. This validation is structural only; it does not independently re-derive every row against all 798 ownership records.

 
### Full-path reference scanner limitation found by Builder self-review

The CSV column exact_path_reference_rows and artifact exact_path_reference_matches count literal repository-relative path-string matches. They are **not** a complete build-graph/reachability inventory. CMake commonly references a source by basename (for example, add_executable(... brain_action_consequence_integration_suite.cpp)), so a full-path matcher can miss a real build/test edge.

Concrete counterexample:
- Donor core/cpp/tests/CMakeLists.txt blob cbfd1fde52fffa6eeac025da2b7ddcb5ab493261 registers jarvis_brain_action_consequence_integration_suite using basename brain_action_consequence_integration_suite.cpp at lines 187–189 and CTest at line 285.
- Candidate CMake blob dab0c52ab4dfe15e1e2cbccfa9e6c904abdf54e3 does not register it.
- The inventory artifact's full-path reference matches for this donor path contain documentation references but omit these CMake basename references.

Accordingly, exact_path_reference_rows in the 159-path CSV is a lower-bound literal-reference count, not a proof of non-reachability when zero. A full closure pass must parse CMake source arguments/target registration, workflow commands, scripts, generated-source rules and include relationships by normalized basename/path. The path inventory remains useful for blob identity and variant ownership, but build reachability is still OPEN.

 
### Explicit code-owner / authority / retention evidence check — 2026-11-28

The repository has no root CODEOWNERS, .github/CODEOWNERS, root OWNERS or .github/OWNERS file (all four exact GitHub contents lookups returned 404). The active governance document assigns Project Director, Project Builder, Independent Reviewer and Blind Fresh Tester responsibilities, but does not assign per-path subsystem maintainers or authorize donor baseline/retention decisions.

Consequences:
- The 798 path/blob ownership rows and 213 branch-tip inventory establish content provenance and branch reachability, not human code ownership or authority.
- Branch names, tip counts, commit authorship and source similarity are not evidence that a branch author is the technical owner or that a source variant is approved.
- No per-path owner can be responsibly inferred from the current repository evidence. The code-owner field is therefore UNASSIGNED / NOT EVIDENCED for the 159-path corpus.
- Authority to select a baseline, adopt/retire/delete a donor, retain historical branches or change protected/review state remains with the Project Director under the accepted governance.
- Retention/retirement evidence is incomplete: no per-path retention rationale, archival owner, deprecation decision or deletion authority is recorded. Do not delete or prune historical variants.

This is a governance/evidence gap, not permission for the Builder to invent owners or make retention decisions. The Builder can continue technical semantic adjudication and prepare evidence-backed recommendations; owner assignment, authority and retention acceptance remain explicit Director decisions.

 
## Builder coverage map for the 159-path inventory — 2026-11-28

The following high-priority cohorts have bounded source/test/build evidence reports. Status is deliberately PARTIAL: a report or passing historical test does not close provenance, owner, authority, retention, reverse-consumer and independent-verification requirements for every path.

| Inventory path/cohort | Durable evidence report | Builder status |
|---|---|---|
| core/cpp/tests/CMakeLists.txt; core/cpp/CMakeLists.txt | DF02_CORE_CPP_TEST_CMAKE_VARIANT_ADJUDICATION_2026-11-28.md; DF02_CORE_CPP_LIBRARY_CMAKE_VARIANT_ADJUDICATION_2026-11-28.md | PARTIAL — candidate/donor/alternate graphs and test-source identities reconciled for inspected refs; all 40 CMake variants not yet semantically adjudicated |
| core/cpp/src/brain.cpp; core/cpp/include/jarvis/core/brain.hpp; core/cpp/src/brain_restored_api.cpp | DF02_RESTORED_BRAIN_API_OWNERSHIP_VARIANT_ADJUDICATION_2026-11-27.md | PARTIAL — API/TU ownership and donor deep test evidence; full reverse-consumer and authority closure open |
| core/cpp/src/process_isolation.cpp; core/cpp/include/jarvis/core/process_isolation.hpp; process-isolation tests | DF02_PROCESS_ISOLATION_VARIANT_ADJUDICATION_2026-11-27.md; DF02_PROCESS_ISOLATION_CHILD_LIFECYCLE_AND_CONTROL_ADJUDICATION_2026-11-27.md | PARTIAL — candidate/donor/alternate semantics and e737 CI evidence; adversarial lifecycle/control tests and owner/authority open |
| core/cpp/src/cognitive_runtime.cpp; cognitive_runtime.hpp; runtime integration tests | DF02_COGNITIVE_RUNTIME_VARIANT_AND_CLOSED_LOOP_ADJUDICATION_2026-11-27.md | PARTIAL — closed-loop test contract and historical e737 CI; current candidate CTest and broader semantic/generalization evidence open |
| core/cpp/src/memory.cpp; core/cpp/include/jarvis/core/memory.hpp; memory tests | DF02_MEMORY_RETRIEVAL_CONSOLIDATION_VARIANT_ADJUDICATION_2026-11-28.md; DF02_MEMORY_LEARNING_EVOLUTION_PERSISTENCE_INTEGRATION_VARIANT_ADJUDICATION_2026-11-27.md | PARTIAL — retrieval, journal variants, CI and failure-path defects; recovery failure, metadata degradation, nonfinite scoring, portable serialization and multi-writer integrity open |
| core/cpp/src/association_model.cpp; core/cpp/src/causal_model.cpp; phase-5 suite | DF02_ASSOCIATION_CONTEXTUAL_GENERALIZATION_AND_CAUSAL_HYPOTHESIS_ADJUDICATION_2026-11-27.md | PARTIAL — exact donor test passed historically; intervention/counterfactual causal validity and nonfinite input validation open |
| core/cpp/src/brain_prediction_context.cpp; phase-10 suite | DF02_CONTEXTUAL_PREDICTION_NUMERIC_CALIBRATION_ADJUDICATION_2026-11-27.md | PARTIAL — contextual donor test passed historically; candidate test source differs; calibration/generalization/contamination tests open |
| core/cpp/src/developmental_learning.cpp; developmental environment suites | DF02_DEVELOPMENTAL_LEARNING_CONTEXT_TRANSFER_ADJUDICATION_2026-11-27.md | PARTIAL — context-bounded synthetic learning tests passed historically; open-world transfer and safety remain unproven |
| core/cpp/src/affective_state.cpp; affective learning/state tests | DF02_AFFECTIVE_STATE_APPRAISAL_LEARNING_ADJUDICATION_2026-11-27.md | PARTIAL — historical donor suites passed; calibration, evidence-floor and long-duration stability remain open |
| core/cpp/src/attention.cpp; attention learning tests | DF02_ATTENTION_SALIENCE_FEEDBACK_PERSISTENCE_ADJUDICATION_2026-11-27.md | PARTIAL — historical donor test passed; fairness/starvation, numeric robustness and calibrated utility remain open |
| core/cpp/src/action_execution.cpp; brain_action_execution.cpp; action consequence tests | DF02_ACTION_EXECUTION_AND_CONSEQUENCE_PERSISTENCE_ADJUDICATION_2026-11-27.md | PARTIAL — historical action/consequence tests passed; persistence failure semantics and real actuator safety remain open |
| core/cpp evolution controller, runner, coordinator, adoption journal, orchestrator, safety and associated headers/tests | DF02_EVOLUTION_TEST_CONTRACT_ADJUDICATION_2026-11-27.md; DF02_EVOLUTION_TRUST_LIFECYCLE_EXACT_COMPARISON_2026-11-27.md; DF02_EVOLUTION_CONTROLLER_TRANSACTION_AND_ROLLBACK_ADJUDICATION_2026-11-27.md; DF02_EVOLUTION_EVENT_REPLAY_AUTHORITY_BOUNDARY_ADJUDICATION_2026-11-27.md; related coordinator/runner/adoption reports | PARTIAL — candidate/donor/third-lineage test contracts and historical e737 execution; full trust-key lifecycle, durable failure atomicity, branch ownership and authority open |
| engineering/cpp/include/jarvis/engineering/message_bus.hpp; engineering/cpp/src/message_bus.cpp; agent.hpp; coordinator.cpp | DF02_ENGINEERING_MESSAGE_BUS_TASK_LEDGER_AUTHORITY_ADJUDICATION_2026-11-28.md | PARTIAL — exact candidate/donor API and authority deltas inspected; runtime adoption/retirement prohibited and not decided |

No cohort above is marked COMPLETE or CLOSED. The 159-path CSV remains the structural inventory; this table is a partial coverage index, not a substitute for a 159-row semantic/authority closure ledger.

## Remaining high-priority queue after these bounded cohorts

Continue with the highest-dispersion paths not yet covered by a complete exact report, especially:
- engineering/cpp/CMakeLists.txt and engineering/cpp/tests/CMakeLists.txt (all 35 variants and their parent-level includes);
- core/cpp/src/evolution_controller.cpp and evolution_experiment_runner.cpp, including all 19/17 variants, source-to-header contract and exact alternate CI;
- core/cpp/include/jarvis/core/evolution_experiment.hpp, evolution_experiment_runner.hpp and evolution_experiment_coordinator.hpp;
- core/cpp/src/evolution_adoption_journal.cpp and evolution_orchestrator.cpp, including replay, atomicity and recovery failure paths;
- core/cpp/src/cognitive_cycle.cpp and associated headers/tests, including execution ordering, feedback timing and exception paths;
- core/cpp/src/knowledge.cpp and core/cpp/include/jarvis/core/knowledge.hpp;
- remaining source/test paths in the 159 inventory not listed above.

For each next cohort, preserve the same discipline: immutable candidate/donor/alternate blobs; exact API/implementation/test source comparisons; CMake/TU/symbol reachability; behavioral tests and current-vs-historical CI attribution; reverse consumers; branch-tip provenance; explicit owner/authority/retention status; and independent scrutiny only after Builder self-review. No source path is closed by mention in this table.
