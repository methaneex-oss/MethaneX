# Brain Layer-to-Language Ownership Map

**Status:** Proposed engineering architecture for the Brain foundation; subject to independent architecture review.  
**Date:** 2026-10-31  
**Scope:** The Brain only. This is not a language plan for the complete JARVIS product, its future devices, or its full deployment ecosystem.  
**Repository baseline inspected:** `main` for the current C++ build manifest, architecture and blueprint, TypeScript interface files, and Rust runtime; existing polyglot audit branch for the prior technology audit; governance branch for project scope and authority.

## 1. Governing decision

The Brain is the cognitive foundation of JARVIS. The wider JARVIS system may eventually include multiple hosts, devices, sensors, actuators, applications and external integrations. Those are not implementation targets in this document.

The Brain must remain host- and hardware-independent. It must be able to operate without a network connection or a GPU. It must expose explicit contracts through which future hosts and interfaces can observe and interact with it without becoming its cognitive authority.

> **ENGINEER THE MECHANISMS; LET BEHAVIOR BE ACQUIRED THROUGH EXPERIENCE.**

Language allocation follows responsibility and state ownership, not a desire to use a particular number of languages.

### The authoritative ownership model

- **C++20 owns the authoritative live cognitive state and cognitive-cycle orchestration** in the current architecture.
- **Python/PyTorch owns trainable model implementations and their training/evaluation lifecycle**, only where an experiment demonstrates that learned numerical models add capability. It does not own the Brain's canonical memory, event history, beliefs, goals or decisions.
- **Rust may own narrowly defined safety, isolation, concurrency or protected-host services** when a concrete contract and threat model justify it. The currently inspected Rust cognitive state is not a second authority.
- **TypeScript owns typed interface contracts and the monitoring/operator-facing interface plane.** This plane is needed from the foundation stage, not deferred until the complete JARVIS product exists. It observes Brain activity and submits only explicitly authorized requests; it does not make cognitive decisions.
- **CUDA and Triton are optional acceleration technologies**, not independent cognitive layers and not required to run the Brain.

No component is considered integrated merely because its language or dependency appears in the repository.

## 2. Repository evidence and limits

The current `core/cpp/CMakeLists.txt` defines a C++20 static library, `jarvis_core`, with source files for Brain orchestration, memory, world modelling, causal and associative models, decision, adaptation, attention, threat, resilience, evolution, planning, reasoning, action execution, learning, reflection, knowledge, self-model, representation, perception, goals, intent, strategy, cognitive cycle/runtime/workspace, and capability management.

This confirms that C++ is the current implemented center of gravity. It does **not** prove that every listed mechanism is behaviorally complete or integrated.

The inspected Rust crate (`runtime/rust`) has no declared Cargo dependencies. Its current `BrainRuntime` owns a `CognitiveState`; `cognition.rs` implements a simplified independent belief map and bounded working-memory list. That overlaps with cognitive authority in the C++ Brain and must not be expanded as a parallel belief or memory engine.

The inspected TypeScript files are:

- `interfaces/typescript/src/brain.ts`: primitive values, observations, decision context, capabilities, and a `BrainTransport` with observe/decide/capability methods.
- `interfaces/typescript/src/agent_bridge.ts`: typed agent-bridge messages and transport/session contracts.

These are useful starting contracts, but the inspected `BrainTransport` is not yet a complete Brain observability/monitoring contract. In particular, it does not yet define a sufficient event/activity stream, subsystem health and lifecycle status, cognitive-cycle trace, model/training status, persistence/replay status, or safe operator command/audit model.

The inspected C++ CMake target does not declare a Python/PyTorch integration, CUDA target or Triton kernel build. This is a statement about the inspected build manifest, not a claim that no Python source exists anywhere in every branch.

The existing master blueprint defines Layers 0–19. This document maps those existing layers; it does not reorder them or declare them complete.

## 3. Layer-by-layer language allocation

The language listed as **primary** owns the layer's authoritative implementation. A supporting language may implement a bounded mechanism or interface, but may not silently acquire the primary layer's state authority.

