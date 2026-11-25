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


## 18. Final remaining 22-path / 62-blob triage

The final cohort was inspected at exact candidate/donor content where present, with all 62 alternate blob SHA/branch owners and feature signatures enumerated. This completes **targeted triage coverage of the full all-ref alternate cohort: 88 unique donor paths / 544 alternate blobs**. It does not complete the per-version semantic/authority ledger.

### 18.1 Runtime, safety, codec and learning source differences

- `cognitive_runtime.cpp`: five alternate blobs (153–267 lines). Donor action/feedback orchestration was compared with the candidate; alternate families range from priority/work-item runtime prototypes to feedback/action-execution integrations.
- `evolution_safety.cpp`: four alternate blobs. The policy variants range from finite/outcome/confidence checks to isolation and attestation enforcement; exact validation families differ.
- `causal_model.cpp`: three alternate blobs. Typed/escaped codec integration is present on later branches; one early alternate has the smaller phase implementation. These versions must be reconciled with the exact causal-link codec and persistence tests.
- `adaptation.cpp`: two alternate blobs. The relative-error/first-observation/change-response semantics vary; exact scale and prior behavior are not interchangeable.
- Engineering coordinator, cognition, action-execution, evolution, cognitive-workspace and canary headers have two or three alternates each; their API changes cover durable task dispatch, evidence/context/feedback fields, execution/consequence contracts, previous-value restoration, workspace representation/action outcomes and canary preview.

### 18.2 Final test-version cohort

| Test path | Candidate assertions | Donor assertions | Alternate blobs | Notable scope |
|---|---:|---:|---:|---|
| knowledge-memory phase 3 | 14 | 14 | 5 | evidence/feedback, disputed beliefs, contradiction and sequence variants |
| learning-adaptation phase 8 | 23 | 60 | 5 | prediction/adaptation and persistence/learning coverage |
| process isolation | 8 | 8 | 4 | alternate sandbox/attestation/process-boundary scenarios |
| DLT-002 long-run | — | custom checks | 3 | donor-only long-running feedback/behavioral trial harness |
| evolution adoption journal | 8 | 53 | 3 | identity, evaluation/adoption/rollback/replay and attestation |
| association causality phase 5 | 12 | 46 | 3 | changed observations, causal associations, sequence/context persistence |
| cognitive-runtime learning integration | — | 88 | 2 | donor-only action/feedback/utility/goal/context/persistence integration |
| Brain action-consequence integration | — | 95 | 2 | donor-only execute/verify/rollback, consequence and feedback sequence |
| developmental learning | — | 63 | 2 | donor-only contextual strategy learning/generalization |
| cognitive runtime | 19 | 100 | 2 | runtime queue/action/feedback/persistence behavior |
| DLT-002 persistence | — | 63 | 2 | donor-only persistent adaptive trial and restart/replay |
| prediction feedback phase 10 | 12 | 371 | 2 | donor has large sequence/utility/stale-feedback/replay/persistence scenario set |

Custom-check suites are not misclassified as zero tests because they do not use C `assert` macros. Counts are reported only as a comparison indicator. The full content and scenario names are available for further per-blob adjudication.

### 18.3 Coverage boundary and next phase

**All 88 path clusters / 544 alternate blobs have now been enumerated and targeted-triaged.** Individual semantic disposition is still incomplete: source/test versions must be grouped by exact identical content, exact owner/ref provenance, material deltas, dependency/API consumers, build registration, behavior evidence and authority. Some alternate blobs are only feature-signature/metadata triage, not line-by-line semantic acceptance.

The next objective is Phase 2 reverse-consumer/dependency adjudication: reconcile the 40,048 lexical symbol rows and 1,946 exact-path-reference rows by exact consumer blob/context and branch-tip owner; classify compiled/runtime/test/build/workflow/documentation/false-positive; identify API/dependency edges and duplicate owners; link each edge to source/test/build evidence. Candidate-tip consumer evidence and prior compiled-graph reports are inputs, not all-ref closure.

