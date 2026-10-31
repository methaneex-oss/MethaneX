# JARVIS Brain — Polyglot Engineering Governance and Implementation Rules

**Status:** Proposed governance baseline; subject to independent review and owner approval.  
**Date:** 2026-10-31  
**Scope:** Brain foundation only. These rules do not authorize implementation of the wider JARVIS product, device ecosystem, deployment platform, or external integrations.  
**Parent architecture:** [Brain Master Construction Blueprint](JARVIS_BRAIN_MASTER_BLUEPRINT.md)  
**Language allocation:** [Brain Layer-to-Language Ownership Map](BRAIN_LAYER_LANGUAGE_OWNERSHIP_MAP.md)

> **ENGINEER THE MECHANISMS; LET BEHAVIOR BE ACQUIRED THROUGH EXPERIENCE.**

This document governs how the already-proposed language allocation is implemented. It does not independently approve every proposed language boundary, settle unresolved transport choices, or authorize a migration. The allocation remains subject to independent review.

---

## 1. Authority, precedence, and scope

### 1.1 Authority order

When requirements conflict, apply this order:

1. Explicit project-owner decisions and the current project constitution.
2. The Brain Master Construction Blueprint and approved Brain architecture decisions.
3. The approved language ownership map.
4. This engineering governance document.
5. Layer-specific design documents and implementation plans.
6. Local code conventions and individual implementation choices.

A lower-level document or code comment cannot silently override a higher-level decision. If a conflict is discovered, record it and request a decision; do not resolve it by quietly changing architecture.

### 1.2 Scope boundary

These rules apply to code, tests, build systems, schemas, interfaces, model artifacts, tools, and documentation that form or support the Brain foundation.

They do not authorize:
- Building the complete JARVIS product interface or device integrations.
- Choosing a deployment/cloud architecture for future hosts.
- Adding a hosted LLM, hosted cognitive engine, or external AI API to the core.
- Replacing the current Brain architecture or migrating languages wholesale.
- Declaring a layer complete because its directory, API, model, or test exists.

### 1.3 The Brain remains one cognitive system

The Brain may contain multiple processes and languages, but it must not become a collection of competing brains. Every authoritative state domain, event stream, lifecycle, and decision boundary must have an explicitly named owner.

A language boundary is an implementation boundary, not permission to duplicate cognition.

---

## 2. Universal engineering principles

Every language and component must comply with these rules.

### 2.1 Mechanisms, not prescribed learned behavior

- Engineer general mechanisms, representations, update rules, constraints, and evaluation procedures.
- Allow behavior, associations, preferences, predictions, and strategies intended to be learned to emerge from evidence and experience.
- Do not encode desired learned conclusions as fixed stimulus-to-response tables, emotion mappings, belief outcomes, success/failure labels, or scenario-specific answers.
- Deterministic rules are appropriate for invariants, validation, authorization, resource limits, safety constraints, protocol semantics, and other explicit system contracts.
- Distinguish an algorithmic learning rule from a hardcoded learning outcome. The former defines how updates occur; the latter predetermines what the system should learn.
- Tests may define expected properties and controlled experimental outcomes. They must not smuggle scenario-specific answers into production behavior.

### 2.2 Evidence before complexity

- Add a component, language, framework, process, or abstraction only to solve a demonstrated requirement.
- State the capability gap, alternatives considered, expected advantage, integration cost, failure modes, and verification plan before adoption.
- Prefer the smallest design that meets the actual requirement without blocking the intended architecture.
- Do not create speculative abstractions, duplicate frameworks, or placeholder subsystems to make the architecture look complete.
- Remove or defer technology that has no active, justified responsibility.

### 2.3 Preserve continuity and state integrity

- Durable experience/event history and canonical state transitions must remain attributable, ordered, and recoverable.
- Never silently discard, reorder, reinterpret, or overwrite authoritative cognitive state.
- Updates must have defined validation, provenance, conflict handling, idempotency, and recovery semantics.
- A restart or component replacement must not create a second source of truth.
- State reconstruction must be testable from the durable records that are declared authoritative.

