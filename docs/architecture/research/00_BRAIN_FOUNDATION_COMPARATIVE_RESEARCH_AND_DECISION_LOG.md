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


---

## 10. Investigation A — Cognitive Information Lifecycle and Ownership

**Investigation status:** Initial analysis complete; proposed ownership model requires Reviewer challenge.  
**Date:** 2026-11-01  
**Decision status:** Provisional engineering direction, not approved architecture.

### 10.1 The actual problem

The Brain will continuously receive experience, form interpretations, construct representations, update beliefs, make predictions, evaluate outcomes, decide and learn. These activities can occur concurrently and can revisit earlier information.

The central design problem is not simply where to store information. It is:

> **How can the Brain preserve what happened, maintain what it currently thinks, and allow that understanding to change without confusing evidence, interpretation, belief, prediction or learned behaviour?**

If these distinctions are weak, several serious defects become likely:
- an inference is later mistaken for a directly observed fact;
- a generated or simulated event is remembered as something that actually happened;
- a source's identity and reliability are lost as information moves between mechanisms;
- one mechanism silently overwrites another mechanism's authoritative state;
- a belief changes but dependent predictions and plans continue using stale assumptions;
- contradictory evidence is erased instead of evaluated;
- a crash leaves a partially applied cognitive update;
- repeated copies of the same source are incorrectly treated as independent corroboration.

### 10.2 Marvel J.A.R.V.I.S. reference

The fictional J.A.R.V.I.S. portrayal demonstrates contextual assistance: information is useful because it is interpreted in relation to Tony Stark, his current task, his technology and the surrounding situation. The DoD human-machine teaming workshop's discussion of a J.A.R.V.I.S. interaction illustrates interpretation of an implicit request from contextual cues.

**What this suggests for engineering**
- Information must retain enough context to be interpreted in the situation in which it is used.
- A useful assistant needs to connect incoming information with relevant prior information and current goals.
- Information should be available across coordinated capabilities without every capability independently inventing its meaning.
- The system should be able to act on contextually interpreted information, not merely retrieve isolated records.

**What Marvel does not answer**
- Whether the fictional system distinguishes raw observation from inference.
- How it records provenance, confidence, uncertainty or conflicting sources.
- How it revises a prior belief without changing the historical record.
- How it prevents a generated simulation from being mistaken for an actual event.
- How information ownership, concurrency, transactions or recovery work internally.

**Conclusion from this reference:** adopt contextual integration as a capability requirement, but do not copy an imagined internal architecture. The fiction does not supply a reliable data-lifecycle or ownership model.

### 10.3 Human cognition reference

Human memory and cognition provide several relevant, but non-identical, mechanisms:

1. **Episodic memory** supports memory for particular events with contextual details. The hippocampus is strongly implicated in episodic memory, although the full neural basis of memory is distributed and remains an active research area. A 2024 review discusses hippocampal roles beyond the traditional long-term-memory-only account, including evidence relevant to working memory and perception.  
   Source: Hawkins and Yonelinas, 2024.

2. **Working memory and attention** support temporary use of information relevant to ongoing cognition. Working memory is not simply a separate permanent store; it interacts with attention, perception and long-term memory. Its exact neural implementation is debated.

3. **Consolidation and transformation** mean retained experience is not necessarily a frozen copy. Research describes multiple representations and changing degrees of detail and generalization across encoding, consolidation and retrieval. The 2025 review on adaptive episodic memory discusses context-specific and gist-like representations that can coexist and influence later behaviour.

4. **Source monitoring** concerns how a person attributes remembered information to a source or mental process—for example, distinguishing what was perceived, heard, inferred, imagined or suggested. Human source monitoring is fallible. This is an important warning: JARVIS must not rely on familiarity or plausibility alone to establish whether something was observed or inferred.

5. **Correction and belief updating** depend partly on remembering the source and correction. A 2024 review reports that correction effectiveness can decline when the source of information is not remembered. This supports preserving source/provenance as part of the information record rather than treating it as disposable metadata.

**What human cognition suggests**
- Preserve episodic/contextual detail where it has future evidential value.
- Maintain temporary working context separately from durable retained information.
- Permit derived abstractions and generalizations without treating them as the original experience.
- Track source and the distinction between perception, inference and imagination.
- Allow memory and understanding to update, but do not confuse reconstructive memory with an authoritative historical log.

**What must not be copied**
- Human memory distortion, forgetting and source confusion are limitations, not design goals.
- A biological memory trace is not a software record or database row.
- The hippocampus is not a literal central event database; biological memory involves distributed representations and interacting systems.
- Current neuroscience does not settle one universal architecture for all forms of memory and cognition.

### 10.4 Comparison and selection

