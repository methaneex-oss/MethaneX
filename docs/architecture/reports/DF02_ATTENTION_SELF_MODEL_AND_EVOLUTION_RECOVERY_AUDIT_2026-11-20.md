# DF-02 — Attention, self-model and evolution-recovery regression audit

**Date:** 2026-11-20  
**Candidate snapshot:** `cbc51e2b10f1fc976257653adf773735a2b27d49`  
**Donor snapshot:** PR #97 HEAD `c1da222e6c94aeb3f2ad000392c21fe4fc81ab25`

## 1. Attention no longer scores prediction error or internal activation

| Artifact | Candidate blob | Donor blob |
|---|---|---|
| `core/cpp/include/jarvis/core/attention.hpp` | `c7e8ab0c5430d5c942fe314d928400f769c0a77c` | `bc3f97b79664e433fed5bca07b24a6b94dbec1d3` |
| `core/cpp/src/attention.cpp` | `58f734dbe9772675d687752026231297f289e770` | `67def4987f4a49a852bd2e4c9760f05c2ee15216` |
| `core/cpp/tests/attention_architecture_suite.cpp` | `3a5609ed29e117c2241ce3f23543c8042f5815b2` | `4b6f4ad50b9706e372c51e21803e57438d99d155` |

The donor attention model accepts internal activation and extracts prediction error from prediction-outcome events. Both contribute to salience alongside novelty, uncertainty and urgency, and their weights can be reinforced or suppressed through the model's existing policy update methods.

The candidate score API and implementation include only novelty, uncertainty and urgency. It has no internal-activation or prediction-error fields/weights. The attention architecture suite is reduced from 15 assertions / 75 lines to 12 assertions / 62 lines.

The donor Brain computes internal activation from affective state and passes it to attention scoring; it also supplies prediction error from prediction feedback. The candidate Brain source has no equivalent internal-activation/prediction-error attention integration.

**Finding:** candidate attention cannot prioritize an event based on the magnitude of a prediction error or internal activation through this attention mechanism. This weakens the feedback path that should make surprising and internally salient experience receive attention.

## 2. Self-model loses incremental performance updating from execution outcomes

| Artifact | Candidate blob | Donor blob |
|---|---|---|
| `core/cpp/include/jarvis/core/self_model.hpp` | `afd8a340f3e172b09c3859eb2602e383316ec4f8` | `caffaa55562201db6f46ca07bb72189b11695b0b` |
| `core/cpp/src/self_model.cpp` | `3c6a375eadd6894a635d2e18023a7079cba97c86` | `c1beeec968fa62fce8fb037f8b95a869031331ce` |

The donor adds `SelfModel::update_performance(name, observed_performance)`. It revises capability performance from new evidence while preserving availability and isolation as separate dimensions. When no capability record exists, it creates one with availability 1.0 and the observed performance.

The donor Brain's action-outcome replay calls `self_model_.update_performance` for non-rejected action outcomes. The candidate SelfModel has no such method and candidate Brain has no corresponding call. The candidate can set capability availability/performance through explicit observation or restoration, but it does not have this incremental execution-feedback update path.

The same-path self-model health suite is identical in the two snapshots (8 assertions), so the candidate tests do not cover the donor's additional performance-update behavior.

**Finding:** capability performance is not revised from action execution reliability through this self-model mechanism in the candidate.

## 3. Evolution transaction compensation loses the exact previous value

| Artifact | Candidate blob | Donor blob |
|---|---|---|
| `core/cpp/include/jarvis/core/evolution.hpp` | `736876b339846e0ad4da62854a206712e79a201b` | `907cdf538671ad600c498b60b74a2281853b9076` |
| `core/cpp/src/evolution.cpp` | `3860a5a59495460c44e49b8539adff637d7ae65d` | `7a3bc311034c48181cc9b9d4df81c308ebaa8f3d` |
| `core/cpp/src/evolution_controller.cpp` | `01484ebf12fc3902bce749030a1f54610b26236a` | `4e77ec2e5daa09a964132ca486b8c5ee1cebf2f5` |

The donor model adds `restore_previous`, which returns the parameter to its exact pre-adoption value. Its controller uses that operation when journal commit or durable history append fails after the model has been changed.

The candidate model has no `restore_previous`. Its controller uses `rollback` for those transaction-compensation paths; candidate `rollback` resets the parameter to its original baseline, not the exact value immediately before the failed adoption. If a parameter already had a prior successful non-baseline adoption, a later adoption transaction failure can therefore discard that prior valid state.

**Finding:** candidate compensation is not state-preserving for repeated evolution transactions. This is separate from the missing durable evaluation/isolation checks in the previous evolution audit.

## 4. Evolution Brain integration test scope is sharply reduced

Candidate `evolution_brain_integration_suite.cpp` blob `3164cbc19bfb056cdccfdd58f0be047226d41a86` has 7 assertions / 46 lines; donor blob `59d7dd68c42eea18d488d8e5e6aa9f7a9a327ded` has 97 assertions / 298 lines. The candidate retains the same-path target but does not provide equivalent test evidence for the donor's Brain/controller integration scenarios.

## 5. Builder disposition

These findings affect the loop that assigns attention to surprising experience, updates the self-model from action outcomes and safely compensates failed evolutionary transactions.

Do not adopt the donor's fixed weights or update rates automatically. The capability contracts should be preserved or replaced with equally strong, explicitly tested mechanisms whose parameters can be learned or calibrated from evidence. The key requirements are prediction-error-sensitive attention, incremental performance revision that does not overwrite isolation/availability, and transaction compensation that restores the exact pre-operation state.

No runtime, header, test or CMake files were changed in this documentation pass. No donor code was copied. DF-02 remains OPEN.
