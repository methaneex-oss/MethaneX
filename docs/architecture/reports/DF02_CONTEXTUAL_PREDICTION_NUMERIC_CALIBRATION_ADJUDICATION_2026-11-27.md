# DF-02 Contextual Prediction, Numeric Calibration and Evidence-Confidence Adjudication — 2026-11-27

**Scope:** donor-only `brain_prediction_context.cpp`, prediction-context data carried in Brain API/journal, and phase-10 prediction-feedback tests.  
**Candidate:** PR #192 frozen SHA `caf87986dfea7aca75728818651c8687e9f5faf0`. **Donor:** PR #97 `c1da222e6c94aeb3f2ad000392c21fe4fc81ab25`.  
**Disposition:** contextual prediction is a donor-added capability. It combines graph-derived concept evidence with numeric calibration and feedback. Historical e737 donor prediction-feedback test #30 passed; candidate test source differs and current candidate CTest not run.

## 1. Exact ownership

Donor source `b3ceff150f3fe8223dc3f76f4c298ac264d72dae` (76 tips, 112 lines) has a one-tip alternate `a1038030fae59123b4aa58b1ef2c1b19140898e7`; candidate source path absent. Donor phase-10 test `973350623e52bd9609ebaf1e01082ee52aeb480b` is a test variant (exact history in artifact). Brain public declarations reside in the candidate/donor `brain.hpp` lineages.

## 2. Contextual prediction mechanism

`Brain::predict_with_context` rejects empty key/nonfinite confidence, minimum-strength and nonfinite double input before append. Under the Brain lock it:
- prefers generalized concept matches from shared contextual associations;
- falls back to a concept candidate containing the key, selecting strongest coherence;
- stores concept members and evidence strength in the prediction event;
- optionally applies learned numeric adaptation by **prediction key** (not context), blending numeric prediction with metric estimate and increasing confidence from metric confidence;
- combines base/calibrated confidence and contextual evidence using a noisy-or-like formula;
- appends/replays/consolidates the prediction, then returns the exact sequence-stored record.

Context evidence is graph/co-occurrence coherence, not a separately calibrated predictive likelihood. Confidence amplification assumes evidence components are complementary; calibration/independence is not demonstrated.

## 3. Context leakage / identity risks

- Numeric `adaptation_.metric(key)` is global to the prediction key. A context-specific prediction for that key can inherit numeric estimate/confidence from another context, because the contextual concept is used to increase confidence but does not scope the adaptation metric. This may be intentional global calibration, but context-conditioned performance and regime isolation are not established.
- Concept-member provenance is serialized by joining IDs with `\x1f`; no escaping/length-prefixing at this layer. IDs containing that separator can make ambiguous provenance.
- Context confidence derives from association graph coherence and similarity. It can be high from repeated co-change without independent predictive validation; no calibration curve/Brier/log-loss or false-context-transfer analysis was inspected.

## 4. Test evidence and gaps

Phase-10 source asserts non-finite predictions/confidence are rejected, numeric int/double equivalence, numeric calibration, contextual concept creation and provenance persistence, concept generalization, feedback strengthening/weakening, duplicate/mismatched sequence rejection before affect mutation, malformed/nonfinite/inconsistent prediction feedback rejection, and later action-choice changes/persistence through replay.

Donor test #30 passed in historical e737 CI; candidate test source differs and current candidate CTest was not run. Gaps: same prediction key under conflicting contexts and cross-context numeric calibration contamination; calibration quality and confidence calibration; member-ID delimiter collisions; false concept-context transfer; adversarial graph/coherence cases; fuzzing.

## 5. Five review lenses

1. **Semantic:** contextual concept evidence and numeric calibration path identified.
2. **Build/test:** donor source/test CTest #30 passed in historical e737 CI; candidate test source differs and current candidate CTest was not run.
3. **Integrity:** context-member serialization identity and global metric scope are open.
4. **Cognition:** graph evidence influences predictions, but is not calibrated contextual probability or robust semantic understanding.
5. **Hostile review:** evidence-strength/confidence terms qualified; no capability claim beyond source/test contract.

## 6. Open obligations / disposition

| Item | State |
|---|---|
| Exact donor source/test | Verified |
| Candidate source path absent | Confirmed |
| Context graph and numeric calibration behavior | Source/test inspected |
| Cross-context metric contamination | Open |
| Confidence calibration/false transfer | Open |
| ID encoding robustness | Open |
| Native tests | Not performed |
| Full consumer/authority/retention | Open |
| DF-02 | OPEN |

Contextual prediction remains **OPEN / NO AUTHORITY DECISION**. No source selected/adopted/retired/deleted; no DF-02 closure, Foundation clearance or Stage A authorization.

 
## Historical execution and candidate test-source divergence — 2026-11-28

The e737cae7 alternate branch contains the exact donor source/test blobs:
- brain_prediction_context.cpp b3ce6d18bcae51f5f8847c2d5a6118dfb4d2c3c4 (240 lines);
- prediction_feedback_phase10_suite.cpp 973350e9db5d3b16d18d0bb1c4f98175c9a4f5c (1,339 lines / 371 assert expressions).

The same CTest name jarvis_prediction_feedback_phase10_suite is registered in candidate CMake, but the frozen candidate test source is a different blob e72da8e7653aee775cfade9060064231c7a01630 (73 lines / 12 assert expressions). The candidate test contains neither predict_with_context nor apply_prediction_feedback. Therefore "candidate CTest registration = yes" does not mean the candidate contains the donor's contextual prediction/feedback behavioral contract.

The donor/alternate test passed CTest #30 in Brain CI #1826 native/sanitizer, JARVIS Brain Tests #975 brain/sanitizer and Brain ThreadSanitizer #957; all five jobs report 71/71. This execution is for the 1,339-line donor test and contextual source, not the 73-line candidate test or current PR #203.

The result supports the donor variant's tested contextual prediction/feedback behavior in synthetic scenarios. It does not establish probability calibration, causal validity, broad held-out context generalization or current-candidate behavior. No code was adopted.
