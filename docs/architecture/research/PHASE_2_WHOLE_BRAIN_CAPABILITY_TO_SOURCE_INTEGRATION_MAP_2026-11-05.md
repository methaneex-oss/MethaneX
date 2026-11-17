# Phase 2 — Whole-Brain Capability-to-Source Integration Map

**Date:** 2026-11-05  
**Repository:** `methaneex-oss/MethaneX`  
**Specification reference:** PR #174, exact HEAD `0811a59e46bf934e32e794f90e4e7d18d4e2bd97`  
**Accepted architecture reference:** PR #173, exact HEAD `97191111bc2573c14d391c0af9628db7b11f194b`  
**Whole-system boundary:** PR #171 reviewed package HEAD `b05434758ad4fe72815503f89bd5d2990ccb658b`  
**Main source baseline:** `1273ddbcd0087d189e01388ded2d362fb1e058d2`  
**PR #97 donor snapshot:** `c1da222e6c94aeb3f2ad000392c21fe4fc81ab25`  
**Integrated donor tree identified by Phase 1:** `15d49e5fdeb5723c475922ab78fb92f97c4b3b84`  
**Status:** Phase 2 investigation report — static source/document evidence; not an implementation plan or implementation authorization.

---

## 1. Executive finding

The existing repository contains a meaningful cognitive substrate and several advanced donor capabilities. It does **not** yet establish one integrated, specification-complete Brain.

The decisive gap is not simply missing mechanisms. It is incomplete exchange and downstream use of information between mechanisms that already exist. The audited main CognitiveCycle retrieves memories but does not pass them into its reasoning problem; it records the reasoning result but does not use that result to revise beliefs or influence later prediction, goal selection, planning or decision. Other examples include a causal learner that treats co-state transitions as causal links, a goal lifecycle that processes supplied goals but does not generate experience-acquired candidates, and a numeric learning loop that does not establish broad cognitive development.

The donor work contains more advanced pathways than main, including affective modulation, action-consequence feedback, developmental strategy transfer and evolution controls. These are real candidate mechanisms with identifiable source and consumer paths. They are not a complete Brain, are not automatically compatible with the accepted specification, and must not be merged wholesale. PR #176's D1/D2 corrections and remaining failure-verification boundary remain relevant.

**Current conclusion:** preserve and selectively adapt the strongest mechanisms, but prioritize integration contracts, state authority, provenance, dependency invalidation, learning attribution and end-to-end evidence. Adding more isolated modules would not resolve the primary problem.

## 2. Evidence and authority discipline

This report uses three evidence classes:

1. **Main source evidence:** exact source files inspected at `1273ddbcd0087d189e01388ded2d362fb1e058d2`.
2. **Donor source evidence:** selected high-impact PR #97 paths traced at `c1da222e6c94aeb3f2ad000392c21fe4fc81ab25`, as recorded in the Phase 1 donor traceability matrix.
3. **Architecture/specification evidence:** PR #173 and PR #174 exact heads above.

A source declaration, class, test source, CMake target or historical CI result is not equivalent to verified integrated capability. The Phase 1 main source audit was static only; this Phase 2 pass also did not execute builds, tests, benchmarks or runtime experiments. The donor matrix verifies selected source paths and CMake target declarations, not that all donor tests ran at the donor commit.

PR #174's formal acceptance event is preserved. Later F-02/F-03 findings remain open correction obligations. PR #175 remains draft and records Gate A as **NOT CLEARED** and Gate B capability acceptance as **NOT PASSED**. PR #176 remains draft/unmerged; its corrected donor code is not integrated into the candidate implementation tree. PR #178 governance remains proposed pending explicit owner acceptance. This report changes none of those authorities.

## 3. Whole-Brain integration model

BM-01 through BM-12 are logical responsibilities and state authorities, not a required one-class-per-mechanism decomposition and not twelve independent agents. A single coherent Brain must coordinate them while retaining explicit ownership of distinct state.

### 3.1 Recurrent cognitive activity

The intended architecture is not a fixed serial pipeline. A useful high-level interaction model is:

- **Experience acquisition and grounding:** incoming events are preserved with provenance; interpretation may branch where evidence is ambiguous.
- **Contextualization:** relevant memories, beliefs, goals, predictions and internal-condition estimates are retrieved or made active.
- **Parallel appraisal and inference:** attention allocates processing; affective appraisal evaluates contextual significance; reasoning derives provisional conclusions; causal/predictive mechanisms form and resolve scoped expectations.
- **Evaluation and commitment:** belief owners evaluate candidate claims; goal/decision owners evaluate options; plans remain dependent on the evidence and assumptions from which they were formed.
- **Action boundary:** cognitive intent or an action request is handed to governance, authorization, operational validation and execution systems. The Brain does not treat intent as permission or an issued action as a verified consequence.
- **Outcome and development:** attributed outcomes can resolve predictions, revise beliefs, update memory and generate learning candidates. Candidate changes are evaluated, activated by their authoritative owners, persisted and monitored for transfer or regression.
- **Metacognitive and coordination feedback:** detected uncertainty, contradiction, stale state, overload or repeated failure can reopen any affected work; coordination tracks dependencies and coherent recovery.

These activities can overlap, branch, pause, resume or be revisited. A new observation may change the interpretation of an old memory; a belief revision may invalidate a plan; an outcome may change a strategy; metacognition may request new retrieval before a decision. The interaction model must therefore support recurrence and selective processing, not merely execute a predetermined list of calls.

### 3.2 State ownership and shared context

The accepted architecture's hybrid pattern remains the right governing boundary:

- each logical responsibility owns its authoritative state;
- active workspace is a bounded, task-sensitive view, not a truth database;
- state changes carry identity, provenance, version/freshness and dependency information;
- coordination tracks conflicts and invalidations but does not become a second cognitive authority;
- SYS-08 substrate state remains separate from cognitive-state validity;
- governance and execution remain outside Brain decision authority.

The audited `CognitiveWorkspace` stores snapshots of many cycle fields, and the runtime projects a cycle result into it. That demonstrates a workspace projection path, not complete workspace consumption, dependency freshness, multi-context isolation or authoritative-state reconciliation.

## 4. BM-01 through BM-12 source-to-capability map

Status labels below are deliberately conservative:

- **Partial on main:** relevant source exists, but the full specification capability is not demonstrated.
- **Donor candidate:** stronger source path exists on an unmerged donor branch; compatibility and acceptance remain open.
- **Not demonstrated:** inspected evidence does not establish the specified capability.
- **Cross-cutting:** capability depends on coordinated behavior across multiple responsibilities.

