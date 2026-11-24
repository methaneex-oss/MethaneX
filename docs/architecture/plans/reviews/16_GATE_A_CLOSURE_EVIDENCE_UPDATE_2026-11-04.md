# Gate A — Closure Evidence Update

**Date:** 2026-11-04  
**PR:** #175 — planning/implementation evidence only  
**Planning branch:** plan/brain-implementation-roadmap-20261103  
**Governing specification:** PR #174 accepted HEAD 0811a59e46bf934e32e794f90e4e7d18d4e2bd97  
**Candidate code-bearing parent:** 15d49e5fdeb5723c475922ab78fb92f97c4b3b84  
**Builder recommendation:** Report 13  
**Independent technical review:** Report 14  
**Builder/Reviewer reconciliation:** Report 15

## 1. Executive disposition

The six requested closure workstreams have now been materially advanced with new repository evidence.

- Provenance: corrected exact three-tree classification and risk-based source attribution are documented in Report 08 and this report.
- API compatibility: the earlier seven-API count was incomplete. The full candidate public-header delta and repository-wide C++ call-site inventory are now documented in Report 09.
- Workflow continuity: all five current-main workflow contracts have workflow-by-workflow preservation/adaptation specifications in Report 10.
- D1/D2: corrected implementation and regression tests are on draft PR #176, not merged into PR #156.
- Multi-event consistency: deterministic journal-failure and restart/replay tests cover goal completion and evolution rollback boundaries on PR #176. One deeper controller-internal compensation failure boundary remains un-injected.
- Independent re-check: still outstanding. No separate reviewer GitHub identity was supplied or found in the report commit metadata, and PR #175 has no submitted formal review.

**Gate A remains NOT CLEARED.** This is not because the integration strategy is undecided. The strategy remains accepted as the Builder recommendation: start integration from accepted PR #174 and selectively port reviewed mechanisms from PR #156. The remaining blockers are correction-branch integration, the residual controller compensation boundary, and an actual independent re-check.

## 2. Provenance closure — corrected exact tree comparison

Report 08 now contains the authoritative three-tree result:

- PR #97 base: 4ba84b8b5ccf0e41530c46fdb8101551254ba864
- PR #97 head: c1da222e6c94aeb3f2ad000392c21fe4fc81ab25
- Candidate code-bearing parent: 15d49e5fdeb5723c475922ab78fb92f97c4b3b84

The 165-path base-to-candidate delta is correctly partitioned into:
- 143 paths changed by PR #97 and byte-for-byte unchanged after PR #97;
- 16 paths changed in both PR #97 and the post-PR #97 segment;
- 2 existing paths modified only after PR #97;
- 4 files first introduced after PR #97.

The previous 145 / 14 / 6 classification was corrected. Two world-model paths were moved from “new” to “post-PR #97 modified existing”; evolution_controller.cpp and evolution_canary_controller_suite.cpp were moved from “PR #97-only” to “post-PR #97 modified existing”. All exact blob identities for the 16 overlap, two modified-existing and four new paths are in Report 08 §7.

### 2.1 High-risk PR #97-only source attribution

For all 143 PR #97-only paths, the candidate blob exactly matches the PR #97 head blob. The following high-risk source paths were additionally traced to their file-introduction commit and latest path-touching commit. The latest commit is a source-history pin; where it is c1da222, that commit is the PR #97 integration checkpoint rather than a new semantic change.

