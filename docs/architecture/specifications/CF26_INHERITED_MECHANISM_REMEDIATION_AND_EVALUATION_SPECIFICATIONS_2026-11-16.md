# CF-26 Inherited-Mechanism Remediation and Evaluation Specifications

**Status:** Builder specification package for independent technical challenge; not runtime implementation authorization  
**Target architecture baseline:** PR #173, branch `architecture/brain-foundation-planning-20261103`, starting revision `30e234324b361349c8a88ec35b8ae4b57f062bbe`  
**Governing source baselines:** PR #171 `b05434758ad4fe72815503f89bd5d2990ccb658b`; PR #172 engineering-evidence baseline `1273ddbcd0087d189e01388ded2d362fb1e058d2`; PR #97 donor `c1da222e6c94aeb3f2ad000392c21fe4fc81ab25`  
**Authority:** Project Director's CF-26 Option A decision (2026-11-15) and accepted BFA-C01–BFA-C14 remain controlling. This package does not amend them.

## 1. Purpose, scope and interpretation

This package converts the seven owned CF-26 remediation/evaluation outputs into bounded mechanism specifications. It explains the architectural contracts that any later implementation must satisfy, the evidence required to evaluate compatibility, and the conditions under which a mechanism may be accepted, adapted, replaced or kept deferred.

The specifications are intentionally technology-neutral. They do not select algorithms, data structures, databases, APIs, transports, model providers, execution topology or code decomposition. They do not authorize runtime source changes, builds, tests, benchmarks, migration, Stage A, merge or deployment.

The 209-path census is a scoped file/blob inventory, not proof that every function is correct. Test-source references describe intended assertions only. Every later implementation claim must be supported by execution evidence from the exact implementation revision and an independently reviewable evaluation package.

**Non-negotiable developmental rule:** engineer mechanisms and evidence discipline; do not preload beliefs, goal preferences, emotional meanings, strategy choices, source trust, or desired behavioural outcomes. Parameters may begin as bounded engineering constraints only when their operational purpose, scope, provenance, owner, uncertainty and revision conditions are explicit. A fixed coefficient does not become learned merely because it is configurable.

## 2. Shared specification contract

All seven specifications inherit the following requirements:

1. **Authoritative ownership:** the responsibility named in the architecture owns the semantic state and its lifecycle. A coordinator may manage dependencies and delivery but cannot rewrite another owner's conclusions.
2. **Proposal/commit separation:** candidate changes remain proposals until the responsible owner validates the evidence and performs an authorized coherent state transition. Governance approval is separate from cognitive acceptance and execution.
3. **Evidence lineage:** retain source, derivation, version, time, context, uncertainty, epistemic class, dependencies, evaluator and decision rationale. Summaries and derived values must remain traceable to source evidence.
4. **Temporal and contextual scope:** no confidence, reliability, appraisal, prediction or learned relation is silently generalized beyond its demonstrated domain, task, time window or context.
5. **Contradiction and ambiguity:** preserve competing claims and unresolved candidates. Do not force a winner because of insertion order, a first-match shortcut, a missing value or a deadline.
6. **Persistence and recovery:** accepted changes must survive the declared persistence/reconstruction boundary with version lineage. Partial recovery remains explicitly partial; missing evidence is not fabricated.
7. **Failure and rollback:** rejected, failed, stale or reversed changes remain inspectable. Dependent work is invalidated through Coordination; each state owner repairs its own authoritative state.
8. **Developmental integrity:** experience can propose change but does not guarantee it. A single success, failure, prediction error or reward-like signal cannot prescribe a cognitive update.
9. **Evaluation independence:** the author/activator of a material candidate cannot be its sole evaluator. Claims remain unverified when independent evaluation is unavailable.
10. **Scope discipline:** any proposal changing accepted cognitive authority, foundational scope, mandatory subsystem status, security/governance boundary or high-impact learning authority returns to the Project Director before adoption.

A later implementation specification must identify concrete owners, dependencies, state transitions, failure modes and observable evidence without weakening these invariants.

### 2.1 Specification-by-specification contract coverage

The shared requirements above are normative for every specification; they are not optional package-level aspirations. The following map identifies where each specification applies them and where its local failure/recovery contract is stated.

