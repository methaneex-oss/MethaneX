# DF-02 — Prediction identity and feedback-validation regression audit

> **Scope clarification:** This is a capability-gap comparison between the pre-PR-#97 candidate source baseline and the unmerged PR #97 donor implementation line. It does **not** claim the candidate previously integrated these donor mechanisms and then lost them. The term “regression” in this historical report filename means a functional delta relative to the donor, not a post-integration code regression. The donor is not an adopted baseline; the Project Director retains source selection and adoption authority.

**Date:** 2026-11-20  
**Candidate baseline:** PR #192 base/merge-base `61311fe5b44c81c4409c8ba8dc581a83bdd5dd2c`. Every candidate source/test blob cited in this report was re-fetched at that exact PR base and matched the blob previously inspected at `cbc51e2b10f1fc976257653adf773735a2b27d49`.  
**Donor snapshot:** PR #97 HEAD `c1da222e6c94aeb3f2ad000392c21fe4fc81ab25`

This audit compares the prediction storage, resolution and feedback-validation path. It identifies a structural issue: the candidate represents unresolved predictions by key only, while the donor supports distinct prediction instances and sequence-bound outcomes.

## 1. Exact source/test evidence

| Artifact | Candidate blob | Donor blob |
|---|---|---|
| `core/cpp/include/jarvis/core/brain.hpp` | `8268ef84e0b361ead536724ba7761904b30ee58f` | `671186f4c39879a182f9e511394fc564d86f2988` |
| `core/cpp/src/brain.cpp` | `e9f3758fcc9c0e89b7280ce376db9033d547682d` | `dec9e5442b3ca4b81a7879855c6146b2619934cc` |
| `core/cpp/tests/prediction_feedback_phase10_suite.cpp` | `e72da8e7653aee775cfade9060064231c7a01630` | `973350623e52bd9609ebaf1e01082ee52aeb480b` |
| `core/cpp/tests/brain_deep_suite.cpp` | `ca8e7012c92822608c3be0539784d281b0578bfd` | `1314123ea3b524b24fd6693fc6fb4873b6c550d5` |

## 2. Candidate prediction identity is key-only

The candidate stores predictions in `std::unordered_map<std::string, Prediction>`. Calling `predict(key, ...)` for a second unresolved prediction with the same key replaces the first map entry. The candidate exposes `resolve_prediction(key, actual)` only; it does not expose sequence-based prediction resolution or a structured `PredictionFeedbackStatus`.

The donor stores predictions as a vector, preserving multiple prediction instances even when they share the same key. It exposes sequence-based lookup/resolution and feedback status. A caller can resolve the exact prediction instance by its immutable memory sequence rather than implicitly resolving whichever entry currently occupies a key.

**Finding:** key reuse can collapse distinct unresolved predictions in the candidate. Delayed feedback for an earlier prediction cannot reliably target the original prediction once a later prediction with the same key overwrites it.

## 3. Donor validates feedback against the exact prediction event before mutation

The donor's replay/feedback path checks that an outcome references an existing unresolved prediction, verifies its key and optional sequence, and validates the reported error against the prediction and actual outcome before cognitive subsystems are updated. Sequence-bound resolution supports multiple pending predictions for the same key and prevents stale/duplicate/malformed outcome events from mutating the wrong prediction.

The candidate's simpler key-map path resolves by key and marks the stored prediction resolved; it does not carry the donor's sequence-bound validation contract.

This matters because prediction error is not merely a metric. It is fed into adaptation, association, attention, affective appraisal and subsequent learning. A stale or misattributed outcome can therefore contaminate persistent experience and future behavior.

## 4. Test evidence is materially reduced

The registered phase-10 prediction-feedback suite falls from **371 assertions / 1,339 lines** in the donor to **12 assertions / 73 lines** in the candidate. The donor suite exercises the sequence-aware feedback contract and extensive replay/learning behavior; the candidate suite does not include the sequence-based API/status contract. The donor brain-deep suite is 260 assertions / 835 lines versus 68 assertions / 182 lines in the candidate.

These counts do not imply every removed assertion maps to a unique missing feature, but they establish that the candidate test suite does not provide equivalent evidence for the donor's prediction-feedback guarantees.

## 5. Builder disposition

This is a high-priority learning-integrity regression. A robust repair must preserve multiple outstanding predictions per key, bind delayed outcomes to exact prediction identity, validate event consistency before updating any learning subsystem, and test duplicate/stale/out-of-order feedback plus persistence/replay. It should not introduce fixed stimulus-to-emotion or outcome-to-behavior mappings; the observed prediction error should remain evidence consumed by general learning mechanisms.

No runtime code was changed. No donor code was copied. DF-02 remains OPEN pending remaining candidate path and dependency/ownership adjudication.
