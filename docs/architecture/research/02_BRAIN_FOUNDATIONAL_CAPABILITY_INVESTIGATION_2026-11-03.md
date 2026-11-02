# JARVIS Brain — Foundational Capability Investigation

**Status:** Investigation report — provisional findings; not an architecture specification or approval  
**Date:** 2026-11-03  
**Authorized scope:** Bounded 30-minute foundational capability investigation  
**Research baseline:** PR #171, exact HEAD `b05434758ad4fe72815503f89bd5d2990ccb658b`  
**Engineering baseline:** `main`, exact HEAD `1273ddbcd0087d189e01388ded2d362fb1e058d2`  
**Governing principle:** **ENGINEER THE MECHANISMS; LET BEHAVIOR BE ACQUIRED THROUGH EXPERIENCE.**

---

## 1. Purpose and authority

This investigation answers one question:

> What capabilities must JARVIS's Brain possess for it to become a coherent cognitive system that can learn from experience and change its future performance?

This is a capability investigation, not Brain architecture design. It identifies capability responsibilities, interactions, evidence, current engineering evidence and unresolved questions. It does not select component boundaries, runtime topology, algorithms, technologies or implementation order.

The independently approved research package at PR #171 is the evidence baseline. Its approval is not architecture approval. This report is a separate deliverable and requires its own review and Project Director acceptance before it can be used as an approved planning baseline.

## 2. Scope and method

The investigation used three reference lenses:

1. **MCU J.A.R.V.I.S.** — a fictional functional reference for contextual assistance, integrated operation and human-machine collaboration. It is not evidence of a hidden technical design.
2. **Human cognition** — a scientific reference for memory, attention, cognitive control, learning, generalization and adaptive behaviour. Biological mechanisms are not copied one-to-one.
3. **JARVIS engineering reality** — source and test inspection at the exact `main` commit above. Source presence is evidence of implementation structure, not proof of capability. Tests were inspected but not executed in this investigation.

The investigation also reviewed:
- Document 00 — System Architecture Foundation.
- Document 01 — Whole-System Anatomy and Responsibility Map.
- The approved Brain Foundation Comparative Research and Decision Log.
- The approved Brain Foundation Mechanism Gap Analysis.

The investigation did not modify PR #171, runtime source, tests, dependencies or build configuration.

## 3. Executive findings

### 3.1 The Brain must be planned as a capability network, not a feature catalogue

Memory, perception, attention, reasoning, prediction, valuation, decision and learning are not independent features. Their value depends on how they exchange evidence, context, state and feedback.

A collection of individually functioning mechanisms can still fail to produce coherent cognition if:
- one mechanism loses the source or uncertainty of information;
- beliefs are updated without reconsidering dependent predictions;
- memories are stored but never influence later interpretation or decisions;
- predictions are made but not compared with verified outcomes;
- an error is recorded but does not change an appropriate future process;
- a local adaptation improves one case while degrading other contexts;
- a generated explanation is treated as proof that the underlying process was correct.

### 3.2 Learning is a property of the whole cognitive system

Learning cannot be defined as writing an event to memory, incrementing a metric or changing a parameter. A learning claim requires a causal chain:

**experience → evidence-sensitive update → persistent change → later behavioural effect → evaluation in relevant and novel contexts.**

The change must be attributable to experience, must not be a test-specific hardcoded result, and must be assessed for transfer and regression.

### 3.3 The current repository has meaningful foundations, not a demonstrated complete Brain

The inspected code includes an event-backed cognitive cycle, memory retrieval, beliefs, causal links, reasoning, prediction, goals, planning, decision-making, action assessment and outcome feedback. This is real engineering work and should be preserved.

However, the inspected tests demonstrate narrow, scripted behaviour. They do not establish broad generalization, open-ended learning, robust cross-context transfer, or a fully integrated developmental Brain. The correct status is **existing cognitive foundations with capability evidence gaps**, not “nothing exists” and not “the Brain is complete.”

## 4. Foundational capability baseline

The following capabilities appear necessary for a coherent first developmental Brain. This is a capability baseline, not a decision to create one software module per row.

