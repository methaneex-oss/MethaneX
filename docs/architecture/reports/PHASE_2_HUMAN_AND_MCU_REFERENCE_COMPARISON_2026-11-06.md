# Phase 2 Human-Cognition and MCU J.A.R.V.I.S. Reference Comparison

**Status:** Builder-prepared bounded comparison; awaiting independent review and Project Director disposition  
**Prepared:** 2026-11-06  
**Governing specification:** PR #174 accepted head `0811a59e46bf934e32e794f90e4e7d18d4e2bd97`  
**Architecture baseline:** PR #173 corrected head `97191111bc2573c14d391c0af9628db7b11f194b`  
**Main source baseline:** `1273ddbcd0087d189e01388ded2d362fb1e058d2`  
**Phase 2 map reviewed:** PR #179 prior head `6f2c2cf05196e69a48f5deefcc3f4609e258c19a`  
**Scope:** Bounded function-level comparison for BM-01 through BM-12. This is not a neuroscience implementation specification, a claim of biological equivalence, or an MCU capability certification.

## 1. Purpose and method

This register answers three different questions for each mechanism:

1. **Human cognitive reference:** What broad cognitive function is relevant, based on published cognitive science/neuroscience reviews?
2. **MCU J.A.R.V.I.S. functional inspiration:** What fictional assistant/system function is a useful product-design analogy?
3. **JARVIS repository evidence:** What does the pinned main source actually demonstrate, and what remains absent or partial?

The three columns are deliberately not interchangeable. Human research is empirical but incomplete and theory-dependent. MCU J.A.R.V.I.S. is fictional and may illustrate an interface or capability aspiration, not a scientifically validated cognitive mechanism. Repository code is implementation evidence and must be evaluated through source paths and tests, not resemblance.

The human comparison uses functional-level analogies. It does not infer that a software mechanism should reproduce a brain region, neurotransmitter, anatomical circuit or human subjective state. Human cognition is distributed, context-sensitive and multiply realized; BM boundaries are engineering responsibility boundaries, not biological modules.

The MCU comparison is deliberately limited to the on-screen J.A.R.V.I.S. assistant associated with Tony Stark in the Marvel Cinematic Universe. The relevant film corpus is the *Iron Man* / *Avengers* film continuity, including *Iron Man 3* and *Avengers: Age of Ultron*. The register uses broad fictional patterns such as conversational interaction, system/instrument monitoring, information analysis, simulation and technical orchestration as design analogies. It does not treat the fictional system as a scientific source, a complete cognitive architecture or evidence that JARVIS should copy its behavior. Marvel's official pages establish the relevant film franchise and fictional context, not a technical specification for J.A.R.V.I.S.

## 2. Comparison register

