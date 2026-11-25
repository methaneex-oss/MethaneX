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


## 13. Cognitive-cycle, memory continuity and learning source-version review

Five additional source paths were compared at exact frozen-candidate and donor blobs and their alternate versions. This slice covers 29 alternate blobs (8 cognitive-cycle, 7 memory, 6 knowledge, 5 developmental-learning and 2 evolution-model versions).

### 13.1 Cognitive cycle — 8 alternate blobs

Candidate `cognitive_cycle.cpp` is 161 lines; donor is 776. Five alternate versions contain the integrated context/perception/prediction-feedback/affective/attention/developmental feature family; three are small earlier phase prototypes (106–143 lines). The exact donor implementation adds reversible escaping for hierarchical context keys and reserved-segment collision protection; infers structured developmental context from observation identity, representation features and goal; retrieves context/action/perceptual memories; uses structured perception and attention; incorporates disputed facts/relations and belief uncertainty; integrates affective state/appraisal; applies strategy/developmental context; validates/assimilates prediction feedback by sequence; and assimilates goal outcomes. Candidate's exact run path does not contain this integration family. These differences correspond to previously focused cognitive-cycle, prediction-identity, representation and affective/developmental reports, but the eight alternate blobs still need owner/lineage and test evidence adjudication.

### 13.2 Memory continuity — 7 alternate blobs

Candidate `memory.cpp` is 428 lines; donor is 225 lines (donor source is heavily compacted, so line count is not a complexity/quality measure). The exact code comparison establishes:
- Candidate journal load truncates an unreadable suffix at the last valid record without first preserving it. Donor attempts to copy that suffix to a `.corrupt` quarantine file and only truncates the active journal if quarantine succeeds. The legacy journal is still unframed and has no checksum; the donor explicitly acknowledges that a malformed record boundary cannot be safely resynchronized.
- Candidate metadata magic is v1; donor supports v1 and v2, with a consolidation field in v2. Donor validates and stages metadata updates before applying them, rather than leaving a partial update on a malformed snapshot.
- Candidate `append` persists the event and updates metadata/continuity/sequence, but does not update learned-tier counts or the latest-sequence-by-kind map in that function. Donor updates both. Exact constructor/load/promotion paths must be tested to establish the behavioral impact.
- Donor adds `Memory::consolidate`: finite-value validation, bounded evidence inputs and a recurrence-derived consolidation score combining salience, novelty, prediction error, confidence and recurrence. This mechanism's coefficients are evidence for review, not accepted policy.
- Six of seven alternate blobs contain the v1 metadata compatibility/consolidation family; five contain learned-tier rebuild logic; one alternate includes quarantine behavior. The remaining version differences must be grouped and checked for loss/corruption, sequence, persistence-failure rollback and metadata compatibility.

### 13.3 Knowledge model — 6 alternate blobs

Candidate and donor `knowledge.cpp` are both 35 lines, but the public assimilation type differs: candidate takes `Evidence`; donor takes `KnowledgeEvidence`. Five of six alternate blobs contain finite-value/contradiction validation and an `assess` path. This is a contract/API difference despite similar file length; cross-reference the header, feedback provenance and source-calibration reports before disposition.

### 13.4 Developmental learning — 5 alternate blobs

The frozen candidate has no `developmental_learning.cpp`; donor has 444 lines. Five alternate versions range from 102 to 563 lines, and all include finite-value validation, learning-rate and consolidation code. Three include the context-path encoding feature. The path is absent in the candidate, so these are historical alternate implementations—not candidate integration. Exact ownership, API/CMake/test registration, persistence and behavior remain open.

### 13.5 Evolution model compensation — 2 alternate blobs

Candidate rollback sets both current and previous value to baseline. Donor rollback preserves the pre-rollback current value as `previous_value` and restores baseline; donor also exposes `restore_previous` with finite-value and bounds validation. Both alternate blobs contain the previous-value restoration API. This is a real compensation semantics difference, already cross-referenced by the evolution-recovery report.

