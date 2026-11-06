# Phase 2 — Human Cognition and MCU J.A.R.V.I.S. Functional Reference Comparison

**Status:** Draft architecture evidence; not independently reviewed or Project Director accepted.  
**Date:** 2026-11-06  
**Requirements baseline:** Accepted Brain Mechanism Specification, PR #174 exact HEAD `0811a59e46bf934e32e794f90e4e7d18d4e2bd97`, file blob `3b6a53c8a295fa0d9fc29bbb6c7688b61d1dcdb1`.  
**Source-mapping baseline:** Main `1273ddbcd0087d189e01388ded2d362fb1e058d2`; current working map PR #179 branch.  
**Purpose:** Satisfy Phase 2 acceptance criterion 10 by comparing BM-01–BM-12 against (a) defensible human cognitive functions and (b) the fictional MCU J.A.R.V.I.S. as a functional inspiration. This document does not authorize biological imitation, runtime implementation, donor adoption, or claims of human-equivalent cognition.

## 1. Interpretive rules

### 1.1 Three distinct evidence classes

1. **Human empirical/scientific reference:** findings from cognitive psychology, neuroscience and computational cognitive science. These are constrained, debated and often task-specific. They motivate functional requirements; they do not prescribe a literal software architecture.
2. **MCU J.A.R.V.I.S. fictional reference:** a narrative portrayal of an integrated artificial assistant that coordinates information, technical systems and action. It is a product-vision lens only. It is not empirical evidence, a validated architecture, or a specification of how intelligence works.
3. **JARVIS software mechanism:** the concrete state, dataflow, algorithms, interfaces, safety controls and evaluation contracts implemented in this repository. It must be justified by engineering evidence and the accepted Brain specification.

A similarity at the functional level does not establish shared internal mechanisms. A fictional capability shown on screen is not evidence that the corresponding real-world mechanism is feasible, safe or solved.

### 1.2 Important scientific limits

- Human cognition is not a single centralized serial pipeline. Processes interact recurrently, compete for resources, use multiple memory systems and vary with task/context.
- Predictive-processing and active-inference accounts are influential theoretical families, but a 2024 review reports only modest empirical support for predictive coding and calls for further validation of active-inference scope. Do not treat one predictive-processing theory as settled neuroscience.
- Metacognition is not necessarily one fully domain-general monitor. Reviews describe important commonalities but also limits and domain/task dependence.
- Emotion is not a fixed stimulus-to-label lookup table. Affective processes interact with perception, attention, memory, learning and decision-making.
- Reinforcement learning and working memory interact; they should not be treated as isolated, mutually exclusive faculties.
- Human learning depends on coordination among attention, memory, executive function, emotion regulation, metacognition and self-regulation.

## 2. Cross-cutting reference principles

| Reference principle | Human evidence / functional lesson | Software consequence | What must not be inferred |
|---|---|---|---|
| Coordinated learning | Attention, memory, executive function, emotion regulation and metacognition cooperate in learning [H1] | Test interacting mechanisms and later behavioral change, not isolated APIs | That a single module called “learning” implements learning |
| Memory is plural and interactive | Multiple memory systems and working-memory/reinforcement-learning interactions are documented [H2, H3] | Separate event continuity, working context, semantic/procedural abstractions and retrieval; test how each changes decisions | That a single vector store or tier label is equivalent to human memory |
| Affective-cognitive interaction | Emotion-related representations influence perception, attention, memory and decisions [H4] | Appraisal must use context/evidence and affect downstream processing without hardwired universal reactions | That a scalar “emotion” variable captures human affect |
| Context-sensitive control | Cognitive control supports context-dependent behavior selection and monitoring [H5] | Recurrent control should arbitrate among goals, context, uncertainty and feedback | That a fixed priority table is flexible control |
| Uncertainty and self-evaluation | Metacognitive confidence is inferential and can diverge from objective performance; domain generality is limited [H6, H7] | Keep confidence, evidence quality, calibration and self-model distinct; test calibration per task | That confidence is truth or that one confidence score is globally calibrated |
| Prediction is a hypothesis family | Predictive-processing theories have an active but contested empirical status [H8] | Treat prediction/error as testable computational mechanisms, compare alternatives and ablations | That “the brain predicts” validates any particular predictive-coding implementation |