**Selected direction: an engineered provenance-preserving information lifecycle, using human memory distinctions as the stronger structural reference and Marvel-style contextual integration as the operational requirement.**

Why this is stronger:
- Human cognition provides useful distinctions among episodic experience, active working context, and transformed/generalized memory.
- Source-monitoring research directly exposes the danger of confusing observed, inferred and imagined information.
- Marvel adds the requirement that these distinct information types must still be integrated into timely, context-sensitive assistance.
- Engineering can improve on biological weaknesses by preserving immutable source records, explicit derivation links and auditable revision history.

This is not a 50/50 blend. The human reference is stronger for information-class separation and lifecycle design. The Marvel reference is stronger as a whole-system capability target for contextual use.

### 10.5 Proposed information classes and authoritative ownership

The following is a proposed ownership map. Ownership means the mechanism accountable for the authoritative state and rules of that information class. It does not imply a separate process, service, database or programming-language module.

| Information class | Proposed authoritative owner | Mutability / lifecycle | Key rule |
|---|---|---|---|
| Original experience record | Experience Integration / experience-record responsibility | Append-only historical record; corrections are new linked records or annotations | Never rewrite what was originally received |
| Source and provenance | Experience Integration, with provenance preserved by every downstream consumer | Immutable source facts; quality assessments may be revised as new evidence arrives | Never detach a claim from its source/derivation |
| Interpretation / hypothesis | Reasoning and interpretation responsibility | Revisable, versioned, may coexist with alternatives | Never relabel an interpretation as an observation |
| Representation | Representation System | Revisable, versioned, derived from evidence and other representations | Preserve derivation links; invalidation must propagate to dependants |
| Belief / knowledge claim | Belief and Knowledge Formation | Revisable epistemic state with evidence and revision history | No silent overwrite; preserve supporting and opposing evidence |
| Working cognitive context | Working Context / cognitive state responsibility (exact owner to resolve) | Ephemeral and continuously changing; reconstructable where necessary | Active availability is not proof of truth or durable memory |
| Prediction / forecast | Prediction System | Versioned forecast; evaluated against later outcomes | Simulated futures must remain marked as non-events |
| Valuation / evaluation | Evaluation and Valuation responsibility | Revisable state tied to context, goals, evidence and uncertainty | No universal fixed score or hardcoded stimulus-to-emotion mapping |
| Decision / intention | Decision responsibility | State transitions with rationale, constraints and status | Decision is not authorization or execution |
| Action execution outcome | Motor/Action system owns execution record; Brain consumes verified outcome | Historical outcome record, with later corrections linked | Brain must distinguish intended action, attempted action and verified result |
| Candidate adaptation | Learning and Adaptation | Isolated, versioned, evaluable candidate | Candidate is not active cognitive authority |
| Activated learned adaptation | The mechanism whose model/strategy is changed owns its active state; Learning coordinates the change | Versioned active state with lineage and recovery path | Learning coordinates; it does not become owner of every mechanism's state |
| Metacognitive assessment | Metacognitive System | Revisable assessment with evidence and scope | Monitoring does not grant unrestricted control over mechanisms |

**Important ownership caveat:** some rows name functional responsibilities rather than settled components. For example, whether the original experience record is directly owned by Experience Integration or by a dedicated experience-history responsibility remains an architectural boundary decision. Do not create a component merely because the table contains an owner label.

### 10.6 Information lifecycle — not a rigid pipeline

The following lifecycle is conceptual. It is not a fixed execution sequence. Information may enter at different points, branch into competing interpretations, be revisited, or remain unresolved.

1. **Acquire / admit:** a sensory or external source supplies an experience payload. The Brain receives it through an agreed interface; the Brain does not own the sensory device or external acquisition process.
2. **Preserve the received event:** record the original payload or a faithful, integrity-protected reference to it, plus source identity, event time, arrival/processing time, modality, context and integrity metadata.
3. **Assess the input:** evaluate completeness, duplication, integrity, source quality and uncertainty. Do not silently discard an unclear event merely because it cannot yet be interpreted.
4. **Make available to cognition:** publish or expose the admitted experience through controlled contracts. This does not assert that every mechanism must process every event.
5. **Interpret and represent:** one or more cognitive processes may produce hypotheses, structured representations, relationships or abstractions. Each derived item records its dependencies.
6. **Evaluate epistemic status:** evidence is assessed; beliefs may be formed, withheld, qualified, supported, contradicted or revised.
7. **Use in active cognition:** relevant items may enter working context, support predictions, reasoning, evaluation and decisions. Working-context inclusion is not a truth judgement.
8. **Compare against outcomes:** later experience may confirm, weaken or contradict predictions and beliefs. The original experience remains unchanged; derived states may be revised.
9. **Consolidate and learn:** selected information may be retained, generalized, used to alter a model or strategy, or left as a candidate pending evaluation. Memory retention is not itself proof of learning.
10. **Revisit / invalidate:** new evidence or changed assumptions may cause dependent representations, beliefs, predictions or plans to be marked stale and reconsidered.

