# JARVIS — System Architecture Foundation

**Document status:** Project Director-approved architectural baseline; current branch revision carries an administrative approval-record update only  
**Documentation reset:** 2026-11-01  
**Scope:** Whole-system anatomy and the governing decision to engineer the Brain first  
**Implementation status:** This document authorizes no implementation, migration, deletion, or merge.
**Approved baseline:** commit `8490737429b052b65fed3b998e0320d8834f640f`; blob `ff0e57f2f9a266466687dca2c4cbcda6a64cb7d7`.  
**Current branch blob:** `e6a544e2968d8b8dc4cce88db9c040804a94534c`. The post-approval difference is limited to approval-status/approval-record documentation; no architectural requirements or system boundaries were changed. The current blob is not represented as having received a separate architectural approval.

> **ENGINEER THE MECHANISMS; LET BEHAVIOR BE ACQUIRED THROUGH EXPERIENCE.**

---

## 1. Purpose

This document establishes the starting point for a fresh architectural documentation effort for JARVIS.

JARVIS is the complete intended intelligent system. It is not defined as only a Brain, chatbot, language model, software agent, device interface, or collection of integrations.

The architecture will take inspiration from the organization and functional relationships of biological systems, while using engineering to improve upon biological limitations. Biology is a source of architectural insight, not a literal implementation specification.

The first major system to be architected in detail and constructed is the **Brain**. This is a deliberate construction order: the Brain is the central cognitive authority on which future JARVIS systems will depend. It does not make the Brain the entire final product.

This document establishes that direction. It does not prematurely settle every subsystem, mechanism, interface, technology, or construction detail. Those require dedicated specifications and review.

## 2. Governing architectural principles

### 2.1 Whole system, Brain first

- The destination is the complete JARVIS system.
- The Brain is the first major system to be fully architected and engineered.
- Future systems must be designed to connect to, serve, extend the capabilities of, or provide information and action pathways for the Brain.
- Future systems must not silently become competing cognitive authorities.
- Brain-first is a construction dependency, not a claim that all other systems are optional or outside the project.

### 2.2 Engineer mechanisms; do not hardcode the intelligence they should produce

The project engineers mechanisms that make cognition, learning, adaptation, and development possible. It must not pre-program the conclusions, beliefs, preferences, associations, emotional reactions, strategies, or behaviours that those mechanisms are intended to acquire.

Examples:

- Build memory mechanisms; do not preload a predetermined lifetime of memories and call that learning.
- Build learning mechanisms; do not encode the desired learned result as a fixed rule.
- Build reasoning mechanisms; do not substitute scenario-specific answer tables for reasoning.
- Build valuation and affect-related mechanisms; do not prescribe a fixed emotional response to every class of event.
- Build world-representation mechanisms; do not make a fixed, exhaustive world database the substitute for understanding and updating.

Deterministic engineering remains appropriate for mathematical operations, data structures, type and schema validation, protocol rules, security, permissions, resource limits, integrity constraints, and other explicit engineering invariants. Such constraints must not be confused with hardcoded cognitive conclusions.

The Brain cannot begin as an unstructured blank system. It requires an engineered bootstrap: initial representations and data structures, learning/update procedures, initialization conditions, operational constraints, and mechanisms that permit experience to be received and processed. These are legitimate when they establish the capacity and conditions for development. They become prohibited hardcoding when they encode specific beliefs, associations, preferences, emotional reactions, strategies, or desired behavioural conclusions that should instead be acquired and revised through experience. Later specifications must state the purpose and developmental implications of each bootstrap assumption, and provide a way to test that it enables learning rather than predetermining its results.

### 2.3 Foundations enable development; they do not contain every future capability

The Brain foundation must provide the structural and mechanistic basis on which more advanced cognitive capabilities can be developed.

It must not become a container for every advanced mechanism merely because that mechanism may eventually be useful to JARVIS.

For every proposed Brain component, later specifications must distinguish:

1. **Foundational mechanism:** required to make the cognitive architecture coherent and extensible.
2. **Advanced mechanism:** a more sophisticated capability that can be developed on top of the foundation.
3. **Acquired capability or behaviour:** something that emerges or improves through experience, learning, and development rather than being prescribed as a fixed outcome.

The foundation must anticipate future extension through sound boundaries and contracts. Anticipating a future system does not mean implementing that system inside the Brain.

For classification purposes, use these operational tests:

- **Foundational mechanism:** a general structural or computational capacity necessary for a coherent, extensible cognitive system, or for the system to develop further capabilities. Its purpose is to enable classes of future processing, not prescribe a particular learned conclusion.
- **Advanced mechanism:** a more sophisticated mechanism that depends on, composes, or extends foundational capacities. It may be deliberately engineered later without being part of the minimum foundation.
- **Acquired capability or behaviour:** a competence, internal model, association, preference, strategy, or behavioural tendency formed or materially improved through experience and learning rather than installed as a predetermined result.
- **Developmental change within a foundation:** foundational mechanisms may themselves have parameters, structures, or operating characteristics that adapt through experience. Calling a mechanism foundational does not imply that every aspect of its state must remain fixed.

Classification is based on architectural role and dependency, not on whether a capability sounds basic or sophisticated. Later specifications must explain ambiguous cases and identify what is engineered initially versus what is expected to develop.

### 2.4 Biological inspiration, engineering freedom

Biological anatomy and physiology provide useful questions and patterns: specialization, integration, feedback, parallel pathways, regulation, adaptation, resilience, and coordination.

JARVIS is not required to reproduce biological organs or neural structures one-for-one. Where engineering offers a better design—such as explicit interfaces, distributed computation, parallel execution, precise observability, fault isolation, reproducibility, or stronger integrity—the architecture should use it.

Every biological analogy must be translated into an explicit engineering responsibility. A name borrowed from biology is not itself an architecture.

### 2.5 One coherent cognitive authority

The Brain owns the authoritative cognitive processes and state assigned to it by the approved architecture. Other systems may sense, transport, transform, store, regulate, or execute information and operations under explicit contracts, but they must not create an ungoverned second Brain.

The exact ownership boundaries and state contracts are not finalized by this document. They must be specified before dependent systems are designed in detail.

Cognitive authority must be distinguished from governance authority. The Brain forms cognitive intent, evaluates options, and makes cognitive decisions. Governance establishes and enforces the rules, permissions, and authorization boundaries under which consequential operations may occur; it is not a second cognitive system and must not independently originate JARVIS's beliefs, goals, or intentions. The Brain cannot authorize itself merely by deciding that an action should occur.

The intended high-level control path is: **cognitive intent and decision → action request → governance authorization → operational validation → execution → outcome verification → feedback to the Brain**. The exact allocation and implementation of these steps remain open, but no step may be silently skipped. Governance policy may be centrally defined while enforcement is distributed across relevant execution boundaries.

### 2.6 Evidence before architectural certainty

Distinguish clearly between:
- a concept, analogy, or hypothesis;
- a proposed architectural decision;
- an approved architectural decision;
- a specified mechanism;
- an implemented mechanism;
- a tested mechanism;
- a demonstrated capability in a defined operating context.

Documentation, source-code presence, a successful build, or a passing narrow test must not be presented as proof of a broader capability.

## 3. Whole-system anatomy — initial conceptual map

The following is a starting taxonomy for investigation and decomposition. It is not yet a final component inventory, dependency graph, or implementation specification. Names and boundaries may change when their responsibilities are analyzed.

### 3.1 Brain — central cognitive system

**Primary responsibility:** maintain and develop JARVIS's coherent cognitive state; interpret experience; construct and revise internal representations; learn; reason; evaluate; and determine cognitive responses.

The Brain is the first system to be architected and built in depth.