DF-02 remains OPEN. No donor path/blob is accepted, adopted, selected as baseline, retired or deleted by this triage.


## 19. Phase 2 — reverse-consumer graph, candidate-tip registration audit (first slice)

The all-ref lexical consumer table was reconciled against the exact frozen candidate CMake registrations and consumer blob content. This is the first reverse-consumer slice; it does not semantically adjudicate every historical row.

### 19.1 Candidate-tip consumer graph

| Measure | Exact result |
|---|---:|
| Candidate-tip symbol-match rows | 3,441 |
| Donor paths with candidate-tip matches | 111 |
| Candidate-tip symbols matched | 352 |
| Candidate consumer paths/blobs | 193 / 193 |
| Candidate rows by scanner category | 2,050 source; 1,136 test; 219 workflow; 8 build; 28 other |
| Candidate consumer paths by file role | 62 C++ source; 61 header; 49 test source; 11 workflow; 2 build; 7 other |

Candidate current-tip matches include 61 of the 62 registered C++ source files; `brain_novelty.cpp` is the one registered source with no lexical donor-identifier match. The remaining C++ source match is `core/cpp/src/brain_restored_api.cpp`, which is present in the candidate path corpus but is not registered in candidate CMake. This is the same orphan translation unit/duplicate-definition risk described in §10; it is not a compiled consumer.

### 19.2 Candidate test registration cross-check

Candidate CMake registers 45 core test source targets and one engineering test target (46 total). The candidate-tip consumer table contains 49 test source paths; three are not registered in candidate test CMake:
- `core/cpp/tests/brain_smoke.cpp`
- `core/cpp/tests/evolution_experiment_test.cpp`
- `core/cpp/tests/representation_suite.cpp`

This is a registration gap, not a claim those files fail or should automatically be added. Registration, source intent and build/test authority need a separate disposition. The exact candidate CMake source set is 57 core + five engineering production translation units (62 total); test sources are not counted as production compile units.

### 19.3 Candidate absent direct identifiers — high-specificity set

The 502 unique matched symbols divide into 352 present on candidate-tip matches and 150 with no candidate-tip match. A conservative token-shape filter identifies 73 higher-specificity absent identifiers (CamelCase types or long domain API names); this filter is a prioritization aid, not semantic classification.

Examples of historically present, candidate-absent APIs with exact source/test contexts:
- `run_isolated_command` — 416 match rows, eight consumer paths, six donor paths; no candidate-tip occurrence.
- `has_valid_isolation_attestation` — 74 rows, 11 consumer paths.
- `observe_canary_for_brain` — 138 rows; `preview_canary_for_brain` — 84 rows.
- `validate_adoption_for_brain`, `compensate_adoption_for_brain`, `record_evaluation_for_brain`, `rollback_for_brain` and replay methods — exact source/test consumers across the evolution lifecycle.
- `resolve_prediction_feedback`, `apply_prediction_feedback`, `PredictionFeedbackStatus`, `PredictionContext` and `latest_sequence_by_kind` — historical prediction identity/feedback and memory cursor APIs.
- `DevelopmentalLearning`, `developmental_strategies`, `best_related_strategy`, `choose_with_developmental_learning`, `AffectiveLearningModel`, `AffectiveOutcomeEvidence` and affective/context APIs — historical cognitive-learning consumers.
- `EngineeringTaskLedger`, `EngineeringTaskRecord`, `EngineeringTaskStatus` — historical durable workforce-task consumers.
- `decode_causal_side`/`encode_causal_side` — historical codec consumers.

The high-frequency generic tokens `restored`, `observe`, `evaluate`, `rollback`, `policy`, `confidence`, `journal` and `append` generate substantial lexical over-approximation. Context inspection confirms false positives such as prose/workflow phrases and unrelated generic method names. These are not dependency edges unless the exact token context and API semantics support that relationship.

### 19.4 Historical-only reverse-consumer table

