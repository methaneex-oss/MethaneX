# Brain Foundation Mechanism Gap Analysis

**Status:** Research addendum for independent review — provisional, not an approved architecture  
**Date:** 2026-11-01  
**Project:** JARVIS Brain Foundation  
**Related research record:** `00_BRAIN_FOUNDATION_COMPARATIVE_RESEARCH_AND_DECISION_LOG.md`  
**Scope:** Close mechanism-level gaps identified after Investigations A–G. This document does not authorize implementation, technology selection, or detailed component design.

---

## 1. Why this addendum exists

The earlier A–G investigations primarily examined how cognitive information is represented, coordinated, maintained in working context, used in decisions and predictions, and changed through learning. They did not yet provide a sufficiently explicit account of several mechanisms that make those capabilities possible.

This addendum examines the missing mechanism families and the integration questions they create. It is deliberately not a complete Brain architecture. Its purpose is to expose dependencies, avoid premature subsystem decisions, and give the independent Reviewer concrete issues to challenge.

The governing principle remains:

> **Engineer the mechanisms; let behavior be acquired through experience.**

A mechanism may provide a capacity to associate, generalize, simulate, value, or reason. It must not encode an exhaustive catalogue of conclusions, preferences, emotional reactions, strategies, or task-specific behaviours that should instead develop through experience and governed learning.

## 2. Representational foundation — a cross-cutting prerequisite

A Brain cannot reliably coordinate perception, memory, prediction, reasoning and learning if each mechanism silently uses incompatible meanings for the information it exchanges. However, forcing every cognitive object into one universal representation would erase important differences between events, continuous signals, concepts, spatial structures, causal models, plans, language, and learned parameters.

### Provisional candidate direction: common envelope, plural typed representations

Investigate a minimum shared information envelope while preserving domain-appropriate internal structures. The common envelope should be evaluated for whether it needs to express:

- identity and type;
- content or a reference to modality-/task-specific content;
- source and provenance;
- event time, observation time and temporal validity where relevant;
- context and scope;
- epistemic status (observation, interpretation, hypothesis, belief, prediction, decision, verified outcome, etc.);
- uncertainty or confidence with a defined meaning, not an unqualified scalar;
- dependencies and supporting/contradicting evidence;
- version, derivation and lineage;
- ownership and access constraints.

This is a candidate contract, not a final schema. Not every field applies to every object. Uncertainty must not be collapsed into one number when the underlying uncertainty is about different things (measurement quality, source reliability, ambiguity, model uncertainty, or missing context).

### Why this matters

A 2026 Frontiers study describes ACT-R systems coupled to scalable vector-symbolic memory representations and compares external knowledge pipelines using an LLM and ConceptNet. The study demonstrates a concrete integration route between a process-oriented cognitive architecture and external knowledge representations; it also shows that the knowledge source can materially shape downstream cognitive-model behaviour. It therefore supports treating knowledge-source provenance and bias as architectural concerns, not just data-cleaning details. It does not establish that vector-symbolic memory or ACT-R is the right choice for JARVIS.

A 2025 Soar study identifies the gap between visual reasoning systems and general-purpose non-visual reasoning: visual capability that is not connected to broader reasoning remains narrow. This reinforces the need to investigate cross-representation grounding and translation rather than assuming that a common interface automatically produces integrated understanding.

**Reviewer challenge:** Is the proposed common envelope sufficient to preserve identity, provenance, context and uncertainty across modalities without turning into a rigid universal ontology? What information must remain native to each representation?

## 3. Mechanism families still requiring explicit architectural treatment

These are capability/mechanism families for investigation, not a proposed list of software modules. A distinct name does not automatically justify an independently owned component.

### 3.1 Perceptual interpretation and grounding

**Conceptual responsibility boundary:** SYS-03 acquires signals and prepares observations through modality-appropriate preprocessing. Its outputs are evidence-bearing observations or detection proposals, not authoritative interpretations of what the world contains. Preprocessing may include signal cleaning, segmentation, feature extraction, detection proposals or modality conversion; none automatically establishes an entity's identity, an event's meaning, or a belief about the world.

The Brain's perceptual-cognitive responsibility begins when it interprets prepared observations in context. It evaluates candidate entities, events, properties and relations; associates observations across time and modalities; grounds language and other symbols in current evidence and representations; preserves competing hypotheses; and revises beliefs when evidence warrants. This is a conceptual boundary, not a claim that sensory processing is technically simple or that SYS-03 cannot use learned perceptual models.

