# Phase 2 — Whole-Brain Capability-to-Source Integration Investigation

**Status:** IN PROGRESS — first evidence batch recorded; not an acceptance or implementation gate  
**Repository:** `methaneex-oss/MethaneX`  
**Specification reference:** PR #174 exact head `0811a59e46bf934e32e794f90e4e7d18d4e2bd97`  
**Engineering source baseline:** `main` at `1273ddbcd0087d189e01388ded2d362fb1e058d2`  
**Phase 1 continuity:** Phase 1 whole-repository investigation and reuse audit, plus its tracked-file inventory, donor traceability and review-correction records  
**Governing principle:** ENGINEER THE MECHANISMS; LET BEHAVIOR BE ACQUIRED THROUGH EXPERIENCE.

---

## 1. Purpose and scope

Phase 2 investigates how the existing repository's mechanisms and capabilities map onto the twelve logical responsibilities in the accepted Brain mechanism specification. The objective is not to divide the Brain into twelve independent projects. The objective is to determine how one coherent Brain acquires experience, forms and revises representations, retains and retrieves memory, reasons, predicts, appraises, attends, forms goals, learns, coordinates, persists and changes future computation.

This is a static source and artifact investigation. It does not authorize implementation, refactoring, builds, runtime tests, benchmarks, merges, donor integration or deletion.

### 1.1 Required evidence for each material capability

For each mechanism and cross-mechanism path, this investigation records:

1. Exact source baseline, path and blob SHA.
2. Public/internal interfaces and state owner.
3. Inputs and their epistemic status/provenance.
4. Actual processing, not inferred intent from names.
5. Outputs and actual downstream consumers.
6. Persistence, replay and recovery behavior.
7. Test source/target evidence and, separately, verified CI execution where available.
8. Known limits, contradictions, coupling and failure paths.
9. Classification: reusable as-is, reusable with adaptation, incomplete, conflicting, unverified, or no relevant evidence found.

A class, method, test filename or PR description is not proof of integrated capability.

### 1.2 Baseline discipline

All source claims in this first batch are pinned to main commit `1273ddbcd0087d189e01388ded2d362fb1e058d2`. PR #97 donor material is a separate candidate line and must not be conflated with main. The specification is a planning contract, not proof of implementation.

---

## 2. Initial whole-Brain integration picture

The source already contains a substantial C++ cognitive core. Its `Brain` facade composes event/memory, world model, beliefs, association and causal models, decision/action, adaptation/learning, attention, threat, resilience, evolution, planning, reflection, knowledge, self-model/state, self-testing, goals, intent and strategy.

That is meaningful reusable material. It is not yet evidence that all twelve specified responsibilities are integrated into a coherent, experience-learning Brain.

The most important integration path found in this first batch is:

`Event observation → Brain::observe → journal/memory → retrieved memories + beliefs + causal links → ReasoningEngine → causal simulation/predictions → eligible supplied goals → planning → decision → action assessment`

A separate feedback path is exposed:

`verified/claimed outcome input → prediction resolution and/or Evidence learning → adaptation/evolution → persisted journal events → replay`

The exact quality of the evidence supplied to these paths, the relationship between them, and whether downstream state changes are semantically justified remain under investigation.

---

## 3. Initial BM-to-source matrix