The remaining 36,607 rows are historical-ref-only matches: 118 donor paths, 497 symbols, 270 consumer paths and 942 exact consumer blobs. Category totals: 21,898 source; 13,838 test; 642 workflow; 229 build. Across all refs, the table covers 118 donor paths, 502 matched symbols, 346 consumer paths and 1,135 consumer blobs. Historical branch matches are evidence of branch-local consumer candidates; they do not imply current candidate dependency or a later/approved owner.

The `unique_tip_count` field is preserved for each match. Rows present on only one unique branch tip are branch-local evidence requiring owner/provenance review; multi-tip presence does not prove equivalent semantics or acceptance.

### 19.5 Exact-path reference candidates

The 1,946 exact-path-reference rows cover all 159 donor paths, 76 consumer paths and 101 blobs: 1,930 documentation, 15 workflow and one other-category reference. 736 are candidate-tip and 1,210 historical-only. These are primarily planning/inventory/review lineage citations, not code dependency edges. The top consumers include the whole-Brain integration map, Gate-A baseline/provenance reports and the DF-02 inventory/semantic reports; their authority and status must be classified individually, not treated as runtime ownership.

### 19.6 First-slice disposition and next work

Completed for this slice: exact candidate-tip graph aggregation, candidate CMake production/test registration cross-check, high-specificity absent-token prioritization and sampled context classification. Confirmed one candidate orphan production translation unit and three candidate test-source registration gaps. No donor dependency/adoption is inferred.

**Phase 2 remains OPEN.** Next: build a donor-path → exact symbol/context → consumer blob/ref-owner matrix; review the 73 high-specificity absent tokens and all 352 candidate-present symbols for true API/dependency edges; then adjudicate the 36,607 historical-only rows by branch/blob, category, compiled registration and lineage. Full semantic closure and authority/retention work remain mandatory.


## 20. Candidate C++ include-graph cross-check

A recursive include reachability pass was run over the exact candidate-tip source contents and CMake-registered production/test source sets, using the 193 candidate consumer blobs.

- Candidate registered production translation units: 62 (57 core + five engineering).
- Candidate matched header paths: 61.
- Direct production includes: 59 unique matched headers; recursive production reachability: 61/61.
- Registered test translation units: 46 (45 core + one engineering).
- Direct test includes: 43 unique matched headers; recursive test reachability: 60/61.
- All 61 matched headers are reachable from either registered production or registered tests; no matched header was left unreachable.

This cross-check is separate from lexical symbol-match rows. It establishes current candidate include reachability for these files; it does not prove semantic ownership, runtime use, or dependency equivalence to donor. The unregistered `brain_restored_api.cpp` is intentionally outside the compiled-source graph, and the three unregistered test files are outside the registered-test graph.

## 21. Candidate-tip graph slice — status

Candidate-tip registration and include reachability have been reconciled. The 352 candidate-present symbols still require exact-context review; the 73 high-specificity candidate-absent identifiers require historical branch-owner and consumer-lineage adjudication. The 36,607 historical-only rows and 1,210 historical exact-path refs remain open. Phase 2 is IN PROGRESS; this is not a full dependency or ownership closure.


## 22. Candidate-absent high-specificity consumer triage

The 150 candidate-absent matched symbols were separated by token specificity. A conservative filter yields 73 higher-specificity identifiers (domain APIs/types or long underscore APIs); the remaining 77 are mostly generic/ambiguous identifiers and remain context-dependent. The 73 are a prioritization set, not 73 proven dependencies.

### 22.1 Direct historical consumer evidence

