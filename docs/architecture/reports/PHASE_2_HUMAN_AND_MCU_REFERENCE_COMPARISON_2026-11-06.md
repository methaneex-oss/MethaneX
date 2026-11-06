# Phase 2 — Human Cognitive Functions and MCU J.A.R.V.I.S. Reference Comparison

**Date:** 2026-11-06  
**Project:** Existing JARVIS cognitive architecture  
**Specification baseline:** PR #174 accepted specification HEAD `0811a59e46bf934e32e794f90e4e7d18d4e2bd97`  
**Engineering source baseline:** `main` at `1273ddbcd0087d189e01388ded2d362fb1e058d2`  
**Phase 2 map:** PR #179 HEAD `6f2c2cf05196e69a48f5deefcc3f4609e258c19a`  
**Status:** Builder-prepared; not independently reviewed or accepted by the Project Director.

## 1. Purpose and epistemic boundary

This document evaluates whether the Phase 2 BM-01–BM-12 architecture has defensible functional analogies to (a) human cognitive functions and (b) the fictional J.A.R.V.I.S. portrayed in the Marvel Cinematic Universe (MCU). The comparison is intended to expose missing responsibilities, integration assumptions and overclaims. It is not a claim that the software is biologically equivalent to a human brain or equivalent to a fictional system.

Three evidence classes are kept separate:

- **Empirical human-cognition evidence:** findings and models reported in peer-reviewed cognitive science/neuroscience. These are bounded, contested and revised; they do not imply that the software should copy biological implementation.
- **Engineering hypothesis:** a proposed computational mechanism or interaction that may be useful but is not established merely because it resembles a human function.
- **Fictional reference:** a narrative capability or behavior attributed to MCU J.A.R.V.I.S. This is a design analogy only. Fiction supplies no scientific evidence and no acceptance proof.

The governing project principle remains: **Engineer the mechanisms; let behavior be acquired through experience.** Human and fictional references must not become hardcoded cognitive outcomes, fixed emotion mappings, preloaded preferences, or a requirement to imitate biological neural structures.

## 2. Comparison method

For each mechanism, the analysis asks:

1. What functional problem is the mechanism intended to solve?
2. Which human cognitive functions provide a defensible analogy, and what is actually established?
3. What fictional MCU J.A.R.V.I.S. behavior provides a useful interface/coordination analogy, if any?
4. What does the pinned repository actually demonstrate?
5. What engineering implication follows, and what must not be inferred?

A similarity of labels is insufficient. The relevant evidence is information flow, state ownership, lifecycle behavior, persistence, downstream use and measurable behavioral consequences.

## 3. BM-01–BM-12 comparison

### BM-01 — Experience intake and provenance

- **Human function / evidence:** Sensory systems acquire signals under modality-specific noise, temporal conditions and limited access. Human memory research also distinguishes encoding conditions and source/context information from later retrieval. This is a functional analogy, not a one-to-one mapping to a human sensory pathway.
- **Engineering hypothesis:** Preserve immutable acquisition evidence, source identity, timestamps, modality, integrity and derivation lineage before interpretation. Distinguish external observations from internal predictions, simulations and infrastructure events.
- **MCU reference:** J.A.R.V.I.S. receives sensor feeds, communications and telemetry from the environment and connected systems.
- **Repository evidence:** Main event intake and journal/replay provide a continuity foundation; the Phase 2 map identifies incomplete typed provenance/temporal semantics and a main production perception integration gap.
- **Implication / limit:** Preserve raw evidence and its provenance independently of interpretations. A sensor feed, provider acknowledgement or event-journal append is not proof that the interpreted content is true.

### BM-02 — Representation and interpretation

- **Human function / evidence:** Perception and language comprehension are context-sensitive and can involve multiple candidate interpretations under ambiguity. Predictive mechanisms in language comprehension are not unitary and are selectively engaged depending on task, resources and experience (Federmeier et al., 2026).
- **Engineering hypothesis:** Maintain plural interpretations, contextual grounding, alternative hypotheses and evidence lineage. Operator intent must be inferred from context and evidence, not fixed phrase/source lookup.
- **MCU reference:** J.A.R.V.I.S. interprets natural-language requests, sensor feeds and situational context.
- **Repository evidence:** Main has representation and perception utility code, but the audited main CognitiveCycle does not call the pipeline; donor PR #97 contains a separate integration path. Normalization/tokenization is not general semantic grounding.
- **Implication / limit:** Integrate interpretation into the production cognitive path only under separate authorization. Tests must show context changes interpretation and that raw evidence remains unchanged. MCU dialogue fluency is fictional behavior, not a grounding benchmark.