| Spec responsibility | Existing source candidates at audited main | First-pass finding | Current disposition |
|---|---|---|---|
| BM-01 Experience intake and provenance | `event.hpp`, `brain.cpp`, `cognitive_cycle.cpp`, `memory.cpp` | Event carries sequence, timestamp, source, kind and attributes; `CognitiveCycle::run` passes an observation into `Brain::observe`; Memory appends journal events. Full source trust, modality and acquisition lineage still need tracing. | Reusable foundation; provenance completeness unverified |
| BM-02 Representation and interpretation | `world_model.hpp/.cpp`, `cognition.hpp`, perception-related sources to be traced | A WorldModel stores facts and relations with confidence, sequence and disputed status. This is not yet evidence of broad interpretation, ambiguity preservation or multimodal representation. | Partial candidate; deeper audit required |
| BM-03 Continuity and memory | `memory.hpp/.cpp` | Persistent event journal, metadata snapshot, memory tiers, ranked retrieval, salience/confidence metadata and working-tier demotion exist. Retrieval semantics and learned tier policy need deeper analysis. | Strong reusable foundation; integration gap found |
| BM-04 Belief/world-state management | `brain.hpp/.cpp`, `cognition.hpp`, `world_model.hpp/.cpp` | Brain stores beliefs in a keyed map; WorldModel separately stores facts/relations. Authority and synchronization between these representations are not yet established. | Potential state-ownership overlap; investigate |
| BM-05 Association, causal modelling and prediction | `association_model.*`, `causal_model.*`, prediction logic in `brain.cpp` | Causal links are inferred from observed transitions and used for bounded forward simulation; predictions can be journaled and resolved. Causal validity, confounding, generalization and attribution are not established by source presence. | Reusable candidate; causal overclaim risk |
| BM-06 Attention and active context | `attention.hpp/.cpp`, `attention_state.hpp`, `cognitive_cycle.*` | Attention scoring and reinforcement/suppression interfaces exist; cycle context contains selected working data. Actual control over compute allocation, interruption, resumption and starvation is not yet shown. | Partial candidate; integration unverified |
| BM-07 Affective appraisal and valuation | `threat.*`, `self_state.*`, PR #97 affective donor files | Main source visibly includes threat and internal-state signals; this alone does not establish contextual affective appraisal. PR #97 affective mechanisms are donor candidates, not main capability. | Main capability not demonstrated in this batch; donor audit required |
| BM-08 Goals, intent, planning and decision | `goals.*`, `intent.*`, `strategy.*`, `planning.*`, `decision.*`, `cognitive_cycle.cpp` | Goal lifecycle, intent selection, planning and decision mechanisms are wired in the cycle. Initial cycle selects from existing eligible goals; experience-acquired goal formation is not demonstrated by this path. | Reusable but supplied-goal bias / developmental gap |
| BM-09 Learning and developmental adaptation | `adaptation.*`, `learning_loop.*`, `evolution.*`, `brain.cpp` | Prediction feedback can update adaptive metrics and produce/adopt evolution proposals; several changes are journaled. Current inspected path is primarily scalar/keyed adaptation, not broad learned representation/strategy acquisition. | Narrow learning mechanisms exist; general learning unproven |
| BM-10 Metacognitive monitoring and control | `reflection.*`, `self_model.*`, `self_state.*`, `self_testing.*` | Reflection summarizes belief confidence and resolved prediction accuracy; self-model tracks capability health. Corrective authority and broad metacognitive monitoring remain unverified. | Partial monitoring candidates |
| BM-11 Integrated coordination and continuity control | `cognitive_cycle.*`, `brain.cpp`, `memory.cpp` | A sequential cycle coordinates a subset of responsibilities; Brain constructor replays journal events. This does not establish the specification's full recurrent/concurrent coordination, dependency invalidation or coherent multi-owner recovery. | Partial coordination; architecture gap likely |
| BM-12 General reasoning and inference | `reasoning.hpp/.cpp`, `cognitive_cycle.cpp` | Explicit ReasoningEngine exists, but it checks keyed-value consistency and traverses supplied causal links. Memory results are put in context but omitted from ReasoningProblem premises; reasoning results are not consumed by later cycle decisions in the inspected function. | Existing narrow inference; integration and breadth gaps |

This matrix is provisional. A first-pass label is not a final disposition.

---

## 4. Directly inspected integration paths

### 4.1 Cognitive cycle and reasoning — exact evidence

File: `core/cpp/src/cognitive_cycle.cpp`  
Blob: `3df14c552f2048b0394dc362f7ee7a654a93fb32`

Observed behavior:

- Lines 35–38: observation is sent to `brain_.observe`; ranked memories are retrieved; beliefs and causal links are copied into cycle context.
- Lines 40–44: `ReasoningProblem` receives beliefs, causal links and a step limit. The retrieved memories are not added to its premises.
- Lines 46–61: causal simulation results are converted into persisted predictions.
- Lines 63–71: eligible goals are obtained and one is selected.
- Lines 79–95: self-state uncertainty, goal values, threat and resource/deadline inputs are assembled into a planning context.
- Lines 108–120: plan outputs are passed to the decision engine.
- Lines 127–135: decisions are assessed against action constraints; the cycle completes without authorizing or executing an external action.
- Lines 138–158: separate outcome methods resolve predictions, pass evidence to learning and generate reflection.

