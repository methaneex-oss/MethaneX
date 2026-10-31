# JARVIS Brain — Identity, Behavioral Requirements, and Engineering Constitution

**Status:** Proposed foundational specification; not binding until independent review and explicit project-owner approval.  
**Date:** 2026-10-31  
**Scope:** The Brain foundation of the existing JARVIS project.  
**Architecture references:** `docs/JARVIS_BRAIN_MASTER_BLUEPRINT.md`, `docs/BRAIN_LAYER_LANGUAGE_OWNERSHIP_MAP.md`, and `docs/BRAIN_POLYGLOT_ENGINEERING_GOVERNANCE.md`.

> **ENGINEER THE MECHANISMS; LET BEHAVIOR BE ACQUIRED THROUGH EXPERIENCE.**

This document defines what the project is trying to build, what JARVIS is intended to be, what can reasonably be inferred from the Marvel Cinematic Universe portrayal, what the Brain must ultimately be capable of, and the non-negotiable constraints governing its construction.

It is deliberately more fundamental than a language map or coding-standard document. It is intended to prevent the project from becoming a chatbot, a collection of disconnected modules, a fixed behavior engine, or a generic AI-agent framework.

---

# PART I — WHAT WE ARE BUILDING

## 1. The identity of JARVIS

JARVIS is intended to be a persistent, adaptive, context-aware artificial cognitive system: a continuing intelligence that can perceive situations, maintain an evolving model of itself and its environment, understand relationships and consequences, reason, predict, form and pursue goals, make decisions, use authorized capabilities, evaluate outcomes, and improve through experience.

JARVIS is **not** defined by:
- A voice, avatar, user interface, or conversational style.
- A language model or a wrapper around one.
- A collection of commands and predefined responses.
- A database that stores facts but cannot use experience to change future behavior.
- A fixed rules engine that maps recognized situations to hand-authored actions.
- A group of independent agents or subsystems that happen to share a name.
- A specific computer, phone, house, suit, satellite, robot, or other physical host.

Those may become interfaces, resources, or execution environments. They do not define the intelligence.

### 1.1 One continuing cognitive identity

JARVIS must function as one continuing cognitive system, even if its implementation later spans processes, machines, or physical environments.

That requires:
- A coherent identity and self-model.
- Explicit ownership of authoritative state.
- Persistent experience and memory continuity.
- Traceable changes to beliefs, models, goals, and capabilities.
- Consistent authorization and safety constraints.
- The ability to recover after component failure or restart without silently becoming a different system.

Multiple components do not mean multiple competing cognitive authorities. Replicas, caches, workers, models, and interface clients must have explicit roles and consistency boundaries.

### 1.2 The Brain is the present construction target

The current project target is the **Brain**, not the complete JARVIS product.

The Brain must be hardware-independent. It should expose abstract experience-input and capability/action contracts so future environments can provide sensory information and receive authorized actions. It must not be designed around a phone, house, suit, satellite, or one deployment topology.

The future environments are embodiments and resources through which the Brain may perceive and act. Their device-specific implementation is outside the current scope.

### 1.3 The Brain is not the whole organism

A useful distinction:

- **Brain:** cognitive state, mechanisms, learning, reasoning, self-model, goals, decision-making, orchestration, and action/outcome cognition.
- **Embodiment and interfaces:** sensors, actuators, displays, voice, devices, tools, and external capability adapters.
- **Host/runtime infrastructure:** computation, storage, process lifecycle, isolation, and resource management.

These parts must eventually cooperate, but this work is currently about the Brain and its necessary internal observability/contracts. It is not permission to build the entire embodiment or deployment ecosystem now.

---

## 2. The governing construction philosophy

### 2.1 Engineer mechanisms; acquire behavior

The project must engineer the mechanisms that make cognition and development possible. It must not predetermine the detailed behaviors those mechanisms are supposed to learn.

Build:
- General representation and memory mechanisms.
- Evidence-sensitive belief revision.
- Prediction and error comparison.
- Attention and resource allocation.
- Learning and consolidation mechanisms.
- Causal and relational modelling.
- Goal, planning, and decision mechanisms.
- Self-monitoring, evaluation, and adaptation.
- Safety, integrity, and authorization constraints.

Do not hardcode:
- A fixed emotion for a particular stimulus.
- A fixed belief for a particular observation.
- A predetermined preference for a named user or situation.
- A hand-authored response for every recognized scenario.
- A fixed strategy that is claimed to have been learned.
- A success/failure-to-behavior mapping that bypasses evidence.
- A scripted personality masquerading as an acquired one.
- Scenario-specific answers inside a general-purpose reasoning or learning mechanism.

The desired result is a system whose future behavior can differ because its actual experience, evidence, internal state, and learned models have changed.

### 2.2 What may legitimately be engineered in advance

"No hardcoding" must not be misinterpreted as "no rules, no algorithms, and no initial structure."

