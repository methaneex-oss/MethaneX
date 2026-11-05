# Phase 2 — Whole-Brain Capability-to-Source Integration Map

**Date:** 2026-11-05  
**Repository:** `methaneex-oss/MethaneX`  
**Phase 2 branch:** `docs/jarvis-phase-2-whole-brain-integration-map-20261105`  
**Documentation parent:** PR #178 head `39fe09dcf13496f5f0005ccf3f00739303e29f88`  
**Accepted specification reference:** PR #174 exact accepted head `0811a59e46bf934e32e794f90e4e7d18d4e2bd97`  
**Specification blob:** `docs/architecture/specifications/00_BRAIN_MECHANISM_SPECIFICATION.md` — `3b6a53c8a295fa0d9fc29bbb6c7688b61d1dcdb1`  
**Engineering source baseline:** `main` at `1273ddbcd0087d189e01388ded2d362fb1e058d2`  
**Source-audit package:** PR #174, exact accepted head above; source-audit blob `4479874476715fd59a4c3ba6c908f06c43a1c6c2`  
**Donor reference:** PR #97 exact inspected head `c1da222e6c94aeb3f2ad000392c21fe4fc81ab25`; open/draft/unmerged  
**Status:** Phase 2 source-to-capability mapping in progress. This report is the first source-backed integration map, not Phase 2 completion or an implementation baseline.

---

## 1. Purpose and decision boundary

Phase 2 maps the twelve logical Brain mechanisms in accepted PR #174 to the actual repository: current main implementation, selected donor implementation, authoritative state ownership, inputs/outputs, downstream consumers, persistence/replay, test evidence, and known limitations.

The unit of analysis is the **integrated Brain**, not twelve independent modules. A mechanism is not considered integrated merely because a class, header, source file, test source, or workspace field exists. The relevant question is whether its state and outputs participate in the required recurrent cognitive processes and whether changes remain coherent across persistence, interruption, recovery and later behavior.

This is documentation/source investigation only.

- No runtime code, tests, build configuration, dependencies or interfaces were changed.
- No build, runtime test, benchmark or sanitizer was run.
- No donor PR was merged.
- No implementation baseline was selected.
- No implementation authorization is inferred from Phase 1 completion, PR #174 acceptance or this mapping.
- Gate A remains **NOT CLEARED** in the last recorded evidence and must be rechecked before any later gate decision.

### 1.1 Evidence labels used here

| Label | Meaning |
|---|---|
| **Main source present** | The pinned main tree contains a relevant implementation. This does not establish full specification compliance. |
| **Partial** | Some required behavior exists, but important semantics, consumers or lifecycle stages are absent or incomplete. |
| **Donor-only** | A relevant path exists in a separate, unmerged donor revision. It is not current-main capability. |
| **Integration gap** | Source exists but the required information does not reach, or is not consumed by, the next mechanism. |
| **Not demonstrated** | The inspected source does not establish the capability. This is not proof that no related code exists elsewhere. |
| **Blocked for implementation** | An open specification finding, uncleared gate, or missing authorization prevents implementation reliance. |
| **Reuse / adapt / defer** | Preliminary source disposition, not an approved implementation decision. |

### 1.2 Phase 1 continuity and impact

The following Phase 1 conclusions are carried forward:

1. The project is substantial and must not be restarted.
2. Main at `1273ddbcd0087d189e01388ded2d362fb1e058d2` is the pinned engineering baseline for this map, not a claim that main is the complete Brain.
3. PR #97 at `c1da222e6c94aeb3f2ad000392c21fe4fc81ab25` is a donor source, not an approved implementation baseline. It is open, draft, unmerged and contains 159 changed files.
4. Later PR #148–#156 work is also donor material and must be evaluated at exact revisions before reuse.
5. PR #174 was formally accepted as a planning baseline at the exact head recorded above. The PR #173 architecture review correction record identifies F-02 as experience-acquired candidate-goal formation and F-03 as the SYS-08 computational-substrate boundary; its corrected architecture and correction record are mapped in §14. The downstream reasoning-consumption gap is a separate PR #174 source-audit finding (AUD-12 / this report's IF-03), not F-03. The exact original reviewer prose and the independent-clearance record for PR #173 must not be inferred from the Builder correction record alone.
6. PR #178 governance remains proposed, open, draft and unmerged. Its rules are used here as project working constraints, not represented as binding accepted governance.
7. Gate A remains NOT CLEARED. The outstanding controller-internal compensation failure injection and genuine independent re-review must not be silently treated as closed.
8. The main branch's event journal and replay, structured memory, perception/representation, world/causal models, attention, goals, planning, action assessment, prediction feedback, evolution and metacognition are valuable foundations. They are not collectively proof of a specification-complete Brain.
9. The Rust prototype must not become a competing cognitive-state authority. TypeScript interfaces and engineering-agent orchestration must not be counted as a second functioning Brain.
10. Historical branch/document preservation work remains open separately; it does not justify restarting the technical inventory.

---

## 2. Whole-Brain architecture and state ownership

PR #174 defines BM-01 through BM-12 as logical responsibilities within one coherent cognitive system. It explicitly rejects a one-class-per-mechanism mandate and requires a single coherent cognitive authority.

The current main C++ `Brain` is the strongest candidate for the central state-owning runtime in the inspected tree. It owns or coordinates memory, beliefs, predictions, causal and association models, attention, goals, intent, strategy, planning, decision, capability and evolution-related components. This is evidence of a central C++ authority, not proof that all mechanisms have complete or unambiguous state ownership.

The `CognitiveCycle` and `CognitiveRuntime` sit above this state owner:
- `CognitiveCycle::run` assembles an observation context, retrieves memories, reads beliefs/causal links, invokes reasoning, creates predictions, selects a goal, plans, decides, assesses actions and reflects.
- `CognitiveRuntime` queues work, executes cycles and projects cycle results into a `CognitiveWorkspace`.
- `CognitiveWorkspaceStore` provides mutex-protected snapshot/replace/clear semantics.

A workspace snapshot is not an independent authority. It is a projection of cycle results. The map must preserve that distinction.

### 2.1 Preliminary ownership map

| Authority / component | State or responsibility observed on main | Boundary that must remain explicit |
|---|---|---|
| `Brain` | Central event-backed cognitive state and access to major cognitive models | Must remain the single coherent Brain authority; do not create parallel Brain state in Rust, TypeScript or orchestration |
| `Memory` | Durable event continuity journal, memory metadata, tier/salience/confidence and ranked recall | Retained experience is not automatically an accepted belief or semantic knowledge |
| `Brain::beliefs_` / `WorldModel` | Current key/value beliefs; facts and relations with disputed markers | Belief acceptance/revision and competing-claim lineage are incomplete |
| `CausalModel` / prediction map | Associations/causal links, simulation and keyed prediction lifecycle | Causal hypothesis, prediction, observed outcome and accepted causal knowledge must remain distinct |
| `AttentionModel` / `BrainState` | Attention signal and compact state metrics | Active context, interruption/resumption and multi-context ownership are not demonstrated by a scalar signal |
| `GoalModel` / intent / planner / decision | Goal lifecycle, intent selection, plan construction and action ranking | Candidate-goal formation and evidence lineage are missing on main; decision is not authorization |
| `LearningLoop` / adaptation / evolution | Numeric prediction adaptation and proposal/adoption path | Not a general cross-mechanism developmental process |
| `ReflectionModel` / `SelfModel` / `SelfStateModel` | Aggregate uncertainty, prediction accuracy, coherence and capability-health state | Reflection is not a full evidence-aware corrective control loop |
| `ReasoningEngine` | Bounded inference over beliefs and causal links | BM-12 state/lineage and downstream consumer contract are not satisfied |
| `CognitiveRuntime` / `CognitiveWorkspace` | Work queue, cycle execution and projected context | Scheduling/workspace must not silently become a second owner of beliefs/goals/memory |
| Action/governance boundary | Main cycle produces action assessments; execution/authorization is outside this cycle | Brain intent/decision must not imply permission or verified external consequence |

### 2.2 Cross-mechanism loop required by the specification

The relevant recurrent interactions are:

1. **Evidence and interpretation:** BM-01 preserves experience and provenance; BM-02 interprets; BM-03 supplies memory; BM-04 evaluates claims; BM-10 detects omissions/conflicts; BM-11 marks dependent state stale.
2. **Prediction and delayed outcome:** BM-03/BM-04 provide context and premises; BM-05 predicts; later BM-01 evidence resolves only when attribution and resolution conditions are met; BM-09 evaluates changes; BM-11 maintains dependency freshness.
3. **Memory-supported reasoning:** BM-03 retrieves candidate evidence; BM-02 interprets it in context; BM-04/BM-05 provide qualified claims/hypotheses; BM-12 reasons with explicit premises and assumptions; the relevant owner evaluates conclusions; BM-10 challenges overreach; BM-11 invalidates conclusions when dependencies change.
4. **Candidate-goal formation:** experience, representation, memory, beliefs, prediction and appraisal inform BM-08 candidate goals; BM-08 evaluates and revises them; governance remains external to Brain authority.
5. **Learning and development:** evidence is attributed to a mechanism; BM-09 forms/evaluates a candidate; activation is controlled; persistence and lineage are recorded; later behavior is evaluated in acquisition and relevant novel contexts.
6. **Coordination and recovery:** BM-11 tracks dependencies, concurrency, interruption, partial completion and recovery. It does not become a competing reasoning or belief authority.

Main currently contains fragments of these paths. It does not yet demonstrate the complete loop as specified.

---

## 3. BM-01 through BM-12 source-to-capability map

### BM-01 — Experience intake and provenance

**Specification responsibility:** Preserve what was received, where it came from, temporal/contextual conditions, integrity and derivation lineage before interpretation or learning changes it.

**Main source evidence**
- `core/cpp/include/jarvis/core/event.hpp` — blob `a31db633e8181378fcec0a20c5958c0065d430ee`
- `core/cpp/src/brain.cpp` — blob `e9f3758fcc9c0e89b7280ce376db9033d547682d`
- `core/cpp/src/memory.cpp` — blob `ba72a897306d4761246d0deab2fbab37c49d372f`

**Observed path:** `Brain::observe(Event)` timestamps an event when its timestamp is zero, appends it to Memory, receives a sequence, increments event/cycle counters, replays the event into cognitive state and synchronizes self-state. The event carries sequence, timestamp, source, kind and scalar attributes.

**Consumers:** BM-02 representation/perception; BM-03 Memory; BM-04 belief/world state; BM-05 causal/prediction paths; BM-06 attention; BM-09 learning feedback.

**Persistence/recovery:** Event records are journaled and replayed. Memory loading recovers a valid prefix and truncates bytes beyond the valid end. The journal is useful continuity infrastructure, but the inspected envelope does not enforce first-class separate receipt/event times, modality, scope, epistemic status, provenance chain, reliability dimensions or derivation lineage.

**Gaps**
- Source identity is a string; provenance independence and source authentication are not established.
- Event time versus acquisition/receipt time is not represented as separate typed semantics in the event envelope.
- Raw acquisition, interpreted representation, internal model output and external observation are not strongly distinguished by the core event contract.
- A journal append is not semantic acceptance, nor tamper-evident/rollback-resistant trust.
- Malformed, delayed, reordered, duplicate and partial evidence semantics are not established across all consumers.

**Donor comparison:** PR #97 has event/action/prediction outcome persistence paths, but the Phase 1 donor matrix does not establish that its event envelope fully satisfies the accepted evidence contract. Do not infer that richer action feedback solves general provenance.

**Disposition:** **Reuse** event sequencing and journal/replay as infrastructure; **adapt** evidence semantics and provenance contracts. Preserve the trust-boundary requirements from the existing PR #160 work as a required input.

**Required integration proof:** One experience must retain immutable acquisition lineage through interpretation, memory retrieval, belief revision, reasoning, prediction and learning; restart/replay must preserve those distinctions.

### BM-02 — Representation and interpretation

**Specification responsibility:** Produce one or more interpretations from experience while retaining ambiguity, alternatives, confidence meaning and evidence lineage.

**Main source evidence**
- `core/cpp/include/jarvis/core/representation.hpp` and `core/cpp/src/representation.cpp` — implementation blob `0e53bfaa0c1114cb7390d9f7ce577c87d6bc6169`
- `core/cpp/src/perception_pipeline.cpp` — blob `ab9a745bb68e416d4e32c9d0c26a2d0b2016ab17`
- `core/cpp/include/jarvis/core/perception_pipeline.hpp`
- `core/cpp/src/cognitive_cycle.cpp` — blob `3df14c552f2048b0394dc362f7ee7a654a93fb32`

**Observed path:** The representation engine normalizes event attributes into semantic nodes/relations and assigns modality using a finite source/kind string mapping. The perception pipeline supports registered providers, support checks, validation, exception isolation and strongest-confidence selection, then falls back to normalized event representation.

**Consumers:** World/knowledge models and cognitive context; the current cycle's observed code path is not a demonstrated general semantic interpretation pipeline feeding every downstream mechanism.

**Gaps**
- Exact source/kind strings (voice/speech, vision/camera, audio/microphone, sensor/system, text/command/message) act as modality fallback conventions. They are adapters, not acquired understanding.
- The strongest-confidence provider selection does not preserve multiple plausible interpretations or resolve disagreement.
- Attribute normalization is not semantic grounding, entity identity, contextual language understanding or operator-intent understanding.
- Confidence is not source reliability or belief confidence.
- Contextual language/operator-intent grounding remains a separate BM-02 requirement gap. It is not PR #173 F-02, which concerns experience-acquired candidate-goal formation.

**Donor comparison:** PR #97's developmental context extraction uses observation kind/source and representation features/values; its fixed tokenization and context hierarchy are engineered inductive biases. It does not by itself establish general contextual language/operator-intent grounding.

**Disposition:** **Reuse** provider capability and representation boundaries; **adapt** ambiguity, grounding, source/context and alternative-interpretation semantics. Keep contextual grounding open as a distinct BM-02 gap.

**Required integration proof:** Ambiguous input yields competing interpretations; contextual evidence and memory change their relative support; operator intent is grounded from context rather than a fixed phrase/source lookup; raw evidence remains unchanged.

### BM-03 — Continuity and memory

**Specification responsibility:** Retain experience, retrieve by relevance, support episodic/semantic/procedural/associative functions, track use, consolidate and forget without losing required lineage.

**Main source evidence**
- `core/cpp/include/jarvis/core/memory.hpp` — blob `f3662038237246efa51155f940d77564f144d6d9`
- `core/cpp/src/memory.cpp` — blob `ba72a897306d4761246d0deab2fbab37c49d372f`
- `core/cpp/src/cognitive_cycle.cpp` — blob `3df14c552f2048b0394dc362f7ee7a654a93fb32`

**Observed path:** Memory stores event continuity and metadata with Working/Episodic/Semantic/Procedural tier labels, salience and confidence. It supports append, load, recent/history access, ranked recall, promotion and working-memory eviction. Ranked recall uses exact matches, attribute overlap, relative record position, salience and confidence. `CognitiveCycle::run` retrieves ranked memories using observation attributes.

**Consumers:** Current cycle context receives memories. The inspected reasoning invocation does not consume them. Other uses in the source must be distinguished from the specific BM-12 integration requirement; mere workspace/context availability is not downstream use.

**Gaps**
- Current recall is structured attribute-overlap retrieval, not general semantic/conceptual retrieval across different wording, modalities or abstraction levels.
- Tier labels do not prove distinct semantic/procedural memory functions.
- Retrieval usefulness/irrelevance is not tracked as a complete evaluated lifecycle.
- Consolidation lineage and evidence behind promotion are incomplete.
- Memory can be stored without being used by reasoning or decision.
- Missing retrieval is not evidence that an experience never occurred; this semantic distinction needs to be preserved at all consumers.