Questions:
- How are observations grouped into candidate entities, events, properties, relations and state changes while preserving the distinction between a sensor detection and the Brain's grounded interpretation?
- How is the same entity tracked across successive frames or observations when viewpoint, appearance, location or available features change, and how are identity breaks, occlusion, re-entry and mistaken continuity handled?
- How are cross-modal identity hypotheses formed (for example, whether a seen object and a heard sound share a source) without treating temporal coincidence as proof?
- How are event identity and continuity distinguished from repeated similar events, overlapping events or one event observed through different modalities?
- How are competing interpretations retained instead of prematurely selecting one?
- How are temporal continuity, object identity and missing/occluded information represented?
- How does the Brain distinguish acquisition uncertainty (signal quality, missing data, modality-specific detection limits) from perceptual-inference uncertainty (ambiguous identity, competing explanations and contextual assumptions)? These uncertainties remain separately attributable and may compound.
- How are conflicting sensory observations preserved and assessed against source reliability, timing, context, viewpoint and corroboration rather than silently averaged or overwritten?
- How does linguistic reference recognition (resolving a phrase or pronoun within discourse) differ from grounding that reference to an observed, remembered, hypothetical or currently unknown entity?
- How are symbols and language grounded in observed or otherwise evidenced entities and events?

Failure modes include false identity continuity, hallucinated attributes, modality conflict, premature closure and treating a sensor's confidence score as truth. A detector may propose an object with a score; the Brain must still assess whether it is the same entity seen earlier, whether another modality corroborates it, and whether the real-world interpretation is justified. Sensor confidence is not automatically the Brain's confidence in the inferred claim.

### 3.2 Association and relational discovery

Association is the discovery or activation of relationships between experiences, representations, concepts, events and outcomes. It is not identical to reasoning: an association can suggest a relation without establishing that the relation is causal or true.

Questions:
- What makes two experiences associable (similarity, temporal proximity, shared context, causal evidence, functional relation, learned structure)?
- How are weak associations kept distinct from validated relations?
- How can associations be strengthened, weakened, context-gated or forgotten without rewriting historical evidence?
- How does the system avoid spurious correlations and runaway associative activation?

A critical safeguard is to preserve the distinction between *co-occurrence*, *similarity*, *predictive relationship* and *causal relationship*.

### 3.3 Abstraction and generalization

Abstraction forms representations that capture common structure across particular experiences. Generalization applies acquired structure to cases not previously encountered.

Questions:
- What evidence justifies moving from specific episodes to a broader concept or rule?
- How are exceptions, context boundaries and counterexamples retained?
- Can an abstraction be revised or split when new experience reveals that apparently similar cases differ?
- How does the Brain detect overgeneralization and distribution shift?

A fixed hand-authored concept catalogue may bootstrap basic operation, but it cannot substitute for mechanisms that acquire and revise abstractions. Conversely, unconstrained generalization can create brittle stereotypes or false universal rules.

### 3.4 Reasoning and inference

Reasoning should not be treated as one undifferentiated operation. Candidate reasoning forms to investigate include deductive, inductive, abductive, analogical, causal, probabilistic and procedural reasoning, alongside metareasoning about whether further reasoning is worthwhile.

The architecture must distinguish:
- evidence from assumptions;
- a valid inference from a plausible hypothesis;
- correlation from causal explanation;
- a generated explanation from a verified explanation;
- a conclusion from the confidence and conditions under which it holds.

The first Brain foundation need not implement every sophisticated reasoning form. It must, however, avoid a design that makes later forms impossible to integrate or that treats fluent language generation as proof of reasoning correctness.

### 3.5 Imagination, mental simulation and counterfactual evaluation

Imagination is relevant as an internal capacity to construct candidate situations that are not currently observed. Planning and prediction depend on some ability to evaluate possible futures; counterfactual reasoning asks what might have happened under different conditions.

Questions:
- How are imagined/simulated states marked as non-observational?
- How are simulations constrained by current beliefs, causal models and known limitations?
- How are multiple possible futures represented without confusing them with predictions or facts?
- How are simulated outcomes compared with later real outcomes to improve the underlying model?