### 2.4 Explicit contracts

Every cross-component boundary must document:
- Purpose and responsibility.
- Producer and consumer.
- Authoritative state owner.
- Schema and compatibility/version policy.
- Identity, sequence, correlation, and provenance.
- Validation and rejection behavior.
- Ordering, duplication, idempotency, and replay behavior.
- Concurrency, timeout, cancellation, and backpressure behavior.
- Error and degraded-mode behavior.
- Security and authorization requirements.
- Persistence and restart behavior, where applicable.
- Tests proving both normal operation and failure behavior.

No boundary is complete merely because serialization or a function call works.

### 2.5 Observable by design

- Important state transitions, cognitive-cycle phases, model operations, faults, recovery, and operator actions must be observable through structured records.
- Observability must report actual state and evidence; it must not fabricate a narrative of what the Brain supposedly did.
- Logs are diagnostic output, not authoritative event history.
- Monitoring must not mutate cognition or become a hidden scheduler.
- Sensitive data must be minimized, access-controlled, and excluded from routine telemetry unless explicitly required and protected.

### 2.6 Offline and hardware-independent operation

- The core must not require internet access, a hosted service, or a GPU to perform its baseline cognitive responsibilities.
- Optional model workers and accelerators may be unavailable without corrupting canonical state or preventing the core from operating in its declared degraded mode.
- Hardware-specific paths require a tested fallback where the capability is intended to remain generally available.
- Do not assume a particular device, operating system, CPU architecture, filesystem, or network topology without an explicit requirement.

---

## 3. Language selection and ownership rules

### 3.1 Language selection test

Before introducing a language or assigning it a new responsibility, answer all of the following:

1. What exact requirement is not adequately served by the current implementation?
2. Which language characteristics provide a material advantage for that requirement?
3. What are the strongest alternatives, including keeping the current language?
4. What are the total costs: runtime, build, packaging, debugging, security, interoperability, testing, and maintenance?
5. Does the choice create another authoritative state owner or duplicate mechanism?
6. Can the component fail independently and recover without corrupting the Brain?
7. Can the result be tested on the supported baseline hardware and without network access?
8. What measurable evidence would prove the choice was worthwhile?

A small advantage can justify a language choice when it is real and durable. A theoretical advantage, popularity, novelty, or personal preference is not evidence.

### 3.2 One responsibility, one authority

- Every state domain has one canonical writer/authority.
- Other languages may hold validated projections, caches, temporary working data, or candidate outputs only when their role and consistency rules are explicit.
- A projection must identify its source, version/sequence, freshness, and invalidation behavior.
- No two components may independently decide which belief, memory, goal, event, or decision is canonical.
- If ownership is unclear, stop extending the affected components until it is resolved.

### 3.3 No language quotas

The allocation table is not a requirement to use every language in every layer. Most cognitive responsibilities remain C++-owned. Python, Rust, TypeScript, and GPU technologies are used only within their defined boundaries and only when they provide value.

### 3.4 Changing an allocation

Changing a language allocation requires:
- A written problem statement and evidence that the current allocation is inadequate.
- A comparison against the current design and realistic alternatives.
- A migration and compatibility plan, including state and artifact continuity.
- A failure, rollback, and test plan.
- Independent review of architectural impact.
- Explicit project-owner approval before implementation.

No silent language migration, broad rewrite, or new state authority is permitted.

---

## 4. C++20 rules — authoritative cognitive foundation

C++20 is the current primary implementation language for the Brain's canonical cognitive state, core mechanisms, and cognitive orchestration.

### 4.1 Ownership

C++ owns, unless an approved architecture decision explicitly changes it:
- Canonical live cognitive state and accepted state transitions.
- Core event processing, sequencing, and lifecycle.
- Cognitive-cycle and subsystem orchestration.
- Canonical memory/world-state/belief/goal/decision integration.
- Admission of external or learned proposals into authoritative state.
- Learning-cycle governance and integration of accepted updates.
- Candidate adoption, rollback, and cognitive recovery semantics.

