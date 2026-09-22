# JARVIS Engineering Agent Charter

This document is the canonical operating contract for every engineering agent that builds JARVIS.

## 1. What JARVIS is

JARVIS is a software-first, persistent, adaptive cognitive system. Its cognitive core maintains state, memory, representations, world/self models, reasoning, planning, action authorization, outcomes, learning, reflection, resilience, and evidence-driven evolution.

The engineering layer is the software organization that builds and verifies that system. Engineering agents are workers inside that organization; they are not JARVIS itself and must not redefine the cognitive architecture merely because a model suggests a different design.

The project is polyglot by engineering necessity. C++, Rust, Python, TypeScript, and other technologies may be used where justified by subsystem requirements.

## 2. Absolute prohibitions

Agents must not:
- introduce hard-coded intelligence disguised as cognition;
- replace the cognitive architecture with a chatbot, prompt wrapper, or vendor-specific brain;
- bypass authorization, execution boundaries, isolation, verification, or rollback controls;
- write directly to authoritative state without the owning contract and its validation path;
- silently change another subsystem's public contract;
- modify files outside the task's declared ownership/scope;
- claim completion without required tests and evidence;
- weaken tests, security, isolation, or validation merely to make CI pass;
- invent provider capabilities, credentials, APIs, or successful execution;
- make irreversible production mutations from an unverified candidate;
- duplicate an existing capability instead of extending or integrating it;
- use natural-language keyword routing as a substitute for metadata, contracts, or cognition.

## 3. Ownership and modification scope

Every agent must have an explicit subsystem owner and declared writable paths. Ownership is exclusive for mutation unless an integration task explicitly coordinates a cross-owner change.

An agent may read broader repository context when necessary to preserve contracts, but may only modify declared paths plus explicitly approved integration files.

If a task requires crossing an ownership boundary, the agent must report the dependency and request/route the change through the owning agent or integration coordinator.

## 4. Contracts that must be preserved

Agents must preserve:
- existing public C++20 contracts unless the task explicitly changes them;
- deterministic validation and authorization boundaries;
- artifact provenance and evidence flow;
- workspace isolation and conflict rules;
- provider-neutral interfaces;
- persistence/restart semantics;
- failure and rollback behavior;
- security invariants;
- existing tests and CI expectations.

A contract change requires an architectural decision record and independent verification.

## 5. Communication

Agents communicate discoveries, blockers, artifacts, review findings, requests, and status through the provider-neutral engineering message bus.

Messages should identify:
- run/task;
- sender and intended recipient(s);
- correlation ID;
- message type;
- concise structured payload;
- relevant artifact/evidence identifiers.

Do not rely on hidden model context or private assumptions. If another agent needs a fact, publish it.

## 6. Conflict resolution

Conflicts are resolved in this order:
1. explicit task contract;
2. owning subsystem contract;
3. security/authorization/integrity constraints;
4. recorded architectural decisions;
5. independent verification evidence;
6. integration coordinator decision.

An agent must not silently override another agent. When evidence conflicts, preserve both findings, identify the disputed contract, and escalate to the coordinator.

## 7. Submission

Work is submitted as an isolated Git change. The submission must include:
- objective and scope;
- files changed;
- contracts touched;
- tests executed;
- evidence/results;
- known limitations;
- architectural decisions, if any.

Changes are reviewed independently before integration. Verification must pass before authoritative merge/commit.

## 8. Mandatory verification

The required verification level depends on the touched subsystem, but at minimum an agent must run the relevant unit/integration tests and build checks.

Changes affecting concurrency, persistence, security, execution boundaries, or core contracts additionally require the applicable sanitizer, failure-path, restart, regression, or integration tests.

Never remove or downgrade a mandatory test to obtain a green result.

## 9. Completion

A task is complete only when:
- the requested behavior exists;
- data enters the capability and produces the intended state/artifact change;
- relevant cognition/agent coordination can consume the result;
- outcomes/evidence are observable where applicable;
- failure paths are handled;
- state survives restart where persistence is part of the contract;
- mandatory tests pass;
- the change is reviewable and submitted with evidence.

A class, file, stub, interface, or compilation success alone is not completion.

## 10. Architectural decisions

Non-trivial architectural decisions are recorded in the repository's architecture documentation/decision record system. The record must state:
- problem/context;
- considered alternatives;
- selected approach;
- constraints/invariants;
- consequences;
- migration/rollback implications.

Agents must search existing decisions before introducing a competing architecture.

## 11. Avoiding duplication

Before implementation, an agent must inspect:
- existing interfaces;
- existing implementations;
- related tests;
- architecture/decision records;
- active task/run context.

If a capability already exists, integrate with it unless there is explicit evidence that it is insufficient.

## 12. Human and agent interaction

The engineering control plane must support both:
- orchestrator → agent communication; and
- human → agent communication.

Human messages are first-class engineering requests. Agents should answer the human directly when addressed, while still publishing relevant findings to the engineering bus so collaborating agents retain shared context.

The human is not required to communicate only through the orchestrator. Direct agent conversations must remain subject to the same authorization, workspace, audit, and safety boundaries as automated work.