| Candidate path | Introduced | Latest path-touching commit | Semantic scope evidenced by path history |
|---|---|---|---|
| core/cpp/src/action_execution.cpp | f74be717 | 239cf2de | Controlled execution; unknown consequence is not neutral |
| core/cpp/src/adaptation.cpp | 0e130a81 | 2fa85bb3 | Prediction-error adaptation; sustained surprises under noisy baselines |
| core/cpp/src/association_model.cpp | 5e5da77e | 09f5006f | Association learning and shared-context concept generalization |
| core/cpp/src/attention.cpp | c5d3454a | ad7f2d31 | Adaptive attention; prediction-error feature normalization |
| core/cpp/src/cognitive_runtime.cpp | ec634d4b | cf6c0570 | Runtime action execution restricted to selected plan |
| core/cpp/src/decision.cpp | 2e2f2421 | 73dbf6ba | Adaptive action ranking and signed expected consequences |
| core/cpp/src/evolution.cpp | fc3d30db | 8b2a5d2e | Fitness-driven adaptation and rollback value preservation |
| core/cpp/src/evolution_adoption.cpp | af9a8974 | c1da222 | Adoption lifecycle and integration validation |
| core/cpp/src/evolution_adoption_journal.cpp | ecdbe26e | c1da222 | Durable adoption journal and integration validation |
| core/cpp/src/evolution_canary.cpp | 5337399c | 09ee20cc | Canary regression detection and non-mutating preview |
| core/cpp/src/evolution_experiment_coordinator.cpp | 9f09beca | c1da222 | Multi-trial coordination and integration validation |
| core/cpp/src/evolution_experiment_runner.cpp | a02b443b | c1da222 | Isolated experiment execution and integration validation |
| core/cpp/src/evolution_history.cpp | ab21fc1f | b13d7cb1 | Thread-safe history and idempotent lifecycle appends |
| core/cpp/src/evolution_orchestrator.cpp | 764e251e | c1da222 | Opportunity detection and safe experiment orchestration |
| core/cpp/src/evolution_safety.cpp | 7a921ea0 | c1da222 | Evolution safety gates and integration validation |
| core/cpp/src/evolution_sandbox.cpp | 6c10747a | c1da222 | Bounded candidate execution and integration validation |
| core/cpp/src/goals.cpp | fd0ed93 | 6b75c0ba | Goal model and priority response to regression direction |
| core/cpp/src/intent.cpp | f918e49 | 134f64aa | Intent selection and learned goal-outcome momentum |
| core/cpp/src/memory.cpp | 586af14 | c1da222 | Persistent continuity memory and integration validation |
| core/cpp/src/planning.cpp | d0b3ee81 | e68a67ea | Action-sequence planning and reversible-action risk penalty |
| core/cpp/src/process_isolation.cpp | 6a19fd5b | c1da222 | Isolated execution and process-boundary controls |
| core/cpp/src/reasoning.cpp | 0b5dbcdc | c1da222 | Evidence-driven multi-step reasoning and integration validation |
| core/cpp/src/reflection.cpp | 546adc19 | 280c91f7 | Self-evaluation and uncertainty for ungrounded world models |
| core/cpp/src/representation.cpp | e1f37eb0 | af6a607b | Perceptual normalization and appraisal metadata separation |
| core/cpp/src/self_model.cpp | eba6608d | 86bc3cd2 | Dynamic self-model updated from action outcomes |
| core/cpp/src/affective_learning.cpp | ed10e329 | ed10e329 | Affective learning translation unit |
| core/cpp/src/affective_state.cpp | 6523b0d9 | f6f509af | Affective-state dynamics and causal tension appraisal |
| core/cpp/src/brain_action_execution.cpp | ceb6774f | c015679b | Action consequences and calibrated forecast value |
| core/cpp/src/brain_affective_planning.cpp | a9f5e110 | 83e3108f | Affective planning integration |
| core/cpp/src/brain_prediction_context.cpp | ac14e288 | 658025fe | Contextual prediction and consolidation of prediction experience |

### 2.2 High-risk PR #97-only interface attribution

The following headers were similarly traced to their first and latest path-touching commits. Their final candidate blobs match PR #97 head under the exact tree comparison.

