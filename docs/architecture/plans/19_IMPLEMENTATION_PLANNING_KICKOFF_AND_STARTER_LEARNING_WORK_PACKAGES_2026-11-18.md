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

### WP-07 — Attention, appraisal, goals and metacognitive integration

**Purpose:** Plan how the integrated loop selects work, evaluates context and revises goals without deterministic behavioural shortcuts.

**Planning outputs:**
- attention priority and dependency-freshness obligations;
- appraisal influence and revision evidence;
- metacognitive diagnose–request–correct–verify loop;
- supplied-goal versus experience-derived candidate-goal distinctions;
- cognitive decision versus external execution authorization boundary.

**Primary owners:** BM-06/BM-07/BM-08/BM-10, integrated with all preceding packages.

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