| Mechanism | Human cognitive function relevant to the comparison | MCU J.A.R.V.I.S. functional inspiration (fiction only) | Pinned-main implementation status / engineering implication |
|---|---|---|---|
| **BM-01 Experience intake and provenance** | Sensory and informational acquisition; source/context attribution; distinguishing observed events from remembered or inferred content. These are necessary prerequisites for later perception and learning, but no single human process provides a perfect provenance ledger. | Receive voice/system inputs and telemetry from Stark's environment and equipment. Analogy: multiple input channels and source-aware acquisition. Do not infer trustworthy provenance, calibrated sensors or robust epistemic separation from cinematic presentation. | Main event intake and journal/replay are real, but typed source reliability, receipt/event-time separation, derivation lineage and complete epistemic distinctions are incomplete. Reuse event continuity; strengthen evidence/provenance semantics before claiming BM-01 complete. |
| **BM-02 Representation and interpretation** | Perceptual organization, semantic cognition and context-sensitive language comprehension. Context and non-linguistic information contribute to interpretation; ambiguity and competing interpretations matter. | Interpret voice commands, visual/sensor data and contextual references in an ongoing interaction. Analogy: multimodal/contextual interpretation. The films do not specify a learning algorithm or establish general language grounding. | Main has representation and a compiled/test-registered perception utility, but the audited main CognitiveCycle does not call it. Donor PR #97 has a distinct integrated call path. Contextual operator-intent grounding remains open. |
| **BM-03 Continuity and memory** | Episodic memory, semantic knowledge and reconstruction at different levels of detail; retrieval is shaped by attention, current goals and prior knowledge. Human memory is reconstructive and fallible, not a perfect database. | Retrieve prior technical records, user/system history and stored plans when assisting Stark. Analogy: persistent information access and recall. Fiction does not demonstrate source-valid memory, forgetting policy or robust consolidation. | Main has journaled event memory, tier labels and attribute-overlap recall. Retrieved memories are not supplied to the inspected main reasoning premises. Semantic/procedural generality is not demonstrated. |
| **BM-04 Belief and world-state management** | Evidence integration, uncertainty, revision and maintenance of competing hypotheses about objects/events. Human judgment is vulnerable to bias; confidence is not truth. | Maintain a current technical/environmental situation model from sensor readings and records. Analogy: state estimation and conflict indication. Do not treat a fictional dashboard/state map as belief revision. | Main has belief and WorldModel projections with different conflict semantics, limited provenance and incomplete dependent-state invalidation. Retain plural claims, evidence lineage and revision history as requirements. |
| **BM-05 Association, causal modelling and prediction** | Associative learning, causal judgment and counterfactual mental simulation. Causal reasoning involves mechanisms and interventions beyond mere co-occurrence or correlation. | Run diagnostics, estimate system outcomes and simulate technical scenarios. Analogy: predictive analysis and simulation. A cinematic prediction is not evidence of causal discovery. | Main has bounded association/causal links and prediction resolution. Co-state changes do not establish causal effects; intervention, confounder, counterexample and held-out tests remain necessary. |
| **BM-06 Attention and active context** | Selective attention, working-memory maintenance and goal-dependent prioritization; attention and episodic memory interact. Human attention is limited and can be captured by irrelevant stimuli. | Prioritize alerts, surface relevant displays and keep current task information available. Analogy: task-relevant presentation and alert triage. Do not reduce attention to a fixed urgency score. | Main has an attention model and compact state metrics, but active-context ownership, multiple concurrent contexts, interruption and resumption are not demonstrated. |
| **BM-07 Affective appraisal and valuation** | Emotion and cognition interact across perception, attention, learning, memory and decision. Appraisal is context-sensitive; emotional categories and mechanisms remain scientifically debated. | Communicate urgency or status and assist with risk-sensitive technical choices. Analogy: prioritization and human-facing expression only. A fictional assistant's tone or alert severity is not evidence of affective experience. | Integrated affective appraisal is not established as a coherent main capability in the audited baseline; PR #97 is donor-only and includes engineered appraisal priors. Do not label heuristics as human emotion. |
| **BM-08 Goals, intent, planning and decision** | Goal selection, motivation, executive control, prospective planning and flexible action selection. Goal generation and goal pursuit are related but distinct problems. | Help Stark pursue tasks, prepare procedures and coordinate technical actions. Analogy: task decomposition and plan support. Film plots do not establish autonomous, experience-acquired motivation or safe authorization. | Main processes supplied goals, intent, planning and decision, but experience-acquired candidate-goal formation is not demonstrated. Brain decisions remain distinct from external authorization and verified execution. |
| **BM-09 Learning and developmental adaptation** | Learning across episodic, semantic, procedural and reinforcement-related systems; goal-directed learning can alter representations and future behavior. Generalization must be tested rather than assumed. | At most, use the fiction as an aspiration for improving assistance based on interaction and technical outcomes. The MCU portrayal is not a validated example of open-ended developmental learning. | Main learning is narrower than the specified cross-mechanism lifecycle. Donor strategy/prediction feedback and bounded transfer evidence must not be generalized into broad learning without controlled, held-out and longitudinal tests. |
| **BM-10 Metacognitive monitoring and control** | Confidence, performance monitoring, error detection and regulation of one's own cognitive processing. Confidence is an estimate that can be miscalibrated. | Self-diagnostics, reporting system limits and identifying failed subsystems. Analogy: operational self-monitoring. Do not infer subjective self-awareness from diagnostics. | Main reflection/self-model signals are aggregate and do not establish a complete evidence-aware detect → correct → evaluate loop. Metacognitive claims require calibrated performance evidence and causal corrective effects. |
| **BM-11 Integrated coordination and continuity control** | Cognitive control, task switching, working-memory coordination, interruption handling and adaptive selection of behavior under changing context. Human control is distributed and resource-limited. | Coordinate subsystems, manage task flow and maintain a coherent assistant interaction across devices. Analogy: orchestration and continuity. The fictional portrayal does not establish fairness, crash consistency or exactly-once external effects. | Main CognitiveCycle is a bounded single-pass coordinator. Donor runtime adds feedback-first scheduling and action/consequence paths with fairness, shutdown and queue-loss risks. Runtime contracts/tests are required before donor acceptance. |
| **BM-12 General reasoning and inference** | Reasoning over evidence, assumptions, causal models and counterfactuals; human reasoning is bounded and sensitive to representation and context. No single theory explains all reasoning. | Analyze information, answer technical questions and assist with scenario evaluation. Analogy: analytical assistance. Dialogue fluency is not proof of valid inference or evidence lineage. | Main ReasoningEngine is a bounded keyed-value/causal traversal prototype. Retrieved memory is not in its premises and its output lacks a downstream consumer in the inspected cycle. General reasoning is not established. |

