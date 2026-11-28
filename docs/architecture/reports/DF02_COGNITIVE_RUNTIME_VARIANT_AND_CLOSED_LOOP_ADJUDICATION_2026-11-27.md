# DF-02 Cognitive Runtime Variant and Closed-Loop Evidence Adjudication — 2026-11-27

**Scope:** all seven exact `core/cpp/src/cognitive_runtime.cpp` blobs, frozen candidate/donor headers, runtime test sources and CMake target/CTest differences.  
**Candidate:** PR #192 frozen SHA `caf87986dfea7aca75728818651c8687e9f5faf0`.  
**Donor:** PR #97 frozen HEAD `c1da222e6c94aeb3f2ad000392c21fe4fc81ab25`.  
**Disposition:** a major runtime capability delta and a bounded behavioral closed-loop test contract are established. Source/test inspection only; no tests executed. Path remains OPEN.

## 1. Exact version inventory

Seven distinct runtime source blobs are represented in the frozen artifact (candidate, donor, five alternates); all contents were fetched and inspected.

| Blob SHA | Role | Tip count | Representative branch |
|---|---|---:|---|
| `1a1383cedc42e357dc9efce117328b8d55e30bca` | Candidate | 103 | architecture/brain-foundation-planning-20261103 |
| `cf00acb6abd52308343f3a0e7016e6173b945603` | Donor | 76 | ci/priority-one-provenance-validation20261031 |
| `c95a3baf64fc24ccdd00eb73bfd065b792f88f62` | Alternate | 19 | capability-decision-work |
| `4b3ec814636ca0fb27c7f79557113f1f49f0b6f2` | Alternate | 11 | feat/action-execution-feedback-phase7 |
| `56143e8e200b65d683e81b66af4c6caead39b6ae` | Alternate | 1 | docs/jarvis-affective-plan |
| `7e8210a3e0ab1d00bdf1bc5d5d334d05933d77c2` | Alternate | 1 | feat/continuous-cognitive-runtime |
| `972804414c9522e52062568cb7227fad9b45ff06` | Alternate | 1 | feat/runtime-closed-loop-feedback |

Tip counts indicate blob sightings, not independent implementations or authority. The variants show a progression of asynchronous cognition, continuous runtime, feedback, action-execution feedback, and affective runtime; chronology/branch naming alone does not determine the successor.

## 2. Candidate/donor source and API delta

Candidate source SHA `1a1383cedc42e357dc9efce117328b8d55e30bca` (187 lines) is an asynchronous work queue around `CognitiveCycle`: start/stop, direct and trigger-based submit, priority ordering, bounded input/result queues, result polling, workspace publication and worker exception containment. The candidate runtime API does not expose feedback queueing, adapter-driven action execution or perception-provider installation.

Donor source SHA `cf00acb6abd52308343f3a0e7016e6173b945603` (225 lines) adds:
- feedback queue and validation (`submit_feedback`, `process_feedback`) for prediction outcomes, evidence and goal-progress/outcome assimilation;
- sequence-bound prediction feedback and optional explicit signed task utility, avoiding key-only ambiguity when prediction keys recur;
- optional perception-provider installation at runtime construction;
- execution of only plan-selected actions, in plan order, via the configured action adapter and Brain action authorization/verification/rollback boundary;
- action execution results in the cycle result/workspace and action/feedback metrics;
- observed-consequence feedback, when an adapter supplies it, can feed prediction resolution and developmental/affective learning.

The donor runtime/header blobs:
- source `cf00acb6abd52308343f3a0e7016e6173b945603`;
- header `e5a3c853add8b5fcb9b8c04c9b25f20179b5b629`.

Candidate header SHA `d02b2607cebcb7c31963e2fe336970707a481e00`. Candidate config exposes input/result capacities, drain behavior and trigger; donor adds feedback capacity, action adapter (authorization/execute/verify/rollback/observe-consequence), and perception providers. This is a genuine architectural capability change, not simply a refactor.

