# Integrated Cognitive Action & Feedback Loop Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Connect JARVIS's existing cognitive runtime, action authorization/execution, observation, and outcome-learning paths into one bounded continuous execution loop without creating a parallel cognitive architecture.

**Architecture:** Preserve `CognitiveCycle` as the cognitive owner and `ActionAuthorizer`/`ActionExecutor` as the controlled action boundary. Extend the runtime only where it needs to transport action requests and structured outcomes, then route outcomes through the existing cognitive feedback/persistence path. No LLM, tool adapter, or hard-coded phrase mapping becomes authoritative.

**Tech Stack:** C++17/20-style existing core, existing CMake/test structure, persistent Brain state, existing action model/authorization/execution contracts, `CognitiveRuntime` and `CognitiveCycle`.

**Spec:** `docs/superpowers/specs/2026-09-25-cognitive-action-feedback-loop-design.md`

## Global Constraints

- Continue development of the existing `methaneex-oss/MethaneX` repository; do not create a replacement architecture.
- Preserve existing C++/Rust/TypeScript boundaries and existing authoritative Brain, memory, cognition, capability, authorization, and execution components.
- Do not create a second Brain, memory system, learning engine, action executor, or orchestration runtime.
- No hard-coded phrase-to-action intelligence or fake `understand()/think()/learn()/reason()` implementations.
- Cognition proposes; authorization controls; execution performs; observation/outcome feeds cognition.
- Failed, denied, malformed, timed-out, and unavailable actions must remain observable and must not terminate the continuous cognitive worker.
- Bounded queues and explicit lifecycle behavior are required for new runtime work.
- External models remain replaceable components and never become the JARVIS state authority.

## Review Focus

1. **Authorization bypass:** an action that is assessed but not permitted must never reach its execution callback — owned by Task 2's authorization/execution integration test.
2. **Execution failure:** an adapter that returns failure must generate a structured outcome and keep the cognitive runtime alive — owned by Task 2's failure test.
3. **Outcome ordering:** feedback from a completed prediction must be consumed before a subsequent cognitive cycle when both are queued — owned by Task 3's ordering test.
4. **Malformed feedback:** invalid or uncorrelated outcome data must be rejected without worker termination — owned by Task 3's validation test.
5. **Persistence:** a resolved prediction/outcome must survive reconstruction of the existing Brain journal — owned by Task 4's persistence test.

---

### Task 1: Establish the Runtime-to-Action Contract

**Files:**
- Modify: `core/cpp/include/jarvis/core/cognitive_runtime.hpp`
- Modify: `core/cpp/src/cognitive_runtime.cpp`
- Modify: `core/cpp/include/jarvis/core/cognitive_workspace.hpp` only if the existing workspace lacks fields required to observe proposed/executed action state
- Test: `core/cpp/tests/cognitive_runtime_suite.cpp`

**Interfaces:**
- Consumes: existing `CognitiveCycleResult`, `ActionAssessment`, `ActionAuthorizationContext`, and `ActionExecutionResult`.
- Produces: a bounded runtime representation of action work and its structured outcome, without embedding authorization or execution logic in `CognitiveRuntime`.

- [ ] **Step 1: Read the current action model, authorization, execution, workspace, cycle, and runtime implementations and record their exact current signatures before changing them.**

  Verify the existing contracts in:
  - `core/cpp/include/jarvis/core/action_model.hpp`
  - `core/cpp/include/jarvis/core/action_authorization.hpp`
  - `core/cpp/include/jarvis/core/action_execution.hpp`
  - `core/cpp/include/jarvis/core/cognitive_runtime.hpp`
  - `core/cpp/include/jarvis/core/cognitive_workspace.hpp`
  - corresponding `.cpp` files.

- [ ] **Step 2: Add a failing integration test for an action assessment reaching a controlled runtime boundary.**

  The test must construct a real `Brain`, run a real `CognitiveRuntime`, provide a candidate action, and assert that the runtime exposes a structured action result rather than merely a decision string.

