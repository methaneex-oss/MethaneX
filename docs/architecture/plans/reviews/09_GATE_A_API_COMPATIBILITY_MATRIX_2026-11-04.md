# Gate A — API Declaration and Caller Compatibility Matrix

**Date:** 2026-11-04  
**Candidate source:** `brain_restored_api.cpp` blob `00d69ab2eb3811d453a643ef18dc69741109cbc8`  
**Comparison source:** current-main `brain_restored_api.cpp` blob `618deb6976eed951eae02b7f0da741e6d730bb0c`  
**Header blobs:** candidate `brain.hpp` `ca718aa4603bbdd0abc7de26ed296bcf8c6562fe`; current main `brain.hpp` `8268ef84e0b361ead536724ba7761904b30ee58f`  
**Status:** Static body reconciliation recorded; caller/signature compatibility inventory still requires completion

## 1. Inventory facts

- Current main: 69 `Brain::` definition occurrences across 64 unique method names.
- Candidate: 77 definition occurrences across 71 unique method names.
- All 64 current-main unique method names occur in candidate.
- The seven-item list in §3 was preliminary and is superseded by the full public-header inventory in §7.2 (26 candidate-only public method names).
- 24 common-name body differences were classified in the semantic addendum and are reproduced below.
- These counts do not establish overload-level or ABI compatibility.

## 2. Common-name body differences

| Function | Candidate-side behavior | Static disposition | Compatibility/verification action |
|---|---|---|---|
| `abandon_goal` | Candidate validates existence/terminal status; journal then replay | Prefer candidate event-first behavior | Check caller/result compatibility; failure-injection coverage |
| `activate_goal` | Validates state and completed prerequisites before journal/replay | Prefer candidate validation | Check all callers and prerequisite-state assumptions |
| `adopt_evolution` | Legacy proposal-only adoption fails closed | Prefer candidate safety gate | Verify callers handle rejection of legacy path |
| `adopt_evolution_experiment` | Validates evidence; Brain-specific controller adoption and compensation | Candidate stronger evidence lineage | Review controller/journal failure ordering |
| `append_goal_event` | Removes main's no-op timestamp self-assignment | No meaningful semantic difference | No special action |
| `assimilate_goal_outcome` | Terminal checks; event-first progress then completion | Candidate safer against pre-journal mutation | Multi-event partial failure/idempotency unresolved |
| `choose` | Adds learned-strategy adjustment | Candidate capability useful but context defect confirmed | Must use selected active intent identity; callers otherwise remain |
| `choose_with_affect` | Same learned strategy plus affective modulation | Same context defect | Same correction; test distinct active/pending goals later |
| `complete_goal` | Prevalidates and journals/replays before mutation | Prefer candidate event-first behavior | Check caller expectations and persistence failure |
| `create_goal` | Duplicate guard and journal/replay; non-finite values not rejected before append | Candidate partly stronger; D2 confirmed | Reject all non-finite numeric inputs before event creation |
| `isolate` | Event-first isolation transition | Prefer candidate | Failure-injection/replay verification later |
| `isolate_capability` | Checks capability and event-first transition | Prefer candidate | Caller compatibility and replay verification |
| `observe_capability` | Journal/replay centered observation | Prefer candidate | Verify source attribution/replay later |
| `observe_evolution_canary` | Preview/validate evidence and journal canary/rollback | Candidate stronger evidence lineage | Rollback/restart/replay ordering unresolved |
| `observe_evolution_fitness` | Event-first journal/replay | Prefer candidate | Failure-injection/replay verification later |
| `predict` | Finite validation and learned calibration | Candidate stronger; calibration needs evidence | Regression/calibration behavior unverified |
| `recover` | Finite/existence checks and event-first recovery | Prefer candidate | Replay and failed-persistence ordering unresolved |
| `reflect` | Adds affective calibration evidence | Candidate richer input; semantics not independently validated | Verify ownership/meaning and call compatibility |
| `register_evolution_parameter` | Candidate finite/duplicate checks, bool return, replay; main void | Candidate safer but signature changed | Audit declarations, direct callers, callbacks, function/member pointers, ABI |
| `resolve_prediction` | Delegates to explicit feedback resolver | Candidate centralizes validation | Check all callers interpret bool as resolved status |
| `restore_capability` | Checks capability; event-first journal/replay | Prefer candidate | Caller compatibility and replay verification |
| `rollback_evolution` | Binds rollback to adopted experiment and evidence | Candidate stronger lineage | Controller/journal/restart failure ordering unresolved |
| `set_goal_priority` | Finite/existence checks and event-first | Prefer candidate | Caller/result semantics and replay |
| `update_goal_progress` | Finite/terminal checks and event-first | Prefer candidate | Caller/result semantics and replay |