| Specification | Semantic owner and state boundary | Proposal/commit and provenance | Failure/recovery and invalidation | Independent evaluation |
|---|---|---|---|---|
| 1 — Belief/claim revision | §3.2 | §§3.2–3.3; claim identity, epistemic status, evidence lineage and owner commit | §3.4; preserve prior version, unresolved alternatives and dependent invalidation | §3.5; independent evaluator under shared rule 9 |
| 2 — Goal/intent/context | §4.2 | §§4.2–4.3; candidate versus selected intent and exact context identity | §4.4; stale candidate, unavailable evidence and unresolved selection | §4.5; independent evaluator under shared rule 9 |
| 3 — Evidence/numeric governance | §5.2–5.3 | §5.3; parameter owner, register version, provenance and scoped decision consequence | §5.5; retain uncalibrated status, reject stale/invalid register updates and restore prior version | §§5.4–5.5; independent calibration/evaluation required |
| 4 — Affective appraisal | §6.2 | §§6.2–6.3; appraisal owner, contextual evidence and candidate parameter change | §6.5; retain prior appraisal/parameter state and invalidate dependent appraisals/plans | §§6.4–6.5; independent contextual calibration and regression evaluation |
| 5 — Prediction-context resolution | §7.2–7.3 | §7.3; candidate outcome versus owner-accepted prediction resolution | §7.5; preserve unresolved status and re-evaluate stale/ambiguous candidates | §§7.4–7.5; independent matching and replay evaluation |
| 6 — Action/developmental-world evidence | §8.2–8.3 | §§8.2–8.3; proposal, authorization, execution, observation and consequence remain distinct | §8.5; unavailable/partial evidence remains unresolved and replay cannot invent outcomes | §§8.4–8.5; independent evidence-boundary and leakage evaluation |
| 7 — Learning/evolution integration | §§9.2–9.3 | §§9.3–9.4; candidate proposal, owner commit and external high-impact approval | §9.5; rollback, invalidation and owner-local recovery | §9.6; evaluator independent of candidate author/activator |

A specification does not satisfy a row merely by naming a responsibility: the cited sections and the shared contract together define the normative boundary. If an independent evaluator, required source evidence or recovery dependency is unavailable, the result remains unverified/deferred rather than being inferred from author review.

---

## 2.2 Donor-conflict disposition, owner and acceptance-test crosswalk

This crosswalk is normative for the seven specifications. It explicitly binds the inherited conflicts identified in the PR #97 donor audit to a replacement contract, accountable semantic owner and objective acceptance test. A disposition applies to semantics, not wholesale retirement or approval of a source file.

| Donor behaviour or risk | Disposition and replacement contract | Accountable semantic owner | Required acceptance test |
|---|---|---|---|
| Caller-supplied reliability metadata is clamped/averaged into source reliability | ADAPT; caller metadata remains an attributed input claim, not independent calibration. Separate source competence from item-level evidence reliability and measurement quality | Evidence-reliability/parameter-register owner (Spec 3) | Vary caller-supplied values while holding independent outcomes fixed; calibrated source competence must not change solely because metadata changed. Unknown and correlated sources remain explicitly qualified |
| Operational thresholds and fixed learning-rate parameters | ADAPT; register each parameter with semantic purpose, owner, domain, units, provenance, calibration, uncertainty, sensitivity, expiry and rollback | Parameter-register owner (Spec 3); Learning/adaptation for candidate parameter changes | Test out-of-domain, stale, missing and adversarial values; no universal confidence threshold; no parameter may be called learned unless an experience-dependent, evaluated update changes it |
| General first-eligible goal selection | REPLACE; eligibility filters candidates but does not rank or select them; compare evidence-qualified alternatives and permit unresolved/no-intent | Goal/intent-selection owner (Spec 2) | Permute candidate/container order and add an eligible but inferior candidate; selected intent must not change solely because of order or first-match position |
| Strategy context chosen independently from selected intent | REPLACE; context binds to exact selected-intent, candidate and evidence versions | Goal/intent-selection owner (Spec 2), with Planning consumer | Deliberately mismatch selected intent and context source; reject activation and invalidate context when intent/evidence version changes |
| Belief map and action-status semantic overwrite | REPLACE; versioned claims, preserved alternatives, explicit supersession/withdrawal and dependency invalidation | Belief stewardship owner (Spec 1) | Concurrent conflicting updates, out-of-order delivery and replay must preserve prior versions; stale proposals cannot overwrite current state; unresolved conflict remains unresolved |
| Fixed affective weights/transforms | ADAPT; provisional engineered parameters only, no preloaded emotional conclusions or universal valence | Affective appraisal owner (Spec 4), independent calibration evaluator | Hold stimulus constant across differing goals/context/internal conditions and include mixed/ambivalent cases; appraisal must remain revisable and cannot be prescribed by a fixed stimulus mapping |
| Execution status used as outcome evidence; developmental-world leakage risk | ADAPT; separate proposal, authorization, execution, observation and verified consequence; keep hidden world/evaluator state outside Brain evidence | Governance/action executor, observation owner and developmental-world owner (Spec 6) | Simulate accepted-but-not-executed, partial execution, no observation, delayed observation and hidden-state leakage; no missing consequence is synthesized |
| Learning-rate/evolution mechanisms treated as broad learning or allowed to self-activate | ADAPT; candidate/evaluation/activation/rollback remain separate, with each state owner committing its own state | Learning/adaptation owner and affected semantic state owners (Spec 7) | Candidate improves one metric but regresses unrelated capability; reject/narrow/rollback. High-impact candidate without governance approval remains inactive |

**Cross-spec acceptance:** run the seven specifications as one integrated evidence contract, not as seven independent green checkmarks. At minimum, demonstrate a source observation whose provenance and uncertainty survive interpretation, memory and reasoning; a belief revision that invalidates a dependent prediction; a goal-selection change that is not caused by list order; an action whose execution acknowledgement is not mistaken for world consequence; a learning candidate whose activation is independently evaluated and owner-committed; and rollback that reconciles dependent state. Include delayed, contradictory, duplicated, unavailable and partially recovered evidence.