This ownership does not imply that every existing C++ subsystem is complete, correct, or properly integrated. Those are verification questions.

### 4.2 Implementation requirements

- Maintain the repository's C++20 language baseline unless an approved decision changes it.
- Use RAII and explicit ownership/lifetime semantics. Avoid unmanaged resource lifetimes.
- Prefer value semantics and clear interfaces; use shared ownership only when shared lifetime is genuinely required.
- Define thread-safety and synchronization contracts for every shared mutable state boundary.
- Avoid hidden global mutable state, implicit cross-subsystem coupling, and unbounded queues or caches.
- Validate all externally supplied, deserialized, and cross-language data before it enters canonical state.
- Handle numeric edge cases, including non-finite values, overflow, underflow, invalid ranges, and precision conversion.
- Make error paths explicit. Do not silently convert failure into success, default cognition, or dropped experience.
- Keep headers and public interfaces narrow; avoid leaking implementation details across layers.
- Do not introduce templates, macros, inheritance hierarchies, or custom frameworks without a concrete need.
- Keep deterministic behavior where the contract requires it; do not confuse determinism with hardcoded cognitive outcomes.

### 4.3 Build and quality

- CMake remains the declared build system for the inspected C++ core.
- Compiler warnings must be addressed or explicitly justified; do not suppress warnings globally to obtain a green build.
- Build configurations and compiler requirements must be documented and reproducible.
- Use sanitizers and static analysis where supported by the project toolchain.
- Test lifecycle, persistence, replay, concurrency, invalid inputs, resource limits, and failure/recovery—not just successful method calls.
- Do not change build manifests to hide unbuilt source, silently exclude failing tests, or weaken verification.

---

## 5. Python and PyTorch rules — bounded trainable mechanisms

Python/PyTorch is the proposed stack for trainable numerical mechanisms when evidence shows that learned models add capability beyond a suitable baseline. It is not a second cognitive runtime.

### 5.1 Permitted responsibilities

Potential responsibilities include:
- Trainable representations and embeddings.
- Learned feature extractors.
- Temporal or sequence models.
- Predictive/world-dynamics models.
- Learned retrieval ranking or salience estimation.
- Bounded value/utility estimates and other learned components where justified.
- Training, evaluation, experiment tracking, checkpointing, and candidate artifact production.

The first capability must be selected from a demonstrated limitation in the Brain, not from the availability of a popular model architecture.

### 5.2 Prohibited authority

Python/PyTorch workers must not independently own or rewrite:
- Canonical event history.
- Authoritative memory or belief state.
- Canonical goals, decisions, or action authorization.
- Cognitive lifecycle or orchestration.
- Candidate adoption or rollback decisions.

A model output is a proposal, estimate, representation, or candidate result. The C++ Brain validates it and decides whether and how it affects authoritative state.

### 5.3 Training data and learning integrity

- Training examples must be derived from traceable experience, observations, outcomes, or explicitly authorized datasets.
- Preserve lineage from source experience to transformed example, training run, checkpoint, evaluation, and candidate.
- Record data provenance, transformations, exclusions, split policy, and relevant configuration.
- Prevent train/test leakage, duplicate contamination, target leakage, and evaluation on memorized examples.
- Include held-out and unseen contexts, distribution shift, contradictory evidence, uncertainty/calibration, and forgetting tests where applicable.
- Compare against a meaningful baseline, including a non-neural baseline where appropriate.
- Do not manufacture labels or hand-author desired answers to make a model appear to learn.
- Do not equate loss reduction, benchmark performance, or checkpoint creation with useful behavioral learning.
- Evaluate whether the trained capability changes later Brain behavior appropriately after adoption.

### 5.4 Runtime and operational boundaries