Its foundation is expected to require mechanisms for:
- cognitive substrate and coherent internal state;
- experience intake and internal representation;
- memory and continuity;
- learning and adaptation;
- prediction and model revision;
- reasoning and inference;
- attention and cognitive resource allocation;
- goals, valuation, and decision formation;
- cognitive coordination, reflection, and controlled development.

This is a list of areas for architectural investigation, not a decision that every advanced mechanism belongs in the initial foundation. Their exact decomposition, order, ownership, and interfaces remain to be specified.

### 3.2 Nervous system — information and coordination pathways

**Primary responsibility:** provide the engineered pathways through which the Brain and the wider JARVIS system exchange signals, commands, state updates, and feedback.

Biological inspiration suggests investigating distinct responsibilities such as:
- central pathways and internal communication;
- peripheral pathways to external systems and devices;
- incoming or afferent information pathways;
- outgoing or efferent command pathways;
- fast-response and event-notification pathways;
- autonomic or background coordination pathways;
- routing, prioritization, timing, synchronization, and delivery guarantees.

These are functional questions, not finalized software modules. The Nervous System must not interpret information as the Brain does, own the Brain's beliefs, or independently decide JARVIS's goals and intentions. Its precise boundary with runtime infrastructure, interfaces, and the Brain remains to be designed.

### 3.3 Sensory systems — acquisition from the environment

**Primary responsibility:** acquire signals and observations from JARVIS's internal and external environments and make them available through defined pathways.

Potential areas include:
- vision and image acquisition;
- hearing and audio acquisition;
- language and other communication input;
- physical and environmental sensing;
- digital, application, device, and system-state observation.

Sensors and sensory processing must not be conflated with the Brain's interpretation, belief formation, or learning. The boundary between signal acquisition, preprocessing, representation, and cognition requires explicit design.

### 3.4 Motor and action systems — effects on the environment

**Primary responsibility:** provide controlled means through which JARVIS can carry out actions selected and authorized through its cognitive and system-governance pathways.

Potential areas include:
- software and computer operation;
- communication and interaction;
- device and hardware control;
- robotic or other physical actuation;
- action monitoring, result reporting, and feedback.

Action execution is not the same as decision-making. An issued command is not proof of execution, and execution is not proof of the intended consequence.

### 3.5 Autonomic and regulatory systems — internal operation

**Primary responsibility:** maintain the operational conditions required for JARVIS to function reliably without requiring the Brain to supervise every low-level maintenance activity.

Potential responsibilities include:
- resource and workload regulation;
- health and fault monitoring;
- process and service lifecycle management;
- scheduling and background maintenance;
- isolation, recovery, and operational stability.

Operational recovery and security containment are different responsibilities even when both involve isolation or restart. For example, restarting a failed process is operational recovery; isolating a process suspected of compromise is security containment; deciding whether the process or its outputs can be trusted again is a security/governance decision. Their interfaces must be explicit so autonomic recovery cannot undo security containment or independently restore trust.

The distinction between autonomic regulation and cognitive control must be specified. Operational regulation must not silently become an alternative source of goals or cognitive decisions.

### 3.6 Embodiment and infrastructure

**Primary responsibility:** provide the computational, storage, communication, and physical or digital environments in which JARVIS operates.

Potential areas include:
- compute and acceleration resources;
- local and persistent storage;
- operating-system and runtime facilities;
- networks and communication hardware;
- devices, peripherals, and physical platforms;
- connections to external applications and services.

Infrastructure provides resources and interfaces. It is not itself the source of JARVIS's intelligence.

### 3.7 Additional system-level and cross-cutting responsibilities

The six domains above are an initial conceptual map, not an exhaustive list of every responsibility. The whole-system architecture must explicitly account for the following responsibilities and decide whether each is a distinct system, a cross-cutting capability, or a responsibility distributed across existing domains. Their inclusion here does not mandate a separate deployable subsystem.