### 13.6 Disposition

These exact comparisons identify real memory durability/recovery, learning integration, context/feedback and compensation differences. They do not close the alternate versions or authorize adoption. Phase 1 remains OPEN; Phase 2/3 reverse-consumer and authority work remains.


## 14. Single-alternate-path cohort — targeted source and test diffs

The exact corpus contains **25 donor paths with exactly one alternate blob** (12 production/header paths, 11 test paths, two workflow files). The 12 production/header alternates were diffed against frozen candidate content where present. This cohort is small enough for focused follow-up, but the findings below are still path-level—not authority closure.

### 14.1 Production/header deltas

| Path | Exact alternate finding |
|---|---|
| `causal_model.hpp` | API/representation change: removes `CausalPrediction`/`SimulationResult` and horizon simulation declaration; switches causal-link storage from vector to keyed map. Source/API compatibility must be traced. |
| `self_model.hpp` | Removes `SelfCapabilityHealth` and `SelfModel::health()`; alternate API is narrower. |
| `action_execution.cpp` | Alternate removes `ActionAuthorizer` and trusts assessment's `permitted` + disposition directly. This is an authorization-boundary regression candidate; compare authorization context/identity checks and tests before any use. |
| `association_model.cpp` | Large alternate adds changed/present-key reconciliation, contradictory-observation counts and confidence/strength decay for links whose endpoints change inconsistently. This is substantive learning behavior. |
| `attention.cpp` | Alternate clamps learned novelty/uncertainty/urgency weights to [0,4], preventing unbounded weight growth. |
| `evolution_adoption.cpp` | Alternate low-level helper fails closed because it lacks an evaluation journal; routes the authority boundary to `EvolutionController`. |
| `evolution_canary.cpp` | Alternate drops worst-case-delta tracking and uses mean regression only; candidate/donor track the worst regression. This changes rollback sensitivity. |
| `reasoning.cpp` | Alternate excludes disputed beliefs as authoritative premises and propagates confidence as min(cause confidence, link strength). Candidate deducts from all supplied premises and uses link strength as conclusion confidence. |
| `self_model.cpp` | Alternate removes aggregate capability-health calculation. |
| `adaptation.hpp` | Single alternate is a small one-line API/content delta; must be reconciled with adaptation behavior and downstream headers. |

### 14.2 Candidate-absent source paths

Two source paths are absent from frozen candidate but present in donor and alternate historical content:
- `brain_action_execution.cpp` (186-line alternate): action execution/outcome integration path, including event replay, consequence feedback and consolidation hooks.
- `brain_prediction_context.cpp` (68-line alternate): contextual prediction identity and context-aware predict/replay APIs.

These are historical capability candidates, not candidate integration. Check header ownership, CMake registration, exact consumer graph, tests and provenance before any disposition.

### 14.3 Single-alternate test cohort

The alternate test blobs show differing coverage, but assertion counts alone are not quality metrics:

| Test path | Candidate assertions | Donor assertions | Alternate assertions | Candidate status |
|---|---:|---:|---:|---|
| action execution phase 7 | 14 | 45 | 24 | present |
| affective evidence | — | 20 | 20 | absent |
| Brain 10 | 29 | 32 | 29 | present |
| Brain deep | 68 | 260 | 88 | present |
| cognitive runtime goal feedback | — | 22 | 19 | absent |
| cognitive workspace runtime | 6 | 8 | 6 | present |
| developmental world integration | — | 40 | 28 | absent |
| goal-directed cognition | — | 23 | 23 | absent |
| goals architecture | 34 | 45 | 68 | present |
| reasoning architecture | 19 | 33 | 26 | present |
| engineering agent/console | 7 | 31 | 8 | present |

Candidate-absent suites are not silently treated as failed or passed. They represent no frozen-candidate test registration/source. The single alternate blob is a different test revision and must be reviewed against its exact source API and target registration.

### 14.4 Disposition