- Training and inference workloads must be bounded by explicit resource, time, memory, and cancellation limits.
- Worker failure, timeout, malformed output, or unavailability must not corrupt C++ state.
- Model artifacts must be versioned, integrity-checked, reproducible to the extent practical, and associated with their training/evaluation lineage.
- Define model input/output schemas, compatibility, numeric ranges, uncertainty semantics, and version negotiation.
- Keep CPU-capable operation. GPU acceleration is optional.
- Decide embedded Python versus a separate local worker only after a measured comparison of reliability, latency, memory, isolation, packaging, and debugging costs.
- Do not introduce a network-dependent microservice as the default solution.

### 5.5 Dependency and environment control

- Pin and document Python and PyTorch versions and all production-relevant dependencies.
- Separate training-only dependencies from runtime dependencies.
- Use reproducible environments and lockfiles or equivalent dependency capture.
- Do not add large ML dependencies to the C++ core build.
- Document model artifact storage, loading, compatibility, and safe failure behavior.

---

## 6. Rust rules — conditional infrastructure and isolation

Rust may be used for a narrowly scoped infrastructure responsibility when its memory-safety, concurrency, or isolation properties materially improve the system.

### 6.1 Permitted responsibilities

Potential uses include:
- A process-isolated worker or constrained execution service.
- A safety-sensitive host boundary.
- A narrowly scoped concurrent infrastructure service.
- A protected adapter where the threat model and contract justify Rust.

The exact responsibility must be documented before implementation.

### 6.2 Cognitive authority prohibition

- Rust must not grow a parallel cognitive state, belief engine, working memory, world model, or decision authority.
- Existing Rust cognitive-state behavior must be treated as an overlap to resolve, not as proof that a second Brain is needed.
- Before removing or refactoring overlapping Rust code, inspect callers, public APIs, tests, dependencies, and branch state. Do not delete blindly.
- If retained, the Rust component must become an explicit infrastructure service or a validated projection with no independent cognitive authority.

### 6.3 Safety and unsafe code

- Prefer safe Rust.
- Any use of `unsafe` requires a narrowly scoped justification, documented invariants, review, and focused tests.
- The absence of `unsafe` does not by itself prove process isolation, security, integrity, or correctness.
- Define resource limits, permissions, IPC validation, crash behavior, and recovery at the service boundary.
- Do not claim a security property merely because the component is written in Rust.

---

## 7. TypeScript rules — observability and authorized interface plane

TypeScript is a cross-cutting Brain interface and monitoring responsibility required from the foundation stage. This does not authorize building the complete JARVIS user interface or device ecosystem.

### 7.1 Permitted responsibilities

- Typed schemas for Brain status, activity, events, traces, capabilities, and operator requests/results.
- Monitoring and diagnostic clients.
- Operator-facing views for observing Brain activity and health.
- Explicitly authorized requests through documented Brain contracts.
- Contract validation and compatibility handling at the interface boundary.

### 7.2 No cognitive authority

- TypeScript does not own canonical memory, beliefs, goals, world state, decisions, or learning state.
- Monitoring is read-only by default.
- Operator commands must be classified by authority: read-only query, safe operational request, privileged lifecycle operation, or cognitive input.
- Privileged actions require authentication/authorization, validation, audit identity, and explicit policy enforcement in the trusted Brain boundary.
- An interface cannot forge internal events, fabricate outcomes, bypass C++ validation, or directly mutate canonical state.
- UI state and cached snapshots must be visibly distinguishable from authoritative Brain state.

### 7.3 Contract quality

- Use strict TypeScript settings and avoid `any` at trusted boundaries.
- Define runtime validation for untrusted messages; TypeScript types alone do not validate runtime data.
- Version schemas and specify compatibility behavior.
- Define event identity, ordering, correlation, pagination/stream continuation, reconnect, duplicate handling, and stale snapshot behavior.
- Represent errors and degraded status explicitly; do not disguise missing data as healthy/empty state.
- Do not select HTTP, WebSocket, gRPC, or another transport until requirements and trade-offs are compared. Transport remains an architecture decision, not an assumption in this document.

