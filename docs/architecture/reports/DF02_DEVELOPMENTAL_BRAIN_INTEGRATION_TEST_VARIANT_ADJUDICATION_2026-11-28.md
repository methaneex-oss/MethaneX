# DF-02 Developmental Brain Integration Test Variant Adjudication — 2026-11-28

**Scope:** candidate-absent developmental-learning production/header cohort and the donor-only developmental brain integration test family; exact branch-tip blob inventory, behavioral contract and CMake reachability.  
**Candidate:** PR #192 frozen SHA `caf87986dfea7aca75728818651c8687e9f5faf0`.  
**Donor:** PR #97 frozen HEAD `c1da222e6c94aeb3f2ad000392c21fe4fc81ab25`.  
**Disposition:** donor-only integration/test surface is evidenced; semantic and authority closure remain OPEN. Source inspection only, no tests run.

## 1. Exact blob cohort and lineage metadata

Discovery artifact #14956148301 was re-downloaded; archive SHA-256 was verified as `9902957475c76f4840d1d280c7d4f50537941e9445810afb805132374a328f38`. Path/blob owner records:

### Production source — 6 blobs, all absent from candidate

| Blob SHA | Tip count | Representative owner |
|---|---:|---|
| `b06634c7563dc2cb338008ba145073bc6a21bfd9` | 1 | feat/dlt-002-adaptive-trial |
| `bfe2db73a2722c421e6616d1caa20606f4f86098` | 17 | fix/causal-key-value-codec-20261028; fix/memory-journal-framing-20261028; other lineage branches |
| `c9a34d562fa1a20641530daba81bfdc1f3621fee` | 19 | ci/priority-one-validation-20261031; docs/brain-constitution-planning-readiness-20261031; others |
| `cf18d273dd67a85279bf6172a787752d29951995` | 1 | test/jbp-004-memory-learning-evolution-integration |
| `dbf5f43271dfa0a3c57236e2faa82eb88d15490d` | 38 | donor PR #97 HEAD and associated integration branches |
| `e9d98374e583b8afcf0674fe2c25d0d57ef3bc6f` | 1 | docs/jarvis-affective-plan / implementation-planning lineage |

### Integration test — 9 blobs, all absent from candidate

| Blob SHA | Tip count | Representative owner |
|---|---:|---|
| `123a4be6e548788c7ad130f99ff19d8b4945b884` | 1 | ci/priority-one-provenance-validation-20261031 |
| `543ae3210b5daa265c39114c5fc94902dda4f33f` | 1 | fix/gate-a-d1-d2-20261104 |
| `721a0991436b9f74e4dd320c58a9bc4069469e09` | 1 | affective planning/implementation branches |
| `760162dd6d1e669162e0bf22223a437491f5e262` | 32 | donor PR #97 HEAD and integration branches |
| `77697d65949d35e7e6c22779e89eb0313b0e2500` | 1 | feat/source-feedback-journal |
| `a98f24cbcf5f0164888161d66e4a13c02fbde8b5` | 21 | feat/dlt-002-adaptive-trial and memory/learning lineage |
| `b9dc34b63f7ca0b356a5a2589c39fb8b5862d2f6` | 1 | fix/evolution-replay-evidence-20261031 |
| `e6eba3db6df8da9ecfed21974936908a32ea11c5` | 18 | docs/brain-constitution-planning-readiness-20261031 and integration branches |
| `fbf0155750d1c23b4ac2f8f5d63408a8342b508e` | 1 | fix/learning-contradiction-resolution-20261030 |

### Public header — 4 blobs, candidate absent

- `070d82a187aff0b261578ac88605bcdfc795f343` — one tip, affective plan lineage.
- `65174400d8c3ce1dea17667ac928767cf3af333a` — 19 tips, planning/validation branches.
- `6bc9ace700e789371528dcaf5b643925af8e5125` — one tip, JBP-004 persistence integration branch.
- `e3b9bf8af265b67829fd7deb323d88a3a9dd4b75` — 56 tips, donor PR #97 and related integration.

Branch-tip metadata is provenance evidence only. It does not establish authority, semantic parentage or acceptance. The donor test blob and source/header contents were fetched at exact SHA from Git blob endpoints.

## 2. Build and integration ownership

Frozen candidate CMake has no developmental-learning source, header, or integration suite. Donor CMake registers:
- `src/developmental_learning.cpp` into `jarvis_core`;
- `jarvis_developmental_learning_suite`;
- `jarvis_developmental_brain_integration_suite`.

