# DF-02 Restored Brain API Ownership and Variant Adjudication — 2026-11-27

**Scope:** exact candidate/donor and 18 historical alternate blobs for `core/cpp/src/brain_restored_api.cpp`; cross-check against frozen `brain.cpp`, public `brain.hpp`, and core CMake registration.  
**Candidate:** PR #192 frozen SHA `caf87986dfea7aca75728818651c8687e9f5faf0`.  
**Donor:** PR #97 frozen HEAD `c1da222e6c94aeb3f2ad000392c21fe4fc81ab25`.  
**Disposition:** API-surface, duplicate-definition and build-owner differences are established for this cohort; semantic/authority disposition remains OPEN. No tests run.

## 1. Exact blob and owner inventory

The hash-verified discovery artifact records 20 distinct blobs for this path (candidate, donor, 18 alternates). All exact contents are present in `consumer_blob_sources.jsonl`. The complete branch/tip ownership data is in the artifact `path_blob_ownership.csv`; this report records SHA, role and tip count to avoid implying that branch multiplicity equals independent implementation.

| Blob SHA | Role | Tip count | Representative owner branch |
|---|---|---:|---|
| `00d69ab2eb3811d453a643ef18dc69741109cbc8` | Alternate | 15 | docs/brain-constitution-planning-readiness-20261031 |
| `0d0863bb1bc5dda64850734cbd2ef5d8415991b8` | Alternate | 13 | fix/evolution-authenticated-replay-20261029 |
| `1dab3407183a60c4f84622af44b2e4140d72f6ca` | Alternate | 3 | feat/prediction-developmental-validation-20261030 |
| `2338ed21629dbe3356dc5a7c1dbbacb1ca707a85` | Alternate | 1 | fix/evolution-lifecycle-review-20261029 |
| `2a49f2aad3a99e74316a068801e3f0f90bf69bad` | Alternate | 1 | integration/knowledge-composition-20261031 |
| `2df0bd3ed3b0b5958c5f0fe9ac2fe9405999ae9c` | Alternate | 1 | fix/evolution-replay-attestation-20261029 |
| `36b534fd8bf68e038cfe59bbbf37200d031b3f3b` | Alternate | 19 | feat/dlt-002-adaptive-trial |
| `38a8d558184e5b67d182002d00fe5ec17b011abb` | Alternate | 1 | fix/causal-key-value-codec-20261028 |
| `3a64cc46a5d8ad08c2064dfc4558809f13b5287f` | Alternate | 1 | ci/priority-one-provenance-validation-20261031 |
| `3a9295be7bfd240585577f7962e16de4c770b655` | Alternate | 2 | ci/priority-one-validation-20261031 |
| `618deb6976eed951eae02b7f0da741e6d730bb0c` | Candidate | 40 | architecture/brain-foundation-planning-20261103 |
| `630d6c7f651d4f11cdfa3d8b4779e6b0df519737` | Alternate | 1 | fix/evolution-replay-evidence-20261031 |
| `673f345a8adfa496503541a792ceca3b19f03651` | Alternate | 1 | feat/source-feedback-journal |
| `7155d4d9c8eef527836fb79bf901aa32ddbae38b` | Donor | 9 | feat/jarvis-affective-state |
| `72aeea8ced9402fc6ada130cc8c16ef5f8b29f21` | Alternate | 2 | fix/evolution-evaluation-lifecycle-ci-20261029 |
| `7a5af222407ce1e5d27e1f985500815ea761485b` | Alternate | 1 | fix/evolution-evaluation-lifecycle-20261029 |
| `85c2a877a3c1f5c1484e2ece95ad7f650ced8ac8` | Alternate | 1 | fix/learning-layer-review-20261028 |
| `a847ab60454631242f827ac2172c8e6fc0376d55` | Alternate | 2 | fix/learning-contradiction-resolution-after-dlt003 |
| `b7bcea4a5b0b7678e6edb0e7ca6a259d18e86af2` | Alternate | 1 | fix/gate-a-d1-d2-20261104 |
| `dce980e0f6b30fdc32cd9d7bf12ef7717751a4a3` | Alternate | 1 | fix/evolution-trustworthy-lifecycle-20261029 |

The candidate/donor role blobs were fetched at the immutable refs. Candidate restored-API SHA: `618deb6976eed951eae02b7f0da741e6d730bb0c`; donor SHA: `7155d4d9c8eef527836fb79bf901aa32ddbae38b`. Branch names are provenance pointers only; authority and retention remain unresolved.

## 2. Method-surface comparison

A repeatable source-text extraction of method definitions beginning with `Brain::` produced these **unique method-name** counts:

| Exact blob | Unique names | Extracted definition signatures (overloads included) |
|---|---:|---:|
| Candidate restored API | 64 | 69 |
| Donor restored API | 68 | 74 |

Candidate API method-name set is a subset of donor API set in this extraction. Four donor-only names:
- `developmental_best_related_strategy`
- `developmental_related_strategies`
- `record_evolution_evaluation`
- `resolve_prediction_feedback`