### 7.4 Minimum monitoring coverage

The interface plane should progressively expose:
- Process and lifecycle state.
- Current cycle/activity phase.
- Structured activity/event stream with stable identifiers.
- Subsystem health and capability availability.
- Memory/journal health, replay and integrity status.
- Prediction/outcome traces.
- Learning jobs, datasets, model versions, evaluations, and candidate states.
- Resource/performance metrics.
- Fault, recovery, rollback, and audit events.
- Build/configuration identity.

Expose only data that is safe and useful to operators. Do not leak secrets or unrestricted private experience content through telemetry.

---

## 8. CUDA and Triton rules — optional acceleration

CUDA and Triton do not own cognitive layers or canonical state.

- Start with the simplest correct CPU/PyTorch implementation.
- Profile the real end-to-end workload before writing custom kernels.
- Identify the bottleneck and measure data-transfer, launch, synchronization, memory, compilation, and maintenance costs.
- Adopt an accelerator path only when it produces a material, repeatable end-to-end benefit on representative workloads.
- Preserve a CPU fallback for capabilities expected to operate without a GPU.
- Test numerical equivalence within a declared tolerance, determinism requirements, edge cases, memory pressure, and device loss.
- Do not make GPU availability a condition for Brain correctness or basic operation.
- Do not add CUDA/Triton build complexity for speculative future gains.

---

## 9. Cross-language communication and data contracts

### 9.1 Contract-first integration

No language boundary may be implemented as an informal shared-memory assumption or undocumented ad hoc serialization.

Before integration, specify:
- Contract owner and schema authority.
- Message/event identity and schema version.
- Sequence, correlation, causality, and provenance fields.
- Required versus optional fields and defaults.
- Numeric types, precision, units, valid ranges, and non-finite handling.
- Serialization format and canonical encoding.
- Validation rules and rejection semantics.
- Ordering, replay, duplicate, and idempotency semantics.
- Timeout, cancellation, backpressure, and resource bounds.
- Authentication, authorization, and audit requirements.
- Compatibility, rollout, and rollback strategy.

### 9.2 Data ownership and mutation

- The authoritative owner is the only component allowed to commit canonical state transitions.
- Consumers receive immutable messages or explicitly scoped mutable requests.
- A worker response must identify the request/correlation and the model or component version that produced it.
- Stale, duplicate, malformed, incompatible, or out-of-order messages must have defined handling.
- A failed consumer must not cause the producer to lose durable experience.
- Do not pass raw pointers, language-specific object layouts, or unversioned in-process assumptions across process/language boundaries.

### 9.3 Time and ordering

- Distinguish event occurrence time, ingestion time, processing time, and wall-clock time where relevant.
- Use monotonic clocks for durations and deadlines.
- Do not assume clocks on different processes or hosts are perfectly synchronized.
- Preserve source sequence and causal/correlation identifiers where available.
- Define what happens when events arrive late, duplicated, or out of order.

### 9.4 Process and transport decisions

- In-process calls, local IPC, and network transports have different failure and security properties; do not treat them as interchangeable.
- Choose the simplest transport that meets measured requirements.
- Define process supervision, restart, health checks, protocol compatibility, resource quotas, and shutdown semantics for separate workers.
- Network transport is not required merely because multiple languages are present.
- Local-only and offline operation must remain supported.

---

## 10. Security, trust, and permissions

- Treat all external inputs, files, model outputs, serialized messages, and operator commands as untrusted until validated.
- Apply least privilege to processes, files, devices, and interfaces.
- Separate observation permissions from mutation permissions.
- Authenticate and authorize privileged operations at the trusted boundary, not only in the UI.
- Record privileged actions with actor identity, intent, request/correlation ID, authorization result, and outcome.
- Prevent replay or duplicate execution of non-idempotent commands.
- Define secrets handling; never place credentials, tokens, or private keys in source code, logs, model artifacts, or ordinary telemetry.
- Bound input sizes, queues, execution time, memory, and recursion/depth where relevant.
- Protect persistence and model artifacts against corruption and unauthorized replacement.
- Security controls must be testable. Do not make broad claims such as "sandboxed", "isolated", or "secure" without a threat model and verification.