## 3. BM-01 through BM-12 comparison

### BM-01 — Experience intake and provenance

- **Human functional reference:** sensory systems transform physical energy into neural signals through modality-specific pathways; perception depends on both incoming signals and context. The relevant lesson is the need to preserve the distinction between an external event, the available sensory sample, and the system's interpretation.
- **MCU reference:** J.A.R.V.I.S. is portrayed as receiving information from Stark's environment and connected technical systems and making it available to the broader assistant/control function.
- **Software mechanism:** typed acquisition adapters; source, timestamp, modality, acquisition conditions, integrity, transformation history, uncertainty and observer identity; explicit distinction between raw observation, normalized representation and inferred claim.
- **Functional overlap:** multiple information channels feed a common decision-support system.
- **Difference:** human sensory transduction is biological and modality-specific; software adapters receive already digitized/provider-defined data. MCU sensing is fictional and does not specify calibration, missingness or provenance.
- **Cannot infer:** that a successful API call means an observation is accurate, complete, independent or externally verified.
- **Required tests:** malformed/partial input; provider unavailable/throws; stale timestamps; duplicated/replayed observations; conflicting sensors; raw-event preservation under normalization failure; provenance lineage to every derived belief.

### BM-02 — Representation and interpretation

- **Human functional reference:** perception and cognition construct task- and context-sensitive representations; categorization and interpretation are not identical to raw sensation. Top-down expectations can assist interpretation but can also bias it.
- **MCU reference:** J.A.R.V.I.S. presents synthesized situation descriptions and technical interpretations rather than merely relaying sensor bytes.
- **Software mechanism:** explicit representations with source lineage, context, alternatives, ambiguity, confidence and reversible derivation; contextual language/operator-intent grounding must remain distinct from candidate-goal formation.
- **Functional overlap:** transform heterogeneous observations into usable structured context.
- **Difference:** software representations are explicit data structures and algorithms; human representations are distributed, embodied and only partially accessible to introspection. The fictional assistant's interpretation accuracy is narratively assumed.
- **Cannot infer:** that normalization, parsing, embeddings or a fluent explanation establish grounded understanding.
- **Required tests:** ambiguous inputs; context reversal; out-of-distribution samples; contradictory sources; lossless provenance; parser/provider failure; abstention when interpretation is underdetermined.

### BM-03 — Continuity and memory

- **Human functional reference:** memory includes distinct but interacting processes, including working memory and long-term systems; encoding, consolidation and retrieval are affected by attention, goals and value. Working memory and reinforcement learning interact [H2, H3].
- **MCU reference:** J.A.R.V.I.S. retains operational context and historical system information across tasks in the fictional portrayal.
- **Software mechanism:** durable event continuity plus separately governed metadata/semantic/procedural abstractions; provenance-aware retrieval; consolidation and forgetting as explicit, recoverable state transitions.
- **Functional overlap:** past experience informs current interpretation and action.
- **Difference:** software persistence is explicit serialization and retrieval; biological memory is reconstructive and distributed. A journal is not semantic memory; a metadata tier is not a human memory system.
- **Cannot infer:** that storing events, ranking records or persisting a tier proves acquired knowledge or useful recall.
- **Required tests:** corruption and truncation matrix; all-or-nothing metadata restoration; duplicate/unknown record handling; restart/replay; retrieval relevance; memory-to-reasoning influence; forgetting/consolidation rollback; changed future predictions on held-out contexts.

### BM-04 — Belief and world-state management