| Candidate path | Introduced | Latest path-touching commit | Interface scope |
|---|---|---|---|
| core/cpp/include/jarvis/core/action_execution.hpp | 934c507c | 3df5df3d | Action execution evidence |
| core/cpp/include/jarvis/core/action_model.hpp | e3a12f4e | 2aaf00c2 | Developmental context in action assessment |
| core/cpp/include/jarvis/core/adaptation.hpp | 3b5ea7bb | 1d287395 | Sustained prediction surprises |
| core/cpp/include/jarvis/core/association_model.hpp | cfc019cf | df85f142 | Structural concept generalization |
| core/cpp/include/jarvis/core/attention.hpp | 5370a6c5 | 1965aaec | Prediction-error attention features |
| core/cpp/include/jarvis/core/cognition.hpp | 066dfbf7 | 64cfa374 | Cognitive API compatibility |
| core/cpp/include/jarvis/core/cognitive_cycle.hpp | 7a1ec823 | dbe8df55 | Extensible perception pipeline |
| core/cpp/include/jarvis/core/cognitive_runtime.hpp | 57c7e56d | 32315cf4 | Feedback processing state |
| core/cpp/include/jarvis/core/decision.hpp | 8f0daab2 | 86cd4930 | Learnable valuation weights |
| core/cpp/include/jarvis/core/evolution.hpp | 4cb1b77f | 09a07547 | Reversible evolution state |
| core/cpp/include/jarvis/core/evolution_controller.hpp | 7d5adad6 | 3a356413 | Adoption persistence compensation |
| core/cpp/include/jarvis/core/evolution_experiment.hpp | 5e2e4612 | c1da222 | Experiment lifecycle integration |
| core/cpp/include/jarvis/core/goals.hpp | d61013b9 | 786225ac | Persistent goal-outcome momentum |
| core/cpp/include/jarvis/core/intent.hpp | d9bfbe58 | b51d1915 | Affect-aware intent appraisal |
| core/cpp/include/jarvis/core/memory.hpp | f7d3e364 | e4709589 | Journal sequence indexing |
| core/cpp/include/jarvis/core/planning.hpp | cd62adff | e05ecf31 | Continuous affective planning signals |
| core/cpp/include/jarvis/core/self_model.hpp | f8048a27 | 86bc3cd2 | Self-model updates from action outcomes |

The 16 overlap paths, two post-PR #97 modified-existing paths and four post-PR #97 additions are individually listed with blob identities in Report 08. Their path histories and semantic integration changes are bounded by the source commits recorded there and in the underlying Git history.

### 2.3 Why the residual 1,416-commit hunk ledger is not required for this baseline decision

The risk-based alternative is now independently checkable at the final-tree level:
- all 165 final paths are accounted for;
- every path is assigned to one of four exact origin classes;
- all 143 unchanged PR #97 paths have blob equality against PR #97 head;
- all 22 post-PR #97 path changes are identified;
- the high-risk Brain/runtime source and interface paths have introduction/latest-touch attribution;
- the post-PR #97 integration paths are explicitly mapped.

The residual history is not silently approved. PR #156 is not recommended for wholesale adoption. Every selective port must still undergo path/hunk review against BM-01–BM-12 and the accepted scenarios. This means unattributed low-risk historical hunks cannot change the baseline recommendation; they can only affect a later individual port decision.

**Provenance workstream: CLOSED for the Gate A baseline recommendation under the risk-based standard.** This does not close mechanism capability acceptance.

## 3. API compatibility closure

Report 09 §7 supersedes the earlier seven-API count. The candidate public Brain header adds 26 public method names absent from current main, additional overloads, and signature-sensitive changes to the constructor, execute_action and register_evolution_parameter.

A repository-wide exact-identifier scan covered all .cpp/.hpp files under core/cpp:
- common changed-method call sites: Actions run 41805564990;
- candidate public API and call-site inventory: Actions run 41806123218.
Both scan workflows were temporary and removed after their successful runs. The complete method/file counts remain in the Actions logs and the condensed index is in Report 09.

The current-main CMake source list does not compile brain_restored_api.cpp; the candidate CMake source list does. Therefore source-body comparisons in that orphan current-main file are not evidence of a compiled current-main public API. Report 09 now distinguishes public declarations, compiled source membership and source-level definitions.

