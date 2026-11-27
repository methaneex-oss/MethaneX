# DF-02 Exact Semantic Comparison — Evolution Evaluation, Isolation and Adoption Authority

**Date:** 2026-11-27  
**Disposition:** material source/API/test-contract divergence established; all affected donor paths and historical variants remain OPEN for full 159-path closure.  
**Authority boundary:** evidence-only. No source/runtime changes, donor adoption, retirement, deletion, baseline selection, merge, or Stage A authorization.

## Frozen comparison anchors

- Candidate: PR #192 frozen target `caf87986dfea7aca75728818651c8687e9f5faf0`.
- Donor: PR #97 HEAD `c1da222e6c94aeb3f2ad000392c21fe4fc81ab25`.
- Repository: `methaneex-oss/MethaneX`.
- All source and test blob SHAs below were retrieved from those exact immutable refs using GitHub repository-content reads. A blob SHA identifies the exact file content; it does not establish branch ownership authority or acceptance.

## Exact source/API evidence

| Path | Candidate blob | Donor blob | Semantic finding |
|---|---|---|---|
| `core/cpp/src/evolution_controller.cpp` | `01484ebf12fc3902bce749030a1f54610b26236a` | `4e77ec2e5daa09a964132ca486b8c5ee1cebf2f5` | Candidate `record_evaluation` stages the journal and appends history without validating identity, finite metrics, outcome, isolation attestation, or recomputed outcome. Candidate `adopt` checks only `candidate_executed`, stages the journal and evaluates the safety gate; it does not require an already durable evaluation record. Donor validates experiment identity, finite values, confidence bounds, completed outcome, policy-required isolation attestation and recomputed outcome. Donor adoption requires an evaluation record for the exact experiment and matching evidence. |
| `core/cpp/src/evolution_experiment_runner.cpp` | `83d3c26e589cd16151818774a81ccb62f9d514fc` | `0545662ea0ef865feb0527207fc4c32ecb50566e` | Candidate accepts callback sandbox output when the returned `isolated` boolean is true. Donor explicitly treats callback results as non-isolated and adds `run_isolated_command`, requiring a started, isolated, completed, non-timeout, non-output-limited, zero-exit result with a finite fully parsed fitness value before issuing a private snapshot-bound isolation attestation. |
| `core/cpp/src/evolution_experiment_coordinator.cpp` | `c689d16b31c039a7be9ab5c9bde0de49e677b32d` | `93d2e01c785ed4867efec07673cd802afbe27427` | Candidate validates completion/timeouts/output/finite fitness but does not require `started`, enforce configured isolation, or preserve an all-trials-isolated result. Donor checks `started`, enforces `require_isolation` on baseline and candidate trials, and tracks whether all trials were isolated before attestation. |
| `core/cpp/include/jarvis/core/evolution_experiment.hpp` | `53bcd379fb788a3b0c369309c328f70d56f051ba` | `551d0d41b19abbeca425d102ec4c61984dfac0b6` | Candidate experiment is a plain result struct with `candidate_executed`. Donor adds isolation state, private attestation snapshot fields, and `has_valid_isolation_attestation()` that binds identity, proposal, baseline/candidate values, thresholds, confidence, outcome and execution state. Mutation after attestation invalidates it. |
| `core/cpp/include/jarvis/core/evolution_controller.hpp` | `e06441d23685093a3c533498a09adf3a8baf5914` | `c1af30f84f03d87d151fe3c5fbfd89ef39fbe34e` | Donor adds explicit validate/record/replay evaluation, validate/adopt/compensate, canary preview/observation, rollback validation/execution/replay, and adopted-experiment lookup APIs. Candidate exposes only the smaller controller surface. |
| `core/cpp/src/evolution_orchestrator.cpp` | `efd55281ba7d2edf95c6a9f6537ed2944022617e` | `c913ff0f42fc4647605376579b3f343b5c12c387` | Donor refuses to proceed to adoption unless the winning experiment remains in `CandidateEvaluated` after durable evaluation recording. Candidate lacks this explicit lifecycle-state guard before superseding alternatives and invoking controller adoption. |
| `core/cpp/src/evolution_adoption_journal.cpp` | `a9e141ac0b784466e86575eefdb3260b2e15dfc0` | `d8df30a2902d3dac734fb1a571cbbecdd881b76f` | Candidate `stage` returns success for an already-adopted record and otherwise overwrites the record with a new pending experiment using the same ID, without checking complete identity/metrics. Donor compares parameter key, baseline/candidate fitness, confidence, proposal current/proposed/expected gain/proposal confidence, minimum improvement and isolation; conflicting reuse fails closed. Donor also adds explicit restoration transitions used for compensation. |