| Blueprint layer | Brain responsibility | Primary language | Supporting language(s) and exact boundary |
|---|---|---|---|
| **0 — Cognitive substrate** | Event model/sequencing, lifecycle, canonical state, synchronization, journaling, integrity, error boundaries, capability registry, observability events | **C++20** | **Rust** only for a separately justified protected service, isolation boundary or concurrency-sensitive component. **TypeScript** defines monitoring/event contracts now. Python is not in the trusted event/state path. |
| **1 — Self-state and self-model** | Current activity, active goals, beliefs/uncertainty, capability availability, resource state, internal health and workload | **C++20** | Python/PyTorch may later provide a learned estimator or anomaly model, but C++ validates and owns accepted self-state. TypeScript reads authorized projections. |
| **2 — Perception and representation** | Normalize experiences into entities, events, concepts, attributes, relations, temporal/spatial structures and uncertainty | **C++20** for canonical schemas, validation and integration | **Python/PyTorch** for trainable feature extraction, embeddings or representation-learning models where experiments justify them. Learned outputs are proposals/features, not direct writes to canonical state. |
| **3 — World model** | Entities, environments, relations, transitions, temporal history, resources and event state | **C++20** | Python/PyTorch may learn predictive or latent dynamics models; C++ owns accepted world-state updates and provenance. |
| **4 — Memory architecture** | Working, episodic, semantic, procedural, associative and autobiographical memory; retrieval, consolidation, supersession, persistence and recovery | **C++20** | Python/PyTorch may support learned retrieval ranking, similarity representations or consolidation experiments. It does not own canonical memory, event ordering, persistence truth or replay. Rust may support a protected storage service only after its contract is specified. |
| **5 — Attention** | Allocate cognitive resources by relevance, urgency, novelty, risk, goals, uncertainty, context and consequences | **C++20** | Python/PyTorch may supply a learned salience/ranking model after a measurable baseline and evaluation exist. C++ retains scheduling, constraints and final attention-state authority. |
| **6 — Knowledge engine** | Acquire/reconcile information; track evidence, provenance, reliability, freshness, uncertainty, contradictions and source dependence | **C++20** | Python/PyTorch may support learned extraction or matching, but evidence validation, provenance, calibration policy and canonical knowledge updates remain in C++. TypeScript may expose status and audit views. |
| **7 — Reasoning engine** | Deductive, inductive, abductive, causal, temporal, spatial, probabilistic, counterfactual, constraint and analogical reasoning | **C++20** as the integrated reasoning and state-transition authority | Python/PyTorch may host bounded learned predictors or proposal mechanisms; they must not be treated as proof engines or silently replace explicit evidence/uncertainty handling. |
| **8 — Goals and motivation** | Stateful goals/subgoals, priorities, dependencies, constraints, deadlines, preferences, conflicts, completion and revision | **C++20** | Python/PyTorch only for experimentally justified learned preference/utility estimation. Goal identity, lifecycle, constraints and revision authority remain in C++. |
| **9 — Planning** | Hierarchical, temporal, resource, parallel, contingency, predictive and dynamic planning | **C++20** | Python/PyTorch may provide learned heuristics or value estimates if they outperform a controlled baseline. C++ owns plan validity, constraints, lifecycle and replanning integration. |
| **10 — Decision engine** | Integrate world state, memory, reasoning, goals, plans, risk, uncertainty, reversibility, cost and consequences | **C++20** | Python/PyTorch may provide bounded learned estimates; C++ owns the decision process and records its evidence and result. TypeScript may request or inspect decisions only through explicit authorization. |
| **11 — Action/execution cognition** | Capability discovery, authorization, preparation, execution, monitoring, verification, cancellation, rollback and post-action evaluation | **C++20** for cognitive intent, authorization policy integration and outcome handling | **Rust** may implement a constrained executor/isolation service where its safety properties are needed. TypeScript may submit authorized requests and display execution status. Device-specific adapters are outside this Brain-only plan. |
| **12 — Learning** | Learn from experience, outcomes, feedback, errors, observations and demonstrations; replay, skill acquisition and continual learning | **C++20** owns learning-cycle orchestration, validated experience lineage, update admission and cognitive-state integration | **Python + PyTorch** is the principal trainable-model stack: training, learned representations, sequence/temporal models, predictors, evaluation, checkpointing and candidate artifacts. C++ decides whether validated outputs are accepted into the live Brain. |
| **13 — Metacognition** | Inspect why conclusions were reached, evidence, assumptions, uncertainty, alternatives, confidence and limitations | **C++20** | Python/PyTorch may provide bounded learned diagnostics only if grounded in actual execution records. TypeScript presents inspectable traces and reports; it must not fabricate explanations or become the source of truth. |
| **14 — Evolution/self-improvement** | Detect limitations, hypothesize, generate candidates, sandbox, compare, adopt/reject, monitor and rollback | **C++20** owns governance, candidate lifecycle, safety gates, adoption and rollback | **Python/PyTorch** may train or evaluate candidate models and algorithms. **Rust** may enforce a constrained sandbox boundary if justified. No candidate self-adopts or bypasses C++ governance. |
| **15 — Self-healing/resilience** | Detect anomaly, diagnose, isolate, preserve state, recover/reconstruct, verify and learn | **C++20** owns cognitive resilience state and recovery orchestration | **Rust** may own narrowly scoped process isolation or memory-safe host services. TypeScript displays health and recovery events. A Rust service cannot independently rewrite Brain beliefs or memory. |
| **16 — Cognitive orchestration** | Coordinate subsystem interactions and feedback loops | **C++20** | Python/PyTorch provides model operations through explicit contracts; Rust provides optional infrastructure services; TypeScript observes and controls only through authorized interfaces. |
| **17 — Continuous cognition** | Event/priority-driven observe–interpret–update–attend–recall–reason–predict–plan–decide–act–evaluate–learn cycles | **C++20** | Python/PyTorch inference/training may be asynchronous and optional. Rust may support isolated services. TypeScript monitoring subscribes to emitted activity and lifecycle events; it must not drive cognition by polling or become a hidden scheduler. |
| **18 — External integration** | Brain-facing contracts for future senses, actuators, tools, files, applications, devices and services | **C++20** owns the Brain-side capability contracts and acceptance semantics | **TypeScript** is appropriate for typed integration/monitoring clients and operator interfaces. **Rust** may implement selected adapters when safety or isolation justifies it. Actual JARVIS product/device integrations are outside this document's implementation scope. |
| **19 — Full-system validation** | Validate normal, edge, invalid, ambiguous, concurrent, failure, recovery, adaptation, regression and long-duration behavior | **No single language owns testing**; tests follow the component under test | C++ tests for core/state/replay; Python tests for learning/data/model lifecycle; Rust tests for safety/isolation services; TypeScript tests for contract and monitoring behavior; cross-language integration and adversarial tests at boundaries. |

