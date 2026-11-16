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

---

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

These specifications are not seven isolated components. Their shared contracts must be reconciled in a single end-to-end evaluation. **The numbered trace below is an illustrative evidence path, not a mandatory cognitive pipeline or execution order.** The architecture remains recurrent, branching, concurrent and interruptible: responsibilities may repeat, be skipped when irrelevant, operate in parallel, or be reopened when new evidence or invalidation arrives.

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
