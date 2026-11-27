# JARVIS Real-Capability Gap Audit — 2026-11-27

**Disposition:** bounded static-source evidence; not implementation, acceptance, or DF-02 closure.  
**Initial reviewed PR #203 source tree:** `a7d9d735fd516b984314f037224b4827fbbf9c26`. **Revalidated at current PR #203 head:** `fc628a1c5eb84659861082fb8ad3649635dcf4cd` (docs-only successor; every source/test/CMake blob listed below re-fetches with the same blob SHA at the current head).  
**Scope:** compare the existing cognitive core's demonstrated mechanisms and control flow against the intended real JARVIS capability—not its class names or design documents.

## Source evidence examined

Exact repository files and blob SHAs:

- `core/cpp/src/brain.cpp` — `e9f3758fcc9c0e89b7280ce376db9033d547682d`
- `core/cpp/include/jarvis/core/brain.hpp` — `8268ef84e0b361ead536724ba7761904b30ee58f`
- `core/cpp/src/cognitive_cycle.cpp` — `3df14c552f2048b0394dc362f7ee7a654a93fb32`
- `core/cpp/src/memory.cpp` — `ba72a897306d4761246d0deab2fbab37c49d372f`
- `core/cpp/tests/cognitive_cycle_suite.cpp` — `38ff2c7d6e851b4745e9dc7c01f968b7245400a2`
- `core/cpp/tests/prediction_feedback_phase10_suite.cpp` — `e72da8e7653aee775cfade9060064231c7a01630`
- `core/cpp/tests/action_execution_phase7_suite.cpp` — `b4a0060596c91c67080ac0a2db324f720d760fbe`
- `core/cpp/tests/memory_architecture_suite.cpp` — `2a9eb061427c622260304d09f45089e1debef294`
- `core/cpp/CMakeLists.txt` — `c51816888e1bddb7bc00c59e72529524e27a0717`
- `core/cpp/tests/CMakeLists.txt` — `dab0c52ab4dfe15e1e2cbccfa9e6c904abdf54e3`

**Verification limit:** GitHub source retrieval and static inspection only. No local checkout/compiler/runner was available in this execution; none of the tests below were executed. The test source was read, which is not a passing test result.

## Demonstrated mechanisms vs. actual capability

| Mechanism | Source-supported behavior | What is not established |
|---|---|---|
| Event observation | `Brain::observe` journals an event, updates state, replay/beliefs, causal/association structures, novelty/attention/threat and self-state | Real sensor/perception acquisition, modality interpretation, event reliability/provenance calibration |
| Memory | Event journal, typed scalar values, ranked recall, memory-tier metadata, reload/replay | Robust framed/checksummed journal, demonstrated corruption recovery/quarantine, memory consolidation quality/generalization |
| Reasoning | CognitiveCycle constructs a reasoning problem from current beliefs/causal links and calls ReasoningEngine | Open-domain robust inference, knowledge acquisition, calibrated uncertainty, adversarial reasoning evaluation |
| Prediction | Causal simulation can project predictions; cycle-scoped keys are persisted for outcomes | Predictive accuracy over unseen environments; multi-step forecast calibration |
| Goals/planning | Selects eligible goal, plans over caller-provided candidate actions and context, computes decisions and assessments | Autonomous goal discovery, task decomposition grounded in environment, real tool/device action selection and scheduling |
| Action safety/execution | Assessment; ActionExecutor accepts callbacks, authorization context, verification and rollback callbacks | Built-in concrete tool/device adapters, operational environment integration, independent verification of physical side effects |
| Learning | Prediction outcome feeds adaptation; evidence feeds knowledge; learning-loop can propose parameter evolution | Reliable cross-domain learning, transfer, continual-learning quality, causal attribution, learning without regressions |
| Capability execution | Capability descriptor/provider boundary validates ID/provider and executes through supplied provider | A real built-in capability catalog and persistent/available providers in the user's environment |
| Self-model/diagnostics | Capability health observations, self-state, reflection, self-test and isolation/recovery interfaces exist | Accurate self-diagnosis, validated repair, demonstrated safe recovery from real faults |

## Important control-flow facts