These are planning-level acceptance contracts. They do not claim runtime remediation, test execution or independent clearance. CF-26 remains OPEN until the independent reviewer challenges this exact crosswalk, the full seven-specification package, the 209-path inventory and the 14 mechanism dispositions; any reserved decision remains with the Project Director.

## 3. Specification 1 — Versioned belief and claim revision

### 3.1 Problem and disposition

The donor's authoritative belief map overwrites an existing value before recording dispute, and action-status beliefs can be replaced without a complete versioned claim history. The WorldModel retains some conflicting facts but is not a complete claim ledger. This semantic last-write-wins behaviour is incompatible with the accepted epistemic lifecycle.

**Disposition:** replace semantic overwrite with owner-governed, versioned claim revision. Preserve the event journal and raw evidence history separately.

### 3.2 Ownership and state contract

- **Semantic owner:** Belief stewardship owns accepted belief state, claim status and revision history.
- **Evidence owners:** Memory/knowledge and interpretation/grounding retain their own source records and candidate interpretations.
- **Coordination:** owns dependency invalidation and stale-work propagation; it does not resolve claim meaning.
- **Continuity/state stewardship:** validates canonical epistemic class, lineage, version and recovery semantics.
- **Governance:** retains authority over access, privacy and any external action; a belief never grants permission.

A claim record must preserve at least: stable claim identity; proposition/content; subject and relation; source and derivation references; epistemic class/status; temporal validity and context/domain; confidence/uncertainty with its meaning; supporting and contradicting evidence; owner; current version; supersession/withdrawal relation; decision rationale; and dependencies known to consume the claim.

### 3.3 Lifecycle

A new observation or inference creates a candidate claim, not an automatic overwrite. Belief stewardship evaluates whether the evidence supports a new claim, qualifies an existing claim, narrows its scope, preserves a competing alternative, supersedes a prior version, suspends it, withdraws it, or leaves the matter unresolved. The previous version and its evidence remain inspectable.

A claim may be treated as current only within its declared scope and validity. A newer timestamp alone does not establish greater reliability. Independent corroboration, source dependence, context mismatch, delayed evidence and contradictory observations must be considered explicitly. If resolution is not justified, retain alternatives and abstain from a singular conclusion.

Concurrent proposals must be reconciled against the current owner-state version before commit. A stale proposal is re-evaluated; it is not silently rebased onto a newer claim. A commit is coherent with its version and lineage. Cross-owner propagation may be asynchronous under the architecture's versioned invalidation contract.

### 3.4 Failure and recovery

- Duplicate evidence delivery must not create duplicate semantic effects.
- Missing or corrupt history produces an explicit recovery gap, not a reconstructed fact.
- A failed commit leaves the prior authoritative version intact.
- A rollback or withdrawal publishes affected dependencies and reason; Coordination propagates invalidation, and consumers revalidate before consequential commits.
- If the owner cannot determine whether a claim is current, dependent conclusions remain stale or unresolved.

### 3.5 Objective evaluation

The later evaluation must include: contradictory evidence; delayed and out-of-order evidence; independent versus correlated sources; same claim under different temporal/context scopes; concurrent writers; duplicate replay; restart/reconstruction; partial journal loss; supersession; withdrawal; rollback; and a dependent prediction/plan consuming a now-stale claim.

**Acceptance criteria:** no prior claim or contradictory evidence is silently erased; every accepted revision has a complete lineage and explicit scope; stale proposals cannot overwrite newer owner state; dependent work becomes visibly stale and is reconciled; replay is idempotent; uncertainty and unresolved alternatives survive persistence/recovery.

**Reject the mechanism** if any tested path loses a prior claim, silently resolves contradiction by arrival order, or lets stale dependent work commit as current.

---

## 4. Specification 2 — Goal/intent selection and context identity

### 4.1 Problem and disposition

The donor uses first-eligible selection as a fallback and can bind strategy context to an eligible item independently of the selected intent. Eligibility is a filter, not a ranking, justification or preference.

**Disposition:** preserve goal/intent state and lifecycle; replace first-eligible general selection and independent strategy-context coupling. A narrowly bounded emergency default is an external operational policy, not a learned goal.

### 4.2 Ownership and state contract

- **Goal/valuation/planning responsibility:** owns candidate goals, their origin, constraints, status, priority rationale, dependencies and lifecycle.
- **Decision responsibility:** owns the selected intention/decision and its commitment record.
- **Attention/workspace:** owns active task-scoped references, not goal truth.
- **Coordination:** owns work/dependency scheduling and stale-work notices.
- **Governance/action path:** alone authorizes and executes external actions.

Each candidate must preserve origin (supplied, inferred, or self-formed), motivating evidence, context, constraints, feasibility assumptions, uncertainty, risk, expected consequences, conflicts, dependencies, and status. The selected intent must have a stable identity and explicit links to the exact candidate and evidence versions used.

### 4.3 Candidate evaluation and selection

The mechanism first constructs a relevant candidate set and records why candidates were included or excluded. Eligibility checks may remove candidates only for explicit constraints; they do not determine preference. Remaining candidates are compared using evidence-qualified and context-scoped considerations such as relevance, feasibility, constraints, dependencies, uncertainty, risk and expected consequences. The specification must not prescribe a universal fixed ranking or encode preferred goals.