- **Human functional reference:** people maintain and revise representations of the world under uncertainty, with source reliability, prior expectations and contradictory evidence affecting judgment. These representations can be incomplete or wrong.
- **MCU reference:** J.A.R.V.I.S. maintains a coherent operational picture of people, devices, locations, suit state and mission conditions.
- **Software mechanism:** one authoritative Brain belief/world-state owner; preserve multiple claims, provenance, epistemic status, contradictions, freshness and dependency links; do not silently collapse disputed evidence.
- **Functional overlap:** maintain a current model used by multiple downstream processes.
- **Difference:** software state is explicitly addressable and must define conflict-resolution semantics; human beliefs are not stored in one globally consistent database. MCU displays often imply a single accurate state.
- **Cannot infer:** that a coherent data model guarantees truth, completeness or calibrated uncertainty.
- **Required tests:** contradictory evidence; source reliability changes; stale dependency invalidation; replay; independent-source corroboration; belief revision without erasing provenance; competing WorldModel/Brain projection consistency.

### BM-05 — Association, causal modelling and prediction

- **Human functional reference:** people learn statistical regularities and make causal inferences, but correlation, temporal order and co-occurrence are not sufficient for causal identification. Human causal judgments can be biased and context-dependent.
- **MCU reference:** J.A.R.V.I.S. predicts likely system states and consequences to support tactical and technical choices.
- **Software mechanism:** distinguish association from causal hypotheses; record interventions/observations, confounders, counterexamples, sample coverage, uncertainty and prediction lineage; compare predictions with independently observed outcomes.
- **Functional overlap:** use learned relationships to anticipate consequences.
- **Difference:** software causal models are explicit and inspectable but can encode wrong assumptions; human causal reasoning uses richer embodied/social context but is also fallible. MCU prediction is plot-level capability.
- **Cannot infer:** that a changed belief snapshot establishes causation or that prediction accuracy on a narrow synthetic environment proves open-world causal reasoning.
- **Required tests:** confounded correlation; intervention vs observation; reversed relationships; counterexamples; delayed outcomes; missing outcomes; held-out contexts; calibration; causal ablations.

### BM-06 — Attention and active context

- **Human functional reference:** attention is selective and resource-limited; task goals, salience, emotion and expectations affect what is processed. Control must manage competition and shifting demands.
- **MCU reference:** J.A.R.V.I.S. prioritizes mission-relevant alerts and system information while coordinating multiple concurrent activities.
- **Software mechanism:** explicit attention allocation with reasons, urgency, uncertainty, resource cost, fairness and starvation bounds; context selection must be revisable as evidence changes.
- **Functional overlap:** prioritize limited processing and expose relevant information.
- **Difference:** software scheduling operates over queues, compute and explicit policies; human attention includes perceptual and cognitive constraints not reducible to scheduler priority. Fiction rarely exposes starvation or fairness failures.
- **Cannot infer:** that sorting by a salience score is equivalent to attention or that high priority should always preempt other work.
- **Required tests:** sustained high-priority load; fairness; task switching; interruption recovery; salience conflict; attention allocation under uncertainty; starvation detection.

### BM-07 — Affective appraisal and valuation

- **Human functional reference:** affective processes are integrated with perception, attention, memory, learning and decision-making; emotion is not simply a separate output added after cognition [H4].
- **MCU reference:** J.A.R.V.I.S. communicates urgency, concern and risk in a socially legible manner, but this is characterization, not evidence of an internal affective system.
- **Software mechanism:** context-sensitive appraisal of relevance, goal impact, uncertainty and anticipated consequence; maintain appraisal as a revisable internal estimate with provenance; allow it to modulate attention/learning without fixed stimulus-to-emotion tables.
- **Functional overlap:** valuation changes what is prioritized and how outcomes affect future processing.
- **Difference:** human affect is embodied, physiological, subjective and socially situated; software appraisal is an engineered control signal. A natural-sounding expression does not imply subjective feeling.
- **Cannot infer:** consciousness, sentience, human emotion, or a universal emotional meaning from a software affect value.
- **Required tests:** same event under different goals/context; reversed consequence; uncertain attribution; affect/attention interaction; no fixed stimulus mapping; downstream behavior change; calibration and harmful overreaction checks.

### BM-08 — Goals, intent, planning and decision

