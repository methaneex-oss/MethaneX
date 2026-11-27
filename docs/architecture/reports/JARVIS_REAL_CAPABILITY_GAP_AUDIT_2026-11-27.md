# JARVIS Real-Capability Gap Audit — 2026-11-27

**Disposition:** bounded static-source evidence; not implementation, acceptance, or DF-02 closure.  
**Reviewed PR #203 source tree:** `a7d9d735fd516b984314f037224b4827fbbf9c26` (documentation-only head; runtime files match the candidate source tree reviewed).  
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
