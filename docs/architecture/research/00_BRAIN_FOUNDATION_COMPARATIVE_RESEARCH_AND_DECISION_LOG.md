# Brain Foundation Comparative Research and Decision Log

**Status:** Working research record — not an approved architecture specification  
**Project:** JARVIS — Brain Foundation  
**Last updated:** 2026-11-01  
**Repository:** `methaneex-oss/MethaneX`  
**Working branch:** `docs/jarvis-system-architecture-foundation-20261101`  
**Purpose:** Preserve the research, comparisons, provisional choices, assumptions, unresolved questions and reasoning produced during Brain Foundation architecture investigation so the independent Reviewer can challenge the work.

---

## 1. Document authority and use

This is a living investigation record. It is being maintained so the Reviewer can inspect the reasoning as it develops, rather than receiving only a polished conclusion after decisions have already been made.

It is **not**:
- an approved Brain Foundation architecture;
- authorization to implement or modify runtime code;
- a replacement for the two already-approved whole-system architecture documents;
- evidence that any proposed mechanism exists in the repository or has been implemented;
- a claim that Marvel fiction or neuroscience supplies a complete technical blueprint.

The approved whole-system foundation and responsibility map remain the baseline. This investigation concerns the Brain only, within those already-defined whole-system boundaries.

### 1.1 Governing design principle

> **ENGINEER THE MECHANISMS; LET BEHAVIOR BE ACQUIRED THROUGH EXPERIENCE.**

The Brain Foundation must provide the cognitive machinery from which future capabilities can develop. It must not hardcode every advanced behaviour, personality response, emotion mapping, preference, or task-specific outcome into the foundation.

### 1.2 Comparative method — mandatory for every question

Every architectural question investigated in this work must receive two distinct reference solutions:

1. **Marvel J.A.R.V.I.S. reference:** identify the capability demonstrated in the fictional portrayal, the design lesson that can reasonably be extracted, and what cannot be inferred about its internal implementation.
2. **Human cognition reference:** identify relevant cognitive/neuroscience mechanisms and evidence, distinguishing well-supported findings from hypotheses, incomplete explanations and open scientific questions.

Then:
3. Compare the two solutions against the actual engineering problem.
4. Select the stronger solution for JARVIS, or an explicitly justified combination if neither alone is adequate.
5. Explain why it is superior, what advantage it provides, and what limitations must not be copied.
6. Record unresolved questions and evidence needed before the architecture is approved.

The selection is not automatically a 50/50 blend. If one reference offers the better mechanism, choose it. If both are insufficient, state that and develop an engineering solution informed by the useful parts of each. Do not manufacture equivalence merely to make the comparison symmetrical.

### 1.3 Evidence discipline

- Marvel J.A.R.V.I.S. is fictional. Its stories show capabilities and interactions, not a canonical technical architecture. Do not claim to know its hidden implementation.
- Human cognition is a biological reference, not a software specification. Human mechanisms are distributed, context-dependent and not fully understood. Do not turn a neuroscience theory into an established fact.
- Clearly label facts, interpretations, engineering proposals and decisions.
- A proposed mechanism is not a settled decision until its boundaries, contracts, failure behaviour and evaluation criteria have been examined.
- Preserve disagreements, rejected options and uncertainty. Do not erase earlier reasoning when a decision changes; record the revision and why it changed.

---

## 2. Initial scope and working boundaries

The Brain is responsible for cognitive work such as experience processing, representation, memory, belief and knowledge formation, prediction, evaluation, learning and adaptation, reasoning and decision-making, and cognitive self-monitoring.

It does not take ownership of sensory acquisition, external interaction interfaces, actual motor/tool execution, system-wide signalling, homeostatic regulation, security enforcement, governance authority, or external training/release infrastructure. It interfaces with those systems through explicit contracts.

The foundation is intended to enable future advanced mechanisms. It is not intended to contain a hardcoded catalogue of all future capabilities.

No runtime implementation is authorized by this research record.

---

## 3. Comparative investigation — questions already examined

The following are the first five integration questions examined. These are **provisional findings**. They are not final design approvals.

## Q1. How does information become part of the Brain's current understanding?

### Marvel J.A.R.V.I.S. reference

The fictional portrayal demonstrates contextual interpretation and the use of information in relation to Tony Stark's ongoing projects, equipment and intentions. The U.S. Department of Defense human-machine teaming workshop report discusses a J.A.R.V.I.S. example in which a question is interpreted as an implicit instruction based on context and likely intent.

