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

1. **Evidence and interpretation:** BM-01 preserves acquired experience and provenance; BM-02 is responsible for interpretation; BM-03 supplies memory; BM-04 evaluates claims; BM-10 detects omissions/conflicts; BM-11 marks dependent state stale. On pinned main, the raw event reaches `Brain::observe`, but the standalone `PerceptionPipeline` is not called by the production `CognitiveCycle`; therefore the BM-01→BM-02 production edge is not established on main. PR #97 has a donor-only pipeline-to-cycle edge. Do not draw the donor edge as a current-main capability.
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

**Observed path:** The representation engine normalizes event attributes into semantic nodes/relations and assigns modality using a finite source/kind string mapping. The perception pipeline supports registered providers, support checks, validation, exception isolation and strongest-confidence selection, then falls back to normalized event representation. These are real main-branch implementation units, but their existence must be separated from production integration. At main `1273ddbcd0087d189e01388ded2d362fb1e058d2`, `core/cpp/CMakeLists.txt` compiles `src/perception_pipeline.cpp`, and `core/cpp/tests/CMakeLists.txt` registers `jarvis_perception_pipeline_suite` and its CTest entry. However, `cognitive_cycle.hpp` does not include or own `PerceptionPipeline`, and `CognitiveCycle::run` calls `brain_.observe(input.observation)` then retrieves memory from raw observation attributes; it does not call `PerceptionPipeline::process` or `RepresentationEngine::normalize`. The bounded main-branch search found no production caller. Therefore main has a compiled perception utility with a registered unit-test target, not a perception pipeline integrated into its production CognitiveCycle. A unit test of the utility does not prove the production observation path invokes it.

**Main/donor boundary:** PR #97 at donor HEAD `c1da222e6c94aeb3f2ad000392c21fe4fc81ab25` has a different call graph: its `CognitiveRuntime` constructor registers configured providers with `cycle_.perception_pipeline()`, and its donor `CognitiveCycle::run` invokes the pipeline and uses the returned representation. This is donor-only capability and remains subject to P2-I-037's provider-failure observability/contract limitation. Do not copy or credit this path to main.

**Consumers:** On main, no production consumer of `PerceptionPipeline` was found in the audited `CognitiveCycle`; the cycle context has no representation field in its header. The standalone pipeline output therefore does not currently feed main memory retrieval, context formation or reasoning. In PR #97 donor, the representation is carried into donor cycle context and participates in downstream retrieval/context processing, but this remains a separate unmerged revision.

**Gaps**
- Exact source/kind strings (voice/speech, vision/camera, audio/microphone, sensor/system, text/command/message) act as modality fallback conventions. They are adapters, not acquired understanding.
- The strongest-confidence provider selection does not preserve multiple plausible interpretations or resolve disagreement.
- Attribute normalization is not semantic grounding, entity identity, contextual language understanding or operator-intent understanding.
- Confidence is not source reliability or belief confidence.
- Contextual language/operator-intent grounding remains a separate BM-02 requirement gap. It is not PR #173 F-02, which concerns experience-acquired candidate-goal formation.

**Donor comparison:** PR #97's `CognitiveRuntime` registers configured perception providers and its donor `CognitiveCycle::run` calls the configured pipeline; its developmental context extraction uses observation kind/source and representation features/values. Its fixed tokenization and context hierarchy are engineered inductive biases. This donor integration does not establish current-main integration or general contextual language/operator-intent grounding.

**Additional provider-failure boundary (donor HEAD):** `PerceptionPipeline::process` catches exceptions from `PerceptionProvider::perceive`, silently continues to other providers and falls back to deterministic raw-event normalization when none succeeds. It returns only a `PerceptualRepresentation`; no provider-failure result, capability-health event or runtime metric is exposed. The `PerceptionProvider::supports` interface is declared `noexcept`, so the catch surrounding `supports` cannot isolate a provider that actually throws there: violating the contract invokes termination rather than reaching the catch. The existing throwing-provider test covers a `perceive` exception and confirms fallback output, but it does not assert a recorded capability failure or test the `supports` contract. See P2-I-037 in §38.

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
- `Memory::load_metadata` has a separate, source-confirmed recovery weakness: metadata file open/header/count/decode failures return without a caller-visible status. Records are applied incrementally, so a malformed later record can leave earlier metadata applied while later records retain journal-derived defaults. This is not closed by event-journal replay and is not covered by the existing successful-restart test; see R3-02 in §46.
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
- On donor PR #97, feedback work is selected whenever the feedback queue is non-empty; there is no visible feedback-burst quota or aging rule in `worker_loop`. Under sustained feedback arrivals that keep the queue non-empty, queued input work can be delayed without a source-level service bound.
- `stop()` sets `stopping_`; `submit_feedback()` rejects while stopping, while `execute_actions()` discards the boolean return from its secondary feedback submission. With shutdown beginning during an in-flight action, the action may complete and its follow-on feedback may be rejected without an action-level acknowledgement. `drain_on_stop` drains already queued work; it does not make new submissions during shutdown admissible.
- When the donor result queue reaches `result_capacity`, `publish_result()` removes the oldest result and increments `dropped_results`. The counter makes aggregate loss observable, but the source does not establish per-result acknowledgement/reconciliation or safe retry semantics for a caller that did not receive a result.
- The current cycle does not own a complete action → verified consequence → learning loop; it stops at action assessment. PR #97 contains a separate Brain-owned action execution/consequence donor path.

**Donor comparison:** PR #97 adds Brain-owned action execution, consequence observation and feedback. The donor matrix records that execution and verification are separated and that observed consequence feeds the event/prediction path. It also records unresolved rollback/partial-side-effect semantics. PR #176 contains D1/D2 corrections, but its merge relationship and controller failure-injection status must be checked before adoption. The feedback-first scheduling, shutdown rejection and result-overflow behavior above are source-confirmed control-flow properties; starvation, lost caller reconciliation and duplicate retry are conditional risks, not reproduced production incidents. See IR-03 in §45 for the required test matrix and measurable acceptance conditions.

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
- `ReasoningEngine::solve` currently returns `valid=true`, `kind=consistency`, and `confidence=0.0` when `problem.premises` is empty. This is a source-confirmed contract mismatch: the accepted BM-12 specification requires an explicit insufficient-evidence/unresolved result, not a successful substantive-inference signal. The exact acceptance invariant is tracked as R3-04 in §46.
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
- No test source was executed locally during this mapping; exact donor-HEAD provider CI and a historical long-run artifact were later retrieved and reviewed in §§18–19.
- No CI run was manually dispatched by this audit; GitHub automatically triggered a PR build after the documentation branch update.
- No new performance, learning, transfer or longitudinal experiment was run by this audit; the historical DLT-002 artifact was retrieved and independently inspected in §19.
- No independent reviewer has reviewed this Phase 2 map.
- No full line-by-line audit of every PR #97 changed file or every later donor was performed.
- No compatibility/ABI/API proof exists for porting donor code into main.
- No runtime integration behavior is certified or capability-accepted by this document; the test and artifact evidence in §§18–19 is bounded verification evidence, not a Gate A decision.

### 6.3 Existing CI evidence must remain exact-commit scoped

Phase 1 recorded earlier CI results for selected PR #151, PR #176 and other donor revisions. They remain evidence only for the exact commits and workflows recorded in Phase 1. They must not be transferred to the current main commit, PR #97 head, PR #156 or this documentation branch.

### 6.4 Automatic build for the Phase 2 report branch

GitHub automatically ran the **Native Brain Build** workflow after the PR #179 documentation update:
- Run number **1620**, run ID `42073461253`.
- PR #179 head at run time: `33ea25dc28af096a3fc48669834417bbe74bea80`.
- PR #178 base: `39fe09dcf13496f5f0005ccf3f00739303e29f88`.
- Checked-out synthetic merge commit: `dec6629f8a5935696201cf25db6d203f5cfb8e7f`, merging that PR #179 head into the PR #178 base.
- The `cpp` job completed successfully. CMake Release configuration and `cmake --build build --parallel` both completed successfully; the build reached 100% and linked the registered C++ test executables.
- The workflow job has no CTest/test-execution step, and no artifacts were attached. This is build evidence, not a test pass.
- The log contains existing compiler warnings in `core/cpp/src/evolution_rollback.cpp` for missing initializers of `EvolutionHistoryRecord::reason` and `parent_experiment_id`. PR #179 changes only the Phase 2 report, so these warnings are not introduced by its documentation changes.

This run validates compilation of the PR #179/PR #178 merge tree at the exact synthetic merge SHA above. It does not validate PR #97 donor code, execute any test suite, demonstrate runtime learning, or clear Gate A. The later report-only commits are not represented by this run; no C++ source changed in those documentation updates.

### 6.5 Verified CI for the later integrated donor line — PR #156 and PR #176

The later donor integration line has substantially stronger CI evidence than the exact PR #97 head. These runs are bound to their checked-out synthetic merge commits, not treated as isolated branch builds.

**PR #156 — integration branch**
- PR head: `7fe212bbb0bd61116ea56581435e03b06c69b673`; base PR #155 head: `52c367a4b53fdfe9b29776795200555076e8cb49`.
- All workflows checked out synthetic merge commit `fb433acca35004d9d14ed790f2df16c895979b7a`, merging PR #156 into PR #155's base.
- Native Brain Build run #1403, ID `41174439433`: completed successfully.
- JARVIS Brain Tests run #1178, ID `41174439423`: native CTest job passed **73/73**; sanitized CTest job passed **73/73**.
- Brain ThreadSanitizer run #1160, ID `41174439446`: ThreadSanitizer CTest passed **73/73**.
- The logs specifically show `jarvis_evolution_brain_integration_suite`, `jarvis_developmental_brain_integration_suite`, `jarvis_goals_architecture_suite` and `jarvis_dlt_004_feature_composition` passing.

**PR #176 — D1/D2 correction and failure-boundary tests**
- PR head: `4cf017e073da980c9f77d739fde6f92ef1a2fbc1`; base PR #156 head: `7fe212bbb0bd61116ea56581435e03b06c69b673`.
- All workflows checked out synthetic merge commit `bc229522e36c03c4bbab68b56b14fd2cb1a7b1c5`, merging PR #176 into PR #156's base.
- Native Brain Build run #1587, ID `41808525486`: completed successfully.
- JARVIS Brain Tests run #1220, ID `41808525557`: native CTest job passed **73/73**; sanitized CTest job passed **73/73**.
- Brain ThreadSanitizer run #1202, ID `41808525492`: ThreadSanitizer CTest passed **73/73**.
- The logs specifically show the corrected `jarvis_goals_architecture_suite`, `jarvis_evolution_brain_integration_suite`, `jarvis_developmental_brain_integration_suite` and `jarvis_dlt_004_feature_composition` targets passing. The D1 selected-intent context regression and D2 non-finite goal-input rejection assertions are included in the changed test sources and therefore were compiled and executed by these CTest runs.

**Interpretation limits**
- These are real successful provider CI executions with build, CTest, sanitizer and ThreadSanitizer steps; they are stronger than test registration or a PR-description claim.
- Each run tested the PR head combined with its stated base branch in the recorded synthetic merge commit. It does not prove the donor head is compatible with current main `1273ddbcd0087d189e01388ded2d362fb1e058d2`.
- The same 73-test suite run in three configurations is not 219 distinct tests.
- Passing tests do not establish evaluator independence, production provenance trust, generalization beyond the specified test environments, or Gate A acceptance.
- At the time this subsection was first written, PR #97's exact head had not yet been verified. That historical statement is superseded by the exact-current-HEAD native and ASan/UBSan runs in §18.3. The PR #156/PR #176 line remains a later, distinct donor/integration revision and additionally supplies ThreadSanitizer evidence.


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
10. A bounded human-cognition and MCU J.A.R.V.I.S. comparison register is delivered for substantial mechanism/integration decisions, or the Project Director explicitly approves deferral. The required artifact is `docs/architecture/reports/PHASE_2_HUMAN_AND_MCU_REFERENCE_COMPARISON_2026-11-06.md`; it is drafted in PR #191, with independent review and Project Director acceptance still pending. The Main Builder owns its preparation; the Independent Reviewer challenges its evidence and limits; the Project Director accepts the deliverable or records an explicit deferral. Human cognition must be grounded in appropriate scientific sources with uncertainty/controversy stated; MCU J.A.R.V.I.S. is fictional functional inspiration only, not scientific evidence. The comparison must not prescribe literal biological imitation or surface-behavior claims.
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

### 11.1 Main contains a bounded Brain-level action execution and feedback path

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

### 11.2 An affective/developmental source file exists on main but is not part of the main Brain target

A source artifact at `core/cpp/src/brain_restored_api.cpp`, blob `618deb6976eed951eae02b7f0da741e6d730bb0c`, contains definitions for affective and developmental accessors and a `choose_with_affect` method. It references `affective_state_model_`, `affective_learning_model_`, and `developmental_learning_`.

However:

- The pinned main `core/cpp/include/jarvis/core/brain.hpp`, blob `8268ef84e0b361ead536724ba7761904b30ee58f`, does not declare those affective/developmental accessors or those model members.
- The pinned main `core/cpp/CMakeLists.txt`, blob `c51816888e1bddb7bc00c59e72529524e27a0717f`, explicitly lists the `jarvis_core` sources and includes `src/brain.cpp`, but not `src/brain_restored_api.cpp`.
- The main Brain header's private model list contains the current models but no affective-state, affective-learning, or developmental-learning model members.
- The file is therefore not evidence that those methods or models are compiled into, or available through, the main Brain target.

**Finding P2-I-008 — Do not count `brain_restored_api.cpp` as an integrated mainline affective/developmental capability.**

It is an uncompiled/orphan source artifact relative to the inspected main CMake target and current Brain declaration. Its presence may be useful provenance for future donor/source investigation, but it is not current-main runtime capability. This reinforces the existing conclusion that the richer affective/developmental implementation must be audited at its exact donor revision and cannot be credited to main merely because a source file is present.

No manual compilation of this orphan file was attempted. The conclusion is based on the target source list and declaration/member mismatch, not on a claimed build failure.

### 11.3 Learning workflow files in main explicitly default to the donor branch

The following workflow files exist on main:

- `.github/workflows/jarvis-learning-mechanisms.yml`, blob `0eac13b1e6a43ea7fa06aaf9e0134f5b6ae27710`.
- `.github/workflows/jbp-brain-int-001.yml`, blob `31523dfa6bb5160397ebefd1f25325484461e271`.

Both declare `feat/jarvis-affective-state` as the default `source_ref` and check out that selected ref. The learning workflow invokes affective/developmental test targets; the integration workflow builds and runs developmental/action-consequence test targets.

**Finding P2-I-009 — Workflow presence on main is not evidence that main was tested for donor capabilities.**

A workflow definition stored on main is not itself execution evidence. Where the workflow's default checkout is the donor branch, its resulting tests (if run with that default) verify the donor ref, not the pinned main baseline. Any claim about a CI result must identify the actual workflow run, input `source_ref`, checked-out SHA, build/test result and artifact. No workflow run was retrieved or executed in that batch; this was later superseded for exact PR #97 HEAD by the direct Actions provenance in §18.3. The workflow-default warning remains relevant to runs that checked out the donor branch from main.

### 11.4 Updated interpretation of the action and affective pathways

| Pathway | Pinned main evidence | Current classification |
|---|---|---|
| Cognitive-cycle action assessment | `CognitiveCycle::run` calls `ActionModel::assess` | Main source present; no execution in this cycle |
| Brain-level action execution | `Brain::execute_action` delegates to `ActionExecutor` | Main source present |
| Execution outcome feedback | Status/reason recorded through `Brain::learn` | Main source present; narrow feedback semantics |
| Durable action-learning effect | Phase 7 test observes an action-status belief | Limited test evidence; future action-selection improvement not demonstrated |
| Affective model accessors in orphan source | `brain_restored_api.cpp` only | Not part of main target; not current-main capability |
| Affective/developmental donor tests | Workflows default to `feat/jarvis-affective-state` | Donor verification path; not main verification |

### 11.5 Follow-up required

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

This batch advances several investigations identified in §8, especially P2-03 and P2-05. It does not authorize donor integration or implementation.

### 12.1 PR #97 contains a genuinely integrated affective/developmental Brain path on its donor revision

The orphan-artifact finding in §11.2 needs a precise two-revision interpretation:

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

### 12.2 Donor event/replay path joins prediction, affect, attention, developmental association and action strategy

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

### 12.3 Donor integration tests demonstrate behavioral feedback, not just state storage

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

These are meaningful source-level behavioral assertions. At the time of this first inspection, no exact-HEAD test result had yet been retrieved. The exact donor-HEAD CI execution was subsequently located and is documented in §18.3. CMake registration alone was not treated as execution evidence.

**Finding P2-I-011 — PR #97 contains test specifications for persistent, consequence-sensitive changes in later action selection.** The tests are substantially stronger than the main Phase 7 status-belief test. Exact donor-HEAD CI execution is now confirmed in §18.3. Their assertions still require independent review of test validity and controls, and broader evaluation of confounding, generalization and real external consequence quality before they can support capability acceptance.

### 12.4 CI provenance: PR #179 build verified; PR #97 exact-head CI subsequently verified; later integration CI separately verified

A workflow run associated with PR #179's updated commit was retrieved:
- Workflow: **Native Brain Build**, run number **1610**, run ID **42064855161**.
- Job `cpp`: completed successfully.
- Job log checkout line identifies synthetic PR merge commit `337d30b6906ae19711359e65412e1d89801064ca`, described as merging PR #179 commit `9e00b3ba195975bbc74791af8af297e743bb8f5e` into PR #178 base `39fe09dcf13496f5f0005ccf3f00739303e29f88`.
- CMake configure and full native C++ build completed successfully for that merge tree.
- The workflow job's recorded steps contain configure and build, but no CTest/test step. No artifacts were attached.

**What this proves:** the combined PR #179/PR #178 merge tree compiled successfully in that workflow run.

