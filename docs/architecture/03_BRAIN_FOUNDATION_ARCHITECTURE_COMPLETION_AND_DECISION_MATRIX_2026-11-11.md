# Brain Foundation Architecture — Completion and Decision Matrix

**Date:** 2026-11-11  
**Status:** Completion work product for Project Director review; not yet independently cleared or finally accepted  
**Parent proposal:** PR #173, exact starting HEAD `97191111bc2573c14d391c0af9628db7b11f194b`  
**Governing principle:** **ENGINEER THE MECHANISMS; LET BEHAVIOR BE ACQUIRED THROUGH EXPERIENCE.**

## 1. Controlling disposition

The Project Director's earlier acceptance of PR #173 as sufficient is superseded. PR #173 remains retained as the architectural starting point and evidence source; it is not accepted as the complete or final Brain Foundation Architecture.

This matrix does not authorize implementation, runtime changes, testing, technology selection, merge or deployment. Its purpose is to close architecture-level gaps, make proposed foundational decisions explicit, and provide a traceable completion and independent-review contract.

The target is a complete foundational architecture: every foundational responsibility, authority, state class, interaction, developmental obligation, failure boundary and verification obligation must be defined at the conceptual architecture level. Algorithm internals, concrete schemas, APIs, protocols, code structure, technology and deployment choices remain later specifications—but only after their architectural obligations and decision owners are defined here.

## 2. Completion standard

A foundational element is complete only when all applicable questions have explicit answers:

1. **Purpose:** what responsibility exists and what outcome it serves.
2. **Authority:** which responsibility owns the authoritative state and which may only propose, consume or challenge it.
3. **Inputs:** what evidence, state or requests it may use, with provenance and epistemic status preserved.
4. **Outputs:** what it may produce and what those outputs do not imply.
5. **Interactions:** which responsibilities it depends on, informs, invalidates or coordinates with.
6. **Development:** what must be available at bootstrap and what must be acquired or improved through experience.
7. **Failure:** how uncertainty, partial failure, stale state, contradiction and recovery are handled.
8. **Verification:** what observable evidence demonstrates the capability and what counterevidence falsifies the claim.
9. **Traceability:** which approved baseline, requirement or Project Director decision justifies it.

A topic is not complete merely because it is named, listed as a future capability, or described as an unresolved question.

## 3. Existing proposal coverage and closure matrix