- **Defence and security:** protect assets, identities, data, execution paths, and trust boundaries; detect and respond to compromise; and govern containment and restoration of trust.
- **Governance, authorization, and safety assurance:** define policy, authority, permissions, operational constraints, auditability, and approval boundaries for consequential actions. Governance is not cognitive goal formation.
- **Interaction and interfaces:** manage user/operator-facing and system-facing interaction surfaces, including presentation, dialogue transport, control surfaces, and feedback. Interface handling must not become an independent cognitive authority.
- **Development, training, and evaluation:** provide controlled environments and processes for developing, training, testing, validating, and evaluating mechanisms. These responsibilities may sit outside the live operational JARVIS boundary and must not silently alter live cognitive state.
- **Global modulation and regulation:** investigate whether system-wide modulation of cognitive operating conditions is a distinct responsibility or belongs within Brain mechanisms and/or autonomic regulation. Do not create an endocrine-inspired subsystem merely to imitate biology or hardcode emotional outputs.

The whole-system responsibility map must define ownership, interfaces, and overlap resolution for these responsibilities. It must also identify additional responsibilities discovered during decomposition.

## 4. Brain-first construction boundary

The first detailed architectural program concerns the Brain foundation.

The initial Brain work must answer:

1. What is the minimum coherent cognitive substrate?
2. What foundational mechanisms are necessary for persistent experience, internal representation, learning, and adaptation?
3. What cognitive state does the Brain own, and how is that state represented and maintained?
4. How do foundational mechanisms interact to form a coherent cognitive process rather than isolated features?
5. How can the Brain learn from experience without having desired behaviours or conclusions hardcoded?
6. How can future advanced mechanisms be added without destabilizing or replacing the foundation?
7. What contracts will future Nervous System, sensory, motor, autonomic, and infrastructure systems use to interact with the Brain?
8. How will claims about learning, capability, and development be independently demonstrated?

The Brain must be testable and capable of developmental work before the complete JARVIS environment exists. At the same time, its architecture must not assume that it will remain permanently isolated from future sensory, action, communication, and embodiment systems.

## 5. Documentation architecture

The documentation will be developed in the following conceptual order. This is an order for architectural understanding and specification, not an implementation schedule.

### A. Whole-system definition
- JARVIS purpose, scope, and system boundaries.
- Whole-system anatomy and responsibilities.
- Relationships and authority boundaries between major systems.
- Biological inspiration translated into engineering requirements.

### B. Brain architecture
- Brain purpose, scope, and cognitive authority.
- Brain foundation versus advanced mechanisms.
- Brain subsystem decomposition.
- Internal state, representation, memory, learning, reasoning, and cognitive-cycle contracts.
- Mechanism interaction and development principles.
- Extension boundaries for future systems.

### C. Other system architectures
- Nervous System.
- Sensory systems.
- Motor and action systems.
- Autonomic and regulatory systems.
- Embodiment and infrastructure.
- External integration boundaries.

### D. Cross-system engineering
- Communication and interface contracts.
- State ownership and information flow.
- Timing, concurrency, synchronization, and failure handling.
- Security, permissions, and trust boundaries.
- Observability and operator oversight.
- End-to-end verification and system-level behaviour.

### E. Technology and construction specifications
Only after responsibilities and contracts are understood:
- language and runtime allocation;
- internal component design;
- dependency and deployment choices;
- construction sequence;
- verification strategy;
- developmental and integration strategy.

Each subordinate document must identify its purpose, scope, assumptions, dependencies, decisions, unresolved questions, and acceptance criteria. It must not silently redefine decisions made by a higher-authority document.

## 6. Treatment of existing documentation and implementation

This is a documentation reset, not an instruction to destroy project history or erase working code.

Existing documents, plans, branches, and implementations are **reference material only** until reviewed against this architecture and explicitly accepted into the new documentation baseline.

