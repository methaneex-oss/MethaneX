# DF-02 Cognitive Runtime Variant Adjudication — 2026-11-28

**Scope:** frozen candidate/donor runtime header/source, runtime test, feedback test, and CMake registration. Candidate `caf87986dfea7aca75728818651c8687e9f5faf0`; donor `c1da222e6c94aeb3f2ad000392c21fe4fc81ab25`. Source review only; no native build/CTest executed.

## Exact blobs
| Path | Candidate | Donor |
|---|---|---|
| `core/cpp/include/jarvis/core/cognitive_runtime.hpp` | `d02b2607cebcb7c31963e2fe336970707a481e00` | `e5a3c853add8b5fcb9b8c04c9b25f20179b5b629` |
| `core/cpp/src/cognitive_runtime.cpp` | `1a1383cedc42e357dc9efce117328b8d55e30bca` | `cf00acb6abd52308343f3a0e7016e6173b945603` |
| `core/cpp/tests/cognitive_runtime_suite.cpp` | `48cac9cb0e27e2dc8a15323429d1f7158ee427a0` | `361cba84a6fc6e07e31d14b5fa618c3f0a7848fa` |
| `core/cpp/tests/cognitive_runtime_goal_feedback_suite.cpp` | absent | `15a6bdffe37ae7df6c625ea9737fda4c0bf08a7f` |
| `core/cpp/CMakeLists.txt` | `c51816888e1bddb7bc00c59e72529524e27a0717` | `bc264ce7b4ae489404ca03ea6d9676d0330a6a56` |
| `core/cpp/tests/CMakeLists.txt` | `dab0c52ab4dfe15e1e2cbccfa9e6c904abdf54e3` | `cbfd1fde52fffa6eeac025da2b7ddcb5ab493261` |

## Material donor additions
- bounded asynchronous feedback queue/API for prediction sequence-bound outcomes, evidence, goal progress and utility; validates finite values and malformed payloads; reports accepted/rejected/processed/failed feedback.
- action adapter callbacks for execute/verify/rollback/consequence-observation/authorization; executes actions in selected plan order, records outcomes and feeds executor reliability evidence.
- configurable perception providers installed before worker start.
- workspace publishes representation, current Brain beliefs/causal links/predictions, affect/attention, goals and action outcomes; cycle evidence remains decision-time context, workspace is documented as current state.
- Expanded test suite from 87 to 356 lines plus new 84-line goal-feedback suite. Assertions cover provider sequencing/evidence, action authorization and execution, failed executor worker survival, prediction feedback including repeated keys/sequence binding, utility learning, goal progression/completion/regression, malformed/stale feedback, metrics, workspace and persistence.
- Candidate CMake has one runtime suite/CTest. Donor adds `cognitive_runtime_learning_integration_suite` and `cognitive_runtime_goal_feedback_suite`; exact registrations confirmed.

## Source-level operational risks
1. Worker prioritizes feedback over cycle inputs whenever feedback exists: continuous feedback can starve cognition. Priority queue has no aging; continuous higher-priority submissions may starve low-priority tasks.
2. Adapter callbacks run synchronously on the worker, with no runtime deadline/cancellation/isolation. A hung callback can stall the runtime and make `stop()` block.
3. `start()` sets `running_=true` before thread construction; thread-construction failure appears to leave the flag set without rollback.
4. During shutdown, stopping prevents new feedback submissions; action outcomes generated while draining may be rejected and lost. Drain semantics need a clear contract/test.
5. Fixed reliability scores (verified=1.0, executed=.75, rolled-back=.25) are heuristic and not outcome calibration; “executed” is not necessarily beneficial.
6. Callback executor remains in-process; runtime authorization is not a security sandbox or guaranteed reversible-action boundary.
7. Workspace reads multiple Brain state components separately and replaces workspace without proving atomic snapshot across concurrent external mutation.
8. No fault-injection coverage found for queue overflow, callback hangs/exceptions at each stage, journal failure, thread creation failure, simultaneous stop/submit, starvation, or mixed snapshots.

## Disposition
Exact candidate/donor source and tests inspected; CMake registration confirmed. Historical variants, exact reverse consumers, semantic/authority/retention, concurrency/failure tests, native build/CTest remain open. **Path OPEN / NO AUTHORITY DECISION.** No implementation selected/adopted/retired/deleted; DF-02 and Foundation gates remain open.