- **Human functional reference:** executive functions support planning, sequencing, inhibition, context-sensitive action selection and flexible adjustment toward goals [H5, H1].
- **MCU reference:** J.A.R.V.I.S. helps Stark plan and execute complex operations, coordinate devices and adapt assistance to mission demands.
- **Software mechanism:** distinguish externally supplied goals from experience-acquired candidate goals; track prerequisites, conflicts, expected outcomes, constraints and uncertainty; planning remains subordinate to safety/authorization.
- **Functional overlap:** select and sequence actions in relation to objectives and changing context.
- **Difference:** human goals arise from biological needs, social learning and personal values; software goals must be explicitly represented and governed. MCU goal autonomy is narrative.
- **Cannot infer:** that ranking supplied goals demonstrates autonomous goal formation or that cognitive intent authorizes an external action.
- **Required tests:** candidate-goal formation from experience; competing goals; prerequisite changes; goal abandonment/revision; changed context; action authorization denied/expired; plan interruption and recovery.

### BM-09 — Learning and developmental adaptation

- **Human functional reference:** learning is supported by interacting memory, attention, executive control, motivation/affect and feedback systems. Working memory can influence reinforcement learning and vice versa [H1, H3].
- **MCU reference:** J.A.R.V.I.S. appears to adapt assistance to Stark's evolving equipment and operational context; the films do not provide a validated account of how this learning occurs.
- **Software mechanism:** distinguish observation-based learning from action-outcome learning; attribute consequences; preserve uncertainty/provenance; update representations, beliefs, predictions or strategies; persist changes; demonstrate appropriate later behavioral change and revision.
- **Functional overlap:** prior experience changes future performance.
- **Difference:** human learning is biological and lifelong; software updates are explicit and must be tested for leakage, instability, reward hacking and unintended drift. Fiction compresses learning into narrative convenience.
- **Cannot infer:** learning from stored data, counters, confidence changes, a successful API call or performance on training examples.
- **Required tests:** matched fixed-policy/non-learning baseline; held-out contexts; reversed relationships; independent seeds; restart/replay; no-consequence control; contradiction and revision; persistent future behavior change.

### BM-10 — Metacognitive monitoring and control

- **Human functional reference:** metacognition includes evaluating and regulating one's own cognitive processes. Confidence is inferential and can be inaccurate; strong domain-general architectures are not established [H6, H7].
- **MCU reference:** J.A.R.V.I.S. reports system status, uncertainty-like warnings and performance limitations to its operator.
- **Software mechanism:** monitor prediction error, uncertainty, evidence sufficiency, subsystem health and calibration; distinguish confidence in a conclusion from confidence in the process that produced it; trigger review/abstention/escalation.
- **Functional overlap:** monitor internal processing and adjust behavior when reliability is low.
- **Difference:** software telemetry can be exact for measured variables but incomplete about its own blind spots; human metacognition is fallible and not a transparent readout of all cognition. MCU self-monitoring is fictional.
- **Cannot infer:** that a self-reported confidence value is calibrated or that a health dashboard is metacognition.
- **Required tests:** calibration curves; confidence under distribution shift; known blind spots; disagreement between confidence and outcome; abstention thresholds; monitoring-triggered correction; domain-specific validation.

### BM-11 — Integrated coordination and continuity control

- **Human functional reference:** cognition is distributed and recurrent; executive control, attention, memory, perception and action influence one another over multiple timescales [H1, H5].
- **MCU reference:** this is the strongest fictional inspiration: J.A.R.V.I.S. coordinates sensing, analysis, memory, communication and external technical action as one assistant.
- **Software mechanism:** one cognitive authority orchestrates recurrent processing, state ownership, dependency freshness, interruption, action authorization, observed consequence, durable updates and recovery. External systems remain explicit boundaries.
- **Functional overlap:** many mechanisms cooperate to produce coherent, context-sensitive behavior.
- **Difference:** a software coordinator is an engineered control architecture, not a brain; the MCU portrayal hides implementation complexity and failure cases. Distributed human cognition is not a single scheduler.
- **Cannot infer:** that a class named CognitiveCycle, a pipeline diagram or a multi-agent setup constitutes whole-brain integration.
- **Required tests:** end-to-end producer/consumer lineage; stale-state invalidation; concurrent updates; partial commits; shutdown; queue saturation; retry/idempotency; restart/replay; action consequence verification; one-authority invariant.