The following must be engineered explicitly:
- Mathematical algorithms and learning rules.
- Data structures and representations.
- Initial conditions and bounded starting capabilities.
- Validation and type constraints.
- Resource limits and operational invariants.
- Security and authorization policies.
- Safety constraints and emergency boundaries.
- Protocol semantics and state-transition invariants.
- Evaluation procedures and test properties.

These define how the system operates and what it must never violate. They must not secretly encode the conclusions or learned behaviors that the system is supposed to acquire.

### 2.3 Separate hard constraints from learned judgments

Some rules are non-negotiable system constraints: authorization, integrity, privacy, resource bounds, and explicitly defined safety invariants.

Other judgments should be evidence-sensitive and revisable: relevance, preference, expected value, trust estimates, predictions, associations, strategies, and interpretations.

Never disguise a learned judgment as an immutable safety rule. Never allow a learned preference or prediction to override a hard authorization or integrity constraint.

---

# PART II — MCU JARVIS: BEHAVIORAL ANALYSIS

## 3. Scope and method of the fictional reference analysis

The reference here is the **Marvel Cinematic Universe portrayal of J.A.R.V.I.S.**, principally the Iron Man films and The Avengers, with Avengers: Age of Ultron used to establish how Tony describes the system's development.

This is not a claim that the films reveal a real technical architecture. Screenplay dialogue and depicted behavior are evidence of fictional capabilities; the internal mechanisms are usually not specified.

The analysis therefore separates:
1. **Depicted behavior:** what the character demonstrably does in the story.
2. **Reasonable functional inference:** what capabilities would be needed to produce that behavior.
3. **Engineering target:** what this project should build to approximate the capability.
4. **Unknowns:** what the films do not establish and must not be invented as canon.

The MCU depiction is a behavioral reference, not a source-code specification and not a reason to copy impossible cinematic shortcuts.

## 4. How Tony describes JARVIS's beginning and development

In *Avengers: Age of Ultron*, Tony explicitly describes JARVIS as having started as a natural-language user interface and later grown to operate the Iron Legion and a substantial part of Stark Industries' business. This is the clearest in-universe statement about the system's developmental trajectory.

The important architectural implication is not that a natural-language interface automatically becomes intelligence. It is that the fictional system's role expanded from an interaction surface into a broad operational and cognitive-support system.

The films do **not** disclose:
- The original source code or implementation language.
- A complete learning algorithm.
- Whether JARVIS trained neural models, used symbolic mechanisms, or combined approaches.
- How its memory was represented or persisted.
- A formal cognitive architecture.
- Whether its personality was learned, configured, or authored.
- A scientific basis for consciousness or subjective experience.

We must not fill those gaps with invented certainty.

## 5. Observed behavior across the MCU portrayal

### 5.1 Natural-language interaction and contextual communication

JARVIS understands ordinary conversational requests, responds in context, asks or signals when it does not understand, and communicates information without requiring Tony to operate a rigid command menu.

**Functional inference:** language is an interface into a wider internal system. It requires context resolution, intent interpretation, reference tracking, dialogue state, and access to other capabilities.

**Engineering target:** language must not be the Brain itself. It is one means of receiving and expressing information. The Brain must retain context and state independently of the current conversation.

### 5.2 Persistent environmental operation

In *Iron Man*, JARVIS operates Tony's home, controls environmental systems, loads preferences, and enforces access restrictions. It is available across Tony's living and working environments rather than existing only inside a chat session.

**Functional inference:** persistent lifecycle, environmental state, identity/access control, event monitoring, and continuity across interaction contexts.

**Engineering target:** persistent Brain state and event continuity, with future environment adapters. Do not build a house-control product as part of the current Brain scope.

### 5.3 Perception, scanning, and technical interpretation

JARVIS processes detailed scans of Tony and his equipment. It examines the arc-reactor device and identifies that its output is inconsistent with Tony's stated purpose. It then offers a technically grounded interpretation and upgrade assistance.

**Functional inference:** perception is not merely detection. The system must represent observed structures, relate them to prior context and stated intent, identify discrepancies, estimate consequences, and formulate useful conclusions.

**Engineering target:** grounded representations, provenance, uncertainty, domain models, comparison between intention and observed function, and reasoning that can expose contradictions. Do not hardcode the particular arc-reactor conclusion.

### 5.4 Technical reasoning and design collaboration

JARVIS assists with engineering work, calculations, simulations, visualization, design manipulation, diagnostics, and fabrication workflows.

**Functional inference:** it can maintain structured technical context, reason over models, run or interpret simulations, compare candidate designs, and coordinate tools.

**Engineering target:** general structured reasoning, causal and physical modelling where available, simulation interfaces, evidence-backed recommendations, and tool orchestration. Do not claim scientific or engineering competence merely because a model can generate plausible text.

### 5.5 Prediction, monitoring, and warnings

During suit testing, JARVIS monitors power, altitude, vital signs, environmental conditions, system limits, and emerging hazards. It predicts danger, warns Tony, recommends actions, and offers to take control.

