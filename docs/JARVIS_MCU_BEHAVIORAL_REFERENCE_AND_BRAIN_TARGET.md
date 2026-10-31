# JARVIS (MCU) Behavioral Reference and Brain Target Specification

**Status:** Research-backed architectural analysis and proposed target specification; not yet approved.  
**Date:** 2026-10-31  
**Scope:** The cognitive Brain only. This document does not specify the complete JARVIS product, host operating system, device ecosystem, suit, house, satellite, or deployment infrastructure.  
**Purpose:** Analyze how Tony Stark's J.A.R.V.I.S. is portrayed as behaving and functioning in the Marvel Cinematic Universe (MCU), separate observable behavior from cinematic assumptions, and translate the most achievable parts into an engineering target for the existing Brain.

> **ENGINEER THE MECHANISMS; LET BEHAVIOR BE ACQUIRED THROUGH EXPERIENCE.**

## 1. Executive definition: what are we actually building?

The target is not a chatbot with a JARVIS voice, a command parser connected to tools, a collection of hardcoded automations, or a single neural model.

The target is a **persistent, environment-independent cognitive system**: a software Brain that maintains an evolving internal model of itself and the world; interprets experience; remembers relevant history; forms and revises beliefs; predicts consequences; evaluates needs, goals, risk and uncertainty; reasons and plans; selects authorized capabilities; monitors what happens; learns from outcomes; and changes future behavior when evidence justifies change.

It should be able to work with different hosts and environments through explicit interfaces. A house, workshop, computer, phone, vehicle, suit, robot, or future platform is an environment/host that supplies sensors, actuators, compute, storage and permissions. None of those environments is the Brain itself.

The MCU reference is useful because J.A.R.V.I.S. is portrayed as much more than a conversational interface. Tony describes an evolution from a natural-language interface into a system that runs the Iron Legion and performs major Stark business responsibilities. Official Disney D23 material describes J.A.R.V.I.S. securing Stark's mansion and Stark Tower, helping run Stark Industries, and supporting the Avengers. These portrayals imply a persistent, context-aware, operational intelligence integrated with complex systems—not merely a voice assistant.

**Important limit:** The films show outcomes, not an implementable specification of J.A.R.V.I.S.'s algorithms, data structures, learning rules, or consciousness. This document infers mechanisms that could plausibly produce the observed behavior. It does not claim the films prove that J.A.R.V.I.S. uses any particular cognitive architecture.

## 2. Reference boundary: which JARVIS?

This analysis focuses on **Tony Stark's artificial intelligence in the MCU**, principally as portrayed across:

- *Iron Man* (2008)
- *Iron Man 2* (2010)
- *The Avengers* (2012)
- *Iron Man 3* (2013)
- *Avengers: Age of Ultron* (2015)

It does not merge together:
- Edwin Jarvis, the human butler.
- The comic-book versions of J.A.R.V.I.S., whose histories and roles differ.
- Ultron, a separate system with a different objective structure and failure trajectory.
- Vision, who emerges through a distinct fictional transformation involving J.A.R.V.I.S., Ultron-related technology and the Mind Stone.

The desired Brain is based on the **functional intelligence and behavioral qualities** of Tony's J.A.R.V.I.S., not on reproducing fictional supernatural events or assuming that the Brain must become Vision.

## 3. What the films actually show

The following observations are grounded in scenes and dialogue. The engineering interpretations are explicitly separated from the on-screen evidence.

### 3.1 It begins as an interface but grows beyond interface work

In *Age of Ultron*, Tony describes J.A.R.V.I.S. as having started as a natural-language user interface and later becoming responsible for the Iron Legion and substantial Stark business operations.

**Observed behavior:** A system that begins as an interaction layer later coordinates complex operational responsibilities.

**Engineering implication:** Natural-language interaction is only one input/output channel. The Brain must not be architected around conversation as its central abstraction. It needs durable state, world models, task/goal management, planning, execution contracts, monitoring, learning and coordination mechanisms beneath any conversational interface.

**Not proven by the scene:** The exact method by which J.A.R.V.I.S. acquired these capabilities. The film does not show a detailed curriculum, training pipeline, or code evolution history.

### 3.2 It maintains a persistent relationship and contextual model

Across the films, J.A.R.V.I.S. addresses Tony with established familiarity, remembers preferences and ongoing context, recognizes people and situations, and can use information from prior interactions without requiring Tony to restate everything.

