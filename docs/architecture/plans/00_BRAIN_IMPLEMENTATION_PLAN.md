# Brain Implementation Plan — Planning Baseline

**Document status:** Proposed implementation plan; submitted for independent review and Project Director decision  
**Planning run:** Run 01 — 2026-11-03  
**Planning authority:** Project Director authorization received 2026-11-03  
**Governing specification:** PR #174, accepted HEAD `0811a59e46bf934e32e794f90e4e7d18d4e2bd97`  
**Parent architecture:** PR #173, accepted HEAD `97191111bc2573c14d391c0af9628db7b11f194b`  
**Engineering evidence baseline used by the existing audit:** `main` at `1273ddbcd0087d189e01388ded2d362fb1e058d2`  
**Scope:** Documentation and planning only  
**Governing principle:** **ENGINEER THE MECHANISMS; LET BEHAVIOR BE ACQUIRED THROUGH EXPERIENCE.**

---

## 1. Purpose and authority

This plan translates the accepted Brain Mechanism Specification into a proposed, evidence-driven implementation programme. It is intended to establish implementation order, dependency management, bounded work packages, integration obligations, verification evidence and stage gates.

This is an existing JARVIS project. This plan does not restart the project, replace the accepted architecture, or treat the current source tree as either wholly reusable or wholly disposable.

### 1.1 Authority boundary

This document is a planning proposal only. It does not authorize:

- runtime source changes, refactoring or migrations;
- creation or execution of runtime tests, builds, benchmarks, fuzzers or sanitizers;
- algorithm, model-provider, framework, database, programming-language, schema, API, protocol or deployment-topology selection;
- merge, release or deployment;
- autonomous action or external-world execution by the Brain.

A later Project Director decision must explicitly authorize implementation. Runtime verification and deployment remain separately governed gates.

### 1.2 Governing inputs

1. Accepted whole-system boundary and system ownership baseline in PR #171.
2. Accepted foundational capability investigation in PR #172.
3. Accepted Brain Foundation Architecture in PR #173.
4. Accepted 12-mechanism specification in PR #174, including 34 acceptance scenarios and BM-12 reasoning ownership.
5. Existing source audit at main commit `1273ddbcd0087d189e01388ded2d362fb1e058d2`.

The source audit is static inspection, not proof of runtime behavior. Its observations must be revalidated against the exact implementation target before coding begins.

---

## 2. Executive planning conclusion

Do not implement the 12 mechanisms as 12 independent feature tickets and do not build a single serial cognitive pipeline.

The recommended approach is a sequence of **integrated vertical capability increments** supported by shared foundations. Each increment must connect owner-managed state, context, evidence lineage and downstream use. A mechanism is not considered integrated merely because it has a class, API, test fixture or workspace field.

The most important early integration risks evidenced by the source audit are:

- memory retrieval is placed in cycle context but is not supplied to the inspected reasoning premises;
- the reasoning result has one partial downstream consumer (forward simulation/prediction), but memory is omitted from its premises and the full BM-12 premise/assumption/lineage contract is absent;
- current reasoning is a narrow consistency check and bounded traversal over pre-supplied causal links, not general inference;
- belief updates can overwrite a current scalar value without preserving a complete competing-claim history;
- causal links can be strengthened from co-state changes without demonstrated controls for confounding, temporal order or counterexamples;
- prediction records lack explicit scope, assumptions, horizon and resolution conditions;
- the learning loop demonstrates a narrow numeric prediction-feedback/adaptation path, not broad cognitive learning;
- supplied-goal processing exists, but experience-acquired candidate-goal formation is not demonstrated;
- attention and workspace structures exist, but their presence does not establish dependency freshness, multi-context coordination or coherent recovery;
- affect-related/developmental APIs have a source-level integration discrepancy that must be resolved before counting them as functioning capabilities;
- metacognitive summaries do not yet establish a complete diagnose–correct–verify loop.

These findings determine the proposed sequence. They do not prove that every related source component is unusable.

---

## 3. Implementation principles

Every work package must preserve the following:

1. **One coherent Brain authority.** Logical mechanisms own distinct state; they are not independent agents with competing identities, beliefs or goals.
2. **Mechanisms before behavior.** Implement enabling capabilities and evidence-handling contracts; do not encode desired learned conclusions as fixed mappings.
3. **Experience is evidence, not an instruction.** Intake does not automatically become interpretation, belief, causal knowledge, preference, emotion or goal.
4. **Owner-managed authoritative state.** Shared active context is a bounded view and coordination surface, not a universal source of truth.
5. **Traceable state change.** Material conclusions and updates must retain provenance, scope, assumptions, dependencies, version and lifecycle.
6. **Recurrent, selective processing.** The system must support interruption, delayed evidence, revisiting, concurrent independent work and targeted invalidation.
7. **External authority remains external.** Governance, security, operational authorization, execution and verified outcome remain outside Brain cognitive authority.
8. **Claims require evidence.** A passing unit test does not prove integrated cognition; a successful fixture does not prove learning or transfer.
9. **Preserve working capabilities.** Extend or replace existing code only after bounded source inspection establishes the reason.
10. **No premature implementation commitment.** This plan does not select concrete algorithms, providers, schemas, APIs, frameworks or infrastructure.

---

## 4. Dependency model

The dependency model is a capability graph, not a rigid total ordering. Some responsibilities can be developed in parallel after their contracts are stable; integration must still be demonstrated through end-to-end scenarios.

### 4.1 Foundational dependency clusters

| Cluster | Mechanisms | Why it comes early | Required exit evidence |
|---|---|---|---|
| Evidence and continuity spine | BM-01 Experience intake; BM-03 Memory; BM-11 Coordination/continuity | All later cognition depends on attributable experience, durable history, state ownership and recoverable dependencies | Evidence survives lifecycle; retrieval retains provenance; interruption/recovery preserves coherent owner state |
| Representation and epistemic state | BM-02 Representation; BM-04 Belief/world-state | Reasoning and prediction need explicit distinctions among observation, interpretation, hypothesis and accepted claim | Competing interpretations/claims can be retained, qualified, revised and traced |
| Inference and model use | BM-12 Reasoning; BM-05 Association/causal modelling/prediction | Reasoning must use evidence and memory, while causal/predictive claims require explicit assumptions and resolution | Memory materially influences an inference; premises/assumptions and lineage are inspectable; prediction can be validly resolved |
| Context-sensitive control | BM-06 Attention; BM-07 Affective appraisal; BM-10 Metacognitive monitoring | Processing priorities, appraisal and self-correction depend on usable context and observable cognitive state | Context can be prioritized, interrupted and resumed; appraisal modulates rather than commands; monitoring triggers targeted correction |
| Goal-directed cognition | BM-08 Goals/intent/planning/decision | Goal evaluation and decisions depend on beliefs, predictions, memory, reasoning, context and appraisal | Supplied and candidate goals remain distinct; unsupported goals are revised/deferred; plans use qualified premises |
| Developmental change | BM-09 Learning and adaptation, coordinated with all state owners | Learning changes several cognitive state classes and must be evaluated for persistence, transfer and regression | Accepted change persists, affects later behavior, transfers appropriately and can be contained or reversed |

### 4.2 Critical dependency edges

- BM-01 → BM-02/BM-03/BM-04/BM-05/BM-09: acquired evidence and provenance precede interpretation, retention, revision, prediction and learning.
- BM-03 → BM-02/BM-05/BM-07/BM-08/BM-12: retrieved history must be available with contextual applicability and lineage.
- BM-02 → BM-04/BM-05/BM-12: interpretations inform claims and inference but do not silently become accepted beliefs.
- BM-04 ↔ BM-05: qualified beliefs can support predictions; attributed outcomes and counterevidence can trigger belief/model reassessment.
- BM-03 + BM-04 + BM-05 + BM-02 → BM-12: reasoning requires evidence-bearing premises, memory, interpretation, belief status and scoped hypotheses.
- BM-12 → BM-04/BM-05/BM-08: provisional conclusions are evaluated by their owning mechanisms; reasoning does not directly seize belief, causal-model, goal or decision authority.
- BM-06 ↔ all active mechanisms: attention selects bounded processing context; it does not own the underlying memory, belief or prediction state.
- BM-07 → BM-06/BM-08/BM-09: appraisal may modulate priority, evaluation and learning; it is not a deterministic stimulus-to-action map.
- BM-10 → relevant owner mechanism/BM-11: monitoring identifies a limitation and requests targeted work; it does not overwrite another mechanism's authoritative state.
- BM-09 ↔ all mechanism owners: learning candidates are evaluated and activated by the relevant state owner, with BM-11 coordinating dependencies and recovery.
- BM-11 supports all clusters: concurrency, invalidation, interruption and recovery cannot be deferred until after integration.

