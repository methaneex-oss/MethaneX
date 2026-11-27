# DF-02 Direct LearningLoop/EvolutionModel Adoption Path Adjudication — 2026-11-27

**Scope:** donor-only `LearningLoop`, candidate/donor `EvolutionModel`, direct adoption API and architecture test.  
**Candidate:** PR #192 frozen SHA `caf87986dfea7aca75728818651c8687e9f5faf0`. **Donor:** PR #97 `c1da222e6c94aeb3f2ad000392c21fe4fc81ab25`.  
**Disposition:** a separate direct-feedback evolution path exists beside experiment/controller adoption. It applies parameter changes without experiment isolation or the strict controller gate. The direct test does not exercise successful adoption.

## 1. Exact refs

- `evolution.cpp`: donor `7a3bc311034c48181cc9b9d4df81c308ebaa8f3d`.
- `evolution.hpp`: donor `907cdf538671ad600c498b60b74a2281853b9076`.
- `learning_loop.cpp`: donor-only `bc9a6aaca38d060667bcdf82f2b1a1f72c5936ba`.
- `learning_loop.hpp`: donor-only `287f2fe34cebd60b7a562d68c666572f71431cd6`.
- `learning_loop_architecture_suite.cpp`: donor-only `1b01fc772f525619fb635579ccf7831187fee08a`.

## 2. Direct mechanism

`EvolutionModel::observe_fitness` maintains a clamped running mean for a parameter. `propose` moves parameter in the direction of mean fitness sign by a fixed fraction, with expected gain = abs(mean fitness) × step magnitude and confidence = 1−exp(−observations/8). `evaluate` checks key exists, finite proposal fields, expected gain above policy minimum, proposal differs from current, current matches stored parameter and confidence meets policy. `adopt` applies the proposal, clamped to parameter bounds.

`LearningLoop::process` accepts key/predicted/actual/fitness, updates adaptation, observes fitness, proposes and directly calls `EvolutionModel::adopt` for same key when confidence ≥0.75 and expected gain positive. It does not create an experiment, run an isolated candidate, validate evaluator provenance or route through EvolutionController/SafetyGate/AdoptionJournal.

This path is distinct from the experiment-based controller, canary and Brain adoption transaction. It may be a standalone legacy mechanism; no Brain cognitive-cycle consumer was located in the reviewed source.

## 3. Source-derived safety gaps

- **Proposal not recomputed:** public `EvolutionModel::evaluate/adopt` accepts caller-supplied finite `proposed` and `expected_gain`; it checks current-value equality and thresholds but does not recompute proposal/gain from recorded fitness or verify the candidate value is within bounds before eligibility. A fabricated proposal can pass, then be clamped at mutation.
- **No experimental evidence:** the direct path uses aggregate feedback and fixed sign/step heuristic. It is not candidate execution or measured candidate-vs-baseline improvement.
- **Policy threshold mismatch:** LearningLoop hardcodes confidence ≥0.75 independently of EvolutionPolicy minimum confidence, creating a second gate.
- **No Brain integration evidence:** this class has a test but no inspected integration into Brain/CognitiveRuntime. The strict controller and direct model are separate paths, and consumer/authority disposition is open.
- **Rollback semantics:** EvolutionModel rollback resets parameter to baseline, not previous value; it is not an adoption-history-aware rollback.

## 4. Test contract

The donor test runs eight repeated feedback samples, asserts adaptation observations/estimate/confidence/proposals and that `adopted <= 1`, then only asserts parameter remains ≥ initial value. Confidence after eight observations is (1-e^{-1}approx0.632), below the hardcoded 0.75 LearningLoop threshold, so this test does **not** exercise successful direct adoption. It does test invalid key and NaN prediction leave adaptation unchanged.

No test directly fabricates an EvolutionProposal, exercises successful direct adoption at ≥12 observations, verifies proposal/gain recomputation, bounds clamping, rollback semantics, or compares direct path against experiment-gated controller. Tests were inspected, not executed.

## 5. Five review lenses

1. **Semantics:** direct feedback proposal/adoption is separate from experimental evolution.
2. **Build/test:** donor-only LearningLoop source/test inspected; no native execution.
3. **Trust:** direct proposal fields and fitness are not independently evaluated.
4. **Cognition:** standalone scalar update heuristic; no Brain consumer demonstrated.
5. **Hostile review:** controller experiment gate is not conflated with this API; successful direct adoption remains untested.

## 6. Open obligations / disposition

| Item | State |
|---|---|
| Exact direct path source/test | Verified |
| Direct adoption gate vs experiment controller | Compared |
| Successful adoption in test | Not exercised |
| Fabricated proposal validation | Gap |
| Experiment/evaluator provenance | Absent in path |
| Brain integration/authority | Not located/open |
| Native tests | Not performed |
| DF-02 | OPEN |

LearningLoop/EvolutionModel direct adoption remains **OPEN / NO AUTHORITY DECISION**. No source selected/adopted/retired/deleted; no DF-02 closure, Foundation clearance or Stage A authorization.