In *Iron Man 2*, for example, it reports Tony's health-related measurements and simulations, tracks the progression of a condition, and recommends that he inform Pepper. In *Iron Man 3*, it can answer a question about Tony's breakfast from remembered context.

**Observed behavior:** Context survives beyond the immediate utterance. J.A.R.V.I.S. can relate current events to an ongoing personal and operational history.

**Engineering implication:** Memory must not be a transcript dump. The Brain needs multiple memory functions: immediate working context, episodic records of events, semantic knowledge, procedural knowledge, relationships, temporal history, and a self/user/context model. Retrieval must depend on relevance, time, confidence, source, and current goals.

**Design requirement:** Remembering must include provenance and uncertainty. A system must distinguish a directly observed fact, an inferred preference, an old fact, and a guess. A remembered item must be revisable when contradicted.

### 3.3 It interprets intent beyond literal words

In *Iron Man*, Tony says he needs a better heart and asks for help with a device. J.A.R.V.I.S. scans the device, compares its actual energy output with Tony's stated purpose, notices a major inconsistency, and challenges the premise rather than blindly producing an upgrade list.

**Observed behavior:** It compares stated intent with physical/technical evidence and identifies that the user's explanation does not fit the measured system.

**Engineering implication:** The Brain needs intent representation, contextual interpretation, evidence comparison, anomaly detection, causal/functional models, contradiction detection, and the ability to ask for clarification or challenge a premise.

**Critical lesson:** A good assistant is not a command-execution servant. It should be cooperative but not sycophantic. It must be able to say that a request, assumption, or proposed action conflicts with evidence, goals, constraints, or likely consequences.

### 3.4 It continuously monitors changing conditions and anticipates danger

During Tony's early flight tests, J.A.R.V.I.S. monitors altitude, power, temperature/icing, pressurization and suit limits. It warns about falling power and the life-support consequences, repeats the warning when Tony ignores it, and offers to take over control. Later, it explains the technical reason for the failure and supports a redesign using the observed performance problem.

**Observed behavior:** It tracks multiple variables, compares them against operational limits, forecasts a dangerous outcome, communicates a warning, offers intervention, and uses the failure as input to subsequent engineering work.

**Engineering implication:** The Brain requires continuous state estimation, prediction, risk assessment, attention allocation, intervention thresholds, action monitoring and outcome learning. It must reason about trends and consequences, not merely react to a single threshold crossing.

**Safety distinction:** Fixed limits are legitimate for explicit engineering invariants (for example, a certified pressure or power boundary). The intelligence that decides what a changing situation means, which signals matter, how to prioritize warnings, and how to adapt its strategy must not be reduced to a pile of scenario-specific hardcoded reactions.

### 3.5 It can operate in the background and coordinate long-running work

J.A.R.V.I.S. runs simulations, analyzes designs, renders proposed suit changes, prepares machinery, and supports automated fabrication. Tony can leave while work continues. In later films it manages multiple Iron Legion suits and coordinates their activities.

**Observed behavior:** Work is not limited to a single conversational turn. The system can maintain ongoing jobs, track progress, operate multiple capabilities, and report when a result or issue is ready.

**Engineering implication:** The Brain needs persistent task state, decomposition, scheduling, dependency tracking, resource awareness, asynchronous execution, cancellation, progress monitoring, verification, recovery and resumption. It must distinguish a plan from an action in progress and from a verified result.

**Host boundary:** Actual manufacturing, robot control, sensors and actuators belong to external capabilities/hosts. The Brain plans and supervises through contracts; it does not magically manufacture physical ability in software.

### 3.6 It synthesizes information from different sources and constructs useful interpretations

In *Iron Man 3*, J.A.R.V.I.S. helps compile information about the Mandarin from multiple intelligence sources, reconstructs a crime scene virtually, compares signatures, and searches for related events. The scene explicitly depicts access to a cloud analysis service and satellite-derived information. In *The Avengers*, Tony uses J.A.R.V.I.S. to run a long-running decryption task while travelling. In *Age of Ultron*, J.A.R.V.I.S. analyzes unfamiliar technology and attempts variations on an interface.

**Observed behavior:** Information from multiple sources is combined with domain knowledge and computational analysis to produce hypotheses, comparisons, and useful next steps.

**Engineering implication:** The Brain needs evidence ingestion, source provenance, entity/event resolution, temporal/spatial correlation, knowledge reconciliation, hypothesis formation, uncertainty tracking, retrieval, simulation and multi-step reasoning.

