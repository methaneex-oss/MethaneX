# Existing Brain Mechanism Source Audit — 2026-11-03

**Purpose:** Record what the current engineering baseline actually contains before specifying further mechanisms.  
**Audit type:** Static source inspection only.  
**Repository:** \`methaneex-oss/MethaneX\`  
**Branch:** \`main\`  
**Exact source baseline:** \`1273ddbcd0087d189e01388ded2d362fb1e058d2\`  
**Related specification:** \`docs/architecture/specifications/00_BRAIN_MECHANISM_SPECIFICATION.md\`

**Important:** No build, runtime tests, benchmarks, sanitizer runs or execution experiments were performed for this audit. A method, class or test source file is not proof that a capability works end to end.

---

## 1. Audit method and claim boundaries

The audit inspected the source files listed below at the exact baseline commit. It records visible behavior and integration boundaries, not inferred runtime success.

The accepted architecture and capability investigation are the authority for what the Brain must become. Existing source is evidence of reusable mechanisms and current gaps; it is not an instruction to preserve every current implementation choice.

### Primary inspected source files

| Source | Blob SHA | Inspection purpose |
|---|---|---|
| \`core/cpp/include/jarvis/core/event.hpp\` | \`a31db633e8181378fcec0a20c5958c0065d430ee\` | Event and attribute representation |
| \`core/cpp/include/jarvis/core/brain.hpp\` | \`8268ef84e0b361ead536724ba7761904b30ee58f\` | Brain state ownership and public surface |
| \`core/cpp/src/brain.cpp\` | \`e9f3758fcc9c0e89b7280ce376db9033d547682d\` | Replay, belief updates and observation processing |
| \`core/cpp/src/brain_restored_api.cpp\` | \`618deb6976eed951eae02b7f0da741e6d730bb0c\` | Prediction, affect-related and goal outcome APIs |
| \`core/cpp/include/jarvis/core/memory.hpp\` | \`f3662038237246efa51155f940d77564f144d6d9\` | Memory responsibilities and state |
| \`core/cpp/src/memory.cpp\` | \`ba72a897306d4761246d0deab2fbab37c49d372f\` | Persistence, ranking and promotion |
| \`core/cpp/include/jarvis/core/cognitive_cycle.hpp\` | \`28e7af98327956268a769adf7813125be842c1a2\` | Cycle input/context/result |
| \`core/cpp/src/cognitive_cycle.cpp\` | \`3df14c552f2048b0394dc362f7ee7a654a93fb32\` | Current integrated cycle path |
| \`core/cpp/include/jarvis/core/cognitive_workspace.hpp\` | \`b015d44e332ea2511d29e607495714d0b982d44e\` | Shared workspace contents |
| \`core/cpp/src/cognitive_workspace.cpp\` | \`fbd2321d9cd1c98217389beced292654e33a906e\` | Workspace snapshot/replace/clear |
| \`core/cpp/src/cognitive_runtime.cpp\` | \`1a1383cedc42e357dc9efce117328b8d55e30bca\` | Runtime scheduling and workspace projection |
| \`core/cpp/src/learning_loop.cpp\` | \`bc9a6aaca38d060667bcdf82f2b1a1f72c5936ba\` | Current learning loop |
| \`core/cpp/src/adaptation.cpp\` | \`7e07a491a5b13379a5719882a834ecc2452a54ef\` | Numeric adaptation |
| \`core/cpp/src/attention.cpp\` | \`58f734dbe9772675d687752026231297f289e770\` | Attention scoring/reinforcement |
| \`core/cpp/src/goals.cpp\` | \`778a829de8314e83b095af2f2c2a6b83baa769f4\` | Goal lifecycle |
| \`core/cpp/src/intent.cpp\` | \`4283a4255284c51257df6bad12734782f2a6cde9\` | Intent selection |
| \`core/cpp/src/strategy.cpp\` | \`5406a341cd4b3f42e16166f6122a0cb580aee298\` | Strategy context formulation |
| \`core/cpp/src/causal_model.cpp\` | \`f873d0a6e7fa0676bb88bf7a1f66436bc88a3c0d\` | Causal link formation/simulation |
| \`core/cpp/src/association_model.cpp\` | \`b378d4237527dfbb4c65f43545f7f0fc7c42669b\` | Association updates |
| \`core/cpp/src/knowledge.cpp\` | \`25ecf822e6132f576266c1f86a964a227c7fb75f\` | Source reliability metric |
| \`core/cpp/src/perception_pipeline.cpp\` | \`ab9a745bb68e416d4e32c9d0c26a2d0b2016ab17\` | Provider-based representation acquisition |
| \`core/cpp/include/jarvis/core/reasoning.hpp\` | \`5c6f82797d4f5052ad5d71a25624de192a2c87d9\` | Reasoning problem/result/engine interfaces |
| \`core/cpp/src/reasoning.cpp\` | \`feec78b2e8a1f2b0b58733fd509e4e5a750258fc\` | Consistency checking and bounded causal-link inference |
| \`core/cpp/include/jarvis/core/cognitive_cycle.hpp\` | \`28e7af98327956268a769adf7813125be842c1a2\` | Reasoning and memory cycle-context fields |
| \`core/cpp/src/cognitive_cycle.cpp\` | \`3df14c552f2048b0394dc362f7ee7a654a93fb32\` | Actual memory retrieval and reasoning invocation path |

The source links are reproducible by opening each path at the exact commit above.

---

## 2. Existing mechanisms and evidence

### 2.1 Event and experience representation

**Observed:**

- \`Event\` carries sequence, timestamp, source, kind and an attribute map.
- Attribute values are limited to a scalar variant: null, boolean, integer, floating point or string.
- \`Observation\` wraps an event and a novelty value.
- A separate representation engine can normalize events into semantic nodes and relations with evidence spans.
- A perception pipeline can ask registered providers whether they support an input, validate their representation, select the strongest-confidence valid result, isolate provider exceptions and fall back to normalized event representation.

**Limitations visible at this boundary:**

- The event envelope itself does not provide first-class typed fields for event time versus receipt time, modality, context scope, epistemic status, provenance chain, source reliability, uncertainty dimensions or derivation lineage.
- Those concepts may be carried indirectly in attributes or other structures, but the event type does not enforce them.
- Selecting the strongest-confidence provider result is not the same as reconciling competing interpretations or preserving multiple plausible hypotheses.
- Provider confidence is not automatically source reliability or belief confidence.

**Specification consequence:** Preserve the existing event/representation capability as potential infrastructure, but specify explicit evidence and epistemic semantics before treating the current envelope as sufficient.

### 2.2 Memory and retrieval

**Observed:**

- Memory maintains a durable event continuity journal and a separate metadata file.
- Memory records carry a tier, salience and confidence.
- The declared tiers are Working, Episodic, Semantic and Procedural.
- Memory can append, enumerate, query by source/kind, retrieve recent events, rank records, list salient records, promote records and demote excess Working records.
- Tier selection is influenced by learned counts keyed by event kind.
- Ranked retrieval compares query attributes with stored event attributes. The score combines exact matching values, attribute overlap, relative record position, salience and confidence.
- The source comment states that tier selection, salience and retrieval are intended to be learned from memory feedback rather than encoded as event-kind rules.

**Limitations visible at this boundary:**

- The inspected ranked retrieval is structured attribute-overlap retrieval. It does not demonstrate semantic/conceptual retrieval across different wording, modalities or abstraction levels.
- The ranking's relative record-position component is not a substitute for temporal relevance, causal context or task relevance.
- The metadata record does not itself express a rich consolidation lineage or the evidence behind why a record was promoted.
- The existence of multiple tier labels does not demonstrate distinct working, episodic, semantic and procedural memory behavior.
- The inspected retrieval path must be checked at the integration boundary, not only within Memory.

**Integration finding:** \`CognitiveCycle::run\` obtains ranked memories and stores them in its result context. It then constructs \`ReasoningProblem\` using beliefs and causal links only. The retrieved memories are not passed into the inspected reasoning premises. This is a concrete memory-to-reasoning integration gap in that path.

### 2.3 Beliefs and world state

**Observed:**

- A belief contains key, scalar value, confidence, observation count and updated sequence.
- Brain stores beliefs in a map keyed by attribute name.
- During replay, event attributes are iterated and used to create or update beliefs.
- If a value matches the existing value, confidence increases using a generic reliability-weighted adjustment.
- If a value differs, the current value is overwritten and confidence decreases using a generic adjustment.
- The world model receives facts and may receive a relation when subject, predicate and object attributes are present.
- The world model has a disputed flag in its fact/relation types.

**Limitations visible at this boundary:**

- The inspected belief record does not preserve explicit source/evidence lineage, scope, validity interval, competing hypotheses or revision reason.
- One key maps to one current scalar belief; alternative claims are not represented in that record.
- The generic same/different update is not a complete evidence-sensitive belief revision mechanism.
- A contradiction can lower confidence while the current value is still replaced; this does not by itself preserve the alternative claim.
- A disputed flag in a world-model type is not proof that conflict detection, reconciliation and downstream invalidation are fully integrated.

**Specification consequence:** Belief revision requires richer conceptual semantics and must not be reduced to overwriting a key/value pair with a confidence adjustment.

### 2.4 Association and causal modelling

**Observed:**

- AssociationModel observes before/after belief snapshots.
- When a belief key changes, it forms associations between that changed key and other current belief keys, updating strength and confidence.
- CausalModel observes before/after belief snapshots.
- When a belief changes, CausalModel pairs its new encoded value with other values present in the after-state and creates or strengthens causal links.
- Simulation traverses links above a fixed minimum strength and produces predictions with confidence reduced by traversal depth.

**Limitations visible at this boundary:**

- Co-presence of a changed belief and another current belief is not sufficient causal evidence.
- The inspected causal update does not explicitly control for confounding, temporal ordering, alternative causes, interventions or counterexamples.
- Association strength and causal strength must remain distinct concepts.
- A traversal threshold is an implementation rule, not evidence that a relation is causally valid.
- The source does not demonstrate broad causal discovery or counterfactual evaluation.

**Specification consequence:** The mechanism must distinguish association, co-occurrence and causal hypotheses, preserve scope and counterevidence, and avoid promoting observed co-state transitions into universal causal knowledge.

### 2.5 Prediction and outcome comparison

**Observed:**

- A prediction record contains key, predicted scalar, confidence, creation sequence, resolved status and error.
- Predictions are persisted as events and reconstructed by replay.
- An outcome can resolve an unresolved prediction; numeric predictions use bounded absolute difference while non-numeric values use exact equality.
- Resolved numeric prediction outcomes can update an adaptive metric.
- A restored API also supports resolving by prediction sequence, which is important where similar keys may have multiple predictions.

**Limitations visible at this boundary:**

- The inspected core prediction record does not explicitly preserve prediction scope, assumptions, horizon, expected observation conditions or resolution criteria.
- A generic error measure is not suitable for every prediction domain.
- Outcome attribution and event-time matching need explicit semantics.
- A prediction outcome event should not be treated as a valid external outcome merely because a caller supplied a scalar.

**Specification consequence:** Prediction lifecycle, independent identity, resolution conditions, outcome provenance and domain-appropriate comparison must be specified before extending learning claims.

### 2.6 Attention and active context

**Observed:**

- Attention scoring uses novelty, uncertainty derived from strongest belief confidence, and an optional urgency attribute.
- The default attention policy weights those three features equally.
- Reinforcement and suppression modify the policy weights.
- Attention state can maintain contexts with salience, priority, last-seen cycle, observation count and focus status.
- A CognitiveWorkspace structure can hold observation, memories, beliefs, causal links, predictions, reasoning, goals, selected goal, plan, decisions, action assessments, intent, strategy and reflection.
- The workspace store supports snapshot, replace and clear under a mutex.
- The runtime projects a cycle result into a workspace snapshot.

**Limitations visible at this boundary:**

- The inspected AttentionModel scoring interface does not directly take goal relevance, affective appraisal, resource contention, consequences or task-specific context as inputs.
- The default equal weights are a bootstrap policy, not a learned attention capability.
- A workspace snapshot containing many fields is not proof of authoritative state ownership, dependency freshness, multi-context isolation or concurrency reconciliation.
- The inspected cycle/runtime path must be assessed for whether workspace state is actually used to coordinate later cognition, not merely populated for inspection.

**Specification consequence:** Attention and workspace need explicit ownership, freshness, interruption, resumption, starvation and dependency semantics.

### 2.7 Goals, intent and strategy

**Observed:**

- Goal records contain identifier, description, priority, progress, creation cycle, deadline cycle, status, prerequisites and subgoals.
- GoalModel supports create, activate, progress update, complete, abandon and priority update.
- Eligibility checks status, deadline and completed prerequisites, then sorts by priority and creation order.
- Brain exposes goal creation and lifecycle operations.
- CognitiveCycle uses a supplied goal identifier when present; otherwise it selects the first eligible goal.
- IntentModel selects among eligible goals using priority, remaining progress and deadline pressure.
- StrategyModel maps intent, attention, threat, uncertainty and resource budget into planning context.

**Limitations visible at this boundary:**

- The inspected goal lifecycle does not form candidate goals from experience.
- Goal creation requires an already formed Goal object with an identifier and description.
- Goal priority is supplied or explicitly updated; the inspected path does not demonstrate experience-acquired priority formation.
- Selecting the first eligible goal is a deterministic fallback, not evidence of autonomous goal formation or context-sensitive goal evaluation.
- Intent/strategy are downstream transformations of existing goal state; they do not establish an acquired motivational system.

**Specification consequence:** Preserve supplied-goal processing, but separately specify experience-acquired candidate-goal formation, evidence lineage, evaluation, revision and abandonment.

### 2.8 Learning and evolution

**Observed:**

- AdaptationModel maintains per-key numeric estimate, mean error and observation count.
- It updates estimate and mean error using a running average over bounded numeric prediction/outcome values.
- Confidence depends on observed experience count and mean error.
- LearningLoop updates the adaptation metric, observes fitness, requests evolution proposals and adopts a matching proposal only when confidence is at least 0.75 and expected gain is positive.
- Brain's prediction-feedback path records outcome and fitness events, invokes LearningLoop and records an adoption event when the evolution model has adopted a changed parameter.
- The repository contains a broader set of evolution-related modules for candidate generation, experiments, canary observations, history, rollback, scheduling and evaluation.

**Limitations visible at this boundary:**

- The inspected LearningLoop is centered on numeric prediction feedback and evolution parameters.
- This does not demonstrate generalized concept acquisition, belief-structure revision, causal-model correction, semantic memory development, learned goal formation or procedural skill acquisition.
- A confidence threshold and positive expected-gain check are safeguards for that narrow proposal path; they are not a universal learning criterion.
- The existence of experiment/canary/rollback modules does not demonstrate that every cognitive state class can be changed, evaluated and restored coherently.
- The inspected generic learning-event path assimilates one non-reliability field into the knowledge-source metric; it is not a complete cross-capability learning process.

**Specification consequence:** Learning must be specified as a cross-mechanism developmental process with explicit attribution, candidate formation, evaluation, activation, persistence, transfer and regression protection.

### 2.9 Metacognition and self-state

**Observed:**

- Reflection reports coherence, uncertainty, prediction accuracy and observations.
- Brain maintains a self-state model with activity, workload, uncertainty, health, active goals and resource pressure.
- The inspected \`sync_self_state\` path derives several self-state values from event counts, threat, attention, novelty and capability health.

**Limitations visible at this boundary:**

- A reflection summary is not proof that the system can inspect the actual provenance and assumptions behind every conclusion.
- Self-state fields derived from broad aggregate values may be insufficient for context-specific metacognitive diagnosis.
- The inspected source does not establish a complete corrective loop from detected limitation through targeted correction to evaluation of whether correction worked.

**Specification consequence:** Specify bounded metacognitive monitoring tied to actual evidence and state dependencies, not only summary metrics.

### 2.10 Affective and developmental API discrepancy requiring investigation

Static source inspection found affect-related and developmental-learning API definitions in \`core/cpp/src/brain_restored_api.cpp\`, including methods referring to:

- \`affective_state_model_\`;
- \`affective_learning_model_\`;
- \`developmental_learning_\`;
- goal outcome assimilation.

However, the \`Brain\` class declaration retrieved from \`core/cpp/include/jarvis/core/brain.hpp\` at the same exact baseline does not show those corresponding members in its inspected private member inventory, and the visible public declaration set does not show all corresponding methods.

This is a **source-level integration discrepancy**, not a confirmed build failure. No build or test was run. The compilation unit membership, conditional declarations, generated files or other integration explanation must be checked before these APIs are counted as integrated, functioning foundational affective or developmental mechanisms.

**Specification consequence:** Minimum affective appraisal remains a required architectural capability. The current source inventory does not yet establish that its implementation is integrated and usable.

### 2.11 General reasoning and inference

**Observed interfaces:**

- \`reasoning.hpp\` defines \`ReasoningProblem\` with only a vector of belief premises, causal links and a maximum step count.
- \`ReasoningResult\` carries a kind, validity flag, one confidence value, a free-form explanation and derived belief conclusions.
- \`ReasoningEngine\` exposes \`solve\`, \`infer\` and \`consistent\`.

**Observed implementation in \`reasoning.cpp\`:**

- \`consistent\` detects only incompatible scalar values associated with the same belief key.
- \`infer\` copies supplied premises, parses causal-link endpoints encoded as \`key=value\`, and traverses links with positive strength for a bounded number of steps. A link is followed when its cause key/value is already known and its effect key is not already present.
- Derived belief confidence is based on the clamped link strength; the inspected path does not carry a premise/evidence lineage into the derived belief.
- The traversal does not evaluate counterexamples, alternative explanations, assumption sets, premise scope, source provenance, temporal applicability or whether a causal link is merely a hypothesis with limited support.
- If an effect key is already present, the traversal skips it; it does not produce an explicit contradiction/counterexample record for that conflict.
- \`solve\` treats an empty premise set as \`valid=true\` with zero confidence and an explanatory string stating that no premises were supplied. Inconsistent premises return a contradiction result. Otherwise, the result is classified as deduction when new beliefs were added or consistency when none were added.

**Observed integration in \`CognitiveCycle::run\`:**

1. Ranked memories are retrieved and stored in \`result.context.memories\`.
2. Current beliefs and causal links are loaded separately.
3. \`ReasoningProblem\` receives \`result.context.beliefs\`, \`result.context.causal_links\` and the step bound only. Retrieved memories, interpretations, explicit assumptions, task question/context and premise provenance are not passed to the reasoning engine in this path.
4. The result is stored in \`result.context.reasoning\`.
5. In the inspected remainder of this cycle, the reasoning result is not used to revise BM-04 belief state, alter prediction premises, evaluate goals or influence plan/decision formation. The cycle continues through prediction, goal selection and planning using their other inputs; it does not gate downstream work on reasoning validity.

**Limitations visible at this boundary:**

- The code establishes a narrow consistency check and bounded traversal over pre-supplied causal links, not general reasoning across diverse evidence types.
- There is no explicit reasoning ownership contract in the existing cycle beyond the engine call/result field.
- Premises are not individually identified with provenance, assumptions, scope or dependency versions.
- Retrieved memories are context output only in this path; they do not materially influence the inspected inference operation.
- The single result confidence and explanation string do not establish calibrated uncertainty or inspectable premise-to-conclusion lineage.
- Empty premises being marked valid is not evidence of a substantive inference; consumers must distinguish no-op/insufficient-evidence from a supported conclusion.

**Specification consequence:** The integrated specification now assigns BM-12 explicit ownership of general reasoning/inference and its provisional conclusion/lineage records. BM-04 remains authoritative for belief commitment; BM-02, BM-03, BM-05 and BM-08 retain their separate representation, memory, causal/prediction and planning/decision responsibilities. The source audit does not establish that BM-12 is implemented. Memory-to-reasoning integration and downstream use of reasoning conclusions remain unverified gaps.

---

## 3. Cross-mechanism integration findings

| ID | Existing mechanism | Observed integration gap or limitation | Specification obligation |
|---|---|---|---|
| AUD-01 | Memory retrieval | Retrieved records enter cycle context but not the inspected reasoning premises | Define and verify memory-to-reasoning evidence flow |
| AUD-02 | Belief revision | Key/value overwrite with generic confidence adjustment | Preserve competing claims, provenance, scope and revision lineage |
| AUD-03 | Causal learning | Changed belief co-state can create causal links | Separate association from causal hypotheses and require counterevidence |
| AUD-04 | Prediction | Scope, assumptions, horizon and resolution criteria not explicit in core record | Define scoped prediction lifecycle and attributed resolution |
| AUD-05 | Attention | Limited scoring inputs and neutral equal bootstrap weights | Define context-sensitive prioritization and acquired weighting |
| AUD-06 | Workspace | Snapshot container lacks demonstrated freshness/dependency semantics | Define bounded active context, ownership and invalidation |
| AUD-07 | Goal formation | Goal objects are supplied; no inspected experience-acquired candidate formation | Specify candidate generation/evaluation as developmental capacity |
| AUD-08 | Learning | Narrow numeric adaptation/evolution path | Specify multiple learning classes and persistent behavioral evidence |
| AUD-09 | Affective processing | API/source integration discrepancy | Reconcile actual ownership and establish foundational appraisal behavior |
| AUD-10 | Metacognition | Reflection/self-state summaries do not establish corrective cognition | Tie monitoring to actual evidence, dependencies and verified correction |
| AUD-11 | Recovery | Journal replay exists, but complete validation of every derived mechanism is not demonstrated by this inspection | Specify recovered-state validation and partial-failure semantics |
| AUD-12 | General reasoning/inference | Existing engine performs narrow belief-key consistency checks and bounded causal-link traversal; memories are retrieved but omitted from premises, and reasoning output is not consumed downstream in the inspected cycle | Assign explicit reasoning ownership, define premise/assumption/provenance/uncertainty/counterexample contracts, and require end-to-end reasoning acceptance scenarios |

---

## 4. What can be reused versus what cannot yet be claimed

### Potentially reusable existing mechanisms

- Event journal and monotonic sequencing.
- Basic representation normalization and provider isolation.
- Durable event retention and memory metadata.
- Basic structured memory retrieval.
- Belief and world-model containers.
- Association and causal-model prototypes.
- Prediction records and outcome resolution.
- Attention scoring and reinforcement.
- Goal lifecycle and prerequisite handling.
- Intent, planning and decision components.
- Existing \`ReasoningEngine\` interface and bounded causal-link inference prototype; reuse is conditional on meeting the expanded BM-12 evidence, lineage and integration contract.
- Numeric adaptation and controlled parameter evolution.
- Reflection and self-state summaries.
- Cognitive runtime queue and workspace projection.
- Recovery, experiment and rollback-related components.

These are candidates for compatibility assessment, not approved final mechanisms.

### Capabilities not established by this static audit

- Memory retrieval materially influencing reasoning in the inspected CognitiveCycle path.
- General reasoning across evidence types with explicit assumptions, premise provenance, competing explanations, counterexamples and inspectable conclusion lineage.
- Reasoning conclusions being evaluated by authoritative owners and materially influencing downstream belief, prediction, goal or planning processes.
- General semantic/conceptual memory retrieval across different wording or modality.
- Evidence-complete belief revision with competing hypotheses and lineage.
- Reliable causal discovery beyond co-state association.
- Scoped prediction with explicit assumptions/horizon/resolution conditions.
- Experience-acquired candidate-goal formation.
- Integrated foundational affective appraisal.
- Broad cross-representation learning and transfer.
- End-to-end metacognitive correction.
- Coherent multi-mechanism recovery under partial failure and concurrency.

"Not established" does not mean "impossible" or "no related code exists." It means the inspected source does not justify claiming the capability.

---

## 5. Relationship to the accepted architecture

The audit supports the accepted architecture's central distinction:

- Existing mechanisms provide useful starting material.
- Several current paths are narrower than the foundational capability they are intended to support.
- A coherent Brain requires mechanisms to exchange and use one another's state, not merely coexist as source files or APIs.
- The most important gaps are integration and evidence semantics, not simply a lack of more modules.

The detailed specification therefore prioritizes explicit ownership, evidence lineage, dependency handling and end-to-end learning behavior.

---

## 6. Audit limits and follow-up

This audit does not inspect every source file, every test, every build target or every runtime configuration. It is a bounded mechanism audit, not a complete codebase audit.

Before implementation, a later source-compatibility investigation should:

1. map all relevant declarations, definitions, build-target membership and dependencies;
2. reconcile the affective/developmental API discrepancy;
3. trace event replay and persistence for each authoritative state owner;
4. inspect the complete memory feedback/consolidation path;
5. inspect evolution experiment, canary and rollback interactions with all affected state classes;
6. inspect runtime scheduling, queue semantics and workspace consumption;
7. identify exact tests that exercise integration rather than isolated APIs;
8. execute only after a separate verification authorization.

**No runtime tests or builds were run for this audit.**

**End of audit.**
