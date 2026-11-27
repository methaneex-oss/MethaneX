# DF-02 Brain Journal Replay, Outcome-Validation and Derived-Learning Adjudication — 2026-11-27

**Scope:** frozen candidate/donor `brain.cpp` replay/outcome path, deep test suite and donor-only action-consequence/affective integration suites. This is a bounded semantic audit, not closure of all 35 Brain source variants.  
**Candidate:** PR #192 frozen SHA `caf87986dfea7aca75728818651c8687e9f5faf0`. **Donor:** PR #97 `c1da222e6c94aeb3f2ad000392c21fe4fc81ab25`.  
**Disposition:** donor materially improves prediction identity, validation-before-mutation, replay consistency and derived affective source binding. One trust gap remains: action consequence error is finite-checked but not recomputed against expected/actual values. Source/test inspection only; no tests executed.

## 1. Exact refs and evidence

- Candidate `brain.cpp`: `e9f3758fcc9c0e89b7280ce376db9033d547682d` (218 lines in artifact).
- Donor `brain.cpp`: `dec9e5442b3ca4b81a7879855c6146b2619934cc` (888 lines).
- Candidate deep suite: `ca8e7012c92822608c3be0539784d281b0578bfd` (181 lines).
- Donor deep suite: `1314123ea3b524b24fd6693fc6fb4873b6c550d5` (834 lines).
- Donor action-consequence integration suite: `7616082579d53e3579cae8e87895bdb3dadba66f` (316 lines; no candidate path).
- Donor affective decision suite: `9ff9c0480fa34fa4f5600e514af419b2bbc79765` (76 lines; no candidate path).

The existing Brain lineage report inventories 35 `brain.cpp` blobs; this report does not claim all 35 were fully semantically closed.

## 2. Candidate/donor replay contract delta

Candidate replay uses prediction map keyed by prediction name and resolves prediction outcomes by key. Reusing a prediction key can overwrite prior prediction state and makes sequence-specific resolution ambiguous. Candidate replay also lacks donor's pre-mutation event validation and action-outcome/derived-affective source checks.

Donor uses sequence-bearing prediction records and:
- validates prediction outcomes against an unresolved prediction, key and optional exact creation sequence before affective or learning subsystems mutate;
- validates error-model version and recomputed numeric/binary prediction error;
- rejects duplicate/resolved or mismatched feedback;
- validates action-outcome shape/numeric metadata before affective appraisal, attention or strategy-learning handlers;
- binds derived `affective_learning` records to an authoritative source action-outcome event by sequence, observed consequence and matching expected/actual/error fields;
- persists external-observation and novelty metadata so replay can reproduce live affective processing;
- consolidates outcome evidence with explicit evidence confidence separated from execution reliability;
- reconstructs prediction, association, developmental, affective and attention state from journal events.

The donor deep suite source includes duplicate-derived-source protection, replay equality for affect/calibration/attention, persistence-driven action choice, contextual action outcome learning, prediction sequence feedback, and state reconstruction. Donor action-consequence integration asserts expected/actual/error, prediction sequence/key, verified execution, learning, non-observed outcome neutrality/uncertainty, partial verification failure with observed consequence, and restored decision/learning state. These are behavioral assertions, not test execution evidence.

## 3. Concrete trust gap — action consequence error consistency

Donor `valid_action_outcome_event` checks action/context identity, execution-status enum, finite expected/actual/consequence-error fields, unit-range metadata and observed-flag type. When `observed=true`, it requires actual consequence and consequence error. However, it **does not recompute or validate that the stored consequence error is consistent with expected and actual consequence** (the tests use `actual - expected`, e.g. 0.8 to -0.2 yields -1.0).

A persisted/publicly observed event can therefore contain finite but mutually inconsistent values (for example, expected=0.8, actual=-0.2, consequence_error=0.0) and pass this validator. Affective processing consumes the error as prediction error and the consequence as utility; downstream learning may consume the same event. Derived affective records are source-bound to the original fields, but that only preserves the inconsistency—it does not independently validate the calculation.

This is a source-derived integrity risk; a deterministic rejection test is missing in the inspected donor suites. Do not claim outcome events are fully authenticated/semantically validated until a rule is defined (including scale/normalization and legacy event versions) and enforced.

## 4. Additional replay/learning boundaries

- Prediction-outcome validation is materially stronger: current error model v2 requires exact recomputed error, with an explicit narrow legacy allowance for Brain-authored binary mismatch records. Numeric errors are normalized by a max scale.
- Derived affective-learning source binding prevents a record from pointing at an unrelated or unobserved action consequence and checks copied source values. This is integrity linkage, not cryptographic authenticity.
- External-observation and novelty are persisted for deterministic replay, which reduces live/replay drift.
- Invalid events are rejected by live `observe` before append, but replay sets `state_.cycle` to max event sequence before validation. Invalid historic records can advance cycle metadata even when downstream mutation is rejected; impact and quarantine semantics are not tested.
- Journal replay reconstructs state in a single process on object creation; it does not establish crash-safe atomicity, torn-write recovery, fsync durability or concurrent writer safety.

## 5. Five review lenses

1. **Semantic:** prediction sequence/validation and derived-source binding are confirmed; action-consequence error consistency is missing.
2. **Build/test:** donor deep and action-consequence test sources inspected; no native build/CTest.
3. **Trust/authority:** validation-before-mutation reduces malformed-event influence, but a finite yet inconsistent outcome can still affect learning; event provenance linkage is not authentication.
4. **Cognition:** replay preserves learning/affect/action-choice behavior in fixture tests; does not prove generalization or autonomous cognition.
5. **Hostile review:** donor improvements and trust gap both recorded; 35-version source cohort not closed; no selection or acceptance.

## 6. Open obligations / disposition

| Item | State |
|---|---|
| Candidate/donor replay source comparison | Complete for bounded functions |
| Donor prediction-outcome validation | Source inspected |
| Derived affective source linkage | Source inspected |
| Action consequence error recomputation | Gap identified; regression test open |
| Invalid historic event/cycle metadata behavior | Open |
| Full 35-blob semantic/owner/consumer ledger | Open |
| Native build/tests | Not executed |
| DF-02 | OPEN |

`core/cpp/src/brain.cpp` remains **OPEN / NO AUTHORITY DECISION**. No source selected, adopted, retired or deleted; no DF-02 closure, Foundation clearance or Stage A authorization.
