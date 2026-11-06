# Phase 2 — Human Cognition and MCU J.A.R.V.I.S. Reference Comparison

**Date:** 2026-11-06  
**Source-map baseline:** PR #179 HEAD 6f2c2cf05196e69a48f5deefcc3f4609e258c19a  
**Main source baseline:** 1273ddbcd0087d189e01388ded2d362fb1e058d2  
**Accepted mechanism specification:** PR #174 HEAD 0811a59e46bf934e32e794f90e4e7d18d4e2bd97  
**Status:** Builder-prepared; independent review and Project Director disposition pending.

## 1. Purpose and limits

This register fulfils Phase 2 acceptance criterion 9.10 and IR-04. It compares BM-01–BM-12 with relevant human cognitive functions and fictional functional motifs associated with MCU J.A.R.V.I.S.

Human cognition is a comparative scientific reference, not a blueprint to reproduce literally. The literature contains competing models, task-dependent findings, and known limitations. MCU J.A.R.V.I.S. is fictional product inspiration, not scientific evidence and not evidence of an implementation. Repository status below reflects the Phase 2 source map: main at 1273ddbcd0087d189e01388ded2d362fb1e058d2 and unmerged donor PR #97 at c1da222e6c94aeb3f2ad000392c21fe4fc81ab25. Donor capability is not main capability.

No algorithm, schema, runtime topology, implementation baseline, or code change is selected or authorized here.

## 2. Mechanism comparison register

### BM-01 — Experience intake and provenance
- **Human reference:** Perception and episodic memory encode experienced events in temporal/contextual relation. Episodic-memory theory distinguishes recollection of experienced events from other retained knowledge, while acknowledging conceptual and empirical debates [H1].
- **MCU motif:** J.A.R.V.I.S. receives voice, suit telemetry, sensor and connected-system inputs across the films. This illustrates heterogeneous acquisition, not source authenticity or trustworthy provenance.
- **Engineering implication:** Preserve acquired content and source/time/context lineage separately from interpretation, model output, prediction and verified external outcome. Missing metadata is not a known negative; journal append is not semantic acceptance.
- **Repository status:** Main has event sequencing, timestamp/source/kind fields, journal append and replay. The source map identifies missing typed acquisition/receipt time, modality, epistemic status, source independence and derivation lineage.
- **Evidence needed:** Stable acquisition identity through representation, memory, belief revision, reasoning, prediction and learning, including malformed, delayed, duplicate and restart/replay cases.

### BM-02 — Representation and interpretation
- **Human reference:** Pragmatic language interpretation integrates linguistic form, world knowledge, speaker knowledge and context; probabilistic pragmatic models are one influential account, not a complete theory [H2].
- **MCU motif:** J.A.R.V.I.S. interprets Tony's requests in the context of ongoing suit, laboratory and mission activity. Fiction does not establish how ambiguity or uncertainty is represented.
- **Engineering implication:** Combine context, knowledge, speaker/source model, active task and uncertainty. Preserve alternatives. Do not substitute keyword-to-intent tables for grounding.
- **Repository status:** Main has representation normalization and a perception pipeline utility/test target, but the inspected main CognitiveCycle does not invoke it. PR #97 has donor-only integration.
- **Evidence needed:** Ambiguous inputs retain alternatives; new context changes their support; provider failure is not converted into a false external-world claim; production-path tests after authorization.

### BM-03 — Continuity and memory
- **Human reference:** Episodic memory and working memory have distinguishable functions; memory tasks can depend on multiple systems rather than mapping one-to-one to a single store [H1, H3].
- **MCU motif:** J.A.R.V.I.S. maintains apparent continuity across conversations, projects, diagnostics and suit operations.
- **Engineering implication:** Distinguish event retention, episodic retrieval, semantic knowledge, procedural competence, working context, consolidation and forgetting. Retrieved memory is not automatically belief; empty retrieval is not proof of historical absence.
- **Repository status:** Main has a journal, memory tiers, salience/confidence, ranked recall and working-memory eviction. Retrieval is attribute-overlap based; retrieved memories enter cycle context but are not passed into the inspected reasoning invocation.
- **Evidence needed:** Relevant memories materially affect later inference; irrelevant memories do not dominate; lineage survives reconstruction.

