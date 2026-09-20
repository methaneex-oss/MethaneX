# JARVIS Engineering Layer

The engineering layer is the software organization that builds, verifies, and evolves JARVIS. It is deliberately separate from the cognitive substrate.

## Boundary

The cognitive core reasons about goals, state, evidence, capabilities, and actions. The engineering layer provides structured workers that can perform engineering work and return artifacts plus evidence.

An agent is not intelligence by itself. An agent is a provider-backed worker with declared capabilities, permissions, cost, risk, availability, and artifact contracts.

The coordinator does not interpret natural-language phrases or vendor names. It evaluates declared metadata against a task contract and produces eligible candidates. Provider-specific adapters are added outside this protocol.

## Work flow

```text
Engineering objective
        ↓
Task contract
        ↓
Agent discovery
        ↓
Eligibility / authorization constraints
        ↓
Agent selection
        ↓
Execution boundary
        ↓
Artifacts + evidence
        ↓
Independent verification
        ↓
Cognitive outcome
```

The current implementation establishes the provider-neutral contract and deterministic coordinator. It intentionally does not pretend that a test fixture is a real coding agent.

## Planned provider adapters

Adapters can later connect this contract to real workers or services such as coding-model runtimes, GitHub, CI, issue tracking, model registries, and infrastructure providers. Those providers remain replaceable capabilities rather than part of the cognitive core.

## Safety requirements

Agent execution must eventually be bounded by:

- explicit workspace scope
- declared permissions
- resource and timeout limits
- artifact provenance
- reproducible verification
- isolated execution for untrusted work
- human or policy authorization for high-impact operations
- rollback or compensating action where mutation is reversible

No provider may bypass the execution boundary.