## 3. Cross-mechanism implications

The useful human-cognition comparison is not a one-to-one component mapping. Several implications matter across the whole architecture:

1. **Attention and memory are coupled.** Retrieval and encoding should be evaluated in relation to task context and attention, not as isolated storage/retrieval calls.
2. **Affect is not a separate decorative layer.** Human research supports interactions among affect, perception, attention, memory and decision; it does not justify fixed stimulus-to-emotion or emotion-to-action tables.
3. **Causal reasoning requires more than correlation.** Candidate causal relationships need mechanism, counterfactual/intervention and alternative-cause evaluation.
4. **Goal generation is distinct from supplied-goal execution.** A system that plans a user-supplied objective has not demonstrated that it can form goals from experience.
5. **Metacognition is not a confidence field.** It requires evaluating confidence against outcomes, detecting limits and changing subsequent processing in a measurable way.
6. **Coordination is not a second cognitive authority.** A scheduler may coordinate mechanisms without owning beliefs, goals or identity.
7. **Learning claims require future effects.** A stored episode or changed scalar is not enough; the change must alter a later relevant behavior and survive appropriate held-out/restart evaluation.

## 4. Engineering rules derived from the comparison

- Use human cognition as a source of functional questions and constraints, not as a blueprint to imitate literally.
- Treat every human comparison as a hypothesis with an evidence citation and a stated limit.
- Treat MCU J.A.R.V.I.S. solely as fictional product/interaction inspiration. It may suggest user-facing qualities and integration scenarios; it cannot justify cognitive, emotional, causal or learning claims.
- Treat repository source and executed tests as the only evidence for what this implementation currently does.
- Preserve the governing principle: **engineer the mechanisms; let behavior be acquired through experience.**
- Do not hardcode the learned conclusion in the name of biological plausibility or fictional resemblance.
- Keep safety, authorization, integrity, resource bounds and state ownership deterministic where required; these are engineering constraints, not acquired cognition.

## 5. Scientific reference set

The following peer-reviewed reviews support the limited human-function comparisons above. They are not exhaustive and do not settle contested theories.