### BM-12 — General reasoning and inference

- **Human functional reference:** human reasoning includes deduction, induction, abduction, causal and analogical reasoning, and is affected by knowledge, context, working memory and cognitive biases. No single simple reasoning primitive captures all of it.
- **MCU reference:** J.A.R.V.I.S. synthesizes technical information and provides explanations/recommendations across varied tasks.
- **Software mechanism:** evidence-grounded inference with explicit premises, assumptions, provenance, uncertainty, contradictions, counterexamples, alternative hypotheses and conclusion lineage; retrieved memory can inform premises without becoming unquestioned truth.
- **Functional overlap:** derive and compare conclusions from evidence to guide decisions.
- **Difference:** software inference is limited by formalized representations and algorithms; human reasoning is broader but fallible and resource-bounded. Fiction portrays broad competence without specifying proof obligations.
- **Cannot infer:** that a consistency checker or shallow causal traversal is general reasoning, or that fluent explanation establishes valid inference.
- **Required tests:** empty premises => unresolved/insufficient evidence; contradiction; unsupported premise; stale memory; conflicting sources; alternative hypotheses; counterexample; causal confounding; conclusion provenance; downstream consumers reject unresolved results; held-out multi-step problems.

## 4. Whole-system synthesis

The useful human-cognition lesson is not “copy a human brain.” It is that cognition depends on interactions among mechanisms, context, uncertainty, resource limits, memory, control and feedback. The useful MCU lesson is not “copy the character's dialogue or appearance.” It is the product-level expectation that sensing, understanding, memory, reasoning, planning, communication and action support one coherent assistant.

The engineering synthesis is therefore:

1. Build explicit mechanism contracts and state ownership.
2. Preserve evidence lineage and uncertainty across transformations.
3. Allow recurrent, selective interaction rather than a fixed serial pipeline.
4. Separate cognitive intention from external authorization, execution and verified consequence.
5. Require durable, attributable learning that changes later computation.
6. Make failures, partial outcomes, stale dependencies and recovery observable.
7. Evaluate capability with controls and held-out contexts, not surface fluency or cinematic resemblance.

This is consistent with the project's governing principle: engineer the mechanisms; let behavior be acquired through experience.

## 5. Phase 2 relevance and current repository implications

This comparison is an architecture reference register, not proof that the corresponding capabilities exist in the current implementation.

- The current mainline integration map identifies significant gaps in acquisition/perception integration, memory-to-reasoning flow, downstream reasoning consumption, candidate-goal formation, affective appraisal integration, recurrent coordination and action/consequence learning.
- PR #97 remains a separate donor line. Its richer runtime behavior cannot be attributed to main or treated as an approved implementation baseline.
- The current mainline reasoning engine's empty-premise result and memory metadata recovery behavior remain technical findings requiring separately authorized implementation and tests.
- The mainline journal and Brain mutation-order findings require deterministic failure injection and replay evidence.
- The external executable host and authorization-grant lifecycle remain unresolved in the repository evidence reviewed for Phase 2.

## 6. Acceptance and review checklist

- [x] BM-01 through BM-12 each have a human functional reference, fictional MCU lens, software mechanism, overlap/difference, inference limit and test direction.
- [x] Human scientific claims are distinguished from engineering hypotheses and fictional inspiration.
- [x] Predictive-processing and metacognition are not presented as settled, universally general theories.
- [x] The comparison rejects literal biological imitation and surface-behavior equivalence.
- [x] Mainline implementation gaps are not presented as solved by this comparison.
- [ ] Independent reviewer challenges the scientific references, MCU interpretation, mechanism mapping and limits.
- [ ] Project Director accepts the artifact or records a bounded deferral.
- [ ] Cross-links from the canonical Phase 2 report and authority index are verified after review.