| Mechanism | Main source evidence and current behavior | Donor evidence / reuse direction | Current disposition |
|---|---|---|---|
| **BM-01 Experience intake and provenance** | `event.hpp`, `brain.cpp`, `memory.cpp`: sequenced events carry timestamp, source, kind and scalar attributes; Brain observes and journals events; replay reconstructs state. The event envelope does not enforce full source lineage, distinct event/receipt times, modality, epistemic status or derivation lineage. | PR #97 action-outcome path records action/context, expected and observed consequence, reliability and execution/verification distinctions. Retain event continuity and outcome records; reconcile richer provenance semantics. | **Partial on main; donor candidate.** Reuse event journal direction, adapt evidence/provenance contract. |
| **BM-02 Representation and interpretation** | Phase 1 identifies representation normalization and provider pipeline, including provider capability checks, candidate validation, exception isolation and fallback normalization. Main does not demonstrate broad raw multimodal perception or robust plural interpretation under ambiguity. | Donor learning/context paths use representation features, but tokenization and context hierarchy contain engineered inductive biases. | **Partial on main.** Preserve provider/representation boundary; do not confuse normalized event attributes with grounded understanding. |
| **BM-03 Continuity and memory** | `memory.cpp`: durable event journal, metadata sidecar, Working/Episodic/Semantic/Procedural tiers, structured attribute-overlap ranking, salience/confidence metadata and promotion/demotion. The inspected cycle retrieves memories but omits them from reasoning premises. | PR #97 has event-backed persistence/reconstruction and tests covering memory/learning/evolution persistence. This is a continuity foundation, not semantic memory or a tamper-evident trust system. | **Partial on main; donor candidate.** Keep journal/replay; adapt semantic/contextual retrieval, consolidation lineage and retrieval-use evidence. |
| **BM-04 Belief and world-state management** | `brain.cpp`, world-model and belief types: event attributes update a key/value belief map; same values raise confidence and changed values replace current values with generic confidence adjustment. Explicit competing hypotheses, evidence lineage, scope and revision reasons are not established in the inspected record. | PR #148+ donor line is identified by Phase 1 as stronger for competing alternatives, evidence accumulation, source/provenance separation and replay-order validation. | **Partial on main; donor candidate.** Preserve world-state containers; adapt evidence-sensitive revision and alternative retention. |
| **BM-05 Association, causal modelling and prediction** | `association_model.cpp`, `causal_model.cpp`, `reasoning.cpp`: associations and causal links can be formed from belief changes/co-state; simulation traverses links above a fixed strength threshold; predictions are journaled and resolved. Causal confounding, interventions, counterexamples, scoped assumptions and full outcome attribution are not established. | PR #97 adds contextual prediction and feedback paths; Phase 1 records bounded numeric/contextual scope and the need for held-out evaluation. | **Partial on main; donor candidate.** Keep prediction identity/outcome lifecycle; do not equate co-state transition with causation. |
| **BM-06 Attention and active context** | `attention.cpp`: score combines novelty, uncertainty derived from strongest belief confidence and optional urgency; reinforcement/suppression adjusts weights. `cognitive_workspace.*` and runtime project cycle fields into a snapshot. The scoring path does not directly use broad goal relevance, affective appraisal, consequences or resource contention. | PR #97 affective planning can influence bounded planning/intent paths. | **Partial on main.** Preserve attention and workspace prototypes; adapt context relevance, concurrent context isolation, interruption/resumption and starvation detection. |
| **BM-07 Affective appraisal and valuation** | Main source audit found affect-related declarations/definitions in `brain_restored_api.cpp` but an ownership/member declaration discrepancy in inspected `brain.hpp`; no build was run, so this is an integration discrepancy, not a confirmed compile failure. Foundational affective appraisal is not established on main. | PR #97 `affective_state.cpp` updates continuous valence/arousal/uncertainty/tension/stability from outcome, prediction error, novelty, salience, uncertainty and confidence. `brain_affective_planning.cpp` consumes appraisal weights/state in intent/planning and action evidence. These are visible consumers, not isolated values. Equations and decay are engineered priors; scope is bounded. | **Not established on main; donor candidate.** Reconcile ownership and SYS-05/SYS-08 boundaries; evaluate calibration and context sensitivity before adoption. |
| **BM-08 Goals, intent, planning and decision** | `goals.cpp`, `intent.cpp`, `strategy.cpp`, `decision.cpp`, `cognitive_cycle.cpp`: goal lifecycle, prerequisite/deadline eligibility, intent scoring, planning context and candidate-action ranking exist. Goals are created as supplied Goal objects; cycle selects supplied ID or first eligible goal. Experience-acquired candidate-goal formation is not demonstrated. | PR #97 affective planning and developmental strategy learning influence bounded action planning/utility. PR #176 corrects D1 learned-strategy context selection and D2 non-finite goal input on donor branch. | **Partial on main; donor candidate.** Keep lifecycle/planning/decision substrate; add no hardcoded goal generator; D1/D2 corrections and remaining compensation review are mandatory donor considerations. |
| **BM-09 Learning and developmental adaptation** | `learning_loop.cpp`, `adaptation.cpp`, evolution modules: numeric prediction/outcome feedback updates estimates and fitness; proposals require confidence ≥0.75 and positive expected gain. This is narrow parameter adaptation, not broad concept, belief, causal, memory, goal or procedural learning. | PR #97 developmental strategy learning has a concrete path from contextual experience to strategy retrieval and planning-score influence, with persistence/test sources. Context hierarchy, tokenization, similarity and thresholds are engineered biases; synthetic training does not prove open-world transfer. | **Partial on main; donor candidate.** Keep evaluation/adoption controls; extend learning evidence across state owners and require persistence, future effect, transfer and regression checks. |
| **BM-10 Metacognitive monitoring and control** | Reflection, self-state and self-testing exist. Reflection reports coherence/uncertainty/prediction accuracy; self-state is partly derived from aggregate event/threat/attention/novelty/capability values. A full evidence-linked corrective loop is not demonstrated. | Donor evolution evaluation/canary/rollback controls offer useful bounded change monitoring, but do not amount to general metacognition. | **Partial on main.** Adapt from summary reporting to evidence/dependency-aware monitoring and verified correction. |
| **BM-11 Integrated coordination and continuity control** | `Brain` replays journal events; `CognitiveRuntime` has a worker queue and workspace projection; workspace store supports snapshot/replace/clear under a mutex. These are useful coordination primitives. Full cross-mechanism dependency invalidation, multi-owner conflict reconciliation and recovery validation are not demonstrated. | PR #97 evolution controller, adoption journal, canary and rollback components provide candidate controlled-change coordination. PR #176 tests several append-failure and restart boundaries but leaves deeper controller compensation verification open. | **Partial on main; donor candidate.** Preserve runtime/journal primitives; specify coherent dependency tracking, transactional boundaries and recovery validation. |
| **BM-12 General reasoning and inference** | `reasoning.hpp/.cpp`: consistency checks same-key scalar conflicts and bounded forward traversal over encoded causal links. Empty premises return `valid=true` with zero confidence. In `CognitiveCycle::run`, memories are omitted from premises and reasoning output is not consumed downstream. | No donor evidence inspected here establishes the full BM-12 premise/assumption/provenance/alternative/counterexample contract. | **Not demonstrated.** Retain narrow inference as a specialist/prototype only; BM-12 requires expanded reasoning ownership and end-to-end integration. |