### BM-03 — Continuity and memory

- **Human function / evidence:** Human memory includes functionally distinct episodic, semantic and procedural forms; retrieval and encoding are affected by attention and context. Attention-memory interactions are an active research area, not a single settled mechanism (Cowan et al., 2024; Schwartz et al., 2025).
- **Engineering hypothesis:** Preserve episode lineage, support relevance-sensitive retrieval, distinguish retention from belief acceptance, and evaluate whether retrieved information materially helps later inference.
- **MCU reference:** J.A.R.V.I.S. appears to retain conversation, system and mission context across interactions.
- **Repository evidence:** Main has event-backed memory, metadata and retrieval infrastructure, but the audited cycle's retrieval is not shown to supply the reasoning premise set.
- **Implication / limit:** Measure retrieval usefulness and downstream influence, not merely stored-record count or successful recall. Do not infer human-like autobiographical memory or consciousness.

### BM-04 — Belief and world-state management

- **Human function / evidence:** Human judgments integrate evidence, prior knowledge, context and uncertainty; they are fallible and revisable. No single universal human belief-update rule is established.
- **Engineering hypothesis:** Represent claims with scope, provenance, temporal validity, support and contradiction; preserve revisions and avoid forced certainty.
- **MCU reference:** J.A.R.V.I.S. maintains a coherent operational picture of entities, threats and system conditions.
- **Repository evidence:** Main contains belief/world-model structures and revision-related paths, but Phase 2 identifies gaps in evidence lineage and dependent-state invalidation.
- **Implication / limit:** A working claim must remain distinguishable from an observation, interpretation, simulation or accepted fact. Operational consistency is not equivalent to human belief.

### BM-05 — Association, causal modelling and prediction

- **Human function / evidence:** Humans learn statistical regularities and make predictions, but correlation and temporal co-occurrence do not by themselves establish causation. Predictive processing is a family of theories and findings, not a settled single explanatory principle (Nagai, 2019; Furutachi & Hofer, 2026).
- **Engineering hypothesis:** Separate associations, causal hypotheses, predictions, outcomes and accepted causal claims. Resolve predictions only with attributable evidence meeting their scope and timing conditions.
- **MCU reference:** J.A.R.V.I.S. forecasts trajectories, consequences and tactical developments.
- **Repository evidence:** Main contains causal/prediction infrastructure; Phase 2 finds incomplete cross-mechanism learning and outcome attribution.
- **Implication / limit:** Require counterexamples, context and delayed-outcome handling. Do not claim predictive capability from stored prediction objects or fictional tactical accuracy.

### BM-06 — Attention and active context

- **Human function / evidence:** Attention selects information for further processing; working memory and attention interact bidirectionally. Executive functions include working memory, inhibition and cognitive flexibility (Diamond, 2013; Cowan et al., 2024).
- **Engineering hypothesis:** Allocate bounded processing capacity, retain active task context, handle interruption/resumption and detect starvation or oscillation.
- **MCU reference:** J.A.R.V.I.S. shifts focus among user requests, sensors, threats and concurrent tasks.
- **Repository evidence:** Main contains attention/context structures, but Phase 2 does not establish a complete multi-context interruption and resumption lifecycle.
- **Implication / limit:** Measure fairness, context preservation and resumption correctness. A priority scalar is not a model of human attention.

### BM-07 — Affective appraisal and valuation

- **Human function / evidence:** Emotion and appraisal research relates significance, goals, bodily/internal conditions and action tendencies, but there is no universally accepted fixed mapping from stimulus to emotion or emotion to action.
- **Engineering hypothesis:** Appraisal should be contextual, revisable and evidence-bearing; its influence should modulate attention, evaluation and learning without becoming an unconditional command.
- **MCU reference:** J.A.R.V.I.S. is portrayed with a stable conversational style and situationally appropriate responses; these are authored fictional traits.
- **Repository evidence:** Phase 2 identifies incomplete main integrated affective appraisal and donor-backed fragments.
- **Implication / limit:** Do not hardcode emotion labels or action consequences. Do not treat a conversational persona as evidence of affect, subjective experience or biological emotion.

### BM-08 — Goals, intent, planning and decision

- **Human function / evidence:** Goal-directed behavior involves interacting executive, memory, valuation and learning functions; goals can be maintained, revised or abandoned as context and evidence change.
- **Engineering hypothesis:** Distinguish supplied goals from internally formed candidate goals, candidate status from commitment, decisions from authorization, and plans from verified outcomes.
- **MCU reference:** J.A.R.V.I.S. interprets mission objectives, proposes plans and coordinates actions under Tony Stark's direction.
- **Repository evidence:** Main has goal/planning/decision structures, but experience-acquired candidate-goal formation is not demonstrated in the inspected path.
- **Implication / limit:** Require a traceable experience-to-candidate-goal path and counterevidence handling. Do not encode a fixed objective generator or treat MCU initiative as an implementation specification.

