# DF-02 Cognitive Runtime Variant Adjudication — 2026-11-28

**Scope:** exact candidate/donor comparison of `cognitive_runtime.hpp/.cpp`, tests, and CMake reachability at the frozen PR #192 candidate SHA and PR #97 donor HEAD.  
**Candidate:** `caf87986dfea7aca75728818651c8687e9f5faf0`.  
**Donor:** `c1da222e6c94aeb3f2ad000392c21fe4fc81ab25`.  
**Disposition:** runtime feature and behavior-contract differences established at source level. No tests executed in this audit. This is one bounded cohort; DF-02 remains OPEN.

## 1. Exact files and blobs

| File | Candidate blob | Donor blob |
|---|---|---|
| `include/jarvis/core/cognitive_runtime.hpp` | `d02b2607cebcb7c31963e2fe336970707a481e00` | `e5a3c853add8b5fcb9b8c04c9b25f20179b5b629` |
| `src/cognitive_runtime.cpp` | `1a1383cedc42e357dc9efce117328b8d55e30bca` | `cf00acb6abd52308343f3a0e7016e6173b945603` |
| `tests/cognitive_runtime_suite.cpp` | `48cac9cb0e27e2dc8a15323429d1f7158ee427a0` | fetched; expanded test file at donor |
| `tests/cognitive_runtime_goal_feedback_suite.cpp` | absent (404) | `15a6bdffe37ae7df6c625ea9737fda4c0bf08a7f` |
| `tests/CMakeLists.txt` | `dab0c52ab4dfe15e1e2cbccfa9e6c904abdf54e3` | fetched; includes additional suite registration |
| `core/cpp/CMakeLists.txt` | fetched at candidate | `bc264ce7b4ae489404ca03ea6d9676d0330a6a56` |

## 2. Candidate baseline behavior

Candidate runtime provides:
- explicit caller-submitted cognitive cycles and trigger-signal submission;
- bounded priority input queue, worker thread, start/stop and drain behavior;
- bounded result queue, dropping oldest result on overflow and metrics;
- cycle processing and workspace publication;
- exceptions caught at worker boundary and surfaced as failed results.

Candidate workspace uses cycle-context beliefs, causal links, predictions, eligible goals, and reflection. It does not install runtime perception providers, execute actions through adapters, or expose asynchronous feedback queue/metrics. The candidate runtime test submits 32 inputs, verifies completed cycles/selected goal/decisions, queue metrics, stop, and rejection after stop. It does not test execution, feedback, persistence of outcome, or perception-provider integration.

## 3. Donor additions and semantic differences

The donor adds a larger control surface:
- `CognitiveActionAdapter`: execute, verify, rollback and consequence-observation callbacks with authorization context;
- configurable feedback queue capacity and perception-provider installation;
- `CognitiveFeedback`: prediction-key/sequence-bound actual outcome, evidence, goal-progress/confidence and signed outcome utility;
- feedback/action metrics and pending-feedback visibility;
- asynchronous feedback processing on the runtime worker;
- selected-plan action execution (not every candidate assessment), authorization boundary, verification/rollback callbacks, and action outcome evidence;
- workspace refreshed from current Brain snapshot after action/feedback processing, including representation, memories, current beliefs/predictions, affect, appraisal, attention, eligible goals, execution results and reflection.

The donor's explicit plan-order matching avoids executing all candidate action assessments as if they were a batch of alternatives. Unmatched plan steps are skipped; repeated action names are matched against the next unconsumed assessment. This is better aligned with selected-plan semantics but needs tests for ambiguous/repeated names and mismatched plan/assessment data.

The donor separates prediction accuracy from outcome utility: utility is constrained to [-1,1] and can feed developmental learning independently of exact prediction match. It binds feedback to prediction creation sequence to avoid repeated-key stale feedback. Feedback submission validates basic payload shape/finite values without reading mutable Brain state from producer threads; the worker records assimilation failures rather than counting them as success.

## 4. Test-contract delta