### 4.1 Important integration correction: reasoning result is not a downstream capability

The main cycle's call to `ReasoningEngine::solve` does not establish that reasoning affects cognition. At the audited commit:

1. memories are retrieved into `result.context.memories`;
2. beliefs and causal links are fetched;
3. only beliefs and causal links are passed to `ReasoningProblem`;
4. the reasoning result is stored in `result.context.reasoning`;
5. later prediction, goal selection, planning and decision use other inputs.

Therefore the inspected path has neither memory-supported inference nor downstream reasoning integration. This is a direct source-level finding, not an inference from missing tests.

### 4.2 Important donor correction: affect is integrated but bounded

PR #97's affective state has identifiable downstream consumers in intent/planning and action-outcome evidence weighting. It is more than a standalone affect variable. However, this does not prove that affect modulates every cognitive mechanism, that its appraisal model is mature, or that its fixed equations represent acquired affective understanding. The correct disposition is selective donor evaluation, not rejection and not wholesale adoption.

## 5. Cross-mechanism flows and integration obligations

| Integrated behavior | Required interaction | Current evidence / gap |
|---|---|---|
| Grounded interpretation | BM-01 → BM-02, with BM-03 context and BM-06 focus | Event normalization/provider pipeline exists; broad grounded multimodal interpretation and plural ambiguity handling are not established. |
| Memory-supported reasoning | BM-03 → BM-12, informed by BM-02/BM-04/BM-05; conclusions returned to BM-04/BM-05/BM-08 | Main cycle explicitly fails this flow: memories are retrieved but not passed into reasoning; reasoning result is not consumed downstream. |
| Evidence-sensitive belief revision | BM-01/02/03/12 → BM-04; BM-11 invalidates dependents | Main key/value overwrite is too narrow; donor alternative/evidence work requires selective compatibility assessment. |
| Causal learning and prediction | BM-04/03 → BM-05; attributed BM-01 outcomes resolve predictions; BM-09 evaluates model changes | Main causal links from co-state changes are insufficient; donor contextual prediction requires held-out performance evidence. |
| Contextual attention and appraisal | BM-04/05/07/08/10 → BM-06; focus and context affect retrieval/reasoning/planning | Main attention scoring uses narrow inputs; donor affect influences planning, but full cross-mechanism modulation is not established. |
| Candidate-goal development | BM-01/02/03/04/05/07/10 → BM-08; BM-09 evaluates improvement | Main handles supplied goals and lifecycle; no inspected experience-acquired candidate-goal formation. |
| Learning that changes future behavior | Experience/outcome → attribution → BM-09 candidate → owner activation → persistence → later behavior → held-out evaluation | Main numeric adaptation is narrow; donor strategy path shows a concrete contextual learning-to-planning consumer, with engineered context biases and limited transfer evidence. |
| Metacognitive correction | BM-10 detects issue → BM-11 coordinates → relevant owner revises → BM-10 evaluates effect | Reflection/self-state summaries exist; complete corrective loop is not demonstrated. |
| Coherent interruption/recovery | BM-11 tracks work/dependencies; SYS-08 restores substrate; owners validate cognitive state | Journal replay and runtime queue exist; cross-mechanism dependency freshness and full recovery validation remain open. |
| Safe action-outcome learning | BM-08 intent/request → governance/authorization → execution → independently verified consequence → BM-01/BM-05/BM-09 | Main cognitive cycle ends at action assessment. PR #97 provides a stronger Brain-owned execution/verification/outcome path, but its integration and safety semantics require selective review. |