**Donor comparison:** PR #97 includes event journal/reconstruction and learning persistence paths. Those are useful continuity donors, not proof of semantic retrieval or memory-supported inference. The donor matrix explicitly states event-based persistence is not synonymous with trusted memory.

**Disposition:** **Reuse** journal, replay and metadata foundation; **adapt** retrieval and consolidation semantics; **defer** claims of semantic/procedural generality until demonstrated.

**Required integration proof:** A relevant memory changes a later inference/decision; an irrelevant memory does not; the effect and provenance are inspectable; working-context eviction does not erase durable history; replay preserves retrieval and lineage.

### BM-04 — Belief and world-state management

**Specification responsibility:** Maintain evidence-qualified, scoped, revisable claims with support, contradiction, versioning and dependent-state invalidation.

**Main source evidence**
- `core/cpp/src/brain.cpp` — blob `e9f3758fcc9c0e89b7280ce376db9033d547682d`
- `core/cpp/src/world_model.cpp` — blob `5b68e8fe37d99732557237e347ae02234a3de172`
- `core/cpp/src/knowledge.cpp` — blob `25ecf822e6132f576266c1f86a964a227c7fb75f`

**Observed path:** Main replay updates a map of beliefs keyed by attribute name. Matching values increase confidence; differing values replace the current scalar and reduce confidence. WorldModel stores facts/relations and marks conflicts disputed, retaining a disputed fact list; a higher-confidence incoming fact can replace the current fact. KnowledgeModel maintains a running average reliability keyed by source string.

**Consumers:** BM-05 causal/prediction, BM-08 planning/decision, BM-10 reflection/monitoring and BM-12 reasoning receive beliefs in some form. The inspected model does not preserve enough lineage for the accepted cross-mechanism contract.

**Gaps**
- One current scalar per key is not a competing-claim model.
- A conflicting value may overwrite the prior belief even while confidence falls.
- The inspected belief record does not encode source/evidence lineage, scope, validity interval, revision reason or alternative claims.
- Source reliability keyed by string and averaged does not establish source identity, independence, freshness or provenance.
- Disputed flags are not a complete adjudication lifecycle. Main's inspected CognitiveCycle does not consume WorldModel disputed facts/relations; the donor cycle does, but only merges a disputed marker into belief records and raises uncertainty, not a complete alternative-claim reasoning contract.
- Dependent predictions/plans/conclusions are not shown to be invalidated atomically or marked stale when a belief changes.

**Donor comparison:** PR #148 is the identified donor line for competing alternatives, evidence accumulation, stronger post-conflict evidence and replay-order validation. PR #97 retains the same WorldModel source but its CognitiveCycle additionally reads disputed facts/relations, marks corresponding beliefs disputed and incorporates world-dispute pressure into planning uncertainty. That is a consumer integration improvement, not full competing-claim adjudication or authoritative world-state reconciliation. PR #148 remains unmerged; exact PR #148 head and compatibility must be rechecked before port decisions.

**Disposition:** **Reuse** current belief/world structures as a base; **adapt** evidence lineage, alternatives, scope, revision and dependency invalidation. Do not use last-write-wins or a generic confidence formula as final epistemic semantics.

**Required integration proof:** Contradictory evidence preserves both claims; support/contradiction changes qualified belief status; downstream predictions/plans/reasoning are marked stale; restart preserves the complete revision history.

### BM-05 — Association, causal modelling and prediction

**Specification responsibility:** Discover candidate relationships, distinguish association from causality, create scoped predictions and resolve them against attributable outcomes.

**Main source evidence**
- `core/cpp/src/association_model.cpp` — blob `b378d4237527dfbb4c65f43545f7f0fc7c42669b`
- `core/cpp/src/causal_model.cpp` — blob `f873d0a6e7fa0676bb88bf7a1f66436bc88a3c0d`
- `core/cpp/src/brain.cpp` — blob `e9f3758fcc9c0e89b7280ce376db9033d547682d`
- `core/cpp/src/cognitive_cycle.cpp` — blob `3df14c552f2048b0394dc362f7ee7a654a93fb32`

**Observed path:** Association/CausalModel observe before/after belief snapshots. CausalModel forms links when changed beliefs co-occur with other current values; simulation traverses sufficiently strong links with confidence attenuated by depth. Brain persists predictions as events and resolves by key. Numeric outcomes use bounded absolute error; non-numeric values use equality. CognitiveCycle simulates current beliefs and creates cycle-scoped prediction keys.

**Consumers:** Planning receives predicted value/risk context; prediction resolution feeds adaptation; BM-09 is expected to evaluate learning; BM-04 should receive relevant outcome evidence.

**Gaps**
- Co-state change is not sufficient causal evidence; confounding, temporal precedence, interventions, alternative causes and counterexamples are not demonstrated.
- Association and causal strength require separate epistemic semantics.
- Prediction records on main have limited scope/assumption/horizon/resolution semantics.
- Generic absolute difference/equality is not domain-appropriate for all predictions.
- Caller-supplied scalar outcome does not by itself establish independent external verification or attribution.
- A resolved prediction and numeric adaptation do not prove improved held-out predictive performance.

**Donor comparison:** PR #97 adds contextual prediction and prediction feedback. Its pathway uses contextual concepts/candidates and numeric adaptation, but the donor matrix explicitly limits the claim and requires held-out metrics. PR #151's controlled compositional transfer is separate evidence and must not be conflated with PR #97.

**Disposition:** **Reuse** keyed prediction persistence and simulation as a narrow starting point; **adapt** causal evidence, prediction scope, resolution and attribution. Preserve the distinction between prediction feedback and broad learning.

**Required integration proof:** Two similar predictions resolve independently; delayed/out-of-order outcomes resolve only the matching prediction; action cancellation/provider failure cannot count as verified external consequence; counterexamples weaken the relevant causal hypothesis; held-out metrics establish whether prediction improved.

### BM-06 — Attention and active context

**Specification responsibility:** Allocate limited processing capacity among experiences, memories, predictions, goals and internal conditions; manage active contexts, interruption and resumption.

**Main source evidence**
- `core/cpp/src/attention.cpp` — blob `58f734dbe9772675d687752026231297f289e770`
- `core/cpp/include/jarvis/core/cognitive_workspace.hpp` — blob `b015d44e332ea2511d29e607495714d0b982d44e`
- `core/cpp/src/cognitive_workspace.cpp` — blob `fbd2321d9cd1c98217389beced292654e33a906e`
- `core/cpp/src/cognitive_runtime.cpp` — blob `1a1383cedc42e357dc9efce117328b8d55e30bca`

**Observed path:** Attention scoring combines novelty, uncertainty (derived from strongest belief confidence) and optional urgency. The default policy initializes equal weights; reinforce/suppress adjusts these weights. CognitiveWorkspace holds a projection of observation, memories, beliefs, causal links, predictions, reasoning, goals, plan, decisions, action assessments, intent, strategy and reflection. Runtime queues and prioritizes cycle inputs, runs work and replaces workspace snapshots.

**Consumers:** Attention affects state and may feed strategy/planning context; runtime uses trigger priority for scheduling. Workspace exposes a cycle result to callers.

**Gaps**
- Attention scoring does not directly include goal relevance, affective appraisal, consequence, resource contention or full task context.
- Equal initial weights are a bootstrap policy, not acquired attention.
- A single event salience score is not the full active-context ownership/lifecycle.
- Workspace is a snapshot/projection; it does not establish multiple context isolation, dependency freshness, interruption/resumption guarantees or authoritative state.
- Scheduling priority in CognitiveRuntime must not be conflated with cognitive attention.

**Donor comparison:** PR #97 includes attention learning and affective consumers, but its learned weighting/context assumptions must be inspected with the same scrutiny as main. It does not automatically close multi-context and lifecycle requirements.

**Disposition:** **Reuse** AttentionModel and workspace/runtime scaffolding; **adapt** contextual relevance, ownership, concurrency, interruption/resumption and starvation detection. Keep runtime scheduling and cognitive attention as distinct concepts.

**Required integration proof:** Competing contexts are prioritized; context can be suspended/resumed with evidence, goals, permissions and freshness intact; attention can be redirected by new evidence without erasing durable state; starvation and oscillation are observable.

### BM-07 — Affective appraisal and valuation

**Specification responsibility:** Context-sensitive appraisal of significance and internal conditions; modulate attention, memory, learning, goal evaluation and decision without fixed stimulus-to-emotion or emotion-to-action mappings.

**Main source evidence**
- Phase 1 source audit identifies affect-related and developmental API definitions in `core/cpp/src/brain_restored_api.cpp` — blob `618deb6976eed951eae02b7f0da741e6d730bb0c`.
- Main `brain.hpp` inspected at blob `8268ef84e0b361ead536724ba7761904b30ee58f` does not show corresponding affective members in its inspected private member inventory.
- `core/cpp/src/brain.cpp` self-state synchronization is aggregate and derives workload/uncertainty/health from counters, threat, attention, novelty and capability health.

**Observed path:** The main baseline does have threat, attention and self-state signals, and an affect-related restored API source file. The Phase 1 audit identified a source-level integration discrepancy: API definitions refer to affective/developmental members not present in the inspected Brain declaration. This is not a confirmed build failure; compilation-unit membership and declaration integration were not verified by build.

**Consumers:** Main threat/attention influence planning and decisions. A complete contextual appraisal state with evidence lineage and downstream consumers is not established on main.

**Gaps**
- Main does not establish a coherent, compiled, authoritative affective-state owner.
- Aggregate self-state is not affective appraisal.
- Context-dependent significance, appraisal evidence, revision and multi-dimensional state are not demonstrated.
- Affective influence on memory, learning, goals and decisions is not established as a coherent integrated path on main.
- SYS-05 autonomic regulation and SYS-08 runtime substrate ownership must remain external; BM-07 owns only cognitive estimates/appraisal.

**Donor comparison:** PR #97 contains continuous affective state, appraisal adaptation, affect-aware planning/decision and action-outcome evidence weighting. The Phase 1 donor matrix records actual consumers and persistence, but also classifies appraisal equations and context encoding as engineered priors. PR #97 is a donor, not a merged main capability. Its fixed equations, feature assumptions, evidence attribution and failure/replay behavior require full compatibility review.

**Disposition:** **Do not count BM-07 as implemented on main.** **Evaluate PR #97 selectively** as the strongest identified donor path; preserve SYS-05/SYS-08 boundaries and reject fixed stimulus/emotion/action mappings as a general cognitive policy.

**Required integration proof:** Same event, different goals/history/internal conditions, yields contextually different appraisals; appraisal modulates but does not command cognition; evidence can revise appraisal; restart preserves state/lineage; no competing authority with SYS-05/SYS-08.

### BM-08 — Goals, intent, planning and decision

**Specification responsibility:** Process supplied goals and form experience-informed candidate goals; evaluate feasibility, conflicts, consequences, resources and constraints; produce plans/decisions without authorizing execution.

**Main source evidence**
- `core/cpp/src/goals.cpp` — blob `778a829de8314e83b095af2f2c2a6b83baa769f4`
- `core/cpp/src/intent.cpp` — blob `4283a4255284c51257df6bad12734782f2a6cde9`
- `core/cpp/src/strategy.cpp` — blob `5406a341cd4b3f42e16166f6122a0cb580aee298`
- `core/cpp/src/planning.cpp` — blob `aab022b7cbc06f380413395757d590b56a1f3a20`
- `core/cpp/src/decision.cpp` — blob `6a49e0f1f80c3c6b0955ddf98182fc6611c0e84c`
- `core/cpp/src/cognitive_cycle.cpp` — blob `3df14c552f2048b0394dc362f7ee7a654a93fb32`

**Observed path:** GoalModel creates/activates/updates/completes/abandons goals and checks prerequisites/deadlines. CognitiveCycle uses an explicit supplied goal ID if present; otherwise it selects the first eligible goal. IntentModel scores existing eligible goals using priority, remaining progress and deadline. StrategyModel translates intent/attention/threat/uncertainty/resource budget into PlanningContext. Planner ranks actions and builds a plan; DecisionEngine ranks candidate actions; ActionModel assesses them against constraints. The cycle explicitly does not authorize or execute actions.

**Consumers:** BM-06 attention/active context should consume goal context; BM-05 predictions inform planning; BM-07 appraisal is missing as a coherent main consumer; external governance and execution layers remain separate.

**Gaps**
- Main accepts already-created goals; it does not demonstrate candidate-goal formation from experience.
- Priority is supplied/updated; no learned priority formation is demonstrated.
- Default first-eligible selection is a deterministic fallback, not autonomous goal evaluation.
- PR #173 F-02 concerns experience-acquired candidate-goal formation, not contextual language/operator-intent grounding. The latter remains a separate BM-02 gap.
- Decision/plan outputs need explicit dependency freshness and re-evaluation when beliefs/predictions/goals change.
- Action assessment is not execution authorization or verified consequence.

**Donor comparison:** PR #97 adds affect-aware planning and developmental context strategy adjustment. This can inform downstream modulation but does not by itself solve experience-acquired candidate-goal formation (PR #173 F-02). Contextual language/operator-intent grounding remains a separate BM-02 gap. The PR #97 action execution path is a separate donor capability described under BM-09/BM-11 interactions.