### BM-09 — Learning and developmental adaptation

- **Human function / evidence:** Learning and development are distributed across multiple interacting systems and are context- and experience-dependent. Predictive learning is one proposed developmental mechanism, not a complete account of cognition (Nagai, 2019).
- **Engineering hypothesis:** Candidate changes require evidence, evaluation, activation, persistence, later behavioral effect, transfer assessment and regression control across the relevant mechanism owners.
- **MCU reference:** J.A.R.V.I.S. is depicted as adapting to new information and operational demands.
- **Repository evidence:** Main demonstrates narrower numeric adaptation/evolution paths; Phase 2 does not establish broad cross-mechanism developmental learning.
- **Implication / limit:** A counter increment, model update or score improvement is not proof of learning. Require persistent experience-dependent behavioral change and evaluation in relevant and novel contexts.

### BM-10 — Metacognitive monitoring and control

- **Human function / evidence:** Humans monitor confidence, errors, uncertainty and task performance imperfectly; monitoring can guide strategy changes but is not infallible.
- **Engineering hypothesis:** Monitor evidence quality, contradictions, capability limits and downstream consequences; initiate proportionate correction and preserve its lineage.
- **MCU reference:** J.A.R.V.I.S. reports diagnostics, identifies anomalies and advises the operator.
- **Repository evidence:** Main has reflection/self-model/health-related components, but Phase 2 characterizes the corrective loop as incomplete.
- **Implication / limit:** Validate monitor calibration and whether corrective work improves outcomes. A self-report or health metric is not proof of accurate self-knowledge.

### BM-11 — Integrated coordination and continuity control

- **Human function / evidence:** Cognitive activity is coordinated across distributed processes and is affected by limited resources, interruption and competing goals. Human brain organization is not a direct blueprint for software scheduling.
- **Engineering hypothesis:** Maintain one authoritative cognitive state, explicit ownership, dependency freshness, concurrency reconciliation, interruption and recovery. Runtime acknowledgements must remain distinct from cognitive completion.
- **MCU reference:** J.A.R.V.I.S. coordinates sensors, tools, subsystems and actions while presenting a coherent interface.
- **Repository evidence:** Main has a bounded cycle/runtime/workspace architecture; donor PR #97 has richer runtime behavior with unresolved fairness, shutdown-feedback and result-loss risks.
- **Implication / limit:** Test end-to-end lifecycle and recovery. Do not mistake orchestration, queues or workspace snapshots for a second intelligence or cognitive authority.

### BM-12 — General reasoning and inference

- **Human function / evidence:** Human reasoning draws on working memory, long-term knowledge, language, executive control and context. It is fallible, bounded and influenced by prior knowledge; no single computational account covers all human reasoning.
- **Engineering hypothesis:** Reasoning episodes need explicit premises, assumptions, provenance, inference lineage, alternatives, contradictions, counterexamples, uncertainty and dependency freshness. Results must reach the appropriate downstream owner and be evaluated there.
- **MCU reference:** J.A.R.V.I.S. performs dialogue, diagnosis, planning support and tactical analysis in the narrative.
- **Repository evidence:** The accepted specification defines BM-12; Phase 2 identifies a main source gap where retrieved memories are omitted from reasoning premises and reasoning results are not consumed by the downstream cycle path.
- **Implication / limit:** Require evidence that memory changes inference and that qualified conclusions affect appropriate downstream computation. Fluent generated text is not proof of reasoning or learning.

## 4. Cross-mechanism conclusions

The human comparison reinforces that cognition should be treated as interacting functions rather than isolated modules. In particular:

1. Attention and memory interact; memory cannot be evaluated solely as a storage subsystem.
2. Interpretation, context and prior knowledge interact; a phrase lookup is not contextual language understanding.
3. Prediction and learning require outcome attribution and revision; prediction error alone does not prove learning.
4. Executive control and working memory interact; scheduling and active context need interruption/resumption semantics.
5. Goals, valuation, memory, prediction and reasoning must influence one another through explicit contracts without collapsing their state ownership.
6. Development is non-linear and context-dependent; a single linear pipeline is not a sufficient model of the intended Brain.
7. A persistent behavioral change is stronger evidence than the presence of a learning API, metric or candidate record.

