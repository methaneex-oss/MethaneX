# JARVIS Integrated Cognitive Action & Feedback Loop Design

**Date:** 2026-09-25  
**Repository:** `methaneex-oss/MethaneX`  
**Status:** Design approved for implementation planning

## 1. Objective

Strengthen JARVIS as one continuously operating cognitive system by connecting the existing cognitive runtime to the existing action boundary and closing the observation/outcome loop back into cognition, memory, prediction resolution, and learning.

This is not a new Brain, Memory, Learning Engine, or orchestration architecture. Existing components remain authoritative. The work adds missing wiring and runtime contracts around them.

## 2. Existing Architecture to Preserve

The current system already contains a C++ cognitive cycle with meaningful stages including observation/perception input, memory recall, causal reasoning, prediction, goal selection, planning, decisions, action assessment, and reflection. A continuous cognitive runtime owns repeated cycle execution and a workspace exposes the latest cognitive state.

The existing prediction feedback capability belongs to `CognitiveCycle`; the runtime must only transport validated outcomes into that capability. External models remain replaceable components. Deterministic infrastructure, validation, authorization, persistence, and safety boundaries remain deterministic.

## 3. Target Runtime Loop

The integrated execution path should progressively become:

```text
External observation/event
        |
        v
CognitiveRuntime
        |
        v
CognitiveCycle
  perceive/interpret
        |
        +--> memory/context/world state
        |
        +--> reasoning/prediction
        |
        +--> goal/plan/decision
        |
        v
Authorized action boundary
        |
        v
Action execution adapter
        |
        v
Observed result/outcome
        |
        +--> memory/state update
        +--> prediction resolution
        +--> reflection/learning
        |
        +---------------------> next cognitive cycle
```

The runtime must not execute arbitrary tools directly. It should submit an action intent to a controlled boundary that performs authorization and capability checks before execution.

## 4. Action Contract

An action crossing the cognitive/action boundary must carry enough structured state to preserve causality:

- action identifier
- originating cognitive cycle identifier
- selected decision/goal context where available
- capability identifier
- structured parameters
- authorization context
- execution status
- start/end timestamps or monotonic sequence information
- result or failure classification
- resulting observations
- correlation to predictions when applicable

No phrase matching or manually authored situation-to-response table is permitted.

## 5. Authorization Boundary

Cognition may propose an action, but cognition does not implicitly grant permission to execute it.

The action boundary must evaluate:

1. capability existence;
2. authorization/policy state;
3. parameter validity;
4. execution availability;
5. safety constraints;
6. isolation requirements.

A denied action must become an observable cognitive outcome rather than disappearing silently.

## 6. Outcome Semantics

Execution must produce a structured outcome even when execution fails. At minimum, outcomes distinguish:

- accepted;
- denied;
- unavailable;
- started;
- completed;
- failed;
- timed out;
- cancelled;
- invalid input.

An outcome may contain structured evidence. Evidence must not automatically become truth; confidence, provenance, and contradictions remain part of the cognitive evidence model.

## 7. Feedback Integration

The existing `CognitiveCycle::process_outcome(...)` path remains the owner of prediction resolution and learning-related state transitions.

`CognitiveRuntime` owns transport, ordering, bounded queues, lifecycle, and metrics. It must not duplicate prediction-resolution logic.

Feedback processing should occur before subsequent queued cognitive work when practical so a completed outcome can affect the next cognitive cycle.

## 8. Failure and Resilience

The worker must survive malformed or failed action outcomes. An action adapter failure must become structured state and must not terminate the continuous cognitive worker.

Failures must remain observable to the self-model/resilience mechanisms. The runtime must preserve state where possible and maintain explicit metrics for rejected, failed, dropped, and processed work.

## 9. Observability

The workspace and runtime metrics should expose enough information to answer:

- what JARVIS last perceived;
- what it believed/reasoned;
- what goal and decision were selected;
- what action was proposed;
- whether authorization permitted it;
- what happened during execution;
- what outcome was observed;
- whether a prediction was resolved;
- whether feedback was persisted;
- whether the runtime degraded or rejected work.

Observability is not itself intelligence; it is evidence that the integrated path is actually operating.

## 10. Testing Requirements

Tests must exercise the actual integrated path, not only isolated classes.

Required coverage includes:

- action proposal reaches the authorization boundary;
- denied action produces a structured outcome;
- authorized action reaches an execution adapter;
- execution result becomes feedback;
- prediction feedback resolves through the existing cognitive cycle;
- persisted outcome survives Brain reconstruction;
- malformed feedback cannot terminate the worker;
- queue capacity and shutdown semantics remain bounded and deterministic;
- multiple cycles can consume prior outcomes;
- failures remain observable through runtime metrics/workspace state.

## 11. Explicit Non-Goals

This design does not:

- replace the existing Brain;
- create a second memory implementation;
- create a second learning engine;
- make an LLM the JARVIS runtime;
- introduce a generic chatbot loop;
- introduce hard-coded phrase-to-action intelligence;
- make autonomous external execution unrestricted;
- redesign the existing polyglot architecture;
- require every action to use a single model/provider;
- treat a passing unit test as proof of whole-system capability.

## 12. Success Criterion

The batch is successful only when a real runtime execution path can demonstrate:

```text
observation
  -> cognition
  -> decision
  -> authorized action
  -> execution result
  -> observation/outcome
  -> existing memory/prediction/learning path
  -> subsequent cognition
```

The result should be observable and testable as one JARVIS capability, not merely as a collection of newly added classes.