Candidate therefore has no same-path production implementation or integrated test path at the frozen target. The donor suite demonstrates a compiled/test graph contract in its source; it does not demonstrate a native build or executed test run in this audit.

## 3. Integration test behavior actually asserted

The donor integration suite is a large end-to-end source contract (the exact donor test blob is 1,139 lines in one variant, 1,750 in another, and up to 1,846 lines across the nine versions; source extraction recorded assertion counts from 13 to 392). The exact versions are materially different test scopes rather than interchangeable copies.

The donor HEAD suite asserts, among other scenarios:
- prediction sequence identity and one-time resolution, with developmental association creation;
- successful versus failed action execution changes capability performance and learned strategy evidence;
- strategy updates improve action scoring in the trained context and a related novel context, and the standard Brain/cognitive-cycle APIs consume the learned signal;
- restart/replay preserves strategy and related-context decision effects;
- featureless-observation episodic fallback, positive/negative and unobserved outcome separation;
- targeted action-outcome recall filters kind before ranking and preserves exact-context outcomes despite unrelated/newer records;
- contextless legacy outcomes do not contaminate a known unrelated context;
- normal and affective decision APIs apply learned generalization;
- contradictory outcomes revise a learned strategy, and revised positive strategy persists after restart;
- reliability changes confidence/influence rather than the valence of equal observed consequences;
- successful execution without consequence observation is not treated as positive task-utility evidence, while operational failure may produce negative strategy-reliability evidence;
- malformed outcome status, observed flag, missing context and nonfinite confidence are rejected before learning/capability state mutation;
- inferred numeric observation context supports a complete perception → action-outcome learning → later decision loop, including a related numeric band and journal replay.

The suite contains many assertion-based tests, but only static source and CMake reachability were checked here. No assertion was executed.

## 4. Historical test variants

The nine exact test blobs are not one monotonic version sequence. Feature-marker/source-size inspection grouped them approximately:
- compact early test: 49 lines / 13 assertions (`721a099...`);
- 1,139-line family: 194 assertions (three blobs);
- 1,225-line family: 221 assertions;
- 1,549-line family: 315 assertions;
- 1,750-line family: 373 assertions (two blobs);
-  1,846-line family: 392 assertions.

Feature markers across the larger variants include context transfer, action outcomes, journal restart, malformed-event guards, numeric/featureless context, episodic retrieval, prediction sequence identity, contradiction/recovery, and capability-performance behavior. These markers provide scope grouping, not a substitute for a precise diff of each blob. All nine versions remain unadjudicated at full semantic diff level.

## 5. Review lenses and unresolved risks

1. **Semantics:** integration test provides strong mechanism-level contracts for developmental transfer, outcome evidence and persistence; it does not validate broad generalization quality or learning stability.
2. **Build:** candidate absence vs donor source/test registration confirmed; actual build/test execution unavailable.
3. **Trust:** tests directly append legacy events to Memory to isolate retrieval behavior. This is intentionally fixture-level, but malformed/replay trust must be checked at the real ingestion and persistence boundary.
4. **Capability:** learned context affects action ranking, but scores are deterministic heuristic outcomes; no blinded real-task benchmark, matched baseline, false-transfer rate or statistical acceptance threshold is shown.
5. **Hostile:** high assertion count can still miss bugs. Tests use fixed hand-authored contexts and candidate actions; no fuzz/property testing, long-run stability, concurrency or crash-injection proof.

Open obligations:
- exact diff closure across all nine test blobs and six source blobs;
- declaration/definition/build ownership and API consumer graph;
- feature transfer false-positive/false-negative and negative-context policy;
- malformed evidence and journal corruption/crash behavior across replay paths;
- confidence/reliability calibration, learning stability, no-learning matched benchmark;
- provenance, authority and retention dispositions for historical tips;
- native build and CTest execution.

## 6. Disposition

| Obligation | State |
|---|---|
| Exact owner-tip/blob inventory | Complete for this cohort |
| Donor source/header/test content inspection | Complete for bounded exact refs |
| Candidate absence and donor CMake registration | Confirmed |
| Nine test variants grouped by scope | Partial; full semantic diffs open |
| Cross-file caller/dependency closure | Partial |
| Test execution / build | Not run |
| Authority/provenance/retention | Open |
| DF-02 | OPEN |

**Disposition:** donor-only developmental-learning production and integration-test cohort is documented, not accepted. No source selected/adopted, path closed, alternate retired/deleted, or Stage A authorized.
