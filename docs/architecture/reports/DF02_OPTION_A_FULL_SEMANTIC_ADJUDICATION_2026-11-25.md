# DF-02 Full Option A Semantic Adjudication — Execution Record

**Date:** 2026-11-25  
**Project Director decision:** D2 = B — reopen and complete full Option A semantic adjudication.  
**Scope:** frozen PR #192 review target `caf87986dfea7aca75728818651c8687e9f5faf0`; donor PR #97 HEAD `c1da222e6c94aeb3f2ad000392c21fe4fc81ab25`.  
**Status:** OPEN — Phase 0 evidence acquisition/integrity is complete. Semantic and authority adjudication is not complete.

## 1. Director's instruction and boundary

The earlier bounded DF-02 non-adoption closeout is superseded as the accepted closure standard by the Project Director's 2026-11-25 decision D2=B. DF-02 is reopened. Complete Option A must adjudicate donor-path semantic successors, historical blob variants, reverse consumers, dependencies, duplicate capabilities/owners, retention/retirement and provenance/authority across the available historical refs.

This does **not** select a Stage A source baseline, authorize donor adoption, approve retirement/deletion, integrate branches, change runtime code or start Stage A. Decisions reserved to the Project Director remain reserved. Evidence is not authority.

## 2. Frozen discovery artifact — integrity verified

All-ref scan workflow **45470173876**, artifact **14956148301**, SHA-256:

`9902957475c76f4840d1d280c7d4f50537941e9445810afb805132374a328f38`

The ZIP was downloaded and independently hashed; the computed digest matches. The artifact's `summary.json`, `report.md`, and tables were parsed locally.

| Evidence dimension | Verified result |
|---|---:|
| Branch refs | 254 |
| Unique branch tips | 213 |
| Donor paths | 159 |
| Candidate same-path | 95 divergent / 63 absent / 1 identical |
| Unique text blobs scanned | 1,416 |
| Donor identifiers extracted | 724 |
| Exact path-reference candidates | 1,946 |
| Symbol-consumer candidates | 40,048 |
| Consumer-blob/path/category records | 1,227 |
| Unique consumer paths in symbol-match table | 346 |
| Unique consumer blobs in symbol-match table | 1,135 |
| Exact path/blob ownership rows | 798 |

The scanner itself explicitly limits matches to lexical discovery, not semantic dependency proof.

## 3. Version-ownership reconciliation

The 798 ownership rows comprise the 159 donor-path versions and 639 non-donor versions. The 639 non-donor versions separate into 96 candidate-branch blobs (95 divergent paths plus the one identical path) and **544 distinct non-candidate historical alternate blobs across 88 donor paths**.

All 544 alternate blobs have their exact full content represented in the artifact's `consumer_blob_sources.jsonl`. All 96 candidate blobs also have full content in that corpus. Six donor blobs were absent from the consumer corpus; they were individually retrieved by exact SHA from GitHub and verified to be available. The donor-path content set is therefore now complete for all 159 paths.

The 544 alternate blobs comprise:
- 299 production source/header versions;
- 190 test versions;
- 53 build-system versions;
- 2 workflow versions.

Version dispersion is concentrated in files with active integration and lifecycle work. The highest counts are:
- `core/cpp/tests/CMakeLists.txt`: 38 alternate versions;
- `core/cpp/src/brain.cpp`: 33;
- `engineering/cpp/CMakeLists.txt`: 33;
- `core/cpp/tests/evolution_brain_integration_suite.cpp`: 22;
- `core/cpp/CMakeLists.txt`: 20;
- `core/cpp/include/jarvis/core/brain.hpp`: 19;
- `core/cpp/src/brain_restored_api.cpp`: 18;
- `core/cpp/src/evolution_controller.cpp`: 17.

These exact versions and their branch/tip owners are evidence inputs. Counts do not establish semantic ownership, maturity, correctness, or adoption authority.

## 4. Consumer-discovery breakdown