Candidate's `cognitive_runtime_suite.cpp` is a queue/cycle smoke-contract. Donor's expanded runtime suite exercises:
- perception provider output and evidence sequence provenance;
- selected action execution and verification, action outcome journaling and executor feedback;
- authorization denial without adapter invocation;
- executor failure while worker remains alive;
- prediction feedback resolution, duplicate-key sequence binding, signed utility and developmental association;
- goal progress/completion and journal persistence after restart;
- stale prediction feedback reported failed, malformed feedback rejected;
- runtime queue metrics and shutdown.

Donor adds a separate `cognitive_runtime_goal_feedback_suite.cpp` for goal feedback persistence and regression failure. Candidate lacks this test path. Exact CMake registrations exist in donor; candidate registers the base runtime suite only. **Source assertions and registration are not executed-test evidence.**

## 5. Risk and open test obligations

Source inspection identifies questions not closed by these suites:
- **Fairness/starvation:** worker prioritizes feedback whenever feedback queue is nonempty, ahead of input cycles. Sustained feedback production could starve cognition-input work; no fairness bound/test is demonstrated.
- **Shutdown accounting:** `drain_on_stop=false` clears queued inputs/feedback. Metrics do not clearly expose how many accepted items were discarded; tests should assert lifecycle/accounting. `drain_on_stop=true` can block indefinitely if callbacks/providers hang; no cancellation/deadline contract is visible here.
- **Callbacks:** execution, verification, rollback and consequence-observation callbacks are synchronous worker operations. Exceptions are caught at a broader cycle boundary, but no timeouts, isolation or cancellation are shown. A hung callback can prevent stop/join.
- **Feedback attribution:** exact sequence binding is an improvement, but conflict cases where both key and sequence are supplied, invalid identifiers, duplicated evidence, utility without accepted prediction, and cross-goal/source trust still require full cycle/brain/journal contract review.
- **Action safety:** runtime delegates authority to ActionExecutor/authorization context and configured callbacks. Runtime does not itself establish that callbacks are safe, idempotent or externally verified; adapters are trusted integration boundaries.
- **Workspace consistency:** donor intentionally publishes current brain state while cycle evidence stays in the result context. Snapshot, affect, attention, intent, reflection are obtained through multiple calls, not one atomic aggregate; concurrent callers could observe a mixed-time workspace.
- **Priority/FIFO:** the input queue uses priority insertion, equal priorities retain FIFO. `WorkItem.sequence` is recorded but source comparison did not establish it is used to restore order under all cases; add ordering tests.
- **Queue overload:** results drop oldest; feedback and inputs reject on capacity. Behavior is observable through metrics but overload/recovery tests need boundary and race coverage.

## 6. Five review lenses

1. **Semantics:** donor introduces perception/action/feedback/goal-learning integration. Test evidence is stronger and more behavior-specific, but runtime still depends on external adapters and caller-supplied cycle inputs.
2. **Build/test reachability:** exact CMake registration distinguishes candidate's smaller suite set from donor's expanded runtime and goal-feedback tests. No compilation or test execution performed here.
3. **Trust/security:** action authorization is a boundary, not a guarantee about adapter trust. Feedback is untrusted input and has basic validation; provenance/authenticity and replay/duplicate handling are broader contracts.
4. **Capability realism:** donor provides asynchronous orchestration of submitted cognition, selected actions and outcome feedback. It is not autonomous perception/goal discovery by itself, and cannot run without adapters/inputs.
5. **Hostile review:** feature presence is not capability proof. Donor adds materially valuable behavior/test contracts, but no donor adoption decision follows; no code changed.

## 7. Disposition

| Obligation | Status |
|---|---|
| Candidate/donor header and implementation comparison | Complete for bounded files |
| Candidate/donor runtime tests and CMake reachability | Compared |
| Perception/action/feedback additions | Mapped |
| Queue fairness, cancellation, callback timeout, shutdown loss accounting | Open |
| Full caller/consumer and dependency graph | Partial |
| Native tests / build | Not executed |
| Provenance, authority, retention across alternate blobs | Open |
| DF-02 | OPEN |

**Disposition:** cognitive runtime cohort is source-adjudicated but not semantically/authority-closed. No implementation selected/adopted, alternate retired, or path closed. No runtime changes, Stage A, baseline, or Foundation gate authorization.
