# DF-02 Knowledge, Adaptation, Representation and Reflection Adjudication — 2026-11-27

**Scope:** candidate/donor source for knowledge, adaptation, representation and reflection; exact donor test contracts; historical alternate knowledge-model implementations.  
**Candidate:** PR #192 frozen SHA `caf87986dfea7aca75728818651c8687e9f5faf0`. **Donor:** PR #97 `c1da222e6c94aeb3f2ad000392c21fe4fc81ab25`.  
**Disposition:** donor improves numeric adaptation, deterministic representation identity, metadata filtering/validation and reflection evidence accounting. Frozen KnowledgeModel remains simple; advanced historical feedback variants are not selected/integrated. Source/test inspection only.

## 1. Exact refs

| Component | Candidate SHA | Donor SHA |
|---|---|---|
| `knowledge.cpp` | `25ecf822e6132f576266c1f86a964a227c7fb75f` | `21de8abbcd4426cb4ead70cb089e7d7c4ed0e81a` |
| `adaptation.cpp` | `7e07a491a5b13379a5719882a834ecc2452a54ef` | `51b91a52c20f71a1be462f660c45bee9199259c3` |
| `reflection.cpp` | `06f34e20f35aad535a2c606b3669b2127ef7a480` | `fe7dd1fada300300673b90caffa128384c65bde1` |
| `representation.cpp` | `0e53bfaa0c1114cb7390d9f7ce577c87d6bc6169` | `054bd9ecee3ef3da83dd405dc5785464d874fa21` |

Donor tests: knowledge-memory `e33b9813edbfaf02a91a3f94988f5c7a54ceed8f`, adaptation phase-8 `59859480a6d09aaab70eaf09ffc94c731484d2ff`, representation `07c515018eca0f34f496e85608f504620fd07306`. Candidate tests: `f796977fd116418b3cf0a5f9c8d33ed7a48f811e`, `79cb7b8146686b35273628de213d33edd4328cff`, `1ee7663934f067de4fdd31832719b06274ae6171`.

## 2. Source behavior

- **Knowledge:** frozen candidate/donor implementation is a simple source registration/lookup/assimilation model; donor changes the evidence type but not a source-trust calibration mechanism. The artifact contains richer historical variants (feedback, reliability, contradiction/source calibration, sequence provenance), but those variants are not the frozen donor implementation. Do not claim that all source-feedback behavior is integrated based on historical blobs or API names.
- **Adaptation:** donor accepts real-valued prediction/actual instead of clamping both to [0,1]; normalized absolute error, first-observation level initialization, long-term and recent error, surprise streak and recency-sensitive update. It supports numeric metrics and bounded confidence, with nonfinite inputs ignored.
- **Representation:** donor replaces `std::hash`-based IDs with deterministic sequence+length+key identity; extracts event confidence; excludes appraisal metadata from semantic features while retaining metadata; metadata-only events have confidence 0; validates finite confidence on representation/nodes/evidence/relations.
- **Reflection:** donor includes disputed-belief pressure separately from belief confidence, empty belief state as uncertainty=1, affective calibration/learning-pressure/observation inputs, and coherence averaged only across dimensions with actual evidence. Empty evidence gives coherence 0 rather than a claim of competence.

## 3. Source-derived limits

- **Global adaptation metric:** metric is keyed only by variable/prediction key, not context. Numeric adaptation can transfer across distinct contexts; contextual prediction report also records this risk.
- **Surprise-streak policy:** update rate accelerates after three/four consecutive large normalized errors; it is a heuristic change-response policy. Thresholds/rates are fixed and not calibrated on distribution shift.
- **Knowledge trust:** richer historical KnowledgeModel alternatives have feedback/reliability/calibration features, but frozen candidate/donor source does not include those methods. Integration/authority of the alternates remains open.
- **Reflection:** coherence is an arithmetic evidence average, not calibrated cognitive reliability. Affective calibration and learning-pressure are supplied signals and depend on their provenance.
- **Representation:** deterministic identity removes hash instability, but event key/value feature extraction is not semantic understanding; metadata exclusion list is a fixed schema, and unknown appraisal fields can become features unless added to the exclusion list.

## 4. Test evidence

Knowledge-memory tests assert source registration, evidence assimilation, retrieval and persistence. Adaptation phase-8 tests exercise bounded metric updates, numeric-scale handling, confidence, recent-error/surprise behavior and reconstruction. Representation tests assert deterministic IDs, confidence/metadata separation, validation and replay. Tests were inspected, not executed.

Gaps: context-separated adaptation, adversarial distribution shift, unknown metadata contamination, ID collision edge cases, source trust calibration/feedback integration, reflection calibration and long-term state stability. Full test mapping across Brain integration suites remains incomplete.

## 5. Five review lenses

1. **Semantics:** numeric adaptation and representation/reflection changes confirmed.
2. **Build/test:** donor suites inspected; no native build/CTest.
3. **Integrity:** deterministic IDs/finite validation improve integrity; context-global metric and metadata schema remain risks.
4. **Cognition:** reflection and adaptation are measurable heuristics; not proof of calibrated self-assessment or semantic knowledge.
5. **Hostile review:** historical KnowledgeModel variants are not treated as adopted donor code; capability claims scoped to frozen source.

## 6. Open obligations / disposition

| Item | State |
|---|---|
| Candidate/donor four source files | Compared |
| Donor three test suites | Inspected |
| Historical KnowledgeModel variants | Inventory evidence; not integrated |
| Context-global adaptation transfer | Open |
| Source trust/feedback integration | Open |
| Reflection calibration/long-term tests | Open |
| Native tests | Not executed |
| Full consumer/authority/retention | Open |
| DF-02 | OPEN |

Knowledge/adaptation/representation/reflection remain **OPEN / NO AUTHORITY DECISION**. No source selected/adopted/retired/deleted; no DF-02 closure, Foundation clearance or Stage A authorization.
