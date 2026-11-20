# DF-02 — Cognitive runtime, memory, association and adaptation regression audit

**Date:** 2026-11-20  
**Candidate snapshot:** `cbc51e2b10f1fc976257653adf773735a2b27d49`  
**Donor snapshot:** PR #97 HEAD `c1da222e6c94aeb3f2ad000392c21fe4fc81ab25`

This supplement examines five core mechanisms and their registered tests. It is a source-level comparison, not an endorsement of every donor implementation detail. Exact blobs are pinned below.

## 1. Cognitive runtime loses the feedback-ingress and selected-action execution path

| Artifact | Candidate blob | Donor blob |
|---|---|---|
| `core/cpp/include/jarvis/core/cognitive_runtime.hpp` | `d02b2607cebcb7c31963e2fe336970707a481e00` | `e5a3c853add8b5fcb9b8c04c9b25f20179b5b629` |
| `core/cpp/src/cognitive_runtime.cpp` | `1a1383cedc42e357dc9efce117328b8d55e30bca` | `cf00acb6abd52308343f3a0e7016e6173b945603` |
| `core/cpp/tests/cognitive_runtime_suite.cpp` | `48cac9cb0e27e2dc8a15323429d1f7158ee427a0` | `361cba84a6fc6e07e31d14b5fa618c3f0a7848fa` |

The donor runtime exposes `submit_feedback`, tracks `pending_feedback`, processes feedback through the cognitive cycle and reports processed/rejected/failed feedback metrics. It also has `execute_actions`: it matches plan steps to action assessments, executes only the selected plan actions in plan order, and does not execute every candidate alternative. This prevents a planning cycle from secretly executing alternatives and teaching the system consequences for actions it did not choose.

Those public methods and implementations are absent from the candidate runtime. The candidate runtime retains input submission, queueing, result polling and worker-loop functionality, but no corresponding feedback queue/processor or planned-action execution method.

The registered runtime suite is reduced from 100 assertions / 356 lines to 19 assertions / 87 lines.

**Finding:** candidate runtime lacks two critical bridges between cognition and an interactive learning agent: external feedback ingress and execution of the selected plan. This is a functional integration gap, not a naming difference.

## 2. Memory loses explicit experience consolidation and learned-tier reconstruction APIs

| Artifact | Candidate blob | Donor blob |
|---|---|---|
| `core/cpp/include/jarvis/core/memory.hpp` | `f3662038237246efa51155f940d77564f144d6d9` | `5401d5bd236cca8d3a93f2815164a7734cf6990f` |
| `core/cpp/src/memory.cpp` | `ba72a897306d4761246d0deab2fbab37c49d372f` | `ab42bba1d32d6f48d091787491c72294a4a55bb5` |
| `core/cpp/tests/memory_architecture_suite.cpp` | `2a9eb061427c622260304d09f45089e1debef294` | `ecabc6af76c52ed1e4175b151e76fadecae7729d` |

The donor exposes `Memory::consolidate`, `Memory::rebuild_learned_tiers` and `latest_sequence_by_kind`. Its consolidation path consumes salience, novelty, prediction error and confidence, considers recurrence, updates persistent consolidation metadata and can move an event between memory tiers. The loader rebuilds learned tier aggregates from persisted metadata.

The candidate has no corresponding `consolidate`, `rebuild_learned_tiers` or `latest_sequence_by_kind` API/implementation. It retains other memory facilities, including tier metadata, ranking and manual promotion; this finding is specifically about the missing explicit experience-driven consolidation and learned-tier reconstruction path, not a claim that the candidate has no memory or persistence.

The memory architecture suite is reduced from 70 assertions / 188 lines to 27 assertions / 61 lines.

**Design caution:** the donor consolidation routine contains fixed coefficients and thresholds. They are evidence of an existing mechanism, not automatically the correct JARVIS policy. Any restoration should keep the mechanism testable and allow experience to determine content; it must not turn those coefficients into hard-coded semantic stimulus→response rules.

## 3. Association model loses contextual inference, concept generalization and prediction-feedback updates

| Artifact | Candidate blob | Donor blob |
|---|---|---|
| `core/cpp/include/jarvis/core/association_model.hpp` | `faa835175cfd6c2fdc1d4561269edb8ab406c689` | `9890f4e0178200acada0f43a5626be6f6daa6cce` |
| `core/cpp/src/association_model.cpp` | `b378d4237527dfbb4c65f43545f7f0fc7c42669b` | `80bc2e94d8cab4e5a48ead18ba9efcad4ed785b6` |
| `core/cpp/tests/association_causality_phase5_suite.cpp` | `d520025258805b02c1b3fbb2dbebe32e01562fbf` | `0d31349857e85a019467e9864bbe6625a6ecdef7` |