This model permits loops and branches. For example, a new interpretation can be generated from old experience; a belief conflict can trigger retrieval; a prediction error can initiate learning evaluation; a revised model can produce a new prediction. No single global sequence is imposed.

### 10.7 Worked example — uncertain vehicle observation

Assume a sensory system reports an image of a vehicle approaching a secured entrance.

**Initial experience**
- The original image payload or its integrity-protected reference is retained.
- Source device, event timestamp, receipt timestamp, location/context and sensor-quality metadata are attached.
- The experience record states only what was received. It does not state that the vehicle is hostile.

**Competing interpretations**
- Interpretation A: the vehicle may be an authorized delivery.
- Interpretation B: the vehicle may be an unknown visitor.
- Interpretation C: the image may be too poor to classify reliably.

All three remain interpretations, not historical observations. Their confidence and evidence basis may differ.

**Representation and belief**
- Representation may identify a vehicle, entrance, time and spatial relation.
- Belief formation may conclude only that a vehicle is present, while withholding a claim about authorization.
- If an access-control source later supplies a matching delivery record, that is additional evidence with its own provenance. It is not independent corroboration if it merely repeats the original image's inferred label.

**Prediction and decision**
- Prediction may forecast possible arrival or access outcomes under each interpretation.
- Brain may form an intention to request further information or recommend verification.
- It must not treat its own belief as governance authorization to open the entrance.

**New evidence**
- A later authorized credential check contradicts the delivery interpretation.
- The original image and initial interpretations remain in history.
- The belief is revised; dependent predictions and plans are marked stale and reconsidered.
- The system records why the earlier interpretation changed.

**What this example tests**
- Observation/inference separation.
- Competing hypotheses.
- Provenance retention.
- Circular-evidence prevention.
- Belief revision without historical rewriting.
- Dependency invalidation.
- Decision/authorization separation.

### 10.8 State categories and persistence proposal

Do not collapse all information into one storage policy. At minimum, distinguish:

- **Historical evidence:** durable, append-only or immutable-by-contract; corrections represented by linked events/annotations.
- **Revisable derived state:** versioned and attributable to the evidence and assumptions from which it was produced.
- **Ephemeral working state:** temporary; may be discarded or reconstructed subject to continuity requirements.
- **Candidate state:** isolated and not authoritative until accepted through a controlled process.
- **Operational recovery state:** checkpoints and transaction metadata needed to resume safely; not equivalent to memory or knowledge.
- **Materialized views/indexes:** rebuildable convenience structures, not authoritative evidence unless explicitly designated otherwise.

An event-history approach may help preserve changes and causal lineage, but this investigation does **not** select event sourcing, a particular database, a single global event store or a universal consistency model. Those are implementation choices to evaluate after contracts and failure semantics are defined.

### 10.9 Dependency and staleness management

Derived cognitive information must declare what it depends on. Dependencies may include:
- source experience records;
- interpretations and assumptions;
- representation versions;
- belief versions;
- model/strategy versions;
- context and time validity;
- external facts or policy versions where relevant.

When a dependency changes, consumers should not automatically assume every downstream result is invalid. Instead:
1. identify affected derived items;
2. mark them as potentially stale;
3. determine whether the change is relevant to their assumptions;
4. re-evaluate, recompute, retain with qualification, or invalidate;
5. preserve the previous result and the reason for the update.

This is preferable to either extreme: no invalidation (stale cognition) or global invalidation after every update (unnecessary recomputation and instability).

### 10.10 Permissions and update authority

Provisional rules:
- Any mechanism may request or receive information only through defined contracts and access boundaries.
- A mechanism may propose a derived item, but only its designated owner may commit authoritative state for that information class.
- Downstream mechanisms may attach feedback or challenge evidence; they do not directly overwrite another mechanism's state.
- Historical experience cannot be edited by an interpretation, belief or learning process.
- A candidate adaptation cannot become active merely because it was generated.
- External action results must be distinguished from Brain intentions and must be verified by the responsible execution/outcome path.
- Governance and security authority remain outside Brain cognitive ownership as defined in the whole-system architecture.

These are ownership principles, not a complete access-control or transaction protocol.

### 10.11 Failure cases the eventual design must handle

