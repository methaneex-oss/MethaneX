# DF-02 Affective-State and Appraisal-Learning Adjudication — 2026-11-27

**Scope:** candidate/donor affective-state model, appraisal-learning model and selected Brain evidence/goal integration tests.  
**Candidate:** PR #192 frozen SHA `caf87986dfea7aca75728818651c8687e9f5faf0`. **Donor:** PR #97 `c1da222e6c94aeb3f2ad000392c21fe4fc81ab25`.  
**Disposition:** donor integrates continuous valence/arousal/uncertainty/tension/stability and an adaptive appraisal/calibration model. Source/test inspection only.

## 1. Exact refs

- Donor `affective_state.cpp`: `563a61cd8f6440f78a084f76a799b2c84bdd6813`.
- Donor `affective_learning.hpp`: `fa06043dc481336ba544247f365d37f5476a0651`.
- Donor `affective_state.hpp`: `f63da2e0060938864bf434012d0b3b4d74fa5f29`.
- Donor state test: `29f15bdd1a5d55afd5170a9d21bc3572befc97f0`.
- Donor learning test: `bfbbca315c60c9b1c941dbc553a0cabba304581c`.
- Donor Brain affective-decision integration: `9ff9c0480fa34fa4f5600e514af419b2bbc79765`.
- Donor affective evidence integration: `c8a401cab1a29d57506f990043a1f82536fd9029`.
- Donor goal-outcome integration: `06d72304fa0c4ea67eb4a27b91c484007f231199`.

The learning model is header-only; source/header lineage and alternate blobs are listed in the frozen discovery artifact.

## 2. Model semantics

Affective state updates bounded valence, arousal, uncertainty and tension from signed outcome, prediction error, novelty, salience, uncertainty, confidence and learned appraisal weights. Stability is derived from uncertainty/tension. Time-step integration and exponential decay are bounded.

The appraisal learner tracks mean absolute consequence error, scales learning pressure, adapts six sensitivity weights with bounded updates, and modulates future signals. Its influence confidence is `1 - mean_absolute_error`; poor calibration reduces affective influence. It is continuous appraisal state—not semantic emotion labels or fixed action rules.

## 3. Test evidence

Donor tests assert positive/negative outcome state changes, tension/uncertainty, decay, restore bounds, appraisal-weight learning from poor versus accurate evidence, reduced influence confidence, actual future signal modulation, persistence after Brain replay, generic evidence salience, reliability affecting uncertainty rather than task valence, and goal completion feedback.

Tests are source inspected, not executed. They use repeated synthetic evidence, not independent external validation.

## 4. Remaining limitations

- Calibration error is based on consequence error supplied by the event; it is not an independent calibrated forecast-quality measure. Brain action-outcome validation separately has a consequence-error consistency gap.
- Evidence confidence/relevance can be low but nonzero (relevance floor 0.25); weak evidence still changes appraisal. This may be intentional but requires policy validation.
- `modulate` clamps sensitivity ratios to at least 0.25 of baseline, so learned zero weights do not completely suppress a signal in that helper.
- Fixed appraisal equations and update rates are heuristics; no calibration curves, stability/oscillation tests, distribution shift or long-duration behavior tests.
- Affective integration depends on externally supplied `dt`; wall-clock timing/restart decay is not independently validated.

## 5. Five review lenses

1. **Semantics:** continuous state and adaptive appraisal behavior mapped.
2. **Build/test:** donor state/learning/integration test sources inspected; no native execution.
3. **Integrity:** consequence-error provenance and calibration inputs depend on Brain evidence validation.
4. **Cognition:** affect modulates decision/planning; no evidence it represents semantic emotion or independently validates its forecasts.
5. **Hostile review:** equation/test contract separated from efficacy; no source acceptance.

## 6. Open obligations / disposition

| Item | State |
|---|---|
| State/appraisal source and tests | Inspected |
| Learning/calibration integration | Inspected |
| Replay persistence | Test contract present |
| Calibration/long-term stability evaluation | Open |
| Consequence-error integrity | Cross-report gap |
| Native tests | Not executed |
| Full owner/consumer/authority/retention | Open |
| DF-02 | OPEN |

Affective-state/learning remains **OPEN / NO AUTHORITY DECISION**. No source selected/adopted/retired/deleted; no DF-02 closure, Foundation clearance or Stage A authorization.

 
## Historical execution evidence for donor affective integration tests — 2026-11-28

The following exact donor test blobs are present unchanged on historical alternate branch e737cae7f907696ef787a4e85b0dee3a739d71b1:
- affective_state_suite.cpp 3956eec2ed9885e80ada1d038de6c581338b8f8c (CTest #51);
- affective_decision_learning_suite.cpp 920ddcbc8a422783bb8724093afd952cc885e6b6 (#52);
- affective_state_model_suite.cpp 29f15bdd1a5d55afd5170a9d21bc3572befc97f0 (#53);
- affective_learning_suite.cpp bfbbca315c60c9b1c941dbc553a0cabba304581c (#54);
- affective_evidence_suite.cpp c8a401cab1a29d57506f990043a1f82536fd9029 (#55);
- affective_goal_outcome_suite.cpp 06d72304fa0c4ea67eb4a27b91c484007f231199 (#56);
- affective_decision_suite.cpp 982b11e117b8f59cce3719a5253cb52e96304c0d (#57);
- affective_brain_decision_suite.cpp 9ff9c0480fa34fa4f5600e514af419b2bbc79765 (#58).

All eight tests passed in Brain CI #1826 native/sanitizer, JARVIS Brain Tests #975 brain/sanitizer, and Brain ThreadSanitizer #957; each of the five test jobs reports 71/71. The donor test-CMake blob registers these suites; frozen candidate CMake does not. This is historical alternate-branch execution, not current PR #203 test evidence or an adoption decision.

The pass evidence confirms that the continuous affective state, appraisal learning, evidence weighting, goal outcome and Brain integration test contracts execute together in that branch. It does not resolve the previously listed calibration, nonfinite-input, weak-evidence floor, long-duration stability or consequence-provenance gaps. Synthetic test success is not independent validation of real affective calibration.
