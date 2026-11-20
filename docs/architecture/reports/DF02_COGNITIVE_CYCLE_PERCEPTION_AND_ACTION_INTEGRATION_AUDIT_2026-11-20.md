# DF-02 — Cognitive-cycle perception, affect and action integration audit

**Date:** 2026-11-20  
**Candidate snapshot:** `cbc51e2b10f1fc976257653adf773735a2b27d49`  
**Donor snapshot:** PR #97 HEAD `c1da222e6c94aeb3f2ad000392c21fe4fc81ab25`

## 1. Exact source/test evidence

| Artifact | Candidate blob | Donor blob |
|---|---|---|
| `core/cpp/include/jarvis/core/cognitive_cycle.hpp` | `28e7af98327956268a769adf7813125be842c1a2` | `eed8bc75f59557c255e796343d77498d90b31ea5` |
| `core/cpp/src/cognitive_cycle.cpp` | `3df14c552f2048b0394dc362f7ee7a654a93fb32` | `f191dd610d6cbe1621756c35e7c13af2054a7266` |
| `core/cpp/tests/cognitive_cycle_suite.cpp` | `38ff2c7d6e851b4745e9dc7c01f968b7245400a2` | `3e762cdec8b27030cf94478a1a68a4605a38c8c5` |

## 2. Perception and representation are not part of the candidate cycle contract

The donor cycle includes `representation.hpp` and `perception_pipeline.hpp`, stores a `PerceptionPipeline`, exposes mutable/const pipeline accessors for provider configuration, and accepts a `developmental_context` on each input. Its cycle context preserves the `PerceptualRepresentation` alongside the observation.

The candidate cycle includes neither perception nor representation in its public contract. Its input has no developmental context, and its context contains only the raw observation and downstream memory/belief/reasoning/planning structures.

**Finding:** the candidate cycle does not expose the donor's shared perception pipeline or structured perceptual representation path. A raw observation is not equivalent to a reusable perception representation consumed by reasoning, memory and developmental mechanisms.

## 3. Affective appraisal and attention are not exposed in the candidate cycle result

The donor cycle context carries `AffectiveState`, `AffectiveAppraisal` and `AttentionSignal`. The candidate context carries none of these. This is a public integration difference even though separate affective and attention subsystems exist elsewhere in the candidate tree.

**Finding:** the candidate cognitive cycle does not provide the donor's unified per-cycle affective/attention context to downstream cycle consumers.

## 4. Selected actions are not executed or represented as execution outcomes

The donor cycle context contains `std::vector<ActionExecutionResult> action_execution_results` and includes the action-execution interface. The candidate context ends at `action_assessments`; it has no execution-result collection. The donor runtime additionally executes only the actions selected by the plan. The candidate runtime lacks the corresponding `execute_actions` method.

**Finding:** the candidate end-to-end cycle/runtime boundary stops at action assessment; it does not provide the donor's integrated selected-action execution and execution-outcome path.

## 5. Feedback API is materially narrower

The candidate `CognitiveFeedbackResult` exposes only prediction-resolved status, learned reliability and reflection. Its `process_outcome` accepts an optional prediction key, actual value and optional evidence.

The donor result additionally reports goal-progress assimilation and returns affective state/appraisal. It provides:
- an overload taking the exact originating `Prediction` object, preserving its journal sequence;
- a key-based overload with optional goal ID, goal progress, goal confidence, prediction sequence and outcome utility.

The donor implementation resolves feedback by exact prediction sequence when available, and assimilates goal-outcome evidence through Brain. The candidate cannot submit goal-progress evidence or outcome utility through its cycle feedback contract and cannot report whether goal progress was assimilated.

## 6. Test evidence

The registered cognitive-cycle suite is **186 assertions / 788 lines** in the donor and **31 assertions / 98 lines** in the candidate. The candidate's source is 162 lines versus 777 donor lines. The scale difference is not by itself proof that every removed line is missing behavior; the exact public-contract differences above establish concrete integration gaps independently of line counts.

## 7. Builder disposition

The candidate cycle has useful raw-observation, memory, belief, reasoning, goal, planning, decision and assessment components. However, the donor's wider integrated contract also binds perception/representation, affective appraisal, attention, selected action execution, sequence-safe prediction feedback and goal-outcome assimilation into one cycle.

A repair must preserve the existing candidate architecture while proving these mechanisms interact in a complete loop. Do not solve this by merely adding fields to a result struct: the provider pipeline, evidence provenance, action execution, feedback validation, persistent learning and next-cycle behavior need integration tests.

No runtime or CMake files were changed. No donor code was copied. DF-02 remains OPEN.