| Capability | Required cognitive responsibility | Why it is foundational |
|---|---|---|
| Coherent cognitive state and continuity | Maintain a coherent current state and preserve developmental continuity across events and restarts | Without continuity, experience cannot reliably influence later cognition |
| Experience representation and provenance | Distinguish received observations from interpretations, hypotheses, beliefs, predictions, decisions and verified outcomes | Without epistemic distinctions, the Brain can confuse evidence with its own conclusions |
| Memory and retrieval | Retain relevant experience, retrieve it in context, and distinguish episode-specific detail from derived knowledge | Memory must inform future cognition rather than act as an isolated archive |
| Belief and knowledge formation/revision | Form, qualify, support, contradict and revise claims in response to evidence | The Brain needs a revisable model of what it currently has reason to believe |
| Attention and working context | Select information and processing effort according to context, goals, uncertainty and consequence | The Brain cannot process all available information equally or indefinitely |
| Prediction and outcome comparison | Anticipate possible outcomes, preserve prediction assumptions and compare predictions with later verified outcomes | Prediction error supplies evidence about model limitations |
| Learning and adaptation | Change relevant representations, associations, retrieval, predictions or strategies from experience | This is the mechanism of developmental improvement, not a final storage step |
| Reasoning and inference | Derive conclusions from evidence while distinguishing inference, hypothesis, assumption and verified result | Belief revision and decisions require more than association or fluent output |
| Goals, valuation and decision formation | Represent desired states, constraints, competing priorities and expected consequences; form decisions or defer | Cognitive processing must be directed and able to resolve trade-offs |
| Cognitive control and metacognitive monitoring | Detect uncertainty, contradiction, stalled progress, prediction failure and capability limits; initiate appropriate reconsideration | A system must be able to monitor and correct its own ongoing cognition |
| Integrated coordination | Preserve ownership, provenance, timing, dependencies and consistency as capabilities interact | Integration is what turns mechanisms into one coherent cognitive system |

**Classification qualification:** the minimum form of each capability is foundational; sophisticated forms may be advanced. For example, basic evidence-grounded inference is foundational, while a broad suite of causal, spatial, probabilistic and analogical reasoning may be developed progressively. The exact foundation/advanced boundary remains an architecture-stage question.

## 5. Capabilities that should be anticipated but not assumed to be fully foundational

These capabilities matter to the long-term JARVIS objective. Their mature forms should not automatically be forced into the minimum Brain foundation.

| Capability area | Minimum capacity to preserve | Advanced development that remains open |
|---|---|---|
| Perceptual interpretation and grounding | Interpret evidence-bearing observations, retain alternatives and uncertainty, and ground references to observed or remembered entities | High-fidelity multimodal perception, persistent entity tracking and complex cross-modal grounding |
| Abstraction and generalization | Form revisable regularities from experience and retain exceptions/counterexamples | Broad compositional concept formation and transfer across distant domains |
| Imagination and counterfactual evaluation | Keep candidate futures distinct from observed history and evaluate basic alternatives | Rich multi-step simulation, counterfactual search and complex mental models |
| Affective processing and valuation | Evaluate significance, risk, goals and internal conditions without fixed stimulus-to-emotion or emotion-to-action rules | Sophisticated affective dynamics and learned modulation across memory, attention and action |
| Social cognition and teammate modelling | Track explicit instructions, task context, commitments and uncertainty about inferred intent | Rich theory-of-mind, multi-party social reasoning and complex team models |
| Language-mediated cognition | Interpret language in context and ground references without treating language as the universal representation of thought | Flexible multilingual pragmatics and deep language/non-language integration |
| Proactive and continuous cognition | Support ongoing state updates and the ability to resume or defer work | Rich autonomous initiative, curiosity and continuous operation across changing environments |
| Skill and procedural learning | Preserve the possibility of acquiring and improving reusable strategies | General skill acquisition, hierarchical procedural learning and transfer to unfamiliar tasks |