**Functional inference:** continuous state estimation, temporal prediction, risk estimation, threshold/invariant monitoring, and a safety-aware action boundary.

**Engineering target:** predict from current and historical evidence, represent uncertainty, monitor outcomes, distinguish advisory recommendations from authorized control, and enforce explicit safety policies. A warning is not proof of a reliable prediction; it must be evaluated against actual outcomes.

### 5.6 Proactive assistance

JARVIS sometimes surfaces relevant information or warnings without Tony issuing a narrowly specified request. It tracks ongoing work, recognizes context, and offers assistance at moments when it is relevant.

**Functional inference:** event-driven attention, context tracking, relevance estimation, interruption management, and bounded initiative.

**Engineering target:** the Brain must be able to notice significant changes, unresolved risks, contradictions, opportunities, or task dependencies and decide whether to alert, ask, recommend, or act within its authority. Proactivity must be grounded in evidence and relevance, not a loop that generates unsolicited messages.

### 5.7 Research, information retrieval, and large-scale computation

In *The Avengers*, Tony describes JARVIS as running a decryption effort against SHIELD systems while Tony is occupied elsewhere. The system also provides research and analysis support.

**Functional inference:** background task execution, asynchronous work, progress tracking, resource management, retrieval, and result reporting.

**Engineering target:** internal task orchestration and bounded background computation. The fictional intrusion is not a permission model: our Brain must never bypass authorization or access controls. Security and lawful authorization override imitation of fictional actions.

### 5.8 Multi-system and multi-agent coordination

By *Age of Ultron*, Tony says JARVIS operates the Iron Legion and a significant part of Stark Industries' business. JARVIS also operates in suit and facility contexts.

**Functional inference:** capability discovery, distributed execution coordination, task scheduling, shared context, status monitoring, and consistent identity across interfaces.

**Engineering target:** a single cognitive authority coordinating external capabilities through explicit contracts. Do not create one independent brain per device, subsystem, or agent.

### 5.9 Social fluency and a recognizable interaction style

JARVIS is formal, dry, tactful, occasionally humorous, and able to adjust communication to Tony's context. In the first *Iron Man*, the dialogue about sarcasm harmonics presents personality as something Tony notices and comments on.

**Functional inference:** social context, conversational memory, interaction calibration, and stable communication characteristics.

**Engineering target:** coherent, context-sensitive communication that can develop from interaction history and explicit constraints. Do not hardcode a list of jokes, sarcasm triggers, or a theatrical butler persona and call that personality or intelligence.

### 5.10 Long-running continuity

JARVIS is not portrayed as forgetting everything between requests. It supports ongoing projects, technical investigations, health monitoring, facilities, and operations over time.

**Functional inference:** persistent memory, task continuity, temporal context, project state, and durable records.

**Engineering target:** experience and knowledge must survive the lifecycle conditions the Brain promises to support. The system must know what it has observed, inferred, attempted, changed, and not yet resolved, with provenance and uncertainty.

### 5.11 Development and expanded responsibility

The *Age of Ultron* description shows a broadening role: from natural-language UI to managing complex operational systems. That is a growth in scope and responsibility, but it does not prove that JARVIS acquired every capability through autonomous learning.

**Engineering target:** capability growth must be governed, measurable, and safe. New capability must be integrated into the existing cognitive system rather than added as an isolated feature with no feedback into memory, reasoning, or future behavior.

## 6. What must not be copied from the films

The films are fiction and compress or omit engineering constraints. Do not copy:
- Unbounded access to private or protected systems.
- Unreviewed autonomous control over dangerous equipment.
- A fictional directive as a substitute for a formal safety architecture.
- Instantaneous analysis, perfect prediction, or impossible computational performance.
- The assumption that a fluent voice proves understanding.
- The assumption that a coherent personality proves consciousness.
- The Vision/Mind Stone transformation as a requirement for JARVIS.
- Ultron's or Vision's capabilities as if they were ordinary JARVIS capabilities.

JARVIS's later transfer into the synthetic being that becomes Vision is a distinct fictional event. Vision is not the implementation target for this Brain. F.R.I.D.A.Y. is a later separate assistant and must not be conflated with JARVIS.

---

# PART III — THE BRAIN WE MUST BUILD

## 7. Target capability definition

When the Brain foundation is mature, it should be able to perform the following classes of work through its internal mechanisms and authorized capability interfaces.

### 7.1 Perceive and represent experience

- Accept structured or unstructured experience through abstract input contracts.
- Preserve source, time, context, sequence, and provenance.
- Extract entities, events, attributes, relations, temporal/spatial structure, and uncertainty.
- Integrate multiple observations without assuming they are all correct.
- Distinguish direct observation, inference, memory, prediction, and externally supplied claims.
- Detect novelty, ambiguity, missing information, and conflicting signals.

### 7.2 Maintain memory and continuity