Selection may yield a chosen intent, an unresolved comparison, a request for evidence/clarification, deferral, suspension or no-intent. Tie-breaking must not depend on container order or first-match position. If an operational fallback is required, its external policy owner, trigger, scope, bounded consequence, label and expiry must be explicit; it must never be represented as a self-formed or learned preference.

The active strategy context must reference the selected intent's identity and exact candidate/evidence versions. It cannot be selected independently from a different eligible goal. Any change in selected intent or source evidence invalidates dependent context and plans.

### 4.4 Failure and recovery

When candidates are stale, mutually incompatible, infeasible or insufficiently evidenced, the mechanism preserves alternatives and returns unresolved/no-intent rather than forcing selection. On interruption or restart, it reconstructs the selected intent only from its persisted identity and lineage; otherwise it marks the commitment unresolved. A fallback cannot bypass governance or authorize action.

### 4.5 Objective evaluation

Evaluate candidate-order permutations; equal and near-equal candidates; conflicting goals; stale and newly disconfirmed evidence; no eligible candidates; budget exhaustion; missing context; interrupted selection; restart; a selected goal whose supporting claim is withdrawn; and operational fallback activation/expiry.

**Acceptance criteria:** identical evidence and constraints produce order-invariant candidate consideration; selected context always points to the selected intent; unresolved/no-intent is representable; no fixed preference is introduced; stale dependencies invalidate context before consequential use; fallback use is separately governed and visibly labelled.

**Reject the mechanism** if insertion order determines a cognitive preference, if context silently binds to a different candidate, or if a fallback is reported as acquired motivation.

---

## 5. Specification 3 — Evidence reliability and numeric parameter governance

### 5.1 Problem and disposition

The inspected production path averages caller-supplied reliability metadata; the correctness-scoring method was not found wired into the inspected production feedback path. The codebase also contains distinct operational thresholds and a fixed weighted learning-rate equation with a 0.05–0.95 clamp. These values are not calibrated source trust or acquired learning dynamics merely because they are numeric/configurable.

**Disposition:** adapt reliability and parameter handling into scoped, evidence-qualified, versioned measurements and operational controls.

### 5.2 Separate the quantities

The later mechanism must not conflate:
- **Source competence/reliability:** historical performance of a source for a declared task/domain and time range.
- **Evidence quality:** properties of this particular observation or record, including integrity, completeness, provenance and measurement uncertainty.
- **Claim confidence:** support for a proposition given the available evidence and assumptions.
- **Decision threshold:** an operational boundary for a named decision, with explicit error costs and authority.
- **Learning parameter:** a value controlling candidate adaptation, with a declared objective and evaluation domain.

A source's historical reliability must not be copied onto every item it emits. Caller-supplied metadata is an input claim, not independent validation. Unknown sources remain unknown; missing values are not converted to neutral or trusted values without an explicit, justified policy.

### 5.3 Parameter register and governance

Every retained numeric parameter must have: stable identity; purpose; responsible owner; semantic category; scope/domain/task; units and valid range; initialization provenance and rationale; version; calibration/evaluation evidence; uncertainty; decision consequences; error costs; sensitivity; drift/review trigger; and rollback path.

A threshold may be used only for a named operational decision such as abstention, escalation or resource control. It must not silently turn a hypothesis into fact, rank unrelated goals, prescribe affective meaning or authorize an action. Distinct thresholds retain distinct meanings; no universal confidence cutoff is inferred.

The audited learning-rate equation and clamp remain provisional engineered parameters. Their use requires comparison against alternatives or bounded baselines, sensitivity analysis, learning stability, adaptation speed, negative transfer, task/context transfer, unrelated-capability regression and rollback evidence. They must not be described as learned dynamics unless a separate experience-dependent adaptation process changes them under the learning lifecycle.

### 5.4 Objective evaluation

Evaluate independent outcome scoring versus caller metadata; source-domain mismatch; sparse samples and uncertainty; correlated sources; drift; unknown/new sources; adversarial or malformed metadata; threshold perturbation; false-positive/false-negative costs; parameter sensitivity; held-out task transfer; and rollback/replay.

**Acceptance criteria:** source competence, evidence quality and claim confidence remain distinct; all values are scoped/versioned/owned; no parameter is treated as calibrated without independent evidence; thresholds have named consequences and authority; learning-rate claims are limited to demonstrated sensitivity/transfer results.

**Reject the mechanism** if caller metadata alone becomes trusted source truth, if an unscoped numeric threshold establishes belief/action authority, or if a fixed schedule is presented as experience-acquired learning.

### 5.5 Failure, recovery and independent calibration decision

The parameter-register owner rejects an update if its identity, scope, units, provenance, version, objective or decision consequence is missing or inconsistent. Missing calibration evidence leaves the parameter explicitly UNCALIBRATED; it is not replaced by a neutral/trusted default. If evidence is stale, correlated beyond the declared assumptions, unavailable or outside the registered domain, the affected measurement remains unknown or provisional and dependent decisions must not consume it as calibrated. A failed parameter update leaves the prior accepted version intact; rollback restores that version and publishes its dependencies for invalidation/re-evaluation. Replay must not count the same evidence twice.