## 3. Candidate-only APIs

| API | Static purpose recorded in addendum | Required compatibility assessment |
|---|---|---|
| `developmental_best_related_strategy` | Related-strategy retrieval | Declaration, callers, visibility, return/lifetime semantics, test use |
| `developmental_feature_strategy_estimate` | Feature-based strategy estimate | Declaration, callers, feature input contract, learning/update side effects |
| `developmental_related_strategies` | Related-strategy retrieval | Declaration, callers, result ordering/ownership, test use |
| `import_legacy_memory_event` | Restricted passive legacy import | Callers, trust boundary, replay semantics, exclusion from trusted learning |
| `record_evolution_evaluation` | Evidence-bound evolution evaluation | Callers, evidence validation, lifecycle, persistence/replay |
| `record_knowledge_source_feedback` | Source-bound knowledge feedback | Callers, source identity/provenance, feedback validation, persistence |
| `resolve_prediction_feedback` | Explicit prediction-feedback status | Callers, bool/status semantics, prediction lifecycle |

The addendum establishes these as candidate-only APIs by name, not whether they are public, internal, reachable, or compatibility-sensitive. Those classifications remain to be completed from declarations and call sites.

## 4. Signature-sensitive item: `register_evolution_parameter()`

Candidate returns `bool`; current-main restoration returns `void`. The candidate adds finite-value and duplicate-registration validation and journals/replays registration.

A call expression that ignores the return may remain source-usable, but that is not a complete compatibility assessment. The following remain to be inventoried:
- all declarations and overloads;
- direct call sites and wrappers;
- function pointers/member pointers, callback registrations, templates, or type-erased call boundaries;
- downstream consumers that may depend on the return contract;
- ABI-sensitive boundaries, if any.

No ABI/build compatibility claim is made without authorized compile/link evidence.

## 5. Required completion checklist

- [ ] Reconcile every candidate/current-main declaration pair, including overloads.
- [ ] Inventory direct and indirect call sites for all 24 changed functions.
- [ ] Audit all call sites and type references for `register_evolution_parameter()`.
- [x] Complete the static public declaration/overload/call-site inventory for the candidate public Brain API; external ABI/downstream compatibility remains a later compile/link gate.
- [ ] Identify removed, renamed or changed signatures beyond the 24 body differences.
- [ ] Record unresolved build/ABI questions for a later authorized verification gate.

**Disposition:** Body-level semantic reconciliation is useful but does not prove caller/API compatibility. Gate A remains NOT CLEARED pending completion of the declaration/caller inventory and independent review.


## 6. Targeted declaration and caller inspection — 2026-11-04

The following checks were performed against the exact candidate code-bearing parent
`15d49e5fdeb5723c475922ab78fb92f97c4b3b84` and current `main`.

### 6.1 Re-fetched declaration and implementation evidence

| Item | Candidate evidence | Current-main evidence | Finding |
|---|---|---|---|
| `brain.hpp` | blob `ca718aa4603bbdd0abc7de26ed296bcf8c6562fe` | blob `8268ef84e0b361ead536724ba7761904b30ee58f` | Candidate exposes additional feedback, developmental-strategy, evolution-evaluation, and legacy-import interfaces; the candidate-only list is not merely inferred from implementation symbols. |
| `brain_restored_api.cpp` | blob `00d69ab2eb3811d453a643ef18dc69741109cbc8` | blob `618deb6976eed951eae02b7f0da741e6d730bb0c` | Candidate definitions were re-fetched and the seven candidate-only API names were confirmed in the implementation. |
| `register_evolution_parameter` | Header declares `bool`; candidate implementation/test contract uses a result | Header and implementation declare/define `void` | This is a real source-level signature change, not only a body difference. |

### 6.2 Candidate-only API call-site evidence

The following candidate test files were fetched directly from the pinned candidate parent:

| API | Candidate test evidence | Interpretation |
|---|---|---|
| `record_knowledge_source_feedback` | `knowledge_source_feedback_suite.cpp`, blob `66a855dfe2aec24cdc173a1cedafbdbefeb811c3`; 18 textual occurrences | The API is exercised by a dedicated test suite, including positive and negative assertions and restored-instance cases. This is static test-source evidence, not a test-pass claim. |
| `resolve_prediction_feedback` | `prediction_feedback_phase10_suite.cpp`, blob `973350623e52bd9609ebaf1e01082ee52aeb480b`; four occurrences | The sequence-based overload is exercised in the fetched suite. The key-based overload's complete caller inventory remains open. |
| `import_legacy_memory_event` | `evolution_brain_integration_suite.cpp`, blob `d9dc62b1c6aebdb4ab38f3d64150699d96f393c4`; two occurrences. `developmental_brain_integration_suite.cpp`, blob `e6eba3db6df8da9ecfed21974936908a32ea11c5`; ten occurrences | The import API is used in candidate integration-test source. Its trust boundary and replay behavior still require semantic review; call-site presence alone does not establish safety. |
| `record_evolution_evaluation` | `evolution_brain_integration_suite.cpp`, blob `d9dc62b1c6aebdb4ab38f3d64150699d96f393c4`; eleven occurrences | The API has candidate integration-test coverage in source, including accepted and rejected evaluation paths. No execution/pass claim is made. |
| `developmental_best_related_strategy` | No occurrence in the seven targeted candidate test files inspected for this checkpoint | No caller was found in this bounded sample. This is not proof that the API is unreachable or unused across the entire candidate tree. |
| `developmental_related_strategies` | No occurrence in the seven targeted candidate test files inspected for this checkpoint | Same limitation: repository-wide candidate call-site inventory remains open. |
| `developmental_feature_strategy_estimate` | No occurrence in the seven targeted candidate test files inspected for this checkpoint | Same limitation: repository-wide candidate call-site inventory remains open. |

The seven targeted test files were: `knowledge_source_feedback_suite.cpp`,
`prediction_feedback_phase10_suite.cpp`, `evolution_brain_integration_suite.cpp`,
`developmental_brain_integration_suite.cpp`, `developmental_learning_suite.cpp`,
`judgment_intent_strategy_phase6_suite.cpp`, and
`developmental_training_environment_suite.cpp`. The candidate test CMake file
(blob `0251936730f82a7a8c928fa31dfe1d7effc83d91`) contains 73 C++ source entries.
Only the named subset was inspected for these API call-site counts.

### 6.3 Return-type compatibility evidence

Current-main code search returned four direct caller locations for
`register_evolution_parameter`: `brain_contract.cpp`,
`evolution_brain_integration_suite.cpp`, `brain_10_suite.cpp`, and
`brain_deep_suite.cpp`. The returned call expressions are statement-form calls
that ignore the `void` result. The candidate's evolution integration test uses
boolean assertions against the candidate return value.

This establishes that the inspected current-main direct callers do not consume a
return value. It does **not** establish complete compatibility: indirect uses,
function/member pointers, downstream consumers, and ABI-sensitive boundaries
have not been exhaustively enumerated. A call expression that discards a bool
can remain source-usable, but the changed function type can still affect typed
references and binary interfaces.

### 6.4 Remaining API closure work

- The complete candidate-tree caller inventory for the three developmental
  strategy accessors is still open.
- The complete declaration/overload/caller inventory for all 24 body-different
  methods is still open.
- Function-pointer/member-pointer, callback, template, and type-erased uses have
  not been exhaustively ruled out.
- No compilation, linking, ABI inspection, or runtime tests were performed or
  authorized.

**Updated disposition:** This checkpoint adds direct candidate test-source
evidence for four candidate-only APIs and bounded no-hit evidence for three
accessors. It narrows, but does not close, the compatibility workstream.
Gate A remains NOT CLEARED.


## 7. Corrected public declaration and full C++ call-site inventory — 2026-11-04

The earlier statement that the candidate had seven candidate-only APIs is superseded. A direct public-header comparison found a broader public surface. This section is authoritative for the declaration-level comparison.

### 7.1 Exact header/build evidence

| Item | Current main | Candidate code-bearing parent |
|---|---|---|
| Brain header | core/cpp/include/jarvis/core/brain.hpp, blob 8268ef84e0b361ead536724ba7761904b30ee58f | same path, blob ca718aa4603bbdd0abc7de26ed296bcf8c6562fe |
| CMake source list | core/cpp/CMakeLists.txt, blob c51816888e1bddb7bc00c59e72529524e27a0717 | same path, blob bc264ce7b4ae489404ca03ea6d9676d0330a6a56 |
| Brain restored API source | brain_restored_api.cpp exists, blob 618deb6976eed951eae02b7f0da741e6d730bb0c | brain_restored_api.cpp, blob 00d69ab2eb3811d453a643ef18dc69741109cbc8 |
| CMake registration | Does not compile brain_restored_api.cpp | Compiles brain_restored_api.cpp and the new Brain API/support translation units |