### 4.3 Parallelism constraints

Parallel work is permitted only where:
- ownership and conceptual contracts are stable;
- work packages do not modify the same authoritative state boundary without an explicit coordination plan;
- dependencies are represented and versioned;
- integration acceptance scenarios are assigned to an owner.

Parallel coding before shared contracts are stable risks duplicate state models, incompatible lifecycle semantics and integration debt. Do not optimize for number of simultaneous contributors.

---

## 5. Proposed implementation phases

These are planning phases, not authorization to start them. Each phase requires its own approved scope and exit decision.

### Phase 0 — Target-baseline and contract readiness

**Purpose:** Establish what code is actually being built upon and turn the accepted specification into traceable engineering obligations.

**Work:**
- verify the current PR stack, exact base/head commits and target branch;
- re-audit affected source and tests at the exact target commit, not only the historical main baseline;
- map each BM responsibility and acceptance scenario to current source, existing tests and missing evidence;
- record build/test entry points and known environment constraints without running them absent authorization;
- identify state owners, public interfaces, persistence/replay paths, runtime call paths and external system boundaries;
- resolve specification ambiguities that would otherwise force implementation guesses, including BM-07's prohibition on claiming authority over SYS-08 state;
- define change-control, traceability and review requirements.

**Exit gate:** Every proposed work package has a verified source baseline, specification trace, owner, dependencies, scope and measurable acceptance evidence. No unresolved ambiguity is silently converted into an implementation decision.

### Phase 1 — Evidence, continuity and coordination spine

**Primary responsibilities:** BM-01, BM-03, BM-11; supporting contracts for BM-02 and BM-04.

**Work:**
- establish attributable experience intake and immutable/traceable acquisition lineage;
- assess existing event journal and memory persistence for recoverability and corruption/partial-write behavior;
- define memory retrieval evidence and context requirements, separating retrieval success from relevance and truth;
- define owner-managed state changes, dependency freshness, interruption, idempotency and recovery checkpoints;
- ensure restored state is validated rather than assuming replay alone proves coherent reconstruction.

**Exit gate:** A recorded experience can be retained, retrieved with source/context, survive the specified lifecycle, and be recovered without claiming unverified derived state is valid. Workspace snapshots are not accepted as authoritative state merely because they contain fields.

### Phase 2 — Representation, belief and reasoning vertical slice

**Primary responsibilities:** BM-02, BM-04, BM-12, integrated with BM-03 and BM-11.

**Work:**
- preserve observation/interpretation/belief distinctions and competing hypotheses;
- establish evidence-sensitive belief revision and invalidation semantics;
- extend reasoning from the narrow existing engine only where compatible with the BM-12 contract;
- make memory-derived evidence materially available to reasoning with provenance and contextual limits;
- preserve premise/assumption sets, inference lineage, alternatives, contradictions, counterexamples, scope and uncertainty;
- ensure reasoning results are consumed by the appropriate downstream owners and do not bypass BM-04/BM-05/BM-08 authority.

**Exit gate:** At least one end-to-end scenario demonstrates that relevant retrieved memory changes a later inference, lineage explains why, contradiction or defeated assumptions qualify the conclusion, and only the owning mechanism can accept the resulting belief/plan/model change.

### Phase 3 — Causal hypotheses and prediction lifecycle

**Primary responsibility:** BM-05, integrated with BM-01/03/04/09/11/12.

**Work:**
- distinguish association, correlation, temporal order and causal hypotheses;
- require context, scope, assumptions and counterevidence for causal claims;
- define prediction identity, horizon, expected evidence, resolution criteria and attribution;
- handle delayed, partial, missing, conflicting and invalid outcomes;
- ensure infrastructure failure, failed execution and unverified consequence are not misclassified as external-world evidence;
- define how prediction error can create a learning candidate without automatically changing a model.