### Important interpretation

This table is a responsibility map, not an instruction to create a separate implementation in every language for every layer. Most layers remain C++-owned. Python/PyTorch is introduced only for trainable mechanisms. Rust is conditional. TypeScript is cross-cutting for contracts and monitoring. CUDA/Triton accelerate suitable numerical workloads without owning a cognitive layer.

## 4. TypeScript monitoring and interface plane — required from the foundation stage

The fact that the master blueprint places broad external integration at Layer 18 does **not** mean the Brain should be developed blind until Layer 18.

A narrow Brain observability and operator-interface plane is required now, alongside Layer 0. It is a cross-cutting engineering plane, not a new cognitive layer and not the complete JARVIS interface ecosystem.

### 4.1 What it must let an authorized observer monitor

The contracts should evolve to expose, at minimum:

- Brain process and lifecycle state.
- Current cognitive cycle and activity phase.
- Recent event/activity stream with stable event and correlation identifiers.
- Subsystem status, capability availability and degraded states.
- Memory/journal health, replay progress and integrity status.
- Learning activity: queued/running/completed/failed jobs, dataset and model version identifiers, evaluation results and candidate status.
- Prediction/outcome and learning-cycle trace identifiers where safe to expose.
- Resource and performance measurements needed to diagnose the Brain.
- Error, fault, recovery, rollback and audit events.
- Configuration/version/build identity needed to interpret the observed state.

Expose structured events and snapshots, not just free-form log strings. Preserve event ordering and correlation where the underlying source provides them. Monitoring must not become a second event store or a second cognitive state authority.

### 4.2 Operator actions and authority

Monitoring is not equivalent to unrestricted control. The interface contract must distinguish:

1. **Read-only observation** — default access for status, activity, metrics and traces.
2. **Safe operational requests** — explicitly authorized actions such as pause/resume a non-critical worker, request diagnostics, or ask for a checkpoint, where the Brain defines the operation.
3. **Privileged lifecycle actions** — model adoption/rollback, configuration changes, memory maintenance, recovery and shutdown. These require authorization, validation, audit records and explicit failure semantics.
4. **Cognitive inputs** — observations or experiences submitted through validated Brain ingress contracts. An interface client must not forge internal prediction, learning, calibration, or other Brain-owned events.

No interface may bypass C++ validation, trust policy, authorization, journal sequencing or learning/adoption gates. The interface must report the result actually returned by the Brain; it must not display a requested action as successful before confirmation.

### 4.3 Initial TypeScript contract work

The existing `interfaces/typescript/src/brain.ts` provides a starting `BrainTransport`, but its current `observe`, `decide` and `capabilities` methods are not a sufficient monitoring API. The next interface design should consider distinct typed contracts for:

- `BrainStatusSnapshot`
- `BrainActivityEvent`
- `SubsystemHealth`
- `CognitiveCycleTrace`
- `LearningJobStatus` and `ModelCandidateStatus`
- `PersistenceIntegrityStatus`
- `OperatorCommand`, `OperatorCommandResult` and audit identity/context

These are proposed contract concepts, not claims that these types already exist. The exact schema, transport, authentication, authorization, retention and back-pressure behavior must be designed before implementation. Avoid choosing WebSocket, HTTP, gRPC or another transport merely by habit; compare them against streaming, local operation, deployment, failure isolation and security requirements.

The TypeScript layer is an observer/client and contract definition. It does not own the Brain's event journal, canonical status, model registry or decision state.

## 5. Python/PyTorch integration boundary

Python/PyTorch is the principal new learning technology, but adding it is not the first step in every layer.

The integration contract must establish:

1. C++ emits or exposes validated experiences with context, sequence, provenance and outcome semantics.
2. Training data is derived from real experience, not hand-authored scenario answers.
3. Python/PyTorch trains a bounded model or mechanism and records code/configuration/data/model lineage.
4. Evaluation includes an appropriate baseline, held-out and unseen contexts, leakage controls, contradiction and distribution-shift tests, and continual-learning/forgetting measurements where relevant.
5. A candidate produces a versioned artifact and evaluation report.
6. C++ validates compatibility and controls adoption, activation, monitoring and rollback.
7. The live Brain records which model version influenced a result where required for traceability.
8. A failed or unavailable Python worker cannot corrupt canonical Brain state or prevent CPU-only core operation.

Embedded Python versus a separately managed local process remains undecided. Decide only after measuring latency, fault isolation, concurrency, packaging, restart behavior, model lifecycle and testability. Do not create a network-dependent microservice or require a hosted AI API.

The first PyTorch capability must be selected from an evidenced limitation in the existing Brain. It must complete a vertical slice from experience to training to inference to outcome feedback to measurable later behavioral change.

## 6. Rust boundary and duplicate cognitive authority

The current inspected Rust `CognitiveState` and `Belief` implementation maintains its own belief map and working-memory list. That is a competing simplified cognitive implementation, not a demonstrated safety boundary.

Before Rust is expanded, decide whether to:

- retire the duplicate cognitive behavior while retaining useful crate/runtime scaffolding; or
- refactor the crate so it owns only a precisely defined infrastructure contract and consumes/serves Brain-owned data without making independent belief or memory decisions.

Do not delete or rewrite it without dependency, caller, test and branch analysis. Do not claim Rust currently provides production security, protected key storage, journal integrity or process isolation merely because the crate forbids unsafe code.

A future Rust service must specify its authority, threat model, inputs/outputs, failure semantics, resource limits, authentication boundary, build/deployment requirements and independent tests.

## 7. CUDA and Triton placement

CUDA and Triton do not own layers. They are optional implementation/acceleration tools for numerical workloads inside Python/PyTorch or a justified native component.

Adoption gate:

1. A correct CPU implementation and behavioral baseline exist.
2. Representative training/inference workloads are measured.
3. Profiling identifies a bottleneck that GPU execution can address.
4. End-to-end benchmarks include data transfer and launch overhead.
5. Numerical tolerance, determinism, hardware compatibility and fallback are tested.
6. The Brain remains usable without GPU hardware.

Start with ordinary PyTorch operations. Add custom Triton kernels or CUDA code only when measurements show a material benefit. Do not add both pre-emptively.