### BM-04 — Belief and world-state management
- **Human reference:** Human judgment and belief revision involve evidence evaluation and uncertainty, but people are not perfectly Bayesian or uniformly consistent; rationality research is interdisciplinary [H4].
- **MCU motif:** J.A.R.V.I.S. reports diagnostics and revises working assessments as new sensor/operator information arrives.
- **Engineering implication:** Represent qualified claims with source, scope, time, support, contradiction, alternatives and revision lineage. Do not use last-value scalar replacement as a universal conflict policy.
- **Repository status:** Main has belief maps, WorldModel facts/relations, disputed markers and source-reliability estimates. The source map identifies weak competing-claim lineage, provenance/scope and dependent-state invalidation.
- **Evidence needed:** Contradictions preserve alternatives; revisions stale dependent predictions/plans/conclusions; a disputed flag alone is insufficient.

### BM-05 — Association, causal modelling and prediction
- **Human reference:** People learn regularities, form expectations and update from outcome information. Statistical learning and reinforcement learning are distinct but interacting accounts; model parameters do not map uniquely to cognitive processes [H5, H6].
- **MCU motif:** J.A.R.V.I.S. performs diagnostics, forecasts system behavior and simulates technical consequences.
- **Engineering implication:** Separate association from causal hypotheses; represent scope, assumptions, horizon and resolution conditions; retain counterexamples and alternative causes; resolve only against attributable outcomes.
- **Repository status:** Main has association/causal models and prediction resolution. The source map identifies co-state-change causal limits, weak confounder/alternative-cause treatment, limited prediction semantics and incomplete external outcome attribution.
- **Evidence needed:** Held-out contexts, changed relationships, confounders, counterexamples, delayed outcomes and failed/unverified actions; report calibration separately from decision quality.

### BM-06 — Attention and active context
- **Human reference:** Cognitive control supports context-sensitive behavior selection and monitoring/adjustment of ongoing behavior; flexibility is limited and task representations matter [H7].
- **MCU motif:** J.A.R.V.I.S. prioritizes alerts, telemetry and concurrent requests while maintaining task context.
- **Engineering implication:** Distinguish cognitive attention from runtime queue priority. Active contexts need ownership, interruption, resumption and starvation detection. A scalar salience score is not the whole function.
- **Repository status:** Main has attention scoring, workspace projection and runtime queue priority. The source map identifies missing contextual influences and incomplete multi-context lifecycle guarantees.
- **Evidence needed:** Bounded service under competing contexts; interrupted contexts resume with constraints/provenance; scheduler fairness is tested separately from relevance.

### BM-07 — Affective appraisal and valuation
- **Human reference:** Appraisal theories connect emotion with interpretations of events in relation to concerns, goals and control. Meta-analytic work finds substantial associations but also variation and unresolved detail; no single fixed appraisal set is settled [H8, H9].
- **MCU motif:** J.A.R.V.I.S. communicates urgency, risk and concern-like warnings. These are interface motifs, not evidence of human feelings.
- **Engineering implication:** Model context-sensitive significance, risk, uncertainty and goal relevance as qualified signals. Do not hardcode stimulus-to-emotion or emotion-to-action mappings.
- **Repository status:** Main has threat, attention and aggregate self-state signals, but a coherent authoritative affective appraisal owner and integrated downstream path are not established. PR #97 contains donor-only affective mechanisms.
- **Evidence needed:** Same event under different goals/context can yield different appraisal; later evidence revises it; appraisal modulates cognition without fixed reaction tables.

### BM-08 — Goals, intent, planning and decision
- **Human reference:** Goal pursuit involves goal selection, planning, prospective memory and executive control. Implementation intentions can affect attention and decision behavior, with effects moderated by goal/plan characteristics [H7, H10].
- **MCU motif:** J.A.R.V.I.S. commonly helps execute or advise on goals supplied by Tony or mission circumstances. This supports goal processing, not autonomous experience-acquired motivation.
- **Engineering implication:** Distinguish supplied goals from internally formed candidates. Candidate goals require evidence lineage, feasibility/conflict evaluation and revision; decisions do not authorize execution.
- **Repository status:** Main supports supplied-goal lifecycle, intent selection, planning, decision and action assessment. Experience-acquired candidate-goal formation is not demonstrated; first-eligible selection is a fallback, not autonomous goal evaluation.
- **Evidence needed:** Test supplied goals separately from candidate goals formed from novel experience; defeat candidate premises with later evidence; preserve external governance.

