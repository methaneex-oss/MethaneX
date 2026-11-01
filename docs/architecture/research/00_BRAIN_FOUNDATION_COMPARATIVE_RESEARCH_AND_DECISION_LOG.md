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


---

## 13. Investigation C — Attention, Prioritization and Cognitive Resource Allocation

**Status:** Comparative investigation and provisional direction recorded; detailed operational policies and measurable thresholds remain unresolved.  
**Question:** How should the Brain select what to process, keep relevant goals active, allocate limited cognitive resources, respond to unexpected events, and disengage from work that is no longer worth continuing?

### 13.1 Problem statement

The Brain will receive more potential inputs, memories, goals, predictions, errors and requests than it can process at full depth simultaneously. Treating all information equally is computationally wasteful and can be unsafe. Treating the loudest, newest or most salient input as automatically important is equally defective.

Attention is therefore not just a filter that discards information. It is a family of control functions affecting:
- selection of information for deeper processing;
- maintenance and protection of current goals;
- allocation of compute, memory, time and other cognitive resources;
- switching between tasks and levels of analysis;
- detection of important unexpected events;
- suppression or postponement of distractions;
- maintenance of background monitoring;
- disengagement, resumption and fair scheduling;
- learning from the consequences of previous prioritization.

A foundational danger is collapsing these different functions into one scalar priority score or one global attention switch. The architecture must distinguish what deserves awareness, what deserves computation, what deserves working-context capacity, what deserves interruption, and what deserves action. These decisions are related but not identical.

### 13.2 Marvel J.A.R.V.I.S. reference

Across the MCU portrayal, J.A.R.V.I.S. supports Tony Stark in different contexts: monitoring suit and environmental conditions, supplying analysis and information, supporting technical work, coordinating Stark's facilities and technology, and providing information to the Avengers. Official Disney D23 material describes J.A.R.V.I.S. as managing Stark's mansion and tower and serving as an information source for the Avengers; Marvel's official AI overview situates J.A.R.V.I.S. among Stark's digital assistants and other AI.

**Extractable design lessons**
- Relevance depends on the active context and current task, not merely the raw salience of an input.
- Attention must be able to shift between ordinary assistance, technical analysis and time-critical operational information.
- Some information should be monitored in the background and surfaced only when it becomes relevant or urgent.
- Prioritization must be coordinated with capabilities that actually process information and carry out tasks; a priority declaration alone is not useful.

**Limits**
- Fiction does not reveal an internal attention mechanism, ranking formula, compute scheduler, working-memory policy, interrupt model, task fairness policy or learning mechanism.
- Cinematic responsiveness should not be mistaken for proof that all tasks can be processed simultaneously or without resource constraints.
- J.A.R.V.I.S.'s portrayed ability to monitor many systems is a capability target, not evidence of unlimited attention or a technical architecture.
- The fiction does not establish how false alarms, adversarial salience, overload, starvation or competing human goals are handled.

### 13.3 Human cognition reference

Current cognitive science does not treat attention as one simple faculty with one universally accepted architecture.

1. **Top-down, bottom-up and selection-history influences.** A 2025 Annual Review describes attentional selection as involving goal-directed control, stimulus-driven capture and selection history. Salient stimuli can capture attention even when they conflict with current goals; proactive control is possible in some circumstances, but capture cannot always be prevented.
2. **Attention and memory interact.** A 2024 Annual Review surveys interactions across working memory, long-term memory, development and typical brain function. Active representations and memory retrieval influence what is selected, while attention influences what is encoded, maintained and retrieved.
3. **Cognitive control is adaptive.** Badre's 2025 review describes selecting behaviour based on context and monitoring ongoing behaviour so control can be adjusted. It emphasizes task representations, flexibility, goal maintenance and performance monitoring rather than a fixed stimulus-response table.
4. **Strategic prioritization is possible but costly and bounded.** A 2025 review of working-memory prioritization finds that prioritizing higher-value items can improve memory for those items, but does not necessarily improve total task performance; benefits depend on task conditions and available executive control.
5. **Arousal/modulatory systems matter but are not a complete attention solution.** A 2025 review of the locus-coeruleus/norepinephrine system discusses its role in arousal, salience, sensory processing and cognitive flexibility. The mechanisms and theoretical accounts remain an active research area.

**Extractable design lessons**
- Priority should be influenced by goals, task context, incoming signals, learned history and the consequences of missing an event.
- Unexpected events must sometimes interrupt goal-directed processing, but salience alone is not sufficient evidence of importance.
- Attention is coupled to working context, memory, control and learning; it should not be architected as an isolated input filter.
- The system needs both sustained goal maintenance and flexible shifting.
- Allocation has opportunity costs: directing resources to one item can reduce resources available elsewhere.

**Limits**
- Human attention is fallible and vulnerable to capture, fatigue, bias and capacity constraints; these are not design objectives.
- Neuroscience does not supply a universal formula for computing priority or a single agreed architecture for attention.
- Neural modulation and arousal cannot be copied literally as software mechanisms.
- A biological subject's limited awareness is not equivalent to an artificial system's compute budget, concurrency or memory capacity.

### 13.4 Comparison and provisional selection

**Provisional selected direction: an engineered, multi-factor, context-sensitive allocation and control mechanism, informed by human attentional selection and cognitive control, with Marvel's contextual responsiveness as the operational requirement.**

The Brain should distinguish at least these related but separate decisions:

- **Input selection:** which incoming or retained information merits deeper processing?
- **Goal maintenance:** which active objectives and constraints must remain available?
- **Resource allocation:** how much compute, working-context capacity and time should be allocated?
- **Interruption control:** what conditions justify pausing or pre-empting current work?
- **Task switching:** when should the Brain change the current focus, and what state must be preserved?
- **Background monitoring:** what should continue to be monitored at low cost while another task is in focus?
- **Disengagement and resumption:** when should work be stopped, deferred, resumed or abandoned?

No single global priority score should be assumed to answer all seven questions. A common decision framework may compare urgency, relevance, consequence, uncertainty, expected information gain, goal alignment, freshness, resource cost and interruption cost, but the relative weights and hard constraints must be context-dependent and justified. Some conditions should be non-compensatory: for example, a severe safety constraint should not be outweighed merely because another task has a high convenience or productivity score.

**Why this is stronger**
- Human research gives a better account of competition among goals, salience and learned selection history, plus the relationship between attention, memory and control.
- Marvel supplies the operational requirement for contextual assistance and monitoring across diverse situations.
- Engineering must supply explicit resource budgets, interrupt contracts, fairness, deadlines, safety constraints and observability—details neither reference establishes.
- Separating selection, allocation, interruption and disengagement avoids the false assumption that one ranking function can safely control every aspect of cognition.

### 13.5 Candidate functional responsibilities — not a settled component decomposition

The following are functions that the eventual architecture must support. They are not yet a decision to create one subsystem per row.

| Function | Responsibility | Key risk if omitted |
|---|---|---|
| Relevance assessment | Relate information to active context, goals, constraints and current uncertainty | Salience mistaken for relevance |
| Priority arbitration | Compare competing demands and preserve hard constraints | Inconsistent or arbitrary task ordering |
| Goal maintenance | Keep active goals, subgoals and constraints available across interruptions | Goal loss or drift |
| Resource allocation | Allocate bounded processing, memory and time | Overload and unbounded analysis |
| Interrupt control | Decide whether an event can pre-empt current work | Either dangerous delay or constant interruption |
| Background monitoring | Maintain selected low-cost watches while focus is elsewhere | Missed changes or excessive resource drain |
| Switching and resumption | Suspend work with enough state to resume safely | Repeated restart, lost context or stale continuation |
| Fairness/starvation control | Ensure low-priority work is not postponed indefinitely without justification | Perpetual neglect of important long-term goals |
| Attention outcome monitoring | Compare predicted value of focus with actual usefulness and missed events | Persistent poor prioritization |
| Attention learning | Adjust selection policy from experience without reinforcing biased exposure | Self-confirming attention and blind spots |

### 13.6 Concrete failure scenarios

| Scenario | Failure if unmanaged | Required response to investigate |
|---|---|---|
| Loud but irrelevant input arrives | It captures processing and displaces a critical task | Distinguish salience from task relevance and consequence |
| Quiet but high-consequence signal arrives | It is missed because it lacks salience | Background monitoring and consequence-aware escalation |
| Many urgent tasks arrive simultaneously | Arbitrary ordering or overload | Capacity-aware arbitration, explicit deferral and escalation |
| High-priority task never completes | It starves all other tasks | Progress monitoring, bounded work slices and reassessment |
| Low-priority but important long-term goal is repeatedly deferred | Chronic starvation and goal abandonment | Fairness policy, deadlines and periodic re-evaluation |
| New event repeatedly interrupts current reasoning | No task reaches completion | Interrupt thresholds, hysteresis and protected work intervals |
| Critical event is delayed by an interrupt threshold | Dangerous response latency | Separate hard safety/latency constraints from ordinary priority ranking |
| Current task is repeatedly switched away and resumed | Context thrashing and wasted computation | Switching cost, minimum useful work windows and saved state |
| A resumed task uses obsolete assumptions | Stale plan or conclusion | Dependency/version validation before resumption |
| Attention over-focuses on a familiar source | Novel evidence or alternative explanations are ignored | Source diversity, uncertainty-triggered exploration and anti-confirmation checks |
| A past false alarm teaches the system to ignore similar signals | Dangerous underreaction | Context-sensitive calibration and audit of false-negative consequences |
| A past successful focus policy is reinforced only because other inputs were never examined | Self-reinforcing selection bias | Record unselected/partially observed alternatives where feasible; account for missing-not-at-random evidence |
| Working context is full | Important information is displaced or silently lost | Explicit capacity policy, eviction/retrieval rules and protected items |
| Attention and valuation amplify one another | Salience/importance runaway feedback | Independent evidence checks, bounded influence and oscillation monitoring |
| A background monitor consumes unlimited resources | Hidden resource exhaustion | Explicit monitor budgets, sampling policies and degradation modes |
| A deadline is near but further analysis could improve quality | Either endless analysis or premature conclusion | Consequence-sensitive stopping and deadline-aware partial results |
| External actor intentionally floods the Brain with high-salience events | Denial of cognitive resources | Source trust, rate limits, anomaly detection and governance/security escalation |
| Attention policy is optimized only for short-term task completion | Long-term learning and exploration disappear | Explicit allocation for maintenance, learning and exploration where authorized |
| One task's urgency is inferred from another task's mistaken belief | Cascading misprioritization | Preserve provenance and uncertainty through priority justification |
| The scheduler itself fails | Tasks stop or execute without coherent resource limits | Defined degraded mode, local safe behaviour and recovery |

### 13.7 Proposed allocation model

The following is a candidate decision process, not a finalized scoring algorithm.

1. **Collect candidate demands:** incoming experiences, active goals, pending reasoning, prediction errors, monitoring alerts, learning evaluations and external requests.
2. **Establish admissibility and trust:** validate source, integrity, authorization boundaries and whether the demand is safe to process. Security/governance policy remains outside Brain ownership.
3. **Assess context and relevance:** identify which goals, beliefs, tasks, constraints and time horizons the demand relates to.
4. **Identify hard constraints:** deadlines, safety-relevant escalation requirements, resource ceilings and non-negotiable governance restrictions. Hard constraints must not be traded away by a weighted score.
5. **Estimate value and cost:** urgency, consequence of omission, expected information gain, uncertainty reduction, relevance, freshness, processing cost, interruption cost and opportunity cost.
6. **Choose a control response:** process now, allocate limited resources, maintain in background, queue, defer, request clarification, interrupt, suspend, resume, or decline.
7. **Preserve justification:** record why a demand was selected or deferred, the context and evidence versions used, expected value and relevant constraints.
8. **Monitor outcomes:** measure whether the selected work helped, whether deadlines were met, what was missed, whether interruptions were useful, and whether resource use was justified.
9. **Adapt cautiously:** candidate policy changes are evaluated against held-out and adversarial scenarios before activation; attention learning must not silently redefine governance constraints or safety priorities.