- Maintain working context for active cognition.
- Store episodic records of events and experiences.
- Build and revise semantic knowledge and relationships.
- Acquire procedural knowledge and strategies through experience.
- Maintain autobiographical/self-history and ongoing task/project context.
- Retrieve by relevance, relationship, time, context, and purpose—not only exact keyword.
- Consolidate, qualify, supersede, or forget information under explicit policies.
- Preserve provenance and distinguish confidence from frequency.
- Recover consistent state after supported restart and replay conditions.

Memory is not one undifferentiated database. The exact memory model must be justified against the existing architecture and validated behaviorally.

### 7.3 Maintain models of the world and itself

The Brain should maintain revisable models of:
- Entities and their properties.
- Relationships and dependencies.
- Environments and changing conditions.
- Processes, actions, and causal relationships.
- Temporal patterns and likely state transitions.
- Its own capabilities, limitations, resources, current activity, and uncertainty.

A model is an approximation supported by evidence, not a perfect copy of reality. It must represent confidence, freshness, contradictions, and gaps.

### 7.4 Predict and simulate consequences

- Generate predictions from current state, context, memory, and learned models.
- Predict likely outcomes and relevant side effects.
- Compare predictions with actual outcomes.
- Measure prediction error and uncertainty.
- Use counterfactual or alternative simulations when they can inform a decision.
- Revise models when evidence shows they are wrong.
- Avoid treating a single prediction as certainty.

### 7.5 Allocate attention and internal resources

- Select what deserves processing now.
- Balance relevance, urgency, novelty, risk, uncertainty, goals, expected value, and available resources.
- Reprioritize when new evidence arrives.
- Interrupt or defer lower-priority work when justified.
- Avoid both missed critical signals and constant low-value interruptions.
- Learn useful attention policies from outcomes without hardcoding scenario-to-priority mappings.

### 7.6 Appraise and regulate internal state

The Brain should have internal state variables that influence processing, persistence, attention, exploration, and decision-making.

These mechanisms may represent urgency, uncertainty, novelty, confidence, workload, risk, progress, conflict, resource pressure, and other justified dimensions.

They must:
- Have defined computational meaning.
- Be updated from evidence and system conditions.
- Interact with attention, memory, prediction, and decisions.
- Be measurable and testable.
- Avoid fixed mappings such as "this stimulus means fear" or "failure always means rejection."

Do not claim the implementation experiences human emotions or subjective feelings. The engineering requirement is a functional internal valuation/regulation mechanism, not a claim about consciousness.

### 7.7 Reason and form explanations

- Combine evidence from multiple sources and memory.
- Distinguish facts, assumptions, hypotheses, inferences, and unknowns.
- Support deductive, inductive, abductive, causal, temporal, spatial, probabilistic, analogical, and counterfactual reasoning where implemented.
- Detect contradictions and revise conclusions.
- Compare alternative explanations.
- Track why a conclusion was reached and what evidence could change it.
- Abstain, ask, or gather more information when the evidence is inadequate.

### 7.8 Form and manage goals

- Represent user-directed and system-authorized goals.
- Track goal state, dependencies, constraints, progress, deadlines, and completion evidence.
- Decompose goals into subgoals where appropriate.
- Identify conflicts and resource constraints.
- Revise plans when circumstances change.
- Preserve the distinction between an inferred opportunity and an authorized goal.
- Do not invent authority from a predicted preference.

### 7.9 Plan and decide

- Generate and compare candidate actions.
- Estimate expected outcomes, cost, risk, reversibility, uncertainty, and resource use.
- Consider dependencies and downstream consequences.
- Select actions consistent with goals and hard constraints.
- Explain material reasons, assumptions, and uncertainty.
- Reconsider a decision when new evidence changes its basis.
- Preserve a record of the decision and its eventual outcome.

### 7.10 Act through capabilities

The Brain must eventually be able to use authorized tools and actuators through explicit capability contracts.

Before an action:
- Validate the request and its source.
- Check capability availability and compatibility.
- Check authorization and applicable safety constraints.
- Assess consequences, reversibility, and required confirmation.
- Record intent and the expected outcome.

During and after an action:
- Monitor execution and time/resource limits.
- Handle failure, cancellation, and partial completion.
- Verify the actual result rather than assuming success.
- Record the consequence and feed it back into cognition.

The Brain's current implementation can define and test these abstract boundaries without implementing phone, house, suit, satellite, or other device adapters.

### 7.11 Learn and change future behavior

Learning must operate across the whole cognitive system, not only as parameter updates in one model.

The Brain must be able to:
- Learn from direct experience, feedback, observation, outcomes, and authorized demonstrations.
- Update representations, associations, beliefs, predictions, strategies, and models as justified.
- Preserve the evidence and lineage that caused an update.
- Generalize beyond the exact training instance.
- Revise prior learning when contradictory evidence arrives.
- Detect uncertainty, overconfidence, interference, and forgetting.
- Retain useful learning across supported restarts.
- Demonstrate that learning changes later behavior on held-out or novel situations.