### BM-09 — Learning and developmental adaptation
- **Human reference:** Learning uses multiple processes; generalization research highlights trade-offs between rule-based and similarity-based transfer and the role of hybrid accounts. Transfer must be measured on novel relevant contexts [H5, H6].
- **MCU motif:** The films portray adaptive technical assistance and upgrades but provide no inspectable learning history, causal attribution or held-out evaluation.
- **Engineering implication:** Identify evidence, target state owner, candidate rationale, persistence and later behavioral effect. Distinguish observational/evidence-based from action-outcome learning; evaluate regression, interference, reversal and transfer.
- **Repository status:** Main has numeric prediction adaptation and evolution proposal/adoption primitives. The source map does not establish a cross-mechanism developmental loop revising representation, memory, beliefs, causal models, goals, reasoning or skills with validated later effects.
- **Evidence needed:** Experience → evidence-sensitive update → persistent change → changed future computation → evaluation in original, held-out and novel relevant contexts. A score/counter/storage write is insufficient.

### BM-10 — Metacognitive monitoring and control
- **Human reference:** Metacognition includes monitoring and regulation of thinking. Confidence/uncertainty signals can guide effort but may be heuristic and miscalibrated [H11, H12].
- **MCU motif:** J.A.R.V.I.S. reports system health, limitations, diagnostic confidence and operational risks. Fictional reporting does not prove accurate introspection.
- **Engineering implication:** Monitoring records must link to actual premises, assumptions, evidence, uncertainty and dependencies. Detection must lead to bounded correction and measured evaluation.
- **Repository status:** Main has aggregate reflection, prediction-accuracy summaries, uncertainty/coherence measures and capability-health state. Evidence-lineage-aware monitoring and a closed corrective loop are not demonstrated.
- **Evidence needed:** Inject known omissions, stale premises, calibration errors and capability degradation; verify detection, proportionate correction and measured effect.

### BM-11 — Integrated coordination and continuity control
- **Human reference:** Cognitive control and working-context maintenance support coordination, but human cognition is not a perfectly reliable scheduler or transactional state machine [H3, H7].
- **MCU motif:** J.A.R.V.I.S. coordinates suit subsystems, sensors, tools, communications and concurrent tasks. The films do not specify queue fairness, consistency or crash recovery.
- **Engineering implication:** Coordination is not a second Brain. Define ownership, dependency freshness, interruption, concurrency, partial completion, idempotency, persistence acknowledgement and recovery. Keep cognitive and substrate state distinct.
- **Repository status:** Main has a bounded CognitiveCycle, runtime queues and workspace snapshots. PR #97 donor runtime shows feedback-first scheduling, shutdown feedback rejection and drop-oldest result behavior; no production incident is claimed.
- **Evidence needed:** Deterministic fairness, in-flight shutdown, partial commit, crash/restart, result-loss reconciliation and idempotent retry at the actual runtime boundary.

### BM-12 — General reasoning and inference
- **Human reference:** Human reasoning includes deduction, induction, causal/analogical inference and possibility/counterfactual reasoning. Represented alternatives matter, and human reasoners also neglect alternatives in some tasks [H4, H13].
- **MCU motif:** J.A.R.V.I.S. synthesizes technical evidence, diagnostics and alternatives to advise Tony. Fiction is not proof of general intelligence or reliable inference.
- **Engineering implication:** Preserve premise identity/provenance/scope/time, assumptions, inference lineage, alternatives, contradictions, counterexamples, uncertainty and dependencies. Conclusions remain provisional until the appropriate owner evaluates them.
- **Repository status:** Main has bounded reasoning over scalar beliefs and causal links. The source map identifies missing premise lineage, narrow inference breadth, memory not supplied to reasoning and results not consumed downstream.
- **Evidence needed:** Sufficient/insufficient premises, contradictions, alternatives, counterexamples, relevant/irrelevant memories, stale assumptions and downstream effects.

## 3. Cross-mechanism conclusions

1. Context is shared across BM-01/02/03/04/06/08/12; contextual grounding is not a phrase-list problem.
2. Memory retrieval is not integrated reasoning unless relevant content and provenance reach BM-12 and can change inference.
3. Goal processing and experience-acquired goal formation are separate capabilities.
4. Affective appraisal is context-sensitive valuation, not a required human-emotion replica.
5. Learning is not parameter tuning alone; it requires persistent evidence-sensitive change and later behavioral evaluation.
6. Coordination must integrate scheduling, active context, persistence and recovery without creating a second cognitive authority.
7. Fiction motivates a coherent assistant experience; it cannot establish mechanisms, safety, reliability or learning.

## 4. Limits

- The cited literature is a focused reference set, not a systematic review of every BM mechanism.
- Human cognition is heterogeneous, task-dependent and explained by competing theories.
- Software may satisfy a functional requirement through a different mechanism; analogy does not imply structural equivalence.
- MCU portrayals omit implementation cost, training, security, privacy, failure rates and operational constraints.
- No comparison establishes that the repository behaves like a human or MCU J.A.R.V.I.S.
- No production or donor runtime behavior was executed for this document.