The Brain's boundaries must also remain clear: sensory systems acquire signals; action systems execute authorized operations; governance controls permissions and policy; signalling systems transport information. The Brain must reason over their outputs and outcomes without absorbing all those external responsibilities into itself.

## 6. Capability interactions and dependencies

The relationships below are conceptual dependencies, not a fixed linear cognitive pipeline.

1. **Experience and representation ↔ memory:** new observations can trigger retrieval; retrieved episodes can change how new observations are interpreted. Historical evidence must remain distinguishable from revised interpretations.
2. **Representation ↔ belief formation:** representations organize entities, events and relationships; belief formation assesses what those representations and their evidence justify.
3. **Attention ↔ working context ↔ memory:** attention selects what is currently relevant; working context makes selected information available; retrieval and memory influence what receives attention. The relationship is reciprocal, not a one-way stage.
4. **Belief/world understanding ↔ prediction:** predictions depend on current beliefs and assumptions. New evidence or belief revision can invalidate dependent predictions.
5. **Prediction ↔ outcome evaluation ↔ learning:** a prediction must be linked to the outcome that resolves it. Prediction error is evidence for review, not an instruction to apply one universal update.
6. **Learning ↔ memory/representation/reasoning/valuation:** different experiences may change different cognitive structures. Learning is distributed across these capabilities and requires evaluation of interference and regression.
7. **Goals/valuation ↔ attention/reasoning/planning/decision:** goals influence relevance and resource allocation; reasoning and prediction inform valuation; decisions must account for uncertainty, consequence and constraints.
8. **Metacognitive monitoring ↔ all cognitive capabilities:** monitoring can detect a problem and request reconsideration, more evidence, a different strategy or deferral. It must not become an unrestricted second cognitive authority or bypass governance.
9. **Decision ↔ action boundary ↔ verified outcome:** the Brain forms intent and decision; external authorization and execution remain separate; only verified outcomes should be used as evidence about what happened.
10. **Continuity ↔ development:** new learning may change capability and self-understanding, but it must not erase the historical lineage of the system's development.

A useful minimum test of integration is whether a change in one capability causes the relevant dependent capabilities to reconsider stale information without corrupting unrelated state.

## 7. Three-reference comparison

### 7.1 MCU J.A.R.V.I.S. — functional inspiration

The Department of Defense's 2020 Human-Machine Teaming Workshop Report uses an Iron Man/J.A.R.V.I.S. vignette to illustrate contextual interpretation. When Tony says to keep a project on his private server after expressing uncertainty about trust, J.A.R.V.I.S. interprets the statement as an implicit instruction to preserve confidentiality rather than as a literal question. The report also identifies real-time information, task completion, machine operation and context-sensitive support as aspects of the fictional example.

**Engineering lesson:** useful assistance requires contextual interpretation, a model of the collaborator/task, coordinated capabilities and the ability to act on inferred intent.

**Limit:** this is a fictional vignette discussed by a workshop report. It does not demonstrate how MCU J.A.R.V.I.S. internally stores memory, learns, reasons, represents affect or coordinates modules. No hidden implementation should be inferred.

### 7.2 Human cognition — scientific reference

- **Attention and memory:** the 2024 Annual Review of Psychology synthesis treats attention and memory as closely related across working memory, long-term memory and other domains. This supports treating attention and memory as interacting capabilities rather than isolated stores.
- **Cognitive control:** Badre's 2025 review describes context-sensitive selection of behaviour and monitoring/adjustment of ongoing behaviour. This supports a basic capability for flexible control and corrective response.
- **Memory and generalization:** Sun et al. (2023) model complementary memory and learning systems and show, within their formal framework, that unregulated consolidation can harm generalization in unpredictable environments. This is a specific theory/model, not a universal settled account of human memory. It supports the need to distinguish retention of episodes from generalization and to evaluate whether consolidation improves future performance.
- **Continual learning:** the 2026 systematic review of 189 papers identifies catastrophic forgetting and the preservation of prior knowledge as persistent challenges. This reinforces that learning new information is not sufficient if it destroys useful prior capability.

**Engineering lesson:** cognition depends on interacting processes; flexible control, context-sensitive retrieval, selective learning and generalization must be evaluated together.