| ID | Foundational domain | PR #173 coverage | Remaining closure required | Completion obligation |
|---|---|---|---|---|
| CF-01 | Cognitive identity and continuity | Partial | Define identity invariants, version lineage, interruption and reconstruction semantics | Identity continuity must survive restart without converting missing state into invented knowledge |
| CF-02 | Experience acquisition boundary | Partial | Define trust and evidence boundary between SYS-03 acquisition/preprocessing and Brain interpretation | Acquisition output remains evidence/proposal, not an automatically accepted cognitive fact |
| CF-03 | Representation and grounding | Partial | Define candidate representation lifecycle, entity/event identity hypotheses, ambiguity and cross-modal reconciliation | Competing interpretations remain available until evidence justifies resolution |
| CF-04 | Memory and episodic retention | Partial | Distinguish raw episode, transformed representation, summary, semantic knowledge and retrieval result | Summaries never silently replace source evidence; retrieval can be traced to retained lineage |
| CF-05 | Belief and knowledge stewardship | Partial | Define belief lifecycle, contradiction handling, confidence semantics, scope and withdrawal | Beliefs remain revisable, qualified and linked to supporting/contradicting evidence |
| CF-06 | Attention and working context | Partial | Define activation, prioritization, capacity pressure, interruption, suspension and resumption | Active context is bounded, freshness-aware and never authoritative over source state |
| CF-07 | Prediction and outcome resolution | Partial | Define prediction lifecycle, horizons, assumptions, delayed/out-of-order outcome matching and unresolved status | Prediction error is computed only against a suitably matched, verified outcome |
| CF-08 | Reasoning and inference | Partial | Define inference classes, evidence/assumption separation, memory use, explanation lineage and stopping/abstention | Reasoning conclusions identify their evidential basis and uncertainty; fluent text is not proof |
| CF-09 | Simulation and imagination | Partial | Define hypothetical-state isolation and transition to evidence only through observation | Simulated content cannot contaminate memory or belief as observed history |
| CF-10 | Learning and adaptation | Partial | Define learning classes, eligibility, candidate evaluation, activation, consolidation, interference and rollback | Every material adaptation has evidence lineage, scope, evaluation and recovery semantics |
| CF-11 | Goals and motivation | Partial | Define supplied, inferred and candidate goals; goal competition, persistence, revision and abandonment | Goal formation is experience-responsive without bootstrap objectives prescribing desired behaviour |
| CF-12 | Affective appraisal | Partial | Define minimum appraisal dimensions, contextual dependence and routes of influence | Affect informs appraisal and allocation without fixed emotion/action mappings or fact authority |
| CF-13 | Planning and decision | Partial | Define alternatives, constraints, feasibility, commitment, revision and distinction from action | Plans and decisions remain cognitive products, not authorization or execution evidence |
| CF-14 | Metacognition and self-model | Partial | Define monitored properties, limits of self-estimation, corrective requests and outcome evaluation | Monitoring can initiate bounded correction but cannot become a second unrestricted cognitive authority |
| CF-15 | Coordination and concurrency | Partial | Define dependency, ownership conflict, cancellation, interruption, partial completion and stale work | Concurrent responsibilities coordinate without a mandatory serial pipeline or silent state overwrite |
| CF-16 | Language and symbolic cognition | Partial | Define language as one representational/interaction modality, not the Brain's whole cognition | Language output remains grounded in available evidence and does not substitute for non-linguistic state |
| CF-17 | Social and agent modelling | Deferred | Define minimum foundational representation and explicitly scope mature social cognition as advanced | Architecture permits later development without assuming human-like social motives or fixed persona |
| CF-18 | Action intention and feedback | Partial | Define proposal lifecycle, denial, execution evidence, verified outcome and learning feedback | Brain cannot authorize itself; denial is not execution; request is not outcome |
| CF-19 | Internal condition and homeostasis | Partial | Define distinction between cognitive significance/appraisal and SYS-05 operational regulation | Operational state can inform cognition but does not silently set goals, beliefs or emotional meaning |
| CF-20 | SYS-06 modulation boundary | Partial | Keep unresolved optional responsibility with explicit non-dependency and governance conditions | Foundational Brain functions when SYS-06 is absent; no implicit mandatory subsystem |
| CF-21 | SYS-08 substrate and SYS-01 state authority | Partial | Define persistence acknowledgement, failure reporting, reconstruction and semantic validation | Storage/runtime success is not cognitive truth; SYS-01 validates recovered cognitive state |
| CF-22 | Security, privacy and governance | Partial | Define data access, authorization, provenance, retention and action-governance boundaries at conceptual level | Cognitive capability never bypasses system governance or security authority |
| CF-23 | Developmental stages | Partial | Define bootstrap, early learning, capability growth and mature/advanced scope without age-based assumptions | Stages describe capability evidence, not hardcoded personality or a fixed timetable |
| CF-24 | Failure and degraded operation | Partial | Define responsibility-local failure, uncertainty escalation, recovery and safe suspension | Partial failure is visible and contained; it does not silently corrupt unrelated cognition |
| CF-25 | Verification and evidence | Partial | Map every capability to positive, negative, transfer, persistence and regression evidence | No capability claim without repeatable evidence and explicit limits |
| CF-26 | Existing mechanism disposition | Open | Require later source-level compatibility review against approved architecture | Existing code is candidate evidence/material, not an architectural constraint or automatic discard |
| CF-27 | Architecture decision governance | Open | Separate settled foundational decisions from implementation decisions and reserved Project Director approvals | No hidden decisions migrate into implementation specifications |

## 4. Integrated responsibility and authority model

The following is the required conceptual responsibility model. It is a model of ownership and interaction, not a prescribed process topology or one-module-per-responsibility design.

| Responsibility | Authoritative state it owns | May consume | May propose or emit | Must not do |
|---|---|---|---|---|
| Continuity/state stewardship | Cognitive identity, lifecycle and state lineage | All versioned state summaries and recovery evidence | Validated continuity snapshots and recovery status | Invent missing cognitive history or reinterpret infrastructure failure as experience |
| Experience interpretation/grounding | Candidate interpretations and grounded referent hypotheses | Qualified observations, context, memory, beliefs | Candidate entities, events, relations, interpretations and uncertainty | Rewrite source observations or silently collapse competing hypotheses |
| Memory/knowledge stewardship | Episodes, retained evidence references, memory organization and knowledge lineage | Observations, interpretations, outcomes, learning changes | Retrieval sets, summaries, associations and candidate knowledge updates | Promote generated summaries or simulations to observed facts |
| Belief stewardship | Current qualified beliefs and their revision history | Evidence, memory, inference, prediction outcomes | Belief proposals, confidence/qualification changes, withdrawal and contradiction notices | Erase contradiction or claim certainty unsupported by evidence |
| Attention/working context | Active selection and task-scoped context state | Goals, relevance signals, uncertainty, deadlines, evidence availability | Activation, prioritization, suspension and resumption decisions | Become long-term truth storage or overwrite source owners |
| Prediction/modeling | Predictions, assumptions, scope and resolution state | Beliefs, representations, context, prior outcomes | Predictions, expected outcomes, mismatch and unresolved status | Treat unverified outcomes or late arrival as confirmed prediction error |
| Reasoning/inference | Inference artifacts and derivation lineage | Evidence, memory, beliefs, models, active context | Conclusions, alternatives, explanations, requests for more evidence | Present assumptions as observations or use fluent explanation as evidence |
| Goals/valuation/affect | Goal candidates, valuation/appraisal state and their lineage | Experience, constraints, internal conditions, outcomes, predictions | Candidate goals, appraisals, priorities and alternatives | Encode fixed stimulus-to-emotion, emotion-to-action or desired-goal mappings |
| Planning/decision | Plans, decision records and commitment state | Goals, constraints, beliefs, predictions, valuations | Plan candidates, decisions, defer/ask/stop recommendations and action proposals | Grant permissions or claim an action was executed |
| Learning/adaptation | Learning candidates, accepted adaptations and developmental lineage | Evidence, prediction errors, outcomes, evaluation results | Candidate state changes, consolidation proposals and regression alerts | Treat every error as a learning instruction or update unrelated state without evidence |
| Metacognitive control | Monitoring state, capability estimates and corrective-work records | Signals from all responsibilities | Bounded reconsideration, evidence requests, suspension and strategy-change requests | Become a second global source of truth or bypass governance |
| Coordination | Work scheduling, dependency and conflict-resolution records | Work requests and state-version metadata | Dispatch, arbitration, cancellation, resumption and stale-work notices | Own other responsibilities' semantic state or silently decide their conclusions |

