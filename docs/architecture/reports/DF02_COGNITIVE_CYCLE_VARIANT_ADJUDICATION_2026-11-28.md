# DF-02 Cognitive Cycle Context, Perception and Learning Variant Adjudication — 2026-11-28

**Scope:** exact candidate/donor cognitive_cycle.hpp/.cpp, main cycle test, stress test and test-CMake comparison.
**Candidate:** caf87986dfea7aca75728818651c8687e9f5faf0.
**Donor:** c1da222e6c94aeb3f2ad000392c21fe4fc81ab25.
**Disposition:** significant cycle semantics and evidence integration changes identified; source review only, no test execution.

## 1. Exact file identities

| File | Candidate | Donor |
|---|---|---|
| include/jarvis/core/cognitive_cycle.hpp | 28e7af98327956268a769adf7813125be842c1a2 | eed8bc75f59557c255e796343d77498d90b31ea5 |
| src/cognitive_cycle.cpp | 3df14c552f2048b0394dc362f7ee7a654a93fb32 | f191dd610d6cbe1621756c35e7c13af2054a7266 |
| tests/cognitive_cycle_suite.cpp | 38ff2c7d6e851b4745e9dc7c01f968b7245400a2 | 3e762cdec8b27030cf94478a1a68a4605a38c8c5 |
| tests/cognitive_cycle_stress_suite.cpp | b1f73ca14ac7a82eb4054b88c6f75f997eb6d9f3 | same blob |
| tests/CMakeLists.txt | dab0c52ab4dfe15e1e2cbccfa9e6c904abdf54e3 | cbfd1fde52fffa6eeac025da2b7ddcb5ab493261 |

## 2. Candidate cycle semantics

Candidate's bounded cycle is caller-directed:
1. Validate planning horizon.
2. Commit the observation to Brain.
3. Retrieve memory using observation attributes.
4. Snapshot beliefs/causal links and run reasoning.
5. Simulate causal predictions and persist cycle-scoped prediction keys.
6. Select explicit goal or first eligible goal.
7. Plan supplied actions, decide, assess action constraints, reflect.

The reasoning result is a side-result: simulation uses current beliefs rather than reasoning conclusions. Goal choice without an explicit goal is list-order fallback. Candidate context contains no structured perceptual representation, affective/appraisal/attention snapshots, or action-execution results. Outcome feedback only resolves a prediction by key and/or learns generic evidence; it does not assimilate goal outcome, sequence-bound prediction identity, or signed utility.

## 3. Donor changes

Donor introduces several connected mechanisms:

- **Perception pipeline and structured representation:** providers run after the observation has been durably committed, receiving the assigned sequence. Representation confidence and extracted features are captured in cycle context.
- **Memory before observation:** recall happens before appending the current event, preventing self-recall from masquerading as prior experience. Retrieval adds action-specific outcome records and perceptual cues, bounded per action/provider cue but not by a single global limit.
- **Forecast resolution:** captures unresolved predictions made since the prior observation and resolves only when a same-key belief has updated at the committed current observation sequence and the value type matches. Action-consequence predictions are excluded from this path, avoiding fabricated outcomes for unexecuted actions.
- **Reasoning integration:** when reasoning is valid and produces conclusions, simulation uses those conclusions; otherwise it falls back to observed beliefs rather than empty premises. This gives derived conclusions a path into predictions.
- **Uncertainty integration:** average prediction uncertainty, reflection uncertainty, belief/world disputes, attended uncertainty and representation confidence are combined via a maximum, avoiding a few forms of double counting. Low-confidence/featureless perception increases decision uncertainty.
- **Intent-driven goal selection:** if no explicit goal is supplied, the cycle tries the Brain's current intent among eligible goals, then uses list order. Explicit caller goal remains authoritative.
- **Reliability-informed action scoring:** executor reliability or capability performance modifies utility/expected value and bounded risk. Isolated/unavailable capabilities are removed from candidate actions.
- **Contextual developmental learning:** derives a hierarchical situation context from observation kind/source, sorted feature schema and value descriptors. Numeric descriptors use logarithmic magnitude bands; slash and percent characters are escaped, and reserved “values” segment handling prevents parser ambiguity. Caller context overrides inference. Exact-context outcome evidence calibrates expected consequence; direct strategy dominates transfer, related strategy is bounded, episodic fallback weaker; exploration bonus is bounded and reduced by local evidence.
- **Affective planning:** appraisal-weighted valence, arousal, uncertainty, tension and stability enter PlanningContext. The exact developmental context is copied into assessments for later execution/outcome learning.

This is a materially more connected cognition loop than the candidate, but all inputs remain externally submitted; providers and adapters are integrations, not autonomous sensors or actuators.