1. Badre, D. (2025). “Cognitive Control.” *Annual Review of Psychology*, 76, 167–195. https://doi.org/10.1146/annurev-psych-022024-103901
2. Schwartz, S. T., Yang, H., Xue, A. M., & Wagner, A. D. (2025). “Attending to Remember: Recent Advances in Methods and Theory.” *Current Directions in Psychological Science*. https://pubmed.ncbi.nlm.nih.gov/40964066/
3. Tarder-Stoll, H., Sekeres, M. J., Levine, B., & Moscovitch, M. (2026). “Adaptive episodic memory: how multiple memory representations drive behavior in humans and nonhumans.” *Physiological Reviews*, 106(2). https://doi.org/10.1152/physrev.00005.2025
4. Dolcos, F., et al. (2020). “Neural correlates of emotion-attention interactions: From perception, learning, and memory to social cognition, individual differences, and training interventions.” *Neuroscience & Biobehavioral Reviews*, 108, 559–601. https://doi.org/10.1016/j.neubiorev.2019.08.017
5. Phelps, E. A. (2006). “Emotion and Cognition: Insights from Studies of the Human Amygdala.” *Annual Review of Psychology*, 57, 27–53. https://doi.org/10.1146/annurev.psych.56.091103.070234
6. Molinaro, G., & Collins, A. G. E. (2023). “A goal-centric outlook on learning.” *Trends in Cognitive Sciences*, 27(12), 1150–1164. https://doi.org/10.1016/j.tics.2023.08.011
7. Gerstenberg, T. (2024). “Counterfactual simulation in causal cognition.” *Trends in Cognitive Sciences*, 28(10), 924–936. https://doi.org/10.1016/j.tics.2024.04.012
8. Fleming, S. M. (2024). “Metacognition and Confidence: A Review and Synthesis.” *Annual Review of Psychology*, 75, 241–268. https://doi.org/10.1146/annurev-psych-022423-032425
9. Fleming, S. M. (2026). “Towards an integrative neuroscience of metacognition.” *Nature Reviews Neuroscience*, 27, 789–806. https://doi.org/10.1038/s41583-026-01081-x
10. Gollwitzer, P. M., & Sheeran, P. (2025). “Psychology of Planning.” *Annual Review of Psychology*, 76, 303–328. https://doi.org/10.1146/annurev-psych-021524-110536
11. Mattar, M. G., & Daw, N. D. (2026). “Planning in the Brain: It's Not What You Think It Is.” *Annual Review of Neuroscience*, 49, 435–450. https://doi.org/10.1146/annurev-neuro-102124-015847
12. Fedorenko, E., Ivanova, A. A., & Regev, T. I. (2024). “The language network as a natural kind within the broader landscape of the human brain.” *Nature Reviews Neuroscience*, 25, 289–312. https://doi.org/10.1038/s41583-024-00802-4
13. Diamond, A. (2013). “Executive Functions.” *Annual Review of Psychology*, 64, 135–168. https://doi.org/10.1146/annurev-psych-113011-143750

## 6. Fictional-reference source boundary

- Marvel Studios, *Iron Man* (2008), *Iron Man 2* (2010), *The Avengers* (2012), *Iron Man 3* (2013), *Avengers: Age of Ultron* (2015), and later MCU appearances. The films themselves are the primary fictional texts for any scene-specific claim.
- Marvel's official *Iron Man 3* page: https://www.marvel.com/ironman3
- Marvel's official *Avengers: Age of Ultron* page: https://www.marvel.com/Ultron
- Marvel's 15th-anniversary discussion of the 2008 *Iron Man* film: https://www.marvel.com/articles/movies/iron-man-kevin-feige-jon-favreau-15-anniversary-interview

These official pages provide franchise/film context, not an authoritative technical specification of MCU J.A.R.V.I.S. The comparison above is therefore intentionally high-level. Any future scene-level mapping must cite the film and scene being discussed, and must not use the scene as scientific evidence.

## 7. Limitations and acceptance

- This register is a bounded comparison, not a systematic review of all cognitive science.
- Scientific sources are review-level entry points; individual claims should be checked against primary studies before they influence implementation decisions.
- Human cognition contains unresolved theoretical disagreements; the document records broad functions rather than choosing one theory as canonical.
- The MCU comparison is fictional and qualitative.
- The repository status column is pinned to the stated main commit and must be refreshed if main changes.
- This artifact does not authorize implementation, donor adoption, gate clearance or Phase 2 completion.

**Prepared by:** Main Builder role for documentation closeout.  
**Independent review:** Required; not yet performed on this artifact.  
**Project Director decision:** Required — accept this comparison artifact, or approve a bounded deferral with rationale and a later completion point.
