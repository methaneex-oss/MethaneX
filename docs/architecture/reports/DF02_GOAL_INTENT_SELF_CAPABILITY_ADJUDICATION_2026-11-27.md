# DF-02 Goal Lifecycle, Intent Selection and Self-Capability Model Adjudication — 2026-11-27

**Scope:** exact candidate/donor goals, intent and self-model source; donor goal architecture/outcome and goal-directed cognition tests.  
**Candidate:** PR #192 frozen SHA `caf87986dfea7aca75728818651c8687e9f5faf0`. **Donor:** PR #97 `c1da222e6c94aeb3f2ad000392c21fe4fc81ab25`.  
**Disposition:** donor adds progress momentum/deadline appraisal, affective intent modulation and capability availability/performance/isolation separation. Source/test inspection only.

## 1. Exact source refs

- `goals.cpp`: candidate `778a829de8314e83b095af2f2c2a6b83baa769f4`; donor `afaedcfb0f2f68ff88b3a20e474fce04bb59815c`.
- `intent.cpp`: candidate `4283a4255284c51257df6bad12734782f2a6cde9`; donor `9707d5b6da4ddede4dfc99d52f30e7cdc7eed032`.
- `self_model.cpp`: candidate `3c6a375eadd6894a635d2e18023a7079cba97c86`; donor `c1beeec968fa62fce8fb037f8b95a869031331ce`; alternate `754bd30f73fe974f0d417bd039f0362882cfccc5`.
- Donor goals architecture test `0b99d090b400d0af50b186cd3a416fa28a177b99`; candidate `14a52aa606b53f8529aa5c54861c11902deb7c97`.
- Donor goal-outcome test `c9f19978d6d2df45028cb824e835144dc45c70e7`.
- Donor goal-directed cognition test `7fe6cf6c4dd2dc2a54bb9f48fcdd3c3d91d7c282`; alternate `1ae2ac06eaa860f82a77244f3f3fbe41027268d4`.

## 2. Goal/intent behavior

Donor goal model validates ID/description, finite priority and progress bounds; supports prerequisites, activation, progress, completion/abandonment, deadlines and deterministic priority/creation-cycle ordering. Progress change updates a separate outcome-momentum EMA and immediately adapts priority from signed progress delta, preventing lagging positive momentum from masking a new regression.

Intent selects only active goals; it scores priority, progress need, momentum and deadline pressure, then derives urgency/uncertainty/confidence. Affective intent selection modulates an already selected objective; affect cannot create a goal.

## 3. Self-model behavior

Donor separates capability availability, performance and isolation. Observation updates availability/performance; performance evidence uses a bounded EMA and does not change availability/isolation. Isolation sets availability to zero; restore explicitly clears isolation and sets both dimensions. Health is the arithmetic mean of capability availability and performance, combined multiplicatively.

This is an operational capability ledger, not a validated self-knowledge model: no uncertainty/variance or evidence provenance is maintained in this API.

## 4. Source-derived gaps

- **Goal prerequisite cycles/self-dependency:** create validates goal scalar fields but not prerequisite graph existence, self-dependency or cycles. Cyclic goals can remain permanently ineligible; no cycle detection/regression test found.
- **Completion bypass:** `update_progress`/ `complete` do not require goal status Active or prerequisites satisfied. Pending goals can be completed directly, potentially bypassing dependency lifecycle. This may be intentional for externally observed completion, but must be reconciled with prerequisite policy.
- **Intent input validation:** threat/uncertainty/affective inputs are clamped without explicit finite guard; NaN may propagate. Active-goal tie selection is first-in-input order.
- **SelfModel input validation:** `observe_capability`, `update_performance` and `restore` use `std::clamp` without finite guards; NaN can contaminate capability state/health. Empty capability names are accepted by `observe_capability`.
- **Health semantics:** isolated/unavailable capabilities still contribute their performance to the arithmetic mean; this may misrepresent usable capability health. No explicit weighting by criticality or evidence confidence.

## 5. Test evidence

Donor goal architecture tests cover prerequisites, lifecycle, priority/progress, deadline eligibility and persistence. Goal-outcome tests cover completion feedback/affective changes. Goal-directed cognition suite checks goal-driven intent/action choice. No dedicated donor SelfModel suite was located in this exact path search; Brain/capability integration coverage is separate.

Tests were inspected, not executed. Gaps: prerequisite cycles, pending completion without activation, deadline boundary, NaN/Inf intent/self-model inputs, empty capability names, isolated-health aggregation and tie-order invariance.

## 6. Five review lenses

1. **Semantics:** goal lifecycle/momentum, affective intent, capability availability/performance separation compared.
2. **Build/test:** donor goal test source inspected; direct SelfModel test mapping incomplete; no native execution.
3. **Integrity:** graph lifecycle and numerical input gaps remain.
4. **Cognition:** goals and intent are caller-created/active objectives; no autonomous open-ended goal discovery established.
5. **Hostile review:** operational self-model not described as calibrated self-awareness; source/test limitations explicit.

## 7. Open obligations / disposition

| Item | State |
|---|---|
| Candidate/donor goals/intent/self-model sources | Compared |
| Goal architecture/outcome test contracts | Inspected |
| Goal cycle/completion gate | Gap/contract open |
| Intent/self-model nonfinite validation | Gap |
| SelfModel test coverage | Mapping incomplete |
| Full consumer/authority/retention | Open |
| Native tests | Not performed |
| DF-02 | OPEN |

Goal/intent/self-model remain **OPEN / NO AUTHORITY DECISION**. No source selected/adopted/retired/deleted; no DF-02 closure, Foundation clearance or Stage A authorization.