**Extractable design lesson:** information should not be processed as isolated text or sensor values only. It must be interpreted in relation to the current situation, the user's apparent goal, relevant history and the surrounding system context.

**Limitation:** the fictional portrayal does not specify a verifiable pipeline for observations, interpretation, belief formation, memory, evidence weighting or revision. We cannot infer that J.A.R.V.I.S. uses any particular database, representation or learning algorithm.

### Human cognition reference

Human cognition distinguishes temporary active information from long-term knowledge and memory. Working memory uses temporarily selected representations drawn from recent perception and long-term memory; attention and memory interact rather than operating as isolated boxes. Memory is also dynamic: consolidation can selectively stabilize and transform experience to support future behaviour.

**Extractable design lesson:** current understanding should not be a single undifferentiated store. Active context, retained experience, structured representations and current beliefs have different roles and different persistence/revision requirements.

**Limitation:** working memory is not simply a software cache, and biological memory is reconstructive and fallible. JARVIS should preserve historical evidence more reliably than human recollection where the system's storage and privacy rules permit.

### Comparison and provisional selection

**Selected direction: a human-cognition-informed, explicitly engineered information lifecycle, with Marvel-style contextual interpretation as a required capability.**

The human reference gives the stronger conceptual separation between active context, retained memory and long-term knowledge. Marvel contributes a useful system-level requirement: interpretation must be context-sensitive and useful in the live situation.

Provisional information classes to keep distinct:
- original experience/observation;
- interpretation or hypothesis;
- representation of entities, events, concepts and relationships;
- belief or knowledge claim with epistemic status;
- working cognitive context;
- prediction and its assumptions;
- valuation/evaluation;
- decision or intention;
- verified action outcome;
- candidate and activated learning/adaptation.

These are information classes and ownership responsibilities, not a mandatory linear pipeline. They may coexist, branch, recur and revise one another. An interpretation must not rewrite the original observation. A new observation may cause a belief or representation to be reconsidered without falsifying the historical record.

**Advantage of the selection:** better traceability, clearer ownership, controlled revision and reduced risk of confusing raw evidence with current interpretation.

**Still unresolved:** exact lifecycle states, authoritative owners, persistence rules, dependency invalidation and how different information classes are exchanged.

## Q2. How can concurrent learning and adaptation processes avoid interfering with one another?

### Marvel J.A.R.V.I.S. reference

The fictional system is portrayed as integrated across Stark's technology and able to coordinate multiple functions in a coherent operational environment.

**Extractable design lesson:** cognitive subsystems and external systems must behave as a coordinated whole; local activity cannot be allowed to produce incoherent system-wide behaviour.

**Limitation:** Marvel's portrayal does not provide a technically grounded account of concurrent learning jobs, model versioning, conflicting updates, transactional commits, rollback or adaptation isolation. It is not evidence for a specific concurrency-control design.

### Human cognition reference

Human memory research describes selective consolidation: recent experience is not indiscriminately transferred into stable long-term memory. Consolidation can stabilize selected information and transform memory representations in ways that support later generalization. Research on complementary learning systems also highlights the tension between retaining specific experiences and extracting general structure; unregulated transfer can impair generalization.

**Extractable design lesson:** new experience and candidate learning should not automatically overwrite established cognitive structures. Integration should be selective and sensitive to interference and generalization.

**Limitation:** biological consolidation is not equivalent to parallel software training jobs. It does not directly specify locks, transactions, conflict resolution or safe model deployment.

### Comparison and provisional selection

**Selected direction: selective, staged and versioned adaptation, informed by human consolidation and implemented with explicit software consistency controls.**

Candidate adaptations should be produced without immediately changing authoritative active behaviour. They should be assessed for evidence quality, compatibility, interference, regression, transfer and resource cost. Compatible changes may be integrated; conflicting changes may remain separate, be deferred or be rejected. Activation must be controlled, traceable and recoverable.

Marvel contributes the system-level requirement that independently operating capabilities remain coordinated, but the human reference gives the better learning principle.

**Advantage of the selection:** prevents simultaneous learning activity from silently corrupting active cognition and supports controlled developmental progress.

**Still unresolved:** conflict/merge policy, evaluation thresholds, atomic activation, stale candidate detection, concurrent reads during activation, rollback semantics and recovery after interruption.

## Q3. How does the Brain know when to stop thinking, conclude, ask for information or defer?

### Marvel J.A.R.V.I.S. reference

The fictional portrayal demonstrates timely, context-sensitive assistance: J.A.R.V.I.S. is expected to provide relevant information and act in the context of the ongoing situation rather than continue analysis without regard to the task.