Authority is semantic, not a claim that each row must be a separate process, service, model or code package. Implementation may combine responsibilities if ownership, observability, isolation and correction remain explicit.

## 5. Cognitive information and state lifecycle

### 5.1 Required epistemic classes

The architecture must preserve at least these distinct classes:

1. **Acquired observation:** received sensory, device, human-reported or system-provided evidence, retaining source and acquisition context.
2. **Perceptual/interpretive hypothesis:** candidate meaning assigned to observations.
3. **Episode:** retained record of an experience and its provenance.
4. **Memory summary:** derived compression or reconstruction of one or more episodes, linked to source lineage.
5. **Belief:** a qualified claim currently accepted within a stated scope.
6. **Prediction:** a claim about an expected future or not-yet-resolved state.
7. **Simulation/hypothesis:** an internally generated possible state or explanation.
8. **Goal:** a represented desired state or condition, with origin and constraints.
9. **Plan:** a candidate organized course of action.
10. **Intention/decision:** a selected or committed cognitive direction.
11. **Action proposal/request:** a request to the authorized external action path.
12. **Execution evidence:** evidence that an authorized execution process did or did not perform an operation.
13. **Verified outcome:** evidence about the resulting state, distinct from execution acknowledgement.
14. **Learning candidate/adaptation:** proposed or accepted change to cognitive state or capability.
15. **Metacognitive assessment:** an estimate or finding about cognition itself, with evidence and limits.

No class silently converts into another. Conversion requires an explicit operation, source lineage, context and status.

### 5.2 Lifecycle rules

- New evidence is retained with its original source, event time and receipt time where available.
- Interpretation produces hypotheses; insufficient evidence preserves alternatives or an unknown status.
- Retrieval may reactivate episodes or summaries but does not rewrite the underlying historical record.
- Belief formation and revision require evidence qualification, scope and lineage.
- Prediction remains unresolved until a suitable outcome is matched or the prediction is explicitly expired/cancelled under a defined rule.
- Simulation remains hypothetical unless independently corroborated by acquired evidence.
- Goal formation records origin: supplied, derived from explicit instruction, or internally proposed from experience and current conditions.
- A plan may be revised without rewriting the goal or evidence that motivated it.
- Intention may produce an action proposal, but authorization belongs to governance.
- Execution evidence and verified outcomes are returned as separate evidence classes.
- Learning may be proposed from experience, but candidate evaluation precedes activation where the change is material or risky.
- Any material state change preserves prior version and dependencies so that affected downstream state can be re-evaluated.

### 5.3 Conflict and uncertainty rules

- Contradiction is represented, not erased by last-write-wins.
- Source reliability, signal quality, ambiguity, missing context, model uncertainty and disagreement remain distinguishable.
- Confidence is attached to a proposition and scope; it is not a universal quality score.
- Time-sensitive claims retain validity intervals where relevant.
- Unknown, unresolved, unavailable and false are distinct states.
- When evidence is insufficient, the architecture permits abstention, clarification, more observation or deferral.

## 6. Integrated cognitive interaction model

The Brain operates as a recurrent, branching and concurrent system. The following interaction pattern is illustrative of causal responsibilities, not a mandatory serial pipeline:

1. Qualified experience becomes available from the acquisition boundary.
2. Interpretation/grounding forms candidate representations while retaining source evidence and alternatives.
3. Memory may retain the episode and retrieve related experience.
4. Belief stewardship evaluates whether evidence supports, contradicts or qualifies current claims.
5. Attention activates information relevant to current tasks, goals, uncertainty and resource limits.
6. Reasoning may request further memory, interpretation, prediction, simulation or external evidence.
7. Prediction/modeling forms expectations and tracks their resolution.
8. Goal/valuation/affective appraisal evaluates significance in context; it can influence attention, encoding, retrieval, learning eligibility and decision comparison.
9. Planning evaluates feasible alternatives against goals, constraints, beliefs, risks and predicted consequences.
10. Decision formation selects, defers, asks, suspends or proposes an action.
11. Governance and the authorized action path independently authorize, validate and execute or deny the proposal.
12. Execution evidence and verified outcomes return as new evidence.
13. Prediction comparison and learning evaluate what should change, if anything.
14. Metacognition monitors the quality and limits of the process and can initiate bounded correction.
15. Coordination tracks dependencies, stale work, interruption and resumption throughout.

Any step may be skipped, repeated, run concurrently, interrupted or reopened. The architecture does not require every experience to cause a durable update. It requires every durable update to have a defensible evidential basis.

### 6.1 Required interaction contracts

Every cross-responsibility exchange must conceptually identify:
- producing owner and consuming responsibility;
- item identity, version and epistemic class;
- source and derivation lineage;
- context and temporal scope;
- uncertainty and known limitations;
- whether the item is provisional, accepted, stale, superseded or withdrawn;
- dependencies and invalidation conditions;
- whether the exchange is informational, a proposal, a request or an authoritative state transition.

Concrete message schemas and transport are implementation specifications, but omission of these semantics is not permitted.

## 7. Foundational mechanisms versus acquired capability

### 7.1 Bootstrap mechanisms that must exist

The initial Brain must have enough enabling structure to:
- preserve identity and state lineage;
- represent source-bearing observations and uncertainty;
- maintain distinct epistemic classes;
- retain and retrieve basic episodes;
- maintain qualified, revisable beliefs;
- establish bounded active context and task continuity;
- form bounded predictions and resolve them against outcomes;
- perform foundational evidence-aware inference;
- represent supplied goals and constraints;
- perform minimum context-sensitive affective appraisal;
- represent plans, decisions and action proposals distinctly;
- evaluate material learning candidates before activation;
- preserve dependencies, detect stale state and recover from partial failure;
- monitor uncertainty and request bounded correction;
- interoperate with governance, action, acquisition and substrate responsibilities without absorbing their authority.

These are enabling mechanisms and integrity invariants, not a preloaded body of desired knowledge or behaviour.

### 7.2 Capabilities that must be acquired or improved through experience

The Brain must develop, rather than receive as fixed conclusions:
- semantic and cross-modal grounding quality;
- entity/event continuity and abstraction;
- retrieval relevance, association and consolidation;
- belief calibration and world knowledge;
- predictive accuracy and useful causal models;
- reasoning strategies and transfer;
- learned attention and relevance allocation;
- candidate-goal formation, priorities and preferences;
- nuanced affective appraisal and modulation;
- planning competence and consequence modelling;
- skill and procedural capability;
- self-model accuracy and metacognitive strategy selection.

No developmental phase is defined by an assumed personality, emotional catalogue, fixed motivation, preferred strategy or predetermined conclusion.

## 8. Closure decisions for the 14 unresolved questions in PR #173

These are recommended architecture-level dispositions to remove avoidable ambiguity. They do not select algorithms, concrete schemas or technology.