The semantic owner of the affected parameter makes the technical calibration-status decision only after an independent evaluator has assessed the declared calibration, sensitivity, transfer, drift and regression evidence. There is no universal numeric calibration threshold. A parameter remains provisional when the evidence does not meet its own predeclared objective and error-cost criteria. Any high-impact activation additionally requires the separate SYS-11 approval contract in architecture §21.1.1; that approval does not certify calibration.

---

## 6. Specification 4 — Affective appraisal semantics and calibration

### 6.1 Problem and disposition

Affective state/appraisal is a foundational responsibility, but inherited initial weights, integration/decay coefficients and transforms are engineered parameters. They must not smuggle fixed emotional meanings, valence assignments or stimulus-to-appraisal conclusions into bootstrap behaviour.

**Disposition:** preserve the capacity for contextual appraisal and candidate parameter adaptation; adapt all inherited values as provisional, uncalibrated engineering conditions until evidence supports a scoped use.

### 6.2 Ownership and semantic boundary

- **Affective appraisal responsibility:** owns appraisal state, its contextual interpretation, evidence lineage and candidate calibration changes.
- **Goal/valuation/planning:** owns goals and decision priorities; it may consume appraisal but may not convert it into a fixed response rule.
- **Memory/learning:** retains episodes and evaluates candidate changes.
- **Coordination:** propagates stale dependencies when an appraisal parameter or source claim is revised.
- **Governance:** owns permissions and safety policy; affect does not grant action authority.

An appraisal record must identify the evaluated information, relevant goal/context/internal-condition versions, uncertainty, provenance, parameter versions, alternative appraisals, and whether the output is provisional, accepted or unresolved. Appraisal is not an external fact, diagnosis, permission or mandatory action.

### 6.3 Developmental acquisition contract

Bootstrap may provide representational capacity, numerical stability bounds, provenance handling and evaluation procedures. It must not preload a fixed catalogue of emotional meanings or universal valence for stimuli/events. Any inherited weight or transform begins as an explicitly provisional engineered parameter with a declared initialization rationale and limited scope.

Experience may generate a candidate appraisal-parameter change, but no prediction error, success, failure, reward-like signal or single outcome directly dictates the change. A candidate must identify the experiences and contexts supporting it, the alternatives considered, expected scope, uncertainty and dependencies. Evaluation must include relevant variation, held-out contexts, counterexamples, mixed/ambivalent cases, unrelated-capability regression and calibration against observed outcomes. A candidate may be rejected, deferred, narrowed or reversed.

The mechanism must distinguish internal operational/homeostatic evidence from cognitive affective meaning. SYS-05 may provide evidence about internal conditions; it does not prescribe goals or affective interpretation. SYS-06 remains optional/unresolved and is not a prerequisite.

### 6.4 Objective evaluation

Evaluate new contexts, repeated contexts, contradictory outcomes, mixed significance, missing internal-condition signals, noisy signals, delayed consequences, parameter perturbation, persistence/replay, restart, rollback and downstream effects on attention, memory, learning eligibility and goal comparison. Include counterexamples that would expose hidden fixed mappings.

**Acceptance criteria:** every appraisal is context/provenance-qualified; no fixed stimulus-to-emotion or emotion-to-action rule is required; inherited parameters are labelled provisional until calibrated; changes are experience-supported, independently evaluated, versioned and reversible; dependent appraisals/plans become stale after rollback.

**Reject the mechanism** if fixed weights are treated as universal emotional meaning, if one outcome directly prescribes appraisal, or if appraisal silently grants permission or determines action.

### 6.5 Failure, recovery and independent calibration decision

If relevant goal, context, internal-condition or source evidence is missing, stale, withdrawn or inaccessible, the appraisal is marked incomplete/uncertain and must not be filled by a fixed emotional interpretation. A failed or rejected candidate calibration leaves the prior accepted parameter version and appraisal lineage intact. If rollback or recalibration changes a parameter, dependent appraisals, priorities and plans are marked stale through Coordination and re-evaluated before consequential reuse. Replay must preserve the original evidence and must not apply one experience twice.

The affective appraisal owner decides whether its parameter is technically calibrated only against the predeclared objective and the contextual, held-out, counterexample and regression evidence in §§6.3–6.4, with independent evaluation separate from candidate authorship/activation. No universal numeric threshold is imposed. Insufficient or unavailable evaluation leaves the parameter provisional. SYS-11 approval is additionally required only for high-impact activation; it does not replace technical calibration.

---

## 7. Specification 5 — Prediction-context candidate resolution

### 7.1 Problem and disposition

The inspected contextual matching path can take `matches.front()` when multiple candidates exist. Candidate order is not evidence and cannot determine semantic identity or prediction outcome.

**Disposition:** preserve prediction identity and explicit outcome resolution; adapt context matching to explicit candidate evaluation, ambiguity preservation and dependency-aware resolution.

### 7.2 Ownership and state contract

- **Prediction responsibility:** owns prediction identity, assumptions, horizon, expected outcome, confidence/uncertainty, context and lifecycle.
- **Memory/knowledge:** owns retained episode and evidence lineage.
- **Interpretation/grounding:** owns candidate event/entity interpretations.
- **Coordination:** owns cross-responsibility dependency freshness and stale-work propagation.