This one-alternate cohort reveals authorization, contradiction learning, attention-weight bounds, canary regression policy, disputed-premise reasoning, capability-health API and candidate-absent action/prediction/affective/developmental tests. All require exact owner/consumer/provenance classification. The two workflow files are tracked separately as test/CI evidence, not runtime capabilities. Phase 1 remains OPEN; no adoption/retirement/baseline authority is inferred.


## 15. Cumulative cohort accounting and next slice

A path-overlap reconciliation across the preceding sections prevents double-counting: `evolution_brain_integration_suite.cpp` is included in §9's seven high-dispersion clusters and §11's test review, so it is one path/22 alternate blobs, not two. The cumulative targeted triage cohort is therefore **44 unique path clusters / 320 alternate blobs**. The total discovery cohort is 544 alternate blobs across 88 donor paths; **44 path clusters / 224 alternate blobs remain outside this targeted cohort**.

The highest remaining alternate-version counts are: core CMake (20); evolution-experiment API header (13); evolution-opportunity orchestration suite (12); experiment-runner header (11); memory-learning-evolution persistence suite (11); experiment-coordinator suite (11); adoption-journal header (8); developmental-brain integration suite (8); engineering message bus header/source (7 each); engineering agent header (7); engineering coordinator source (6); memory architecture suite (6); cognitive-cycle suite and cognitive runtime source (5 each. These form the next audit priority, followed by the remaining low-dispersion cohorts.

This reconciliation is a count/coverage correction, not semantic closure. The complete alternate cohort remains OPEN.


## 16. Core CMake, evolution API headers and remaining high-variation integration suites

A further priority slice reviewed **22 path clusters / 162 alternate blobs**: core CMake (20); 11 API headers (62); six integration/persistence suites (53); and four engineering workforce/message-bus paths (27).

### 16.1 Core CMake source ownership

The frozen candidate registers 57 translation units; donor registers 64. The candidate has no source-only registrations relative to donor; donor adds seven source paths: `affective_learning.cpp`, `affective_state.cpp`, `brain_action_execution.cpp`, `brain_affective_planning.cpp`, `brain_prediction_context.cpp`, `brain_restored_api.cpp`, and `developmental_learning.cpp`. Candidate does not register `brain_restored_api.cpp` (the 40-name duplicate-definition risk documented in §10); donor registers the split API implementation alongside its smaller `brain.cpp`. The donor CMake also enables affective-planning test integration and examples. The 20 alternate CMake blobs have 20 unique source sets; their source counts range from 25 to 64 and include different feature-phase combinations. Source registration is not a semantic owner/acceptance decision.

### 16.2 Evolution/cognitive API header differences

Exact candidate/donor header comparisons establish:
- `evolution_experiment.hpp`: donor adds the `isolated` field and a private attestation snapshot binding the experiment identity, proposal/fitness/policy fields, outcome and execution flags; the validity method checks those values have not changed after attestation. Candidate has only `candidate_executed` and no attestation.
- `evolution_experiment_runner.hpp`: donor exposes a dedicated isolated-command API using `ProcessIsolationBackend`; candidate only has the callback runner.
- `evolution_experiment_coordinator.hpp`: donor adds `require_isolation` defaulting true, with simulation/testing explicitly distinguished from adoption policy.
- `evolution_adoption_journal.hpp`: donor records proposal/fitness/policy/isolation identity and exposes compensating `restore_pending`/`restore_adopted` transitions.
- `evolution_controller.hpp`: donor exposes Brain-scoped validate/record/replay/evaluate/adopt/compensate/rollback methods and per-experiment canary storage; candidate's API is narrower.
- `evolution_orchestrator.hpp`: donor accepts trial configuration; its source path checks durable evaluation lifecycle before adoption.
- `developmental_learning.hpp`: absent from candidate, present in donor, and includes bounded finite-input learning signals, associations and context-conditioned strategies.
- `knowledge.hpp`: candidate's `Evidence` type is replaced by donor `KnowledgeEvidence`; this changes the type contract.
- `memory.hpp`: donor adds consolidation metadata/API, latest-sequence-by-kind cursor and kind/exact-match retrieval parameters.
- `cognitive_cycle.hpp`: donor adds structured perception, developmental context, affective/attention signals, action-execution result slots, sequence-bound prediction feedback, goal-outcome assimilation and optional outcome utility.
- `cognitive_runtime.hpp`: donor adds action execute/verify/rollback/consequence adapter, perception providers, feedback queue/capacity and action/feedback metrics. Candidate has no corresponding runtime action-feedback adapter.

These interfaces have cross-file consequences. Header/API availability alone does not establish that the implementations, registration, tests and persistence are consistent.

### 16.3 Integration and persistence suites

| Test path | Candidate | Donor | Alternate blobs | Review note |
|---|---|---|---:|---|
| evolution opportunity orchestration | 17 assertions | 21 | 12 | scheduling/opportunity/evaluation orchestration scenarios vary |
| memory-learning-evolution persistence | absent | 208 lines, custom checks | 11 | donor-only end-to-end learning/action outcome/evolution persistence and restart behavior |
| evolution experiment coordinator | 6 assertions | 6 | 11 | same assertion count; source scenarios differ in trial/isolation policy |
| developmental Brain integration | absent | 1,138 lines / 194 assertions | 8 | donor-only prediction identity, action feedback, strategy generalization, goal/context and persistence scenarios |
| memory architecture | 27 | 70 | 6 | donor covers metadata/corrupt-tail/legacy/consolidation and memory behavior beyond candidate |
| cognitive cycle | 31 | 186 | 5 | donor tests perception/context, feedback, goal/strategy, uncertainty/dispute and persistence integration |

For the persistence suite, checks are explicit helper calls (not C `assert` macros), so an assertion-count of zero from a macro scanner is not a zero-test claim. Its donor test validates that prediction/action outcomes update learning, developmental strategies affect decisions, evolution consumes evidence, and these states/records survive a new Brain instance's journal replay. The developmental integration suite is donor-only; its 194 assertions test sequence-bound prediction resolution, action consequence feedback, developmental generalization, disputed-belief uncertainty, inferred context and restart behavior. These are historical test contracts, not acceptance of the donor architecture.

### 16.4 Engineering message bus and durable task-dispatch variants

- `message_bus.hpp/.cpp`: candidate handler returns void and the bus reports delivery after invoking it. Donor handler returns acceptance, propagates receiver backpressure, retains a bounded deduplication window, tracks in-flight IDs, length-prefixes delivery keys and compares message content to reject conflicting duplicate IDs. This changes delivery semantics/idempotency.
- `engineering/agent.hpp`: donor adds task dependencies and result revision identity fields.
- `engineering/coordinator.cpp`: donor adds durable `dispatch_tracked` flow: checks ledger task/version/queued state, uses stored task as authoritative, authorizes/claims/starts with version transitions, handles execution exceptions, validates returned identity and records failures/results. Candidate has only the small non-ledger dispatch.

The engineering variants are distinct workforce-control-plane contracts. They require exact task-ledger, message-bus, concurrency and authorization consumer/test reconciliation; no adoption is authorized.

### 16.5 Disposition

This slice confirms substantial API, source-registration, persistence, runtime action-feedback, message-delivery and durable-task lifecycle variation. The 162 alternate blobs remain in the audit cohort and are not fully dispositioned. Phase 1 remains OPEN; Phase 2 reverse consumers and Phase 3 authority/retention reconciliation are still required.


## 17. Cognitive-runtime feedback/action execution, safety, codecs and final low-dispersion suite cohort

The final targeted source/test slice covers the remaining 22 path clusters / 62 alternate blobs in the discovery corpus. It is triage coverage; each exact alternate version still needs final disposition and cross-consumer/authority review.

### 17.1 Cognitive runtime action/feedback lifecycle

Candidate `cognitive_runtime.cpp` is 187 lines; donor 225; five alternate blobs. Donor adds bounded feedback queue submission and validation, sequence-bound prediction resolution, optional goal-outcome assimilation and utility feedback, feedback failure accounting, and an action adapter with execute/verify/rollback/consequence-observation callbacks. It executes only actions selected by the plan, not every candidate assessment; unavailable adapters fail closed, execution exceptions are surfaced, and action outcomes can be submitted as evidence. Candidate has only input queue/work-item/result processing and no corresponding action execution/feedback lifecycle. The runtime adapter is an external execution boundary, not autonomous physical access.

### 17.2 Safety and serialization/learning contracts

- `evolution_safety.cpp`: donor rejects non-finite/out-of-range confidence/policy/minimum-improvement fields, requires valid isolation attestation when policy requires it, recomputes whether claimed Improved fitness actually exceeds minimum improvement, then applies regression/confidence gates. Candidate only checks outcome, fitness finiteness, confidence threshold and regression.
- `causal_model.cpp`: donor delegates causal-side encoding/decoding to the typed/escaped causal-link codec; candidate encodes `key=value` and parses on the first equals sign. This can alias keys/values containing delimiters and typed values; exact codec/consumer compatibility is a persistence contract.
- `adaptation.cpp`: donor rejects non-finite inputs without creating/updating a metric, uses scale-relative error for unbounded numeric values, initializes the estimate from the first actual observation, and tracks consecutive surprise/change evidence. Candidate clamps prediction/actual to [0,1], uses absolute error and its prior estimate. This is a learning-model semantic change, not just numeric hygiene.
- `engineering/coordinator.hpp`: donor exposes tracked durable dispatch with task version and base-revision preconditions, paired with the ledger-backed source implementation.
- `cognition.hpp`: donor adds source/reliability evidence, prediction context, disputed-belief flag and confidence fields. `action_execution.hpp` adds observed consequence, consequence error and prediction identity. `cognitive_workspace.hpp` adds structured representation, affect/attention and execution results. `evolution_canary.hpp` adds a non-mutating preview API. `evolution.hpp` adds previous-value restoration.

### 17.3 Remaining test paths — candidate/donor comparison

| Test path | Candidate assertions | Donor assertions | Alternate blobs | Candidate status |
|---|---:|---:|---:|
| knowledge-memory phase 3 | 14 | 14 | 5 | present |
| learning-adaptation phase 8 | 23 | 60 | 5 | present |
| process isolation | 8 | 8 | 4 | present |
| DLT-002 long-run | — | custom-check harness, 479 lines | 3 | absent |
| evolution adoption journal | 8 | 53 | 3 | present (candidate file is a 4-line stub) |
| association causality phase 5 | 12 | 46 | 3 | present |
| cognitive-runtime learning integration | — | 88 | 2 | absent |
| Brain action-consequence integration | — | 95 | 2 | absent |
| developmental learning | — | 63 | 2 | absent |
| cognitive runtime | 19 | 100 | 2 | present |
| DLT-002 persistence | — | 63 | 2 | absent |
| prediction feedback phase 10 | 12 | 371 | 2 | present |

The DLT long-run/persistence suites use custom check helpers rather than `assert` macros, so macro counts are not used as a test-pass claim. The prediction-feedback donor suite contains extensive sequence identity, stale-feedback rejection, persistence/replay and utility/outcome coverage; candidate coverage is substantially smaller. The runtime learning/action-consequence/developmental suites are donor-only path/test artifacts, not candidate test passes.

### 17.4 Cumulative targeted cohort reconciliation

This final slice covers 22 previously unreviewed path clusters / 62 alternate blobs. Combined with the earlier 44 path clusters / 320 alternate blobs, **the targeted corpus is now 66 unique path clusters / 482 alternate blobs**. The all-ref discovery cohort contains 88 paths / 544 alternate blobs, so **22 path clusters / 62 alternate blobs remain untriaged**. The report's cohort accounting is updated accordingly.

The 482 versions have not all received individual semantic disposition; targeted comparisons and feature-family triage are not a substitute for the required per-blob/per-owner/consumer/authority ledger. DF-02 remains OPEN.