| PR #173 question | Recommended closure | Rationale / later specification boundary |
|---|---|---|
| Q1. Atomic vs asynchronous transitions | Require atomicity for each authoritative owner-state commit and its lineage; allow asynchronous cross-owner propagation with versioning, dependency tracking, idempotency and explicit pending/stale status | Prevents partial corruption without imposing global synchronous cognition; transaction mechanism remains later |
| Q2. Active workspace semantics | Treat workspace as bounded, task-scoped, freshness-aware activation of references and derived working items; source owners remain authoritative | Avoids duplicate universal state; capacity and eviction policies are later mechanism details |
| Q3. Epistemic and uncertainty distinctions | Adopt the 15 conceptual classes in §5.1 as the minimum taxonomy; permit typed extensions without collapsing classes | Provides enough distinction for memory, prediction, simulation, action and learning |
| Q4. Essential reasoning forms | Foundation requires evidence-based deduction, induction with qualification, abduction/hypothesis generation, constraint reasoning and comparative evaluation; causal/analogical/counterfactual depth is staged but architecturally supported | Defines capability families without choosing algorithms |
| Q5. Conflicting beliefs | Preserve multiple scoped claims and evidence; evaluate source, temporal validity, context and independence; resolve only when criteria support it; otherwise retain conflict/abstain | Avoids global scalar ranking or silent overwrite; scoring method is later |
| Q6. Safe online learning | Allow low-risk reversible candidates only under explicit eligibility and monitoring; require stronger controlled evaluation for identity, core epistemic, goal/valuation, safety-relevant or broad model changes; governance approval where system policy requires | Separates learning opportunity from permission to mutate high-impact state; exact risk tiers and algorithms are later |
| Q7. Minimum self-model | Maintain evidence-qualified estimates of capability, uncertainty, resource limits, current commitments, known failure patterns and recent correction effectiveness; track provenance and calibration error | Useful for metacognition without a second cognitive authority |
| Q8. Minimum affective appraisal | Appraise goal relevance, valence/significance, urgency, risk, uncertainty and relevant internal condition as contextual, revisable signals; preserve dimensions separately and permit unknown/ambivalent states | Foundational appraisal without fixed emotion labels or stimulus-response mappings |
| Q9. SYS-06 justification | SYS-06 remains optional and unresolved. Brain must function without it. Any future proposal must define distinct value beyond Brain-owned appraisal and SYS-05 regulation, plus authority, failure, observability and governance boundaries | Avoids assuming a subsystem because an analogy suggests it |
| Q10. Experience-acquired goals | Candidate goals may arise from discrepancies, opportunities, needs, outcomes, observed constraints or learned models; origin and evidence are retained; goals are evaluated for feasibility, conflict, risk and consequences; no trigger directly mandates a goal | Makes internally proposed goals possible without a hardcoded objective generator |
| Q11. Transfer/generalization evidence | Require original-context improvement, relevant variation, held-out related context, counterexamples, unrelated-capability regression checks and persistence/reconstruction checks; claims are bounded to tested scope | Prevents fixture memorization from being called general learning |
| Q12. Minimum Brain contract before full embodiment | Brain can operate on supplied observations, records, goals and verified outcomes; missing modalities remain unavailable/unknown; it can reason, learn and request evidence within those limits; no simulated embodiment is treated as real | Allows staged integration without false sensor/action claims |
| Q13. Preserve/adapt/replace existing mechanisms | No blanket retain or discard decision. Perform later source-level compatibility assessment per mechanism against ownership, evidence, developmental, integration and verification criteria; record keep/adapt/replace with tests/evidence | Existing implementation is evidence and candidate material, not architecture authority |
| Q14. Decisions requiring Project Director approval | PD approval required for changes to cognitive authority, foundational scope, safety/governance boundary, mandatory subsystem status, bootstrap-acquired boundary, high-impact learning authority, and any deviation from governing principle; routine mechanism details remain delegated to approved specs | Keeps strategic authority explicit without routing every engineering choice to PD |

## 9. Goal, valuation and affective architecture closure

### 9.1 Goal categories

The Brain must distinguish:
- **supplied goal:** provided by an authorized external source or user;
- **derived goal:** logically or operationally derived from an explicitly supplied goal and its constraints;
- **candidate self-formed goal:** proposed by the Brain from experience, learned models, discrepancies or internal conditions;
- **active goal:** currently selected for consideration or pursuit;
- **suspended/abandoned/completed goal:** lifecycle statuses with reason and evidence.

A candidate self-formed goal is not automatically legitimate, safe, feasible or authorized. It must be evaluated, and any external action remains subject to governance.

### 9.2 Goal competition and persistence

Goals may conflict, become infeasible, lose relevance or be superseded. The architecture must preserve:
- goal origin and motivating evidence;
- constraints and dependencies;
- priority rationale and uncertainty;
- affected commitments and downstream plans;
- reasons for revision, suspension or abandonment.

Priority is contextual and revisable. No fixed rank ordering is prescribed for all situations.

### 9.3 Minimum affective appraisal

Affective appraisal is a cognitive responsibility that evaluates the significance of information in context. It may influence attention, memory encoding/retrieval, learning eligibility, goal priority and alternative evaluation. It does not establish external facts, create permission or dictate action.

The minimum foundation need not begin with a named human-like emotion catalogue. It must support differentiated, contextual and revisable appraisal, including uncertainty and mixed significance. SYS-05 operational/homeostatic signals may be inputs, but SYS-05 does not own cognitive meaning. SYS-06 remains optional and unresolved.

## 10. Learning architecture closure

Learning is a coordinated change process across memory, beliefs, representations, predictions, reasoning, attention, goals, valuation, affect and skills.

### 10.1 Required learning lifecycle

1. **Experience registration:** preserve source, context, temporal information and epistemic status.
2. **Learning opportunity detection:** identify a possible discrepancy, regularity, outcome or capability limitation without assuming it warrants change.
3. **Candidate formation:** specify the proposed target state, scope, supporting evidence, assumptions and dependencies.
4. **Risk and eligibility assessment:** consider reversibility, impact, evidence quality, interference, safety and authority.
5. **Evaluation:** compare against prior behaviour, relevant variation, counterexamples and unaffected capabilities.
6. **Activation decision:** accept, reject, defer or request further evidence; high-impact changes follow their required approval path.
7. **Consolidation/persistence:** preserve accepted change and lineage.
8. **Post-change monitoring:** assess durability, transfer and regression.
9. **Correction/recovery:** qualify, reverse, isolate or supersede an adverse change while preserving history.

