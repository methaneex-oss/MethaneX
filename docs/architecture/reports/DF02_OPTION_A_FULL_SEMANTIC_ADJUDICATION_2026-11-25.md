# DF-02 Full Option A Semantic Adjudication — Execution Record

**Status updated:** 2026-11-26  
**Project Director decision:** D2 = B — full Option A semantic and authority adjudication required.  
**Frozen review target:** PR #192 SHA `caf87986dfea7aca75728818651c8687e9f5faf0`; donor PR #97 HEAD `c1da222e6c94aeb3f2ad000392c21fe4fc81ab25`.

## Controlling phase disposition (2026-11-26)

- **Phase 0 — evidence acquisition/integrity: COMPLETE.**
- **Phase 1 — targeted triage coverage: COMPLETE** across 88 donor-path clusters / 544 alternate blobs. This is coverage triage, not per-version semantic closure.
- **Phase 2 — consumer graph/evidence indexing: PARTIALLY COMPLETE.** Candidate CMake/include reachability, consumer blob/ref-owner cross-map, identifier partitions and context filtering reconciled. Exact semantic API/dependency edges remain unresolved.
- **Phase 3 — duplicate capabilities/owners, branch authority, provenance and retention/retirement: NOT COMPLETE.**
- **Phase 4 — sourced 159-path closure ledger and independent scrutiny: NOT COMPLETE.**
- **DF-02: OPEN.** No historical version selected, adopted, baseline-authorized, retired or deleted.

Planning scope is frozen against expansion; the consolidated status and handoff is in `docs/architecture/plans/JARVIS_DOCUMENTATION_PLANNING_FOUNDATION_FINALIZATION_2026-11-26.md`. This freeze does not substitute for DF-02 completion or Foundation acceptance.

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

The 97 candidate non-owner consumer blobs span 97 paths: 31 headers, 29 source files, 22 test sources, eight workflows and seven other files. The 251 historical non-owner blob versions span 123 paths: 90 test, 72 source, 67 header, 18 workflow and four other path-role entries (counts are consumer blob versions, so a path with multiple versions contributes more than once). Exact content and tip SHA owners are preserved in the scan corpus.

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


## 27. High-specificity absent-token consumer role and path concentration

The 73-token set is further partitioned by consumer role: 1,651 source/header rows, 756 test rows and three workflow rows; 2,375 of these are code-context (1,617 source/header and 755 test, with three workflow text matches). The tokens occur across 105 consumer paths and 44 donor paths.

The largest historical consumers for this set are `brain_restored_api.cpp` (457 rows), `brain.cpp` (422), `brain.hpp` (206), `evolution_controller.cpp` (145), the evolution Brain/canary/runner integration suites, `evolution_experiment_runner.cpp`, memory-learning-evolution persistence, cognitive cycle, coordinator, developmental-learning source and related tests.

The most concentrated donor-path identifiers are `evolution_controller.hpp` (371 rows), `brain_restored_api.cpp` (350), `evolution_controller.cpp` (263), `developmental_learning.hpp` (208), `evolution_experiment.hpp` (121), and `developmental_learning.cpp` (95). These direct source/test contexts are prioritized for semantic owner and dependency review; counts do not establish capability ownership or adoption.


## 28. Candidate-present vs historical-only identifier specificity split

Using the same conservative token-shape filter across all 502 matched identifiers, historical rows for candidate-present tokens are kept separate from candidate absence:

| Specificity cohort | Symbols | Candidate rows | Historical-only rows |
|---|---:|---:|---:|
| Higher-specificity, candidate-present | 157 | 638 | 6,927 |
| Higher-specificity, candidate-absent | 73 | — | 2,410 |
| Lower-specificity/ambiguous, candidate-present | 195 | 2,803 | 25,166 |
| Lower-specificity/ambiguous, candidate-absent | 77 | — | 2,104 |
| **Totals** | **502** | **3,441** | **36,607** |

The all-ref high-specificity cohort is 230 symbols/9,975 rows; the lower-specificity cohort is 272 symbols/30,073 rows. The high-specificity candidate-present cohort has 638 rows (627 code-context, 11 comment/string-only); the historical versions of those same candidate-present symbols contribute 6,927 rows (6,819 code-context,108 comment/string-only). The candidate-absent high-specificity cohort contributes 2,410 historical rows (2,375 code-context,35 comment/string-only).

The lower-specificity cohort has 2,803 candidate rows (2,698 code-context,105 comment/string-only), 25,166 historical rows for candidate-present tokens (20,963 code-context,4,203 comment/string-only), and 2,104 historical rows for candidate-absent tokens (1,764 code-context,340 comment/string-only).

The split prioritizes API/type names and longer domain identifiers. It does not make high-specificity rows true dependencies automatically, nor lower-specificity rows false positives. Exact declaration/call context, owner SHA, include/build/test role and authority remain required evidence.


## 29. Candidate-present high-specificity API context

The 157 higher-specificity candidate-present identifiers account for 638 rows across 126 consumer paths / 52 donor paths. The comment/string-strip filter leaves **627 code-context** rows and 11 comment/string-only. Role totals: 389 source/header, 199 test, 49 workflow and one build row.

The strongest candidate-present names include `EvolutionExperiment` (25 rows/25 paths), `CandidateAction` (22/22), `EvolutionModel` (22/12), `EvolutionProposal` (21/21), `ExperimentOutcome` (21/21), `EvolutionController` (19/7), `AttentionSignal` (18/10), `register_evolution_parameter` (14/8), `ActionAssessment` (10/10), `EvolutionSandbox` (10/10), `CognitiveCycleInput` (9/9), `CognitiveRuntime` (8/5), `AgentMessageBus` (8/5), and `EvolutionExperimentCoordinator` (7/4). This is a candidate API/context map, not an acceptance statement for every historical variant.

The remaining 195 candidate-present lower-specificity symbols account for 2,803 rows. Exact source context and consumer roles still need semantic classification; generic tokens are not treated as dependencies.


## 30. Manually promoted lower-specificity historical API tokens

The conservative token-shape filter misses short but semantically meaningful names. Twenty-one lower-specificity candidate-absent tokens were promoted after exact source/test context review. They account for **1,486 rows** across source/test consumers; these remain candidate historical API/dependency edges, not authority decisions.

| Token | Rows | Consumer paths | Donor paths | Role |
|---|---:|---:|---|
| `consolidate` | 212 | 8 | 4 | memory consolidation |
| `attest_isolated` | 122 | 5 | 3 | isolation attestation (tests) |
| `replay_adoption` | 108 | 5 | 2 | adoption-journal replay |
| `replay_rollback` | 108 | 5 | 2 | rollback replay |
| `replay_evaluation` | 100 | 4 | 2 | evaluation replay |
| `preview` | 98 | 5 | 2 | canary preview |
| `restore_previous` | 92 | 5 | 2 | prior-state restoration |
| `observe_strategy` | 86 | 8 | 2 | developmental strategy observation |
| `await_result` | 62 | 8 | 6 | isolated runner result handling |
| `prediction_error` | 61 | 16 | 1 | prediction/feedback error |
| `adoption_journal` | 59 | 5 | 1 | journal contract |
| `adopt_for_brain` | 56 | 4 | 2 | Brain adoption API |
| `restore_pending` | 55 | 4 | 2 | journal compensation transition |
| `restore_adopted` | 55 | 4 | 2 | journal compensation transition |
| `find_prediction` | 40 | 3 | 1 | prediction-memory retrieval |
| `set_context` | 26 | 10 | 2 | contextual state/strategy APIs |
| `strategy_value` | 25 | 6 | 3 | developmental strategy valuation |
| `restored_cycle` | 24 | 3 | 3 | cognitive-cycle restore tests |
| `score_for` | 20 | 2 | 2 | evolution scoring tests |
| `attention_policy` | 19 | 6 | 1 | attention policy |
| `numeric_value` | 58 | 3 | 2 | typed causal-value representation |

