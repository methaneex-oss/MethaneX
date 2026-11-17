# Parallel Non-Operative JARVIS Implementation-Planning Supplement — 2026-11-17

**Document status:** Non-operative planning supplement; prepared under a narrow Project Director exception recorded in the 2026-11-17 Builder conversation.  
**Repository:** methaneex-oss/MethaneX  
**Planning branch:** plan/brain-implementation-roadmap-20261103  
**Planning source HEAD:** 1423ac7803ac07fec1ecbaf4608c2c035a95332b (PR #175)  
**Governing principle:** **Engineer the mechanisms; let behavior be acquired through experience.**

---

## 1. Purpose and authority

This supplement begins a bounded, non-operative planning exercise in parallel with completion of the Documentation Foundation. It organizes the existing Brain responsibility model into a dependency-aware planning sequence, names the evidence required at each capability boundary, and defines a reusable work-package and verification structure.

The Project Director's 2026-11-17 exception authorizes only this preparatory planning work before formal Documentation Foundation acceptance. It does not make this document an operative implementation roadmap and does not change the current project phase or any repository gate.

### 1.1 Permitted work under this exception

- Reconcile the existing implementation roadmap with the current architecture and mechanism-specification proposals.
- Map mechanism ownership, upstream dependencies, downstream consumers and external authority boundaries.
- Propose integrated capability increments rather than isolated module tickets.
- Define observable acceptance criteria, test classes, evidence requirements, failure cases and rollback/containment expectations.
- Identify the decisions and approvals required before any later work package can be activated.

### 1.2 Work that remains prohibited

This supplement does not authorize:

- Runtime source changes, refactoring, migrations, implementation tickets for immediate execution, builds, runtime tests, benchmarks, fuzzing or sanitizers.
- Selection of a source baseline, donor adoption, cherry-picking, branch replay, rebase, retarget, merge or integration of PRs.
- Selection of concrete algorithms, model providers, frameworks, databases, programming languages, schemas, APIs, protocols, deployment topology or infrastructure.
- Changes to authoritative cognitive state ownership or to the accepted whole-system security, governance, authorization and execution boundaries.
- Starting Stage A, claiming any documentation gate has passed, training the Brain, or deploying it.

The exception is narrower than reopening the held project stage. Stage A remains NOT STARTED / HELD. Runtime implementation remains NOT AUTHORIZED.

## 2. Exact planning inputs and current authority status

This plan uses existing repository documents as planning evidence, not as a new architecture decision.

| Work item | Exact revision / state | What may be used now | What remains unresolved |
|---|---|---|---|
| PR #173 — Brain Foundation Architecture | Current report-only HEAD a96af5b18d3a1d580ff56cff6191240893bceeb5; architecture reviewed at 1f137cbaed985821bbc32408151911b18418f713 | The reviewed architecture's responsibility model, ownership and partial-failure invariants may inform planning | xAI verdict is PARTIALLY CLEAR. Whole-architecture acceptance, CF-26 independent challenge and CF-27 final gate remain open. |
| PR #174 — Brain Mechanism Specification | Current PR HEAD c34472354e4122fc1d78dc25bf45d81f1eb4dc69; current specification blob cfdda9e6e7070cd5533b076e9bd77c2904694a32 | Its BM-01–BM-12 responsibility definitions, information contracts and scenario structure may be used as a proposed specification input | Current proposal remains draft/unmerged; independent re-review and Project Director disposition remain outstanding. The historically accepted 0811a59e specification is accepted only for that exact historical planning-baseline scope, not as acceptance of the corrected current proposal. |
| PR #175 — implementation roadmap | HEAD a01899b4e3b3ee9c6e5e3d83fedd0f22ce2b3891 before this matrix addition; open/draft/unmerged; base PR #174 at 0811a59e46bf934e32e794f90e4e7d18d4e2bd97 | Existing dependency graph, proposed vertical increments, verification portfolio and work-package template are retained as planning material | Gate A remains NOT CLEARED; Gate B capability acceptance has NOT PASSED. No implementation baseline is selected. The proposal's historic recommendation to use PR #174 as an integration starting point is not adopted by this supplement. |
| PR #176 — donor defect corrections | HEAD 4cf017e073da980c9f77d739fde6f92ef1a2fbc1; open/draft/unmerged; based on PR #156 HEAD 7fe212bbb0bd61116ea56581435e03b06c69b673 | D1/D2 correction and bounded journal/replay failure evidence may be considered as candidate donor risk evidence | It is not integrated into PR #156 or PR #175. The deeper EvolutionController compensation failure boundary remains open. PR description reports the exact-head four-workflow pass and 73/73 CTest result; those are candidate-branch results, not whole-Brain capability acceptance. |
| PR #156 — integrated donor candidate | HEAD 7fe212bbb0bd61116ea56581435e03b06c69b673; open/draft/unmerged | Its code and reports remain candidates for later path-specific source review | It is not an approved source baseline and is not recommended for wholesale adoption. External trust, journal integrity and downstream factual-feedback limits remain open. |
| PR #193 — deferred-plan hold | HEAD fa2bd50d6fb0bb77dc3cbaab684f51d606e94bb5; open/draft/unmerged; based on prior PR #175 snapshot 874c732973b6ab303d65a503f5a215b0af8e1153 | Its hold language and continuity record remain authoritative evidence of the existing restraint | It is diverged from current PR #175: 48 commits ahead and 3 behind relative to the current PR #175 head. No history operation or integration is proposed. |
| PR #192 — Documentation Foundation | Exact PR #192 HEAD at this planning refresh beb4d5a174a1dd613878f89132e97b5e6052c7d3; open/non-draft/unmerged | Its exact current gate state defines the documentation/authority constraints | DF-02, DF-06, DF-09 and DF-12 remain open; DF-11 is waived. PR #192's recorded base is stale relative to its current base branch; no retarget or rebase is authorized. |

The source audit and completion matrix are not evidence that a mechanism is fully implemented, integrated or capable. Source presence, a CMake target, an isolated test fixture and a historical green build must not be promoted into a whole-Brain capability claim.

## 3. Planning principles

1. **One coherent Brain, multiple cooperating responsibilities.** Logical mechanisms own distinct semantic state; they are not independent agents with competing identities, beliefs or goals.
2. **Mechanisms before behavior.** Build enabling capabilities and evidence-handling contracts; do not encode desired conclusions as fixed mappings.
3. **Experience is evidence, not an instruction.** Intake does not automatically become interpretation, accepted belief, causal knowledge, preference, affective state or goal.
4. **Authoritative state has one semantic owner.** Shared context, caches, workspace snapshots, evaluators and coordinators are not second writers.
5. **Cognition is recurrent, not a compulsory serial pipeline.** Retrieval, reinterpretation, prediction, attention and correction may branch, recur, proceed concurrently or be interrupted.
6. **Every consequential claim is traceable.** Preserve source, provenance, scope, assumptions, temporal context, version, uncertainty and dependencies.
7. **Proposal is not acceptance.** Proposal, evaluation, authorization where required, owner commit and downstream propagation are distinct lifecycle states.
8. **Learning is cross-mechanism developmental change.** A changed score or parameter is not, by itself, broad cognitive learning.
9. **Cognitive intent does not authorize external action.** Governance, security, tool permission, execution and verified external consequence remain within their authoritative system boundaries.
10. **Degradation is local and explicit.** Missing evidence, stale dependencies, partial writes or unavailable owners must not be converted into success, truth or a completed learning transition.

## 4. Responsibility ownership map

The BM identifiers below follow the current mechanism-specification vocabulary. This is a planning map, not approval of the current PR #174 proposal.

| Mechanism | Semantic responsibility / owner boundary | Primary dependencies | Observable planning target |
|---|---|---|---|
| BM-01 — Experience intake and provenance | Preserve what was acquired, from where, when, under what conditions and with what integrity | External observations / interactions; BM-11 continuity | Experience can be distinguished from interpretation and later derived claims. |
| BM-02 — Representation and interpretation | Construct context-bearing interpretations while preserving alternatives and uncertainty | BM-01, BM-03; BM-06 context | New or ambiguous input can be represented without silently collapsing it into one accepted meaning. |
| BM-03 — Continuity and memory | Own durable experience history, retrieval, consolidation and memory lifecycle | BM-01, BM-11; consuming mechanisms | Relevant history can be retrieved with provenance, context, freshness and applicability limits. |
| BM-04 — Belief and world-state management | Own accepted, disputed, provisional and invalidated claims about the world | BM-01, BM-02, BM-03, BM-12; BM-05 outcomes | Competing claims are retained and revised by evidence-sensitive owner transitions, not arrival order. |
| BM-05 — Association, causal modelling and prediction | Own associations, causal hypotheses, model scope, predictions and resolution | BM-01, BM-03, BM-04, BM-12; verified outcomes | Predictions state assumptions, scope, horizon and resolution conditions; co-occurrence does not become universal causation. |
| BM-06 — Attention and active context | Select and prioritize bounded processing context without taking ownership of underlying state | All active mechanisms; BM-10 | Relevant information is surfaced and stale context is revisited without replacing source-owner state. |
| BM-07 — Affective appraisal and valuation | Own contextual appraisal and valuation signals that can modulate priority and evaluation | BM-02, BM-04, BM-05, BM-06, BM-08, BM-09 | Appraisal is contextual, revisable and non-deterministic; it does not impose fixed stimulus-to-emotion or emotion-to-action rules. |
| BM-08 — Goals, intent, planning and decision | Own candidate/supplied goal lifecycle, plan evaluation and decision proposals | BM-03, BM-04, BM-05, BM-06, BM-07, BM-10, BM-12 | Candidate goals are distinguished from supplied goals; plans expose premises, constraints and staleness. |
| BM-09 — Learning and developmental adaptation | Own learning-candidate formation/evaluation and coordinate owner-approved changes | All affected state owners; BM-11 | Justified experience produces persistent, measurable and appropriately transferable changes, with regression containment. |
| BM-10 — Metacognitive monitoring and control | Monitor confidence, limitations, dependency health and correction effectiveness | All mechanisms; BM-11 | Identified limitations trigger targeted re-evaluation rather than ungrounded self-assertion or state overwrite. |
| BM-11 — Integrated coordination and continuity control | Own work identity, dependency tracking, coordination, checkpoints and recovery validation | All mechanisms | Cross-owner work is tracked through pending/delivered/failed/stale/reconciled states; coordination does not seize semantic authority. |
| BM-12 — General reasoning and inference | Own inference construction, premises, assumptions, alternatives, contradictions and lineage | BM-02, BM-03, BM-04, BM-05, BM-11 | Reasoning materially uses relevant evidence and memory; downstream owners decide whether any conclusion changes their state. |

The external system boundary must remain explicit. A Brain-generated intent or plan does not grant tool permission, policy authority, actuator access, or proof that an external action succeeded.

## 5. Dependency graph and concurrency constraints

The intended dependency graph is not a total serial order.

### 5.1 Foundational dependency clusters

**A. Evidence and continuity spine — BM-01 + BM-03 + BM-11.**  
All later capabilities depend on attributable experience, recoverable memory, stable identity and dependency tracking. These responsibilities may be designed in parallel only after their source/owner and lifecycle contracts are mutually consistent.

**B. Representation and epistemic state — BM-02 + BM-04.**  
Representation distinguishes observation, interpretation and hypothesis. Belief stewardship decides what is accepted, disputed, qualified, invalidated or unknown. Memory must provide evidence with contextual applicability, not just a text match.

**C. Inference and model use — BM-12 + BM-05, integrated with BM-02/BM-03/BM-04.**  
Reasoning requires evidence-bearing premises and memory; causal and predictive work requires explicit assumptions, counterevidence and resolution conditions. Reasoning results are proposals and must be consumed by the proper downstream owner.

**D. Context-sensitive control — BM-06 + BM-07 + BM-10.**  
Attention selects bounded context; appraisal modulates rather than commands; metacognition detects limitations and requests targeted correction. These controls depend on the evidence, belief and prediction states they monitor.

**E. Goal-directed cognition — BM-08.**  
Goal evaluation, intent, planning and decision depend on beliefs, predictions, memory, reasoning, context and appraisal. The boundary between cognitive intent and external authorization remains outside BM-08.

**F. Developmental change — BM-09 coordinated with every affected owner and BM-11.**  
Learning cannot mutate multiple independent state classes as one unowned global write. Candidate evaluation, owner approval, activation, persistence, monitoring and rollback need explicit contracts.

### 5.2 Critical dependency edges

- BM-01 → BM-02 / BM-03 / BM-04 / BM-05 / BM-09.
- BM-03 → BM-02 / BM-04 / BM-05 / BM-07 / BM-08 / BM-12.
- BM-02 → BM-04 / BM-05 / BM-12.
- BM-04 ↔ BM-05; qualified beliefs may support predictions, and attributed outcomes/counterevidence may trigger owner reassessment.
- BM-02 + BM-03 + BM-04 + BM-05 → BM-12; reasoning must consume relevant evidence, memory, interpretation, belief status and scoped hypotheses.
- BM-12 → BM-04 / BM-05 / BM-08 only as a qualified proposal; the receiving owner evaluates and commits its own state.
- BM-06 ↔ all active mechanisms as a bounded context selector, not a universal state owner.
- BM-07 → BM-06 / BM-08 / BM-09 as contextual modulation, not a deterministic command.
- BM-10 → relevant owner mechanism / BM-11 for targeted monitoring, staleness and recovery.
- BM-09 ↔ every affected state owner through explicit candidate and activation protocols.
- BM-11 supports every cluster through dependency tracking, interruption, conflict visibility and recovery.

Parallel work is only valid where state ownership, semantics, dependency versions and integration acceptance scenarios are stable. Number of concurrent workstreams is not a progress metric.

## 6. Proposed integrated capability increments

These increments organize future planning. They are not a start order for coding and do not override the architecture/specification gates.

### Increment 0 — Contract and authority readiness

**Planning purpose:** convert the final accepted architecture and mechanism specification into traceable capability obligations.

**Planning outputs:**
- Exact-revision crosswalk from each mechanism and accepted scenario to an owner, contract, dependency, source area and evidence requirement.
- Resolution of the current PR #173 architecture-review findings and PR #174 current-proposal re-review/Director disposition.
- Reconciled CF-26/CF-27 register and explicit decisions for any reserved architecture questions.
- Explicit distinction between accepted planning baselines, current proposals, source candidates and historical evidence.
- A no-assumption list: all choices that require a later Project Director decision.

**Exit condition:** architecture and specification authority are unambiguous at exact revisions; all unresolved questions that would force engineering guesses are recorded. No source baseline is selected by this increment.

### Increment 1 — Experience, memory and coordination continuity

**Responsibilities:** BM-01, BM-03, BM-11, with contracts for BM-02 and BM-04.

**Capability target:** an acquired experience can be preserved, retrieved with source/context and freshness, connected to dependent work, and recovered after interruption without fabricating derived validity.

**Acceptance evidence to plan:**
- Identity and provenance survive persistence/retrieval.
- Retrieval relevance and truth are distinguished from retrieval success.
- Duplicate delivery/replay has no duplicate semantic effect.
- Dependency changes visibly stale dependent interpretations, predictions and plans.
- Interrupted or partial persistence remains incomplete/unresolved until owner validation.
- Recovery reconciles against current owner versions; it does not promote a workspace snapshot into authoritative state.

### Increment 2 — Representation, belief revision and memory-supported reasoning

**Responsibilities:** BM-02, BM-04, BM-12, integrated with BM-03 and BM-11.

**Capability target:** relevant experience and retrieved memory influence an inference; competing interpretations and claims remain visible; the receiving owner controls whether a conclusion changes accepted state.

**Acceptance evidence to plan:**
- A source observation is distinguishable from representation, hypothesis, belief and conclusion.
- Two plausible interpretations can coexist with scope and uncertainty.
- Relevant retrieved memory changes a later inference and its lineage explains why.
- A contradiction, counterexample or defeated assumption makes affected conclusions stale or qualified.
- BM-04 evaluates candidate claims; BM-12 cannot write belief state directly.
- Unsupported reasoning output cannot silently alter downstream plans or predictions.

### Increment 3 — Association, causal hypotheses and prediction lifecycle

**Responsibilities:** BM-05 with BM-01, BM-03, BM-04, BM-09, BM-11 and BM-12.

**Capability target:** the Brain can form scoped hypotheses and predictions, preserve assumptions and counterevidence, and resolve only when the specified evidence condition is met.

**Acceptance evidence to plan:**
- Association, correlation, temporal order and causal hypotheses remain distinct.
- Every prediction has identity, scope, assumptions, horizon, expected evidence, resolution criteria and attribution.
- Delayed, partial, missing, conflicting or invalid outcomes are represented accurately.
- Failed infrastructure, failed execution and unverified consequences are not treated as external-world facts.
- Prediction error can form a learning candidate but cannot directly change model state.

### Increment 4 — Attention, appraisal and metacognitive regulation

**Responsibilities:** BM-06, BM-07, BM-10, integrated with earlier increments.

**Capability target:** context and priorities adapt to evidence and task demands; affective appraisal modulates evaluation; metacognitive monitoring identifies uncertainty and requests correction.

**Acceptance evidence to plan:**
- Interruptions and competing tasks do not destroy unrelated authoritative state.
- Attention can reopen prior work when new evidence changes its dependencies.
- Appraisal is contextual and revisable; it does not encode stimulus→emotion or emotion→action shortcuts.
- The accepted whole-system SYS ownership boundaries for security, governance, resource and execution state are preserved.
- Metacognitive correction is evaluated for effectiveness and side effects.

### Increment 5 — Experience-grounded goals, intent, planning and decisions

**Responsibilities:** BM-08 with BM-02/03/04/05/06/07/10/12 and external SYS boundaries.

**Capability target:** supplied goals and experience-derived candidate goals are distinguished; plans expose evidence, assumptions, constraints and dependency freshness; cognitive decisions remain separate from execution authorization.

**Acceptance evidence to plan:**
- A candidate goal may be formed from novel evidence without a fixed event-to-goal rule.
- Goal origin, provenance, persistence, conflict and revision are inspectable.
- Competing goals are evaluated against evidence, feasibility, constraints and later outcomes.
- Plans are invalidated or reconsidered when material premises change.
- A plan or intent cannot itself authorize a tool, actuator or external-world action.

### Increment 6 — Cross-mechanism learning and developmental adaptation

**Responsibilities:** BM-09 coordinated with every affected owner and BM-11.

**Capability target:** justified experience causes an owner-approved, persistent internal capability change that affects later behavior appropriately and is contained if harmful.

**Acceptance evidence to plan:**
- Candidate lifecycle is explicit: formation → evidence attribution → risk/eligibility assessment → evaluation → owner approval → activation → persistence → monitoring → containment/rollback.
- Learning is not limited to numeric parameter adjustment; its classes and owners are traceable to the accepted specification.
- One candidate affecting multiple state classes cannot leave a partially activated incoherent Brain.
- Regression, interference and counterexamples are evaluated.
- A changed state survives restart/reconstruction and influences later behavior for the right reason.
- Transfer is demonstrated on a held-out but meaningfully related context; unrelated contexts are checked for negative transfer.

### Increment 7 — Integrated Brain verification and controlled starter-training readiness

**Responsibilities:** all BM mechanisms, coordination and the whole-system governance/execution boundary.

**Capability target:** a verified interacting Brain, not a collection of independently green subsystems.

**Acceptance evidence to plan:**
- Longitudinal multi-experience scenarios show memory, representation, belief, reasoning, prediction, attention, goal evaluation and learning interacting.
- Pre-change and post-change behavior are compared using declared measures and holdout experiences.
- Learned change persists, transfers within justified boundaries and does not conceal regression.
- Restart, delayed outcomes, contradictions, partial failures and recovery are included.
- Training inputs exercise mechanisms without preloading the target knowledge or desired behavior.
- Safety/authorization limits are validated before any controlled external action.
- Final claims disclose limitations and do not infer open-ended autonomy.

## 7. Reusable work-package definition

No implementation ticket should be activated from a mechanism name alone. Each future work package must contain:

1. **Capability outcome:** observable change in what the Brain can reliably do, not a class or file request.
2. **Mechanism ownership:** authoritative owner, participating mechanisms and external SYS dependencies.
3. **Specification trace:** exact accepted specification sections, architecture invariants and acceptance scenarios.
4. **Source evidence:** exact target commit, paths, symbols, call paths, tests and known limits, after a Director-approved baseline exists.
5. **Observed gap:** what the inspected evidence establishes; distinguish a gap in the inspected path from proof of total absence.
6. **State lifecycle:** inputs, outputs, provenance, scope, temporal context, freshness, proposal/commit transition and invalidation behavior.
7. **Dependency contract:** upstream versions, downstream consumers, stale-work handling and cross-owner propagation.
8. **Failure semantics:** partial write, owner unavailability, timeout, duplicate delivery, replay, interrupted rollback and recovery.
9. **Verification plan:** unit, contract, integration, persistence/replay, concurrency, adversarial, regression and longitudinal tests as appropriate.
10. **Learning proof, where claimed:** pre/post behavior, persistence, held-out transfer, regression and rollback/containment.
11. **Non-goals and prohibited shortcuts:** hardcoded stimulus→emotion, event→goal, success→preference or failure→trauma rules; arrival-order winner selection; unqualified confidence; workspace-as-authority; unverified outcome acceptance.
12. **Acceptance decision:** evidence bundle, unresolved findings, reviewer disposition and Project Director acceptance before the next gate.

## 8. Verification portfolio to prepare

| Verification class | What it establishes | Representative challenge |
|---|---|---|
| Unit/invariant | Local semantic and state-transition correctness | Reject stale, malformed, unsupported or contradictory proposals. |
| Contract | Inter-mechanism obligations | Ensure consumers use the correct owner version and preserve epistemic status. |
| Vertical integration | One end-to-end capability increment | Experience → memory retrieval → representation → inference → owner evaluation. |
| Concurrency/conflict | Owner authority under simultaneous work | Concurrent contradictory proposals, stale commits and delivery reordering. |
| Failure/recovery | Integrity under interruption | Lost notifications, duplicate replay, partial persistence, owner outage, failed rollback and restart. |
| Evidence/adversarial | Robustness to misleading evidence | Correlated sources, quoted/untrusted instructions, ambiguous reference, delayed contradiction and source relabeling. |
| Longitudinal learning | Experience-dependent change | Repeated but non-identical episodes with attributable pre/post state and behavioral comparison. |
| Transfer/regression | Appropriate generalization | Held-out related contexts plus unrelated contexts to detect negative transfer or overgeneralization. |
| System-boundary | Cognitive intent versus external authority | A plan cannot bypass permission, governance or verified action-consequence records. |

A green unit-test suite, a source tree containing every BM class, or one successful prediction-feedback loop is insufficient to claim an integrated learning Brain.

## 9. Cross-cutting acceptance invariants

The current PR #173 reviewed architecture defines nine normative invariants for later specification and implementation. This planning supplement preserves them as constraints; it does not select algorithms for satisfying them.

1. **Single semantic authority:** each authoritative state item has exactly one owner.
2. **Owner-atomic transition:** an accepted owner transition commits coherently with identity, version, provenance, scope, epistemic status and dependencies.
3. **No silent winner:** arrival order, timestamp alone, container order, first-match or last-write-wins cannot choose semantic truth.
4. **Proposal/commit separation:** proposal, evaluation, required authorization, owner commit and downstream propagation remain distinct.
5. **Dependency validation:** consumers validate exact source versions and freshness before use and before consequential commit.
6. **Bounded asynchronous propagation:** pending, delivered, failed, stale and reconciled propagation states remain visible.
7. **Partial-failure integrity:** failure cannot fabricate experience, observation, prediction outcome, successful action consequence, learning approval or completed rollback.
8. **Idempotent recovery:** replay and duplicate delivery do not create duplicate semantic effects; partial recovery is never represented as complete.
9. **Locality of degradation:** a local failure invalidates dependent work without corrupting unrelated authoritative state unless evidence establishes wider impact.

## 10. Decisions required before the plan can become operative

| Decision / gate | Required disposition | Current state |
|---|---|---|
| Whole-Brain architecture | Exact-revision independent re-review and Project Director acceptance | PR #173 review is PARTIALLY CLEAR; acceptance open. |
| Mechanism specification | Exact-current-proposal independent re-review and Project Director disposition, including recovered F-02/F-03 obligations | PR #174 remains draft/unmerged; review/disposition open. |
| CF-26 / CF-27 | Complete independent challenge, exact-revision final gate and authority decisions | Open. |
| Documentation Foundation | Complete applicable DF gates and receive exact-revision Director acceptance | PR #192 not accepted; DF-02/06/09/12 open. |
| Gate A source reconciliation | Close all source provenance, API, workflow, D1/D2, failure-ordering and independent-review obligations | PR #175 Gate A NOT CLEARED. |
| Candidate defect work | Verify D1/D2 corrections and remaining compensation boundary, then decide whether/how any affected source is considered | PR #176 open/draft; deeper EvolutionController compensation boundary open. |
| Source baseline selection | Project Director decision after architecture/specification and Gate A evidence is complete | No baseline selected. |
| Work-package activation | Separate explicit authorization, approved scope and accepted prerequisites for each increment | Not authorized. |

No row in this table is closed by this supplement.

## 11. Risks and explicit non-decisions

- **Architecture/specification mismatch:** PR #174's current proposal must be reconciled against PR #173's current architecture before any implementation reliance.
- **Donor overreach:** PR #156 is not a whole-system or specification-complete baseline. The PR #175 recommendation to start from PR #174 and selectively port from PR #156 remains a historical Builder recommendation, not a Director decision.
- **False integration confidence:** a passing candidate build/test suite does not establish integrated Brain capability, external ABI compatibility, production trust configuration or workflow continuity.
- **Mechanism silos:** building twelve independent mechanism modules risks interfaces without cross-mechanism learning; acceptance must be capability- and interaction-based.
- **Premature behavior encoding:** hardcoded target emotions, preferences, goals, causal rules or response choices would violate the governing principle.
- **Authority leakage:** coordination, evaluation, workspace, reasoning or learning must not become a second semantic writer or bypass external system authorization.
- **Stale planning lineage:** PR #193 is not a safe fast-forward of current PR #175. Do not reconcile their histories by assumption.

## 12.1 Capability-to-scenario traceability completed — 2026-11-18

Added `docs/architecture/plans/18_CAPABILITY_TO_ACCEPTANCE_SCENARIO_TRACEABILITY_MATRIX_2026-11-18.md`. It maps every scenario in the current proposed PR #174 specification (54 scenarios, A–K) to primary mechanism owners, the existing integrated planning increments I0–I7, and a minimum evidence class.

This exposes an important version distinction: the original PR #175 plan's reference to 34 scenarios reflects the historically accepted PR #174 baseline at `0811a59e46bf934e32e794f90e4e7d18d4e2bd97`; the current corrected PR #174 proposal at `c34472354e4122fc1d78dc25bf45d81f1eb4dc69` contains 54. The matrix does not silently replace the accepted historical baseline with the unaccepted current proposal. It is explicitly provisional until PR #174 review and Project Director disposition.

The matrix also makes downstream BM-12 owner evaluation (scenarios 41–48), contextual language/intent/commitment lifecycle (35–40, 49–54), dependency invalidation/recovery (23–26, 44–48), and longitudinal learning/transfer/regression (19–22) visible as integrated evidence obligations.

## 12.2 Remaining planning continuation steps



1. Reconcile the accepted/reviewed PR #173 architecture, current PR #174 specification proposal and CF-26/CF-27 obligations into one exact-revision contract crosswalk.
2. Reconcile PR #175 Reports 08–16, current PR #176 correction evidence and the remaining Gate A findings into a single conditional donor-risk register. Do not select the donor or baseline.
3. Map every BM-01–BM-12 responsibility and accepted scenario to the integrated increments in §6, recording owner, dependencies, producer/consumer obligations and evidence.
4. Turn §7–§8 into a capability-to-verification matrix: one row per observable capability, with positive, negative, recovery, persistence, transfer and regression evidence.
5. Present the completed non-operative planning package for Project Director review. Only a separate explicit decision may activate implementation planning or select a source baseline.

---

**Final status:** this supplement is a non-operative planning artifact prepared under a narrow 2026-11-17 Project Director exception. It does not supersede the PR #193 hold, does not start Stage A, does not select a source baseline, and does not authorize implementation, tests, integration or deployment.