### 10.2 Learning classes

The architecture distinguishes, at minimum:
- episodic retention and retrieval learning;
- semantic/relational knowledge learning;
- belief calibration and revision;
- predictive/model learning;
- reasoning-strategy learning;
- attention/relevance learning;
- goal and valuation learning;
- affective appraisal calibration;
- procedural/skill learning;
- self-model/metacognitive learning.

These classes may share infrastructure but must not be assumed equivalent or governed by one undifferentiated update rule.

### 10.3 Learning evidence

A claimed durable learning event must show:
- what changed and where;
- which evidence caused or supported the change;
- baseline and post-change behaviour;
- original-context performance;
- transfer and counterexample performance where applicable;
- regression checks on unrelated capabilities;
- persistence across reconstruction where relevant;
- uncertainty and limits of the claim.

A prediction error, reward signal, failure or success alone is not sufficient proof that a particular belief, emotion, goal or strategy should change.

## 11. Failure, recovery and degraded cognition

| Failure condition | Required Brain response | Forbidden interpretation |
|---|---|---|
| Missing or corrupt memory segment | Mark unavailable, preserve gap and recover from validated lineage where possible | Invent episode content or treat missing record as evidence that event did not occur |
| Conflicting observations | Retain alternatives and seek discriminating evidence or abstain | Last-write-wins truth |
| Stale belief-dependent plan | Mark dependency stale and reconsider before relying on it | Continue as if old assumptions remain current |
| Prediction outcome unavailable | Keep unresolved or expire under explicit rule | Count as success or failure by default |
| Learning candidate regression | Contain, reject, reverse or supersede with lineage | Hide regression or erase developmental history |
| Workspace pressure | Deprioritize/suspend with recoverable references and commitments | Silently discard authoritative state |
| Coordination responsibility unavailable | Continue independent safe work or suspend dependent work with visible status | Pretend all work completed |
| SYS-08 substrate outage | Record operational failure; recover through substrate; SYS-01 validates restored cognitive state | Treat outage as external-world event, memory absence or prediction error |
| SYS-06 absent | Continue within foundational capability and known limits | Assume mandatory modulation exists |
| Governance denies action | Preserve denial as governance outcome and reconsider plan | Treat request as executed or denial as world-state change |
| Metacognitive estimate wrong | Retain estimate lineage and recalibrate against observed performance | Grant self-estimate unquestioned authority |

## 12. Verification architecture and traceability requirements

Every foundational capability must have a verification record with:
- capability statement and owner;
- preconditions and input evidence;
- expected observable behaviour;
- prohibited/negative behaviour;
- evidence and lineage requirements;
- persistence/reconstruction requirements;
- variation/transfer scope;
- counterexamples and boundary cases;
- regression surface;
- known limitations and claim scope.

### 12.1 Required verification classes

1. **Responsibility tests:** owner performs its defined role without crossing authority.
2. **Interaction tests:** cross-responsibility exchange preserves epistemic class, provenance, version and dependency.
3. **Lifecycle tests:** provisional-to-accepted, stale, superseded, withdrawn and recovered transitions behave correctly.
4. **Contradiction tests:** competing evidence remains visible and resolution is justified.
5. **Failure-injection tests:** partial failure, unavailable dependencies and substrate recovery do not corrupt unrelated state.
6. **Longitudinal learning tests:** a change persists and alters later behaviour for evidence-supported reasons.
7. **Transfer tests:** learning applies in relevant varied/novel contexts without unsupported overgeneralization.
8. **Regression tests:** unrelated capabilities and counterexamples remain protected.
9. **Governance tests:** action proposals cannot bypass authorization and execution/outcome distinctions.
10. **Developmental tests:** bootstrap contains enabling mechanisms but not prescribed learned beliefs, goals, preferences, emotions or strategies.

### 12.2 Capability claims

Claims must be bounded to the tested capability, environment, data, variation and time horizon. Passing a narrow fixture is not evidence of broad intelligence, generalized grounding, autonomous motivation or human-like affect.

## 13. Developmental capability progression

This is a capability progression, not a calendar, personality model or claim that every capability develops linearly.