## Behavioral evidence comparison (source inspection only)

| Test path | Candidate blob | Donor blob | Exact observation |
|---|---|---|---|
| `core/cpp/tests/evolution_brain_integration_suite.cpp` | `3164cbc19bfb056cdccfdd58f0be047226d41a86` | `59d7dd68c42eea18d488d8e5e6aa9f7a9a327ded` | Candidate suite is a short success/adoption/canary rollback/restart scenario. Donor adds negative replay/authority scenarios, including rejection of a legacy adoption event without experiment evidence, protection against unversioned rollback undoing a newer adoption, durable evaluation before adoption, and broader replay/idempotency cases. |
| `core/cpp/tests/evolution_experiment_runner_suite.cpp` | `08888276d875ce5e55f421e828f1bb4f061d1ea5` | `307fe75b42f804d9bb2b0e8199df1e9cf773e3c6` | Candidate tests callback-returned isolation boolean and basic timeout/output/invalid-fitness/exception rejection. Donor tests process-isolated command execution, successful attestation, attestation invalidation after mutating fitness, and callback results remaining untrusted. |
| `core/cpp/tests/evolution_canary_controller_suite.cpp` | Not re-fetched in this slice | Not re-fetched in this slice | Existing controlling report §11 records candidate 9 assertions versus donor 36, including donor repeated-observation threshold persistence and idempotent evaluation/adoption/rollback replay. Treat this as prior report evidence, not fresh execution. |

The exact candidate and donor `core/cpp/CMakeLists.txt` blobs are respectively `c51816888e1bddb7bc00c59e72529524e27a0717` and `bc264ce7b4ae489404ca03ea6d9676d0330a6a56`. Both register the controller, runner, coordinator, orchestrator and adoption journal translation units. The donor additionally registers `brain_restored_api.cpp`, `brain_action_execution.cpp`, `brain_prediction_context.cpp`, affective planning/state/learning and developmental learning units. This is compiled-graph divergence, not a proposal to import those units.

The exact candidate and donor core test-CMake blobs are `dab0c52ab4dfe15e1e2cbccfa9e6c904abdf54e3` and `cbfd1fde52fffa6eeac025da2b7ddcb5ab493261`. The two integration test paths above are represented in both source trees. Registration does not prove that either suite was built or executed in this run.

## Technical interpretation

1. **Evaluation is an authority boundary, not just a metric calculation.** A proposal or callback result must not become an adopted model mutation without evidence that the exact experiment ran, was valid, and passed the applicable policy.
2. **A boolean isolation claim is not an isolation proof.** The donor's process backend and snapshot-bound attestation are materially stronger than trusting a callback's `isolated` field. Even this donor mechanism still needs threat-model review of OS sandbox configuration, executable identity, resource limits, and platform-specific guarantees; the C++ attestation snapshot is integrity binding inside the process, not cryptographic proof against a compromised process.
3. **Durable evaluation and adoption must be one recoverable lifecycle.** The donor's journal identity matching, explicit pending/adopted restoration and replay APIs address transaction/restart cases absent or weaker in the candidate path. These mechanisms require persistence fault-injection and crash/restart tests before being considered reliable.
4. **No implementation is selected by this report.** Donor code is not automatically correct, secure, mature, or authorized. The evidence establishes semantic differences and test obligations only.

## Risks and unresolved questions

- The 159-path ledger still lacks a complete per-path, per-variant semantic disposition, including exact owner-tip and provenance for all 544 alternate blobs.
- The 40,048 lexical symbol candidates and 1,946 path-reference candidates are not fully adjudicated by this slice. Exact reverse-consumer relationships must be established from context, target registration and owner tips.
- The donor's process-isolation implementation requires OS/platform-specific security review and execution tests; a successful source diff is not a sandbox guarantee.
- Journal persistence needs fault injection at every write/rollback boundary, crash/restart replay tests, and verification of identity conflicts and legacy event handling.
- The source-level findings do not establish the correctness of every alternate blob in each path's history, nor who has authority to retain or retire those blobs.
- No native build, CTest, sanitizer, static analyzer, or behavioral execution was run by this GitHub content connector. This report must not be cited as test execution.

## Bounded task ledger for this slice