1. `CognitiveCycle::run` is caller-driven. It receives a single `Event`, caller-supplied `candidate_actions`, goal selection, planning horizon and constraints. It does not itself acquire real-world inputs or enumerate tools.
2. The cycle performs memory recall, belief/causal snapshot, reasoning, optional causal prediction, goal selection, planning, decision and action assessment. The implementation comment and flow explicitly stop before executing an external action; authorization is outside this cognitive cycle.
3. `Brain::execute_action` delegates to callbacks supplied by the caller. The tested callbacks are lambdas; this verifies the action-execution contract, not a real actuator/tool integration.
4. `Brain::execute_capability` requires a caller-supplied provider whose capability ID matches, registers it in a boundary, executes it and journals the result. This is an integration seam; it is not evidence that JARVIS already possesses connected, functioning capabilities.
5. The test suites use assert-based, finite, synthetic scenarios. They test representative contract behavior but do not demonstrate live environment perception, autonomous operation, long-horizon performance or cross-domain generalization.

## Bounded defects/risks observed for follow-up (not fixed; implementation not authorized)

- **Persistence integrity:** `memory.cpp` writes an unframed event stream; load stops at the first invalid/truncated event and truncates the file to the last valid byte. It does not quarantine the damaged suffix or emit a recovery diagnostic in the inspected path. Existing documentation already notes this limitation; this audit confirms the candidate source implementation has it. A future authorized implementation should add corruption-preserving recovery, integrity framing/checksums, and failure-injection tests rather than simply silently discarding the suffix.
- **Multi-event feedback consistency:** `Brain::learn_from_prediction` persists prediction outcome, then fitness, then invokes the learning loop and may persist an adoption event. If a later append fails, earlier persisted events/state may remain while the complete feedback transition did not occur. This requires an explicit failure-injection/transactional-semantics review; the source inspection alone does not establish an observed runtime failure.
- **Value/error semantics:** prediction error is absolute numeric difference clamped to [0,1], and some learning inputs are also bounded to [0,1]. This may be appropriate for normalized variables but can collapse magnitude for non-normalized domains. The data contract/domain normalization needs explicit validation; no universal metric is assumed.
- **Learning reproducibility:** the journal is event-replay-based, but the inspected persistence format does not demonstrate versioned schema, checksummed records or deterministic replay guarantees across software versions. That remains a verification obligation.

## MCU JARVIS benchmark: candid gap

Fictional MCU JARVIS is depicted as an integrated assistant/control system: conversational interface, environment/lab/armor monitoring, real-time data and analysis, design assistance, robotics/remote control, and multimodal interfaces. These are fictional reference behaviors, not engineering requirements to copy literally.

The real project currently has meaningful *internal cognitive mechanisms* and integration contracts. The inspected core is not yet a standalone assistant that can perceive a real environment, communicate through voice, research online, operate software/devices, or autonomously close a task loop. It needs actual adapters and a robust orchestration loop connected to verified capabilities, feedback and persistence. This is a substantial capability gap, not a cosmetic one.

Human-cognition-grounded architecture comparisons also emphasize integrated perception, working/long-term memory, reasoning, learning, decision-making and action; capability presence alone is not sufficient—mechanism coupling and behavioral evaluation matter. Relevant references:
- Kotseruba & Tsotsos, “40 years of cognitive architectures: core cognitive abilities and practical applications” (2018/2020): https://link.springer.com/article/10.1007/s10462-018-9646-y
- Langley, Laird & Rogers, “Cognitive architectures: Research issues and challenges” (2009): https://www.sciencedirect.com/science/article/pii/S1389041708000557
- “Integrated cognitive architectures: a survey” (2007): https://doi.org/10.1007/S10462-009-9094-9

## Five review passes on this bounded audit

1. **Requirement/semantic pass:** claims distinguish source mechanisms from actual end-to-end behavior; the cognitive cycle is not mislabeled autonomous.
2. **Build/test-evidence pass:** CMake source/test registration was inspected. Test files were read, but no compile/test run was possible in this execution. PASS for accurate evidence labeling; execution verification BLOCKED.
3. **Security/persistence pass:** callback/provider boundary and memory corruption-tail behavior identified; no security conclusion beyond inspected code is claimed. Failure-injection testing remains OPEN.
4. **Architecture/capability pass:** compares mechanisms to integrated cognition and fictional JARVIS reference while explicitly marking real-world interfaces, autonomy and operational capability as absent/unproven.
5. **Hostile-review pass:** checked for inflated claims, unsupported test-success statements, unauthorized source changes and scope creep. No source/runtime changes made. The report is bounded, but independent reviewer scrutiny is still required.

## Next bounded objective