## 7. References

**Human cognition and neuroscience**

- [H1] National Academies of Sciences, Engineering, and Medicine. *How People Learn II: Learners, Contexts, and Cultures* (2018), Chapter 4, “Processes That Support Learning.” https://www.nationalacademies.org/read/24783/chapter/6
- [H2] Squire, L. R. & Wixted, J. T. “The Cognitive Neuroscience of Human Memory Since H.M.” *Annual Review of Neuroscience* 34 (2011), 259–288. https://doi.org/10.1146/annurev-neuro-061010-113720
- [H3] Yoo, A. H. & Collins, A. G. E. “How Working Memory and Reinforcement Learning Are Intertwined: A Cognitive, Neural, and Computational Perspective.” *Journal of Cognitive Neuroscience* 34(4) (2022), 551–568. https://doi.org/10.1162/jocn_a_01808
- [H4] Todd, R. M., Miskovic, V., Chikazoe, J. & Anderson, A. K. “Emotional Objectivity: Neural Representations of Emotions and Their Interaction with Cognition.” *Annual Review of Psychology* 71 (2020), 25–48. https://doi.org/10.1146/annurev-psych-010419-051044
- [H5] Badre, D. “Cognitive Control.” *Annual Review of Psychology* 76 (2025), 167–195. https://doi.org/10.1146/annurev-psych-022024-103901
- [H6] Fleming, S. M. “Metacognition and Confidence: A Review and Synthesis.” *Annual Review of Psychology* 75 (2024), 241–268. https://doi.org/10.1146/annurev-psych-022423-032425
- [H7] Mazancieux, A. et al. “Towards a common conceptual space for metacognition in perception and memory.” *Nature Reviews Psychology* 2 (2023), 751–766. https://doi.org/10.1038/s44159-023-00245-1
- [H8] Hodson, R., Mehta, M. & Smith, R. “The empirical status of predictive coding and active inference.” *Neuroscience & Biobehavioral Reviews* 157 (2024), 105473. https://doi.org/10.1016/j.neubiorev.2023.105473
- [H9] Brosch, T., Scherer, K. R., Grandjean, D. & Sander, D. “The impact of emotion on perception, attention, memory, and decision-making.” *Swiss Medical Weekly* 143 (2013), w13786. https://doi.org/10.4414/smw.2013.13786

**Fictional reference**

- Marvel. “Every Major A.I. in the Marvel Universe.” Official Marvel character/reference material. https://www.marvel.com/comics/guides/2500/every-major-a-i-in-the-marvel-universe
- MCU J.A.R.V.I.S. is treated here only as the fictional assistant depicted in the Iron Man/Avengers films. Film behavior is illustrative narrative material, not scientific or engineering validation.

---

**Status:** Comparison artifact drafted. It is not yet independently reviewed or Project Director accepted. It does not clear Gate A, Gate B or Phase 2 by itself.

## 8. Whole-Brain scope limitation — 2026-11-07

This comparison covers BM-01 through BM-12 because those are the mechanisms defined in the existing PR #174 specification. Its checked comparison rows establish coverage of that specified set only. They do not establish that the specified set is exhaustive of the future Brain.

The whole-Brain planning requirement is broader: first identify the complete intended capability space using human cognition, MCU J.A.R.V.I.S. and the developing-Brain analogy; then derive the mechanisms and interactions; then assess completeness and reconcile the existing BM specification. Do not use this document's twelve completed comparison rows as a whole-Brain completeness certificate.

The next Builder must preserve the human/MCU research and extend it where the whole-Brain capability analysis identifies gaps. The human reference is functional/scientific rather than literal biological imitation; MCU behavior is fictional inspiration rather than engineering evidence; the developmental analogy distinguishes enabling capacity from competence acquired through experience.

See [Whole-Brain Planning Scope and Builder Correction](WHOLE_BRAIN_PLANNING_SCOPE_AND_BUILDER_CORRECTION_2026-11-07.md) for the corrected planning sequence and Builder error record.

