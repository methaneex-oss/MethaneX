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
- Candidate has seven candidate-only unique APIs listed in §3.
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
- [ ] Classify all seven candidate-only APIs by visibility, callers, lifecycle and ownership.
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
