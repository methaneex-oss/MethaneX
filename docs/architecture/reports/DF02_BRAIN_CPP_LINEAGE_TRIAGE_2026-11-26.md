# DF-02 Semantic Adjudication Slice — `core/cpp/src/brain.cpp`

**Date:** 2026-11-26  
**Status:** evidence classification only; path remains OPEN  
**Scope:** exact blob-content lineage triage for one high-dispersion donor path. No implementation, adoption, retirement, or authority decision.

## Source and integrity

Source discovery artifact: workflow run `45470173876`, artifact `14956148301`; artifact SHA-256 recorded in the controlling audit as `9902957475c76f4840d1d280c7d4f50537941e9445810afb805132374a328f38`. Artifact was re-downloaded in this execution and its CSV/JSON/JSONL contents parsed. Ownership records reconcile this path to **35 distinct blobs across 213 tips**.

Exact candidate blob: `e9f3758fcc9c0e89b7280ce376db9033d547682d` (218 lines; 100 tips).  
Exact donor blob: `dec9e5442b3ca4b81a7879855c6146b2619934cc` (888 lines; 8 tips).

## Lineage triage

Using exact content comparison against the candidate and donor blobs (SequenceMatcher ratio used only as a lineage heuristic, threshold >0.75), the 35 blobs group as follows:

| Heuristic family | Distinct blobs | Ref/tip count | Interpretation boundary |
|---|---:|---:|---|
| Candidate-derived | 7 | 133 | Candidate-shaped source lineage, not proof of semantic equivalence |
| Donor-derived | 27 | 76 | Donor-shaped lineage, not proof of semantic equivalence |
| Unclassified | 1 | 3 | Neither reference comparison exceeded the heuristic threshold; needs exact review |
| **Total** | **35** | **212** | The scan's 213 tips include the path-absent tip; totals here count tips carrying one of the path blobs |

Candidate-derived variants include the candidate exact blob (100 tips) and six alternate versions (18, 11, and four single-tip variants). Their line counts are 92, 112, 150, 168, and 218. The 218-line variant is nearly content-identical to candidate by the heuristic; shorter variants are reduced/modified candidate-lineage snapshots and are not presumed interchangeable.

Donor-derived blobs range from 692 to 1,267 lines; the exact donor blob has 888 lines. The unclassified blob is `1e19646037d12a50dac7b33f5960b5fae37504a1` (692 lines; 3 tips). These groupings reflect source-text similarity only.

## Structural finding

A bounded method-definition-pattern count over exact blobs showed the candidate-shaped variants typically have roughly 42–50 `Brain::` definitions in this source file, while donor-shaped variants typically have 9. This supports a **source ownership/layout divergence** hypothesis (candidate keeps more Brain methods in this translation unit; donor lineage splits implementation across other translation units). It does not prove behavior, build compatibility, API equivalence, correctness, or which arrangement should be retained.

The source-level feature scan previously reported cognitive capability tokens in the donor/candidate variants. Those token-presence counts are not treated as semantic proof and are excluded from closure.

## Required follow-up for this path

1. Identify exact semantic changes within the 7 candidate-shaped blobs and the 27 donor-shaped blobs, grouping patches by actual behavior/API change—not by branch name or similarity score.
2. Trace moved method ownership across exact `brain.hpp`, `brain_restored_api.cpp`, and other production translation units plus candidate/donor CMake registration; establish duplicate-definition and missing-definition outcomes per source graph.
3. Trace exact registered tests and behavioral evidence for each materially distinct implementation lineage.
4. Reconcile provenance, competing owners, and retention/retirement authority. Keep unresolved groups explicitly open.
5. Add a sourced disposition to the 159-path matrix only after the above, then independent scrutiny.

## Disposition

**This slice improves evidence organization and lineage classification but does not close the path.** `core/cpp/src/brain.cpp` remains OPEN in DF-02 Phase 1/2/3/4. No donor or alternate blob is selected, adopted, retired, or deleted; no baseline or Stage A authority is created.
