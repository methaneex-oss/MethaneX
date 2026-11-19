# Implementation Planning Kickoff and Starter Learning Work Packages — 2026-11-18

**Document status:** Active planning work; non-operative; submitted for independent review and Project Director disposition  
**Planning branch:** `plan/brain-implementation-roadmap-20261103` (PR #175)  
**Planning source HEAD at kickoff:** `4d0cfe729e64c718dd4f21ba95a0167166252e6e`  
**Historical accepted mechanism-specification planning baseline:** PR #174 `0811a59e46bf934e32e794f90e4e7d18d4e2bd97`  
**Current corrected PR #174 proposal:** `c34472354e4122fc1d78dc25bf45d81f1eb4dc69` — proposed, not accepted  
**Current corrected PR #173 architecture proposal:** `a96af5b18d3a1d580ff56cff6191240893bceeb5` — review remains PARTIALLY CLEAR; not accepted as the complete/final architecture  
**Scope:** Planning and readiness decomposition only  
**Governing principle:** **ENGINEER THE MECHANISMS; LET BEHAVIOR BE ACQUIRED THROUGH EXPERIENCE.**

---

## 1. Why this kickoff exists

The existing roadmap, parallel-planning supplement and capability-to-scenario matrix establish the conceptual programme. This document turns that programme into a bounded, dependency-aware planning backlog that can be reviewed and refined while the Documentation Foundation closeout proceeds.

This is continuation of the existing JARVIS project. It does not restart the architecture, replace the existing 12-mechanism model, or assume that every current source component is reusable or defective.

The planning objective is to prepare the first implementation programme around a real, integrated, experience-dependent learning capability. It is not to implement isolated mechanism labels or a fixed stimulus-to-response behaviour engine.

## 2. Authority and status

This kickoff is **non-operative planning**. It does not authorize runtime source changes, runtime tests/builds, baseline selection, donor adoption, API/schema/technology choices, integration, merge, deployment or Stage A activation.

The following authority distinctions are mandatory:

1. PR #173's historical accepted planning-baseline decision at `97191111bc2573c14d391c0af9628db7b11f194b` is not acceptance of the current corrected architecture proposal or proof of whole-architecture completeness.
2. PR #174's historical accepted mechanism-specification planning baseline at `0811a59e46bf934e32e794f90e4e7d18d4e2bd97` remains distinct from the current 54-scenario proposal at `c34472354e4122fc1d78dc25bf45d81f1eb4dc69`. The 54-scenario proposal is not treated as accepted authority.
3. PR #175's Gate A remains NOT CLEARED and Gate B capability acceptance remains NOT PASSED. No implementation source baseline has been selected.
4. PR #192 Documentation Foundation remains not accepted. Its open DF-02, DF-06 and DF-09 work and pending DF-12 Director decision are not bypassed by this parallel planning work.
5. PR #156 and PR #176 remain donor/correction evidence, not adopted implementation sources.

This kickoff is not a request to silently waive those gates. It prepares work so that, once the required decisions are made, implementation does not begin with unresolved ownership, vague acceptance criteria or speculative source edits.

## 3. Programme shape

The programme is organized around integrated capability increments, not twelve independent mechanism projects and not a rigid single-file cognitive pipeline.

| Increment | Planning focus | Principal mechanism responsibilities | Required integration result |
|---|---|---|---|
| I0 | Contract, authority and target readiness | All BM owners; SYS boundaries | Exact governing specification, ownership, source target and evidence obligations are reconciled before implementation activation |
| I1 | Experience and continuity spine | BM-01, BM-03, BM-11 | Attributable experience can be retained, retrieved and reconstructed with provenance and valid owner state |
| I2 | Representation and epistemic state | BM-02, BM-04, BM-03 | Observation, interpretation, hypothesis and belief remain distinguishable; competing claims and revision history survive |
| I3 | Memory-supported reasoning | BM-12 with BM-02/03/04/11 | Relevant memory materially changes an inference, with premises, assumptions, lineage and limits visible |
| I4 | Prediction and outcome feedback | BM-05 with BM-01/03/04/09/12 | Predictions have scope and resolution criteria; outcomes are attributed correctly; prediction error becomes evidence, not an automatic state write |
| I5 | Context-sensitive regulation | BM-06, BM-07, BM-10 | Attention, appraisal and monitoring coordinate processing without owning other mechanisms' authoritative state |
| I6 | Goals, planning and decisions | BM-08 with all relevant owners and SYS boundaries | Candidate goals and supplied goals are distinguished; decisions use qualified premises; cognitive intent does not grant execution authority |
| I7 | Cross-mechanism learning and starter-training evaluation | BM-09 coordinated with all affected owners and BM-11 | Justified experience produces owner-approved persistent change that measurably affects later behaviour and is evaluated for transfer and regression |

The increment order is a dependency model. Parallel planning is allowed where state ownership and interfaces are stable; parallel implementation is not authorized by this document.

## 4. First integrated capability target: an experience-dependent learning loop

The first capability target is a narrow but genuine closed learning loop:

**experience → representation and context → memory and belief updates → prediction → observed outcome → prediction error / feedback → candidate learning → affected-owner evaluation and approval → persistent state change → later behaviour change → subsequent evaluation.**

This is a planning target, not a prescribed implementation algorithm. Each arrow is a required interaction to evidence; it is not permission to hardcode a fixed mapping.

### 4.3 Capability is the result; engineering artifacts are instruments

Progress is judged by what the Brain can demonstrably do in a task, not by the number of mechanisms, work packages, documents, test cases, passing test suites or green workflows. Those artifacts help engineers build, inspect and diagnose the system; none is itself a capability.

A capability claim must name a bounded task family and show the Brain performing it under stated conditions. The primary evidence is the task outcome and the Brain's observable choices: what it understood, what relevant experience it used, what it decided, what it changed when circumstances changed, where it sought clarification or deferred, and whether the resulting task state or external consequence was independently verified. Internal traces explain and attribute that behavior; they do not substitute for it.

Tests, fixtures, benchmarks and metrics remain necessary supporting instruments for repeatability, diagnosis, comparison and failure discovery. Their count or pass rate is not the acceptance objective. A narrow successful test supports only the specific behavior it demonstrates; it does not establish broad competence, general intelligence or a complete learning capability.

The first WP-02–WP-04 slice is an internal cognitive foundation, not by itself a complete useful JARVIS capability or proof of developmental learning. It must be connected to a bounded task and a receiving behavior before any capability claim. Subsequent WP-05–WP-08 work must demonstrate the full experience-to-later-behavior change in task performance, including persistence and justified transfer.

### 4.1 Required properties

- Experience intake preserves source, time, context, scope and uncertainty; intake is not automatically accepted as truth.
- Representation preserves the distinction between observation and interpretation.
- Memory retains attributable history and retrieves it with relevance and applicability context.
- Belief updates preserve competing claims, evidence, confidence/qualification, revision and invalidation lineage.
- Predictions identify what is expected, under which assumptions and scope, over what horizon, and what evidence would resolve them.
- Outcomes distinguish observed facts from missing evidence, provider failure, execution failure and unverified consequences.
- Prediction error or feedback forms a candidate update; it does not directly write authoritative memory, belief, causal-model or goal state.
- The mechanism that owns affected state evaluates and approves its own update under shared change/recovery coordination.
- Persistent change is verified after reconstruction/restart and is shown to influence a later, meaningfully related experience.
- Held-out transfer and negative-transfer/regression checks are planned; a single successful example is not sufficient evidence of learning competence.

### 4.2 Explicit non-goals

- No stimulus→emotion, failure→trauma, success→reward, negative-affect→rejection or other fixed behavioural mapping.
- No hardcoded target knowledge or desired answer embedded in training fixtures.
- No universal scalar reward or single numeric parameter treated as the whole learning system.
- No assumption that memory storage alone demonstrates useful memory.
- No assumption that a prediction error automatically proves causality or authorizes adaptation.
- No claim of general intelligence, complete autonomy or complete learning from a narrow vertical slice.

## 5. Initial planning work packages

These are planning packages, not executable implementation tickets. Every package must be revalidated against the exact source baseline and accepted governing specification before activation.

### WP-00 — Authority and contract freeze

**Purpose:** Prevent implementation from depending on ambiguous or superseded authority.

**Planning outputs:**
- exact accepted architecture/specification references and explicit disposition of current proposals;
- BM-01–BM-12 and relevant SYS ownership map;
- scenario-to-owner and scenario-to-increment mapping;
- unresolved decision register, with decision owner and evidence required;
- change-control and traceability rules.

**Activation prerequisite:** Project Director disposition of the applicable architecture/specification revisions and approval of the implementation planning baseline.

### WP-01 — Exact source and integration target reconciliation

**Purpose:** Establish the actual source state against which the approved specification will be implemented.

**Planning outputs:**
- exact repository, branch, commit and tree manifest;
- per-mechanism source map, call paths, tests and persistence/replay paths;
- compatibility disposition: retain, adapt, replace or reject, each with evidence;
- public API and downstream compatibility risk register;
- workflow/build/test preservation plan;
- selective donor evidence map, with no wholesale adoption assumption.

**Activation prerequisite:** Gate A clearance and explicit Project Director source-baseline selection. Historical static audits are not substitutes for exact-target reinspection.

### WP-02 — Experience, memory and continuity contract

**Purpose:** Define the first durable evidence path across intake, memory and coordinated state.

**Planning outputs:**
- experience identity, provenance and context obligations;
- owner-managed memory lifecycle and retrieval evidence;
- persistence, replay, interruption, idempotency and recovery obligations;
- partial-write, corruption and stale-dependency failure cases;
- acceptance scenarios proving retrieved history is actually consumed downstream.

**Primary owners:** BM-01, BM-03, BM-11; supporting BM-02/BM-04 contracts.

### WP-03 — Representation and belief revision contract

**Purpose:** Ensure experience can be interpreted and beliefs revised without collapsing uncertainty or competing claims.

**Planning outputs:**
- observation/interpretation/hypothesis/belief distinctions;
- competing-claim and counterevidence lifecycle;
- provenance, scope, confidence/qualification and invalidation rules;
- owner-controlled acceptance and revision;
- scenarios for contradiction, delayed evidence and mistaken interpretation.

**Primary owners:** BM-02, BM-04; integrated with BM-01/BM-03/BM-11.

### WP-04 — Memory-supported reasoning contract

**Purpose:** Ensure reasoning is a real downstream consumer of relevant evidence and memory.

**Planning outputs:**
- premise, assumption, inference and conclusion lineage;
- applicability and retrieval-context constraints;
- contradiction, counterexample and defeated-assumption handling;
- explicit downstream owner disposition;
- scenarios where changing or removing relevant memory changes the inference for a traceable reason.

**Primary owner:** BM-12; integrated with BM-02/BM-03/BM-04/BM-11.

## 5A. First-slice owner-contract detail — planning refinement

The following contract detail makes WP-02–WP-04 reviewable and testable without selecting implementation technology, data schema, algorithm or source baseline. It is derived from the historically accepted PR #174 mechanism specification at `0811a59e46bf934e32e794f90e4e7d18d4e2bd97`. It is a planning decomposition, not a replacement specification or implementation authorization.

### WP-02 contract: attributable experience, memory and continuity

| Contract element | BM-01 — acquisition owner | BM-03 — memory owner | BM-11 — coordination owner |
|---|---|---|---|
| Receives | External/internal observation, provider result, action evidence, internal event or restored record | Evidence-bearing experience plus context and retention request | Owner events, dependency versions, work identity, interruption/recovery signals |
| Authoritative state | Acquired record and source/acquisition lineage | Retained episodes, classifications, retrieval/consolidation records and supersession lineage | Dependency graph/status, coordination records, checkpoints, conflict and recovery status |
| Must preserve | Original content or verifiable reference; source, acquisition/event time, modality, context, integrity and transformation lineage | Episode provenance/context; distinction between storage and truth; retrieval-use evidence; working eviction versus durable history | State ownership, dependency identity/version, committed versus pending/failed status, interruption and recovery history |
| Must not claim | Interpretation, belief truth, successful perception from transport acknowledgement | That retrieval implies relevance/truth, or that missing memory proves non-occurrence | Authority to overwrite owner state, or successful cognitive recovery from substrate/process availability |
| Failure states | Missing/malformed/partial/duplicate/delayed/reordered evidence; source/provider unavailable; integrity unknown | Empty result, unavailable store, retrieval failure, corruption, stale index/dependency and partial persistence are distinct | Conflict, duplicate/out-of-order event, partial commit, stale dependency, interrupted work and unvalidated recovery |
| Required evidence | Original-to-derived lineage; source and event-time distinction; malformed/provider failure negative controls | Retain/retrieve/reconstruct with provenance; relevant-versus-irrelevant retrieval; durable episode survives working-context eviction | Idempotent replay; owner conflict disposition; dependency invalidation; interrupted recovery with cognitive-state validation |

**Cross-owner invariants:**

1. A successful transport, provider or storage acknowledgement is not proof that an experience was semantically accepted or that cognitive state is valid.
2. Intake failure, unavailable source, missing evidence and an empty retrieval result must never be rewritten as a negative observation.
3. Memory stores episodes and derived memory artifacts; the relevant epistemic owner decides what those artifacts support.
4. BM-11 coordinates and validates dependencies but does not become the owner of BM-01 acquisition records or BM-03 memory content.
5. Replay and reconstruction must be idempotent or explicitly detect duplicates; partial writes cannot be reported as complete state transitions.
6. If recovery cannot establish coherent owner state, affected state remains unavailable, provisional or quarantined pending owner validation.

**Minimum scenario coverage:** accepted-baseline scenarios 2, 4, 6, 24, 25 and 26; use scenario 3 only where provider/capability failure is in scope. Scenario 4 is an integration obligation: retrieved history must later affect inference, not merely appear in a context object.

**WP-02 exit evidence:** one attributable episode is retained and retrieved with provenance/context; relevant and irrelevant retrieval are distinguished; durable history survives the declared lifecycle; interruption/reconstruction validates state and pending work; negative cases distinguish absence, failure, corruption, partial write and unavailability.

### WP-03 contract: representation and owner-controlled belief revision

| Contract element | BM-02 — representation owner | BM-04 — belief/world-state owner |
|---|---|---|
| Receives | BM-01 acquired evidence, context, retrieved memory and active task/goal context | Evidence, candidate interpretations, retrieved episodes, reasoning conclusions, counterevidence and dependency-change notices |
| Authoritative state | Derived representations, candidate interpretations, entity/event hypotheses, relations and transformation lineage | Accepted/qualified beliefs, scope, evidence support/contradiction, status, revision lineage and dependent-state references |
| Must preserve | Acquisition/interpretation distinction; alternative interpretations; modality/source context; evidence and assumption links | Claim scope/time, epistemic status, uncertainty, competing claims, prior versions and evidence responsible for each revision |
| Must not claim | That normalized labels or lexical matches prove identity; that interpretation is accepted belief | That every inference is a belief; that missing evidence proves absence; that one generic confidence update is valid for all evidence |
| Failure states | Unsupported or ambiguous interpretation, absent modality capability, low confidence and contradictory context | Unresolved conflict, stale claim, failed/partial update, missing support and dependent state requiring invalidation |
| Required evidence | Same evidence under ambiguous contexts; later revision without rewriting acquisition; multiple interpretations retained where underdetermined | Accept/qualify/suspend/withdraw paths; contradiction and counterevidence; prior revision lineage; dependent-state invalidation and recovery |

**Cross-owner invariants:**

1. BM-01's acquired evidence remains unchanged by interpretation or belief revision.
2. BM-02 may publish one or more candidate interpretations with evidence links and epistemic status; it cannot silently promote them into accepted beliefs.
3. BM-04 alone accepts, qualifies, revises, suspends, supersedes or withdraws authoritative belief state.
4. BM-04 revision must preserve the previous version and identify the evidence/reason for change.
5. A belief change exposes affected predictions, plans, goals and derived representations for owner-specific reconsideration; BM-11 coordinates invalidation but does not decide their new content.
6. Where evidence does not discriminate, competing claims remain visible and commitment may be deferred.

**Minimum scenario coverage:** accepted-baseline scenarios 1, 2 and 7, with scenario 23 for stale dependent plans. Delayed evidence, mistaken interpretation and failed belief update are mandatory negative-path cases.

**WP-03 exit evidence:** an acquired observation is represented without overwrite; competing interpretations/claims survive; new evidence changes only the justified derived state; belief revision is performed by BM-04 with preserved lineage; dependent state is identified and reconsidered by its actual owner.

### WP-04 contract: memory-supported general reasoning

| Contract element | BM-12 — reasoning owner | Receiving owner(s) |
|---|---|---|
| Receives | Evidence-bearing premises from BM-01; interpretations from BM-02; retrieved episodes from BM-03; current claims/status from BM-04; scoped hypotheses/predictions from BM-05; task/context and constraints from relevant owners | Provisional conclusion, alternative explanations, premise/assumption lineage, uncertainty, scope, counterexamples and unresolved gaps |
| Authoritative state | Reasoning episode; premise/assumption set; inference/argument lineage; provisional conclusions and alternatives; contradiction/counterexample records; dependency references | BM-04 owns accepted beliefs; BM-05 owns causal/prediction state; BM-08 owns goal/plan/decision state |
| Must preserve | Premise identity/version, source and temporal provenance, retrieval context, epistemic category, applicability, assumptions, alternatives, uncertainty and dependency lineage | Original reasoning episode plus accept/qualify/reject/defer disposition and rationale |
| Must not claim | That valid derivation proves premise truth; that retrieved memory is relevant merely because returned; that a provisional conclusion is an accepted belief, causal model, plan or authorization | That receipt/logging alone is successful reasoning integration |
| Failure states | Empty/incomplete premises, stale/out-of-scope premise, contradiction, defeated assumption, unavailable memory, unresolved alternatives and invalidated conclusion | Rejection/qualification, missing consumer, stale conclusion, owner evaluation failure and downstream state not changed |
| Required evidence | Traceable inference with explicit premises/assumptions; paired relevant-memory and no-memory comparison; irrelevant-memory negative control; contradiction/defeated-assumption handling | Owner-specific evaluation record; preserved rationale; exact linkage between accepted inference and any resulting authoritative state change |

**Cross-owner invariants:**

1. BM-12 performs general derivation/evaluation; BM-02 represents, BM-03 retrieves, BM-04 commits belief state, BM-05 resolves predictions/causal hypotheses and BM-08 owns goals/plans/decisions.
2. BM-12 cannot promote retrieved memories, interpretations, assumptions or provisional conclusions to a stronger epistemic status.
3. A conclusion is not accepted merely because it is validly derived: premise truth, provenance, applicability, scope and uncertainty remain separate questions.
4. Empty or contradictory premises produce an explicit unresolved/conflict result, not a substantive success.
5. If a material premise, assumption, memory interpretation, belief or context changes, BM-11 tracks the dependency and the affected owner must reconsider the conclusion before consequential reuse.
6. Delivery, logging or storage of a reasoning artifact is not downstream integration. The receiving owner must evaluate it and preserve its disposition.
7. If a receiving owner accepts a conclusion, evidence must show the exact accepted inference and owner-state version, plus a material effect on that owner's computation/state where the scenario requires one.

**Minimum scenario coverage:** accepted-baseline scenarios 4 and 27–34. The current PR #174 proposal's additional scenarios 41–48 remain proposed/unaccepted, but are recorded as forward-looking planning risks and must not be represented as accepted requirements.

**WP-04 exit evidence:** a relevant retrieved episode materially changes an inference for a traceable reason; irrelevant memory does not gain authority; premise/assumption and alternative lineage is inspectable; contradictions and defeated assumptions qualify/withdraw conclusions; BM-04 or another actual receiving owner records its disposition; at least one accepted result causes a demonstrated, version-linked downstream owner-state/computation change when that capability is in scope.

### First-slice integrated acceptance trace

The first coding-slice target is not satisfied by independent BM-01, BM-03, BM-02, BM-12 and BM-04 unit tests alone. Its end-to-end evidence must join the same attributable experience and its later use across the following trace:

1. BM-01 records an experience with source, event/acquisition time, context and immutable acquisition lineage.
2. BM-02 creates a candidate interpretation linked to that experience, retaining ambiguity and epistemic status.
3. BM-03 retains the episode and later retrieves it with provenance and contextual applicability.
4. BM-12 receives the retrieved episode as an identifiable premise, alongside current evidence/claims and explicit assumptions; it records how the memory affected or did not affect the inference.
5. BM-04 evaluates any candidate belief change and records accept/qualify/reject/defer with evidence and revision lineage.
6. BM-11 tracks dependency versions, interruption and recovery; after a relevant upstream change, stale conclusions are not reused without reconsideration.
7. A later attributable experience confirms, qualifies or defeats the earlier conclusion; the responsible owner updates state while preserving the full history.

**Required paired/negative controls:** remove or substitute the relevant memory and compare inference lineage; supply irrelevant memory; provide contradictory or defeated evidence; make retrieval unavailable; interrupt between persistence stages; replay a duplicate; fail a partial write; reconstruct with stale dependent state. Each case must yield a distinct, attributable status rather than a generic success/failure.

**Planning stop condition:** if an accepted specification does not settle an owner transition, state authority, failure disposition or required evidence, record the unresolved question and decision owner. Do not choose a schema, algorithm, ordering guarantee, persistence protocol or implementation behavior by implication.

### First-slice acceptance case set — non-operative test design

This case set turns the accepted-baseline scenarios into a bounded first-slice verification plan. It is not a replacement for the governing scenarios, does not prescribe fixture content or implementation technology, and does not claim any case has been executed.

| Case | Accepted scenario(s) | Controlled challenge | Minimum pass evidence | Required owner(s) |
|---|---:|---|---|---|
| FS-01 — Acquisition integrity | 2 | Interpret and revise the meaning of one acquired experience across later evidence | Original acquisition identity/content or verifiable reference remains unchanged; derived interpretations and belief versions link back to it | BM-01, BM-02, BM-04 |
| FS-02 — Relevant memory influence | 4, 30 | Run a matched inference with and without a relevant retrieved episode | Inference/premise lineage identifies the memory; a justified difference in conclusion or support is observable; no unsupported memory premise appears | BM-03, BM-12, receiving owner |
| FS-03 — Irrelevant memory restraint | 5 | Supply a retrieved but contextually irrelevant episode | Retrieval is recorded, but the episode is excluded or qualified as a premise with an inspectable applicability rationale; no authority is gained from retrieval alone | BM-03, BM-12, BM-04 |
| FS-04 — Sufficient premise derivation | 27 | Supply sufficient, in-scope evidence and assumptions | Every premise has identity/version/provenance; inference links premises to conclusion; conclusion remains provisional pending owner evaluation | BM-12, BM-04 |
| FS-05 — Insufficient evidence | 28 | Remove a necessary premise or make it unavailable | Explicit unresolved/insufficient-evidence result; no fabricated substantive conclusion; missing retrieval is not treated as proof of absence | BM-03, BM-10, BM-12 |
| FS-06 — Contradiction preservation | 29 | Supply mutually incompatible premises | Conflict and affected conclusions remain inspectable; no silent winner, last-write preference or unqualified conclusion | BM-12, BM-04 |
| FS-07 — Defeated assumption | 31 | Introduce later evidence that defeats an explicit inference assumption | Dependent conclusion is qualified/withdrawn or marked stale; prior inference and assumption lineage remain; affected owners are notified | BM-12, BM-04, BM-11 |
| FS-08 — Counterexample and generalization restraint | 32 | Supply a counterexample to a previously supported generalization | Affected generalization is invalidated or narrowed; unrelated claims remain unchanged unless their dependencies require review | BM-12, BM-04, BM-05, BM-11 |
| FS-09 — Uncertainty and alternatives | 33 | Provide underdetermined evidence supporting multiple plausible explanations | Alternatives and uncertainty remain explicit; no forced single answer; any request for discriminating evidence is traceable | BM-12, BM-02, BM-04 |
| FS-10 — Stale/out-of-scope premise | 34 | Reuse a premise after its scope, validity or supporting state changes | Premise is rejected, qualified or marked stale before consequential use; source and invalidation reason are inspectable | BM-12, BM-04, BM-05, BM-10 |
| FS-11 — Belief owner disposition | 1, 7, 23 | Present a reasoning conclusion with competing or contradictory evidence and dependent state | BM-04 records accept/qualify/reject/defer; prior belief version survives; affected dependent plan/prediction is reconsidered by its actual owner | BM-04, BM-05/BM-08 as applicable, BM-11 |
| FS-12 — Lifecycle and recovery | 6, 24, 25, 26 | Evict working context, interrupt persistence, replay duplicate events and reconstruct | Durable episode remains retrievable; duplicate/partial transitions are detected; owner state and dependencies are validated before resume; incomplete recovery is not reported as success | BM-03, BM-10, BM-11, affected owner |

**Case-set rules:**

- Each case records exact input/experience IDs, software revision, configuration, environment, initial owner-state versions, event order, and evaluator version once execution is separately authorized.
- Cases must be paired where the claim depends on comparison (for example, relevant memory versus no memory); only the intended variable changes.
- Negative controls are first-class outcomes. A case that correctly remains unresolved, rejects irrelevant evidence or defers a belief update can pass.
- A case passes only when the expected owner state transition and its lineage are observed. Logs, API responses, class presence or emitted artifacts alone are insufficient.
- The first-slice set does not claim BM-05 prediction resolution or BM-09 developmental learning has passed. Those are later dependent increments and use the separate WP-05/WP-06 contracts and R0–R6 protocol.
- Thresholds, fixture identities, statistical treatment and run limits remain to be frozen under WP-00/WP-08 after accepted inputs and a source baseline are established.



---

### WP-05 contract: scoped prediction, outcome attribution and feedback

| Contract element | BM-05 — prediction/model owner | Evidence/receiving owners |
|---|---|---|
| Receives | Qualified premises and beliefs, relevant episodes, context, causal/association hypotheses, prediction objective and expected observation | Attributable later experience/outcome, sensor/provider/execution status, changed premises and dependency notices |
| Authoritative state | Association/causal hypotheses, prediction identity, scope, assumptions, horizon, expected observation, resolution criteria and resolution lineage | BM-01 owns acquired outcome evidence; BM-04 owns belief revision; BM-09 owns learning-candidate lifecycle; BM-11 coordinates dependencies |
| Must preserve | Distinction among co-occurrence, correlation, association, temporal precedence, causal hypothesis and verified causal knowledge; prediction identity and independent resolution | Event/acquisition time, source reliability, actual observation versus acknowledgement/failure, outcome attribution and unresolved status |
| Must not claim | That co-occurrence alone proves causality; that an action request or provider acknowledgement proves an outcome; that unresolved means success/failure | That prediction error alone identifies its cause or authorizes model/behavior change |
| Failure states | Duplicate/similar predictions, missing or delayed outcome, partial/ambiguous/contradictory evidence, out-of-order outcome, invalid resolution criteria, unobserved outcome | Sensor/provider failure, cancelled/failed execution, infrastructure failure, weak attribution and conflicting observations |
| Required evidence | Independent prediction IDs and resolution; scoped assumptions/horizon; content-appropriate comparison; counterexample/confounder handling; delayed/out-of-order attribution | BM-01 evidence lineage; BM-04 disposition where belief changes; BM-09 candidate/defer record where adaptation is considered |

**Cross-owner invariants:**

1. Every prediction has an identity and explicit scope, assumptions, horizon, expected observation and resolution conditions; similar predictions must remain independently resolvable.
2. A prediction is unresolved until qualifying evidence satisfies its declared resolution conditions. Missing observation, failed sensor, cancelled action, provider acknowledgement and verified negative outcome are distinct.
3. BM-01 records what was actually observed and its source; BM-05 decides whether that evidence bears on a particular prediction, preserving attribution rationale.
4. Comparison uses a measure appropriate to the predicted content. Exact equality is not a universal prediction-error metric.
5. Association, correlation, temporal order and causal hypothesis remain distinct statuses. A prediction discrepancy is not, by itself, causal explanation.
6. BM-05 may publish a resolved outcome and evidence-backed candidate; BM-04 evaluates belief changes, BM-09 evaluates learning candidates, and BM-11 tracks affected dependencies.
7. Weak or ambiguous attribution defers resolution or marks it qualified; it must not be forced into a success/failure label for convenience.

**Minimum scenario coverage:** accepted-baseline scenarios 7–11, with scenario 17 where a defeated premise affects a candidate goal. Scenario 8 specifically challenges co-occurrence-to-causality promotion; scenarios 9–10 challenge prediction identity and delayed outcome attribution; scenario 11 distinguishes cancelled action/sensor failure from verified external outcome.

**WP-05 exit evidence:** two similar predictions resolve independently; a delayed/out-of-order attributable outcome resolves only the matching prediction; an unobserved or failed-sensor case remains unresolved; a confounder/counterexample prevents unjustified causal promotion; downstream BM-04/BM-09 receives the exact attributed evidence and records its own disposition.

### WP-06 contract: owner-approved learning, persistent change and recovery

| Contract element | BM-09 — learning coordinator/owner | Affected authoritative state owner(s) |
|---|---|---|
| Receives | Attributed experiences and outcomes, discrepancy/limitation evidence, candidate scope, counterexamples, current capability baseline and dependency status | Candidate change proposal, evidence set, expected effect, affected-state map, risk/containment and evaluation record |
| Authoritative state | Learning hypotheses/candidates, evidence and evaluation records, accepted learning-change version/history, monitoring and rollback lineage | The actual belief, representation, memory, causal model, prediction, attention, goal, reasoning strategy or skill state owned by BM-01–BM-12 |
| Must preserve | Candidate lifecycle from evidence/attribution through evaluation, controlled activation, persistence, monitoring and recovery; prior and accepted versions | Owner-specific approval/qualification/rejection, state version, constraints and local invariants |
| Must not claim | That every surprise is learnable; that one episode proves a general rule; that a candidate is accepted before required owner evaluation; that persistence alone proves behavioral learning | That BM-09 can overwrite owner state or bypass owner-specific acceptance and safety constraints |
| Failure states | Weak attribution, insufficient/conflicting evidence, overfit candidate, counterexample regression, negative transfer, incomplete evaluation, partial activation or reconstruction failure | Owner rejection/defer, incompatible update, stale dependency, partial state transition and failed rollback/containment |
| Required evidence | Candidate rationale; evidence/counterevidence; context and scope; evaluation; explicit owner decisions; accepted version and provenance; post-activation monitoring | Exact pre/post owner state and behavior; persistence/reconstruction; rollback or containment; later relevant effect and held-out transfer/regression |

**Cross-owner invariants:**

1. Learning is a candidate lifecycle, not an automatic reaction to surprise, reward, prediction error or repetition.
2. Attribution precedes candidate formation. If evidence cannot be attributed to the relevant prediction, belief, representation, strategy, skill or capability, learning is deferred.
3. A candidate states what may change, why, the evidence and assumptions, expected scope/effect, counterexamples and interference risk.
4. BM-09 coordinates evaluation and records the accepted developmental change; each affected mechanism retains authority over its own authoritative state and must explicitly accept, qualify, reject or defer the proposed change.
5. Multi-owner changes must not be reported as complete while only some affected owners have committed. Planning must define observable prepare/commit/failure/recovery outcomes without selecting a particular transaction technology or protocol.
6. If evaluation is incomplete, the candidate remains inactive. If activation or persistence partially fails, the affected capability is restored to a coherent prior state or isolated and explicitly marked incomplete; no false success is published.
7. Persistence is necessary but insufficient. A learning claim requires measurable, causally attributable change in the receiving owner's later behavior/state after reconstruction.
8. Evaluation must include counterexamples and acquisition-context performance, related held-out transfer, unrelated-context non-transfer where appropriate, negative transfer and regression.
9. Candidate rejection, suspension or rollback preserves the evidence and history that caused the decision; a rollback is itself an attributable state transition.
10. A numeric parameter change or local optimization supports only a narrow adaptation claim unless broader capability evidence is separately demonstrated.

**Minimum scenario coverage:** accepted-baseline scenarios 19–21. Scenario 22 constrains claim scope. The current proposed specification adds further learning-related requirements, but those additions remain proposed/unaccepted and cannot be presented as accepted baseline obligations.

**WP-06 exit evidence:** an attributed candidate is evaluated against supporting evidence and counterexamples; affected owners explicitly disposition it; a justified accepted change persists through reconstruction; a later relevant task shows a measurable receiving-owner behavior/state change; held-out related and unrelated cases establish transfer boundaries; a regressing candidate is rejected or rolled back with coherent state and preserved history.

### WP-05/WP-06 handoff invariant

A resolved prediction/outcome may contribute evidence to a learning candidate, but it does not directly mutate a belief, causal model, strategy or skill. The evidence path is: BM-01 attributable outcome → BM-05 prediction-specific resolution and attribution → BM-09 candidate formation/evaluation → affected owner decision → coordinated activation/persistence → post-change monitoring and reconstruction → measured later behavior. Every transition retains identity, provenance, status and the responsible owner. No transition is inferred solely from a log entry, delivery event, numeric score or storage acknowledgement.

### WP-05 — Prediction and feedback contract

**Purpose:** Connect expectations to correctly attributed outcomes and qualified learning candidates.

**Planning outputs:**
- prediction identity, scope, assumptions, horizon and resolution criteria;
- delayed, partial, conflicting, missing and invalid outcome handling;
- separation of environment outcome from provider/execution/substrate failure;
- prediction-error attribution and candidate formation;
- receiving-owner approval and rejection evidence.

**Primary owner:** BM-05; integrated with BM-01/BM-03/BM-04/BM-09/BM-12.

### WP-06 — Owner-approved learning and persistence contract

**Purpose:** Make learning a coordinated, persistent change across the mechanisms that own affected state.

**Planning outputs:**
- candidate lifecycle and risk/eligibility evidence;
- affected-owner identification and approval boundaries;
- atomicity/coordination requirements for multi-owner updates;
- persistence/reconstruction and rollback/containment obligations;
- longitudinal, held-out transfer, negative-transfer and regression evaluation plan.

**Primary owner:** BM-09; coordinated by BM-11 and every affected state owner.

### WP-07 — Attention, appraisal, goals, planning and metacognitive integration

**Purpose:** Define how one Brain selects what deserves processing, evaluates significance in its current context, forms or revises goals, plans useful next steps, and detects when its own cognition needs correction.

**Capability outcome:** When faced with multiple active contexts, changing circumstances, incomplete evidence and competing demands, the Brain can preserve and prioritize the right work; resume a suspended context with its constraints; evaluate the significance of an event relative to current goals, relevant history and qualified internal-condition evidence; form, evaluate, revise or abandon a candidate goal; build and update a feasible plan; choose an appropriate cognitive decision; and identify when it should gather evidence, ask for clarification, defer or surface a limitation. It must not confuse salience with truth, appraisal with command, intent with permission, an action request with execution, or an attempted action with a verified consequence.

**Owner contract:**

| Owner | Authoritative state | Required behavior | Must not claim or do |
|---|---|---|---|
| **BM-06 — Attention and active context** | Focus, attention history, active-context membership, resource allocation, interruption and resumption state | Allocate limited processing capacity using contextually relevant signals such as task relevance, uncertainty, novelty, urgency, risk, goal state, consequences, appraisal and cognitive load; support multiple appropriately isolated contexts; redirect focus when new evidence or changed goals justify it; preserve enough state to resume work | Treat salience as truth, priority as authorization, active context as authoritative memory/belief state, or eviction as deletion of durable evidence |
| **BM-07 — Affective appraisal and valuation** | Contextual appraisal state, qualified cognitive estimates of relevant internal conditions, evidence and developmental lineage | Evaluate significance relative to goals, context, history, predictions and authorized internal-condition observations; preserve uncertainty and multiple dimensions; permit the same event to have different significance under different conditions; allow later evidence to revise appraisal | Use a fixed stimulus-to-emotion or emotion-to-action mapping; let appraisal directly command action, establish an external fact, or overwrite SYS-owned state. SYS-05 remains authoritative for autonomic regulation; SYS-08 remains authoritative for compute, storage, devices and runtime substrate |
| **BM-08 — Goals, intent, planning and decision** | Goal lifecycle, candidate-goal lineage, intent, plans, decision rationale and dependencies | Distinguish supplied goals, experience-acquired candidate goals, governance constraints and dependent subgoals; form candidates from interpreted experience without fixed triggers; evaluate relevance, feasibility, expected consequences, conflicts, resources, uncertainty, risk and constraints; accept, revise, defer, suspend or abandon with reasons; build plans from qualified evidence and reconsider them when dependencies change; choose among acting through an authorized request, clarifying, observing, gathering evidence, deferring, rejecting or escalating | Claim a supplied goal is internally originated; fabricate a goal when none is justified; equate priority with urgency or authorization; treat a cognitive decision/action request as permission or verified execution |
| **BM-10 — Metacognitive monitoring and control** | Monitoring observations, detected inconsistencies, confidence/calibration assessments, limitation hypotheses and corrective-work lineage | Detect unsupported conclusions, scope overreach, contradiction, stale dependencies, missing evidence, poor prediction calibration, overload, repeated failure and capability degradation; request proportionate retrieval, evidence, reasoning, belief or plan reconsideration; verify whether correction improved the task outcome; preserve original and correction history | Directly overwrite another owner's state, replace reasoning or decision ownership, endlessly reprocess without new evidence, or conceal repeated unsuccessful correction as increased confidence |

**Cross-owner invariants:**

1. Attention selects what receives processing; it does not determine truth or create a goal. Retrieval and durable history remain with BM-03, qualified claims with BM-04, predictions with BM-05 and conclusions with BM-12.
2. Appraisal is a qualified contextual influence on attention, memory, learning, goal evaluation and decision formation. It is neither a factual premise by itself nor an action command.
3. Goal origin, current priority, feasibility, governance constraint, authorization, action request, execution record and verified outcome remain separate states with traceable transitions.
4. Every material goal and plan retains its supporting evidence, assumptions, scope, resource constraints and dependency versions. A changed premise or constraint triggers proportionate reconsideration before consequential use.
5. BM-10 requests correction; the actual state owner performs it. Correction is complete only when its effect on the task or affected capability is evaluated.
6. BM-11 coordinates context dependencies, interruption, conflict and recovery but does not become a second cognitive authority. External governance, security, execution and outcome verification remain with their approved SYS/external owners.
7. Having no eligible candidate goal, insufficient evidence, or no safe/useful next step is a valid result. The Brain must be able to clarify, observe, defer or report a limitation rather than manufacture certainty or activity.

**Failure states to preserve:** attention starvation, overload, focus oscillation, dropped or stale context; unreliable or conflicting appraisal; unsupported or infeasible candidate goals; unresolved goal conflict; resource or constraint changes; stale plans; missed dependency invalidation; unauthorized action requests; unverified consequences; metacognitive non-convergence; and interruption/reconstruction that cannot validate the resumed context. Each is distinct and must not be collapsed into generic task failure.

**Minimum accepted-baseline scenario coverage:** scenarios 12–18 and 23 in the historical accepted PR #174 baseline. Scenarios 27–34 provide cross-cutting reasoning, uncertainty, contradiction, defeated-assumption and stale-premise obligations where WP-07 consumes or acts on those results. The additional PR #174 proposal scenarios 35–54 remain proposed/unaccepted and must not be promoted into accepted requirements by this planning contract.

**Integrated capability demonstration:** use a bounded, meaningful task sequence with at least two competing contexts and changing evidence. The Brain must preserve both contexts and their constraints; expose why focus changed; evaluate the same material event under differing goal/context conditions without a fixed mapping; form or revise a candidate goal only when the evidence supports it; produce a feasible plan; ask for missing information or defer when materially underdetermined; invalidate and reconsider a plan when a supporting belief or constraint changes; and preserve intent separately from any external authorization, action and verified outcome. Interrupt and resume the work to establish continuity. The task result—not the number of internal operations or test assertions—is the primary capability evidence.

**WP-07 exit evidence:** a repeatable integrated task demonstration shows competent context selection and resumption, justified goal/plan formation and revision, useful appraisal modulation, and bounded metacognitive correction. The task outcome and decision quality are observable; supporting traces establish provenance and owner boundaries; negative controls show that irrelevant salience, unsupported goals, stale plans and denied actions do not produce false success. Later developmental claims must additionally show that experience improves subsequent task behavior and transfers only where justified; that later learning claim belongs to WP-06/WP-08, not WP-07 alone.

**Primary owners:** BM-06/BM-07/BM-08/BM-10, integrated with BM-01–BM-05, BM-09, BM-11/BM-12 and the applicable SYS governance/execution boundaries.

### WP-08 — Integrated starter-training and evaluation protocol

**Purpose:** Prepare controlled training runs that test mechanisms and interactions rather than preload desired behaviour.

**Planning outputs:**
- staged experience curriculum with source and difficulty controls;
- baseline and post-training measures;
- held-out related-context and unrelated-context checks;
- persistence/reconstruction checks;
- regression, interference, contradiction and recovery scenarios;
- claim thresholds and explicit limitations.

**Activation prerequisite:** Integrated capability acceptance plan approved; runtime/training execution separately authorized.

## 6. Required evidence classes

Every work package must identify which evidence classes apply and what constitutes a pass:

1. **Contract evidence:** owner, inputs/outputs, lifecycle, authority and failure semantics are explicit.
2. **Source evidence:** exact selected revision, paths, symbols, call paths and compatibility disposition.
3. **Unit/owner evidence:** local invariants and owner-controlled state transitions.
4. **Integration evidence:** at least two or more mechanisms exchange and consume attributable state correctly.
5. **Persistence/reconstruction evidence:** changes survive the declared lifecycle and reconstructed state is validated.
6. **Negative-path evidence:** delayed, missing, contradictory, malformed, stale, partial and failed operations.
7. **Longitudinal evidence:** repeated experiences produce measured, persistent later change.
8. **Transfer evidence:** improvement carries to a held-out related context without unjustified transfer to unrelated contexts.
9. **Regression/containment evidence:** harmful or unsupported changes are detected, contained or reversed without incoherent partial state.
10. **External-boundary evidence:** cognitive conclusions cannot impersonate verified execution, governance, security or external-world outcomes.

A work package cannot pass by class/file presence, a green isolated unit test, or a successful demonstration that embeds the expected answer.

## 7. Decision register before implementation activation

| Decision | Required authority/evidence | Current state |
|---|---|---|
| Accept complete/final PR #173 architecture revision | Independent review and explicit Project Director disposition | OPEN |
| Reconcile and accept applicable PR #174 specification revision | Exact-head independent review and explicit Project Director disposition | OPEN for current corrected proposal |
| Close Documentation Foundation and accept exact final revision | DF gate evidence, required independent/fresh-reader clearance, exact-revision Project Director decision | OPEN / NOT ACCEPTED |
| Clear Gate A and select implementation source baseline | Exact-target source reconciliation and Project Director decision | NOT CLEARED / NOT SELECTED |
| Pass Gate B capability acceptance | Mechanism-to-source traceability and integrated capability evidence | NOT PASSED |
| Activate specific implementation work packages | Approved baseline, scoped package, explicit Project Director authorization | NOT AUTHORIZED |
| Execute starter-training runs | Integrated test/training protocol and separate execution authorization | NOT AUTHORIZED |

## 8. Planning exit criteria

This kickoff planning package is ready for review when:
- each work package has a bounded capability outcome, owner set, dependencies, required evidence and activation prerequisite;
- the first integrated learning loop is explicit and does not hardcode desired behaviour;
- accepted historical baselines are not conflated with current proposals;
- every implementation activation dependency is visible;
- the plan distinguishes planning completion from source-baseline selection, implementation authorization and capability acceptance.

Planning exit does **not** mean implementation is authorized. Implementation may begin only after the applicable architecture/specification, Documentation Foundation, Gate A, Gate B and Project Director decisions are satisfied and recorded.

---

**Current disposition:** Planning kickoff started. Work packages are proposed and non-operative. No runtime implementation, runtime tests/builds, donor adoption, source-baseline selection, merge, integration or deployment is claimed or authorized by this document.