A later build was also retrieved for the then-current PR #179 report commit:
- [Native Brain Build run #1634](https://github.com/methaneex-oss/MethaneX/actions/runs/42080973918), run ID `42080973918`, completed successfully on 2026-11-05.
- Exact PR head checked out: `8b114f4d8b911f8280235b64ee2cd59e2eef5fe8`.
- Exact synthetic merge checkout: `044be4ae1312f1abfd41e631bca9383919f7b3c8`, merging that PR #179 head into PR #178 base `39fe09dcf13496f5f0005ccf3f00739303e29f88`.
- The job completed CMake configure and full native C++ build successfully. It did **not** run CTest; the workflow steps contain configure and build only.
- The log repeats the existing `evolution_rollback.cpp` missing-field-initializer warnings for `EvolutionHistoryRecord::reason` and `parent_experiment_id`, and the Actions Node.js 20 deprecation warning for `actions/checkout@v4`.

This later run supersedes the older PR #179 build commit listed above for the working report's then-current HEAD. It still proves build success only, not test execution or donor acceptance. The subsequent PR #179 commits through this report revision modify only this Markdown report, so they do not alter the C++ build inputs tested by run #1634.


**What it does not prove:** no test suite passed in that run; no donor branch code was built by this run; no runtime learning trial, persistence trial, sanitizer or independent behavioral evaluation was executed by this run.

An initial query through the pull-request-triggered commit-run wrapper returned no run for donor HEAD `c1da222e6c94aeb3f2ad000392c21fe4fc81ab25`. That was an incomplete search: the wrapper did not expose the branch-push runs. A subsequent direct Actions run-list query found and verified the exact-HEAD push CI runs. The corrected provenance and results are recorded in §18.3; the earlier statement that exact-head CI was unverified is superseded. This must be distinguished from the later PR #156/PR #176 integrated donor line, whose exact synthetic-merge CI runs are verified in §6.5.

### 12.5 Reconciliation of competing Phase 2 reports #179 and #180

Both open/draft PRs modify the same report path, but they have different bases and are not interchangeable:
- PR #179: branch `docs/jarvis-phase-2-whole-brain-integration-map-20261105`, base PR #178 governance branch at `39fe09dcf13496f5f0005ccf3f00739303e29f88`. The initial reconciliation snapshot used HEAD `9e00b3ba195975bbc74791af8af297e743bb8f5e`; subsequent report revisions are recorded in PR #179's commit history.
- PR #180: branch `research/phase-2-brain-integration-map-20261105`, base PR #174 specification branch at `0811a59e46bf934e32e794f90e4e7d18d4e2bd97`, HEAD `6ca140300b914ed981a50301bbf1d82a5bfe4d8b`.

The PR #180 report is a 311-line first-batch investigation. It records seven inspected integration areas, six cross-mechanism findings and useful explicit source declarations in six mechanism headers not separately named in the PR #179 report's source inventory, plus the `CognitiveCycle` public header identity:
- `attention.hpp` — `c7e8ab0c5430d5c942fe314d928400f769c0a77c`;
- `causal_model.hpp` — `f740bdf222b3309b13f0c2f541c97448fc05da3e`;
- `goals.hpp` — `803fdd34130c71f54912b23fcba2f9eed23dd4f2`;
- `intent.hpp` — `1749ae0d795da496dd6a9a4dcdbd203ae7ddaf6f`;
- `learning_loop.hpp` — `287f2fe34cebd60b7a562d68c666572f71431cd6`;
- `reflection.hpp` — `435e03f8f03f74cb910338ab4ab1264e4eaf085c`;
- `cognitive_cycle.hpp` — `28e7af98327956268a769adf7813125be842c1a2`.

Those declarations are now accounted for in the current Phase 2 source map: attention policy and reinforcement, causal transition/simulation, goal lifecycle, intent selection, learning-loop processing and reflection evaluation. The substantive PR #180 integration findings are already represented in the broader PR #179 map (including the memory/reasoning disconnection, reasoning non-consumption, goal-formation gap, causal-inference caveat, sequential-cycle limitation and split persistence paths). PR #179 adds the complete BM-01–BM-12 map, a larger integration-finding register, donor comparison, readiness matrix, appendices and the additional source-tracing evidence above.

The six PR #180 findings map to the PR #179 register as follows:

| PR #180 finding | PR #179 equivalent | Reconciliation note |
|---|---|---|
| P2-I-001 — retrieved memory omitted from reasoning premises | IF-02 | Main-baseline source fact; donor memory-to-action valuation is separately mapped in §13.2 |
| P2-I-002 — reasoning result not consumed downstream | IF-03 | Main-baseline source fact; donor reasoning conclusions feed causal simulation in §13.2 |
| P2-I-003 — supplied-goal lifecycle is not candidate-goal formation | IF-06 and P2-I-015 | Extended by the exact PR #173 F-02 mapping in §14 |
| P2-I-004 — causal links may overstate causality | IF-05 | Same main causal-model limitation |
| P2-I-005 — sequential cycle is not full recurrent/concurrent cognition | IF-08 | Same bounded-coordinator limitation |
| P2-I-006 — journal and metadata use separate persistence paths | IF-10 and P2-I-023/P2-I-016 | Extended with donor multi-event journal behavior and SYS-08 boundary evidence |

A second exact-identity reconciliation extracted all 20 distinct 40-character blob SHAs from the PR #180 report and checked them against the current PR #179 report; all 20 are present, with no source-identity hash left unaccounted for. This hash check does not mean the reports are textually identical or that every sentence was copied; it verifies that the source identities cited by the first-batch report are represented in the working report.

A material correction is also required before PR #180 can be considered a clean duplicate: its BM-02 section labels contextual language/operator-intent grounding as F-02, and its BM-12 section labels downstream reasoning integration as F-03. Those labels do not match the PR #173 correction record. PR #173 F-02 is experience-acquired candidate-goal formation; PR #173 F-03 is the SYS-08 computational-substrate boundary. The downstream reasoning issue is PR #174 source-audit finding AUD-12 / Phase 2 IF-03. PR #179 now corrects these labels and retains contextual language grounding as a separate BM-02 gap. PR #180 must not be merged or treated as an authoritative clean copy without this correction.

**Reconciliation decision for this working phase:** continue PR #179 as the working report because it is materially more complete and is based on the governance branch intended to carry the proposed project rules. Preserve PR #180's seven source identities (six mechanism headers plus `cognitive_cycle.hpp`) and its initial findings as incorporated evidence. Do not merge PR #180, close it, or claim its different base has been reconciled at the Git history level. Its branch ancestry and any unique unincorporated content remain a separate review item before either PR can be accepted or merged. No PR status was changed in this batch.

### 12.6 Updated interpretation matrix

| Capability | Main at pinned baseline | PR #97 donor at exact HEAD | Evidence status |
|---|---|---|---|
| Affective state ownership | Not integrated into main Brain target | Owned by donor Brain and replay path | Donor source-backed; not main capability |
| Affective appraisal learning | Orphan source artifact only | Event-driven calibration with source-event validation | Donor source-backed; exact-head native/sanitizer CI passed; independent semantic review and observer trust remain open |
| Developmental strategy learning | Not present in main Brain owner | Context-keyed strategy state affects action ranking | Exact-head integration suites passed; long-run behavior evidenced at older donor SHA; independent review and broader controls remain open |
| Action execution | Public Brain API with status/reason learning | Consequence observer, scoped prediction, structured outcome event | Main narrow path; donor richer path |
| Outcome attribution | No equivalent structured consequence contract established | Action event and source-linked affective event | Donor stronger; observer trust unresolved |
| Replay | Main event journal replay | Donor replay reconstructs affective, attention, prediction and strategy effects | Donor stronger; multi-event crash atomicity unresolved |
| Future action preference | Not demonstrated by main Phase 7 test | Donor tests assert learned preference and related-context transfer | Exact-head runtime integration suite passed in CI; historical DLT transfer evidence at `c6a8...`; independent reviewer acceptance remains open |
| CI proof | PR #179 combined merge tree configured/built; no tests in that run | Exact donor HEAD `c1da...`: native Release and Debug ASan/UBSan each had 71/71 CTest processes exit successfully; the test CMake explicitly undefines `NDEBUG` for executable test targets in Release, so assertions remain active in both jobs; Core Verification also succeeded | Exact-head assertion-enabled native and Debug ASan/UBSan integration CI verified; separate 330-minute DLT run at `c6a8...` is historical donor evidence, not current HEAD |

### 12.7 Remaining work

1. Exact-head push CI is retrieved and bound to PR #97 HEAD in §18.3. The 330-minute DLT-002 artifact remains at older donor SHA `c6a8...` (§19); the later three-seed, 30 aggregate trial-minute sweep at ancestor SHA `82c49a75...` is documented in §22. Neither is an exact-current-HEAD whole-system long-run run.
2. Selected donor integration tests and the runtime learning integration suite have been inspected. Complete test-by-test review remains open, especially test-only shortcuts, hidden assumptions, reward/context leakage, observer trust and baseline/control validity.
3. The CognitiveRuntime → CognitiveCycle → selected action → Brain consequence path is source-traced in §18.1 and exercised by exact-head CI plus the historical DLT harness. Remaining work is to classify other public donor APIs and all application/deployment entrypoints without assuming every deployment uses this path.
4. The multi-event action-outcome → affective-learning → capability-learning append/replay sequence is source-traced in §18.2. Atomicity is absent at the inspected Memory API boundary; failure-injection, interruption, retry and restart-equivalence tests remain required.
5. Donor action authorization, stale assessment, rollback-failure and observer-provenance behavior still require a dedicated comparison against main and Gate A requirements.
6. PR #180's six unique header identities and initial findings are incorporated into the working report. Its distinct base and Git history remain unreconciled; keep PR #180 open until owner-directed duplicate disposition.
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

**P2-I-023 (expanded in §§18.2 and 28) — Donor event replay provides ordered reconstruction and source-linked validation, but action learning is a multi-record, partially committable sequence.** Failure-injection tests must establish what state is reconstructed when each append boundary fails and whether callers can distinguish execution success from learning-record persistence failure.

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
| PR #174 follow-on F-02 | Contextual language/operator-intent grounding | Later review obligation summarized in Phase 1 reconciliation record; original review artifact was not located in the checked-in correction records or PR #174 discussion/review submissions inspected for this response; no exhaustive repository-wide document search was run | OPEN specification-review obligation; map to BM-02. Do not merge with PR #173 F-02. |
| PR #174 follow-on F-03 | Downstream reasoning integration | Later review obligation summarized in Phase 1 reconciliation record; original review artifact was not located in the checked-in correction records or PR #174 discussion/review submissions inspected for this response; no exhaustive repository-wide document search was run | OPEN specification-review obligation; map to BM-12 / IF-03 and the applicable reasoning source-audit finding. Do not merge with PR #173 F-03.

The full original reviewer prose for PR #173 F-02/F-03 was not present in the PR's changed files, PR conversation comments or review submissions returned by the repository queries. The separate Builder correction record contains their finding titles, substantive summaries, exact correction map and rationale. The PR #174 follow-on F-02/F-03 source is different: `PHASE_1_REVIEW_CORRECTIONS_AND_SCOPE_RECONCILIATION_2026-11-05.md` states that a subsequent review report supplied in the conversation identified contextual language/operator-intent grounding and downstream reasoning integration; it also records that this later report was not mirrored as a submitted GitHub review. The PR #174 issue discussion confirms historical acceptance of exact head `0811a59e46bf934e32e794f90e4e7d18d4e2bd97` and later F-01 correction activity, but does not contain that F-02/F-03 review report. Accordingly, the original PR #174 follow-on review artifact is **not available in the checked repository evidence inspected here**. This report preserves its two grounded summaries and open status without fabricating verbatim reviewer text. The missing original artifact must be recovered or its unavailability explicitly accepted by the Project Director before those obligations can be considered fully reconciled.

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
| Decision result | `string` or `null` | vector of scored Decision objects with CandidateAction and typed DecisionOutcome | Candidate alternatives, scores and disposition semantics are lost by the declared return shape |
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


---

## 17. Additional source-tracing batch — PR #97 ancestry and current-main divergence

**Audit date:** 2026-11-05  
**Current main:** `1273ddbcd0087d189e01388ded2d362fb1e058d2`  
**PR #97 recorded base:** `4ba84b8b5ccf0e41530c46fdb8101551254ba864`  
**PR #97 head:** `c1da222e6c94aeb3f2ad000392c21fe4fc81ab25`

### 17.1 Exact PR metadata and commit-graph results

Current PR #97 metadata reports **1,244 commits**, **159 changed files**, **18,788 additions** and **1,644 deletions**. It remains open, draft and unmerged.

GitHub commit comparisons returned:
- Recorded base `4ba84b8b5ccf0e41530c46fdb8101551254ba864` to donor head `c1da222e6c94aeb3f2ad000392c21fe4fc81ab25`: diverged; common ancestor `af09cf28d35e4a7b75c3c019e9f97893d8e19364`; 1,244 ahead and 1 behind.
- Recorded base to current main `1273ddbcd0087d189e01388ded2d362fb1e058d2`: main is 8 commits ahead, with the recorded base as merge base.
- Current main to donor head: diverged; same common ancestor `af09cf28d35e4a7b75c3c019e9f97893d8e19364`; 1,244 ahead and 9 behind.

The donor is therefore a large divergent implementation line, not a small patch based on the current main snapshot. The current main contains nine commits after the common ancestor that are absent from the donor head.

### 17.2 Reconcile counts by scope

These numbers are from different comparisons:
- **159 changed files**: current PR #97 diff against its recorded PR base.
- **165 paths**: Phase 1 main-to-candidate tree-delta inventory, including later integration changes. Its partition is 143 PR #97-only unchanged paths, 16 paths changed in both PR #97 and the later integration segment, 2 existing paths modified only after PR #97, and 4 files first introduced after PR #97.
- **1,244 commits**: current GitHub PR #97 commit count.
- **1,416-commit hunk ledger**: a separate historical/provenance enumeration artifact in Phase 1, not the PR #97 commit count.

Phase 1 source for the 165-path partition and the distinct hunk-ledger scope:
- `docs/architecture/reports/PHASE_1_WHOLE_REPOSITORY_INVESTIGATION_AND_REUSE_AUDIT_2026-11-04.md` — blob `925eb079b6c26578b64ee69caadb97b90143afb6`, §7 and §9.

### 17.3 Review consequence

This ancestry reinforces the existing donor disposition:
1. Treat PR #97 as a high-value donor, not the current main implementation baseline.
2. Compare every candidate donor path against the accepted PR #174 architecture, current main and later donor corrections at exact blob identities.
3. Revalidate API, event, persistence, workflow, test and failure semantics at the actual candidate revision.
4. Do not merge PR #97 wholesale or infer that its 1,244 commits represent 1,244 independently accepted cognitive capabilities.
5. Keep Gate A semantic provenance, ABI/downstream compatibility, rollback and independent-review obligations open until independently evidenced.

**Finding P2-I-021 — PR #97 is a 1,244-commit divergent donor line, with 9 commits of current-main history absent from its head.** Its 159-file PR diff and the separate 165-path main-to-candidate inventory are different evidence scopes. This rules out treating PR #97 as a current-main-compatible drop-in baseline.

**Status remains:** Phase 2 IN PROGRESS. Gate A NOT CLEARED. No implementation baseline selected, no donor approved, no implementation authorization implied.


---

## 18. Additional source-tracing batch — donor runtime call graph and exact-HEAD CI verification

**Audit date:** 2026-11-05  
**Main baseline:** `1273ddbcd0087d189e01388ded2d362fb1e058d2`  
**Donor baseline:** PR #97 `feat/jarvis-affective-state` at `c1da222e6c94aeb3f2ad000392c21fe4fc81ab25`  
**Scope:** Read-only source, CMake, Actions metadata and job-log audit. No runtime/test/build files changed.

### 18.1 The donor has a concrete runtime caller chain from cycle to external action and consequence feedback

The previous map correctly distinguished `CognitiveCycle::run` from action execution, but the donor runtime closes that boundary. The actual call chain is:

1. `CognitiveRuntime::worker_loop` runs `cycle_.run(item.input)`.
2. When the cycle completes, the worker invokes `execute_actions(result)`.
3. `execute_actions` walks the selected plan steps, matches each planned action to its assessment, and does not execute every candidate alternative.
4. For an executable assessment with an available adapter, it calls `brain_.execute_action(...)`.
5. The action adapter supplies execution, verification, optional rollback and consequence-observation callbacks. The consequence observer's returned value is passed into the Brain action-execution boundary.
6. `Brain::execute_action` creates the context-keyed consequence prediction before execution when authorized and an observer exists; then persists/replays the action outcome and any derived learning events. It resolves the consequence prediction only after the Brain lock is released and only when the authoritative action outcome persisted and the consequence was observed.

Source references at the exact donor HEAD:

- [`cognitive_runtime.cpp`](https://github.com/methaneex-oss/MethaneX/blob/c1da222e6c94aeb3f2ad000392c21fe4fc81ab25/core/cpp/src/cognitive_runtime.cpp#L155-L223), blob `cf00acb6abd52308343f3a0e7016e6173b945603`.
- [`cognitive_cycle.cpp`](https://github.com/methaneex-oss/MethaneX/blob/c1da222e6c94aeb3f2ad000392c21fe4fc81ab25/core/cpp/src/cognitive_cycle.cpp#L140-L158), blob `f191dd610d6cbe1621756c35e7c13af2054a7266`.
- [`cognitive_cycle.cpp`](https://github.com/methaneex-oss/MethaneX/blob/c1da222e6c94aeb3f2ad000392c21fe4fc81ab25/core/cpp/src/cognitive_cycle.cpp#L430-L535), same blob — context-specific consequence calibration and learned strategy/episodic evidence are applied before planning.
- [`cognitive_cycle.cpp`](https://github.com/methaneex-oss/MethaneX/blob/c1da222e6c94aeb3f2ad000392c21fe4fc81ab25/core/cpp/src/cognitive_cycle.cpp#L620-L731), same blob — episodic outcome weighting, affective planning context, plan and action assessment.
- [`cognitive_cycle.cpp`](https://github.com/methaneex-oss/MethaneX/blob/c1da222e6c94aeb3f2ad000392c21fe4fc81ab25/core/cpp/src/cognitive_cycle.cpp#L706-L731), same blob.
- [`brain_action_execution.cpp`](https://github.com/methaneex-oss/MethaneX/blob/c1da222e6c94aeb3f2ad000392c21fe4fc81ab25/core/cpp/src/brain_action_execution.cpp#L8-L60), blob `3b66bafb438cd28790e6f25611b96c86f1eff05c`.
- [`brain_action_execution.cpp`](https://github.com/methaneex-oss/MethaneX/blob/c1da222e6c94aeb3f2ad000392c21fe4fc81ab25/core/cpp/src/brain_action_execution.cpp#L112-L183), same blob.

The cognitive cycle also applies affective state through its planning context and uses context-specific developmental strategy/episodic evidence in its action scoring path. The separate public `choose_with_affect` and `choose_with_developmental_learning` methods are not the methods called by `CognitiveRuntime` in the inspected path; the runtime's cycle applies the relevant mechanisms directly. They should not be described as the runtime's entry point.

**Finding P2-I-022 — The donor contains a source-connected CognitiveRuntime → CognitiveCycle → selected-plan execution → Brain action-outcome → consequence-learning path.** This corrects any reading that donor action execution is only a standalone Brain API with no runtime caller. The path is source-proven and is exercised by the DLT executable described in §19. It does not prove every deployed sensor/action provider routes through this runtime, nor does it establish trustworthiness of arbitrary injected callbacks.

### 18.2 The action path is deliberately multi-event, but the journal does not provide an atomic learning transaction

The donor action-execution implementation appends separate events in this order:

1. The authoritative `action_outcome` event.
2. When a consequence was observed, a source-linked `affective_learning` event.
3. For every non-rejected attempt, a separate `learning` event carrying action-executor reliability evidence.

Each append is a separate call to `Memory::append`. The code checks each returned sequence, but it does not wrap the three records in a journal transaction or make the later append contingent on all prior derived events succeeding. If the affective-learning append fails, the capability-learning append is still attempted. A process interruption between appends can leave a valid prefix of the intended event group.

Replay has useful integrity controls:
- Brain construction replays the journal in sequence.
- Affective-learning records must reference a valid observed action-outcome sequence and must match its expected, actual and error values.
- Processed affective-learning source sequences and derived-learning source sequences are tracked to suppress duplicate application.

Those controls make individual records replayable and validate the source relationship; they do not make the group atomic. A failure after the action-outcome append but before the affective-learning append can preserve the action outcome and its direct affect/developmental processing while omitting the separate affective calibration update. A failure before the authoritative action-outcome append leaves the already-created prediction unresolved because the post-lock prediction-resolution path requires `outcome_persisted`.

The underlying Memory journal appends and flushes each event separately. Its recovery code quarantines an unreadable suffix before truncating the active journal, but the legacy format has no frame marker/checksum for safe resynchronization. No multi-event transaction, write-ahead intent/commit marker, or explicit filesystem `fsync` call was identified in the inspected implementation.

Source references:
- [`brain_action_execution.cpp`](https://github.com/methaneex-oss/MethaneX/blob/c1da222e6c94aeb3f2ad000392c21fe4fc81ab25/core/cpp/src/brain_action_execution.cpp#L112-L183), blob `3b66bafb438cd28790e6f25611b96c86f1eff05c`.
- [`brain.cpp`](https://github.com/methaneex-oss/MethaneX/blob/c1da222e6c94aeb3f2ad000392c21fe4fc81ab25/core/cpp/src/brain.cpp#L199-L199), blob `dec9e5442b3ca4b81a7879855c6146b2619934cc`.
- [`brain.cpp`](https://github.com/methaneex-oss/MethaneX/blob/c1da222e6c94aeb3f2ad000392c21fe4fc81ab25/core/cpp/src/brain.cpp#L245-L268), same blob — action-outcome affect processing and affective-learning source-sequence deduplication.
- [`brain.cpp`](https://github.com/methaneex-oss/MethaneX/blob/c1da222e6c94aeb3f2ad000392c21fe4fc81ab25/core/cpp/src/brain.cpp#L292-L358), same blob — source validation and replay rejection of malformed derived records.
- [`brain.cpp`](https://github.com/methaneex-oss/MethaneX/blob/c1da222e6c94aeb3f2ad000392c21fe4fc81ab25/core/cpp/src/brain.cpp#L431-L460), same blob — action outcome updates operational capability state and observed-consequence developmental strategy.
- [`brain.cpp`](https://github.com/methaneex-oss/MethaneX/blob/c1da222e6c94aeb3f2ad000392c21fe4fc81ab25/core/cpp/src/brain.cpp#L619-L622), same blob — derived-learning source-sequence deduplication.
- [`memory.cpp`](https://github.com/methaneex-oss/MethaneX/blob/c1da222e6c94aeb3f2ad000392c21fe4fc81ab25/core/cpp/src/memory.cpp#L33-L60), blob `ab42bba1d32d6f48d091787491c72294a4a55bb5`.
- [`memory.cpp`](https://github.com/methaneex-oss/MethaneX/blob/c1da222e6c94aeb3f2ad000392c21fe4fc81ab25/core/cpp/src/memory.cpp#L135-L135), same blob.

**Finding P2-I-023 — Action outcome, affective calibration and capability-learning persistence are individually journaled, not committed as one atomic experience transaction.** This is a concrete recovery/failure boundary that must be covered by failure-injection tests before the donor path can be accepted as crash-consistent. Required tests include append failure at each event boundary, process termination between appends, restart/replay equivalence, retry/idempotency behavior and explicit reporting of partial learning persistence. No such multi-event failure-injection evidence was found in the inspected selected suites.

### 18.3 Exact PR #97 HEAD CI was found and verified; earlier §12.4 wording is superseded

A direct Actions run-list query for the exact donor commit identified two push-triggered workflows on **2026-10-28**:

| Workflow | Run ID | Exact checked-out HEAD | Result | Jobs and executed steps |
|---|---:|---|---|---|
| Brain CI | `40788714686` | `c1da222e6c94aeb3f2ad000392c21fe4fc81ab25` | Success | `native-brain`: configure, build, CTest; `sanitizer`: ASan/UBSan configure, build, CTest |
| JARVIS Core Verification | `40788714735` | `c1da222e6c94aeb3f2ad000392c21fe4fc81ab25` | Success | `cpp-core`: configure, build, test |

For Brain CI run `40788714686`:
- The `native-brain` job completed successfully and its CTest log reports **71/71 test processes passed** in a Release configuration. The complete `core/cpp/tests/CMakeLists.txt` explicitly applies `-UNDEBUG` to GNU/Clang executable test targets and `/UNDEBUG` to MSVC executable test targets, so the Release test executables retain their `assert(...)` checks. The native result is assertion-bearing test evidence, not merely process-smoke evidence.
- The `sanitizer` job completed successfully and its CTest log reports **71/71 tests passed** under AddressSanitizer and UndefinedBehaviorSanitizer in Debug configuration. Debug naturally retains the suites' `assert` expressions; this job adds ASan/UBSan instrumentation to the assertion-bearing test run.
- The executed test list includes `jarvis_developmental_brain_integration_suite`, `jarvis_affective_brain_decision_suite`, `jarvis_brain_action_consequence_integration_suite`, `jarvis_cognitive_runtime_learning_integration_suite`, the memory/evolution persistence suite and the other registered C++ suites.
- No workflow artifacts were attached to this CI run.

Run references:
- [Brain CI run 40788714686](https://github.com/methaneex-oss/MethaneX/actions/runs/40788714686).
- [JARVIS Core Verification run 40788714735](https://github.com/methaneex-oss/MethaneX/actions/runs/40788714735).
- [Donor Brain CI workflow](https://github.com/methaneex-oss/MethaneX/blob/c1da222e6c94aeb3f2ad000392c21fe4fc81ab25/.github/workflows/brain-ci.yml), blob `74182cd073ef4b1eec77f78800f96c337545007e`.
- [Donor CMake test registration](https://github.com/methaneex-oss/MethaneX/blob/c1da222e6c94aeb3f2ad000392c21fe4fc81ab25/core/cpp/tests/CMakeLists.txt), blob `cbfd1fde52fffa6eeac025da2b7ddcb5ab493261`.

**What this proves:** the exact PR #97 donor HEAD compiled and all 71 registered C++ tests passed in the native CI job and again under ASan/UBSan. The selected integration tests were executed, not merely declared in CMake.

**What this does not prove:** no ThreadSanitizer run at this exact donor HEAD was found; no broad external-world deployment, long-duration test at this exact SHA, independent reviewer acceptance, adversarial observer validation, or multi-event append-failure recovery was established by these two CI runs. CI pass is test evidence, not Gate A approval.

**Finding P2-I-024 — PR #97 exact HEAD has verified assertion-bearing native Release and Debug ASan/UBSan CI, with 71/71 CTest processes exiting successfully in each job.** The test CMake explicitly undefines `NDEBUG` for executable test targets in Release, so the native job's assertions remain active; the Debug sanitizer job also retains assertions and adds AddressSanitizer/UndefinedBehaviorSanitizer coverage. This replaces the earlier §12.4 statement that exact-head donor CI was unverified. The CI evidence materially strengthens implementation/test provenance but does not resolve the remaining semantic, failure-model or independent-review obligations.


### 18.4 The exact-HEAD runtime integration test checks learning, transfer isolation, reversal and restart behavior

The exact-HEAD CTest suite includes `cognitive_runtime_learning_integration_suite`, blob `656de56b1368e40afb090778a7a5504ab4208056`. Its assertions exercise the runtime call chain rather than invoking only isolated Brain methods:

- The configured consequence observer supplies deterministic action-dependent consequences. The first selected action is executed through `CognitiveRuntime`; the test checks the observed consequence, persisted `action_outcome`, resolved context-keyed prediction, prediction-error metric and affective-learning update.
- The next cycle reconsiders the same candidate set and selects the alternative after the negative observed consequence.
- A semantically unrelated context does not blindly inherit the original context's learned action preference.
- The environment regime is reversed; repeated runtime cycles eventually switch the selected action to the newly beneficial action.
- After stopping and reconstructing Brain from the same journal, a new CognitiveRuntime selects the action supported by the persisted/replayed experience. This tests a future decision after restart, not only inspection of a restored strategy table.
- The test also exercises a no-consequence-observation condition: three actions execute and verify successfully while the consequence observer is omitted; the developmental strategy table must remain empty for that context.

Source references:
- [`cognitive_runtime_learning_integration_suite.cpp`](https://github.com/methaneex-oss/MethaneX/blob/c1da222e6c94aeb3f2ad000392c21fe4fc81ab25/core/cpp/tests/cognitive_runtime_learning_integration_suite.cpp#L66-L156), blob `656de56b1368e40afb090778a7a5504ab4208056`.
- [`cognitive_runtime_learning_integration_suite.cpp`](https://github.com/methaneex-oss/MethaneX/blob/c1da222e6c94aeb3f2ad000392c21fe4fc81ab25/core/cpp/tests/cognitive_runtime_learning_integration_suite.cpp#L158-L270), same blob.
- [`cognitive_runtime_learning_integration_suite.cpp`](https://github.com/methaneex-oss/MethaneX/blob/c1da222e6c94aeb3f2ad000392c21fe4fc81ab25/core/cpp/tests/cognitive_runtime_learning_integration_suite.cpp#L275-L317), same blob.
- [CMake registration](https://github.com/methaneex-oss/MethaneX/blob/c1da222e6c94aeb3f2ad000392c21fe4fc81ab25/core/cpp/tests/CMakeLists.txt#L240-L245), blob `cbfd1fde52fffa6eeac025da2b7ddcb5ab493261`.

**Important precision about the test's “No-feedback control” comment:** this is not a complete no-learning control. Omitting `observe_consequence` prevents environmental consequence evidence and the test correctly checks that no developmental action-value strategy is created. However, `CognitiveRuntime::execute_actions` still calls `evidence_for_action` for a verified, non-rejected execution and submits the action status/reason as operational evidence. The control therefore retains status/reliability feedback and does not assert that all belief, knowledge or affective updates are absent. It is a **no-consequence-observation control**, not a learning-ablation experiment.

**Assessment:** this exact-HEAD test is strong, targeted integration evidence for consequence-sensitive action selection, context isolation, reversal and persistence/restart. Its deterministic callback-based task remains a bounded integration fixture; it does not replace randomized multi-seed controls, broader task transfer or real external observer validation.

---

## 19. Additional source-tracing batch — independent inspection of the DLT-002 long-run artifact

**Audit date:** 2026-11-05  
**Run:** DLT-002 workflow run `40243557728`  
**Run commit:** `c6a8a00db848035c2f93564fa35f837c0fdb477f`  
**Artifact:** `DLT-002-40243557728-1`, artifact ID `12627858274`, SHA-256 `85c230eca64206269376efdd31a1d14667a84e1dadbcb23029c6d4e55b9becd5`  
**Scope:** Retrieved and inspected the archived workflow artifact, including run metadata, acceptance log, episode CSV, checkpoint CSV, trial log and preserved Brain journal. This was an artifact review, not a rerun.

### 19.1 The run completed, but it is not a test run of the current PR #97 HEAD

The workflow metadata and artifact establish:
- Branch: `feat/jarvis-affective-state`.
- Exact tested commit: `c6a8a00db848035c2f93564fa35f837c0fdb477f`, not current donor HEAD `c1da222e6c94aeb3f2ad000392c21fe4fc81ab25`.
- Configured duration: 19,800 seconds (330 minutes), 60-second checkpoints, seed `20261026`.
- Workflow job completed successfully. The long-run executable reported `final_status=COMPLETED` with **12,479 episodes**.
- Before the long run, the workflow ran only the two DLT-002 cross-process persistence tests (2/2 passed) and a 60-second smoke trial checking that all six phases appeared. It did **not** run the full 71-test CTest suite in this workflow.
- The archived `dlt_002_long_run.cpp` blob at that run commit is `4f322c6360d899871331b719bf29f6812dd715df`; the corresponding file at current donor HEAD is `cbd80951c2f331fa4893c1805fff45a4035d5d24`. The artifact CSV schema also differs from current HEAD's expanded output schema. Therefore the long-run result must be cited as historical donor evidence at `c6a8...`, not as a run of `c1da...`.

Evidence:
- [DLT-002 run 40243557728](https://github.com/methaneex-oss/MethaneX/actions/runs/40243557728).
- [DLT-002 workflow at current donor HEAD](https://github.com/methaneex-oss/MethaneX/blob/c1da222e6c94aeb3f2ad000392c21fe4fc81ab25/.github/workflows/dlt-002-four-hour.yml), blob `52d08751d29c1b7c7b60e07834ac1bfdc4eba626`.
- [DLT-002 executable at run commit](https://github.com/methaneex-oss/MethaneX/blob/c6a8a00db848035c2f93564fa35f837c0fdb477f/core/cpp/tests/dlt_002_long_run.cpp), blob `4f322c6360d899871331b719bf29f6812dd715df`.
- [DLT-002 executable at current donor HEAD](https://github.com/methaneex-oss/MethaneX/blob/c1da222e6c94aeb3f2ad000392c21fe4fc81ab25/core/cpp/tests/dlt_002_long_run.cpp), blob `cbd80951c2f331fa4893c1805fff45a4035d5d24`.

### 19.2 Archived episode evidence shows strong performance in a narrow synthetic contextual task

The artifact's 12,479 episode records produce these environment-evaluated optimal-action selection results:

| Phase | Optimal selections | Episodes | Accuracy |
|---|---:|---:|---:|
| clear-baseline | 2,957 | 2,964 | 99.764% |
| flooded | 2,431 | 2,436 | 99.795% |
| tunnel | 2,079 | 2,108 | 98.624% |
| clear-reversal | 1,884 | 1,889 | 99.735% |
| generalization-probe | 1,615 | 1,633 | 98.898% |
| flooded-reversal | 1,429 | 1,449 | 98.620% |
| **Total** | **12,395** | **12,479** | **99.327%** |

The recorded first ten decisions in the held-out `navigation/canyon` generalization phase were all optimal (10/10). Before the first action in that phase, the trial recorded a related strategy source from `navigation/flooded`, action `route-one`, similarity `0.5`. The run also recorded 9,931 positive and 2,548 negative consequences.

The trial design is meaningful but bounded:
- It is a two-action, one-step contextual choice task. Each cycle uses planning horizon 1 and the executable expects exactly one selected/executed action.
- The environment randomizes the hidden alpha-to-action mapping per seed, with beta mapped to the opposite action; it withholds the latent `route_condition` field from the Brain's observation.
- Outcomes contain 20% noise.
- The same context is reversed in later phases, and the held-out canyon context tests transfer from prior context-specific experience.
- The environment supplies an explicit context label (for example, `navigation/flooded` or `navigation/canyon`) to the Brain. The hidden latent condition/action mapping is withheld, but the task is not context-free or fully unstructured.
- The recorded expected action and latent condition are evaluation labels used by the harness to score selections; they are not passed as Brain observations.

The artifact supports the claim that this donor revision performed well over a long, noisy, partially observed synthetic contextual-learning challenge, including context reversal and a first-window transfer probe. It does not establish general intelligence, broad world-model competence, open-ended developmental learning, or performance in an external physical environment.

### 19.3 The long-run evidence has material experimental limitations

1. **Single seed:** the 330-minute run uses seed `20261026`; one successful seed does not establish robust performance across randomized mappings/noise streams.
2. **No matched no-learning control in this artifact:** the run does not compare the same Brain with consequence feedback disabled, nor a matched learner with the learning mechanism ablated. The exact-HEAD runtime integration suite does contain a short no-consequence-observer control, but operational action-status evidence is still submitted in that control; it is not a full learning-ablation control (see §18.4). The later seed-sweep workflow's fixed-action baseline is not equivalent to a matched Brain control.
3. **Narrow task:** two candidate actions, one action per cycle, one-step planning, a synthetic environment and a fixed six-phase protocol do not test multi-step plans, open-ended goals, rich sensor uncertainty, causal intervention breadth or unconstrained action selection.
4. **Phase counts are unequal:** the trial changes phase by elapsed wall-clock time while each episode takes variable processing time; episode counts per phase are consequently unequal. Aggregate accuracy is not a phase-balanced score.
5. **Prediction accounting is incomplete in this run revision:** the artifact records 38,400 prediction records and 12,479 prediction-outcome records, with 12,479 resolved predictions. The run's older metrics do not split unresolved action-consequence forecasts from other unresolved predictions. It therefore cannot prove that every action-consequence prediction was resolved.
6. **No full-suite gate in the long-run workflow:** only the two persistence tests and the six-phase smoke test were run before the 330-minute executable. The exact current donor HEAD's 71-test native and ASan/UBSan CI is separate evidence in §18.3, not part of this DLT workflow.

The current donor HEAD's DLT executable adds separate unresolved action-consequence and other-prediction counts and fails a feedback-enabled run when unresolved action-consequence forecasts remain. That is a source-level improvement at `c1da...`; the archived 330-minute artifact predates that version and must not be used to claim that the newer gate passed.

**Finding P2-I-025 — A 330-minute DLT-002 run completed 12,479 episodes with 99.327% environment-evaluated optimal action selection and a 10/10 first-window generalization probe, but the run is from donor commit `c6a8...`, uses one seed and a narrow synthetic one-step task, and lacks a matched no-learning control.** It is useful behavioral evidence, not capability acceptance and not verification of current donor HEAD.

**Status remains:** Phase 2 IN PROGRESS. Gate A NOT CLEARED. No implementation baseline selected, no donor approved, and no implementation authorization implied.


---

## 20. Additional self-review batch — runtime evidence schema collision and feedback backpressure

**Audit date:** 2026-11-05  
**Donor baseline:** `c1da222e6c94aeb3f2ad000392c21fe4fc81ab25`  
**Scope:** Independent second-pass review of the donor runtime's action-feedback event contract, replay projection and queue failure behavior. Documentation only; no source or test changes.

### 20.1 A newly generated action-reliability event still uses the legacy unordered-map evidence fallback

The event schema defines `Attributes` as `std::unordered_map<std::string, Scalar>`. The Brain's general learning replay path correctly prefers explicit `evidence_key` and `evidence_value` fields. Its fallback path is explicitly described as backward compatibility for older journal records, but it takes the **first eligible key encountered while iterating the unordered map**.

The donor `Brain::execute_action` currently creates a new `learning` event with:
- a dynamic key `action_executor.<action-name>` holding numeric reliability;
- `reliability`;
- `source_action_sequence`;
- `affective_relevant=false`.

It does **not** populate `evidence_key` and `evidence_value`. Replay therefore enters the legacy fallback. The fallback excludes reliability, salience, novelty, confidence, evidence_key, evidence_value and source_action_sequence, but does not exclude `affective_relevant`. Depending on unordered-map iteration order, it may assimilate the intended `action_executor.<name>` reliability fact or the `affective_relevant=false` metadata as the fact. The code's own replay comment warns that first-entry unordered-map assimilation can learn appraisal metadata or a different fact; this newly emitted event still takes that path.

This is not a claim that every current build will select the wrong entry on every run. The defect is that the event producer does not satisfy the explicit payload contract and replay semantics are not deterministic by schema across implementations, insertion layouts or persisted/reloaded maps.

Source references:
- [`event.hpp`](https://github.com/methaneex-oss/MethaneX/blob/c1da222e6c94aeb3f2ad000392c21fe4fc81ab25/core/cpp/include/jarvis/core/event.hpp#L11-L12), blob `a31db633e8181378fcec0a20c5958c0065d430ee`.
- [`brain_action_execution.cpp`](https://github.com/methaneex-oss/MethaneX/blob/c1da222e6c94aeb3f2ad000392c21fe4fc81ab25/core/cpp/src/brain_action_execution.cpp#L157-L166), blob `3b66bafb438cd28790e6f25611b96c86f1eff05c`.
- [`brain.cpp`](https://github.com/methaneex-oss/MethaneX/blob/c1da222e6c94aeb3f2ad000392c21fe4fc81ab25/core/cpp/src/brain.cpp#L620-L655), blob `dec9e5442b3ca4b81a7879855c6146b2619934cc`.

**Finding P2-I-026 — The donor emits a new action-reliability learning event without the explicit evidence payload required to avoid the legacy unordered-map replay fallback.** The fallback can assimilate metadata instead of the intended reliability fact. Before acceptance, the event producer must emit explicit typed evidence fields, metadata must never be eligible as a fact, and tests must prove identical replay results across serialization/restart and unordered-map iteration variation.

### 20.2 The runtime submits a second, differently typed value under the same evidence key

There are two action-feedback producers:

1. `Brain::execute_action` appends its internal `learning` event with `action_executor.<name>` mapped to a **double reliability** value and source `action_executor` (subject to the fallback issue in §20.1).
2. After execution, `CognitiveRuntime::execute_actions` calls `evidence_for_action`, which creates `Evidence` with the same key `action_executor.<name>`, source `action.<name>`, and value `result.reason` — a **string**. `Brain::learn` persists this second event using explicit `evidence_key`/`evidence_value`.

The Brain's belief projection stores one current `Belief` per key. When a later learning event supplies a different value for an existing key, replay replaces the current value and marks the belief disputed. Therefore, when the first event has assimilated the numeric reliability fact, the runtime's later string-valued reason event collides with it under the same key and changes the belief's type/value. The knowledge evidence also carries different sources, but that does not remove the single-key collision in `beliefs_`.

The runtime integration suite verifies consequence prediction, strategy changes, context isolation and restart behavior, but it does not assert the type/value/disputed state of `action_executor.<name>` after these two feedback events. The exact-HEAD 71/71 CI pass therefore does not close this schema defect.

Source references:
- [`cognitive_runtime.cpp`](https://github.com/methaneex-oss/MethaneX/blob/c1da222e6c94aeb3f2ad000392c21fe4fc81ab25/core/cpp/src/cognitive_runtime.cpp#L43-L55), blob `cf00acb6abd52308343f3a0e7016e6173b945603`.
- [`cognitive_runtime.cpp`](https://github.com/methaneex-oss/MethaneX/blob/c1da222e6c94aeb3f2ad000392c21fe4fc81ab25/core/cpp/src/cognitive_runtime.cpp#L205-L212), same blob.
- [`brain.cpp`](https://github.com/methaneex-oss/MethaneX/blob/c1da222e6c94aeb3f2ad000392c21fe4fc81ab25/core/cpp/src/brain.cpp#L676-L684), blob `dec9e5442b3ca4b81a7879855c6146b2619934cc`.
- [`brain.cpp`](https://github.com/methaneex-oss/MethaneX/blob/c1da222e6c94aeb3f2ad000392c21fe4fc81ab25/core/cpp/src/brain.cpp#L791-L818), same blob.

**Finding P2-I-027 — The internal action-reliability event and runtime status/reason feedback reuse one evidence key with incompatible value types (numeric reliability versus string reason).** The one-value-per-key belief projection can become disputed and change type. Define separate typed keys/contracts for reliability and execution status/reason, or make the event semantics explicitly multi-valued; then test the post-action belief and replayed state.

### 20.3 The runtime can reject secondary action feedback while the caller discards the result

`submit_feedback` rejects a feedback item when the runtime is stopped/stopping, feedback capacity is zero, or the bounded feedback queue is full. It increments `feedback_rejected` and returns `false`. The action-execution loop invokes it with an explicit `(void)` cast, discarding that result.

Because `execute_actions` runs synchronously on the same worker that drains the feedback queue, feedback queued by earlier planned steps cannot be processed until the current `execute_actions` call returns. A multi-step plan whose non-rejected actions exceed available queue capacity, or concurrent external feedback that fills the queue, can therefore cause secondary status/reason evidence to be rejected while action execution continues. The authoritative action-outcome event and direct observed-consequence learning are already handled inside `Brain::execute_action`; the potential loss concerns the additional runtime evidence record, not automatic loss of the persisted consequence event.

Source references:
- [`cognitive_runtime.cpp`](https://github.com/methaneex-oss/MethaneX/blob/c1da222e6c94aeb3f2ad000392c21fe4fc81ab25/core/cpp/src/cognitive_runtime.cpp#L86-L125), blob `cf00acb6abd52308343f3a0e7016e6173b945603`.
- [`cognitive_runtime.cpp`](https://github.com/methaneex-oss/MethaneX/blob/c1da222e6c94aeb3f2ad000392c21fe4fc81ab25/core/cpp/src/cognitive_runtime.cpp#L155-L223), same blob.

**Finding P2-I-028 — The runtime action loop discards the result of bounded secondary-feedback submission.** Queue saturation can silently omit the additional status/reason evidence from the action result's perspective. Required proof includes a multi-step plan exceeding feedback capacity, concurrent feedback saturation, visible per-action rejection handling and confirmation that the primary action-outcome record remains intact.

### 20.4 Required correction evidence before donor acceptance

1. Give every newly generated learning event an explicit, typed `evidence_key` and `evidence_value`; reserve unordered-map fallback for genuinely legacy journal records and exclude all appraisal/control metadata.
2. Separate executor reliability from status/reason facts at the evidence-key and schema level.
3. Test that one action produces the intended distinct facts, with no accidental metadata belief and no cross-type overwrite; verify identical results after restart/replay.
4. Exercise feedback-queue capacity zero, capacity one, full queue, multi-step plans and concurrent producer saturation. Rejected secondary evidence must be visible and handled according to an explicit loss/retry policy.
5. Preserve the existing no-consequence-observation invariant: verified execution without observed environmental consequence must not create a developmental utility preference.

**Status remains:** Phase 2 IN PROGRESS. Gate A NOT CLEARED. No implementation baseline selected, no donor approved, and no implementation authorization implied.

---

## 21. Additional self-review batch — action execution ambiguity and cognitive-persistence acknowledgement

**Audit date:** 2026-11-05  
**Main baseline:** `1273ddbcd0087d189e01388ded2d362fb1e058d2`  
**Donor baseline:** PR #97 HEAD `c1da222e6c94aeb3f2ad000392c21fe4fc81ab25`  
**Scope:** Independent second-pass inspection of the shared ActionExecutor contract, donor Brain action-outcome persistence, runtime reporting and registered action tests. Documentation only; no runtime source, tests, build configuration or dependencies changed.

### 21.1 Execution verification and cognitive persistence are separate success conditions, but the result type reports only the former

Exact donor source identities:
- `core/cpp/src/brain_action_execution.cpp` — `3b66bafb438cd28790e6f25611b96c86f1eff05c`.
- `core/cpp/include/jarvis/core/action_execution.hpp` — `04c73d02bdd4e1154be142dfeb024fc07ad432f8`.
- `core/cpp/src/memory.cpp` — `ab42bba1d32d6f48d091787491c72294a4a55bb5`.
- `core/cpp/src/cognitive_runtime.cpp` — `cf00acb6abd52308343f3a0e7016e6173b945603`.

The donor `Brain::execute_action` obtains an `ActionExecutionResult` from `ActionExecutor::run`. It then appends the authoritative `action_outcome` event. The local `outcome_persisted` flag becomes true only when `Memory::append` returns a nonzero sequence. Replay, consequence-linked affective learning, capability-learning append and subsequent prediction resolution are gated by that persistence result.

`Memory::append` returns zero when its `persist(event)` operation fails. The inspected persistence implementation can fail while creating the parent directory, opening the journal, writing/flushing the record or restoring the original file size after a failed write.

However, `outcome_persisted` is local to `Brain::execute_action`; it is not copied into `ActionExecutionResult`, and the result type has no separate journal/learning-persistence status. The method returns the executor result even when the authoritative action-outcome append failed. If the action was physically executed and verified and the consequence observer returned a value, the caller can therefore receive a result that still says `verified`, `executed` and `outcome.observed`, while the Brain did not persist or replay that outcome. The pre-execution consequence prediction is left unresolved because resolution is conditional on `outcome_persisted`.

The donor runtime increments its action-success metric based on `execution.status == verified`; it does not receive the local persistence flag. Its later secondary status/reason feedback is a separate event and cannot reconstruct the missing observed consequence. Thus operational execution success and journal acquisition are currently indistinguishable in the returned result/metric surface.

**Finding P2-I-029 — The donor action API can report verified execution without reporting failure to persist the authoritative cognitive outcome.** The source does not establish that a verified action's observed consequence was durably acquired. This is a persistence-acknowledgement and caller-observability gap, not proof that a write failure occurred in the cited CI runs.

Required proof/correction before donor acceptance:
1. Expose executor status and cognitive-record persistence status as separate result fields; do not overload `verified` to imply learning persistence.
2. Surface partial persistence explicitly when the action outcome is committed but a derived affective/capability event is not.
3. Define caller behavior when execution succeeded but the authoritative outcome record did not persist; avoid blind re-execution of a possibly completed external action.
4. Add deterministic append-failure injection at the authoritative action-outcome append and each derived-event append; verify returned status, unresolved prediction state, restart/replay state and retry/idempotency behavior.
5. Ensure runtime metrics and published cycle results expose the distinction.

### 21.2 The shared executor contract cannot represent ambiguous partial side effects from a failed or throwing callback

The ActionExecutor implementation exists on both inspected baselines:
- Main `core/cpp/src/action_execution.cpp` — blob `c2f8653eb755fa2790a88e49bc8b0b9c3077e439`.
- Donor `core/cpp/src/action_execution.cpp` — blob `af5bed6cec9ed1309b24ed3d50241fb4c0d33bff`.

Both versions accept an execution callback returning only `bool`. If the callback throws, or returns `false`, the executor immediately returns `failed` before setting `result.executed=true`. In the donor version this also bypasses the later consequence-observer block, which runs only when `result.executed` is true. The rollback callback is reached only after a successful callback has set `executed=true` and the later verification stage fails or is unavailable. The donor's rollback result is represented by a boolean; no independent rollback-verification callback exists in this request/result contract.

This behavior is safe only if the adapter contract guarantees that a false return or exception means **no external side effect occurred**. The inspected request/header does not state that guarantee, and the result type has no representation for “execution may have partially taken effect.” A real adapter can encounter a timeout, transport disconnect or exception after the external system accepted part or all of a command. The current API cannot distinguish that ambiguous state from a clean no-effect failure, cannot request/verify compensation on that path, and cannot ask the consequence observer to determine what actually happened.

This is an interface/failure-semantics gap; the source does not prove that any deployed adapter currently violates a no-side-effect-on-false convention.

Test coverage inspected:
- `core/cpp/tests/action_execution_phase7_suite.cpp` — blob `db11ac95d26a97b01dfeb67cfb85194dc284ffb8`: tests a false-return callback with no side effect and a successful rollback after verification failure. It does not test callback exception after partial effect, rollback false/throw, or rollback verification.
- `core/cpp/tests/cognitive_runtime_suite.cpp` — blob `361cba84a6fc6e07e31d14b5fa618c3f0a7848fa`: tests a false-return callback and worker continuity; the callback simply returns false and does not model an external partial effect.
- `core/cpp/tests/brain_action_consequence_integration_suite.cpp` — blob `7616082579d53e3579cae8e87895bdb3dadba66f`: tests consequence observation after execution succeeds but verification fails. This is useful evidence that verification failure and environmental consequence are distinct; it does not cover executor ambiguity before `executed=true`.

**Finding P2-I-030 — The shared ActionExecutor API has no explicit partial-effect/unknown-execution state, and its false/exception path bypasses compensation and consequence observation.** This is a contract ambiguity affecting both main and donor executor primitives. It is not evidence that an external side effect occurred in any tested scenario.

Required proof/correction:
1. Specify whether a false/throwing adapter result is guaranteed to mean “no side effect”; if that guarantee cannot be enforced, replace the binary result with a structured execution disposition that can represent not-started, completed, failed-before-effect and effect-unknown/partial.
2. Define when rollback is permitted/required and how rollback completion is independently verified.
3. Preserve the ability to observe and reconcile external consequences when execution status is ambiguous, without inventing a neutral or absent outcome.
4. Add tests for false-before-effect, false-after-partial-effect, throw-before-effect, throw-after-partial-effect, rollback false, rollback exception, rollback verification failure and process restart after each boundary.
5. Keep authorization rejection distinct from execution failure and from uncertain external completion.

**Line-level source anchors for independent review:**
- [Donor Brain outcome-persistence flag and authoritative append](https://github.com/methaneex-oss/MethaneX/blob/c1da222e6c94aeb3f2ad000392c21fe4fc81ab25/core/cpp/src/brain_action_execution.cpp#L60-L120), blob `3b66bafb438cd28790e6f25611b96c86f1eff05c`.
- [Donor prediction resolution gated by outcome persistence and result return](https://github.com/methaneex-oss/MethaneX/blob/c1da222e6c94aeb3f2ad000392c21fe4fc81ab25/core/cpp/src/brain_action_execution.cpp#L175-L188), same blob.
- [ActionExecutionResult fields](https://github.com/methaneex-oss/MethaneX/blob/c1da222e6c94aeb3f2ad000392c21fe4fc81ab25/core/cpp/include/jarvis/core/action_execution.hpp#L35-L58), blob `04c73d02bdd4e1154be142dfeb024fc07ad432f8`.
- [Memory append failure return and journal persistence](https://github.com/methaneex-oss/MethaneX/blob/c1da222e6c94aeb3f2ad000392c21fe4fc81ab25/core/cpp/src/memory.cpp#L34-L35) and [persist failure path](https://github.com/methaneex-oss/MethaneX/blob/c1da222e6c94aeb3f2ad000392c21fe4fc81ab25/core/cpp/src/memory.cpp#L135-L136), blob `ab42bba1d32d6f48d091787491c72294a4a55bb5`.
- [Runtime action-success metric and discarded secondary feedback result](https://github.com/methaneex-oss/MethaneX/blob/c1da222e6c94aeb3f2ad000392c21fe4fc81ab25/core/cpp/src/cognitive_runtime.cpp#L200-L212), blob `cf00acb6abd52308343f3a0e7016e6173b945603`.
- [Donor executor false/exception and rollback/observer branches](https://github.com/methaneex-oss/MethaneX/blob/c1da222e6c94aeb3f2ad000392c21fe4fc81ab25/core/cpp/src/action_execution.cpp#L20-L95), blob `af5bed6cec9ed1309b24ed3d50241fb4c0d33bff`.
- [Main executor false/exception and rollback branches](https://github.com/methaneex-oss/MethaneX/blob/1273ddbcd0087d189e01388ded2d362fb1e058d2/core/cpp/src/action_execution.cpp#L18-L78), blob `c2f8653eb755fa2790a88e49bc8b0b9c3077e439`.
- [Clean false-return and verification-failure rollback tests](https://github.com/methaneex-oss/MethaneX/blob/c1da222e6c94aeb3f2ad000392c21fe4fc81ab25/core/cpp/tests/action_execution_phase7_suite.cpp#L46-L80), blob `db11ac95d26a97b01dfeb67cfb85194dc284ffb8`.
- [Runtime false-return test](https://github.com/methaneex-oss/MethaneX/blob/c1da222e6c94aeb3f2ad000392c21fe4fc81ab25/core/cpp/tests/cognitive_runtime_suite.cpp#L200-L220), blob `361cba84a6fc6e07e31d14b5fa618c3f0a7848fa`.
- [Observed consequence despite verification failure](https://github.com/methaneex-oss/MethaneX/blob/c1da222e6c94aeb3f2ad000392c21fe4fc81ab25/core/cpp/tests/brain_action_consequence_integration_suite.cpp#L197-L228), blob `7616082579d53e3579cae8e87895bdb3dadba66f`.

### 21.3 Self-review of findings P2-I-026 through P2-I-030

The second-pass review checked the findings against the exact donor/main source blobs and the selected registered tests:

- **P2-I-026:** confirmed. The new donor reliability event lacks the explicit evidence payload, and the legacy unordered-map fallback does not exclude `affective_relevant`.
- **P2-I-027:** confirmed with its stated condition. The internal reliability fact and runtime status/reason event use the same key with different Scalar alternatives; the Brain belief projection is keyed by that string.
- **P2-I-028:** confirmed. Action execution submits secondary feedback synchronously from the worker that later drains the same queue; queue rejection is counted but the per-action submit result is discarded.
- **P2-I-029:** confirmed. The persistence-success flag is local and absent from the returned result/metrics, while the append return value gates replay and prediction resolution.
- **P2-I-030:** confirmed as a contract gap, not an observed production incident. The callback contract does not document a no-side-effect guarantee for false/exception results; the tests only exercise clean false-return and verification-failure rollback paths.

No source changes were made to resolve these findings because Phase 2 remains a documentation/investigation stage and implementation is not authorized. The findings are not Gate A clearance or a donor rejection decision; they are concrete requirements for the later independent review and any separately authorized correction work.

**Status remains:** Phase 2 IN PROGRESS. Gate A NOT CLEARED. No implementation baseline selected, no donor approved, and no implementation authorization implied.

---

## 22. Additional source-tracing batch — three-seed DLT-002 artifact review and revision-drift reconciliation

**Audit date:** 2026-11-05  
**Workflow:** [JARVIS DLT-002 Multi-Seed Learning Sweep, run #8](https://github.com/methaneex-oss/MethaneX/actions/runs/40565468650), ID `40565468650`  
**Run commit:** `82c49a75bd30de2962879f044776f4bf2391970a`  
**Current donor HEAD:** `c1da222e6c94aeb3f2ad000392c21fe4fc81ab25`  
**Scope:** Downloaded and independently parsed all three preserved seed artifacts; recomputed episode and phase metrics from the raw CSVs; checked the workflow and DLT executable against the exact run commit; compared the run commit's relevant source files with current PR #97 HEAD. This was artifact/source review, not a rerun.

### 22.1 Run identity and preserved artifacts

The GitHub run record establishes:
- Workflow: `JARVIS DLT-002 Multi-Seed Learning Sweep`.
- Run number: 8; run ID: `40565468650`.
- Event: `push`; branch: `feat/jarvis-affective-state`.
- Exact run commit: `82c49a75bd30de2962879f044776f4bf2391970a`.
- Run conclusion: success; all three matrix jobs completed successfully.
- Each matrix job used a 10-minute trial and one of the three configured seeds: `20261026`, `20261027`, `20261028`.

All three artifacts were downloaded and inspected, including their metadata, summaries, episode CSVs, checkpoint CSVs, trial logs and preserved Brain journals:

| Seed | Artifact ID | SHA-256 | Episodes | Optimal selections | Fixed-policy best | Learner delta |
|---|---:|---|---:|---:|---:|---:|
| 20261026 | [12764655498](https://github.com/methaneex-oss/MethaneX/actions/runs/40565468650/artifacts/12764655498) | `d189293bb8b2d552288caea1e03798436ec335e68a9b0e9a6b6d262be6c9263a` | 586 | 569/586 (97.1%) | 293/586 (50.0%) | +47.1 pp |
| 20261027 | [12763543000](https://github.com/methaneex-oss/MethaneX/actions/runs/40565468650/artifacts/12763543000) | `af42bcb1105bc884c6fba94c17097545aa16fe0e3aacbcbf0315fb9d0e6afef0` | 590 | 557/590 (94.4%) | 296/590 (50.2%) | +44.2 pp |
| 20261028 | [12763204259](https://github.com/methaneex-oss/MethaneX/actions/runs/40565468650/artifacts/12763204259) | `ae93f0cec02f0896a4e8ec96f8eda2dcb772521b5888916697f30622434b7ef2` | 589 | 556/589 (94.4%) | 295/589 (50.1%) | +44.3 pp |

Recomputation from the raw episode CSVs gives **1,682 optimal selections from 1,765 episodes (95.30%)**. The sum of the three per-seed best fixed-action baselines is 884/1,765 (50.08%), giving a descriptive aggregate difference of **+45.22 percentage points**. This is a weighted aggregation of the three runs, not a separate fourth experiment.

### 22.2 Phase-level results and transfer probe

Recomputed from the raw episode CSVs:

| Phase | Optimal selections | Episodes | Accuracy |
|---|---:|---:|---:|
| clear-baseline | 280 | 300 | 93.33% |
| flooded | 286 | 297 | 96.30% |
| tunnel | 279 | 295 | 94.58% |
| clear-reversal | 276 | 294 | 93.88% |
| generalization-probe | 289 | 291 | 99.31% |
| flooded-reversal | 272 | 288 | 94.44% |

Each seed's **first decision** in the unseen `navigation/canyon` context was optimal before any canyon outcome feedback: 3/3 across the three independent seeds. The first ten decisions in that context were 29/30 optimal, but those ten include feedback from earlier decisions; they are not ten feedback-free transfer observations.

The final checkpoint in each artifact reports zero unresolved action-consequence forecasts. It also reports 1,429–1,439 unresolved *other* predictions. The executable deliberately distinguishes these categories; the result must not be summarized as “all predictions resolved.”

### 22.3 What the environment did and did not reveal

The exact run-revision [executable](https://github.com/methaneex-oss/MethaneX/blob/82c49a75bd30de2962879f044776f4bf2391970a/core/cpp/tests/dlt_002_long_run.cpp) has blob `cbd80951c2f331fa4893c1805fff45a4035d5d24`. The [workflow](https://github.com/methaneex-oss/MethaneX/blob/82c49a75bd30de2962879f044776f4bf2391970a/.github/workflows/jarvis-learning-seed-sweep.yml) has blob `f40a859a9b6b4f8138cd14df9fa09ad362f3515c`.

Source inspection confirms this is a meaningful but constrained experiment:
- The environment randomizes the alpha-to-action mapping independently per seed; beta maps to the opposite action.
- The latent `route_condition` is removed by the observation filter before the Brain receives the observation.
- The Brain is still explicitly given context labels such as `navigation/clear`, `navigation/flooded`, `navigation/tunnel` and `navigation/canyon`.
- Outcomes have 20% noise.
- The six phases include context changes, reversals and an unseen canyon transfer probe.
- The harness evaluates two candidate actions, requires exactly one selected/executed action per episode, and configures planning horizon 1.
- The expected action and latent condition are evaluation labels used to score behavior; they are not supplied as Brain observations.
- The comparison policy is the better of two fixed actions over the full scored run. The workflow explicitly says this is **not** a matched Brain with learning disabled.

This supports evidence of rapid, repeatable adaptation in a randomized, noisy, partially observed, context-labelled two-action task. It does not isolate the causal contribution of the developmental-learning mechanism from every other Brain subsystem, establish a matched learning-ablation effect, or demonstrate broad open-ended goal formation and general intelligence.

### 22.4 Exact run commit is an ancestor, but not the current integrated donor revision

[GitHub's commit comparison](https://github.com/methaneex-oss/MethaneX/compare/82c49a75bd30de2962879f044776f4bf2391970a...c1da222e6c94aeb3f2ad000392c21fe4fc81ab25) reports that current donor HEAD is 18 commits ahead of the run commit and has no commits behind it; `82c49a75...` is the merge base/ancestor in this comparison.

The source identity comparison is material:

| File | Run-commit blob | Current PR #97 HEAD blob | Same? |
|---|---|---|---|
| `cognitive_runtime.cpp` | `cf00acb6abd52308343f3a0e7016e6173b945603` | same | Yes |
| `cognitive_cycle.cpp` | `2bff7eebe0905afbf2556833de189fee2da15b42` | `f191dd610d6cbe1621756c35e7c13af2054a7266` | No |
| `brain_action_execution.cpp` | `3b66bafb438cd28790e6f25611b96c86f1eff05c` | same | Yes |
| `brain.cpp` | `bbc3469e6463c40a8957fdb43590bf3a55b36379` | `dec9e5442b3ca4b81a7879855c6146b2619934cc` | No |
| `developmental_learning.cpp` | `bfe2db73a2722c421e6616d1caa20606f4f86098` | `dbf5f43271dfa0a3c57236e2faa82eb88d15490d` | No |
| `memory.cpp` | `bb2aee0eae27a667d64d7c32c2e2a8b613d35f16` | `ab42bba1d32d6f48d091787491c72294a4a55bb5` | No |
| `dlt_002_long_run.cpp` | `cbd80951c2f331fa4893c1805fff45a4035d5d24` | same | Yes |
| `jarvis-learning-seed-sweep.yml` | `f40a859a9b6b4f8138cd14df9fa09ad362f3515c` | same | Yes |

The experiment harness and workflow are byte-identical to current donor HEAD, and two central runtime/action files are also identical. However, the cycle, Brain replay, developmental-learning and Memory implementations changed in the 18 later commits. Therefore these three seed trials are **not exact-current-HEAD integrated Brain runs**. They are stronger multi-seed evidence than the single-seed historical 330-minute artifact in §19, but their whole-system revision must remain pinned to `82c49a75...`.

### 22.5 Verification and experimental limits

The seed-sweep workflow configures CMake and builds only `jarvis_dlt_002_long_run`; it does not run the full CTest suite, sanitizers, ThreadSanitizer or a separate-process persistence train/verify test before each trial. The artifact preserves a journal and metadata, but the long-running executable itself is a single-process trial. The separate exact-current-HEAD 71/71 native and ASan/UBSan CI evidence remains §18.3 and must not be attributed to this run.

The fixed-action baseline is useful as a simple lower bound under randomized mappings and reversals, but it is not a matched learner with developmental feedback disabled. The experiment also does not establish observer independence: the environment callback both supplies the consequence and determines the evaluation labels. The first unseen-context decision is genuinely pre-feedback for that context, while subsequent decisions receive canyon feedback and should not all be described as zero-shot transfer.

**Finding P2-I-031 — Three independent 10-minute DLT-002 trials at donor commit `82c49a75...` completed 1,765 episodes with 95.30% aggregate optimal-action selection and 3/3 optimal first decisions in the unseen context.** The result is meaningful repeatability evidence for the narrow synthetic task. It is not a matched learning-ablation result and not an exact-current-HEAD whole-system run because four material Brain/cycle/learning/persistence files changed in the 18 later commits.

**Updated interpretation:** PR #97 has (a) exact-current-HEAD Debug ASan/UBSan CI with assertion-enabled 71/71 tests, alongside a native Release job whose 71/71 CTest process successes do not evaluate `assert` expressions (§18.3 and §26), (b) a three-seed 30 aggregate trial-minute run at ancestor revision `82c49a75...` with a fixed-action baseline (§22), and (c) a 330-minute single-seed run at older revision `c6a8a00...` (§19). These are three distinct evidence classes and must not be combined into a claim that the current donor HEAD passed a 330-minute, multi-seed, full-suite, matched-control validation.

**Status remains:** Phase 2 IN PROGRESS. Gate A NOT CLEARED. No implementation baseline selected, no donor approved, and no implementation authorization implied.

---

## 23. Additional source-tracing batch — direct decision helpers versus the CognitiveRuntime production path

**Audit date:** 2026-11-05  
**Donor baseline:** PR #97 HEAD `c1da222e6c94aeb3f2ad000392c21fe4fc81ab25`  
**Scope:** Searched all 37 changed `core/cpp/src/*.cpp` donor production source files for calls to `choose_with_affect` and `choose_with_developmental_learning`; separately searched the 54 changed C++ test sources; then compared the helper implementations with the actual CognitiveCycle/CognitiveRuntime path. This is source/call-graph review only.

### 23.1 The public helper decision methods are not called by the inspected production source set

Exact implementation identities:
- `core/cpp/src/brain_restored_api.cpp` — `7155d4d9c8eef527836fb79bf901aa32ddbae38b`; defines `Brain::choose` and `Brain::choose_with_affect`.
- `core/cpp/src/brain_affective_planning.cpp` — `2a9406257c23f3a66a64071842be7d6448799406`; defines the two `Brain::choose_with_developmental_learning` overloads.
- `core/cpp/src/cognitive_cycle.cpp` — `f191dd610d6cbe1621756c35e7c13af2054a7266`.
- `core/cpp/src/cognitive_runtime.cpp` — `cf00acb6abd52308343f3a0e7016e6173b945603`.

A search across all 64 `.cpp` files under the donor branch's `core/cpp/src/` directory (37 changed by PR #97 and 27 unchanged) found the helper method definitions, but no production-source callsites for `Brain::choose_with_affect` or `Brain::choose_with_developmental_learning`. The 54 changed C++ test sources do call these methods directly, including:
- `affective_brain_decision_suite.cpp` — blob `9ff9c0480fa34fa4f5600e514af419b2bbc79765`;
- `affective_decision_learning_suite.cpp` — blob `920ddcbc8a422783bb8724093afd952cc885e6b6`;
- `affective_evidence_suite.cpp` — blob `c8a401cab1a29d57506f990043a1f82536fd9029`;
- `developmental_brain_integration_suite.cpp` — blob `760162dd6d1e669162e0bf22223a437491f5e262`;
- `brain_deep_suite.cpp` — blob `1314123ea3b524b24fd6693fc6fb4873b6c550d5`;
- `memory_learning_evolution_persistence_suite.cpp` — blob `98e6598f60912714234f2dfabfbe52fa5eb77044`.

This does not make the public APIs invalid or prove that external consumers never call them. It establishes that they are not the call path used by the donor's checked-in CognitiveRuntime implementation.

### 23.2 CognitiveRuntime uses a separate integrated CognitiveCycle decision path

The production path is:
1. `CognitiveRuntime::worker_loop` calls `cycle_.run(item.input)`.
2. After a completed cycle, `execute_actions` executes only the selected plan steps through `brain_.execute_action`.
3. `CognitiveCycle::run` directly reads stored and related developmental strategies, constructs learned candidate actions, and applies direct-evidence, related-context transfer, episodic fallback and exploration-pressure adjustments before planning.
4. It separately reads affective state and appraisal, derives affective uncertainty/tension/valence/arousal/stability, and places them into the planning and decision contexts.
5. The resulting decisions are action-assessed; their developmental context is preserved for the later action-outcome event.

This is a real integrated path, not merely a test helper:
- The cycle reads `brain_.developmental_strategies()` and `brain_.developmental_related_strategies()`.
- It applies direct-context strategy evidence and related-context transfer to candidate utility/expected value.
- If no strategy evidence exists, it can use observed episodic `action_outcome` memories, requiring a real observed consequence.
- It computes exploration pressure from attention, affective state, reflection, prediction and perception uncertainty.
- It then injects affective appraisal values into the `PlanningContext` and `DecisionContext`.

The donor `developmental_brain_integration_suite` explicitly tests both layers: it first checks the direct `choose_with_developmental_learning` helper, then creates a related goal and asserts that the normal `CognitiveCycle` decision path ranks the learned action above its competitor. Thus the helper-only assertions and the actual cycle integration assertions must be counted separately.

### 23.3 The helper and cycle implementations are not semantically identical

The two `choose_with_developmental_learning` overloads in `brain_affective_planning.cpp` use `apply_developmental_evidence` on a copy of the candidate actions, then build a one-step plan from the unmodified action list and pass affective fields into the decision engine. The separate `choose_with_affect` implementation in `brain_restored_api.cpp` applies a best exact/related strategy with a fixed 0.25 influence scale and builds its plan from developmentally weighted candidates.

The CognitiveCycle path uses a different evidence-aggregation procedure:
- exact-context evidence is weighted by strategy confidence;
- related-context transfer is weighted by similarity and strategy confidence;
- episodic outcomes are a fallback only when direct/related strategy evidence is absent;
- an exploration incentive is added based on uncertainty and absence of local evidence;
- the plan is built from the already adjusted candidate actions.

These are materially different scoring/dataflow paths. A result from a helper test cannot be assumed to equal the result from the runtime path. The cycle path has its own integration test coverage, but the two implementations create a maintenance and behavioral-consistency obligation.

**Finding P2-I-032 — The donor exposes affective/developmental decision helpers that are exercised directly by tests but are not called by the inspected production source path; CognitiveRuntime instead uses a separate CognitiveCycle implementation with different evidence aggregation and scoring.** The runtime has genuine affective/developmental integration, but helper-method test results must not be presented as if they were direct runtime-path results. The two decision paths require explicit ownership, semantic equivalence or intentional separation, and paired regression coverage.

### 23.4 Required proof before donor acceptance

1. Declare which decision path is the canonical production contract and whether the helper methods are supported public APIs, test utilities or alternate modes.
2. If both paths remain supported, define the intended semantic differences and prevent silent divergence in evidence weighting, transfer, exploration, affective modulation and planning.
3. Add paired tests that apply identical Brain state, candidate actions, goal/context and evidence to both paths and assert either equivalence or the documented difference.
4. Retain explicit CognitiveCycle/CognitiveRuntime tests for learned action ranking, context transfer, observed-consequence dependence and restart/replay; helper-only tests are insufficient.
5. Include the chosen path and its exact source/test/CI provenance in any later implementation-baseline review.

**Line-level source anchors:**
- [Helper affective/developmental decision implementations](https://github.com/methaneex-oss/MethaneX/blob/c1da222e6c94aeb3f2ad000392c21fe4fc81ab25/core/cpp/src/brain_affective_planning.cpp#L93-L185), blob `2a9406257c23f3a66a64071842be7d6448799406`.
- [Brain choose/choose_with_affect helper](https://github.com/methaneex-oss/MethaneX/blob/c1da222e6c94aeb3f2ad000392c21fe4fc81ab25/core/cpp/src/brain_restored_api.cpp#L217-L218), blob `7155d4d9c8eef527836fb79bf901aa32ddbae38b`.
- [CognitiveCycle developmental evidence and transfer path](https://github.com/methaneex-oss/MethaneX/blob/c1da222e6c94aeb3f2ad000392c21fe4fc81ab25/core/cpp/src/cognitive_cycle.cpp#L535-L681), blob `f191dd610d6cbe1621756c35e7c13af2054a7266`.
- [CognitiveCycle affective decision context](https://github.com/methaneex-oss/MethaneX/blob/c1da222e6c94aeb3f2ad000392c21fe4fc81ab25/core/cpp/src/cognitive_cycle.cpp#L683-L735), same blob.
- [CognitiveRuntime invokes the cycle and selected-action execution](https://github.com/methaneex-oss/MethaneX/blob/c1da222e6c94aeb3f2ad000392c21fe4fc81ab25/core/cpp/src/cognitive_runtime.cpp#L155-L223), blob `cf00acb6abd52308343f3a0e7016e6173b945603`.
- [Test of direct helper and normal CognitiveCycle integration](https://github.com/methaneex-oss/MethaneX/blob/c1da222e6c94aeb3f2ad000392c21fe4fc81ab25/core/cpp/tests/developmental_brain_integration_suite.cpp#L50-L175), blob `760162dd6d1e669162e0bf22223a437491f5e262`.

### 23.5 Self-review

The callsite search covered all 64 donor `core/cpp/src/*.cpp` files (37 PR #97 changes and 27 unchanged source files) and all 54 changed donor C++ test sources listed by PR #97. The conclusion is deliberately limited to that inspected source set. The normal runtime path was separately traced through `CognitiveRuntime::worker_loop`, `CognitiveCycle::run` and `Brain::execute_action`; it was not inferred from method names or test labels.

No source/test/build changes were made. This finding does not erase the integrated cycle behavior or downgrade the existing exact-HEAD CI evidence; it narrows which tests exercise which public decision path.

**Status remains:** Phase 2 IN PROGRESS. Gate A NOT CLEARED. No implementation baseline selected, no donor approved, and no implementation authorization implied.

---

## 24. Additional source-tracing batch — evolution history projections, event ordering and compensation windows

**Audit date:** 2026-11-05  
**Donor baseline:** PR #97 HEAD `c1da222e6c94aeb3f2ad000392c21fe4fc81ab25`  
**Scope:** Traced the donor evolution evaluation/adoption/canary/rollback lifecycle across Brain wrappers, EvolutionController, EvolutionHistory, EvolutionAdoptionJournal, Memory events, replay and registered tests. No implementation or test changes were made.

### 24.1 EvolutionHistory and EvolutionAdoptionJournal are in-memory projections, not independent durable stores

Exact source identities:
- `core/cpp/src/evolution_history.cpp` — `e394042ba7fc6db85e4663722f735918aa1ce7fb`.
- `core/cpp/src/evolution_adoption_journal.cpp` — `d8df30a2902d3dac734fb1a571cbbecdd881b76f`.
- `core/cpp/src/evolution_controller.cpp` — `4e77ec2e5daa09a964132ca486b8c5ee1cebf2f5`.
- `core/cpp/src/brain_restored_api.cpp` — `7155d4d9c8eef527836fb79bf901aa32ddbae38b`.
- `core/cpp/src/brain.cpp` — `dec9e5442b3ca4b81a7879855c6146b2619934cc`.

`EvolutionHistory::append` validates record fields, de-duplicates by experiment/key/action, assigns an in-memory sequence and appends to a vector. It performs no filesystem or journal write. `EvolutionAdoptionJournal` similarly owns an in-memory map of staged/pending/adopted/rolled-back records and state-transition methods; it has no independent serialization or storage path.

The durable source of truth in the Brain-mediated path is the Memory event journal. Brain replay reconstructs the controller projections:
- `evolution_evaluated` invokes `EvolutionController::replay_evaluation`, rebuilding the staged adoption record and evaluated history projection.
- `evolution_adopt` validates/reconstructs the experiment, applies the proposal if not already adopted/rolled back, then calls `replay_adoption` and appends the adopted history projection.
- `evolution_canary` replays the canary observation into controller-local state.
- `evolution_rollback` applies the rollback and updates the adoption journal/history projection when the experiment identity and current state match.

The controller's comments and validation describe evaluation history as durable. The actual implementation checks the in-memory `EvolutionHistory` projection, which is expected to have been reconstructed from the durable Brain journal. The distinction matters: the projection is not a second durable log and cannot independently recover if its owning Brain journal is missing or incomplete.

### 24.2 The Brain lifecycle uses different persistence/mutation ordering at each stage

| Operation | Ordering observed in Brain wrapper | Failure/recovery implication |
|---|---|---|
| Record evaluation | Validate → append `evolution_evaluated` to Memory → update controller journal/history projections | If projection update returns false after Memory append, caller receives false although the durable event remains; replay can reconstruct the projection. |
| Adopt experiment | Validate → controller mutates model and marks adoption journal Adopted → append `evolution_adopt` to Memory → update history projection | If Memory append fails, Brain calls compensation to restore model/journal. The compensation return value is currently discarded by the caller. |
| Observe canary | Preview → append `evolution_canary` → update canary state → if rollback required, append `evolution_rollback` → perform controller rollback | If controller rollback fails after the rollback event append, the call returns a failure reason while the durable rollback event remains for a later replay attempt. |
| Manual rollback | Append `evolution_rollback` → perform controller/model rollback → update Brain state | If controller rollback fails after event append, the call returns false but the durable event remains; replay may later apply it if its experiment/state checks pass. |

The adoption compensation method checks that the controller journal is Adopted, restores the model's previous value, then moves the journal back to Pending. The Brain wrapper calls it when the `evolution_adopt` Memory append returns zero, but does not check or surface the compensation return value. This is a real observability gap if compensation ever fails; source review does not establish that the compensation failed in any run.

The canary/manual rollback paths use event-first ordering. Their intended recovery model appears to be “durable rollback request, then apply projection/model transition”; a returned failure does not necessarily mean that no rollback event was durably recorded. That caller contract is not expressed as a distinct persisted/pending/failed status.

### 24.3 Existing tests prove normal replay and in-memory state transitions, not persistence-failure atomicity

Inspected tests:
- `core/cpp/tests/evolution_adoption_journal_suite.cpp` — blob `fc8ae17bb837831fef7bf69873ec0e5243e2bc22`: exercises pending/adopted/rolled-back transitions, idempotent operations, restore-pending/restore-adopted compensation helpers and normal controller rollback. It does not inject a failed Memory append or force a compensation helper to fail.
- `core/cpp/tests/evolution_canary_controller_suite.cpp` — blob `80cac5df347987a9074e1ced43202f8759f797d7`: exercises canary decisions, adoption, rollback and replay idempotence in memory.
- `core/cpp/tests/evolution_brain_integration_suite.cpp` — blob `59d7dd68c42eea18d488d8e5e6aa9f7a9a327ded`: exercises Brain-level evaluation/adoption/manual rollback/canary rollback and reconstruction from the Memory journal, including rejection of unversioned legacy adoption/rollback events.

The tests establish useful normal-path and restart/replay behavior. They do not demonstrate crash/failure atomicity at each boundary between Memory append, EvolutionModel mutation, AdoptionJournal transition and EvolutionHistory projection update. In particular, the journal unit tests call compensation methods successfully; that is not the same as injecting a failed compensation into the Brain lifecycle.

### 24.4 Finding and required evidence

**Finding P2-I-033 — EvolutionHistory and EvolutionAdoptionJournal are volatile projections reconstructed from Brain Memory events; the Brain lifecycle has mixed event-first and mutation-first ordering, and the adoption compensation result is discarded.** This is not evidence that replay is broken or that compensation has failed. It means the real transaction/recovery boundary is the Brain Memory event plus the model/controller projections, not the two in-memory helper stores considered as independent durable logs.

Required proof before donor acceptance:
1. Document Memory events as the authoritative durable lifecycle records and explicitly classify EvolutionHistory/AdoptionJournal as rebuildable projections.
2. Give callers a structured result distinguishing event persisted, model/controller transition applied, compensation completed and replay-required/pending states.
3. Do not discard the result of `compensate_adoption_for_brain`; expose or durably record compensation failure.
4. Add deterministic fault injection at each Memory append boundary and at each projection transition; verify live state, returned status, durable event sequence and restart reconstruction.
5. Test retry/idempotency when an event is persisted but the in-memory transition reports failure, including same-process retry and process restart.
6. Verify that canary rollback and manual rollback return values accurately describe whether the rollback event was persisted and whether the model actually reached baseline.

**Line-level source anchors:**
- [EvolutionHistory is an in-memory vector with validation/deduplication](https://github.com/methaneex-oss/MethaneX/blob/c1da222e6c94aeb3f2ad000392c21fe4fc81ab25/core/cpp/src/evolution_history.cpp#L7-L24), blob `e394042ba7fc6db85e4663722f735918aa1ce7fb`.
- [EvolutionAdoptionJournal state transitions](https://github.com/methaneex-oss/MethaneX/blob/c1da222e6c94aeb3f2ad000392c21fe4fc81ab25/core/cpp/src/evolution_adoption_journal.cpp#L5-L115), blob `d8df30a2902d3dac734fb1a571cbbecdd881b76f`.
- [Controller adoption compensation and rollback boundaries](https://github.com/methaneex-oss/MethaneX/blob/c1da222e6c94aeb3f2ad000392c21fe4fc81ab25/core/cpp/src/evolution_controller.cpp#L113-L264), blob `4e77ec2e5daa09a964132ca486b8c5ee1cebf2f5`.
- [Brain evaluation/adoption/canary/rollback event ordering](https://github.com/methaneex-oss/MethaneX/blob/c1da222e6c94aeb3f2ad000392c21fe4fc81ab25/core/cpp/src/brain_restored_api.cpp#L256-L380), blob `7155d4d9c8eef527836fb79bf901aa32ddbae38b`.
- [Brain replay reconstructs evolution projections from durable events](https://github.com/methaneex-oss/MethaneX/blob/c1da222e6c94aeb3f2ad000392c21fe4fc81ab25/core/cpp/src/brain.cpp#L497-L610), blob `dec9e5442b3ca4b81a7879855c6146b2619934cc`.
- [Journal transition/compensation tests](https://github.com/methaneex-oss/MethaneX/blob/c1da222e6c94aeb3f2ad000392c21fe4fc81ab25/core/cpp/tests/evolution_adoption_journal_suite.cpp#L1-L108), blob `fc8ae17bb837831fef7bf69873ec0e5243e2bc22`.
- [Brain-level adoption/restart/canary tests](https://github.com/methaneex-oss/MethaneX/blob/c1da222e6c94aeb3f2ad000392c21fe4fc81ab25/core/cpp/tests/evolution_brain_integration_suite.cpp#L1-L298), blob `59d7dd68c42eea18d488d8e5e6aa9f7a9a327ded`.

**Status remains:** Phase 2 IN PROGRESS. Gate A NOT CLEARED. No implementation baseline selected, no donor approved, and no implementation authorization implied.

---

## 25. Independent self-review checklist — current Phase 2 working report

This checklist records the second-pass validation performed before handing this report to an independent reviewer. It is a report-quality check, not a substitute for the independent review itself.

### 25.1 Scope and provenance checks

- [x] Main source claims remain pinned to main commit `1273ddbcd0087d189e01388ded2d362fb1e058d2`; donor claims remain explicitly pinned to PR #97 HEAD `c1da222e6c94aeb3f2ad000392c21fe4fc81ab25`.
- [x] Accepted specification references remain pinned to PR #174 HEAD `0811a59e46bf934e32e794f90e4e7d18d4e2bd97`.
- [x] PR #97 donor code is not described as integrated into main.
- [x] PR #179 remains the working report branch, based on PR #178's governance branch; PR #180 remains a separate open/draft branch based on PR #174's specification branch.
- [x] All 20 distinct blob SHAs found in the PR #180 first-batch report are present in the PR #179 working report. Seven source identities specifically called out in the reconciliation section (six mechanism headers plus `cognitive_cycle.hpp`) are recorded.
- [x] The PR #180 branch-base difference and unresolved Git-history disposition are explicit. No merge/close action was performed.
- [x] The PR #173 original reviewer wording is not fabricated. The unavailable wording and the available correction record/review-submission status are explicitly distinguished.

### 25.2 Coverage and evidence checks

- [x] BM-01 through BM-12 have an explicit source-to-capability map and an evidence-backed status; the map does not infer capability from names or test filenames.
- [x] The original cross-mechanism finding sequence P2-I-001 through P2-I-033 is present with no missing numeric IDs; subsequent withdrawals and additions are reconciled in §35.
- [x] Donor action feedback, runtime decision path, memory/replay, goal progress, affective/developmental learning and evolution state ownership are distinguished from the main baseline.
- [x] The action outcome → affective-learning → capability-learning append sequence is described as separate event writes, not an atomic transaction.
- [x] EvolutionHistory and EvolutionAdoptionJournal are correctly classified as in-memory projections reconstructed from Brain Memory events, not separate durable stores.
- [x] The three-seed DLT-002 aggregate is recomputed from raw episode CSVs and pinned to ancestor commit `82c49a75...`; the source-file identity differences against current donor HEAD are recorded.
- [x] The older 330-minute DLT artifact, the three-seed ancestor run and the exact-current-HEAD CI runs are presented as separate evidence classes, not blended into a single validation claim.
- [x] The exact PR #97 HEAD native Release and Debug ASan/UBSan runs are verified from provider job logs: 71/71 test processes in each; the complete test CMake explicitly undefines `NDEBUG` for executable targets, so assertions remain active in Release and Debug. The separate Core Verification run is also identified.
- [x] The latest verified PR #179 branch build is run #1639 on synthetic merge commit `11546a265346826fc0c90e0e766ed8a403eb37f8`, combining report commit `99f48d52d1ea816d6f9a2138d976578bc5e33222` with governance base `39fe09dcf13496f5f0005ccf3f00739303e29f88`; it configured and built but had no CTest step.
- [x] The 64-file donor C++ production source callsite search and 54 changed C++ test-source search are scoped accurately; no claim is made about external consumers outside the repository.

### 25.3 Claim-strength and wording checks

- [x] Source-level findings are not presented as runtime-confirmed defects unless CI/artifact evidence actually establishes runtime behavior.
- [x] “No source found in the inspected path” is not converted into a repository-wide absence claim.
- [x] A public helper method's direct unit/integration test is not conflated with the canonical CognitiveRuntime path.
- [x] The DLT fixed-action baseline is not described as a matched Brain learning ablation.
- [x] The no-consequence-observation runtime control is not described as a no-learning control.
- [x] First-decision transfer in the unseen context is distinguished from later decisions that receive feedback.
- [x] Verified action execution is not equated with successful cognitive-outcome persistence.
- [x] Failed/throwing executor callbacks are described as an ambiguous partial-effect contract unless a no-side-effect guarantee is documented.
- [x] Evolution compensation and rollback failure paths are recorded as unverified failure boundaries, not asserted production incidents.
- [x] Existing C++ compiler and GitHub Actions deprecation warnings are not attributed to the Phase 2 documentation changes.

### 25.4 Remaining exit blockers

The report is intentionally **not** marked complete. Before Phase 2 can pass its exit criteria, the following still require closure:
1. Close the remaining BM-01/BM-02 production-entrypoint and provenance trace. P2-I-037 now establishes the donor C++ provider-failure behavior, but does not map every non-C++ or deployed acquisition caller or establish end-to-end provenance.
2. Resolve P2-I-037: expose specialized-provider failure/degraded-mode status as a first-class capability result while preserving the raw acquired experience and valid fallback; settle the `supports noexcept` contract and test provider recovery and failure observability.
3. Complete the test-by-test validity review of the selected donor suites, including observer independence, hidden assumptions, reward/context leakage, matched controls and generalization limits. Existing test registration and CI pass evidence do not replace this review.
4. Close the action execution/governance chain: P2-I-030's partial/unknown external-effect contract, P2-I-029's action-result persistence acknowledgement, P2-I-035's queued-feedback evidence/completion accounting, and P2-I-038's authorization-context lifecycle must be assessed together without conflating their distinct failure boundaries.
5. Resolve P2-I-038 at the actual host boundary: identify the executable host and grant issuer; prove either immutable bounded-session grants with cancellation/restart invalidation or a live refresh/revocation/version contract; verify fail-closed behavior immediately before external side effects. The repository-only audit did not identify the external host.
6. Complete deterministic failure injection and recovery verification for Memory append boundaries, multi-event action feedback (P2-I-023), queued-feedback evidence assimilation and completion-metric accounting (P2-I-035), the two-event `goal_progress`/`goal_complete` boundary (P2-I-036), evolution event ordering, compensation, and restart/retry equivalence. Source-derived failure paths are not runtime-reproduced until these tests execute.
7. Reconcile all remaining BM-11 coordination, invalidation, concurrency, interruption and recovery edges across language/runtime boundaries, including the distinction between cognitive intent, authorization denial, execution failure, unknown external effect and verified consequence.
8. Recover the original PR #173 F-02/F-03 reviewer document if verbatim wording is mandatory; the report records the current retrieval limit rather than inventing it. Preserve the corrected distinction: F-02 is experience-acquired candidate-goal formation; F-03 is SYS-08 computational-substrate boundary.
9. Obtain independent review of the completed source map and an explicit Project Director decision on any remaining PR #179/#180 duplicate disposition. Do not treat a draft report PR as accepted governance.
10. Keep Gate A NOT CLEARED until its own required provenance, compatibility, rollback, independent test and independent review conditions are satisfied. Phase 2 report completion and Gate A clearance are separate decisions.

**Self-review result:** no internal contradiction or unsupported completion claim was identified in this pass. The report remains a substantial but incomplete Phase 2 investigation. Its findings are ready for independent challenge; they are not approval to implement, merge donor code or select an implementation baseline.

**Status remains:** Phase 2 IN PROGRESS. Gate A NOT CLEARED. No implementation baseline selected, no donor approved, and no implementation authorization implied.


## 26. Additional verification audit — correction of the Release-assertion finding

**Audit date:** 2026-11-06  
**Donor baseline:** PR #97 HEAD `c1da222e6c94aeb3f2ad000392c21fe4fc81ab25`  
**Scope:** Re-opened the complete donor test CMake configuration after the prior audit raised P2-I-034. The previous audit inspected test registration but missed the assertion-enabling block at the end of the same file. This correction supersedes the previous §26.1 conclusion.

### 26.1 P2-I-034 is withdrawn — Release test targets explicitly undefine NDEBUG

The prior audit stated that Release-mode test executables compiled out their `assert(...)` expressions because no test-target override undefines `NDEBUG`. That statement was incorrect.

The complete file `core/cpp/tests/CMakeLists.txt` at donor HEAD has blob `cbfd1fde52fffa6eeac025da2b7ddcb5ab493261`. Its final block, lines 303–315, explicitly states that the executable suites use `assert()` and that assertions must remain enabled in Release. It obtains the directory's `BUILDSYSTEM_TARGETS`, iterates the executable targets, and applies:

- GNU/Clang: `-UNDEBUG`
- MSVC: `/UNDEBUG`

This target-specific undefinition is applied after the Release configuration's normal `NDEBUG` definition in the generated compile command ordering. Therefore the checked-in CMake configuration is designed to keep assertion expressions active for the test executables in Release as well as Debug.

The workflow's native job configures `CMAKE_BUILD_TYPE=Release`, and its exact-HEAD run reported 71/71 CTest processes passing. In light of the test-target override, that result must not be discounted on the basis of assertion elision. The separate Debug ASan/UBSan job also passed 71/71 and remains valid assertion-bearing sanitizer evidence.

**Disposition:** P2-I-034 is **withdrawn**. It is not an active donor finding and must not be used as a Gate A blocker. The earlier conclusion resulted from an incomplete inspection of `core/cpp/tests/CMakeLists.txt`; the complete-file recheck corrected it. No source defect is established by that earlier claim.

A residual test-design consideration remains: required setup and state-changing calls inside `assert(...)` are fragile if those test sources are compiled outside this CMake target configuration or under a different build system. That portability concern is not evidence that the repository's current CMake Release job elides those expressions, and it is not promoted to a separate finding in this audit.

### 26.2 Current interpretation of the CI evidence

- Exact donor HEAD `c1da222e6c94aeb3f2ad000392c21fe4fc81ab25`: native Release CTest 71/71 and Debug ASan/UBSan CTest 71/71, both successful.
- The Release test-target CMake override preserves assertions; the native result is valid registered-test execution evidence, subject to the normal limits of the test suite's coverage and validity.
- The Debug sanitizer result adds AddressSanitizer and UndefinedBehaviorSanitizer coverage. It does not provide ThreadSanitizer coverage or replace deterministic persistence/action failure injection.
- A previously inspected PR #179 workflow run was build-only and did not run CTest. That historical report-branch build result is not donor runtime/test evidence and should not be conflated with the donor's exact-HEAD CI.

### 26.3 Self-review and correction record

The correction was checked against the complete test CMake file, not a partial line range. The relevant blob SHA is recorded above. The test-target loop applies to executable targets in the test subdirectory, where the suite executables are declared. The prior report statement that no override existed is therefore explicitly superseded.

No donor production source, test source, workflow, or CMake file was modified. This was a review-record correction only. The other findings P2-I-001 through P2-I-033 are not changed by withdrawing P2-I-034; they remain subject to their own evidence and acceptance status.

**Status remains:** Phase 2 IN PROGRESS. Gate A NOT CLEARED. No implementation baseline selected, no donor approved, and no implementation authorization implied.


## 27. CI and trial-evidence correction — donor workflows were present and must be counted

This section corrects the overly narrow CI statement in §10.4. The earlier query used a PR-triggered commit-run wrapper and did not enumerate push/workflow-dispatch runs. A direct Actions-run listing for `feat/jarvis-affective-state` exposes successful donor-branch runs. The previous statement that donor CI remained unverified is therefore superseded.

### Exact donor HEAD CI

**Brain CI run #1595 — run ID `40788714686`**
- Event: `push`.
- Branch: `feat/jarvis-affective-state`.
- Exact checked-out HEAD: `c1da222e6c94aeb3f2ad000392c21fe4fc81ab25`.
- Run conclusion: success.
- Jobs: `native-brain` success; `sanitizer` success.
- Native job completed configure, build and CTest. The log reports **100% tests passed out of 71**, total CTest time 2.61 seconds.
- Sanitizer job completed configure, build and CTest with **100% tests passed out of 71**, total CTest time 13.00 seconds.
- Sanitizer configuration explicitly enabled AddressSanitizer and UndefinedBehaviorSanitizer.
- No artifacts were attached to this Brain CI run.

The exact HEAD is also PR #97's head, and the run metadata links it to PR #97. This is direct CI evidence for compilation and execution of the 71 registered CTest tests at the donor HEAD. It is not a substitute for inspecting the tests' validity, and it does not establish real-world deployment, untested behavior, long-duration robustness, or complete cognitive capability.

**JARVIS Core Verification run #1227 — run ID `40788714735`**
- Event: `push`, branch `feat/jarvis-affective-state`.
- Exact HEAD: `c1da222e6c94aeb3f2ad000392c21fe4fc81ab25`.
- Conclusion: success; job `cpp-core` success.
- This is additional CI evidence, but the specific test scope must be taken from its own job steps/log rather than inferred from the run name.

### DLT-002 multi-seed trial evidence — valid, but at an earlier donor revision

**JARVIS DLT-002 Multi-Seed Learning Sweep run #8 — run ID `40565468650`**
- Event: `push`, branch `feat/jarvis-affective-state`, PR #97 association.
- Exact HEAD: `82c49a75bd30de2962879f044776f4bf2391970a`.
- Conclusion: success.
- Three independent jobs completed successfully for seeds `20261026`, `20261027`, and `20261028`.
- Each job built the native C++ DLT-002 executable and ran a changing-environment trial for 10 minutes.
- Recorded completed episode counts: 586, 590 and 589 respectively.
- Each job summarized behavioral/prediction evidence and uploaded a raw-evidence artifact. Artifact IDs: `12764655498`, `12763543000`, and `12763204259`.

The trial commit is an ancestor of donor HEAD `c1da222e6c94aeb3f2ad000392c21fe4fc81ab25`, with 18 commits between it and HEAD. Therefore:
- This is real multi-seed runtime evidence for an earlier donor revision.
- It is not direct runtime evidence for the final donor HEAD.
- The later exact-HEAD 71-test CI includes the registered DLT-002 persistence train/verify tests, but does not rerun the 10-minute three-seed DLT-002 trial.
- Do not merge the earlier trial evidence and later CI evidence into a claim that the final donor HEAD passed the same long-duration experiment.

### DLT-002 protocol source inspection

The long-run harness `core/cpp/tests/dlt_002_long_run.cpp` constructs a partially observed, noisy environment:
- The latent-state/action mapping is randomized per seed inside the environment; it is explicitly documented as evaluation-only and not supplied to the Brain.
- Outcomes include 20% noise that contradicts the latent action/condition relationship.
- The protocol includes context-local learning, reversal of the original clear-context mapping, an unseen-context transfer probe, and a second reversal in a different context while visible cues remain unchanged.
- The Brain receives observations, context and available candidate actions; the harness checks that exactly one planned action is executed and that a real observed consequence is returned.
- It requires an issued action-consequence prediction and records prediction error/decision metrics separately from evaluation-only latent labels.
- The trial is a controlled simulation with a seeded world, not an unconstrained physical environment. Its results support performance in that protocol only.

The separate persistence fixture `core/cpp/tests/dlt_002_persistence.cpp` performs deterministic training using explicitly supplied action/consequence experiences, then verifies context-specific learned strategy signs, action selection, affective calibration, prediction resolution and replay after process restart. This is valuable persistence verification, but it is a controlled fixture with prescribed experience labels; it must not be described as the same evidence as the randomized long-run environment.

### Updated CI evidence classification

| Evidence | Exact revision | Result | What it supports | What it does not support |
|---|---|---|---|---|
| Brain CI native CTest | `c1da222e6c94aeb3f2ad000392c21fe4fc81ab25` | 71/71 pass | Build and registered test execution | Untested runtime behavior or capability completion |
| Brain CI ASan/UBSan CTest | `c1da222e6c94aeb3f2ad000392c21fe4fc81ab25` | 71/71 pass | Executed test paths did not trigger reported ASan/UBSan failures | Thread-race verification, all undefined behavior, production runtime |
| DLT-002 multi-seed sweep | `82c49a75bd30de2962879f044776f4bf2391970a` | 3/3 seeds completed | Ten-minute controlled changing-environment trials with raw artifacts | Same long-run result at final donor HEAD |
| DLT-002 train/verify CTest | `c1da222e6c94aeb3f2ad000392c21fe4fc81ab25` | Included in 71/71 CTest | Registered persistence train/verify fixture executed | Full long-run learning performance |

**CI evidence correction — coverage was under-reported in the previous batch.** Status: corrected; this is a review-record accuracy correction, not a source defect. The donor has exact-HEAD native and ASan/UBSan CI evidence, plus earlier multi-seed DLT-002 evidence. The evidence is stronger than previously recorded, but it still does not clear Gate A.

---

## 28. Runtime and persistence failure-path trace

The exact donor runtime path is now source-traced across:
`CognitiveRuntime::worker_loop` → `CognitiveCycle::run` → `CognitiveRuntime::execute_actions` → `Brain::execute_action` → `ActionExecutor::run` → `action_outcome` journal append/replay → separately appended `affective_learning` and `learning` events → prediction feedback resolution → later runtime feedback processing.

Relevant exact donor blobs:
- `cognitive_runtime.cpp`: `cf00acb6abd52308343f3a0e7016e6173b945603`.
- `brain_action_execution.cpp`: `3b66bafb438cd28790e6f25611b96c86f1eff05c`.
- `action_execution.cpp`: `af5bed6cec9ed1309b24ed3d50241fb4c0d33bff`.
- `memory.cpp`: `ab42bba1d32d6f48d091787491c72294a4a55bb5`.

### Verified execution ordering

1. The runtime worker prioritizes queued feedback over queued new cognitive inputs.
2. A completed cycle executes only actions present in the selected plan, in plan order; unselected candidate assessments are not executed.
3. Before external execution, Brain checks authorization and creates a context-keyed consequence prediction only if authorization succeeds and a consequence observer is configured.
4. The executor obtains execution/verification/rollback status and independently invokes the consequence observer when the action crossed the execution boundary. A failed verification/rollback status does not automatically erase an observed external consequence.
5. Brain appends the authoritative action outcome. Only after that append succeeds does it replay the action outcome and attempt separate affective-learning and capability-learning appends.
6. Prediction feedback is resolved only after releasing the Brain lock, and only if the action outcome persisted, the consequence was observed, and a prediction sequence exists.
7. The runtime later publishes the cycle result. The generic evidence feedback created from an action result is queued and processed by the same worker on a subsequent worker iteration.

### Failure-path limitation requiring explicit acceptance criteria

The action outcome, affective-learning event and capability-learning event are separate journal appends. A successful action-outcome append followed by a failed secondary append leaves a partial sequence in the journal (subject to the lower-level flush/rollback limitations described in P2-I-014). The current implementation checks each append result and avoids replaying a failed secondary event, but it does not make the three-event sequence atomic and does not expose a complete per-stage persistence outcome in `ActionExecutionResult`.

This is not evidence that the normal path is broken. It is a crash/I/O-failure recovery limitation. When the action-outcome append reports success, its event has been written and stream-flushed; the implementation does not establish stable-storage durability against power loss. One or both derived learning records may be absent after a later append failure. The current tests demonstrate normal replay and restart behavior, not every possible append-failure interleaving.

**Expanded detail — multi-record action learning atomicity (P2-I-023).**
- Severity: Medium (provisional; consequence depends on the required durability contract).
- Confidence: High for the separate-append behavior; Medium for operational impact absent an injected I/O-failure reproduction.
- Status: CONFIRMED as a limitation / UNRESOLVED as an acceptance blocker.
- Affected donor revision: `c1da222e6c94aeb3f2ad000392c21fe4fc81ab25`.
- Affected code: `core/cpp/src/brain_action_execution.cpp`, action-outcome append followed by optional affective-learning and capability-learning appends; `core/cpp/src/memory.cpp`, `Memory::append` persists one event at a time.
- Root cause: the logical learning transaction is represented by multiple independently appended events with no transaction envelope, completion marker, or deterministic repair/reconciliation step.
- Consequence: after a secondary append failure or process termination between appends, replay reconstructs the persisted subset, not necessarily the full intended update set. The action record may exist while affective calibration or capability-reliability learning does not.
- Required Builder decision: define whether partial derived learning is an acceptable recoverable state. If not, introduce a durable transaction/completion protocol or replay-time derivation with idempotent source-event identity. Do not simply retry secondary appends without duplicate protection.
- Verification: inject failures at each append boundary; restart from the resulting journal; prove the action outcome is retained exactly once, each derived learning update is either completed exactly once or explicitly marked pending/recoverable, and predictions are not double-resolved.

This finding is distinct from a claim of data corruption: the inspected append path attempts to roll back a failed individual event write to the original file size. The gap is atomicity across multiple successful/failed appends and the recovery contract for partially completed logical learning.

### Remaining runtime caller-graph work

The donor tree includes `CognitiveRuntime`, `Brain::execute_action`, a TypeScript Brain interface and several simulation/test harnesses. The present batch verifies the native runtime class and its action-adapter call path. It does not yet establish that every intended external application entry point constructs and drives this runtime, that TypeScript calls the same path, or that production integrations consistently provide independent consequence observation. Those remain open integration questions, not presumed defects.

**Phase 2 remains IN PROGRESS. Gate A remains NOT CLEARED. PR #97 remains an unmerged donor.**


---

## 29. DLT-002 protocol audit — what its runtime evidence can and cannot establish

A second source-level pass examined the measurement path, not just the successful workflow summaries.

### Protocol strengths

At the earlier DLT-002 trial revision (`82c49a75bd30de2962879f044776f4bf2391970a`), the harness:
- Randomizes which route is optimal for each latent condition per seed, inside the environment rather than exposing that mapping to the Brain.
- Uses 20% contradictory/noisy outcomes.
- Preserves a visible context while changing the latent condition/action relationship, including a reversal phase.
- Includes a held-out context transfer probe and a later second reversal.
- Checks that a completed cognitive cycle selected exactly one planned action and that the returned consequence was actually observed.
- Requires the action-consequence prediction to have been issued by Brain and records its calibrated value, rather than substituting the planner's raw action prior.
- Separates evaluation-only latent labels and expected action from the observation and consequence feedback given to Brain.
- Records per-episode choices, consequences, prediction counts and per-context strategy values, plus periodic checkpoints.

This is a meaningful controlled test of context-conditioned action learning, reversal, noisy feedback, prediction feedback and transfer. It is stronger than a static unit fixture that feeds the correct answer directly to the learner.

### Limitations of the protocol and its evidence

1. **Environment is controlled and small.** Two route actions and a finite set of named contexts do not establish open-world action learning, complex perception, or broad transfer.
2. **The task context is supplied.** The Brain receives the world context as part of the input. The trial does not test whether JARVIS can infer the relevant context from raw sensory evidence.
3. **The hidden labels are evaluation-only, but the harness computes success.** The metric is valid for this environment, yet it is not an independent external benchmark and must be interpreted within the protocol.
4. **Episode count is not learning quality.** The workflow's 586–590 completed episodes and successful exit establish run completion, not by themselves high decision accuracy, successful reversal, or positive transfer.
5. **The trial run predates final donor HEAD by 18 commits.** It cannot close the final-revision runtime evidence gap.
6. **No cross-seed statistical analysis is included in the workflow summary alone.** Three seeds are useful replication, but the raw per-episode artifacts and predeclared acceptance thresholds must be analyzed before claiming reliable effect size or variance.
7. **The persistence fixture uses prescribed context/action/consequence pairs.** It tests durable acquisition and restoration, not autonomous discovery of the environment's latent mapping.

### Three-reference interpretation

- **MCU JARVIS functional reference:** the protocol contributes evidence toward contextual adaptation, prediction from experience and changing action preference after consequences. It does not approach broad environmental awareness or complex multi-domain planning.
- **Human cognition reference:** context-dependent learning, noisy reinforcement, reversal and transfer are relevant cognitive phenomena. The simulation is an engineering abstraction, not a model of neural circuitry, emotion, or human developmental learning.
- **Our JARVIS engineering reality:** the harness supplies a reproducible environment, hidden evaluation labels, actual observed consequences and a real Brain/runtime path. Its claims should be bounded to those measured properties.

**Acceptance implication:** DLT-002 is credible evidence of a designed learning mechanism being exercised in a controlled environment. It is not sufficient by itself to clear Gate A. The next runtime evidence should rerun the same protocol at the final candidate commit, retain raw artifacts, analyze phase-specific accuracy and reversal latency, quantify held-out transfer against a no-transfer/control baseline, and report seed-level distributions rather than only completion counts.

### Updated Phase 2 position

The donor now has:
- Exact-HEAD 71/71 native CTest and 71/71 ASan/UBSan CTest evidence.
- Earlier three-seed, ten-minute DLT-002 runtime evidence.
- Source-level tests for action consequence, developmental strategy, affective appraisal and persistence across reconstruction.
- A concrete remaining durability limitation for multi-event action learning.
- An unresolved production integration/caller-graph question beyond the native C++ runtime.

The next investigation should prioritize (a) independent analysis of the retained DLT-002 artifacts and acceptance metrics, (b) failure-injection verification of multi-event recovery, and (c) identifying the actual application boundary that supplies observations, actions and consequence observations to the Brain. No donor merge or Gate A approval is implied.


---

## 30. DLT-002 raw artifact analysis — three-seed behavioral results

The three retained ZIP artifacts from workflow run #8 (40565468650) were downloaded and the raw episodes.csv, trial.log, checkpoints.csv, and summary files were inspected. This moves the evidence assessment beyond workflow completion and summary counts.

**Revision boundary:** all three artifacts identify donor commit 82c49a75bd30de2962879f044776f4bf2391970a, which is an ancestor of the current donor HEAD c1da222e6c94aeb3f2ad000392c21fe4fc81ab25 with 18 intervening commits. These are valid results for the earlier revision only.

### Aggregate observed results

Across the three seeds:

| Phase | Optimal selections | Decisions | Accuracy |
|---|---:|---:|---:|
| Clear baseline | 280 | 300 | 93.3% |
| Flooded | 286 | 297 | 96.3% |
| Tunnel | 279 | 295 | 94.6% |
| Clear reversal | 276 | 294 | 93.9% |
| Held-out canyon probe | 289 | 291 | 99.3% |
| Flooded reversal | 272 | 288 | 94.4% |
| **Total** | **1,682** | **1,765** | **95.3%** |

Individual learning-enabled trial summaries report:
- Seed 20261026: 569/586 optimal (97.1%).
- Seed 20261027: 557/590 optimal (94.4%).
- Seed 20261028: 556/589 optimal (94.4%).

These aggregate values are descriptive results from the retained artifacts, not a statistical claim of generalization beyond this task.

### Reversal behavior

The raw episode records show that the policy did not simply maintain a fixed action throughout the trial:

- In the clear-context reversal, the first ten decisions were 5/10, 6/10 and 7/10 optimal across the three seeds; the final ten were 10/10 in all three.
- In the later flooded-context reversal, the first ten were 4/10, 7/10 and 4/10 optimal; the final ten were 9/10, 10/10 and 10/10.
- The trial logs show context-local strategy values changing sign as the hidden action/consequence relationship reverses, followed by the policy's decision accuracy recovering.

This supports behavioral adaptation after contradictory experience in this bounded task. It also exposes a measurable adaptation cost: early post-reversal choices are substantially worse than the late-phase choices. The current summary's final phase accuracy hides that transient cost; future acceptance reports should retain and publish first-window accuracy and recovery curves.

### Held-out transfer behavior

All three seeds:
- Retrieved a related strategy before the first action in the unseen navigation/canyon context.
- Reported a source-context similarity of 0.5.
- Selected the evaluation-optimal action on the first canyon decision, before any canyon outcome feedback.
- Achieved 29/30 optimal decisions across the first ten canyon decisions (the first decision precedes canyon feedback; subsequent decisions may use newly received feedback).
- Achieved 289/291 optimal decisions over the full probe phase.

The source context varied by seed (clear or flooded), and the selected source action matched the hidden evaluation-optimal action in the probe. This is stronger than merely observing high final probe accuracy: the first choice occurred before the new context could teach the Brain its own action mapping.

**However, this is not yet a causal estimate of transfer benefit.** The sweep did not run a matched no-transfer policy or an ablation that disables related-strategy retrieval. The first-choice success is evidence consistent with transfer under the harness's similarity mechanism, not proof that transfer improves performance relative to a no-transfer counterfactual. The fixed-policy controls in the summary are always-route-one and always-route-two; they are not matched learning-disabled Brain controls.

### Prediction accounting

The three artifacts record:
- 1,995–2,008 prediction records per seed in the final summary.
- 566–569 resolved predictions in the summary's retained prediction snapshot.
- Zero unresolved action-consequence forecasts in every seed.
- 1,429–1,439 unresolved non-action-consequence predictions in those same snapshots.

The summary script reads the final row of checkpoints.csv, whose last periodic checkpoint is at approximately 578 seconds. The trial.log completion record is written after the run finishes at approximately 600 seconds and reports a later prediction snapshot (586–590 resolved predictions and 2,215–2,239 prediction records). These values differ because the checkpoint precedes the final run interval, not because the two outputs use different metrics: both use the same prediction_metrics snapshot calculation. Cite the checkpoint and completion values with their timestamps and do not present them as contradictory counts. The zero unresolved action-consequence count is useful evidence that action-consequence forecasts were resolved in both snapshots; it does not establish that every other prediction class is resolved.

### Experimental design gap

The executable supports enabled and no-feedback modes, but the three-seed workflow invokes the executable without the final mode argument, so it uses the default enabled mode for every seed. It does not schedule a paired no-feedback run. The fixed-action baselines therefore do not isolate the causal contribution of learning from other Brain/runtime effects.

**Updated evidence judgement:** DLT-002 run #8 provides substantial, reproducible evidence of learning-enabled policy adaptation, repeated reversal and first-choice performance in a held-out context at commit 82c49a.... It does not establish a matched causal learning effect, and it is not current-HEAD runtime evidence. The next experiment should pair identical seeds and environment schedules in enabled and no-feedback modes, predefine primary metrics, include a transfer-disabled ablation, and rerun at the final candidate commit.

---

## 31. Application-boundary and polyglot integration map

A bounded whole-tree inspection was performed against donor HEAD c1da222e6c94aeb3f2ad000392c21fe4fc81ab25. The result is important because the presence of language-specific directories or interfaces is not evidence that they are connected to the native cognitive runtime.

### Native C++ cognitive substrate

- core/cpp/CMakeLists.txt builds jarvis_core as a static C++20 library and includes the cognitive runtime, cycle, perception pipeline, memory, action execution, developmental learning, affective learning and related mechanisms.
- CognitiveRuntime is a concrete worker-thread runtime with bounded input, result and feedback queues; perception providers; an action adapter; and a shared cognitive workspace.
- The verified in-tree construction/use sites found in the inspected executable C++ code are simulation examples and test/trial harnesses, including core/cpp/examples/developmental_world.cpp, core/cpp/tests/developmental_world_integration_suite.cpp, core/cpp/tests/cognitive_runtime_suite.cpp, core/cpp/tests/cognitive_runtime_learning_integration_suite.cpp and core/cpp/tests/dlt_002_long_run.cpp.
- Those harnesses provide the external environment boundary explicitly: observations are submitted, candidate actions are supplied, the adapter executes a selected action, and observe_consequence returns the world result to Brain.

### TypeScript interface boundary

The inspected TypeScript files contain contracts and session forwarding:
- interfaces/typescript/src/brain.ts defines BrainTransport with observe, decide and capabilities methods.
- interfaces/typescript/src/agent_bridge.ts defines message/request/transport/session interfaces.
- interfaces/typescript/src/operator_session.ts forwards operator requests to an injected transport and receives messages from that transport.

These files do not implement a concrete transport connecting TypeScript to the C++ CognitiveRuntime, nor do they show an observation/action/consequence adapter into the native runtime. operatorSend forwards a request; it does not itself execute a cognitive cycle or grant action authority. The source explicitly keeps execution authorization inside the runtime boundary.

### Rust runtime boundary

The inspected runtime/rust/src/lib.rs and runtime/rust/src/cognition.rs implement a separate minimal BrainRuntime/CognitiveState with a map of beliefs, evidence counts and a bounded working-memory vector. Its observe method updates that local state. The inspected Rust module does not call or bind to the C++ Brain/runtime and does not implement the full C++ cognitive cycle, action adapter, prediction-feedback loop or durable journal integration.

### Documentation alignment

The repository README describes JARVIS as foundational development focused on completing and integrating the cognitive substrate before higher-level device, interface and deployment layers. The architecture document describes intended polyglot boundaries and explicit contracts. The observed code is consistent with a native C++ substrate plus preliminary TypeScript/Rust boundary work; the source inspected does not yet demonstrate a single integrated, deployed, polyglot application.

### Integration status and required proof

This is an **unresolved integration-scope item, not a confirmed implementation defect**. The current donor evidence supports a runnable C++ cognitive substrate in controlled harnesses. It does not support claims that the TypeScript operator layer, Rust runtime and C++ cognitive runtime are already one connected production system.

Before describing the whole brain as application-integrated, the Builder should provide an explicit executable entry-point map with:
1. The real application process or service that owns the Brain and starts/stops CognitiveRuntime.
2. The concrete TypeScript-to-native transport implementation and serialization/version contract, if TypeScript is intended to drive the native Brain.
3. The role of the Rust runtime: production component, isolated prototype, or superseded experiment; if production, its synchronization and ownership boundary with C++.
4. The source of real observations and the provenance/independence of consequence observations.
5. Authorization, cancellation, timeout, retry, backpressure and shutdown semantics at the application boundary.
6. An end-to-end integration test that launches the actual entry point and proves one externally sourced experience changes a later decision through the same persistent Brain instance, followed by restart/replay verification where required.

Until that evidence exists, classify the C++ runtime as an integrated native substrate exercised through controlled harnesses, and classify the cross-language/application boundary as not yet demonstrated. Do not count the existence of interfaces/typescript or runtime/rust as integration evidence.

### Updated Phase 2 priorities

1. Run paired enabled/no-feedback and transfer-ablation DLT-002 experiments with the same seeds and schedules.
2. Rerun the long-run behavioral protocol on the exact final candidate SHA and publish per-phase, early-reversal and transfer metrics.
3. Execute failure injection for P2-I-023 and define the multi-event learning transaction's partial-commit recovery contract.
4. Require the actual application entry-point/transport map and one end-to-end test across the intended language boundaries.
5. Preserve the distinction between mechanism existence, controlled runtime integration, cross-language integration and deployed operation in all Gate A decisions.

**Phase 2 remains IN PROGRESS. Gate A remains NOT CLEARED. PR #97 remains an unmerged donor.**


---

## 32. Journal append failure semantics — second persistence finding

A deeper inspection of the journal writer found a separate failure-path gap from P2-I-023. This finding concerns single-event append rollback, startup repair of a malformed journal tail, and the meaning of "durable", rather than the multi-event learning transaction.

### Direct source evidence

At donor HEAD c1da222e6c94aeb3f2ad000392c21fe4fc81ab25:

- core/cpp/src/memory.cpp, Memory::persist, serializes an event through std::ofstream opened with binary|app, calls write_event, calls flush, checks the stream state, and closes the stream.
- If the write/flush reports failure, it calls std::filesystem::resize_file(journal_path_, original_size, rollback_error) and returns false.
- The rollback_error is not checked or surfaced. There is no second verification that the file size returned to original_size.
- The writer does not call fsync/fdatasync or an equivalent platform-specific stable-storage primitive. C++ stream flush is not a guarantee that bytes have reached stable storage across sudden power loss or kernel crash.
- Memory::load scans sequentially until it encounters an invalid/truncated event, then copies the unreadable suffix to a `.corrupt` file before attempting to truncate the active journal to the last valid record boundary. It cannot safely resynchronize beyond an invalid record because the journal has no frame marker/checksum. The quarantine copy is checked, but the subsequent `std::filesystem::resize_file(journal_path_, valid_end, error)` result is not checked or surfaced; a failed repair therefore leaves the malformed suffix in the active journal while construction continues with only the valid prefix in memory.

### Failure sequence and impact

If an append fails after writing a partial record and the subsequent resize_file rollback also fails (for example, a filesystem/storage error or permission/space failure), Memory::append returns 0 but the partial suffix may remain in the active journal. The same Memory instance can then accept a later append: persist opens with app and writes after the leftover suffix. That later append can report success and update in-memory state, even though on restart the loader stops at the earlier malformed suffix and quarantines the later valid record along with it.

There are two related conditional failure paths. First, if an append partially writes and its rollback truncation fails, a later append on the same Memory instance can be acknowledged behind the malformed suffix. Second, if startup successfully quarantines a malformed suffix but the load-time truncation fails, the constructor still returns a usable Memory instance whose in-memory state contains only the valid prefix while the on-disk journal still contains the bad tail; a subsequent append may then be written after that tail. In either case, a later restart can stop at the earlier malformed record and quarantine later acknowledged records. The source proves both truncation results are ignored, but no injected filesystem failure has yet reproduced either sequence. This is not evidence that ordinary appends or normal recovery are currently losing data.

Separately, even a successful append currently establishes stream-flush completion, not a documented power-loss durability guarantee. Any use of "durable" in the report or product contract must specify whether it means process-restart persistence under normal OS operation or stable-storage persistence after abrupt machine failure.

### Finding P2-I-014 — Journal append rollback and startup tail-repair failures are unchecked; stable-storage durability is unspecified

- Severity: Medium (provisional; may be higher if the product contract promises crash/power-loss durability).
- Confidence: High for the unchecked rollback result and absence of fsync-like calls in the inspected writer; Medium for the operational loss scenario until fault-injection reproduction.
- Status: Confirmed code-level failure-path weakness; acceptance impact unresolved.
- Affected revision: c1da222e6c94aeb3f2ad000392c21fe4fc81ab25.
- Affected code: core/cpp/src/memory.cpp, Memory::persist and Memory::load.
- Root cause: both append-time rollback and load-time tail-repair truncation are best-effort operations whose error results are discarded; Memory has no poisoned/recovery-required state preventing later appends after an unrepaired tail; the journal's durability contract is not explicit.
- Required Builder decision: define the supported failure model (process crash, OS crash, power loss, disk-full, I/O error). If rollback cannot be verified, put the Memory instance into a failed/poisoned state and reject subsequent appends until recovery, or use a journal format/recovery protocol that can safely identify and repair the tail before continuing. Specify whether successful append promises process-restart persistence or stable-storage durability.
- Verification: use a fault-injectable filesystem/journal backend to fail event writes, append rollback truncation, quarantine copying, and load-time truncation independently. Assert that Memory does not accept later appends while an invalid tail remains unrepaired; restart and verify every acknowledged event is recovered exactly once. Retain the existing successful-quarantine/recovery test, and add failure assertions for both ignored truncation results. Add crash/power-loss tests only for durability guarantees the project explicitly elects to provide.

### Relationship to P2-I-023 and current test coverage

P2-I-023 remains the multi-record logical learning atomicity issue: action_outcome, affective_learning and learning are separate appends. P2-I-014 is the lower-level single-record journal rollback/durability issue. Fixing one does not fix the other.

The inspected memory_architecture_suite includes a positive-path corrupt-tail test: it corrupts a later record, verifies that the suffix is quarantined, verifies the active journal is repaired, appends a new event, and verifies restart recovery. This validates successful repair only. The memory_learning_evolution_persistence_suite and dlt_002_persistence likewise test normal successful append/reconstruction and learned-state restoration. None of these tests injects event-write failure, append rollback truncation failure, quarantine-copy failure, load-time truncation failure, flush failure, or abrupt power loss. Their successful recovery assertions must not be described as evidence for those untested failure modes.

**Updated persistence assessment:** normal-path event append/replay and learning reconstruction have meaningful integration coverage. Multi-event transaction recovery and low-level journal failure handling remain unverified. The word "durable" should be qualified to match the actual guarantees implemented and tested.


## 33. Self-review and correction audit before feedback follow-up

**Audit date:** 2026-11-06  
**Review scope:** Report consistency, source provenance, finding status, section structure, and separation of review artifacts from the donor branch.

### 33.1 Material correction made before handoff

- Re-opened the complete donor `core/cpp/tests/CMakeLists.txt` after noticing that the prior Release-assertion analysis had inspected only the test registrations.
- Verified the final CMake block applies `-UNDEBUG` for GNU/Clang and `/UNDEBUG` for MSVC to executable test targets.
- Replaced the incorrect active finding P2-I-034 with an explicit withdrawal and correction record in §26.
- The report must not state that the donor's Release CTest job elides assertions. That earlier conclusion is withdrawn.
- The correction does not change the separate exact-HEAD Debug ASan/UBSan evidence or any of P2-I-001 through P2-I-033.

### 33.2 Structure and finding-index checks

- The appended investigation batches are numbered consecutively as §§27–32; the subsequent feedback-persistence follow-up is isolated in §34.
- P2-I-034 is recorded only as a withdrawn finding; it is not part of the active finding set.
- The active finding sequence remains P2-I-001 through P2-I-033. The withdrawal is retained for auditability rather than silently deleting the prior reviewer error.
- The report continues to distinguish confirmed source defects, unverified failure-path risks, unresolved integration scope, and experimental limitations.
- Historical CI and DLT-002 results remain scoped to their exact commit SHAs; earlier-revision experiments are not presented as current-HEAD runtime proof.

### 33.3 Source and branch boundary

- Donor source baseline remains PR #97 HEAD `c1da222e6c94aeb3f2ad000392c21fe4fc81ab25`.
- The CMake evidence used for the correction is donor blob `cbfd1fde52fffa6eeac025da2b7ddcb5ab493261`.
- The report is maintained on `docs/jarvis-phase-2-whole-brain-integration-map-20261105` and PR #179; no donor branch source or tests were changed.
- The review remains independent and review-only. No implementation, merge, donor approval, or baseline selection is implied.

### 33.4 Remaining work and decision boundary

This batch improves the accuracy and navigability of the report; it does not complete Phase 2. The remaining blockers in §25.4 still apply, including acquisition/provenance tracing, test-validity review, authorization and action-failure boundaries, deterministic failure injection, runtime coordination/recovery, and independent review.

**Self-review result at this stage:** the prior Release-assertion finding was materially wrong and has been explicitly withdrawn. The report's active finding index, section numbering, and donor/report branch boundary have been reconciled in this update. Phase 2 remains IN PROGRESS; Gate A remains NOT CLEARED. No implementation baseline is selected and no donor is approved.



---

## 34. Finding P2-I-035 — Runtime feedback persistence acknowledgement is not reflected in completion metrics

**Audit date:** 2026-11-06  
**Affected donor revision:** `c1da222e6c94aeb3f2ad000392c21fe4fc81ab25`  
**Scope:** Trace queued `CognitiveFeedback` through prediction resolution, evidence learning, journal append and runtime completion metrics. This follow-up isolates a distinct caller-visible status gap at the queued-feedback boundary; it cross-references, but does not duplicate, the existing action-persistence and multi-event atomicity findings.

### Direct source trace

1. `CognitiveRuntime::process_feedback` calls `CognitiveCycle::process_outcome` and decides whether the item failed using only two conditions: a requested prediction was not resolved, or a requested goal update was not assimilated. If neither condition is requested, neither can fail the item.
2. `CognitiveCycle::process_outcome` resolves a requested prediction first. It then calls `learn_from_outcome(evidence)` when evidence is present and stores the returned numeric reliability in `CognitiveFeedbackResult::learned_reliability`. It exposes no separate evidence-persistence status.
3. `Brain::learn` appends a `learning` event. If `Memory::append` returns sequence zero, it returns numeric zero before replaying the event or updating the knowledge projection. On success, it can also return numeric zero when the assimilated source reliability is zero. Therefore the numeric return value is not an unambiguous persistence acknowledgement.
4. `CognitiveRuntime::process_feedback` does not inspect `learned_reliability` and has no evidence-assimilated/persisted flag to inspect. A non-throwing evidence append failure can therefore still increment `feedback_processed`.

This produces two concrete conditional cases:

- **Evidence-only feedback:** if the `learning` event append fails, neither prediction nor goal failure condition is requested; the runtime increments `feedback_processed` even though the evidence event was not replayed into Brain state.
- **Prediction plus evidence feedback:** prediction resolution is attempted and can persist before the separate evidence append. If prediction resolution succeeds but the later `learning` append fails, the runtime still increments `feedback_processed`; the journal contains the resolved prediction outcome but not the associated evidence-learning event.

These are source-derived failure-path outcomes, not reproduced incidents. The inspected tests do not inject a failure specifically at the `Brain::learn` evidence append.

### Source anchors

- [`CognitiveRuntime::process_feedback`](https://github.com/methaneex-oss/MethaneX/blob/c1da222e6c94aeb3f2ad000392c21fe4fc81ab25/core/cpp/src/cognitive_runtime.cpp#L127-L154), blob `cf00acb6abd52308343f3a0e7016e6173b945603`.
- [`CognitiveCycle::process_outcome`](https://github.com/methaneex-oss/MethaneX/blob/c1da222e6c94aeb3f2ad000392c21fe4fc81ab25/core/cpp/src/cognitive_cycle.cpp#L750-L773), blob `f191dd610d6cbe1621756c35e7c13af2054a7266`.
- [`CognitiveFeedbackResult` exposes only a numeric `learned_reliability`, not an evidence-persistence status](https://github.com/methaneex-oss/MethaneX/blob/c1da222e6c94aeb3f2ad000392c21fe4fc81ab25/core/cpp/include/jarvis/core/cognitive_cycle.hpp#L70-L76), blob `eed8bc75f59557c255e796343d77498d90b31ea5`.
- [`Brain::learn`](https://github.com/methaneex-oss/MethaneX/blob/c1da222e6c94aeb3f2ad000392c21fe4fc81ab25/core/cpp/src/brain.cpp#L791-L820), blob `dec9e5442b3ca4b81a7879855c6146b2619934cc`.
- [Runtime feedback integration test](https://github.com/methaneex-oss/MethaneX/blob/c1da222e6c94aeb3f2ad000392c21fe4fc81ab25/core/cpp/tests/cognitive_runtime_suite.cpp#L223-L260), blob `361cba84a6fc6e07e31d14b5fa618c3f0a7848fa`.
- [Goal-feedback runtime test](https://github.com/methaneex-oss/MethaneX/blob/c1da222e6c94aeb3f2ad000392c21fe4fc81ab25/core/cpp/tests/cognitive_runtime_goal_feedback_suite.cpp#L1-L90), blob `15a6bdffe37ae7df6c625ea9737fda4c0bf08a7f`.

### P2-I-035 — Finding details and required correction

- **Severity:** Medium (provisional; impact depends on whether `feedback_processed` is consumed as an operational or acceptance signal).
- **Confidence:** High for the control-flow and missing-status evidence; Medium for the failure outcome until append failure is deterministically injected.
- **Status:** Confirmed code-level acknowledgement gap; conditional append-failure scenarios not reproduced.
- **Affected revision:** `c1da222e6c94aeb3f2ad000392c21fe4fc81ab25`.
- **Affected code:** `CognitiveRuntime::process_feedback`, `CognitiveCycle::process_outcome`, `Brain::learn`, and the `Memory::append` boundary.
- **Root cause:** `CognitiveFeedbackResult` exposes no unambiguous evidence-persistence status. `Brain::learn` returns a scalar reliability value that can be zero both after append failure and after a valid zero-reliability update. `CognitiveRuntime::process_feedback` checks prediction resolution and goal assimilation but does not inspect the evidence-learning result before incrementing `feedback_processed`.
- **Impact:** a queue item can be counted as successfully processed even though its evidence-learning event was not appended/replayed. With prediction-plus-evidence feedback, the prediction outcome may persist while the separate evidence event fails, leaving a partial result that the current metric reports as fully processed.

Required Builder/Tester evidence:

1. Give evidence assimilation an explicit structured result that distinguishes validation rejection, journal append failure, persisted-and-replayed evidence, and a valid zero-reliability update. Do not infer persistence from a floating-point reliability value.
2. Make runtime feedback accounting reflect partial outcomes. A prediction may be resolved while associated evidence learning fails; expose that as partial/failed rather than a fully processed feedback item.
3. Define whether prediction resolution and evidence learning form one logical feedback transaction. If partial completion is permitted, persist a recoverable pending marker or equivalent reconciliation identity; retries must be idempotent.
4. Inject `Memory::append` failure for (a) evidence-only feedback and (b) combined prediction-plus-evidence feedback. Assert the returned per-component status, `feedback_processed`/`feedback_failed` counters, live Brain state, journal contents, restart/replay state and retry behavior.
5. Include a successful zero-reliability evidence case so the test proves that a numeric return of zero is not mistaken for append failure.

**Relationship to existing findings:** P2-I-029 concerns the action-execution result/metrics boundary after `Brain::execute_action`; P2-I-035 concerns the later queued-feedback processing boundary and `feedback_processed` accounting. They share the general persistence-acknowledgement principle but are distinct caller/result paths. P2-I-023 remains related because prediction resolution and evidence learning can be separate persisted events; P2-I-035 specifically addresses the runtime's false-success accounting when evidence assimilation is not acknowledged.

### Test-coverage judgement

The inspected `cognitive_runtime_suite` exercises successful prediction-plus-evidence feedback, sequence-bound prediction resolution and invalid-payload rejection. The inspected goal-feedback suite exercises successful progress assimilation and a regressive goal update counted as failed. These tests do not establish correct metrics or recovery when the evidence-learning append itself fails.

**Updated review judgement:** runtime feedback queue acceptance is not equivalent to successful evidence assimilation; successful prediction resolution is not proof that associated evidence learning persisted. The existing P2-I-023/P2-I-029 findings remain open, and this additional call path must be included in their failure-injection matrix. Phase 2 remains IN PROGRESS. Gate A remains NOT CLEARED. PR #97 remains an unmerged donor.


---

## 35. Finding-index and provenance reconciliation before goal-completion audit

**Audit date:** 2026-11-06  
**Scope:** Independent consistency pass after the runtime-feedback persistence follow-up in §34.

### 35.1 Finding identity reconciliation

The full report contained reused numeric labels in later appended batches. These have been reconciled so a reviewer can identify one issue unambiguously:

- **P2-I-012** remains the donor runtime action/consequence/learning/decision integration finding. The later CI evidence correction in §27 is a report-history correction, not a second finding, and no longer carries a finding ID.
- **P2-I-013** remains the mainline finding that the inspected main CognitiveRuntime does not connect cycle assessments to the standalone Brain action-execution API.
- **P2-I-014** now identifies the lower-level journal append rollback and startup tail-repair failure/durability issue in §32.
- **P2-I-023** is the canonical multi-event action-learning atomicity finding. The earlier source-trace statement in §13.5 and the detailed failure-path treatment in §28 are explicitly cross-referenced to this same finding rather than creating competing IDs.
- **P2-I-029** remains the action-execution/persistence-acknowledgement finding. **P2-I-035** separately covers the evidence-only and prediction-plus-evidence feedback path's caller-visible acknowledgement and completion-metric gap; it cross-references P2-I-023's partial-commit concern.
- **P2-I-034** is withdrawn. It is retained only as an audit trail for the incorrect Release-assertion conclusion; it is not an active finding or Gate A blocker.
- **P2-I-036** covers the distinct two-event goal-completion path: a persisted `goal_progress(progress=1.0)` event is not sufficient for goal-state replay without the separate `goal_complete` event.

The active finding set is P2-I-001 through P2-I-033 plus P2-I-035 and P2-I-036. P2-I-034 is withdrawn and intentionally not reused. Repeated references to an existing finding are expansions or cross-references, not additional findings.

### 35.2 Runtime-feedback follow-up verification

The §34 source trace was independently checked against the donor blobs for `cognitive_runtime.cpp`, `cognitive_cycle.cpp`, `cognitive_cycle.hpp`, `brain.cpp`, and `memory.cpp`:

- `process_feedback` marks feedback failed only for an unresolved requested prediction, an unassimilated requested goal update, or an exception. It does not inspect whether optional evidence learning persisted.
- `process_outcome` resolves a requested prediction before invoking `learn_from_outcome` for evidence, so the two effects can persist independently.
- `Brain::learn` returns numeric zero both when the Memory append fails and when a valid zero-reliability update is learned; the scalar return is not a persistence status.
- The current successful runtime tests do not inject failure at the evidence-learning append. The report labels the failure sequences as conditional source-derived outcomes, not reproduced incidents.

P2-I-035 is a distinct finding because it concerns the queued-feedback processing boundary and its completion metric, rather than the action-execution result boundary in P2-I-029. It cross-references P2-I-023 because the prediction outcome and evidence-learning event can partially persist.

### 35.3 Report structure and source boundaries

- Sections are numbered consecutively through §37, with no duplicate section numbers.
- Active finding IDs are reconciled as stated above; the CI correction remains an unnumbered report-history correction, while §34 contains distinct finding P2-I-035 and §36 contains distinct finding P2-I-036, with explicit cross-references to P2-I-023/P2-I-029 where applicable.
- Donor evidence remains pinned to PR #97 HEAD `c1da222e6c94aeb3f2ad000392c21fe4fc81ab25`.
- The donor branch remains unchanged by this review. The report and its corrections are confined to the Phase 2 review branch and PR #179.
- No production source, test, workflow or build configuration was edited by this review batch.

### 35.4 Decision boundary

This report is materially more complete and internally navigable, but Phase 2 is not complete. The unresolved requirements in §25.4 remain open, including acquisition/provenance tracing, selected-suite validity and controls, authorization freshness, partial-effect/rollback behavior, deterministic journal, goal-completion and feedback failure injection, cross-runtime integration, and independent review.

**Status at this audit point:** Phase 2 IN PROGRESS. Gate A NOT CLEARED. PR #97 remains an unmerged donor. No implementation baseline is selected, no donor is approved, and no implementation authorization is implied.



---

## 36. Goal-completion feedback has a two-event partial-commit boundary

**Audit date:** 2026-11-06  
**Affected donor revision:** `c1da222e6c94aeb3f2ad000392c21fe4fc81ab25`  
**Finding P2-I-036 — A failed goal-completion append can leave a persisted 100% progress event that replay deliberately does not apply to goal state.**

### Direct source trace

- `Brain::assimilate_goal_outcome` normalizes the supplied evidence and sets `completed` when `progress_after >= 1.0`. It first appends a `goal_progress` event. If that append succeeds, it immediately replays the event and advances the Brain event/cycle counters. Only then does it append a separate `goal_complete` event. If the second append returns zero, the method returns `false` without rolling back the first event.
- `Brain::replay` processes affective experience before dispatching the event-specific goal projection. For `goal_progress`, it calls `goals_model_.update_progress` only when the recorded progress is strictly less than 1.0. For `goal_complete`, it calls `goals_model_.complete`.
- `GoalModel::update_progress` itself marks a goal completed at progress 1.0, but the replay guard deliberately prevents the `goal_progress` event from applying that transition. The separate `goal_complete` event is therefore required to reconstruct completion.
- The persisted `goal_progress(progress=1.0)` event still passes through `process_affective_experience`, which updates affective state and appraisal before the replay branch skips the goal-model update.

### Conditional failure sequence and impact

If the first append succeeds and the second `goal_complete` append fails:

1. The journal contains a `goal_progress` event with progress 1.0.
2. Affective processing has consumed that event.
3. The goal model has not been advanced to progress 1.0 or completed, because replay intentionally skips the goal-model update for progress values equal to 1.0.
4. `assimilate_goal_outcome` returns `false`; the runtime correctly increments `feedback_failed` for the requested goal update.
5. On restart, the persisted progress event is replayed with the same guard and still does not complete the goal. Without a persisted `goal_complete` event, the goal remains at its prior progress/status.

This is a source-derived failure path, not a reproduced incident. It is distinct from P2-I-023's action-outcome/affective/capability multi-event sequence and P2-I-035's queued-evidence completion-metric gap: this path concerns the goal lifecycle and the replay semantics that make the second event necessary.

### Source anchors

- [`Brain::assimilate_goal_outcome`](https://github.com/methaneex-oss/MethaneX/blob/c1da222e6c94aeb3f2ad000392c21fe4fc81ab25/core/cpp/src/brain_restored_api.cpp#L172-L215), blob `7155d4d9c8eef527836fb79bf901aa32ddbae38b`.
- [`Brain::replay`](https://github.com/methaneex-oss/MethaneX/blob/c1da222e6c94aeb3f2ad000392c21fe4fc81ab25/core/cpp/src/brain.cpp#L339-L370), blob `dec9e5442b3ca4b81a7879855c6146b2619934cc`.
- [Goal progress affective processing](https://github.com/methaneex-oss/MethaneX/blob/c1da222e6c94aeb3f2ad000392c21fe4fc81ab25/core/cpp/src/brain.cpp#L287-L289), same blob.
- [`GoalModel::update_progress`](https://github.com/methaneex-oss/MethaneX/blob/c1da222e6c94aeb3f2ad000392c21fe4fc81ab25/core/cpp/src/goals.cpp#L37-L59), blob `afaedcfb0f2f68ff88b3a20e474fce04bb59815c`.
- [Goal-feedback success/restart test](https://github.com/methaneex-oss/MethaneX/blob/c1da222e6c94aeb3f2ad000392c21fe4fc81ab25/core/cpp/tests/cognitive_runtime_goal_feedback_suite.cpp#L45-L78), blob `15a6bdffe37ae7df6c625ea9737fda4c0bf08a7f`.

### Severity, confidence and status

- **Severity:** Medium (provisional; the impact is a persistent goal-state/replay inconsistency under a second-append failure).
- **Confidence:** High for the source ordering and replay guard; Medium for operational impact until deterministic append-failure injection reproduces the sequence.
- **Status:** Confirmed code-level partial-commit hazard; failure-path acceptance remains unresolved.
- **Affected code:** `core/cpp/src/brain_restored_api.cpp`, `core/cpp/src/brain.cpp`, and `core/cpp/src/goals.cpp`.

### Required Builder/Tester evidence

1. Decide whether a 100% `goal_progress` event is independently authoritative for goal completion. If it is, replay must apply it consistently; if it is not, the two-event completion protocol needs an explicit transaction/completion marker or recoverable pending state.
2. Inject failure specifically at the second append (`goal_complete`) after a successful `goal_progress(progress=1.0)` append.
3. Assert the live goal state, returned assimilation status, affective state, journal event sequence and reconstructed goal state after restart.
4. Retry the same logical goal outcome and prove completion is eventually reconstructed without duplicate or unintended affective-learning updates.
5. Preserve tests for ordinary sub-1.0 progress, successful completion, terminal-goal rejection and restart equivalence.

The inspected `cognitive_runtime_goal_feedback_suite` covers successful 0.4 progress, successful 1.0 completion, rejection of a regressive update after completion, and successful restart reconstruction. It does not inject failure between the two completion appends.

**Updated review judgement:** goal feedback is not a single atomic state transition at the 100% boundary. A successful `goal_progress` append is not sufficient to reconstruct completion under the current replay rules. P2-I-036 remains open. Phase 2 remains IN PROGRESS. Gate A remains NOT CLEARED. PR #97 remains an unmerged donor.


---

## 37. Goal-completion finding verification and report-state audit

**Audit date:** 2026-11-06  
**Scope:** Independent source verification of §36, final finding-index consistency, report-branch state and donor isolation.

### 37.1 P2-I-036 source verification

The goal-completion finding was checked against the exact donor source blobs:

- `Brain::assimilate_goal_outcome` appends and replays `goal_progress` before it attempts the separate `goal_complete` append. A failure of the second append returns `false` without undoing the first event.
- `Brain::replay` invokes `process_affective_experience` before its event-specific dispatch. The `goal_progress` branch updates the goal projection only when `progress < 1.0`; the `goal_complete` branch performs the completion transition.
- `GoalModel::update_progress` can set status to completed at progress 1.0, but the replay guard deliberately prevents the `goal_progress(progress=1.0)` event from invoking that method.
- Therefore a successful first append followed by a failed second append leaves a persisted 100% progress event that affects affective state but does not reconstruct goal completion. The same replay behavior persists after restart until a `goal_complete` event is successfully recorded.
- The cited goal-feedback test covers successful progress, successful completion, terminal-goal rejection and successful restart. It does not inject failure between the two completion appends.

The conditional failure sequence is source-supported but not experimentally reproduced. P2-I-036 remains a valid, distinct medium-severity provisional finding. Its required second-append failure injection and retry/replay assertions remain open.

### 37.2 Finding-index and section reconciliation

- Active findings are P2-I-001 through P2-I-033, plus P2-I-035 and P2-I-036.
- P2-I-034 remains withdrawn and is not reused.
- P2-I-012 is the donor runtime-loop integration finding; the later CI correction is unnumbered.
- P2-I-013 is the mainline runtime/action-execution integration gap.
- P2-I-014 is the low-level journal rollback/startup-tail-repair finding.
- P2-I-023 is the multi-event action-learning atomicity finding.
- P2-I-035 is the queued-feedback evidence-persistence/completion-metric finding.
- P2-I-036 is the two-event goal-completion/replay finding.
- Sections are numbered consecutively through §37 with no duplicate section numbers. Repeated mentions of a finding are cross-references or expanded treatment, not additional IDs.

### 37.3 Repository and PR boundary

- Donor PR #97 remains open/draft at exact HEAD `c1da222e6c94aeb3f2ad000392c21fe4fc81ab25`, targeting `main`.
- The review report remains on `docs/jarvis-phase-2-whole-brain-integration-map-20261105`, PR #179 targeting `docs/jarvis-project-governance-rules-20261105`.
- The donor branch compares identical to its recorded HEAD; this review changed only the review report, not donor production code, tests, workflows or CMake configuration.
- The report remains a review artifact. Its findings and required tests are not implementation authorization.

### 37.4 Final decision

The additional goal-completion audit strengthens the failure/recovery map but does not close the relevant acceptance criteria. The report is ready for independent review of its evidence and severity judgments; deterministic failure injection, remaining BM-01/BM-02 provenance work, test-validity review, runtime integration boundaries and Project Director decisions remain outstanding.

**Final handoff status:** Phase 2 IN PROGRESS. Gate A NOT CLEARED. PR #97 remains an unmerged donor. No implementation baseline is selected, no donor is approved, and no implementation authorization is implied.


---

## 38. Finding P2-I-037 — Specialized perception-provider failures are not observable and provider isolation is incomplete

**Audit date:** 2026-11-06  
**Affected donor revision:** `c1da222e6c94aeb3f2ad000392c21fe4fc81ab25`  
**Severity:** Medium (provisional; the impact depends on whether downstream callers treat a fallback representation as complete interpretation).  
**Confidence:** High for the silent `perceive` failure/fallback path and missing failure telemetry; High for the C++ `noexcept` contract consequence; Medium for operational impact in a production provider deployment.  
**Status:** Confirmed observability/contract gap; no production provider outage is asserted.

### Source trace

1. `PerceptionPipeline::process` iterates registered providers. For each provider it invokes `supports(input)`, then `perceive(input, context)` if supported.
2. Exceptions from `perceive` are caught and discarded. Invalid provider representations are also silently skipped. If no provider returns a valid representation, the pipeline normalizes the raw event and returns that fallback.
3. The method's return type is only `PerceptualRepresentation`. It carries no provider selection/failure status, degraded-mode marker, failed-provider identity or structured diagnostic.
4. `CognitiveRuntimeMetrics` has no perception-provider failure/degradation counter. The cycle consumes the returned representation as its context representation; it cannot distinguish a provider-derived interpretation from fallback normalization by inspecting an explicit pipeline outcome.
5. `PerceptionProvider::supports` is declared `noexcept`. The `try/catch` around that call in `PerceptionPipeline::process` therefore does not make throwing implementations recoverable: an exception escaping a `noexcept` override terminates the process before the catch can handle it. The interface currently requires providers to be non-throwing in `supports`, but the implementation comment's broad provider-isolation language does not state or test this distinction.
6. The existing `ThrowingProvider` test throws from `perceive`, then asserts only that fallback output is valid. It does not assert that provider failure is recorded, surfaced to the cycle/runtime, or reflected in capability health. It cannot test a throwing `supports` implementation without violating the declared `noexcept` contract.

### Specification comparison

Accepted PR #174 BM-01 requires intake failures and missing evidence not to be converted into fabricated observations, and requires external experience to remain distinguishable from internal outputs. BM-02 requires interpretation to preserve uncertainty and alternatives. Its scenario 3 explicitly requires a provider failure to be recorded as a capability failure, not as evidence that the external event did not occur. The donor pipeline preserves the raw event and can provide a normalized fallback, which is useful degradation behavior; it does not expose the provider failure as a first-class result.

### Impact and boundary

- A provider can fail while the cycle still receives a valid fallback representation. That may be an acceptable degraded-mode continuation, but the caller has no typed evidence that specialized perception failed.
- A downstream consumer can therefore treat the fallback as an ordinary successful representation unless it independently knows the configured provider set and reconstructs failure state.
- Silent provider failure prevents operational capability-health monitoring and weakens later evaluation of whether a learning or decision change followed specialized interpretation or fallback normalization.
- The `supports noexcept` issue is narrower: it is a contract-design constraint, not a claim that the current test provider throws from `supports`.
- The report does not claim raw experience is lost, that fallback normalization is inherently wrong, or that a real deployment currently uses a throwing provider.

### Required Builder/Tester evidence

1. Define a structured perception result that distinguishes provider-selected representation, fallback normalization, invalid provider output, provider exception and no supporting provider. Preserve the raw acquired event and its immutable sequence/source lineage in every case.
2. Record provider identity, failure category and relevant diagnostic/correlation identity in an operational capability-health path. Do not encode provider failure as an observation about the external world.
3. Decide whether `supports` must be a total non-throwing predicate. If so, document and test that contract and remove the misleading catch or expose a safe non-throwing adapter. If provider failure must be isolated there too, remove `noexcept` and catch at the pipeline boundary.
4. Test: successful provider; no provider supports; provider `perceive` throws; provider returns invalid representation; first provider fails while a later provider succeeds; all providers fail and fallback is returned; and provider health recovers after a later successful call.
5. Assert both the returned representation and the failure/degradation telemetry, plus preservation of the original event sequence/source and no false external-world consequence.
6. Add an integration test proving that the runtime/workspace exposes degraded perception status without promoting the fallback into a claim of successful specialized interpretation.

### Source anchors

- [`PerceptionPipeline::process`](https://github.com/methaneex-oss/MethaneX/blob/c1da222e6c94aeb3f2ad000392c21fe4fc81ab25/core/cpp/src/perception_pipeline.cpp#L13-L50), blob `ab9a745bb68e416d4e32c9d0c26a2d0b2016ab17`.
- [`PerceptionProvider::supports` and provider contract](https://github.com/methaneex-oss/MethaneX/blob/c1da222e6c94aeb3f2ad000392c21fe4fc81ab25/core/cpp/include/jarvis/core/perception_pipeline.hpp#L25-L31), blob `1e5fed009a2453211dac1a4187ff47c5cc65da39`.
- [`CognitiveRuntimeMetrics`](https://github.com/methaneex-oss/MethaneX/blob/c1da222e6c94aeb3f2ad000392c21fe4fc81ab25/core/cpp/include/jarvis/core/cognitive_runtime.hpp#L42-L59), blob `e5a3c853add8b5fcb9b8c04c9b25f20179b5b629`.
- [`ThrowingProvider` fallback test](https://github.com/methaneex-oss/MethaneX/blob/c1da222e6c94aeb3f2ad000392c21fe4fc81ab25/core/cpp/tests/perception_pipeline_suite.cpp#L39-L44) and [asserted fallback behavior](https://github.com/methaneex-oss/MethaneX/blob/c1da222e6c94aeb3f2ad000392c21fe4fc81ab25/core/cpp/tests/perception_pipeline_suite.cpp#L72-L78), blob `2312d9f86763a05d7eef9e341d7b1d60bfe845e9`.
- [Accepted BM-02 provider-failure scenario](https://github.com/methaneex-oss/MethaneX/blob/0811a59e46bf934e32e794f90e4e7d18d4e2bd97/docs/architecture/specifications/00_BRAIN_MECHANISM_SPECIFICATION.md#L752-L760), blob `3b6a53c8a295fa0d9fc29bbb6c7688b61d1dcdb1`.

**Finding disposition:** P2-I-037 is a distinct BM-02/BM-11 observability and failure-contract finding. It does not duplicate the general representation/grounding gap or the external consequence observer provenance findings. It remains open pending structured failure reporting and tests.


---

## 39. Final self-review — provider failure finding, exit blockers and repository boundary

**Audit date:** 2026-11-06  
**Scope:** Independent consistency pass after adding P2-I-037.

### 39.1 Finding and source consistency

- P2-I-037 is present as a new finding and does not reuse P2-I-034, which remains withdrawn.
- The `perceive` exception path, fallback behavior and absence of an explicit provider-failure result are grounded in the exact donor blobs cited above.
- The `supports noexcept` consequence is described as a contract limitation; no claim is made that a conforming implementation can throw and be caught.
- The existing test's scope is described accurately: it exercises a throwing `perceive`, validates fallback output and does not assert a capability-failure record.
- The accepted specification's provider-failure scenario is cited separately from implementation evidence.
- The finding does not assert raw-event loss or a production incident.

### 39.2 Report structure and finding index

- Active findings are P2-I-001 through P2-I-033, plus P2-I-035, P2-I-036 and P2-I-037.
- P2-I-034 remains withdrawn and is not reused.
- Sections are numbered consecutively through §39; repeated references to existing findings remain cross-references.
- The BM-02 map and §25.4 exit blockers now point to P2-I-037 and require provider-failure observability in the remaining acquisition/perception trace.

### 39.3 Final repository boundary

- Donor source remains pinned to PR #97 HEAD `c1da222e6c94aeb3f2ad000392c21fe4fc81ab25`.
- This update is confined to the Phase 2 report branch and PR #179. No donor production source, test, workflow or build configuration was changed.
- Phase 2 remains IN PROGRESS. Gate A remains NOT CLEARED. PR #97 remains an unmerged donor; no implementation baseline is selected and no implementation authorization is implied.


---

## 40. Finding P2-I-038 — Runtime action authorization has no explicit grant freshness or revocation path

**Audit date:** 2026-11-06  
**Affected donor revision:** `c1da222e6c94aeb3f2ad000392c21fe4fc81ab25`  
**Severity:** Medium (provisional; actual risk depends on how the host supplies and updates governance permissions).  
**Confidence:** High that the inspected runtime contract carries a static authorization-context value and exposes no in-place refresh/revocation API; Medium that this creates stale authorization in a deployment because host lifecycle behavior is not established by the inspected repository.  
**Status:** Freshness/revocation capability not demonstrated; no unauthorized real-world action is asserted.

### Source trace

1. `ActionAuthorizationContext` contains only `granted_permissions`, `maximum_risk` and `require_reversible`. It has no issuer, policy version, grant identity, issue/expiry time, revocation epoch or freshness token.
2. `CognitiveRuntimeConfig` owns a `CognitiveActionAdapter`, whose `authorization` member is an `ActionAuthorizationContext` value. The `CognitiveRuntime` constructor moves the configuration into private `config_`; the public runtime API exposes no authorization-context update, policy-change notification or revocation operation.
3. `CognitiveRuntime::execute_actions` passes the stored `config_.action_adapter.authorization` into `Brain::execute_action` for each selected action.
4. `Brain::execute_action` performs an authorization check before creating an action-consequence prediction, then passes the same request context to `ActionExecutor::run`, which checks it again immediately before invoking the execution callback. The two checks are useful ordering but do not refresh the underlying grants; both consume the same copied context.
5. `ActionAuthorizer::authorize` validates assessment disposition, risk threshold, reversibility and membership of each required permission in the supplied vector. It does not consult an external authority or compare a policy version/freshness value.
6. The authorization test covers a missing permission, a matching permission, a risk denial and prevention of a denied execution callback. It does not cover permission revocation, expiry, policy-version change, stale queued work or host policy refresh.

### Specification and boundary comparison

Accepted PR #174 preserves governance as an external constraint rather than a Brain-created goal or permission. BM-06 also requires enough state to suspend and resume work without losing permissions or freshness information; BM-11 requires interruption, cancellation, resumption and recovery without fabricating completion. The inspected donor provides a clear separation between cognitive assessment and a supplied authorization context, but it does not define the lifecycle or freshness of that external context.

This is not a claim that every action needs a short time-to-live or that a static permission set is inherently unsafe in a single-process test harness. It is a claim that the repository does not establish how a running runtime learns that a previously granted permission has been revoked, expired or superseded. Rechecking the same in-memory value twice is not a revocation check.

### Impact and limits

- A host that changes its external policy while leaving the runtime alive has no demonstrated API in this contract to push the new policy into the existing runtime.
- A previously queued or assessed action could therefore be authorized against an old grant set if the host does not stop/recreate the runtime or provide an out-of-band enforcement layer.
- The repository does not establish whether production callers recreate the runtime on policy change, enforce authorization inside the external action adapter, or use an independent security boundary. Those possibilities must be verified before calling this an exploitable authorization bypass.
- Risk threshold and reversibility checks are local data checks; they do not establish user/operator consent, resource ownership, tenant scope, credential freshness or external governance approval.

### Required Builder/Tester evidence

1. Document the authoritative grant issuer and policy owner, and specify whether the runtime receives immutable per-session grants or must observe live policy changes.
2. If grants are immutable for a session, define the session boundary and prove policy changes terminate/cancel affected queued work before any subsequent side effect.
3. If grants can change in place, add a versioned authorization provider or explicit refresh/revocation contract. Bind an assessment/request to the policy version under which it was formed and revalidate against the current version immediately before execution.
4. Define stale-policy behavior: deny by default, preserve the cognitive intent/assessment as non-executed, record the denial separately, and do not count it as execution failure or external consequence.
5. Test revocation after assessment but before execution, revocation while an action waits in the input queue, expiry at the execution boundary, policy-version mismatch, refresh failure, and cancellation during runtime shutdown.
6. Demonstrate that a denial prevents the executor callback from running and remains distinguishable from a rejected cognitive assessment, an execution failure and a verified negative external consequence.
7. Verify the actual host/application boundary; if an independent authorization service enforces freshness, identify its source, contract, tests and failure behavior rather than assuming the in-process vector is the complete security boundary.

### Source anchors

- [`ActionAuthorizationContext`](https://github.com/methaneex-oss/MethaneX/blob/c1da222e6c94aeb3f2ad000392c21fe4fc81ab25/core/cpp/include/jarvis/core/action_authorization.hpp#L9-L19), blob `047f3f8d74c8558255750fbe14d29f7ae9153360`.
- [`CognitiveActionAdapter` and `CognitiveRuntimeConfig`](https://github.com/methaneex-oss/MethaneX/blob/c1da222e6c94aeb3f2ad000392c21fe4fc81ab25/core/cpp/include/jarvis/core/cognitive_runtime.hpp#L17-L40), blob `e5a3c853add8b5fcb9b8c04c9b25f20179b5b629`.
- [`CognitiveRuntime::execute_actions`](https://github.com/methaneex-oss/MethaneX/blob/c1da222e6c94aeb3f2ad000392c21fe4fc81ab25/core/cpp/src/cognitive_runtime.cpp#L112-L175), blob `cf00acb6abd52308343f3a0e7016e6173b945603`.
- [`Brain::execute_action`](https://github.com/methaneex-oss/MethaneX/blob/c1da222e6c94aeb3f2ad000392c21fe4fc81ab25/core/cpp/src/brain_action_execution.cpp#L8-L50), blob `3b66bafb438cd28790e6f25611b96c86f1eff05c`.
- [`ActionAuthorizer::authorize`](https://github.com/methaneex-oss/MethaneX/blob/c1da222e6c94aeb3f2ad000392c21fe4fc81ab25/core/cpp/src/action_authorization.cpp#L14-L45), blob `669bc86c8111ae9755bcd40715352b4fc71350d0`.
- [`Action authorization tests`](https://github.com/methaneex-oss/MethaneX/blob/c1da222e6c94aeb3f2ad000392c21fe4fc81ab25/core/cpp/tests/action_authorization_suite.cpp#L1-L48), blob `66127a2b574d5c44571332733edb800fb558bcaf`.
- [Accepted BM-06 permission/freshness preservation](https://github.com/methaneex-oss/MethaneX/blob/0811a59e46bf934e32e794f90e4e7d18d4e2bd97/docs/architecture/specifications/00_BRAIN_MECHANISM_SPECIFICATION.md#L307-L324), blob `3b6a53c8a295fa0d9fc29bbb6c7688b61d1dcdb1`.

**Finding disposition:** P2-I-038 is a distinct governance-context lifecycle gap. It is not the same as P2-I-030's partial external side-effect contract or P2-I-029's persistence acknowledgement. Keep it provisional until the real host policy lifecycle is inspected.


---

## 41. Final self-review — authorization lifecycle finding and repository boundary

**Audit date:** 2026-11-06  
**Scope:** Independent consistency pass after P2-I-038.

### 41.1 Evidence and claim-strength checks

- The finding is limited to the inspected C++ runtime/action path and does not assert that no external policy service exists outside the repository.
- The context is copied into runtime configuration and reused for each action; the report does not confuse the repeated local authorization check with a fresh external policy lookup.
- The required tests cover revocation/expiry at the execution boundary and queued work, while the finding explicitly allows a documented immutable-session design if cancellation/session semantics are proven.
- P2-I-038 is separate from P2-I-030 (partial external effects), P2-I-029 (action-outcome persistence acknowledgement) and P2-I-037 (perception-provider failure observability).

### 41.2 Finding and section index

- Active findings are P2-I-001 through P2-I-033, plus P2-I-035, P2-I-036, P2-I-037 and P2-I-038.
- P2-I-034 remains withdrawn and is not reused.
- Sections are numbered consecutively through §41; the BM-02/provider and authorization lifecycle additions are cross-referenced from the remaining exit blockers.

### 41.3 Final repository boundary

- Donor source remains pinned to PR #97 HEAD `c1da222e6c94aeb3f2ad000392c21fe4fc81ab25`.
- This update changes only the Phase 2 report branch and PR #179. It does not modify donor production code, tests, workflows or build configuration.
- Phase 2 remains IN PROGRESS. Gate A remains NOT CLEARED. PR #97 remains an unmerged donor; no implementation baseline is selected and no implementation authorization is implied.


---

## 42. Host-boundary audit for P2-I-038 — no in-repository authorization refresh owner identified

**Audit date:** 2026-11-06  
**Scope:** Follow the runtime authorization value beyond the cognitive C++ library into the checked-in TypeScript operator bridge and the separate engineering-agent subsystem. This is a repository-wide source-tree inspection at donor HEAD `c1da222e6c94aeb3f2ad000392c21fe4fc81ab25`, not an audit of external deployment infrastructure.

### 42.1 Findings from the cross-language boundary

- The TypeScript `BrainTransport` contract exposes `observe`, `decide` and `capabilities`; it does not expose action execution, authorization grants, grant refresh, revocation, policy version or expiry.
- `OperatorSession` explicitly documents that communication does not grant execution authority and that authorization remains inside the engineering/runtime boundary. Its implementation only wraps message transport (`send`, `receive`, `connected`). It does not issue, cache, refresh or revoke permissions.
- `AgentBridgeSession` is a message transport contract with participant/run/workspace identifiers. It has no authorization-policy lifecycle fields or callback.
- The C++ `engineering::EngineeringAuthorizer` is a separate agent/task-coordination interface. `EngineeringCoordinator::dispatch` and `dispatch_tracked` invoke its `authorize` method before dispatch, but this interface is not the `ActionAuthorizationContext` used by `CognitiveRuntime`/`Brain::execute_action`.
- The engineering test instantiates `AllowAllAuthorizer`, whose implementation unconditionally returns true. That is test wiring for the engineering-agent coordinator; it is not evidence that the cognitive runtime authorizes all actions, nor evidence of a production policy provider.
- The repository tree contains no checked-in adapter joining `OperatorSession`/`AgentBridgeTransport` to `CognitiveRuntime` authorization refresh, and no identified policy issuer implementation that can establish the runtime's grant lifecycle.

### 42.2 Revised interpretation of P2-I-038

The prior finding remains correctly scoped as a missing lifecycle contract in the inspected cognitive-runtime path. This cross-boundary inspection removes one possible but unsupported assumption: the checked-in TypeScript operator bridge is not the missing grant-refresh mechanism, and the engineering-agent authorizer is not interchangeable with the Brain action authorizer.

Do not conclude that no external host policy exists. The repository does not contain the deployment host or an identified external authorization service implementation. Therefore the operational question remains unresolved outside the inspected tree. P2-I-038 should remain **Medium / High source-level confidence / UNRESOLVED at system boundary**, rather than being promoted to a confirmed exploitable security vulnerability.

### 42.3 Required evidence to resolve the boundary

1. Identify the actual executable/application host that constructs `CognitiveRuntimeConfig` and supplies `ActionAuthorizationContext`.
2. If that host is outside this repository, obtain its source/contract and identify the policy issuer, grant lifetime, revocation delivery, runtime replacement/cancellation semantics and fail-closed behavior.
3. Prove whether a policy change can occur while the runtime remains alive and whether already assessed/queued actions are invalidated before executor invocation.
4. If the host intentionally creates immutable per-session grants, define the session boundary and prove that revocation terminates the session and prevents all subsequent side effects. A process restart must not silently resume stale queued work.
5. Add an end-to-end test at the actual host/runtime boundary. Unit tests of `ActionAuthorizer` with a copied vector cannot establish external policy freshness.

### 42.4 Exact source anchors

- [`BrainTransport` observation/decision interface](https://github.com/methaneex-oss/MethaneX/blob/c1da222e6c94aeb3f2ad000392c21fe4fc81ab25/interfaces/typescript/src/brain.ts), blob `291916d45af0c67180542f8d775dba8b8ec1976f`.
- [`OperatorSession` governance-boundary contract and transport-only implementation](https://github.com/methaneex-oss/MethaneX/blob/c1da222e6c94aeb3f2ad000392c21fe4fc81ab25/interfaces/typescript/src/operator_session.ts), blob `2a699a78bc5beb31ed07cd913e0a527bb64d6bcf`.
- [`AgentBridgeSession` transport contract](https://github.com/methaneex-oss/MethaneX/blob/c1da222e6c94aeb3f2ad000392c21fe4fc81ab25/interfaces/typescript/src/agent_bridge.ts), blob `cd86f7d5f44e2d30c0401bb4bf02e05328d1c038`.
- [`EngineeringAuthorizer` and `AllowAllAuthorizer`](https://github.com/methaneex-oss/MethaneX/blob/c1da222e6c94aeb3f2ad000392c21fe4fc81ab25/engineering/cpp/include/jarvis/engineering/execution.hpp), blob `2bf187c48bee71bda48ecac6f7135cba3cc7495b`.
- [`EngineeringCoordinator` authorization call sites](https://github.com/methaneex-oss/MethaneX/blob/c1da222e6c94aeb3f2ad000392c21fe4fc81ab25/engineering/cpp/src/coordinator.cpp), blob `e175dd61aaa3d8302aba6381401305db9f034062`.
- [`AllowAllAuthorizer` test wiring](https://github.com/methaneex-oss/MethaneX/blob/c1da222e6c94aeb3f2ad000392c21fe4fc81ab25/engineering/cpp/tests/agent_and_console_suite.cpp), blob `7ac8c21e6df0d157d4d95fe87fabae962734139a`.

**Disposition:** P2-I-038 remains open. The TypeScript operator bridge and engineering-agent authorizer do not close the Brain runtime grant-lifecycle gap. No production authorization bypass is established. Phase 2 remains IN PROGRESS; Gate A remains NOT CLEARED.


---

## 43. Self-review — authorization host-boundary trace and report consistency

**Audit date:** 2026-11-06  
**Scope:** Validate §42 against the exact donor blobs, ensure authorization domains are not conflated, and reconcile the report/PR boundary.

### 43.1 Independent checks

- Re-fetched the exact `BrainTransport`, `OperatorSession`, `AgentBridgeSession`, `EngineeringAuthorizer`, `EngineeringCoordinator` and engineering test files at donor HEAD `c1da222e6c94aeb3f2ad000392c21fe4fc81ab25`; the blob identities recorded in §42 match.
- Confirmed `OperatorSession` sends and receives messages only. Its comment expressly leaves execution authority inside the engineering/runtime boundary; no grant issuer or refresh path is implemented there.
- Confirmed `EngineeringCoordinator` calls its injected `EngineeringAuthorizer`, while the engineering test uses `AllowAllAuthorizer`. This is a separate agent-task dispatch path and is not the `ActionAuthorizationContext` consumed by the Brain action path.
- The donor repository tree contains 260 tracked files at the audited commit. No matching application-host, runtime-host, authorization-provider or authorization-service source path was identified by the targeted tree-name inspection. This is a bounded repository search, not proof that external deployment infrastructure does not exist.
- The report correctly avoids calling this an exploitable bypass. The missing host lifecycle evidence keeps the operational risk unresolved and the finding open.

### 43.2 Index and status reconciliation

- Active findings remain P2-I-001 through P2-I-033, plus P2-I-035 through P2-I-038. P2-I-034 remains withdrawn.
- P2-I-038 remains a distinct Brain action-authorization grant lifecycle finding; §42 adds boundary evidence and does not create a duplicate finding.
- Report sections are consecutively numbered through §43.
- Donor PR #97 remains open/draft and unmerged. Review PR #179 remains open on the Phase 2 report branch. No donor source, tests, workflow or build files were changed.

### 43.3 Handoff

The next evidence owner is the Builder/Project Director: identify the executable host and authoritative policy lifecycle, or explicitly establish that the runtime's grant context is immutable for a bounded session and show how revocation terminates that session and invalidates pending work. The Independent Tester should then exercise revocation/expiry at the real host-to-executor boundary. Until that evidence exists, P2-I-038 and Gate A remain open.

**Phase 2 status:** IN PROGRESS. **Gate A:** NOT CLEARED. No implementation baseline selected; no donor approved; no implementation authorization implied.


---

## 44. Consolidated Phase 2 closure plan after findings P2-I-037 and P2-I-038

**Audit date:** 2026-11-06  
**Purpose:** Replace the earlier broad exit-blocker wording with a dependency-aware closure sequence. This section is a review handoff, not an implementation authorization or claim that Phase 2 is complete.

### 44.1 What this investigation has now established

1. The BM-01–BM-12 capability map exists and is source-anchored against the accepted PR #174 specification, the audited main baseline and the PR #97 donor revision.
2. The report has identified concrete cross-mechanism defects and limitations beyond missing modules, including disconnected memory/reasoning use, narrow goal formation, partial persistence/feedback boundaries, action execution ambiguity, specialized perception failure observability and the unresolved host authorization lifecycle.
3. PR #97 contains a substantial integrated donor implementation and meaningful exact-HEAD CI evidence, but remains a draft, unmerged donor. Its existence and test results do not establish compatibility with current main or satisfy Gate A.
4. The report distinguishes source-derived failure paths from reproduced runtime incidents. P2-I-035, P2-I-036 and P2-I-038 remain open; P2-I-037 remains open pending structured failure reporting and tests.
5. The TypeScript operator bridge and engineering-agent authorization path were traced and are not the missing Brain action-grant refresh owner. The external application/deployment host remains unidentified in this repository.
6. No production source, test, workflow or CMake file was changed by this review batch. No runtime experiment or new test execution is claimed by §§40–44.

### 44.2 Dependency-aware order of work

**Priority 1 — establish the real system boundary**

- Identify the actual executable that constructs the Brain/runtime, supplies external observations, invokes actions and reports consequences.
- Trace every supported language/API entrypoint from external input to typed experience/provenance and from selected action to executor/observer.
- Establish the authoritative governance owner and the lifetime of its grants.
- This is a prerequisite to claiming whole-system provenance or authorization correctness. The current C++ library audit alone cannot establish deployed behavior.

**Priority 2 — close acquisition/perception truthfulness (BM-01/BM-02)**

- Resolve P2-I-037 with typed provider outcomes, observable failure/degraded-mode state and preserved raw-event lineage.
- Decide and test the `supports noexcept` contract; do not claim exception isolation where C++ termination semantics prevent it.
- Trace contextual language/operator-intent grounding separately from candidate-goal formation.
- Demonstrate that provider failure is not converted into a false statement about the external event.

**Priority 3 — close execution, evidence and recovery semantics (BM-09/BM-11)**

- Resolve the host authorization lifecycle (P2-I-038) before treating the action path as safe for live operation.
- Define and test the executor's partial/unknown side-effect result (P2-I-030), persistence acknowledgement (P2-I-029), action-feedback partial commits (P2-I-023), queued-feedback completion accounting (P2-I-035), and goal-completion two-event recovery (P2-I-036).
- Inject failures at each durable append and external-effect boundary; verify replay, retries, idempotency, compensation and caller-visible status.
- Keep cognitive assessment, policy denial, execution failure, unknown effect and verified external consequence as distinct states.

**Priority 4 — verify learning claims and test validity**

- Review each learning test's causal path: experience/evidence → update → durable state → changed future computation.
- Require matched learning-disabled controls where a claim attributes improvement to learning or transfer.
- Separate unit/helper tests, production runtime-path tests, persistence/restart tests and end-to-end host integration tests.
- Report per-seed and held-out results, uncertainty and limitations; do not infer broad intelligence from a narrow synthetic task.

**Priority 5 — independent decision and governance**

- Have the Independent Tester reproduce the open failure paths and verify runtime behavior at the real host boundary.
- Have an independent reviewer challenge the source map, severity, evidence quality and acceptance criteria.
- Have the Project Director decide the PR #179/#180 documentation disposition and explicitly authorize any next implementation scope.
- Only then decide whether a donor baseline is suitable. Do not merge PR #97 by implication.

### 44.3 Explicit ownership handoff

| Work item | Primary evidence owner | Required output |
|---|---|---|
| Host/runtime/application boundary and grant issuer | Main Builder / Project Director | Exact entrypoint, construction path, policy owner and lifecycle contract |
| Provider failure/degraded-mode contract (P2-I-037) | Main Builder; Tester verifies | Typed result, raw-event lineage, failure telemetry, recovery tests |
| Authorization freshness/revocation (P2-I-038) | Builder identifies host; Tester exercises | Revocation/expiry test at executor boundary or proven immutable-session cancellation |
| Persistence and multi-event recovery (P2-I-023/035/036) | Tester, with Builder-provided harness | Deterministic append-failure matrix and replay/retry evidence |
| Learning-test causal validity and controls | Independent Tester | Matched controls, held-out trials, per-seed metrics and artifact review |
| Phase 2 report and Gate A decision | Independent Reviewer / Project Director | Independent report review and separate explicit gate decision |
| Main perception production integration (IR-01) | Main Builder; Independent Tester verifies after separate implementation authorization | Main CognitiveCycle caller/dataflow and production-path provider/fallback tests; no donor code port implied |
| Donor BM-11 fairness/shutdown/result recovery (IR-03) | Main Builder defines contract; Independent Tester verifies donor behavior | Sustained-load fairness, in-flight-action shutdown, result saturation, restart/retry/idempotency test evidence |
| PR #173 / PR #174 finding provenance (IR-02) | Main Builder recovers records; Project Director accepts bounded source limitation if unrecoverable | Separate status ledger; original PR #174 follow-on review artifact recovered or its absence explicitly accepted |
| Human/MCU comparison artifact (IR-04) | Main Builder / architecture evidence owner; Independent Reviewer challenges | `PHASE_2_HUMAN_AND_MCU_REFERENCE_COMPARISON_2026-11-06.md`; Project Director accepts or approves deferral |
| R3-01 legacy phase-scope conflict | Main Builder documents scope; Project Director confirms interpretation; Independent Reviewer verifies | Scope notice in legacy completion document, current-authority link and repository conflict register |
| R3-02 Memory metadata recovery | Main Builder defines/implements only after authorization; Independent Tester verifies | Corrupt/truncated/missing metadata recovery contract, deterministic tests and caller-visible status |
| R3-03 competing PR #179/#180 report authority | Project Director decides; Main Builder records decision | One selected working authority, explicit disposition of the other PR, no silent duplicate same-path deliverables |
| R3-04 empty-premise reasoning result | Main Builder defines/implements only after authorization; Independent Tester verifies | Specification-conformant unresolved result and deterministic empty-premise acceptance test |

### 44.4 Acceptance rule

Phase 2 may be called complete only when its defined source-map, cross-boundary, test-validity and independent-review deliverables are actually closed, with unavailable evidence explicitly resolved or accepted by the Project Director as a bounded limitation. Gate A remains a separate decision and cannot be cleared by completion of this report.

**Current decision:** Phase 2 IN PROGRESS. Gate A NOT CLEARED. PR #97 remains draft/unmerged and is not an approved implementation baseline. P2-I-035 through P2-I-038 remain active findings; P2-I-034 remains withdrawn. No implementation authorization is implied.


---

## 45. Independent review response — IR-01 through IR-04

**Response date:** 2026-11-06  
**Review source:** PR #183, review commit `30eaefe3bee02e2038f66fb18c907673026ebe76`  
**Primary report revision being corrected:** PR #179 prior HEAD `e6a824e820dd91a19a1f54c5460079eec02a7306`  
**Scope:** Documentation correction and source verification only. No production implementation, donor port, gate decision or baseline selection is authorized.

### 45.1 Repository snapshot and ancestry verification

The following state was re-fetched before this correction:

| Reference | Verified state at response start |
|---|---|
| `main` | `1273ddbcd0087d189e01388ded2d362fb1e058d2` |
| PR #179 | Open/draft/unmerged; branch `docs/jarvis-phase-2-whole-brain-integration-map-20261105`; HEAD `e6a824e820dd91a19a1f54c5460079eec02a7306`; base `docs/jarvis-project-governance-rules-20261105` at `39fe09dcf13496f5f0005ccf3f00739303e29f88` |
| PR #180 | Open/draft/unmerged; branch `research/phase-2-brain-integration-map-20261105`; HEAD `6ca140300b914ed981a50301bbf1d82a5bfe4d8b`; base `spec/brain-mechanism-specification-20261103` at `0811a59e46bf934e32e794f90e4e7d18d4e2bd97` |
| PR #183 | Open, non-draft, unmerged; branch `review/phase-2-independent-review-20261106`; HEAD `30eaefe3bee02e2038f66fb18c907673026ebe76`; base `main` at `1273ddbcd0087d189e01388ded2d362fb1e058d2` |
| PR #97 donor | Exact inspected donor HEAD `c1da222e6c94aeb3f2ad000392c21fe4fc81ab25`; remains a separate unmerged donor reference |

The PR #179 and #180 branches are not successive revisions of one branch. Their comparison has common merge base `1273ddbcd0087d189e01388ded2d362fb1e058d2`; comparing #180 HEAD to #179 HEAD reports divergence (78 commits ahead and 13 behind in that direction). Each PR adds the same report path against a different base. PR #179 remains the broader working report; PR #180's branch/history is preserved and no merge or closure is performed by this correction. Project Director disposition remains required.

The complete 3,052-line PR #179 report and complete PR #183 review were fetched at their exact starting heads. The review's four findings are addressed below. The report's prior evidence, historical sections and findings register are retained; this response does not rewrite the reviewer's document.

### 45.2 IR-01 — Main perception pipeline is not connected to main CognitiveCycle

**Disposition:** AGREE. **Confidence:** High. **Status:** Confirmed main-branch integration gap; correction is documentary, implementation remains open.

**Reviewer observation:** Main compiles the `PerceptionPipeline` source and registers its unit-test target, but the production main `CognitiveCycle` does not call it. This correction does not claim that the test was executed during this response. PR #97 donor has a different integration state.

**Independent source verification:**

- Main is pinned to `1273ddbcd0087d189e01388ded2d362fb1e058d2`. Main `core/cpp/include/jarvis/core/cognitive_cycle.hpp` does not include `perception_pipeline.hpp`, own a pipeline or expose provider registration.
- Main `core/cpp/src/cognitive_cycle.cpp` (`CognitiveCycle::run`) calls `brain_.observe(input.observation)`, retrieves memories using `input.observation.data`, reads beliefs/causal links and constructs reasoning premises. It does not call `PerceptionPipeline::process` or `RepresentationEngine::normalize`.
- Main `core/cpp/CMakeLists.txt` compiles `src/perception_pipeline.cpp`; `core/cpp/tests/CMakeLists.txt` registers `jarvis_perception_pipeline_suite` and its CTest entry. This proves compilation/test registration of the utility, not production call-path integration. The bounded main-branch search found no production caller.
- Donor PR #97 at `c1da222e6c94aeb3f2ad000392c21fe4fc81ab25` has a `CognitiveRuntime` constructor that registers configured providers with `cycle_.perception_pipeline()`, and donor `CognitiveCycle::run` invokes the pipeline. That is donor-only and remains subject to P2-I-037.

**Correction made:** §2.2 now marks the main BM-01→BM-02 production edge as unestablished and distinguishes the donor edge. §3 BM-02 now states the exact main call-path absence, compilation/test registration, absence of a production consumer, and donor-only integration. §3 BM-11 and this section preserve the separate runtime donor boundary.

**Remaining work / acceptance criteria:** Main integration remains unimplemented and unauthorized. Before it can be accepted in a later authorized implementation phase, evidence must include (a) an actual production caller from the main CognitiveCycle/runtime path, (b) a trace showing raw acquired event identity/provenance retained while the representation is produced, (c) a production-path test that injects a provider and demonstrates its representation reaches the intended downstream consumers rather than only testing the utility, (d) fallback/provider-failure behavior that preserves raw experience and exposes degraded status under P2-I-037, and (e) exact-head build and registered integration-test execution. A compiled source file or standalone unit test alone cannot close this gap.

### 45.3 IR-02 — PR #173 and PR #174 F-02/F-03 provenance must remain separate

**Disposition:** AGREE. **Confidence:** High. **Status:** Four separate obligations retained; the original PR #174 follow-on review artifact remains unavailable in the evidence inspected.

The report's §14 correctly identifies the meanings of PR #173 F-02/F-03, but did not separately preserve the later PR #174 follow-on review pair. The reconciliation table in §14.4 now contains all four distinct namespaces:

| Stable namespace for this report | Original finding meaning | Current source-backed status | Map / closure condition |
|---|---|---|---|
| PR #173 F-02 | Experience-acquired candidate-goal formation | OPEN; P2-I-015 says this is not demonstrated in inspected main or PR #97 donor paths | BM-08 / P2-I-015; close only with experience-to-candidate-goal formation and inspectable evidence lineage, or explicit authority-approved limitation |
| PR #173 F-03 | SYS-08 computational-substrate boundary | OPEN; P2-I-016 says the inspected C++ Memory boundary does not expose the required explicit SYS-08 contract | SYS-08 / P2-I-016; close with explicit substrate ownership/failure/acknowledgement/recovery contract and independent review |
| PR #174 follow-on F-02 | Contextual language/operator-intent grounding | OPEN specification-review obligation; BM-02's technical gap remains | BM-02; close with a corrected requirement and evidence that contextual grounding is not a fixed phrase/source lookup |
| PR #174 follow-on F-03 | Downstream reasoning integration | OPEN specification-review obligation; IF-03/AUD-12 source gap remains | BM-12 / IF-03; close with memory-supported premises and qualified reasoning outputs demonstrably affecting appropriate downstream computation |

**Provenance verification:** The PR #173 correction record `docs/architecture/reviews/02_BRAIN_FOUNDATION_ARCHITECTURE_REVIEW_CORRECTIONS_2026-11-03.md` at PR #173 corrected head `97191111bc2573c14d391c0af9628db7b11f194b` explicitly defines PR #173 F-02 as experience-acquired goal formation and PR #173 F-03 as the SYS-08 substrate boundary. The Phase 1 reconciliation record at PR #178 head `39fe09dcf13496f5f0005ccf3f00739303e29f88` states that a subsequent review report supplied in the conversation identified PR #174 follow-on F-02 as contextual language/operator-intent grounding and F-03 as downstream reasoning integration. It also records that the later report was not mirrored as a GitHub review submission. The PR #174 discussion history confirms historical acceptance of exact specification HEAD `0811a59e46bf934e32e794f90e4e7d18d4e2bd97` and later F-01 correction activity; the inspected PR #174 comments/review submissions do not contain the original F-02/F-03 review report.

**Limitation:** The original PR #174 follow-on reviewer document was not located in the checked-in correction records or PR #174 discussion/review objects inspected for this response; no exhaustive repository-wide document search was run. Its exact title, full text and reviewer line-level rationale cannot be independently recovered from these sources. The report preserves the source-backed summaries and explicitly records the missing artifact; it does not invent a verbatim finding. The Project Director must either supply/recover that original review artifact or explicitly accept its unavailability as a bounded provenance limitation. The historical PR #174 acceptance is not erased, and it does not clear these later follow-on obligations. No one finding closes another.

### 45.4 IR-03 — Donor runtime fairness, shutdown feedback and result loss

**Disposition:** AGREE with the source-visible control-flow observations. **Confidence:** High for source semantics; operational consequences are conditional. **Status:** Control-flow properties confirmed; no production incident or reproduced failure claimed.

**Exact donor source inspected:** `core/cpp/src/cognitive_runtime.cpp` blob `cf00acb6abd52308343f3a0e7016e6173b945603`; corresponding header `core/cpp/include/jarvis/core/cognitive_runtime.hpp`; donor test `core/cpp/tests/cognitive_runtime_suite.cpp`. All are pinned to PR #97 HEAD `c1da222e6c94aeb3f2ad000392c21fe4fc81ab25`.

**Verified control-flow properties:**

1. `worker_loop` chooses a feedback item whenever `feedback_` is non-empty and chooses input work only when feedback is empty. No feedback quota, aging rule or cross-queue fairness bound is visible in this loop. If producers maintain a non-empty feedback queue, queued inputs have no source-level bounded service guarantee. This is a conditional starvation risk, not a reproduced starvation incident.
2. `stop()` sets `stopping_ = true`. `submit_feedback()` rejects when `stopping_` is true (and increments `feedback_rejected`). `execute_actions()` submits secondary action evidence using `(void)submit_feedback(...)`, discarding the boolean result. Thus if shutdown begins during action execution, the action can finish while its follow-on feedback submission is rejected without an action-result field indicating that rejection. This is a source-derived race window, not a reproduced live failure.
3. `publish_result()` drops the oldest result when the bounded result queue is full and increments `dropped_results`. Aggregate loss is counted, but the inspected source does not establish per-result acknowledgement, caller reconciliation or a retry-safe idempotency protocol.
4. With `drain_on_stop`, the worker drains items already queued before stopping; that does not allow new feedback submissions after `stopping_` becomes true. This distinction is now explicit in BM-11.

**Existing-test boundary:** The donor `cognitive_runtime_suite.cpp` exercises normal action feedback, feedback processing/rejection for malformed or stale data, stop/start behavior and persistence/reconstruction. It does not establish sustained feedback-vs-input fairness, shutdown initiated while the executor callback is in flight, result queue saturation/loss reconciliation, or restart/retry idempotency across an unknown external side effect. No donor tests were executed by this documentation correction.

**Required test matrix and measurable acceptance:**

| Scenario | Required setup | Acceptance condition |
|---|---|---|
| Sustained feedback load / input fairness | Keep feedback producers active while one or more valid inputs remain queued | A documented finite feedback burst/quota or aging rule guarantees an eligible input is selected after no more than the configured maximum consecutive feedback dispatches; test asserts dispatch-count bound, not a machine-dependent wall-clock guess |
| Shutdown during action execution | Block an executor callback on a test barrier; initiate `stop()`; release the action and observe its secondary feedback submission | The completed action's feedback is either durably accepted before shutdown, or the action result/caller receives an explicit rejected/pending-recovery disposition with a stable correlation ID; no silent ignored false return |
| Result queue saturation | Configure a small result capacity, stop polling, and publish more completed results than capacity | Every dropped result is identifiable by sequence/correlation ID; metrics and caller API expose loss; caller can distinguish completed-but-unobserved from never-executed work |
| Restart/retry/idempotency | Crash/reconstruct after action side effect but before feedback/result acknowledgement; retry the same logical request | Stable idempotency key or durable execution ledger prevents duplicate external side effects; unknown effect remains unknown until independently reconciled; replay does not fabricate success/failure |
| Recovery accounting | Restart after queued feedback rejection and after result overflow | Persisted/replayed state reconciles accepted, rejected, processed, failed and unknown work without double-counting learning or goal progress |

**Correction made:** BM-11 now records the feedback-first scheduler, shutdown rejection window, ignored secondary submission result and drop-oldest result policy as donor-specific control-flow semantics. It explicitly separates these from confirmed incidents and cross-references this test matrix. Existing P2-I-023/P2-I-029/P2-I-030/P2-I-035/P2-I-036 remain separate; this response does not collapse them into a single queue finding.

**Remaining limitation:** No scheduler change, runtime instrumentation, test or failure injection was performed. These remain donor BM-11 verification obligations; they do not establish that main has the donor runtime or that an incident has occurred.

### 45.5 IR-04 — Human and MCU comparison criterion has an owner and bounded artifact

**Disposition:** AGREE. **Confidence:** High. **Status:** Deliverable and ownership are now defined; the artifact itself remains outstanding.

The existing §9.10 comparison criterion is retained but now names a bounded deliverable:

- **Artifact:** `docs/architecture/reports/PHASE_2_HUMAN_AND_MCU_REFERENCE_COMPARISON_2026-11-06.md` (required; not yet created).
- **Primary owner:** Main Builder / architecture evidence owner.
- **Independent challenge:** Independent Reviewer verifies source quality, distinction between evidence and analogy, and whether comparisons materially affect decisions.
- **Authority:** Project Director accepts the deliverable or explicitly approves a bounded deferral.
- **Scope:** Compare substantial BM-01–BM-12 mechanism/integration decisions against (a) relevant human cognitive functions with appropriate scientific references, uncertainty and contested findings stated, and (b) MCU J.A.R.V.I.S. as fictional functional inspiration only. For each comparison, record the function being compared, what is established vs hypothesized, what the fiction contributes as a design analogy, what the actual repository implements, and the resulting engineering implication/limit.
- **Exclusions:** No literal biological imitation, anthropomorphic equivalence, MCU behavior treated as scientific evidence, or claim that resemblance establishes capability.

**Correction made:** §9.10 now assigns this artifact and its owners; §44.3 ownership table now lists the accountable evidence owners and outputs. The comparison requirement is not silently waived. Phase 2 remains open until the artifact is reviewed or the Project Director explicitly approves deferral.

### 45.6 Self-review, verification and approval boundary

**Documentation corrections applied in this revision:**

- §2.2 — main vs donor BM-01→BM-02 interaction edge.
- §3 BM-02 — production call-path absence on main; standalone compilation/test registration; donor-only integration.
- §3 BM-11 — donor scheduling, shutdown feedback rejection and bounded result-queue loss semantics.
- §9.10 — bounded human/MCU comparison artifact, owner, reviewer and Project Director authority.
- §14.4 — separate reconciliation rows for PR #173 F-02/F-03 and PR #174 follow-on F-02/F-03; missing original PR #174 review artifact explicitly recorded.
- §44.3 — explicit owner/output rows for the four review-response workstreams.
- §45 — finding-by-finding response, exact source revisions, limitations and measurable acceptance criteria.

**Verification performed:** Repository metadata, exact PR heads/bases, main ref, source blobs, report/review files, PR #173 correction record, Phase 1 reconciliation record, PR #174 discussion history, and PR #179/#180 commit ancestry were re-fetched. The donor runtime test source was inspected for existing scenario coverage. No local shell command, build, CTest run, benchmark, sanitizer, runtime experiment or failure injection was executed as part of this documentation-only response. No test result is claimed.

**Files changed by this response:** This Phase 2 report only. The PR #183 independent review, PR #180 report/branch, production source, tests, CMake files, workflows and donor branch are unchanged.

**Current status:** Phase 2 remains IN PROGRESS. Gate A remains NOT CLEARED. Gate B is not assessed or cleared here. No implementation baseline is selected. PR #97 remains an unmerged donor. No production implementation, donor port, merge, deployment or gate clearance is authorized. The PR #174 follow-on F-02/F-03 source artifact and the human/MCU comparison deliverable remain outstanding. The IR-03 runtime scenarios remain unexecuted.

**Next action:** Submit this exact updated PR #179 head for independent re-review against IR-01 through IR-04. The reviewer should independently reproduce the main/donor perception call graph; verify the four-row finding provenance ledger and missing-source limitation; inspect donor scheduler/shutdown/result queue code and assess the acceptance matrix; and verify that the human/MCU comparison deliverable has a named owner and explicit Project Director disposition. The reviewer should retain the REVISE verdict unless the documented corrections and outstanding authority/evidence conditions are independently satisfied.


---

## 46. Third independent review response — R3-01 through R3-04

**Review source:** PR #190, review commit `a1df22531765b7022f6bfbcfd9f3f5251cf5adf5`.  
**Reviewed target:** PR #179 at `6f2c2cf05196e69a48f5deefcc3f4609e258c19a`.  
**Scope of this response:** Documentation, repository authority clarification and source-level defect recording. No production implementation, test code, donor port, gate decision, merge or baseline selection is authorized by this response.

### 46.1 R3-01 — Legacy Phase 2 completion document conflicts with whole-Brain status

**Disposition:** AGREE that the repository presents a material scope/status ambiguity. **Confidence:** High that the documents appear contradictory; medium on the intended historical meaning of the legacy document. **Status:** Documentation clarification applied; Project Director confirmation remains required.

**Evidence:** At the audited main baseline `1273ddbcd0087d189e01388ded2d362fb1e058d2`, `docs/JARVIS_PHASE_2_COMPLETION.md` (blob `7e001e63703bf07efe95c321c1f6c4272ae626f7`) names its phase as “Perception & Representation” and lists provider contracts, provider isolation, representation types, evidence/provenance, fallback normalization and CMake integration. It then says “Phase 2 is structurally complete and ready for system validation before Phase 3” and identifies the World Model as the next phase. The current whole-Brain report maps BM-01–BM-12 and explicitly remains IN PROGRESS.

**Interpretation boundary:** The legacy document's own `## Phase` field narrows its listed completed work to Perception & Representation. That is consistent with a completed work package or earlier phase taxonomy, but the document does not explicitly state that it is a historical sub-phase or that its “Phase 2” numbering is independent of the current whole-Brain Phase 2. The Builder must not silently rewrite the original decision as though that ambiguity had already been formally resolved.

**Correction applied:** The legacy document now carries a dated scope clarification immediately below its title. It preserves the original completion record, identifies the listed scope as Perception & Representation, states that it does not establish completion of the current whole-Brain BM-01–BM-12 Phase 2, and links to this current working integration map. The README development-status section now links to the current whole-Brain report. This is a clarification, not deletion or silent rewriting of the legacy record.

**Remaining authority decision:** The Project Director must confirm whether the legacy document is (a) a historical Perception & Representation work-package completion record under an earlier numbering scheme, or (b) an obsolete/incorrect whole-Brain Phase 2 completion claim. If (a), retain it as a scope-limited historical artifact. If (b), approve a superseded notice and authority-map entry. Until confirmed, the whole-Brain report remains the working Phase 2 status map and no completion claim is accepted from the legacy document.

**Acceptance evidence:** Exact updated legacy/README/report blobs; repository-wide search for other unqualified whole-Brain Phase 2 completion claims; Project Director's written scope disposition; independent verification of the cross-links and status wording. The current response has not performed an exhaustive repository-wide document search, so it does not claim that no other conflicting document exists.

### 46.2 R3-02 — Memory metadata recovery can silently produce partial restoration

**Disposition:** AGREE. **Confidence:** High for the inspected source semantics. **Status:** Source-confirmed mainline defect recorded; production fix and failure-injection tests remain unauthorized and open.

**Exact source:** Main baseline `1273ddbcd0087d189e01388ded2d362fb1e058d2`; `core/cpp/src/memory.cpp`, blob `ba72a897306d4761246d0deab2fbab37c49d372f`, `Memory::load_metadata` lines 160–189.

**Observed behavior:**

1. Failure to open the metadata file returns without a recovery result.
2. Invalid magic, missing/truncated header, or record count above `kMaxMetadataRecords` returns without a recovery result.
3. The loader applies each successfully decoded record directly to `metadata_` and increments `learned_tiers_` while iterating.
4. If a later record fails `read_metadata_record`, the function returns after earlier records have already been applied. There is no temporary all-or-nothing snapshot, rollback, quarantine marker, corrupt/degraded status or caller-visible error in this function.
5. Event-journal reconstruction and metadata restoration are distinct. A valid journal does not recreate the lost tier/salience/confidence snapshot. Records not restored retain the metadata defaults established during journal loading; previously applied records can remain partially restored.

This does not establish that event history is lost. It establishes that learned metadata can be missing or partially restored without an explicit recovery status, and that retrieval/tier behavior may therefore differ after restart. The existing successful restart/promotion coverage does not test malformed or truncated metadata. No corruption experiment was executed in this response.

**Required implementation contract (not implemented here):** Metadata restoration must have an explicit outcome such as restored, absent/first-run, corrupt, truncated, incompatible-version or I/O-failed. Decode/validate the complete snapshot before mutating live metadata, or otherwise guarantee rollback to a defined safe state. If recovery falls back to journal-derived defaults, expose degraded status and preserve enough evidence to diagnose/rebuild the metadata; do not silently present a partial snapshot as a complete restore. The exact recovery policy (fail construction, quarantine and rebuild, or continue degraded) requires an explicit design decision and must not be guessed in this documentation patch.

**Required deterministic tests:** valid metadata restore; absent metadata on first run; bad magic; truncated header; excessive count; truncation at every record boundary; invalid enum/value fields; unknown event sequence; valid first record followed by invalid second record; duplicate records; interrupted write; and restart after recovery. Assert no partial live-state mutation on failed validation, accurate recovery status, stable journal history, deterministic fallback metadata and no double-counting of `learned_tiers_`.

**Acceptance evidence:** Exact source-level contract; test coverage for the corruption matrix; failure-injection execution on the exact candidate SHA; restart/replay evidence proving retrieval/tier behavior is either restored or explicitly degraded; independent review. R3-02 remains open until these are completed under separate implementation authorization.

### 46.3 R3-03 — PR #179 and PR #180 compete for the same report path

**Disposition:** AGREE. **Confidence:** High. **Status:** Conflict documented; Project Director disposition required; no PR was closed, retargeted or merged.

**Verified repository state:** PR #179 is open/draft/unmerged at `6f2c2cf05196e69a48f5deefcc3f4609e258c19a`, based on `docs/jarvis-project-governance-rules-20261105`. PR #180 is open/draft/unmerged at `6ca140300b914ed981a50301bbf1d82a5bfe4d8b`, based on `spec/brain-mechanism-specification-20261103`. Both add `docs/architecture/reports/PHASE_2_WHOLE_BRAIN_CAPABILITY_TO_SOURCE_INTEGRATION_MAP_2026-11-05.md`. The branches have different bases and are not a simple linear succession. PR #179 is materially expanded and includes later review-response material; PR #180 remains an earlier investigation with its own base/provenance.

**Correction applied:** This report now records the two PRs as competing proposals for one canonical destination, rather than independent complementary deliverables. It identifies PR #179 as the current expanded working candidate for review, not as an already accepted or merged authority. PR #180 remains preserved and unmerged.

**Project Director decision required:** Select the canonical report branch/PR and explicitly disposition the other: close as superseded after preserving its provenance, retarget/reconcile it if its base contributes required material, or retain it only as a clearly labelled historical investigation outside the canonical destination. Do not merge both same-path files or assume that larger content alone grants authority. The Builder has not made this governance decision.

**Acceptance evidence:** Written Project Director decision; exact selected head/base; explicit disposition of the other PR; no two active PRs proposing conflicting contents for the same canonical path; independent verification that the chosen report links to the accepted specification and current governance authority.

### 46.4 R3-04 — Empty-premise reasoning reports a successful valid result

**Disposition:** AGREE. **Confidence:** High. **Status:** Mainline source/specification mismatch recorded; implementation and test remain unauthorized and open.

**Exact source:** Main baseline `1273ddbcd0087d189e01388ded2d362fb1e058d2`; `core/cpp/src/reasoning.cpp`, blob `feec78b2e8a1f2b0b58733fd509e4e5a750258fc`, `ReasoningEngine::solve` lines 84–89.

**Observed behavior:** When `problem.premises.empty()`, the implementation returns `ReasoningKind::consistency`, `valid=true`, `confidence=0.0`, and explanation “No premises were supplied.” The explanatory text and zero confidence signal absence of evidence, but `valid=true` remains a potentially misleading success predicate for callers. The inspected CognitiveCycle does not gate downstream processing on reasoning validity, which is a separate integration gap and is not repaired by this finding.

**Specification requirement:** The accepted BM-12 contract requires an explicit insufficient-evidence/unresolved result when no premises are supplied, rather than a successful substantive inference. The source behavior therefore violates the result contract even though confidence is zero. The specification's exact file path/line anchors must be preserved from the accepted PR #174 specification artifact when the implementation test is authored; the independent review cites the empty-premise rule at specification lines 801–810.

**Required acceptance test:** Construct a `ReasoningProblem` with no premises and arbitrary/empty causal links. Assert that the result is explicitly classified as insufficient-evidence/unresolved (or the exact accepted equivalent), contains no conclusions, does not carry a success/validity signal that callers can interpret as a supported inference, and exposes a stable machine-readable reason. Add companion cases with one supported premise and with contradictory premises to ensure the empty-input correction does not collapse ordinary consistency or contradiction behavior. Test downstream callers so an unresolved result cannot be consumed as a qualified conclusion.

**Required contract decision:** Prefer a distinct result status/kind for unresolved/insufficient evidence. If the existing `valid` field is retained, document whether it means structurally well-formed or evidentially supported; do not overload it ambiguously. The empty-premise path must never be represented as a successful substantive inference. No implementation choice is made in this report.

**Acceptance evidence:** Specification-to-enum/result mapping; deterministic empty-premise test and neighboring regression tests; exact-head build/CTest execution; downstream caller behavior; independent review. R3-04 remains open until verified.

### 46.5 Consolidated status and approval boundary

| Finding | Documentation response | Remaining status |
|---|---|---|
| R3-01 | Legacy scope clarification and README/report cross-links added | Project Director must confirm historical scope/supersession; repository-wide conflict search and independent verification remain |
| R3-02 | Main Memory partial-restore behavior and acceptance contract recorded | Production recovery contract, implementation authorization, corruption tests and runtime evidence remain open |
| R3-03 | Same-path PR conflict and decision options recorded | Project Director must select canonical authority and disposition the other PR |
| R3-04 | Empty-premise source/spec mismatch and deterministic acceptance test recorded | Result-contract decision, implementation authorization, tests and execution remain open |

No production code, tests, CMake files, workflows, donor files or runtime state were changed. No build, CTest run, benchmark, sanitizer or failure-injection experiment was executed. Phase 2 remains IN PROGRESS. Gate A remains NOT CLEARED. Gate B remains unassessed. No implementation baseline is selected. PR #97 remains an unmerged donor. No merge, donor approval, production fix or implementation authorization is implied.


---

## 47. Follow-up review response — mainline persistence findings R1 and R2

**Review source:** PR #188, `docs/architecture/reviews/PHASE_2_INDEPENDENT_REVIEW_FOLLOWUP_2026-11-06.md`, review HEAD `36b843f6959628a689d81bc1e12e523e17227073`.  
**Reviewed target in that report:** PR #179 at `6f2c2cf05196e69a48f5deefcc3f4609e258c19a`.  
**Current report branch before this response:** PR #179 at `ab1deaf5c18e27f04a3303870c8b5d494b99f6e7`.  
**Scope:** Documentation/source reconciliation only. No production source, tests, build configuration, donor code, gate state, baseline selection or implementation authorization is changed or implied.

### 47.1 R1 — Goal lifecycle mutates live state before journal acknowledgement

**Disposition:** AGREE. **Source confidence:** High. **Runtime impact:** Conditional on append failure; not reproduced in this response. **Status:** Mainline finding recorded; implementation and failure-injection verification remain open.

**Affected baseline and source identities:**
- Main: `1273ddbcd0087d189e01388ded2d362fb1e058d2`.
- `core/cpp/src/brain.cpp`, blob `e9f3758fcc9c0e89b7280ce376db9033d547682d`.
- `core/cpp/src/goals.cpp`, blob `778a829de8314e83b095af2f2c2a6b83baa769f4`.
- `core/cpp/src/memory.cpp`, blob `ba72a897306d4761246d0deab2fbab37c49d372f`.

**Verified transition ordering:** On the audited main source, `Brain::activate_goal`, `update_goal_progress`, `complete_goal`, `abandon_goal` and `set_goal_priority` first call the corresponding mutating `GoalModel` operation, then append the event to Memory. The GoalModel methods directly mutate the stored Goal. If `Memory::append` returns zero, the Brain wrapper returns failure but does not restore the previous GoalModel state. The live process can therefore observe a goal transition that has no committed journal event; a reconstructed Brain cannot replay that missing transition.

This finding is distinct from donor P2-I-036, which concerns the donor's two-event goal-progress/completion protocol. R1 concerns the mainline single-event wrapper ordering.

**Adjacent mutator audit:** The same ordering pattern is not confined to goal methods. The inspected main `brain.cpp` also shows:
- `isolate_capability` mutates SelfModel before appending `capability_isolate`;
- `restore_capability` mutates SelfModel before appending `capability_restore`;
- `isolate` mutates Resilience state before appending `resilience_isolate`;
- `rollback_evolution` mutates Evolution state before appending `evolution_rollback`;
- `observe_evolution_canary` obtains a controller decision that may already roll back an experiment, then attempts to append the rollback event.

By contrast, the inspected `create_goal`, `observe_capability`, `register_evolution_parameter` and `observe_evolution_fitness` append before applying their corresponding state mutation. `recover`, `adopt_evolution` and `adopt_evolution_experiment` attempt compensating state changes when append fails. These differences are recorded as source-level ordering categories, not as a claim that every path has been exhaustively tested or that every compensation is correct. The complete Brain mutator surface still requires a systematic inventory and failure-path verification.

**Required correction contract (not implemented here):**
1. Establish one explicit mutation/commit protocol for persistent Brain state.
2. For each transition, validate and prepare the state change before durable append; after append, application must be guaranteed not to fail under the held Brain lock, or use a verified compensation/transaction protocol.
3. A failed append must leave live state, journal sequence/content, counters and reconstructed state mutually consistent.
4. Do not fix only the five goal wrappers while leaving equivalent mutation-before-append paths in capability, resilience, evolution or canary transitions.
5. Preserve idempotent retry semantics and define what callers observe when commit or compensation cannot be confirmed.

**Required acceptance evidence:**
- A complete source inventory of Brain mutators, categorized as persist-before-apply, mutate-before-persist with compensation, mutate-before-persist without compensation, or non-persistent/derived.
- Deterministic append-failure injection for goal activation, progress, completion, abandonment and priority; successful controls for each.
- Equivalent failure tests for every sibling mutator found to use the same ordering pattern, including canary rollback.
- Assertions across method result, live state, Memory sequence/content, Brain counters, restart/replay and retry.
- Exact-head build and registered CTest execution, followed by independent review.

### 47.2 R2 — Mainline journal rollback and startup tail-repair errors are unchecked

**Disposition:** AGREE. **Source confidence:** High. **Data-loss/recovery sequence:** Conditional on filesystem failure; not reproduced in this response. **Status:** P2-I-014 scope extended to main; recovery contract and tests remain open.

**Affected baseline and source identity:**
- Main: `1273ddbcd0087d189e01388ded2d362fb1e058d2`.
- `core/cpp/src/memory.cpp`, blob `ba72a897306d4761246d0deab2fbab37c49d372f`.

**Verified mainline behavior:**
1. `Memory::persist` records the original journal size, writes and flushes an event, and checks the stream result. On write/flush failure it calls `std::filesystem::resize_file` to roll back to the original size, but does not inspect or surface the rollback error.
2. `Memory::load` scans to the last valid event boundary. If the file is longer than that boundary, it calls `resize_file` to truncate the malformed suffix, but does not inspect or surface the truncation error and does not quarantine the suffix before attempting repair.
3. `Memory::append` has no explicit poisoned/journal-recovery-required state. A failed persist returns zero, but the Memory instance is not marked unusable if rollback itself failed.
4. The inspected main loader reconstructs the valid prefix and then attempts repair. If repair fails, the object has no caller-visible indication that the journal may still contain an unreadable tail.

The donor P2-I-014 discussion must therefore not be represented as donor-only. Main has the unchecked append rollback and unchecked startup truncation path. The donor's startup path includes a quarantine-copy step before truncation; main's inspected path does not. The donor truncation result also requires verification rather than assuming quarantine alone guarantees successful repair.

**Conditional consequence:** If rollback or startup truncation fails, the journal may remain malformed. Without a poisoned/recovery-required state, a later append may be acknowledged behind that malformed region; a subsequent restart may stop at the earlier valid prefix and fail to recover later acknowledged records. This is a source-derived failure sequence, not an observed incident.

**Required correction contract (not implemented here):**
1. Define journal health states, including at least healthy, append/repair uncertain, recovery required and recovered.
2. If rollback or tail repair cannot be verified, Memory must reject further appends until a recovery procedure establishes a valid append point.
3. Surface rollback, quarantine and truncation failures to the owning Brain/caller through structured status; do not silently continue with uncertain journal integrity.
4. Preserve/quarantine malformed bytes before destructive repair where required by the recovery policy.
5. Specify the durability guarantee precisely. Stream flush is not equivalent to stable-storage durability after power loss or kernel crash.
6. Keep main and donor behavior separately mapped; do not silently port donor quarantine code or treat donor behavior as an approved baseline.

**Required acceptance evidence:**
- P2-I-014 affected-revision matrix updated to include main and distinguish main/donor startup-repair behavior.
- Deterministic injection for partial event write, append rollback failure, startup truncation failure, and donor quarantine-copy failure.
- After each injected failure, attempt another append, reconstruct/restart, and verify that every acknowledged event is recovered exactly once and no unacknowledged event is presented as committed.
- Verify that uncertain journal health blocks subsequent appends until recovery succeeds.
- Exact-head build/CTest execution and independent review.

### 47.3 Consolidated disposition and authority boundary

| Review item | Documentation response | Remaining status |
|---|---|---|
| R1 — main goal mutation-before-append | Confirmed and recorded; adjacent mutator ordering categories added | Open; implementation authorization, complete mutator audit, deterministic failure tests and independent verification required |
| R2 — main journal rollback/tail repair | Confirmed and recorded; P2-I-014 scope extended from donor-only to main plus donor | Open; journal-health/recovery contract, fault injection, restart/replay proof and independent verification required |
| R3-01 through R3-04 | Responses remain in §46 | R3-01 Project Director scope confirmation; R3-02/R3-04 technical implementation and tests; R3-03 Project Director PR disposition |

**Review-process limitation:** PR #188 publishes the technical findings and states that the connected GitHub identity is also the author of PR #179. It explicitly records that a formal `REQUEST_CHANGES` review could not be submitted from that identity. This documentation response treats R1/R2 as findings requiring reconciliation, but neither PR #188 nor this Builder response satisfies the repository's genuinely separate reviewer-identity requirement. A separate reviewer must verify the corrected report and submit the required formal review.

**Verification boundary:** Source files were re-fetched at main and their blob identities match those cited above. No local build, CTest, sanitizer, runtime experiment, filesystem fault injection or end-to-end test was run for this response. No runtime behavior is claimed as reproduced.

**Current status:** Phase 2 remains IN PROGRESS. Gate A remains NOT CLEARED in the current report record. Gate B remains unassessed in this report. No implementation baseline is selected. PR #97 remains an unmerged donor. No production implementation, donor port, merge or gate clearance is authorized.


---

## 48. Project Director disposition — canonical Phase 2 report (2026-11-06)

**Decision authority:** Project Director decision communicated on 2026-11-06 in the project conversation.  
**Decision:** PR #179 is selected as the canonical *working* Phase 2 Whole-Brain Capability-to-Source Integration Map. PR #180 is designated a historical first-pass precursor and is superseded for the canonical report path. This is a report-authority decision only; it does not accept or merge PR #179, approve PR #178's proposed governance baseline, clear any gate, select an implementation baseline, approve PR #97, or authorize production implementation.

**Verified selection snapshot:**

- PR #179 was open, draft and unmerged at HEAD `553fb2a179ed34bd637127b1cce7a7885301441a`, branch `docs/jarvis-phase-2-whole-brain-integration-map-20261105`, with base `docs/jarvis-project-governance-rules-20261105`.
- PR #180 was open, draft and unmerged at HEAD `6ca140300b914ed981a50301bbf1d82a5bfe4d8b`, branch `research/phase-2-brain-integration-map-20261105`, with base `spec/brain-mechanism-specification-20261103`.
- Both PRs add the same canonical report path. Their histories are divergent and their bases differ; they are not a safe pair of reports to merge independently.
- PR #180's initial BM-01–BM-12 mapping and its concrete first-pass observations are retained in the expanded PR #179 report. In particular, the memory-to-reasoning premise gap, lack of a downstream reasoning consumer in the inspected cycle, narrow reasoning scope, absence of demonstrated experience-acquired goal formation, and causal-confounding limitations remain represented. PR #179 adds the subsequent source tracing, review responses, evidence qualifications, donor/main distinctions and closure criteria. No distinct PR #180 finding identified in the inspected 310-line initial report was found to be lost from the expanded report.

**Disposition:** Preserve PR #180 and its commit history as historical provenance. Do not merge it. Close PR #180 as superseded by PR #179, with an explanatory closure comment linking this decision and the canonical PR. Keep PR #179 open and draft pending the remaining Phase 2 work and independent review. Do not merge PR #179 merely because it is now the selected working authority.

**Remaining Phase 2 obligations:** R3-02 Memory metadata recovery and R3-04 empty-premise reasoning remain open technical defects requiring separately authorized implementation and tests. R3-01's legacy-document scope interpretation still requires explicit confirmation; the existing clarification is not a final historical taxonomy decision. Repository-wide authority/conflict search and independent verification remain outstanding. Phase 2 remains IN PROGRESS; Gate A remains NOT CLEARED in the current report record; Gate B remains unassessed. No implementation baseline or production implementation authorization is established.

**Verification boundary:** This decision records report authority and PR disposition only. It does not claim that R3-02/R3-04 have been fixed, that tests have been run, or that the current report has passed independent re-review.


---

## 49. Project Director Phase 2 completion directive — scope and clearance boundary (2026-11-06)

The Project Director instructed the Main Builder to finish Phase 2 and ensure that all applicable obligations are cleared.

### 49.1 Legacy Phase 2 document scope

The Project Director's response was: “Ok finish phase tow and make sure everything is cleared,” following the Builder's direct question whether `docs/JARVIS_PHASE_2_COMPLETION.md` describes an earlier, narrower Perception & Representation work package rather than the current whole-Brain Phase 2.

**Working interpretation:** The response authorizes the Builder to proceed on the narrower-work-package interpretation for purposes of Phase 2 reconciliation. The legacy document's own `Phase` field names “Perception & Representation”; it must therefore not be used as evidence that the current BM-01–BM-12 whole-Brain Phase 2 is complete.

**Authority precision:** Because the response did not restate the scope distinction explicitly, this interpretation is recorded as the working disposition, not as a fabricated verbatim Project Director decision. The legacy completion claim remains preserved as historical source text. The current whole-Brain report remains the working authority for the present Phase 2 investigation. A separate explicit owner decision may still be required if governance acceptance demands a durable decision record outside this conversation.

### 49.2 Completion is not equivalent to gate clearance

The instruction to finish Phase 2 does not itself clear Gate A, Gate B, authorize runtime changes, select an implementation baseline, approve donor code, or waive independent review. These are separate controls and require their own evidence and authority.

At this report revision:
- Phase 2 remains **IN PROGRESS**.
- Gate A remains **NOT CLEARED** in the latest verified governance/Phase 1 record.
- Gate B remains **UNASSESSED**; no authoritative clearance record was found in the bounded search performed for this update.
- No implementation baseline is selected.
- No runtime implementation authorization is recorded.
- The Main Builder cannot satisfy the independent-review requirement by reviewing its own changes.

### 49.3 Required closure discipline

The Builder must close each Phase 2 obligation with one of the following evidence-backed dispositions: completed and verified; accepted with explicit owner authority; deferred with owner, rationale and carry-forward; or blocked with exact dependency. “Everything cleared” must not be used as a status claim while any mandatory gate, acceptance review, test, owner decision or traceability obligation remains open.



---

## 50. Follow-up source audit and missing reference deliverable (2026-11-06)

### 50.1 Human-cognition and MCU J.A.R.V.I.S. comparison

The required comparison artifact has now been drafted in:

- `docs/architecture/reports/PHASE_2_HUMAN_AND_MCU_REFERENCE_COMPARISON_2026-11-06.md`
- PR #191, draft and unmerged, head `609d38ede50bbdd98a93dfed112781eacabee9fd`.

It covers BM-01 through BM-12 and distinguishes empirical human-cognition references, fictional MCU inspiration and concrete software mechanisms. Each mechanism has a functional overlap, difference, inference limit and test direction. The scientific discussion explicitly qualifies contested predictive-processing claims and domain-generality claims about metacognition.

**Disposition:** Deliverable drafted; independent challenge and Project Director acceptance remain open. PR #191 is not merged and must not be treated as an accepted authority.

### 50.2 R3-02 — Memory metadata recovery: refined source-level findings

**Exact audited main baseline:** `1273ddbcd0087d189e01388ded2d362fb1e058d2`.  
**Source:** `core/cpp/src/memory.cpp`, blob `ba72a897306d4761246d0deab2fbab37c49d372f`; `core/cpp/include/jarvis/core/memory.hpp`, blob `f3662038237246efa51155f940d77564f144d6d9`.

The bounded re-read confirms:

1. Metadata header handling returns silently when the file cannot be opened, magic is invalid, the count header is truncated or the count exceeds `kMaxMetadataRecords`. The caller receives no distinction between first-run absence, corruption, truncation, incompatibility or I/O failure.
2. Records are decoded and applied one at a time directly to live `metadata_` entries. A later malformed/truncated record returns after earlier records have already changed tier/salience/confidence and incremented `learned_tiers_`. This is a partial-restore path.
3. A metadata record whose sequence is not present in the journal is silently skipped. Duplicate sequence records are not rejected; each accepted duplicate can increment the learned-tier aggregate again. Trailing bytes after the declared record count are not checked in the inspected function.
4. The format exposes a magic value and count but no separately decoded schema/version field in this implementation. A magic change may be treated as a generic invalid header rather than a caller-visible incompatible-version result.
5. The existing `jarvis_memory_architecture_suite` tests a successful promotion/snapshot/restart path and restored tier/salience/confidence. It does not exercise malformed metadata, partial-record failure, duplicate/unknown sequence, invalid enum/value, trailing bytes or no-partial-mutation guarantees. The target is registered in `core/cpp/tests/CMakeLists.txt`.
6. The journal and metadata snapshot are separate persistence artifacts. Reconstructing events from the journal does not recreate learned tier/salience/confidence metadata. Any fallback to journal-derived defaults must therefore be explicit and observable as degraded metadata recovery.

**Required correction design:** Decode into a temporary validated snapshot; validate header, count, every record, sequence uniqueness/membership, enum range, finite/ranged values and exact file termination; only then atomically apply the complete snapshot and rebuild aggregate indexes from the validated records. On failure, leave journal-derived metadata unchanged and publish a structured recovery status plus diagnostics. Define first-run/absent separately from corrupt, truncated, unsupported-version and I/O-failed. Do not increment learned-tier aggregates from duplicate or partially applied records.

**Acceptance matrix still required:** valid snapshot; absent metadata; invalid magic; truncated header; excessive count; truncation at every record boundary; invalid tier; non-finite and out-of-range values; unknown sequence; duplicate sequence; trailing bytes; valid first record followed by invalid second record; interrupted snapshot replacement; restart after each recovery status; and assertions that no partial metadata or double-counted tier state leaks into retrieval.

**Status:** Source-level omission and failure path confirmed; no corruption experiment or production correction has been executed. R3-02 remains open.

### 50.3 R3-04 — Empty-premise reasoning: exact test gap

**Exact audited main baseline:** `1273ddbcd0087d189e01388ded2d362fb1e058d2`.  
**Source:** `core/cpp/src/reasoning.cpp`, blob `feec78b2e8a1f2b0b58733fd509e4e5a750258fc`; `core/cpp/include/jarvis/core/reasoning.hpp`, blob `5c6f82797d4f5052ad5d71a25624de192a2c87d9`.

The empty-premise branch returns `ReasoningKind::consistency`, `valid=true`, zero confidence and no conclusions. The current `jarvis_reasoning_architecture_suite` exercises consistent premises, contradiction, ordinary consistency, bounded inference and deduction. It does **not** include an empty-premise assertion. Its CMake target and CTest registration exist, but registration is not execution evidence.

The inspected `CognitiveCycle::run` retrieves ranked memories into `result.context.memories`, then constructs reasoning premises only from `result.context.beliefs`; retrieved memories are not supplied to the reasoning problem. The reasoning result is stored in cycle context, but the inspected function does not consume it to qualify downstream beliefs, predictions, goal selection, planning or decisions. These are separate integration gaps: changing the empty-input result alone will not connect memory-supported reasoning to downstream cognition.

**Required correction design:** Add an explicit unresolved/insufficient-evidence status or kind, with a stable machine-readable reason and no conclusions. Define the semantics of `valid` unambiguously (structural validity versus evidential support); do not allow callers to treat an empty-evidence result as a supported inference. Downstream consumers must gate on the explicit status. Preserve regression behavior for supported premises and contradictory premises.

**Acceptance matrix still required:** empty premises with empty and non-empty causal links; one supported premise; contradictory premises; malformed/unsupported premises; stable reason code; no success signal; downstream consumer rejection; exact-head build and registered CTest execution.

**Status:** Source/specification mismatch and test gap confirmed; no correction or test execution has been performed. R3-04 remains open.

### 50.4 CI evidence for the report update

The report update commit `f6267456560a08054d69f7960d2951452b14017c` has a completed successful GitHub Actions `Native Brain Build` run: run `42271797166`, job `128077942862`. Its steps are Configure and Build; it contains no CTest step. This is build evidence for the exact report commit's synthetic PR workflow context, not evidence that any test suite ran or that runtime defects were corrected.

The comparison artifact commit `609d38ede50bbdd98a93dfed112781eacabee9fd` completed separate `Native Brain Build` run `42272045285` successfully. This is configure/build evidence only; no CTest step is represented by this run.

### 50.5 Updated obligation status

| Obligation | Current disposition |
|---|---|
| BM-01–BM-12 source map | Substantially mapped; end-to-end acquisition/host and several recurrent edges remain incomplete |
| Human/MCU comparison | Drafted in PR #191; independent review and Project Director acceptance outstanding |
| R3-01 legacy scope | Working interpretation recorded in §49; durable explicit owner scope decision and repository-wide authority search still required |
| R3-02 metadata recovery | Source failure path refined; correction design and corruption/recovery tests open |
| R3-03 duplicate report authority | PR #179 selected as canonical working report; PR #180 closed as superseded, not merged |
| R3-04 empty-premise reasoning | Source/spec mismatch and missing test confirmed; result contract, implementation and tests open |
| R1/R2 mainline persistence | Source findings recorded in §47; complete mutator audit, failure injection and recovery proof open |
| P2-I-037/P2-I-038 and action/recovery findings | Open; require host boundary, typed provider failures, authorization lifecycle and failure-path tests |
| Independent review | Still requires a genuinely separate GitHub reviewer identity and formal review submission |
| Gate A | NOT CLEARED |
| Gate B | UNASSESSED |
| Phase 2 exit | NOT MET |

**Scope:** This update adds source-backed analysis and records a new draft architecture deliverable. It changes no runtime source, test, CMake configuration, workflow, donor code, implementation baseline or gate state. It does not claim Phase 2 completion.


---

## 51. Bounded legacy-authority scan and preservation update (2026-11-06)

### 51.1 Exact tracked-main documentation scan

The Phase 1 tracked-file inventory identifies the complete 200-file main tree at `1273ddbcd0087d189e01388ded2d362fb1e058d2`. Within that exact tree, the Markdown/documentation artifacts are:
- `README.md`;
- `docs/ARCHITECTURE.md`;
- `docs/JARVIS_BRAIN_MASTER_BLUEPRINT.md`;
- `docs/JARVIS_PHASE_2_COMPLETION.md`;
- `core/cpp/tests/phase4_notes.md`.

Each was fetched at the pinned main baseline and checked for Phase 2 / completion / Perception & Representation claims. The only whole-Brain Phase 2 completion statement found in that bounded tracked-main documentation set is in `docs/JARVIS_PHASE_2_COMPLETION.md`. Its own phase field is “Perception & Representation.” The master blueprint describes an earlier fixed Layer 0–19 construction plan, not a second whole-Brain Phase 2 completion claim. The README and short architecture summary contain no competing Phase 2 completion declaration; the test note is explicitly a Phase 4 test-history note.

**Search boundary:** This is a complete scan of the Markdown/documentation paths in the exact 200-file audited main tree, not a claim that every historical branch, open PR, external artifact or untracked file across the repository has been exhaustively searched. The all-branches authority scan remains a separate follow-up.

### 51.2 Preservation and supersession notices

On the PR #179 working branch:
- `README.md` links to the current whole-Brain Phase 2 map and labels it IN PROGRESS, not complete or implementation-authorizing. Current blob: `4952c7d2c407706fb69e3cdb3731f21c96b14611`.
- `docs/JARVIS_PHASE_2_COMPLETION.md` preserves its original content and adds a top-level scope clarification separating the narrower Perception & Representation work package from current BM-01–BM-12 whole-Brain Phase 2. Current blob: `faa5cace14d13179d717438be61f533ac5b8ef97`.
- `docs/JARVIS_BRAIN_MASTER_BLUEPRINT.md` now has a top-level historical/superseded notice linking to the accepted Brain Mechanism Specification and current Phase 2 map, while preserving the original blueprint content. Change commit: `cb7b082a153f10156345484525a5054bf44e6988`; new blob: `7ee8b5a399cda312d2c0be15d8244e9260d3b828`.

These are documentation preservation changes only. No historical document or branch was deleted or moved.

### 51.3 Updated R3-01 disposition

**Bounded main-tree conflict scan:** completed for the pinned tracked documentation set; only the legacy Phase 2 completion file contains the conflicting whole-Brain completion phrase.  
**Legacy scope:** the working interpretation is that this is a narrower Perception & Representation work package. The scope clarification is present on PR #179 and the original statements remain intact.  
**Still open:** the Project Director's conversational “Ok finish phase tow” is treated as authorization to proceed with this working interpretation, but it does not restate the exact historical scope in a durable decision record. If formal authority requires an explicit written scope decision, that remains outstanding. An all-branches/all-artifacts scan and independent verification also remain outstanding.

### 51.4 Exact-head build evidence

The latest report commit before this section, `e06a22faa535b38d4f98566968509688873e245f`, completed Native Brain Build run `42272147335`, job `128079137294`, with Configure and Build successful. No CTest step was present. This validates build compatibility of the documentation branch's synthetic PR workflow context only; it does not execute the registered test suites or resolve runtime findings.

### 51.5 Status

The main-tree documentation authority scan and three preservation/link updates are complete within the bounded scope above. R3-01 is **partially resolved**, not fully cleared. Phase 2 remains IN PROGRESS; Gate A remains NOT CLEARED; Gate B capability acceptance has NOT PASSED. This corrects the shorthand in this historical section in accordance with §53. Independent review, owner acceptance and the outstanding technical test/implementation obligations remain separate requirements.


---

## 52. Phase 2 exit-criteria ledger — explicit closure state (2026-11-06)

This section evaluates the twelve exit criteria in §9 against the current repository evidence. “Mapped” does not mean “implemented”; “registered” does not mean “executed”; and “blocked” does not mean “cleared.”

| # | Exit criterion | Current disposition | Evidence / remaining closure condition |
|---:|---|---|---|
| 1 | BM-01–BM-12 mapped to exact specification, main and relevant donor evidence | **SUBSTANTIALLY COMPLETE** | Mechanism sections and exact source identities exist. Final independent verification of every anchor remains required. |
| 2 | Material producer/consumer edges, including recurrent and delayed paths | **PARTIAL** | Main and donor call paths, memory/reasoning, action feedback and persistence paths are mapped. The complete recurrent dependency/invalidation graph and external host edges are not fully established. |
| 3 | Authoritative state owners identified; no competing Brain authority ambiguous | **PARTIAL** | C++ main is the inspected Brain authority; Rust is an isolated prototype and TypeScript is a contract layer. WorldModel/Brain projections and the external host's authority boundary still require final owner confirmation. |
| 4 | Memory-to-reasoning and reasoning-to-downstream integration traced and resolved or explicitly blocked; PR #173 F-03 kept separate | **MAPPED / BLOCKED** | IF-02/IF-03 are source-traced. Main cycle retrieves memories but does not pass them to reasoning; reasoning output is not consumed downstream. Closing requires separately authorized integration work or explicit owner-approved carry-forward. SYS-08 remains a separate substrate-boundary obligation. |
| 5 | PR #173 F-02/F-03 mapped to exact corrections; original review recovered or unavailability recorded; authority reconciled | **PARTIAL** | F-02 candidate-goal formation and F-03 SYS-08 are distinguished. The later PR #174 follow-on F-02/F-03 review artifact remains unavailable in checked repository records; bounded provenance limitation is recorded, but owner acceptance of that limitation and formal independent clearance remain open. |
| 6 | Persistence, replay, stale dependencies, concurrency, interruption, partial completion and recovery mapped with tests or explicit non-verification | **PARTIAL** | Multiple source-derived failure paths and test gaps are recorded, including R1/R2, R3-02, P2-I-023/029/030/035/036/037/038. Several required fault-injection and host-boundary tests have not been executed. |
| 7 | Donor paths compared against main and accepted requirements at exact commits | **SUBSTANTIALLY COMPLETE** | PR #97 and later donor lines are separately identified and compared; no donor is approved. Independent verification remains required. |
| 8 | Hardcoded assumptions classified | **SUBSTANTIALLY COMPLETE** | Infrastructure invariants, provisional policies, situation-specific mappings and test-environment ground truth are distinguished. Independent challenge remains required. |
| 9 | Learning evidence separated into storage, numeric adaptation, structural change, action-outcome learning, later behavioral effect and held-out transfer | **SUBSTANTIALLY COMPLETE** | DLT evidence and limitations are documented; matched-control and broader transfer claims remain explicitly limited. Further test-validity review is open. |
| 10 | Human-cognition and MCU J.A.R.V.I.S. comparison delivered or explicitly deferred | **DRAFT DELIVERED** | PR #191 contains BM-01–BM-12 comparisons, scientific references, functional overlap/differences, inference limits and test directions. Independent review and Project Director acceptance are outstanding. |
| 11 | Historical Phase 1 preservation tasks remain visible | **PARTIALLY ADDRESSED** | Main-tree README/legacy completion/blueprint notices are updated on PR #179. Historical branches and the full archive/cross-link maintenance remain preserved as open follow-up; no history was deleted. |
| 12 | Completed/partial/blocked/deferred/unverified status recorded; independent review and owner approval recorded | **PARTIAL / BLOCKED** | This ledger and prior status sections distinguish the states. A separate reviewer identity, formal review submission, Project Director acceptance of the exact report revision, and disposition of the proposed governance parent remain outstanding. |

### 52.1 Mandatory authority and evidence blockers

1. **Independent reviewer:** PR #179 and PR #191 currently have no submitted review records. A separate GitHub reviewer identity must review the exact final report/comparison revisions and submit the required formal review. The author cannot satisfy this requirement.
2. **Governance parent:** PR #179 is based on PR #178 at exact head `39fe09dcf13496f5f0005ccf3f00739303e29f88`. PR #178 remains open, draft and unmerged; its governance rules are proposed, not accepted. The Project Director must either accept that exact governance revision or authorize a different PR #179 base/authority path. Do not silently promote the governance proposal.
3. **Implementation authority:** Gate A is NOT CLEARED and Gate B capability acceptance has NOT PASSED. No implementation baseline or runtime scope is selected. R1/R2/R3-02/R3-04 and other source findings cannot be marked fixed without the required gate, baseline, scope and explicit implementation authorization.
4. **External host boundary:** the repository-only audit has not identified the deployed executable, grant issuer or actual external action host. The Project Director must identify the real host or approve a bounded deferral with owner and acceptance boundary.
5. **Missing review provenance:** the original PR #174 follow-on F-02/F-03 review artifact has not been recovered in the bounded checked repository evidence. The Project Director must supply it or explicitly accept the recorded provenance limitation.
6. **Legacy taxonomy:** the working interpretation and scope clarification are recorded in §§49 and 51. A durable explicit owner decision remains required if the project's approval process requires a separately worded historical-scope record.

### 52.2 Phase 2 exit decision

**Phase 2 exit criteria are NOT YET MET.** The report and comparison have materially advanced the documentation work, but criteria 2, 3, 5, 6, 11 and 12 remain partial, and several mapped defects require authorized implementation or owner-approved carry-forward.

This is not a declaration that all Brain capabilities must be implemented before the mapping phase can close. It is a declaration that each remaining obligation must have a verified result or an explicit, authorized blocked/deferred disposition, with owner and carry-forward recorded. Until then, claiming Phase 2 complete would contradict the repository's own acceptance criteria.

**Status at the time of this ledger:** Phase 2 IN PROGRESS. Gate A NOT CLEARED. Gate B capability acceptance NOT PASSED. No implementation baseline selected. No donor approved. No production implementation authorized.


---

## 53. Gate A / Gate B live-status reconciliation (2026-11-06)

A fresh read of PR #175's live body at head `874c732973b6ab303d65a503f5a215b0af8e1153` and its Gate A Report 16 at blob `6a8276deff9c4560daee7a665193f3e8ea16ce7c` refines the shorthand status in earlier sections.

### Gate A

**NOT CLEARED.** Report 16 identifies:
- the provenance, static in-repository API and workflow-specification workstreams as closed within their bounded scopes;
- D1/D2 fixes and principal journal failure/replay tests as present on PR #176, not merged into PR #156;
- deeper EvolutionController internal compensation failure injection as still open;
- independent re-check as open because no separate reviewer identity or submitted formal review exists.

PR #176 remains open/draft/unmerged at `4cf017e073da980c9f77d739fde6f92ef1a2fbc1`. Its passing 73/73 native, ASan/UBSan and ThreadSanitizer CTest results apply to that donor correction head only. They do not close the residual controller-compensation boundary or independent-review requirement.

### Gate B

**Capability acceptance has NOT PASSED.** PR #175's live body states that static BM-01–BM-12 traceability is documented, but capability acceptance has not passed. This is more precise than the earlier “unassessed” shorthand: traceability exists, but the required capability acceptance result is explicitly negative/not passed. No Gate B clearance is recorded.

### Corrected current status

- Gate A: **NOT CLEARED**.
- Gate B capability acceptance: **NOT PASSED**; no formal clearance.
- Phase 2: **IN PROGRESS; exit criteria not met**.
- Implementation baseline: **not selected**.
- Donor approval: **none**.
- Runtime implementation authorization: **not granted**.

This section supersedes any earlier shorthand in this report that described Gate B only as “unassessed.” It does not alter either gate or waive any requirement.


---

## 54. Live PR, review and CI reconciliation (2026-11-06)

This section records a fresh live check after §§50–53. It updates status only; it does not change approval, gate, implementation or baseline authority.

### 54.1 Documentation PR chain at the time of the live check

The #179 head shown below is the head observed immediately before the report-reconciliation commit that added §54; the report update itself advances that branch.

| PR | Live state | Exact head | Authority consequence |
|---|---|---|---|
| #178 governance rules | OPEN, DRAFT, unmerged | `39fe09dcf13496f5f0005ccf3f00739303e29f88` | Proposed governance baseline; not accepted authority |
| #179 whole-Brain integration map | OPEN, DRAFT, unmerged | `85f4cba12517eecbb82a4ff2f8dd4f7d5581e3f9` | Canonical working Phase 2 map; still based on proposed #178 |
| #191 human/MCU comparison | OPEN, DRAFT, unmerged | `609d38ede50bbdd98a93dfed112781eacabee9fd` | Required comparison draft; based on earlier #179 commit `f6267456560a08054d69f7960d2951452b14017c` |

PR #188 and PR #190 remain open review-report PRs, not submitted formal reviews of #179. Their authorship is the same repository identity as the reviewed work. Their reports remain useful advisory evidence but cannot satisfy the independent-review requirement.

### 54.2 Formal review record check

A fresh read of submitted review records returned **zero review submissions** for PRs #178, #179, #188, #190 and #191. In particular, PR #179 and #191 have no formal independent review recorded at their current heads. This is a hard external dependency: the Main Builder cannot create an independent review of its own work or represent an advisory report as one.

### 54.3 CI reconciliation

- PR #179 head `85f4cba12517eecbb82a4ff2f8dd4f7d5581e3f9`: Native Brain Build run `42273356466` completed successfully.
- PR #191 head `609d38ede50bbdd98a93dfed112781eacabee9fd`: Native Brain Build run `42272045285` completed successfully.

Both are **build-only** evidence. Neither result establishes that CTest ran, that the comparison was independently accepted, or that any runtime finding was corrected. The PR #191 artifact exists at the exact required path in §9; it remains a draft pending review and owner acceptance.

### 54.4 Authority and exit consequences

1. PR #178 remains a proposed governance parent. PR #179 depends on it. The Project Director must explicitly accept that exact governance revision or authorize a different authority/base path. The Main Builder must not merge, rebase or silently promote either branch.
2. The human/MCU comparison deliverable is drafted, so criterion 10's *preparation* portion is complete. Criterion 10 is not accepted until independent review and Project Director acceptance are recorded.
3. Criterion 12 remains blocked by the absent independent review and owner approval.
4. Criteria 2, 3, 5, 6 and 11 remain partial as described in §52. Their remaining evidence and owner decisions have not been manufactured by this update.
5. Gate A remains **NOT CLEARED**. Gate B capability acceptance remains **NOT PASSED**. Neither gate is a Phase 2 exit substitute.
6. Phase 2 remains **IN PROGRESS; exit criteria NOT MET**. No implementation baseline is selected, no donor is approved, and no runtime implementation is authorized.

**Builder disposition:** Documentation/build work has advanced, but the remaining closure items include decisions and formal review that only the Project Director or a genuinely separate reviewer can provide. They are not tasks the Main Builder may self-certify. Continue with bounded source/evidence work that does not require those approvals; stop at authority boundaries rather than inventing clearance.


---

## 55. Direct source re-check — perception-to-cognition integration boundary (2026-11-06)

### 55.1 Pinned source evidence

The following files were re-fetched from the exact Phase 1 main baseline `1273ddbcd0087d189e01388ded2d362fb1e058d2`:

| Source | Blob | Relevant contract |
|---|---|---|
| `core/cpp/include/jarvis/core/perception_pipeline.hpp` | `1e5fed009a2453211dac1a4187ff47c5cc65da39` | Declares `PerceptionInput`, `PerceptionContext`, `PerceptionProvider` and `PerceptionPipeline::process` |
| `core/cpp/src/perception_pipeline.cpp` | `ab9a745bb68e416d4e32c9d0c26a2d0b2016ab17` | Selects the strongest valid provider result; isolates provider exceptions; falls back to representation normalization |
| `core/cpp/include/jarvis/core/cognitive_cycle.hpp` | `28e7af98327956268a769adf7813125be842c1a2` | `CognitiveCycleInput` carries an `Event observation`; it has no `PerceptionPipeline` or `PerceptualRepresentation` input |
| `core/cpp/src/cognitive_cycle.cpp` | `3df14c552f2048b0394dc362f7ee7a654a93fb32` | `CognitiveCycle::run` calls `brain_.observe(input.observation)` directly |
| `core/cpp/include/jarvis/core/cognitive_runtime.hpp` | `d02b2607cebcb7c31963e2fe336970707a481e00` | Runtime owns `Brain`, `CognitiveCycle`, trigger and workspace; no perception pipeline member |
| `core/cpp/src/cognitive_runtime.cpp` | `1a1383cedc42e357dc9efce117328b8d55e30bca` | Worker dequeues `CognitiveCycleInput` and calls `cycle_.run(item.input)` directly |
| `core/cpp/tests/CMakeLists.txt` | `dab0c52ab4dfe15e1e2cbccfa9e6c904abdf54e3` | Registers perception-pipeline, cognitive-cycle and cognitive-runtime suites as separate test targets |

### 55.2 Dataflow conclusion

The implemented perception subsystem and the main cognitive coordinator are both present, but the inspected mainline contracts do not connect them:

`PerceptionInput → PerceptionPipeline::process → PerceptualRepresentation`

is a separate path from:

`CognitiveCycleInput::observation (Event) → Brain::observe → memory/beliefs/reasoning/planning/decision`.

The runtime's worker forwards the event-bearing cycle input directly; it does not invoke the perception pipeline or convert a perceptual representation into the cycle's observation. The test build file separately registers the perception and cycle/runtime suites. Separate unit-suite registration is not an end-to-end integration test.

This confirms a concrete missing producer/consumer edge, not merely an inference from class names. It strengthens the existing IR-01 / BM-01 integration finding and the partial status of exit criterion 2. It does **not** establish that no other executable or external host performs perception elsewhere; this conclusion is bounded to the pinned C++ mainline path inspected here.

### 55.3 Required closure evidence

Before criterion 2 can be marked complete, a later authorized integration/review task must:

1. Define the ownership and lifecycle of perception providers and the pipeline relative to the single Brain authority.
2. Define the representation-to-observation/event contract, including provenance, timestamp, source, uncertainty/confidence, validation and failure semantics.
3. Trace the representation through memory, belief formation, reasoning, prediction and downstream decisions; do not merely call the pipeline and discard its output.
4. Add an integration test that submits raw perception input through the real runtime boundary and asserts that the resulting representation influences the expected Brain-owned state and later behavior.
5. Test provider failure, unsupported input, invalid representation, fallback normalization and recovery without silently converting provider failure into apparently successful perception.
6. Run the exact-head relevant CTest targets and record results; registration/build success alone is insufficient.

This is an architecture/dataflow correction requirement, not authorization to implement it now. Gate A remains NOT CLEARED; no implementation baseline is selected and no runtime change is authorized.

### 55.4 Status

**Source re-check complete. Integration defect remains open.** Exit criterion 2 remains PARTIAL. The new evidence does not change the Phase 2 exit decision in §52 or the live authority boundary in §54.


---

## 56. State-authority audit — Brain, WorldModel, WorldState and Rust prototype (2026-11-06)

### 56.1 Pinned evidence

The audit used the same Phase 1 main baseline `1273ddbcd0087d189e01388ded2d362fb1e058d2`.

| Source | Blob | Finding |
|---|---|---|
| `core/cpp/include/jarvis/core/brain.hpp` | `8268ef84e0b361ead536724ba7761904b30ee58f` | `Brain` owns `WorldModel world_`, `Memory memory_`, beliefs, predictions, causal/association models, goals and other cognitive models. Public `world()` returns a const reference. |
| `core/cpp/src/brain.cpp` | `e9f3758fcc9c0e89b7280ce376db9033d547682d` | Constructor replays journal events into Brain-owned state; observation replay updates both beliefs and Brain-owned WorldModel. |
| `core/cpp/include/jarvis/core/world_model.hpp` | `1c14f692374b0ab272f05634b7bdd26e358b4f1f` | WorldModel is a separately constructible model with its own facts/relations and internal mutex. |
| `core/cpp/include/jarvis/core/world_state.hpp` | `5e91ec301d8254380731e0fdf14d16b6a3d5face` | WorldState separately owns another WorldModel, event history and snapshots. |
| `core/cpp/src/world_state.cpp` | `84658ee6e1a4485e1fe0f24ebb40eb3e281670f0` | WorldState::apply updates its private model and in-memory snapshots; this path is not journal-backed in the inspected implementation. |
| `core/cpp/tests/world_state_suite.cpp` | `bc6539059a8cc856572f3b01358085f27b1673a9` | Tests standalone WorldState behavior, including local history/checkpoints and clear; does not establish Brain/WorldState integration. |
| `core/cpp/tests/world_self_model_phase4_suite.cpp` | `f375f6e36c16fbb038d2ce3ba5c4cd18adf1860c` | Exercises a standalone WorldModel and separately checks Brain-owned `brain.world()` updates and Brain restart behavior. |
| `core/cpp/include/jarvis/core/cognitive_runtime.hpp` | `d02b2607cebcb7c31963e2fe336970707a481e00` | CognitiveRuntime receives a Brain reference and owns a CognitiveCycle; it does not own a WorldState. |
| `core/cpp/CMakeLists.txt` | `c51816888e1bddb7bc00c59e72529524e27a0717` | Compiles `world_model.cpp` and `world_state.cpp`; the separately present `brain_restored_api.cpp` is not in the listed `jarvis_core` source set. |
| `runtime/rust/src/lib.rs` | `ba949e43b7e06ce081b078035dfe7e48625d521c` | Rust exposes a separate `BrainRuntime` containing a `CognitiveState`, with a simple observe method. |
| `runtime/rust/src/cognition.rs` | `e46bb5b19528b58bf518f75f5edf704221cf5c9f` | Rust CognitiveState holds an in-memory belief map and bounded working-memory vector; no durable journal or C++ Brain synchronization is present in the inspected files. |

### 56.2 Authority conclusion

The evidence supports the following bounded classification:

1. **C++ Brain is the authoritative integrated state owner in the inspected mainline runtime.** It owns the journal-backed Memory and WorldModel and is passed by reference into CognitiveRuntime/CognitiveCycle.
2. **WorldState is a separate standalone state abstraction, not demonstrated as a second live Brain authority.** It owns its own WorldModel/history/snapshots and is compiled and unit-tested, but the inspected Brain and CognitiveRuntime do not own or invoke it. Its existence creates a potential competing projection if later integrated without an explicit ownership contract; it is not evidence that a second live Brain currently exists.
3. **Rust BrainRuntime is a prototype, not a synchronized authority.** Its in-memory CognitiveState is independently mutable and has no demonstrated journal, C++ bridge or shared-state protocol in the inspected files. Treat it as isolated prototype evidence, not a production runtime.
4. **BrainSnapshot is not a complete snapshot of all Brain-owned state.** Its declared projection includes BrainState, SelfState, beliefs, predictions, causal links and goals, but omits the Brain-owned WorldModel facts/relations, Memory journal state, associations and several other model states. The public `world()` accessor exposes a separate read path, but this is not equivalent to a coherent whole-Brain snapshot.
5. **Source/build boundary:** `brain_restored_api.cpp` exists in the tree but is absent from the inspected `jarvis_core` CMake source list. Its contents must not be treated as compiled mainline behavior without a separate build/target proof. The present audit does not infer runtime capability from that orphan file.

### 56.3 Remaining ownership and consistency questions

Criterion 3 cannot yet be marked complete. The source audit narrows the issue but does not settle:

- whether WorldState is intended to remain a standalone utility, become a Brain-owned projection, or be retired from the integrated architecture (Project Director/architecture owner decision);
- whether BrainSnapshot is intended as a partial diagnostic view or a whole-Brain consistency boundary;
- how WorldModel facts/relations, journal sequence and snapshot timestamps are expected to remain consistent under concurrent observation and snapshot reads;
- whether Rust is formally retained as a non-authoritative prototype and what prevents future deployment from creating a second writer;
- whether the external host owns only input/action orchestration or also maintains authoritative cognitive state.

Required closure evidence is an explicit state-authority diagram and owner decision, plus tests proving one write authority, projection consistency, restart/replay equivalence, and safe read/snapshot semantics. No production changes are authorized by this audit.

### 56.4 Status

**Source ownership classification advanced; criterion 3 remains PARTIAL.** The inspected evidence identifies C++ Brain as the current integrated authority, while WorldState and Rust remain separate, non-integrated state holders. Project Director/architecture-owner disposition and external-host confirmation remain open. Gate A remains NOT CLEARED; Phase 2 exit criteria remain NOT MET.


---

## 57. Mainline authorization and uncertain-effect source re-check (2026-11-06)

### 57.1 Scope and pinned evidence

This is a bounded re-check of the accepted Phase 1 main C++ baseline `1273ddbcd0087d189e01388ded2d362fb1e058d2`, not a claim about an unidentified deployed host.

| Source | Blob | Relevant contract |
|---|---|---|
| `core/cpp/include/jarvis/core/action_authorization.hpp` | `047f3f8d74c8558255750fbe14d29f7ae9153360` | Authorization context is a permission vector, maximum-risk scalar and reversible-action flag |
| `core/cpp/src/action_authorization.cpp` | `669bc86c8111ae9755bcd40715352b4fc71350d0` | Authorizer checks assessment, risk, reversibility and string membership; no issuer/version/expiry/revocation lookup |
| `core/cpp/include/jarvis/core/action_execution.hpp` | `38ff7033e7621db8f05cc1edc4bf59cb899ccdd3` | Executor callback returns bool; result has rejected/prepared/executed/verified/failed/cancelled/rolled_back, but no unknown/partial-effect state |
| `core/cpp/src/action_execution.cpp` | `c2f8653eb755fa2790a88e49bc8b0b9c3077e439` | False or throwing execution callback returns failed immediately, before verification or rollback; successful callback sets executed=true |
| `core/cpp/include/jarvis/core/brain.hpp` | `8268ef84e0b361ead536724ba7761904b30ee58f` | `Brain::execute_action` accepts authorization context as a caller-supplied value with a default empty context, then calls the executor |
| `core/cpp/include/jarvis/core/capability_execution.hpp` | `d2835c4e77b4b672422eaf4ef024d23a7d2eafc9` | Capability request independently carries raw granted-permission strings and a maximum-risk scalar |
| `core/cpp/src/capability_execution.cpp` | `5fef6077caf96c77eef6bda2eedd57540759d4e7` | Capability boundary checks string membership/risk and invokes a registered provider; no grant freshness or revocation lookup is present in this contract |
| `core/cpp/tests/action_authorization_suite.cpp` | `cf0cd95ec6fd83da756c305c54439a018cad796b` | Tests missing/matching permission, risk denial and denied callback prevention |
| `core/cpp/tests/action_execution_phase7_suite.cpp` | `b4a0060596c91c67080ac0a2db324f720d760fbe` | Tests clean false return, verification failure with successful rollback, and verified action feedback |

### 57.2 P2-I-038 — mainline confirmation and limits

The mainline implementation independently confirms the authorization lifecycle gap already identified in the donor audit:

1. The mainline `ActionAuthorizationContext` has no grant issuer, subject/resource scope, grant identity, policy version, issue/expiry time, revocation epoch or freshness token.
2. `ActionAuthorizer::authorize` makes its decision from the supplied in-memory values. The code does not consult an external authority or current policy version.
3. `Brain::execute_action` accepts that context directly from its caller. The inspected Brain API does not establish who issued it, how it is refreshed, or how queued work is invalidated after revocation.
4. The capability execution path has a parallel raw permission-vector contract. It is a distinct boundary and must not be assumed to inherit action authorization lifecycle guarantees.
5. The registered authorization tests prove local permission/risk checks, not grant issuance, identity binding, expiry, revocation, freshness, or queued-action invalidation.

**Finding refinement:** P2-I-038 is confirmed as a mainline API/lifecycle contract gap, not merely a donor-only concern. Deployment exploitability remains unestablished because the external application host may enforce an additional policy boundary or recreate/cancel runtimes when grants change. No unauthorized real-world action is asserted.

### 57.3 P2-I-030 — false/exception execution is not equivalent to no side effect

The mainline executor also confirms the existing uncertain-effect finding:

- The execution callback's `bool` contract does not encode whether an external side effect occurred before a false return or exception.
- When the callback returns false, `ActionExecutor::run` sets `failed` and returns without invoking verification or rollback.
- When it throws, the executor likewise returns `failed` immediately.
- `result.executed` is set only after a true callback return. Consequently, `executed == false` is not proof that the external system was untouched.
- The current false-return test exercises a clean failure callback; it does not simulate a side effect followed by false/throw.

This is a contract and evidence gap. It is not a reproduced external side effect. Required closure remains the P2-I-030 matrix already recorded in §21.2: false/throw before and after side effect, rollback false/throw, rollback verification failure, restart/reconciliation, and a structured unknown/partial outcome that cannot be mistaken for a clean rejection.

### 57.4 Closure requirements

1. Identify the actual host, grant issuer, policy owner and external action adapter; establish whether policy is immutable per session or revocable in place.
2. Define a versioned/identified grant contract, or prove a session-stop/cancellation protocol that invalidates queued work before side effects.
3. Revalidate authorization immediately before execution against the authoritative current policy; fail closed on stale or unavailable policy.
4. Distinguish cognitive assessment, authorization rejection, not-started execution, completed execution, failed-before-effect, effect-unknown/partial, verified consequence and verified compensation.
5. Replace or formally constrain boolean execution callbacks so false/exception has an enforceable no-side-effect meaning; otherwise return structured effect disposition.
6. Add fault-injection and host-boundary tests, including revocation after assessment and while queued, grant expiry, policy-version mismatch, false/throw after partial external effect, and failed compensation.
7. Preserve the original intent and evidence trail when execution is uncertain; do not convert an unknown external outcome into a successful or neutral learning label.

No runtime code or tests were changed by this audit. Gate A remains NOT CLEARED; no baseline/scope authorization was added.

### 57.5 Status

**Source re-check complete; P2-I-038 and P2-I-030 remain OPEN.** This strengthens criteria 2, 3 and 6 evidence but does not close them. The real host boundary remains an owner-supplied dependency. Phase 2 exit remains NOT MET.

---

## 58. Exact-head CI update after §§56–57

The report update containing §§56–57 must be evaluated at its exact commit. The preceding successful run `42297709974` applies only to commit `b36760801b798b958a6563126ea3bac6f8e78abe`; it must not be attributed to this later report revision. This section is a provenance guard and does not claim a new build or CTest result.


---

## 59. World-model provenance and snapshot consistency gap (2026-11-06)

### 59.1 Direct source trace

At the pinned main baseline `1273ddbcd0087d189e01388ded2d362fb1e058d2`:

- `Fact` declares `first_sequence` and `updated_sequence` in `core/cpp/include/jarvis/core/world_model.hpp` (blob `1c14f692374b0ab272f05634b7bdd26e358b4f1f`, line 12 onward).
- Brain observation replay updates the belief's `updated_sequence` to `event.sequence`, but constructs the corresponding WorldModel fact as `Fact{event.source, key, value, reliability, 1}` in `core/cpp/src/brain.cpp` (blob `e9f3758fcc9c0e89b7280ce376db9033d547682d`, line 82). The aggregate initialization leaves both Fact sequence fields at their zero defaults.
- The standalone WorldState event path similarly calls `model_.observe(Fact{event.source, key, value, 0.5, 1})` in `core/cpp/src/world_state.cpp` (blob `84658ee6e1a4485e1fe0f24ebb40eb3e281670f0`, line 21), while separately recording the event sequence in its history/checkpoint.
- `BrainSnapshot` does not include WorldModel facts or relations; `Brain::snapshot()` copies state, self-state, beliefs, predictions, causal links and goals only (`brain.hpp` blob `8268ef84e0b361ead536724ba7761904b30ee58f`, line 55 onward; `brain.cpp` blob above, line 215).
- The existing WorldModel/Brain test verifies a query result and restart of selected self-state fields, but does not assert that WorldModel Fact sequence metadata matches the journal event sequence (`world_self_model_phase4_suite.cpp`, blob `f375f6e36c16fbb038d2ce3ba5c4cd18adf1860c`).

### 59.2 Impact and limits

The Brain journal and belief records carry event sequence identity, but the WorldModel Fact projection currently drops that identity at construction. Consumers querying a Fact cannot rely on its declared first/updated sequence fields to establish freshness or trace the fact back to a journal event. This is a provenance defect in the projection, not proof that the underlying journal has lost the event.

The incomplete BrainSnapshot projection compounds the observability problem: a caller cannot obtain Brain-owned world facts/relations as part of the same declared snapshot object. The public `world()` reference provides a separate query surface, but the inspected API does not define an atomic cross-model snapshot contract. Do not claim a concurrency race or stale read has been reproduced; the finding is a source-level absence of an explicit consistency contract plus missing sequence propagation.

### 59.3 Required closure evidence

1. Define the intended semantics of Fact `first_sequence` and `updated_sequence` for new, repeated and conflicting observations.
2. Populate those fields from the authoritative journal event sequence on Brain replay and from the supplied event sequence in WorldState, without fabricating values for caller-created facts that lack provenance.
3. Add tests for first observation, repeated same-value observation, conflicting observation, restart/replay and sequence monotonicity.
4. Define whether BrainSnapshot is intentionally partial or must include a coherent WorldModel projection; if coherent, specify lock/order semantics and test it under concurrent observation/snapshot reads.
5. Ensure WorldState remains explicitly standalone unless an authorized architecture decision gives it a distinct projection role and ownership contract.

No production change is authorized by this audit.

### 59.4 Status

**New source-level finding recorded.** This adds a concrete provenance/observability gap to exit criteria 2, 3 and 6. Criterion 3 remains PARTIAL; criterion 6 remains PARTIAL. The issue is uncorrected and untested. Gate A remains NOT CLEARED; Phase 2 exit criteria remain NOT MET.


---

## 59. Bounded production-host call-site search (2026-11-06)

### 59.1 Search result

A bounded GitHub code-index search was run against the repository default branch, which resolves to the Phase 1 main baseline `1273ddbcd0087d189e01388ded2d362fb1e058d2`:

| Search term | Returned source call sites |
|---|---|
| `CognitiveRuntime(` | Runtime declaration and constructor implementation; runtime construction in cognitive runtime, trigger and workspace tests |
| `CognitiveRuntimeConfig` | Runtime declaration/implementation and test setup |
| `Brain brain(` | Brain declaration/implementation and multiple test constructions |
| `execute_action(` | Brain API declaration/definition and `action_execution_phase7_suite` test invocation |
| `CognitiveCycleInput` | Cycle/runtime declarations, implementations and test construction |

No production application executable or non-test host construction/call site was returned by these searches. The result is consistent with the earlier source trace: the inspected repository exposes a C++ cognitive library and test harnesses, but does not identify the deployed host that owns external input acquisition, grant issuance, action adapters and consequence observation.

### 59.2 Evidence limitation

GitHub code search is an index-based bounded search, not a complete filesystem or deployment inventory. The absence of a returned production call site is **not proof** that no host exists: the host may be in an unindexed path, another repository, a private deployment, generated code, or an external application. This section therefore records a precise repository-discovery limitation rather than an exhaustive absence claim.

### 59.3 Required owner input

To close the external-host portions of criteria 2, 3, 5 and 6, the Project Director or deployment owner must identify:

1. The deployed executable/repository and exact revision that constructs the Brain/runtime.
2. The owner of raw observation acquisition, normalization and provenance.
3. The authoritative permission/grant issuer and policy-change/revocation channel.
4. The action adapter/executor that performs external side effects.
5. The source of independent consequence evidence and the reconciliation/retry/idempotency contract.
6. Whether host state is authoritative, a projection of Brain state, or merely an adapter/workspace.

If the deployed host is intentionally outside this repository, its contract and exact version must be attached or linked as review evidence. A repository-only source map cannot certify uninspected deployment behavior.

### 59.4 Status

**Bounded call-site search complete; external host remains unidentified.** Criteria 2, 3, 5 and 6 retain their existing PARTIAL/BLOCKED dispositions. No implementation authority or phase-exit status changes.


---

## 60. PR #173 / #174 F-02 and F-03 review-provenance reconciliation (2026-11-06)

### 60.1 Evidence recovered

A bounded GitHub record check recovered the following:

- PR #173's 2026-11-03 Builder resubmission issue comment (comment `6598465160`, author `methaneex-oss`) identifies the Independent Review as having reviewed original commit `bd2f6f2d38e874aea015e2cc5de3c1a8d2b0f688` and records the correction map for F-01, F-02 and F-03 at architecture head `97191111bc2573c14d391c0af9628db7b11f194b`. It is a Builder-authored correction/handoff, not the review artifact itself.
- PR #174's 2026-11-03 resubmission comment records F-01 correction at exact head `0811a59e46bf934e32e794f90e4e7d18d4e2bd97`, including the BM-12 reasoning additions and the separate Builder correction record.
- PR #174's Project Director decision comment (2026-11-03 13:14 UTC) explicitly states that the Project Director accepted exact head `0811a59e46bf934e32e794f90e4e7d18d4e2bd97` following the Independent Reviewer's approval, and explicitly clears F-01. It does not separately state that F-02 and F-03 were re-reviewed/cleared.
- PR #174's 2026-11-04 revision comment records updated specification, source-audit and correction-record blobs, but is again Builder-authored.
- The live PR #173 and #174 formal review collections each return zero reviews; PR #174 review comments return an empty list. Its four issue comments are all authored by `methaneex-oss`. Thus those records do not contain the underlying reviewer artifact.

### 60.2 Reconciled interpretation

The original PR #173 F-02/F-03 correction mapping is recoverable and must not be described as wholly missing. The later PR #174 Project Director acceptance and F-01 clearance are also recoverable. However, the exact follow-on independent-review artifact specifically assessing F-02/F-03 at the revised PR #174 head was not recovered from the checked PR review/comment records or the checked repository artifacts.

Do not infer that the reviewer failed to assess F-02/F-03, and do not infer that the Project Director's acceptance explicitly cleared them. The defensible state is: original corrections mapped; PR #174 accepted as a planning baseline; F-01 explicitly cleared; later F-02/F-03 re-review evidence not independently recoverable in the bounded checked records; separate owner disposition still required for Phase 2's provenance criterion.

### 60.3 Required closure

1. Recover and attach the exact independent review artifact for PR #174's F-02/F-03 follow-on assessment, if it exists; otherwise the Project Director must explicitly accept the bounded provenance limitation.
2. Record whether the PR #173 F-02/F-03 corrections were accepted as sufficient by the reviewer/Project Director, with exact scope and commit.
3. Keep SYS-08 substrate responsibility separate from goal-formation F-02; do not merge similarly numbered findings across review packages.
4. Retain the existing accepted PR #174 baseline and its stated limits; this reconciliation does not revoke that acceptance.

### 60.4 Status

**Criterion 5 remains PARTIAL.** The original F-02/F-03 correction map and PR #174 acceptance are now better evidenced, but the specific follow-on review artifact / explicit owner disposition remains unresolved. No gate or implementation authority changes.


---

## 61. Exit-ledger delta after §§55–60 (2026-11-06)

This addendum supersedes only the affected evidence descriptions in §52; it does not silently change any criterion to complete.

| Criterion | Updated disposition | Latest evidence and remaining requirement |
|---:|---|---|
| 1 | SUBSTANTIALLY COMPLETE | BM-01–BM-12 mapping remains substantially complete; exact source anchors and comparison exist. Independent reviewer must still challenge the complete map and anchor accuracy. |
| 2 | PARTIAL | §55 confirms the missing PerceptionPipeline → CognitiveCycle runtime edge at the pinned C++ main baseline. §57 adds authorization/uncertain-effect path evidence; §59 adds WorldModel fact-provenance and snapshot-consistency gaps. Full recurrent, delayed, invalidation and external-host edges remain incomplete. |
| 3 | PARTIAL | §56 identifies C++ Brain as the integrated mainline state owner; WorldState is standalone and Rust BrainRuntime is an isolated in-memory prototype, not a demonstrated second live authority. §59 identifies missing Fact sequence propagation and an incomplete BrainSnapshot projection. External host authority and owner disposition remain open. |
| 4 | MAPPED / BLOCKED | Memory-to-reasoning and reasoning-to-downstream gaps remain source-traced and require authorized integration or explicit owner-approved carry-forward. |
| 5 | PARTIAL | §60 recovers the original PR #173 F-02/F-03 correction map and PR #174 acceptance/F-01 clearance. The specific follow-on F-02/F-03 review artifact at the revised PR #174 head remains unrecovered from checked review/comment/repository records; Project Director disposition is still required. |
| 6 | PARTIAL | Existing persistence, partial-commit, replay, authorization and uncertain-effect findings remain open. §59 adds missing WorldModel fact sequence provenance and the absence of a defined coherent BrainSnapshot contract. Required failure injection and exact-head CTest evidence are incomplete. |
| 7 | SUBSTANTIALLY COMPLETE | Donor comparisons remain documented and no donor is approved. Independent verification remains required. |
| 8 | SUBSTANTIALLY COMPLETE | Hardcoded assumption taxonomy remains documented; independent challenge remains required. |
| 9 | SUBSTANTIALLY COMPLETE | Learning evidence tiers and limits remain documented; independent test-validity review remains required. |
| 10 | DRAFT DELIVERED | PR #191 contains the human/MCU comparison; independent review and Project Director acceptance remain outstanding. |
| 11 | PARTIALLY ADDRESSED | Main-tree notices are present on the working branch. Full archive/cross-link and historical branch preservation verification remains open. |
| 12 | PARTIAL / BLOCKED | No formal review submissions exist for current PR #179 or #191. A separate reviewer must review exact final heads; Project Director must accept the report and resolve the PR #178 governance-parent decision and remaining owner dispositions. |

### 61.1 Current non-negotiable blockers

1. PR #178 remains open/draft/unmerged; PR #179 remains stacked on its proposed governance branch. Exact governance authority/base disposition is not recorded.
2. PR #179 and PR #191 have no formal independent review submissions. Builder-authored review reports and correction records do not satisfy that requirement.
3. The Project Director has not accepted the exact current PR #179 report head or PR #191 comparison head.
4. External host/action authority is not identified by the bounded repository audit; this requires owner-supplied evidence or explicit owner-approved deferral.
5. No production implementation baseline/scope has been selected. Gate A is NOT CLEARED and Gate B capability acceptance has NOT PASSED. Runtime corrections remain unauthorized.

### 61.2 Completion decision

The source and documentation audit is more complete than the §52 snapshot, but **Phase 2 exit criteria remain NOT MET**. This is not a request to implement all BM capabilities during Phase 2. It is a requirement to close each mapping/evidence criterion with verified evidence or an explicit authorized blocked/deferred disposition, and to obtain the required independent review and Project Director acceptance.

**Main Builder disposition:** continue bounded source tracing and report corrections; do not merge, rebase, promote proposed governance, self-certify independent review, select a baseline, or change runtime mechanisms. Phase 2 cannot be honestly declared complete until the external review and owner decisions are recorded.