Under the current governance, implementation remains unauthorized. Continue the DF-02 semantic/authority audit: trace candidate/donor variants for the cognitive cycle, memory integrity, capability execution and action control into exact registered tests and consumer/build edges; source each variant and owner; record unresolved disposition. If/when implementation is authorized, the first high-value engineering milestone should be a failure-injection test suite for journal corruption and multi-event feedback append failures, then a versioned/integrity-preserving journal design with recovery semantics—not more interface scaffolding.

**Status:** static audit evidence produced; no tests executed; no source change; no DF-02 closure; no Gate A/B acceptance; Stage A held.


## 2026-11-27 current-head reconciliation and review rerun

The initial audit's tree pointer was stale after documentation-only commits. Re-fetched PR #203 at current head `fc628a1c5eb84659861082fb8ad3649635dcf4cd`. All ten source/test/build files listed in the evidence table above were re-fetched by exact PR head; their blob SHAs match the audit's listed SHAs. Therefore the technical source observations remain tied to identical file content, while the audit's PR-tree pointer is now current. This establishes content identity for those files, not a full-tree equivalence claim.

### Five focused review passes (performed against this audit and source evidence)

1. **Semantic/traceability:** Verified claims remain scoped to exact source behavior; caller-provided observation/actions and first-eligible goal fallback are described as externally driven, not autonomous. PASS for claim boundaries; autonomy gap remains.
2. **Build/test evidence:** Inspected CMake registration and test source at the current PR head. GitHub fetch cannot compile or execute locally; runtime tests remain NOT RUN. This pass is evidence-labeling only; execution verification BLOCKED.
3. **Security/persistence/failure:** Static source inspection confirms journal loader stops at invalid event/sequence and truncates trailing bytes to the last valid boundary. No quarantine/forensic preservation is visible in this loader. Failure-injection tests are NOT RUN. Finding remains OPEN, no patch authorized.
4. **Architecture/capability benchmark:** Compared source-level loop and interfaces to integrated cognition and the fictional MCU benchmark. It has memory/belief/reasoning/prediction/planning/decision/assessment mechanisms but not demonstrated environment acquisition, built-in concrete adapters, or autonomous task orchestration. PASS for candid capability classification; integration gap remains.
5. **Hostile review:** Checked report for stale tree pointer, unsupported test claims, blanket capability assertions and scope violations. Found the stale tree pointer and corrected it above; exact file blob identities were revalidated. No source/runtime edits and no acceptance/closure claims added.

**Execution evidence:** GitHub remote source retrieval only. No local checkout, compiler, test runner, workflow dispatch or independent reviewer available in this execution. No tests passed or failed because none were executed.


## 2026-11-27 immediate-run: memory recovery and behavioral-test coverage trace

**Exact source blobs re-read at PR #203 head `9d31b61608753c58f1a5e431e45fda21be15e159`:**

- `core/cpp/src/memory.cpp` — `ba72a897306d4761246d0deab2fbab37c49d372f`
- `core/cpp/include/jarvis/core/memory.hpp` — `f3662038237246efa51155f940d77564f144d6d9`
- `core/cpp/tests/memory_architecture_suite.cpp` — `2a9eb061427c622260304d09f45089e1debef294`
- `core/cpp/src/action_execution.cpp` — `c2f8653eb755fa2790a88e49bc8b0b9c3077e439`
- `core/cpp/tests/action_execution_phase7_suite.cpp` — `b4a0060596c91c67080ac0a2db324f720d760fbe`
- `core/cpp/include/jarvis/core/cognitive_cycle.hpp` — `28e7af98327956268a769adf7813125be842c1a2`
- `core/cpp/tests/cognitive_cycle_suite.cpp` — `38ff2c7d6e851b4745e9dc7c01f968b7245400a2`

### Persistence findings refined

1. **Journal tail handling is destructive recovery, not recovery preservation.** `Memory::load()` parses sequential records, tracks `valid_end`, and unconditionally truncates the journal to `valid_end` when the file is longer. A corrupt first record yields `valid_end == 0`, so the entire journal can be truncated to zero. A corrupt later record discards the invalid record and all bytes after it. This may restore a parseable prefix, but there is no quarantine/copy/forensic retention in this code path. No checksum or record framing marker is visible in the inspected format.
2. **Metadata recovery can silently become partial.** `load_metadata()` validates the magic/count header, then mutates in-memory records as it reads each metadata record. If a later record is malformed/truncated, it returns immediately; earlier metadata mutations remain applied, while later entries are ignored. The function does not report a structured degraded/recovery status or preserve the failing offset in this implementation.
3. **Metadata snapshot replacement has a portability/durability question.** `persist_metadata_snapshot()` writes a temporary file and renames it to the metadata path. The inspected code does not show explicit file/directory fsync. The exact replacement behavior when the destination already exists is platform-dependent; this needs platform-specific test evidence rather than an assumption that rename always atomically replaces it.
4. **Append rollback is best-effort.** `persist()` records original file size and attempts resize rollback if a write/flush fails. It does not establish durable crash consistency or power-loss guarantees; the stream flush is not equivalent to fsync. This is a bounded observation, not a claim that append rollback always fails.