**Limit:** biological mechanisms are not software specifications. Human cognition remains incompletely understood and includes limitations JARVIS should not reproduce.

### 7.3 JARVIS engineering reality — inspected evidence

The current `main` branch was independently fetched and confirmed at `1273ddbcd0087d189e01388ded2d362fb1e058d2` (commit dated 2026-10-29).

Evidence inspected:

- `core/cpp/src/cognitive_cycle.cpp` lines 35–60: the cycle receives an observation, recalls ranked memories, reads beliefs and causal links, performs reasoning and projects predictions.
- The same file, lines 64–133: it selects an eligible goal, plans candidate actions, forms decisions and assesses actions against constraints. Lines 138–160 expose outcome and prediction feedback paths.
- `core/cpp/src/brain.cpp` lines 21–23: construction replays the persisted event history to reconstruct cognitive state. Lines 86–90 contain observation, evidence assimilation, prediction and prediction-outcome handling.
- `core/cpp/src/memory.cpp` lines 119–160: event append/persistence and journal loading are implemented. Lines 292 onward provide ranked retrieval.
- `core/cpp/tests/cognitive_cycle_suite.cpp` lines 25–95: a scripted observation, explicit goal, candidate actions, planning, decision, assessment and one prediction/outcome path are asserted.
- `core/cpp/tests/learning_adaptation_phase8_suite.cpp` lines 17–60: repeated numeric forecast outcomes are used to check decreasing mean error and persistence of an adaptation metric after reconstruction.
- `core/cpp/CMakeLists.txt` lines 9, 11 and 59 include `brain.cpp`, `memory.cpp` and `cognitive_cycle.cpp` in the core build.

**Deeper source-level findings from the same exact baseline:**

- **Retrieved memory is not yet shown to influence the cycle's reasoning.** `CognitiveCycle::run` retrieves ranked memories into `result.context.memories`, but the `ReasoningProblem` is populated from beliefs and causal links only. In the inspected function, the retrieved memories are exposed in the result context but are not passed into the reasoning premises or later planning/decision inputs. This is a concrete integration gap between memory retrieval and reasoning in this path, not proof that no other path can use memory.
- **The current memory query is attribute-overlap retrieval.** `Memory::recall_ranked` compares query keys and exact scalar values, then combines match/overlap, relative record position, salience and confidence. This provides useful structured retrieval, but it does not by itself demonstrate semantic or conceptual retrieval across different wording, abstraction or context.
- **Belief records have limited explicit provenance.** The inspected `Belief` structure contains key, value, confidence, observation count and updated event sequence; it does not itself carry a source or evidence set. Source information is retained elsewhere in event/world records, but the direct belief object does not expose a full evidence lineage in this baseline.
- **Prediction records are comparatively thin.** The inspected `Prediction` structure records key, predicted scalar, confidence, creation sequence, resolution flag and error. It does not explicitly retain assumptions, scope or a prediction horizon. The cognitive cycle calls a simulation with a horizon, but that horizon is not present in the resulting `Prediction` record.
- **Belief updates are currently simple key/value revisions.** In the replay path, observation reliability is assigned a fixed 0.7; learning events use their supplied reliability. Existing values are overwritten, with confidence adjusted according to whether the new value matches the previous value. This is a concrete current update rule, not evidence of general evidence reconciliation, source conflict analysis or context-sensitive belief revision.
- **The learning-event path assimilates one non-reliability field into the knowledge-source metric.** The inspected loop stops after the first qualifying key/value pair. Belief/world/association processing iterates the event's data separately. This means the source-reliability metric path should not be described as a complete multi-fact knowledge assimilation process.
- **The current cycle's goal is supplied or selected from eligible goals.** If no goal ID is supplied, the function selects the first eligible goal. This proves a goal-selection path exists, but does not demonstrate autonomous goal formation from open-ended experience or learned intent selection within this cycle.
- **Outcome feedback is not equivalent to broad learning.** A resolved numeric prediction updates an adaptation metric; the separate learning call updates knowledge-source reliability and belief/world/association state. The inspected path does not demonstrate that every prediction error triggers a justified revision of the underlying causal model, memory organization or strategy.