1. Duplicate delivery of the same experience event.
2. Same event received from two sources with differing quality.
3. Delayed event arriving after a belief or plan has already been formed.
4. Source identity unavailable or later found incorrect.
5. A derived interpretation accidentally written into an observation field.
6. Conflicting interpretations generated concurrently.
7. Belief update succeeds but dependent prediction invalidation fails.
8. Process crash between recording experience and distributing it.
9. A replay/retry duplicates a learning update.
10. A simulated event or imagined scenario is persisted as actual experience.
11. A source correction arrives after the original source has been used in multiple derived claims.
12. An information item becomes stale because its context or validity period has changed.

For each case, later architecture work must specify detection, containment, recovery, audit evidence and whether the operation is retryable.

### 10.12 Provisional decisions and explicit non-decisions

**Provisional directions selected**
- Preserve original experience separately from all derived understanding.
- Treat provenance and derivation as first-class information, not optional metadata.
- Keep observation, interpretation, representation, belief, prediction, decision and outcome distinct.
- Permit multiple interpretations and beliefs with different epistemic status.
- Keep working context distinct from durable memory.
- Give each authoritative information class a clear owner.
- Use versioned derived state and dependency-aware selective re-evaluation.
- Separate candidate adaptations from activated learned state.
- Preserve event time separately from processing/arrival time.

**Not decided yet**
- Whether experience history is a dedicated subsystem or a responsibility within Experience Integration.
- Whether a common envelope plus modality-specific payloads is the correct contract.
- Exact schemas, identifiers, clocks, ordering guarantees and causal metadata.
- Whether and where event sourcing is appropriate.
- Database, graph, vector, object or other storage technologies.
- Transaction boundaries and consistency guarantees.
- Exact retention, privacy, deletion and forgetting policies.
- Exact confidence/calibration representation.
- Exact rules for stale-state propagation and dependency evaluation.
- Exact process/service boundaries and programming languages.

### 10.13 Reviewer challenge checklist for this investigation

The Reviewer should specifically test:
- Are information classes separated for sound reasons, or have we over-fragmented them?
- Is every proposed authoritative owner actually the right owner?
- Does Experience Integration own the original record, or should a distinct experience-history responsibility exist?
- Can original evidence be preserved without requiring every raw modality payload to be stored indefinitely?
- Does the model preserve provenance through transformation, summarization, abstraction and retrieval?
- Are we distinguishing event time, processing time and causal order correctly?
- Can competing interpretations coexist without uncontrolled duplication?
- Is selective dependency invalidation practical, or does it introduce excessive complexity?
- Does the proposal accidentally turn the Brain into one centralized data authority?
- Are candidate adaptations, operational recovery state, memory and current beliefs sufficiently distinct?
- What information is lost if the original payload is too large, sensitive or transient to retain?
- Which of these rules are foundational invariants, and which are implementation policy?

### 10.14 Research references added for this investigation

