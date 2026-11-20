# DF-02 — Affective decision integration and orphaned Brain API audit

**Date:** 2026-11-20  
**Candidate baseline:** PR #192 base/merge-base `61311fe5b44c81c4409c8ba8dc581a83bdd5dd2c`. Every candidate source/test blob cited in this report was re-fetched at that exact PR base and matched the blob previously inspected at `cbc51e2b10f1fc976257653adf773735a2b27d49`.  
**Donor snapshot:** PR #97 HEAD `c1da222e6c94aeb3f2ad000392c21fe4fc81ab25`

## 1. Candidate decision API omits the donor's affective context

| Artifact | Candidate blob | Donor blob |
|---|---|---|
| `core/cpp/include/jarvis/core/cognition.hpp` | `e9aec6461351db42c77ff8414a175ce4c5eea33e` | `92febfa5d5feab45de1a3a19fe37282852898e6c` |
| `core/cpp/include/jarvis/core/decision.hpp` | `7dd9d6b7337311868d236dc0ced81f558200ab1a` | `88ee24e6dc93826759de46b38d15a08a685a3aac` |
| `core/cpp/src/decision.cpp` | `6a49e0f1f80c3c6b0955ddf98182fc6611c0e84c` | `012025bc2ef66b1b9555b9b9f2b220b49c8d36c4` |
| `core/cpp/include/jarvis/core/brain.hpp` | `8268ef84e0b361ead536724ba7761904b30ee58f` | `671186f4c39879a182f9e511394fc564d86f2988` |
| `core/cpp/tests/decision_planning_architecture_suite.cpp` | `16934f99898c3ffffcf5ac04a7a031e0845da050` | `3ed85a1acc55f47eb266599d809525ef08ba0b11` |

The donor `DecisionContext` carries valence, arousal, affective uncertainty, tension and stability. `DecisionPolicy` provides explicit weights for those dimensions. The donor `DecisionEngine::decide` consumes those values when ranking actions, and the public Brain API includes `choose_with_affect`.

The candidate `DecisionContext` and `DecisionPolicy` omit these affective dimensions and weights. Its public Brain header does not expose `choose_with_affect`. The candidate decision test contains no affective-context assertions; the donor test exercises the affective decision inputs.

**Finding:** the donor's direct affective-state-to-decision integration is absent from the candidate decision API. This does not prove that every affective influence is absent from every candidate subsystem; it establishes that this explicit Brain → DecisionEngine integration contract is not present in the candidate public API.

## 2. Candidate contains an uncompiled, stale Brain API translation unit

| Artifact | Candidate blob | Donor blob |
|---|---|---|
| `core/cpp/CMakeLists.txt` | `c51816888e1bddb7bc00c59e72529524e27a0717` | `bc264ce7b4ae489404ca03ea6d9676d0330a6a56` |
| `core/cpp/src/brain.cpp` | `e9f3758fcc9c0e89b7280ce376db9033d547682d` | `dec9e5442b3ca4b81a7879855c6146b2619934cc` |
| `core/cpp/src/brain_restored_api.cpp` | `618deb6976eed951eae02b7f0da741e6d730bb0c` | `7155d4d9c8eef527836fb79bf901aa32ddbae38b` |

The candidate tree contains `brain_restored_api.cpp`, but candidate `core/cpp/CMakeLists.txt` does not include it in the `jarvis_core` source list and no candidate source includes it. The donor CMake does compile this translation unit.

The candidate orphan file contains many definitions also present in the candidate's compiled `brain.cpp` (including `beliefs`, `predict`, `resolve_prediction`, `choose`, `plan`, `reflect`, evolution methods and snapshot/state methods). It also contains methods absent from the candidate public header, including `choose_with_affect`, contextual association/concept accessors and other restored APIs. It calls `association_.contextual`, `association_.concept_candidates` and `association_.generalized_concepts`, which are absent from the candidate `AssociationModel` header and implementation.

Therefore this file is not a valid compiled successor in the candidate tree. Simply adding it to CMake is not a safe repair: it would introduce duplicate Brain definitions and calls to missing AssociationModel methods. The candidate branch currently carries this code as an uncompiled, stale/partial translation unit.

**Disposition:** this is a concrete source ownership/build-integration defect and explains why file presence alone must not be counted as mechanism integration. It needs a coordinated source split/merge decision and exact target/test verification; no runtime/CMake changes were made.

## 3. Builder conclusion

The affective decision contract and the orphaned Brain API are linked findings: some affective and contextual API implementations remain visible in an uncompiled file, but the public header, compiled CMake source set and dependency APIs do not form a coherent buildable integration.

Do not add the orphan file as a one-line CMake fix. First resolve duplicate ownership, restore or deliberately retire the public API surface, align AssociationModel dependencies, then test affective influence on actual decision ranking and persistent outcomes. No donor code was copied and no source baseline was selected. DF-02 remains OPEN.