These findings narrow the engineering claim: the code has a real event-backed cycle and several interacting mechanisms, but some interactions are currently shallow or one-way in the inspected path. Capability presence must not be confused with capability integration or demonstrated learning.

**What this establishes:** a persistent event-backed cognitive substrate and a real integration path across several named capabilities already exist.

**What it does not establish:** open-world perception and grounding, broad semantic or causal learning, generalization to unfamiliar contexts, robust affective/social cognition, reliable metacognitive correction, or persistent improvement across a varied experience stream.

The inspected tests are source evidence only; they were not run during this investigation. Passing these narrow tests, if confirmed by CI, would still not prove the broader capabilities listed above.

## 8. Principal capability gaps and risks

1. **Representation and epistemic integrity:** the Brain must reliably distinguish observation, inference, belief, prediction, simulation, intention and verified outcome. Loss of these distinctions contaminates all downstream cognition.
2. **Learning versus metric updates:** adaptation of a numeric forecast metric is not equivalent to learning a reusable concept, relationship, causal model or strategy.
3. **Generalization and transfer:** repeated success on one key/value forecast does not demonstrate improvement on a novel but related case.
4. **Attention-memory interaction:** retrieval and attention must jointly support context-sensitive cognition; simple ranked retrieval does not prove relevant memory selection under competing goals and uncertainty.
5. **Prediction quality:** predictions need explicit assumptions, horizons, provenance and outcome resolution. A generic scalar error is not sufficient for every prediction type.
6. **Valuation and affect:** valuation must influence cognition without encoding fixed emotional responses or deterministic emotion-to-action rules.
7. **Metacognitive effectiveness:** detecting an error is insufficient unless the system chooses an appropriate corrective response and later evaluates whether correction helped.
8. **Cross-capability consistency:** changes to beliefs or representations must not leave dependent plans and predictions silently stale.
9. **Evidence of persistent behavioural change:** the project needs longitudinal evidence that prior experience changes future performance in ways that transfer and remain robust under regression tests.

## 9. Questions that must be answered during Brain architecture planning

This investigation deliberately leaves the following decisions open:

1. What is the minimum coherent cognitive state that must persist across events and restarts?
2. Which information classes must remain distinct, and what provenance/uncertainty semantics are mandatory?
3. What is the minimum viable relationship between episodic experience, active context, retained knowledge and learned abstractions?
4. How should attention and memory interact when multiple goals, uncertain evidence and competing tasks exist?
5. What kinds of belief revision and contradiction handling are foundational?
6. Which prediction forms are required initially, and how will assumptions and outcome evidence be represented?
7. What is the minimum learning capability that can demonstrate genuine transfer rather than repeated fitting to one input?
8. Which reasoning capabilities are foundational, and which can be added later?
9. How should goals and valuation be represented without hardcoded preferences or emotional mappings?
10. What corrective authority should metacognitive monitoring have, while preserving state ownership and governance boundaries?
11. How can cognitive coordination support concurrency, interruption, partial failure and recovery without a hidden single point of cognitive failure?
12. What experiments can demonstrate persistent experience-dependent behavioural change across varied contexts?

## 10. Progression recommendation

**Recommended next planning stage: Brain Foundation Architecture Planning.**

Use this report as a candidate capability baseline only after independent review and Project Director acceptance. The next stage should resolve capability ownership, boundaries, interaction contracts and the foundational-versus-advanced split. It should not jump directly to technology or implementation decisions.

No architecture has been designed or approved by this report. No algorithms, frameworks, programming languages, databases, runtime topology or implementation sequence are selected here.

## 11. Explicit exclusions and completion statement

This investigation did not:
- design or approve a Brain architecture;
- decompose capabilities into implementation mechanisms or coding tasks;
- select technologies, algorithms, languages, frameworks or databases;
- modify runtime source, tests, dependencies or build configuration;
- run or claim success for runtime tests;
- authorize implementation, migration, merge or deployment.