These 21 names are manually prioritized above the remaining 56 lower-specificity candidate-absent tokens (618 rows). The 195 candidate-present lower-specificity tokens (2,803 rows) remain context-ambiguous. This demonstrates that token-shape heuristics alone are insufficient; the semantic review must include source/API meaning, exact branch owners and test/build consumers.


## 31. Candidate-only identifiers — no historical consumer match

Exact symbol-set comparison: 352 candidate-tip matched identifiers, 497 historical-only matched identifiers, 347 shared, **five candidate-only identifiers** and 150 historical-only identifiers. The five candidate-only identifiers occur in ten candidate rows:

| Identifier | Rows | Candidate consumers | Donor-path match |
|---|---:|---|---|
| `clamp_unit` | 1 | `core/cpp/src/evolution_opportunity.cpp` | `affective_learning.hpp` |
| `for_parameter` | 3 | `evolution_history.hpp`, `evolution_learning.cpp`, `evolution_strategy.cpp` | `evolution_history.cpp` |
| `jarvis_cognitive_trigger_suite` | 1 | `core/cpp/tests/cognitive_trigger_suite.cpp` | test CMake path |
| `perceive` | 3 | perception pipeline header/source/test | cognitive-runtime suite path |
| `should_rollback` | 2 | evolution rollback header/source | evolution controller path |

These are candidate-tip-only lexical identifiers, not proven novel capabilities. Their exact current consumers and build/test registrations are recorded; review whether they represent candidate additions, renamed interfaces, private helpers, or scanner artifacts. The five-token result also means the historical scan has no match for these names, not that the historical architecture lacked equivalent behavior.


## 32. Remaining lower-specificity absent tokens — exact context split

The 56 lower-specificity candidate-absent tokens left after the 21 manually promoted names were individually checked against exact consumer content. They divide into:

| Context cohort | Tokens | Rows | Role |
|---|---:|---:|---|
| Additional code-context candidates | 51 | 502 | 227 source, 252 test, 23 workflow-text rows; exact token appears in code context for source/test, but semantic relation remains unresolved |
| Comment/string-only | 5 | 116 | `instead` (58), `reconstructed` (45), `predictor` (7), `experienced` (5), `damaged` (1) |

The 51 code-context tokens include short cognitive-runtime feedback/queue APIs (`submit_feedback`, `pending_feedback`, `process_feedback`, `wait_for_feedback`, `publish_result`, `execute_actions`), engineering ledger/message-bus functions (`requeue`, `dispatch_tracked`, `delivery_key`, `same_content`, `commit_record`, `append_record`, `load_locked`, `execvp`), developmental-world APIs (`add_action`, `reset_episode`, `available_actions`, `step_count`, `set_state`, `true_state`), causal/adaptation (`predictor`, `observe_outcome`, `integer_value`, `learning_rate`, `modulate`), and memory/learning/test helpers (`for_key`, `record_prediction`, `record_experience`, `latest_unresolved`, `copy_file`, `serialize`, `parse_double`, `replayed_behavior`, `strategy_brain`, `concept_brain`, etc.). Generic words `changed`, `direct`, `learner`, `resolve`, `accumulated` and `generalized` require careful semantic context despite code-context occurrence.

Thus the 77 lower-specificity candidate-absent identifiers are fully partitioned by exact context: 21 manually prioritized API/type names (1,486 rows; 1,262 code-context/224 comments), 51 additional code-context names (502 rows), and five text-only names (116 rows). This is a context filter, not dependency/authority closure.


## 33. Exact-content reverse-consumer cross-map — complete identifier partition

The frozen artifact's 502-symbol set was re-partitioned by **symbol presence on the frozen candidate tip**, correcting the row-level distinction between candidate-present symbols with historical rows and genuinely candidate-absent identifiers. The complete partition reconciles to all 40,048 discovery rows:

| Cohort | Symbols | Match rows | Consumer paths | Exact consumer blobs | Donor paths |
|---|---:|---:|---:|---:|---:|
| Candidate-present identifiers (candidate + historical matches) | 352 | 35,534 | 346 | 1,135 | 111 |
| Candidate-absent identifiers (historical-only) | 150 | 4,514 | 148 | 480 | 75 |
| **Total** | **502** | **40,048** | **346** | **1,135** | **118** |

Candidate-present rows split into 3,441 candidate-tip and 32,093 historical rows. Candidate-absent rows are all historical-only. These are unique symbol/path/blob discovery dimensions, not unique dependencies. Exact blob SHA, owner tips and full consumer contents are available in the scan artifact and were re-read locally for this cross-map.
**Count interpretation:** row counts are additive across the two symbol cohorts; consumer-path, consumer-blob and donor-path counts are distinct-set sizes and therefore overlap between cohorts. The union values in the total row are deduplicated. The candidate-present cohort contains historical rows for symbols also present on the frozen candidate; these are not candidate-absent symbols.


### 33.1 Candidate-absent, high-priority exact-context findings

The candidate-absent cohort is 2,894 source rows, 1,594 test rows and 26 workflow-text rows. It is concentrated in the cognitive Brain/evolution lifecycle and its historical tests. Selected exact-context API/type evidence:

| Identifier | Rows | Consumer paths | Exact blobs | Role split | Exact-context interpretation |
|---|---:|---:|---:|---|---|
| `run_isolated_command` | 416 | 8 | 82 | source 161 / test 255 | Coordinator/runner and integration tests call isolated experiment execution |
| `consolidate` | 212 | 8 | 212 | source/test | Memory consolidation APIs and test scenarios |
| `observe_canary_for_brain` | 138 | 5 | 77 | source 108 / test 30 | Brain-to-controller canary observation integration |
| `attest_isolated` | 122 | 5 | 122 | source/test | Isolation-attestation APIs and test evidence |
| `replay_adoption` | 108 | 5 | 108 | source/test | Adoption journal replay lifecycle |
| `replay_rollback` | 108 | 5 | 108 | source/test | Rollback journal replay lifecycle |
| `replay_evaluation` | 100 | 4 | 100 | source/test | Evaluation-record replay lifecycle |
| `preview` | 98 | 5 | 98 | source/test | Canary preview interfaces/scenarios |
| `restore_previous` | 92 | 5 | 92 | source/test | Previous-value compensation/restore paths |
| `observe_strategy` | 86 | 8 | 86 | source/test | Developmental strategy observation |
| `preview_canary_for_brain` | 84 | 4 | 50 | source 54 / test 30 | Brain-facing preview API consumer |
| `observe_association` | 74 | 5 | 74 | source/test | Developmental/association learning consumer |
| `validate_adoption_for_brain` | 74 | 5 | 45 | source 72 / test 2 | Brain-level adoption validation call |
| `has_valid_isolation_attestation` | 74 | 11 | 74 | source 29 / test 45 | Evidence-validation and serialized attestation validity |
| `compensate_adoption_for_brain` | 62 | 4 | 39 | source 54 / test 8 | Brain/controller compensation contract |
| `await_result` | 62 | 8 | 62 | source/test | Isolated runner result handling |
| `resolve_prediction_feedback` | 59 | 10 | 59 | source 45 / test 14 | Sequence-bound prediction feedback consumer |
| `apply_prediction_feedback` | 59 | 3 | 31 | source | Association/model feedback assimilation |
| `record_evaluation_for_brain` | 56 | 4 | 36 | source 54 / test 2 | Evaluation-record lifecycle integration |
| `rollback_for_brain` | 56 | 4 | 36 | source 54 / test 2 | Journaled rollback integration |
| `attest_isolated_result` | 47 | 4 | 47 | source | Experiment attestation creation |
| `PredictionFeedbackStatus` | 39 | 8 | 39 | source 25 / test 14 | Prediction-feedback status contract |
| `DevelopmentalLearning` | 28 | 8 | 28 | source 18 / test 10 | Brain developmental-learning subsystem |
| `EngineeringTaskLedger` | 15 | 6 | 6 | source 9 / test 6 | Durable workforce-task ledger declarations/uses |
| `decode_causal_side` | 15 | 4 | 5 | source 12 / test 3 | Typed causal-side codec call sites |

The catalog also contains the remaining 125 candidate-absent identifiers, including affective/developmental/world APIs, prediction-context and sequence-cursor contracts, engineering-ledger APIs, and test-only target names. Candidate absence alone is not a semantic gap: names can be renamed, private, branch-specific, test-only or false-positive. The above exact contexts establish historical use, not ownership or adoption authority.

### 33.2 Candidate-present symbol partition

The 352 candidate-present identifiers account for 35,534 discovery rows: 21,054 source, 13,380 test, 835 workflow, 237 build and 28 other. Historical rows for these identifiers must not be misclassified as absent dependencies. The high-frequency tokens are lexical over-approximations and remain context review targets: `restored` (3,143 rows), `observe` (2,232), `evaluate` (1,625), `rollback` (1,177), `policy` (1,038), `confidence` (827), `journal` (733), `append` (569), `isolated` (505), `records` (484), `predict` (422), `parameter` (402), `associations` (370), `observe_capability` (333), `resolve_prediction` (306), and `EvolutionExperiment` (301).

The most concentrated exact consumer paths remain `brain.cpp` (4,836 candidate-present rows), `brain.hpp` (3,063), `brain_restored_api.cpp` (2,934), evolution Brain integration (1,371), `evolution_controller.cpp` (1,345), developmental Brain integration (1,098), canary-controller tests (1,066), memory-learning-evolution persistence (934), cognitive cycle (913), and memory architecture (427). This list is prioritization only; generic identifiers require declaration/call and dependency semantics before classification.

### 33.3 What this slice closes and what it does not

Closed for the frozen scan: symbol-presence partition, exact consumer-path/blob counts, owner-tip metadata cross-map, and candidate-absent token set. The discovery-row totals reconcile (35,534 + 4,514 = 40,048). It reduces ambiguity in the audit queue and makes the historical-only API cohort reproducible.

Still open: exact semantic dependency classification across the 1,135 blobs, complete per-symbol declaration/call/include/build/test edge dispositions, competing-owner/capability equivalence, branch authority and provenance/retention. This slice is evidence-index completion—not DF-02 closure, adoption, retirement, or baseline selection.


## 34. Builder self-review of §33 reconciliation

Recomputed from the downloaded artifact tables and full consumer-blob source corpus:

- Identifier union: 352 candidate-present + 150 candidate-absent = 502 unique identifiers.
- Discovery-row arithmetic: 35,534 candidate-present + 4,514 candidate-absent = 40,048 rows.
- Category arithmetic: candidate-present source 21,054 + test 13,380 + workflow 835 + build 237 + other 28 = 35,534; candidate-absent source 2,894 + test 1,594 + workflow 26 = 4,514.
- Distinct-set counts were checked against the full row table: 346 consumer paths and 1,135 consumer blobs overall; path/blob/tip dimensions overlap between cohorts and are not additive.
- Artifact ZIP digest recomputed locally and matches the recorded SHA-256.
- At the §34 self-review point, report, planning index and continuity checkpoint were synchronized on PR #203; that point-in-time compare showed three documentation paths only. Later §35–36 finalization and archive commits expanded the current PR to five documentation paths. The current PR changed-path list is the controlling inventory; no runtime source or frozen PR #192 file changed.

**Self-review result:** §33's arithmetic and scope boundaries are consistent. Remaining semantic work is accurately marked OPEN. This is Builder self-review only; it is not independent review, DF-02 closure, DF-09 CLEAR, or Director acceptance.


## 35. 2026-11-26 — planning foundation freeze and phase disposition

The documentation/planning package has been consolidated into `docs/architecture/plans/JARVIS_DOCUMENTATION_PLANNING_FOUNDATION_FINALIZATION_2026-11-26.md`. The planning index and Builder continuity checkpoint are synchronized on the same follow-up branch. Planning is frozen against expansion: no competing roadmap, architecture rewrite or optional review loop is authorized absent a material contradiction, required gate finding or Project Director decision.

This freeze is a churn-control disposition, **not** Foundation acceptance and not a shortcut around Director decision D2=B (full DF-02 Option A). Phase dispositions:

| Phase | Disposition | Exact boundary |
|---|---|---|
| 0 — evidence acquisition/integrity | COMPLETE | Frozen all-ref artifact/hash and donor/candidate/alternate content verified |
| 1 — targeted path/version triage | COMPLETE for coverage | All 88 path clusters / 544 alternate blobs enumerated and targeted-triaged; not individual semantic disposition |
| 2 — consumer graph/indexing | PARTIALLY COMPLETE | Candidate CMake/include reachability, blob/ref owner cross-map, symbol cohort and context partition reconciled; semantic API/dependency edge dispositions incomplete |
| 3 — duplicate capability/owner and authority/provenance/retention | NOT COMPLETE | No complete ownership/authority/retention/retirement ledger |
| 4 — closure matrix and independent scrutiny | NOT COMPLETE | No fully sourced 159-path closure ledger or independent scrutiny |

The package contains evidence of substantial candidate-vs-historical differences, API/trust-policy variants, build/test registration differences and consumer contexts. The counts and lexical partitions do not answer which branch/version is authoritative, semantically equivalent, superseded, retained or eligible for retirement. No donor implementation is adopted; no source baseline is selected.

