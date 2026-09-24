# JARVIS Cognitive Architecture

## Purpose

The brain is a persistent cognitive substrate. It receives observations, maintains an evolving internal representation, forms and revises beliefs, predicts outcomes, evaluates alternatives, learns from results, and adapts its own strategies.

## Cognitive flow

```text
Observation
    ↓
Perception / Evidence
    ↓
Attention ───────→ Working Context
    ↓                     ↓
Belief Revision ←→ World Model
    ↓                     ↓
Causal Model ←────── Prediction
    ↓
Simulation / Counterfactuals
    ↓
Planning / Decision
    ↓
Action through capability layers
    ↓
Outcome
    ↓
Learning → Reflection → Adaptation → Evolution
    ↘
   Continuity Memory
```

## Continuity

The event stream is the durable history. A running process can reconstruct cognitive state from that history, allowing a restart or component replacement without treating the new process as a blank mind.

## Learning

Learning is outcome-driven. Predictions can be resolved against observed results, producing error signals that update adaptive metrics. Knowledge from different sources is fused according to evidence rather than assigning permanent authority to one external model.

## Evolution

Evolution is intended to be evidence-driven rather than scheduled. The C++ core owns the lifecycle, deterministic evidence gates, orchestration, history and reversible adoption semantics. Statistical/ML-heavy learning may be supplied by Python through an explicit provider boundary rather than embedding model-specific intelligence into the native core.

Evolution must remain observable, reversible and integrity-preserving.

## Resilience

The brain maintains awareness of component health and capability availability. Failure handling is based on detected state and recovery information rather than a hard-coded timer. A degraded subsystem should be isolated where necessary while unaffected cognitive capabilities continue operating.

## Language boundaries

The cognitive substrate is intentionally polyglot:

- **C++** — cognitive state, deterministic reasoning primitives, memory/state structures, orchestration, lifecycle coordination and other native low-latency substrate work.
- **Rust** — security-sensitive runtime services, process/sandbox enforcement, privilege boundaries, concurrency-sensitive infrastructure and other components where memory safety is a primary requirement.
- **Python** — scientific/ML-heavy learning, statistical experimentation, model evaluation and optimization where its ecosystem provides a real technical advantage.
- **TypeScript** — integration contracts, external interfaces and orchestration-facing adapters.

C++ must not become the owner of OS-level isolation/security enforcement merely because the cognitive core needs to request an isolated execution. The core requests an execution through an explicit provider boundary; the runtime responsible for enforcement owns the actual security mechanism.

Components communicate through explicit contracts rather than language-specific assumptions. A language is not selected because it is convenient; it is selected because the responsibility belongs there.