A strict provenance boundary is essential: an internally generated scenario must never be silently promoted to an observed event or historical memory.

### 3.6 Valuation and affective processing

Valuation concerns the significance of events and possible outcomes relative to needs, goals, constraints, risks and current internal state. Affective processing may modulate attention, memory, learning, urgency and action evaluation. These are related but should not be reduced to a hardcoded emotion label or a fixed emotion-to-action mapping.

Questions:
- What information contributes to valuation, and how are conflicts between goals or timescales represented?
- How can affective state emerge from interacting appraisals and internal conditions rather than stimulus-to-emotion lookup tables?
- How does affect influence cognition without becoming a substitute for evidence or authorization?
- How can the system learn that a previously useful valuation is no longer appropriate?

The existing SYS-06/endocrine-inspired question remains unresolved. Human physiology can motivate investigation of slow modulation, homeostasis and interactions between body state and cognition, but does not prove that JARVIS needs a separate endocrine subsystem. The Brain must not absorb external physical regulation simply to imitate biological anatomy.

### 3.7 Social cognition and teammate modelling

The human-machine teaming literature identifies shared models of self, teammate and team, together with common ground, joint attention, trust, predictability and communication of limitations. For JARVIS, basic collaborator/context modelling may be needed for reliable contextual assistance; richer theory-of-mind and multi-party social reasoning may be advanced capabilities.

Questions:
- How are explicit instructions distinguished from inferred intent?
- How are shared goals, commitments, task state and common ground maintained?
- How does the Brain represent uncertainty about another person's beliefs or intentions?
- When must it clarify rather than act on an inference?
- How does it avoid treating conversational fluency or anthropomorphic presentation as evidence of competence?

The model of a human collaborator is a fallible cognitive representation, not an authority source. Inferred intent cannot replace governance or authorization.

### 3.8 Language-mediated cognition

Language includes comprehension, reference resolution, pragmatics, grounding, discourse context and formulation. It is an important cognitive interface but should not be assumed to be the universal format of thought.

The architecture should permit language to interact with non-linguistic representations, memory, reasoning and action planning without requiring every internal state to be serialized as text. It should distinguish the user's literal words, inferred meaning, contextual assumptions and any resulting intention.

Programming-language selection is explicitly out of scope.

### 3.9 Metacognitive monitoring and corrective response

Monitoring is useful only if it can alter cognition in a controlled, evidence-sensitive way. It may identify stalled goal progress, insufficient evidence, unresolved contradiction, prediction/outcome mismatch, out-of-distribution input, a capability limitation, stale dependency, failed reasoning attempt, or uncertainty about whether an action was authorized, executed and verified. These observations do not dictate one fixed response.

Depending on the diagnosed problem and its consequences, corrective responses may include reconsidering an interpretation and reopening alternatives; seeking evidence from another modality or source; retrieving relevant experience and prior outcomes; revising assumptions, predictions, causal explanations or confidence; changing an unsuccessful reasoning approach; recognizing a capability limit, communicating uncertainty or requesting assistance; and suspending a conclusion or consequential action when evidence is insufficient.

The process should preserve evidence and rationale for a correction and later assess whether it improved outcomes. Monitoring is not an unrestricted executive: it cannot rewrite another mechanism's state, bypass ownership, override governance or certify its own diagnosis. It can raise concerns or request reconsideration; the relevant cognitive responsibility retains its defined authority. Generated explanations and self-reported confidence are not independent evidence of monitoring accuracy.

## 4. Integration is the central unresolved problem

Adding the mechanism families above as independent boxes would be a design failure if their state, timing, ownership and interactions are not coherent. Conversely, putting everything into one central controller risks a bottleneck, hidden global state and a single point of cognitive failure.

Three broad integration patterns warrant comparison; none is selected here:

1. **Central workspace / broadcast-oriented integration.** Mechanisms publish candidate contents to a shared workspace, with selective access or broadcast. Potential benefit: flexible cross-mechanism coordination. Risks: competition, bottlenecks, unclear authority, and the possibility that workspace access is mistaken for truth or priority.
2. **Distributed owner-managed coordination.** Mechanisms retain authoritative state for their responsibilities and exchange typed events/requests/results. Potential benefit: clear ownership, local evolution and failure containment. Risks: synchronization complexity, stale views, coordination overhead and fragmented context.
3. **Hybrid integration.** Owner-managed state combined with a limited shared active context/workspace and explicit coordination. Potential benefit: balance between local authority and global coordination. Risks: duplicated state, unclear source of truth and additional consistency rules.

