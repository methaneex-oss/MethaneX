# DF-02 — Representation provenance and evolution-canary preview audit

**Date:** 2026-11-20  
**Candidate baseline:** PR #192 base/merge-base `61311fe5b44c81c4409c8ba8dc581a83bdd5dd2c`. Every candidate source/test blob cited in this report was re-fetched at that exact PR base and matched the blob previously inspected at `cbc51e2b10f1fc976257653adf773735a2b27d49`.  
**Donor snapshot:** PR #97 HEAD `c1da222e6c94aeb3f2ad000392c21fe4fc81ab25`

## 1. Candidate representation treats appraisal metadata as semantic content

| Artifact | Candidate blob | Donor blob |
|---|---|---|
| `core/cpp/src/representation.cpp` | `0e53bfaa0c1114cb7390d9f7ce577c87d6bc6169` | `054bd9ecee3ef3da83dd405dc5785464d874fa21` |
| `core/cpp/include/jarvis/core/representation.hpp` | `4a9a12e8e66ce9c393081a4ffff0b7519f3a92ae` | `4a9a12e8e66ce9c393081a4ffff0b7519f3a92ae` |

The candidate representation normalizer converts every event-data field into a semantic attribute node. That includes appraisal/evidence metadata such as `confidence`, `reliability`, `novelty`, `salience`, `urgency`, `prediction_error`, `outcome` and `world_step`. These values can then be treated as content features by downstream semantic processing rather than remaining provenance/appraisal metadata.

The donor separates those fields: it retains them in `PerceptualRepresentation.metadata` and excludes them from semantic nodes. The donor also:
- derives node confidence from validated event confidence when supplied, rather than always assigning a modality-only default;
- assigns deterministic, length-prefixed node identifiers instead of relying on implementation-defined `std::hash` values and possible collisions;
- rejects non-finite representation/node/evidence/relation confidence with `std::isfinite`; the candidate's range-only comparisons allow NaN through because both comparisons are false.

**Finding:** the candidate risks conflating evidence-quality/appraisal signals with represented world content, uses non-stable node identity, ignores supplied confidence and accepts NaN confidence. These are provenance, repeatability and validation defects in a foundational representation boundary.

The candidate `representation_suite.cpp` has 10 assertions / 31 lines versus 22 / 66 in the donor, but neither candidate nor donor `core/cpp/tests/CMakeLists.txt` registers `representation_suite`; these assertions are not part of the registered CTest suite and must not be represented as CI coverage.

## 2. Evolution canary loses non-mutating preview

| Artifact | Candidate blob | Donor blob |
|---|---|---|
| `core/cpp/include/jarvis/core/evolution_canary.hpp` | `46ca0938caf1b27b1ea804f1b5ea795683ab0ef0` | `9a2e2966a242df345ebb778e78b69b7db90dc502` |
| `core/cpp/src/evolution_canary.cpp` | `b40c2eec58db1a3f7d3007781f0a5e6abe8c70a9` | `8773507b4bc5842c60b78bcb384f09ea4c4caa2b` |
| `core/cpp/tests/evolution_canary_controller_suite.cpp` | `6acd8aedb7520aebe745b15a2a10c527262f28e0` | `80cac5df347987a9074e1ced43202f8759f797d7` |

The donor exposes `EvolutionCanary::preview`, which copies the canary state and evaluates a hypothetical new observation without mutating the live accumulator. The candidate exposes only mutating `observe`, `evaluate` and `reset`.

The registered canary-controller suite falls from 36 assertions / 105 lines in the donor to nine assertions / 39 lines in the candidate.

**Finding:** the candidate loses a non-mutating decision/evidence-inspection operation and substantial canary/controller test coverage. This is a secondary evolution-control gap; the larger isolation and durable-adoption regressions are recorded in the preceding DF-02 reports.

## 3. Builder disposition

Keep provenance/appraisal metadata distinct from semantic content, use stable identifiers, validate finite numeric fields, and prove that representations survive process restart with the same identity. Do not blindly adopt the donor's exact default confidence values or coefficients; the important contracts are separation, provenance and deterministic validation.

No runtime or CMake files were changed. No donor code was copied. DF-02 remains OPEN.