---

## 11. Persistence, reproducibility, and artifact integrity

- Identify which records are authoritative, derived, cached, or disposable.
- Define schema versioning and migration rules before changing durable formats.
- Preserve provenance and lineage for experience, memory updates, training data, models, and candidate changes.
- Validate integrity before replay, adoption, or recovery.
- Make interrupted writes and partial updates detectable and recoverable.
- Define backup/export/import behavior only where required by the Brain foundation; do not assume a cloud persistence service.
- Record build identity, source revision, compiler/runtime versions, dependency versions, configuration, and model artifact identity for reproducible investigations.
- Never silently replace a known-good model or persistent state with an unverified candidate.

---

## 12. Testing and verification rules

Testing must establish mechanism correctness, integration correctness, and experience-dependent behavioral change. Passing a unit test suite alone does not establish that the Brain learns.

### 12.1 Required test layers

For each component, select applicable tests from:
- Unit and API contract tests.
- Integration and cross-language contract tests.
- Property-based and invariant tests.
- Fuzz and malformed-input tests.
- Concurrency, ordering, and race tests.
- Persistence, replay, restart, and corruption tests.
- Resource exhaustion, timeout, cancellation, and backpressure tests.
- Security and authorization tests.
- Performance and memory profiling.
- Failure injection, recovery, and rollback tests.
- Long-duration and repeated-experience tests.
- Regression tests against previously observed defects.

### 12.2 Learning and adaptation proof

Where a component claims learning, require a traceable causal chain:

`experience → validated representation → update → persisted/retained change → later evaluation → measurable behavioral difference`

Tests must establish:
- The update was caused by the relevant experience and not by a hardcoded scenario branch.
- The change survives the persistence/restart conditions the architecture promises.
- Later behavior changes in the expected direction on relevant held-out or novel cases.
- Contradictory evidence can revise or qualify earlier learning.
- Repeated evidence does not cause uncontrolled confidence inflation or unstable updates.
- Unrelated knowledge and capabilities are not unintentionally damaged.
- The system can identify uncertainty or abstain when evidence is insufficient.
- A failed or rejected update does not contaminate authoritative state.

A stored value, incremented counter, changed parameter, lower training loss, or passing demonstration is not sufficient proof by itself.

### 12.3 Independent verification

- The implementer must run relevant tests and report exact commands, revisions, and results.
- Independent testers should design tests from requirements and failure hypotheses, not merely rerun builder-authored happy paths.
- Reviewers inspect architecture, ownership, correctness, safety, maintainability, and test adequacy; they do not infer correctness from green CI alone.
- Findings must identify evidence, severity, impact, and reproduction path.
- Do not weaken, skip, or delete a test to make a change pass without explicit justification and approval.
- Clearly distinguish tests run locally, CI results, tests not run, and tests blocked by environment.

### 12.4 Completion vocabulary

Use these terms precisely:
- **Implemented:** code exists.
- **Built:** the relevant target compiled successfully.
- **Unit-tested:** relevant isolated tests passed.
- **Integrated:** the component participates through its real contract in the intended system.
- **Verified:** defined acceptance and failure tests passed on a stated revision.
- **Behaviorally demonstrated:** observed experience caused a persistent, measurable change in later behavior under controlled evaluation.
- **Complete:** all documented exit criteria and required independent review/approval are satisfied.

Do not substitute one status for another.

---

## 13. Dependencies, frameworks, and third-party code