| API/identifier | Match rows | Consumer paths | Donor paths | First inspected context |
|---|---:|---:|---:|---|
| `run_isolated_command` | 416 | 8 | 6 | coordinator calls isolated runner |
| `observe_canary_for_brain` | 138 | 5 | 2 | Brain delegates canary observation |
| `preview_canary_for_brain` | 84 | 4 | 2 | restored API exposes preview |
| `has_valid_isolation_attestation` | 74 | 11 | 1 | restored API serializes attestation validity |
| `observe_association` | 74 | 5 | 2 | developmental-learning association observation |
| `validate_adoption_for_brain` | 74 | 5 | 2 | Brain gates adoption on controller validation |
| `compensate_adoption_for_brain` | 62 | 4 | 2 | Brain/controller compensation path |
| `resolve_prediction_feedback` | 59 | 10 | 1 | sequence-bound feedback API |
| `apply_prediction_feedback` | 59 | 3 | 2 | association-model feedback assimilation |
| `record_evaluation_for_brain` | 56 | 4 | 2 | evaluation record gate |
| `rollback_for_brain` | 56 | 4 | 2 | journaled Brain rollback |
| `attest_isolated_result` | 47 | 4 | 1 | experiment attestation creation |
| `PredictionFeedbackStatus` | 39 | 8 | 1 | feedback status contract |
| `DevelopmentalLearning` | 28 | 8 | 1 | Brain developmental subsystem type |
| `EngineeringTaskLedger` | 15 | 6 | 3 | durable engineering task-ledger declaration/use |
| `decode_causal_side` | 15 | 4 | 4 | typed causal-side decoder call |

Other specific historical consumer tokens cover previous-value restoration, evaluator evidence, prediction contexts, memory sequence cursors, developmental/affective learning and strategy APIs, action consequence/verification, goal-outcome feedback, and donor-only integration-test/world types. Each must be linked to exact branch/blob owner and consumer role before it becomes a dependency edge.

### 22.2 Context classification boundary

Sampled exact source contexts confirm that the high-specificity rows above are real API/type/call references in historical blobs, but their ownership and current applicability remain unresolved. Other scanner rows for generic names such as `restored`, `observe`, `evaluate`, `rollback`, `policy`, `confidence`, `journal` and `append` are often prose, unrelated functions, test helper names or workflow text. The scanner is an over-approximation; no row is promoted to a dependency based on token match alone.

### 22.3 Next bounded work

Prioritize the 73 higher-specificity absent identifiers: group by exact donor blob and historical owner; inspect declaration/definition/call sites; map include/API edges and build/test registration; classify production, test-only, workflow, docs and false-positive; reconcile duplicates and behavioral evidence. Then review the 352 candidate-present symbols in the same exact-context manner. The 36,607 historical-only rows remain a large branch-specific cohort and must be filtered by exact blob/tip/category before conclusions.

Phase 2 remains OPEN. This triage identifies high-value consumer edges; it does not prove ownership, dependency closure, adoption or retirement authority.


## 23. Exact-token code-context filter across the 40,048 consumer rows

A second independent context filter scanned the full content for each row's exact identifier using token boundaries, and stripped C++ comments and string literals (simple lexical stripping, not a full compiler lexer). It classified rows as code-context or comment/string-only. Workflow/build/other text remains raw-text classification.

| Row cohort | Code-context rows | Comment/string-only rows | Total |
|---|---:|---:|---:|
| Candidate-tip | 3,325 | 116 | 3,441 |
| Historical-only | 31,921 | 4,686 | 36,607 |
| All refs | 35,246 | 4,802 | 40,048 |

By category across all refs: source 21,370 code-context / 2,578 comment-string; test 12,750 / 2,224; workflow 861 raw-text matches; build 237; other 28. Candidate source: 1,981 code-context / 69 comment-string; candidate test: 1,089 / 47; workflow219, build8, other28.

This removes comment/string-only lexical matches from the direct-code priority queue. **Code-context is not semantic dependency proof**: generic names such as `observe`, `restored`, `evaluate`, `policy`, `confidence`, `rollback` can still be unrelated method calls/fields. Raw-text matches in workflow/build/docs are classified separately. The simple comment/string stripper can miss C++ raw-string edge cases; the report does not claim compiler-level tokenization.

### Phase 2 queue after context filtering