**Investigation result:** a provisional foundational capability baseline has been identified, its cross-capability dependencies have been described, the existing engineering substrate has been distinguished from demonstrated capability, and the major unresolved questions for architecture planning have been recorded.

**Next gate:** independent review of this report, followed by explicit Project Director acceptance before Brain architecture planning begins.

---

## References

### Project research baseline
- [PR #171 — JARVIS System Architecture Foundation](https://github.com/methaneex-oss/MethaneX/pull/171)
- [Document 00 — System Architecture Foundation, exact approved research baseline](https://github.com/methaneex-oss/MethaneX/blob/b05434758ad4fe72815503f89bd5d2990ccb658b/docs/architecture/00_JARVIS_SYSTEM_ARCHITECTURE_FOUNDATION.md)
- [Document 01 — Whole-System Anatomy and Responsibility Map](https://github.com/methaneex-oss/MethaneX/blob/b05434758ad4fe72815503f89bd5d2990ccb658b/docs/architecture/01_JARVIS_WHOLE_SYSTEM_ANATOMY_AND_RESPONSIBILITY_MAP.md)
- [Comparative Research and Decision Log](https://github.com/methaneex-oss/MethaneX/blob/b05434758ad4fe72815503f89bd5d2990ccb658b/docs/architecture/research/00_BRAIN_FOUNDATION_COMPARATIVE_RESEARCH_AND_DECISION_LOG.md)
- [Mechanism Gap Analysis](https://github.com/methaneex-oss/MethaneX/blob/b05434758ad4fe72815503f89bd5d2990ccb658b/docs/architecture/research/01_BRAIN_FOUNDATION_MECHANISM_GAP_ANALYSIS.md)

### Engineering baseline
- [Cognitive cycle](https://github.com/methaneex-oss/MethaneX/blob/1273ddbcd0087d189e01388ded2d362fb1e058d2/core/cpp/src/cognitive_cycle.cpp#L35-L160)
- [Brain state and learning implementation](https://github.com/methaneex-oss/MethaneX/blob/1273ddbcd0087d189e01388ded2d362fb1e058d2/core/cpp/src/brain.cpp#L21-L90)
- [Memory persistence and retrieval](https://github.com/methaneex-oss/MethaneX/blob/1273ddbcd0087d189e01388ded2d362fb1e058d2/core/cpp/src/memory.cpp#L119-L160)
- [Cognitive cycle test](https://github.com/methaneex-oss/MethaneX/blob/1273ddbcd0087d189e01388ded2d362fb1e058d2/core/cpp/tests/cognitive_cycle_suite.cpp#L25-L95)
- [Learning adaptation test](https://github.com/methaneex-oss/MethaneX/blob/1273ddbcd0087d189e01388ded2d362fb1e058d2/core/cpp/tests/learning_adaptation_phase8_suite.cpp#L17-L60)
- [Core CMake source list](https://github.com/methaneex-oss/MethaneX/blob/1273ddbcd0087d189e01388ded2d362fb1e058d2/core/cpp/CMakeLists.txt#L9-L59)

### External scientific and functional references
- U.S. Department of Defense (2020), [Future Directions in Human-Machine Teaming Workshop Report](https://basicresearch.defense.gov/Portals/61/Future%20Directions%20in%20Human%20Machine%20Teaming%20Workshop%20report%20%20%28for%20public%20release%29_1.pdf), especially pp. 1–6.
- Badre, D. (2025), [Cognitive Control](https://doi.org/10.1146/annurev-psych-022024-103901), Annual Review of Psychology, 76, 167–195.
- Cowan, N. et al. (2024), [The Relation Between Attention and Memory](https://doi.org/10.1146/annurev-psych-040723-012736), Annual Review of Psychology, 75, 183–214.
- Sun, W. et al. (2023), [Organizing memories for generalization in complementary learning systems](https://doi.org/10.1038/s41593-023-01382-9), Nature Neuroscience, 26, 1438–1448.
- Yang, Q. et al. (2026), [Continual learning: A systematic literature review](https://doi.org/10.1016/j.neunet.2025.108226), Neural Networks, 195, 108226.