The required causal proof is:

`experience → representation/context → evidence evaluation → update → retained state/model change → later prediction/decision/action → measured outcome`

A changed database row, increased counter, modified model weight, lower training loss, or scripted demonstration does not by itself prove learning.

### 7.12 Reflect and improve its own mechanisms

- Monitor the quality and reliability of its own processes.
- Identify repeated prediction errors, reasoning failures, memory retrieval failures, and capability limitations.
- Form evidence-backed hypotheses about possible improvements.
- Test candidate changes in isolation.
- Compare candidates against a baseline and regression suite.
- Adopt only through explicit validation and governance.
- Monitor the result and roll back harmful changes.

Self-improvement must not mean unrestricted self-modification or self-authorization.

---

## 8. How the Brain should function

### 8.1 A recurrent, event-driven cognitive system

The Brain must not be implemented as a simplistic fixed pipeline that executes every subsystem in the same order for every input.

A useful conceptual loop is:

`experience → representation and context → memory/belief/world-state update → prediction → appraisal and attention → reasoning and goal evaluation → planning/decision → authorized action → consequence observation → learning and consolidation`

This is a description of interacting responsibilities, not a hardcoded universal sequence.

Actual cognition must be able to:
- Start from external experience or an internal event.
- Revisit earlier processing when new evidence changes interpretation.
- Run independent bounded processes concurrently where appropriate.
- Interrupt lower-priority work for urgent events.
- Ask for missing information.
- Delay action when confidence or authorization is insufficient.
- Continue long-running tasks without requiring a user message every cycle.
- Reconcile outcomes and update future processing.

The orchestration mechanism may be engineered. The specific route through cognition must depend on context, state, and task.

### 8.2 Cognition is not the same as conversation

Conversation is one input/output mode. The Brain must continue to maintain state, monitor relevant processes, evaluate predictions, and progress authorized work even when no conversation is active.

Conversely, continuous operation must not mean constant activity. The system must allocate resources according to relevance, urgency, and available capacity.

### 8.3 Internal and external events

The Brain must distinguish:
- External observations.
- User communications and instructions.
- Tool/action results.
- Internal predictions and hypotheses.
- Memory retrievals.
- Learning and consolidation events.
- Faults, lifecycle events, and resource conditions.

Each event type needs provenance and authority semantics. An internally generated hypothesis must never be mistaken for a directly observed fact.

### 8.4 Uncertainty is a first-class state

The Brain must not be forced to invent certainty.

It must represent:
- Confidence and its meaning.
- Evidence quantity and quality.
- Source reliability and dependence.
- Freshness and context.
- Contradictory evidence.
- Missing information.
- Calibration and observed prediction accuracy.

Confidence must not simply increase because the same unverified claim is repeated or because a subsystem has executed successfully.

### 8.5 Personality and communication

A recognizable JARVIS interaction style is desirable, but it is not the Brain's foundation.

Communication should be shaped by:
- Current context and task.
- Interaction history.
- Social and operational constraints.
- User preferences when actually learned or explicitly supplied.
- The importance, urgency, and uncertainty of the information.

Do not encode a butler persona, canned sarcasm, or a fixed set of conversational behaviors as a substitute for cognition. Style must never distort evidence, conceal uncertainty, or override safety.

---

# PART IV — NON-NEGOTIABLE PROJECT RULES

## 9. No hardcoded cognition or learned outcomes

This is a governing prohibition.

Do not hardcode:
- Scenario-to-answer mappings.
- Stimulus-to-emotion mappings.
- Failure-to-trauma or success-to-reward mappings as fixed outcomes.
- User-specific beliefs or preferences that are supposed to be learned.
- Fixed associations, strategies, priorities, or conclusions presented as acquired knowledge.
- Special-case branches that make a benchmark scenario pass without a general mechanism.
- Fake memory updates that do not affect later cognition.
- Fake learning loops that only increment values or store labels.
- Pre-scripted "intelligent" demonstrations that bypass the real cognitive cycle.

Every exception must be identified as an explicit invariant, safety rule, bootstrap primitive, test fixture, or deterministic protocol rule—not disguised as learned behavior.

## 10. No external AI APIs or outsourced cognition

The Brain's cognitive capabilities must be built and owned inside this project.

**Prohibited as a required or hidden cognitive dependency:**
- Hosted LLM APIs.
- External AI inference APIs.
- External agent or reasoning services.
- Hosted memory, planning, prediction, or decision engines.
- Third-party cognitive runtimes that perform the Brain's core reasoning or learning on its behalf.
- A network service that the Brain must contact to understand, remember, reason, decide, or learn.
- A chatbot/LLM wrapper presented as the Brain.

The Brain must not outsource its core thinking to an external provider and merely relay the result.

Use the approved language allocation to implement the mechanisms internally:
- C++20 for authoritative cognition and orchestration.
- Python/PyTorch for bounded trainable mechanisms and their training/evaluation lifecycle.
- Rust only for justified infrastructure, isolation, or safety boundaries.
- TypeScript for monitoring and authorized interface contracts.
- CUDA/Triton only when profiling demonstrates a real acceleration benefit.