A prediction must retain stable identity, source context, creation time, expected event/outcome, temporal horizon, assumptions, dependencies, and status (active, unresolved, matched, partially matched, contradicted, expired or withdrawn). A candidate outcome must retain its own identity, source, event/processing time, scope and evidence quality.

### 7.3 Matching and resolution

Candidate generation may use contextual similarity as a retrieval aid, not as proof. Every candidate must be checked against prediction identity, temporal horizon, context, assumptions, event semantics and source independence. If multiple candidates remain plausible, preserve ambiguity or request more evidence. No first-match, list-order or nearest-score-only rule may silently resolve a prediction.

Delayed and out-of-order observations remain eligible only when their event-time and scope satisfy the prediction contract. A single observation cannot resolve multiple predictions unless the relationship is explicitly supported. Partial matches remain partial; missing outcomes remain unresolved or expire only under an explicit owner-governed rule. Prediction error is computed only after a suitably matched, verified outcome is accepted.

### 7.4 Objective evaluation

Evaluate reordered candidate lists; multiple equally plausible matches; no match; partial match; duplicate observations; one observation competing for multiple predictions; delayed/out-of-order outcomes; time-window boundaries; changed assumptions; stale dependencies; restart/replay; and contradictory later evidence.

**Acceptance criteria:** candidate ordering does not change semantic resolution; ambiguity remains representable; outcome matching respects event time, scope and identity; duplicate delivery is idempotent; prediction error is generated only from accepted matched outcomes; revisions invalidate dependent learning/decisions.

**Reject the mechanism** if `front()`, insertion order or similarity alone resolves a prediction without sufficient evidence.

### 7.5 Failure, recovery and independent resolution evaluation

If a candidate outcome, source record or required dependency is unavailable, corrupt, stale or withdrawn, the prediction remains unresolved/partially matched; the mechanism must not substitute the nearest remaining candidate or infer a negative outcome. Concurrent candidate resolutions are evaluated against the current prediction-owner version; a stale proposal is re-evaluated, not silently rebased. A failed resolution leaves the prior prediction version and candidate evidence intact. Duplicate delivery/replay is idempotent, and a later contradictory outcome reopens the resolution only through the prediction owner's versioned lifecycle.

The prediction owner alone commits resolution status. An independent evaluator assesses candidate-order invariance, event-time/context matching, ambiguity preservation and replay/rollback behaviour. If independent evaluation is unavailable, resolution may remain operationally provisional but cannot be claimed as verified capability.

---

## 8. Specification 6 — Action and developmental-world evidence contracts

### 8.1 Problem and disposition

The donor contains separate request, execution and outcome concepts, which should be preserved. However, fixed execution-status reliability values and the developmental environment's observation boundary need explicit evidence semantics. A failed execution is not a negative environmental consequence; a simulated world transition is not real-world evidence.

**Disposition:** preserve request/execution/outcome separation and the controlled developmental substrate; adapt evidence provenance, status reliability and observation boundaries.

### 8.2 Ownership and state contract

- **Brain decision/planning:** owns cognitive intention and action proposal, not authorization or execution.
- **Governance/action path:** owns authorization, policy checks, operational validation and execution.
- **Developmental world:** owns simulated task state and transition results.
- **Brain:** receives only the observations and execution/outcome evidence explicitly exposed through the environment contract.
- **Learning/adaptation:** may form candidate learning from verified evidence but cannot relabel execution failure as world consequence.
- **SYS-07 / designated policy owners:** retain security and access enforcement.

Each action episode must distinguish: proposal identity; authorizing authority and decision; executor identity; execution attempt/status; operational failure reason; observed world/environment transition; observation provenance; and later verified consequence. Acknowledgement that an action was accepted or bytes were persisted is not proof that the intended external state change occurred.

### 8.3 Evidence boundary

Execution statuses such as success, rejection, timeout or failure describe the execution path only. They must not be converted into positive/negative environmental outcomes without independent observation. Any inherited reliability values (including 0.75/0.25/0.0) are provisional engineering parameters, not calibrated truth. Their objective, owner, scope and consequences must be specified and evaluated before use.

For developmental trials, the world owns hidden task state and transition logic. The Brain receives observations under an explicit partial-observation boundary. Hidden world state, simulator code, seeded future events or evaluator labels must not leak into Brain evidence. Each episode records environment/version, seed or reproducibility identity, initial conditions, action proposals, authorization/execution evidence, observations, exogenous changes and termination reason. Simulated outcomes are labelled as simulated and cannot silently become real-world episodes or claims.

### 8.4 Objective evaluation

Evaluate denied actions; executor timeout/crash; partial execution; successful execution without verified consequence; unexpected consequence; delayed observation; contradictory observation; hidden-state leakage; partial-observation variants; seed/replay reproducibility; exogenous changes; reset/restart; and a failed action followed by later world observation.

**Acceptance criteria:** proposal, authorization, execution and verified consequence remain separate; failure evidence updates only the execution path unless an independently observed consequence supports more; simulator-only evidence remains labelled and isolated; provenance/replay are complete; no action or learning activation bypasses governance.

**Reject the mechanism** if execution status is treated as world outcome, simulator internals leak as observations, or simulated experience is represented as real-world evidence.