**Current closeout:** documentation/planning is consolidated and frozen for scope control; Foundation acceptance remains pending. The remaining named foundation blockers are DF-02 semantic closure, exact blind-reader DF-09 CLEAR, DF-11 governance-compliant independent scrutiny or formal amendment, final terminal inventory/status synchronization after the last writes, and Director-only DF-12 acceptance. PR #173 whole-architecture acceptance/CF-26/CF-27, PR #174 current 54-scenario proposal acceptance/provenance, Gate A and Gate B remain open in the planning lineage. Stage A remains HELD. No merge, source baseline, donor adoption, runtime implementation, training or deployment is authorized.


## 36. 2026-11-26 canonicalization and gate-status correction

The planning index has been replaced with a concise canonical status page; the duplicated prior status snapshots are preserved verbatim in `docs/architecture/archive/JARVIS_PLANNING_INDEX_HISTORICAL_SNAPSHOTS_2026-11-26.md` and explicitly marked historical/non-controlling. This reduces status drift without deleting provenance.

**DF-11 correction:** D3=A records the Project Director's instruction to retain the prior waiver/provenance residual and avoid reconstruction. However, accepted governance Rules 17.3 and 20.1 require genuine independent review and prohibit silently waiving required gates; the waiver request is therefore not effective as a gate closure under the current governance. DF-11 is **BLOCKED** unless a genuine independent review is completed or a formal governance amendment resolves the conflict. Builder self-review is not independent. This correction supersedes earlier report wording that described DF-11 as waived/closed.

Planning consolidation/freeze is administratively completed by Builder, but acceptance remains pending. This does not close DF-02 phases 3–4, DF-09, DF-11 governance compliance, terminal inventory, or DF-12. The exact current scope and exit criteria are in the canonical index and 2026-11-26 finalization snapshot. No donor adoption, baseline selection, runtime work, Stage A or merge authority is granted.


## 37. 2026-11-26 — reverse-consumer registration/ownership adjudication: cognitive/evolution slice

This slice moves Phase 2 beyond lexical index counts by checking exact frozen candidate and donor source contents against their production and test build registrations. Refs are frozen candidate `caf87986dfea7aca75728818651c8687e9f5faf0` and donor PR #97 HEAD `c1da222e6c94aeb3f2ad000392c21fe4fc81ab25`; no current branch tip is substituted.

### 37.1 Production translation-unit registration

Exact `core/cpp/CMakeLists.txt` comparison:
- Candidate registers **57** production C++ translation units; donor registers **64**.
- Seven donor-registered translation units are absent from candidate registration: `brain_restored_api.cpp`, `brain_action_execution.cpp`, `brain_prediction_context.cpp`, `brain_affective_planning.cpp`, `affective_state.cpp`, `affective_learning.cpp`, and `developmental_learning.cpp`. Candidate has no production-only translation unit relative to donor in this exact list.
- Candidate's `brain_restored_api.cpp` nevertheless exists as an exact candidate blob, but it is **not registered** in candidate `jarvis_core`. Donor registers it. This distinction is confirmed by CMake, not inferred from symbol presence.

Brain source ownership is materially split between revisions: candidate `brain.cpp` is 219 lines / 50 counted method-definition patterns; donor `brain.cpp` is 889 lines / 9, while candidate `brain_restored_api.cpp` is 77 lines / 69 patterns and donor's is 405 lines / 74. The earlier 40-name overlap finding between candidate Brain source files must be interpreted with the registration fact: the restored API translation unit is dormant in candidate CMake, so lexical overlap does not establish a live duplicate-symbol build defect. Donor registers the split files and its exact ownership differs. This is a source/build-graph fact only, not a choice of the donor split.

### 37.2 Test target and CTest registration

Exact `core/cpp/tests/CMakeLists.txt` comparison:
- Candidate: **45 executable targets / 45 CTest registrations**.
- Donor: **71 executable targets / 70 CTest registrations** (DLT-002 persistence has separate CTest train/verify entries; long-run targets are intentionally not CTest entries).
- There are **26 donor-only executable test targets** and no candidate-only targets in the compared lists. Donor-only families cover affective state/decision/evidence/goal outcomes, cognitive-runtime learning and goal feedback, developmental learning/Brain/world/environment, goal-directed cognition/outcomes, experience memory, action-consequence integration, attention-learning, memory-learning-evolution persistence, and DLT trial/persistence/long-run validation.
- Candidate absence from registration is not proof that a test source or capability is absent everywhere; the classification is specifically the exact frozen CMake target/CTest graph.

### 37.3 Exact source/test blob evidence in the selected lifecycle cohort

| Path | Candidate blob SHA | Donor blob SHA | Candidate lines | Donor lines | Finding bounded to this comparison |
|---|---|---|---:|---|
| `core/cpp/src/brain.cpp` | `e9f3758fcc9c0e89b7280ce376db9033d547682d` | `dec9e5442b3ca4b81a7879855c6146b2619934cc` | 219 | 889 | Different Brain method ownership and replay/feedback implementation scope |
| `core/cpp/src/brain_restored_api.cpp` | `618deb6976eed951eae02b7f0da741e6d730bb0c` | `7155d4d9c8eef527836fb79bf901aa32ddbae38b` | 77 | 405 | Exists but candidate CMake omits it; donor registers it |
| `core/cpp/src/cognitive_runtime.cpp` | `1a1383cedc42e357dc9efce117328b8d55e30bca` | `cf00acb6abd52308343f3a0e7016e6173b945603` | 188 | 226 | Donor adds runtime/feedback behavior; exact consumer contracts need closure |
| `core/cpp/src/evolution_controller.cpp` | `01484ebf12fc3902bce749030a1f54610b26236a` | `4e77ec2e5daa09a964132ca486b8c5ee1cebf2f5` | 82 | 316 | Material evaluation/adoption policy and evidence-validation variation |
| `core/cpp/src/evolution_experiment_runner.cpp` | `83d3c26e589cd16151818774a81ccb62f9d514fc` | `0545662ea0ef865feb0527207fc4c32ecb50566e` | 24 | 60 | Isolation/attestation and run-result validation behavior differs |
| `core/cpp/src/evolution_experiment_coordinator.cpp` | `c689d16b31c039a7be9ab5c9bde0de49e677b32d` | `93d2e01c785ed4867efec07673cd802afbe27427` | 76 | 85 | Coordinator/runner integration differs; not established as equivalent |
| `core/cpp/src/evolution_safety.cpp` | `6c930ebbe69ad92fe155e3c169e3e996442f22cf` | `5a4669de9296958eacc77534bad87ce7c30ae52d` | 17 | 27 | Safety gate policy/validation variation |
| `core/cpp/src/evolution_adoption_journal.cpp` | `a9e141ac0b784466e86575eefdb3260b2e15dfc0` | `d8df30a2902d3dac734fb1a571cbbecdd881b76f` | 72 | 115 | Journal lifecycle/replay/compensation behavior differs |
| `core/cpp/tests/evolution_brain_integration_suite.cpp` | `3164cbc19bfb056cdccfdd58f0be047226d41a86` | `59d7dd68c42eea18d488d8e5e6aa9f7a9a327ded` | 46 | 298 | Prior assertion-count review: candidate 7, donor 97; donor tests adoption/rollback/replay/isolation/canary lifecycle |
| `core/cpp/tests/evolution_experiment_runner_suite.cpp` | `08888276d875ce5e55f421e828f1bb4f061d1ea5` | `307fe75b42f804d9bb2b0e8199df1e9cf773e3c6` | 80 | 91 | Prior assertion-count review: candidate 11, donor 43; donor adds isolation/attestation/simulated-run validation cases |
| `core/cpp/tests/evolution_canary_controller_suite.cpp` | `6acd8aedb7520aebe745b15a2a10c527262f28e0` | `80cac5df347987a9074e1ced43202f8759f797d7` | 39 | 105 | Prior assertion-count review: candidate 9, donor 36; donor expands canary journal/replay/rollback cases |
| `core/cpp/tests/evolution_adoption_journal_suite.cpp` | `24a1be9541cc038518065724aef1968efc4dc595` | `fc8ae17bb837831fef7bf69873ec0e5243e2bc22` | 5 | 108 | Candidate test source is present but minimal relative to donor suite; exact blobs reviewed |