These are engineering requirements inferred from functional comparisons, not claims that the software reproduces human cognition.

## 5. Fictional MCU reference: appropriate and inappropriate use

**Appropriate use**
- A coherent operator-facing interface across heterogeneous subsystems.
- Context continuity across dialogue and operational tasks.
- Explicit status, uncertainty and diagnostic reporting.
- Coordinated use of tools and sensor inputs under external authorization.
- Separation between recommendation, authorization, execution and verified consequence.

**Inappropriate use**
- Treating fictional abilities as scientific evidence or acceptance criteria.
- Copying plot-driven omniscience, instantaneous understanding or perfect prediction.
- Assuming a persona, emotion-like dialogue or self-reference demonstrates subjective experience.
- Encoding predetermined goals, preferences or stimulus-response mappings to imitate a scene.
- Using cinematic outcomes to justify unsafe autonomous execution or hidden side effects.

MCU J.A.R.V.I.S. is a product/design inspiration reference only. Its behavior is scripted by writers and constrained by narrative needs; it is not a technical system description.

## 6. Engineering decision register

| Topic | Supported conclusion | Not established / prohibited inference |
|---|---|---|
| Integrated cognition | Mechanisms need explicit recurrent interactions and shared evidence lineage | That the current repository already implements a complete Brain |
| Memory | Retention, retrieval, context and downstream use must be evaluated together | That storing more records produces understanding |
| Language grounding | Context and competing interpretations matter | That normalization/tokenization equals intent understanding |
| Learning | Persistent change must affect later behavior and survive recovery | That numeric adaptation alone proves broad learning |
| Affect | Appraisal may modulate cognition in context | Fixed stimulus-to-emotion or emotion-to-action rules |
| Goals | Candidate goals need evidence and developmental lineage | Hardcoded objective generation presented as acquired motivation |
| Reasoning | Premises, assumptions, uncertainty and downstream use must be inspectable | Fluent output or an inference class proves general reasoning |
| Coordination | One cognitive authority requires explicit lifecycle and failure semantics | Queues/workspaces/agents become independent cognitive authorities |
| MCU inspiration | Interface and coordination analogies can guide design questions | Fiction proves scientific validity or software capability |

## 7. Limitations and review requirements

- This is a bounded conceptual comparison, not a systematic review of cognitive science.
- The cited literature includes theoretical models and active debates. The document does not claim consensus where none exists.
- Human cognitive functions are heterogeneous and context-sensitive; the comparison is functional, not anatomical.
- MCU references are intentionally limited to fictional behavior; no claim is made about a real implementation.
- Repository statements are pinned to the stated main/PR baselines. They are not claims about later revisions.
- The document does not select algorithms, data structures, APIs, providers, databases, deployment topology or implementation sequence.
- The document does not authorize runtime implementation, donor merge, deployment, Gate A/Gate B clearance or production action.

**Primary owner:** Main Builder / architecture evidence owner.  
**Independent review:** Required before acceptance.  
**Project Director decision:** Required to accept this artifact or approve a bounded deferral.  
**Current status:** Submitted for independent review; not accepted.

## 8. References

1. Diamond, A. (2013). Executive Functions. *Annual Review of Psychology*, 64, 135–168. https://doi.org/10.1146/annurev-psych-113011-143750
2. Cowan, N., Bao, C., Bishop-Chrzanowski, B. M., Costa, A. N., Greene, N. R., Guitard, N., Li, C., Musich, A. N., & Ünal, Z. E. (2024). The Relation Between Attention and Memory. *Annual Review of Psychology*, 75, 183–214. https://doi.org/10.1146/annurev-psych-040723-012736
3. Schwartz, S. T., Yang, H., Xue, A. M., & Wagner, A. D. (2025). Attending to Remember: Recent Advances in Methods and Theory. *Current Directions in Psychological Science*. https://doi.org/10.1177/09637214251339452
4. Federmeier, K. D., Chiu, H.-S., Fisher, C. L., et al. (2026). Prediction in language comprehension across the lifespan. *Nature Reviews Psychology*, 5, 595–611. https://doi.org/10.1038/s44159-026-00599-2
5. Nagai, Y. (2019). Predictive learning: its key role in early cognitive development. *Philosophical Transactions of the Royal Society B*, 374(1771), 20180030. https://doi.org/10.1098/rstb.2018.0030
6. Furutachi, S., & Hofer, S. B. (2026). Rethinking Predictive Processing. *Annual Review of Neuroscience*, 49, 471–494. https://doi.org/10.1146/annurev-neuro-102124-031410

**End of comparison document.**