**API workstream: CLOSED for static in-repository declarations, overloads and call sites.** External ABI, function-pointer and downstream consumer compatibility remain mandatory later compile/link/rebuild gates; they are not claimed proven here.

## 4. Workflow continuity closure

Report 10 §5 now specifies all five workflows individually, including:
- exact current-main and candidate blob identity;
- triggers and ref filters;
- source_ref/tested_commit behavior;
- runner and timeout;
- build targets and test suites;
- trial duration, seeds and replication semantics;
- failure/timeout behavior and artifacts.

The resulting candidate dispositions are:
- DLT-002: exact file match;
- JBP MEM-001: adapt source_ref/tested_commit reproducibility controls;
- JARVIS learning mechanisms: restore the 35-gate plus integrated trial workflow;
- JBP BRAIN-INT-001: restore five integrated suites, persistence and smoke trial;
- JBP LEARNING-002: restore three independent seed-matrix runs.

The specification is complete. Workflow files have not been ported or run as part of this documentation closure. Candidate CMake target registration is not presented as successful workflow evidence.

**Workflow specification workstream: CLOSED.** Workflow adaptation/execution remains future integration work.

## 5. D1 and D2 corrections

A separate draft correction PR was created to keep runtime changes off documentation-only PR #175:

https://github.com/methaneex-oss/MethaneX/pull/176

Current correction branch head: 4cf017e073da980c9f77d739fde6f92ef1a2fbc1.

- D1: Brain::choose() and Brain::choose_with_affect() now use selected_intent.id for strategy context and the explicit global fallback when no intent is selected.
- D2: Brain::create_goal() rejects non-finite priority/progress before clamping or event creation.

Regression tests cover active-vs-pending goal identity, no-intent fallback, both decision APIs, restart/replay, NaN and both infinities for both numeric inputs, and side-effect-free rejection.

The correction PR is draft and unmerged. Therefore PR #156 itself still contains the defects until this correction is reviewed and merged or the fixes are selectively ported. No merge is authorized or claimed.

## 6. Multi-event consistency contract and failure-injection evidence

The donor correction branch now includes deterministic failure-injection tests based on Memory sequence exhaustion; no production-only fault-injection API was added.

### 6.1 Goal completion — explicitly partial transition

- assimilate_goal_outcome writes a goal_progress event and then a separate goal_complete event.
- The replay handler deliberately does not apply progress=1.0 from goal_progress; the explicit goal_complete event is the status commit.
- If the second append fails, the API returns false. The progress evidence event remains in the journal, but the goal remains at its pre-completion progress/status.
- The regression test forces the first append to sequence UINT64_MAX-1 and the second append to UINT64_MAX, which is rejected. It verifies the in-memory goal state and restart replay both remain pre-completion.

Contract: this operation is not atomic. It is explicitly partial on second-append failure. Callers must honor false and inspect/reconcile the goal state before retry; automatic retry/idempotency is not claimed.

### 6.2 Evolution canary rollback — durable observation before rollback commit

- The canary observation event is appended before the controller evaluates the canary.
- A rollback event must then be appended before the adopted parameter is rolled back.
- If the rollback-event append fails, observe_evolution_canary returns rollback_not_persisted; the parameter remains adopted. The durable canary observations reconstruct the same canary state on restart, without an invented rollback.
- The regression test places the journal cursor at UINT64_MAX-1, allows the final observation event to persist, and forces the rollback event append to fail. It checks parameter state and replay. It also verifies manual rollback append failure leaves the parameter unchanged.

Contract: canary evidence is durable; parameter rollback is not applied until its rollback event is durable. A failed rollback append leaves the parameter adopted and the canary evidence replayable. Re-evaluation occurs on a later observation after journal recovery; automatic retry is not claimed.

### 6.3 Crash after durable rollback event — replay recovery and idempotency