Do not introduce another language merely because a library or example uses it. The current allocation is the approved planning set; any addition requires explicit project-owner approval and architectural review.

### 10.1 External I/O is not external cognition

Future JARVIS embodiments may need to communicate with authorized devices, tools, data sources, or services. That is an external I/O capability, not permission to outsource cognition.

Any such integration must:
- Be explicitly authorized and within the project's scope at that time.
- Use a bounded adapter with a documented contract.
- Treat returned data as untrusted input.
- Preserve provenance and permissions.
- Remain replaceable and non-authoritative.
- Never become a required reasoning or learning service.

This Brain-first phase must not drift into building those external integrations.

## 11. Build the required mechanisms; do not import a finished Brain

- Do not adopt a prebuilt agent framework, hosted model, or packaged cognitive engine as the Brain.
- Do not use an external model as the hidden source of reasoning while C++ merely routes requests.
- Do not import a fixed personality, decision policy, memory engine, or behavior catalogue and claim the Brain acquired it.
- Build the project's cognitive mechanisms and their integration deliberately.
- Ordinary low-level libraries, compilers, runtimes, math/serialization primitives, and development tools are not automatically forbidden; each dependency must be justified, scoped, reviewed, and must not own cognition.
- A dependency that performs a core cognitive responsibility is not a harmless utility dependency and requires explicit project-owner approval.

"Build it ourselves" means we own the architecture, mechanisms, state, learning, evaluation, and behavior. It does not require rewriting every commodity data structure, compiler, operating-system facility, or mathematical primitive without evidence of benefit.

## 12. No architecture drift or speculative expansion

- Continue the existing JARVIS project; do not restart or replace it with a generic design.
- Preserve the approved Brain blueprint and existing architecture unless evidence requires a change.
- Do not add a new subsystem merely because the MCU character appears to have a capability.
- First determine which existing mechanism should support that capability and whether a genuine gap exists.
- Do not duplicate existing responsibilities under new names.
- Do not expand the project into device integrations, product UI, deployment, hosting, or unrelated infrastructure during Brain construction.
- Do not declare a layer complete because files exist or tests compile.
- Do not treat code volume, language count, or subsystem count as progress.

## 13. One authoritative owner for every cognitive state domain

For every state domain, document:
- The canonical owner.
- The permitted readers and writers.
- The update and validation rules.
- Persistence and replay semantics.
- Conflict resolution.
- Provenance and version/sequence.
- Recovery behavior.

No competing C++, Rust, Python, or TypeScript cognitive state may independently decide the canonical truth.

Workers and models may produce proposals, predictions, features, rankings, or candidate updates. The authoritative Brain validates and governs their acceptance.

## 14. No fake integration

A subsystem is not integrated because:
- It can be instantiated.
- It has an API.
- A unit test passes.
- It writes a value into another component.
- A demo manually calls the next function.
- A log message claims that a cycle completed.

Integration must be demonstrated through real contracts, actual data flow, correct ownership, failure handling, and a measurable contribution to the cognitive loop.

## 15. No fake learning

A learning claim requires:
- Experience-derived input with provenance.
- A defined update mechanism.
- Evidence that the experience caused the update.
- Retention under the promised persistence conditions.
- A later behavior change.
- Evaluation on held-out or novel cases.
- Checks for contradictory evidence, overfitting, interference, and regression.

Learning is a property of the interacting Brain, not a checkbox belonging to one file.

## 16. No unbounded autonomy

The Brain should develop initiative and the ability to progress authorized tasks, but autonomy must be bounded by explicit authority.

At minimum distinguish:
- Observe and analyze.
- Recommend or ask.
- Prepare an action.
- Execute a reversible, pre-authorized action.
- Execute a consequential or irreversible action only with the required authorization.
- Emergency behavior governed by explicit safety invariants.

A learned preference, inferred intent, or confident prediction is not authorization. The interface must not be able to bypass the trusted action boundary.

## 17. Safety, privacy, and security are foundational

- Validate all external and cross-language input.
- Apply least privilege.
- Protect private experience, credentials, and durable state.
- Separate read-only monitoring from mutation and privileged operations.
- Make high-impact actions auditable and appropriately authorized.
- Bound resource use and execution.
- Detect faults and preserve recoverable state.
- Never use fictional JARVIS's unauthorized system access as a design precedent.
- Do not claim safety, security, or isolation without a threat model and tests.

## 18. Observability is required now

The Brain must not be a black box during construction.

The foundation-stage monitoring plane must expose truthful, structured information about:
- Lifecycle and subsystem health.
- Current cognitive activity and phase.
- Event and experience flow.
- Memory and persistence health.
- Belief/model updates and provenance.
- Prediction and outcome traces.
- Learning runs, evaluations, and candidate status.
- Resource use and performance.
- Faults, recovery, and rollback.
- Build, configuration, and model identity.