## 5. Scientific reference register

[H1] Tulving, E. (2002). *Episodic Memory: From Mind to Brain*. Annual Review of Psychology, 53, 1–25. https://doi.org/10.1146/annurev.psych.53.100901.135114

[H2] Goodman, N. D., & Frank, M. C. (2016). *Pragmatic Language Interpretation as Probabilistic Inference*. Trends in Cognitive Sciences, 20(11), 818–829. https://doi.org/10.1016/j.tics.2016.08.005

[H3] Baddeley, A. D. (2021). *Developing the Concept of Working Memory: The Role of Neuropsychology*. Archives of Clinical Neuropsychology, 36(6), 861–873. https://doi.org/10.1093/arclin/acab060

[H4] Hahn, U. (2026). *Human Rationality*. Annual Review of Psychology, 77, 193–221. https://doi.org/10.1146/annurev-psych-020425-020958

[H5] *Unifying Principles of Generalization: Past, Present, and Future*. Annual Review of Psychology. https://doi.org/10.1146/annurev-psych-021524-110810

[H6] *What do Reinforcement Learning Models Measure? Interpreting Model Parameters in Cognition and Neuroscience*. Current Opinion in Behavioral Sciences (2021). https://doi.org/10.1016/j.cobeha.2021.06.004

[H7] Badre, D. (2025). *Cognitive Control*. Annual Review of Psychology, 76, 167–195. https://doi.org/10.1146/annurev-psych-022024-103901

[H8] Yeo, G. C., & Ong, D. C. (2024). *Associations between Cognitive Appraisals and Emotions: A Meta-analytic Review*. Psychological Bulletin, 150(12), 1440–1471. https://doi.org/10.1037/bul0000452

[H9] Fernando, J. W., Kashima, Y., & Laham, S. (2017). *Alternatives to the Fixed-set Model: A Review of Appraisal Models of Emotion*. Cognition and Emotion, 31(1), 19–32. https://doi.org/10.1080/02699931.2015.1074548

[H10] Gollwitzer, P. M., & Sheeran, P. (2025). *Psychology of Planning*. Annual Review of Psychology, 76, 303–328. https://doi.org/10.1146/annurev-psych-021524-110536

[H11] Ackerman, R., & Thompson, V. A. (2017). *Meta-Reasoning: Monitoring and Control of Thinking and Reasoning*. Trends in Cognitive Sciences, 21(8), 607–617. https://doi.org/10.1016/j.tics.2017.05.004

[H12] Fleming, S. M. (2026). *Towards an Integrative Neuroscience of Metacognition*. Nature Reviews Neuroscience, 27, 789–806. https://doi.org/10.1038/s41583-026-01081-x

[H13] Byrne, R. M. J. (2026). *Inference and Imagination*. Topics in Cognitive Science, 18(3), e70066. https://doi.org/10.1111/tops.70066

## 6. Fictional reference corpus

The MCU comparison uses the films as fictional primary material: *Iron Man* (2008), *Iron Man 2* (2010), *The Avengers* (2012), *Iron Man 3* (2013), *Avengers: Age of Ultron* (2015), and *Avengers: Endgame* (2019). Broad functional motifs are described without dialogue quotation or claims about a validated internal implementation.

## 7. Phase 1 Continuity and Impact

This document inherits the Phase 1 source baseline at main commit 1273ddbcd0087d189e01388ded2d362fb1e058d2 and accepted BM specification PR #174 exact HEAD 0811a59e46bf934e32e794f90e4e7d18d4e2bd97. It preserves the existing BM-01–BM-12 architecture; the conclusion that main is substantial but incomplete; the single cognitive-state authority boundary; the distinction between main and unmerged donor code; and the source-map findings on disconnected perception, memory/reasoning, downstream reasoning, candidate-goal formation, affective appraisal and developmental learning. It does not alter any prior authority or gate decision.

## 8. Review and acceptance

**Builder self-check:** Completed for structure, scope, status distinctions and reference links. Not an independent review.

**Independent Reviewer:** Pending. Must challenge scientific source fit, the BM comparisons, fictional-reference boundaries and engineering implications.

**Project Director:** Acceptance or explicit bounded deferral pending.

**Phase 2:** IN PROGRESS. **Gate A:** NOT CLEARED. **Gate B:** Not assessed or cleared. **Implementation baseline:** None. **PR #97:** Unapproved, unmerged donor. **Runtime implementation:** Not authorized.