File: `core/cpp/include/jarvis/core/cognitive_cycle.hpp`  
Blob: `28e7af98327956268a769adf7813125be842c1a2`

The context exposes memories, beliefs, causal links, predictions, reasoning, goals, plan, decisions, action assessments and reflection. This is useful shared-cycle context, but field presence does not prove that every result influences subsequent processing.

**Finding P2-I-001:** In this inspected cycle, memory retrieval is disconnected from the reasoning premise set, and the produced reasoning result has no visible downstream consumer in the remainder of `CognitiveCycle::run`. This is a concrete integration gap, not a claim that no other caller uses reasoning elsewhere.

### 4.2 Reasoning engine — exact evidence

File: `core/cpp/include/jarvis/core/reasoning.hpp`  
Blob: `5c6f82797d4f5052ad5d71a25624de192a2c87d9`

File: `core/cpp/src/reasoning.cpp`  
Blob: `feec78b2e8a1f2b0b58733fd509e4e5a750258fc`

Observed behavior:

- `consistent` detects different values for the same belief key.
- `infer` walks supplied causal links for up to `max_steps`, matching encoded cause values and adding unseen effect keys.
- `solve` treats an empty premise set as valid consistency with zero confidence.
- With non-empty consistent premises, it returns the premises plus derived effects.
- The result contains a coarse kind, validity, confidence, explanation and conclusions.

Limits visible in the inspected interface/implementation: no explicit assumption objects, premise provenance, temporal scope, counterexample handling, alternative explanation set, inference-step lineage or retrieved-memory input. The cycle does not consume its result downstream.

**Finding P2-I-002:** BM-12 is represented by a real but narrow rule/causal-link inference engine. It is not yet evidence of general reasoning as specified. This distinction is consistent with the specification's requirement that a named class is not sufficient proof.

### 4.3 Memory and continuity — exact evidence

File: `core/cpp/include/jarvis/core/memory.hpp`  
Blob: `f3662038237246efa51155f940d77564f144d6d9`

File: `core/cpp/src/memory.cpp`  
Blob: `ba72a897306d4761246d0deab2fbab37c49d372f`

Observed behavior:

- Memory stores an event continuity vector and metadata records.
- Event records preserve sequence, timestamp, source, kind and typed attributes.
- Journal persistence and loading exist; the loader validates sequence monotonicity and truncates an invalid trailing portion.
- Metadata stores tier, salience and confidence; metadata has its own persisted snapshot.
- Ranked recall uses attribute overlap/value matches, recency/index, salience and confidence.
- Working memory demotion changes tier metadata rather than deleting the underlying event.
- The API exposes Working, Episodic, Semantic and Procedural tiers.

Important limits:

- Tier labels do not prove semantic/procedural knowledge is actually acquired.
- The inspected recall is attribute-key/value matching, not semantic retrieval across paraphrases or abstraction.
- The journal and metadata snapshot are separate persistence artifacts; recovery consistency and crash-window semantics need dedicated tracing.
- The in-memory learned tier statistics and metadata restoration require further investigation before claiming learned consolidation.

### 4.4 Causal model and prediction — exact evidence

File: `core/cpp/include/jarvis/core/causal_model.hpp`  
Blob: `f740bdf222b3309b13f0c2f541c97448fc05da3e`

File: `core/cpp/src/causal_model.cpp`  
Blob: `f873d0a6e7fa0676bb88bf7a1f66436bc88a3c0d`

Observed behavior:

- A changed belief between before/after vectors is paired with other changed/current facts to create or strengthen causal links.
- New links begin at strength 0.55; repeated observations strengthen a link by a fixed incremental formula.
- Simulation follows links above a fixed 0.5 threshold, bounded to at most eight levels, and discounts confidence by depth.
- The model exposes predicted values and confidence.

This is a candidate association/transition-learning mechanism, but the source path does not establish intervention, confounder control, counterfactual evaluation, context-conditional causality or transfer reliability. Repeated temporal co-occurrence must not be reported as verified causal understanding.