The earlier B investigation's candidate direction—logical modularity and owner-managed cognitive responsibilities—does not decide among these runtime integration patterns. Logical responsibility boundaries must not be confused with process, machine or deployment boundaries.

### Integration invariants to test

- Every mutable cognitive state has a clear authority/owner.
- Consumers can identify whether information is current, derived, provisional or stale.
- Cross-mechanism updates preserve provenance and causal/dependency links.
- Concurrent updates cannot silently overwrite incompatible conclusions.
- A mechanism failure degrades affected capabilities without corrupting unrelated authoritative state.
- Mechanisms can cooperate without forcing all cognition through one serial pipeline.
- A shared workspace, if any, is a coordination facility, not a universal database or truth oracle.

## 5. Learning implications across these mechanisms

Learning is not a single final stage. Experience may change associations, abstractions, retrieval patterns, predictive models, reasoning strategies, valuations, language grounding and social expectations. Those changes have different risk profiles.

A candidate learning model must identify:
- what object is being updated;
- what experience and evidence support the update;
- whether the update is reversible;
- what other mechanisms depend on the changed representation;
- how conflicting evidence is handled;
- how the update is evaluated;
- how the previous state can be recovered where necessary.

Routine, low-impact and reversible adaptation should not be burdened with the same process as a material change to an active model, strategy or capability. At the same time, online adaptation must not be a loophole for silently changing safety-critical behaviour. The earlier G investigation's update-class-specific validation direction remains a hypothesis to test.

## 6. Evidence and implications from recent comparative work

- **Neuro-symbolic agentic AI survey (2026):** a systematic review of 178 papers (2020–November 2025) categorizes integration patterns across knowledge representation, learning/inference, logic/reasoning, explainability/trust and metacognition. Its reported low metacognition coverage (5% of reviewed papers) is a warning that combining symbolic and neural capabilities does not automatically produce adequate self-monitoring. It is a survey of a defined paper corpus, not proof that one integration pattern is superior.
- **Metacognitive architecture scoping review (2026):** identifies 35 cognitive metacognitive architectures across 101 reports and notes heterogeneous representations, algorithms and evaluation. The field's terminology and empirical evaluation are not sufficiently standardized to justify assuming that a named metacognitive subsystem is effective merely because it exists.
- **ACT-R / vector-symbolic memory study (2026):** demonstrates one route for coupling a cognitive process model with scalable external representations, while showing that source choice can influence behavioural outcomes. It motivates provenance, bias and evaluation requirements.
- **Visual-symbolic Soar integration (2025):** highlights that high-level visual reasoning and general-purpose non-visual reasoning can remain disconnected. Cross-modal integration must be demonstrated, not assumed.

## 7. Candidate evaluation scenarios for the Reviewer to challenge

The following scenarios are not a final test plan. They are probes for whether a proposed Brain foundation is genuinely integrated:

1. **Ambiguous observation:** several interpretations fit a qualified observation. The Brain must retain alternatives, identify uncertainty and seek additional evidence where useful.
2. **Conflicting sources:** two sources disagree about an entity or event. The Brain must preserve provenance, assess source/context differences and avoid overwriting history with a single unsupported answer.
3. **Novel category:** a new experience resembles several known categories but also contains a counterexample. The Brain must form or revise an abstraction without overgeneralizing.
4. **Prediction failure:** an expected outcome does not occur. The Brain must identify which assumptions or dependencies failed and update the appropriate model rather than merely log a failure.
5. **Counterfactual reasoning:** a simulated alternative is evaluated and later contrasted with the real outcome. The simulation must remain distinguishable from observed history.
6. **Valuation conflict:** immediate and long-term goals conflict. The Brain must represent the conflict and trade-offs without hardcoded stimulus-to-emotion or emotion-to-action rules.
7. **Ambiguous human intent:** context suggests an implicit request but the evidence is insufficient. The Brain must distinguish inference from explicit instruction and clarify when needed.
8. **Concurrent updates:** multiple mechanisms update related beliefs or representations. The system must preserve ownership, dependencies and consistency.
9. **Partial mechanism failure:** one mechanism becomes unavailable or returns stale results. The Brain must identify the limitation and avoid treating missing output as negative evidence.
10. **Learning regression:** a new experience improves one context but harms another. The Brain must detect the trade-off, preserve lineage and support revision or rollback.

