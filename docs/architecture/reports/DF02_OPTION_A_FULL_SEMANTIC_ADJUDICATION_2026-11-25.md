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


## 9. Phase 1 — high-dispersion cluster triage (2026-11-25)

A first targeted source-level triage was performed on seven high-dispersion path clusters. This is an initial semantic review, not full closure of every version in these clusters.

### 9.1 Exact version counts

| Path | Unique versions across tips | Alternate blobs beyond donor/candidate | Candidate/donor size observation |
|---|---:|---:|---|
| `core/cpp/src/brain.cpp` | 35 | 33 | Candidate 218 lines; donor 888 lines |
| `core/cpp/include/jarvis/core/brain.hpp` | 21 | 19 | Candidate 324 lines; donor 83 lines |
| `core/cpp/src/brain_restored_api.cpp` | 20 | 18 | Candidate 18 alternate versions; path is not included in candidate CMake source registration |
| `core/cpp/src/evolution_controller.cpp` | 19 | 17 | Candidate 81 lines; donor 315 lines |
| `core/cpp/tests/evolution_brain_integration_suite.cpp` | 24 | 22 | Candidate 45 lines; donor 297 lines |
| `core/cpp/tests/CMakeLists.txt` | 40 | 38 | Candidate 45 executable/CTest entries; donor 71 executables / 70 CTest entries |
| `engineering/cpp/CMakeLists.txt` | 35 | 33 | Candidate registers one test executable; donor registers two |

### 9.2 Lifecycle and trust-boundary variants

The 17 alternate `evolution_controller.cpp` versions are not interchangeable snapshots. Feature-presence triage found:
- 13 versions contain the Brain-level validation/adoption/replay lifecycle methods;
- 11 contain isolation-attestation checks;
- four explicitly allow simulated evidence;
- one contains trusted evaluator-digest and evaluation-evidence checks;
- all 17 include rollback-related code and candidate-execution evidence checks.

The inspected diffs show materially different acceptance policies: invalid/non-finite evidence rejection; outcome recomputation; duplicate experiment handling; journal staging; evaluator identity/evidence validation; and whether simulated evidence is allowed. These are trust-boundary differences. A branch name or later-looking date is not sufficient to select the strongest or correct implementation. Existing DF-02 evolution-isolation/adoption reports are relevant evidence, but each exact version cluster still needs an explicit owner/lineage/disposition.

### 9.3 Brain/runtime variants

The 33 alternate `brain.cpp` blobs form materially different lineages. Feature triage across exact contents found 27 versions with sequence-aware prediction identity, 26 with prediction-feedback resolution, 26 with adoption replay, 27 with experience consolidation and developmental paths, and 26 with affective-experience processing. Candidate and donor remain substantially different source snapshots. The clusters must be grouped by exact content/branch lineage and reconciled against focused cognitive-runtime, feedback, memory, affective and developmental reports; feature-presence counts alone are not semantic acceptance.

The 19 alternate `brain.hpp` versions also vary: 10 expose sequence-aware prediction identity, nine prediction-feedback APIs, 10 consolidation, nine affective processing and six knowledge-source-feedback APIs. Header/API compatibility and the implementation/test/build owner must be traced together, not assessed in isolation.

### 9.4 Restored API orphaning and source registration

Exact frozen candidate and donor CMake contents were compared. Candidate `core/cpp/CMakeLists.txt` registers `src/brain.cpp` but not `src/brain_restored_api.cpp`; donor CMake registers both. The candidate test CMake does not register the restored API file either. This confirms that the source path is not a compiled candidate target under the frozen build configuration; it must not be counted as a candidate-integrated API solely from its path or lexical matches. Its 18 historical alternate blobs remain a distinct source-history cluster requiring duplicate-definition, dependency and API-provenance adjudication.

### 9.5 Test registration is version-sensitive

All 40 `core/cpp/tests/CMakeLists.txt` blob versions have distinct executable target sets in the artifact. The frozen candidate has 45 executable/CTest entries. Donor has 71 executable targets but 70 CTest registrations (the training/verification executable distinction matters). Donor-only target names include affective/developmental suites, cognitive-runtime learning/goal-feedback integration, memory-learning-evolution persistence, action-consequence integration, goal-outcome, ExperienceMemory, and DLT long-run/trial suites. This is a registration/build gap, not proof those mechanisms should be imported.

The engineering test-CMake path has 35 versions and 30 unique target sets. The branch histories range from small operator/agent foundations to provider/orchestration stacks; these are distinct engineering architectures, not a single monotonic successor. The donor's task-ledger test is registered on a specific alternative line; the candidate does not register it. The existing engineering task-ledger report must be reconciled with the exact blob-owner matrix.

### 9.6 Phase 1 disposition