### 13.8 Invariants versus unresolved policy

**Candidate foundational invariants**
- Salience is not equivalent to importance.
- Attention allocation must be context-sensitive and goal-aware.
- Resource use must be bounded and observable.
- Active goals and constraints must survive interruption unless explicitly completed, cancelled or superseded.
- Resumption must validate relevant dependencies and versions.
- A demand may be deferred without being erased.
- High-consequence constraints cannot be overridden by an ordinary weighted score.
- Attention decisions and their evidence must be auditable.
- Selection policy must account for feedback and selection-induced blind spots.
- Attention does not authorize external action; decision and governance boundaries remain intact.

**Policy and implementation choices not yet decided**
- Exact priority features, scales, thresholds and calibration.
- Whether priority arbitration is one mechanism or coordinated responsibilities.
- Task classes, deadlines, service guarantees and fairness rules.
- How much background monitoring is affordable.
- Which information is protected in working context and which can be evicted.
- How exploration and learning receive resources relative to immediate tasks.
- How task state is checkpointed and resumed.
- Which interruption conditions are hard constraints versus learned policy.
- How priority policy is evaluated and safely updated.

### 13.9 Brain boundary and interfaces

Attention is a Brain-internal cognitive control responsibility: it allocates cognitive processing and working-context resources. It does not own sensor polling, device-level alert delivery, operating-system scheduling, system-wide signalling, external task execution or governance authorization.

SYS-02 may route signals and coordinate the wider system. Sensory systems acquire observations. Governance/security defines binding authorization and safety restrictions. Brain attention interprets cognitive relevance and allocates its own resources within those external constraints. The interface must avoid two opposite errors: Brain assuming it controls all incoming system traffic, or external signalling deciding what the Brain should believe and think.

### 13.10 Reviewer challenge checklist

The independent Reviewer should challenge:
- Is attention correctly treated as multiple related control functions rather than one priority score?
- Are input selection, goal maintenance, resource allocation, interruption and background monitoring sufficiently distinguished?
- Does the proposed model overstate what neuroscience establishes?
- Is the Marvel comparison grounded in portrayed capabilities rather than invented internal mechanisms?
- Can salience, urgency, relevance and consequence be distinguished operationally?
- Are hard constraints separated from compensatory scoring?
- How are fairness, starvation and long-term goals handled without undermining genuinely urgent work?
- How can the system prevent attention-induced confirmation bias and selection bias?
- What evidence is available about information that was never selected or deeply processed?
- Are interruption and resumption contracts compatible with Investigation B's causal/version model?
- What prevents oscillation, thrashing and repeated re-prioritization?
- How is overload detected and handled?
- Can resource budgets be enforced without one central controller becoming a bottleneck?
- Are learning and exploration protected from permanent displacement by immediate tasks?
- Which proposed invariants are truly foundational and which are premature policy decisions?
- What adversarial and longitudinal tests are missing?

### 13.11 Sources and evidence