The donor adds four public operations absent from the candidate:
- `contextual`: bounded multi-hop inference over association paths with strength decay;
- `concept_candidates`: identifies entities sharing relational neighborhoods;
- `generalized_concepts`: uses shared relational context to generalize from known members;
- `apply_prediction_feedback`: adjusts association strength/confidence and contradiction counts from successful or unsuccessful predictions.

The candidate association model exposes only direct observation, enumeration and related-association lookup. The phase-5 suite is reduced from 46 assertions / 161 lines to 12 assertions / 57 lines.

**Finding:** the candidate loses explicit multi-hop/contextual association, relational concept formation and the mechanism by which prediction outcomes revise association evidence. These mechanisms are important to generalization and experience-dependent belief change.

**Design caution:** the donor feedback update uses fixed success/failure rates. The architectural capability (outcome-sensitive association revision) is distinct from those particular coefficients; the coefficients require their own justification and tests before any adoption.

## 4. Adaptation is narrowed to bounded [0,1] values and loses recency/change response

| Artifact | Candidate blob | Donor blob |
|---|---|---|
| `core/cpp/src/adaptation.cpp` | `7e07a491a5b13379a5719882a834ecc2452a54ef` | `51b91a52c20f71a1be462f660c45bee9199259c3` |
| `core/cpp/tests/learning_adaptation_phase8_suite.cpp` | `79cb7b8146686b35273628de213d33edd4328cff` | `59859480a6d09aaab70eaf09ffc94c731484d2ff` |

The candidate clamps both prediction and actual values into `[0,1]`, then applies a cumulative-mean update. That is unsuitable for general numeric predictions where values may be negative, exceed one or represent signed outcomes/physical quantities: distinct values collapse to the same boundary and sign/magnitude information is lost.

The donor preserves finite signed/unbounded numeric inputs, normalizes error by scale, keeps long-term and recency-sensitive error separately, detects sustained surprising sequences, and uses a numerically safer convex blend for extreme finite values. Its confidence uses both stable and recent accuracy. The donor test explicitly covers regime change, isolated noise, signed/extreme finite values, invalid samples and persistence; the candidate suite does not.

The phase-8 suite is reduced from 60 assertions / 176 lines to 23 assertions / 66 lines.

**Finding:** candidate adaptation is not a general numeric predictor calibrator; it is a bounded-probability updater. This mismatch is material where JARVIS predictions include signed consequence values or unbounded quantities.

## 5. Cognitive-cycle source/test scope is substantially reduced

| Artifact | Candidate blob | Donor blob |
|---|---|---|
| `core/cpp/src/cognitive_cycle.cpp` | `3df14c552f2048b0394dc362f7ee7a654a93fb32` | `f191dd610d6cbe1621756c35e7c13af2054a7266` |
| `core/cpp/tests/cognitive_cycle_suite.cpp` | `38ff2c7d6e851b4745e9dc7c01f968b7245400a2` | `3e762cdec8b27030cf94478a1a68a4605a38c8c5` |

The candidate and donor expose overlapping top-level cycle method names, but the donor implementation is 777 lines versus 162 candidate lines. The registered test is 186 assertions / 788 lines in the donor and 31 assertions / 98 lines in the candidate. This scale of reduction is a strong semantic-review signal, not by itself proof that every removed line represents lost behavior. The cycle internals and all removed donor test scenarios require explicit successor mapping before equivalence can be claimed.

## 6. Consolidated evidence

| Mechanism | Donor test assertions | Candidate test assertions | Reduction |
|---|---:|---:|---:|
| Cognitive cycle | 186 | 31 | 155 |
| Cognitive runtime | 100 | 19 | 81 |
| Memory architecture | 70 | 27 | 43 |
| Association/causality | 46 | 12 | 34 |
| Adaptation | 60 | 23 | 37 |
| **Total** | **462** | **112** | **350** |

These five suites retain same-path target files in the candidate, but their reduced assertions do not establish equivalent behavior. The missing APIs and integration methods above are separately verified by exact header/source comparison.

## 7. Builder disposition

These findings are high-priority candidate regressions affecting the experience → representation/association → prediction feedback → memory consolidation → adaptation → planning/action loop.

They do not justify blindly restoring donor code. Some donor mechanisms contain fixed coefficients that must be examined against JARVIS's mechanism-first, experience-acquired behavior principle. The correct next step is to map each missing capability to its current candidate successor (if any), identify duplicate ownership and dependencies, and design integration tests that prove persistent behavior change without hard-coded semantic mappings.

No runtime source, CMake or test file was changed in this documentation pass. No donor code was copied or adopted. DF-02 remains OPEN for the remaining candidate lexical paths and full semantic successor/dependency/duplicate-owner/retention/retirement/authority adjudication.