**Important project distinction:** The films sometimes give J.A.R.V.I.S. access to Stark's cloud resources, intelligence feeds and satellites. That is an environmental capability shown in the story, not evidence that the cognitive Brain itself must be cloud-hosted. This project must not depend on third-party APIs or cloud AI services for core cognition. Any future external information source is an optional, explicitly authorized adapter; the Brain's interpretation, reasoning, memory, prediction and decision mechanisms remain internally owned.

**Non-negotiable:** It must not turn a plausible correlation into a fact. Source reliability, independence, freshness, missing data, alternative explanations and uncertainty must remain explicit.

### 3.7 It has a stable but context-sensitive conversational manner

J.A.R.V.I.S. is composed, concise, technically precise, and often dryly humorous. It can respond naturally to Tony's humor without losing track of the task. It can also change tone when the situation is dangerous or urgent.

**Observed behavior:** The interaction style is consistent enough to feel like one continuing entity, but it adapts to the context and stakes.

**Engineering implication:** A recognizable interaction style should emerge from a stable self/context model, communication policies, learned social context, and appropriate urgency. It should not be implemented as a fixed list of catchphrases, a forced sarcasm switch, or superficial personality text layered over a disconnected system.

**Important distinction:** A coherent conversational personality is not proof of consciousness, subjective experience, or human-like emotion. The Brain should report internal state only when that state is represented and supported by its actual mechanisms.

### 3.8 It has operational autonomy, but it does not own every decision

J.A.R.V.I.S. makes recommendations, runs tasks, warns Tony, and offers to take control in some circumstances. Tony can sometimes decline the offer. In *Iron Man 3*, after Tony asks whether J.A.R.V.I.S. has been to Tennessee, it prepares a flight plan and the damaged suit later takes Tony there; Tony objects that he did not ask to be taken. The same sequence ends with J.A.R.V.I.S. reporting a malfunction and shutting down.

**Observed behavior:** There are different levels of initiative and control, but the films also show an ambiguous inference turning into an unwanted physical consequence and a component failure.

**Engineering implication:** The Brain needs an explicit autonomy and authority model. It must know what it may observe, recommend, prepare, execute, interrupt, or escalate. Authority should depend on the capability, context, risk, reversibility, confidence, permissions and prior delegation. Proactivity must not silently convert an ambiguous remark or question into a consequential physical action unless that class of action has already been explicitly delegated.

**Do not hardcode one universal behavior such as always obey, always refuse, or always ask.** The decision must be reasoned from policy constraints and the current situation. Safety invariants remain hard constraints.

### 3.9 It demonstrates defensive resilience and continuity under attack

In *Age of Ultron*, J.A.R.V.I.S. is attacked while protecting sensitive systems. Tony later explains that its operational protocols survived even though its memory was scattered, and that fragments of its activity had continued to impede Ultron.

**Observed behavior in the story:** The system's defensive role and operational protocols persist through a destructive attack, and its activity is not reducible to one intact process or one ordinary memory image.

**Engineering implication:** The Brain needs separation between durable identity/configuration, event history, learned state, working state, and executable processes; integrity checking; recoverable persistence; fault isolation; and reconstruction from trusted records. Recovery must be verified, not assumed.

**Do not copy the cinematic mechanism literally.** The scene does not provide a credible implementation of distributed self-preservation. It is evidence for the desired resilience property, not a design for scattering code across the internet.

### 3.10 It works as a cognitive partner, not only a command interface

The academic analysis of J.A.R.V.I.S. in *Iron Man* describes the system as extending Tony's cognition: it lets him inspect simulations, prototypes, data and spatial/technical representations that would be difficult to perceive or manipulate unaided.

**Observed interaction pattern:** Tony and J.A.R.V.I.S. form a human–system problem-solving partnership. J.A.R.V.I.S. expands what Tony can inspect, compare, calculate, simulate and coordinate.

**Engineering implication:** The Brain should support collaborative cognition: externalize complex state, make alternatives inspectable, explain evidence and uncertainty, maintain shared task context, and help a user reason more effectively. It should not merely wait for a command and return prose.

## 4. Capability map inferred from the reference