Source-line and method-pattern counts are indicators of structural divergence, not semantic-quality scores. Test assertion counts cited above are from the already documented exact-content test-history slice; they do not establish test equivalence or quality.

### 37.4 Phase disposition

**Phase 2 progress:** this selected production/test cohort now has exact candidate/donor blob identities, CMake registration outcomes, and bounded source/test-contract deltas reconciled. This closes the registration classification for these inspected paths only and creates concrete reverse-consumer/build edges. It does **not** close the remaining 159-path matrix, all 1,135 consumer blobs, exact API/dependency edges, branch-owner/authority/provenance/retention decisions, or independent scrutiny. Phase 2 remains **PARTIALLY COMPLETE**; Phase 3 and Phase 4 remain **NOT COMPLETE**. No donor adoption, source baseline selection, retirement, deletion, runtime implementation or Stage A authorization follows from these findings.


## 38. 2026-11-26 — candidate-absent donor source/API reverse-consumer evidence

This slice follows the seven donor-only production translation units identified in §37 through exact donor symbol matches, candidate declarations, consumer categories, and registered donor tests. The lexical dataset is used to locate exact source contexts; row counts are not treated as semantic edge counts.

### 38.1 Brain action-execution contract

- Donor `brain_action_execution.cpp` exact blob `3b66bafb438cd28790e6f25611b96c86f1eff05c` is 192 lines and implements `Brain::execute_action`. Donor `brain.hpp` declares the API (blob `671186f4c39879a182f9e511394fc564d86f2988`).
- The frozen candidate header also declares `execute_action` (candidate `brain.hpp` blob `8268ef84e0b361ead536724ba7761904b30ee58f`), but the candidate has no `brain_action_execution.cpp` path and no matching implementation in the inspected candidate `brain.cpp` / `brain_restored_api.cpp`; its CMake does not register the donor implementation.
- The scan locates 59 exact identifier rows across 14 consumer paths / 59 blobs: 19 source-context rows and 40 test-context rows. These include the Brain declaration, cognitive runtime, action-execution phase suite, Brain deep/cycle suites, and action-consequence/developmental integration tests. Donor `brain_action_consequence_integration_suite.cpp` is 317 lines and contains four direct `execute_action` call scenarios (lines 67, 144, 173 and 205 of the exact donor blob `7616082579d53e3579cae8e87895bdb3dadba66f`).
- Candidate does not register the donor's action-consequence integration target. This is a concrete candidate API/implementation/test-registration gap at the frozen refs; unresolved-link risk is conditional on a consumer actually linking/calling the declaration. It is not evidence that donor implementation should be adopted.

### 38.2 Contextual prediction and affective-planning APIs

| Donor-only source | Exact identifiers | Match rows | Consumer paths / blobs | Category | Evidence interpretation |
|---|---|---:|---:|---|---|
| `brain_prediction_context.cpp` | `predict_with_context` | 19 | 4 / 19 | 11 source, 8 test | Donor declaration/implementation and association-causality/prediction-feedback tests; candidate frozen source API lacks the matched method |
| `brain_affective_planning.cpp` | `plan_with_affect`, `choose_with_developmental_learning` | 42 | 5 / 32 | 20 source, 22 test | Donor Brain API and planning/learning integration consumers; candidate lacks these matched API identifiers at the frozen ref |

Exact donor source blobs: contextual prediction `b3ceff150f3fe8223dc3f76f4c298ac264d72dae` (113 lines); affective planning `2a9406257c23f3a66a64071842be7d6448799406` (189 lines). The donor affective-planning source directly defines `plan_with_affect` and overloads of `choose_with_developmental_learning`. These exact API/consumer edges are identified; behavior equivalence, ownership authority, and candidate replacement remain undecided.

### 38.3 Developmental-learning subsystem

- Donor source `developmental_learning.cpp` SHA `dbf5f43271dfa0a3c57236e2faa82eb88d15490d` (445 lines) and header `developmental_learning.hpp` SHA `e3b9bf8af265b67829fd7deb323d88a3a9dd4b75` (104 lines) define `DevelopmentalLearning`, association/strategy observation, strategy retrieval and consolidation.
- The scan reports 476 identifier rows across 10 identifiers, 40 consumer paths / 177 exact blobs: 354 source, 111 test and 11 workflow-context rows. Concentrated consumers include Brain/Brain restored API, cognitive cycle, memory/association/causal components, developmental Brain integration, developmental-learning tests, persistence and cognitive-cycle suites.
- Candidate path is absent and candidate CMake does not register this donor translation unit. Donor CMake registers it and registers developmental-learning/Brain-integration suites. Exact donor integration test `developmental_brain_integration_suite.cpp` SHA `760162dd6d1e669162e0bf22223a437491f5e262` has 1,139 lines and directly exercises learned strategy selection, action consequence, persistence/restoration and consolidation (e.g., lines 64–89, 125–139, 223–227, 1032–1067). These are identified consumer/test contracts, not a validated successor decision.

### 38.4 Affective source files with no lexical reverse-consumer hits

Donor `affective_state.cpp` and `affective_learning.cpp` are registered production sources, but the frozen scan yields **zero symbol-consumer rows** for either file. Exact path references are predominantly documentation/inventory/audit references. The scan limitation means this is a **no-symbol-hit cohort**, not a finding of no dependency: indirect, renamed, type-level, generic-token, or unindexed consumers remain possible and require manual include/type/build/behavior tracing before any retirement or non-adoption disposition.

### 38.5 Reconciliation and disposition

This selected slice now identifies concrete API/build/test edges for three candidate-absent production components (action execution, contextual prediction, affective planning), a broad consumer/test cohort for developmental learning, and an explicit no-symbol-hit limitation for the two affective files. Together with §37, it materially improves Phase 2 reverse-consumer evidence. It is **not** semantic closure for these complete paths or versions: declaration/definition ownership, exact include/API edges for every blob, competing versions, branch authority, behavior evidence, provenance and retention dispositions are still pending. Phase 2 remains PARTIALLY COMPLETE; DF-02 remains OPEN. No adoption, retirement, deletion, source-baseline selection, implementation, merge or Stage A authorization.


## 12. Exact process-isolation variant adjudication (2026-11-27)

Report: [DF02 Process-Isolation Variant Adjudication](DF02_PROCESS_ISOLATION_VARIANT_ADJUDICATION_2026-11-27.md), verified blob SHA `de3a7297122df4df4c0a77aba43e9c0b7e298ff1`.