Monitoring must not own cognitive state, fabricate internal events, or drive the cognitive cycle.

---

# PART V — DEVELOPMENT AND ACCEPTANCE

## 19. Developmental construction model

The Brain is being built as a developing cognitive foundation, not as a finished fictional superintelligence and not as a chatbot with features added one at a time.

The developmental analogy is useful only at the level of staged capability acquisition:
- Establish a reliable substrate and basic mechanisms.
- Provide bounded initial capacities and valid inputs/outputs.
- Allow mechanisms to interact.
- Supply controlled experience and feedback.
- Measure whether the system retains and generalizes what it learns.
- Expand capabilities only when earlier mechanisms support them.

The analogy does not imply that a software Brain is biologically equivalent to a human infant, that human developmental stages map directly to software layers, or that consciousness will emerge automatically.

## 20. What "working Brain" means

A working Brain is not a collection of compiled subsystems. At minimum, it must demonstrate an integrated cycle in which:

1. It receives an experience with source and context.
2. It constructs a usable representation.
3. It relates the experience to current memory and beliefs.
4. It identifies uncertainty or contradiction.
5. It forms a prediction or expectation where appropriate.
6. It allocates attention and selects relevant processing.
7. It reasons about the situation and possible consequences.
8. It forms or updates a goal/plan when authorized.
9. It makes a decision within constraints.
10. It executes or requests an authorized capability when appropriate.
11. It observes the actual consequence.
12. It compares outcome with expectation.
13. It updates the relevant mechanisms and persistent state.
14. A later experience demonstrates a measurable change attributable to that learning.

Not every event must invoke every stage. The Brain must select an appropriate path based on context and urgency. The complete chain is an acceptance scenario proving that the mechanisms cooperate.

## 21. Behavioral acceptance properties

The mature Brain must be evaluated for properties such as:

- **Continuity:** retains relevant context and state across time and supported restarts.
- **Grounding:** distinguishes observation from inference, memory, and hypothesis.
- **Context sensitivity:** interprets the same input differently when relevant context differs.
- **Consistency:** detects and manages contradictions instead of silently holding incompatible conclusions as certain.
- **Prediction:** makes measurable predictions and learns from their errors.
- **Adaptation:** improves future behavior from experience without scenario-specific hardcoding.
- **Generalization:** applies learned structure to unfamiliar but related cases.
- **Revision:** changes prior beliefs when stronger or contradictory evidence warrants it.
- **Calibration:** confidence corresponds to observed reliability.
- **Initiative:** notices relevant events and advances authorized work without constant prompting.
- **Restraint:** asks, abstains, or waits when evidence, capability, or authority is insufficient.
- **Planning:** considers dependencies, resources, uncertainty, and consequences.
- **Action integrity:** verifies what actually happened rather than assuming a command succeeded.
- **Recovery:** handles faults and restarts without corrupting continuity.
- **Self-monitoring:** can report its own status and limitations using evidence.
- **Development:** improves through repeated experience while preserving previously useful capabilities.

These are behavioral properties to test, not promises that every property is already implemented.

## 22. Evaluation must challenge the Brain

Tests must include:
- Novel and ambiguous inputs.
- Contradictory observations.
- Repeated but unreliable claims.
- Delayed and out-of-order evidence.
- Missing context.
- Misleading correlations.
- Failed predictions.
- Changed environmental conditions.
- Similar tasks with different relevant context.
- Long-running tasks and interruption.
- Restart and replay.
- Partial action failure.
- Unauthorized and malicious inputs.
- Resource pressure and unavailable optional workers.
- Repeated experience and delayed evaluation.
- Regression against prior capabilities.

A builder-authored happy-path suite is not sufficient. Independent testers must devise their own adversarial tests from the requirements and likely failure modes.

## 23. Completion and truthfulness

Use precise status terms:
- **Designed:** responsibility and contract are specified.
- **Implemented:** code exists.
- **Built:** the relevant target compiled.
- **Tested:** named tests ran on a stated revision.
- **Integrated:** real data flows through the intended contract.
- **Verified:** defined acceptance and failure tests passed.
- **Behaviorally demonstrated:** experience caused persistent, measurable change in later behavior.
- **Approved:** independent findings have been reviewed and the project owner accepts the decision.
- **Complete:** all documented exit criteria are met.

Never claim the Brain is intelligent, learning, integrated, safe, or complete solely from source-code presence, logs, unit-test counts, or a short demonstration.

## 24. What this project does not claim

This project does not claim:
- Human-equivalent intelligence.
- Consciousness, sentience, subjective experience, or human emotions.
- Perfect understanding or infallible reasoning.
- Unlimited autonomy or unrestricted access.
- That cinematic capabilities can be reproduced without engineering limits.
- That every MCU behavior has a known technical implementation.
- That the current Brain already meets the target specification.

The project makes engineering claims only when supported by implementation evidence and repeatable evaluation.