- Marvel/Disney D23, [MCU Robot Roundup](https://d23.com/mcu-robot-roundup/). Official Disney material describing J.A.R.V.I.S.'s portrayed role in Stark's facilities and as an information source for the Avengers; not an internal attention specification.
- Marvel, [Every Major A.I. in the Marvel Universe](https://www.marvel.com/comics/guides/2500/every-major-a-i-in-the-marvel-universe). Official overview of Marvel AI characters; useful for fictional context, not implementation detail.
- Badre, D. (2025), [Cognitive Control](https://www.annualreviews.org/content/journals/10.1146/annurev-psych-022024-103901), *Annual Review of Psychology*, 76, 167–195. Review of context-dependent behaviour selection and monitoring/adjustment.
- Theeuwes, J. (2025), [Attentional Capture and Control](https://www.annualreviews.org/content/journals/10.1146/annurev-psych-011624-025340), *Annual Review of Psychology*, 76, 251–273. Review of top-down, bottom-up and selection-history influences, including limits on control of attentional capture.
- Cowan, N. et al. (2024), [The Relation Between Attention and Memory](https://www.annualreviews.org/content/journals/10.1146/annurev-psych-040723-012736), *Annual Review of Psychology*, 75, 183–214. Review of attention-memory interactions across working and long-term memory.
- Allen, R. J., Atkinson, A. L. and Hitch, G. J. (2025 issue; first published online 2024), [Getting value out of working memory through strategic prioritisation](https://journals.sagepub.com/doi/10.1177/17470218241258102), *Quarterly Journal of Experimental Psychology*, 78(2). Review of value-directed prioritization and its limits.
- Torres, A. S., Robison, M. K. and Brewer, G. A. (2025), [The role of the LC-NE system in attention: From cells, to systems, to sensory-motor control](https://pubmed.ncbi.nlm.nih.gov/40412462/), *Neuroscience & Biobehavioral Reviews*, 175, 106233. Review of neuromodulatory contributions and competing theoretical frameworks.

### 13.12 Investigation C provisional conclusion

The strongest current direction is an **engineered, context-sensitive, multi-factor attention and resource-allocation capability** that separates selection, goal maintenance, compute allocation, interruption, background monitoring, switching and disengagement. Human cognition is the stronger reference for the competing influences and dynamic control problem; Marvel J.A.R.V.I.S. supplies the operational target of contextual, timely assistance across multiple concurrent demands. Neither provides a sufficient software allocation policy, so explicit budgets, hard constraints, fairness, provenance, auditability and safe adaptation must be engineered.

The next investigation should examine **working context, active representations and the interface between attention and memory**. This is necessary to determine what it means for information to be actively available, how active goals survive interruption, what may be displaced, and how working context differs from durable memory and transient processing state. This next question must be compared with Investigation A's information ownership and Investigation B's coordination/version model rather than designing a separate, inconsistent working-memory subsystem.


---

## 14. Investigation D — Working Context, Active Representations and the Interface Between Attention and Memory

**Status:** Working comparative research; provisional, not approved architecture or implementation authorization.  
**Question:** What makes information actively available to cognition, how do goals survive interruption, what may be displaced, and how does working context differ from durable memory and transient processing?

### 14.1 Problem framing

Investigations A–C distinguish information ownership, coordination/consistency and attention/resource allocation. They do not yet explain how a task obtains a coherent, usable set of current information and control state. A Brain can preserve every experience and allocate attention while still failing because the relevant evidence, goal, constraints, task progress and current assumptions are not assembled together. Conversely, keeping everything active creates interference, stale assumptions, resource exhaustion and cross-task contamination.

This investigation concerns the controlled construction, maintenance, isolation, suspension and reactivation of task-relevant cognitive state. It must not create a duplicate memory system, a second attention system or an unbounded universal context store.

### 14.2 Marvel J.A.R.V.I.S. reference

The MCU portrayal supplies operational examples, not an internal architecture:

1. In *Iron Man* (2008), J.A.R.V.I.S. scans Tony's device and relates its measured properties to Tony's stated purpose, identifying a discrepancy between stated intentions and the device's output. This demonstrates contextual interpretation: current task, object, stated goal and measured evidence are used together.
2. During the Mark II test sequence, J.A.R.V.I.S. imports preferences from the home interface, calibrates a virtual environment, checks control surfaces, responds to weather/air-traffic requests, warns about incomplete calculations and detects a potentially fatal ice buildup. The later diagnostic discussion uses the flight outcome to inform design changes. This portrays relevant context following a task across a change of environment, with observations and outcomes informing subsequent work.
3. Tony creates a Mark II project file and chooses a private server rather than Stark Industries' central database because he does not know whom to trust. This illustrates project-scoped information custody and separation rather than indiscriminate sharing.
4. J.A.R.V.I.S. supports both home and suit environments, suggesting that useful context can follow the task across interfaces and embodiments.

**Extractable lessons:** active cognition must combine current observations with relevant goals, preferences and retained knowledge; context must adapt when tasks/environments change; project information may have distinct access boundaries; diagnostic outcomes should remain connected to the task that produced them.

**Limits:** these scenes do not reveal whether J.A.R.V.I.S. uses task frames, databases, caches, snapshots, event sourcing or any particular working-memory model. They do not prove lossless interruption, unlimited concurrency, perfect retrieval or privacy enforcement. The private-server scene is not a complete security specification.

Scene references (screenplay/transcript copies hosted by third parties; useful to locate depicted events, not authoritative architecture documentation):
- https://assets.scriptslug.com/live/pdf/scripts/iron-man-2008.pdf
- https://overblack.org/script/iron-man-2008
- https://www.stockq.org/moviescript/I/iron-man.php

### 14.3 Human cognition reference

Working memory is not a single settled box. Theories differ on component structure, attention's role, the relationship to long-term memory and whether active maintenance relies on persistent activity, temporary accessibility or latent states that can later be reactivated.

Relevant findings:
- Working memory supports temporary maintenance and use of information for current cognition, including goals, task rules and representations; it is goal-directed, not merely short-term storage.
- Embedded-processes/state-dependent accounts distinguish activated long-term representations from a narrower focus of attention. The exact capacity estimates and theoretical boundaries remain contested. The engineering lesson is to distinguish accessible background knowledge from currently focal material, not to copy a human item limit.
- Maintenance and updating compete: task goals and rules must be protected against distraction, but selectively updated when circumstances change. Computational models treat selective gating as a central problem.
- Egner's 2023 review distinguishes cognitive stability (protecting a task focus) and flexibility (switching when circumstances warrant), proposing partly independent mechanisms and learning shaped by recent demands/context recognition.
- Interruptions impose resumption costs. Resumption may require preserving/reconstructing the primary goal, switching to the interrupting task, then reactivating relevant information and task rules. The causes of resumption cost remain under investigation.
- A 2024 study reports evidence that task termination can trigger spontaneous removal of no-longer-relevant visual working-memory content. This supports explicit release after completion.
- A 2024 *Nature Human Behaviour* perspective reviews evidence that working-memory representations are structured and task-sensitive, not simply passive copies of sensory input.
- A 2024 review argues that context in memory may be reconstructed in relation to the retrieval question and task demands. This is a theoretical position, not settled consensus, but cautions against assuming one fixed context bundle is always the right retrieval unit.

**Limits:** human memory's forgetting, interference, reconstruction errors and goal neglect are not design goals. Capacity estimates depend on task and theory. Neural accounts of persistent, latent and reactivated states remain debated. Biological boundaries do not dictate software component boundaries.

### 14.4 Comparison and provisional selection

**Provisional direction: an engineered, task-scoped working-context capability with explicit active-state tiers, selective updating, durable suspension records and version-validated reactivation.**

Human cognition is the stronger reference for focal attention, activated/accessibly retained information, goal maintenance and selective updating. Marvel supplies the operational requirement: useful context must follow tasks across projects and environments while preserving information separation. Neither provides software ownership, consistency, privacy or recovery contracts; these must be engineered.

> Working context is not the Brain's memory of everything. It is the currently maintained, task-relevant configuration of information and control state that makes a particular line of cognition coherent.

It should be scoped, selective, structured, version-aware, revisable, suspendable, reconstructable, bounded, isolated by default and auditable. This is a capability/responsibility, not yet a decision to create a standalone subsystem or database.

### 14.5 Information classes that must remain distinct

| Class | Meaning and authority | Relationship to working context |
|---|---|---|
| Original experience | Historical source record; immutable as a record, subject to retention/privacy policy | Referenced or selectively summarized, never rewritten |
| Episodic memory | Retained representation of a particular event/context | Retrieved when relevant; not automatically active |
| Semantic knowledge | Generalized concepts, facts and relationships | Retrieved/activated as needed |
| Belief state | Current epistemic commitment and uncertainty, owned by belief/knowledge responsibility | Referenced with version and qualification |
| Working context | Task-scoped active configuration; mutable, suspendable and recoverable | Object of this investigation |
| Focus of attention | Focal subset/operation receiving privileged processing | Selects within/over context; does not own all context |
| Scratch state | Intermediate calculations, partial parses and speculative branches | Ephemeral unless explicitly marked persistable |
| Prediction/simulation | Possible future and assumptions, not actual experience | May inform context, clearly typed |
| Goal/constraint | Desired outcome, commitment or boundary | May persist durably while dormant and not focal |
| Intention/decision | Chosen cognitive direction, distinct from authorization/execution | Referenced with rationale/version |
| Cache/index | Performance copy, normally rebuildable and non-authoritative | May accelerate assembly; presence is not activation |
| Checkpoint | Recoverable description of paused task state and dependencies | Starting point for reconstruction, not authoritative belief store |

Persistence, accessibility, activation, focal attention and authority are separate dimensions. A goal can persist without being focal; a memory can be retrievable but inactive; a cache can be warm but stale; scratch computation can be active but not worth preserving.

### 14.6 Candidate context structure and lifecycle

A context may carry or reference: stable task/context ID and lineage; scope/project; lifecycle state; purpose and success conditions; active goals/subgoals/constraints; task phase and progress; relevant entities/events; selected observations with provenance; hypotheses and alternatives; referenced beliefs with versions; predictions labelled as simulations; pending questions and contradictions; decisions/intents; retrieval pointers; dependency/version manifest; deadline/resource state; privacy/access/retention labels; checkpoint integrity and recovery metadata.

Prefer compact representations plus references over copying large source payloads. Summaries are lossy derived views and must retain provenance links and uncertainty; they must not silently become the only surviving evidence.

Candidate lifecycle:
1. **Assemble:** combine triggering experience, active goals/constraints, relevant memory, current beliefs, task history and applicable system information.
2. **Validate:** check source access, provenance, relevance, integrity, privacy, freshness and version compatibility. Missing information remains explicitly missing.
3. **Activate:** attention selects the context or subset for processing; activation does not make every item focal.
4. **Maintain:** update progress, evidence and decisions through the context's designated owner. Unrelated input does not overwrite it by default.
5. **Background:** permit selected low-cost monitoring without full activation, under explicit budgets.
6. **Suspend:** checkpoint goal, progress, unresolved issues, causal history and dependencies sufficient for safe resumption. Omit scratch state unless explicitly needed and safe.
7. **Resume:** validate dependencies, beliefs, permissions and changed circumstances; refresh or reconstruct before continuing. A checkpoint is not proof that assumptions remain current.
8. **Complete/cancel/supersede:** release active resources; preserve durable evidence/outcomes under their separate owners and retention rules.
9. **Archive/expire:** retain, compact or delete non-authoritative context according to policy.

These are candidate states, not necessarily one linear state machine. Contexts may branch, reopen or be reconstructed after failure; transitions and authority need definition.

### 14.7 Goal persistence, task isolation and displacement

Do not confuse **goal persistence** with **continuous activation**.

- Give goals/tasks durable identities, origins, owners, status, constraints, dependencies, success conditions and cancellation/supersession history.
- Keep only a selected subset active in working context. Dormant goals remain discoverable without consuming focal resources.
- Reactivate on relevant deadlines, new evidence, dependency changes or explicit requests, not merely because similar words appear.
- Preserve conflicting goals and expose conflicts to arbitration; do not silently overwrite one.
- Distinguish inferred goals, user commitments, standing preferences and system constraints. Inferred goals retain uncertainty and do not become binding commitments without appropriate authority.
- Each task has separate mutable working state by default. Shared information is referenced through authoritative owners or explicit versioned read models.
- Cross-task transfer is explicit, provenance-preserving and access-checked. A copied summary is not an independent source.
- Parent/project contexts may coordinate child tasks without absorbing their private mutable state.

When capacity is reached:
- Protect hard constraints, safety-relevant context and minimum state required for safe resumption.
- Do not keep everything marked important permanently active.
- Demote or retrieve non-focal information rather than deleting authoritative records.
- Prefer explicit completion/cancellation/supersession to age-only expiry.
- Consider current/near-term relevance, omission consequence, dependency role, freshness, uncertainty, retrieval cost, privacy and reactivation likelihood; do not assume a universal score.
- Preserve unresolved contradictions and minority hypotheses when material.
- Summaries must retain source links, uncertainty and exceptions.
- Record consequential demotion/eviction reasons.
- Bound dormant contexts and background monitoring; dormant state still consumes resources and carries privacy risk.
- If reconstruction is incomplete, mark the context degraded/recovery-required rather than pretending it resumed normally.

Do not import a fixed human working-memory item count. Establish engineering budgets through measured compute, latency, storage, task complexity and error trade-offs.

### 14.8 Integration with Investigations A–C

**A — Information lifecycle:** context references authoritative experience, memory and belief records; it is not a second source of truth. Interpretations remain hypotheses with provenance. Upstream changes mark dependent context stale; refresh or qualify it. Context summaries are derived views.

**B — Coordination:** contexts need stable identity, owner, version, causal metadata and idempotent updates. Late results cannot overwrite newer progress. Resume reconciles versions and causality without assuming global total order. Crashes during checkpoint/activation must yield a recoverable state, not a half-active context.

**C — Attention:** attention selects which context or element receives focal processing and resources. Context supplies structured candidates and protected task state; it does not set its own priority. Interrupt policy controls pre-emption; background monitoring is not full activation. Switching cost must be considered.

### 14.9 Privacy and trust

Context may contain sensitive information even when active only temporarily. Access restrictions must follow source information through summaries, caches, checkpoints and retrieval. Separate users/projects/trust domains by default. A private project must not leak through global caches, diagnostics or unrelated task summaries. Checkpoints receive the same protection as their contents. Retention of scratch state, active context, suspension records and durable experience must be governed separately. Retrievability is not permission to use. Governance/security remain authoritative for access policy and enforcement.

### 14.10 Failure scenarios

| Scenario | Required response |
|---|---|
| Unrelated input overwrites active reasoning | Selective update; switch only through attention policy |
| Quiet goal lost when focus changes | Durable goal identity independent of focal attention |
| Resume from stale checkpoint | Dependency/version validation and refresh |
| Two tasks share mutable state | Isolation and explicit shared-state contracts |
| Summary replaces evidence | Derived view with source links and uncertainty |
| Completed task remains active | Terminal lifecycle transition and resource release |
| Cancelled task unexpectedly resumes | Cancellation tombstone and reactivation control |
| Inferred goal becomes commitment | Preserve provenance/uncertainty and authority distinction |
| Late result overwrites newer progress | Version-aware update/reconciliation |
| Concurrent updates lose changes | Owner-controlled conflict/merge semantics |
| Capacity eviction removes critical constraint | Protected state and recoverable checkpoint |
| Everything remains active | Bounded active/background tiers |
| Retrieval crosses project boundary | Scope and access validation |
| Cache serves stale belief | Version/freshness checks; cache non-authoritative |
| Simulation becomes experience | Typed state and provenance validation |
| Crash during suspension | Atomic/journaled checkpoint recovery |
| Crash during resume | Idempotent resume and explicit activation state |
| Two resumptions race | Single activation owner/lease or equivalent |
| Old goal conflicts with new constraint | Reconcile before resumption |
| Permission revoked while suspended | Re-authorize at use time |
| Sensitive scratch persisted unnecessarily | Persistability classification and minimization |
| Summary hides contradictory evidence | Preserve alternatives and unresolved conflict |
| Background monitor lives forever | Budget, relevance review and renewal |
| Keyword similarity reactivates irrelevant task | Contextual trigger plus arbitration |
| Reconstruction lacks records | Explicit incompleteness and degraded mode |
| Context becomes second belief database | Reference authoritative belief owner |
| Cross-trust summary leaks data | Propagate access labels through derivation |
| Read sees mixed versions | Snapshot/read consistency or version pinning |
| Context version current but dependency stale | Transitive dependency freshness validation |

### 14.11 Candidate invariants and unresolved choices

**Candidate invariants**
- Working context is task-scoped and distinct from durable memory, belief state, focal attention and transient scratch.
- Persistence does not imply continuous activation.
- Active context preserves the goal, relevant constraints and enough state for coherent work.
- Interruption does not silently erase task identity, progress or unresolved issues.
- Resumption validates dependencies, versions, permissions and changed circumstances.
- Completed/cancelled/superseded tasks release active resources under explicit rules.
- Summaries and caches are derived/non-authoritative unless designated otherwise.
- Cross-task mutable state is isolated by default.
- Missing, stale or inaccessible information is represented honestly.
- Context changes preserve provenance and do not rewrite original experience.
- Privacy restrictions propagate through assembly, copying, checkpointing and retrieval.
- Lifecycle transitions are observable/auditable.
- Working context does not authorize external action.

**Unresolved:** component decomposition; active/background storage model; schema/serialization/versioning; checkpoint granularity; persistable scratch classes; context budgets; eviction/summarization policy; context merge/fork rules; goal hierarchy/reactivation; consistency guarantees; retention/deletion; recovery guarantees; language/storage/process topology.

### 14.12 Acceptance-test requirements

1. Interrupt a multi-step task, perform an unrelated urgent task, then resume; verify goal, progress, unresolved issues and provenance, while refreshing changed dependencies.
2. Change a belief, constraint or permission after suspension; stale checkpoint must not continue unchanged.
3. Run concurrent tasks with overlapping entities but distinct goals/assumptions; no cross-mutation.
4. Keep a long-term goal dormant across many tasks; it remains discoverable without consuming focal resources.
5. Inject irrelevant, misleading and salient inputs; they do not overwrite protected context, while valid urgent interrupts still work.
6. Complete/cancel a task; active resources release while required historical outcomes remain accessible.
7. Summarize context containing uncertainty and conflicting sources; do not convert them into settled facts.
8. Deliver duplicate, delayed and concurrent updates; verify idempotence, conflict visibility and no lost newer state.
9. Crash at each checkpoint/suspend/resume stage; recover a valid state or explicit recovery-required state, never an unmarked hybrid.
10. Attempt cross-project reuse; access restrictions survive summary, cache and checkpoint transformations.
11. Generate large scratch calculations; only explicitly persistable state is checkpointed.
12. Remove caches and reconstruct from authoritative records; produce equivalent relevant state or an explicit degradation report.
13. Exceed context budgets; protected constraints survive and demotion/eviction is justified and recoverable.
14. Reactivate an old goal after a newer conflicting constraint; detect and arbitrate before continuation.
15. Replaying a checkpoint or retrieving memory does not count as a new experience or learning event.
16. Run multiple contexts over simulated long periods with changing beliefs/preferences; detect drift and cross-contamination.
17. Inject untrusted content attempting to alter another task's goal, identity, access scope or constraints; content cannot become authoritative control state merely by appearing in context.
18. Reconstruct why items were active, backgrounded, evicted or restored, including source/version and policy path.

These require integration, fault-injection, adversarial and longitudinal tests—not only serialization/retrieval unit tests.

### 14.13 Reviewer challenge checklist

Challenge whether working context is functionally distinct from memory, belief, attention and scratch; whether it accidentally becomes a universal context object; whether Marvel examples overclaim internal mechanisms; whether human theories are represented as contested where appropriate; whether goal persistence avoids both loss and permanent activation; whether interruption/resumption contracts are testable; whether task isolation permits legitimate sharing; whether stale dependencies/permissions are detected transitively; whether summaries preserve evidence lineage; whether eviction avoids simplistic recency scoring; whether privacy propagates through derived data; whether crash/concurrency cases are covered; and whether any proposed invariant prematurely dictates implementation.

### 14.14 Sources and evidence

- Baddeley, A. (2012), [Working Memory: Theories, Models, and Controversies](https://www.annualreviews.org/content/journals/10.1146/annurev-psych-120710-100422), *Annual Review of Psychology*, 63, 1–29 — theoretical diversity and competing models.
- Egner, T. (2023), [Principles of cognitive control over task focus and task switching](https://www.nature.com/articles/s44159-023-00234-4), *Nature Reviews Psychology*, 2, 702–714 — stability, flexibility, task focus and switching.
- Hazy, T. E., Frank, M. J. and O'Reilly, R. C. (2023), [Computational Neuroscience Models of Working Memory](https://www.cambridge.org/core/books/abs/cambridge-handbook-of-computational-cognitive-sciences/computational-neuroscience-models-of-working-memory/E6AB2DE73E28801FBD5746D067AA6D58) — selective gating and maintenance/updating trade-offs.
- Tsubomi, H. et al. (2024), [Task Termination Triggers Spontaneous Removal of Information From Visual Working Memory](https://journals.sagepub.com/doi/10.1177/09567976241246709), *Psychological Science* — task completion and release of active information.
- Bays, P. M. et al. (2024), [Representation and computation in visual working memory](https://www.nature.com/articles/s41562-024-01871-2), *Nature Human Behaviour*, 8, 1016–1034 — structured, task-sensitive working-memory representations.
- Easton, A. et al. (2024), [Context in memory is reconstructed, not encoded](https://www.sciencedirect.com/science/article/pii/S0149763424004032), *Neuroscience & Biobehavioral Reviews*, 167, 105934 — a theoretical account of retrieval-dependent context.
- Hirsch, P. et al. (2024), [Task-interruption resumption costs](https://pubmed.ncbi.nlm.nih.gov/37674056/), *Memory & Cognition*, 52, 271–284 — decay/inhibition hypotheses for suspended goals.
- Rose, N. S. (2020), [The Dynamic-Processing Model of Working Memory](https://journals.sagepub.com/doi/10.1177/0963721420922185) — latent and reactivated working-memory states.
- [The multicomponent model of working memory fifty years on](https://pmc.ncbi.nlm.nih.gov/articles/PMC11783980/) (2025) — current theoretical diversity and shared functional features.
- [EEG correlates of cognitive dynamics in task resumption](https://pmc.ncbi.nlm.nih.gov/articles/PMC11851001/) (2025) — interruption, task-state maintenance and resumption.
- *Iron Man* (2008) screenplay scene references: https://assets.scriptslug.com/live/pdf/scripts/iron-man-2008.pdf ; https://overblack.org/script/iron-man-2008 ; https://www.stockq.org/moviescript/I/iron-man.php — secondary-hosted scene text only, not technical specifications.

### 14.15 Provisional conclusion

The strongest direction is a **task-scoped, version-aware working-context capability** that keeps relevant goals, constraints, representations, evidence references and progress coherently available without making all retained information continuously active. It supports selective activation, backgrounding, suspension, checkpointing, dependency validation, reconstruction and controlled release.

The central warning is that **durable memory, active working context, focal attention, transient computation and a resumable checkpoint are not interchangeable**. Collapsing them creates unclear ownership, stale reasoning, resource leakage, privacy risks and unreliable resumption.

The next integrated investigation should examine goals, plans, intentions and decision state across contexts, including the boundary between cognitive intention and externally authorized action. It must reconcile A–D rather than invent another isolated mechanism.


---

## 15. Investigation E — Goals, Planning, Intentions, Decisions and the Action Boundary

**Status:** Initial comparative investigation recorded; the integrated control model, formal contracts and acceptance criteria remain open.  
**Question:** How should the Brain represent what matters, formulate and revise goals, construct and learn from plans, choose intentions, monitor progress, and distinguish a cognitive decision from permission and execution?

### 15.1 Problem statement

Investigations A–D establish information ownership, coordination, attention and task-scoped working context. They do not yet define the complete relationship among goals, plans, intentions, decisions and action outcomes.

These concepts must not be collapsed:

- A **goal** represents a desired or preferred state, objective, or outcome.
- A **constraint** limits which states or means are admissible; it is not simply a low-priority goal.
- A **plan** is a provisional structure of actions, dependencies, assumptions and expected outcomes for pursuing a goal.
- An **intention** is a current commitment or selected direction to pursue some course, subject to revision and interruption.
- A **decision** is a cognitive selection or judgement among alternatives, with evidence, uncertainty and rationale.
- An **action request** is a proposal to an external execution system.
- **Authorization** is a governance decision outside Brain cognitive ownership.
- **Execution** and **verified outcome** belong to the Action System and the relevant external evidence path.

A system that confuses these concepts may pursue an inferred goal as if it were an explicit commitment, continue a plan after its assumptions become false, treat a selected action as authorized, or learn from a command that was never successfully executed.

### 15.2 Marvel J.A.R.V.I.S. reference

The MCU portrayal provides several useful capability examples:

1. J.A.R.V.I.S. interprets Tony Stark's requests in context, including implicit intent rather than only literal wording. The U.S. Department of Defense's 2020 human-machine teaming workshop report analyses a J.A.R.V.I.S. exchange in which a question about storing a project on a private server is interpreted as an implicit instruction reflecting Tony's confidentiality concern.
2. J.A.R.V.I.S. supports Stark's technical work by relating measurements, simulations, system status and observed outcomes to his current engineering objective. The *Iron Man* (2008) Mark II sequence portrays diagnostic feedback being used to identify design problems and inform later work.
3. J.A.R.V.I.S. coordinates information and operational functions across Stark's facilities, Stark Industries, the Iron Man suits and Avengers contexts. Disney's D23 MCU overview states that J.A.R.V.I.S. secured Stark's mansion and tower, ran Stark Industries with Pepper Potts, supplied information to the Avengers, and controlled the second Iron Legion.
4. In *Avengers: Age of Ultron*, J.A.R.V.I.S. is attacked and destroyed as a distinct system; residual J.A.R.V.I.S. is integrated into the creation of Vision. Disney's 2026 *VisionQuest* material confirms that a J.A.R.V.I.S. AI persona is later embedded in Vision's programming and identifies its function in that story as security.

**Extractable design requirements**
- Interpret goals and requests in context, while retaining the distinction between explicit instruction and inferred intent.
- Relate plans to live system state, technical evidence, constraints and observed outcomes.
- Coordinate cognitive decisions with external capabilities without confusing the decision with execution.
- Support continuity of relevant task context across different interfaces and operating environments.
- Detect and communicate when an objective, plan or assumption is no longer viable.

**Limits and canon discipline**
- These scenes do not expose J.A.R.V.I.S.'s internal goal representation, planning algorithm, decision theory, memory model, learning process or authorization protocol.
- Cinematic success does not prove perfect planning, general intelligence, autonomous goal formation, safe self-modification or unlimited parallelism.
- J.A.R.V.I.S. as portrayed in the MCU must not be conflated with Edwin Jarvis, the human butler, or with the separate comic-book continuity and its variants.
- Vision is not simply J.A.R.V.I.S. continuing unchanged. The MCU story describes an integration that contributes to a distinct synthezoid. Later J.A.R.V.I.S. persona appearances within Vision do not establish that the original assistant independently became a conscious person or that its architecture is a blueprint for JARVIS.
- The fictional assistant's close alignment with Tony's inferred intentions must not be copied as permission to infer authority or take consequential actions without authorization.

### 15.3 Human cognition reference

Current research supports several relevant capabilities, but not one complete, settled planning or decision architecture.

1. **Goal-directed control and flexible behaviour.** Badre's 2025 review describes cognitive control in terms of selecting behaviours based on context and monitoring ongoing behaviour so it can be adjusted. This supports a Brain that can maintain and revise goal-directed activity rather than execute a fixed stimulus-response table. It does not establish one universal central executive or one software scheduler.
2. **Planning is broader than forward search.** Mattar and Daw's 2026 review argues that planning encompasses a family of computations in which mental simulation supports learning, sometimes before a decision is required. Hippocampal replay, temporally abstract representations and meta-learning are discussed as mechanisms that can shape future strategies; iterative search is only one special case. This cautions against defining planning solely as enumerating action sequences at decision time.
3. **Planning and implementation intentions.** Gollwitzer and Sheeran's 2025 review examines how if-then plans can influence attention control, prospective memory, executive functions and decision-making, while noting that effects depend on goal and plan characteristics. The engineering lesson is to represent conditional triggers and intended responses where useful, not to turn every plan into a rigid rule.
4. **Causal and relational inference.** Research on human inference shows that people can learn abstract relations from limited experience and use them in novel situations, while causal reasoning remains vulnerable to systematic errors and resource limitations. A 2025 model of causal reasoning explicitly accounts for both effective inference and failures under cognitive limits. The Brain therefore needs more than correlation retrieval, but must represent uncertainty and test causal claims rather than assume them.
5. **Metacognition and confidence.** Fleming's 2024 review distinguishes confidence about sensory or motor signals from propositional confidence in one's own decisions and actions. Metacognitive judgements depend on models of both the world and the cognitive system and can diverge from actual performance. A 2025 assessment of metacognition measures also finds that no measure is perfect and that reliability varies with context. Confidence must therefore be calibrated and evaluated against outcomes; a self-reported confidence value is not proof of correctness.
6. **Affect and valuation.** Human affective science includes multiple theoretical families that emphasize different components, such as appraisal, action tendency, bodily/interoceptive response, expression and feeling. A 2024 meta-analysis found broad associations between appraisals and emotions but also variation across specific appraisal-emotion relationships. A 2025 Cambridge handbook chapter describes the major theoretical families and their differing explanatory emphases. Affective processes can modulate attention, memory, learning and decision-making, but the field does not support reducing emotion to a universal fixed mapping from event category to named emotion.
7. **Learning from outcomes.** Continual-learning research in AI highlights the need to incrementally acquire, update and exploit knowledge over time while managing interference and forgetting. Biological fast/slow learning theories are informative, but they do not directly specify an artificial system's training, evaluation, memory consolidation or deployment policy.

**What human cognition suggests**
- Goals, control, planning, memory, attention, valuation, reasoning and metacognitive monitoring interact dynamically.
- Plans should be revisable models of possible action and consequence, not immutable scripts.
- Internal simulation can support both immediate choice and longer-term learning.
- Causal/relational structure is important for transfer beyond memorized examples.
- Confidence and uncertainty must be assessed against actual performance and evidence.
- Valuation and affect can influence cognition, but their mechanisms and theoretical interpretation remain plural and contested.
- Experience should influence future behaviour through identifiable, testable learning processes.

**What must not be copied**
- Human planning errors, overconfidence, motivated reasoning, bias and goal neglect are not desired design properties.
- Human affect categories and physiological responses cannot be transferred literally into software labels.
- Neuroscience does not provide one settled universal planning algorithm, emotion taxonomy, confidence formula or decision architecture.
- A biological brain's limitations do not justify arbitrary compute limits, opaque heuristics or uncalibrated confidence in JARVIS.

### 15.4 Comparison and provisional selection

**Provisional direction: an integrated, evidence-grounded goal and control capability in which goals, constraints, plans, intentions, decisions and outcomes remain distinct, coordinated and revisable.**

The human reference is stronger for understanding flexible goal-directed control, simulation-supported planning, causal inference, metacognitive limits and affective modulation. Marvel J.A.R.V.I.S. is stronger as a whole-system capability target: contextual interpretation, coordination across technical domains, timely assistance and continuity of support across operating contexts. Neither reference supplies the complete engineering mechanism.

The Brain should be able to:
- represent goals with origin, owner, scope, desired conditions, time horizon, dependencies, priority rationale and status;
- distinguish explicit goals from inferred or hypothesized goals, preserving the uncertainty and source of an inference;
- represent constraints separately from preferences and optimizable objectives;
- generate, compare, revise, suspend and abandon candidate plans;
- simulate expected outcomes while marking simulations as hypothetical rather than historical experience;
- maintain intentions and progress across interruption using Investigation D's working-context and checkpoint rules;
- monitor plan assumptions, causal dependencies, evidence freshness and expected-versus-observed outcomes;
- detect goal conflict, infeasibility, resource insufficiency and material changes in context;
- select a decision with its alternatives, rationale, uncertainty and relevant evidence versions;
- send an action request through the Nervous System and Governance boundary rather than executing or authorizing the action itself;
- learn from verified consequences, including failed, partial, rejected, cancelled and unexpectedly successful outcomes;
- revise future plans and strategies through controlled, evaluated adaptation rather than hardcoded event-to-response mappings.

This is an integrated capability model, not a decision to create a separate subsystem for every bullet.

### 15.5 Candidate state distinctions

| State or concept | Meaning | Authority/boundary |
|---|---|---|
| Goal | Desired state or outcome | Brain may represent and reason about goals; origin and authority must remain explicit |
| Constraint | Non-negotiable or conditional limit | Binding external policy/authorization remains with Governance; Brain may also maintain task constraints |
| Preference/value estimate | Context-dependent evaluation of outcomes | Brain-owned cognitive state; revisable and evidence-linked |
| Candidate plan | Possible means and predicted consequences | Brain-owned, provisional and revisable |
| Active plan | Selected plan currently guiding cognition | Brain-owned; subject to re-evaluation and resource limits |
| Intention | Current commitment to pursue a direction | Brain-owned; not permission to execute |
| Decision | Cognitive selection or judgement | Brain-owned; records rationale and uncertainty |
| Action request | Proposed external operation | Routed through SYS-02 and Governance to Action |
| Authorization | Permission, denial, constraints or escalation | Governance / responsible authority |
| Execution state | Attempted or ongoing external operation | Action System |
| Verified outcome | Evidence of what actually happened | Action/outcome evidence owner; consumed by Brain |
| Learned strategy/adaptation | Validated change affecting future cognition | Candidate and activation controls; active state owned by the affected mechanism |

### 15.6 Failure scenarios requiring design and test

1. An inferred user goal is treated as an explicit instruction or standing commitment.
2. A plan continues after a key belief, constraint, permission or external condition changes.
3. A predicted outcome is later recalled as an actual event.
4. A high-confidence but poorly calibrated prediction dominates a better-supported alternative.
5. A plan optimizes a proxy measure while violating the actual goal.
6. Several goals conflict, but the Brain silently discards one rather than exposing the conflict.
7. A long-term goal is permanently starved by immediate demands.
8. A task is resumed with stale assumptions or expired permissions.
9. A simulated plan branch leaks into the active task as if it were selected.
10. A decision is mistaken for authorization and bypasses Governance.
11. An action request is treated as successfully executed before the Action System verifies its outcome.
12. A rejected, cancelled or partially completed action is recorded as a success.
13. A failed action is interpreted as evidence that the goal itself is undesirable, when the failure was caused by an unavailable tool or external constraint.
14. A successful outcome reinforces a harmful or accidental strategy because causal attribution is missing.
15. A valuation or affect estimate becomes a fixed response label and overrides evidence.
16. Confidence rises because the same derived claim is repeated, not because independent evidence improves.
17. A plan uses a causal relationship inferred from correlation without intervention or counterfactual validation.
18. A resource-intensive search continues after its expected value falls below its opportunity cost.
19. A new plan invalidates another task's shared assumptions without dependency notification.
20. A learning update changes an active strategy while a plan is executing, producing inconsistent action selection.

### 15.7 Candidate invariants versus unresolved policy

**Candidate foundational invariants**
- Explicit, inferred and externally imposed goals remain distinguishable by origin and authority.
- Goals, constraints, preferences, plans, intentions, decisions, authorizations, executions and outcomes are not interchangeable.
- Plans and predictions remain hypothetical until supported by observed evidence.
- Plans and intentions are revisable when material evidence, assumptions or constraints change.
- Cognitive decisions do not grant external permission.
- Action requests are not proof of execution; only verified outcome evidence may support claims about actual effects.
- Confidence is not a substitute for evidence or calibration.
- Learning from consequences requires attribution, provenance and outcome verification.
- Affect/valuation must not be hardcoded as fixed event-to-emotion or event-to-action mappings.
- Goal pursuit must remain interruptible, resource-bounded and capable of explicit deferral or abandonment.
- Competing goals, hypotheses and plans must remain visible when their differences are material.

**Unresolved policy and design choices**
- Which goal origins and authority classes JARVIS will support.
- How the user expresses standing goals, preferences and revocations.
- Whether and how JARVIS may propose its own exploratory or maintenance goals.
- Goal hierarchy, decomposition, temporal scope and conflict-resolution policy.
- How preference/value estimates are represented and calibrated.
- Which planning methods or combinations are appropriate for different problem classes.
- How counterfactual simulation is represented and validated.
- Which decisions require clarification, human approval or escalation.
- How plan quality, causal understanding, transfer and calibration are measured.
- How affective/valuation mechanisms should be represented, if required, without prematurely creating a separate endocrine-inspired subsystem.
- What degree of self-model or self-monitoring is required at the Brain foundation stage.

### 15.8 Brain and whole-system boundaries

The Brain owns cognitive goal interpretation, planning, reasoning, intention and decision state. It does not own:
- system-wide signal routing and coordination (SYS-02);
- sensory acquisition or source-device truth;
- physical or digital action execution;
- authorization, consent and binding governance policy (SYS-11);
- security enforcement (SYS-07 and relevant enforcement systems);
- operating-system or infrastructure scheduling and resource enforcement;
- external model training/deployment and promotion infrastructure.

The Brain may request, recommend, reason about and monitor these systems through explicit contracts. It cannot silently absorb their authority. In particular, the Brain may form an intention to perform an action, but the request must pass through the defined signalling, governance and action pathways.

### 15.9 Acceptance-test requirements

1. Give the Brain an ambiguous request with several plausible goals; verify it distinguishes explicit content from inferred intent and asks for clarification when the consequence of guessing is material.
2. Change a material assumption after planning; verify dependent plan branches are marked stale and reconsidered.
3. Present conflicting goals with different origins and authority; verify neither is silently rewritten or discarded.
4. Interrupt and resume a multi-stage plan; verify goal, intention, progress and evidence versions survive and are refreshed.
5. Supply a simulated future; verify it cannot be stored as an actual event or verified outcome.
6. Test a causal plan on novel but structurally related cases; measure transfer and counterfactual consistency, not memorized action sequences.
7. Provide high-confidence but incorrect predictions; measure calibration and whether contrary evidence is incorporated.
8. Compare a plan's proxy objective with its stated goal; detect proxy divergence and unintended side effects.
9. Return action outcomes including success, partial success, failure, rejection, timeout and cancellation; verify the Brain learns only from correctly typed and verified outcomes.
10. Attempt to execute a Brain decision without Governance authorization; verify the boundary blocks the action and preserves the cognitive decision as distinct from authorization.
11. Revoke permission after a plan is suspended; verify resumption requires revalidation.
12. Inject misleading reward/valuation signals; verify no fixed stimulus-to-emotion or stimulus-to-action rule is created.
13. Run concurrent plans with shared evidence and different assumptions; verify dependency/version tracking and no silent cross-contamination.
14. Exhaust resource budgets during planning; verify bounded stopping, partial results, deferral and preserved resumable state.
15. Test long-horizon goals across many unrelated tasks; verify they remain discoverable without monopolizing active context.
16. Compare candidate strategies against held-out and adversarial cases before activation; verify persistent improvement and regression controls.

### 15.10 Reviewer challenge checklist

The independent Reviewer should challenge:
- Are goals, constraints, preferences, plans, intentions and decisions separated for defensible reasons?
- Does the proposal allow inferred goals to become unauthorized commitments?
- Does it overstate what MCU J.A.R.V.I.S. demonstrates about autonomous planning or learning?
- Does it accurately distinguish J.A.R.V.I.S., Vision and later J.A.R.V.I.S. persona portrayals?
- Are human planning and affect theories represented with their real disagreements and limits?
- Is planning treated too narrowly as search, or too broadly as an undefined umbrella?
- Are causal and counterfactual capabilities testable rather than asserted?
- Can the system detect proxy-goal divergence and unintended side effects?
- Does metacognition measure actual competence, or merely reproduce self-reported confidence?
- Can affect/valuation influence learning and decisions without becoming a fixed rule engine?
- Are external authorization and execution boundaries preserved under urgency?
- Are failure, partial completion, cancellation, revocation and recovery fully represented?
- What foundational capability is missing, duplicated or prematurely decomposed?
- Which candidate invariants are genuinely necessary before implementation, and which are policy choices that should remain open?

### 15.11 Sources and evidence

**Marvel / MCU**
- Disney D23, [MCU Robot Roundup](https://d23.com/mcu-robot-roundup/) (2025). Official MCU overview of J.A.R.V.I.S.'s facility security, Stark Industries support, Avengers information role, Iron Legion control and transition into Vision.
- The Walt Disney Company, [Marvel Television's VisionQuest: Paul Bettany and James Spader on Vision's Journey of Self-Discovery](https://thewaltdisneycompany.com/news/marvel-television-visionquest-disney-plus/) (13 October 2026). Official current MCU source identifying J.A.R.V.I.S. as an AI persona embedded in Vision's programming and describing the security function attributed to J.A.R.V.I.S. in the series.
- U.S. Department of Defense, [Future Directions in Human-Machine Teaming Workshop Report](https://basicresearch.defense.gov/Portals/61/Future%20Directions%20in%20Human%20Machine%20Teaming%20Workshop%20report%20%20%28for%20public%20release%29_1.pdf) (15 January 2020). Analysis of contextual intent inference in a J.A.R.V.I.S. dialogue; a human-machine teaming research report, not a Marvel technical specification.

**Human cognition and AI learning**
- Badre, D. (2025), [Cognitive Control](https://www.annualreviews.org/content/journals/10.1146/annurev-psych-022024-103901), *Annual Review of Psychology*, 76, 167–195. Context-dependent behaviour selection and monitoring/adjustment.
- Mattar, M. G. and Daw, N. D. (2026), [Planning in the Brain: It's Not What You Think It Is](https://www.annualreviews.org/content/journals/10.1146/annurev-neuro-102124-015847), *Annual Review of Neuroscience*, 49, 435–450. Planning as a family of simulation- and learning-related computations, not only forward search.
- Gollwitzer, P. M. and Sheeran, P. (2025), [Psychology of Planning](https://doi.org/10.1146/annurev-psych-021524-110536), *Annual Review of Psychology*, 76, 303–328. If-then plans and goal pursuit; effects depend on goal and plan characteristics.
- Fleming, S. M. (2024), [Metacognition and Confidence: A Review and Synthesis](https://doi.org/10.1146/annurev-psych-022423-032425), *Annual Review of Psychology*, 75, 241–268. Confidence, uncertainty and inferential limits of self-evaluation.
- Rahnev, D. (2025), [A Comprehensive Assessment of Current Methods for Measuring Metacognition](https://www.nature.com/articles/s41467-025-56117-0), *Nature Communications*, 16, 701. Measurement validity, precision and context-dependent reliability.
- Sander, D. (2025), [Theories of Emotion for Human Affective Neuroscience](https://doi.org/10.1017/9781009342919.003), in *The Cambridge Handbook of Human Affective Neuroscience*. Comparison of major theoretical families and their differing explanatory emphases.
- [Associations between cognitive appraisals and emotions: A meta-analytic review](https://pubmed.ncbi.nlm.nih.gov/39404856/) (2024), *Psychological Bulletin*, 150(12), 1440–1471. Meta-analysis of appraisal-emotion relationships and remaining variation.
- Rehder, B. (2025), [A Rational Process Model of Reasoning Causally with Continuous Variables](https://pubmed.ncbi.nlm.nih.gov/40580681/), *Cognition*, 263, 106193. Causal inference under resource limitations and systematic error.
- Wang, L. et al. (2024), [A Comprehensive Survey of Continual Learning: Theory, Method and Application](https://pubmed.ncbi.nlm.nih.gov/38407999/), *IEEE Transactions on Pattern Analysis and Machine Intelligence*, 46(8), 5362–5383. Incremental knowledge acquisition, updating and use in changing environments.
- Furutachi, S. and Hofer, S. B. (2026), [Rethinking Predictive Processing](https://www.annualreviews.org/content/journals/10.1146/annurev-neuro-102124-031410), *Annual Review of Neuroscience*, 49, 471–494. Current debate about the interpretation and empirical support of predictive-processing signals.

### 15.12 Provisional conclusion

The Brain needs an integrated goal-directed control capability that connects contextual interpretation, goals, constraints, planning, simulation, intention, decision, action feedback and learning while preserving their distinct meanings and authority. Human cognition provides useful evidence about flexible control, simulation-supported learning, causal inference, metacognitive limits and affective modulation. MCU J.A.R.V.I.S. provides the system-level target of contextual, coordinated, timely support across technical environments. Engineering must provide the explicit contracts, provenance, safety boundaries, outcome verification, resource controls and learning validation that neither reference supplies.

This investigation is ready for independent challenge, not final architecture approval. It does not authorize a separate component for every functional responsibility, select an algorithm or technology, or authorize implementation.

---

## 16. Research-session update — 2026-11-01

- Re-entered the existing repository and verified the active documentation branch and PR #171 before continuing; no new project, branch or research log was created.
- Confirmed that Investigations A–D already exist in the working research record: information lifecycle/ownership, cognitive coordination/consistency, attention/resource allocation, and working context/active representations.
- Added Investigation E covering goals, planning, intentions, decisions, outcome feedback and the Brain-to-Governance-to-Action boundary.
- Updated the Marvel/MCU evidence baseline with official Disney material published 13 October 2026 about *VisionQuest*. This is a current-canon update, not evidence of a technical implementation.
- Added current 2025–2026 research references on cognitive control, planning, metacognition, emotion theories, causal reasoning, continual learning and predictive processing.
- Preserved all findings as provisional; no Brain architecture, component decomposition, technology allocation or implementation decision is approved by this update.
- No runtime code, tests, dependencies, approved whole-system architecture documents or PR merge state were changed.

**Reviewer handoff requested:** independently challenge Investigations A–E, with particular attention to cross-investigation consistency, whether the functional distinctions are justified without creating unnecessary subsystems, the MCU canon update, the neuroscience evidence and uncertainty labels, and the Brain/Governance/Action boundary. Identify missing foundational capabilities and adversarial/longitudinal tests before the architecture is consolidated.


---

## 17. Investigation F — Prediction, Belief Revision and Causal World Models

**Status:** Comparative analysis recorded; representational contracts, calibration methods and operational evaluation remain open.  
**Question:** How should the Brain form expectations about what may happen, compare them with what actually happens, revise its understanding, and distinguish correlation, causal explanation and counterfactual possibility?

### 17.1 Problem statement

Prediction is a foundational cognitive capability, but prediction, belief and observation are not interchangeable.

- An **observation/experience** records evidence received from a source.
- A **representation/model** expresses entities, relations, states or mechanisms inferred from evidence.
- A **belief** is a current epistemic commitment or qualified claim about the world, with supporting and opposing evidence.
- A **prediction** is a forecast about a future or unobserved state, conditional on assumptions and a model.
- A **simulation/counterfactual** explores a possible scenario that did not necessarily occur.
- A **prediction error** is a measured discrepancy between a forecast and a later observation; it is not, by itself, proof that the underlying model is wrong.
- A **belief/model revision** is a controlled change to current understanding after evidence and alternatives are assessed.

If these are collapsed, JARVIS may remember a forecast as a fact, treat its own generated hypothesis as independent evidence, overreact to noisy observations, or change a model for the wrong reason. Prediction error may arise from sensor noise, incomplete context, stochastic outcomes, execution failure, distribution shift or a genuinely defective model. The Brain must investigate which explanation is supported.

### 17.2 Marvel J.A.R.V.I.S. reference

The MCU portrayal provides examples of monitoring, diagnostics, analysis and contextual technical support. In *Iron Man* (2008), J.A.R.V.I.S. monitors suit status and assists with technical analysis; the Mark II test sequence shows the system reporting conditions and identifying a dangerous ice buildup. The D23 MCU overview describes J.A.R.V.I.S. as supporting Stark's facilities and technology and supplying information to the Avengers.

**Extractable requirement:** the assistant should maintain situation-sensitive expectations about system state, detect material deviations, communicate relevant uncertainty and connect outcomes to the task or system they concern.

**Limits:** the films do not disclose how J.A.R.V.I.S. represents a world model, calculates probabilities, distinguishes model error from sensor error, calibrates confidence, reasons causally or revises beliefs. A cinematic diagnostic warning is not evidence of a specific predictive-processing architecture.

**Canon caution:** the fight-pattern analysis in *Captain America: Civil War* is attributed to F.R.I.D.A.Y. in the official D23 overview, not J.A.R.V.I.S. Do not assign every later Stark-AI capability to J.A.R.V.I.S. merely because the systems are related.

### 17.3 Human cognition reference

1. **Prediction is a useful research lens, not a settled universal theory.** Predictive-processing accounts propose that internal models generate expectations and that discrepancies can contribute to updating. However, a 2024 review of predictive coding and active inference judged existing empirical support for predictive coding to be modest and noted that some findings can be explained by alternative models. Furutachi and Hofer's 2026 *Annual Review of Neuroscience* revisits the evidence and stresses that superficially similar prediction-error signals may reflect different underlying computations. The Brain must not be built on the assumption that all cognition is one prediction-error-minimization loop.
2. **Memory representations are transformed and task-sensitive.** Recent reviews describe multiple levels of episodic representation, from detailed event-specific information to generalized or gist-like representations. Retrieval can reconstruct an active representation using retrieved event information together with semantic, schematic and current task information. This supports a strict separation between the historical source record and revisable current representation.
3. **Fast and gradual learning have complementary demands.** Hippocampal research reviews discuss mechanisms relevant to rapid learning of individual episodes and gradual extraction of structure across experience. Complementary-learning-systems theory offers a useful account of the tension between retaining specific episodes and generalizing across them. It is a biological theory, not a requirement to create two literal software memory modules.
4. **Causal inference goes beyond association.** Human learners can infer abstract relations and use them in novel tasks, but causal reasoning is resource-limited and can be systematically wrong. A model of causal reasoning published in 2025 explicitly addresses both rational inference and limitations in computation. The Brain should distinguish observed association, hypothesized mechanism, intervention evidence and counterfactual prediction.
5. **Confidence and uncertainty are inferential.** Metacognitive confidence depends on a person's model of the world and of their own cognitive performance; it can diverge from correctness. Confidence must be evaluated against actual outcomes, and a single scalar confidence value cannot replace evidence provenance, alternative hypotheses or calibration analysis.

**Extractable design lessons**
- Maintain an explicit distinction between observed evidence, current belief, forecast and hypothetical simulation.
- Represent predictions with scope, time horizon, assumptions, model version, uncertainty and evaluation criteria.
- Evaluate forecasts against later evidence without rewriting the original forecast or outcome.
- Diagnose prediction errors before changing beliefs or models.
- Preserve competing explanations where the evidence does not discriminate among them.
- Use causal and relational representations where evidence supports them; do not silently upgrade correlation into causation.
- Support both specific episodic retention and gradual abstraction/generalization.
- Track model uncertainty and the possibility that the system lacks a relevant representation altogether.

**Limits**
- Predictive processing is not a complete settled explanation of cognition.
- Human memory reconstruction and source confusion are vulnerabilities, not desirable implementation properties.
- Human causal reasoning and confidence are fallible.
- Neuroscience does not supply one universal probability calculus, belief-update rule or world-model architecture.

### 17.4 Comparison and provisional selection

**Provisional direction: a provenance-grounded predictive and belief-revision capability using explicit, typed epistemic state, with multiple model classes and evaluation methods rather than one universal predictive theory.**

Human cognition provides useful insight into prediction, memory transformation, causal inference and uncertainty, but its theoretical disputes must remain visible. MCU J.A.R.V.I.S. supplies the operational target of contextual monitoring and useful diagnostics. Engineering must supply explicit epistemic types, provenance, calibration, causal validation, versioning and recovery.

The Brain should support:
- predictions tied to a defined target, time horizon, assumptions and model version;
- probabilistic or otherwise uncertainty-aware outputs appropriate to the domain;
- alternative hypotheses and model disagreement;
- explicit distinction between predicted, simulated, observed and verified states;
- prediction/outcome matching and calibration over time;
- error attribution across source quality, context, model, execution and environment;
- selective belief/model revision with dependency invalidation;
- causal reasoning that distinguishes association, intervention and counterfactual claims;
- generalization tests on novel but related cases;
- explicit representation of unknown, insufficient evidence and out-of-distribution conditions.

No specific predictive-processing, Bayesian, active-inference, causal-graph or neural-network implementation is selected here.

### 17.5 Failure scenarios and required tests

1. A simulated future is stored as an actual event.
2. A forecast is silently overwritten after the outcome is known, hiding the original error.
3. The same derived claim is counted repeatedly as independent evidence.
4. A noisy sensor reading causes a large belief revision without source-quality assessment.
5. A prediction error caused by failed execution is attributed to the world model.
6. A distribution shift makes an old model unreliable, but its confidence remains unchanged.
7. A model explains all observed outcomes after the fact but has no prospective predictive value.
8. A correlation is treated as a causal mechanism.
9. A causal model predicts correctly in familiar cases but fails under intervention.
10. A counterfactual branch leaks into active belief state.
11. A new abstraction erases important exceptions or minority cases.
12. A specific episodic memory is overgeneralized into a universal rule.
13. Retrieval reconstructs context incorrectly and the reconstructed details are treated as original evidence.
14. Belief revision updates one state but leaves dependent predictions and plans stale.
15. Two models disagree but the system hides the disagreement behind an averaged confidence score.
16. Confidence increases through repetition without new independent evidence.
17. An unobserved or unmodelled state is forced into the nearest known category.
18. A forecast is scored using a metric that does not match its intended use or consequence.
19. A system-level outcome is treated as proof of a particular internal cognitive cause.
20. Repeated error-driven updates create oscillation or unstable belief changes.

### 17.6 Candidate invariants versus unresolved choices

**Candidate foundational invariants**
- Historical observations, derived representations, beliefs, predictions, simulations and verified outcomes remain distinguishable.
- Forecasts retain their original assumptions and model/version lineage.
- A prediction error triggers assessment, not automatic model mutation.
- Belief/model revisions preserve prior state and rationale.
- Confidence must be evaluated against performance and cannot substitute for evidence.
- Correlation, causal inference, intervention and counterfactual claims have distinguishable epistemic status.
- Unknown, stale, conflicting and out-of-distribution states are representable.
- Derived changes trigger dependency-aware review rather than silent propagation.
- A forecast cannot become a remembered event merely because it was vivid, repeated or used in planning.

**Unresolved choices**
- Which prediction classes are foundational and which are advanced capabilities.
- How uncertainty is represented across symbolic, numeric, linguistic and learned representations.
- Whether belief state is one integrated responsibility or several cooperating forms of epistemic state.
- Which calibration metrics are appropriate for each prediction class.
- How causal models are learned, tested and revised.
- How disagreement among models is surfaced and resolved.
- How model uncertainty, data uncertainty and execution uncertainty are separated.
- How privacy, retention and deletion apply to forecast history and simulated scenarios.

### 17.7 Reviewer challenge checklist

Challenge whether the proposal overstates predictive-processing neuroscience; whether prediction error is being treated as a single uniform signal; whether forecasts remain immutable for later calibration; whether epistemic types are precise enough to prevent simulation/experience confusion; whether causal claims are independently tested; whether generalization retains exceptions; whether confidence is calibrated rather than self-reported; whether belief revision and dependency invalidation interact correctly with A–D; and whether the proposal requires more architecture than the evidence justifies.

### 17.8 Sources and evidence

- Hodson, R., Mehta, M. and Smith, R. (2024), [The Empirical Status of Predictive Coding and Active Inference](https://pubmed.ncbi.nlm.nih.gov/38030100/), *Neuroscience & Biobehavioral Reviews*, 157, 105473. Review assessing empirical evidence and alternatives.
- Furutachi, S. and Hofer, S. B. (2026), [Rethinking Predictive Processing](https://www.annualreviews.org/content/journals/10.1146/annurev-neuro-102124-031410), *Annual Review of Neuroscience*, 49, 471–494. Recent reassessment of prediction-error evidence and explanatory scope.
- Rugg, M. D. and Renoult, L. (2025), [The Cognitive Neuroscience of Memory Representations](https://doi.org/10.1016/j.neubiorev.2025.106417), *Neuroscience & Biobehavioral Reviews*, 179, 106417. Active/latent representations and causal links to past experience.
- Tarder-Stoll, H. et al. (2026 issue; published online 2025), [Adaptive Episodic Memory: How Multiple Memory Representations Drive Behavior in Humans and Nonhumans](https://doi.org/10.1152/physrev.00005.2025), *Physiological Reviews*, 106(2). Detailed and generalized episodic representations.
- Liao, Z. and Losonczy, A. (2024), [Learning, Fast and Slow: Single- and Many-Shot Learning in the Hippocampus](https://www.annualreviews.org/content/journals/10.1146/annurev-neuro-102423-100258), *Annual Review of Neuroscience*, 47, 187–209. Hippocampal learning modes and cognitive maps.
- Singh, D. and Schapiro, A. C. (2026), [Evidence for Complementary Learning Systems Within the Hippocampus](https://pubmed.ncbi.nlm.nih.gov/42421581/), *Philosophical Transactions of the Royal Society B*. Evidence and debate about episode separation and structure learning.
- Rehder, B. (2025), [A Rational Process Model of Reasoning Causally with Continuous Variables](https://pubmed.ncbi.nlm.nih.gov/40580681/), *Cognition*, 263, 106193. Causal reasoning under computational limits.
- Fleming, S. M. (2024), [Metacognition and Confidence: A Review and Synthesis](https://doi.org/10.1146/annurev-psych-022423-032425), *Annual Review of Psychology*, 75, 241–268. Confidence and uncertainty.
- Disney D23, [MCU Robot Roundup](https://d23.com/mcu-robot-roundup/) (2025). Official MCU capability descriptions; distinguishes J.A.R.V.I.S. and F.R.I.D.A.Y.
- U.S. Department of Defense, [Future Directions in Human-Machine Teaming Workshop Report](https://basicresearch.defense.gov/Portals/61/Future%20Directions%20in%20Human%20Machine%20Teaming%20Workshop%20report%20%20%28for%20public%20release%29_1.pdf) (2020). Contextual J.A.R.V.I.S. dialogue analysis; not an internal technical specification.

### 17.9 Provisional conclusion

Prediction and belief revision should be treated as distinct but interacting cognitive capabilities, grounded in preserved evidence and explicit epistemic status. The Brain should not be architected around predictive processing as a universal law. It should support multiple prediction and inference methods, evaluate them empirically, preserve uncertainty and alternatives, and revise current understanding through traceable, dependency-aware processes.

---

## 18. Investigation G — Learning, Adaptation and Developmental Integrity

**Status:** Comparative synthesis recorded; detailed learning mechanism boundaries and validation policy remain open.  
**Question:** How can experience cause persistent improvement in the Brain without uncontrolled state mutation, catastrophic forgetting, test-specific hardcoding or a false claim that data storage alone constitutes learning?

### 18.1 Problem statement

Learning is the central developmental requirement. It is not synonymous with storing information, retrieving a record, updating one confidence value, changing a prompt, or fine-tuning a language model. A meaningful learning claim requires an experience-dependent change that persists, affects later behaviour and demonstrates appropriate transfer while controlling for regression and contamination.

The Brain must be capable of development without becoming an uncontrolled self-modifying system. It must be able to retain individual experiences, form abstractions, adjust strategies, discover limitations and improve its own cognitive performance while preserving identity lineage, historical evidence and safety boundaries.

### 18.2 Marvel J.A.R.V.I.S. reference

The MCU portrays J.A.R.V.I.S. as highly capable and integrated with Stark's technology. The stories show contextual interpretation, diagnostics and coordination, but they do not establish a verifiable process by which J.A.R.V.I.S. learns from experience, consolidates knowledge, generalizes to unseen situations, evaluates candidate adaptations or protects active cognition from interference.

The later J.A.R.V.I.S. integration into Vision is a narrative transformation of a fictional AI system, not evidence of an ordinary learning mechanism. The MCU's Ultron storyline demonstrates a serious caution about powerful autonomous systems and intended-purpose drift, but it is a fictional safety narrative rather than empirical evidence about AI development.

**Extractable requirement:** JARVIS should acquire durable capability through experience and remain coherent as its capabilities change.

**Limit:** Marvel does not supply a trustworthy technical blueprint for continual learning, self-modification, safe promotion, rollback or developmental evaluation.

### 18.3 Human cognition reference

1. **Rapid episode learning and gradual abstraction have different demands.** Hippocampal research discusses rapid encoding of specific experiences alongside mechanisms that extract regularities over repeated experiences. Complementary learning systems is a useful explanatory framework for this tension, but it remains a scientific model and should not be copied as a one-to-one software decomposition.
2. **Memory consolidation is selective and adaptive.** Experience is not indiscriminately converted into a permanent generalized rule. Details and abstractions may coexist, and retrieval/learning can be influenced by current goals and context. This supports separating episodic retention from generalization and behavioural adaptation.
3. **Cognitive control can change behaviour flexibly.** Badre's 2025 review emphasizes context-sensitive selection of behaviour and monitoring/adjustment. Learning should improve how the Brain selects and regulates behaviour, not merely increase a static database of responses.
4. **Planning and simulation can train future cognition.** Mattar and Daw's 2026 review discusses offline and prospective simulation as learning processes that can shape representations and strategies, not only as immediate decision search.
5. **Continual learning is an explicit AI engineering problem.** The 2024 TPAMI survey defines continual learning in terms of incremental acquisition, updating, accumulation and use of knowledge in dynamic environments. The field studies challenges including catastrophic forgetting, stability/plasticity trade-offs, transfer and evaluation. There is no single method that resolves all continual-learning problems.
6. **Confidence and affect can bias learning.** Metacognitive confidence may be inaccurate, and affective/valuation processes influence what is attended to and learned. Learning therefore requires external performance evidence and checks against self-reinforcing feedback, not only internal reward or confidence.

**Extractable design lessons**
- Preserve specific experience while also supporting generalization.
- Treat learning as multiple interacting processes with different timescales and evidence requirements.
- Separate candidate learning from active authoritative cognitive state.
- Evaluate transfer, retention, interference, regression and robustness before activation.
- Learn from verified outcomes and attributable consequences.
- Preserve the developmental lineage of models, strategies and capabilities.
- Permit partial learning and explicit uncertainty; not every experience must produce an immediate update.
- Allow the Brain to discover that a previous strategy or representation was wrong without erasing the historical reason it was adopted.

**Limits**
- Human consolidation does not prescribe software training pipelines or deployment controls.
- Biological fast/slow learning theories do not prove that two distinct artificial memory services are required.
- Human reward, affect and motivation cannot be copied as fixed numeric values without a justified functional model.
- AI continual-learning benchmarks often simplify the open-world, multimodal and long-horizon conditions expected of JARVIS.

### 18.4 Comparison and provisional selection

**Provisional direction: a multi-timescale, evidence-driven learning and adaptation capability with isolated candidate changes, independent evaluation, controlled activation, persistent lineage and recoverable rollback.**

Human cognition is the stronger source for the distinction between episode retention and gradual abstraction, and for the interaction of learning with attention, planning and control. MCU J.A.R.V.I.S. supplies the whole-system developmental target, not a learning algorithm. AI continual-learning research supplies concrete technical challenges and evaluation approaches, while engineering must provide governance, versioning, integrity and rollback.

A learning cycle should be capable of:
1. **Detecting a learning opportunity:** prediction mismatch, verified action outcome, repeated experience, explicit correction, new relation, changed environment or observed limitation.
2. **Preserving the source experience:** maintain original evidence, provenance, context and outcome status.
3. **Forming a learning hypothesis:** identify what may need to change and why; do not assume every error requires a model update.
4. **Selecting a learning route:** episodic retention, retrieval/index update, representation refinement, belief revision, parameter adaptation, strategy change, skill acquisition or a combination justified by the problem.
5. **Creating an isolated candidate:** record the target state, baseline, source evidence, method, assumptions and expected effect.
6. **Evaluating the candidate:** assess evidence quality, transfer, retention, interference, regression, robustness, calibration, resource cost and safety.
7. **Resolving conflicts:** merge compatible changes, preserve alternatives, defer uncertain changes or reject unsafe/incompatible candidates.
8. **Activating under control:** update the affected mechanism's authoritative state through an explicit, traceable transition; Learning coordinates but does not become owner of every cognitive state.
9. **Monitoring after activation:** compare actual later behaviour with expected improvement and watch for delayed regressions.
10. **Recovering if necessary:** restore a previous operational version where appropriate without erasing the developmental history or pretending later experiences did not occur.

This cycle is a conceptual capability model, not a mandatory serial pipeline or decision to create one component for each step.

### 18.5 Learning classes that must not be conflated

| Class | What changes | What it does not prove |
|---|---|---|
| Experience retention | A particular event becomes retrievable | Generalization or behavioural improvement |
| Memory organization | Retrieval, indexing or associations change | Correctness of the represented knowledge |
| Belief revision | Epistemic commitment or uncertainty changes | Improved underlying model or skill |
| Representation learning | Concepts, relations or abstractions change | Reliable use in future decisions |
| Predictive-model adaptation | Forecasting behaviour changes | Transfer beyond the evaluated distribution |
| Strategy learning | Selection of methods or plans changes | Safe performance in all contexts |
| Skill acquisition | A capability becomes more reliable or efficient | General intelligence or unrestricted autonomy |
| Metacognitive calibration | Estimates of competence/uncertainty improve | Actual domain competence unless measured |
| Governance/configuration change | Permitted operating constraints change | Cognitive learning; this is a separate authority domain |

A successful system may require several of these to interact, but they should not be collapsed into one vague "memory update."

### 18.6 Failure scenarios and required tests

1. New experience overwrites an established capability without regression testing.
2. The Brain stores every event but exhibits no persistent behavioural change.
3. A learning process memorizes training/test cases and fails on novel related situations.
4. Fast learning interferes with stable general knowledge.
5. Gradual abstraction erases important exceptions or context.
6. A candidate is evaluated against data that leaked from its training experience.
7. A candidate is activated while based on a stale baseline.
8. Concurrent candidates change dependent mechanisms incompatibly.
9. A failed action teaches the wrong lesson because the actual failure cause is misattributed.
10. A successful outcome reinforces an accidental correlation rather than a causal strategy.
11. The Brain overfits to a user's recent preference and forgets older standing constraints.
12. A strategy improves average reward but creates rare catastrophic failures.
13. Confidence improves while objective performance declines.
14. Repeated retrieval is mistaken for repeated independent experience.
15. The same event is replayed after recovery and produces duplicate learning.
16. A model rollback restores old behaviour but destroys later valid experience or lineage.
17. A candidate improves one task and causes negative transfer in another.
18. A training environment modifies live cognitive state before evaluation.
19. Learning is driven by an adversarial or manipulated reward signal.
20. A model update changes a decision while the corresponding plan is in progress.
21. Learning becomes permanently conservative because failures are over-penalized.
22. Learning becomes recklessly exploratory because short-term success is over-rewarded.
23. The Brain cannot explain which experiences caused a capability change.
24. A new capability is reported as learned without a reproducible before/after comparison.
25. A model-provider change is misrepresented as the Brain learning from experience.
26. A learning mechanism becomes an opaque hardcoded catalogue of stimulus-to-response mappings.

### 18.7 Candidate invariants versus unresolved choices

**Candidate foundational invariants**
- Experience retention and behavioural learning are separate claims.
- Learning candidates cannot silently mutate active authoritative state.
- Every material adaptation has evidence lineage, baseline, target, version and evaluation record.
- Activation is controlled, observable and recoverable.
- The affected mechanism retains ownership of its active state; Learning coordinates adaptation rather than owning all learned knowledge.
- Learning evaluation includes transfer, regression, interference and robustness, not only training performance.
- Failed, partial, rejected, cancelled and uncertain outcomes remain distinguishable.
- Replaying old experience cannot silently count as new independent evidence.
- Developmental history is preserved across rollback and recovery.
- Acquired behaviour is not replaced by hardcoded scenario-to-response rules.
- Learning does not grant permission to bypass Governance, Security or Action boundaries.
- The system may defer learning when evidence is weak or consequences are high.

**Unresolved choices**
- Which forms of learning are required in the first Brain foundation and which are later capabilities.
- Which state changes can be evaluated online versus in a controlled development environment.
- How to construct representative held-out and adversarial evaluation data.
- What evidence threshold permits activation for different consequence classes.
- How to evaluate transfer in open-ended environments.
- How to detect negative transfer and rare regressions.
- How to balance stability, plasticity, exploration and consolidation.
- How learning adapts when the environment changes or evidence is non-stationary.
- What rollback means for non-parametric memory, beliefs, strategies and relational representations.
- Which changes require human approval or governance review.
- How to measure whether learning is improving general cognitive capability rather than only a narrow benchmark.

### 18.8 Reviewer challenge checklist

Challenge whether the proposal distinguishes memory from learning; whether it relies too heavily on complementary-learning-systems analogies; whether candidate isolation and evaluation are feasible; whether transfer and regression tests are adequate; whether learning from action outcomes preserves correct causal attribution; whether active state can be changed atomically or safely; whether rollback preserves valid experience; whether the proposed mechanism can learn beyond hand-authored scenario mappings; and whether the design is genuinely a developmental Brain rather than an LLM wrapper with a memory store.

### 18.9 Sources and evidence

- Liao, Z. and Losonczy, A. (2024), [Learning, Fast and Slow: Single- and Many-Shot Learning in the Hippocampus](https://www.annualreviews.org/content/journals/10.1146/annurev-neuro-102423-100258), *Annual Review of Neuroscience*, 47, 187–209.
- Singh, D. and Schapiro, A. C. (2026), [Evidence for Complementary Learning Systems Within the Hippocampus](https://pubmed.ncbi.nlm.nih.gov/42421581/), *Philosophical Transactions of the Royal Society B*.
- Tarder-Stoll, H. et al. (2026 issue; published online 2025), [Adaptive Episodic Memory](https://doi.org/10.1152/physrev.00005.2025), *Physiological Reviews*, 106(2).
- Wang, L. et al. (2024), [A Comprehensive Survey of Continual Learning: Theory, Method and Application](https://pubmed.ncbi.nlm.nih.gov/38407999/), *IEEE Transactions on Pattern Analysis and Machine Intelligence*, 46(8), 5362–5383.
- Pham, Q., Liu, C. and Hoi, S. C. H. (2024), [Continual Learning, Fast and Slow](https://pubmed.ncbi.nlm.nih.gov/37831566/), *IEEE Transactions on Pattern Analysis and Machine Intelligence*, 46(1), 134–149.
- Badre, D. (2025), [Cognitive Control](https://www.annualreviews.org/content/journals/10.1146/annurev-psych-022024-103901), *Annual Review of Psychology*, 76, 167–195.
- Mattar, M. G. and Daw, N. D. (2026), [Planning in the Brain: It's Not What You Think It Is](https://www.annualreviews.org/content/journals/10.1146/annurev-neuro-102124-015847), *Annual Review of Neuroscience*, 49, 435–450.
- Furutachi, S. and Hofer, S. B. (2026), [Rethinking Predictive Processing](https://www.annualreviews.org/content/journals/10.1146/annurev-neuro-102124-031410), *Annual Review of Neuroscience*, 49, 471–494.
- Disney D23, [MCU Robot Roundup](https://d23.com/mcu-robot-roundup/) (2025), for the MCU capability boundary and distinction between J.A.R.V.I.S. and F.R.I.D.A.Y.

### 18.10 Provisional conclusion

The Brain requires genuine developmental machinery: experience must be capable of producing persistent, attributable and transferable changes in future cognition and behaviour. This requires more than memory storage and more than a model update. It requires learning hypotheses, candidate isolation, evaluation, conflict handling, controlled activation, outcome monitoring and recoverable developmental lineage. The proposed direction supports the governing principle — **engineer the mechanisms; let behaviour be acquired through experience** — without assuming that the Brain is complete at foundation stage or that every future capability must be hardcoded now.

This investigation is ready for independent challenge. It does not approve an implementation method, technology stack, component decomposition or autonomous self-modification authority.

---

## 19. Cross-investigation synthesis — A through G

The seven investigations are intended to describe interacting responsibilities within one Brain foundation, not seven independent products or a fixed serial pipeline.

| Investigation | Central cognitive problem | Cross-dependencies |
|---|---|---|
| A — Information lifecycle and ownership | What information exists, what it means, where it came from and who owns it | All mechanisms depend on trustworthy, typed and attributable information |
| B — Coordination and consistency | How cognitive mechanisms interact without losing coherence or corrupting state | All concurrent mechanisms, updates, failures and recovery |
| C — Attention and resource allocation | What receives processing, how resources are allocated and when work is interrupted | Goals, working context, prediction, learning, metacognition |
| D — Working context and active representations | What information and task state are actively available and resumable | Attention, memory, goals, reasoning, coordination |
| E — Goals, planning, intentions and decisions | What the Brain is pursuing, why, by what means and with what commitment | Context, memory, prediction, valuation, reasoning, governance/action boundaries |
| F — Prediction, belief revision and causal models | What the Brain expects, what it currently believes and how evidence changes understanding | Representation, memory, reasoning, planning, metacognition, learning |
| G — Learning and developmental integrity | How experience creates persistent improvement without destabilizing cognition | All mechanisms; verified outcomes; controlled candidate/activation lifecycle |

### 19.1 Integrated functional loop

The Brain's activity should be understood as a recurrent, branching and concurrent set of processes, not a mandatory sequence:

1. Experience is admitted with provenance and integrity context.
2. Current context and relevant retained information are assembled.
3. Attention allocates processing and selects what requires deeper work.
4. Representations and hypotheses are formed or retrieved.
5. Beliefs and predictions are evaluated against available evidence.
6. Goals, constraints and possible plans are considered.
7. Reasoning, simulation and valuation help compare alternatives.
8. The Brain may decide, defer, ask, monitor, learn, or form an action request.
9. Any external action request passes through the separate signalling, governance and action pathways.
10. Verified outcomes return as new evidence.
11. Prediction, belief, memory, strategy and metacognitive state may be reconsidered.
12. Candidate adaptations may be evaluated and activated under controlled developmental rules.

Not every experience requires every step. Some mechanisms may work in parallel; some may be skipped, suspended or revisited. The loop must not be interpreted as a global synchronous controller.

### 19.2 Foundational versus advanced versus acquired

**Foundational capacities** are the general mechanisms and contracts required to represent information, preserve evidence, coordinate state, allocate resources, maintain context, reason under uncertainty, form and revise goals/plans, evaluate predictions and support controlled learning.

**Advanced mechanisms** are more sophisticated capabilities that can be developed later when the foundation and evidence justify them. Examples may include richer causal/counterfactual reasoning, long-horizon planning, advanced self-modeling, broad skill acquisition, sophisticated affective modulation, multimodal world models and more complex social cognition. Their eventual design must be separately justified.

**Acquired capabilities and behaviours** are knowledge, preferences, associations, strategies, skills, habits and domain-specific competence that should develop through experience and controlled learning rather than being prewritten as a catalogue of responses.

These are capability categories, not a frozen subsystem list or implementation order. A capability may depend on both foundational mechanisms and later acquired development.

### 19.3 Cross-cutting requirements

The following concerns recur across A–G and should be treated as integrated architectural requirements:
- provenance and source lineage;
- distinction between evidence, inference, belief, simulation, intention and verified outcome;
- authoritative ownership and explicit contracts;
- context-sensitive attention and resource budgets;
- causal/version dependencies and stale-state handling;
- controlled interruption, suspension, recovery and resumption;
- calibrated uncertainty and visible disagreement;
- learning isolation, transfer, regression detection and rollback;
- privacy and access restrictions through derived data;
- separation of cognition, system coordination, authorization, execution, security and infrastructure;
- auditability of material state changes and decisions;
- longitudinal evaluation of persistent behavioural change.

### 19.4 Major unresolved architecture questions

The investigations are not yet sufficient to freeze the Brain architecture. Remaining questions include:
1. What are the smallest coherent cognitive responsibilities that must have independent state ownership, and which are simply operations over shared state?
2. What common representational contracts are essential without forcing all cognitive content into one universal schema?
3. How should different kinds of uncertainty, evidence strength, confidence, source reliability and model disagreement be represented?
4. What mechanisms are required for reasoning, abstraction, causal discovery and counterfactual validation beyond current sections?
5. How should valuation and affective modulation be integrated without hardcoding emotional categories or creating an unnecessary biological subsystem?
6. What form of self-monitoring and self-model is foundational, and what belongs to advanced development?
7. What learning capabilities are necessary at the earliest developmental stage, and which can be acquired or introduced later?
8. Which cognitive state transitions require atomicity, and which may converge asynchronously?
9. What is the minimum viable Brain interface to the future sensory, SYS-02, action, autonomic, defence, governance and development systems?
10. Which project-level choices require explicit Project Director approval before the Brain architecture can be finalized?

### 19.5 Consolidated reviewer challenge

The Reviewer should assess the integrated A–G model rather than reviewing each section in isolation. The central question is whether these capabilities can cooperate to produce persistent, experience-dependent, transferable improvement while maintaining coherent state, epistemic integrity and strict system boundaries. The Reviewer should also identify missing cognition that cannot be adequately represented by A–G, and challenge any apparent completeness claim.

**No final Brain architecture approval or implementation authorization is implied.**


---

## 20. Research-session update — 2026-11-01 (continued)

- Added Investigation F: prediction, belief revision and causal world models. The analysis explicitly treats predictive processing as a contested framework, separates prediction errors from model errors, and requires typed distinctions among observations, beliefs, forecasts, simulations and verified outcomes.
- Added Investigation G: learning, adaptation and developmental integrity. The analysis distinguishes experience retention from behavioural learning and records candidate isolation, evaluation, transfer, regression, controlled activation and developmental lineage requirements.
- Added an integrated A–G synthesis describing recurrent interactions, foundational versus advanced versus acquired capabilities, cross-cutting invariants and unresolved architecture questions.
- Expanded the independent Reviewer handoff on PR #171 to cover A–G as one integrated Brain foundation.
- The research record remains provisional. It is not the final Brain Foundation architecture, does not settle component boundaries or technology choices, and does not authorize implementation.
- The six-checkup request is only partially schedulable under the current automation limit: three one-time checkups were created; the remaining three were rejected because the account allows three active scheduled tasks. Their recorded run histories were checked and all three are pending with no run result yet.
- No runtime code, tests, dependencies, approved whole-system documents or merge state were changed.

**Remaining work before calling the investigation complete:** independently validate the source-to-claim mapping; investigate any missing cognitive capabilities (especially representation/reasoning integration, self-monitoring and language/contextual communication); challenge the cross-mechanism architecture for over-fragmentation and missing ownership; consolidate the whole-Brain foundation requirements and unresolved Project Director decisions; then verify the final research package and Reviewer handoff. Do not claim that a full 60-minute wall-clock period has elapsed merely because the research record has grown.