## 6. Learning evidence: what qualifies and what does not

The accepted specification's minimum learning chain is:

**experience → evidence-sensitive update → persistent change → later behavioral effect → evaluation in relevant and novel contexts.**

This has several implications:

- A prediction error is evidence of mismatch, not automatically evidence of its cause.
- A stored event is retention, not necessarily learning.
- A changed numeric estimate is narrow adaptation, not proof of concept acquisition or general reasoning.
- A strategy record is not useful learning unless later selection/planning actually consumes it.
- A passing test fixture demonstrates only the behavior the fixture exercises; it does not establish open-world transfer.
- A donor CTest result does not prove compatibility with the accepted specification tree.
- Learning can be observational as well as action-outcome-based; the Brain need not act first, but the evidence must still be justified and its effect persistent and testable.

PR #97 provides a stronger donor example than main in the developmental strategy path: context is derived from observation/representation features, strategies are retained and retrieved by exact or similarity-related context, and the planning consumer adjusts action utility/expected value. This is a concrete learning-to-future-decision path. But its engineered context hierarchy, tokenization, similarity and thresholds create inductive biases; PR #176's D1 correction is required to prevent a mismatched goal context. Its synthetic training evidence is not sufficient to claim general transfer.

The numeric adaptation path in main and contextual prediction donor path should be retained as narrow capabilities, not elevated into the whole learning architecture.

## 7. Cross-cutting architectural risks

1. **State authority drift:** multiple mechanisms or donor branches may own overlapping representations unless each authoritative state and update contract is reconciled.
2. **Evidence promotion:** scalar event attributes and model outputs can be treated as facts without explicit provenance, scope and epistemic transitions.
3. **False causality:** co-state transitions and strength thresholds can turn correlation into causal-looking predictions.
4. **Disconnected cognition:** workspace population can hide missing downstream consumption.
5. **Stale dependent state:** belief, memory, goal or strategy changes may leave predictions/plans/conclusions active without invalidation.
6. **Hardcoded priors disguised as learning:** fixed thresholds, feature hierarchies, decay constants, tokenizers and action score weights may be useful bootstrap biases but must remain visible, bounded and revisable.
7. **Learning interference:** local gains can damage unrelated strategies, goals, beliefs or contexts unless regression and held-out evaluation are explicit.
8. **Persistence overclaim:** event journaling and replay do not by themselves establish authenticated memory, crash consistency for every owner, or coherent reconstruction of all derived state.
9. **Substrate/cognition confusion:** runtime/storage success must not be accepted as semantic state validation.
10. **Action/outcome confusion:** intent, authorization, execution and verified consequence must remain separate evidence classes.
11. **Authority and donor drift:** PR #156/PR #97/PR #176 and planning PRs are candidate evidence, not accepted implementation baselines. Gate A remains NOT CLEARED.
12. **Unfinished F-02/F-03 obligations:** contextual language/operator-intent grounding and downstream reasoning integration must be corrected in the specification before affected requirements are relied upon for implementation.

## 8. Human cognition and MCU JARVIS comparison: functional lessons, not literal templates

The comparison must evaluate functional capabilities and interactions rather than copy fictional or biological implementation details.

### Human cognition: useful functional reference

- Multiple partially specialized processes operate concurrently and recurrently rather than as one fixed pipeline.
- Perception is contextual and revisable; memory can bias interpretation, and new evidence can revise remembered meaning.
- Working context is limited, attention is selective, and long-term memory is not identical to active awareness.
- Beliefs, predictions, causal understanding, goals and strategies are shaped by experience and can be revised.
- Affect/valuation influences attention, memory and decisions without being equivalent to a factual belief or an execution command.
- Metacognitive monitoring can detect uncertainty and limitations, but is imperfect and bounded.
- Learning includes observational, associative, procedural and action-outcome pathways, with interference and forgetting as real risks.