Success must be measured by persistent, evidence-grounded changes in future performance across relevant contexts—not by the presence of modules, successful unit tests alone, fluent explanations, or claims that learning occurred.

## 8. Unresolved questions before a Brain architecture can be responsibly proposed

1. What is the minimum shared representational envelope, and which representations must remain modality- or mechanism-specific?
2. Which cognitive states require distinct authoritative ownership, and which are operations over shared representations?
3. Which integration pattern best supports coordination without a serial bottleneck or fragmented state?
4. What foundational perceptual, associative, abstraction and reasoning capabilities are required for the first developmental Brain?
5. What is the minimum useful simulation/imagination capacity, and how will simulated content remain epistemically separate?
6. How should valuation and affect modulate cognition without fixed behaviour mappings or bypassing evidence and governance?
7. Which social-cognitive capabilities are foundational for human collaboration, and which are advanced?
8. How should language interact with non-linguistic cognition?
9. How can online learning be bounded, evaluated and reversed according to update impact?
10. What system-level experiments can establish persistent experience-dependent behavioural change?

## 9. Explicit non-decisions

This addendum does **not** select:
- a central workspace, controller, blackboard, broadcast mechanism or distributed runtime topology;
- a symbolic, subsymbolic, vector-symbolic, neural or hybrid universal representation;
- a particular reasoning engine, model provider or learning algorithm;
- a dedicated affective, social-cognitive, imagination or metacognitive subsystem;
- programming languages, frameworks, databases, deployment or implementation layout;
- the final foundational-versus-advanced capability boundary.

These require comparative analysis against approved requirements and scenarios, followed by independent review and Project Director approval.

## 10. Reviewer handoff checklist

The independent Reviewer should challenge:

- whether the mechanism gap list is complete enough for a first Brain foundation investigation;
- whether any family is incorrectly treated as a separate subsystem rather than a capability or process;
- whether the Brain/SYS-03, SYS-02, SYS-04, SYS-06, SYS-07, SYS-10 and SYS-11 boundaries remain coherent;
- whether the common representational envelope is too broad, too narrow or too prescriptive;
- whether the integration-pattern comparison omits a materially different alternative;
- whether the proposed learning safeguards would permit genuine experience-dependent adaptation without uncontrolled mutation;
- whether the evaluation scenarios can expose false integration and false learning;
- whether the evidence supports the stated inferences and whether any source is being overinterpreted.

**Progression gate:** Do not begin the next phase—planning advanced Brain mechanisms—until this research package has been independently reviewed, material findings have been reconciled, and the Project Director has accepted the resulting foundation and scope. Reviewer approval alone does not authorize implementation or technology selection.

---

## References

1. Hakim, S. B., Adil, M., Velasquez, A., & Song, H. H. (2026). *Neuro-symbolic agentic AI: Architectures, integration patterns, applications, open challenges and future research directions*. Computer Science Review. https://doi.org/10.1016/j.cosrev.2026.100902
2. *How metacognitive architectures remember their own thoughts: A systematic scoping review* (2026). Artificial Intelligence Review. https://doi.org/10.1007/s10462-026-11669-5
3. Dulam, S., Gay, J. R., & Dancy, C. L. (2026). *New knowledge source pipelines for sociocultural representations in a cognitive architecture*. Frontiers in Psychology, 17. https://doi.org/10.3389/fpsyg.2026.1874556
4. *Towards visual-symbolic integration in the Soar cognitive architecture* (2025). Cognitive Systems Research, 91, 101353. https://doi.org/10.1016/j.cogsys.2025.101353
5. U.S. Department of Defense (2020). *Future Directions in Human Machine Teaming Workshop*. https://basicresearch.defense.gov/Portals/61/Future%20Directions%20in%20Human%20Machine%20Teaming%20Workshop%20report%20%20%28for%20public%20release%29_1.pdf
6. Laird, J. E., Lebiere, C., & Rosenbloom, P. S. (2017). *A Standard Model of the Mind*. AI Magazine. https://ojs.aaai.org/aimagazine/index.php/aimagazine/article/view/2744/0
