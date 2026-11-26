# DF-02 Semantic Adjudication Slice — `core/cpp/include/jarvis/core/brain.hpp`

**Date:** 2026-11-26  
**Status:** evidence classification only; path remains OPEN  
**Scope:** exact blob lineage and declaration-surface comparison for one high-dispersion donor path. No API selection/adoption or authority decision.

## Evidence source

The frozen discovery artifact `45470173876 / 14956148301` was re-downloaded and parsed. Ownership records contain **21 unique header blobs across 213 branch tips** (212 tips contain the path; one tip is absent).

Candidate blob: `8268ef84e0b361ead536724ba7761904b30ee58f` (324 lines; 100 tips).  
Donor blob: `671186f4c39879a182f9e511394fc564d86f2988` (83 lines; 51 tips).

## Lineage classification

The same content-similarity heuristic (>0.75 against either exact reference; for grouping only) partitions the blobs:

| Family | Blob count | Tips | Boundary |
|---|---:|---:|---|
| Candidate-shaped | 5 | 126 | Text lineage, not API equivalence |
| Donor-shaped | 10 | 76 | Text lineage, not API equivalence |
| Unclassified | 6 | 10 | Manual semantic classification needed |
| **Total** | **21** | **212** | Absent tip excluded |

Candidate-shaped versions are 298–324 lines; the exact candidate is 324 lines. Donor-shaped versions are 83–114 lines; the exact donor is 83 lines. Six unclassified blobs are 70–241 lines. The radically different line-count distribution reinforces that these are competing source/API layouts, not minor edits.

## Declaration-surface divergence (bounded)

Exact declaration review identifies material differences. The donor header declares API groups not present in the candidate header's inspected declaration surface, including:

- sequence-addressed prediction-feedback resolution and contextual prediction;
- goal-outcome assimilation;
- contextual association/concept inference and generalized concepts;
- affective and developmental-learning action/planning overloads;
- action assessment and capability evaluation/execution contracts;
- developmental association/strategy retrieval;
- attention policy, intent/strategy, affective-state/appraisal/calibration/update accessors;
- self-test/self-healing result contracts;
- evolution evaluation-recording and canary-observation lifecycle APIs.

The candidate header, conversely, has its own broader inline/declaration surface (including evolution parameter access, goal operations, self-state/self-model and world accessors, replay/synchronization helpers) and a substantially different class organization. This list is a bounded declaration comparison, not an exhaustive compatibility map and not proof that each capability is absent from all candidate source files.

## Required dependency/ownership checks

1. Pair each donor-only declaration with exact implementation blob(s), source registration, and exact consumer/test call sites; verify symbols are linkable in their claimed graph.
2. For candidate declarations, identify definitions and whether they are registered/linked, including restored-API split files.
3. Compare materially distinct header blobs by API contract and ABI/source compatibility, not branch chronology or similarity.
4. Establish test coverage/behavior evidence and owner/provenance/retention dispositions.
5. Cross-reference the `brain.cpp` lineage report: its candidate/donor source-layout divergence may reflect moved method ownership, but this remains unproven until exact CMake and declaration/definition edges are closed.

## Disposition

**OPEN.** This evidence slice records substantial declaration/API divergence and version ownership. It does not select a header, prove runtime capability, authorize adoption/retirement, close DF-02, or authorize implementation/Stage A.