The donor/candidate exact header blobs are respectively `671186f4c39879a182f9e511394fc564d86f2988` and `8268ef84e0b361ead536724ba7761904b30ee58f`. Donor header adds related declaration families (developmental learning, affective state/learning, contextual prediction and prediction feedback, goal-outcome evidence, evolution-evaluation recording) and changes memory exposure from mutable `Memory&` to const access. These are API/authority changes, not cosmetic additions.

Across all 20 restored-API blobs, 68 method names appear in every version. Version-specific surface variation is concentrated in:
- `developmental_best_related_strategy`, `developmental_related_strategies`, `record_evolution_evaluation`, `resolve_prediction_feedback`: present in 19/20 blobs (absent from candidate blob);
- `developmental_feature_strategy_estimate`: 4 blobs;
- `import_legacy_memory_event`: 5 blobs;
- `record_knowledge_source_feedback`: 6 blobs.

The extra method families are evidence of feature/API evolution; their names do not establish correctness, behavioral integration, or acceptance. The 18 alternates include several distinct content groups, not one monotonically ordered successor.

## 3. Declaration/definition and compiled ownership

Exact candidate and donor source files show a materially different split:

- Candidate `brain.cpp` blob `e9f3758fcc9c0e89b7280ce376db9033d547682d` extracts 47 unique Brain method names. Candidate restored API has 64. The source-text extraction found 43 shared method names, leaving four candidate brain.cpp names not in the restored API (`learn`, `observe`, `replay`, `sync_self_state`) and 21 API names not found in candidate brain.cpp. The previously recorded 40-overlap count used a different extraction and is **not reconciled**; do not treat either count as a final AST/signature count until a compiler/AST-capable analysis resolves it.
- Candidate `core/cpp/CMakeLists.txt` blob `c51816888e1bddb7bc00c59e72529524e27a0717` registers `src/brain.cpp` but **does not register `src/brain_restored_api.cpp`**. Thus this API translation unit is not part of the frozen candidate library build. The overlapping definitions are dormant in that graph; adding the file naïvely risks duplicate definitions and unresolved/incompatible declarations.
- Donor `brain.cpp` blob `dec9e5442b3ca4b81a7879855c6146b2619934cc` extracts eight method names; donor restored API has 68. The extracted method-name sets have zero overlap: the split is deliberately clean in the donor content. Donor `core/cpp/CMakeLists.txt` registers both translation units.
- This path's public declaration, source definition and CMake registration must be treated as one ownership unit. It cannot be accepted based on the API file alone.

## 4. Historical version clusters and authority limits

Exact-content feature counts show that variants add/remove developmental related-strategy methods, feature-strategy estimates, legacy memory import and knowledge-source feedback. The owner metadata links blobs to evolution trust/replay, causal codec, DLT adaptive-trial, source-feedback, learning-contradiction, knowledge-composition and planning branches. These are cross-workstream changes: a method surface can be coupled to memory schema, replay, feedback identity or learning semantics.

No branch owner or branch label proves:
- which declarations are the approved interface;
- which implementation is the semantic successor;
- whether callers are compiled, runtime, test-only or historical;
- whether a feature is duplicated in another component;
- whether the branch can be retained, adopted, retired or deleted.

The full 20-blob content and ownership index is grounded in the discovery artifact. A full exact-signature/AST declaration-definition graph and per-tip authority/provenance/retention review are still required.

## 5. Build/test and consumer evidence

Candidate CMake excludes the restored API source. Donor CMake includes it. This is direct compiled-ownership evidence. The candidate/donor build graph comparison and CMake variant cohort are documented in the full DF-02 audit.

No test was run in this slice. Existing API/integration test source and CMake registration can show references and compile reachability, but they do not establish runtime behavior, ABI/API correctness, or complete call-site closure. The lexical consumer matches in the frozen artifact remain candidate-discovery data until exact context is classified.

## 6. Five review lenses

1. **Semantic/API:** exact method-surface divergence and cross-workstream additions mapped; behavior of all 18 alternates not fully traced.
2. **Build:** candidate orphan source versus donor integrated split confirmed by exact CMake blobs; no native compilation/test execution in this slice.
3. **Trust/authority:** direct mutable memory exposure, evaluation-feedback, replay and legacy-import methods may change authority/persistence semantics; API names alone are insufficient.
4. **Cognitive capability:** richer prediction feedback, contextual/developmental/affective APIs are mechanisms, not evidence of coupled learning or useful adaptive behavior.
5. **Hostile review:** the prior 40-overlap count is disclosed as unresolved against the new extraction (43 unique method names); no claim of AST-level closure or preferred implementation is made.

## 7. Disposition

| Item | State |
|---|---|
| 20 exact blobs inventoried | Complete for this slice |
| Candidate/donor method-name surface compared | Complete for extraction; AST/signature reconciliation open |
| Candidate orphaning and donor compiled split | Confirmed |
| 18 alternate semantic/owner groups | Partial |
| Reverse consumers and API compatibility | Open |
| Build/test behavior | Not executed |
| Provenance, authority and retention | Open |
| DF-02 | OPEN |

**Disposition:** `core/cpp/src/brain_restored_api.cpp` remains **OPEN / NO AUTHORITY DECISION**. No source selected, adopted, retired or deleted. This report does not close DF-02, Foundation gates, or authorize Stage A.