1. Candidate-tip code-context rows (3,325): exact source/header/test/build registration and direct API context, with high-specificity and donor-path-specific symbols first.
2. Historical-only code-context rows (31,921): exact blob/ref owner and branch-lineage grouping, then production/test/build/workflow role and dependency classification.
3. Comment/string-only rows (4,802): classify as documentation/annotation/test fixture or false-positive candidate; retain useful provenance/intent without creating dependency edges.
4. Exact path references (1,946): documentary/workflow lineage and authority/status cross-check.

Phase 2 remains OPEN; this filter is a prioritization/false-positive reduction, not full consumer adjudication.


## 24. Exact consumer blob-to-donor-path ownership cross-map

The 1,135 unique consumer blob records were cross-mapped by exact `(consumer_path, blob_sha)` against the 798 donor-path/blob ownership rows. This is content identity and ref-owner evidence, not semantic ownership:

| Consumer blob cohort | Exact same-path donor ownership row | No exact same-path donor ownership row | Total |
|---|---:|---:|---:|
| Candidate-tip | 96 | 97 | 193 |
| Historical-only | 691 | 251 | 942 |
| All refs | 787 | 348 | 1,135 |

The 97 candidate non-owner consumer blobs span 97 paths: 31 headers, 29 source files, 22 test sources, eight workflows and seven other files. The 251 historical non-owner blob versions span 123 paths: 90 test, 72 source, 67 header, 18 workflow and four other path-role entries (path-role counts are not mutually exclusive across blob versions). Exact content and tip SHA owners are preserved in the scan corpus.

The 787 same-path exact matches are historical/candidate versions of files already in the 159 donor-path inventory. They can be mapped to the donor-path version ledger by exact SHA. The 348 non-owner consumer blobs are a distinct reverse-consumer cohort outside exact same-path donor ownership; their API/context, dependency, registration and branch lineage must be reviewed rather than inferred from path identity.

### Historical-only consumer concentration

The historical-only 36,607 rows are concentrated: top five consumer paths contribute 15,320 rows (41.8%); top 20 contribute 24,305 (66.4%); top 50 contribute 29,890 (81.7%). The top 20 exact paths/blob counts are recorded below and should be prioritized by material API/behavior changes and owner tips:

| Consumer path | Rows | Blobs | Donor paths | Symbols |
|---|---:|---:|---:|---:|
| `core/cpp/src/brain.cpp` | 5,656 | 34 | 90 | 176 |
| `core/cpp/src/brain_restored_api.cpp` | 3,369 | 19 | 60 | 110 |
| `core/cpp/include/jarvis/core/brain.hpp` | 3,131 | 20 | 79 | 151 |
| `core/cpp/src/evolution_controller.cpp` | 1,628 | 18 | 68 | 59 |
| `core/cpp/tests/evolution_brain_integration_suite.cpp` | 1,536 | 23 | 74 | 67 |
| `core/cpp/tests/evolution_canary_controller_suite.cpp` | 1,287 | 16 | 54 | 38 |
| `core/cpp/tests/developmental_brain_integration_suite.cpp` | 1,204 | 9 | 81 | 80 |
| `core/cpp/tests/memory_learning_evolution_persistence_suite.cpp` | 1,083 | 12 | 61 | 55 |
| `core/cpp/src/cognitive_cycle.cpp` | 953 | 9 | 63 | 85 |
| `core/cpp/tests/cognitive_cycle_suite.cpp` | 575 | 6 | 68 | 66 |
| `core/cpp/tests/evolution_experiment_runner_suite.cpp` | 516 | 17 | 53 | 25 |
| `core/cpp/src/evolution_experiment_runner.cpp` | 466 | 16 | 28 | 27 |
| `core/cpp/tests/knowledge_source_feedback_suite.cpp` | 431 | 7 | 53 | 26 |
| `core/cpp/tests/memory_architecture_suite.cpp` | 413 | 7 | 38 | 28 |
| `core/cpp/tests/evolution_opportunity_orchestration_suite.cpp` | 375 | 13 | 22 | 22 |
| `core/cpp/src/evolution_orchestrator.cpp` | 373 | 9 | 27 | 23 |
| `core/cpp/src/evolution_experiment_coordinator.cpp` | 335 | 12 | 21 | 19 |
| `core/cpp/tests/evolution_adoption_journal_suite.cpp` | 333 | 4 | 56 | 36 |
| `core/cpp/tests/dlt_002_long_run.cpp` | 322 | 4 | 42 | 47 |
| `core/cpp/src/memory.cpp` | 319 | 8 | 23 | 41 |