**Exit gate:** Predictions are independently identifiable and resolved only by evidence meeting their stated conditions; unsupported co-occurrence does not become a universal causal rule.

### Phase 4 — Attention, appraisal, metacognitive control and goal-directed cognition

**Primary responsibilities:** BM-06, BM-07, BM-08, BM-10, integrated with prior phases.

**Work:**
- make attention sensitive to task/context relevance, uncertainty, urgency and other justified influences without assuming fixed bootstrap weights are learned competence;
- resolve affective source/API ownership discrepancy and distinguish cognitive estimates from authoritative SYS-05 and SYS-08 state;
- define minimum contextual appraisal as modulation, not a direct action mapping;
- distinguish supplied goals from candidate goals formed through experience;
- evaluate candidate goals against evidence, feasibility, conflicts, constraints and later outcomes;
- ensure plans and decisions expose premises and become stale when dependencies change;
- connect metacognitive detection to targeted correction and evaluation of correction.

**Exit gate:** The system can manage competing contexts, form and evaluate a candidate goal from novel experience without a fixed event-to-goal rule, identify unsupported assumptions, and revise affected plans before use.

### Phase 5 — Cross-mechanism learning and developmental activation

**Primary responsibility:** BM-09, with every relevant state owner and BM-11.

**Work:**
- define learning candidate lifecycle: formation, evidence attribution, evaluation, owner approval, activation, persistence, monitoring, containment and rollback;
- cover more than numeric parameter adaptation: belief revision, retrieval/consolidation improvement, causal/predictive model changes, reasoning calibration, strategy and procedural capability where justified;
- define interference, regression, counterexample and transfer evaluation;
- ensure one candidate that affects multiple mechanisms is coordinated without partial incoherent activation;
- preserve developmental lineage across restart/reconstruction.

**Exit gate:** A justified experience changes an owned cognitive state, persists, causes a measurable later behavioral difference, improves in a relevant varied/novel context, and does not silently damage unrelated capability. Narrow numeric adaptation must be reported only as narrow adaptation.

### Phase 6 — Integrated Brain capability verification and starter training readiness

**Purpose:** Verify the Brain as an interacting cognitive system, not a collection of green unit tests.

**Work:**
- execute approved component, contract, integration, persistence/recovery, adversarial and regression tests;
- run longitudinal experience sequences that include ambiguity, delayed outcomes, contradiction, irrelevant memories, failed actions and novel related contexts;
- compare pre-update and post-update behavior using predefined measures;
- verify learning provenance, persistence, transfer boundaries and rollback;
- assess whether starter training experiences exercise the mechanisms without preloading the target knowledge or behavior;
- record capability limitations and define safe training boundaries.

**Exit gate:** The Project Director receives evidence for each capability claim, unresolved failure, limitations, regressions and readiness for controlled starter training. Passing tests alone does not authorize open-ended autonomous operation.

---

## 6. Work-package structure

Each future work package must use this template:

1. **Package ID and title**
2. **Mechanism ownership:** authoritative owner(s), participating mechanisms and external SYS dependencies.
3. **Specification trace:** exact section(s), invariant(s) and acceptance scenario(s) in PR #174.
4. **Current-source baseline:** exact commit, files, symbols, call paths and tests inspected.
5. **Observed gap:** what source evidence establishes; distinguish absence in inspected path from proof of total absence.
6. **Target behavior:** observable capability, not a class/file request.
7. **Inputs/outputs and lifecycle:** conceptual evidence, state changes, provenance, scope, freshness and failure behavior.
8. **Dependencies and integration contracts**
9. **Verification plan:** unit, contract, integration, persistence/recovery, regression, adversarial and longitudinal evidence as applicable.
10. **Non-goals and prohibited shortcuts**
11. **Risks and rollback/containment**
12. **Reviewer and Project Director gates**

A work package must not be approved merely because it is small or easy to implement. It must advance a coherent capability and have a credible verification path.

---

## 7. Verification strategy

### 7.1 Evidence levels