### 8.5 Failure, recovery and independent evidence evaluation

An action proposal is a cognitive candidate only; authorization and execution remain owned by the governance/action path. Missing authorization, execution acknowledgement, observation or verified consequence must retain its distinct unknown/denied/failed/unobserved status. If the executor, observer or developmental world is unavailable, the episode records the gap and does not synthesize a world consequence. Partial execution and rollback retain their own operational evidence. A later observation may be associated only after identity, event time, context and provenance are revalidated.

The action/world evidence owners preserve the original episode and versions; Learning/adaptation may propose downstream changes only from the evidence actually verified. A failed evidence commit leaves the prior owner state intact; replay is idempotent and simulated records remain labelled/isolated. An evaluator independent of the action author, executor and candidate-learning activator checks authorization separation, observation leakage, outcome provenance and recovery/replay. If the independent evidence path is unavailable, the consequence remains unverified.

---

## 9. Specification 7 — Learning/evolution integration, eligibility and rollback

### 9.1 Problem and disposition

Learning is distributed across memory, representation, beliefs, prediction, valuation/affect, attention, goals, strategy, action consequences and self-model. It cannot be reduced to one parameter updater or a single subsystem. Evolution/parameter experimentation is useful engineering infrastructure but is not equivalent to broad cognitive learning.

**Disposition:** preserve bounded candidate evaluation, canary/rollback and lineage mechanisms; adapt them to a cross-responsibility learning contract and accepted governance boundaries.

### 9.2 Ownership and authority

- **Learning/adaptation:** owns candidate registration, evidence/dependency capture, impact classification, eligibility/risk assessment, evaluation record, activation proposal, accepted adaptation lineage, monitoring and correction/rollback decision.
- **Each state owner:** alone commits changes to its own authoritative state.
- **Coordination:** owns cross-responsibility dependency graph, stale-work propagation, cancellation/suspension/resumption and reconciliation records.
- **Governance / Project Director:** approves changes within reserved high-impact authority; Learning cannot self-authorize.
- **Independent evaluator:** evaluates material learning claims without owning candidate implementation/activation. The Independent Reviewer challenges evidence sufficiency.

### 9.3 Candidate and impact contract

A learning candidate must identify target state/capability, source experiences, prediction/outcome evidence, context, assumptions, affected owners/consumers, dependencies, expected scope, uncertainty, reversibility, possible interference, evaluation plan and rollback plan. Candidate formation is not acceptance.

Learning/adaptation performs and records initial impact classification before evaluation or activation. It considers identity/continuity, epistemic integrity, goal/valuation policy, safety, governance/security, propagation breadth, persistence, reversibility, external consequences and unrelated capabilities. A candidate that could materially alter foundational identity, epistemic classes/transitions, broad world/goal policy, safety-relevant behaviour or governance boundaries is high-impact. Ambiguous cases are treated as high-impact until the governance authority resolves classification.

Eligibility requires evidence quality, sufficient context, owner availability, current dependencies, reversibility/containment, evaluation capacity and authority. A prediction error, reward-like signal, success, failure or repeated exposure does not by itself qualify a candidate. The candidate may be rejected, deferred, narrowed, isolated or sent for more evidence.

### 9.4 Evaluation, activation and integration

Evaluation compares a declared baseline with the candidate across original context, relevant variation, held-out related cases, counterexamples, persistence/reconstruction, transfer and unrelated-capability regression. It records uncertainty and limitations. A candidate that improves one target while degrading an unrelated capability is not accepted as an unqualified improvement.

Activation is a separate decision from evaluation. Only the state owner may commit its own state, and only under an explicit delegation or policy. High-impact activation requires external governance approval. If approval is unavailable, ambiguous or denied, the candidate remains inactive. Evolution experiments may rank parameter candidates within their approved sandbox, but cannot change cognitive authority or turn parameter optimization into claims of general intelligence.

### 9.5 Rollback and dependency recovery

Learning/adaptation owns the decision and evidence record for rejecting, reversing, isolating or superseding a candidate, including exact prior/replacement versions and rationale. It publishes the rollback event and known affected dependencies. Coordination propagates invalidation, marks dependent work stale, notifies consumers, suspends unsafe work and records delivery failures. Each dependent state owner validates and repairs its own authoritative state. Recovery is incomplete while a material dependency remains unreconciled or unavailable; a local parameter rollback alone is not system recovery.

### 9.6 Objective evaluation

Evaluate false-positive eligibility; ambiguous impact classification; low-quality/correlated evidence; cross-owner candidates; high-impact approval absent/denied; concurrent candidates; partial activation; interrupted activation; delayed evidence; unrelated-capability regression; negative transfer; persistence/reconstruction; rollback with active dependent plans/predictions; Coordination unavailable during rollback; notification loss; and recovery after restart.

**Acceptance criteria:** learning remains a cross-responsibility process; every candidate has evidence, scope, dependencies and risk classification; activation is distinct from evaluation; high-impact changes cannot self-authorize; every accepted change is versioned/persisted/monitored; rollback invalidates dependencies and is not declared complete until reconciliation; transfer and regression claims are bounded to independent evidence.