This triage establishes that the high-dispersion clusters contain real semantic, API, build/test-registration and trust-policy variation—not merely duplicate branch names. It identifies the precise files and comparison obligations for the next audit slice. **No alternate version is accepted as owner, successor, retirement candidate, adoption target or source baseline.** Phase 1 remains IN PROGRESS; the 544-version cohort is not fully semantically adjudicated.


## 10. Deeper exact-source comparison — lifecycle policy and API ownership

### 10.1 `EvolutionController::record_evaluation` policy families

The exact method body was extracted from all 17 alternate `evolution_controller.cpp` blobs and grouped by policy features (not branch-name ordering):

| Variant family | Count | Material checks/behavior |
|---|---:|---|
| Minimal journal/evaluation path | 4 | journal stage/history append without the full evidence-validation contract |
| Outcome re-evaluation but incomplete validation | 1 | checks basic identity/execution and re-evaluates the outcome; missing the full finite/isolation contract |
| Finite-value validation, no isolation policy | 2 | rejects empty identity, non-executed/invalid numeric values and pending outcome; lacks isolation-attestation gate and invalid-outcome handling |
| Strict isolation + outcome validation | 5 | requires policy-controlled isolation attestation; rejects invalid/pending outcome; recomputes evaluation; stages journal and appends history with duplicate handling |
| Isolation + simulation-policy variants | 4 | strict attestation path with an explicit `allow_simulated_evidence` policy branch; policy semantics differ from the strict non-simulation family |
| Trusted evaluator/evidence variant | 1 | additionally requires trusted evaluator digest, valid evaluation evidence and isolation attestation, with duplicate record/journal identity checks |

This matrix is a concrete finding: the historical source line is not one consistent implementation. The stronger trusted-evaluator branch is one blob version, not automatically the canonical owner. The weak/minimal variants also remain historical evidence; they cannot be selected just because their branch contains a relevant file.

### 10.2 Brain API/source split and duplicate-definition risk

A name-level exact-source comparison of the frozen candidate `brain.cpp` and candidate `brain_restored_api.cpp` identifies **40 overlapping Brain method definitions** (including prediction, beliefs, associations, goals, capability/evolution and recovery APIs). The candidate CMake file does not compile `brain_restored_api.cpp`, so these overlaps are currently dormant rather than an active duplicate-symbol build failure. If that orphan file were added to the candidate target without reconciliation, the duplicate definitions would be a direct build hazard.

The donor split is different: donor `brain.cpp` has nine Brain methods and donor `brain_restored_api.cpp` has 62; the extracted definition sets have zero overlap. Donor CMake registers the restored API translation unit; candidate CMake does not. This is an architectural ownership split, not a file-presence equivalence. The 18 historical restored-API variants must be grouped by exact content and checked for duplicate definitions, missing dependencies and API lineage before any disposition.

### 10.3 CMake registration variant analysis

The exact 40 versions of core test CMake each have a distinct executable target set. The candidate/donor target delta is 26 donor-only executables (including the affective/developmental family, runtime-learning and goal-feedback integration, action-consequence integration, goal-outcome, memory-learning-evolution persistence, ExperienceMemory and DLT trial/long-run targets); no candidate-only target was found in the target-set comparison. Donor has 71 executable targets but 70 CTest entries, while candidate has 45/45, so executable and test-registration counts must not be conflated.

Engineering test CMake has 35 versions but 30 unique target sets; exact identical blob groups exist and should be reviewed once by blob SHA. The branch families include operator/console, orchestration, worker, workspace, provider and model-routing variants. These clusters are not a single monotonic progression and require ownership/provenance mapping.

### 10.4 Exact-slice disposition

This deeper comparison completes the initial source-level triage of the seven high-dispersion clusters only. It establishes source/API ownership and test-registration discrepancies and identifies exact policy families to reconcile. It does **not** complete the 544 alternate-version cohort, reverse-consumer adjudication or Director authority/retention ledger. Phase 1 remains OPEN.


## 11. Evolution integration/runner/canary test-version review

Three high-variation integration test paths were inspected at exact donor/candidate blobs, with alternate versions enumerated by exact SHA and branch owners:

| Test path | Alternate blobs | Candidate assertions | Donor assertions | Alternate assertion range |
|---|---:|---:|---:|
| `evolution_brain_integration_suite.cpp` | 22 | 7 | 97 | 68–154 |
| `evolution_experiment_runner_suite.cpp` | 17 | 11 | 17 | 13–43 |
| `evolution_canary_controller_suite.cpp` | 15 | 9 | 36 | 35–42 |

Assertion totals are not a substitute for semantic equivalence. Exact scenario review of the donor integration suite confirms coverage of: legacy adoption-event replay without evaluation evidence; persisted legacy rollback events; evaluation/adoption journal ordering; direct adoption rejected without recorded evaluation; equal-fitness and subthreshold gate rejection; outcome mismatch; canary sufficiency/rollback; duplicate evaluation idempotency; persistence and restart state; and replay of evaluated/adopted/rolled-back transitions. The frozen candidate's 7 assertions cover a basic successful evaluation/adoption and canary rollback, followed by restart-to-baseline, but not those negative/replay/legacy-evidence scenarios.