The exact candidate/donor source and public header were fetched at the frozen refs. Fifteen distinct `process_isolation.cpp` blobs were grouped (candidate + donor + 13 alternates), with the full owner metadata preserved in the report. Candidate and donor core implementation are close; donor's concrete corrections include preparing argv before fork (avoiding child-side allocation in a multithreaded fork context) and selecting `execv` for path-qualified executable names. One later historical variant resolves path-containing executables before chroot/working-directory changes and has a guarded descriptor-close path; another adds a Linux-only callable evaluator isolation route.

The audit also found important assurance limits common to the candidate/donor core: `isolated` is set before requested child controls are verified; RLIMIT return values are ignored; network syscall filtering is a bounded syscall list and optional; process-group cleanup, inherited descriptors, path/fingerprint races and OS sandbox robustness lack adversarial tests. Candidate/donor process-isolation test source blobs are identical and cover only basic success/output, timeout, output-cap, requested-control fail-closed behavior and socket denial. Both CMake graphs register the two suites; **CTest was not executed**.

Disposition: source-level cohort comparison completed; historical owner/authority/retention, full reverse-consumer trace and OS-level verification remain open. No implementation preference/adoption or path closure is inferred.


## 13. Restored Brain API ownership variant adjudication (2026-11-27)

Report: [DF02 Restored Brain API Ownership and Variant Adjudication](DF02_RESTORED_BRAIN_API_OWNERSHIP_VARIANT_ADJUDICATION_2026-11-27.md), verified report blob SHA `e8fd69edde496c89eba84d7a25ee2c1eb02e3cc0`.

Exact content inventory: 20 distinct `brain_restored_api.cpp` blobs (candidate + donor + 18 alternates), method-surface extraction, and owner-tip inventory. Candidate restored API has 64 unique method names; donor has 68, with four donor-only method names related to developmental strategies, recorded evolution evaluation and prediction-feedback resolution. Candidate's CMake does not register the restored API translation unit; donor CMake registers it. Candidate source/API extraction shows overlapping definitions; donor source split is clean by method-name extraction. The prior “40 overlap” count and the current “43 unique method names” extraction are not reconciled; AST/signature-level analysis remains required.

Disposition: source ownership/build discrepancy confirmed; alternate semantic clusters, exact API/consumer compatibility, authority/retention and behavior remain open. No path closure or source selection.


## 14. Cognitive runtime closed-loop variant adjudication (2026-11-27)

Report: [DF02 Cognitive Runtime Variant and Closed-Loop Evidence Adjudication](DF02_COGNITIVE_RUNTIME_VARIANT_AND_CLOSED_LOOP_ADJUDICATION_2026-11-27.md), verified SHA `fa192b50437fc7014a4c9c7076d6d77b1f8f6658`.

Exact seven runtime-source blobs compared. Donor adds feedback queue, sequence-bound prediction feedback, goal/evidence assimilation, perception-provider installation, plan-selected action execution through configured adapter, result/workspace/metrics and consequence feedback. Exact donor test suite asserts contextual learning, persistence, action authorization/failure, prediction identity, task utility and regime-change reversal with fixture callbacks. Donor adds two runtime integration suites and registers them in CMake.

Static risks recorded: in-flight action feedback can be rejected during `stop()` because `stopping_` rejects submissions, so `drain_on_stop` may not drain feedback generated by current work; feedback-priority queue may starve cognition inputs; saturation has no retry/backpressure; action adapters and real integrations remain unverified. Tests were inspected, not run. Runtime path remains OPEN.

## 15. Cognitive cycle/contextual-learning adjudication (2026-11-27)

Report: [DF02 Cognitive Cycle Semantic and Contextual-Learning Variant Adjudication](DF02_COGNITIVE_CYCLE_CONTEXTUAL_LEARNING_VARIANT_ADJUDICATION_2026-11-27.md), verified SHA `7ec23e8382b789c7ccfe6900c3ee6111130b2c42`.

Exact ten source blobs and seven test blobs compared. Donor adds inferred collision-resistant contexts, action-specific episodic recall, developmental strategy transfer, evidence-weighted action-value influence, exploration and affect-aware decision inputs, plus sequence-bound prediction and goal feedback. The donor's expanded behavioral suite specifies context collision prevention, action-choice change, context isolation, persistence and regime-change adaptation. Source/tests inspected only; not executed. Duplicate feature-label ordering and other adversarial context cases remain open. No authority or closure decision.


## 16. Memory–learning–evolution persistence integration test adjudication (2026-11-27)

Report: [DF02 Memory–Learning–Evolution Persistence Integration Variant Adjudication](DF02_MEMORY_LEARNING_EVOLUTION_PERSISTENCE_INTEGRATION_VARIANT_ADJUDICATION_2026-11-27.md), verified SHA `b01fb2a58251fe799d09d7005ee0234dc109af5a`.

The donor-only test path has 12 exact blobs, no frozen-candidate version. Donor test source exercises prediction error → learning/evolution evidence; positive/negative action consequences → strategy/decision; proposal → isolation-attested evaluation → adoption; and journal replay across a reconstructed Brain. Donor CMake registers the executable and CTest entry; candidate CMake does not. It reconstructs in the same process, not a process crash/restart; source was inspected, not run. Path/authority/retention remains open.


## 17. Evolution experiment coordinator/statistical gate adjudication (2026-11-27)

Report: [DF02 Evolution Experiment Coordinator Variant and Statistical-Gate Adjudication](DF02_EVOLUTION_EXPERIMENT_COORDINATOR_VARIANT_AND_STATISTICAL_GATE_ADJUDICATION_2026-11-27.md), verified SHA `8af42a473be7cc11e402120380dbda79c3480db8`.

Candidate/donor source and 13 historical versions compared. Donor adds `started` checks, default-required isolation, tracks isolation across all trials and issues attestation. Exact `EvolutionTrials` contract computes `confidence=1/(1+standard_error)`; this is a heuristic score, not a calibrated statistical confidence or difference-CI. Gate uses minimum individual heuristic scores and gain threshold. Historical variants include separate comparison-CI/statistical-evaluation branches. Current coordinator runs baseline trials sequentially before candidate trials; environment drift/order confounding is untested. Candidate/donor test has only one deterministic positive fixture and disables isolation requirement; no native test run. Semantic/authority remains open.


## 18. Evolution orchestrator durable-evaluation gate adjudication (2026-11-27)

Report: [DF02 Evolution Orchestrator Durable-Evaluation Gate Adjudication](DF02_EVOLUTION_ORCHESTRATOR_DURABLE_EVALUATION_GATE_ADJUDICATION_2026-11-27.md), verified SHA `b395b6236b786340f040d392511f809f38e23ca7`.

Exact ten source variants compared. Candidate records evaluation attempts but may proceed to adoption when the selected winner's durable `record_evaluation` fails; donor checks winner lifecycle is still `CandidateEvaluated` and returns before adoption otherwise. Donor test adds adoption-journal/history assertions, but neither candidate nor donor orchestrator suite injects evaluation-record failure to verify this exact correction. Tests inspected, not run. Semantic/authority remains open.


## 19. Canary state and operational-evidence adjudication (2026-11-27)