- [ ] **Step 3: Add only the minimal runtime contract needed to carry action requests/results.**

  The contract must retain action identity/correlation, authorization state, execution status, reason, and outcome data. Do not put callback execution or policy evaluation inside the runtime queue type.

- [ ] **Step 4: Run the focused runtime test and confirm it passes.**

  Use the repository's existing CMake/test invocation discovered during implementation. Expected result: the new action-boundary test passes while all pre-existing cognitive runtime tests remain unchanged and passing.

- [ ] **Step 5: Commit the contract integration.**

  Commit message: `feat(cognition): expose controlled action runtime boundary`

---

### Task 2: Wire Authorization and Execution Without Bypass

**Files:**
- Modify: `core/cpp/src/cognitive_runtime.cpp`
- Modify: `core/cpp/include/jarvis/core/cognitive_runtime.hpp`
- Modify: existing action execution source only where required by its current implementation
- Test: existing action authorization/execution suite and `core/cpp/tests/cognitive_runtime_suite.cpp`

**Interfaces:**
- Consumes: `ActionAssessment`, `ActionAuthorizationContext`, and existing `ActionExecutor`.
- Produces: `ActionExecutionResult` plus a structured runtime outcome suitable for cognitive feedback.

- [ ] **Step 1: Write the failing authorization-bypass test.**

  Construct an assessment with `permitted == false` or insufficient authorization and an execution callback that records invocation. Assert the callback is never invoked and the result is `rejected` with `authorized == false`.

- [ ] **Step 2: Run the focused test and verify the failure is caused by the missing runtime integration.**

  Do not modify authorization policy to force the test to pass.

- [ ] **Step 3: Wire the existing `ActionAuthorizer` and `ActionExecutor` into the runtime boundary.**

  The runtime may supply authorization context and an execution adapter, but it must not duplicate `has_permission`, risk, reversibility, or execution-state logic already owned by those components.

- [ ] **Step 4: Write the failing execution-failure test.**

  Supply an authorized action whose execution callback returns `false`. Assert that the returned state is `failed`, that the worker remains alive, and that the failure can be converted into a cognitive outcome.

- [ ] **Step 5: Implement structured failure conversion.**

  Map rejection, failed execution, verification failure, cancellation, and rollback to explicit outcome states. Preserve the original reason and action correlation.

- [ ] **Step 6: Run the action and runtime suites.**

  Expected: authorization cannot be bypassed, failed execution does not terminate the worker, and existing action tests remain green.

- [ ] **Step 7: Commit the action-boundary integration.**

  Commit message: `feat(cognition): enforce authorized action execution boundary`

---

### Task 3: Close Execution Outcome Into Cognitive Feedback

**Files:**
- Modify: `core/cpp/include/jarvis/core/cognitive_runtime.hpp`
- Modify: `core/cpp/src/cognitive_runtime.cpp`
- Modify: `core/cpp/include/jarvis/core/cognitive_cycle.hpp` or source only if an existing outcome contract cannot represent action outcomes
- Test: `core/cpp/tests/cognitive_runtime_suite.cpp`

**Interfaces:**
- Consumes: structured `ActionExecutionResult`/runtime outcome.
- Produces: existing `CognitiveCycle::process_outcome(...)` updates and observable workspace/runtime metrics.

- [ ] **Step 1: Write the failing ordering test.**

  Queue a prediction outcome and a new cognitive input while the runtime is active. Assert that feedback processing completes before the next cycle consumes state that depends on that outcome.

- [ ] **Step 2: Write the malformed-feedback test.**

  Submit an outcome with no valid prediction/evidence correlation. Assert rejection, unchanged cognitive state, and a still-running worker.

- [ ] **Step 3: Implement bounded feedback transport.**

  Use a dedicated bounded feedback queue or extend the existing one only if the current repository already has the equivalent. Record accepted/rejected/processed counts and keep feedback ahead of normal cognitive work when both are ready.

- [ ] **Step 4: Route feedback through the existing cognitive outcome owner.**

  Call the existing prediction/evidence processing mechanism rather than duplicating prediction resolution in the runtime.