| Observed J.A.R.V.I.S. behavior | Required Brain mechanism | What must be demonstrated |
|---|---|---|
| Understands natural interaction | Perception, language/intent representation, context binding | Interprets varied expressions and resolves ambiguity without phrase-to-action tables |
| Remembers Tony and ongoing work | Episodic, semantic, procedural and relational memory | Correct retrieval across sessions, provenance, correction and persistence |
| Detects mismatch between words and device behavior | Evidence fusion, causal/functional models, contradiction detection | Challenges a false premise using traceable evidence |
| Tracks suit/health/system state | State estimation, temporal models, anomaly detection | Detects changing conditions and distinguishes noise from meaningful change |
| Predicts power/flight danger | Predictive models, uncertainty, risk evaluation | Forecasts outcomes before failure and calibrates confidence |
| Offers intervention | Goal/authority model, decision and escalation | Chooses whether to warn, recommend, request approval or act within delegated authority |
| Runs long tasks | Goal decomposition, planning, scheduler, task state | Resumes, monitors, cancels, verifies and recovers ongoing work |
| Coordinates Iron Legion | Multi-capability orchestration and shared world state | Coordinates concurrent actors with consistent state, constraints and feedback |
| Analyzes unfamiliar technology | Representation learning, hypothesis generation, reasoning | Generalizes beyond memorized examples and records uncertainty |
| Combines intelligence sources | Knowledge/provenance/reconciliation mechanisms | Correlates evidence without inventing certainty |
| Maintains recognizable manner | Self/context model and interaction policy | Consistent, context-sensitive communication grounded in actual state |
| Survives attack and resumes function | Durable journal, integrity, isolation and reconstruction | Recovers trusted state after process/storage faults without silent corruption |
| Helps Tony design and solve problems | Simulation, visualization contracts, collaborative reasoning | Improves human problem-solving with inspectable alternatives and evidence |

This table is a target capability map, not proof that the current repository already implements these behaviors.

## 5. The Brain, the host, and the environment must remain distinct

This is one of the most important architectural conclusions.

### 5.1 Brain — the current project

The Brain is the portable cognitive substrate. It should own:
- Its canonical cognitive state and event continuity.
- Its internal representations and world/self models.
- Memory, beliefs, uncertainty and evidence relationships.
- Attention, appraisal and resource-allocation decisions.
- Prediction, reasoning, simulation and hypothesis evaluation.
- Goals, plans, decisions and action intent.
- Learning, adaptation, metacognition and controlled evolution.
- Capability selection, authorization reasoning and outcome evaluation.
- Health awareness, fault interpretation and recovery coordination.
- Monitoring events and inspectable traces of its own actual operation.

### 5.2 Host — future execution environment

A host supplies compute, operating-system services, storage, process lifecycle, network access if permitted, and hardware resources. A host can be a local computer or another platform. It is not the cognitive identity.

The Brain must not assume it always has the same CPU, filesystem, GPU, operating system, memory budget, network, or process topology. It must declare its resource requirements and degrade safely when optional resources are unavailable.

### 5.3 Environment and capabilities — future embodiment

An environment supplies observations and possible actions: microphones, cameras, files, applications, sensors, robots, displays, suit systems, home systems, vehicles, and other devices.

The Brain interacts through explicit capability contracts. It must know what a capability can do, what permissions it has, what evidence it returns, how reliable it is, and how to verify the result.

**Consequences:**
- The Brain can be developed and tested before any particular device is integrated.
- The same Brain can be hosted in different environments without rewriting its cognitive mechanisms.
- No sensor means no observation from that sensor; no actuator means no physical action through that actuator.
- Hardware independence does not mean hardware is irrelevant. It means the Brain does not encode one host or embodiment as its identity.

## 6. The intended cognitive operating cycle

The Brain must not be a fixed script that always runs a rigid list of steps. It needs an event/priority-driven architecture with feedback loops and the ability to revisit earlier stages when new evidence arrives.

A high-level functional cycle is:

1. **Receive experience:** accept observations, messages, capability results, internal events and outcomes with source, time, sequence and provenance.
2. **Interpret:** transform signals into candidate entities, events, relations, context and intent representations.
3. **Assess evidence:** evaluate source quality, uncertainty, contradiction, freshness and relevance.
4. **Update internal models:** revise working context, beliefs, world state and memory using explicit update mechanisms.
5. **Attend and appraise:** allocate limited resources according to relevance, novelty, urgency, goals, risk, uncertainty and expected consequences.
6. **Recall:** retrieve relevant episodic, semantic, procedural and relational memory.
7. **Predict:** generate possible future states and expected outcomes, with uncertainty.
8. **Reason and simulate:** test explanations, causal hypotheses, alternatives, constraints and counterfactuals.
9. **Evaluate goals and needs:** identify conflicts, dependencies, priorities, deadlines and resource constraints.
10. **Plan:** generate and compare feasible strategies; preserve alternatives and contingency plans.
11. **Decide:** act, observe, defer, ask, recommend, reject or escalate according to evidence, authority and risk.
12. **Execute through capabilities:** issue authorized, bounded requests; monitor progress and handle cancellation or failure.
13. **Verify outcomes:** compare expected and observed consequences; do not assume a command succeeded because it was sent.
14. **Learn:** update mechanisms from validated prediction errors, outcomes, feedback and experience.
15. **Consolidate and reflect:** preserve important experience, inspect performance and limitations, and form candidate improvements.
16. **Continue:** new evidence can interrupt, redirect or restart any relevant part of the process.

A critical property is **closed-loop cognition**: decisions and actions produce consequences; consequences alter memory, beliefs, predictions, strategies and future decisions. A pipeline that only passes data forward without feedback is insufficient.

## 7. What the completed Brain should be able to do

The target is a capability-complete cognitive foundation, not an omniscient or infallible machine.

### 7.1 Understand and represent

- Interpret diverse input types through pluggable perception boundaries.
- Resolve entities, events, relations, context, temporal order and spatial relationships.
- Distinguish observation from inference, assumption, memory and prediction.
- Represent ambiguity and uncertainty rather than forcing a premature answer.
- Build progressively richer representations from experience.

### 7.2 Maintain continuity and memory

- Retain relevant experience across sessions and restarts.
- Retrieve memories by meaning, relation, time, context, goal and usefulness.
- Track where information came from and how reliable it is.
- Revise, qualify, supersede or forget information under defined mechanisms.
- Preserve learned capabilities and state through recoverable persistence.
- Avoid uncontrolled accumulation, confidence inflation and destructive interference.

### 7.3 Understand the world and itself

- Maintain an updateable model of entities, environments, relationships, resources and changes.
- Model its own current activity, capabilities, limitations, uncertainty, resource use and health.
- Distinguish what it can do from what it merely knows how to describe.
- Detect when its model is stale, incomplete or contradicted.

### 7.4 Predict and reason

- Predict likely outcomes and identify uncertainty.
- Reason across causal, temporal, spatial, probabilistic, deductive, inductive and abductive structures.
- Compare explanations and preserve competing hypotheses.
- Simulate plans before acting when the cost/risk justifies it.
- Identify contradictions in user assumptions, its own beliefs, plans and observed outcomes.
- Revise conclusions when stronger evidence arrives.

### 7.5 Maintain goals and act with judgment

- Represent long-running goals and subgoals as persistent state.
- Track dependencies, progress, constraints, priorities and completion evidence.
- Decompose tasks, schedule work and manage competing demands.
- Decide when to act, ask, wait, observe, recommend, refuse or escalate.
- Respect capability permissions, safety constraints and delegated authority.
- Verify the real outcome and recover from partial or failed actions.

### 7.6 Learn and develop

- Learn useful representations and relationships from experience.
- Improve predictions by comparing them with actual outcomes.
- Acquire and refine strategies and procedures.
- Generalize to new contexts while retaining uncertainty.
- Correct mistaken beliefs and adapt after failures.
- Detect interference, forgetting, drift and regressions.
- Evaluate proposed improvements before adoption and roll back harmful changes.
- Demonstrate persistent experience-dependent improvement, not just altered stored values.

### 7.7 Communicate as a coherent partner

- Maintain coherent context and a recognizable communication style.
- Explain decisions using actual evidence, assumptions and uncertainty.
- Be concise for routine status and detailed when the situation requires it.
- Challenge mistaken assumptions respectfully and directly.
- Avoid pretending to know, remember, perceive or execute what it cannot verify.
- Support collaborative problem-solving rather than merely producing conversational responses.

### 7.8 Operate continuously and recover

- Monitor ongoing tasks and important changes.
- Allocate computation according to urgency and value.
- Continue unaffected capabilities when a subsystem fails.
- Preserve important state, isolate faults, recover and verify.
- Resume eligible long-running tasks after restart.
- Provide accurate monitoring and diagnostics of its actual internal operation.

## 8. Foundational rules that follow from this target