## 4. Test contract and reachability

The candidate main cycle test covers goal selection, plan/decision/action assessment consistency, action constraints, prediction outcome resolution, evidence learning, invalid goal, and duplicate feedback. Candidate stress suite and donor stress suite are byte-identical: 256 sequential cycles and journal/event checks.

Donor main test adds focused scenarios for:
- observation representation and durable-sequence provenance;
- provider-extracted semantic cues in recall;
- memory-before-observation and action-outcome retrieval;
- prediction forecasts resolving from later same-variable observations;
- reasoning conclusions feeding simulation;
- dispute/confidence impact on planning;
- intent selection, affect/appraisal and capability exclusion;
- executor reliability, action consequence learning and persistence;
- context inference, delimiter/segment handling, explicit override, featureless observations;
- exact-context and related-context strategy transfer, exploration and expectation calibration;
- goal outcome assimilation and prediction feedback identity/utility.

The donor CMake registration adds/changes suite targets; the stress test remains the same. These are test-source and registration observations only. No native compile/CTest was executed.

## 5. Review findings / remaining adversarial obligations

- **Inferred context determinism:** feature descriptors are sorted by label, but equal labels are not tie-broken by value; duplicate-label representations could produce unstable context ordering. Validate unique labels or sort by stable encoded label/value.
- **Context size/abuse:** provider-derived labels and values become persisted hierarchical keys; encoding avoids delimiter collision but has no demonstrated size cap, normalization policy, or privacy/sensitive-feature policy.
- **Retrieval budget:** recall limit is applied per candidate action and each representation cue, then merged. Total memory retrieval can grow with action count/provider node count; input and provider complexity need bounds.
- **Forecast matching:** same-key/type/current-sequence checks reduce false resolution, but duplicate keys, type changes, concurrent observation cycles and multiple Brain callers require concurrency/identity tests.
- **Evidence quality:** consequence values and reliability are clamped/filtered for planning, but journaled action outcomes may originate from caller-controlled evidence. Trust/source provenance and replay validation are cross-file obligations.
- **Transfer validity:** hierarchical contexts are heuristics; similarity transfer can be semantically wrong even when encoding is collision-free. Negative/positive experience, source confidence, context leakage and false transfer require controlled matched tests.
- **Reliability calibration:** executor/capability reliability has a nonzero floor and affects score/risk; calibration quality, recovery from transient failures and whether reliability represents capability vs executor need separate metrics.
- **Goal/intent consistency:** intent is selected using internal goal/threat/uncertainty state. Explicit goal remains the caller's choice; implicit intent can still be stale or context-insensitive.
- **World disagreement:** dispute pressure is a bounded count ratio, not evidence-weighted severity; fact/relation counting may correlate or double-count. This is a heuristic, not calibrated epistemic uncertainty.
- **External action boundary:** assessment is not authorization. Runtime action executor and adapters govern execution; cycle alone cannot prove actions safe, cancellable or idempotent.
- **Learning loop integration:** cycle-level learning modifies decision inputs, but no independent matched no-learning/learning benchmark or acceptance threshold was run. Existing test assertions are not empirical performance proof.

## 6. Five lenses and disposition

1. **Semantic:** donor integrates perception, evidence, memory, reasoning, prediction, affect, attention, context transfer, capability reliability and action assessment into planning. Candidate does not.
2. **Build/test:** exact CMake/test changes and identical stress-test blob established; execution unavailable.
3. **Trust:** provider outputs and feedback/outcome traces remain external evidence; source authenticity, size limits and replay integrity are broader contracts.
4. **Capability:** cycle is a structured cognition pipeline for a supplied observation, action set and goal context. It is not autonomous open-ended goal generation or independent real-world sensing.
5. **Hostile:** the donor's feature richness is not acceptance. Heuristic context transfer, reliability calibration, uncertainty aggregation, resource bounds and concurrency remain unproven.

| Obligation | State |
|---|---|
| Exact candidate/donor cycle/header comparison | Completed for bounded files |
| Main/stress test source comparison | Completed |
| CMake registration comparison | Completed |
| Inferred-context collision/determinism tests | Open |
| Memory/perception retrieval bound | Open |
| Prediction resolution concurrency and identity | Open |
| Transfer/calibration matched performance evaluation | Open |
| Native build/CTest | Not run |
| Full consumer/provenance/authority/retention closure | Open |
| DF-02 | OPEN |

**Disposition:** cognitive-cycle cohort source-adjudicated, not semantically or authority closed. No donor selection/adoption, alternate retirement, runtime modification, Stage A, baseline or gate authorization.
