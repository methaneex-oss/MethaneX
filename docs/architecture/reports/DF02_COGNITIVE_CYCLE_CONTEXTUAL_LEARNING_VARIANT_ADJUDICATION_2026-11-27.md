# DF-02 Cognitive Cycle Semantic and Contextual-Learning Variant Adjudication — 2026-11-27

**Scope:** ten exact `core/cpp/src/cognitive_cycle.cpp` blobs, candidate/donor header and seven test blobs.  
**Candidate:** PR #192 frozen SHA `caf87986dfea7aca75728818651c8687e9f5faf0`. **Donor:** PR #97 `c1da222e6c94aeb3f2ad000392c21fe4fc81ab25`.  
**Disposition:** substantial context-sensitive action-evaluation/outcome-feedback delta confirmed. Source/test inspection only; tests not executed. Path remains OPEN.

## Exact inventory

Candidate source `3df14c552f2048b0394dc362f7ee7a654a93fb32` (125 tips, 161 lines); donor `f191dd610d6cbe1621756c35e7c13af2054a7266` (38 tips, 776 lines). Eight alternate source blobs:
- `989f4d154f07b31bcdab175aefbea6edd61eb930` (19 tips, CI priority validation)
- `28396e875f627fd98c191415b12eae744a753b87` (11, causal-key/value codec)
- `2bff7eebe0905afbf2556833de189fee2da15b42` (6, DLT behavioral-change evidence)
- `a96684a85e8d0a11be6861834db040375d8cf467` (9, action-execution feedback)
- `67bf9dcaf0ff0f85f2cc095783a209d92b42436f` (1, affective planning)
- `8d0e1659846fa0b1cfd9ca9c70d073fdf5b2d259` (1, action assessment)
- `fbc86fe0e86f817dd3c4053678b079bf8704725b` (1, adaptive trial)
- `198cc7919092b9e84f42a363392a1012e029dbdb` (1, evolving-world challenge)

Candidate header `28e7af98327956268a769adf7813125be842c1a2` (104 tips); donor header `eed8bc75f59557c255e796343d77498d90b31ea5` (76 tips). Candidate test `38ff2c7d6e851b4745e9dc7c01f968b7245400a2` (134 tips, 97 lines); donor test `3e762cdec8b27030cf94478a1a68a4605a38c8c5` (57 tips, 787 lines). Blob sightings/branch labels are provenance, not authority or semantic ancestry.

## Candidate/donor semantic difference

Candidate cycle is caller-driven: retrieve memory, record/represent the supplied observation, update Brain state, select an eligible goal, reason/plan from supplied candidate actions and constraints, decide and assess actions. It does not execute actions or autonomously acquire observations/goals.

Donor adds:
- collision-resistant inferred developmental context from observation kind/source and representation feature labels/values, unless caller supplies explicit context;
- exact-context outcome recall plus action-level memory retrieval, merged by event sequence;
- developmental strategy recall/transfer and episodic outcome fallback influence on candidate utility/expected value;
- exploration-pressure adjustment where local evidence is absent;
- affective state/appraisal inputs into planning/decision context;
- assessment records carrying the exact context for later outcome attribution;
- feedback processing for prediction resolution, evidence learning, goal-progress assimilation and affect/reflection state;
- prediction-sequence binding and explicit task utility, separate from prediction accuracy.

These are substantive behavior/API changes, not a refactor. They do not establish donor correctness or authority.

## Context encoding and collision evidence

Donor infers context from observation kind/source and sorted representation feature labels/values; numeric values use sign/log-magnitude bands. Featureless inputs fall back to observation identity plus goal rather than goal ID alone. Explicit context is passed through. Encoding escapes `/` and `%`; reserved structural segment `values` is escaped as `%76alues`.

Donor test assertions specifically cover:
- `north/south` not aliasing `north_south`;
- feature value `values` not being parsed as the structural `/values/` delimiter;
- feature label `values` escaping;
- legacy stored contexts and transfer behavior;
- numeric scale bands with stable feature schema;
- featureless observations from different source/kind remaining distinct;
- explicit context override.

Remaining edge cases include duplicate feature labels (sort comparator only uses label, so tie order is not explicitly stable), malformed/empty feature descriptors, and unbounded context length. No fuzz/adversarial tests were run.

## Action/outcome behavior and tests

Donor source retrieves action outcomes, filters observed consequence by action/context, weights evidence reliability, and uses episodic outcome only when direct/transferred strategy evidence is absent (avoids double-counting). It adjusts utility/expected value and exploration pressure, then applies affect-aware decision context.

The 787-line donor test suite asserts experience-dependent action-choice change, context-specific learning/no blind transfer, evidence weighting and persistence, goal outcome assimilation, prediction feedback, regime-change reversal, restart influencing a real decision, and a no-feedback control where successful execution alone does not create consequence-based preference. This is materially stronger than candidate's 97-line basic cognitive-cycle fixture.

Behavior remains synthetic: supplied observations/actions/context and callback adapters. The cycle assesses/plans; the runtime/action executor is the separate execution boundary. It is not evidence of autonomous sensing, goal discovery, real-device execution or unattended closed-loop behavior.

## Five review lenses

1. **Semantic:** context inference, escaping, episodic recall, strategy transfer, action scoring, affect and feedback deltas mapped; no equivalence claim.
2. **Build/test:** exact donor test source and header inspected; no native compilation/CTest executed here.
3. **Security/authority:** action assessment is separate from external execution authorization; outcome attribution relies on action/context/evidence; adapter and persistence trust remain open.
4. **Cognition:** test fixture demonstrates behavior change, context isolation, persistence and regime-change adaptation; it does not demonstrate general autonomous cognition.
5. **Hostile review:** collision tests credited; duplicate-feature ordering and execution evidence remain open; no source preference or acceptance inferred.

## Open obligations / disposition

| Item | State |
|---|---|
| 10 source blobs, 7 test blobs inventory | Complete for this slice |
| Candidate/donor semantic comparison | Complete for bounded slice |
| Context collision contract | Inspected; donor assertions present |
| Action-outcome contextual learning | Test contract inspected, not executed |
| Duplicate-feature ordering/adversarial context | Open |
| Reverse consumers/API/owner authority/retention | Open |
| Native build/CTest | Not executed in this slice |
| DF-02 | OPEN |

`core/cpp/src/cognitive_cycle.cpp` remains **OPEN / NO AUTHORITY DECISION**. No source selected, adopted, retired or deleted. No DF-02 closure, Foundation gate clearance, or Stage A authorization.