## 3. Variant-family observations

- Candidate and `c95a3baf64fc24ccdd00eb73bfd065b792f88f62` retain the simpler queue/runtime API (the latter's source is a distinct blob).
- `7e8210a3e0ab1d00bdf1bc5d5d334d05933d77c2` is the continuous-runtime variant with workspace support but no feedback/action adapter contract.
- `972804414c9522e52062568cb7227fad9b45ff06` adds feedback processing but does not expose the donor's full action-execution method set.
- `4b3ec814636ca0fb27c7f79557113f1f49f0b6f2` and `56143e8e200b65d683e81b66af4c6caead39b6ae` include action/feedback/goal/affective method families; the latter has a larger implementation surface.
- Donor integrates action execution, feedback, provider setup and outcome publication. These exact method-family differences are extracted from source; every alternate's complete state-transition and error behavior remains unclosed.

## 4. Cross-file behavior evidence — exact test sources

Candidate runtime test SHA `48cac9cb0e27e2dc8a15323429d1f7158ee427a0` exercises a simple async worker: submit 32 prioritized inputs, receive completed cognitive-cycle results, metrics, queue drain and reject after stop.

Donor runtime test SHA `361cba84a6fc6e07e31d14b5fa618c3f0a7848fa` materially expands the behavioral contract. It uses test fixtures/callbacks (not real external adapters) to assert:
- perception provider output carries the committed observation sequence and evidence provenance;
- only plan-selected actions execute, and result/workspace records execution status;
- verified, denied and failing action adapters produce the corresponding statuses; denial does not call the executor;
- action-outcome memory and action feedback are processed;
- prediction feedback resolves the originating sequence, including repeated-key protection;
- explicit task utility (negative utility) is not conflated with prediction accuracy;
- goal progress and completion feedback are persisted/reloaded;
- contextual developmental learning changes action selection in the trained context, does not blindly transfer to a different context, and reverses after simulated environment-regime change;
- a no-consequence-feedback control verifies that successful execution alone does not create a positive developmental action preference;
- runtime remains alive after fixture failures and persistence affects a later decision after restart.

Two donor-only test suites are present and registered:
- `cognitive_runtime_goal_feedback_suite.cpp`, blob `15a6bdffe37ae7df6c625ea9737fda4c0bf08a7f`;
- `cognitive_runtime_learning_integration_suite.cpp`, blob `656de56b1368e40afb090778a7a5504ab4208056`.

Candidate core test CMake blob `dab0c52ab4dfe15e1e2cbccfa9e6c904abdf54e3` has 45 executable and 45 CTest entries. Donor CMake blob `cbfd1fde52fffa6eeac025da2b7ddcb5ab493261` has 71 executable targets and 70 CTest entries; donor-only targets include the runtime learning-integration and goal-feedback suites. No candidate-only CTest target was found in the exact target-set comparison. Registration and source assertions are not execution evidence. Tests were not run.

## 5. Static safety/semantic risks to verify

1. **Stop/drain race can drop in-flight feedback:** `stop()` sets `stopping_ = true`. While a worker is processing an already-dequeued cycle, `execute_actions()` may submit consequence/evidence feedback. `submit_feedback()` rejects when `stopping_` is true. Thus `drain_on_stop` can drain feedback already queued, but does not guarantee assimilation of feedback generated by in-flight work during shutdown. This is a source-derived risk requiring a deterministic test and a defined shutdown contract.
2. **Feedback priority may starve cognition inputs:** worker loop consumes feedback whenever the feedback queue is nonempty, before input work. With sustained external feedback arrival, queued cognitive inputs may wait indefinitely. Capacities bound each queue, not fairness. A scheduling/fairness policy and stress test are absent from the inspected contract.
3. **Queue saturation:** feedback generated by action execution is submitted asynchronously and can be rejected when the feedback queue is full or shutdown begins. The rejection metric records it, but there is no retry/backpressure or durable pending-feedback queue in this runtime. Action results remain in the cycle result, so feedback loss is observable only through metrics unless callers inspect them.
4. **Action execution is opt-in by adapter, but automatic once configured:** a completed cycle causes the runtime to execute the plan-selected action steps when an adapter is configured. Authorization, verification and rollback are delegated to Brain/action-executor contracts. This must not be described as safe arbitrary external execution; adapter identity, timeout/cancellation, idempotency, process restart and real integration remain unproven.
5. **Name-based assessment matching:** selected plan steps are matched to unused action assessments by action name. Duplicate names with differing parameters or repeated plan steps need explicit behavior/tests.
6. **Feedback meaning and autonomy boundary:** the runtime does not itself acquire an external sensor stream or autonomously invent tasks/goals. Callers submit cognitive inputs/trigger signals; providers process supplied observations; action adapters execute selected steps. The donor integration tests demonstrate a fixture-driven closed loop, not unattended agent autonomy.

These are audit findings/risks; no implementation change was authorized or made.

## 6. Five review lenses

1. **Semantic:** donor adds asynchronous outcome assimilation and real execution boundary, but feedback is a separate queue/state transition; tests show a fixture loop, not autonomy.
2. **Build/test:** donor registers new runtime integration suites; CMake count reconciled. Test content inspected; no native execution in this audit.
3. **Security/authority:** action adapter is bounded by authorization/verification contracts; no real adapter, process-level isolation, cancellation, or restart reconciliation validated.
4. **Cognition/capability:** contextual outcome feedback can change future action selection and persistence in the test fixture. This is stronger evidence than API presence, but still synthetic and limited to supplied candidate actions/context.
5. **Hostile review:** shutdown feedback loss and feedback-priority starvation risks surfaced; no inflated claims or source changes.

## 7. Disposition

| Obligation | State |
|---|---|
| Seven exact runtime source blobs inventoried | Complete for this slice |
| Candidate/donor runtime API and behavior comparison | Complete for bounded comparison |
| Candidate/donor test-source comparison | Complete for bounded contract |
| Donor runtime learning/goal-feedback suites and CMake registration | Confirmed |
| Stop/drain feedback loss and starvation behavior | Risks identified; test/decision open |
| Real adapter, cancellation, idempotency, restart/outcome reconciliation | Open |
| Full historical owner/authority/retention | Open |
| Runtime path and DF-02 | OPEN |

**Disposition:** `core/cpp/src/cognitive_runtime.cpp` remains **OPEN / NO AUTHORITY DECISION**. No implementation selected, adopted, retired or deleted. This report does not close DF-02, Foundation gates, or authorize Stage A.

 
## Additional donor-only integration suites and historical execution evidence — 2026-11-28

The previous bounded test inventory named the runtime learning-integration and goal-feedback suites but did not enumerate their complete contracts or attach actual test-run evidence. The following exact recheck closes that evidence gap for the historical alternate branch only.

### Exact donor-only test contracts and CMake reachability

1. **cognitive_runtime_learning_integration_suite.cpp**
   - Blob: 656de56b1368e40afb090778a7a5504ab4208056; 326 lines / 88 assert expressions.
   - Candidate path is absent. Donor CMake blob cbfd1fde52fffa6eeac025da2b7ddcb5ab493261 registers executable at lines 64–66 and CTest at line 244.
   - The test drives a real CognitiveRuntime worker with deterministic test callbacks. It asserts action execution and observed consequence feedback; resolution of the action-consequence prediction; prediction-error metric, affective learning and episodic outcome memory; a subsequent choice change from calibrate to wait; context isolation between runtime-learning-context and orchard-irrigation-context; adaptation after an environment-regime reversal within a bounded 40-observation loop; strategy persistence across restart; a real post-restart decision using the restored preference; and a no-feedback control proving verified execution alone does not create a developmental preference.
2. **cognitive_runtime_goal_feedback_suite.cpp**
   - Blob: 15a6bdffe37ae7df6c625ea9737fda4c0bf08a7f; 83 lines / 22 assert expressions.
   - Candidate path is absent. Donor CMake registers executable at lines 172–174 and CTest at line 280.
   - It verifies asynchronous goal-progress and goal-completion feedback, durable goal_progress/goal_complete events, regression rejection during worker assimilation, feedback_failed accounting, and goal reconstruction after restart.
3. **brain_action_consequence_integration_suite.cpp**
   - Blob: 7616082579d53e3579cae8e87895bdb3dadba66f; 316 lines / 95 assert expressions.
   - Candidate path is absent. Donor CMake registers executable at lines 187–189 and CTest at line 285.
   - It verifies harmful-surprise attention, unknown versus zero consequence, observed consequence despite verification failure, exact context in action_outcome, strategy change, affect/attention/forecast persistence, and next-observation forecast resolution.

Candidate core test CMake blob dab0c52ab4dfe15e1e2cbccfa9e6c904abdf54e3 does not register these three donor-only suites. Donor core test CMake registers all three. The donor test graph is therefore materially richer; test-source presence alone must not be conflated with candidate reachability.

### Historical execution evidence for exact runtime/test blobs

The alternate branch fix/evolution-authenticated-replay-final-20261030 at HEAD e737cae7f907696ef787a4e85b0dee3a739d71b1 contains the exact runtime and test blobs listed above:
- cognitive_runtime.cpp cf00acb6abd52308343f3a0e7016e6173b945603;
- cognitive_cycle.cpp f191dd610d6cbe1621756c35e7c13af2054a7266;
- brain_action_execution.cpp 3b66bafb438cd28790e6f25611b96c86f1eff05c;
- action_execution.cpp af5bed6cec9ed1309b24ed3d50241fb4c0d33bff;
- cognitive_runtime_learning_integration_suite.cpp 656de56b1368e40afb090778a7a5504ab4208056;
- cognitive_runtime_goal_feedback_suite.cpp 15a6bdffe37ae7df6c625ea9737fda4c0bf08a7f;
- brain_action_consequence_integration_suite.cpp 7616082579d53e3579cae8e87895bdb3dadba66f;
- tests/CMakeLists.txt cbfd1fde52fffa6eeac025da2b7ddcb5ab493261.

These exact suites were compiled and passed in the post-fix historical CI:
- Brain CI #1826: native-brain and sanitizer jobs; test #23 (runtime learning integration), #59 (goal feedback), #64 (action consequence) all Passed in both jobs.
- JARVIS Brain Tests #975: brain and sanitizer jobs; tests #23, #59 and #64 all Passed in both jobs.
- Brain ThreadSanitizer #957: TSAN job; tests #23, #59 and #64 all Passed.
- Each of those five test jobs reported 71/71 tests passed (100%).

This is real behavioral evidence for those exact source/test/CMake blobs on the e737cae7 alternate branch. It is not a test result for PR #203, not a result for frozen donor HEAD c1da222e, and not a baseline/adoption decision. The earlier PR #97 donor HEAD itself returned no workflow runs/status in the connector.

### Capability interpretation and limits

The runtime integration suite demonstrates a fixture-driven closed loop with observed outcomes, context-conditioned learning, regime-shift adaptation and persistence that changes a later action decision. That is materially stronger evidence than API presence or a simple worker-queue test. It still uses two predefined candidate actions and deterministic callbacks; it does not demonstrate autonomous task discovery, open-world perception, real hardware execution, robust multi-agent coordination, or held-out generalization across a broad task distribution. The test's polling windows are bounded (approximately one second for result/feedback waits), and the environment model is synthetic.

The historical CI proves that these tests passed under native, sanitizer and ThreadSanitizer jobs in that branch. It does not certify external adapter safety or eliminate the runtime's previously identified stop/drain feedback-loss, queue-starvation, cancellation, idempotency and restart-reconciliation risks.

No source was changed. Current PR #203 remains documentation-only and the cognitive-runtime path remains OPEN.