Across the historical-only rows, 18,246 matches (49.8%) occur on one unique branch tip. This is branch-local evidence; one-tip presence is not proof of authority or correctness. Multi-tip presence is not semantic equivalence either. Branch-tip SHA and exact blob owners remain required.

### Disposition

This cross-map reduces the historical reverse-consumer queue to exact content ownership groups and prioritizes the 20 most concentrated paths. Phase 2 remains OPEN; the 348 non-owner blobs and all owner-linked consumer relationships require contextual/dependency/authority adjudication.


## 25. Consumer blob owner-tip lineage crosswalk

The `consumer_blob_sources.jsonl` occurrence records were reconciled to `unique_branch_tips.csv` (213 unique tip SHAs, 254 branch refs). Each of the 1,135 unique consumer blobs has exact path/category, branch names, tip SHA list and tip count. This is lineage/identity evidence, not authority.

| Consumer blob set | Unique blobs | Tip-count distribution observation |
|---|---:|---|
| Candidate-tip blobs | 193 | content is widely shared; median occurrence tip count 136, with some blobs on 212 unique tips |
| Historical-only blobs | 942 | median tip count 2; 461 blobs occur on exactly one unique tip; 76 blobs occur on 76 tips |
| All consumer blobs | 1,135 | occurrence metadata covers 253 branch names across the scanned refs |

The exact tip SHA/branch-owner mapping is preserved in the downloaded scan artifact. Historical one-tip blobs are branch-local content candidates and should be reviewed by branch/ref provenance. Shared content across many tips is an exact-blob reuse fact; it does not prove semantic equivalence of surrounding files, approval, or owner authority.

This crosswalk closes the **metadata owner-tip mapping step** for the consumer corpus. The semantic lineage step remains open: identify which branch is a successor, experiment, duplicate, abandoned fork or authorized source; reconcile each material API/capability and test/build edge; document authority and preservation/retirement constraints. No branch is chosen based on branch name, tip count, recency or blob sharing.


## 26. High-specificity candidate-absent tokens — code-context classification

The 73 prioritized identifiers account for 2,410 historical-only match rows. The exact-token/comment-strip filter classifies **2,375 as code-context** and 35 as comment/string-only. The prioritization set is divided into the following non-overlapping token families:

| Family | Tokens | Match rows |
|---|---:|---:|
| Evolution trust/isolation/adoption/canary | 13 | 1,217 |
| Prediction/context/feedback | 9 | 272 |
| Developmental/affective learning | 29 | 627 |
| Engineering workforce/task | 5 | 51 |
| Causal/knowledge evidence | 5 | 96 |
| Other high-specificity API/type names | 12 | 147 |
| **Total** | **73** | **2,410** |

Representative high-specificity names and exact contexts are in §22. This classification prioritizes code/API consumer edges rather than comment/string mentions; it still does not establish whether a call is a valid dependency, intended successor, duplicate implementation, test-only consumer or approved owner.

### Candidate-present symbol context

The 352 candidate-present matched symbols contribute 3,441 rows: 3,325 code-context and 116 comment/string-only. Among source/test rows, 1,981 source/header and 1,089 test rows are code-context; 69 source/header and 47 test rows are comment/string-only. The remaining candidate workflow/build/other matches are raw-text/context evidence.

The highest-frequency candidate identifiers are generic `observe` (377 rows), `restored` (294), `evaluate` (241), `policy` (140), `confidence` (118) and `rollback` (108). These require exact API context before creating a dependency edge. The 352-symbol candidate set is not yet semantically closed.
