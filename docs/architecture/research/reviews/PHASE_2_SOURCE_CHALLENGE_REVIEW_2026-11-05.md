# Phase 2 — Source Challenge Review of the Whole-Brain Integration Map

**Date:** 2026-11-05  
**Review target:** PR #181, head `cf3f8db7e5e5ca5eb1c0345bafdb704e92d70f25`  
**Reviewed report blob:** `82f7479bc0bc9170932b7b6e8d0eb989d94d965b`  
**Main source baseline:** `1273ddbcd0087d189e01388ded2d362fb1e058d2`  
**PR #97 donor snapshot:** `c1da222e6c94aeb3f2ad000392c21fe4fc81ab25`  
**Review type:** adversarial source challenge of the initial Phase 2 map; static source and test-definition inspection only.

## 1. Review conclusion

PR #181's central conclusion survives challenge: main contains useful cognitive mechanisms, but the inspected main cognitive cycle does not establish a coherent, fully integrated Brain. The most consequential demonstrated defect remains the disconnected reasoning path: memories are retrieved but not supplied to reasoning; reasoning output is stored but not consumed by later prediction, planning or decision.

The report is directionally sound and appropriately conservative about implementation readiness. However, it under-describes several real donor integrations, especially the way episodic action-outcome memory is consumed by the donor cognitive cycle and the way affect influences memory consolidation and attention as well as planning. Those omissions matter because Phase 2 must map actual cross-mechanism flows, not only list subsystem capabilities.

The donor branch also does not close the full memory-to-reasoning requirement. It improves memory-to-action-value learning and reasoning-to-prediction integration, but its `ReasoningProblem` still receives beliefs and causal links, not retrieved episodic memories. This distinction must be explicit.

**Disposition:** accept PR #181 as a valid initial map with material refinements required. Do not treat this challenge as Phase 2 completion, implementation authorization, Gate A clearance or Gate B acceptance.

## 2. Confirmed main-branch findings

### 2.1 Memory retrieval is disconnected from reasoning

At main baseline `1273ddbcd0087d189e01388ded2d362fb1e058d2`, `core/cpp/src/cognitive_cycle.cpp` retrieves ranked memories into `result.context.memories`, then constructs `ReasoningProblem` with only `result.context.beliefs` and `result.context.causal_links`. The resulting `ReasoningResult` is assigned to `result.context.reasoning`; the remainder of the cycle builds predictions, selects goals, plans and decides without using that result.

This is stronger than a missing test claim: it is directly visible in the production call path. `core/cpp/src/reasoning.cpp` also confirms that the current solver performs same-key scalar consistency checks and bounded forward traversal over encoded links. An empty premise set returns valid with zero confidence. It does not establish the broader BM-12 inference contract.

### 2.2 Main runtime workspace is a projection, not integrated context control

At main, `core/cpp/src/cognitive_runtime.cpp` copies cycle outputs into a `CognitiveWorkspace`, replaces the shared workspace snapshot and separately queues the cycle result. The worker processes one item at a time. This confirms useful runtime coordination primitives, but not multi-context isolation, dependency invalidation, coherent concurrent state ownership or downstream workspace consumption. The original report's conservative classification is correct.

### 2.3 Main memory is more than a volatile cache, but not full semantic memory

`core/cpp/src/memory.cpp` persists sequenced events in a journal and tier/salience/confidence metadata in a sidecar, then reconstructs the journal on startup. Retrieval remains attribute-overlap/ranking based. Persistence and tier metadata should not be presented as proof of semantic understanding, source authentication, evidence lineage or complete cognitive-state reconstruction.

## 3. Donor integrations that should be made more explicit

### 3.1 Donor episodic memory influences live candidate-action valuation

At PR #97 donor snapshot, `core/cpp/src/cognitive_cycle.cpp`:

- retrieves prior observation memories and action-outcome memories (approximately lines 146–180);
- derives a developmental context from the observation and perceptual representation (lines 435–436);
- retrieves exact-context action-outcome memories (lines 449–457);
- aggregates observed consequence evidence for each candidate action (lines 467–528);
- combines direct and related learned strategy evidence (from approximately line 535 onward);
- applies the evidence before the normal planning/decision path (through approximately lines 725–732).

This is a genuine memory-to-future-action path, not merely a strategy table existing beside memory. The report should record it as a donor candidate spanning BM-03, BM-08 and BM-09.

Important limitation: the evidence is action- and context-specific, relies on structured event fields and an engineered context representation, and does not turn arbitrary episodic memory into general reasoning premises.

### 3.2 Donor reasoning influences prediction, but remains memory-blind

The donor cycle constructs `ReasoningProblem` from beliefs and causal links, just as main does. However, it subsequently uses valid reasoning conclusions as assumptions for forward simulation, falling back to observed beliefs when the reasoning result is invalid or empty (approximately lines 299–305).

Therefore the donor improves **reasoning → prediction**, but not **episodic memory → reasoning**. Do not describe the donor as having closed BM-12 or the full memory-supported inference flow.

### 3.3 Donor affect has additional consumers beyond planning

At PR #97 donor snapshot, `core/cpp/src/brain.cpp`:

- affective state contributes to memory consolidation salience (approximately lines 200–217);
- affective appraisal modulates signals before affective-state updates (approximately line 289);
- affective significance contributes to action-outcome evidence handling (approximately lines 404–465);
- internal affective activation is passed into attention scoring (approximately lines 748–749).

`core/cpp/src/brain_affective_planning.cpp` separately shows affective state/appraisal consumed by intent selection and planning, while developmental evidence changes candidate utility before decision scoring.

The original map correctly identifies donor affective planning and action-evidence consumers, but its BM-07/cross-mechanism account should explicitly include affect → attention and affect → memory consolidation. These are meaningful integrated pathways. They remain bounded engineered dynamics, not evidence of human-equivalent affective understanding.

### 3.4 Donor runtime integration tests assert persistent behavioral change

The donor `core/cpp/tests/cognitive_runtime_learning_integration_suite.cpp` includes source assertions for:

- a first observed consequence affecting later action choice (approximately lines 140–170);
- context isolation (approximately lines 177–205);
- changed environmental regime eventually reversing the learned preference (approximately lines 207–240);
- persistence affecting an actual post-restart decision, not only an inspection API (approximately lines 242–270);
- successful execution/verification without observed consequence not being treated as beneficial outcome learning (approximately lines 273 onward).

The donor `core/cpp/tests/developmental_brain_integration_suite.cpp` also asserts episodic action-outcome retrieval can change decision scores when strategy state is absent (approximately lines 252–316), alongside related-context and restart cases.

These are stronger source-level test specifications than a generic claim that synthetic learning exists. They establish what the tests intend to assert; they do **not** establish that these tests passed at the exact donor SHA in a reproducible CI run, nor do they establish open-world transfer. The donor CMake file declares 71 executables and 70 CTest registrations. Target declaration/registration must not be confused with execution evidence.

## 4. Evidence and compatibility qualifications

1. PR #97 is still an open draft donor PR, not an accepted implementation baseline. Its metadata reports base SHA `4ba84b8b5ccf0e41530c46fdb8101551254ba864`; main audit baseline `1273ddbcd0087d189e01388ded2d362fb1e058d2` is eight commits ahead of that base with no divergence in the GitHub compare result. The donor snapshot must still be evaluated against the exact accepted specification and current source contracts.
2. The PR #97 donor contains 159 changed files and a large historical commit count. The Phase 2 report expressly limits its donor review to selected paths; this challenge does not convert that sample into a complete donor audit.
3. The runtime integration tests use controlled callbacks and synthetic environments. Their regime-change, context-isolation and restart assertions are valuable bounded evidence, but they do not establish generalization to unknown modalities, unstructured environments or arbitrary goals.
4. The affective equations use fixed weights, normalization, decay and bounded scalar dimensions. This is an engineered appraisal substrate. The existence of adaptation around some appraisal weights does not eliminate the fixed prior structure.
5. Neither this review nor PR #181 ran builds, CTest, benchmarks, sanitizers or workflows. No claim is made that code compiles or that any donor test passed during this review.

## 5. Required corrections to the Phase 2 map

1. Add an explicit donor flow: action-outcome episodic memory → context-matched evidence aggregation → candidate utility/expected-value adjustment → normal planning/decision.
2. Separate the donor's two distinct achievements: reasoning conclusions → forward simulation; episodic memory → action-value learning. State clearly that episodic memories are still absent from reasoning premises.
3. Expand BM-07 donor consumers to include affect → attention scoring and affect → memory consolidation, not only intent/planning and action evidence.
4. Record the donor runtime test assertions as source-defined evidence with an explicit non-execution caveat. Distinguish test source, CMake registration, CI execution at the exact SHA, and independently reproduced execution.
5. Continue tracing state ownership/replay for each authoritative mechanism. In particular, identify which affective, developmental, goal, belief, prediction and evolution state is rebuilt from the event journal versus derived from sidecar metadata or retained transiently.
6. Continue tracing failure attribution: distinguish action request, authorization, execution, verification and observed environmental consequence. A verified executor response is not evidence that the intended world outcome occurred.

## 6. Remaining Phase 2 investigation

This challenge is not an exhaustive source audit. The next source work should cover:

- full donor persistence/replay ownership and ordering across all state owners;
- exact PR #176 D1/D2 fixes and the remaining controller compensation failure paths;
- donor/main API and state-contract compatibility against PR #174;
- actual test workflow runs tied to exact commit SHAs, with test selection and logs;
- memory, belief, prediction, goal and strategy invalidation when source evidence changes;
- concurrent runtime/context behavior and recovery after partial failures;
- outcome attribution when sensors/providers fail, return partial evidence or disagree;
- held-out, non-synthetic learning transfer and regression evidence.

## 7. Final assessment

PR #181's principal diagnosis is confirmed. Its donor characterization should be strengthened to reflect real cross-mechanism pathways, while preserving the critical boundary: the donor's integrated action-learning loop is not a general memory-grounded reasoning system. The main implementation baseline remains incomplete; the donor remains unaccepted; no implementation decision follows from this review.

**Phase 2 remains in progress.** The next work is to resolve the evidence gaps above and continue the source-to-consumer map. No Gate A/B status is changed.