Consequently:
- Existing layer numbers, priorities, phase names, technology allocations, and implementation sequences are not automatically carried forward.
- Existing mechanisms and source code are not automatically discarded.
- Existing mechanisms that are technically sound, useful, and compatible with the approved architecture should be preserved and reused where practical.
- Reusable concepts and verified implementation facts may be retained after examination.
- Mechanisms that are partly suitable should be adapted where that is technically preferable to replacement.
- Replacing or discarding an existing mechanism requires a documented technical justification explaining why preservation or adaptation cannot satisfy the approved requirements.
- Contradictory, premature, duplicated, or misleading documentation must be revised, superseded, or clearly marked as historical.
- No existing implementation is authorized to dictate the new architecture merely because it already exists.
- No source-code changes, migrations, deletions, or merges are authorized by this document.

A separate document inventory and disposition review will identify what should be retained, rewritten, superseded, or archived. That review must happen before old documents are treated as governing references.

## 7. Architectural decision discipline

For every major architectural decision, documentation must state:
- the problem and responsibility being addressed;
- the options considered;
- the selected decision and its rationale, if approved;
- alternatives rejected and why;
- implications for other systems;
- assumptions and evidence;
- unresolved risks and questions;
- approval authority and decision status.

Use explicit statuses: **proposed**, **approved**, **rejected**, **superseded**, or **unresolved**. A draft, branch, pull request, or committed document does not by itself constitute architectural approval.

The Project Director retains final authority over project direction and approval of the architecture.

## 8. Document-specific approval gates and sequencing

**Approval record:** Project Director approval: https://github.com/methaneex-oss/MethaneX/pull/171#issuecomment-6556047098. The approval identifies the approved baseline as commit `8490737429b052b65fed3b998e0320d8834f640f` / blob `ff0e57f2f9a266466687dca2c4cbcda6a64cb7d7`. The current branch blob is a later administrative status-record revision, not a newly approved architectural baseline. The approval applies to Document 00's governing direction only. It does not approve Document 01, the Brain research package, a Brain architecture, implementation, or PR merge.

The whole-system responsibility map is a separate architectural deliverable, identified as **JARVIS Whole-System Anatomy and Responsibility Map** (`docs/architecture/01_JARVIS_WHOLE_SYSTEM_ANATOMY_AND_RESPONSIBILITY_MAP.md`). Its presence in the same pull request or documentation branch does not make it part of this document's approval decision.

Approval must be recorded separately for each document:
1. Approval of this foundation document (00) establishes only its governing direction and principles.
2. Approval of the whole-system responsibility map (01) establishes only the system decomposition and responsibility boundaries it explicitly covers.
3. Approval of the Brain foundation architecture is a later, separate decision and must not be inferred from approval of 00 or 01.

No document's approval automatically approves a dependent document, resolves its open questions, or authorizes implementation. Each document must be reviewed against its own scope and acceptance criteria by the independent Reviewer and then explicitly approved by the Project Director.

The responsibility map deepens Section 3 by:
- defining each major system's purpose and boundary;
- decomposing its principal subsystems;
- identifying inputs, outputs, and relationships;
- distinguishing cognitive authority from transport, sensing, execution, regulation, and infrastructure;
- recording open questions without pretending they are settled.

After that, the Brain receives its own detailed foundation architecture. The Brain must not be reduced to the short list in this charter; it must be decomposed and reasoned about carefully before technology or implementation choices are made.

## 9. Acceptance criteria for this foundation document

This document is ready to serve as the starting point for further architectural documentation only when the Project Director confirms that it accurately captures:

- JARVIS as the complete intended system;
- Brain-first construction without Brain-only scope;
- biological inspiration without literal biological imitation;
- foundational mechanisms separated from advanced mechanisms and acquired behaviour;
- no hardcoding of the intelligence that should develop through experience;
- clear separation of cognitive authority from sensing, communication, action, regulation, infrastructure, and governance authorization;
- explicit bootstrap structures that enable learning without pre-programming acquired conclusions;
- preservation and reuse of technically sound existing mechanisms where compatible with the approved architecture;
- a fresh documentation baseline that treats previous plans as reference material pending review;
- no implied authorization to implement or merge.

---

**End of document.**
