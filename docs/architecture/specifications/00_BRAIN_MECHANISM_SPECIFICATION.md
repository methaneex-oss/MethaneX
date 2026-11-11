# JARVIS Brain — Integrated Mechanism Specification

**Historical baseline status:** Accepted as the Brain Mechanism Specification planning baseline at PR #174 HEAD `0811a59e46bf934e32e794f90e4e7d18d4e2bd97` by Project Director decision comment [#6604790481](https://github.com/methaneex-oss/MethaneX/pull/174#issuecomment-6604790481). This acceptance is limited to that exact baseline and is not implementation authorization. The current correction revision contains Builder responses to the follow-on F-02/F-03 findings; independent re-review and Project Director disposition remain outstanding. The historical parent architecture baseline was superseded on 2026-11-11 as sufficient/final architecture; this specification must be reconciled against the current PR #173 architecture before implementation reliance.  
**Stage:** Detailed Brain Mechanism Specification  
**Authority:** Project Director authorization for this specification stage was recorded as received 2026-11-03. The Project Director's exact-revision acceptance of PR #173 as the Brain Foundation Architecture planning baseline was recovered from the 2026-11-03 decision and transcribed in PR #173 comment #6752144835.  
**Parent architecture reference:** PR #173, accepted planning-baseline HEAD `97191111bc2573c14d391c0af9628db7b11f194b` (Project Director decision 2026-11-03; provenance transcription in PR #173 comment #6752144835).
**Foundational capability baseline:** PR #172, commit \`d7d676b79dbf3269f7fd3ebdb4363a6df19f255d\`  
**Whole-system boundary baseline:** PR #171, reviewed package commit \`b05434758ad4fe72815503f89bd5d2990ccb658b\`  
**Engineering source baseline:** \`main\`, commit \`1273ddbcd0087d189e01388ded2d362fb1e058d2\`  
**Governing principle:** **ENGINEER THE MECHANISMS; LET BEHAVIOR BE ACQUIRED THROUGH EXPERIENCE.**

---

## 1. Purpose and specification authority

This document translates the historical PR #173 planning-baseline revision into mechanism-level responsibilities, conceptual contracts, state lifecycles, interaction rules, failure semantics and observable acceptance obligations. The prior Project Director decision for PR #173 HEAD `97191111bc2573c14d391c0af9628db7b11f194b` is transcribed in comment #6752144835, but the Project Director superseded that revision's sufficiency as the complete/final architecture on 2026-11-11. PR #174's separate acceptance at exact HEAD `0811a59e46bf934e32e794f90e4e7d18d4e2bd97` remains a planning-baseline decision only. This corrected specification revision requires independent re-review and explicit disposition; it is not implementation authorization.

It is a specification, not an implementation plan. It must guide later implementation without selecting the implementation prematurely.

The specification preserves the existing JARVIS project and treats existing code as evidence and potentially reusable material. Existing class boundaries, filenames and current call paths are not automatically the required final architecture.

### 1.1 What this stage may specify

This stage may define:

- what each foundational mechanism is responsible for;
- what information it receives, owns, derives and publishes;
- which other mechanisms it depends on and how they interact;
- conceptual state transitions and lifecycle rules;
- provenance, uncertainty, versioning and dependency requirements;
- how failures, interruptions, stale state and partial completion are represented;
- how learning candidates are formed, evaluated, activated, monitored and recovered;
- what observable evidence is required to claim a capability works.

### 1.2 What this stage does not authorize

This stage does not authorize:

- runtime implementation or refactoring;
- runtime test execution, build execution or benchmark execution;
- selection of algorithms, model providers, frameworks, databases, languages, APIs, concrete schemas, protocols or runtime topology;
- implementation task sequencing or migration planning;
- merging PR #173 or this specification PR;
- deployment.

A later specification may describe semantic information requirements and transition preconditions without defining wire formats, concrete types, storage layouts or algorithm choices.

### 1.3 Status vocabulary

- **Required:** a binding specification obligation derived from the accepted architecture.
- **Proposed:** a mechanism-level design direction awaiting independent review and Project Director acceptance.
- **Unresolved:** evidence is insufficient to settle the question.
- **Deferred:** deliberately outside the foundational specification.
- **Not demonstrated:** source inspection has not established the capability; this is not a claim that no related code exists.
- **Implemented:** reserved for behavior verified in the repository and appropriate tests; a class or API alone is insufficient.

No proposed mechanism becomes approved merely because it appears in this document or is committed.

---

## 2. Governing design invariants

Every mechanism specification and later implementation must preserve these invariants.

### 2.1 One coherent cognitive authority

The Brain is one coherent cognitive system. Mechanisms may have distinct responsibilities and authoritative state, but they must not become independent agents with competing beliefs, goals or identities.

Coordination is not a second intelligence. It manages interaction, state ownership, scheduling and conflict handling under explicit rules.

### 2.2 Experience is evidence, not an instruction to believe

An experience may support, weaken, contradict or fail to affect a hypothesis. It must not automatically become a belief, a causal rule, a goal, a preference or a behavioural command.

The system must preserve the difference between what was acquired, what was interpreted, what was inferred and what was later accepted.

### 2.3 Learning changes internal capability, not only a score

Learning must be capable of changing relevant representations, retrieval, beliefs, predictions, associations, strategies, skills or other cognitive state when evidence justifies it.

A numeric parameter update is one possible narrow form of adaptation. It is not a substitute for concept acquisition, causal-model revision, strategy learning or transfer.

### 2.4 Deterministic rules are allowed for integrity, not predetermined cognition

Deterministic rules may enforce:

- state validity and type/integrity invariants;
- authorization and permission boundaries;
- resource and execution constraints;
- provenance requirements;
- explicit safety and governance constraints;
- lifecycle consistency.

They must not encode the learned conclusion the Brain is expected to discover. Examples of prohibited cognitive shortcuts include fixed stimulus-to-emotion mappings, fixed emotion-to-action mappings, universal success/failure interpretations, and preloaded preferences presented as learned motivation.

### 2.5 Preserve plural representations and epistemic status

An observation, perceptual interpretation, memory, belief, prediction, simulation, candidate goal, intention, action request, execution record and verified outcome are different kinds of information.

No mechanism may silently promote one kind into another without a traceable transition and its required evidence.

### 2.6 Recurrent and selective processing

The system is not required to run every mechanism for every experience or in one fixed sequence. Retrieval may alter interpretation; a contradiction may reopen a belief; a prediction outcome may initiate learning; attention may interrupt work; a goal change may invalidate a plan.

Mechanisms must support selective, recurrent, delayed and concurrent processing.

### 2.7 Cognitive state and substrate state remain distinct

SYS-01 owns the semantic meaning and cognitive validity of Brain state. SYS-08 supplies compute, storage, network, devices and runtime substrate. Infrastructure acknowledgements do not prove a cognitive transition completed. Infrastructure failures are not automatically evidence about the external world or the Brain's beliefs.

### 2.8 Cognitive intent does not authorize execution

The Brain may form a goal, plan, decision or action request. Governance, security, operational validation, execution and outcome verification remain separate responsibilities. Only verified outcomes can be treated as evidence that the intended external consequence occurred.

---

## 3. Integrated mechanism map

The following mechanisms are logical responsibilities, not a required one-class-per-mechanism decomposition.

| ID | Mechanism | Primary responsibility | Authoritative state |
|---|---|---|---|
| BM-01 | Experience intake and provenance | Preserve incoming experience and its source/temporal context | Accepted experience record and acquisition lineage |
| BM-02 | Representation and interpretation | Form, compare and revise structured interpretations without erasing raw evidence | Derived representations and interpretation lineage |
| BM-03 | Continuity and memory | Retain, retrieve, associate, consolidate and selectively release experience | Memory records, retrieval history and consolidation lineage |
| BM-04 | Belief and world-state management | Maintain qualified working claims about entities, events and conditions | Belief/world-state claims and revision history |
| BM-05 | Association, causal modelling and prediction | Discover candidate relationships, generate predictions and compare outcomes | Association/causal hypotheses and prediction records |
| BM-06 | Attention and active context | Allocate limited processing capacity and maintain bounded task-relevant context | Attention state and active-context membership |
| BM-07 | Affective appraisal and valuation | Appraise contextual significance, uncertainty, risk and internal conditions; modulate cognition | Affective appraisal state and its evidence lineage |
| BM-08 | Goals, intent, planning and decision | Process supplied goals, form/evaluate candidate goals, develop plans and select cognitive decisions | Goal lifecycle, intent, plan and decision lineage |
| BM-09 | Learning and developmental adaptation | Form and evaluate evidence-supported changes to cognitive mechanisms and content | Learning candidates, evaluations, accepted changes and lineage |
| BM-10 | Metacognitive monitoring and control | Detect limits, inconsistency, uncertainty and performance failure; request proportionate correction | Monitoring records and corrective-work lineage |
| BM-11 | Integrated coordination and continuity control | Coordinate mechanism interactions, dependencies, concurrency, interruption and recovery | Coordination state, dependency status and coherent recovery checkpoints |
| BM-12 | General reasoning and inference | Derive, evaluate, compare and revise provisional conclusions from evidence-bearing premises and explicit assumptions | Reasoning episodes, argument/conclusion lineage, premise dependencies and unresolved inference records |

### 3.1 Foundational versus acquired capability

The initial Brain must possess enough enabling capacity to use these mechanisms, but it must not begin with the mature knowledge, priorities, associations, emotional reactions or strategies that experience is intended to develop.

Initial enabling capacity includes:

- the ability to preserve and distinguish evidence;
- basic representation and interpretation capacity;
- memory retention and retrieval capacity;
- belief formation and revision capacity;
- attention and working-context allocation;
- bounded prediction and outcome comparison;
- candidate learning and evaluation capacity;
- foundational general reasoning and inference, with explicit premise/assumption handling, conclusion evaluation and traceable inference lineage;
- supplied-goal processing and minimum candidate-goal evaluation capacity;
- minimum context-sensitive affective appraisal;
- cognitive self-monitoring and coordinated state continuity.

Expected experience-acquired development includes richer grounding, more useful retrieval, semantic and causal understanding, generalized concepts, learned attention priorities, calibrated appraisal, internally formed candidate goals, strategies, procedural competence, social understanding and more effective metacognition.

The mechanisms must be capable of development without requiring every advanced capability to be present at initialization.

---

## 4. Mechanism specifications

Each mechanism below is specified by responsibility, conceptual inputs and outputs, state ownership, required interactions, lifecycle obligations and failure semantics. Concrete data structures and algorithms remain unresolved unless explicitly accepted later.

### BM-01 — Experience intake and provenance

**Purpose:** Establish a trustworthy account of what the system received before interpretation or learning changes it.

**Inputs:** Sensory/system observations, user or operator information, tool/provider results, action/execution evidence, internal events, and restored historical records.

**Owns:** The accepted acquisition record and lineage connecting it to its source and acquisition conditions. It does not own the meaning of the interpreted content.

**Required behavior:**

1. Preserve the original acquired content or a verifiable reference to it.
2. Preserve source identity, acquisition time, event time when known, modality/channel, context and integrity status.
3. Distinguish missing metadata from a known negative value.
4. Record transformations and derived versions without overwriting the acquired original.
5. Represent duplicate, delayed, reordered, partial, malformed and conflicting inputs explicitly.
6. Distinguish external observations from internal model outputs, simulations, predictions and infrastructure events.
7. Allow a low-quality or incomplete experience to be retained as such without granting it unwarranted authority.

**Publishes:** An evidence-bearing experience available for representation, attention and memory processing.

**Interactions:**

- BM-02 interprets the acquired content while retaining a trace to it.
- BM-06 may prioritize it for processing.
- BM-03 may retain it.
- BM-04 may use derived evidence to form or revise claims.
- BM-05 may use it to resolve a prediction only when it actually bears on that prediction.
- BM-09 may use it as learning evidence after attribution and quality checks.

**Failure semantics:** Intake failure, source unavailability, malformed content and missing evidence must not be converted into a fabricated observation. A transport/storage acknowledgement is not proof of semantic acceptance.

### BM-02 — Representation and interpretation

**Purpose:** Convert acquired experience into one or more useful internal interpretations while preserving uncertainty and alternatives.

**Inputs:** BM-01 experience (including original utterance/content and acquisition context), relevant conversation history, speaker/source role, shared referents, retrieved memory, active beliefs, active context, task/goal context, and available perception capabilities.

**Owns:** Derived representations, candidate interpretations, entity/event hypotheses, relations and transformation lineage.

**Required behavior:**

1. Keep acquisition evidence separate from interpretation.
2. Support multiple plausible interpretations where evidence does not uniquely resolve meaning.
3. Preserve modality and source context; do not collapse materially different evidence into a single unsupported label.
4. Record which evidence and contextual assumptions support each interpretation.
5. Permit later evidence to revise, split, merge or withdraw an interpretation without rewriting the original acquisition record.
6. Distinguish representation confidence from source reliability and from belief confidence.
7. Avoid treating normalized attributes or matching words as proof of semantic identity.
8. Distinguish the original utterance/content from literal/semantic interpretation, reference/discourse interpretation and pragmatic/operator-intent hypotheses.
9. Ground interpretation in relevant conversation history, speaker/source role, shared referents, active task and context; preserve temporal and source provenance.
10. Treat inferred operator intent as a provisional interpretation supported by evidence, not as a fact derived from a fixed phrase-to-intent mapping.
11. Preserve materially different readings and their assumptions when context does not discriminate among them; request clarification when ambiguity changes the likely outcome or consequence.
12. Incorporate corrections as new evidence and revise the interpretation without rewriting the original utterance.
13. Treat quoted, reported, hypothetical or otherwise untrusted imperative text as content to interpret, not automatically as an instruction from the current operator.
14. Represent speech-act/communicative-function hypotheses separately from literal content and inferred desired outcome; attribute utterances and embedded claims to their actual source/speaker where evidence permits, preserving quoted/reported source boundaries.
15. Preserve discourse continuity across turns and interruptions: retain provenance and temporal scope of active referents, unresolved interpretations, corrections and relevant context, while allowing stale or contradicted context to be revised.
16. Keep inferred intent distinct from authority: interpretation does not authorize action.

**Publishes:** Candidate representations, including literal/semantic readings, reference/discourse hypotheses and pragmatic/operator-intent hypotheses where applicable, with evidence links, alternatives, uncertainty and explicit epistemic status.

**Interactions:** BM-03 supplies context; BM-04 compares interpretations with current claims; BM-05 may discover relations; BM-06 supplies active context and allocates further processing; BM-08 supplies goal/request context and evaluates qualified intent hypotheses; BM-09 may improve representational competence through evaluated experience; BM-12 reasons over interpretations and contextual evidence without committing beliefs or authorizing actions.

**Failure semantics:** Unsupported interpretation remains a hypothesis or unresolved input. Provider failure, absent modality support and low confidence must be visible, not silently replaced with a claim of successful perception.

### BM-03 — Continuity and memory

**Purpose:** Preserve useful experience over time and make relevant past experience available to current cognition.

**Owns:** Retained episodes, memory classifications, salience/relevance evidence, retrieval records, consolidation history and forgetting/supersession lineage.

**Conceptual memory functions:**

- **Working/active retention:** short-lived material needed for current processing.
- **Episodic retention:** particular experiences and their contexts.
- **Semantic retention:** generalized knowledge supported by multiple experiences or justified inference.
- **Procedural retention:** acquired skills, methods and action competencies.
- **Associative retention:** learned relationships among representations, experiences and outcomes.

These are functional distinctions, not a mandate for five isolated stores.

**Required behavior:**

1. Preserve the provenance and context of retained experience.
2. Distinguish storing an episode from accepting its interpretation as true.
3. Support retrieval by relevance to current context, not only literal attribute overlap.
4. Return evidence that can materially influence reasoning, prediction, appraisal and decisions.
5. Track retrieval use sufficiently to evaluate whether recalled information helped, misled or was irrelevant.
6. Consolidate only when evidence supports the transformation; preserve links to source episodes.
7. Support competing memories and contradictory episodes without forcing false consistency.
8. Permit correction, supersession, decay or forgetting while retaining required lineage and continuity guarantees.
9. Keep working-context eviction separate from deletion of durable history.
10. Avoid treating salience as truth or confidence as relevance.

**Publishes:** Retrieved evidence, memory-derived representations and consolidation candidates with traceable source episodes.

**Interactions:** BM-02 uses memory to interpret; BM-04 uses it when revising claims; BM-05 uses it for prediction and relation hypotheses; BM-06 controls retrieval/focus; BM-07 may influence encoding priority; BM-09 evaluates consolidation and retrieval changes.

**Failure semantics:** Missing or unavailable memory is not proof that an event never occurred. Retrieval failure, storage failure, corruption and an empty result are distinct conditions.

### BM-04 — Belief and world-state management

**Purpose:** Maintain a revisable, evidence-qualified working understanding of the world and relevant internal state.

**Owns:** Beliefs, their scope, supporting/contradicting evidence, status, revision lineage, and dependencies on other cognitive state.

**Required behavior:**

1. A belief must identify what it claims, where and when it applies, and what evidence supports it.
2. Preserve observation, interpretation, inference and accepted belief as distinct statuses.
3. Support uncertainty, disagreement, competing hypotheses, stale information and unknown state.
4. Revise confidence and content according to the evidence and its relevance; do not use a single generic update rule for all evidence types.
5. Permit a claim to be qualified, disputed, suspended, superseded or withdrawn.
6. Preserve prior versions and the evidence responsible for a revision.
7. Notify or expose affected predictions, plans, goals and derived representations when a belief changes.
8. Do not interpret missing evidence as evidence of absence unless the acquisition conditions justify that conclusion.

**Publishes:** Qualified working claims and explicit change events for dependent mechanisms.

**Interactions:** BM-01/02 supply evidence; BM-03 supplies prior episodes; BM-05 uses claims as assumptions and returns prediction evidence; BM-06 selects claims for active context; BM-08 uses claims in feasibility and planning; BM-09 evaluates belief revision; BM-10 monitors contradiction and uncertainty.

**Failure semantics:** A failed update must not leave a partially revised belief with stale dependents. Conflicting claims remain inspectable; the system may defer commitment rather than invent resolution.

### BM-05 — Association, causal modelling and prediction

**Purpose:** Discover candidate relationships, model possible consequences, make scoped predictions and learn from resolved outcomes.

**Owns:** Association hypotheses, causal hypotheses, prediction records, prediction assumptions and resolution lineage.

**Required behavior:**

1. Distinguish co-occurrence, correlation, association, temporal precedence, causal hypothesis and verified causal knowledge.
2. Never promote co-occurrence alone to a universal causal rule.
3. Preserve context, scope, assumptions, confidence meaning and counterevidence for relationship hypotheses.
4. Generate predictions only from explicit premises and applicable model state.
5. Each prediction must be identifiable and resolvable independently, including when multiple predictions concern similar content.
6. Preserve prediction horizon, scope, assumptions, expected observation and resolution conditions.
7. Support delayed, partial, ambiguous, contradictory and out-of-order outcomes.
8. Do not resolve an outcome from a mere action request, provider acknowledgement or infrastructure event.
9. Compare prediction with outcome using a measure appropriate to the predicted content; exact equality is not a universal error metric.
10. Feed resolved outcomes to BM-04 and BM-09 with traceable attribution.

**Publishes:** Scoped predictions, relation hypotheses, prediction errors and evidence-backed model-change candidates.

**Interactions:** BM-03 supplies prior episodes; BM-04 supplies premises; BM-06 prioritizes unresolved predictions; BM-07 may appraise prediction discrepancy; BM-08 uses predictions for planning; BM-09 evaluates model revision; BM-10 monitors calibration and repeated failure.

**Failure semantics:** An unresolved prediction is neither success nor failure. An unobserved outcome, a failed sensor, a cancelled action and a verified negative outcome must remain distinguishable.

### BM-06 — Attention and active context

**Purpose:** Allocate limited cognitive processing capacity among competing experiences, memories, predictions, goals and internal conditions.

**Owns:** Current focus, attention history, active-context membership, resource allocation decisions and interruption/resumption state.

**Required behavior:**

1. Prioritization may consider novelty, uncertainty, relevance, urgency, risk, active goals, affective appraisal, consequences and current cognitive load.
2. The relative influence of these factors must be capable of development and contextual adjustment.
3. Attention is selective processing, not truth assignment.
4. High salience does not automatically mean high reliability, high importance or a command to act.
5. Active context is bounded and task-sensitive; it is not a duplicate authoritative memory or belief database.
6. Support multiple concurrent contexts where appropriate, with explicit ownership and isolation.
7. Preserve enough state to suspend and resume work without losing evidence, goal constraints, permissions or freshness information.
8. Permit attention to be redirected by new evidence, changed goals, detected danger, uncertainty or metacognitive correction.

**Publishes:** Focus decisions, active-context snapshots and interruption/resumption events.

**Interactions:** BM-03 retrieves likely relevant memories; BM-04 supplies uncertainty and conflict; BM-05 supplies unresolved predictions; BM-07 supplies appraisal signals; BM-08 supplies goal context; BM-10 can request reconsideration.

**Failure semantics:** Starvation, overload, focus oscillation, stale context and dropped work must be observable. Context eviction must not silently delete authoritative state.

### BM-07 — Affective appraisal and valuation

**Purpose:** Provide foundational, context-sensitive appraisal of significance and internal conditions and allow this appraisal to modulate cognition.

**Owns:** Appraisal state, cognitive estimates of relevant internal conditions, appraisal evidence and developmental lineage. These estimates are not authoritative operational or homeostatic state. SYS-05 remains the owner of autonomic regulation state, while SYS-08 remains the owner of compute, storage, devices and runtime substrate state; BM-07 may consume authorized SYS-05 observations and maintain a qualified cognitive estimate with source, freshness and uncertainty. It must not write, redefine or claim authority over SYS-05 state.

**Required foundational capacity:**

- evaluate significance relative to current context and goals;
- represent uncertainty, novelty, risk, progress, loss, conflict or other relevant dimensions where evidence supports them;
- distinguish appraisal from external observation and from a fixed emotion label;
- allow appraisal to influence attention, memory encoding/retrieval, learning, goal evaluation and decision formation;
- revise appraisal when context or evidence changes.

**Developmental capacity:** Rich affective differentiation, nuanced contextual calibration, stable learned modulation and more sophisticated interactions are expected to develop through experience.

**Required behavior:**

1. The same external event may have different significance under different goals, expectations, histories or internal conditions.
2. An appraisal must not be hardwired as a fixed stimulus-to-emotion or emotion-to-action mapping.
3. Appraisal is not itself a command, permission, belief or external-world fact.
4. Preserve which internal/external evidence and context contributed to an appraisal.
5. Permit disagreement between appraisal signals and other evidence; do not force a single scalar to represent all affective dimensions.
6. Keep operational regulation and safety responsibilities in their approved system boundaries. SYS-06 remains proposed/unresolved, not a mandatory subsystem.

**Publishes:** Contextual appraisal signals and revised appraisal state for other mechanisms.

**Interactions:** BM-06 attention; BM-03 memory encoding and retrieval; BM-09 learning; BM-08 valuation, goal evaluation and decisions; BM-10 metacognitive assessment; BM-12 may consider appraisal as qualified contextual input, never as proof of an external fact or a mandatory conclusion.

**Failure semantics:** Missing or unreliable appraisal must not fabricate emotional certainty. The Brain must continue within its defined foundational capacity if the proposed SYS-06 responsibility is absent.

### BM-08 — Goals, intent, planning and decision

**Purpose:** Convert supplied goals and experience-informed candidate goals into evaluated priorities, plans and cognitive decisions while preserving governance boundaries.

**Owns:** Goal records and lifecycle, candidate-goal lineage, intent, plans, decision rationale and dependencies.

**Goal origin distinctions:**

- **Supplied goal:** entered through an authorized external interaction or system contract.
- **Experience-acquired candidate goal:** proposed by the Brain from interpreted experience, changed circumstances, unresolved discrepancies, internal conditions, consequences or other learned context.
- **Governance constraint:** an external authorization, prohibition or policy condition; it is not a Brain-created goal.
- **Subgoal:** a dependent objective serving another goal; it must retain its parent/dependency lineage.

These are distinct origins and must not be conflated.

**Required behavior:**

1. Process supplied goals without treating them as proof of internal motivation.
2. Permit candidate-goal formation from experience without encoding fixed triggers or a predefined desired objective set.
3. Preserve the evidence, context, assumptions and developmental lineage behind each candidate goal.
4. Evaluate candidates for relevance, feasibility, expected consequences, conflicts, resource constraints, uncertainty, risk and governance constraints.
5. Permit a candidate to be accepted, revised, deferred, suspended or abandoned.
6. Distinguish goal priority from urgency, affective appraisal, confidence and authorization.
7. Reconsider goals when their supporting evidence, feasibility, dependencies or constraints change.
8. Build plans from current evidence and predictions; invalidate or reconsider plans when dependencies become stale.
9. Preserve alternatives and reasons for deferral or rejection.
10. Decision formation may select, defer, observe, clarify, recommend, reject or escalate. It does not authorize execution.

**Publishes:** Evaluated goals, intent, plans, decisions and action requests.

**Interactions:** BM-03/04 provide experience and beliefs; BM-05 provides predictions; BM-06 allocates focus; BM-07 contributes appraisal; BM-09 can improve candidate formation and planning competence; BM-10 detects poor goal/decision calibration; external governance validates action requests.

**Failure semantics:** No eligible goal is a valid state, not a reason to invent one. An invalid or unauthorized action request cannot be reframed as permission. Goal abandonment must preserve its history and reason where known.

### BM-09 — Learning and developmental adaptation

**Purpose:** Turn attributed experience and outcome evidence into evaluated, persistent changes to cognitive content or mechanisms.

**Owns:** Learning hypotheses, candidate changes, evidence sets, evaluation records, accepted change versions, dependencies, monitoring results and rollback lineage.

**Required lifecycle:**

1. **Evidence acquisition:** receive experience/outcome with provenance and temporal context.
2. **Attribution:** determine which prediction, belief, representation, strategy, skill or capability the evidence may bear on.
3. **Discrepancy/limitation detection:** identify a meaningful error, repeated pattern, unmet need, capability gap or opportunity; do not assume every surprise warrants learning.
4. **Candidate formation:** state what may change and why, with assumptions and expected scope.
5. **Evaluation:** test candidate against supporting evidence, counterexamples, uncertainty, context, expected benefit, interference risk and relevant alternatives.
6. **Controlled activation:** activate only when the applicable evaluation and governance conditions are met.
7. **Persistence and lineage:** preserve the previous state, accepted state, evidence and evaluation.
8. **Post-activation monitoring:** measure effects in the acquisition context and varied relevant contexts.
9. **Recovery:** reject, revise, suspend or roll back a candidate when it is unsupported or causes material regression.

**Learning classes to support over development:**

- source/reliability calibration;
- memory relevance and consolidation;
- belief and world-model revision;
- association and causal-model revision;
- predictive calibration;
- representation and abstraction improvement;
- attention and appraisal calibration;
- candidate-goal and priority development;
- reasoning and planning strategy improvement;
- procedural and skill acquisition.

These are capability classes, not selected algorithms or an instruction to implement all classes at once.

**Required safeguards:**

- separate evidence that a prediction was wrong from evidence about why it was wrong;
- account for source reliability, context and possible confounders;
- avoid learning from infrastructure failure as if it were external-world feedback;
- avoid overfitting to one episode or one test fixture;
- evaluate transfer where transfer is expected and regression where unrelated behavior should remain stable;
- preserve a baseline and an interpretable change history;
- do not silently replace stable behavior with an unevaluated candidate.

**Publishes:** Accepted developmental changes, rejected/deferred candidates, evaluation evidence and updated capability estimates.

**Interactions:** All mechanisms may propose learning evidence or candidate changes; BM-09 coordinates the change while respecting the authoritative state owner of each affected representation.

**Failure semantics:** If attribution is weak, defer learning. If evaluation is incomplete, keep the candidate inactive. If activation partially fails, restore a coherent prior state or isolate the affected capability and record the incomplete transition.

### BM-10 — Metacognitive monitoring and control

**Purpose:** Assess the Brain's own cognitive process and initiate bounded correction when evidence indicates a limitation or error.

**Owns:** Monitoring observations, detected inconsistencies, confidence/calibration assessments, limitation hypotheses and corrective-work lineage.

**Required behavior:**

1. Distinguish a generated explanation from a record of the actual evidence and operations used.
2. Monitor uncertainty, contradiction, prediction calibration, stale dependencies, missing evidence, repeated failure, overload and capability degradation.
3. Detect when a conclusion exceeds its evidence or scope.
4. Request additional evidence, retrieval, re-reasoning, belief revision, plan reconsideration, reduced confidence, deferral or isolation as appropriate.
5. Evaluate whether a correction improved the outcome.
6. Preserve the original conclusion and correction history.
7. Remain bounded: monitoring cannot directly rewrite state owned by another mechanism without its contract, bypass governance or become a second cognitive authority.

**Publishes:** Qualified monitoring findings and corrective requests.

**Interactions:** All mechanisms provide state/evidence; BM-11 coordinates corrective work; BM-09 evaluates persistent improvement.

**Failure semantics:** Metacognitive uncertainty must not trigger endless reprocessing. Repeated unsuccessful correction should be surfaced as a limitation, not hidden behind repeated confidence recalculation.

### BM-11 — Integrated coordination and continuity control

**Purpose:** Keep the mechanisms operating as one coherent Brain across concurrent work, interruption, delayed evidence and partial failure.

**Owns:** Coordination state, dependency graph/status, work identity, active-context coordination, conflict records, checkpoints and recovery validation requests.

**Required behavior:**

1. Preserve authoritative state ownership; coordination may not silently overwrite another mechanism's state.
2. Track dependencies between beliefs, predictions, plans, goals, memories, reasoning conclusions and learning candidates.
3. When an upstream state changes, identify dependent state that may now be stale and request proportionate reconsideration.
4. Support independent work where safe and serialize or reconcile conflicting changes where required.
5. Detect duplicate, delayed and out-of-order updates.
6. Distinguish committed state changes from proposed, pending, failed or partially applied changes.
7. Support interruption, cancellation, resumption and recovery without fabricating completion.
8. Recover a coherent cognitive state after restart or partial failure and validate it before active use.
9. Preserve unaffected cognitive capabilities when one mechanism is degraded.
10. Prevent SYS-08 substrate acknowledgements from being treated as semantic state validation.

**Publishes:** Coherent active-context views, dependency invalidation/reconsideration requests, conflict outcomes and recovery status.

**Failure semantics:** If consistency cannot be established, affected state remains quarantined, provisional or unavailable. The Brain must not claim a successful recovery based only on storage or process availability.

### BM-12 — General reasoning and inference

**Purpose:** Provide the Brain's explicit general process for deriving, evaluating, comparing, qualifying and revising provisional conclusions from evidence-bearing premises, contextual information and explicit assumptions.

**Owns:** Reasoning episodes; premise/assumption sets; inference and argument lineage; provisional conclusions and alternatives; contradiction/counterexample records; unresolved questions; and dependencies identifying which inputs supported each conclusion. BM-12 does **not** own accepted beliefs or world-state claims. BM-04 remains the sole authority for accepting, revising, suspending or withdrawing beliefs. BM-12 also does not own representations, causal models, predictions, goals, plans or decisions.

**Conceptual inputs:**

- BM-01 evidence records and provenance;
- BM-02 interpretations and representation alternatives;
- BM-03 retrieved episodic, semantic and procedural memories, with retrieval context and provenance;
- BM-04 current beliefs, competing claims, scope and revision status;
- BM-05 association/causal hypotheses and predictions, clearly marked by epistemic status;
- BM-06 active task/context and processing constraints;
- BM-07 contextual appraisal signals, treated as qualified influences rather than factual premises;
- BM-08 goals, questions, plans or decision contexts that establish what is being reasoned about.

**Publishes:** Provisional conclusions, alternative explanations, derived implications, supporting and contradicting premise references, explicit assumptions, scope, uncertainty, counterexamples, unresolved gaps and a traceable inference record. Conclusions are returned to the relevant owner for possible acceptance; publication by BM-12 does not make them beliefs or authorize action.

**Responsibility boundaries:**

- BM-02 constructs interpretations and representation alternatives; it does not own the general derivation/evaluation of conclusions from multiple premises.
- BM-03 supplies retained experience and retrieval; it does not decide what a memory proves.
- BM-04 owns accepted beliefs and world-state revision; it evaluates candidate claims but does not own the general inference process.
- BM-05 owns association/causal hypotheses and predictions, including their generation and outcome resolution; it does not own general reasoning across all evidence types.
- BM-08 owns goal, intent, planning and decision state; it consumes qualified conclusions but does not subsume general reasoning.
- BM-10 monitors reasoning quality and requests correction; it does not replace BM-12's inference responsibility.

**Required behavior:**

1. Establish the question or inference objective and the context/scope in which a conclusion is intended to apply.
2. Distinguish supplied evidence, accepted beliefs, interpretations, retrieved memories, model hypotheses, assumptions and derived conclusions. No input category may be silently promoted to a stronger epistemic status.
3. Preserve premise identity, provenance, temporal context, retrieval context and relevant limitations. A retrieved memory may materially affect an inference only with its provenance and contextual applicability retained.
4. Make assumptions explicit, including assumptions introduced to bridge incomplete evidence. Mark conclusions that depend on assumptions and permit their withdrawal when an assumption fails.
5. Support appropriate forms of inference as developmental capability, including deductive consequence, explanatory/abductive hypothesis formation, inductive generalization and analogy where their evidence requirements are met. The specification does not prescribe a particular logic, algorithm or model, and does not imply equal maturity across inference forms at initialization.
6. Distinguish logical validity, evidential support, plausibility, confidence and truth. A valid derivation from false or contextually inapplicable premises is not a verified fact.
7. Preserve competing explanations where evidence underdetermines the answer. Do not force a single conclusion merely to complete a reasoning task.
8. Detect incompatible premises, contradictions among conclusions, counterexamples and conflicts with newly revised evidence. Record the conflict and affected dependencies rather than silently selecting the last or strongest-looking value.
9. When premises are missing, stale, contradictory, invalidated or outside their scope, qualify, suspend or withhold the affected conclusion; request retrieval, clarification, new evidence or re-reasoning where useful.
10. Revisit conclusions when a material premise, assumption, memory interpretation, belief, causal hypothesis or context changes. Preserve prior reasoning versions and identify which dependency caused reconsideration.
11. Explain conclusions through inspectable premise and inference lineage, not merely a free-form explanation string. The explanation must not claim evidence or operations that were not used.
12. Permit BM-10 to monitor reasoning quality, omissions, overreach and calibration; permit BM-09 to evaluate improvements to reasoning strategies using later outcomes and counterexamples.
13. Do not perform prediction resolution (BM-05), belief commitment (BM-04), goal/plan/decision ownership (BM-08), action authorization or execution.
14. Route each material conclusion or unresolved result to the relevant owner(s) with its uncertainty, alternatives, assumptions, scope, provenance and dependency lineage intact; record the consumer's explicit disposition (accepted for use, qualified, rejected, deferred or returned for evidence).
15. Treat delivery, logging, persistence or acknowledgement alone as insufficient evidence of downstream integration. The receiving owner must evaluate the result within its own responsibility and preserve its epistemic limits.
16. When a consumer accepts a reasoning result for use, the resulting authoritative computation or state transition must retain an explicit dependency on the reasoning artifact/version and record the resulting owner-state version or decision effect.
17. If a result is rejected, invalidated or superseded, its disposition and rationale plus affected dependencies must remain traceable; no silent discard or stale downstream use is permitted.

**Interactions:** BM-02 supplies interpretations; BM-03 supplies retrieved evidence; BM-04 supplies beliefs and receives candidate conclusions for epistemic evaluation; BM-05 supplies scoped causal/predictive hypotheses and receives relevant reasoning findings; BM-06 supplies task focus; BM-07 supplies contextual appraisal; BM-08 supplies reasoning objectives and may consume qualified conclusions; BM-09 evaluates developmental changes; BM-10 monitors quality; BM-11 tracks dependencies and invalidation.

**Failure semantics:** Empty premises produce an explicit insufficient-evidence/unresolved result, not a successful substantive inference. Contradictory premises remain visible and prevent unsupported conclusions from being treated as settled. Missing or failed retrieval is not evidence that no relevant memory exists. If premise provenance or scope cannot be established, the conclusion is withheld or explicitly qualified. If an upstream dependency changes, affected conclusions become stale pending review. Failure to reason is represented as a limitation, not replaced by a fabricated answer.

---

## 5. Cross-mechanism information contracts

The following contracts are mandatory at the conceptual level. They do not prescribe a concrete schema or transport.

### 5.1 Evidence contract

Any information used to materially revise cognition must preserve, where applicable:

- origin/source and source type;
- original acquisition reference;
- event time and acquisition/receipt time as distinct values;
- context and scope;
- transformation/derivation lineage;
- epistemic status;
- reliability and uncertainty dimensions, without conflating them;
- supporting and contradicting evidence;
- integrity and validation status.

Unknown fields remain unknown. They must not be silently defaulted into factual certainty.

### 5.2 Derived-state contract

Any derived claim, interpretation, prediction, appraisal, goal or plan must identify:

- what it represents;
- which evidence and prior state it depends on;
- assumptions and scope;
- confidence/uncertainty meaning;
- owner mechanism;
- version or revision lineage;
- status (candidate, active, disputed, stale, superseded, rejected or other justified state).

### 5.3 Change contract

A material state change must distinguish:

- proposed change;
- evaluation result;
- accepted/activated change;
- persistence result;
- downstream invalidation/reconsideration;
- post-change monitoring;
- rollback or recovery, if needed.

A method returning success, a record being written or a component acknowledging a request is not by itself proof that all dependent cognitive state is coherent.

### 5.4 Outcome contract

Outcome evidence must distinguish:

- action requested;
- authorization granted or denied;
- execution attempted;
- execution result;
- independently verified consequence;
- delayed or absent verification;
- operational/substrate failure.

Only evidence at the appropriate level may resolve a prediction or support a learning change about the external consequence.

---

### 5.5 Reasoning and inference contract

Every material reasoning result must preserve, at the conceptual level:

- the question/objective and intended scope;
- the identity and epistemic status of each premise;
- source/provenance and temporal/contextual limits for evidence-bearing premises;
- explicit assumptions and the conclusions that depend on them;
- the inference relation or reasoning step supporting each conclusion;
- alternatives, contradictions, counterexamples and unresolved gaps considered;
- uncertainty and support strength, without conflating them with truth or source reliability;
- dependency versions/status and conditions that make the conclusion stale;
- whether the conclusion is provisional, withdrawn, superseded or submitted to BM-04/another owner for evaluation.

A result that cannot provide this lineage may still be a tentative internal signal, but it cannot satisfy the specification's evidence standard for a material conclusion.

## 6. Core recurrent interaction patterns

These are allowed interaction patterns, not a mandatory global pipeline.

### 6.1 Experience interpretation and belief revision

1. BM-01 records acquired experience and provenance.
2. BM-06 may prioritize it; BM-03 may retrieve relevant episodes.
3. BM-02 forms one or more interpretations.
4. BM-04 compares interpretations with current claims and evidence.
5. BM-10 may identify unresolved ambiguity or contradiction.
6. BM-04 revises, qualifies or defers the claim.
7. BM-11 marks affected predictions, plans and active contexts for reconsideration.

At no point is raw experience automatically equivalent to a belief.

### 6.2 Prediction and delayed outcome

1. BM-04 and BM-03 provide premises and context.
2. BM-05 forms a scoped prediction with assumptions and resolution conditions.
3. BM-06 may prioritize the unresolved prediction.
4. A later BM-01 experience or verified outcome is matched to the prediction.
5. BM-05 resolves it only if the evidence satisfies the resolution conditions.
6. BM-04 receives relevant evidence; BM-09 evaluates whether a model or strategy change is justified.
7. BM-11 updates dependencies and preserves unresolved work where outcome evidence is incomplete.

A prediction may remain unresolved indefinitely or be explicitly invalidated if its conditions no longer apply. It must not be silently marked correct or incorrect.

### 6.3 Memory-supported reasoning and general inference

1. BM-06/08 establish the active context, question and reasoning objective.
2. BM-03 retrieves potentially relevant episodes and semantic/procedural material with provenance and retrieval context.
3. BM-02 interprets retrieved content in the current context without rewriting the source memory.
4. BM-04 and BM-05 make current beliefs, competing claims, relations and scoped hypotheses available with their epistemic status.
5. BM-12 assembles the premise set, identifies missing/contradictory/stale premises, states assumptions and performs the appropriate inference work.
6. BM-12 records premise-to-conclusion lineage, alternative explanations, uncertainty, counterexamples and which retrieved evidence materially influenced each conclusion.
7. BM-04 evaluates any candidate claim for belief acceptance or revision; BM-05 evaluates implications for causal/predictive models; BM-08 may consume qualified conclusions in goal/plan/decision formation. None is bypassed by BM-12.
8. BM-10 can challenge conclusions that omit relevant evidence, ignore contradictions or overstate their scope; BM-11 tracks premise changes and marks dependent conclusions stale.
9. Retrieval usefulness and reasoning outcomes can later become evidence for BM-03/BM-09.

Retrieving a memory without allowing it to affect inference is not evidence of integrated memory-supported cognition. A reasoning conclusion does not become an accepted belief merely because it was derived.

### 6.4 Candidate-goal formation and evaluation

1. BM-01/02/03/04/05/07 provide interpreted experience, context, discrepancies, internal conditions and consequences.
2. BM-08 may form a candidate goal; no fixed event-to-goal trigger is assumed.
3. The candidate retains its source evidence and developmental lineage.
4. BM-08 evaluates relevance, feasibility, conflict, resources, risk and constraints.
5. BM-10 may flag unsupported assumptions or conflict.
6. Candidate is accepted, revised, deferred, suspended or abandoned with reason and history.
7. If action is proposed, governance and execution remain external to Brain authority.
8. Later verified outcomes update progress and may change the goal's status.

A goal's origin must remain distinguishable from its later priority and authorization status.

### 6.5 Context-sensitive affective appraisal

1. BM-07 receives relevant experience, goals, predictions, memories and internal-condition evidence.
2. It forms an appraisal qualified by context and uncertainty.
3. BM-06, BM-03, BM-08 and BM-09 may use the appraisal as one influence among others.
4. Later evidence can revise the appraisal and its influence.
5. BM-10 monitors whether appraisal improves or degrades calibration and behavior.

No fixed emotional label or action follows automatically from a stimulus.

### 6.6 Learning and persistent behavioral change

1. An experience or outcome is retained with provenance.
2. A relevant mechanism identifies a possible discrepancy or limitation.
3. BM-09 forms a candidate update with a clear target, evidence and scope.
4. The candidate is evaluated against baseline behavior, supporting evidence, counterexamples and interference risk.
5. If accepted, the authoritative owner activates the change and BM-11 tracks dependent state.
6. The change persists across reconstruction when persistence is required.
7. Later behavior is evaluated in the original, varied and novel relevant contexts.
8. Regression triggers containment, revision or rollback.
9. The developmental history remains inspectable.

This is the minimum evidence chain for claiming genuine learning:

**experience → evidence-sensitive update → persistent change → later behavioral effect → evaluation in relevant and novel contexts.**

---

## 7. State lifecycle, freshness and dependency rules

### 7.1 Candidate versus active state

A hypothesis, belief revision, prediction, goal, plan or learning update may exist as a candidate before it becomes active. Candidate status must be explicit where activation has consequences.

### 7.2 Freshness

Derived state is fresh only relative to the versions and assumptions from which it was formed. A changed premise may make a prediction, plan, goal evaluation or appraisal stale even if its own record has not changed.

Staleness does not always require deletion. It requires an explicit decision to reuse with qualification, recompute, suspend or invalidate.

### 7.3 Dependencies

Material dependencies must be discoverable. A belief revision may affect predictions and plans; a memory consolidation may affect retrieval; a changed goal may alter attention and planning; a learned strategy may affect future decisions.

The system must not require every dependent mechanism to update synchronously, but it must prevent stale dependent state from being mistaken for current validated state.

### 7.4 Concurrency and conflicts

Where two processes propose changes to the same authoritative state, the owner must detect conflict and reconcile using evidence, version/freshness and explicit rules. Last-write-wins is not an acceptable universal cognitive conflict policy.

Independent changes may proceed concurrently when their state ownership and dependencies do not conflict.

### 7.5 Interruption and recovery

An interrupted operation must be distinguishable from a completed operation. Recovery must identify the last coherent state, pending candidates, partially applied changes and work requiring revalidation.

A restored event journal is not sufficient by itself to prove every derived in-memory model was correctly reconstructed.

---

## 8. Failure semantics and containment

| Failure condition | Required cognitive treatment |
|---|---|
| Missing or malformed input | Preserve failure/unknown status; do not fabricate evidence |
| Provider unavailable | Record capability unavailability; retain alternative interpretations if available |
| Contradictory observations | Preserve competing evidence; qualify or defer belief revision |
| Retrieval returns nothing | Treat as no retrieved evidence, not proof of historical absence |
| Prediction outcome delayed | Keep prediction unresolved and dependencies visible |
| Outcome cannot be attributed | Do not update the model as though attribution were known |
| Storage/runtime failure | Treat as SYS-08 operational failure; validate restored cognitive state under SYS-01 |
| Partial learning activation | Restore coherent prior state or isolate affected capability |
| Stale plan or goal assumptions | Reconsider before relying on them |
| Attention overload/starvation | Surface deferred work and prioritization limitations |
| Metacognitive loop fails to converge | Surface limitation and stop unproductive repeated correction |
| Governance denies action | Preserve denial as authorization evidence; do not claim execution |
| Execution lacks verification | Keep consequence unverified; do not infer intended success |

Fault containment must preserve unaffected cognition where possible. It must not hide uncertainty or turn degraded operation into false confidence.

---

## 9. Foundational acceptance scenarios

These scenarios are architecture-to-mechanism obligations. They are not claims that the current implementation passes them, and their concrete runtime tests require a later authorization.

### A. Evidence and interpretation

1. Two plausible interpretations are retained for one ambiguous experience; later evidence changes their relative support without rewriting the original acquisition.
2. An observation, a derived interpretation and an accepted belief remain distinguishable after persistence and reconstruction.
3. A provider failure is recorded as a capability failure, not as evidence that the external event did not occur.

### B. Memory and reasoning

4. A retrieved prior episode materially changes a later inference; the system can identify which evidence changed the conclusion.
5. A retrieved but irrelevant episode does not become authoritative merely because it was retrieved.
6. Working-context eviction does not erase durable episodic history.

### C. Belief, causality and prediction

7. Contradictory evidence revises or qualifies a belief while preserving prior lineage and invalidating affected dependent state.
8. Repeated co-occurrence does not automatically establish a universal causal rule.
9. Two similar predictions can be resolved independently.
10. A late outcome resolves the correct prediction using event time and explicit resolution conditions.
11. A cancelled action or failed sensor does not masquerade as a verified external outcome.

### D. Attention and affective appraisal

12. Competing contexts are prioritized and later resumed without losing their constraints or provenance.
13. The same event has different appraisal significance under different goals or internal conditions, without a fixed stimulus-to-emotion mapping.
14. Affective appraisal influences attention or evaluation as evidence-sensitive modulation, not as a direct command to act.

### E. Goals and decisions

15. The Brain can process an externally supplied goal without claiming it originated internally.
16. The Brain can form a candidate goal from a novel experience; the evidence and reasoning lineage are inspectable.
17. Later evidence defeats a candidate goal's premise; the candidate is revised, deferred or abandoned.
18. Governance denial prevents execution while preserving the Brain's intent and the denial as distinct records.

### F. Learning and development

19. A candidate change improves its acquisition context but regresses a relevant counterexample; the candidate is rejected or rolled back.
20. A candidate update persists after reconstruction and changes later behavior.
21. A learned change transfers to a novel related context where transfer is justified, without being applied indiscriminately to unrelated contexts.
22. A numeric parameter improvement is reported only as the narrow adaptation it demonstrates, not as proof of broad learning.

### G. Coordination and recovery

23. A belief change makes a dependent plan stale; the plan is reconsidered before use.
24. Concurrent updates to one authoritative state are reconciled without silently discarding evidence.
25. A partial persistence failure does not cause the Brain to claim a completed state transition.
26. After interruption and reconstruction, the Brain validates recovered identity, evidence lineage, state consistency and pending work before resuming.

### H. General reasoning and inference

27. Given sufficient premises, BM-12 derives a conclusion and identifies the exact premise and inference lineage; the conclusion remains provisional until the owning mechanism evaluates it.
28. An empty or materially incomplete premise set produces an explicit unresolved/insufficient-evidence result and cannot be reported as a successful substantive inference.
29. Contradictory premises are preserved as a conflict; BM-12 does not silently select one value or emit an unqualified conclusion.
30. A retrieved memory changes a conclusion only when its content is relevant to the current context; the reasoning record identifies the memory, its provenance and the way it affected the inference.
31. A conclusion depending on an assumption is withdrawn or qualified when later evidence defeats that assumption, while the prior reasoning lineage remains inspectable.
32. A counterexample or newly revised belief invalidates the affected generalization/conclusion and triggers targeted re-evaluation rather than a blanket rewrite of unrelated knowledge.
33. Two plausible explanations remain alternatives when evidence does not discriminate between them; the Brain does not manufacture certainty to satisfy a request.
34. A valid derivation from a stale, false or out-of-scope premise is not accepted as a verified fact; premise status and scope are checked before downstream use.

---

### I. Contextual language and operator-intent grounding

35. The same ambiguous utterance in two different conversation/task contexts yields context-supported interpretations rather than a fixed phrase-to-intent mapping.
36. An utterance with two materially different possible intended outcomes preserves both readings and requests clarification before consequential commitment.
37. An indirect or incomplete request uses relevant prior turns and shared referents while keeping literal content distinct from inferred intent.
38. An operator correction revises the interpretation, preserves the original utterance and re-evaluates dependent state.
39. Quoted or reported imperative text is not silently treated as an instruction from the current operator.
40. Correctly inferred operator intent does not bypass authorization or execution governance.

### J. Downstream reasoning integration

41. A provisional conclusion with explicit uncertainty is evaluated by BM-04 as a candidate claim; it is not silently committed as certain.
42. Two plausible explanations materially affect BM-08 planning; both remain represented or discriminating evidence is requested rather than consuming only the first result.
43. An explanatory conclusion routed to BM-05 remains a causal hypothesis until appropriate evidence and prediction/outcome evaluation support stronger status.
44. A changed premise or assumption causes BM-11 to mark dependent conclusions and downstream derived state stale and trigger targeted reconsideration.
45. A downstream owner may qualify or reject a reasoning result; its disposition and rationale remain inspectable and the reasoning episode is preserved.
46. A result that is only logged or delivered without relevant downstream evaluation/disposition fails the integration acceptance test.
47. An accepted reasoning result is used by a relevant owner to produce a materially different qualified belief, prediction/model state or goal/plan evaluation; the downstream record identifies the exact reasoning artifact/version and the resulting owner-state/decision version. If no material downstream computation can be demonstrated, the integration claim fails.
48. A previously accepted reasoning result is invalidated by a changed premise or contradicted evidence; BM-11 identifies affected downstream versions, and each owner records whether it recomputes, qualifies, withdraws or retains its state with rationale. Silent persistence of invalid dependent conclusions fails.

---

## 10. Developmental evidence standard

A capability is not demonstrated by the existence of a class, method, data structure, test name or successful single fixture.

Evidence must be proportional to the claim.

| Claim | Minimum evidence required |
|---|---|
| Retention | Experience survives the specified lifecycle and is recoverable with provenance |
| Retrieval | Relevant prior experience can be found under varied query/context conditions |
| Integration | Retrieved evidence materially affects a downstream inference or decision |
| Belief revision | Conflicting/new evidence changes or qualifies a claim with preserved lineage |
| Prediction | Scoped prediction is resolved against a valid, attributed outcome |
| Learning | Candidate update changes the relevant state and persists |
| Behavioral adaptation | Later behavior changes in the predicted direction because of the update |
| Transfer | The change helps in a novel but relevant context |
| Robustness | Counterexamples, unrelated capabilities and regressions are evaluated |
| Recovery | Interrupted/failed changes do not leave incoherent or falsely validated state |

The accepted architecture's minimum learning criterion remains binding:

**experience → evidence-sensitive update → persistent change → later behavioral effect → evaluation in relevant and novel contexts.**

---

## 11. Current implementation evidence boundary

The source audit is recorded separately in:

\`docs/architecture/specifications/research/00_BRAIN_EXISTING_MECHANISM_SOURCE_AUDIT_2026-11-03.md\`

That audit is based on \`main\` at \`1273ddbcd0087d189e01388ded2d362fb1e058d2\`, the engineering baseline used by PR #172. It is static source inspection only. No build, runtime test or benchmark was executed for this specification.

The audit identifies existing mechanisms that may be reusable and integration gaps that must be resolved by specification. It does not claim that the architecture is already implemented.

---

## 12. Unresolved mechanism questions

These questions are deliberately not answered by inventing algorithms or concrete structures.

1. What minimum provenance and temporal semantics are necessary for all evidence-bearing state?
2. Which belief classes require different revision semantics, and what evidence distinguishes them?
3. What is the minimum useful memory consolidation behavior before advanced semantic generalization exists?
4. How should retrieval relevance be learned and evaluated across different wording, modality and abstraction?
5. What is the evidence threshold for distinguishing association from a causal hypothesis, and how should confounders be represented?
6. How should prediction scope, horizon, resolution and partial outcome be represented consistently?
7. Which attention influences are foundational, and how should the system detect starvation and focus oscillation?
8. What minimum affective appraisal dimensions are needed to support foundational cognition without imposing a fixed emotion taxonomy?
9. How can candidate goals be formed from experience while avoiding a hardcoded objective generator?
10. Which learning classes may be evaluated online, and which require isolated or externally approved evaluation?
11. How should one learning candidate coordinate changes across multiple authoritative state owners?
12. Which state transitions require atomic commitment, and which can converge asynchronously?
13. How are concurrent evidence updates reconciled when they have different event times, reliability and context?
14. What recovery evidence is sufficient to revalidate derived state after interruption?
15. Which existing source mechanisms are compatible, incomplete, contradictory or candidates for replacement after a full dependency-level audit?
16. What reasoning forms and evidence conditions are foundational, and how should premise/assumption lineage, competing explanations, counterexamples and uncertainty be represented without prematurely selecting an inference algorithm?

---

## 13. Explicit non-decisions and next gate

This document does not select:

- algorithms for perception, memory retrieval, belief revision, causal discovery, attention, affective appraisal, goal formation, reasoning or learning;
- a model provider or any dependency on one model;
- concrete schemas, API signatures, serialization, transport or database;
- thread/process topology, service boundaries or deployment architecture;
- implementation sequence, tickets, code changes or test execution.

### Next gate

1. Builder submits this specification and its separate source audit for independent review.
2. Independent Reviewer challenges the mechanism responsibilities, interactions, evidence standards, source audit and unresolved boundaries.
3. Builder addresses findings in the existing specification package and records corrections separately.
4. Project Director accepts, rejects or returns the specification baseline.
5. Implementation and runtime verification remain separate authorization gates.

**End of specification.**


## 14. Follow-on review correction status — F-02 and F-03

The Builder's 2026-11-11 response to the recorded follow-on findings is in [PR #174 Follow-on Review Corrections — F-02 and F-03](reviews/01_BRAIN_MECHANISM_SPECIFICATION_F02_F03_CORRECTIONS_2026-11-11.md).

- **F-02 — contextual language/operator-intent grounding:** BM-02 now explicitly distinguishes acquired utterance, literal/semantic interpretation, reference/discourse interpretation and pragmatic/operator-intent hypotheses. It requires context, source role, history, alternatives, uncertainty, correction handling and authority separation. Scenarios 35–40 define minimum verification.
- **F-03 — downstream reasoning integration:** BM-12 now requires owner-routed conclusions with preserved uncertainty, alternatives, assumptions, provenance, scope and dependencies, plus explicit consumer disposition. Delivery/logging alone is not integration. Scenarios 41–46 test actual downstream evaluation and invalidation.

**Provenance qualification:** the original follow-on review report was supplied as a shared-conversation URL but could not be retrieved during this correction pass. The exact reviewed SHA, verbatim finding text and complete original acceptance criteria remain unavailable. The correction report therefore distinguishes recorded finding summaries from verbatim source material and does not claim full original-criteria closure.

**Builder status:** specification-level corrections submitted. **Independent re-review and Project Director disposition remain outstanding.** PR #174's previously accepted planning baseline at exact HEAD `0811a59e46bf934e32e794f90e4e7d18d4e2bd97` is not silently replaced by this corrected revision. No implementation is authorized.