| Task | Status | Evidence | Next action |
|---|---|---|---|
| Exact candidate/donor source comparison for seven evolution lifecycle paths | Implemented / content-inspected | Blob SHAs above | Extend across each distinct alternate blob and exact owner refs |
| API contract comparison | Implemented / content-inspected | `evolution_controller.hpp`, `evolution_experiment.hpp` blob SHAs | Trace all public methods to definitions and consumers |
| Behavioral test source comparison | Implemented / content-inspected | Two test blob pairs above | Inspect remaining lifecycle suites and execute on authorized native runner |
| CMake production registration cross-check | Implemented / content-inspected | Candidate/donor CMake blob SHAs | Complete all historical CMake variants and reverse dependency graph |
| Runtime/build/test execution | Blocked | No native shell/worktree/workflow-dispatch action exposed by connector | Use authorized CI/native execution path; record exact run and SHA |
| Per-path owner/provenance/authority/retention closure | Open | Frozen discovery artifact and prior reports | Complete the 159-row/544-blob ledger; do not infer from tip count |
| DF-02 overall | OPEN | Controlling DF-02 report | Independent scrutiny after full ledger; no closure claim |

## Five review lenses applied to this slice

1. **Semantic correctness:** verified that the candidate/donor differences change the evaluation/adoption preconditions and journal identity semantics, rather than merely renaming APIs. No closure inferred.
2. **Build/reproducibility:** verified the production translation units are registered in both frozen CMake graphs and that the relevant test files exist in both trees. No configure/build/CTest run was available.
3. **Security/trust/provenance:** identified callback isolation trust, durable evaluation authority, journal identity reuse and replay as security-sensitive boundaries. OS sandbox and persistence-fault behavior remain untested.
4. **Cognition/capability realism:** safe self-modification is a prerequisite for adaptive cognition; an agent that cannot prove which experiment produced a model change is not reliable or accountable. These APIs are enabling controls, not evidence of human-like learning or MCU JARVIS-level capability.
5. **Hostile review:** checked that donor was not presented as canonical, that callback booleans were not misdescribed as sandbox guarantees, that source inspection was not mislabeled as execution, and that no implementation/retirement decision was smuggled into the report.

## MCU JARVIS / cognitive-systems benchmark

The fictional MCU JARVIS is depicted as context-aware, adaptive, action-capable and capable of managing complex systems. Those are narrative capabilities, not an engineering specification or empirical evidence. Credible agent/cognitive engineering instead requires explicit state and memory models, grounded perception, prediction/error correction, bounded planning, tool/action authorization, outcome feedback, provenance and recoverable learning. The inspected source shows genuine mechanisms for experiment evaluation, action isolation, model adaptation, journaling and rollback. However, the candidate/donor comparison exposes meaningful trust and lifecycle gaps, and neither source presence nor test registration demonstrates integrated, robust, context-aware behavior. Under the user's benchmark—“If Tony Stark built the real JARVIS using this design and implementation, would it be capable, adaptive, reliable, context-aware and genuinely useful?”—the evidence supports “not yet demonstrated.” The right next step is verified behavioral integration and safe feedback, not more capability labels or documentation volume.

**Final disposition: this is a material, exact-source audit advancement. It does not close any of the seven paths, the 159-path ledger, DF-02, Gate A, Gate B, Foundation acceptance, or authorize Stage A.**


## Discovery-artifact reconciliation — full 159-path coverage inventory

The frozen discovery ZIP was downloaded from workflow artifact `14956148301` and independently SHA-256 hashed in this run. Computed digest: `9902957475c76f4840d1d280c7d4f50537941e9445810afb805132374a328f38`, matching the controlling audit's recorded digest.

The artifact's raw CSVs were parsed and reconciled as follows:

| Reconciled dimension | Exact result |
|---|---:|
| Donor paths in presence inventory | 159 |
| Candidate same-path status | 95 divergent / 63 absent / 1 identical |
| Exact path/blob ownership records | 798 |
| Donor blob records | 159 |
| Candidate blob records | 96 (95 divergent + 1 identical) |
| Non-candidate, non-donor alternate blobs | 544 |
| Paths carrying at least one alternate blob | 88 |
| Alternate blobs by role | 299 production / 190 test / 53 build / 2 workflow |
| Unique branch tips | 213 |
| Unique text blobs scanned | 1,416 |
| Candidate symbol-consumer rows | 40,048 |
| Exact path-reference rows | 1,946 |

The 544 alternate count was independently recomputed from `path_blob_ownership.csv` by excluding exact donor and candidate blobs. The one path where candidate and donor content is identical is represented by a single ownership record carrying both flags; accounting for that shared record avoids double-subtracting it. This reconciles the 544 figure exactly across 88 paths. The 798 ownership records are unique path/blob pairs; the 159 donor + 96 candidate role flags overlap once on the identical blob, so they must not be summed as unique rows.