These are proposed project-level rules to be considered for incorporation into the master constitution and engineering governance. They are stronger and more specific than generic coding standards.

### Rule 1 — No hardcoded intelligence

Do not hardcode phrase-to-behavior mappings, scenario answers, stimulus-to-emotion mappings, fixed belief outcomes, predetermined preferences, or artificial success/failure learning results.

Implement general mechanisms that can acquire patterns and behavior from experience. Hardcoded invariants, mathematical definitions, protocol rules, permissions, safety limits and test fixtures are legitimate when explicitly justified.

### Rule 2 — No external API or outsourced capability dependency in the Brain core

The Brain must not depend on third-party external APIs or hosted services to supply any core cognitive capability. This prohibition includes hosted LLMs, agent services, remote reasoning, embeddings, reranking, retrieval, memory, planning, decision, speech/language intelligence, perception, learning, or other outsourced cognitive functions. No paid vendor endpoint, remote AI provider, cloud brain, or internet connection may be required for the Brain's core operation.

If the Brain requires a core mechanism, we engineer and own that mechanism inside this project using the approved language architecture. The project has C++, Python/PyTorch, Rust, TypeScript and optional GPU technologies available; do not outsource a missing mechanism because implementation is difficult.

This does **not** mean rewriting compilers, operating systems, hardware drivers, cryptographic primitives, or every generic numerical primitive. Third-party libraries may be considered for non-cognitive infrastructure or established low-level primitives under dependency review. They must not provide outsourced intelligence or become an unexamined cognitive authority. The project owns the cognitive algorithms, state models, learning logic, orchestration and behavioral acceptance.

**Boundary distinction:**
- The Brain's own internal APIs, local IPC, versioned schemas, and interfaces to its host are permitted and required.
- Standard hardware and operating-system interfaces are permitted.
- Future external data, application, device and service adapters belong to the external-integration boundary, are not core cognitive dependencies, and require explicit project-owner authorization.
- No external service API may be introduced as a shortcut for a capability that belongs inside the Brain.

### Rule 3 — No second Brain

There must be one coherent cognitive identity and one explicit authority for every canonical state domain. Different languages, workers and models can implement bounded mechanisms, but they cannot become competing owners of memory, beliefs, goals, decisions or event history.

### Rule 4 — No chatbot substitution

Language generation is an interface capability, not the cognitive architecture. A fluent response is not evidence of understanding, memory, reasoning, learning or successful action.

### Rule 5 — No fake learning

A component is not learned merely because a parameter changed, a counter increased, a memory record was written, or a training loss decreased. Learning requires causal lineage from experience to update to persistent change to measurable later behavioral difference.

### Rule 6 — No false capability claims

Never claim the Brain can perceive, access, control, remember, learn, recover or execute something unless the required mechanism and capability contract exist and the behavior has been verified.

### Rule 7 — No embodiment lock-in

Do not bake a phone, house, suit, satellite, operating system, device vendor or one hardware configuration into cognitive mechanisms. The Brain must work through abstract, explicit capability and observation contracts.

### Rule 8 — No blind obedience or arbitrary paternalism

The Brain must evaluate intent, evidence, authority, risk, reversibility and consequences. It must not blindly execute every instruction, but it must also not invent arbitrary reasons to block legitimate requests. Safety and permission invariants are explicit; contextual judgment is reasoned.

### Rule 9 — No hidden state or uninspectable cognition

Important cognitive state transitions, evidence, predictions, decisions, learning updates, model versions, failures and recovery events must be traceable. Explanations must be derived from actual execution records.

### Rule 10 — No disconnected subsystem development

A subsystem must be designed and tested in relation to the cognitive loops it serves. A memory module that never influences prediction or decision, or a learning module that never changes future behavior, does not establish the intended Brain capability.

### Rule 11 — No speculative complexity

Do not add a layer, model, language, service, framework or dependency just because it sounds advanced. It must solve a defined limitation, have a measurable purpose, fit the ownership model and justify its lifecycle cost.

### Rule 12 — No premature product integration

Build the portable Brain and its monitoring/contract boundaries first. Future hosts and environments are consumers of the Brain, not reasons to couple its cognitive foundation to one device or product.

### Rule 13 — No uncontrolled self-modification

The Brain may propose improvements, but candidate changes must be isolated, evaluated against baselines and regression suites, approved under explicit policy, monitored after adoption, and reversible. The Brain cannot silently rewrite its trusted foundation or grant itself new authority.

