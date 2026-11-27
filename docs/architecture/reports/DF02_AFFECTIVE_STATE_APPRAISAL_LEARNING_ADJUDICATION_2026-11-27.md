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