The 159-row path inventory was joined to ownership rows by exact donor path. Every row receives the conservative disposition `OPEN_NOT_FULLY_SEMANTICALLY_ADJUDICATED` and `OPEN_NO_AUTHORITY_DECISION`; this is deliberate. Presence, version counts, candidate status, tip coverage and donor symbol counts are coverage/provenance indices, not semantic closure or ownership authority.

Highest-dispersion cohorts by exact alternate blob count are:
- `core/cpp/tests/CMakeLists.txt`: 38 alternates across 40 versions.
- `core/cpp/src/brain.cpp`: 33 alternates across 35 versions.
- `engineering/cpp/CMakeLists.txt`: 33 alternates across 35 versions.
- `core/cpp/tests/evolution_brain_integration_suite.cpp`: 22 alternates across 24 versions.
- `core/cpp/CMakeLists.txt`: 20 alternates across 22 versions.
- `core/cpp/include/jarvis/core/brain.hpp`: 19 alternates across 21 versions.
- `core/cpp/src/brain_restored_api.cpp`: 18 alternates across 20 versions.
- `core/cpp/src/evolution_controller.cpp`: 17 alternates across 19 versions.

**What this closes:** the discovery-artifact integrity and 159-path/544-alternate coverage arithmetic are now independently reconciled.

**What this does not close:** none of the 159 paths is semantically or authority-closed by the inventory alone. The 544 alternate blobs still require exact-content semantic grouping, branch-tip owner/provenance review, reverse-consumer classification, build/test reachability, behavioral evidence and retention/retirement authority. The 40,048 lexical rows and 1,946 exact-path rows remain discovery candidates, not fully adjudicated dependencies.


## Additional exact historical slice — memory journal framing variant

The same hash-verified discovery artifact contains nine distinct `core/cpp/src/memory.cpp` blobs: one frozen candidate, one frozen donor and seven alternates. Exact ownership records identify the framed-journal alternate:

- Blob: `88314ed3a43c765f8a69255ace97afb7df1a6c5e`.
- Unique owner tip: `b0560edaa72b6d455001be51695731cf988b43b2`.
- Branch: `fix/memory-journal-framing-20261028`.
- Owner-tip commit message: `fix(memory): validate framed stream modes and legacy append guard`, dated 2026-10-28; commit author/committer is the repository owner.
- Exact candidate memory blob: `ba72a897306d4761246d0deab2fbab37c49d372f`.
- Exact donor memory blob: `ab42bba1d32d6f48d091787491c72294a4a55bb5`.

This alternate adds a V2 journal header, length-delimited event frames and a 64-bit FNV-1a checksum. Its reader can skip a complete frame with a bad checksum or invalid event while continuing at the next declared frame boundary; incomplete trailing frames are truncated to the last valid boundary. It also migrates legacy unframed journals to the V2 format after reading, using a temporary file and rename. The checksum detects accidental corruption; it is not a cryptographic authenticity mechanism.

The exact owner-tip CMake files are:
- Production CMake: `core/cpp/CMakeLists.txt`, blob `bc264ce7b4ae489404ca03ea6d9676d0330a6a56`; it registers `src/memory.cpp`.
- Test CMake: `core/cpp/tests/CMakeLists.txt`, blob `07a6421fe425b3a86f414c5923854d8a1ce4bc7e`; it registers `memory_architecture_suite.cpp` but no dedicated `memory_journal_framing_suite.cpp` target (the latter path returns 404 at this exact owner tip).
- Registered memory test source: `core/cpp/tests/memory_architecture_suite.cpp`, blob `5d824f08437916e48749bf539cc94e10c9f44347`. Exact text inspection finds restart and memory-ranking/promotion/consolidation checks but no assertions mentioning framing, checksum, corrupt records, legacy migration or truncation.

A material failure-mode caveat remains in this alternate: the legacy-read path truncates any unreadable suffix to `valid_end` before the migration block and does not quarantine that suffix. If the legacy journal is damaged, this branch does not provide the donor lineage's later `.corrupt` preservation behavior. The framed reader's recovery of complete interior bad frames is a different guarantee from preservation of a damaged legacy tail. The temporary-file rename behavior also needs platform-specific validation, especially replacement semantics where rename-over-existing differs.

**Disposition:** this one-tip historical implementation is a meaningful integrity/recovery design variant, not an accepted successor. Its branch-local provenance is identified, its build registration is confirmed, and the absence of dedicated framing/corruption tests is established by exact test-CMake and test-source inspection. It remains OPEN for comparison against the donor's corrupt-tail quarantine and metadata lifecycle, fault-injection tests, platform behavior, and retention authority. No test was executed in this run.
