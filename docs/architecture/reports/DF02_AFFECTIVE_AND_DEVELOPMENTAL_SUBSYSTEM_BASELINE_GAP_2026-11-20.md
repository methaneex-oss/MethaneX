# DF-02 — Affective and developmental subsystem baseline gap

**Date:** 2026-11-20  
**Candidate source baseline:** PR #192 merge-base `61311fe5b44c81c4409c8ba8dc581a83bdd5dd2c`  
**Donor source baseline:** PR #97 HEAD `c1da222e6c94aeb3f2ad000392c21fe4fc81ab25`  
**PR #97 status:** open; donor branch is not merged into `main`.

## 1. Scope correction

This is a **capability delta**, not a claim that the candidate had these subsystems and then regressed. The candidate PR #192 source baseline predates the PR #97 affective/developmental source line. PR #192's recorded source merge-base is `61311fe...`; the PR #192 scan snapshot `32722f104f76817983b0156cca821949e406b8c1` is 790 commits ahead of that merge-base with 47 changed paths, all documentation or root README. The current PR #192 head's subsequent 99 commits likewise change only documentation, the documentation-link workflow and its script. No C++ source change was introduced by PR #192. The source blobs compared in the other DF-02 reports were re-fetched at the exact candidate merge-base and match.

The donor PR #97 is an unmerged source proposal. Its presence is evidence of a possible implementation line, not proof of Project Director adoption or authority to merge it.

## 2. Candidate baseline contains no affective/developmental source paths

A complete recursive tree inspection of candidate baseline `61311fe...` returned zero tracked paths containing `affective` or `developmental`.

The following donor files exist at PR #97 HEAD but are absent from the candidate tree:

| Donor artifact | Donor blob |
|---|---|
| `core/cpp/include/jarvis/core/affective_state.hpp` | `f63da2e0060938864bf434012d0b3b4d74fa5f29` |
| `core/cpp/include/jarvis/core/affective_learning.hpp` | `fa06043dc481336ba544247f365d37f5476a0651` |
| `core/cpp/src/affective_state.cpp` | `563a61cd8f6440f78a084f76a799b2c84bdd6813` |
| `core/cpp/src/affective_learning.cpp` | `dd1735a10871512691d4b518d1ce45246c80f708` |
| `core/cpp/include/jarvis/core/developmental_learning.hpp` | `e3b9bf8af265b67829fd7deb323d88a3a9dd4b75` |
| `core/cpp/src/developmental_learning.cpp` | `dbf5f43271dfa0a3c57236e2faa82eb88d15490d` |
| `core/cpp/include/jarvis/core/developmental_environment.hpp` | `913c8cca2a03499249b834a890812c57b9aa4b1a` |
| `core/cpp/include/jarvis/core/developmental_world.hpp` | `2ba5bdbfc6db1f24eff8eb0a20ee145d0efc16cf` |
| `core/cpp/src/brain_affective_planning.cpp` | `2a9406257c23f3a66a64071842be7d6448799406` |
| `core/cpp/src/brain_prediction_context.cpp` | `b3ceff150f3fe8223dc3f76f4c298ac264d72dae` |

The candidate does contain `core/cpp/src/brain_restored_api.cpp`, but it is excluded from candidate CMake, duplicates many definitions in `brain.cpp`, and references affective/developmental members and AssociationModel methods that are absent from the candidate's compiled API. It is not an integrated implementation of these subsystems.

## 3. Build and test integration delta

| Build artifact | Candidate | Donor |
|---|---|---|
| `core/cpp/CMakeLists.txt` | `c51816888e1bddb7bc00c59e72529524e27a0717` | `bc264ce7b4ae489404ca03ea6d9676d0330a6a56` |
| `core/cpp/tests/CMakeLists.txt` | `dab0c52ab4dfe15e1e2cbccfa9e6c904abdf54e3` | `cbfd1fde52fffa6eeac025da2b7ddcb5ab493261` |

The donor core CMake compiles `brain_prediction_context.cpp`, `brain_affective_planning.cpp`, `affective_state.cpp`, `affective_learning.cpp` and `developmental_learning.cpp`, and includes the affective-planning test CMake fragment. The candidate core CMake compiles none of these.

The donor test CMake contains 71 executable declarations and 70 CTest registrations; candidate contains 45 / 45. The donor registers 17 additional affective/developmental/runtime integration suites:

- cognitive runtime learning integration;
- developmental learning;
- affective state and affective state model;
- affective decision and affective decision learning;
- affective learning and affective evidence;
- affective goal outcome;
- affective Brain decision;
- cognitive runtime goal feedback;
- developmental Brain integration;
- Brain action-consequence integration;
- developmental training environment;
- developmental environment;
- developmental world and developmental world integration.

These are not candidate test targets and cannot be counted as current candidate coverage.

## 4. What this means for the JARVIS source-baseline decision

The donor line adds an affective-state model, affective learning/appraisal, developmental association/strategy learning, a training environment/world, affect-aware planning, and contextual prediction. Those mechanisms align with the project's intended experience-driven learning loop at the capability level, but they are not yet part of the candidate source baseline.

The donor code still requires the per-mechanism review recorded in the other DF-02 reports. In particular, fixed affective appraisal weights, developmental learning coefficients and policy thresholds must not be adopted as hard-coded semantic mappings. The desired capability is that experience-derived evidence updates internal state, attention, memory, associations, strategies and future choices—not that a fixed stimulus is assigned a predetermined emotion or behavior.

The alternate branches documented in the compiled-consumer report contain additional donor-identical implementations. Their presence is relevant to provenance and duplicate-owner analysis but does not authorize selecting any one branch as the source baseline.

## 5. Builder disposition

This report closes the factual question of whether affective/developmental source and build integration exist in the candidate PR #192 baseline: **they do not**. The donor PR #97 contains a compiled/tested implementation line, and some alternate branches contain related integration. The Project Director's source-baseline/adoption decision remains reserved.

No runtime or CMake code was changed. No donor files were copied. DF-02 remains OPEN pending full semantic mapping, dependency/duplicate-owner/authority decisions and explicit source-baseline disposition.
