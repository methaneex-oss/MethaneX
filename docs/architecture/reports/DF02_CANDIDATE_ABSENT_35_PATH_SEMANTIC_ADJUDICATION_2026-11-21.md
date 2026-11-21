# DF-02 — Candidate-absent 35-path semantic adjudication

**Date:** 2026-11-21  
**Candidate branch tip:** `84dd10094cac675b97b1ab2d45b36618d61efe38`  
**Candidate source baseline:** `61311fe5b44c81c4409c8ba8dc581a83bdd5dd2c`  
**Donor baseline:** PR #97 HEAD `c1da222e6c94aeb3f2ad000392c21fe4fc81ab25`

## 1. Result

The exact candidate-branch consumer matrix identified 35 of the 111 candidate-branch lexical donor paths whose same-path candidate artifact is absent. This report inspects the matched identifiers and their exact candidate consumer lines so that generic token hits are not mistaken for an implementation successor.

The 35 paths divide into:
- 10 source/example artifacts;
- 17 test artifacts;
- six historical plan/spec documents;
- two engineering task-ledger artifacts (source and test).

The key result is that most of the candidate-branch lexical hits are incidental words or helper names. The few API-like matches are either confined to the uncompiled `brain_restored_api.cpp`, generic functions such as `observe`/`restore`/`clamp_unit`, or a narrower inline Brain wrapper. The donor task-ledger source is a genuine alternate-branch implementation, not a candidate implementation.

## 2. Missing source/example artifacts

| Path | Donor blob | Candidate-branch hit | Semantic disposition |
|---|---|---|---|
| `core/cpp/examples/developmental_world.cpp` | `d865c8d66c4529be78c3d7c2cd1a0ed4eb10d3e6` | `make_input` in unrelated `cognitive_runtime_suite.cpp` and `cognitive_trigger_suite.cpp` | No example successor. The helper builds ordinary cognitive-cycle inputs; it is not a developmental world/example. |
| `core/cpp/include/jarvis/core/affective_learning.hpp` | `fa06043dc481336ba544247f365d37f5476a0651` | `AffectiveAppraisal` appears in `brain_restored_api.cpp`; `clamp_unit` appears in `evolution_opportunity.cpp` | The only typed API reference is in uncompiled `brain_restored_api.cpp`. The compiled `clamp_unit` calls are generic finite-value clamps, not affective learning. No compiled affective-learning successor. |
| `core/cpp/include/jarvis/core/affective_state.hpp` | `f63da2e0060938864bf434012d0b3b4d74fa5f29` | `AffectiveState` appears in `brain_restored_api.cpp`; `restore` appears in self-model/Brain code | Typed state reference is confined to the uncompiled orphan API. Other hits are generic persistence/recovery methods. No compiled affective-state owner. |
| `core/cpp/include/jarvis/core/causal_link_codec.hpp` | `a6286281e4b22564a39e02a7e38a778bb81042f0` | `constexpr` in causal-model/memory code and tests | `constexpr` is a language keyword, not a codec consumer. Candidate uses the separate untyped key=value parser documented in the causal-feedback report. |
| `core/cpp/include/jarvis/core/cognitive_goal_outcome.hpp` | `c986480d82b9951177031f3387169819c3856234` | `GoalOutcomeEvidence` in `brain_restored_api.cpp`; `normalize`/`observe` elsewhere | Typed evidence reference is in uncompiled orphan code; other hits are generic method names. No compiled goal-outcome evidence model. |
| `core/cpp/include/jarvis/core/developmental_environment.hpp` | `913c8cca2a03499249b834a890812c57b9aa4b1a` | `observe` across unrelated cognitive/world-model source and tests | Generic event/observation methods do not implement a developmental training environment. No candidate environment type or owner. |
| `core/cpp/include/jarvis/core/developmental_learning.hpp` | `e3b9bf8af265b67829fd7deb323d88a3a9dd4b75` | `LearnedAssociation`/`LearnedStrategy` in `brain_restored_api.cpp`; generic association/strategy terms elsewhere | The typed learner API is only referenced by uncompiled orphan code. Compiled matches are unrelated capability/association/strategy code; no candidate developmental learner. |
| `core/cpp/include/jarvis/core/developmental_world.hpp` | `2ba5bdbfc6db1f24eff8eb0a20ee145d0efc16cf` | `episode`/`observe` in unrelated world/cognitive code | Generic episode and observation vocabulary is not a developmental-world implementation. |
| `core/cpp/src/brain_action_execution.cpp` | `3b66bafb438cd28790e6f25611b96c86f1eff05c` | `execute_action` in candidate `brain.hpp` and phase-7 test | A partial inline Brain wrapper exists, so the donor translation unit is not wholly capability-absent. The wrapper lacks the donor consequence-observer/result feedback contract; the action-feedback report records that gap. |
| `core/cpp/src/developmental_learning.cpp` | `dbf5f43271dfa0a3c57236e2faa82eb88d15490d` | Typed strategy/association API only in uncompiled orphan API; generic words in compiled files | No compiled candidate implementation of the donor developmental-learning source. |