- [ ] **Step 5: Run the focused integration suite.**

  Expected: prediction feedback changes persistent cognitive state, malformed feedback is rejected, and the runtime continues operating.

- [ ] **Step 6: Commit the closed-loop feedback transport.**

  Commit message: `feat(cognition): close action outcomes into cognitive feedback`

---

### Task 4: Prove Persistence and Subsequent Cognitive Influence

**Files:**
- Test: `core/cpp/tests/cognitive_runtime_suite.cpp`
- Modify: only the existing persistence/cognition source if the integration test exposes a real defect in the current path

**Interfaces:**
- Consumes: the complete runtime action/outcome path from Tasks 1–3.
- Produces: evidence that a completed outcome survives persistence and can influence a later cognitive cycle.

- [ ] **Step 1: Write the end-to-end test.**

  Exercise:

  ```text
  observation
    -> cognitive cycle
    -> decision/action assessment
    -> authorization
    -> execution
    -> structured outcome
    -> cognitive feedback
    -> persisted Brain state
    -> second cycle
  ```

  The test must assert state, not merely that functions were called.

- [ ] **Step 2: Run the test and identify any real persistence or integration defect.**

  Do not add test-only state or mocks that bypass the Brain journal.

- [ ] **Step 3: Fix only the underlying defect exposed by the integrated path.**

  Preserve existing serialization formats and compatibility unless a migration is demonstrably necessary.

- [ ] **Step 4: Reconstruct `Brain` from the same journal and assert the outcome remains represented.**

  Assert that the later cognitive cycle can consume the resulting state through the existing memory/cognition mechanisms.

- [ ] **Step 5: Run the complete relevant C++ test suite.**

  Expected: existing cognitive, action, persistence, and runtime tests pass, with no regression in unrelated capabilities.

- [ ] **Step 6: Commit the end-to-end capability verification.**

  Commit message: `test(cognition): verify persistent action feedback loop`

---

### Task 5: Verification and Repository Checkpoint

**Files:**
- Modify: documentation only if implementation changed an observable contract that is not already documented.

**Interfaces:**
- Consumes: complete integrated runtime/action/feedback capability.
- Produces: verified repository checkpoint and evidence suitable for the next JARVIS capability.

- [ ] **Step 1: Run formatting/static checks already required by the repository.**

  Do not introduce a new formatter or linter solely for this batch.

- [ ] **Step 2: Run the complete relevant C++ test target and any existing repository-level tests that exercise the cognitive core.**

  Record exact commands and results.

- [ ] **Step 3: Exercise one real runtime scenario manually or through the strongest existing integration harness.**

  Demonstrate the complete loop from observation through action and outcome back into cognition.

- [ ] **Step 4: Inspect the final diff for architectural duplication.**

  Confirm there is one Brain, one cognitive cycle, one action authorization boundary, one action execution boundary, and one feedback path.

- [ ] **Step 5: Produce the checkpoint report.**

  Report separately:
  - implemented;
  - tested;
  - integrated;
  - runtime-reachable;
  - behaviorally demonstrated;
  - remaining limitations.

- [ ] **Step 6: Commit the final documentation/checkpoint changes if any.**

  Commit message: `docs: record cognitive action loop verification`

---

## Self-Review

- The design preserves the existing cognitive/action architecture instead of introducing a second orchestration system.
- Every new runtime behavior has a corresponding integration test requirement.
- Authorization is explicitly tested as a hard boundary.
- Execution failure is explicitly tested as non-fatal to the cognitive worker.
- Feedback ordering and malformed feedback are explicitly tested.
- Persistence is verified through actual Brain reconstruction rather than test-only memory.
- The plan deliberately avoids defining provider-specific model behavior because external models are components, not the JARVIS architecture.
- The plan does not assume a specific action implementation beyond the repository's existing `ActionAuthorizer` and `ActionExecutor` contracts; implementers must inspect their current `.cpp` behavior before modifying them.