| Developmental level | Required capability evidence | What must not be assumed |
|---|---|---|
| Foundation-ready | Identity, evidence discipline, memory, qualified beliefs, bounded context, basic prediction/inference, supplied-goal processing, minimum appraisal, controlled learning candidates, governance boundaries | Mature autonomy, broad knowledge or sophisticated emotion |
| Integrated learner | Memory informs reasoning; belief changes invalidate dependencies; predictions resolve against outcomes; learning changes persist with evidence | General transfer from one success |
| Adaptive learner | Candidate changes improve varied relevant cases while protecting unrelated capabilities; goal/attention/strategy changes are traceable | Fixed motivation or guaranteed improvement |
| Advanced cognitive development | Stronger abstraction, causal/analogical/counterfactual reasoning, robust grounding, complex skill and social modelling, calibrated metacognition | Human equivalence or unbounded self-direction |

Progression requires evidence for each capability; no level is reached by code volume or subsystem count.

## 14. Advanced and deferred specifications

The following details are intentionally assigned to later mechanism specifications. Each must be specified before implementation of the corresponding capability, and each specification must trace back to this architecture:

- representation and grounding mechanisms;
- episodic, semantic and procedural memory mechanisms;
- retrieval, association and consolidation;
- belief representation, confidence calibration and conflict resolution;
- attention allocation and workspace scheduling;
- prediction, causal modelling and outcome matching;
- reasoning mechanisms and simulation;
- candidate-goal generation and goal competition;
- affective appraisal and modulation mechanisms;
- planning, decision and commitment mechanisms;
- learning eligibility, evaluation, consolidation and rollback;
- metacognitive monitoring and self-model calibration;
- concurrency, dependency and coordination mechanisms;
- persistence, reconstruction and recovery;
- governance/action contracts and verified outcome ingestion;
- verification harnesses and developmental evaluation.

A later specification may choose algorithms and concrete data structures, but it may not redefine ownership, epistemic semantics, developmental constraints or governance boundaries without an explicit architecture change and Project Director approval.

## 15. Decision register proposed for Project Director disposition

| Decision ID | Recommended foundational decision | Required PD disposition |
|---|---|---|
| BFA-C01 | One coherent cognitive authority with distinct state-owning responsibilities | Accept / reject / revise |
| BFA-C02 | Hybrid coordination: owner-managed authoritative state plus bounded task-scoped active context | Accept / reject / revise |
| BFA-C03 | Explicit epistemic classes and provenance-preserving lifecycle | Accept / reject / revise |
| BFA-C04 | Recurrent, branching and concurrent cognition | Accept / reject / revise |
| BFA-C05 | Foundational evidence-aware reasoning including deduction, qualified induction, abduction, constraint reasoning and comparison | Accept / reject / revise |
| BFA-C06 | Distributed learning lifecycle with risk-sensitive evaluation, transfer and regression protection | Accept / reject / revise |
| BFA-C07 | Experience-acquired candidate-goal formation; no predetermined learned objectives | Accept / reject / revise |
| BFA-C08 | Foundational contextual affective appraisal; advanced affective sophistication acquired | Accept / reject / revise |
| BFA-C09 | Bounded metacognitive correction and evidence-qualified self-model | Accept / reject / revise |
| BFA-C10 | Strict separation of cognitive intention, governance authorization, execution and verified outcome | Accept / reject / revise |
| BFA-C11 | SYS-06 optional/unresolved; Brain remains capable without it | Accept / reject / revise |
| BFA-C12 | SYS-08 substrate responsibility; SYS-01 semantic cognitive-state ownership and recovery validation | Accept / reject / revise |
| BFA-C13 | Atomic owner-state commits with asynchronous, versioned cross-owner propagation | Accept / reject / revise |
| BFA-C14 | Capability evidence requires persistence, variation, transfer and regression scope | Accept / reject / revise |

These are proposed decisions for the Project Director, not silently approved decisions. Any rejected or revised decision must have its rationale and downstream architectural impact recorded.

## 16. Traceability to existing approved planning baselines

This completion work must be checked against:
- PR #171 whole-system architecture and responsibility map, exact reviewed package HEAD `b05434758ad4fe72815503f89bd5d2990ccb658b`;
- PR #172 accepted foundational capability investigation, exact HEAD `d7d676b79dbf3269f7fd3ebdb4363a6df19f255d`;
- PR #173 proposed architecture, exact starting HEAD `97191111bc2573c14d391c0af9628db7b11f194b`;
- PR #173 correction record for F-01, F-02 and F-03.

The exact current source revisions must be rechecked before independent review. The engineering evidence baseline used by PR #173 is historical and must not be represented as a current source audit.

## 17. Completion gates and no-shortcut rules

The Brain Foundation Architecture is complete only when:

- [ ] Every CF-01–CF-27 domain has been incorporated into the architecture or explicitly scoped with a reason and accountable later specification.
- [ ] Every responsibility has purpose, authority, inputs, outputs, interactions, developmental status, failure semantics and verification obligations.
- [ ] The 14 PR #173 unresolved questions have explicit dispositions; no foundational question is left as an unowned placeholder.
- [ ] All epistemic classes and lifecycle transitions are coherent across memory, belief, prediction, simulation, goals, action and learning.
- [ ] Goal formation, motivation and affect are foundationally addressed without hardcoded desired behaviours.
- [ ] Learning architecture covers more than numeric parameter adaptation and requires transfer/regression evidence.
- [ ] SYS-01, SYS-03, SYS-05, SYS-06, SYS-07 and SYS-08 boundaries are consistent with the approved whole-system architecture.
- [ ] Every architecture-level decision is either accepted by the Project Director, rejected with rationale, or explicitly reserved for a named later specification.
- [ ] Independent review of the exact completed revision returns CLEAR with no unresolved critical finding.
- [ ] Builder corrections are independently rechecked against exact changed lines.
- [ ] Project Director explicitly accepts the completed exact revision.

**No-shortcut rules:**
- A Builder's self-assessment is not independent review.
- A correction log is not proof that a finding is resolved.
- An open PR, green documentation workflow or large document is not architectural acceptance.
- No merge, implementation, runtime test, technology selection or deployment is authorized by this matrix.
- The next planning stage may begin only after the completion gates and explicit Project Director acceptance are satisfied.

## 18. Required Builder execution order

1. Reconcile every CF item against the existing architecture and add missing material to the architecture itself, not only this matrix.
2. Apply the recommended dispositions for Q1–Q14 as proposed architectural decisions, clearly labelled for Project Director review.
3. Update the main architecture's responsibility, state lifecycle, integration, developmental, failure and verification sections so this matrix is not a disconnected parallel specification.
4. Add a traceability table mapping each foundational requirement and accepted baseline item to exact architecture sections.
5. Run a contradiction and omission review across PR #171, PR #172, PR #173 and this completion artifact.
6. Produce a concise change log and exact revision manifest.
7. Submit the exact completed revision for blind independent review. The reviewer must not be given the Builder's desired verdict.
8. Correct findings, then obtain a fresh independent recheck.
9. Present only the exact reviewed revision and unresolved decision list to the Project Director for final acceptance.

**Current completion status:** The matrix and recommended architecture-level closures are established in this artifact. The architecture itself is not yet declared complete, independently cleared or accepted until steps 1–9 are evidenced.


## 19. Integration status update — 2026-11-11

The Builder has now integrated the matrix's conceptual closure material into the main architecture document as **Architecture completion addendum §§16–30** in `docs/architecture/02_BRAIN_FOUNDATION_ARCHITECTURE.md`.

The integration covers responsibility contracts, epistemic classes and state transitions, cross-responsibility exchange semantics, atomic owner-state commits with asynchronous propagation, foundational reasoning and simulation, goal and affective architecture, learning lifecycle and classes, metacognition, system/security/degraded-operation boundaries, developmental progression, verification obligations, dispositions for the 14 prior open questions, architecture-to-specification boundaries, language/symbolic cognition, social/agent modelling, existing-mechanism compatibility and Project Director reserved-decision authority.

### Exact revision manifest

- Starting PR #173 head: `97191111bc2573c14d391c0af9628db7b11f194b`
- Matrix commit: `59bc9766711e133c812ef7b89d18fa4c21ec9aa7`
- Main architecture integration commit: `80b6d2fc909024e7197cbbcfe652da0197a4bf48`
- Current PR #173 head at this update: `361d821343c4a68bcfbbdc86f528c84554262424`
- Compare from starting head: 2 commits ahead, 0 behind; 2 changed files (one architecture modification and one new matrix).

### Remaining gates — not represented as complete

1. Independent reviewer must inspect the exact current PR head, including the original proposal, F-01/F-02/F-03 correction record and completion addendum, against PR #171 and PR #172.
2. Independent review must challenge contradictions, omissions, unsupported assumptions, developmental integrity, whole-system boundaries and all 14 question dispositions.
3. Builder must correct findings and obtain independent recheck against the corrected exact revision.
4. Project Director must explicitly accept/reject/revise the 14 proposed BFA-C decisions and accept the exact reviewed architecture revision.

**Status:** Conceptual architecture integration performed; independent clearance pending; final Project Director acceptance pending. No implementation, merge or deployment is authorized.


### Additional integration — §§28–30

A subsequent closure pass added explicit architecture-level boundaries for language/symbolic cognition, minimum evidence-grounded social/agent modelling, advanced social-cognition deferrals, the preserve/adapt/replace assessment required for existing mechanisms, and decisions reserved to the Project Director. These additions address CF-16, CF-17, CF-26 and CF-27 more directly.

- Latest architecture integration commit: `80b6d2fc909024e7197cbbcfe652da0197a4bf48`.
- Latest PR #173 head after this pass: `80b6d2fc909024e7197cbbcfe652da0197a4bf48` (subject to final live recheck).

Independent review remains pending. The matrix and main architecture are not finally accepted.