Report: [DF02 Canary Isolation, Evidence Semantics and Operational-Canary Adjudication](DF02_EVOLUTION_CANARY_STATE_AND_OPERATIONAL_EVIDENCE_ADJUDICATION_2026-11-27.md), verified SHA `98b3ae70b4ed21d55cef45ce030762c2c0c679e1`.

Candidate canary uses a single shared accumulator and mean regression; donor uses per-experiment canary state, worst-observation regression and preview. Donor tests check cross-experiment isolation. However, orchestrator feeds the same historical baseline/candidate fitness pair three times, so the canary-retention step is not independent live operational monitoring. Controller returns the rollback decision even if rollback transaction fails; orchestrator marks RolledBack without checking transaction success. Canary accumulators are in-memory and restart persistence is not demonstrated. No tests executed; path open.


## 20. Brain journal replay and outcome-validation adjudication (2026-11-27)

Report: [DF02 Brain Journal Replay, Outcome-Validation and Derived-Learning Adjudication](DF02_BRAIN_JOURNAL_REPLAY_AND_OUTCOME_VALIDATION_ADJUDICATION_2026-11-27.md), verified SHA `2952aaf8719af375e7f4c06f3774b7ff88fabc1e`.

Candidate/donor replay compared. Donor adds sequence-bound predictions, validation-before-mutation, prediction-error recomputation, action outcome validation, source-sequence binding for derived affective learning, external-observation/novelty persistence and replay/consolidation improvements. Donor deep and action-consequence integration test contracts inspected. Gap: action consequence error is only finite-checked, not recomputed against expected/actual, allowing a finite inconsistent outcome to pass validation and affect learning; regression test missing. Invalid historic events can advance cycle metadata before validation. No tests run; 35-source full semantic closure remains open.


## 21. Evolution event replay authority-boundary adjudication (2026-11-27)

Report: [DF02 Evolution Event Replay Authority-Boundary Adjudication](DF02_EVOLUTION_EVENT_REPLAY_AUTHORITY_BOUNDARY_ADJUDICATION_2026-11-27.md), verified SHA `3d5b8bce687df6eda9f6e8389cfa1fe2cc77b88c`.

Direct adoption API enforces matching durable evaluation, outcome recomputation, journal identity, safety policy and attestation. Brain replay `evolution_adopt` instead requires only experiment ID, reconstructs and re-attests claimed isolation, then directly model-adopts and journal-replays without matching evaluation/history validation. Public `observe(Event)` can append event kinds without evolution-specific prevalidation. Replay rollback checks adopted state but not event key versus adoption-record key. Direct rollback also does not require latest active experiment for that parameter; stale canary could reset baseline while newer adoption remains marked adopted. Donor tests cover unversioned legacy rejection and direct API cases, not versioned forged/mismatched events. Source only; no tests run.


## 22. Action execution/consequence persistence adjudication (2026-11-27)

Report: [DF02 Action Execution and Consequence-Persistence Contract Adjudication](DF02_ACTION_EXECUTION_AND_CONSEQUENCE_PERSISTENCE_ADJUDICATION_2026-11-27.md), verified SHA `a68927b37126ded3edf42616a75dd7934d334ba6`.

Donor adds observed consequence, prediction sequence/context binding and feedback learning. Phase-7 tests assert consequence evidence can change later planning and survive reconstruction. Material gap: Brain returns execution status even if journal append fails; prediction remains unresolved and outcome/learning may be lost. Separate outcome/affective/learning appends can partially fail; no transactional batch or persistence-failure status. Tests inspected, not executed.


## 23. Memory journal/metadata/consolidation adjudication (2026-11-27)

Report: [DF02 Memory Journal, Metadata Migration and Consolidation Variant Adjudication](DF02_MEMORY_JOURNAL_METADATA_AND_CONSOLIDATION_ADJUDICATION_2026-11-27.md), verified SHA `cfd0eb834e3b6ffb2cba7f213522a27488eacbd4`.

Nine exact source blobs and eight test blobs compared. Donor improves unreadable-suffix quarantine, metadata V1→V2 migration (consolidation field), staged metadata validation, tier/cursor rebuilding, retrieval filtering and consolidation ranking. Frozen donor's event journal remains raw/unframed/no checksum; the checksummed framing branch is a separate historical alternate, not donor-integrated. Metadata snapshot rename and append flush lack fsync durability. Tests cover corrupt-tail quarantine, missing metadata reconstruction, consolidation/ranking; not crash/fault/concurrency or parseable corruption. No tests executed.


## 24. Evolution runner/isolation-attestation adjudication (2026-11-27)

Report: [DF02 Evolution Experiment Runner and Isolation-Attestation Contract Adjudication](DF02_EVOLUTION_RUNNER_AND_ISOLATION_ATTESTATION_ADJUDICATION_2026-11-27.md), verified SHA `bbf981c13f4cc95e49a332cd06eb7e1e5f72b30b`.

Donor distrusts callback isolation, adds isolated-command parsing and private field-snapshot attestation, and safety gate recomputes gain/threshold. Attestation is not cryptographic provenance and Brain/controller replay can re-attest reconstructed events. Backend isolation remains coarse bool; optional control success isn't a detailed certificate. Fitness range is not enforced in direct runner/controller paths; candidate-executed is not required when policy isolation is disabled. Tests cover callback lying, mutation, timeout, output cap, NaN and exception, not replay forgery, range, disabled-execution, or platform controls. Source only.


## 25. Association/contextual generalization/causal-hypothesis adjudication (2026-11-27)

Report: [DF02 Association, Contextual Generalization and Causal-Hypothesis Adjudication](DF02_ASSOCIATION_CONTEXTUAL_GENERALIZATION_AND_CAUSAL_HYPOTHESIS_ADJUDICATION_2026-11-27.md), verified SHA `8bed402fc935f9a7d99be27d58b122d087ab5725`.

Association donor adds contradiction-aware co-change, contextual graph inference, shared-neighbor concept candidates and prediction feedback. Causal model derives directional hypotheses from transition co-occurrence; no intervention/confounder identification. Public association observe/feedback methods do not reject non-finite evidence before clamp; NaN can poison weights. Test source inspected, not executed; adversarial finite/invalid and causal controls open.


## 26. Causal-link typed codec compatibility adjudication (2026-11-27)

Report: [DF02 Causal-Link Typed Codec Compatibility Adjudication](DF02_CAUSAL_LINK_TYPED_CODEC_COMPATIBILITY_ADJUDICATION_2026-11-27.md), verified SHA `c23780d44acafa6543e28dcf1b167c93fc36894e`.

Donor-only codec adds length-prefixed typed scalar encoding and V1 legacy decode. Source review identifies empty-key encode/decode asymmetry, legacy `@2|` prefix misclassification, nonfinite double acceptance, default-locale float encoding/decoding, and inherent V1 type ambiguity. No dedicated codec tests located; source only.


## 27. Developmental-learning/context-transfer adjudication (2026-11-27)

Report: [DF02 Developmental Learning Context Similarity and Strategy-Transfer Adjudication](DF02_DEVELOPMENTAL_LEARNING_CONTEXT_TRANSFER_ADJUDICATION_2026-11-27.md), verified SHA `b2a029df2d7dde256ab1937e63e627c546fa7dd9`.