### Existing tests versus missing failure evidence

The current `memory_architecture_suite.cpp` verifies normal append, recall ranking, promotion, working-memory forgetting, reload and metadata restoration. It does not inject a truncated/corrupt first record, corruption after a valid prefix, invalid metadata header, truncated metadata payload, duplicate/non-monotonic journal sequence, or persistence failure. The test's happy-path reload therefore does not establish recovery behavior.

The current `action_execution_phase7_suite.cpp` verifies success, execution rejection/failure, verification failure and successful rollback using in-process callbacks. It does not demonstrate a real adapter, process crash recovery, idempotency, timeout/cancellation, concurrent action arbitration, or durable action/outcome reconciliation. The test proves callback orchestration under its fixtures, not end-to-end device/software control.

The cognitive-cycle suite supplies its observation, candidate actions, goal, resource budget and constraints as input. It verifies a synthetic integrated path through observation, planning, decisions and assessments. It does not demonstrate autonomous perception acquisition, goal discovery from open-ended context, external execution, or outcome-triggered unattended loop continuation.

### Test/build graph reconciliation

At the current PR #203 head, static parsing of `core/cpp/tests/CMakeLists.txt` found 45 `add_executable` declarations and 45 `add_test(NAME ...)` registrations; every executable has exactly one matching registration, with no unmatched or duplicate names. Root `core/cpp/CMakeLists.txt` includes CTest and conditionally adds the tests directory under `BUILD_TESTING`. This is static registration evidence only. No CMake configure, compilation, CTest execution, sanitizer, or fault-injection run was performed in this environment.

### Prioritized technical work (implementation not authorized)

- P0: Add corruption/failure-injection tests for journal first-record and mid-stream corruption, metadata partial reads, append failure and snapshot replacement on supported platforms.
- P0: Specify recovery policy before changing behavior: preserve original bytes, quarantine damaged tails, surface structured recovery status, and avoid silently destroying the only copy of user history.
- P1: Define journal record framing/versioning/checksum and explicit durability guarantees; test migration and replay determinism across versions.
- P1: Add action adapter contract tests for timeout, cancellation, idempotency, duplicate invocation, process restart and outcome reconciliation.
- P1: Distinguish cognitive-cycle completion from action completion and closed-loop task completion in API/status contracts.

**Disposition:** these are static-source findings and test-gap analysis. No implementation change, test execution, baseline selection, adoption/retirement decision, DF-02 closure or gate acceptance. Implementation remains unauthorized under the active scope.


## 2026-11-27 — CI evidence follow-up at PR #203 HEAD

The preceding immediate-run section correctly records that no local checkout/compiler/test runner was available during its static-source inspection. A GitHub Actions run subsequently completed for the exact PR #203 commit `15976103cc39b066d3de258fad414028460fef05`:

- Workflow: [Native Brain Build #2697](https://github.com/methaneex-oss/MethaneX/actions/runs/45956482214)
- Trigger: `pull_request`; workflow file: `.github/workflows/build.yml`
- Job `cpp`: **SUCCESS**
- Steps: checkout, CMake configure (`cmake -S core/cpp -B build -DCMAKE_BUILD_TYPE=Release`), and build (`cmake --build build --parallel`) all completed successfully.
- The build log shows the registered C++ test executables were compiled and linked. **No CTest command or behavioral test execution is present in this workflow.**

The exact ten source/test/CMake blob SHAs listed in this audit were re-fetched at commit `15976103cc39b066d3de258fad414028460fef05` and match the recorded identities. This verifies those inspected file contents at that commit; it is not a full-tree equivalence claim.

**Corrected evidence classification:** CMake configure and compilation/build are CI-verified for PR #203 HEAD `15976103...`. CTest, runtime behavioral tests, sanitizer runs, persistence fault-injection tests, and independent review remain **NOT EXECUTED / NOT VERIFIED**. The build result does not close DF-02, establish real-world autonomy, or authorize implementation, baseline selection, Stage A, or acceptance.