Before adding a dependency:
- State the concrete requirement and why the standard library/current dependencies are insufficient.
- Compare maintenance status, license, security history, platform support, binary size, transitive dependencies, performance, and exit cost.
- Determine whether it introduces network, telemetry, model-provider, GPU, or runtime requirements.
- Pin versions and record provenance.
- Define upgrade and vulnerability response procedures.
- Keep dependencies scoped to the component that needs them.
- Avoid duplicate libraries that solve the same problem without a measurable reason.
- Do not vendor large dependencies or copy third-party source without license and maintenance review.
- No dependency may silently become a required external AI service.

---

## 14. Performance, resource, and reliability requirements

- Establish representative workloads before setting numerical performance targets.
- Measure end-to-end latency and throughput, not only isolated function speed.
- Track memory, CPU, GPU, storage, queue depth, and worker overhead where relevant.
- Define resource budgets and overload behavior for every long-running or asynchronous component.
- Prefer bounded queues, explicit cancellation, and backpressure over unbounded accumulation.
- Avoid blocking the core cognitive path on optional training, telemetry, or nonessential integrations.
- Define graceful degradation when optional components are unavailable.
- Optimize only after correctness and profiling identify a real bottleneck.
- Performance improvements must preserve behavior and pass regression tests.

No arbitrary latency, memory, or throughput threshold is imposed here without baseline evidence. Targets must be set per workload and acceptance requirement.

---

## 15. Documentation and change-management requirements

Every nontrivial component or cross-language integration must document:
- Responsibility and explicit non-responsibilities.
- Owning language and canonical state owner.
- Inputs, outputs, schemas, and versioning.
- Dependencies and runtime requirements.
- Concurrency and lifecycle model.
- Failure, recovery, and degraded behavior.
- Security/trust boundary.
- Observability signals.
- Tests and acceptance criteria.
- Known limitations and deferred decisions.

Every architecture-changing pull request must include:
- The requirement and evidence motivating the change.
- Alternatives considered.
- Affected layers, languages, state domains, and contracts.
- Migration/compatibility implications.
- Verification performed and not performed.
- Risks, limitations, and rollback plan.

Keep architecture documents synchronized. If code and documentation disagree, report the discrepancy and resolve it deliberately; do not assume the code automatically represents an approved architecture.

---

## 16. Prohibited engineering patterns

The following are non-negotiable project constraints:

- A second authoritative cognitive state or competing Brain runtime.
- Hardcoded scenario-to-learned-outcome mappings.
- Any external AI API, hosted LLM/inference endpoint, external agent, or cognitive service performing or supplying core Brain reasoning, memory, prediction, planning, decision, or learning.
- A prebuilt external cognitive engine or agent framework used as a substitute for mechanisms owned by this project.
- A new programming language outside the proposed C++20, Python/PyTorch, Rust, TypeScript, and optional CUDA/Triton allocation without explicit project-owner approval and independent architecture review.
- A wholesale rewrite or migration disguised as cleanup.
- Unbounded background workers, queues, caches, or retry loops.
- Interfaces that bypass trusted validation or directly mutate canonical state.
- Model candidates that self-adopt without evaluation and governance.
- Silent schema changes or incompatible artifact replacement.
- Tests weakened or removed to conceal defects.
- Claims of learning, integration, security, resilience, or completion unsupported by evidence.
- GPU, network, or optional worker availability required for baseline Brain operation.
- Duplicate subsystems whose ownership and interaction are not explicitly resolved.

Future external I/O adapters for authorized devices, tools, or data sources are not cognitive engines. They remain outside this Brain-foundation implementation scope and require explicit authorization, bounded contracts, provenance, and trusted validation. They must never become a required external source of cognition.

Low-level general-purpose libraries and infrastructure dependencies are not automatically prohibited, but they require justification and must not silently own a core cognitive responsibility.
---

## 17. Decision records and unresolved choices

The following are intentionally not settled by this document and must be decided from evidence when the relevant implementation is planned:

1. TypeScript transport: local HTTP, WebSocket, gRPC, another transport, or a justified combination.
2. Python execution boundary: embedded runtime versus separate local worker.
3. Canonical event and persistence technology, beyond the requirement that ownership, integrity, replay, and recovery are explicit.
4. Exact cross-language serialization format and schema tooling.
5. Rust's final retained responsibilities after dependency/caller analysis of the current crate.
6. First Python/PyTorch capability, selected from a measured limitation in the existing Brain.
7. GPU/Triton adoption, which requires profiling evidence.
8. Numerical performance and resource targets, which require representative baselines.
9. Platform/ABI support matrix, which must follow actual Brain hosting requirements.

Do not turn these open choices into assumptions through early implementation.

---

## 18. Required approval gates

### Gate A — Architecture and ownership
- Layer responsibility is clear.
- Language and state ownership are explicit.
- No competing cognitive authority is introduced.
- Cross-language contracts are specified.
- Independent architecture review has addressed material findings.

### Gate B — Implementation readiness
- Requirements and acceptance criteria exist.
- Dependencies and runtime costs are justified.
- Failure, security, persistence, and observability plans exist.
- Build and test strategy is reproducible.
- The change remains within the approved Brain scope.

### Gate C — Integration readiness
- Contract and compatibility tests pass.
- Failure and degraded-mode behavior is verified.
- Data ownership, ordering, provenance, and idempotency are verified.
- Monitoring reports actual component state.
- Optional components can fail without corrupting the core.

### Gate D — Behavioral acceptance
- Experience-to-update lineage is demonstrated.
- Persistent change is verified.
- Later behavior is measurably improved on held-out or novel evaluation.
- Contradictions, uncertainty, forgetting/interference, and regression are tested as applicable.
- Independent testing and review findings are resolved or explicitly accepted by the project owner.

Passing an earlier gate does not imply passing a later gate.

---

## 19. Relationship to existing repository architecture

This governance document supplements, and does not replace:
- `docs/JARVIS_BRAIN_MASTER_BLUEPRINT.md` — Brain layers and construction order.
- `docs/ARCHITECTURE.md` — cognitive flow, continuity, learning, evolution, resilience, and language boundaries.
- `docs/BRAIN_LAYER_LANGUAGE_OWNERSHIP_MAP.md` — proposed language responsibilities across Layers 0–19.

The repository currently shows a C++20 CMake core, TypeScript interface contracts, and a Rust runtime with a simplified cognitive-state implementation. The language map proposes a bounded Python/PyTorch role. These are observations and proposals, not proof that all components are integrated or that the allocation has passed independent review.

---

## 20. Review checklist

An independent reviewer should challenge this document against the repository and the Brain blueprint, not merely proofread it.

- [ ] Does the authority order match the project's constitution and owner decisions?
- [ ] Are any responsibilities missing, duplicated, or assigned to the wrong language?
- [ ] Does C++ ownership match actual repository state and intended cognitive architecture?
- [ ] Does the Python/PyTorch boundary prevent a second Brain while still enabling real learning?
- [ ] Are Rust's proposed infrastructure roles concrete, and is existing duplicate cognition handled safely?
- [ ] Is TypeScript monitoring sufficiently capable from the foundation stage without becoming cognitive authority?
- [ ] Are cross-language contracts complete enough to prevent state, ordering, provenance, and failure ambiguity?
- [ ] Are security, persistence, recovery, and offline/CPU operation adequately governed?
- [ ] Are learning acceptance tests capable of distinguishing genuine adaptation from hardcoded behavior or superficial state mutation?
- [ ] Are dependency and performance rules practical rather than arbitrary?
- [ ] Does the document introduce unnecessary restrictions, complexity, or premature decisions?
- [ ] Are any statements inconsistent with the current repository or other architecture documents?
- [ ] What concrete changes are required before this governance baseline can be approved?

**Approval status:** Not approved by this document alone. Independent review and explicit project-owner acceptance are required before treating these rules as binding implementation governance.