**Extractable design lesson:** cognition must remain responsive to operational context, urgency and the needs of the current task.

**Limitation:** fiction does not give us a rigorous stopping criterion, calibrated confidence model, computation budget or method for trading further reasoning against delay and risk.

### Human cognition reference

Research on cognitive control describes flexible selection of behaviour based on context and monitoring of ongoing behaviour so it can be adjusted. Human attention and working memory are limited, and cognitive control supports shifting strategies as circumstances change.

**Extractable design lesson:** ongoing cognition needs monitoring and regulation; continuing the same process is not always the best response.

**Limitation:** human limits are not automatically desirable design targets. Neuroscience does not supply a universal numeric threshold for when an artificial cognitive process should stop.

### Comparison and provisional selection

**Selected direction: engineered, consequence-sensitive stopping and suspension criteria, informed by human cognitive control and constrained by operational requirements.**

Possible outcomes must include:
- conclude with an adequately supported result;
- provide a provisional result with explicit uncertainty;
- request missing information;
- continue because further processing has expected value;
- suspend and preserve state for later resumption;
- present competing alternatives;
- defer or decline a decision when evidence is insufficient.

The decision should consider evidence sufficiency, uncertainty, expected value of further analysis, consequence of error, time constraints and available resources. The process must support interruption and resumption without losing causal or reasoning context.

**Advantage of the selection:** avoids both endless analysis and premature certainty; permits different stopping standards for low-consequence and high-consequence decisions.

**Still unresolved:** operational definitions of evidence sufficiency, calibrated confidence, expected value of additional reasoning, consequence classes, budget enforcement and how to avoid arbitrary universal thresholds.

## Q4. How can identity and development remain continuous while the Brain changes?

### Marvel J.A.R.V.I.S. reference

The fictional portrayal presents a recognisable continuing assistant identity across changing tasks, equipment and technological environments. The system is portrayed as having a continuing relationship and role, rather than appearing as a completely unrelated assistant for every task.

**Extractable design lesson:** continuity should be visible across changing operational contexts and capabilities.

**Limitation:** fictional continuity does not explain how identity is represented, persisted, recovered, versioned or reconciled across copies, backups or forks. It is not evidence for a particular self-model or memory design.

### Human cognition reference

Autobiographical memory integrates past experiences into a life narrative and is associated with a subjective sense of continuity over time. Research also cautions that autobiographical memory is dynamic and that the evidence for some proposed functions is not uniformly strong.

**Extractable design lesson:** continuity depends on relationships among remembered experience, current self-representation and the history of change; it is not merely a static name or configuration file.

**Limitation:** human identity is socially, culturally and biologically grounded. It should not be reduced to a software identity database or copied literally.

### Comparison and provisional selection

**Selected direction: a hybrid, with explicit engineered identity lineage and human-inspired autobiographical/developmental continuity.**

Keep distinct:
1. system identity and instance lineage;
2. historical experience and significant developmental events;
3. acquired capabilities and their versions;
4. current cognitive state;
5. revisable self-model.

Development must be allowed to change capabilities and self-understanding without erasing historical lineage. Restoring an earlier operational version must not pretend later experiences never happened. Forking, cloning and multi-instance identity require explicit policy rather than accidental behaviour.

**Advantage of the selection:** continuity is preserved without freezing the Brain's development.

**Still unresolved:** which identity properties are invariant, which are revisable, how forks and restored snapshots relate to the original lineage, and how self-model claims are validated.

## Q5. How should integration and developmental capability be tested?

### Marvel J.A.R.V.I.S. reference

The fictional portrayal gives an end-to-end performance target: an assistant should coordinate information, reasoning and actions across interconnected technologies in changing situations, while remaining useful to its human collaborator.

**Extractable design lesson:** isolated component tests are insufficient. The complete system must be evaluated under realistic, multi-system tasks and changing circumstances.

**Limitation:** cinematic success is not a test methodology. Fiction does not provide reproducible test oracles, coverage criteria, adversarial test design or evidence of robust learning.

### Human cognition reference

Human cognition research studies interacting processes such as attention, working memory, long-term memory, cognitive control, prediction and learning. The evidence supports investigating their interactions rather than treating each process as independent. However, the brain's full integration architecture remains an active scientific question.

**Extractable design lesson:** test both individual mechanism integrity and cross-mechanism interactions, including feedback, interference, limits and adaptation over time.

**Limitation:** human behavioural experiments do not directly translate into software acceptance tests, and observed human performance is not automatically the correct performance target.

