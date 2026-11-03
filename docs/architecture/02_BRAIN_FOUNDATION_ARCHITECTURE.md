# JARVIS Brain Foundation Architecture — Planning Baseline

**Document status:** Proposed architecture for independent review and Project Director decision  
**Planning authorization:** Project Director authorization received 2026-11-03, following acceptance of PR #172  
**Scope:** Foundational Brain architecture: cognitive responsibilities, state ownership, integration, developmental integrity, and whole-system boundaries  
**Implementation status:** No implementation, migration, runtime modification, test execution, technology selection, merge, or deployment is authorized by this document  
**Governing principle:** **ENGINEER THE MECHANISMS; LET BEHAVIOR BE ACQUIRED THROUGH EXPERIENCE.**

---

## 1. Purpose and authority

This document begins the Brain Foundation Architecture Planning stage. It translates the approved whole-system direction, comparative research, mechanism-gap analysis, and accepted foundational capability investigation into a coherent architectural proposal.

It is not a new JARVIS project. It preserves the existing system and treats existing source code as engineering evidence and potential reusable material—not as an authority that dictates the new architecture.

The architecture must support a developing cognitive system. It must not prescribe the knowledge, beliefs, preferences, emotional reactions, associations, strategies, or behaviours that the Brain is meant to acquire through experience.

### 1.1 Governing source baselines

This proposal is grounded in these exact repository revisions:

1. **Whole-system foundation and responsibility map:** PR #171, branch `docs/jarvis-system-architecture-foundation-20261101`, reviewed package HEAD `b05434758ad4fe72815503f89bd5d2990ccb658b`. The governing Document 00 and responsibility Document 01 have separate, scope-limited Project Director approvals recorded in that PR's discussion. PR #171 itself remains open, draft and unmerged; that status is not treated as a merge or implementation authorization.
2. **Brain capability investigation:** PR #172, branch `research/brain-capability-investigation-20261103`, accepted HEAD `d7d676b79dbf3269f7fd3ebdb4363a6df19f255d`. The Project Director accepted this investigation and explicitly authorized this architecture-planning stage. PR #172 remains open, draft and unmerged unless separately changed.
3. **Engineering evidence baseline used by the investigation:** `main` at `1273ddbcd0087d189e01388ded2d362fb1e058d2`. Claims about current implementation are bounded to the files and tests inspected at that revision. This document does not claim that the current main branch has been re-audited at a later commit.