| Level | What it establishes | What it does not establish |
|---|---|---|
| Static source inspection | Visible structures, call paths and apparent ownership | Runtime correctness or end-to-end capability |
| Unit tests | Local behavior under specified fixtures | Integration, persistence or generalization |
| Contract tests | Compatibility of owner boundaries and lifecycle semantics | Full cognitive behavior |
| Integration tests | Cross-mechanism information flow and downstream use | Long-term learning or transfer |
| Persistence/recovery tests | State and lineage survive restart/interruption as specified | Correct semantic learning |
| Adversarial/regression tests | Resistance to contradictions, stale state, failures and interference | Broad capability in all contexts |
| Longitudinal learning trials | Persistent experience-dependent change and later behavioral effect | Universal intelligence or unrestricted autonomy |
| Transfer tests | Improvement in justified novel related contexts | Unbounded generalization |

### 7.2 Mandatory learning proof

No claim of learning is accepted unless evidence shows:

**experience → evidence-sensitive update → persistent change → later behavioral effect → evaluation in relevant and novel contexts.**

The verification report must identify:
- the actual experience and its provenance;
- the candidate update and why it was formed;
- the owner-authorized state change;
- persistence/recovery evidence;
- the pre/post behavioral difference;
- the relevant transfer context and unrelated negative controls;
- counterexamples, regression results and rollback outcome if applicable.

### 7.3 Core integration tests to prioritize

1. Retrieved relevant memory changes a later inference; retrieved irrelevant memory does not.
2. A contradiction changes/qualifies a belief and invalidates only affected dependent conclusions/plans.
3. A causal hypothesis survives counterexample testing or is weakened/withdrawn.
4. A prediction remains unresolved until attributed evidence satisfies resolution conditions.
5. A defeated assumption makes dependent reasoning and planning stale.
6. Candidate goal formation is evidence-derived and distinct from supplied goals.
7. Affective appraisal influences attention/evaluation without directly commanding behavior.
8. A metacognitive finding triggers targeted correction and checks whether it worked.
9. A learning candidate persists after reconstruction and changes future behavior.
10. A learned change transfers to a relevant novel context while remaining bounded against unrelated contexts.
11. Interrupted or partially committed multi-mechanism updates recover to a coherent state.
12. A governance denial, execution failure or substrate failure is not misrepresented as a verified external outcome.

The 34 scenarios in PR #174 remain binding. The list above prioritizes cross-mechanism integration; it does not replace or reduce the specification suite.

---

## 8. Risk register and controls

| Risk | Why it matters | Required control |
|---|---|---|
| Coding by mechanism name | Produces disconnected modules without capability | Require vertical capability increments and integration exit evidence |
| Preserving current call paths by default | Existing paths contain known integration gaps | Revalidate against specification; reuse only with evidence |
| Premature universal data envelope | Flattens distinct evidence and state semantics | Preserve plural domain representations under common provenance discipline |
| Hardcoded learned behavior | Fakes development and prevents genuine acquisition | Audit mappings; permit deterministic integrity/governance constraints only |
| Numeric adaptation overstated as learning | Misrepresents capability maturity | Require persistent behavioral and transfer evidence |
| Memory retrieval treated as cognition | Retrieval may be irrelevant or unused | Demonstrate material downstream influence with provenance |
| Causal overclaim | Co-state changes can encode spurious causal relations | Require scope, counterexamples, alternative causes and attributed outcomes |
| Global mutable workspace | Creates stale state and competing authority | Owner-managed state, bounded context and dependency invalidation |
| Concurrent partial updates | Can leave incoherent cognitive state | Define conflict handling, atomicity boundaries and recovery |
| Affective API/source mismatch | Risk of counting unintegrated interfaces as capability | Resolve exact declaration/translation-unit/build membership before implementation claims |
| Over-broad first implementation | Expands scope and creates untestable integration | Small vertical slices with explicit exit gates |
| Premature technology choice | Locks architecture before evidence | Defer until a separate decision is justified and authorized |
| Reviewer/Builder authority confusion | Allows self-approval or unauthorized progression | Independent review, then explicit Project Director gate |

---

## 9. Open questions to resolve before implementation