A second evolution test simulates the crash window after an evolution_rollback event is durably appended but before the in-memory controller applies it. On restart, replay applies the rollback to the adopted parameter. A second restart verifies the rollback is not applied twice and only one RolledBack history record exists.

### 6.4 Remaining failure boundary

The tests cover:
- goal completion's second journal append failure;
- canary rollback's second journal append failure;
- manual rollback's first journal append failure;
- crash/restart after a durable rollback event;
- idempotent replay of the rollback event.

They do not inject failures inside every compensating operation of EvolutionController rollback, such as a failure while restoring adoption-journal/history state. That deeper controller-internal compensation boundary remains a residual verification item. Do not describe all evolution rollback failure modes as fully proven.

A follow-up direct test intended to inject EvolutionHistory::append failure during rollback compensation was committed to the branch ref as a37add18babf8afc2e9c12ca0449a2ee84ecd60d. However, the live PR #176 metadata and its Actions runs still report head 4cf017e073da980c9f77d739fde6f92ef1a2fbc1, and the PR commit list does not include a37add18. This test is therefore **not part of the verified PR snapshot and is not counted as evidence**. The branch-ref/PR-head synchronization discrepancy must be resolved before relying on it.

**Failure-ordering workstream: PARTIALLY CLOSED.** The principal journal commit and replay boundaries are defined and tested; internal compensation failure injection remains open.

## 7. CI evidence for the correction branch

At branch head 4cf017e073da980c9f77d739fde6f92ef1a2fbc1, all four GitHub Actions checks completed successfully:

- Brain CI: https://github.com/methaneex-oss/MethaneX/actions/runs/41808525499
- Native Brain Build: https://github.com/methaneex-oss/MethaneX/actions/runs/41808525486
- Brain ThreadSanitizer: https://github.com/methaneex-oss/MethaneX/actions/runs/41808525492
- JARVIS Brain Tests: https://github.com/methaneex-oss/MethaneX/actions/runs/41808525557

Native, ASan/UBSan and ThreadSanitizer CTest runs each report 73/73 tests passed. ThreadSanitizer build/test passed. The goal and evolution failure-injection and crash-window replay tests execute within jarvis_goals_architecture_suite and jarvis_evolution_brain_integration_suite; both suites passed at this exact head.

These are candidate-donor branch results. They do not establish ABI compatibility, integrated Brain capability acceptance, the five long-running workflow contracts, or approval of PR #156 as the baseline.

## 8. Independent re-check — outstanding external dependency

Report 14 is a technical review document, not a submitted GitHub review. The commit that added Report 14 was authored/committed under methaneex-oss, the repository owner account. PR #175's submitted review list was empty at the latest check. No separate reviewer username was supplied, and no CODEOWNERS file was found in the checked locations.

A new independent re-check cannot be truthfully claimed by the same Builder that produced this evidence. To complete item 6, the Project Director must provide the GitHub username of the independent reviewer (or arrange for that reviewer to inspect Report 16 and submit the review). Once supplied, a formal review request can be sent through GitHub.

**Independent re-check: OPEN — reviewer identity required.**

## 9. Final Gate A status and authority boundary

| Workstream | Status |
|---|---|
| Risk-based provenance | CLOSED for baseline recommendation |
| Static API declarations/call sites | CLOSED within core/cpp; external ABI remains a later gate |
| Five workflow preservation specifications | CLOSED as specification; adaptation/execution later |
| D1/D2 remediation | Implemented and CI-verified on draft PR #176; not yet merged into PR #156 |
| Goal/evolution failure consistency | Partially closed; internal compensation failure injection remains open |
| Independent re-check | OPEN; reviewer identity required |

**Gate A: NOT CLEARED.**

Baseline strategy remains: accepted PR #174 as integration starting point; PR #156 as selective source donor only. The Project Director has not selected a baseline. PR #176 is draft and unmerged. No runtime changes were made on PR #175. No merge, rebase, cherry-pick, deployment or baseline approval is claimed by this report.