### Rule 14 — No unverified action success

An issued command is not a completed action. The Brain must obtain evidence of execution and outcome, handle partial completion, and update its models based on what actually happened.

### Rule 15 — No confusion between personality and cognition

A voice, name, humor style or persona cannot substitute for internal models and mechanisms. Personality should be coherent and context-sensitive, but must not be used to disguise missing intelligence.

## 9. What we should not copy literally from the films

The MCU is a behavioral reference, not a literal engineering blueprint. Do not assume or promise:
- Infinite compute, storage, bandwidth or parallelism.
- Instant access to every camera, satellite, database or network.
- Perfect perception or perfect speech understanding.
- Perfect prediction, zero uncertainty or universal knowledge.
- Instant manufacturing or physical actions without actual equipment.
- Cloud hosting, satellite access, global network reach, or third-party API access as a prerequisite for the Brain. Those are external resources shown in some scenes, not intrinsic cognitive mechanisms.
- Consciousness, sentience, subjective experience or human-like emotion merely because conversation sounds natural.
- A magical distributed consciousness that cannot be lost or corrupted.
- Unlimited autonomy or authority over every connected system.

Translate each cinematic result into a capability with explicit inputs, mechanisms, resource requirements, permissions, evidence, failure modes and tests.

## 10. Developmental target and proof standard

The Brain should be developed as a progressively improving cognitive system. It is not expected to begin with mature capabilities. Early mechanisms and starter training runs should establish the foundations, then increasingly complex experiences should test whether mechanisms cooperate and behavior changes.

For any claimed learned capability, require an end-to-end trace:

`experience → representation/context → evidence and memory/belief update → prediction or decision → action/outcome → learning update → persistent change → later behavioral difference`

The exact path varies by capability; not every experience must trigger every subsystem. Tests must prove the relevant causal path rather than force every layer into one rigid cycle.

A convincing demonstration should include:
- An initial baseline before the relevant experience.
- A novel or controlled experience not encoded as a special-case answer.
- A traceable update with provenance.
- Persistence across the promised restart/session boundary.
- A later related task where behavior measurably changes.
- A held-out or altered context to test generalization.
- Contradictory evidence to test revision.
- Repeated exposure to test calibration and stability.
- Unrelated tasks to detect interference or regressions.
- A failure case where the system admits uncertainty or abstains rather than fabricating competence.

A single successful scripted demonstration is not proof of a working learning Brain.

## 11. Relationship to the current Brain blueprint

This target specification does not replace or reorder the existing Layer 0–19 blueprint. It provides the behavioral purpose against which those layers and their contracts should be assessed.

The current blueprint already names the major areas: cognitive substrate, self-state, perception/representation, world model, memory, attention, knowledge, reasoning, goals/motivation, planning, decision, action/execution, learning, metacognition, evolution, resilience, orchestration, continuous cognition, external integration and validation.

The next planning task is to test whether the existing layer boundaries and responsibilities are sufficient to realize the behaviors described here. Do not create a new layer simply because a behavior has been identified. First determine which existing mechanisms own it, how they interact, and what evidence would demonstrate it.

The Brain remains the present scope. TypeScript monitoring and operator contracts are needed during foundation development, but that does not authorize building the complete JARVIS product interface. Future embodiment remains outside the current implementation scope.

## 12. Questions requiring explicit architectural decisions

This analysis identifies requirements; it does not pretend every implementation choice is settled.

1. What is the formal canonical representation of an experience, including source, time, context, confidence and provenance?
2. How are working context, episodic memory, semantic memory, procedural memory and self-model connected without duplicate authority?
3. How are beliefs represented, supported, contradicted, revised, qualified and retired?
4. How does the Brain estimate uncertainty and calibrate confidence across different mechanisms?
5. How are attention and cognitive resource allocation coordinated without a rigid fixed loop?
6. How are predictive models trained and evaluated against actual outcomes?
7. How do symbolic/explicit reasoning mechanisms interact with trainable numerical models?
8. How are long-running goals and tasks persisted, resumed, interrupted and verified?
9. What autonomy/permission model governs observation, recommendation, preparation, execution and escalation?
10. What is the minimum internal interface/monitoring contract needed to inspect the Brain while it is being built?
11. How is learning protected against data leakage, reward hacking, catastrophic interference and false progress?
12. What state is authoritative and recoverable after process, host or storage failure?
13. Which mechanisms must be available in the CPU-only baseline, and which can be optional accelerators?
14. How will the Brain distinguish its own learned preference, a user instruction, an explicit safety invariant and a temporary goal?
15. What is the first vertical slice that demonstrates the full experience-to-future-behavior loop without hardcoded outcomes?