## 3. Missing test artifacts: lexical matches are unrelated helper names

All 17 donor test files below are absent at the candidate branch tip. Their candidate-branch lexical hits do not identify a same-purpose test or preserve the donor test contract.

| Missing donor test path | Donor blob | Candidate hit and exact semantic disposition |
|---|---|---|
| `core/cpp/tests/affective_brain_decision_suite.cpp` | `9ff9c0480fa34fa4f5600e514af419b2bbc79765` | `restored` is the local variable in the generic Brain persistence contract test; no affective decision assertion. |
| `core/cpp/tests/affective_decision_learning_suite.cpp` | `920ddcbc8a422783bb8724093afd952cc885e6b6` | `replayed` is a generic replay identifier in candidate Brain code; no affective decision-learning test. |
| `core/cpp/tests/affective_evidence_suite.cpp` | `c8a401cab1a29d57506f990043a1f82536fd9029` | `restored` persistence variable in generic Brain contract tests; no affective evidence coverage. |
| `core/cpp/tests/affective_goal_outcome_suite.cpp` | `06d72304fa0c4ea67eb4a27b91c484007f231199` | `restored` persistence variable in generic Brain contract tests; no affective goal-outcome coverage. |
| `core/cpp/tests/attention_learning_brain_suite.cpp` | `1fa972d9ecffdae8dce49b17356f6f4dc274d1a3` | `restored` persistence variable in generic Brain contract tests; no attention-learning integration coverage. |
| `core/cpp/tests/brain_action_consequence_integration_suite.cpp` | `7616082579d53e3579cae8e87895bdb3dadba66f` | `restored` persistence variable in generic Brain contract tests; no consequence-to-learning integration coverage. |
| `core/cpp/tests/cognitive_runtime_goal_feedback_suite.cpp` | `15a6bdffe37ae7df6c625ea9737fda4c0bf08a7f` | `restored` persistence variable in generic Brain contract tests; no runtime goal-feedback test. |
| `core/cpp/tests/cognitive_runtime_learning_integration_suite.cpp` | `656de56b1368e40afb090778a7a5504ab4208056` | `make_input` is a helper in the existing runtime/trigger tests; it is not the missing learning-integration suite. |
| `core/cpp/tests/developmental_brain_integration_suite.cpp` | `760162dd6d1e669162e0bf22223a437491f5e262` | `baseline`, `isolated`, `restored`, `values` occur in unrelated evolution tests and generic state checks; no developmental Brain integration suite. |
| `core/cpp/tests/developmental_training_environment_suite.cpp` | `62a0ee4f8ec966e48a45848217ba7a6d6e96196f` | `restored` persistence variable in generic Brain contract tests; no developmental training environment coverage. |
| `core/cpp/tests/developmental_world_integration_suite.cpp` | `4290fcfde741f1be9a4a69adc70699ade6fe7922` | `make_input` helper in unrelated runtime/trigger tests; no developmental world integration coverage. |
| `core/cpp/tests/dlt_001_long_run.cpp` | `896caa7e4d14ce6e4f12e453181a14bbb74c62fd` | `checkpoints`, `episodes`, `report` appear in self-testing/runtime helpers; not a DLT-001 trial or long-run test. |
| `core/cpp/tests/dlt_001_trial.cpp` | `deca50aec499a04d46cbc7aed429e335fff18f72` | `experience` occurs in ordinary prediction-learning tests; `make_input` is a runtime helper. No DLT-001 environment/trial test. |
| `core/cpp/tests/dlt_002_long_run.cpp` | `cbd80951c2f331fa4893c1805fff45a4035d5d24` | `checkpoints`, `episodes`, `report` are generic self-testing/runtime identifiers; no DLT-002 long-run test. |
| `core/cpp/tests/dlt_002_persistence.cpp` | `d818a75cff936bffc8a383e032302f51ac8a1034` | `make_input` and `restored` are unrelated runtime/persistence helpers; no DLT-002 training/persistence verification suite. |
| `core/cpp/tests/goal_directed_cognition_suite.cpp` | `7fe6cf6c4dd2dc2a54bb9f48fcdd3c3d91d7c282` | `restarted` is the local Brain variable in an unrelated memory recovery test; no goal-directed cognition suite. |
| `core/cpp/tests/memory_learning_evolution_persistence_suite.cpp` | `98e6598f60912714234f2dfabfbe52fa5eb77044` | `restored` is the generic Brain persistence variable; no integrated memory-learning-evolution persistence suite. |