**Reject the mechanism** if any single outcome prescribes a change, if a high-impact candidate activates without governance, if a local rollback leaves dependent state silently current, or if parameter optimization is reported as general cognitive learning.

---

## 10. Cross-specification integration and dependency order

These specifications are not seven isolated components. Their shared contracts must be reconciled in a single end-to-end evaluation. **The numbered trace below is an illustrative evidence path, not a mandatory cognitive pipeline or execution order.**

### 10.1 Cross-specification dependency and integration contracts

The following are semantic dependencies and invalidation relationships, not a required execution order or serial pipeline. Coordination owns the cross-responsibility dependency/work graph under architecture §18.2; each semantic owner publishes its own version transitions and remains authoritative for its state.

| Upstream evidence/state | Consuming specification/responsibility | Required contract |
|---|---|---|
| Retained episodes and retrieved summaries | Reasoning premises; Specs 1 and 5 where relevant | Memory/knowledge supplies provenance-bearing candidates; Reasoning records exact retrieved identities/versions and selection rationale; retrieval does not automatically promote a memory to fact |
| Versioned claims and conflict status (Spec 1) | Prediction assumptions/resolution (Spec 5); learning candidates (Spec 7) | Prediction and Learning record claim-version dependencies; claim revision/withdrawal invalidates affected predictions and candidates |
| Source/evidence reliability and parameter register (Spec 3) | Affective calibration (Spec 4), action evidence qualification (Spec 6), learning eligibility (Spec 7) | Consumers preserve quantity semantics and scope; provisional values remain distinguishable from calibrated measurements |
| Goal/intent identity and context (Spec 2) | Affective appraisal (Spec 4), action proposal (Spec 6), learning impact analysis (Spec 7) | Each consumer records the exact selected goal/context version; a changed selection does not rewrite prior evidence |
| Verified action/world observations (Spec 6) | Claim revision (Spec 1), prediction resolution (Spec 5), learning (Spec 7) | Execution status alone is not environmental consequence; only owner-accepted, provenance-bearing observations may inform downstream candidates |
| Accepted adaptation and rollback (Spec 7) | Every affected state owner | Learning records the candidate and rollback; Coordination propagates invalidation; each affected owner validates and repairs its own state |

A dependency becoming stale does not impose a global stop on unrelated cognition. Only work that consumes the affected version is invalidated or suspended. No cross-spec dependency grants one owner permission to commit another owner's semantic state. The architecture remains recurrent, branching, concurrent and interruptible: responsibilities may repeat, be skipped when irrelevant, operate in parallel, or be reopened when new evidence or invalidation arrives.

1. A source observation enters through the acquisition boundary with provenance and uncertainty.
2. Interpretation/grounding creates candidate representations without promoting them automatically to fact.
3. Memory retains the episode and derivation lineage.
4. Belief stewardship accepts, qualifies or preserves competing claims.
5. Prediction forms a scoped expectation with explicit assumptions and dependencies.
6. A suitably matched verified outcome may produce prediction error; unmatched outcomes remain unresolved.
7. Affective appraisal and goal/intent mechanisms may consume the evidence but cannot use fixed mappings to prescribe meaning or behaviour.
8. Learning/adaptation may form a candidate spanning several state owners, classify its impact, evaluate it and request required authority.
9. Each owner commits only its own authorized state; Coordination propagates version/invalidation status.
10. Rollback or delayed contradictory evidence invalidates dependent claims, appraisals, predictions, plans and candidate learning as applicable.
11. Persistence/reconstruction restores versioned state and marks any unreconciled dependency stale or unavailable.

**End-to-end acceptance:** a varied, held-out episode must demonstrate that source evidence can alter later behaviour only through traceable candidate formation, evaluation and owner-authorized commit; a contradictory or delayed outcome must preserve alternatives and invalidate affected dependent work; rollback must restore coherent owner state and dependency status; no fixed stimulus-to-emotion, failure-to-trauma, success-to-reward, error-to-update or first-eligible-goal mapping may substitute for evidence.

## 11. Required evidence package and closure gates

For each of the seven specifications, the implementation-stage evidence package must include:

- exact implementation revision and source/blob manifest;
- requirement-to-owner-to-state-transition traceability;
- baseline and candidate behaviour;
- positive, negative, ambiguous, delayed and adversarial cases;
- persistence, replay, restart and partial-recovery evidence;
- relevant context variation and held-out evaluation;
- counterexamples and failure injection;
- dependency invalidation, rollback and reconciliation evidence;
- unrelated-capability regression results;
- independent evaluation report and explicit limitations;
- Project Director disposition for any reserved change.

**CF-26 specification status:** the seven architecture-level specifications are now defined in this package. They are not implementation, runtime verification or independent acceptance. CF-26 remains subject to independent challenge of this package and the exact PR #173 revision. Runtime tests and implementation remain separately unauthorized.

## 12. Explicit non-authorization

Nothing in this package authorizes:
- runtime source changes, code migration or refactoring;
- build, runtime test, benchmark or training execution;
- algorithm, schema, API, database, framework, model-provider or deployment selection;
- Stage A or any other implementation phase;
- merge, draft exit, deployment or branch-history rewriting.

Any such work requires its own explicit Project Director authorization.