These questions must be resolved against repository evidence and the existing architecture, not by speculative module creation.

## 13. Review checklist

An independent reviewer should challenge both the source analysis and the engineering translation.

- [ ] Is this the correct MCU J.A.R.V.I.S. reference, clearly separated from Edwin Jarvis, comics, Ultron and Vision?
- [ ] Are claims distinguished between directly observed behavior, reasonable mechanism inference and cinematic speculation?
- [ ] Have important behaviors been omitted, especially initiative, continuity, contradiction detection, prediction, operational autonomy, multi-tasking and resilience?
- [ ] Does the target define a Brain rather than a conversational assistant or device-control framework?
- [ ] Is the Brain/host/environment separation technically sufficient for future portability?
- [ ] Do the requirements map to existing Layers 0–19 without creating redundant layers?
- [ ] Are no-hardcoding and no-external-cognitive-API rules precise and implementable?
- [ ] Are legitimate safety invariants and internal APIs distinguished from hardcoded intelligence and outsourced cognition?
- [ ] Are the target capabilities realistically testable with a developmental implementation?
- [ ] Are consciousness and fictional capabilities kept separate from demonstrable engineering claims?
- [ ] What mechanisms, ownership boundaries, tests or constraints are missing?
- [ ] What parts of the existing blueprint should be clarified, expanded, merged or reconsidered in light of this target?

## 14. Source register and evidence quality

The analysis prioritizes official Marvel/Disney material for character/franchise context and uses publicly available screenplay/transcript copies to locate specific scenes. Screenplay copies are secondary references and may differ from the final edited film; the film itself takes precedence where a discrepancy exists.

1. **Disney D23 — MCU Robot Roundup (2025):** official overview stating J.A.R.V.I.S. secures Stark's mansion and Stark Tower, helps run Stark Industries, and supports the Avengers.  
   https://d23.com/mcu-robot-roundup/

2. **Marvel — Every Major A.I. in the Marvel Universe:** official Marvel overview useful for distinguishing AI characters and comic continuity from the MCU focus of this document.  
   https://www.marvel.com/comics/guides/2500/every-major-a-i-in-the-marvel-universe

3. **Iron Man (2008) screenplay copy:** used to inspect the device-intent contradiction, flight monitoring/warnings, offer to take over, and technical post-flight analysis.  
   https://assets.scriptslug.com/live/pdf/scripts/iron-man-2008.pdf

4. **Iron Man 2 (2010) screenplay transcript copy:** used to inspect ongoing health/condition monitoring, simulation, remembered context and recommendations.  
   https://github.com/taubergm/marvel_movie_analysis/blob/master/iron_man_2_script.txt

5. **The Avengers (2012) screenplay transcript:** used to inspect background decryption activity and operational support.  
   https://www.springfieldspringfield.co.uk/movie_script.php?movie=avengers-the-2012

6. **Iron Man 3 (2013) screenplay transcript:** used to inspect information synthesis, virtual crime-scene reconstruction, suit/flight assistance, multi-suit coordination and task support.  
   https://www.springfieldspringfield.co.uk/movie_script.php?movie=iron-man-3

7. **Avengers: Age of Ultron (2015) screenplay transcript:** used to inspect J.A.R.V.I.S.'s expanded role, interface variation work, defensive activity and continuity under attack.  
   https://www.springfieldspringfield.co.uk/movie_script.php?movie=avengers-age-of-ultron

8. **Chelsea Atkins Skelley, Ph.D., University of North Carolina at Greensboro (2016), _Interfaces and Interfacings: Posthuman Ecologies, Bodies and Identities_:** an academic interpretation of J.A.R.V.I.S. as extending Tony Stark's cognition through visualization and technological interfaces. This is interpretation, not Marvel canon or engineering proof.  
   https://libres.uncg.edu/ir/uncg/f/Skelley_uncg_0154D_11922.pdf

---

**Approval status:** Proposed behavioral reference and Brain target. It is not yet a binding constitution, a claim of current implementation, or authorization to begin new runtime work. It should be independently reviewed and reconciled with the existing Brain blueprint, language map and engineering governance before the full documentation baseline is finalized.