- Hawkins, C. H. and Yonelinas, A. P. (2024), [Evolving perspectives of medial temporal memory function: hippocampal processes in visual and auditory forms of episodic and working memory](https://www.frontiersin.org/journals/cognition/articles/10.3389/fcogn.2024.1497281/full), *Frontiers in Cognition*. Review; some interpretations of hippocampal contribution beyond long-term episodic memory remain debated.
- Tarder-Stoll, H. et al. (2026 issue; published online 2025), [Adaptive episodic memory: how multiple memory representations drive behavior in humans and nonhumans](https://journals.physiology.org/doi/full/10.1152/physrev.00005.2025), *Physiological Reviews*. Review of multiple episodic representations, consolidation and adaptive retrieval.
- Kemp, P. L., Goldman, A. C. and Wahlheim, C. N. (2024), [On the role of memory in misinformation corrections: Repeated exposure, correction durability, and source credibility](https://pubmed.ncbi.nlm.nih.gov/38171060/), *Current Opinion in Psychology*. Review highlighting the role of source memory in durable correction.
- Johnson, M. K. (1997), [Source monitoring and memory distortion](https://pmc.ncbi.nlm.nih.gov/articles/PMC1692093/), *Philosophical Transactions of the Royal Society B*. Foundational review of source attribution and source confusion.
- U.S. Department of Defense (2020), [Future Human-Machine Team Scenarios — Workshop Report](https://basicresearch.defense.gov/Portals/61/Future%20Directions%20in%20Human%20Machine%20Teaming%20Workshop%20report%20%20%28for%20public%20release%29_1.pdf). Human-machine teaming report containing a contextual J.A.R.V.I.S. example; not a specification of fictional internal architecture.

### 10.15 Investigation A conclusion

The strongest current direction is not a single memory database or one universal information pipeline. It is a **provenance-preserving, owner-managed cognitive information model** in which historical experience, derived understanding, active context, forecasts, decisions, outcomes and adaptations remain distinguishable and traceable.

Human cognition supplies the stronger reference for separating episodic detail, active context, source attribution and transformed memory. Marvel J.A.R.V.I.S. supplies the operational requirement that information be integrated contextually and made useful across coordinated capabilities.

This direction is ready for independent challenge, but it is not yet approved architecture. The next investigation is **Cognitive Coordination and Consistency**, which must determine how these owners safely exchange and revise information under concurrency, delay, feedback and partial failure.


---

## 11. Project Director instruction — exhaustive problem discovery and Reviewer handoff

On 2026-11-01, the Project Director explicitly instructed the Architecture Partner to expose every problem, misunderstanding, ambiguity, risk, missing mechanism, unresolved dependency and potential failure discovered during Brain Foundation work; investigate and solve what can be solved through comparative research into Marvel J.A.R.V.I.S. and human cognition; and raise uncertain matters directly to the Project Director rather than silently guessing. The Director also instructed that **all work and findings must be documented for the independent Reviewer, including analysis that would otherwise remain informal or undocumented**.

### 11.1 Operating obligations

For every investigation and architectural activity:

1. **Discover before deciding.** Actively search for failure modes, edge cases, missing responsibilities, contradictory assumptions, boundary leaks, hidden dependencies, operational constraints and test gaps. Do not limit the investigation to the questions already listed in this document.
2. **Use both reference lenses.** Examine the relevant Marvel J.A.R.V.I.S. portrayal and human cognitive science separately. State what each genuinely supports and what neither can establish.
3. **Engineer where the references are insufficient.** Neither fiction nor biology is required to contain the complete answer. Where both are inadequate, develop and justify an engineering solution; explicitly label it as such.
4. **Resolve what can be resolved.** Provide a reasoned provisional or final recommendation, with trade-offs, failure semantics and evidence requirements. Do not leave a solvable issue as a vague open question.
5. **Escalate real decisions.** Ask the Project Director when a decision depends on project intent, acceptable risk, authority, identity, privacy, resource limits, desired capability, or a trade-off that cannot responsibly be inferred. Do not ask the Director to decide routine engineering details that can be justified by evidence.
6. **Record uncertainty honestly.** Mark what is established, inferred, proposed, provisionally selected, rejected, unresolved, or awaiting Director decision. Never present uncertainty as certainty.
7. **Maintain a complete audit trail.** Record findings, alternatives, rejected approaches, assumptions, corrections, source references, decision rationale, failure scenarios, test implications and changes of mind in this document. If analysis occurs outside the document, transfer its material conclusions and relevant reasoning here before treating the work as complete.
8. **Keep the Reviewer continuously informed.** Each meaningful research update must identify the new or revised sections and explicitly ask the independent Reviewer to challenge them. The Reviewer must be able to reconstruct not only the conclusion but why it was reached.
9. **Do not silently expand authority.** This instruction authorizes exhaustive architecture research and documentation only. It does not authorize runtime implementation, changes to approved system boundaries, deletion/migration of existing code, or merging the PR.
10. **Preserve scope.** Brain Foundation remains the subject. Distinguish Brain-internal coordination from SYS-02 system-wide signalling and coordination, and distinguish cognitive decision from governance authorization and external execution.

### 11.2 Required issue record

Each material issue should be recorded with, where applicable:
- unique issue/question identifier and affected mechanisms/boundaries;
- concrete scenario that exposes the problem;
- consequence if left unresolved;
- Marvel reference and limits;
- human-cognition reference and limits;
- candidate engineering solutions and comparative evaluation;
- selected direction and why;
- rejected alternatives and their failure modes;
- invariants versus policy/implementation choices;
- unresolved facts, assumptions and confidence;
- whether Project Director input is required;
- acceptance/evaluation criteria and adversarial tests;
- Reviewer challenge questions;
- source references and date investigated.

A single investigation may identify many issues. Do not force them into one artificial question if their causes or solutions differ.

### 11.3 Director escalation rule

When uncertain, do not conceal uncertainty or make a unilateral project-level decision. Present the exact ambiguity, the viable alternatives, the consequences of each, the recommendation (if evidence supports one), and the specific decision required from the Project Director. If no Director decision is currently needed, say so rather than manufacturing a question.

---

## 12. Investigation B — Cognitive Coordination and Consistency

**Status:** Initial comparative investigation recorded; detailed mechanism contracts and acceptance criteria remain open.  
**Question:** How can multiple cognitive mechanisms operate concurrently, exchange information and revise their own authoritative state while preserving a coherent, traceable and recoverable overall cognitive state?

### 12.1 Problem statement

The Brain cannot be assumed to operate as one serial pipeline. Perception-derived experience may be interpreted while memory is retrieved, predictions are generated, attention is reallocated, beliefs are revised and learning evaluates prior outcomes. These activities may overlap, interrupt one another, receive delayed information and produce competing results.

The problem is not simply “how to synchronize threads.” It includes:
- who owns each state and may commit changes;
- how a consumer knows which versions and assumptions it used;
- how causality is represented when messages arrive late or out of order;
- how concurrent but independent updates coexist;
- how genuinely conflicting updates are detected and resolved;
- which information requires immediate consistency and which can tolerate temporary divergence;
- how stale conclusions are detected without recomputing everything;
- how feedback loops are bounded and instability detected;
- how interruption, retry, duplication, crash and recovery affect cognitive state;
- how partial failure is represented without pretending the whole Brain is either fully operational or fully unavailable.

### 12.2 Marvel J.A.R.V.I.S. reference

The Marvel portrayal shows J.A.R.V.I.S. coordinating information and functions across Stark's workshop, home systems, suits and mission contexts. It presents an integrated assistant whose separate capabilities contribute to coherent assistance under changing circumstances. The official Marvel character and Iron Man material describes suit intelligence, situational information and integrated technology capabilities, but remains a fictional capability portrayal.

**Extractable lesson:** coordination must preserve coherent context across concurrent capabilities; a subsystem's local success is not enough if the combined system behaves inconsistently.

**Limits:** Marvel does not provide an inspectable specification for internal scheduling, message delivery, causal ordering, state ownership, conflict resolution, synchronization, transaction boundaries, recovery or consistency guarantees. No particular distributed-systems architecture can be attributed to fictional J.A.R.V.I.S.

### 12.3 Human cognition reference

Research on cognitive control describes coordination emerging from distributed neural activity and hierarchical control networks. A 2024 review of multimodal neuroimaging discusses hierarchical organization and multiplexed control signals across distinct frontoparietal networks. A 2024 network-neuroscience study reports task-specific network configurations associated with working memory and inhibitory control, rather than one identical network configuration for every cognitive demand.

**Extractable lesson:** cognitive coordination is dynamic and context-sensitive; distinct functions can rely on different but interacting network configurations. This cautions against assuming every cognitive operation must pass through one universal central controller or one fixed processing sequence.

**Limits:** neuroscience does not yet provide a complete, settled explanation of global cognitive coordination. Neural networks are not software services, and biological synchrony does not prescribe software locks, queues, event buses, actors, transactions or consensus protocols. Human cognition can also exhibit interference, lapses and inconsistent representations; those are not design goals.

### 12.4 Engineering reference and implications

Distributed-systems engineering makes failure assumptions explicit: messages can be delayed, duplicated, reordered or lost; components can pause, crash and recover; and concurrent operations may not have a single total order. Consistency is not a binary universal property: stronger coordination has costs, while asynchronous/event-driven designs introduce temporary divergence and require explicit handling of delivery, replay and recovery.

Microsoft's architecture guidance on event-driven systems specifically warns that asynchronous consumers can observe eventual rather than immediate consistency; broker-style decoupling can create data inconsistency and replay/recovery complexity, while mediator-style coordination adds control but risks coupling and bottlenecks.

These engineering sources are not substitutes for the two required reference lenses. They are necessary because Marvel and neuroscience do not specify the software correctness mechanisms needed to implement a reliable cognitive system.

### 12.5 Comparison and provisional selection

**Provisional selected direction: distributed, owner-managed cognitive mechanisms coordinated through explicit contracts and causal/version metadata, with selective coordination strength based on the meaning and consequence of each state transition.**

This is not a proposal for fully decentralized cognition, nor for one central controller that owns all thought. It combines:
- human-inspired distributed, context-dependent coordination;
- Marvel-inspired requirement for integrated, coherent assistance;
- explicit software contracts and failure semantics from distributed-systems engineering.

The Brain should not force every mechanism into global synchronization. Instead, it should define where authoritative ownership, causal dependencies, atomic transitions or bounded coordination are necessary. Independent work may proceed concurrently when it does not violate declared dependencies or invariants.

**Why this is stronger:** a universal central controller creates a bottleneck and risks turning the Brain into a monolith; unrestricted asynchronous broadcasting creates stale reads, ambiguous authority and difficult recovery. Owner-managed state with explicit coordination rules offers a more defensible middle path while leaving implementation topology open.

### 12.6 Candidate coordination principles — not yet approved invariants

1. **Single authoritative writer per state domain, not one writer for the whole Brain.** A mechanism may publish proposals or evidence about another domain, but the designated owner commits that domain's authoritative state.
2. **Explicit contracts.** Every cross-mechanism exchange identifies the meaning, schema/version, source, provenance, relevant context, dependencies and expected response semantics. Contracts must not imply that every consumer processes every event.
3. **Causal context, not assumed global order.** Preserve event time, processing time, source sequence where available, and causal/dependency links. Do not infer causality solely from wall-clock timestamps.
4. **Version-aware reads and writes.** A result records the versions of upstream state it consumed. Before committing, the owner or coordinator checks whether relevant dependencies changed; stale results are rejected, recomputed, or retained as qualified historical outputs.
5. **Scoped consistency.** Specify stronger consistency for state transitions whose correctness requires it; permit eventual convergence for independent derived views or low-risk analyses. The required level must be justified by consequence, not selected globally.
6. **Idempotent processing.** Re-delivery and retry must not duplicate an experience, belief revision, learning update or other non-repeatable effect.
7. **Explicit conflict semantics.** Distinguish compatible parallel updates, competing hypotheses, mutually exclusive state transitions and irreconcilable conflicts. Do not resolve every conflict by last-write-wins or arbitrary confidence ranking.
8. **Bounded feedback.** Track derivation and influence paths so a mechanism cannot treat its own output, or a downstream echo of it, as independent confirmation. Monitor repeated re-triggering and oscillation.
9. **Partial-failure awareness.** Mechanisms expose health and state validity sufficiently for the Brain to know whether a result is unavailable, stale, degraded, incomplete or authoritative.
10. **Recoverable transitions.** State changes that span multiple mechanisms require explicit progress, retry, compensation or reconciliation semantics. Do not assume a distributed transaction is automatically available.
11. **No accidental central authority.** A scheduler or coordinator may allocate work and manage deadlines, but must not silently become the epistemic owner of beliefs, memories, predictions or valuations.
12. **Bounded re-evaluation.** Dependency invalidation must avoid both stale cognition and unbounded recomputation. Re-evaluation should be prioritized by materiality, consequence, freshness and resource budget; unresolved work remains visibly stale or qualified.

### 12.7 Concrete failure scenarios to design and test

| Scenario | Failure if unmanaged | Required design response to investigate |
|---|---|---|
| Memory retrieval completes after a belief was revised | Old memory can overwrite or falsely support newer belief | Version-aware merge; preserve retrieval context and evidence age |
| Two interpretations are produced concurrently | One is silently lost or treated as fact | Allow competing hypotheses with provenance and explicit epistemic status |
| A prediction uses belief version 4 while belief advances to version 5 | Forecast may be treated as current despite stale assumptions | Record dependency versions; qualify, reevaluate or invalidate forecast |
| Same experience is delivered twice after retry | Duplicate learning or inflated evidence | Stable identity/deduplication and idempotent effects |
| Messages arrive out of causal order | Later state may be applied before prerequisite evidence | Causal dependency checks; defer or reconcile rather than trust arrival order |
| Mechanism crashes after publishing but before recording completion | Consumers may act on an operation whose source thinks it failed | Durable transition/outbox or equivalent recovery semantics; exact pattern not selected |
| Coordinator becomes unavailable | Whole Brain may stop despite independent mechanisms being healthy | Define degraded operation and bounded local autonomy |
| One mechanism returns malformed or adversarial data | Downstream cognitive state may be corrupted | Contract validation, trust boundaries, quarantine and provenance retention |
| Attention repeatedly reprioritizes the same task | Oscillation/starvation | Hysteresis, cooldown or other evidence-based anti-oscillation control; parameters unresolved |
| Belief update triggers prediction, which re-triggers belief update indefinitely | Cognitive feedback loop never settles | Causal cycle detection, convergence criteria, iteration/resource bounds and escalation |
| Two learning candidates activate against different baselines | Active mechanisms become incompatible | Baseline/version compatibility checks and coordinated activation where dependencies require it |
| Partial outage leaves a mixed set of old and new state | Brain presents internally inconsistent picture | Explicit degraded/transition state and recovery reconciliation |
| Clock skew makes a late event appear earlier | Incorrect chronology or causal inference | Separate event/processing time and causal metadata; do not rely on wall clock alone |
| Re-evaluation queue grows faster than it is processed | Important stale state remains unexamined | Priority policy, overload handling, stale-state visibility and capacity limits |
| A mechanism uses a cached answer after its source is revoked or corrected | Invalid evidence persists in current cognition | Revocation/correction propagation and dependency-aware revalidation |

This is an initial scenario inventory, not an exhaustive proof that all failures have been found. Additional adversarial scenarios must be added as the architecture and contracts become more concrete.

### 12.8 Boundaries: Brain coordination versus SYS-02

Brain-internal coordination governs the exchange, dependency and consistency of cognitive state among Brain mechanisms. SYS-02 remains responsible for system-wide signalling and coordination across the wider JARVIS architecture. The Brain may consume system signals and publish defined cognitive outputs, but this investigation does not assign it ownership of system-wide message routing, device orchestration, motor execution or governance.

A future architecture must define the interface between these responsibilities, including failure reporting and degraded operation, without duplicating ownership.

### 12.9 Open questions requiring further investigation

- Which Brain operations require atomic state transitions across more than one mechanism, and can ownership be redesigned to avoid distributed atomic commits?
- What is the minimum common message/record envelope, and which fields belong in modality- or mechanism-specific payloads?
- Which clock/time model is required, and when are logical/causal sequence markers necessary?
- What consistency guarantees are required for beliefs, active working context, predictions, memory retrieval, candidate learning and activated adaptations?
- How should conflicting beliefs be represented and resolved without flattening uncertainty?
- Who detects and manages dependency cycles, oscillation and runaway feedback?
- What is the right degraded-mode behaviour when memory, reasoning, attention or coordination becomes unavailable?
- Which coordination functions are intrinsic to Brain and which belong to SYS-02?
- What recovery guarantees can be achieved without a central coordinator becoming a single point of failure?
- How can we test convergence, boundedness and consistency over long-running operation rather than only short unit tests?

No database, message broker, actor model, scheduler, programming language, process topology, global event store or synchronization technology is selected by this investigation.

### 12.10 Reviewer challenge checklist

The independent Reviewer is asked to challenge:
- Does the proposed owner-managed coordination model genuinely avoid both central bottlenecks and uncontrolled decentralization?
- Are there cognitive functions that need shared state but have no clear owner?
- Is “single authoritative writer per state domain” sufficient when the state is inherently relational or jointly derived?
- Are version-aware reads/writes and causal metadata practical at the expected scale?
- Which transitions truly require atomicity, and which can converge asynchronously?
- Are competing hypotheses being confused with conflicting authoritative writes?
- Does the proposal overuse distributed-systems patterns where a simpler in-process mechanism would be safer?
- Are event time, processing time, sequence and causality clearly distinguished?
- Could idempotency suppress legitimate repeated experiences or learning events?
- Are conflict policies specified without arbitrary last-write-wins behaviour?
- Can partial failure be represented without creating false confidence in the remaining state?
- How are feedback loops detected, bounded and tested?
- Does this design accidentally take over SYS-02 responsibilities?
- What failure scenarios, safety properties or measurable acceptance criteria are missing?

### 12.11 Sources and evidence

- Marvel, [Every Major A.I. in the Marvel Universe](https://www.marvel.com/comics/guides/2500/every-major-a-i-in-the-marvel-universe), official Marvel overview. Useful for fictional identity/context only; it does not disclose implementation.
- Marvel, [Iron Man (Tony Stark) in Comics](https://www.marvel.com/characters/iron-man-tony-stark/in-comics), official character overview describing suit capabilities and integrated technology; not a J.A.R.V.I.S. architecture specification.
- Liu et al. (2024), [Multimodal neuroimaging of hierarchical cognitive control](https://pubmed.ncbi.nlm.nih.gov/39488242/), *Biological Psychology*. Review discussing distributed neural coordination and hierarchical/multiplexed control; does not settle a software architecture.
- [Task-specific topology of brain networks supporting working memory and inhibition](https://onlinelibrary.wiley.com/doi/10.1002/hbm.70024) (2024), *Human Brain Mapping*. Empirical study reporting task-specific network attributes for working memory and inhibitory control.
- Microsoft Azure Architecture Center, [Event-Driven Architecture Style](https://learn.microsoft.com/en-us/azure/architecture/guide/architecture-styles/event-driven). Engineering reference on asynchronous delivery, eventual consistency, broker/mediator trade-offs and recovery complexity.
- Microsoft Research, [Consistency in Distributed Systems](https://www.microsoft.com/en-us/research/publication/consistency-distributed-systems/). Research discussion of consistency trade-offs in distributed systems.

### 12.12 Investigation B provisional conclusion

The current strongest direction is **owner-managed cognitive mechanisms with explicit contracts, provenance, causal/version metadata and consequence-sensitive consistency guarantees**. This is a provisional engineering choice, not a final architecture approval. The human reference supports distributed, context-dependent coordination; Marvel supplies the requirement for integrated coherence; software engineering supplies the concrete failure-handling mechanisms neither reference specifies.

The next investigation should examine **attention, prioritization and cognitive resource allocation**, while also continuing to refine the open coordination questions. Attention cannot be treated as a simplistic global on/off switch: it must be examined as an interacting control process that selects, protects, reallocates and releases limited cognitive resources without causing starvation, oscillation or blind spots.