### 4.5 Goal processing and developmental goal formation — exact evidence

File: `core/cpp/include/jarvis/core/goals.hpp`  
Blob: `803fdd34130c71f54912b23fcba2f9eed23dd4f2`

File: `core/cpp/src/goals.cpp`  
Blob: `778a829de8314e83b095af2f2c2a6b83baa769f4`

File: `core/cpp/include/jarvis/core/intent.hpp`  
Blob: `1749ae0d795da496dd6a9a4dcdbd203ae7ddaf6f`

File: `core/cpp/src/intent.cpp`  
Blob: `4283a4255284c51257df6bad12734782f2a6cde9`

Observed behavior:

- Goals can be created, activated, progressed, completed, abandoned and reprioritized.
- Eligibility checks prerequisites and deadlines.
- Intent selects from supplied goals using priority, progress need and deadline; urgency also considers threat.
- The inspected cycle selects the first eligible goal unless a goal ID is supplied.

No inspected source in this batch establishes an experience-derived candidate-goal generator. The ability to create a goal via API is not equivalent to the Brain developing candidate goals from experience.

### 4.6 Learning/adaptation — exact evidence

File: `core/cpp/include/jarvis/core/learning_loop.hpp`  
Blob: `287f2fe34cebd60b7a562d68c666572f71431cd6`

File: `core/cpp/src/learning_loop.cpp`  
Blob: `bc9a6aaca38d060667bcdf82f2b1a1f72c5936ba`

Observed behavior:

- Feedback consists of a key, predicted scalar, actual scalar and fitness.
- Adaptation observes predicted versus actual values.
- Evolution observes fitness and produces proposals.
- Adoption is gated by proposal confidence >= 0.75 and positive expected gain.
- The Brain's prediction-feedback path journals outcome/fitness/adoption events and updates the corresponding models.

This is concrete, reusable scalar adaptation/evolution infrastructure. It does not yet establish learning of concepts, representations, broad strategies or skills, nor held-out transfer. Donor work may extend these paths, but requires its own exact-source and integration evidence.

### 4.7 Attention and reflection — exact evidence

File: `core/cpp/include/jarvis/core/attention.hpp`  
Blob: `c7e8ab0c5430d5c942fe314d928400f769c0a77c`

File: `core/cpp/src/attention.cpp`  
Blob: `58f734dbe9772675d687752026231297f289e770`

Attention computes salience from novelty, uncertainty and urgency using policy weights; reinforcement/suppression and policy replacement are exposed. The inspected cycle does not show attention allocating compute, suspending competing work or resuming it.

File: `core/cpp/include/jarvis/core/reflection.hpp`  
Blob: `435e03f8f03f74cb910338ab4ab1264e4eaf085c`

File: `core/cpp/src/reflection.cpp`  
Blob: `06f34e20f35aad535a2c606b3669b2127ef7a480`

Reflection computes aggregate belief uncertainty and resolved prediction accuracy and emits limited observations. This is useful monitoring, but not yet evidence of a full metacognitive correction controller.

---

## 5. Cross-mechanism findings and risks

### P2-I-001 — Retrieved memory is not used as reasoning premises in the inspected cycle
**Status:** Confirmed for `CognitiveCycle::run` at the audited baseline.  
**Implication:** Memory presence and retrieval are not sufficient to claim memory-supported reasoning integration.  
**Next investigation:** Trace all other reasoning callers and determine whether another path provides contextual memory to inference.

### P2-I-002 — Reasoning result is not consumed downstream in the inspected cycle
**Status:** Confirmed for the inspected function.  
**Implication:** Reasoning is currently an observational side result in this cycle path, not demonstrated as a causal input to planning/decision.  
**Next investigation:** Search all consumers and establish whether any other end-to-end reasoning path affects belief, plan or decision.

### P2-I-003 — Mainline goal lifecycle is not experience-acquired goal formation
**Status:** No generator identified in inspected path; repository-wide absence not established.  
**Implication:** Current goal API and priority selection cannot be counted as the specification's developmental goal formation capability.  
**Next investigation:** Trace all candidate goal creation callers, event types and donor branches.