This distinction matters: some functions found in current-main brain_restored_api.cpp are orphan source definitions, not part of the current-main compiled public Brain API. A source-body match in that file must not be described as compiled API compatibility.

### 7.2 Candidate-only public Brain method names

The candidate header declares the following 26 public method names that are absent from the current-main public Brain header:

1. record_knowledge_source_feedback
2. learn_from_prediction
3. predict_with_context
4. resolve_prediction_feedback
5. assimilate_goal_outcome
6. contextual_associations
7. concept_candidates
8. contextual_concepts
9. generalized_concepts
10. choose_with_affect
11. choose_with_developmental_learning
12. plan_with_affect
13. knowledge_assessment
14. developmental_associations
15. developmental_strategies
16. developmental_best_strategy
17. developmental_best_related_strategy
18. developmental_related_strategies
19. developmental_feature_strategy_estimate
20. attention_policy
21. affective_state
22. affective_appraisal
23. affective_calibration
24. affective_learning_updates
25. record_evolution_evaluation
26. import_legacy_memory_event

Additional overloads/signature changes:
- resolve_prediction adds a sequence-based overload alongside the existing key-based overload;
- resolve_prediction_feedback has key-based and sequence-based overloads;
- choose_with_developmental_learning has two overloads;
- Brain constructor adds trusted-knowledge evaluator and feedback/provenance verifier parameters (with defaults);
- execute_action adds an observe_consequence callback before the authorization argument; this changes the positional function type and can break callers that pass authorization as the fifth argument;
- register_evolution_parameter changes return type from void on current main to bool in the candidate;
- several methods previously defined inline in the current-main header are out-of-line in the candidate, so source-call compatibility does not establish ABI compatibility.

### 7.3 Candidate-only API call-site inventory

A repository-wide exact-identifier scan of every .cpp and .hpp under core/cpp was executed on candidate-derived branch head b9cde00f63904505b1d56f9101b9895a07d6cb8d. The temporary scan workflow was removed after the run. The successful GitHub Actions log is run 41806123218. The earlier 24-method scan is run 41805564990.

The full file/count output is in those run logs. The following condensed index identifies the principal declaration/definition/test call sites:

| Candidate-only API | Principal definitions and callers found |
|---|---|
| record_knowledge_source_feedback | brain_restored_api.cpp; knowledge_source_feedback_suite.cpp |
| learn_from_prediction | brain.cpp; association_causality_phase5_suite.cpp; evolution_brain_integration_suite.cpp; learning_adaptation_phase8_suite.cpp; memory_learning_evolution_persistence_suite.cpp; prediction_feedback_phase10_suite.cpp |
| predict_with_context | brain_prediction_context.cpp; association_causality_phase5_suite.cpp; prediction_feedback_phase10_suite.cpp |
| resolve_prediction_feedback | brain.cpp; brain_action_execution.cpp; brain_restored_api.cpp; cognitive_cycle.cpp; affective_evidence_suite.cpp; cognitive_cycle_suite.cpp; prediction_feedback_phase10_suite.cpp |
| assimilate_goal_outcome | brain_restored_api.cpp; cognitive_cycle.cpp; cognitive_cycle_suite.cpp; goal_directed_cognition_suite.cpp |
| contextual_associations | brain_restored_api.cpp; association_causality_phase5_suite.cpp |
| concept_candidates | association_model.hpp/.cpp; brain_prediction_context.cpp; brain_restored_api.cpp; association_causality_phase5_suite.cpp |
| contextual_concepts | brain_restored_api.cpp; association_causality_phase5_suite.cpp |
| generalized_concepts | association_model.hpp/.cpp; brain_prediction_context.cpp; brain_restored_api.cpp; prediction_feedback_phase10_suite.cpp |
| choose_with_affect | brain_restored_api.cpp; affective_brain_decision_suite.cpp; affective_decision_learning_suite.cpp; affective_evidence_suite.cpp; brain_deep_suite.cpp; developmental_brain_integration_suite.cpp |
| choose_with_developmental_learning | brain_affective_planning.cpp; developmental_brain_integration_suite.cpp; memory_learning_evolution_persistence_suite.cpp |
| plan_with_affect | brain_affective_planning.cpp; affective_planning_suite.cpp |
| knowledge_assessment | developmental_brain_integration_suite.cpp; knowledge_source_feedback_suite.cpp |
| developmental_associations | brain_restored_api.cpp; cognitive_runtime_suite.cpp; developmental_brain_integration_suite.cpp; prediction_feedback_phase10_suite.cpp |
| developmental_strategies | brain_restored_api.cpp; cognitive_cycle.cpp; developmental_world.cpp; action_execution_phase7_suite.cpp; brain_action_consequence_integration_suite.cpp; brain_deep_suite.cpp; developmental_brain_integration_suite.cpp; developmental_training_environment_suite.cpp; developmental_world_integration_suite.cpp; DLT-001/002/003 suites; evolution and memory-persistence suites; prediction_feedback_phase10_suite.cpp |
| developmental_best_strategy | brain_restored_api.cpp; action_execution_phase7_suite.cpp; brain_action_consequence_integration_suite.cpp; brain_deep_suite.cpp; cognitive_runtime_learning_integration_suite.cpp; developmental Brain/training/world suites; DLT-001 trial; prediction_feedback_phase10_suite.cpp |
| developmental_best_related_strategy | brain_restored_api.cpp; brain_deep_suite.cpp |
| developmental_related_strategies | brain_restored_api.cpp; cognitive_cycle.cpp; brain_deep_suite.cpp; DLT-002 long-run suite |
| developmental_feature_strategy_estimate | brain_restored_api.cpp; cognitive_cycle.cpp; DLT-004 suite |
| attention_policy | brain_restored_api.cpp; affective_decision_learning_suite.cpp; attention_learning_brain_suite.cpp; brain_action_consequence_integration_suite.cpp; brain_deep_suite.cpp; prediction_feedback_phase10_suite.cpp |
| affective_state | affective_learning.hpp; brain.hpp; cognitive_cycle.hpp; cognitive_workspace.hpp; affective_state.cpp; brain_restored_api.cpp; cognitive_cycle.cpp; cognitive_runtime.cpp; affective decision/planning/evidence suites |
| affective_appraisal | brain.hpp; cognitive_cycle.hpp; cognitive_workspace.hpp; brain_restored_api.cpp; cognitive_cycle.cpp; cognitive_runtime.cpp; action-execution, affective-decision/evidence and DLT-002 persistence suites |
| affective_calibration | brain.hpp; affective_decision_learning_suite.cpp; brain_deep_suite.cpp; DLT-002 persistence suite |
| affective_learning_updates | brain.hpp; brain_restored_api.cpp; action-execution, affective-decision, affective-goal, Brain-action-consequence, Brain-deep, cognitive-runtime-learning, developmental-brain, DLT-002 and DLT-004 suites |
| record_evolution_evaluation | brain_restored_api.cpp; evolution_brain_integration_suite.cpp; memory_learning_evolution_persistence_suite.cpp |
| import_legacy_memory_event | brain_restored_api.cpp; developmental_brain_integration_suite.cpp; evolution_brain_integration_suite.cpp |

The scan also covered all 24 previously identified common-name/body-difference identifiers. It confirms repository call sites by exact identifier, but does not discover external downstream consumers that are not in this repository.

### 7.4 Signature-sensitive call sites

- register_evolution_parameter occurs in brain_restored_api.cpp, brain_10_suite.cpp, brain_contract_suite.cpp, evolution_brain_integration_suite.cpp, learning_adaptation_phase8_suite.cpp and memory_learning_evolution_persistence_suite.cpp. Direct call sites that ignore the bool remain source-call compatible; function/member-pointer and ABI compatibility are not proven.
- execute_action occurs in brain_action_execution.cpp, cognitive_runtime.cpp, action-execution, affective-decision, Brain-action-consequence, Brain-deep, cognitive-cycle, developmental-brain, DLT-002/003/004 and memory-persistence suites. The new observe_consequence positional parameter must be reviewed for any external caller that supplies ActionAuthorizationContext positionally.
- resolve_prediction(sequence) occurs in cognitive_cycle.hpp, brain.cpp, brain_restored_api.cpp, cognitive_cycle.cpp and the attention-learning, Brain-10, Brain-contract, Brain-deep, developmental-brain and prediction-feedback suites.

### 7.5 API disposition

The static declaration/overload/call-site inventory within core/cpp is now complete at the candidate tree snapshot. The previous seven-API count and the prior source-only 24-body comparison are not sufficient descriptions of the public API delta and are superseded by this section.

Candidate donor compilation/linkage is separately verified by the PR #176 CI runs on the corrected donor branch. This does not prove ABI compatibility with external consumers, function-pointer compatibility, or downstream binaries. A clean full integration build/link and external-consumer recompile remain mandatory before any affected port is accepted.

**Disposition:** static API inventory CLOSED within the repository; external ABI/downstream compatibility remains an explicit later verification gate. Gate A remains NOT CLEARED until the other closure obligations and independent re-check are complete.