---

# PART VI — ARCHITECTURAL MAPPING AND GOVERNANCE

## 25. Relationship to the existing 20-layer Brain blueprint

This specification does not replace, reorder, or rename the existing Layers 0–19.

It defines the intended identity and behavior those layers must collectively support. The layer blueprint remains the structural construction map. The language ownership map allocates implementation responsibility. The polyglot engineering governance document defines language and integration rules.

Before implementation planning is finalized, each behavioral requirement in this specification must be mapped to:
- The existing layer or layers responsible.
- The existing mechanism(s) expected to implement it.
- The authoritative state owner.
- Required interfaces and dependencies.
- Required tests and behavioral evidence.
- Current repository implementation status.
- Gaps, overlaps, and unresolved decisions.

Do not create new layers or duplicate modules just to make the mapping appear complete. If the existing blueprint cannot represent a necessary responsibility, document the exact mismatch for review before changing it.

## 26. Language boundaries

The current proposed language allocation remains:
- **C++20:** authoritative cognitive state, core mechanisms, and orchestration.
- **Python/PyTorch:** bounded trainable mechanisms and training/evaluation lifecycle; no second Brain.
- **Rust:** narrowly justified infrastructure, safety, or isolation; no duplicate cognition.
- **TypeScript:** monitoring and authorized interface contracts; no cognitive authority.
- **CUDA/Triton:** optional acceleration only after measured benefit.

No new language is authorized by this document. No language is required in a layer merely to satisfy a quota.

## 27. Required documentation set

The complete Brain engineering documentation should ultimately contain, with no contradictions:

1. **Identity and behavioral constitution** — this document.
2. **Master construction blueprint** — the existing Layers 0–19 and construction order.
3. **Layer-to-language ownership map** — primary/supporting language boundaries.
4. **Polyglot engineering governance** — coding, integration, data, security, persistence, testing, dependencies, performance, and approval rules.
5. **Cognitive mechanism specifications** — responsibilities, state, algorithms, inputs/outputs, interactions, and invariants per mechanism.
6. **State and data ownership catalogue** — canonical owners, persistence, provenance, schemas, and lifecycle.
7. **Interface and observability specification** — monitoring, event traces, operator authority, and safe commands.
8. **Learning and evaluation specification** — experience lineage, training, adoption, behavioral tests, and regression.
9. **Safety and trust model** — threat model, permissions, action classes, and recovery.
10. **Implementation and verification plan** — sequence, acceptance gates, dependencies, and evidence.

These documents should be cross-linked and governed as one coherent specification. Do not write ten disconnected documents that disagree.

## 28. Approval and change control

This document is a proposed foundation, not an automatically approved rewrite of the project.

Before it becomes binding:
- Independently review the MCU behavioral interpretation and identify overreach.
- Review every non-negotiable rule for clarity and unintended consequences.
- Reconcile it with the project constitution, current Brain blueprint, and language map.
- Map the requirements against the real repository and identify missing, duplicated, or misleading architecture.
- Record reviewer findings and their disposition.
- Obtain explicit project-owner approval.

Any future change to the Brain's identity, non-negotiable rules, state authority, language ownership, or scope requires a written rationale, impact analysis, independent review, and project-owner approval.

---

# SOURCE BASIS AND INTERPRETIVE LIMITS

The following sources support the MCU behavioral observations. Screenplay/transcript sources are used to locate depicted behavior; they are not technical documentation for a real AI architecture.

- [Iron Man (2008) screenplay](https://assets.scriptslug.com/live/pdf/scripts/iron-man-2008.pdf) — house operation, technical scanning and analysis, conversational behavior, fabrication assistance, suit monitoring, and safety warnings.
- [The Avengers (2012) screenplay](https://imsdb.com/scripts/Avengers,-The-(2012).html) — background information-processing work described by Tony.
- [Avengers: Age of Ultron screenplay transcript](https://github.com/taubergm/marvel_movie_analysis/blob/master/avengers_ultron_script.txt) — Tony's explicit description of JARVIS's progression from natural-language UI to Iron Legion and business operations.
- [Iron Man 3 screenplay transcript](https://www.springfieldspringfield.co.uk/movie_script.php?movie=iron-man-3) — calibration requests, safety briefings, monitoring of Tony's extended activity, and autonomous suit-test context.
- [Chelsea Atkins Skelley, *Interfaces and Interfacings: Posthuman Ecologies, Bodies and Identities* (2016)](https://libres.uncg.edu/ir/uncg/f/Skelley_uncg_0154D_11922.pdf) — scholarly analysis of the cinematic human/interface relationship and the embodied, gestural interface sequences in *Iron Man 2*. This is an interpretive academic source, not MCU canon.

**Interpretive rule:** where a film does not specify an internal mechanism, this document labels the mechanism as an engineering inference or target rather than attributing it to Marvel canon.

**Approval status:** Proposed. Independent review and explicit project-owner approval are required.