1. What is the current exact implementation target commit, and how has it changed since the historical source audit?
2. Which existing persistence/replay mechanisms can satisfy the accepted continuity and recovery contracts?
3. What exact source/build integration explains the affective/developmental API discrepancy?
4. Which state transitions require atomic commitment across multiple owners, and which can converge asynchronously?
5. What evidence is sufficient to attribute a delayed outcome to a specific prediction/action?
6. What is the minimum memory retrieval evaluation corpus covering varied wording, abstraction, context and irrelevant distractors?
7. How should confidence/uncertainty dimensions remain distinct across perception, source reliability, beliefs, predictions and reasoning?
8. What candidate-goal generation capabilities can be developed without a hardcoded objective generator?
9. Which learning changes can safely be evaluated online, and which require isolated evaluation?
10. What is the smallest useful starter-training curriculum that exercises multiple mechanisms without preloading target conclusions?
11. What are the acceptable performance/resource budgets for the first integrated Brain slice?
12. What external SYS-02/03/04/05/07/08/09/10/11 contracts must be verified before a capability depends on them?

These questions must be answered by evidence and explicit decisions, not by assuming a convenient implementation.

---

## 10. Recommended first implementation increment

After Phase 0 and separate implementation authorization, the recommended first coding increment is a **bounded evidence-to-memory-to-reasoning-to-belief vertical slice**, not a broad implementation of all mechanisms.

It should demonstrate:
- an experience enters with source and temporal provenance;
- it is interpreted without overwriting the acquired evidence;
- relevant prior memory is retrieved with context and provenance;
- BM-12 uses that memory and current premises in a traceable inference;
- alternatives, assumptions, uncertainty and contradictions remain visible;
- BM-04 alone evaluates and commits any belief revision;
- BM-11 tracks dependent state and interruption/recovery;
- a later experience can confirm, qualify or defeat the earlier conclusion.

This increment targets the most concrete integration gap in the audited candidate: memory retrieval reaches cycle context but not the reasoning premises. Reasoning conclusions do feed forward simulation/prediction, but the full BM-12 lineage contract and evaluation by the relevant authoritative owners are not demonstrated. It also creates a foundation for prediction and learning without prematurely implementing every advanced capability.

This is a recommendation, not an implementation authorization or an irreversible architecture decision. Phase 0 may show that a different first vertical slice is safer or more useful.

---

## 11. Review and approval gates

1. Builder submits this plan and its separate run/checkpoint record.
2. Independent Reviewer inspects the exact commit, source evidence, dependency model, phase order, acceptance criteria and scope boundaries.
3. Builder addresses valid findings in the planning package and records each correction separately.
4. Project Director accepts, rejects or returns the plan.
5. Only after acceptance may the Project Director separately authorize a bounded implementation phase.
6. Each implementation phase receives its own review and Project Director gate before progression.

**Independent Reviewer approval is not Project Director acceptance. Project Director acceptance of this plan is not implementation authorization.**

---

## 12. Explicit non-decisions

This plan intentionally does not choose:
- programming language or framework;
- model provider or LLM dependency;
- memory retrieval, inference, causal discovery, learning or affective algorithms;
- database, persistence engine, schema or serialization;
- service/process/thread topology;
- deployment architecture or operational autonomy level;
- exact implementation tickets or code changes.

Those decisions require current-source evidence, a justified comparison and separate authorization where applicable.


## 13. Gate A and Gate B audit update — 2026-11-03

The Project Director authorized the Builder to carry out Gate A and Gate B together as documentation/review work. The resulting records are:

- `reviews/04_GATE_A_BUILDER_TECHNICAL_REREVIEW_2026-11-03.md` — Builder-side technical re-review of the Gate A evidence and disposition.
- `reviews/05_GATE_B_MECHANISM_TRACEABILITY_AUDIT_2026-11-03.md` — source-to-specification traceability across BM-01 through BM-12 at PR #156's exact code-bearing parent.

**Gate A remains NOT CLEARED.** The technical re-review confirms the no-go disposition. Commit-to-origin/path/hunk attribution for the 1,416 inherited commits remains incomplete; divergent PR #151/#150 integration hunks, 24 Brain API body differences, two unmatched definitions and five workflow files still require closure. PR #156 remains a candidate only. A separate independent reviewer verdict has not been submitted.