Immutable source links:
- [System architecture foundation — PR #171 baseline](https://github.com/methaneex-oss/MethaneX/blob/b05434758ad4fe72815503f89bd5d2990ccb658b/docs/architecture/00_JARVIS_SYSTEM_ARCHITECTURE_FOUNDATION.md)
- [Whole-system anatomy and responsibility map — PR #171 baseline](https://github.com/methaneex-oss/MethaneX/blob/b05434758ad4fe72815503f89bd5d2990ccb658b/docs/architecture/01_JARVIS_WHOLE_SYSTEM_ANATOMY_AND_RESPONSIBILITY_MAP.md)
- [Comparative Brain research and decision log](https://github.com/methaneex-oss/MethaneX/blob/b05434758ad4fe72815503f89bd5d2990ccb658b/docs/architecture/research/00_BRAIN_FOUNDATION_COMPARATIVE_RESEARCH_AND_DECISION_LOG.md)
- [Brain mechanism gap analysis](https://github.com/methaneex-oss/MethaneX/blob/b05434758ad4fe72815503f89bd5d2990ccb658b/docs/architecture/research/01_BRAIN_FOUNDATION_MECHANISM_GAP_ANALYSIS.md)
- [Accepted foundational capability investigation](https://github.com/methaneex-oss/MethaneX/blob/d7d676b79dbf3269f7fd3ebdb4363a6df19f255d/docs/architecture/research/02_BRAIN_FOUNDATIONAL_CAPABILITY_INVESTIGATION_2026-11-03.md)

### 1.2 What this planning stage is allowed to decide

This stage may propose and reason about:
- the Brain's foundational cognitive responsibilities and their relationships;
- logical state ownership and authority boundaries;
- the overall integration and coordination pattern;
- the conceptual lifecycle of experience, evidence, cognition, action feedback and development;
- the distinction between foundational mechanisms, advanced mechanisms and acquired capability;
- conceptual contracts with the wider JARVIS systems;
- architectural failure semantics and capability-level acceptance criteria.

This stage does not select programming languages, frameworks, databases, model providers, algorithms, runtime topology, deployment topology, APIs, concrete schemas, or implementation task sequences. Those require later, separately authorized specifications.

### 1.3 Status vocabulary

- **Proposed:** recommended here, not yet approved.
- **Approved:** explicitly accepted by the Project Director for the exact recorded revision.
- **Unresolved:** evidence or requirements do not justify a decision yet.
- **Deferred:** intentionally outside this foundation's minimum scope.
- **Rejected:** considered and not selected, with rationale recorded.

Nothing in this draft becomes an approved architectural decision merely because it is committed or reviewed.

---

## 2. Architectural objective

The Brain is the central cognitive system of JARVIS. Its responsibility is to maintain and develop coherent cognitive state; interpret experience; form and revise representations and beliefs; remember; predict; reason; allocate attention; evaluate goals and alternatives; decide; learn; and monitor its own cognitive limitations.

The Brain is not:
- the complete JARVIS system;
- a chatbot or language-model wrapper;
- a fixed knowledge base with scripted responses;
- a single serial pipeline through which every cognitive operation must pass;
- a universal controller that directly owns sensors, transport, operating-system services, execution, security policy or infrastructure;
- a collection of independent feature modules that happen to share a process.

The architectural success condition is **coherent, persistent, evidence-sensitive cognitive development**. The Brain must be able to use experience to alter relevant future cognition while preserving evidence lineage, uncertainty, unrelated knowledge, identity continuity and the ability to detect regressions.

A subsystem's presence is not proof of capability. A capability is demonstrated only when its observable behaviour is exercised under defined conditions and its effects persist appropriately, influence later behaviour, and remain robust under relevant variation and counterexamples.

---

## 3. Foundational architecture principles

### 3.1 One cognitive authority, multiple cooperating responsibilities

The Brain has one coherent cognitive authority, but that does not require one monolithic controller or one global mutable state store. Cognitive responsibilities may be logically differentiated, maintain clear ownership of their authoritative state, and cooperate through explicit exchanges.

No responsibility may silently become a competing source of goals, beliefs or intentions. A coordination facility can allocate access and resolve process conflicts under defined rules; it does not become a second intelligence.

### 3.2 Recurrent, branching and concurrent cognition

Cognition is not a fixed sequence. New experience can trigger retrieval; retrieved memories can change interpretation; attention can redirect processing; a revised belief can invalidate predictions; an outcome can trigger learning; and metacognitive monitoring can reopen earlier work.

Not every experience needs every operation. Some work can proceed concurrently, some must wait for evidence, some can be interrupted, and some can be deferred. The architecture must support revisiting and correction without treating every cognitive activity as a global synchronous cycle.

### 3.3 Authoritative state ownership with coordinated shared context

**Proposed direction:** use a hybrid integration pattern:
- each logical cognitive responsibility retains authority over the state it owns;
- a bounded, task/context-sensitive active workspace makes selected information available for coordinated cognition;
- cross-responsibility changes are communicated with source, version, dependency and status information;
- the workspace is a view and coordination facility, not a universal database, truth oracle or owner of every cognitive fact.

This combines the clarity and fault containment of owner-managed state with the flexible interaction of a shared active context. It avoids both extremes: an all-controlling central workspace and fully isolated mechanisms that cannot form coherent cognition.

The workspace must not silently overwrite authoritative state. A working-context summary is not the source of truth for the memories, beliefs or predictions from which it was assembled.

### 3.4 Common information discipline, plural representations

**Proposed direction:** use a common conceptual information envelope while retaining plural, domain-appropriate representations.

The envelope must be capable of preserving, where applicable:
- identity and information kind;
- origin/source and provenance;
- event time, observation time and temporal validity;
- context and scope;
- epistemic status;
- uncertainty and its meaning;
- supporting, contradicting and dependent evidence;
- version, derivation and historical lineage;
- ownership, integrity and access constraints.

This is not a final data schema. Not every representation needs every attribute, and a universal ontology must not flatten the differences between episodes, continuous signals, entities, events, concepts, causal structures, language, plans, simulations and learned parameters.

Uncertainty must not be reduced to one unqualified scalar. Signal quality, source reliability, ambiguity, missing context, model uncertainty and disagreement are different conditions.

### 3.5 Preserve epistemic distinctions

The Brain must not conflate:
- raw or preprocessed observation;
- perceptual interpretation or hypothesis;
- retained episode or memory;
- belief or accepted working understanding;
- prediction;
- imagined or simulated possibility;
- goal, plan, intention or decision;
- action request;
- execution evidence;
- verified outcome.

A generated explanation is not proof that the described reasoning occurred. A sensor score is not automatically the Brain's confidence in an identity claim. An issued action is not proof of execution. An execution result is not proof of the intended real-world consequence.

### 3.6 Engineer developmental capacity, not predetermined outcomes

Bootstrap state and rules may establish identity continuity, representation capacity, provenance, learning eligibility, resource limits, safety boundaries and the ability to process initial experience.

Bootstrap must not encode the desired learned beliefs, preferences, emotional reactions, strategies or behavioural conclusions. Deterministic constraints are appropriate for integrity, type validation, permissions, resource limits and explicit engineering invariants; they must not be disguised cognitive conclusions.

### 3.7 Separate cognitive intent from authorization and execution

The Brain forms intent and may issue an action proposal or request. It cannot authorize itself. The request must pass through the wider JARVIS governance and security path, operational validation, execution and outcome verification. Verified outcomes—not mere requests—return as evidence for cognition and learning.

### 3.8 Development must be observable and correctable

Material learning changes must preserve what evidence caused them, what state was changed, what depended on it, how the change was evaluated, and how an adverse change can be contained or reversed. Learning must be assessed longitudinally and under variation, not only by a single successful fixture.

### 3.9 Comparative reference lenses: MCU J.A.R.V.I.S., human cognition and engineering reality

The architecture is evaluated through three distinct lenses. They answer different questions and must not be collapsed into one source of authority.

**MCU J.A.R.V.I.S. — functional inspiration.** The accepted investigation identifies depicted behaviour relevant to contextual/pragmatic interpretation, situational awareness and grounded assistance, diagnostics and state monitoring, technical analysis and iterative improvement, and human-machine task support. Examples include the Iron Man 3 rescue sequence discussed in *The User Experience of Iron Man*, the workshop diagnostic sequence in the Iron Man shooting script, and the suit/Iron Legion diagnostics and maintenance interfaces discussed by Territory Studio. These depictions inform the *kind of capability and interaction* JARVIS should be able to demonstrate. They do not establish fictional internal memory structures, learning algorithms, neural organization or runtime architecture.

**Human cognition — scientific reference.** Research on attention and memory, cognitive control, memory organization/generalization and continual learning informs questions about limited active capacity, selective processing, retrieval, feedback, interference, transfer and developmental stability. The relevant sources include Cowan et al. (2024), Badre (2025), Sun et al. (2023), and Yang et al. (2026), as recorded in the accepted research baseline. These findings are evidence to reason from, not a requirement to reproduce human neural structures or biological limitations.

**JARVIS engineering reality — implementation evidence.** The inspected engineering baseline establishes what exists and what has actually been demonstrated. It includes memory persistence and retrieval, attention reinforcement, bounded reasoning, prediction feedback and persistent numeric adaptation. It also exposes gaps: retrieved memories were not passed into the inspected reasoning premises; structured attribute-overlap retrieval is not proof of generalized semantic retrieval; prediction and belief records have limited explicit evidence/assumption detail; and the Phase 8 learning test demonstrates bounded persistent numeric parameter evolution, not broad concept acquisition or transfer. These observations constrain claims and identify integration work; they do not force the new architecture to preserve every existing implementation choice.

| Architectural concern | MCU J.A.R.V.I.S. lens | Human cognition lens | Engineering-reality constraint |
|---|---|---|---|
| Contextual interpretation and grounding | Depicted contextual, spatial and pragmatic assistance | Perception, attention and memory jointly shape interpretation | Preserve acquisition evidence separately from Brain-level interpretation; do not claim current general grounding |
| Diagnostics and self-monitoring | Depicted system/suit diagnostics and technical analysis | Cognitive control and error monitoring inform corrective responses | Monitoring must lead to observable correction, not merely confidence labels |
| Memory and active context | Fictional continuity is a capability aspiration, not evidence of hidden memory internals | Retrieval, working memory and attention interact | Existing retrieval exists, but the inspected reasoning path did not consume retrieved memories as premises |
| Learning and development | Fictional iterative improvement is an aspiration, not proof of developmental internals | Learning, consolidation, interference and generalization inform evaluation | Existing evidence is bounded numeric adaptation; broader learning requires new evidence |
| Human-machine action support | Depicted collaboration and task assistance | Goal-directed control and social coordination provide useful questions | Brain intent must remain separate from governance authorization, execution and verified outcome |

These lenses influence requirements and failure scenarios, not a predetermined implementation. When they conflict, the architecture must be justified against the actual engineering objective, evidence quality, system boundaries and developmental principle—not by analogy alone.

---

## 4. Foundational cognitive responsibility architecture

The 11 foundational capabilities from the accepted investigation are retained. They are **not** converted into 11 one-capability-per-module boxes. The following groupings identify cooperating responsibility areas and the kinds of state they must keep coherent. They are logical architectural responsibilities; later design may combine or distribute them without changing their authority obligations.

### 4.1 Cognitive continuity and state stewardship

**Responsibilities:** maintain coherent identity and cognitive continuity across events, interruptions and restarts; distinguish current, historical, derived and provisional state; preserve lineage as the Brain changes.

**Must enable initially:** a minimal persistent cognitive identity, lifecycle continuity, version-aware state recovery and the ability to distinguish historical evidence from current interpretation.

**Must develop through experience:** richer self-understanding, capability estimates, personal history and learned continuity of context.

**Interactions:** all other responsibilities depend on continuity and state lineage. Learning may change capability without erasing the history of how the Brain developed.

### 4.2 Experience interpretation, representation and grounding

**Responsibilities:** transform qualified incoming observations into candidate entities, events, properties, relations and context-sensitive interpretations; associate observations across time and modalities; ground language and symbols in observed, remembered, hypothetical or unknown referents.

**Boundary:** SYS-03 acquires and preprocesses signals and may provide detections or proposals. The Brain evaluates what those observations mean, whether observations refer to the same entity/event, and what claims are justified. Acquisition uncertainty and inference uncertainty remain distinguishable.

**Must enable initially:** evidence-bearing observations, source/time/context preservation, candidate interpretations, uncertainty and competing hypotheses.

**Must develop through experience:** robust entity and event models, cross-modal grounding, abstraction and context-sensitive interpretation.

**Interactions:** representation informs memory, belief, prediction and reasoning; memory and current context can alter interpretation; contradictory observations can reopen prior conclusions.

### 4.3 Memory, belief and knowledge stewardship

**Responsibilities:** preserve experiences and their provenance; retrieve relevant episodes and knowledge; distinguish historical records from revised interpretations; form, qualify, revise, suspend or withdraw beliefs as evidence changes.

**Must enable initially:** retention and retrieval, explicit separation of evidence from belief, evidence lineage, and the ability to preserve contradiction rather than silently overwrite it.

**Must develop through experience:** useful associations, organized knowledge, retrieval relevance, concepts and increasingly reliable beliefs.

**Interactions:** memory retrieval must be able to inform active reasoning, not merely appear as unused context. Belief changes must notify dependent predictions, plans and working contexts that may now be stale.

**Current evidence constraint:** the inspected cognitive reasoning path retrieved memories into result context but did not pass them into the reasoning premises in that path. Existing structured attribute-overlap retrieval is not evidence of generalized semantic retrieval. These are integration/evaluation gaps, not reasons to discard the existing memory system without technical assessment.

### 4.4 Attention and active working context

**Responsibilities:** select what deserves processing, maintain task-relevant active information, manage competing demands, and support interruption, backgrounding, suspension and resumption.

**Must enable initially:** bounded active context, task isolation where needed, prioritization under explicit resource constraints, and preservation of the source and freshness of activated information.

**Must develop through experience:** better relevance estimation, context-sensitive prioritization and efficient allocation of cognitive effort.

**Interactions:** goals and valuation influence attention; attention selects information for reasoning; memory retrieval influences attention; prediction errors and metacognitive signals can interrupt or reopen a task.

The active workspace is not long-term memory, the belief store, a goal authority or a duplicate universal state store.

### 4.5 Predictive, inferential and model-based cognition

**Responsibilities:** form predictions from current representations and beliefs; compare them with outcomes; reason from evidence; evaluate causal and alternative explanations; and, as the foundation matures, support simulation and counterfactual evaluation.

**Must enable initially:** bounded prediction, explicit assumptions/scope/horizon, evidence-aware reasoning, outcome resolution and the ability to distinguish prediction from observation.

**Must develop through experience:** improved predictive models, broader inference, causal understanding, abstraction, generalization and reusable reasoning strategies.

**Deferred advanced depth:** sophisticated long-horizon simulation and broad counterfactual reasoning are anticipated but are not required to be fully developed in the minimum foundation.

**Interactions:** beliefs and assumptions support predictions; new evidence may invalidate dependent predictions; resolved outcomes provide learning evidence; reasoning may request memory, perception or further information.

### 4.6 Goals, valuation, affective processing, planning and decision formation

**Responsibilities:** represent goals and constraints; evaluate relevance, significance, urgency, risk, internal conditions and competing outcomes; compare alternatives; form plans and decisions; determine whether to act, ask, wait, defer or stop. This responsibility includes the Brain's minimum affective processing capacity; affect is not omitted from the foundation merely because sophisticated affective dynamics are advanced.

**Must enable initially — goal processing:** receive, represent, track, evaluate and revise explicit goals, constraints and alternatives. The initial Brain must be able to distinguish a supplied goal from a candidate goal it has formed, and a goal from an intention, plan, decision, or authorized action.

**Must develop through experience — goal formation:** develop the capacity to generate candidate goals from interpreted experience, changes in circumstances, discrepancies between expected and observed outcomes, internal conditions, and the consequences of prior goals and actions. These are possible sources of candidate goals, not fixed triggers or prescribed objectives. Candidate goals must be evaluated for evidential basis, relevance, feasibility, uncertainty, risk, conflicts, constraints and expected consequences; they may be revised, deferred, suspended or abandoned as evidence changes. The Brain must preserve why a candidate goal arose and what experience altered its priority. Acquired priorities and preferences are revisable products of development, not preloaded behavioural mappings.

**Must enable initially — affective appraisal:** evaluate the significance of events and information in relation to current goals, risk, uncertainty and relevant internal conditions. This is a minimal capacity for context-sensitive appraisal and modulation, not a requirement to begin with a mature catalogue of emotions, fixed emotional labels, or predetermined reactions.

**Must develop through experience — affective sophistication:** improve the differentiation, calibration and context-sensitivity of affective appraisal, including learned modulation across attention, memory, learning and decision formation. Advanced affective dynamics are developmental depth; the basic affective responsibility is foundational.

**Interactions:** valuation and affective appraisal may alter what receives attention, what is encoded or retrieved, which experiences warrant further evaluation, how alternatives are assessed and how candidate goals are prioritized. These influences must remain evidence-sensitive, bounded and inspectable. Affective appraisal does not itself establish facts, create permission, or dictate an action.

**Boundary with SYS-05 and SYS-06:** the Brain owns cognitive interpretation of significance, goals, valuation and affective appraisal. SYS-05 remains responsible for defined operational/homeostatic regulation and does not silently set cognitive priorities or rewrite goals. SYS-06 is a proposed, unresolved whole-system modulation/global-state-signalling responsibility, not an approved mandatory subsystem. If later justified and separately specified, SYS-06 may provide governed modulation across system operation; it does not own Brain beliefs, goals or emotional meaning and must not encode fixed stimulus-to-emotion or emotion-to-action rules. The existence, placement, scope and contracts of SYS-06 remain open. No endocrine-inspired implementation is selected here.

**Developmental boundary:** no fixed rule such as negative affect → reject, failure → trauma, or success → reward is permitted as a substitute for acquired appraisal. Bootstrap mechanisms may preserve integrity, boundedness and governance invariants; they must not prescribe learned emotional reactions, motivations, priorities or behaviours.

### 4.7 Learning and developmental adaptation

**Responsibilities:** identify when experience justifies a change; determine what is eligible to change; preserve evidence and dependencies; evaluate the proposed change; detect interference or regression; and maintain developmental continuity.

**Must enable initially:** bounded update eligibility, provenance-linked candidate changes, evaluation, persistence where justified, and safeguards against corrupting unrelated state.

**Must develop through experience:** stronger associations, abstractions, predictive models, reasoning strategies, valuation and skills.

Learning is distributed across the Brain. It is not a single terminal stage or one parameter updater. Different learning classes have different evidence and risk requirements. A numeric parameter update is not equivalent to concept acquisition or broad transfer.

### 4.8 Cognitive coordination and metacognitive regulation

**Responsibilities:** coordinate concurrent cognitive work; manage dependencies, interruptions and conflicts; monitor uncertainty, inconsistency, error, capability limits and process effectiveness; initiate bounded corrective responses.

**Corrective responses may include:** reconsidering an interpretation; retrieving relevant experience; seeking additional evidence; revising an assumption or prediction; changing an unsuccessful reasoning approach; requesting clarification or assistance; suspending a conclusion or action when evidence is insufficient; and evaluating whether the correction improved the result.

**Authority boundary:** monitoring does not grant unrestricted control over every cognitive responsibility. It can request reconsideration or initiate a defined corrective path, but it cannot bypass state ownership, erase evidence, override governance or become an unbounded second Brain.

---

## 5. Cognitive state and information lifecycle

The architecture requires coherent distinctions among state classes. This section defines their conceptual role and ownership obligations, not concrete schemas or storage technology.

| State class | Architectural meaning | Authority obligation |
|---|---|---|
| Experience evidence | What was observed, received or reported, with source and acquisition context | Preserve origin and historical lineage; do not rewrite as a later interpretation |
| Interpretations and hypotheses | Candidate meanings, identities, relations and explanations | Retain uncertainty and alternatives where evidence is insufficient |
| Memories and episodes | Retained experience and derived knowledge | Preserve derivation and distinguish remembered evidence from reconstructed summaries |
| Beliefs and world understanding | Claims currently accepted to a stated degree and scope | Support revision, contradiction, suspension and withdrawal |
| Active context | Information currently activated for a task or cognitive situation | Remain bounded, scoped and freshness-aware; never become universal truth storage |
| Predictions and simulations | Expected or imagined states, with assumptions and scope | Never silently promote imagined content to observed history |
| Goals, plans and intentions | Desired states, constraints and candidate courses of action | Remain attributable to cognitive decision processes and subject to governance boundaries |
| Learning candidates and adaptations | Proposed or activated experience-dependent changes | Preserve evidence, dependencies, evaluation and recovery path |
| Metacognitive state | Estimates of process health, uncertainty, capability and unresolved issues | Inform corrective action without becoming unrestricted cognitive authority |

### 5.1 Lifecycle is recurrent, not a mandatory pipeline

An experience may:
- be retained without immediate deep reasoning;
- activate a memory that changes interpretation;
- create a hypothesis that remains unresolved;
- contradict a belief and trigger reconsideration;
- resolve or invalidate an earlier prediction;
- change attention or goal priority;
- contribute to one or more candidate learning updates;
- require no durable learning at all.

The Brain must support parallel work and revisitation. The architecture must also preserve the causal and temporal links needed to understand why a conclusion or behaviour changed.

### 5.2 Dependency and staleness

A material change to a belief, representation, goal or constraint may affect dependent predictions, plans, active contexts and decisions. The architecture must make these dependencies discoverable enough that affected work can be marked stale, reconsidered or suspended.

A dependent item must not remain silently authoritative after its supporting assumptions have been withdrawn. Invalidation should be proportionate: a local change must not unnecessarily erase unrelated state.

### 5.3 Conflicting and delayed evidence

Late, duplicated, reordered or contradictory observations must not be silently treated as new truth. The Brain must preserve event time separately from receipt time where relevant, assess source and context, and retain disagreement until evidence justifies resolution.

---

## 6. Integration and coordination model

### 6.1 Proposed hybrid pattern

The proposed architecture combines:
1. **Owner-managed cognitive state:** each responsibility has clear authority over its own state class.
2. **Bounded shared active context:** selected, task-relevant information is made available to concurrent cognitive work.
3. **Explicit coordination:** requests, proposals, evidence, revisions and outcomes carry enough lineage and status to avoid silent overwrites.
4. **Recurrent cognitive activity:** work may be parallel, interrupted, resumed or revisited; no single fixed pipeline is mandatory.
5. **Bounded metacognitive correction:** monitoring can trigger appropriate reconsideration but cannot seize all authority.

This is a logical integration choice, not a commitment to microservices, multiple processes, distributed deployment or any particular runtime.

### 6.2 Alternatives considered

| Pattern | Strength | Principal failure risk | Planning disposition |
|---|---|---|---|
| Central shared workspace / broadcast | Flexible cross-responsibility access and rapid coordination | Bottleneck, competition, unclear truth/priority, accidental global mutable state | Do not use as sole authority; retain only a bounded coordination/workspace role |
| Fully distributed owner-managed responsibilities | Clear local ownership and fault containment | Fragmented context, stale views, synchronization and coordination overhead | Retain ownership principle, but do not leave responsibilities isolated |
| Hybrid owner-managed state plus bounded workspace | Balances authority with integrated active cognition | Duplicate/stale views unless versioning, provenance and invalidation are explicit | **Recommended provisional direction** |

A centralized serial controller is not selected. Fully isolated modules are not selected. A single universal database or shared workspace is not selected as the source of truth.

### 6.3 Concurrency and conflicting updates

The architecture must define, in later detailed specifications, which changes require atomic commitment, which can be proposed asynchronously, how incompatible updates are detected, and how stale work is reconsidered. The foundation requires the invariant; it does not yet prescribe a concurrency algorithm.

No cognitive responsibility may silently overwrite another responsibility's authoritative state. If two valid sources disagree, the disagreement must remain visible until an evidence-sensitive resolution is justified.

### 6.4 Partial failure and recovery

A failure in one responsibility should degrade the capabilities that depend on it without corrupting unrelated authoritative state. The Brain should be able to preserve recoverable context, mark unavailable information, suspend unsafe conclusions and resume when dependencies return.

Recovery must not fabricate a successful cognitive operation. A missing retrieval is not an empty memory; an interrupted prediction is not a resolved prediction; an attempted update is not an adopted update.

---

## 7. Whole-system boundaries and external interactions

The Brain must be architected to function in a controlled development environment before all JARVIS systems exist, while remaining compatible with the whole-system responsibility map.

| External system | Brain receives | Brain may request or provide | Boundary that must remain intact |
|---|---|---|---|
| SYS-02 Nervous / signalling | Routed observations, events, delivery and failure evidence | Logical messages, requests, priorities and feedback needs | Transport does not interpret evidence or own cognition |
| SYS-03 Sensory acquisition | Qualified observations, modality metadata and acquisition uncertainty | Requests for additional observations or clarification | Acquisition/preprocessing does not alone establish Brain-level meaning or identity |
| SYS-04 Motor / action | Execution state and outcome evidence | Action proposals/requests | Brain intent is not authorization or execution |
| SYS-05 Autonomic regulation | Resource limits, availability and operational health | Resource or scheduling requests | Operational regulation does not create cognitive goals or substitute for cognitive valuation/affective appraisal |
| SYS-06 Proposed modulation/global-state signalling | No SYS-06 capability is assumed to exist; if separately authorized later, the Brain may receive governed modulation signals and their provenance/status | The Brain may provide bounded, evidence-grounded modulation requests if a later SYS-06 contract authorizes them | SYS-06 remains proposed and unresolved, not a mandatory subsystem; it does not own Brain beliefs, goals or affective meaning and may not encode predetermined emotional or behavioural outcomes |
| SYS-07 Defence / security | Trust, threat, integrity and containment information | Requests for security assessment or protected operations | Brain cannot override trust boundaries or restore trust unilaterally |
| SYS-08 Embodiment / computational and environmental substrate | Compute, storage, networking, device, runtime and operating-context availability, constraints, failures and recovery status | Cognitive persistence/read requests, bounded resource requirements and operational needs through defined contracts | SYS-08 owns/provides the substrate, not cognitive meaning or authoritative cognitive content; substrate failures are operational evidence, not automatically evidence about the external world or a cognitive conclusion |
| SYS-09 Interaction | User intent, feedback, clarification and operator decisions | Responses, questions, explanations grounded in actual state | Interface presentation is not independent cognition |
| SYS-10 Development/evaluation | Experiment results and evaluation reports | Testable capability requirements and controlled learning/evaluation requests | Development environment must not silently mutate live cognitive state |
| SYS-11 Governance/assurance | Policies, permissions, approval decisions and constraints | Action requests and evidence needed for authorization/audit | Governance authorizes and constrains; it does not originate Brain beliefs or goals |

The Brain owns the semantic content, provenance relationships, version meaning and cognitive consistency of its authoritative state. SYS-08 provides the compute, storage, networking, devices and runtime substrate through which that state is processed and persisted; substrate ownership does not transfer cognitive authority to infrastructure. The Brain may request persistence and recovery of cognitive state, but it must be able to distinguish a successful cognitive state transition from an infrastructure acknowledgement that bytes were stored or a process was restarted. SYS-08 reports operational availability, capacity, integrity signals and failures; it does not decide whether a belief, memory or interpretation is true.

Responsibility for recovery is correspondingly divided: SYS-08 restores or reports the availability of the underlying operational substrate; SYS-05 may coordinate permitted component lifecycle operations; SYS-07 assesses integrity and security concerns within its authority; and SYS-01 validates recovered cognitive identity, lineage, consistency and epistemic status before treating recovered state as active cognition. A storage/network/runtime failure must not be reinterpreted as an external-world event, prediction outcome, memory absence or learning signal without independent evidence. Exact persistence, recovery and service contracts remain future specification work; no database, storage technology, runtime topology or infrastructure implementation is selected here.

The exact message contracts, trust semantics, timing, cancellation and failure protocols remain future specification work. This document establishes the responsibility boundaries only.

---

## 8. Learning and developmental integrity

### 8.1 Learning is a cross-responsibility change

An experience can change memory organization, associations, abstractions, beliefs, predictions, reasoning strategies, valuation or skills. A learning system that only updates one numeric parameter cannot stand in for all these forms.

For every material candidate change, the architecture must be able to answer:
- what state is proposed to change;
- which experience and evidence support the change;
- what assumptions and context limit the change;
- which other state depends on it;
- whether the change is reversible or recoverable;
- how the change will be evaluated;
- what evidence would cause it to be rejected, revised or rolled back.

### 8.2 Separate candidate formation, evaluation and activation

The architecture should distinguish a candidate learning change from an accepted active change. The process must not assume that every prediction error or adverse event deserves the same update. Evaluation must consider evidence quality, context, repeatability, conflicting observations, expected benefit, risk of interference and relevant counterexamples.

This is a conceptual developmental safeguard. It does not select a specific learning algorithm or threshold.

### 8.3 Transfer and regression are required evidence

A learned change should be evaluated on:
- the original context in which it was acquired;
- a varied but relevant context;
- a novel related context where transfer is expected;
- counterexamples and boundary conditions;
- unrelated capabilities that should remain unaffected;
- delayed evaluation after persistence/reconstruction where appropriate.

A change that improves one fixture but damages broader behaviour is not automatically successful learning.

### 8.4 Preserve developmental lineage

The Brain may change its internal models and capabilities over time. It must retain enough historical lineage to explain what changed, when, on what evidence, and with what measured effect. Continuity is not immutability: learning is expected to change the Brain, but must not make its developmental history unknowable.

---

## 9. Initial foundation versus later development

The following is a capability-level allocation, not an implementation schedule.

| Foundational responsibility | Initial enabling capacity | Expected experience-acquired development |
|---|---|---|
| Cognitive continuity | Persistent identity and recoverable cognitive state | Richer self-model and developmental history |
| Experience representation | Evidence-bearing observations and distinct epistemic statuses | Better grounded, contextual representations |
| Memory and retrieval | Retention, provenance and basic retrieval | Relevance, association, consolidation and generalization |
| Belief/knowledge | Evidence-qualified claims and revision capacity | Broader, more accurate world understanding |
| Attention/working context | Bounded active context and resource allocation | Learned relevance and context-sensitive prioritization |
| Prediction/outcome comparison | Bounded predictions with assumptions and resolution | Better models, horizons and transfer |
| Learning/adaptation | Controlled candidate change, evaluation and persistence | Concept, model, strategy and skill development |
| Reasoning/inference | Evidence-aware foundational inference | Richer causal, analogical and abstract reasoning |
| Goals/valuation/decision | Process supplied goals and constraints; distinguish them from candidate goals formed internally | Experience-acquired candidate-goal formation, revised priorities/preferences, affective calibration and planning competence |
| Cognitive control/metacognition | Detect uncertainty, inconsistency and limitations; request correction | More effective self-monitoring and strategy selection |
| Integrated coordination | Explicit ownership, dependencies and bounded shared context | More efficient concurrent coordination under varied load |

### 9.1 Deferred or advanced capabilities

The foundation should anticipate, but need not initially deliver mature:
- advanced perceptual models and robust multimodal grounding;
- broad abstraction and transfer;
- rich causal and counterfactual reasoning;
- sophisticated imagination and long-horizon simulation;
- advanced affective dynamics and learned global modulation (while minimum affective appraisal remains foundational);
- complex social cognition and teammate modelling;
- mature language-mediated cognition;
- broad procedural/skill learning;
- proactive continuous cognition.

The foundation must not block these capabilities, but their presence must be justified by later evidence and separate design.

---

## 10. Architecture risks and required safeguards

| Risk | Why it matters | Required architectural safeguard |
|---|---|---|
| Epistemic contamination | Observation, inference, simulation and belief become indistinguishable | Explicit status, provenance and derivation distinctions |
| False entity/event continuity | Different entities or events are incorrectly merged | Preserve competing identity hypotheses and evidence |
| Memory disconnected from reasoning | Retrieved experience is present but has no effect on inference | Demonstrate that relevant retrieved evidence can enter and influence reasoning |
| Stale dependent state | Changed beliefs leave predictions/plans silently valid | Dependency tracking and proportionate reconsideration |
| Central coordination bottleneck | Every cognitive operation waits on one controller | Bounded coordination; allow independent work with explicit ownership |
| Fragmented cognition | Responsibilities cannot use each other's relevant state | Shared active context and explicit exchange semantics |
| Runaway association/generalization | Co-occurrence becomes false causal knowledge or universal rule | Preserve relation type, context, exceptions and counterevidence |
| Hardcoded behaviour | Bootstrap rules predetermine learned conclusions | Separate enabling invariants from acquired cognitive content |
| Uncontrolled learning interference | A local improvement damages unrelated capabilities | Candidate evaluation, regression checks and recovery |
| Metacognitive overreach | Monitoring becomes an unrestricted second authority | Bounded corrective requests and preserved state ownership |
| Affective omission or reification | Basic significance/internal-condition appraisal is omitted, or affect is reduced to fixed labels and stimulus-response rules | Include minimum contextual affective appraisal; keep its learned sophistication revisable and distinct from SYS-05 operational regulation and unresolved SYS-06 modulation |
| Goal passivity or hardcoded motivation | Brain can only process externally supplied goals, or bootstrap rules prescribe its objectives | Distinguish supplied and experience-formed candidate goals; preserve evidence, evaluation, revision and governance constraints without preloading desired goals |
| Substrate/cognition conflation | Infrastructure availability or persistence acknowledgements are mistaken for cognitive truth, memory absence or learning evidence | Separate SYS-08 operational substrate state from SYS-01 authoritative cognitive state and recovery validation |
| Action authority confusion | Brain intent is mistaken for permission or execution | Separate intent, authorization, validation, execution and verified outcome |
| False capability claims | Narrow tests are presented as broad intelligence | Capability-specific, longitudinal and transfer-oriented evidence |

---

## 11. Capability-level architecture acceptance criteria

The following criteria convert the accepted investigation's evidence matrix into architecture-level obligations. They are not claims that current JARVIS already satisfies them.

1. **Continuity:** after interruption/reconstruction, the Brain can recover coherent state while distinguishing retained history from current derived state; recovery must not fabricate missing context.
2. **Experience representation:** every material interpretation can be traced to observations, sources, transformations and uncertainty; conflicting evidence remains inspectable.
3. **Memory:** a relevant retrieved episode can materially inform a later reasoning or decision process, and the system can show which evidence influenced the result.
4. **Belief revision:** new evidence can qualify, revise, suspend or withdraw a belief while preserving its previous lineage and notifying dependent state.
5. **Attention/context:** under competing tasks, the Brain can prioritize, suspend and resume context without silently losing goals, permissions, evidence or freshness.
6. **Prediction:** a prediction has enough scope, assumptions and resolution conditions to compare it with a later outcome; an unresolved prediction is not treated as a failure or success by default.
7. **Learning:** a candidate change can be evaluated on varied and novel relevant cases, persist when accepted, and be rejected or recovered when it causes regression.
8. **Reasoning:** conclusions distinguish evidence from assumptions and remain qualified by scope and uncertainty; fluent output alone is not accepted as reasoning evidence.
9. **Goals/valuation/affect/decision:** the Brain can process supplied goals and form traceable candidate goals from experience; candidate goals can be evaluated, revised, suspended or abandoned; minimum affective appraisal can assess significance, risk and internal conditions and influence attention, memory, learning and decisions without fixed emotional or behavioural mappings.
10. **Metacognition/control:** detected uncertainty or error can lead to an appropriate corrective response, and the system can assess whether that response helped; monitoring cannot bypass governance.
11. **Integrated coordination:** a change in one responsibility causes relevant dependent state to be reconsidered without corrupting unrelated state; partial failure does not silently invalidate the whole Brain.
12. **Substrate boundary:** cognitive state remains semantically owned and validated by SYS-01 while SYS-08 supplies operational resources and persistence; substrate failure or acknowledgement is not silently treated as cognitive or external-world evidence.

### 11.1 Cross-capability acceptance scenarios

The architecture must support end-to-end scenarios such as:
- an observation that initially supports two possible entity identities, followed by a later cross-modal observation that changes the stronger hypothesis without rewriting the original observation;
- a retrieved past episode that changes a current inference, with provenance visible in the conclusion;
- new evidence that revises a belief and causes dependent predictions and plans to be reconsidered;
- a prediction whose outcome arrives late or out of order, without treating receipt time as event time;
- a learning candidate that improves one context but regresses an unrelated capability, and is therefore rejected or recovered;
- a task interruption followed by resumption after a relevant belief or permission has changed;
- a metacognitive check that requests more evidence or suspends a conclusion instead of inventing certainty;
- a candidate goal formed after an unexpected outcome, with its evidential lineage visible, its feasibility and constraints evaluated, and the goal revised or abandoned when later evidence defeats its basis;
- an affective appraisal in which the same event has different significance under different goals or internal conditions, changing attention or evaluation without a fixed stimulus-to-emotion or emotion-to-action rule;
- an SYS-06 modulation signal absent because that responsibility is not deployed, with the Brain continuing within its defined foundational capabilities and not assuming SYS-06 is mandatory;
- a SYS-08 storage/runtime interruption during cognitive persistence, where infrastructure failure is recorded as operational evidence and recovered cognitive state is validated by SYS-01 before reuse;
- an action request that is denied by governance, with the denial preserved as a constraint/outcome rather than treated as an executed action.

These scenarios are architecture acceptance obligations. Their concrete fixtures and implementation tests belong to later verification planning.

---

## 12. Decisions proposed for Project Director review

| ID | Proposed decision | Status |
|---|---|---|
| BA-01 | Treat the Brain as one coherent cognitive authority with multiple logically distinct, cooperating responsibilities | Proposed |
| BA-02 | Use owner-managed authoritative cognitive state plus a bounded, task-sensitive shared active context | Proposed |
| BA-03 | Use a common conceptual information envelope with plural domain-appropriate representations | Proposed |
| BA-04 | Treat cognition as recurrent, branching and concurrent rather than a mandatory serial pipeline | Proposed |
| BA-05 | Preserve explicit distinctions among observation, interpretation, memory, belief, prediction, simulation, intention, action request and verified outcome | Proposed |
| BA-06 | Treat learning as a distributed, evidence-sensitive developmental process with candidate evaluation and regression protection | Proposed |
| BA-07 | Give metacognitive monitoring bounded corrective authority, not unrestricted control | Proposed |
| BA-08 | Preserve strict separation between cognitive intent, governance authorization, operational validation, execution and outcome verification | Required by approved whole-system boundary; restated here |
| BA-09 | Keep advanced capabilities extensible but outside the minimum foundational scope unless evidence justifies inclusion | Proposed |
| BA-10 | Include minimum context-sensitive affective appraisal in the foundational Brain; treat sophisticated affective dynamics as acquired development | Proposed |
| BA-11 | Treat experience-acquired candidate-goal formation as a developmental capability, distinct from supplied-goal processing and external action authorization | Proposed |
| BA-12 | Preserve SYS-06 as a proposed, unresolved modulation responsibility rather than an approved mandatory subsystem | Required by PR #171 boundary; restated here |
| BA-13 | Define SYS-08 as the operational substrate provider while SYS-01 retains semantic authority and validation of cognitive state | Required by PR #171 boundary; restated here |

No final technology, algorithm, database, schema, API, process topology or deployment topology is selected.

---

## 13. Unresolved architecture questions

The following questions remain open because the current evidence does not justify pretending they are settled:

1. Which cognitive state transitions require atomic commitment, and which can safely converge asynchronously?
2. What minimum active workspace semantics are necessary without duplicating memory, beliefs or task state?
3. What is the minimum useful set of epistemic and uncertainty distinctions for the first operational foundation?
4. Which reasoning forms are essential to the initial foundation, and which can be layered on later?
5. How should conflicting beliefs be represented and resolved when sources have different reliability, timing and scope?
6. What learning classes are safe for online adaptation, and which require controlled offline evaluation or explicit approval?
7. What is the minimum viable self-model required for effective metacognition without building a second cognitive authority?
8. What minimum affective appraisal state and observable evidence are required initially, and which affective dynamics should remain experience-acquired?
9. Under what conditions, if any, is a distinct SYS-06 modulation responsibility justified, and what authority, scope and interfaces would it have relative to SYS-01, SYS-05 and SYS-08?
10. What evidence is sufficient to claim that candidate-goal formation is genuinely experience-acquired rather than a hardcoded objective generator?
11. What capability evidence is sufficient to claim transfer, generalization and durable behavioural change?
12. What is the minimum cognitive contract needed for the Brain to operate before the full sensory, action and embodiment systems exist, including when SYS-06 is absent?
13. Which existing JARVIS mechanisms can be preserved, adapted or replaced after a source-level compatibility assessment against this architecture?
14. Which architectural decisions require separate Project Director approval before detailed mechanism specifications begin?

---

## 14. Scope boundaries and next gates

### 14.1 Included in this planning deliverable

- Foundational Brain responsibility architecture.
- Logical state ownership and epistemic distinctions.
- Proposed integration and coordination pattern.
- Developmental integrity and learning constraints.
- Whole-system responsibility boundaries.
- Architecture-level risks, acceptance criteria and unresolved questions.

### 14.2 Explicitly excluded

- Runtime code changes or refactoring.
- Test, build or benchmark execution.
- Algorithm selection or detailed mechanism implementation.
- Concrete data schemas, API definitions or transport protocols.
- Language, framework, database, model-provider or deployment selection.
- Implementation tickets, coding sequence, migrations or merge.
- Claims that the current Brain meets the proposed acceptance criteria.

### 14.3 Required next gates

1. Independent Reviewer examines this exact planning revision, challenges the proposed decisions, checks traceability to PR #171 and accepted PR #172, and identifies unresolved or unsupported architectural claims.
2. Builder addresses findings in the same planning artifact and records exact changes and evidence separately where appropriate.
3. Project Director decides which proposed architectural decisions to accept, reject or return for further work.
4. Only after explicit Project Director approval may detailed mechanism specifications be separately authorized.
5. Implementation, runtime tests, technology choices and merge remain separate authorization gates.

---

## 15. Completion statement

This document establishes a proposed integrated architecture direction for the Brain foundation. It does not claim that the architecture is approved, that all foundational capabilities are implemented, or that current JARVIS behaviour satisfies the acceptance criteria.

The central architectural commitment proposed here is that JARVIS's Brain should develop as **one coherent, evidence-sensitive cognitive system whose responsibilities own their state, coordinate through bounded shared context, and change through evaluated experience**.

The proposal is intentionally specific about cognitive responsibilities, authority, integration and developmental integrity, while remaining open about algorithms, concrete schemas, technologies and runtime construction. Those details must follow—not dictate—the approved architecture.

**End of document.**