The donor experiment-runner suite's 17 assertions specifically validate isolated execution attestation, clearing attestation on simulated execution, policy rejection of non-isolated evidence, and invalid outcomes for failed/malformed execution cases. Candidate's 11 assertions do not cover the donor's full attestation/invalid-execution set.

The donor canary suite's 36 assertions exercise evaluation/adoption state, sufficient-evidence rollback, a no-evidence preview, repeated observations to threshold, and idempotent replay of evaluation/adoption/rollback journal transitions. Candidate's nine assertions test basic adoption and rollback but omit most replay/idempotency/threshold-persistence cases.

Alternate versions vary by lifecycle stage: the exact assertion count ranges above include stripped phase prototypes, broader authenticated-replay versions, and later integration branches. The 54 distinct historical test blobs across these three paths are not 54 independent implementations; their source commits/branch owners must be clustered and the scenario changes reviewed. No test blob is selected solely by its assertion count.

**Disposition:** these test histories materially show regression/coverage variation and establish the donor behavior contract to compare against. They do not establish that every donor scenario is valid for a future architecture, and no test code is adopted. Phase 1 remains OPEN.


## 12. Process-isolation and evolution execution/journal source-version review

Five additional source clusters were compared at exact candidate/donor blobs and their alternate versions. This slice covers **56 alternate blobs** (13 + 15 + 11 + 9 + 8); feature counts below are exact-content indicators and are not a substitute for per-blob semantic dispositions.

### 12.1 Process isolation — 13 alternate blobs

Candidate and donor have 250 and 258 lines respectively. Donor's exact diff moves `argv` allocation/preparation before `fork()`, avoiding non-async-signal-safe allocation in a child of a multithreaded parent, and uses `execv` for explicit executable paths while retaining `execvp` for PATH lookup. The candidate only uses `execvp` and constructs `argv` after the fork. Across the 13 alternate blobs, 12 contain both `execv` and `execvp`, 10 contain the async-signal-safety correction, and three contain `close_range`. This is material process-boundary variation; branch content must be compared to exact platform behavior and syscall isolation, not merely the presence of `fork/exec`.

### 12.2 Experiment runner — 15 alternate blobs

Candidate `evolution_experiment_runner.cpp` is 23 lines; donor is 59. Donor marks callback/sandbox results as non-isolated even when the callback returns a self-reported isolation flag, and adds a dedicated `run_isolated_command` path using the process-isolation backend, validating exit status/output/finite fitness and attesting only successful isolated execution. Thirteen of 15 alternate blobs contain isolated-result attestation; seven contain trusted-evaluator digest handling. These policies are not interchangeable.

### 12.3 Experiment coordinator — 11 alternate blobs

Candidate is 75 lines; donor 84. Donor validates `started`, completion, timeout/output limits, finite fitness and config-required isolation for baseline and candidate trials; tracks whether all trials were isolated; and emits an isolation attestation only when the result is actually isolated. Nine of 11 alternate versions contain both `require_isolation` and attestation logic. One version carries valid-evaluation-evidence handling. A candidate self-reported isolation flag cannot be assumed equivalent to donor trial provenance.

### 12.4 Adoption journal — 9 alternate blobs

Candidate is 71 lines; donor 114. Donor's `stage` refuses an existing non-new record unless the experiment's complete identity/metrics/proposal/policy fields match (including parameter key, fitness values, confidence, proposal current/proposed/expected gain/confidence, minimum improvement and isolation). It also supplies `restore_pending` and `restore_adopted` transitions. All nine alternate versions contain both restoration methods and parameter identity checks; eight compare proposal-current values. Candidate's prior adopted-record fast path returns success without this full equality check, creating an idempotency/identity mismatch risk. The journal must be reviewed with the history/codec/replay implementation, not alone.

### 12.5 Evolution orchestrator — 8 alternate blobs

Candidate is 154 lines; donor 162. Donor adds explicit trial configuration and refuses model mutation unless the selected experiment has reached `CandidateEvaluated`, preserving durable evaluation as an adoption precondition. Seven of eight alternate versions contain that lifecycle precondition and candidate-execution evidence. One alternate additionally checks isolation and valid-evaluation evidence. This is a substantive authority/order constraint, not merely an API change.

### 12.6 Disposition

The five exact source diffs establish additional concrete trust, execution, identity, replay and persistence differences. The 56 historical blobs remain unclosed: versions need exact SHA/owner grouping, tests/build reachability, source-line provenance and semantic dispositions. No adoption, baseline or retirement decision is inferred. Phase 1 remains OPEN.