### P2-I-004 — Causal links can overstate causality
**Status:** Mechanism-level risk visible in implementation.  
**Implication:** Transition co-occurrence is promoted to causal-link strength without explicit confounder/intervention/counterexample handling in this model.  
**Next investigation:** Trace provenance of before/after states and tests that challenge spurious correlation.

### P2-I-005 — CognitiveCycle is a sequential orchestration path, not proof of full recurrent/concurrent cognition
**Status:** Confirmed for this class/function only.  
**Implication:** Do not equate one integrated call path with complete BM-11 coordination.  
**Next investigation:** Identify schedulers, event loops, asynchronous/parallel work, dependency invalidation, interruption and recovery paths elsewhere in the repository.

### P2-I-006 — Memory journal and metadata have separate persistence paths
**Status:** Confirmed structurally.  
**Implication:** Need to inspect crash recovery, partial writes, metadata rebuild, atomicity and replay consistency before accepting memory continuity.  
**Next investigation:** Audit serialization failure paths and tests.

---

## 6. Hardcoding and safety classification

The next audit must distinguish:

- **Integrity constraints:** sequence monotonicity, finite/bounded values, provenance preservation, state ownership and valid lifecycle transitions. These are legitimate deterministic constraints.
- **Governance constraints:** authorization, permission, action validation and containment. These must remain deterministic and must not be learned away.
- **Initial neutral/bootstrapping parameters:** configurable initial values that enable operation but are not claims about acquired preferences.
- **Cognitive shortcuts:** fixed mappings that encode the conclusion the Brain is expected to learn, universal event-kind rules, unqualified emotion/action mappings or fixed causal conclusions. These require challenge.
- **Bounded computational safeguards:** maximum recursion/steps/horizon or resource limits. These may be necessary, but their effect on cognition and generalization must be evaluated rather than misclassified automatically as hardcoding.

Examples already visible include the fixed causal-link strength increment and threshold, capped simulation horizon, default memory salience/confidence, and attention policy weights. These are not automatically defects: the audit must determine whether they are safety/operational bounds, neutral initialization, or unjustified cognitive priors.

---

## 7. Work remaining in Phase 2

The first evidence batch is substantial but does not close the phase. Remaining work:

1. Complete BM-01/BM-02 acquisition, perception and representation source tracing.
2. Reconcile Brain belief map with WorldModel facts/relations and identify authoritative state ownership.
3. Trace every call site and downstream consumer of reasoning, memory retrieval, prediction and goal creation.
4. Inspect affective/valuation mechanisms on main and PR #97 donor branch; distinguish donor-only capability from integrated main behavior.
5. Trace action execution, verification, consequence evidence and outcome attribution.
6. Trace adaptation, learning, evolution and strategy mechanisms across main and donor PRs, including persistence/replay and rollback.
7. Audit all BM-11 coordination, concurrency, interruption, invalidation and recovery paths.
8. Inspect relevant tests and CMake registration; distinguish source presence, target registration, CI execution and behavior demonstrated.
9. Produce an interaction/dependency graph and state-flow matrix covering all twelve mechanisms.
10. Produce a reuse disposition register: retain, adapt, integrate, replace, defer, or unresolved—with evidence and conflict analysis.
11. Map every gap to the accepted specification and Phase 1 findings.
12. Self-review for missing call sites, mutable references, ungrounded absence claims and contradictions before independent review.

No implementation ticket or technology choice should be created from a partial finding.

---

## 8. Phase 2 exit criteria

Phase 2 is complete only when:

- all twelve BM responsibilities have source-level traceability or an evidence-backed "not found within audited scope" disposition;
- the major cross-mechanism flows are traced end to end;
- state ownership and duplicate/overlapping representations are reconciled;
- donor/main differences and porting risks are explicit;
- persistence, replay and outcome-feedback chains are mapped;
- test sources, registration and actual CI evidence are distinguished;
- reuse/adaptation/replacement decisions are justified rather than assumed;
- all gaps and conflicts are tied to the Phase 1 register and accepted specification;
- an independent reviewer can reproduce the conclusions from pinned commits and paths.

**Phase 2 is currently IN PROGRESS. No implementation is authorized by this report.**