The 40,048 symbol-match rows classify as 23,948 source, 14,974 test, 861 workflow, 237 build and 28 other-category matches. Only 3,441 rows are marked as present on the frozen candidate tip (2,050 source, 1,136 test, 219 workflow, 8 build, 28 other); these map to 111 donor paths and 193 consumer paths. The remaining 36,607 rows are historical-ref discovery candidates and must be adjudicated against exact content and owner tips, not presumed active dependencies.

The 1,946 exact-path-reference rows classify as 1,930 documentation, 15 workflow and one other. They are kept separate from symbol matches. Generic identifiers, comments, tests, docs and workflows are not promoted to production dependencies without exact-context review.

## 5. Existing report coverage is input, not closure

Existing focused audits cover the 76 divergent candidate paths, the 35 candidate-absent cohort, the 48 no-symbol cohort, and material cognitive/evolution gaps. Prior bounded closeout assertions are not treated as closure under the newly selected Option A.

The full audit must still reconcile:
1. all 159 donor paths to a defensible semantic successor, duplicate/owner cluster, historical retention/retirement disposition, or explicit unresolved status;
2. all 544 alternate blobs, grouping exact identical content across refs, and adjudicating materially different versions rather than treating branch names as independent implementations;
3. the 40,048 symbol candidates and 1,946 exact path candidates by exact blob, context and category, including false-positive rationale and reverse-consumer/dependency relationships;
4. competing owners, capability duplication, API compatibility, build/test registration, behavioral evidence, provenance and authority;
5. every conclusion to immutable source refs/blob SHAs and the applicable Director decision.

No path/blob will be marked resolved merely because it is absent from frozen candidate PR #192 or present on another branch. Historical retention/retirement and donor adoption require their own authority classification.

## 6. Execution phases and exit criteria

- **Phase 0 — evidence acquisition and integrity: COMPLETE.** Exact artifact/hash verified; all donor, candidate and 544 alternate path/blob contents are available; counts reconciled.
- **Phase 1 — path/version semantic ledger: IN PROGRESS.** Group exact blobs by donor path and owner tips; identify identical content clusters and meaningful version transitions; use prior focused reports as evidence; add exact source comparisons for unresolved clusters.
- **Phase 2 — reverse-consumer and dependency adjudication: NOT COMPLETE.** Review exact-context source, test, build, workflow and documentation candidates; distinguish direct/compiled/runtime/test-only/metadata/false-positive.
- **Phase 3 — duplicate-owner and authority reconciliation: NOT COMPLETE.** Identify equivalent capability owners, overlapping/alternate implementations, provenance, decision records and preservation/retirement constraints.
- **Phase 4 — closure matrix and independent scrutiny: NOT COMPLETE.** Each of 159 paths receives a sourced, bounded disposition and any unresolved blocker. A Builder completion claim requires a complete ledger and independent verification; DF-02 cannot close while material unresolved items remain.

## 7. Known tool boundary

The connected GitHub operations permit repository/ref/content access and artifact retrieval, but no workflow-dispatch action is exposed. The 2026-11-24 scan is the exact frozen-target discovery artifact; its new scanner cannot be re-dispatched through the current connector. If additional scan coverage becomes necessary, it must be run by an authorized operator or through an available execution path. This limitation does not invalidate the downloaded artifact and is not used to infer semantic closure.

## 8. Current gate and next work

**DF-02: REOPENED / OPEN — full Option A required.** Phase 0 is complete. The next bounded audit slice is the high-dispersion build/runtime/evolution clusters (CMake, `brain.cpp`, `brain.hpp`, `brain_restored_api.cpp`, `evolution_controller.cpp`, experiment runner/coordinator and their registered integration suites), followed by lower-dispersion source/test and absent/no-symbol cohorts. Every review must produce exact SHA-linked classifications; unresolved material variants remain OPEN.

DF-09 remains blocked pending blind fresh-reader CLEAR against frozen PR #192 SHA `caf87986dfea7aca75728818651c8687e9f5faf0`. DF-11 waiver remains retained with its provenance residual. DF-12 remains pending Director acceptance; consolidation preparation is authorized only after DF-09 CLEAR. No merge is authorized.