These findings are not a claim that all candidate testing is absent. The candidate retains other registered suites, but those suites do not cover the donor-specific scenarios above. The focused reports provide the exact assertion reductions for the relevant retained suites.

## 4. Missing historical plan/spec documents

The six donor documents below are absent from the candidate branch snapshot. Their lexical matches occur in code/tests and do not establish that the documents themselves were consumed, superseded, or formally retired.

| Historical artifact | Donor blob | Candidate hit and disposition |
|---|---|---|
| `docs/superpowers/plans/2026-09-25-cognitive-action-feedback-loop.md` | `a2f4bfc8dfba5a7bf8973f94c68c1978ac66969b` | `process_outcome` is a real candidate cognitive-cycle API, but it does not prove this historical plan is preserved or retired. |
| `docs/superpowers/plans/2026-09-26-concept-context-prediction.md` | `7f06d469820cf2fb973485bbf76237c602b59c60` | `concept_candidates`/ `existing` are candidate source terms, not document-preservation evidence. |
| `docs/superpowers/plans/2026-09-30-developmental-cognition.md` | `17abc6fb32a79571ada116d44ed4aa63b4092ee7` | `journal` references in Brain code/tests are not a successor record for this plan. |
| `docs/superpowers/plans/2026-10-01-affective-state.md` | `339fe43d9332bab8ff2d21165b6be5cf7c9a6f81` | `affective_state` in uncompiled orphan API is not document preservation or accepted design authority. |
| `docs/superpowers/specs/2026-09-25-cognitive-action-feedback-loop-design.md` | `6b601d18898422143978bfdea3a971cfdc794cfd` | `process_outcome` in candidate cycle source/tests does not establish preservation of this specification. |
| `docs/superpowers/specs/2026-10-01-affective-state.md` | `89f0d76f48284a817789bff50affe277136fb6f7` | `neutral` is an incidental token in attention/tests; no evidence of document preservation or formal retirement. |

**Authority boundary:** absence from this candidate branch is not authorization to delete, retire, or declare non-adopted any historical design artifact. The preservation/authority register remains the controlling disposition record.

## 5. Engineering task-ledger artifacts

| Path | Donor blob | Candidate-branch hit | Semantic disposition |
|---|---|---|---|
| `engineering/cpp/src/task_ledger.cpp` | `7acff8990319392c9984035a4a14cc83f7154072` | generic `complete`, `contents`, `number`, `output`, `valid_task` across unrelated Brain/capability/goal files | No candidate TaskLedger API or source owner. The donor implementation is separately verified as compiled/tested on alternate branch `ci/priority-one-validation-20261031`; see the engineering-agent gap report. |
| `engineering/cpp/tests/task_ledger_suite.cpp` | `e90c062261c95ff99d4b1bdcb55ce7bfad0512ec` | generic `coordinator`, `recovered`, `restored` in unrelated Brain/agent tests | No candidate task-ledger suite. The donor-only suite contains 43 assertions and is registered only in the alternate donor build line. |

## 6. Closure impact

This resolves the **35 candidate-absent same-path lexical cases** individually. It distinguishes genuine partial API successors, uncompiled/orphaned API references, generic-token false positives, absent test coverage and historical documentation preservation questions.

The remaining 76 same-path divergent artifacts are addressed by the focused source audits and the supporting cognitive/engineering reports. The seven other-ref-only cases and 41 no-symbol cases remain covered by their respective supplements. The exact 111-path consumer matrix is now a reconciled discovery inventory rather than an unresolved undifferentiated set.

**DF-02 is ready for final technical/authority reconciliation, but is not marked closed here.** Remaining work is to verify complete cross-branch duplicate-owner coverage for the 76 divergent artifacts, ensure every path is cross-referenced to a focused report, and keep Director-only source-baseline/adoption/retirement/non-adoption decisions explicit. No runtime or donor code was copied.