**Disposition:** **Reuse** goal lifecycle, planner, decision and action-assessment foundations; **adapt** candidate-goal origin/evaluation (PR #173 F-02), contextual grounding, dependency freshness and interaction with appraisal/reasoning. Preserve external authorization boundary.

**Required integration proof:** Supplied goals remain distinguished from internally formed candidates; novel experience can produce an evidence-backed candidate without fixed triggers; defeated premises cause revision/abandonment; governance denial prevents execution while preserving intent and denial separately.

### BM-09 — Learning and developmental adaptation

**Specification responsibility:** Attribute evidence, form/evaluate candidate changes, activate under controls, persist lineage, monitor effects and recover regressions across cognitive capabilities.

**Main source evidence**
- `core/cpp/src/learning_loop.cpp` — blob `bc9a6aaca38d060667bcdf82f2b1a1f72c5936ba`
- `core/cpp/src/adaptation.cpp` — blob `7e07a491a5b13379a5719882a834ecc2452a54ef`
- `core/cpp/src/brain.cpp` — blob `e9f3758fcc9c0e89b7280ce376db9033d547682d`
- `core/cpp/src/evolution_controller.cpp` and associated evolution modules are present in main; Phase 1 inventory identifies candidate generation/evaluation/adoption/canary/rollback infrastructure.

**Observed path:** Main LearningLoop validates finite feedback, updates numeric adaptation, observes fitness, proposes evolution changes and adopts a matching proposal only if confidence is at least 0.75 and expected gain is positive. AdaptationModel updates per-key numeric estimates and mean absolute error with a running average over values clamped to [0,1]. Brain records events and replays prediction outcomes into adaptation state.

**Consumers:** Adapted estimates and evolution parameters can affect later numeric predictions and selected model parameters. The inspected main path does not demonstrate cross-mechanism learning that revises semantic memory, representations, belief structures, causal hypotheses, goals, reasoning or procedural skills.

**Gaps**
- Narrow numeric prediction adaptation is not the accepted multi-class developmental process.
- Attribution (what exactly the outcome supports) and independent consequence verification are incomplete at this boundary.
- Candidate evaluation across counterexamples, interference, transfer and regression is not established for all cognitive state classes.
- Persistence of every candidate/evaluation/activation and downstream dependency invalidation must be checked per mechanism.
- A numeric metric improving does not prove behavior improved on held-out contexts.
- Gate A's controller-internal compensation failure injection remains open in Phase 1 evidence.

**Donor comparison:** PR #97 adds developmental strategy learning/contextual transfer and stronger action-outcome/prediction feedback. It provides a real donor path where learned contextual evidence changes later planning/decision scores, but uses engineered context features, tokenization, negator sets, numeric magnitude bands, similarity and thresholds. The donor matrix warns that synthetic distributions do not prove arbitrary open-world transfer. PR #151 separately demonstrates bounded synthetic compositional transfer with held-out feature combinations, not broad intelligence.

**Disposition:** **Reuse** evolution safety/evaluation infrastructure and narrow adaptation where justified; **adapt** learning into a cross-mechanism lifecycle. Preserve donor paths as selective candidates. Do not claim generalized learning from parameter updates or synthetic transfer alone.

**Required integration proof:** Evidence attribution; candidate changes; counterexample/regression rejection; persistence/restart; measurable later behavioral effect; held-out relevant transfer; unrelated-context protection; rollback and recovery under partial failure.

### BM-10 — Metacognitive monitoring and control

**Specification responsibility:** Monitor uncertainty, contradiction, calibration, stale dependencies, missing evidence, overload and capability degradation; request and evaluate bounded correction.

**Main source evidence**
- `core/cpp/src/reflection.cpp` — blob `06f34e20f35aad535a2c606b3669b2127ef7a480`
- `core/cpp/src/self_model.cpp` — blob `3c6a375eadd6894a635d2e18023a7079cba97c86`
- `core/cpp/src/brain.cpp` — blob `e9f3758fcc9c0e89b7280ce376db9033d547682d`

**Observed path:** ReflectionModel computes average belief uncertainty, resolved-prediction accuracy and a composite coherence score; it emits generic observations when uncertainty dominates or prediction performance is low. SelfModel tracks capability availability/performance, supports isolate/restore and computes aggregate health. Brain syncs a self-state snapshot from event count, threat, attention, novelty, capability health and active goals.

**Consumers:** CognitiveCycle stores reflection in its result/workspace; self-state uncertainty influences planning/decision context.

**Gaps**
- Reflection is an aggregate report, not an evidence-lineage-aware monitor of actual reasoning steps and assumptions.
- Generic text observations do not themselves trigger targeted retrieval, re-reasoning, belief revision, plan invalidation or corrective evaluation.
- The inspected path does not establish a closed loop from limitation detection → bounded correction → measured correction effect.
- Stale premise/dependency detection is not demonstrated.
- Self-state aggregate values must not be mistaken for authoritative SYS-05 physiological/autonomic state or SYS-08 substrate state.

**Donor comparison:** PR #97 has affective appraisal and action feedback that may provide richer signals, but those are not a replacement for metacognitive monitoring and correction ownership.

**Disposition:** **Reuse** reflection/self-model health signals; **adapt** toward explicit monitoring records, evidence dependencies, corrective requests and evaluation. Do not let BM-10 become an unrestricted writer of other mechanisms' state.

**Required integration proof:** A known overreach/contradiction is detected with evidence; targeted corrective work occurs; affected conclusion/plan is revised; the system measures whether the correction helped; the prior state and correction lineage remain inspectable.

### BM-11 — Integrated coordination and continuity control

**Specification responsibility:** Coordinate mechanism interactions, dependencies, concurrency, interruption and recovery while maintaining one coherent cognitive state.

**Main source evidence**
- `core/cpp/include/jarvis/core/cognitive_cycle.hpp`
- `core/cpp/src/cognitive_cycle.cpp` — blob `3df14c552f2048b0394dc362f7ee7a654a93fb32`
- `core/cpp/src/cognitive_runtime.cpp` — blob `1a1383cedc42e357dc9efce117328b8d55e30bca`
- `core/cpp/include/jarvis/core/cognitive_workspace.hpp` — blob `b015d44e332ea2511d29e607495714d0b982d44e`
- `core/cpp/src/cognitive_workspace.cpp` — blob `fbd2321d9cd1c98217389beced292654e33a906e`
- `core/cpp/src/brain.cpp` — blob `e9f3758fcc9c0e89b7280ce376db9033d547682d`

**Observed path:** CognitiveCycle runs a bounded sequence from observation through recall, beliefs/causal links, reasoning, predictions, goal selection, planning, decision, action assessment and reflection. CognitiveRuntime provides a prioritized queue, worker thread, result queue, metrics and workspace projection. Workspace snapshots are mutex-protected.

**Gaps**
- The current cycle is mostly a fixed sequence, while PR #174 requires selective, recurrent, delayed and interruptible processing. A single pass is not a complete coordination model.
- The cycle retrieves memories but fails to pass them to reasoning.
- Reasoning results are stored in context but not consumed to qualify beliefs, revise predictions, evaluate goals or influence planning/decision.
- Workspace replace/snapshot does not by itself provide dependency versioning, stale-state detection, multi-context isolation, durable checkpoints or partial-operation recovery.
- Queue priority is scheduling policy, not the full BM-06 cognitive attention process.
- Cross-mechanism transactions and concurrent changes to authoritative state are not demonstrated by a mutex-protected workspace alone.
- The current cycle does not own a complete action → verified consequence → learning loop; it stops at action assessment. PR #97 contains a separate Brain-owned action execution/consequence donor path.

**Donor comparison:** PR #97 adds Brain-owned action execution, consequence observation and feedback. The donor matrix records that execution and verification are separated and that observed consequence feeds the event/prediction path. It also records unresolved rollback/partial-side-effect semantics. PR #176 contains D1/D2 corrections, but its merge relationship and controller failure-injection status must be checked before adoption.

**Disposition:** **Reuse** central Brain authority, CognitiveCycle, runtime queue and workspace projection as scaffolding; **adapt** into explicit dependency-aware recurrent coordination and coherent recovery. Selectively evaluate the donor action loop; do not merge it wholesale.

**Required integration proof:** A belief change invalidates dependent predictions/plans/conclusions; interruption/resumption retains constraints and lineage; partial persistence failure does not claim completion; concurrent updates reconcile; action execution and verified consequence remain distinct and feed learning only with valid evidence.

### BM-12 — General reasoning and inference

**Specification responsibility:** Derive, compare, evaluate and revise provisional conclusions from evidence-bearing premises and explicit assumptions while preserving complete inference lineage. BM-04 owns belief commitment; BM-05 owns causal/prediction lifecycle; BM-08 owns goal/plan/decision; BM-12 is not a second Brain authority.

**Main source evidence**
- `core/cpp/include/jarvis/core/reasoning.hpp` — blob `5c6f82797d4f5052ad5d71a25624de192a2c87d9`
- `core/cpp/src/reasoning.cpp` — blob `feec78b2e8a1f2b0b58733fd509e4e5a750258fc`
- `core/cpp/src/cognitive_cycle.cpp` — blob `3df14c552f2048b0394dc362f7ee7a654a93fb32`

**Observed path:** ReasoningProblem accepts belief premises, causal links and a maximum step count. ReasoningResult contains kind, valid flag, one confidence, free-form explanation and derived beliefs. ReasoningEngine checks scalar consistency and performs bounded traversal over causal links encoded as key/value strings. Empty premises can return `valid=true` with zero confidence and a no-premises explanation.

**Critical integration finding:** CognitiveCycle retrieves ranked memories into `result.context.memories`, then builds ReasoningProblem from `result.context.beliefs` and `result.context.causal_links` only. Memories are not passed to the reasoning engine. The result is stored in cycle context but is not used in the inspected remainder to revise beliefs, change prediction premises, evaluate goals or influence planning/decision. Downstream work is not gated on reasoning validity.

**Gaps**
- No explicit premise identity/provenance/scope/temporal status, assumptions, alternatives, counterexamples or conclusion dependencies in the interface.
- No evidence that a retrieved memory can materially change an inference.
- No general deduction/explanation/induction/analogy breadth demonstrated by bounded causal-link traversal.
- Empty premise set's `valid=true` is not a substantive supported inference.
- Contradiction handling is scalar consistency checking, not a preserved alternative/argument lifecycle.
- Derived beliefs lack the required premise-to-conclusion lineage.
- No downstream consumer in the inspected cycle gives reasoning outputs operational effect.
- Downstream reasoning consumption is PR #174 source-audit finding AUD-12 / Phase 2 IF-03. It is separate from PR #173 F-03, which concerns the SYS-08 substrate boundary.

**Donor comparison:** PR #97 changes selected cognitive/affective pathways but is not established as a complete BM-12 general reasoning donor. The Phase 1 donor matrix does not identify a donor that closes memory-supported general inference and downstream consumption.

**Disposition:** **Retain** the narrow ReasoningEngine as a prototype if useful; **do not count BM-12 as implemented**. Resolve IF-03/AUD-12 and deepen the separate BM-02 contextual-grounding gap before implementation. Track PR #173 F-02 (candidate goals) and F-03 (SYS-08) under their own responsibilities. Do not add another reasoning engine that becomes a competing state authority.

**Required integration proof:** All accepted PR #174 scenarios 27–34; retrieved relevant memory changes inference with provenance; irrelevant memory does not; contradictions and alternatives remain explicit; defeated assumptions invalidate dependent conclusions; conclusions are evaluated by their owning mechanisms; downstream planning/decision uses only qualified, fresh conclusions.

---

## 4. Cross-mechanism integration findings

The following are system-level findings, not isolated module defects.

### IF-01 — Evidence lineage is thinner than the specification contract

The core event envelope and belief records do not consistently preserve source, scope, epistemic status, uncertainty dimensions, temporal applicability and derivation lineage. Memory replay provides continuity, but the provenance semantics needed by reasoning, belief revision, prediction resolution and learning are not yet uniform.

**Impact:** BM-01, BM-02, BM-03, BM-04, BM-05, BM-09, BM-10 and BM-12.  
**Consequence:** A later mechanism may receive a scalar value without enough information to judge what it means, where it applies, or whether it is independent/verified.  
**Disposition:** Resolve the shared evidence contract before selecting concrete schemas or porting donor paths.

### IF-02 — Memory is retrieved but not integrated into reasoning

The current cycle retrieves memory, but the ReasoningProblem receives only beliefs and causal links.

**Impact:** BM-03, BM-06, BM-11 and BM-12.  
**Consequence:** Memory availability is being mistaken for memory-supported cognition if only the workspace/context is inspected.  
**Disposition:** Close the memory-to-reasoning integration gap by verifying end-to-end effect, not merely passing a memory vector to an API. This is IF-02, not PR #173 F-03.

### IF-03 — Reasoning output is not an operative input to downstream cognition

The current cycle stores reasoning output but does not consume it in belief revision, prediction premise formation, goal evaluation, planning or decision.

**Impact:** BM-04, BM-05, BM-08, BM-10, BM-11 and BM-12.  
**Consequence:** Reasoning is a side calculation rather than an integrated inference capability.  
**Disposition:** Resolve downstream ownership and freshness contracts before implementation.

### IF-04 — Belief revision is not yet evidence-sensitive enough

Main's key-to-scalar map and generic same/different update can overwrite prior claims. WorldModel's disputed flags are useful but do not establish full competing-hypothesis adjudication.

**Impact:** BM-01, BM-02, BM-03, BM-04, BM-05, BM-09, BM-10 and BM-12.  
**Disposition:** Compare PR #148's evidence accumulation and competing alternatives at an exact revision; do not transplant without event/replay compatibility analysis.

### IF-05 — Main's causal learner confuses co-state change with causal evidence

CausalModel observes before/after belief snapshots and forms links from changed values and other current values. The inspected code does not establish confounder control, intervention semantics or counterexample management.

**Impact:** BM-04, BM-05, BM-09 and BM-12.  
**Disposition:** Preserve candidate associations as hypotheses; require causal evidence criteria and held-out intervention/counterexample evaluation.

### IF-06 — Candidate-goal formation is absent from the inspected main path

Main processes goals that already exist and selects one. It does not form an experience-acquired candidate goal with evidence lineage.

**Impact:** BM-02, BM-03, BM-04, BM-05, BM-07, BM-08, BM-09 and BM-12.  
**Disposition:** Separate supplied goals, internally proposed candidate goals, subgoals and external governance constraints. No fixed event-to-goal trigger.

### IF-07 — Affective state is donor-backed, not integrated main capability

Main has threat/attention/self-state signals and an affect-related restored source file, but Phase 1 identified a declaration/member integration discrepancy. PR #97 has richer affective state and downstream planning/decision consumers, but is unmerged and contains engineered appraisal priors.

**Impact:** BM-06, BM-07, BM-08, BM-09, BM-10 and BM-11.  
**Disposition:** Inspect donor state ownership, update/decay, persistence/replay, context dependence, consumers and fixed assumptions before selecting any part.

### IF-08 — The current cycle is a single-pass coordinator, not the full recurrent control system

CognitiveCycle provides a valuable integration skeleton but currently executes a mostly linear bounded pass and does not re-open earlier mechanisms when premises, beliefs or context change.

**Impact:** BM-01 through BM-12, especially BM-06, BM-10 and BM-11.  
**Disposition:** Map recurrent dependency transitions, invalidation, interruption, asynchronous completion and recovery. Do not assume a more elaborate class graph solves this.

### IF-09 — Action/consequence loop differs between main and donor

Main CognitiveCycle ends at action assessment and explicitly leaves authorization/execution outside. PR #97 adds a Brain-owned action execution/consequence path with authorization, verification, optional rollback and observed consequence. The donor distinguishes execution result from verified consequence, but partial-side-effect/rollback failure semantics remain a review concern.

**Impact:** BM-01, BM-05, BM-08, BM-09, BM-10 and BM-11.  
**Disposition:** Preserve the security/governance boundary. Evaluate the donor path selectively after exact PR #176 corrections, controller failure-injection evidence and compatibility are rechecked.

### IF-10 — Persistence is stronger than transient state but weaker than complete cognitive continuity

Event replay reconstructs many state changes. It does not automatically prove that derived state, dependencies, memory retrieval history, candidate learning, multi-context work, and partial transactions all recover coherently.

**Impact:** BM-01, BM-03, BM-04, BM-05, BM-08, BM-09, BM-10 and BM-11.  
**Disposition:** Require lifecycle-specific replay, stale-state and partial-failure evidence; preserve history rather than relying on snapshot presence.

### IF-11 — Hardcoded assumptions need classification, not blanket removal

Observed engineered priors include:
- modality fallback from exact source/kind strings;
- attribute-overlap memory retrieval;
- generic belief confidence updates;
- causal-link formation from co-state changes and fixed link thresholds;
- attention's initial equal novelty/uncertainty/urgency weights;
- first-eligible goal fallback and priority/deadline intent scoring;
- numeric adaptation clamped to [0,1], running-average updates and fixed adoption confidence/expected-gain gates;
- reflection's aggregate formula;
- PR #97 developmental context tokenization, hierarchy, negator set, numeric magnitude bands, similarity and thresholds;
- PR #97 affective appraisal equations and feature assumptions.

These are not all equally problematic. Type validation, finite-value checks, authorization, permission boundaries, process isolation, bounded resource use, provenance integrity, state ownership and fail-closed adoption are legitimate engineering/safety constraints. Fixed cognitive conclusions disguised as universal learned behavior are not.

**Disposition:** For each prior, record purpose, evidence basis, scope, whether it is an integrity constraint or a provisional inductive bias, how it can be revised, and the evaluation needed to justify retention.

### IF-12 — Cross-language and subsystem boundaries remain unresolved

C++ is the substantive current Brain. Rust has a small cognition/runtime prototype and must not own competing beliefs/goals/identity. TypeScript contains interfaces but no integrated package/build in the audited tree. Engineering-agent C++ is a separate agent/task coordination subsystem.

**Disposition:** Keep one authoritative cognitive-state owner and establish explicit contracts only after whole-system dataflow and ownership are settled. Do not add language/process topology during this mapping phase.

---

## 5. Donor comparison and preservation decisions

| Donor line | Relevant contribution | Current status | Phase 2 disposition |
|---|---|---|---|
| PR #97, head `c1da222e6c94aeb3f2ad000392c21fe4fc81ab25` | Affective state/appraisal, action execution and consequence feedback, developmental strategy learning, contextual prediction, event persistence/replay, evolution adoption | Open, draft, unmerged; 159 changed files | Selective source candidate only; no wholesale merge |
| PR #148 | Competing belief alternatives, evidence accumulation, source/provenance improvements and replay-order validation (per Phase 1 audit) | Donor; exact live head must be rechecked before any port | Inspect against BM-04/01/09 and main event semantics |
| PR #151 | Bounded synthetic compositional transfer with withheld feature combination, multiple seeds, persistence/restart and source/goal isolation | Donor test evidence; not general intelligence proof | Reuse evaluation design where applicable; record additive learner/fixed-schema limits |
| PR #156 | Integrated donor candidate | Not merged/approved baseline in Phase 1 evidence | Recheck exact head, ancestry and corrections; selective comparison only |
| PR #176 | D1/D2 donor corrections and failure-replay tests | Open/unmerged in Phase 1 evidence; live status must be rechecked | Required input to action/evolution safety review; residual controller failure injection remains open |

### 5.1 PR #97 evidence boundary

The Phase 1 PR #97 traceability matrix covers seven high-impact paths:
- continuous affective-state update/decay;
- affective appraisal adaptation and downstream planning consumption;
- Brain-owned action execution and observed-consequence feedback;
- developmental strategy learning and contextual transfer;
- contextual prediction and prediction feedback;
- event-journal persistence/reconstruction;
- evolution evaluation/adoption control.

It records exact source/test blob identities and CMake target declarations for nine test sources. Those declarations prove only that CMake references the test source at the donor commit. They do not prove compilation or execution at the exact PR #97 head. The matrix is bounded, not a line-by-line audit of all 159 changed paths.

The donor's action feedback and developmental strategy paths are meaningful and should not be discarded. They are also not a reason to ignore fixed context features, goal-context bugs, partial rollback semantics or evidence attribution.

---

## 6. Test, build and verification evidence

### 6.1 What this mapping verified

- PR #174 is open/draft/unmerged at the exact accepted head stated above.
- PR #178 is open/draft/unmerged at head `39fe09dcf13496f5f0005ccf3f00739303e29f88`.
- PR #97 is open/draft/unmerged at exact inspected head `c1da222e6c94aeb3f2ad000392c21fe4fc81ab25`.
- The accepted PR #174 specification and its source-audit package were fetched at the exact accepted revision.
- The main source files listed in this report were fetched at the exact Phase 1 audited main commit, and blob SHAs are recorded where available.
- The full `CognitiveCycle::run` path was inspected; memory retrieval, reasoning invocation, prediction creation, goal selection, planning, decision, action assessment and reflection are visible in that function.
- The current main test CMake file was fetched at the audited main commit. Phase 1 records 45 registered targets and three unregistered test source files.
- The PR #97 changed-file list was retrieved and confirms 159 changed paths. The Phase 1 donor matrix remains the bounded source-level trace for seven pathways.

### 6.2 What was not verified in this phase-start mapping

- No local build or runtime test was run.
- No test source was executed during this mapping.
- No new CI run was initiated.
- No performance, learning, transfer or longitudinal experiment was performed.
- No independent reviewer has reviewed this Phase 2 map.
- No full line-by-line audit of every PR #97 changed file or every later donor was performed.
- No compatibility/ABI/API proof exists for porting donor code into main.
- No runtime integration behavior is certified by this document.

### 6.3 Existing CI evidence must remain exact-commit scoped

Phase 1 recorded earlier CI results for selected PR #151, PR #176 and other donor revisions. They remain evidence only for the exact commits and workflows recorded in Phase 1. They must not be transferred to the current main commit, PR #97 head, PR #156 or this documentation branch.

---

## 7. Preliminary implementation-readiness matrix

This table is an investigation classification, not an authorization decision.

| Mechanism | Main status | Donor status | Highest-impact unresolved requirement | Preliminary disposition |
|---|---|---|---|---|
| BM-01 Experience/provenance | Partial | PR #97 event/action outcome records | Typed provenance, event/receipt time, epistemic and derivation lineage | Reuse journal; adapt contract |
| BM-02 Representation | Partial | PR #97 context features | Multiple interpretations and contextual language/operator-intent grounding (separate BM-02 gap) | Reuse provider boundary; adapt grounding |
| BM-03 Memory | Partial | PR #97 persistence/replay | Semantic/contextual retrieval materially used downstream | Reuse continuity; adapt retrieval |
| BM-04 Belief/world state | Partial | PR #148 evidence alternatives | Competing claims, revision lineage, dependent invalidation | Reuse structures; adapt epistemics |
| BM-05 Association/causality/prediction | Partial | PR #97 contextual prediction | Causal evidence, scoped resolution and attribution | Reuse narrow simulation; adapt |
| BM-06 Attention/context | Partial | PR #97 attention learning/affect consumers | Active-context ownership, multiple contexts, interruption/resumption | Reuse scaffold; adapt |
| BM-07 Affective appraisal | Not demonstrated as integrated main capability | PR #97 substantial donor | State owner integration, context-sensitive evidence and no fixed mapping | Selective donor evaluation |
| BM-08 Goals/intent/planning/decision | Partial | PR #97 affective/developmental planning | Experience-acquired candidate goals (PR #173 F-02); no candidate-generation path demonstrated | Reuse lifecycle/planner; adapt |
| BM-09 Learning/development | Narrow numeric adaptation/evolution | PR #97 strategy/action/prediction feedback; PR #151 bounded transfer | Cross-mechanism candidate lifecycle, held-out behavior, recovery | Reuse safety/evolution; adapt learning |
| BM-10 Metacognition | Aggregate reflection/self-health | No identified complete donor closure | Evidence-aware detection → correction → evaluation loop | Reuse monitoring signals; adapt |
| BM-11 Coordination/continuity | Partial single-pass cycle/runtime/workspace | PR #97 action feedback adds a loop | Recurrent dependencies, stale-state control, interruption and coherent recovery | Reuse coordinator scaffold; adapt |
| BM-12 General reasoning | Narrow bounded causal-link inference | No identified donor closure | Memory-supported inference and downstream use (IF-02/IF-03; PR #174 AUD-12) | Retain prototype; do not count implemented |

---

## 8. Required next Phase 2 investigations

The map is deliberately not closed. The following work is needed before Phase 2 can be declared complete.

### P2-01 — Resolve F-02/F-03 against their originating review artifact

The PR #173 correction record and corrected architecture are now identified. F-02 is experience-acquired candidate-goal formation; F-03 is the SYS-08 computational-substrate boundary. The correction record gives the finding summaries, exact corrected sections and acceptance obligations, but not the full verbatim reviewer prose. Retrieve that original review artifact if verbatim wording is required, and reconcile the independent-clearance/Project Director decision without inferring it from PR #174's separate acceptance.

**Exit evidence:** exact correction-record and architecture revisions; affected BM/SYS responsibilities; source/test impact; explicit status of each correction; independent review status and Project Director decision.

### P2-02 — Complete the 12-mechanism dependency and state-transition graph

Map every material producer/consumer edge, authoritative state owner, event transition, dependency version, stale-state behavior, concurrency boundary and recovery checkpoint. Include recurrent cycles and interruption paths. Identify where current main's single-pass cycle is merely a projection.

**Exit evidence:** traceable graph and edge ledger grounded in exact source paths/functions/commits, plus unresolved edges.

### P2-03 — Expand donor mapping beyond the seven PR #97 pathways

Inspect the remaining high-impact changed files in PR #97 and the later PR #148–#156 line. Reconcile branch ancestry and exact heads. Do not repeat Phase 1; deepen its bounded matrix with BM requirement, main counterpart, donor function, dataflow, tests, failure semantics and hardcoding classification.

**Exit evidence:** donor-by-requirement matrix, exact blob SHAs, compatibility conflicts, evidence quality and selective port dispositions.

### P2-04 — Cross-mechanism learning evidence map

For every learning class in BM-09, identify:
- source evidence and attribution;
- candidate state and owner;
- evaluation and counterexample path;
- activation and rollback;
- persistence/replay;
- later behavioral consumer;
- held-out/generalization evidence;
- fixed assumptions and limitations.

**Exit evidence:** an evidence graph distinguishing observational learning from action-outcome learning, and separating numeric adaptation from structural/cognitive development.

### P2-05 — Failure/recovery and continuity integration map

Trace append failure, replay truncation, metadata mismatch, partial belief/goal changes, prediction resolution, candidate adoption, action rollback, interruption, concurrent updates and stale dependent state. Tie each claim to an actual test source and exact CI run, or mark it unverified.

**Exit evidence:** failure matrix with reproducible verification references and open failure-injection gaps.

### P2-06 — Cross-language and whole-system boundary reconciliation

Map C++ Brain ownership against Rust prototypes, TypeScript interfaces and engineering-agent subsystem. Identify any duplicate cognitive state, data contract mismatch or unbuilt interface. Do not select process topology or introduce dependencies.

**Exit evidence:** single-authority boundary diagram and exact interface/source evidence.

---

## 9. Phase 2 acceptance criteria

Phase 2 is complete only when all of the following are satisfied:

1. BM-01 through BM-12 each have exact specification references, current-main source/function/blob evidence, donor source/function/blob evidence where relevant, and explicit missing/partial/conflict classifications.
2. Every material cross-mechanism producer/consumer edge is mapped, including the recurrent and delayed paths.
3. Every authoritative state owner is identified, and no competing Brain authority is left ambiguous.
4. Memory-to-reasoning and reasoning-to-downstream integration are traced end to end, with IF-02/IF-03 resolved or explicitly blocked by authority. PR #173 F-03 remains a separate SYS-08 substrate-boundary obligation.
5. PR #173 F-02/F-03 are mapped to their exact correction record and architecture sections; the original reviewer prose is recovered or its unavailability is explicitly recorded, and the Project Director/independent-clearance status is reconciled.
6. Persistence, replay, stale dependencies, concurrency, interruption, partial completion and recovery are mapped with test evidence or explicit non-verification.
7. Donor paths are compared to main and accepted requirements at exact commits; no wholesale merge is used as a substitute for integration analysis.
8. Hardcoded assumptions are classified as legitimate integrity/safety controls, provisional inductive biases or prohibited predetermined cognitive conclusions.
9. Learning claims distinguish storage, numeric adaptation, evidence-based structural change, action-outcome learning, later behavioral effect and held-out transfer.
10. Human cognitive function and MCU J.A.R.V.I.S. functional reference comparisons are included for substantial mechanism/integration decisions, without literal biological imitation or surface-behavior claims.
11. Historical Phase 1 preservation tasks remain visible and are not silently treated as completed.
12. A phase report records completed, partial, blocked, deferred and unverified work; independent review and required owner approval are recorded.

### Phase 2 exit boundary

Completion of this mapping phase will **not** clear Gate A, select an implementation baseline, approve donor ports, or authorize runtime implementation. Those decisions require their own explicit evidence and approval.

---

## 10. Current conclusion

The repository contains substantial reusable mechanisms and at least one meaningful donor line with affective state, action/consequence feedback, developmental strategy learning and contextual prediction. The main C++ Brain already has an event-backed state owner, memory, beliefs, world/causal models, attention, goals, planning, decision, prediction adaptation, evolution controls, reflection and a coordinating cycle.

However, the current main path is not a complete implementation of BM-01 through BM-12. Its most consequential integration failures are not simply missing classes:

- acquired evidence does not consistently retain the full provenance and epistemic lineage required downstream;
- memory is retrieved but is not passed into the reasoning premises;
- reasoning output is not consumed by downstream belief, prediction, goal, planning or decision processes;
- belief and causal updates rely on narrow generic rules;
- candidate goals are not formed from experience in the inspected main path;
- integrated affective appraisal is not established on main;
- learning is narrower than the specification's cross-mechanism developmental lifecycle;
- the current coordinator is a bounded single-pass cycle rather than the full recurrent, dependency-aware and recoverable Brain;
- the main action-assessment cycle does not own the full verified action-consequence path present in the PR #97 donor.

The correct direction is selective integration around one cognitive authority, with explicit evidence, dependency, persistence and learning contracts. Adding more isolated modules or merging the largest donor would not resolve these system-level gaps.

**Phase 2 remains in progress. No runtime implementation is authorized by this report.**

---

## Appendix A — Exact inspected source identities

### Accepted specification and source audit
- PR #174 HEAD: `0811a59e46bf934e32e794f90e4e7d18d4e2bd97`
- Specification: `3b6a53c8a295fa0d9fc29bbb6c7688b61d1dcdb1`
- Existing mechanism source audit: `4479874476715fd59a4c3ba6c908f06c43a1c6c2`
- BM-12 review correction record: `518522e5f222ee9fa7efe771c458adc08bd09a19`

### Main source baseline
- Main commit: `1273ddbcd0087d189e01388ded2d362fb1e058d2`
- `event.hpp`: `a31db633e8181378fcec0a20c5958c0065d430ee`
- `brain.hpp`: `8268ef84e0b361ead536724ba7761904b30ee58f`
- `brain.cpp`: `e9f3758fcc9c0e89b7280ce376db9033d547682d`
- `memory.hpp`: `f3662038237246efa51155f940d77564f144d6d9`
- `memory.cpp`: `ba72a897306d4761246d0deab2fbab37c49d372f`
- `cognitive_cycle.cpp`: `3df14c552f2048b0394dc362f7ee7a654a93fb32`
- `cognitive_workspace.hpp`: `b015d44e332ea2511d29e607495714d0b982d44e`
- `cognitive_workspace.cpp`: `fbd2321d9cd1c98217389beced292654e33a906e`
- `cognitive_runtime.cpp`: `1a1383cedc42e357dc9efce117328b8d55e30bca`
- `representation.cpp`: `0e53bfaa0c1114cb7390d9f7ce577c87d6bc6169`
- `perception_pipeline.cpp`: `ab9a745bb68e416d4e32c9d0c26a2d0b2016ab17`
- `world_model.cpp`: `5b68e8fe37d99732557237e347ae02234a3de172`
- `knowledge.cpp`: `25ecf822e6132f576266c1f86a964a227c7fb75f`
- `causal_model.cpp`: `f873d0a6e7fa0676bb88bf7a1f66436bc88a3c0d`
- `association_model.cpp`: `b378d4237527dfbb4c65f43545f7f0fc7c42669b`
- `attention.cpp`: `58f734dbe9772675d687752026231297f289e770`
- `goals.cpp`: `778a829de8314e83b095af2f2c2a6b83baa769f4`
- `intent.cpp`: `4283a4255284c51257df6bad12734782f2a6cde9`
- `strategy.cpp`: `5406a341cd4b3f42e16166f6122a0cb580aee298`
- `planning.cpp`: `aab022b7cbc06f380413395757d590b56a1f3a20`
- `decision.cpp`: `6a49e0f1f80c3c6b0955ddf98182fc6611c0e84c`
- `action_model.cpp`: `1da9e70b4d0716ae6ee7ff2110b28424f094d6df`
- `learning_loop.cpp`: `bc9a6aaca38d060667bcdf82f2b1a1f72c5936ba`
- `adaptation.cpp`: `7e07a491a5b13379a5719882a834ecc2452a54ef`
- `reasoning.hpp`: `5c6f82797d4f5052ad5d71a25624de192a2c87d9`
- `reasoning.cpp`: `feec78b2e8a1f2b0b58733fd509e4e5a750258fc`
- `reflection.cpp`: `06f34e20f35aad535a2c606b3669b2127ef7a480`
- `self_model.cpp`: `3c6a375eadd6894a635d2e18023a7079cba97c86`
- Core test CMake: `dab0c52ab4dfe15e1e2cbccfa9e6c904abdf54e3`

### Donor identities
- PR #97 HEAD: `c1da222e6c94aeb3f2ad000392c21fe4fc81ab25`
- PR #97 changed paths: 159
- PR #97 test CMake blob from Phase 1 matrix: `cbfd1fde52fffa6eeac025da2b7ddcb5ab493261`
- PR #97 detailed seven-path matrix: `docs/architecture/inventory/PHASE_1_PR97_DONOR_CAPABILITY_TRACEABILITY_2026-11-05.md`

**End of Phase 2 first integration map.**

---

## 11. Additional source-tracing batch — action execution, affective artifact boundary, and test provenance

**Audit date:** 2026-11-05  
**Engineering source baseline remains:** `main` at `1273ddbcd0087d189e01388ded2d362fb1e058d2`  
**Scope:** Read-only source/CMake/workflow tracing. No runtime code or tests changed; no build or test execution is claimed.

This batch extends the first map. It does not close Phase 2.

### 9.1 Main contains a bounded Brain-level action execution and feedback path

The first map correctly records that `CognitiveCycle::run` ends with action assessment and does not itself invoke external execution. The whole-Brain map must also account for a separate public Brain API:

- `core/cpp/include/jarvis/core/brain.hpp`, blob `8268ef84e0b361ead536724ba7761904b30ee58f`, lines 157–170.
- `core/cpp/src/action_execution.cpp`, blob `c2f8653eb755fa2790a88e49bc8b0b9c3077e439`.
- `core/cpp/include/jarvis/core/action_execution.hpp`, blob `38ff7033e7621db8f05cc1edc4bf59cb899ccdd3`.
- `core/cpp/tests/action_execution_phase7_suite.cpp`, blob `b4a0060596c91c67080ac0a2db324f720d760fbe`.

The Brain wrapper calls `ActionExecutor::run`, then records an `Evidence` item under `action.<action-name>` with the execution result's reason. The wrapper assigns reliability 1.0 to verified execution, 0.25 to rolled-back execution, and 0.5 to other returned statuses.

The executor performs authorization, invokes the supplied execution callback, invokes a verification callback, and attempts rollback after failed verification when a rollback callback is supplied. The registered Phase 7 test checks verified, failed, rejected and rolled-back cases, then checks that the Brain wrapper records `action.protect = "verified"` as a belief.

**Finding P2-I-007 — Main has a limited action-execution-to-learning feedback path.**

This is real mainline infrastructure and must not be described as donor-only. Its demonstrated feedback is nevertheless narrow: a status/reason string and a fixed status-to-reliability mapping are assimilated as evidence. The inspected API does not itself capture a structured external world-state delta, causal attribution, independent consequence provenance, or a general learned action policy. The test establishes a narrow action-status belief, not durable improvement in future action selection.

**Integration boundary:** `CognitiveCycle::run` still does not call `Brain::execute_action`; the cycle produces assessments, while execution is available through a separate Brain API. Therefore the action path exists in the repository but is not established as a single automatic end-to-end path from the inspected CognitiveCycle.

### 9.2 An affective/developmental source file exists on main but is not part of the main Brain target

A source artifact at `core/cpp/src/brain_restored_api.cpp`, blob `618deb6976eed951eae02b7f0da741e6d730bb0c`, contains definitions for affective and developmental accessors and a `choose_with_affect` method. It references `affective_state_model_`, `affective_learning_model_`, and `developmental_learning_`.

However:

- The pinned main `core/cpp/include/jarvis/core/brain.hpp`, blob `8268ef84e0b361ead536724ba7761904b30ee58f`, does not declare those affective/developmental accessors or those model members.
- The pinned main `core/cpp/CMakeLists.txt`, blob `c51816888e1bddb7bc00c59e72529524e27a0717f`, explicitly lists the `jarvis_core` sources and includes `src/brain.cpp`, but not `src/brain_restored_api.cpp`.
- The main Brain header's private model list contains the current models but no affective-state, affective-learning, or developmental-learning model members.
- The file is therefore not evidence that those methods or models are compiled into, or available through, the main Brain target.

**Finding P2-I-008 — Do not count `brain_restored_api.cpp` as an integrated mainline affective/developmental capability.**

It is an uncompiled/orphan source artifact relative to the inspected main CMake target and current Brain declaration. Its presence may be useful provenance for future donor/source investigation, but it is not current-main runtime capability. This reinforces the existing conclusion that the richer affective/developmental implementation must be audited at its exact donor revision and cannot be credited to main merely because a source file is present.

No manual compilation of this orphan file was attempted. The conclusion is based on the target source list and declaration/member mismatch, not on a claimed build failure.

### 9.3 Learning workflow files in main explicitly default to the donor branch

The following workflow files exist on main:

- `.github/workflows/jarvis-learning-mechanisms.yml`, blob `0eac13b1e6a43ea7fa06aaf9e0134f5b6ae27710`.
- `.github/workflows/jbp-brain-int-001.yml`, blob `31523dfa6bb5160397ebefd1f25325484461e271`.

Both declare `feat/jarvis-affective-state` as the default `source_ref` and check out that selected ref. The learning workflow invokes affective/developmental test targets; the integration workflow builds and runs developmental/action-consequence test targets.

**Finding P2-I-009 — Workflow presence on main is not evidence that main was tested for donor capabilities.**

A workflow definition stored on main is not itself execution evidence. Where the workflow's default checkout is the donor branch, its resulting tests (if run with that default) verify the donor ref, not the pinned main baseline. Any claim about a CI result must identify the actual workflow run, input `source_ref`, checked-out SHA, build/test result and artifact. No workflow run was retrieved or executed in this batch.

### 9.4 Updated interpretation of the action and affective pathways

| Pathway | Pinned main evidence | Current classification |
|---|---|---|
| Cognitive-cycle action assessment | `CognitiveCycle::run` calls `ActionModel::assess` | Main source present; no execution in this cycle |
| Brain-level action execution | `Brain::execute_action` delegates to `ActionExecutor` | Main source present |
| Execution outcome feedback | Status/reason recorded through `Brain::learn` | Main source present; narrow feedback semantics |
| Durable action-learning effect | Phase 7 test observes an action-status belief | Limited test evidence; future action-selection improvement not demonstrated |
| Affective model accessors in orphan source | `brain_restored_api.cpp` only | Not part of main target; not current-main capability |
| Affective/developmental donor tests | Workflows default to `feat/jarvis-affective-state` | Donor verification path; not main verification |

### 9.5 Follow-up required

1. Trace the full donor affective/developmental model sources, their event update triggers, state ownership, persistence/replay and actual downstream consumers at the exact PR #97 revision.
2. Determine whether donor action-consequence mechanisms add genuinely new evidence semantics beyond main's status/reason feedback, rather than assuming they do.
3. Trace all callers of `Brain::execute_action` and establish whether an application/runtime path connects it to cycle outputs.
4. Inspect the action authorization and execution tests for bypass, rollback failure, repeated execution, stale assessment and consequence-attribution boundaries.
5. Retrieve actual workflow runs and bind each result to its checked-out SHA before using it as test evidence.
6. Reconcile the orphan `brain_restored_api.cpp` provenance with its originating branch/commit and determine whether it is stale, intentionally excluded, or a preservation artifact. Do not add it to the target as part of Phase 2.

**Status remains:** Phase 2 IN PROGRESS. Gate A NOT CLEARED. No implementation baseline selected and no implementation authorization implied.


---

## 12. Additional source-tracing batch — PR #97 donor integration, learning tests, CI provenance, and duplicate-report reconciliation

**Audit date:** 2026-11-05  
**Main baseline:** `1273ddbcd0087d189e01388ded2d362fb1e058d2`  
**Donor baseline:** PR #97 branch `feat/jarvis-affective-state`, exact HEAD `c1da222e6c94aeb3f2ad000392c21fe4fc81ab25`  
**Scope:** Read-only comparison of donor Brain ownership, event/replay integration, action-consequence feedback, selected integration tests, CMake registration, workflow evidence, and the competing Phase 2 report.

This batch closes several follow-ups from §9. It does not authorize donor integration or implementation.

### 10.1 PR #97 contains a genuinely integrated affective/developmental Brain path on its donor revision

The orphan-artifact finding in §9.2 needs a precise two-revision interpretation:

- On pinned **main**, `brain_restored_api.cpp` is not listed in the `jarvis_core` source target, and the main `Brain` declaration does not own the affective/developmental models. It remains incorrect to credit these models to main.
- At PR #97 HEAD `c1da222e6c94aeb3f2ad000392c21fe4fc81ab25`, the donor `brain.hpp` includes `developmental_learning.hpp`, `affective_state.hpp` and `affective_learning.hpp`; its `BrainSnapshot` carries affective state; the private Brain members include `DevelopmentalLearning`, `AffectiveStateModel` and `AffectiveLearningModel`. The donor CMake target explicitly compiles `brain_restored_api.cpp`, `brain_action_execution.cpp`, `brain_prediction_context.cpp`, `brain_affective_planning.cpp`, `affective_state.cpp`, `affective_learning.cpp` and `developmental_learning.cpp`.

Exact donor identities:
- `core/cpp/include/jarvis/core/brain.hpp` — `671186f4c39879a182f9e511394fc564d86f2988`.
- `core/cpp/src/brain.cpp` — `dec9e5442b3ca4b81a7879855c6146b2619934cc`.
- `core/cpp/src/brain_action_execution.cpp` — `3b66bafb438cd28790e6f25611b96c86f1eff05c`.
- `core/cpp/src/brain_affective_planning.cpp` — `2a9406257c23f3a66a64071842be7d6448799406`.
- `core/cpp/src/brain_prediction_context.cpp` — `b3ceff150f3fe8223dc3f76f4c298ac264d72dae`.
- `core/cpp/src/affective_state.cpp` — `563a61cd8f6440f78a084f76a799b2c84bdd6813`.
- `core/cpp/src/affective_learning.cpp` — `dd1735a10871512691d4b518d1ce45246c80f708`.
- `core/cpp/src/developmental_learning.cpp` — `dbf5f43271dfa0a3c57236e2faa82eb88d15490d`.
- `core/cpp/CMakeLists.txt` — `bc264ce7b4ae489404ca03ea6d9676d0330a6a56`.
- `core/cpp/tests/CMakeLists.txt` — `cbfd1fde52fffa6eeac025da2b7ddcb5ab493261`.

**Finding P2-I-010 — PR #97's affective/developmental code is a compiled donor-side Brain integration, not merely a collection of disconnected files.** This is a material donor capability and a stronger state than the main orphan artifact. It remains donor-only because PR #97 is open, draft and unmerged. Its presence does not establish compatibility with the accepted PR #174 specification, current main APIs, later corrections, or Gate A.

### 10.2 Donor event/replay path joins prediction, affect, attention, developmental association and action strategy

The donor `Brain::replay` path in `core/cpp/src/brain.cpp` does more than restore independent model objects:

1. It validates prediction-outcome, action-outcome and affective-learning records before the affective processing stage mutates state.
2. It routes accepted events through `process_affective_experience`.
3. Prediction outcomes resolve the identified prediction, update numeric adaptation where applicable, apply association feedback, update developmental associations, and reinforce or suppress attention using prediction error.
4. Action outcomes update capability performance and action-status belief, then feed observed consequence and context into developmental strategy learning. Execution reliability and consequence evidence are represented separately.
5. Affective-learning events are checked against their referenced source action-outcome event. The donor verifies the source sequence, observed flag and matching expected/actual/error values before accepting the calibration update.
6. Brain construction replays the memory journal, reconstructing the integrated models from persisted events.

The donor's `Brain::execute_action` adds a richer path than the main status/reason wrapper:
- It checks authorization and, when an observer is supplied, creates a context-keyed expected-consequence prediction before execution.
- It records action identity, context, status, authorization/execution/verification/rollback flags, whether a consequence was observed, expected and actual consequence, consequence error, operational reliability, evidence reliability, salience, novelty and affective state metrics.
- It appends the authoritative action-outcome event, replays it and consolidates experience.
- For an observed consequence it appends a separately attributed affective-learning event.
- For a non-rejected attempt it appends a separate learning event for capability reliability.
- After releasing the Brain lock, it resolves the consequence prediction only when the consequence was actually observed. Missing observations leave the prediction unresolved.

This distinction matters: executor verification, operational reliability, consequence observation, consequence utility and affective calibration are not collapsed into one success/failure scalar. The donor's design is materially richer than main's narrow status/reason evidence path.

**Important limits and review questions remain:**
- The consequence observer is an injected callback. The source contract does not prove that an external observer is independent, trustworthy, correctly scoped, or measuring the intended world-state consequence.
- The donor derives a default strategy context from the first eligible goal or the literal fallback `global` when no explicit developmental context is present. This is a context fallback, not proof of general context understanding.
- The affective state equations and appraisal weights are engineered update rules. Their existence does not establish that the system's valuation is semantically grounded or that the learned appraisal is calibrated against independent utility.
- Replay validation and source-sequence checks improve integrity, but do not by themselves establish tamper resistance, adversarial provenance, atomic multi-event transactions, or recovery under every partial-append failure.
- The event-driven path is not proof that every external observation or every action is routed through this Brain API in a deployed runtime.

### 10.3 Donor integration tests demonstrate behavioral feedback, not just state storage

Selected donor test identities:
- `core/cpp/tests/brain_action_consequence_integration_suite.cpp` — `7616082579d53e3579cae8e87895bdb3dadba66f`.
- `core/cpp/tests/developmental_brain_integration_suite.cpp` — `760162dd6d1e669162e0bf22223a437491f5e262`.
- `core/cpp/tests/affective_brain_decision_suite.cpp` — `9ff9c0480fa34fa4f5600e514af419b2bbc79765`.

The inspected assertions establish that the donor test suite is designed to check more than model presence:
- A predicted action consequence is compared with an observed consequence; the prediction is resolved and a learning metric receives observations.
- Harmful observed consequences change attention's prediction-error weighting and affective learning updates.
- An executed action without an observed consequence does not create fabricated reward evidence; affective valence remains unchanged, uncertainty increases, and the strategy-use count does not increase.
- A failed verification can coexist with an observed external consequence; operational reliability and consequence learning are kept separate.
- After constructing a new Brain from the same journal, affective state, attention state/policy, developmental strategy, prediction calibration and action preference are checked for restoration.
- Developmental tests check that a learned action's score increases relative to a competing action, that the learned strategy is preferred in a related context, and that a subsequent CognitiveCycle decision reflects the learned preference.
- Episodic outcome tests explicitly distinguish positive, negative and unobserved outcomes and check that relevant prior experience can influence action ranking.

These are meaningful source-level behavioral assertions. They are not results of a test run performed in this Phase 2 batch. CMake declares and registers the action-consequence, developmental-brain and affective-brain suites, but registration alone is not execution evidence.

**Finding P2-I-011 — PR #97 contains test specifications for persistent, consequence-sensitive changes in later action selection.** The tests are substantially stronger than the main Phase 7 status-belief test. Their assertions still require independent execution at an exact commit, review of test validity and controls, and broader evaluation of confounding, generalization and real external consequence quality before they can support capability acceptance.

### 10.4 CI provenance: one PR #179 build is verified; donor CI remains unverified

A workflow run associated with PR #179's updated commit was retrieved:
- Workflow: **Native Brain Build**, run number **1610**, run ID **42064855161**.
- Job `cpp`: completed successfully.
- Job log checkout line identifies synthetic PR merge commit `337d30b6906ae19711359e65412e1d89801064ca`, described as merging PR #179 commit `9e00b3ba195975bbc74791af8af297e743bb8f5e` into PR #178 base `39fe09dcf13496f5f0005ccf3f00739303e29f88`.
- CMake configure and full native C++ build completed successfully for that merge tree.
- The workflow job's recorded steps contain configure and build, but no CTest/test step. No artifacts were attached.

**What this proves:** the combined PR #179/PR #178 merge tree compiled successfully in that workflow run.

**What it does not prove:** no test suite passed in that run; no donor branch code was built by this run; no runtime learning trial, persistence trial, sanitizer or independent behavioral evaluation was executed by this run.

A query for pull-request-triggered workflow runs associated with donor HEAD `c1da222e6c94aeb3f2ad000392c21fe4fc81ab25` returned no runs through the available commit-run wrapper. That wrapper is limited to PR-triggered runs and its first page; this is not evidence that no manually dispatched or otherwise unlisted workflow execution exists. No donor workflow result is accepted as verified here.

### 10.5 Reconciliation of competing Phase 2 reports #179 and #180

Both open/draft PRs modify the same report path, but they have different bases and are not interchangeable:
- PR #179: branch `docs/jarvis-phase-2-whole-brain-integration-map-20261105`, base PR #178 governance branch at `39fe09dcf13496f5f0005ccf3f00739303e29f88`, current HEAD before this batch `9e00b3ba195975bbc74791af8af297e743bb8f5e`.
- PR #180: branch `research/phase-2-brain-integration-map-20261105`, base PR #174 specification branch at `0811a59e46bf934e32e794f90e4e7d18d4e2bd97`, HEAD `6ca140300b914ed981a50301bbf1d82a5bfe4d8b`.

The PR #180 report is a 311-line first-batch investigation. It records seven inspected integration areas, six cross-mechanism findings and useful explicit source declarations in six headers not separately named in the PR #179 report's source inventory:
- `attention.hpp` — `c7e8ab0c5430d5c942fe314d928400f769c0a77c`;
- `causal_model.hpp` — `f740bdf222b3309b13f0c2f541c97448fc05da3e`;
- `goals.hpp` — `803fdd34130c71f54912b23fcba2f9eed23dd4f2`;
- `intent.hpp` — `1749ae0d795da496dd6a9a4dcdbd203ae7ddaf6f`;
- `learning_loop.hpp` — `287f2fe34cebd60b7a562d68c666572f71431cd6`;
- `reflection.hpp` — `435e03f8f03f74cb910338ab4ab1264e4eaf085c`.

Those declarations are now accounted for in the current Phase 2 source map: attention policy and reinforcement, causal transition/simulation, goal lifecycle, intent selection, learning-loop processing and reflection evaluation. The substantive PR #180 integration findings are already represented in the broader PR #179 map (including the memory/reasoning disconnection, reasoning non-consumption, goal-formation gap, causal-inference caveat, sequential-cycle limitation and split persistence paths). PR #179 adds the complete BM-01–BM-12 map, a larger integration-finding register, donor comparison, readiness matrix, appendices and the additional source-tracing evidence above.

The six PR #180 findings map to the PR #179 register as follows:

| PR #180 finding | PR #179 equivalent | Reconciliation note |
|---|---|---|
| P2-I-001 — retrieved memory omitted from reasoning premises | IF-02 | Main-baseline source fact; donor memory-to-action valuation is separately mapped in §13.2 |
| P2-I-002 — reasoning result not consumed downstream | IF-03 | Main-baseline source fact; donor reasoning conclusions feed causal simulation in §13.2 |
| P2-I-003 — supplied-goal lifecycle is not candidate-goal formation | IF-06 and P2-I-015 | Extended by the exact PR #173 F-02 mapping in §14 |
| P2-I-004 — causal links may overstate causality | IF-05 | Same main causal-model limitation |
| P2-I-005 — sequential cycle is not full recurrent/concurrent cognition | IF-08 | Same bounded-coordinator limitation |
| P2-I-006 — journal and metadata use separate persistence paths | IF-10 and P2-I-014/P2-I-016 | Extended with donor multi-event journal behavior and SYS-08 boundary evidence |

A material correction is also required before PR #180 can be considered a clean duplicate: its BM-02 section labels contextual language/operator-intent grounding as F-02, and its BM-12 section labels downstream reasoning integration as F-03. Those labels do not match the PR #173 correction record. PR #173 F-02 is experience-acquired candidate-goal formation; PR #173 F-03 is the SYS-08 computational-substrate boundary. The downstream reasoning issue is PR #174 source-audit finding AUD-12 / Phase 2 IF-03. PR #179 now corrects these labels and retains contextual language grounding as a separate BM-02 gap. PR #180 must not be merged or treated as an authoritative clean copy without this correction.

**Reconciliation decision for this working phase:** continue PR #179 as the working report because it is materially more complete and is based on the governance branch intended to carry the proposed project rules. Preserve PR #180's six unique header identities and its initial findings as incorporated evidence. Do not merge PR #180, close it, or claim its different base has been reconciled at the Git history level. Its branch ancestry and any unique unincorporated content remain a separate review item before either PR can be accepted or merged. No PR status was changed in this batch.

### 10.6 Updated interpretation matrix

| Capability | Main at pinned baseline | PR #97 donor at exact HEAD | Evidence status |
|---|---|---|---|
| Affective state ownership | Not integrated into main Brain target | Owned by donor Brain and replay path | Donor source-backed; not main capability |
| Affective appraisal learning | Orphan source artifact only | Event-driven calibration with source-event validation | Donor source-backed; runtime/independent verification pending |
| Developmental strategy learning | Not present in main Brain owner | Context-keyed strategy state affects action ranking | Donor source-backed; behavioral assertions exist |
| Action execution | Public Brain API with status/reason learning | Consequence observer, scoped prediction, structured outcome event | Main narrow path; donor richer path |
| Outcome attribution | No equivalent structured consequence contract established | Action event and source-linked affective event | Donor stronger; observer trust unresolved |
| Replay | Main event journal replay | Donor replay reconstructs affective, attention, prediction and strategy effects | Donor stronger; multi-event crash atomicity unresolved |
| Future action preference | Not demonstrated by main Phase 7 test | Donor tests assert learned preference and related-context transfer | Test source assertions only; no independent run accepted |
| CI proof | PR #179 combined merge tree configured/built; no tests in that run | No donor PR-triggered run returned by current query | Main PR build only; donor CI unverified |

### 10.7 Remaining work

1. Retrieve the exact donor PR #97 workflow runs through the Actions workflow listing/dispatch history where possible, including any manual `workflow_dispatch` runs, and bind run inputs and checked-out SHA to each artifact.
2. Independently inspect the complete donor integration tests for test-only shortcuts, hidden assumptions, reward leakage, context leakage, baseline/control validity, and whether the action-selection delta is caused by the intended learned state rather than shared global affect.
3. Trace the donor's external caller graph for `Brain::execute_action`, `choose_with_affect`, `choose_with_developmental_learning` and the CognitiveRuntime path. Separate test harness calls from production/runtime calls.
4. Trace the full donor event journal failure model across the multi-event action-outcome → affective-learning → capability-learning sequence, including append failures between records and replay idempotence.
5. Compare donor action authorization, stale assessment and rollback-failure behavior with main and Gate A requirements.
6. Incorporate the six PR #180 header identities into the final appendix and retain its branch-base difference in the duplicate-artifact register.
7. Continue unresolved BM-01–BM-12 edges, especially F-02/F-03 exact originating review text, world-model/belief authority, memory-supported reasoning, candidate-goal generation, coordination/invalidation/recovery and cross-language boundaries.

**Status remains:** Phase 2 IN PROGRESS. Gate A NOT CLEARED. No implementation baseline selected, no donor approved, no implementation authorization implied.


---

## 13. Additional source-tracing batch — donor runtime closure, mainline comparison, and journal failure boundaries

**Audit date:** 2026-11-05  
**Main baseline:** `1273ddbcd0087d189e01388ded2d362fb1e058d2`  
**Donor baseline:** PR #97 HEAD `c1da222e6c94aeb3f2ad000392c21fe4fc81ab25` (reverified against open PR #97; base is `main` at `4ba84b8b5ccf0e41530c46fdb8101551254ba864`)  
**Scope:** Trace the donor CognitiveRuntime → CognitiveCycle → selected-plan execution → Brain outcome processing → persistent learning → later decision path; compare the same boundary on pinned main; inspect the event journal's append/recovery semantics.

### 13.1 Donor runtime closes the action-learning loop at the coordinator boundary

The prior §12.7 follow-up asking whether the donor's runtime routes cycle output to action execution is now resolved at source level.

Exact donor source identities:
- `core/cpp/src/cognitive_runtime.cpp` — `cf00acb6abd52308343f3a0e7016e6173b945603`.
- `core/cpp/src/cognitive_cycle.cpp` — `f191dd610d6cbe1621756c35e7c13af2054a7266`.
- `core/cpp/src/brain_action_execution.cpp` — `3b66bafb438cd28790e6f25611b96c86f1eff05c`.
- `core/cpp/src/brain_affective_planning.cpp` — `2a9406257c23f3a66a64071842be7d6448799406`.
- `core/cpp/src/brain.cpp` — `dec9e5442b3ca4b81a7879855c6146b2619934cc`.
- `core/cpp/tests/cognitive_runtime_learning_integration_suite.cpp` — `656de56b1368e40afb090778a7a5504ab4208056`.
- `core/cpp/tests/cognitive_runtime_suite.cpp` — `361cba84a6fc6e07e31d14b5fa618c3f0a7848fa`.
- `core/cpp/src/memory.cpp` — `ab42bba1d32d6f48d091787491c72294a4a55bb5`.

The donor call chain is explicit:

1. `CognitiveRuntime::worker_loop` dequeues a `CognitiveCycleInput`, runs `cycle_.run(item.input)`, and, only when the result is completed, calls `execute_actions(result)` before publishing it.
2. `CognitiveRuntime::execute_actions` walks `result.context.plan.steps` in plan order. It matches each planned action to one corresponding assessment and marks that assessment consumed. It does not execute every candidate assessment as a batch.
3. A non-executable disposition is recorded as rejected. An executable action requires the configured adapter; when present, runtime calls `brain_.execute_action` with execute, verify, rollback, consequence-observer and authorization callbacks.
4. The execution result is appended to the cycle result; runtime metrics are updated. A narrow executor-reliability `Evidence` is queued as `CognitiveFeedback` for the runtime feedback processor.
5. `Brain::execute_action` creates a context-keyed consequence prediction before execution when authorization and a consequence observer are available. It executes through `ActionExecutor`, then appends and replays an authoritative `action_outcome` event.
6. When a consequence was observed, it appends a source-linked `affective_learning` event. For a non-rejected attempt it separately appends a capability `learning` event. After releasing the Brain lock, it resolves the consequence prediction using the observed actual consequence.
7. Replay routes action outcome through capability performance, developmental strategy, attention and affective-state processing; source-linked affective learning updates appraisal parameters; prediction feedback updates adaptation/association/developmental association/attention paths.
8. The next runtime cycle recalls prior action outcomes and developmental strategies. Those records alter expected consequence, utility and expected value before planning and decision. The loop therefore contains a source-visible path from observed action consequence to a later action-selection input.

**Finding P2-I-012 — PR #97 contains a connected runtime action/consequence/learning/decision loop, not merely callable isolated models.** This is a donor-side integration finding. It does not establish that the loop is in main, that all inputs are real-world trustworthy, or that its behavior has passed independent capability acceptance.

### 13.2 Donor memory is decision-operative, but not a premise source for the reasoning engine

The donor cycle retrieves prior experience before recording the current observation. It supplements generic observation recall with candidate-action-specific `action_outcome` recall, then adds perceptual and exact developmental-context recall.

The retrieved outcome records are used in two explicit decision pathways:
- Exact-context observed consequences calibrate each candidate's `expected_consequence` using evidence reliability and a weak prior.
- Direct-context learned strategies, related-context strategies, or (when no strategy exists) observed episodic outcomes alter action utility and expected value. Exploration pressure is applied where local evidence is absent.

The cycle then passes these adjusted candidates to the planner, decision engine and action assessment boundary. This is stronger than memory being present only in a result object: retrieved episodic evidence is used in action ranking.

There is still a distinct limitation. The donor `ReasoningProblem` is constructed from current beliefs and causal links; retrieved memories are not directly included as reasoning premises. However, when reasoning is valid and has conclusions, those conclusions are used as assumptions for causal simulation, whose projections are persisted as predictions and then contribute to uncertainty/planning. Therefore:
- **Memory → action valuation/planning:** connected in donor.
- **Memory → explicit reasoning premises:** not established in the inspected donor path.
- **Reasoning conclusions → causal simulation/prediction:** connected in donor.
- **Reasoning conclusions → mainline simulation:** not connected in the pinned main path, which simulates directly from current beliefs.

This refines, rather than erases, IF-02 and IF-03: the earlier findings describe the pinned main baseline; donor-side connections must be represented separately and must not be attributed to main.

### 13.3 Mainline runtime does not currently close the same execution loop

The pinned main files were independently fetched at `1273ddbcd0087d189e01388ded2d362fb1e058d2`:
- `core/cpp/src/cognitive_runtime.cpp` — `1a1383cedc42e357dc9efce117328b8d55e30bca`.
- `core/cpp/src/cognitive_cycle.cpp` — `3df14c552f2048b0394dc362f7ee7a654a93fb32`.
- `core/cpp/include/jarvis/core/brain.hpp` — `8268ef84e0b361ead536724ba7761904b30ee58f`.
- `core/cpp/src/brain.cpp` — `e9f3758fcc9c0e89b7280ce376db9033d547682d`.

Main's `CognitiveCycle::run` performs observation, memory retrieval, belief/causal reasoning, prediction, goal selection, planning, decision and action assessment. It returns assessments; it does not execute them. Main's `CognitiveRuntime::worker_loop` runs the cycle, creates/publishes a workspace and result, and updates processed metrics. The pinned main runtime source contains no `execute_actions` method and no call to `brain_.execute_action`.

Main does expose an inline `Brain::execute_action` method in `brain.hpp`. That wrapper calls `ActionExecutor::run` and converts the returned reason/status into one `Evidence` record with a fixed reliability mapping. The inspected main method is not invoked by the main CognitiveRuntime path and does not accept the donor's consequence-observer callback or create the donor's structured outcome-event sequence.

**Finding P2-I-013 — Main has an action-execution API, but its inspected cognitive runtime does not connect cycle assessments to that API.** The main path therefore must not be described as a closed action/consequence learning loop. P2-I-007 in §11 remains accurate only as a narrow standalone Brain API; this section supplies the missing integration qualification.

Main's reasoning boundary is also confirmed at the pinned source: `ReasoningProblem` receives beliefs and causal links; causal simulation uses the current belief set directly. Retrieved memories are included in the cycle result but are not used as reasoning premises or as candidate-action outcome evidence in this main cycle. This supports the main-baseline scope of IF-02/IF-03.

### 13.4 Donor runtime integration tests assert behavioral change across cycles and restart

The donor `cognitive_runtime_learning_integration_suite` provides a particularly important test specification:

- It configures an injected action executor, verifier and consequence observer.
- In the initial synthetic environment regime, `calibrate` produces `-0.8`; after one runtime cycle, the test checks the authoritative action outcome, resolved consequence prediction, prediction-error metric, affective-learning update, persisted context-specific event and negative developmental strategy.
- The next cycle receives the same candidate set and is expected to plan `wait`, demonstrating that the previous consequence changed later action selection.
- A separate context test checks that the learned preference does not blindly transfer to an unrelated context.
- The environment callback is then switched to a reversed deterministic regime. Repeated cycles must eventually select `calibrate`, showing that the strategy can be revised by subsequent contrary evidence.
- After stopping and reconstructing Brain from the journal, a new CognitiveRuntime must choose and execute `calibrate` under the restored regime.
- A no-observer control verifies that successful and verified execution without an observed consequence does not create a developmental strategy preference.

The companion `cognitive_runtime_suite` checks that runtime executes only selected plan steps, records results, does not invoke the executor when authorization rejects the action, and continues operating after an execution failure.

These are strong integration-test assertions for the donor loop. Their limits must remain explicit:
- The observer is a deterministic test callback, not an independent physical-world sensor or trusted evaluator.
- The environment regime switch is controlled by the test, not learned from an uncontrolled environment.
- The test demonstrates bounded adaptation and context isolation for the selected scenarios, not general causal attribution, statistical robustness, safety under arbitrary actions, or broad generalization.
- The tests were inspected but not executed in this Phase 2 batch. Their CMake registration is not execution evidence.

### 13.5 Multi-event action learning is not a single atomic journal transaction

The donor action handler appends multiple separate records:
1. authoritative `action_outcome`;
2. conditional `affective_learning` when the consequence was observed;
3. conditional capability `learning` for non-rejected attempts;
4. a separate prediction-outcome record when the consequence prediction is resolved.

The donor `Memory::append` persists each event individually. `Memory::persist` opens the journal in append mode, writes one event, flushes the stream, and if that individual write fails attempts to resize the journal back to its pre-append size. This protects an individual append from some partial-write failures, but it is not a transaction spanning the entire action-learning sequence. Earlier successful events are not rolled back when a later append fails. In particular, the action outcome may be committed while the affective-learning event or capability-learning event is absent; the function does not expose a complete-chain commit status to the runtime caller.

The replay path validates the affective-learning source against the referenced action-outcome sequence and checks matching expected/actual/error values. It also tracks processed affective-learning source sequences to avoid applying the same source-linked appraisal update twice during replay. This is a useful local integrity/idempotence control, not a transaction protocol for all related events.

The inspected persistence code uses stream `flush()`; no explicit file or directory `fsync` is visible in the inspected append path. The journal format also lacks a frame marker/checksum; startup scans valid records, quarantines an unreadable suffix and truncates to the last valid record boundary. Metadata is persisted separately through a `.meta` file and temporary-file rename. These mechanisms should not be conflated with power-loss durability, tamper resistance or cross-file atomicity.

**Finding P2-I-014 — Donor event replay provides ordered reconstruction and source-linked validation, but action learning is a multi-record, partially committable sequence.** Failure-injection tests must establish what state is reconstructed when each append boundary fails and whether callers can distinguish execution success from learning-record persistence failure.

### 13.6 Updated investigation ledger

Resolved or narrowed in this batch:
- The donor external runtime caller path for `Brain::execute_action` is source-traced through `CognitiveRuntime::execute_actions`.
- Donor memory's action-outcome influence on candidate action valuation is source-traced.
- Donor reasoning conclusions' use in causal simulation is source-traced.
- Main's absence of runtime action execution is confirmed at the pinned main baseline.
- The donor's multi-record append and local affective-source validation boundary is source-traced.

Still open:
1. Exact F-02/F-03 originating review text and acceptance obligation reconciliation.
2. Donor test execution at exact PR #97 HEAD, with full CI run/input/checkout SHA evidence; the current connector cannot list arbitrary/manual workflow-dispatch runs, so absence of a returned PR-triggered run is not proof no other run exists.
3. Independent review of test controls and test validity, plus failure injection at every append boundary.
4. Trustworthiness and calibration of external consequence observers, including evidence provenance and objective ground truth.
5. Donor authorization freshness, stale assessment handling, rollback failure semantics and caller-visible persistence failure semantics.
6. Full world-model/belief authority, candidate-goal formation, coordination/invalidation/recovery, cross-language boundaries and any remaining BM-01–BM-12 edges.
7. PR #180's ancestry/base reconciliation and any unique content not yet represented in PR #179.

### 13.7 Self-review and consistency checks performed before handoff

The working report was re-read and checked against the exact source revisions used in this batch. The following corrections/controls were applied:
- Section headings were renumbered sequentially after the two appended source-tracing batches; the prior duplicate section numbers 9 and 10 are corrected to 11 and 12.
- Main and donor source identities were fetched separately and pinned explicitly. Donor runtime evidence is not attributed to main.
- The earlier main action-execution statement is qualified: the standalone Brain API exists, but the pinned main CognitiveRuntime does not call it.
- IF-02/IF-03 are explicitly scoped to main and contrasted with the narrower donor integrations; the donor still does not pass retrieved memories as direct reasoning premises.
- Donor integration tests are described as source assertions, not as executed test results.
- The only verified CI result remains the PR #179/PR #178 merge-tree native build, with no CTest step. It is not represented as donor CI or test evidence.
- Journal append protection is described per individual record; no multi-event transaction or fsync guarantee is claimed.
- No runtime source, test, build configuration, dependency or donor file was changed. This batch updates the Phase 2 investigation report only.

**Status remains:** Phase 2 IN PROGRESS. Gate A NOT CLEARED. No implementation baseline selected, no donor approved, no implementation authorization implied.


---

## 14. Additional source-tracing batch — correction of F-02/F-03 provenance and goal/substrate capability mapping

**Audit date:** 2026-11-05  
**Architecture correction baseline:** PR #173 head `97191111bc2573c14d391c0af9628db7b11f194b`  
**Accepted specification baseline:** PR #174 head `0811a59e46bf934e32e794f90e4e7d18d4e2bd97`

### 14.1 Correction to the Phase 2 finding labels

A self-review of §1.2 found that the previous report version incorrectly described F-02 as “contextual language/operator-intent grounding” and F-03 as “downstream reasoning integration.” Those labels do not match the repository's PR #173 correction record.

The exact PR #173 artifacts inspected are:
- Corrected architecture: `docs/architecture/02_BRAIN_FOUNDATION_ARCHITECTURE.md`, blob `364aa3b5fabdab527c169ab170dd72e23c502438`.
- Separate correction record: `docs/architecture/reviews/02_BRAIN_FOUNDATION_ARCHITECTURE_REVIEW_CORRECTIONS_2026-11-03.md`, blob `fa6a5baaa4226dc7b845f4da6e07c5635ccc6ad8`.
- PR #173 remains open/draft at `97191111bc2573c14d391c0af9628db7b11f194b`; its PR body records the original independent-review verdict as NOT APPROVED — REVISION REQUIRED, followed by the Builder's correction submission.
- The available GitHub review-list query returned no submitted review nodes for PR #173. The correction record itself says independent re-review pending.
- PR #174's Project Director acceptance comment `6604790481` accepts the specification at `0811a59e46bf934e32e794f90e4e7d18d4e2bd97` and explicitly clears PR #174 finding F-01. It does not itself state that PR #173 F-02/F-03 received an independent re-review verdict.

The PR #173 correction record defines:
- **F-02 — Experience-acquired goal formation.** The architecture must distinguish supplied-goal processing from the developmental capacity to generate candidate goals from interpreted experience, changed circumstances, discrepancies, internal conditions and prior goal/action consequences. Candidate formation must be evidence-grounded, evaluated, revisable and traceable; the listed sources are not fixed triggers or prescribed objectives.
- **F-03 — SYS-08 embodiment and computational-substrate boundary.** SYS-08 provides compute, storage, networking, device and runtime substrate; SYS-01 retains semantic ownership and validation of cognitive state. Infrastructure acknowledgement/failure must not be treated automatically as cognitive truth, memory absence, external-world evidence or learning. Recovery responsibilities and operational contracts must remain distinct.

The correction record says the Builder addressed both findings in the architecture proposal and supplies exact section references. The available PR metadata does not establish a later independent re-review submission for PR #173. Therefore this report does not invent an independent clearance verdict. The Project Director's project history/decision record remains authoritative for whether those corrections were formally accepted.

**Separate reasoning issue:** PR #174's F-01 was the missing explicit owner for general reasoning/inference; it was addressed by adding BM-12. The later source-audit finding AUD-12 and this report's IF-03 concern the existing reasoning engine's narrow behavior and lack of downstream use on pinned main. They are not PR #173 F-03.

### 14.2 F-02 source mapping — goal progress learning exists; candidate-goal formation is not demonstrated

Exact main source identities:
- `core/cpp/include/jarvis/core/brain.hpp` — `8268ef84e0b361ead536724ba7761904b30ee58f`.
- `core/cpp/src/goals.cpp` — `778a829de8314e83b095af2f2c2a6b83baa769f4`.

Exact PR #97 donor identities:
- `core/cpp/include/jarvis/core/brain.hpp` — `671186f4c39879a182f9e511394fc564d86f2988`.
- `core/cpp/src/brain_restored_api.cpp` — `7155d4d9c8eef527836fb79bf901aa32ddbae38b`.
- `core/cpp/include/jarvis/core/goals.hpp` — `66f8cd436a18a0bca8039205f682fc929c32b6a5`.
- `core/cpp/src/goals.cpp` — `afaedcfb0f2f68ff88b3a20e474fce04bb59815c`.
- `core/cpp/include/jarvis/core/cognitive_goal_outcome.hpp` — `c986480d82b9951177031f3387169819c3856234`.
- `core/cpp/tests/goal_directed_cognition_suite.cpp` — `7fe6cf6c4dd2dc2a54bb9f48fcdd3c3d91d7c282`.
- `core/cpp/tests/cognitive_runtime_goal_feedback_suite.cpp` — `15a6bdffe37ae7df6c625ea9737fda4c0bf08a7f`.

Observed implementation:
- Both main and donor expose goal creation through a caller-supplied `Goal` object; the inspected API accepts an already formed goal rather than deriving a candidate from an experience.
- Donor `GoalModel::create` validates and stores the supplied goal. `update_progress` updates an existing goal's progress, outcome momentum and priority from the observed progress delta.
- Donor `GoalOutcomeEvidence` and `GoalProgressModel` track progress and positive/negative/completed outcomes for an identified goal. Donor `Brain::assimilate_goal_outcome` assimilates outcome evidence into an existing goal's progress.
- Donor replay restores goal creation and progress lifecycle events. Runtime goal-feedback tests check progress, regression rejection and completion for an already-created goal.
- The inspected goal-directed test starts with two explicit goal objects and tests intent selection, action planning and progress/outcome assimilation. It does not test candidate-goal generation.
- No candidate-goal proposal/generation API or experience-to-new-goal formation path was found in the inspected main Brain/CognitiveCycle path or the inspected PR #97 goal/Brain/runtime paths.

**Finding P2-I-015 — F-02 remains a capability gap in the inspected main and PR #97 donor paths.** The donor has stronger goal-outcome assimilation and experience-sensitive progress/priority updates, but that is not the same capability as forming a new candidate goal from experience. Do not count goal progress learning, intent selection or supplied-goal evaluation as satisfying experience-acquired candidate-goal formation. This is a bounded source finding, not a proof that no candidate-goal concept exists anywhere outside the inspected paths.

### 14.3 F-03 source mapping — cognitive state persists through direct filesystem code; SYS-08 contract is not explicit at this boundary

Exact pinned main source identities:
- `core/cpp/include/jarvis/core/memory.hpp` — `f3662038237246efa51155f940d77564f144d6d9`.
- `core/cpp/src/memory.cpp` — `ba72a897306d4761246d0deab2fbab37c49d372f`.

Observed boundary:
- The inspected `Memory` constructor accepts a `std::filesystem::path` for the journal.
- The implementation directly creates directories, opens journal and metadata files, appends records, flushes streams, reads files and repairs a corrupt journal suffix using filesystem operations.
- The inspected `Memory` interface does not expose an explicit SYS-08 substrate provider/adapter contract for operational availability, bounded resource requests, storage acknowledgement, integrity/failure status or substrate recovery. Main identities: `memory.hpp` `f3662038237246efa51155f940d77564f144d6d9`; `memory.cpp` `ba72a897306d4761246d0deab2fbab37c49d372f`.
- Donor identities: `memory.hpp` `5401d5bd236cca8d3a93f2815164a7734cf6990f`; `memory.cpp` `ab42bba1d32d6f48d091787491c72294a4a55bb5`.
- The event journal and metadata file are separate persistence artifacts; their lifecycle and recovery are implemented inside this C++ Memory component.
- The donor uses the same general direct-filesystem Memory boundary; the richer donor Brain replay path does not itself establish a separate SYS-08 contract.

**Finding P2-I-016 — The inspected C++ persistence boundary does not make the SYS-08 substrate contract explicit.** The architecture-level separation between SYS-01 cognitive meaning and SYS-08 operational substrate is documented, but this source path directly owns filesystem interaction. The required SYS-08 interface, failure reporting, persistence acknowledgement semantics and recovery handoff are not established by the inspected Memory API. This is a source-boundary gap, not a claim that no SYS-08 implementation exists anywhere in the wider repository.

### 14.4 Updated correction and acceptance ledger

| Finding | Correct meaning | Architecture correction | Source/capability status in this map |
|---|---|---|---|
| PR #173 F-02 | Experience-acquired candidate-goal formation | Builder correction record maps the requirement into PR #173 architecture sections 4.6, 9, 11, 11.1, 12 and 13 | Not demonstrated in inspected main or PR #97 donor paths; P2-I-015 |
| PR #173 F-03 | SYS-08 computational-substrate boundary | Builder correction record maps the requirement into PR #173 architecture sections 7, 11, 11.1 and 12 | Architecture-level boundary exists; explicit C++ Memory-to-SYS-08 contract not demonstrated; P2-I-016 |
| PR #174 F-01 | Explicit general reasoning/inference mechanism ownership | Added BM-12 in accepted PR #174 specification | Narrow reasoning prototype only; memory premises and downstream integration remain gaps; AUD-12 / IF-02 / IF-03 |

The full original reviewer prose for PR #173 F-02/F-03 was not present in the PR's changed files, PR conversation comments or review submissions returned by the current repository queries. The separate Builder correction record contains the finding titles, substantive summaries, exact correction map and rationale. The report therefore uses those grounded summaries and does not fabricate a verbatim quote. If verbatim reviewer wording is a mandatory Phase 2 artifact, the original review document or source conversation must be supplied/recovered.

**Status remains:** Phase 2 IN PROGRESS. Gate A NOT CLEARED. No implementation baseline selected, no donor approved, no implementation authorization implied.


---

## 15. Additional source-tracing batch — belief/world-state dual projections and donor dispute consumption

**Audit date:** 2026-11-05  
**Main baseline:** `1273ddbcd0087d189e01388ded2d362fb1e058d2`  
**Donor baseline:** PR #97 HEAD `c1da222e6c94aeb3f2ad000392c21fe4fc81ab25`

### 15.1 Main replay updates two distinct projections from the same event attributes

Exact main source identities:
- `core/cpp/include/jarvis/core/brain.hpp` — `8268ef84e0b361ead536724ba7761904b30ee58f`.
- `core/cpp/src/brain.cpp` — `e9f3758fcc9c0e89b7280ce376db9033d547682d`.
- `core/cpp/include/jarvis/core/world_model.hpp` — `1c14f692374b0ab272f05634b7bdd26e358b4f1f`.
- `core/cpp/src/world_model.cpp` — `5b68e8fe37d99732557237e347ae02234a3de172`.
- `core/cpp/src/cognitive_cycle.cpp` — `3df14c552f2048b0394dc362f7ee7a654a93fb32`.

Main `Brain` owns both `beliefs_` and `world_`. During replay of observation/learning events, each eligible event attribute is processed into:
- a belief keyed only by the attribute name; and
- a WorldModel fact keyed by `(event.source, attribute-name)`.

The belief update uses last-value replacement for a conflicting value and reduces confidence using a generic reliability formula. WorldModel instead retains a disputed fact record and can keep the previous fact as current when its confidence is higher. The two representations therefore preserve different conflict semantics and can disagree about which value is current. Both are rebuilt by replaying the same event journal; they are not two independent persistence stores.

Main's `CognitiveCycle::run` reads beliefs and causal links. The inspected main cycle does not read `brain_.world().facts()`, `disputed_facts()` or `disputed_relations()`. A repository-wide search of the pinned main C++ source found the `Brain::world()` accessor used in `world_self_model_phase4_suite.cpp`, not as a consumer in the main runtime/cycle. Thus the WorldModel is maintained and externally inspectable, but its disputed-state information is not an operative input to the inspected main reasoning/planning cycle.

### 15.2 PR #97 adds a bounded consumer for disputed world evidence

The donor retains the same WorldModel implementation blob `5b68e8fe37d99732557237e347ae02234a3de172`, but changes the CognitiveCycle integration:
- Donor `core/cpp/src/cognitive_cycle.cpp` — `f191dd610d6cbe1621756c35e7c13af2054a7266`.
- Donor `core/cpp/src/brain.cpp` — `dec9e5442b3ca4b81a7879855c6146b2619934cc`.

The donor cycle retrieves `disputed_facts()` and `disputed_relations()`, marks a belief disputed when a matching WorldModel fact is disputed, and includes disputed-belief/world-dispute pressure in its uncertainty used for planning. This is a concrete improvement over main's non-consuming cycle path. It still does not pass alternative fact values, their source histories and conflict lineage into the reasoning premise contract; it carries dispute as a boolean/aggregate uncertainty signal.

### 15.3 WorldState is a separate compiled utility, not the Brain's authoritative world-state owner

Exact main source identities:
- `core/cpp/include/jarvis/core/world_state.hpp` — `5e91ec301d8254380731e0fdf14d16b6a3d5face`.
- `core/cpp/src/world_state.cpp` — `84658ee6e1a4485e1fe0f24ebb40eb3e281670f0`.
- `core/cpp/tests/world_state_suite.cpp` — `bc6539059a8cc856572f3b01358085f27b1673a9`.
- `core/cpp/tests/world_self_model_phase4_suite.cpp` — `f375f6e36c16fbb038d2ce3ba5c4cd18adf1860c`.
- `core/cpp/CMakeLists.txt` — `c51816888e1bddb7bc00c59e72529524e27a0717`.
- `core/cpp/tests/CMakeLists.txt` — `dab0c52ab4dfe15e1e2cbccfa9e6c904abdf54e3`.

`WorldState` wraps a `WorldModel` with an in-memory event summary/history and per-update snapshots. Its `apply(Event)` converts each event attribute into a fact with default confidence 0.5, records sequence/timestamp/source/kind, and checkpoints the current facts/relations. It offers historical lookup by sequence and clear operations. The source does not provide a persistence or replay constructor for `WorldState`; its history and snapshots are ordinary in-memory vectors.

`world_state.cpp` is included in `jarvis_core`, and `jarvis_world_state_suite` is registered in CTest. The inspected C++ source callsites show its direct use in the standalone world-state test, not as a member of `Brain` or a CognitiveRuntime dependency. By contrast, `Brain` owns `WorldModel` directly. The existence and compilation of this separate timeline/snapshot utility must not be mistaken for an integrated Brain world-state history or recovery mechanism.

### 15.4 Test evidence and interpretation

- `world_self_model_phase4_suite` tests that standalone WorldModel conflict handling retains disputed facts/relations and that Brain replay makes a fact queryable through `brain.world()`. It does not assert that disputed facts alter a main CognitiveCycle decision.
- `world_state_suite` tests standalone event application, snapshot sequence/timestamp, fact/relation access, in-memory history, historical lookup and clearing. It does not test Brain integration or persistence across restart.
- These test sources are registered, but no test execution is claimed in this Phase 2 batch.

**Finding P2-I-017 — Main maintains belief and world projections with different conflict semantics, but the inspected main cycle does not consume WorldModel dispute state.** PR #97 adds a bounded dispute-to-uncertainty consumer; it does not establish complete multi-hypothesis adjudication or reasoning over alternative world claims.

**Finding P2-I-018 — The separate WorldState history/snapshot utility is compiled and tested in isolation but is not connected to Brain/CognitiveRuntime in the inspected source graph.** Its in-memory snapshots are not evidence of persistent, restart-recoverable world-state history.

### 15.5 Remaining BM-04/BM-11 questions

1. Establish the canonical owner and semantic contract between the belief map, WorldModel facts/relations and any WorldState timeline.
2. Define how source identity, claim scope, temporal validity, confidence and independent corroboration affect conflict resolution.
3. Determine whether donor dispute flags are sufficient for any accepted scenario or whether premise-level alternatives and contradiction lineage are required.
4. Trace invalidation from belief/world revision to dependent predictions, strategies, plans and reasoning conclusions.
5. Define whether WorldState is retained as a utility, integrated into the Brain under one owner, or deferred; do not create a second authoritative world-state store.
6. Add tests that demonstrate disputed evidence changing downstream reasoning/decisions, and that restart/replay reconstructs the same conflict history.

**Status remains:** Phase 2 IN PROGRESS. Gate A NOT CLEARED. No implementation baseline selected, no donor approved, no implementation authorization implied.


---

## 16. Additional source-tracing batch — Rust state ownership, TypeScript contracts, and cross-language integration reality

**Audit date:** 2026-11-05  
**Main baseline:** `1273ddbcd0087d189e01388ded2d362fb1e058d2`  
**Scope:** Trace the repository's Rust runtime prototype and TypeScript integration contracts against the authoritative C++ Brain types and build target. This is a source/configuration audit; no cross-language builds or runtime calls were executed.

### 16.1 Rust is a separate minimal cognitive-state prototype, not a connected C++ runtime service

Exact Rust source identities:
- `runtime/rust/Cargo.toml` — `c8e5a4d1cd1faef5c79a816fbef04d5022575f0a`.
- `runtime/rust/src/lib.rs` — `ba949e43b7e06ce081b078035dfe7e48625d521c`.
- `runtime/rust/src/cognition.rs` — `e46bb5b19528b58bf518f75f5edf704221cf5c9f`.
- `runtime/rust/src/error.rs` — `5019356b7382960766de039e3e16a1f1c4e43150`.

The crate is named `jarvis-runtime`, edition 2021, exposes a Rust library and declares no external dependencies. Its `BrainRuntime` owns a public `CognitiveState`; `observe` validates nonempty key/value and finite strength, then updates that state.

The Rust `CognitiveState` owns:
- a `HashMap<String, Belief>` keyed by string;
- a `Vec<String>` working-memory buffer;
- a cycle counter.

Its `Belief` stores only string key/value, scalar strength and evidence count. Repeated equal values update a running mean; a conflicting value replaces the current value only when incoming strength is greater; otherwise existing strength is multiplied by 0.95. The working-memory vector stores only observed values and removes its oldest item after 64 entries.

This is a small standalone state-update prototype. The inspected crate does not expose an event-journal interface, source/provenance record, C++ bridge, RPC endpoint, serialization contract, prediction/causal/goal/action lifecycle, or persistence/replay path. `CognitiveState::observe` is also publicly callable independently of `BrainRuntime::observe`, so the finite-strength validation in the wrapper is not an invariant enforced by the state type itself.

### 16.2 C++ remains the only inspected integrated Brain state owner

Exact C++ source identities:
- `core/cpp/include/jarvis/core/brain.hpp` — `8268ef84e0b361ead536724ba7761904b30ee58f`.
- `core/cpp/include/jarvis/core/cognition.hpp` — `e9aec6461351db42c77ff8414a175ce4c5eea33e`.
- `core/cpp/include/jarvis/core/event.hpp` — `a31db633e8181378fcec0a20c5958c0065d430ee`.
- `core/cpp/CMakeLists.txt` — `c51816888e1bddb7bc00c59e72529524e27a0717`.

The C++ Brain owns the event-backed `Memory`, belief map, prediction map, WorldModel, goals, attention, causal/association models and the rest of the integrated C++ mechanisms described in this map. Its `Belief` uses the shared `Scalar` variant (monostate, bool, int64, double, string), confidence, observation count and updated event sequence. This is a materially different state contract from Rust's string-only belief and in-memory value list.

The inspected `jarvis_core` CMake project declares `LANGUAGES CXX` and compiles the C++ Brain/runtime sources into a static C++ library. It does not declare a Rust language, invoke Cargo, link the Rust crate, or expose a C ABI/FFI bridge. Repository code search found the Rust `BrainRuntime`/ `CognitiveState` symbols only in the Rust crate. No caller from the C++ Brain or C++ CognitiveRuntime was identified.

**Finding P2-I-019 — The Rust crate is an isolated prototype with its own duplicate belief/working-memory state, not a connected subsystem of the authoritative C++ Brain.** It must not be counted as an integrated runtime, persistence service or safety/concurrency boundary. If retained, its future role must be defined as either a subordinate service with an explicit state-free contract or a separate experimental implementation; it must not become a second authority for beliefs, goals or identity.

### 16.3 TypeScript provides draft contracts and operator/agent wrappers, but no concrete Brain transport implementation was found

Exact TypeScript source identities:
- `interfaces/typescript/src/brain.ts` — `291916d45af0c67180542f8d775dba8b8ec1976f`.
- `interfaces/typescript/src/agent_bridge.ts` — `cd86f7d5f44e2d30c0401bb4bf02e05328d1c038`.
- `interfaces/typescript/src/operator_session.ts` — `2a699a78bc5beb31ed07cd913e0a527bb64d6bcf`.

The TypeScript `brain.ts` declares `Observation`, `DecisionContext`, `Capability` and an abstract `BrainTransport` interface with asynchronous `observe`, `decide` and `capabilities` methods. The interface describes a possible integration seam; the inspected file supplies no implementation.

The `agent_bridge.ts` file declares typed request/message/session structures and an abstract `AgentBridgeTransport` with `send`, `receive` and `connected`. `operator_session.ts` wraps that transport with operator identity and convenience functions for send/receive/connectivity. Its source comment explicitly preserves authorization inside the engineering/runtime boundary; the operator wrapper itself does not grant execution authority.

Repository symbol searches found the declarations but no concrete class implementing `BrainTransport` or `AgentBridgeTransport`. The operator functions are wrappers over an injected transport, not a transport implementation. No direct call from these TypeScript files into the C++ Brain, Rust crate or a defined RPC endpoint was identified.

### 16.4 The declared TypeScript shapes do not yet form a lossless C++ wire contract

The source-level comparison exposes several material schema mismatches:

| Concept | TypeScript declaration | C++ declaration | Integration consequence |
|---|---|---|---|
| Observation | source, kind, scalar record, timestampNs | Event has sequence, timestamp_ns, source, kind, Attributes; Observation wraps Event plus novelty | Event sequence and novelty are absent from the TypeScript Observation shape; timestamp and scalar encoding need a specified mapping |
| Scalar values | string, number, boolean, null | monostate, bool, int64, double, string | JavaScript number does not preserve every int64 exactly; null/absence/monostate semantics are not mapped |
| Decision context | goal string plus observation array | numeric goal priority/progress, plan value/risk, resource budget, uncertainty, threat and deadline pressure | The same type name represents materially different data and semantics |
| Decision result | `string | null` | vector of scored Decision objects with CandidateAction and typed DecisionOutcome | Candidate alternatives, scores and disposition semantics are lost by the declared return shape |
| Capability | id, version, string input/output lists | id, name, description, schemas, permissions, cost, risk, reliability, availability and reversibility | Authorization and operational capability metadata have no corresponding TypeScript fields |

The TypeScript files also leave transport serialization, protocol versioning, authentication, replay/idempotency, correlation failure handling, deadlines, cancellation, error mapping and schema evolution unspecified. The use of `bigint` for message sequence/timestamp fields requires an explicit wire representation; the interface does not define one.

The expected `interfaces/typescript/package.json` and `interfaces/typescript/tsconfig.json` paths were not present, and repository code search returned no `package.json` or `tsconfig` result. No TypeScript build/test command or concrete transport implementation was identified in the inspected repository configuration. This is not a claim that the source cannot be compiled manually; it means the checked-in contract does not currently provide a reproducible package/build/verification boundary.

**Finding P2-I-020 — TypeScript contains useful but incomplete integration contracts; it does not yet connect to the C++ Brain and its same-named types are not semantically equivalent.** The contracts must not be treated as a working cross-language API until wire encoding, schema compatibility, concrete transport, authority, error semantics and contract tests are established.

### 16.5 Polyglot architecture disposition

The repository's architecture document states that C++ is intended for native computation/memory, Rust for concurrency- and safety-sensitive services, TypeScript for integration contracts and Python where its ecosystem is appropriate. That is an architectural direction, not evidence that the corresponding cross-language boundaries already exist.

The inspected source state is:
- **C++:** integrated Brain implementation and current cognitive-state authority.
- **Rust:** independent minimal prototype with duplicate belief/working-memory state and no observed bridge to C++.
- **TypeScript:** interface declarations and operator/agent wrappers, with no concrete Brain transport found.
- **Python:** no Python Brain bridge or runtime path was established by this targeted source/configuration search; no Python subsystem is credited in this map.
- **Engineering-agent coordination:** the TypeScript agent bridge is a coordination message contract; it is not itself the Brain's cognitive state or action authority.

The PR #97 changed-file inventory contains no Rust or TypeScript source changes. The donor integration examined in §§10–13 remains a C++ donor path; it does not solve the polyglot boundary.

### 16.6 Updated findings and required proof

**P2-I-019** and **P2-I-020** refine IF-12. They do not imply that all polyglot implementation is undesirable. They establish that the current checked-in Rust and TypeScript assets are not yet interoperable cognitive/runtime subsystems.

Before any cross-language integration is authorized:
1. Declare one authoritative cognitive-state owner and explicitly forbid duplicate belief/goal/identity authority in subordinate services.
2. Specify versioned, lossless event, scalar, decision, capability and error schemas, including integer precision, timestamp units, nullability and sequence semantics.
3. Select a transport and define authentication, authorization, correlation, idempotency, retry, ordering, timeout, cancellation, backpressure and restart behavior.
4. Define whether Rust receives immutable work requests and returns typed results, rather than maintaining a second mutable Brain state.
5. Provide concrete TypeScript transport implementations and a reproducible package/build/test configuration.
6. Add cross-language contract tests against the C++ types and tests proving rejected/duplicate/stale messages cannot mutate cognitive state or bypass action authorization.
7. Demonstrate end-to-end persistence/replay and failure behavior across process boundaries before claiming integrated operation.

**Status remains:** Phase 2 IN PROGRESS. Gate A NOT CLEARED. No implementation baseline selected, no donor approved, no cross-language integration authorized.