JARVIS should reproduce useful functional principles where justified, not assume that human mechanisms or biases are optimal. Human-like capability claims require their own evidence.

### MCU JARVIS: useful functional reference

- Integrated perception, contextual memory, reasoning, planning, communication and action coordination.
- Continuous situational awareness with the ability to interrupt and reprioritize.
- Use of prior context and evidence to inform later decisions.
- Separation between proposing an action and executing it through suit/device/system interfaces.
- Coordination across tools and physical/digital substrate while maintaining a coherent system identity.

MCU JARVIS is fictional and cannot serve as empirical proof of an architecture or learning algorithm. It is a capability/interaction reference, not a source of implementation facts. Its apparent competence must not be translated into hardcoded omniscience, unrestricted authority or unsupported autonomy.

## 9. Dependency and sequencing implications (not an implementation plan)

The investigation implies the following dependency order for future architecture closure, not a coding sequence:

1. Resolve evidence/provenance, epistemic status and state-ownership semantics across all mechanisms.
2. Establish grounded representation and context/memory contracts.
3. Resolve belief alternatives/revision and scoped causal/prediction semantics.
4. Define BM-12 reasoning inputs, lineage and consumer contracts; close F-02/F-03.
5. Define attention/affective modulation and goal/decision interactions without fixed behavior mappings.
6. Establish BM-11 dependency freshness, concurrency, interruption and recovery contracts.
7. Define BM-09 learning attribution, candidate evaluation, owner-mediated activation, persistence, transfer and rollback across state classes.
8. Only then determine whether a proposed implementation baseline and port set satisfy the integrated specification.

These dependencies are not strictly serial: several can be investigated in parallel. Their semantic contracts must converge before implementation can safely integrate them.

## 10. Unresolved questions and evidence required next

- Which exact source/build target memberships explain the affective/developmental API discrepancy in main?
- Which donor branches beyond selected PR #97 paths supply evidence-compatible mechanisms, and how do their state/event contracts differ from main?
- What exact source paths persist and replay each authoritative state owner, and which derived states are rebuilt versus trusted?
- Which workspace/runtime outputs are actually consumed by later cycles, and what guarantees exist for multiple concurrent contexts?
- How are prediction outcomes attributed when execution, sensors or external providers fail or return partial evidence?
- Which learning changes are applied to cognitive content versus numeric parameters, and how are cross-owner changes coordinated atomically or recoverably?
- Which test targets exercise full integrated behavior rather than isolated APIs, and which exact CI runs correspond to the relevant commits?
- What is the measured transfer and regression performance of donor developmental learning on held-out, non-synthetic contexts?
- What mechanism owns contextual language grounding and operator-intent disambiguation (F-02), and how does BM-12's output materially affect downstream belief, prediction, goal and plan processes (F-03)?

Required future evidence must include exact source-to-consumer traces, registered test targets, restart/replay assertions, failure injection, baseline comparisons, held-out contexts, regression checks and observable downstream behavioral effects. No single test score or code-size metric is sufficient.

## 11. Scope limits and gate status

This report is a source/document integration map based on the exact revisions listed above. It is not an exhaustive line-by-line review of all 200 main files, all 159 PR #97 changed paths, every donor branch or every test. It does not claim to have run or reproduced CI. It does not certify runtime behavior.

- No runtime source, tests, dependencies or build configuration were changed.
- No donor PR was merged or selected as the implementation baseline.
- No build, runtime test, benchmark, sanitizer or workflow was executed.
- No algorithm, language, framework, database, schema, API or runtime topology was selected.
- No implementation or deployment is authorized.
- PR #175 Gate A remains **NOT CLEARED**; Gate B capability acceptance remains **NOT PASSED**.
- PR #176 remains a donor correction branch; deeper controller compensation verification remains open.
- PR #178 governance remains proposed until exact-revision owner acceptance.
- Phase 1 historical preservation/documentation follow-up remains open and is not silently closed by this report.

**Phase 2 result:** the repository has a reusable cognitive substrate and meaningful donor mechanisms, but the central requirement is to integrate their evidence, state, feedback and learning paths into one coherent Brain. The current main cycle does not yet demonstrate that integration. The next gate is independent technical challenge of this map and resolution of its explicit evidence gaps—not implementation by default.
