# DF-02 Contextual Prediction, Numeric Calibration and Evidence-Confidence Adjudication — 2026-11-27

**Scope:** donor-only `brain_prediction_context.cpp`, prediction-context data carried in Brain API/journal, and phase-10 prediction-feedback tests.  
**Candidate:** PR #192 frozen SHA `caf87986dfea7aca75728818651c8687e9f5faf0`. **Donor:** PR #97 `c1da222e6c94aeb3f2ad000392c21fe4fc81ab25`.  
**Disposition:** contextual prediction is a donor-added capability. It combines graph-derived concept evidence with numeric calibration and feedback. Source/test inspection only.

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

Tests were inspected, not executed. Gaps: same prediction key under conflicting contexts and cross-context numeric calibration contamination; calibration quality and confidence calibration; member-ID delimiter collisions; false concept-context transfer; adversarial graph/coherence cases; fuzzing.

## 5. Five review lenses

1. **Semantic:** contextual concept evidence and numeric calibration path identified.
2. **Build/test:** donor source/test inspected; candidate path absent; no native run.
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