### Comparison and provisional selection

**Selected direction: a layered engineering test strategy combining human-inspired mechanism interaction tests with Marvel-inspired end-to-end operational scenarios.**

Four provisional test levels:
1. **Mechanism integrity:** each mechanism respects its contract and handles its own failure modes.
2. **Integration integrity:** information ownership, provenance, uncertainty, causal links and update boundaries survive cross-mechanism use.
3. **Cognitive stability:** contradictions, concurrent updates, feedback loops, delayed/out-of-order experiences, partial failures and changing contexts do not produce uncontrolled incoherence.
4. **Developmental capability:** experience produces persistent, measurable improvement that transfers to novel but related situations without test-specific hardcoding or unacceptable regression.

A genuine learning claim requires evidence of persistent experience-dependent change, later behavioural effect and transfer—not merely stored data, passing unit tests or a subsystem reporting that it learned.

**Advantage of the selection:** provides both scientific/mechanistic scrutiny and realistic whole-system performance evaluation.

**Still unresolved:** benchmark design, independent test data, baseline comparisons, transfer criteria, regression tolerance, longitudinal testing and how to detect test-specific hardcoding.

---

## 4. Cross-question findings and risks

The first five questions expose several concerns that cut across multiple mechanisms. These must be carried into subsequent investigations.

### 4.1 Circular evidence and self-reinforcing conclusions

A belief, interpretation or prediction derived from an earlier source must not later be counted as independent corroboration of that same source. Evidence lineage must preserve derivation and dependency.

### 4.2 Feedback instability

Attention, valuation, belief, prediction and learning can influence one another. Positive feedback may amplify a mistaken interpretation or an irrelevant signal. The Brain needs ways to detect, monitor and regulate unstable feedback without imposing one central intelligence controller.

### 4.3 Delayed and out-of-order experience

Preserve event time separately from processing/arrival time. Late evidence may require reinterpretation of current beliefs and predictions, but must not rewrite the original event history.

### 4.4 Partial cognitive failure

A failure during a multi-mechanism update must not leave the Brain in a partially committed state. Recovery needs to distinguish committed knowledge/adaptation from incomplete work and must not duplicate experience or erase committed learning.

### 4.5 Local validity versus global coherence

A mechanism may produce a locally valid update that makes dependent predictions, beliefs or plans stale. The Brain needs dependency awareness and selective re-evaluation rather than assuming that every locally valid update leaves the whole system coherent.

### 4.6 Separation of historical evidence and current understanding

Original experiences should be retained separately from revisable interpretations, representations and beliefs. Current understanding can change; historical evidence should not silently change with it.

---

## 5. Provisional integrated direction

The following is a synthesis of the current findings, not a frozen architecture:

- Use distributed cognitive mechanisms with explicit responsibility and authoritative state ownership.
- Establish shared information contracts that preserve identity, provenance, context, version, uncertainty and causal dependencies.
- Maintain a dynamic working cognitive context that selectively exposes information for current processing.
- Coordinate through controlled events, requests and updates rather than forcing every mechanism into one rigid global sequence.
- Track dependencies so that affected derived outputs can be reconsidered when upstream evidence or beliefs change.
- Stage and validate learning/adaptation before controlled activation.
- Preserve recoverable developmental history and distinguish historical experience from current cognitive state.
- Test mechanisms, integration, stability and persistent transfer separately.

This does not yet determine the final component boundaries, process topology, database, storage technology, programming languages, communication protocol or consistency model. Those choices must follow the mechanism and contract analysis rather than precede it.

---

## 6. Next investigation sequence

The next investigation should address the most foundational unresolved area first.

### Investigation A — Cognitive information lifecycle and ownership

For every information class, determine:
- definition and purpose;
- authoritative owner;
- origin and provenance requirements;
- whether it is immutable, append-only, revisable, ephemeral or candidate state;
- persistence and recovery requirements;
- versioning and dependency rules;
- who may read, propose, validate, update or commit it;
- lifecycle transitions, branches, loops and invalidation conditions;
- failure and conflict behaviour.

Information classes to examine include raw observations/experience events, interpretations, representational structures, beliefs/knowledge claims, predictions, valuations, decisions/intentions, action outcomes, learned adaptations, working context and metacognitive assessments.

A single universal pipeline or database must not be assumed. Event history, owner-managed current state, materialized views, snapshots and candidate adaptations may have different requirements.

### Investigation B — Cognitive coordination and consistency