## 8. Cross-language contracts and non-negotiable rules

Every cross-language boundary must define:

- Versioned schemas and compatibility policy.
- Authoritative owner for each piece of state.
- Event identity, ordering, correlation and idempotency semantics where applicable.
- Serialization format and validation limits.
- Numeric precision, finite-value and range rules.
- Concurrency, timeout, cancellation and back-pressure behavior.
- Error mapping and degraded-mode behavior.
- Authentication, authorization and audit requirements where privileged.
- Persistence and restart semantics for stateful components.
- Reproducible build/test instructions.
- Contract, integration, malformed-input, fault-injection and regression tests.

Non-negotiable rules:

- No hosted external AI API is required for core cognition or local learning.
- No language gets to maintain a competing authoritative copy of Brain memory, beliefs, goals or decisions.
- No hardcoded stimulus-to-behavior or scenario-to-answer mappings masquerade as learning.
- Interfaces cannot inject Brain-owned internal transitions or bypass trust boundaries.
- Monitoring must not alter cognition merely by observing it.
- Network and GPU availability are optional to the core Brain.
- A technology is not integrated until it changes a real capability or materially improves safety/reliability with evidence.
- No wholesale rewrite or migration is authorized by this map.

## 9. Recommended implementation sequence

1. **Keep the existing C++ Brain and current Priority-One work intact.** This document does not change Priority-One acceptance gates or declare them complete.
2. **Design the TypeScript observability contracts now.** Map actual C++ events/state to read-only snapshots and streams; define authorization/audit boundaries for any commands. Do not build a decorative dashboard ahead of a trustworthy contract.
3. **Complete a repository-level C++ ownership/dependency map.** Confirm which existing classes own canonical state and identify overlap before moving modules or changing languages.
4. **Design the first Python/PyTorch vertical slice.** Select the learning capability from an actual measured gap; define experience schema, model lifecycle, evaluation and adoption before adding runtime dependencies.
5. **Resolve the Rust duplicate-state question.** Keep infrastructure value only where a real responsibility is defined.
6. **Integrate one learned capability end to end.** Prove persistent experience-dependent behavioral change, transfer and regression control.
7. **Profile and consider CUDA/Triton.** Do not make them prerequisites.
8. **Run independent architecture review and adversarial testing** on the actual implementation and cross-language boundaries. Builder self-review and CI do not replace these roles.

## 10. Acceptance criteria for this architecture

This plan is ready to guide implementation only when independent review confirms:

- The language-to-layer mapping does not create duplicate state ownership.
- TypeScript monitoring contracts are sufficient to observe real Brain activity without becoming a cognitive authority.
- The proposed Python/PyTorch path is tied to a real learning capability and has an end-to-end adoption/evaluation boundary.
- Rust has a concrete responsibility or is explicitly deferred.
- CPU-only and offline operation remain viable.
- No language or accelerator is introduced without a measurable capability, reliability, safety or maintainability reason.
- The mapping remains consistent with the existing Brain blueprint and does not expand scope to the complete JARVIS product.

This document is an architectural proposal, not evidence that these integrations have been implemented, tested, or accepted. Independent Reviewer and Tester findings must be recorded before implementation boundaries are treated as settled.

## 11. Inspected repository references

- `core/cpp/CMakeLists.txt` — current C++20 `jarvis_core` source manifest.
- `docs/ARCHITECTURE.md` — cognitive flow and broad language-boundary intent.
- `docs/JARVIS_BRAIN_MASTER_BLUEPRINT.md` — canonical Layer 0–19 construction blueprint.
- `interfaces/typescript/src/brain.ts` — current Brain transport contracts.
- `interfaces/typescript/src/agent_bridge.ts` — current agent bridge contracts.
- `runtime/rust/Cargo.toml` — current Rust crate manifest.
- `runtime/rust/src/lib.rs` and `runtime/rust/src/cognition.rs` — inspected Rust runtime and duplicate cognitive-state implementation.
- `docs/BRAIN_POLYGLOT_FOUNDATION_TECHNOLOGY_AUDIT.md` — prior technology audit and integration risks.

**Disposition:** Proposed Brain-only language ownership map. Documentation only. No cognitive implementation, runtime dependency, language migration, or Priority-One behavior is changed by this document.