**Gate B static traceability is complete for all 12 mechanism owners at candidate code-bearing parent `15d49e5fdeb5723c475922ab78fb92f97c4b3b84`. Mechanism acceptance is NOT PASSED.** The audit records substantial reusable foundations and the exact integration/acceptance gaps. It does not claim all 34 acceptance scenarios pass, and no runtime tests or builds were run.

The candidate's reasoning path is described precisely: valid reasoning conclusions can feed forward simulation and prediction. However, retrieved memories are not supplied as reasoning premises and the complete BM-12 premise, assumption, provenance, alternative, counterexample and dependency-lineage contract is not demonstrated.

This combined audit does not select an implementation baseline or authorize runtime changes, builds, tests, benchmarks, technology choices, merges, rebases, cherry-picks, history rewrites or deployment. Gate A closure and independent review remain required before a baseline decision.


## 14. Gate A semantic reconciliation update — 2026-11-04

The targeted semantic reconciliation is recorded separately in:

`reviews/06_GATE_A_SEMANTIC_RECONCILIATION_ADDENDUM_2026-11-04.md`.

The addendum classifies all 24 common Brain API body differences, confirms the earlier parser-unmatched `beliefs()` definition is identical, records the bool-versus-void return-type change for `register_evolution_parameter()`, and identifies seven candidate-only APIs. It reviews the divergent PR #151/#155 and PR #150/#156 integration paths and all five current-main workflow files. All 35 test target names referenced by the current-main learning-mechanisms workflow are present in the candidate CMake registry.

Two candidate correctness risks require attention before a baseline is selected:
1. `Brain::choose` and `choose_with_affect` key learned-strategy retrieval from `eligible.front().id`, although eligible goals include pending goals and the selected intent may be a different active goal.
2. `Brain::create_goal` does not reject non-finite priority/progress before journaling; `GoalModel::create` rejects such values afterward.

Partial multi-event goal completion and evolution rollback/replay ordering also require failure-injection evidence. These are recorded as review findings, not silently fixed.

**Gate A remains NOT CLEARED.** Full per-commit origin/path/hunk attribution across the 1,416 inherited commits, particularly the 1,244-commit PR #97 line, remains incomplete. Independent review is still required. No implementation baseline is selected.



## 15. Risk-based Gate A closure assignment — 2026-11-04

Following the Project Director's authorization, the bounded closure programme is defined in:

`reviews/07_GATE_A_CLOSURE_ASSIGNMENT_2026-11-04.md`.

This assignment refines the remaining historical-provenance requirement. A standalone origin/path/hunk record for every one of the 1,416 inherited commits is not an automatic Gate A prerequisite. The required standard is:
- path-level accounting for all 165 final-tree paths;
- deeper commit/hunk attribution for unexplained, overlapping, conflict-resolved, replaced, or high-risk changes;
- explicit risk and decision-impact classification for every residual provenance gap;
- no waiver of unexplained high-risk final-tree changes based only on aggregate commit/path counts.

The assignment also separates the remaining work into:
1. risk-based provenance and final-tree integrity;
2. declaration/caller/overload/function-pointer API compatibility;
3. continuity dispositions for all five current-main workflows;
4. explicit remediation invariants and future regression acceptance criteria for the two confirmed candidate defects;
5. an independent-review packet pinned to one exact PR head.

The two candidate defects remain **confirmed and unfixed**. D1 is the mismatch between eligible-goal ordering and selected-intent identity in learned-strategy retrieval. D2 is the possibility of journaling NaN goal input before model validation; the consistent future contract rejects all non-finite values before event creation. No runtime changes or tests are authorized by this assignment.

**Gate A remains NOT CLEARED.** The assignment does not select PR #156, waive independent review, or authorize implementation. Gate A clearance still requires evidence for every closure criterion, a genuine independent review, and the Project Director's explicit baseline decision.


## 16. Gate A closure evidence package — 2026-11-04

The authorized closure assignment has been recorded in `reviews/07_GATE_A_CLOSURE_ASSIGNMENT_2026-11-04.md`. Initial evidence artifacts have now been created:

- `reviews/08_GATE_A_RISK_BASED_PROVENANCE_MATRIX_2026-11-04.md` — enumerates all 165 recorded net-tree paths and assigns the 145 / 14 / 6 origin classes from the prior reconciliation. This is path-set accounting, not complete per-path semantic or per-commit hunk closure.
- `reviews/09_GATE_A_API_COMPATIBILITY_MATRIX_2026-11-04.md` — records the 24 body differences, seven candidate-only APIs, and the bool-versus-void signature issue. Declaration/overload/caller inventory remains open.
- `reviews/10_GATE_A_WORKFLOW_CONTINUITY_MATRIX_2026-11-04.md` — records all five workflow dispositions and the exact limitations of target-name/file-identity evidence. No workflow was executed.
- `reviews/11_GATE_A_CANDIDATE_DEFECT_DISPOSITION_2026-11-04.md` — records D1/D2 as confirmed and unfixed, with future remediation invariants and regression acceptance criteria.
- `reviews/12_GATE_A_INDEPENDENT_REVIEW_PACKET_2026-11-04.md` — consolidates the review scope, evidence, questions, limits and verdict format.

These are initial closure artifacts, not proof that every workstream is complete. In particular, the API caller inventory and high-risk per-path semantic attribution still need work. The review packet is assembled but no reviewer identity/request/submission exists.

**Gate A remains NOT CLEARED.** No baseline is selected. No runtime changes, builds, tests, workflow executions, history operations, or implementation were performed.


## 17. Final Gate A baseline applicability recommendation — 2026-11-04

The extended Builder-side Gate A review is recorded in
`reviews/13_GATE_A_FINAL_BASELINE_RECOMMENDATION_2026-11-04.md`.

**Technical recommendation:**
- Do not adopt PR #156 as a wholesale implementation baseline.
- Use accepted PR #174 HEAD `0811a59e46bf934e32e794f90e4e7d18d4e2bd97` as the integration starting point.
- Treat PR #156 code-bearing parent `15d49e5fdeb5723c475922ab78fb92f97c4b3b84` as a source donor. Port reusable mechanisms in small, reviewable, specification-mapped work packages.
- Preserve the five validation workflows present on current main/accepted-spec ancestry.
- Treat confirmed D1/D2 defects as mandatory correction prerequisites; prove the unresolved goal-completion and evolution rollback failure boundaries with failure-injection/replay evidence.
- Do not claim capability acceptance from source presence or the historical 73/73 CTest result. The 34 accepted foundational scenarios remain the governing acceptance target.

The comparison established that accepted PR #174 HEAD is 12 commits ahead of current main and adds the accepted architecture/specification documents; candidate PR #156 is 21 commits behind that accepted point. The candidate and current main are substantially divergent. The candidate contains useful cognitive mechanisms, but wholesale adoption would import known defects, miss current validation workflows and require broad reconciliation.

**Builder technical result:** PR #156 is rejected as a wholesale baseline and accepted as a selective source donor; accepted PR #174 HEAD is the recommended integration base.

**Formal Gate A remains NOT CLEARED.** No independent PR #175 review has been submitted, and the Project Director has not approved the baseline. This recommendation is not implementation authorization. No runtime changes, builds, tests or workflow executions were performed.


**End of proposed Brain Implementation Plan.**


## Gate A closure evidence refresh — 4 November 2026

Latest consolidated evidence: docs/architecture/plans/reviews/16_GATE_A_CLOSURE_EVIDENCE_UPDATE_2026-11-04.md.

- Corrected exact tree provenance: 143 PR #97-only unchanged paths, 16 PR #97/post-PR #97 overlaps, 2 post-PR #97 modifications to existing paths, 4 post-PR #97 additions.
- Static public Brain API inventory completed within core/cpp: 26 candidate-only public method names, overload/signature differences and full identifier/call-site scan. External ABI/downstream compatibility remains a later integration build gate.
- Preservation/adaptation specification completed for all five current-main validation workflows. Workflow implementation/execution remains later integration work.
- D1/D2 corrections, regression tests and deterministic goal/evolution journal failure/replay tests are on draft PR #176. PR #156 remains unchanged until correction review/merge or selective port.
- Residual: deeper EvolutionController compensation failure injection and independent re-check remain open.

**Gate A remains NOT CLEARED.** PR #174 remains the recommended integration starting point; PR #156 remains a selective source donor only. No baseline is selected and implementation is not authorized.
