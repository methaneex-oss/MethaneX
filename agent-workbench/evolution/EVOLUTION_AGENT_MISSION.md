# Autonomous Evolution Agent Mission

## Objective

Continue the existing JARVIS evolution subsystem toward a real evidence-driven autonomous evolution loop. This is a continuation task, not a rewrite.

## Required lifecycle

`opportunity -> evidence -> hypothesis -> candidate -> validation -> ranking -> scheduling -> baseline -> isolated trials -> statistical evaluation -> safety gate -> adoption -> canary -> monitoring -> retain/rollback -> persistent history -> future learning`

## First engineering targets

### 1. Statistical evaluation

Replace heuristic confidence with measured trial statistics. Preserve raw trial observations and compute variance, effect size, confidence intervals, practical improvement thresholds, and regression protection. Use conservative defaults. Do not call heuristic scores confidence.

### 2. Transactional adoption

Audit `EvolutionController` and adoption journal/history interactions. Prevent a partially committed adoption where model state changes but required provenance/history writes fail. Design an explicit commit protocol or compensating rollback.

### 3. Canary lifecycle

Ensure adoption transitions are observable as:

`adopted -> canarying -> healthy/rollback-required -> retained/rolled-back`

Record each transition and its evidence.

### 4. Persistence

Integrate evolution history with the existing durable JARVIS state/event architecture. Restart reconstruction must preserve experiment provenance and current lifecycle state.

### 5. Cognitive evidence

Consume normalized evidence from the cognitive runtime rather than hard-coded phrases. Examples include recurring prediction error, degraded measured capability performance, uncertainty, and repeated action failures.

### 6. Learning feedback

Make historical evolution outcomes influence future candidate ranking/strategy selection through the existing learning infrastructure.

## Collaboration protocol

Before changing shared files, announce the intended file/scope through the agent message bus. Send evidence, test results, and artifact identifiers to dependent agents. Do not silently overwrite another agent's workspace changes.

## Definition of done

A candidate is not considered complete because classes compile. The lifecycle must be connected, exercised by tests, failure paths must be covered, and the resulting evidence must be reproducible.