Donor-only source provides reliability-weighted signed strategy learning, exact/related-context scoring, schema/negation/numeric guards and deterministic ranking. Donor learning and Brain integration tests specify action-choice change, numeric transfer, replay and evidence handling. Identity keys concatenate a unit separator without escaping (possible collisions); categorical token Jaccard and numeric bands can false-transfer. Candidate source path absent. Tests inspected, not executed.


## 28. Contextual prediction/numeric calibration adjudication (2026-11-27)

Report: [DF02 Contextual Prediction, Numeric Calibration and Evidence-Confidence Adjudication](DF02_CONTEXTUAL_PREDICTION_NUMERIC_CALIBRATION_ADJUDICATION_2026-11-27.md), verified SHA `d402b3dca026155b6961cc3ad8ca30a5b879e44d`.

Donor-only prediction-context source derives concept evidence from association graph, optionally calibrates numeric predictions by key, stores provenance and increases confidence via a noisy-or-like formula. Global metric is not context-scoped, so cross-context calibration leakage is possible; graph coherence is uncalibrated confidence evidence. Concept IDs joined with unit separator without escaping. Donor phase-10 tests cover nonfinite, sequence, context and replay cases; cross-context metric contamination/calibration/fuzz gaps remain. No tests executed.


## 29. Decision/planning/reasoning pipeline adjudication (2026-11-27)

Report: [DF02 Decision, Planning and Reasoning Pipeline Variant Adjudication](DF02_DECISION_PLANNING_REASONING_PIPELINE_ADJUDICATION_2026-11-27.md), verified SHA `3d1f24e62752465b5ab9b3944a14c98c7eda22f3`.

Donor decision/planning adds affective and consequence-aware score modulation; reasoning handles disputed premises and typed causal-link decoding. Gaps: planning policy weights not finite-validated (NaN may break sort comparator), expected-value summary omits negative values, reasoning accepts nonfinite link/premise confidence and may propagate malformed evidence, conflicting inferred values and duplicate premise confidence are input-order-dependent. Tests inspected, not run; broader test mapping open.


## 30. Attention salience/feedback/persistence adjudication (2026-11-27)

Report: [DF02 Attention Salience, Feedback and Persistence Adjudication](DF02_ATTENTION_SALIENCE_FEEDBACK_PERSISTENCE_ADJUDICATION_2026-11-27.md), verified SHA `7fe60d584a3ccc1f84bc2e8e58e167647a4e70a9`.

Donor adds prediction-error/internal-activation salience and persisted policy feedback. Public score/reinforce methods do not reject nonfinite values; NaN can contaminate scores/policy. `focus(events)` passes novelty=1.0 for every event, so no per-event novelty ranking. Tests cover basic feedback, ranking, persistence; no adversarial nonfinite/focus utility tests. Source inspected, not run.


## 31. Affective-state/appraisal-learning adjudication (2026-11-27)

Report: [DF-02 Affective-State and Appraisal-Learning Adjudication](DF02_AFFECTIVE_STATE_APPRAISAL_LEARNING_ADJUDICATION_2026-11-27.md), verified SHA `039f269037fec426949596409e923b5edfdc69ac`.

Donor continuous affective state and adaptive appraisal/calibration model inspected; tests specify positive/negative evidence, decay, calibration, modulation, persistence, reliability and goal outcome. Limitations: calibration depends on event-supplied consequence error (cross-report validation gap), weak evidence relevance floor 0.25, modulation ratio floor 0.25, fixed heuristic equations, no long-term calibration/stability or wall-clock timing tests. No tests run.


## 32. Goal/intent/self-capability adjudication (2026-11-27)

Report: [DF02 Goal Lifecycle, Intent Selection and Self-Capability Model Adjudication](DF02_GOAL_INTENT_SELF_CAPABILITY_ADJUDICATION_2026-11-27.md), verified SHA `09147c8a4407f0bb10ea859beea77da78125ba57`.

Donor goal lifecycle, momentum/deadline intent, affective intent and capability availability/performance/isolation separation inspected. Gaps: prerequisite cycles/self-dependencies; progress/complete can bypass Active/prerequisite checks; intent/self-model clamp NaN; empty capability name; health averages isolated performance. Tests inspected, not run; SelfModel test mapping incomplete.


## 33. Knowledge/adaptation/representation/reflection adjudication (2026-11-27)

Report: [DF02 Knowledge, Adaptation, Representation and Reflection Adjudication](DF02_KNOWLEDGE_ADAPTATION_REPRESENTATION_REFLECTION_ADJUDICATION_2026-11-27.md), verified SHA `ef9038472f4112a152af2e07f7a0b5841f720f27`.

Donor numeric adaptation, deterministic representation IDs/metadata filtering/finite validation and reflection evidence averaging inspected. Frozen KnowledgeModel remains simple; richer feedback/calibration alternatives are historical, not integrated. Adaptation metric global by key, surprise streak fixed, reflection coherence heuristic, metadata exclusion schema fixed. Tests inspected, not run.


## 34. Core C++ test build/registration adjudication (2026-11-27)

Report: [DF02 Core C++ Test Build/Registration Reachability Adjudication](DF02_CORE_CPP_TEST_BUILD_REGISTRATION_ADJUDICATION_2026-11-27.md), verified SHA `f039066be4237df1171a505dd347d8428e08d9fb`.

Candidate CMake has 45 executable/CTest entries; donor 71 executable/70 CTest. All source paths reconciled, all CTest commands map targets; 2 long-run targets are workflow-driven, DLT-002 persistence uses separate train/verify fixture commands. No duplicate target/test names. Assertions enabled in Release. Existing native build evidence is older SHA and configure/build only; no CTest execution. Test semantic adequacy remains open.


## 35. Engineering-agent/message-bus/task-ledger adjudication (2026-11-27)

Report: [DF02 Engineering Agent, Message Bus and Durable Task Ledger Adjudication](DF02_ENGINEERING_AGENT_MESSAGE_BUS_AND_TASK_LEDGER_ADJUDICATION_2026-11-27.md), verified SHA `ee2b72bdc18814dd8e69c6a2b2e6d3fdb28f73a1`.

Donor bounded message queue/dedup/backpressure and durable task-ledger CAS/replay inspected. Gaps: sender identity spoofing on raw bus; task journal replay permits immutable constraint changes and lacks explicit transition graph/checksum; torn first-record recovery can truncate entire file; append flush lacks fsync; coordinator doesn't validate/persist actual output artifacts. Tests source inspected, not executed.


## 36. Core C++ source build-registration adjudication (2026-11-27)

Report: [DF02 Core C++ Source Build-Registration Adjudication](DF02_CORE_CPP_SOURCE_BUILD_REGISTRATION_ADJUDICATION_2026-11-27.md), verified SHA `4b9266c34f36559071d09d2b00b63e6ab74a613f`.

Candidate core library has 57 source entries; donor 64, seven new Brain/affective/developmental TUs, none removed or duplicated, all present. C++20, warning flags, CTest, examples default ON; no Werror. Native build evidence is older SHA, configure/build only; no CTest. Source-registration semantic closure remains open.