Examine:
- concurrent mechanism activity;
- stale reads and conflicting updates;
- causal ordering and event-time versus processing-time;
- local versus cross-mechanism consistency;
- dependency tracking and selective invalidation;
- feedback stability;
- interruption, retries, duplicate delivery and partial failure.

### Investigation C — Developmental integrity

Examine:
- learning candidate isolation;
- compatibility and interference assessment;
- controlled integration and activation;
- versioning, rollback and recovery;
- continual learning and catastrophic forgetting;
- transfer, regression and negative transfer;
- preservation of developmental lineage.

After these investigations, consolidate the Brain Foundation architecture and challenge it with realistic failure scenarios before requesting final Project Director approval.

---

## 7. Reviewer instructions

The independent Reviewer should treat this file as an active challenge target, not as a request to approve the proposed direction automatically.

For each question and proposed selection, challenge:
- whether the Marvel example is actually supported by the cited fictional source;
- whether the human mechanism is accurately represented and whether the evidence is strong enough;
- whether the comparison is fair or uses a false equivalence;
- whether the selected engineering direction follows from the evidence;
- whether a stronger alternative has been missed;
- whether the proposal introduces hidden centralization, hardcoding, arbitrary thresholds or unsafe authority;
- whether boundaries and ownership are precise enough to implement later;
- whether failure, recovery, concurrency and testing have been adequately considered.

The Reviewer should identify unsupported claims, missing mechanisms, contradictions, overgeneralizations and unresolved assumptions. A disagreement should be recorded and answered with evidence or a revised proposal, not dismissed to preserve the current draft.

**No architecture approval, implementation authorization or PR merge approval is implied by this document.**

---

## 8. Research references

The following sources support the current research notes. Marvel sources are used only for fictional portrayal; scientific sources are used for the specific cognitive findings described above.

### Marvel and human-machine teaming
- Marvel, [Every Major A.I. in the Marvel Universe](https://www.marvel.com/comics/discover/2500/every-major-a-i-in-the-marvel-universe). Official fictional-universe overview; does not disclose a technical implementation.
- Marvel, [Iron Man — Tony Stark, In Comics](https://www.marvel.com/characters/iron-man-tony-stark/in-comics). Describes capabilities associated with Iron Man suits, including AI-assisted piloting and communications.
- U.S. Department of Defense, [Future Human-Machine Team Scenarios — Workshop Report](https://basicresearch.defense.gov/Portals/61/Future%20Directions%20in%20Human%20Machine%20Teaming%20Workshop%20report%20%20%28for%20public%20release%29_1.pdf), 15 January 2020. Includes an analysis of a J.A.R.V.I.S. interaction and broader human-machine teaming scenarios. It is a workshop report, not a canonical Marvel technical specification.

### Human cognition, attention, memory and learning
- Cowan et al., [The Relation Between Attention and Memory](https://www.annualreviews.org/content/journals/10.1146/annurev-psych-040723-012736), Annual Review of Psychology, 2024.
- Postle and Oberauer, [Working Memory: Theoretical, Computational, and Neural Considerations](https://academic.oup.com/edited-volume/57928/chapter-abstract/475474310), 2024.
- Cowan et al., [Memory Consolidation as an Adaptive Process](https://pubmed.ncbi.nlm.nih.gov/34327677/), Psychonomic Bulletin & Review, 2021.
- Sun et al., [Organizing Memories for Generalization in Complementary Learning Systems](https://www.nature.com/articles/s41593-023-01382-9), Nature Neuroscience, 2023.
- Badre, [Cognitive Control](https://www.annualreviews.org/content/journals/10.1146/annurev-psych-022024-103901), Annual Review of Psychology, 2025.
- Fivush, [The Development of Autobiographical Memory](https://www.annualreviews.org/content/journals/10.1146/annurev.psych.121208.131702), Annual Review of Psychology, 2011.
- Sow, Dijkstra and Janssen, [Developments in the Functions of Autobiographical Memory: An Advanced Review](https://pubmed.ncbi.nlm.nih.gov/36165349/), 2022.

---

## 9. Change log

### 2026-11-01 — Initial comparative record
- Established the mandatory two-reference method: Marvel J.A.R.V.I.S. and human cognition for every architectural question.
- Added provisional comparative analyses for five integration questions: information entering current understanding; concurrent learning; stopping cognition; identity and continuity; and integration testing.
- Recorded a provisional selection and rationale for each question.
- Captured cross-cutting risks and the next investigation sequence.
- Explicitly marked the document as working research, not an approved architecture or implementation authorization.
