# Cross-Baseline Inherited Mechanism Compatibility Inventory — 2026-11-15

## 1. Authority, purpose and decision boundary

**Controlling Project Director decision:** CF-26 Option A, accepted on 2026-11-15 in the current project conversation. The Builder is directed to complete an architectural compatibility inventory across the approved engineering baselines, assign evidence-backed mechanism dispositions, and identify owned remediation/evaluation specifications.

**Architecture target:** PR #173, branch `architecture/brain-foundation-planning-20261103`, exact HEAD `a8be408921afaa7a417cc972e891155bbcd11d19`.
- Architecture document blob: `50b5c6e471df797d490b314c542e8d2bdce71c42`.
- Completion/decision matrix blob: `9938fa331e06c91cce15e33fa6bd97d613ea9659`.

**Compared engineering source baselines:**
1. PR #171 reviewed whole-system package HEAD `b05434758ad4fe72815503f89bd5d2990ccb658b`.
2. PR #172 accepted investigation's engineering-evidence baseline: `main` at `1273ddbcd0087d189e01388ded2d362fb1e058d2`.
3. PR #97 donor branch HEAD `c1da222e6c94aeb3f2ad000392c21fe4fc81ab25` (open, draft, unmerged at the time of the source inventory).

PR #171 and PR #172 engineering source trees have identical Git blob identities across the 166 paths in the inspected core source/header/test scope. PR #97 is therefore compared against that shared baseline. The PR #172 accepted research document remains the approved investigation authority; its engineering code baseline is the exact `1273...` revision above, not an inferred later main state.

**Scope of the file-level census:** every tracked file under:
- `core/cpp/src/`
- `core/cpp/include/jarvis/core/`
- `core/cpp/tests/`

The union contains **209 paths**: **166 shared-baseline paths** (the PR #171 and PR #172 engineering trees have identical blobs for these paths) plus **43 PR #97 donor-only paths**. Within the 166 shared paths, the PR #97 donor has **81 identical** and **85 modified** blobs; together with the 43 donor-only paths this yields the 209-path union. There are no baseline-only paths in this scoped union. The exact source manifest in §8 contains one row for each of the 209 union paths; the number 166 describes the shared baseline subset, not the manifest total. This is a complete path/blob census for those three directories at those exact revisions. It is not a claim that every repository directory, historical branch, external consumer, binary, dataset or deployment artifact was audited.

**No runtime authorization:** this is architecture/source-planning work only. No source code, tests, workflows, dependencies, schemas, runtime state, technology choices, branch history, merge state or deployment were changed or authorized by this report.

## 2. Method and evidence standard

The file census uses recursive Git trees at the exact revisions and records each path's blob SHA below. The mechanism review combines:
- the existing line-level audit of reliability metadata, thresholds, goal selection/context coupling, learning-rate parameterization and belief overwrite;
- direct inspection of the donor's new affective, developmental-learning, experience-memory, developmental-environment/world and Brain integration paths;
- the approved PR #171/PR #172 architectural boundaries and the PR #173 CF-01–CF-27 completion obligations;
- relevant test source as evidence of intended assertions and test coverage only.

**Test-source caveat:** test files are inventoried, but no tests or builds were executed as part of this documentation audit. A test assertion is not a passing test result, and a green historical workflow is not proof that every mechanism works or is architecturally compatible.

Disposition meanings:
- **PRESERVE:** retain the capability/role and its evidence lineage, subject to the architecture's existing contracts.
- **ADAPT:** retain the useful mechanism but change its semantics, evidence discipline, ownership, calibration or failure behaviour before adoption.
- **REPLACE:** the current semantic mechanism conflicts with an accepted foundational contract and needs a different mechanism.
- **RETIRE:** remove only when a mechanism is demonstrably redundant, unsupported or unsafe and replacement coverage is established. No current mechanism is assigned RETIRE solely on the evidence in this inventory.

## 3. Cross-baseline mechanism disposition register

| Mechanism family | Source evidence inspected | Disposition | Compatibility finding and required treatment |
|---|---|---|---|
| Cognitive event journal, memory persistence and replay | `memory.cpp/.hpp`, `brain.cpp`, `cognitive_runtime.cpp`; persistence and replay suites | **PRESERVE + ADAPT** | Retain the event-journal/reconstruction capability and replay validation. Adapt it to the accepted epistemic lifecycle: event time vs processing time, source/provenance, idempotent replay, versioned owner state, explicit partial-recovery status and no invented missing history. Journal persistence is not by itself semantic truth. |
| Perception, representation, knowledge and reasoning | `perception_pipeline`, `representation`, `knowledge`, `reasoning`, their headers and architecture suites | **PRESERVE + ADAPT** | These are existing cognitive capabilities in both source baselines, not disposable legacy. Preserve their roles while requiring candidate interpretations, provenance, ambiguity, evidence/assumption separation and cross-mechanism delivery. Structured attribute overlap or a successful fixture must not be described as generalized grounding. |
| Episodic and prediction-linked experience memory | `experience_memory.hpp` (donor-only); `memory`, prediction feedback and memory suites | **ADAPT** | The donor helper separates semantic key from individual prediction sequence and supports unresolved/resolved lookup. Its in-memory maps are not independently durable, and `record_prediction` can append the same sequence to the per-key index more than once if called repeatedly. Treat the helper as a useful index/association mechanism, not the authoritative memory store; require idempotency, provenance, retention and reconstruction through the authoritative journal. |
| Prediction and contextual matching | `brain_prediction_context.cpp`, `cognitive_runtime.cpp`, prediction feedback suite | **PRESERVE + ADAPT** | Preserve prediction identity and explicit outcome resolution by sequence. Adapt contextual candidate selection: the inspected path takes `matches.front()` when matches exist, so candidate ordering can become semantic selection. Require explicit ranking/ambiguity handling, dependency lineage, delayed/out-of-order outcome matching and unresolved state where no valid match exists. |
| Source reliability and evidence confidence | Existing targeted audit: `knowledge.cpp/.hpp`, `brain.cpp`, memory code and relevant tests | **ADAPT** | Production assimilation averages caller-supplied reliability metadata; correctness scoring was not found wired into the inspected production paths. Keep raw evidence and provenance, but do not call this calibrated source trust. A later specification must separate source competence from evidence reliability and define domain/task/time scope, independent outcome scoring, sample uncertainty, drift and unknown-source behaviour. |
| Numeric thresholds and fixed learning-rate schedule | `decision.hpp/.cpp`, `developmental_learning.hpp/.cpp`, `brain.hpp`, prediction/context paths | **ADAPT** | There is no single universal confidence cutoff. Action-score, risk/escalation, similarity, retention, minimum-strength and confidence-prior values have different semantics. The weighted learning-rate equation and 0.05–0.95 clamp are engineered parameters, not acquired behaviour. Inventory each parameter by objective, owner, consequence, version, calibration and error costs; evaluate sensitivity, transfer and regression before adoption. |
| Goal model, intent selection and strategy context | `goals.cpp/.hpp`, `cognitive_cycle.cpp`, `brain_affective_planning.cpp`, `brain_restored_api.cpp`, `brain_action_execution.cpp` | **PRESERVE goal state; REPLACE general first-eligible selection/context coupling** | Retain explicit goal lifecycle and intent modelling. Replace `eligible.front()` as a general cognitive fallback and eliminate strategy context chosen independently from the selected intent. Candidate evaluation must be evidence/constraint/feasibility-aware; no-intent or unresolved selection must remain explicit. Any emergency fallback must be a separately authorized operational policy, not learned preference. |
| Belief and world-model revision | `brain.cpp`, `world_model.cpp/.hpp`, `reasoning.cpp`; targeted audit | **REPLACE semantic last-write-wins** | The authoritative belief map overwrites the previous value before marking dispute; action-status beliefs are also replaced. WorldModel retains some conflicting incoming facts but does not preserve a complete versioned claim history in every replacement path. Replace this semantic contract with versioned claims, competing alternatives, provenance, scope/time, explicit supersession rationale and dependent-state invalidation. Preserve raw event history separately. |
| Developmental association and strategy learning | `developmental_learning.hpp/.cpp`, `association_model`, Brain integration and developmental learning suites | **PRESERVE + ADAPT** | Preserve the experience-to-association/strategy feedback capability as a candidate learning mechanism. Adapt the fixed weighted learning-rate coefficients, reliability scaling, similarity transfer, consolidation and context selection through explicit evaluation. Distinguish strategy evidence from verified real-world consequence and prevent a single repeated fixture from proving general transfer. |
| Affective state and appraisal learning | Donor-only `affective_state.hpp/.cpp`, `affective_learning.hpp`, `brain.cpp`, `brain_affective_planning.cpp`, affective tests | **PRESERVE + ADAPT** | Preserve continuous appraisal dimensions and experience-updated appraisal weights as candidate mechanisms; they do not encode named emotion-to-action rules in the inspected path. Adapt fixed initial weights, fixed integration/decay coefficients and engineered transforms. In particular, the inspected runtime derives affect from supplied fields and maps goal progress into a signed outcome; these are provisional input semantics, not discovered universal emotional laws. Require evidence calibration, context scope, persistence/replay, sensitivity, counterexamples and tests against hidden fixed behavioural mappings. |
| Action execution and consequence feedback | `action_execution.cpp`, `brain_action_execution.cpp`, `developmental_environment.hpp`, action/consequence integration suites | **PRESERVE + ADAPT** | Preserve the strict separation between request, execution evidence and observed consequence. The developmental environment correctly treats execution failure as no consequence observation. Adapt fixed execution-status reliability values (0.75/0.25/0.0) and ensure negative execution evidence updates capability/strategy reliability without being mislabeled as negative environmental consequence. Governance authorization remains external to the Brain. |
| Developmental environment and world | Donor-only `developmental_environment.hpp`, `developmental_world.hpp`, world/environment tests | **PRESERVE as controlled training/test substrate; ADAPT boundary** | The world owns task state and transition functions; the Brain receives observations, with optional partial-observation filtering. Preserve this separation for controlled developmental trials. Do not equate simulated transitions with real-world experience or allow hidden world state/transition code to leak into Brain evidence. Verify seed control, observation leakage, action failure, exogenous changes, resource limits and reproducible episode lineage. |
| Evolution and parameter experimentation | Evolution controller/orchestrator/canary/sandbox/journal/runner source and tests | **PRESERVE + ADAPT** | Retain isolated candidate evaluation, evidence records, canary/rollback and adoption lineage as bounded engineering mechanisms. Do not equate parameter optimization with broad cognitive learning, conceptual acquisition or self-directed architecture modification. High-impact activation remains subject to the accepted governance and Director boundaries; process isolation and a passing experiment do not grant authority. |
| Attention, reflection, self-model and causal modelling | `attention`, `reflection`, `self_model`, `causal_model`, cognitive workspace and associated tests | **PRESERVE + ADAPT** | Retain the existing responsibilities. Require explicit state ownership, evidence-qualified estimates, dependency invalidation and verified cross-mechanism influence. Attention scores and self-estimates are not truth; causal links are hypotheses unless supported by independent evidence. Do not treat source presence or test names as proof of integration completeness. |
| Social/agent representation | PR #171/PR #172 architecture and PR #173 CF-17/§31; no complete dedicated mechanism established by this scoped source inventory | **DEFER as an owned specification; do not claim implemented** | The architecture's minimum claim-ownership contract remains authoritative. Detailed social/agent representation belongs to the separately owned specification; absence of a dedicated implementation in this inventory is not grounds to invent one or retire the requirement. |
| Mechanism retirement | Complete scoped file/blob census plus the mechanism findings above | **No RETIRE disposition justified yet** | No unique mechanism was shown to be wholly redundant or to have a fully verified replacement. Where semantics conflict, replace the specific contract (e.g. belief overwrite), not necessarily the entire source module. Retirement requires explicit dependency and replacement-coverage evidence. |


### 3.1 Targeted source evidence anchors

The following 1-based line ranges are direct inspection anchors at the exact PR #97 donor revision `c1da222e6c94aeb3f2ad000392c21fe4fc81ab25`. Each row supplies the source blob SHA so a reviewer can reproduce the evidence independently. These are targeted anchors for the dispositions above, not a claim that the listed lines exhaust every use site in the repository.

| Mechanism finding | Exact donor source path | Blob SHA | Relevant lines | What the lines establish |
|---|---|---|---:|---|
| Event journal append and replay/reconstruction | `core/cpp/src/memory.cpp` | `ab42bba1d32d6f48d091787491c72294a4a55bb5` | 33–35 | Journal initialization, persisted append, ordered replay and reconstruction of continuity/metadata |
| Prediction experience index and duplicate append risk | `core/cpp/include/jarvis/core/experience_memory.hpp` | `28cce354eb9db7e8ca292746fd14649debb7ab04` | 28–38 | Prediction identity is indexed by sequence, while each call appends to the per-key sequence vector |
| Contextual prediction first-match selection | `core/cpp/src/brain_prediction_context.cpp` | `b3ceff150f3fe8223dc3f76f4c298ac264d72dae` | 68–72 | Generalized candidates are obtained and `matches.front()` supplies the selected context |
| Caller-supplied source reliability averaging | `core/cpp/src/knowledge.cpp` | `21de8abbcd4426cb4ead70cb089e7d7c4ed0e81a` | 8–19 | Incoming reliability metadata is clamped and averaged into the source metric |
| Reliability fallback and affective signal consumption | `core/cpp/src/brain.cpp` | `dec9e5442b3ca4b81a7879855c6146b2619934cc` | 245–271 | Action-outcome reliability falls back through evidence/reliability metadata to a fixed 0.5 default and is consumed as signal confidence |
| General first-eligible goal fallback | `core/cpp/src/cognitive_cycle.cpp` | `f191dd610d6cbe1621756c35e7c13af2054a7266` | 118–137 | Goal selection returns the first eligible candidate when no explicit selection resolves it |
| Independent first-eligible strategy-context coupling | `core/cpp/src/brain_affective_planning.cpp` | `2a9406257c23f3a66a64071842be7d6448799406` | 96–107 | Affective planning derives context from the first eligible goal independently of the selected intent |
| Fixed learning-rate equation and clamp | `core/cpp/src/developmental_learning.cpp` | `dbf5f43271dfa0a3c57236e2faa82eb88d15490d` | 250–269 | Learning rate is a fixed weighted combination of error/reward/salience/novelty/uncertainty, clamped to 0.05–0.95 and scaled by reliability |
| Inherited affective parameter defaults and transforms | `core/cpp/include/jarvis/core/affective_learning.hpp` | `fa06043dc481336ba544247f365d37f5476a0651` | 13–17, 60–91 | Affective weights have fixed initial values and are applied by deterministic transforms in the inherited model |
| Fixed execution-status reliability values | `core/cpp/src/brain_action_execution.cpp` | `3b66bafb438cd28790e6f25611b96c86f1eff05c` | 62–95 | Execution status maps to 0.75/0.25/0.0 and is persisted separately from evidence reliability |
| Belief/world-model conflict replacement | `core/cpp/src/world_model.cpp` | `5b68e8fe37d99732557237e347ae02234a3de172` | 11–33 | Existing facts are updated and disputed evidence is recorded; a higher-confidence incoming fact can replace the current fact |
| Developmental-world observation boundary | `core/cpp/include/jarvis/core/developmental_environment.hpp` | `913c8cca2a03499249b834a890812c57b9aa4b1a` | 14–16, 67–75 | Brain receives observations rather than transition functions; failed execution does not itself create consequence evidence |
| Representation provenance and confidence initialization | `core/cpp/src/representation.cpp` | `054bd9ecee3ef3da83dd405dc5785464d874fa21` | 28–76 | Confidence is read from event metadata or modality-specific defaults; evidence spans retain source and event sequence |
| Reasoning premise handling | `core/cpp/src/reasoning.cpp` | `18bf2facc9f95c6bd2e8d9a559a0e5b1c5ae06e1` | 31–45 | Reasoning consistency and inference operate over the supplied belief-premise vector |
| Bounded evolution experiment recording | `core/cpp/src/evolution_controller.cpp` | `4e77ec2e5daa09a964132ca486b8c5ee1cebf2f5` | 15–48 | Candidate experiment evidence is validated and appended to the evolution history with replay-aware persistence handling |

**Interpretation limit:** these anchors demonstrate the cited inherited mechanisms and their concrete code locations. They do not prove that the donor code is approved for adoption, that every consumer was audited, or that any later implementation has been corrected. The architecture and seven CF-26 specifications govern the required future treatment; runtime remediation remains separately unauthorized.

## 4. CF-01–CF-27 coverage crosswalk for mechanism dispositions

This crosswalk connects each mechanism family in §3 to the architectural capability obligations it informs. It is a traceability index, not a claim that the mechanisms are implemented, compatible as-is, or sufficient to close a CF obligation. A CF obligation may depend on several mechanism families, and a family may affect several obligations. The authoritative capability status remains in PR #173's completion matrix §3 and §20.

| Mechanism family in §3 | Related CF obligations | Why the relationship matters |
|---|---|---|
| Cognitive event journal, memory persistence and replay | CF-01, CF-04, CF-05, CF-10, CF-14, CF-21, CF-24, CF-25 | Continuity, episodic retention, belief lineage, learning persistence, self-monitoring, substrate recovery and evidence reconstruction |
| Perception, representation, knowledge and reasoning | CF-02, CF-03, CF-05, CF-08, CF-16, CF-17, CF-22 | Acquisition boundaries, grounded representation, qualified knowledge, inference, symbolic input, agent claims and information access |
| Episodic and prediction-linked experience memory | CF-04, CF-07, CF-09, CF-10, CF-25 | Experience retention, prediction linkage, simulation separation, learning evidence and replay verification |
| Prediction and contextual matching | CF-05, CF-07, CF-08, CF-09, CF-10, CF-15, CF-25 | Evidence-linked prediction resolution, reasoning context, simulation separation, learning feedback, coordination and verification |
| Source reliability and evidence confidence | CF-02, CF-03, CF-05, CF-07, CF-08, CF-25 | Acquisition provenance, grounding, belief qualification, prediction matching, inference and calibration evidence |
| Numeric thresholds and fixed learning-rate schedule | CF-10, CF-12, CF-13, CF-14, CF-23, CF-25 | Learning eligibility, affective calibration, decision consequences, metacognitive estimates, developmental progression and evaluation |
| Goal model, intent selection and strategy context | CF-11, CF-12, CF-13, CF-19, CF-22 | Goal origin/competition, valuation, planning/decision, internal-condition inputs and governance constraints |
| Belief and world-model revision | CF-05, CF-07, CF-08, CF-10, CF-15, CF-24, CF-25 | Claim lifecycle, prediction assumptions, inference, learning updates, dependency coordination, recovery and verification |
| Developmental association and strategy learning | CF-08, CF-10, CF-11, CF-12, CF-13, CF-23, CF-25 | Reasoning strategy, adaptation, goal/valuation effects, decision influence, developmental evidence and regression |
| Affective state and appraisal learning | CF-10, CF-11, CF-12, CF-13, CF-19, CF-20, CF-23, CF-25 | Experience-dependent calibration, goal relevance, affective appraisal, decision influence, internal conditions, optional modulation boundary and developmental verification |
| Action execution and consequence feedback | CF-18, CF-22, CF-24, CF-25 | Intention/execution/outcome separation, governance, failure semantics and evidence |
| Developmental environment and world | CF-02, CF-10, CF-18, CF-23, CF-24, CF-25 | Observation boundary, controlled learning, action feedback, developmental stages, failure injection and reproducibility |
| Evolution and parameter experimentation | CF-10, CF-14, CF-23, CF-24, CF-25, CF-27 | Adaptation governance, self-monitoring, developmental claims, rollback/recovery, evaluation and decision authority |
| Attention, reflection, self-model and causal modelling | CF-06, CF-08, CF-09, CF-14, CF-15, CF-24, CF-25 | Context selection, inference, simulation, metacognition, coordination, failure response and verification |
| Social/agent representation | CF-03, CF-05, CF-16, CF-17, CF-22 | Grounded entity claims, attributed beliefs, language reports, social modelling and privacy/security |
| Mechanism retirement and replacement coverage | CF-10, CF-15, CF-24, CF-25, CF-26, CF-27 | Safe adaptation, dependency impact, recovery, replacement evidence, compatibility disposition and reserved approval |

**Coverage check:** the union of the CF references in this table is CF-01 through CF-27. The table deliberately does not label any CF item CLEAR: the mapping identifies relevant evidence families, while closure still requires the owned remediation/evaluation specifications, objective evidence and the independent/Project Director gates in the completion matrix. In particular, CF-26 remains OPEN overall and CF-27 retains its separate decision-governance gate.

## 5. Required remediation/evaluation specifications

The following are the next owned specification outputs. They do not authorize runtime implementation.

| Priority | Specification | Minimum required content | Accountable owner | Evidence required before later adoption |
|---|---|---|---|---|
| 1 | Versioned belief/claim revision | Claim identity, provenance, temporal/context scope, competing values, promotion/suspension/supersession, dependency invalidation, concurrent updates and replay/recovery | Architecture & Engineering Builder | Contradiction, delayed evidence, concurrent writer, restart and rollback scenarios; no lost alternatives |
| 2 | Goal/intent selection and context identity | Candidate-set evaluation, selected-intent identity, context binding, unresolved/no-intent semantics, safe external fallback boundary | Architecture & Engineering Builder | Candidate permutation, conflicting goals, stale evidence, no eligible goal and budget-exhaustion cases |
| 3 | Evidence reliability and numeric parameter governance | Source vs evidence reliability, independent scoring, calibration, uncertainty, drift, threshold objectives, learning-rate versioning | Architecture & Engineering Builder | Held-out calibration, domain/time transfer, sensitivity, false-positive/negative costs and regression |
| 4 | Affective appraisal semantics and calibration | Input provenance, outcome-vs-surprise distinction, goal-progress interpretation, appraisal parameter ownership, persistence/replay and limits | Architecture & Engineering Builder | Counterfactual/variation tests, calibration against independently verified outcomes, no fixed emotion/action mapping |
| 5 | Prediction-context resolution | Candidate scoring, ambiguity, temporal alignment, sequence matching, stale context and dependency invalidation | Architecture & Engineering Builder | Multiple matching contexts, reordered candidates, delayed/out-of-order outcomes and unresolved cases |
| 6 | Action and developmental-world evidence contracts | Request/execution/outcome separation, environment observability, failure semantics, hidden-state isolation and episode lineage | Architecture & Engineering Builder | Execution failure without consequence, unknown outcome, partial observation, exogenous changes and replay |
| 7 | Learning/evolution integration boundary | Distinguish association, strategy, parameter adaptation and broad cognitive capability; candidate eligibility, risk, canary, rollback and authority | Architecture & Engineering Builder | Persistence, variation, transfer, unrelated regression, interrupted activation and rollback evidence |

Project Director approval remains required if a specification changes foundational cognitive authority, scope, governance, mandatory subsystem status or high-impact learning authority. Routine algorithm and data-structure choices remain delegated only within the accepted architecture.

## 6. Disposition of the Director's decision and previously accepted decisions

CF-26 Option A is the controlling instruction for this inventory. It does not supersede, reopen or narrow the Project Director's prior acceptance of BFA-C01–BFA-C14 (PR #173 comment #6894239520). Those fourteen decisions remain accepted as written.

This report does not accept the whole Brain Foundation Architecture, close CF-26, close CF-27, satisfy independent review, authorize Stage A, authorize implementation or testing, select technology, authorize merge or deployment, or change branch history.

CF-27 remains a separate decision-governance obligation: the Builder maintains the exact-revision ledger; the Project Director retains the reserved decision authority. No new reserved architecture decision is inferred from Option A.

## 7. Completion status and limitations

**Completed by this report:**
- exact three-revision source-baseline identification;
- complete file/blob census for the scoped C++ source, core-header and test directories;
- 209-path lineage comparison (81 identical, 85 modified, 43 donor-only);
- mechanism-family dispositions with source evidence and explicit compatibility treatment;
- owned remediation/evaluation specification list.

**Still open:**
- independent challenge of this inventory and the exact PR #173 revision;
- completion of the seven remediation/evaluation specifications;
- execution of the appropriate later tests only after their separate authorization;
- CF-27 decision ledger completion;
- overall independent architecture clearance and Project Director acceptance of the exact final architecture revision.

The inventory is exhaustive at the file/blob level for the stated paths and revisions, not a proof that every function in every source file has been exhaustively verified. Any mechanism not directly evidenced here remains unapproved for reuse merely by association with an inventoried file. No tests/builds were executed during this documentation-only pass.

## 8. Exact source manifest

The baseline columns for PR #171 and PR #172's engineering-evidence revision are identical for every path in this scoped union. The manifest therefore records one shared baseline blob and the PR #97 donor blob. The manifest has 209 path rows: 166 rows have a shared-baseline blob and 43 rows are donor-only. An em dash means the path did not exist at that revision. The donor lineage column partitions the 209 rows into 81 IDENTICAL, 85 MODIFIED and 43 DONOR-ONLY; these categories sum to 209.

| Path | PR #171 / PR #172 evidence blob | PR #97 donor blob | Lineage |
|---|---|---|---|
| `core/cpp/include/jarvis/core/action_authorization.hpp` | 047f3f8d74c8558255750fbe14d29f7ae9153360 | 047f3f8d74c8558255750fbe14d29f7ae9153360 | IDENTICAL |
| `core/cpp/include/jarvis/core/action_execution.hpp` | 38ff7033e7621db8f05cc1edc4bf59cb899ccdd3 | 04c73d02bdd4e1154be142dfeb024fc07ad432f8 | MODIFIED |
| `core/cpp/include/jarvis/core/action_model.hpp` | 6a3b1720d5b58630faf320ba1e3c082cb417b7a9 | a4e67038e57eb7637e53a532b8da62f2d0f68727 | MODIFIED |
| `core/cpp/include/jarvis/core/adaptation.hpp` | 9a2bb897a120f7585286481a6138dc9cb767ac30 | dec808ad879c9d1e7afc3adb3ae777ee611fadb7 | MODIFIED |
| `core/cpp/include/jarvis/core/affective_learning.hpp` | — | fa06043dc481336ba544247f365d37f5476a0651 | DONOR-ONLY |
| `core/cpp/include/jarvis/core/affective_state.hpp` | — | f63da2e0060938864bf434012d0b3b4d74fa5f29 | DONOR-ONLY |
| `core/cpp/include/jarvis/core/association_model.hpp` | faa835175cfd6c2fdc1d4561269edb8ab406c689 | 9890f4e0178200acada0f43a5626be6f6daa6cce | MODIFIED |
| `core/cpp/include/jarvis/core/attention.hpp` | c7e8ab0c5430d5c942fe314d928400f769c0a77c | bc3f97b79664e433fed5bca07b24a6b94dbec1d3 | MODIFIED |
| `core/cpp/include/jarvis/core/attention_state.hpp` | 8f16c4f454db0e1bbb4cdffc711ebcee5e34c637 | 8f16c4f454db0e1bbb4cdffc711ebcee5e34c637 | IDENTICAL |
| `core/cpp/include/jarvis/core/brain.hpp` | 8268ef84e0b361ead536724ba7761904b30ee58f | 671186f4c39879a182f9e511394fc564d86f2988 | MODIFIED |
| `core/cpp/include/jarvis/core/capability_evaluator.hpp` | a8a5c03ce3feee03e0e4ad68fb65376248e5939c | a8a5c03ce3feee03e0e4ad68fb65376248e5939c | IDENTICAL |
| `core/cpp/include/jarvis/core/capability_execution.hpp` | d2835c4e77b4b672422eaf4ef024d23a7d2eafc9 | d2835c4e77b4b672422eaf4ef024d23a7d2eafc9 | IDENTICAL |
| `core/cpp/include/jarvis/core/capability_registry.hpp` | 3f762bf8a57c75fbfb9f976f9a82cdea8d9cca9a | 3f762bf8a57c75fbfb9f976f9a82cdea8d9cca9a | IDENTICAL |
| `core/cpp/include/jarvis/core/causal_link_codec.hpp` | — | a6286281e4b22564a39e02a7e38a778bb81042f0 | DONOR-ONLY |
| `core/cpp/include/jarvis/core/causal_model.hpp` | f740bdf222b3309b13f0c2f541c97448fc05da3e | a6bf02cf75c6f55fa47120c772aad9c77fa40cf1 | MODIFIED |
| `core/cpp/include/jarvis/core/cognition.hpp` | e9aec6461351db42c77ff8414a175ce4c5eea33e | 92febfa5d5feab45de1a3a19fe37282852898e6c | MODIFIED |
| `core/cpp/include/jarvis/core/cognitive_cycle.hpp` | 28e7af98327956268a769adf7813125be842c1a2 | eed8bc75f59557c255e796343d77498d90b31ea5 | MODIFIED |
| `core/cpp/include/jarvis/core/cognitive_goal_outcome.hpp` | — | c986480d82b9951177031f3387169819c3856234 | DONOR-ONLY |
| `core/cpp/include/jarvis/core/cognitive_runtime.hpp` | d02b2607cebcb7c31963e2fe336970707a481e00 | e5a3c853add8b5fcb9b8c04c9b25f20179b5b629 | MODIFIED |
| `core/cpp/include/jarvis/core/cognitive_trigger.hpp` | be1e33d11ebbea1e4dff685fd04b29fbb5324141 | be1e33d11ebbea1e4dff685fd04b29fbb5324141 | IDENTICAL |
| `core/cpp/include/jarvis/core/cognitive_workspace.hpp` | b015d44e332ea2511d29e607495714d0b982d44e | e002025dd69183311b41afa9d57c2b0780b7f7f8 | MODIFIED |
| `core/cpp/include/jarvis/core/decision.hpp` | 7dd9d6b7337311868d236dc0ced81f558200ab1a | 88ee24e6dc93826759de46b38d15a08a685a3aac | MODIFIED |
| `core/cpp/include/jarvis/core/developmental_environment.hpp` | — | 913c8cca2a03499249b834a890812c57b9aa4b1a | DONOR-ONLY |
| `core/cpp/include/jarvis/core/developmental_learning.hpp` | — | e3b9bf8af265b67829fd7deb323d88a3a9dd4b75 | DONOR-ONLY |
| `core/cpp/include/jarvis/core/developmental_world.hpp` | — | 2ba5bdbfc6db1f24eff8eb0a20ee145d0efc16cf | DONOR-ONLY |
| `core/cpp/include/jarvis/core/event.hpp` | a31db633e8181378fcec0a20c5958c0065d430ee | a31db633e8181378fcec0a20c5958c0065d430ee | IDENTICAL |
| `core/cpp/include/jarvis/core/evolution.hpp` | 736876b339846e0ad4da62854a206712e79a201b | 907cdf538671ad600c498b60b74a2281853b9076 | MODIFIED |
| `core/cpp/include/jarvis/core/evolution_adoption.hpp` | 46e50e77190dd939db85dfe673da462061acdfe4 | 46e50e77190dd939db85dfe673da462061acdfe4 | IDENTICAL |
| `core/cpp/include/jarvis/core/evolution_adoption_journal.hpp` | f902abfc65d705e15b6b9c8690f8e023f55afacc | 289e4dd74ad6646d0fd9c2b77645722c2aa3f3fe | MODIFIED |
| `core/cpp/include/jarvis/core/evolution_canary.hpp` | 46ca0938caf1b27b1ea804f1b5ea795683ab0ef0 | 9a2e2966a242df345ebb778e78b69b7db90dc502 | MODIFIED |
| `core/cpp/include/jarvis/core/evolution_candidate_generator.hpp` | a68ce0cec079854e07fe09a14844ac54354f501f | a68ce0cec079854e07fe09a14844ac54354f501f | IDENTICAL |
| `core/cpp/include/jarvis/core/evolution_controller.hpp` | e06441d23685093a3c533498a09adf3a8baf5914 | c1af30f84f03d87d151fe3c5fbfd89ef39fbe34e | MODIFIED |
| `core/cpp/include/jarvis/core/evolution_experiment.hpp` | 53bcd379fb788a3b0c369309c328f70d56f051ba | 551d0d41b19abbeca425d102ec4c61984dfac0b6 | MODIFIED |
| `core/cpp/include/jarvis/core/evolution_experiment_coordinator.hpp` | 2fde3fdf0b3e6772f11358385e069f9b94af34d0 | b7bf85429096b4d3b50c417b929564c2b15ed826 | MODIFIED |
| `core/cpp/include/jarvis/core/evolution_experiment_runner.hpp` | 38668879bec3e1cd5d8bcdf884edad819b1573d6 | eb7f5c23a47054d1e60aa65f28627199f511645d | MODIFIED |
| `core/cpp/include/jarvis/core/evolution_history.hpp` | 02efd6b4956393470902880c8a6ab73b3875c825 | 02efd6b4956393470902880c8a6ab73b3875c825 | IDENTICAL |
| `core/cpp/include/jarvis/core/evolution_learning.hpp` | e11ad3276110b9876c881a184f753cac67baed05 | e11ad3276110b9876c881a184f753cac67baed05 | IDENTICAL |
| `core/cpp/include/jarvis/core/evolution_monitor.hpp` | d8bd6d10534e6c65e922d36dd5b4ad8b47219b31 | d8bd6d10534e6c65e922d36dd5b4ad8b47219b31 | IDENTICAL |
| `core/cpp/include/jarvis/core/evolution_opportunity.hpp` | c03e36726228909c579d517afb8e11910027ba3f | c03e36726228909c579d517afb8e11910027ba3f | IDENTICAL |
| `core/cpp/include/jarvis/core/evolution_orchestrator.hpp` | 75105e51509156f1fad361ec47e0ae365a1a0291 | 05e5ca1578dc5b1635619aa61dc2da0459ef7708 | MODIFIED |
| `core/cpp/include/jarvis/core/evolution_rollback.hpp` | 22e1f10dd5b986f588a8106b8f433e2e6945072b | 22e1f10dd5b986f588a8106b8f433e2e6945072b | IDENTICAL |
| `core/cpp/include/jarvis/core/evolution_safety.hpp` | 60c69311a1f05d43eef2b8931be261fce3db60cf | 60c69311a1f05d43eef2b8931be261fce3db60cf | IDENTICAL |
| `core/cpp/include/jarvis/core/evolution_sandbox.hpp` | 887e07970132f3f049f6e7bef0569b1c3e086932 | 887e07970132f3f049f6e7bef0569b1c3e086932 | IDENTICAL |
| `core/cpp/include/jarvis/core/evolution_scheduler.hpp` | 240a9254ccf6263d36c55cc92f8921250f398234 | 240a9254ccf6263d36c55cc92f8921250f398234 | IDENTICAL |
| `core/cpp/include/jarvis/core/evolution_strategy.hpp` | 236557072d309ef99f76553cec90852d5441137c | 236557072d309ef99f76553cec90852d5441137c | IDENTICAL |
| `core/cpp/include/jarvis/core/evolution_trials.hpp` | 12555232deb8612abef0afee27cfc5ff5cb1fab6 | 12555232deb8612abef0afee27cfc5ff5cb1fab6 | IDENTICAL |
| `core/cpp/include/jarvis/core/experience_memory.hpp` | — | 28cce354eb9db7e8ca292746fd14649debb7ab04 | DONOR-ONLY |
| `core/cpp/include/jarvis/core/goals.hpp` | 803fdd34130c71f54912b23fcba2f9eed23dd4f2 | 66f8cd436a18a0bca8039205f682fc929c32b6a5 | MODIFIED |
| `core/cpp/include/jarvis/core/intent.hpp` | 1749ae0d795da496dd6a9a4dcdbd203ae7ddaf6f | d9d926db40a3361f8354a42051106ab2b00b3c77 | MODIFIED |
| `core/cpp/include/jarvis/core/knowledge.hpp` | 50eb1113a4569c3de05489c421d1cabb1437733d | 3da0d2059331af405bbb0ba98c61308ead99c405 | MODIFIED |
| `core/cpp/include/jarvis/core/learning_loop.hpp` | 287f2fe34cebd60b7a562d68c666572f71431cd6 | 287f2fe34cebd60b7a562d68c666572f71431cd6 | IDENTICAL |
| `core/cpp/include/jarvis/core/memory.hpp` | f3662038237246efa51155f940d77564f144d6d9 | 5401d5bd236cca8d3a93f2815164a7734cf6990f | MODIFIED |
| `core/cpp/include/jarvis/core/perception_pipeline.hpp` | 1e5fed009a2453211dac1a4187ff47c5cc65da39 | 1e5fed009a2453211dac1a4187ff47c5cc65da39 | IDENTICAL |
| `core/cpp/include/jarvis/core/planning.hpp` | 303731d3ac52362ec86afdb482a5567c3b38a8ff | 2bc6fc8a6bc4649da475f71f112a9fa3fd2b3610 | MODIFIED |
| `core/cpp/include/jarvis/core/process_isolation.hpp` | a85f71694c446a430291025ac4fe033e18a59549 | a85f71694c446a430291025ac4fe033e18a59549 | IDENTICAL |
| `core/cpp/include/jarvis/core/reasoning.hpp` | 5c6f82797d4f5052ad5d71a25624de192a2c87d9 | 5c6f82797d4f5052ad5d71a25624de192a2c87d9 | IDENTICAL |
| `core/cpp/include/jarvis/core/reflection.hpp` | 435e03f8f03f74cb910338ab4ab1264e4eaf085c | 5d9e11d7529f35445adbd23209914f6363548186 | MODIFIED |
| `core/cpp/include/jarvis/core/representation.hpp` | 4a9a12e8e66ce9c393081a4ffff0b7519f3a92ae | 4a9a12e8e66ce9c393081a4ffff0b7519f3a92ae | IDENTICAL |
| `core/cpp/include/jarvis/core/resilience.hpp` | 4cb687b6fe75f0a03a5017f1d58ce8ba66a51b66 | 4cb687b6fe75f0a03a5017f1d58ce8ba66a51b66 | IDENTICAL |
| `core/cpp/include/jarvis/core/self_model.hpp` | afd8a340f3e172b09c3859eb2602e383316ec4f8 | caffaa55562201db6f46ca07bb72189b11695b0b | MODIFIED |
| `core/cpp/include/jarvis/core/self_state.hpp` | 333917cc3dc4118a6776240141a5b16ee741bae8 | 333917cc3dc4118a6776240141a5b16ee741bae8 | IDENTICAL |
| `core/cpp/include/jarvis/core/self_testing.hpp` | 3dee193f773b068cf2c67fce7afeba04981f4fd4 | 3dee193f773b068cf2c67fce7afeba04981f4fd4 | IDENTICAL |
| `core/cpp/include/jarvis/core/strategy.hpp` | a5b153e9e4044cda97f261a053786b38fc70e76e | a5b153e9e4044cda97f261a053786b38fc70e76e | IDENTICAL |
| `core/cpp/include/jarvis/core/threat.hpp` | 4e84b378a92e8ea3e6d5fb4a371cba76561daca1 | 4e84b378a92e8ea3e6d5fb4a371cba76561daca1 | IDENTICAL |
| `core/cpp/include/jarvis/core/world_model.hpp` | 1c14f692374b0ab272f05634b7bdd26e358b4f1f | 1c14f692374b0ab272f05634b7bdd26e358b4f1f | IDENTICAL |
| `core/cpp/include/jarvis/core/world_state.hpp` | 5e91ec301d8254380731e0fdf14d16b6a3d5face | 5e91ec301d8254380731e0fdf14d16b6a3d5face | IDENTICAL |
| `core/cpp/src/action_authorization.cpp` | 669bc86c8111ae9755bcd40715352b4fc71350d0 | 669bc86c8111ae9755bcd40715352b4fc71350d0 | IDENTICAL |
| `core/cpp/src/action_execution.cpp` | c2f8653eb755fa2790a88e49bc8b0b9c3077e439 | af5bed6cec9ed1309b24ed3d50241fb4c0d33bff | MODIFIED |
| `core/cpp/src/action_model.cpp` | 1da9e70b4d0716ae6ee7ff2110b28424f094d6df | 1da9e70b4d0716ae6ee7ff2110b28424f094d6df | IDENTICAL |
| `core/cpp/src/adaptation.cpp` | 7e07a491a5b13379a5719882a834ecc2452a54ef | 51b91a52c20f71a1be462f660c45bee9199259c3 | MODIFIED |
| `core/cpp/src/affective_learning.cpp` | — | dd1735a10871512691d4b518d1ce45246c80f708 | DONOR-ONLY |
| `core/cpp/src/affective_state.cpp` | — | 563a61cd8f6440f78a084f76a799b2c84bdd6813 | DONOR-ONLY |
| `core/cpp/src/association_model.cpp` | b378d4237527dfbb4c65f43545f7f0fc7c42669b | 80bc2e94d8cab4e5a48ead18ba9efcad4ed785b6 | MODIFIED |
| `core/cpp/src/attention.cpp` | 58f734dbe9772675d687752026231297f289e770 | 67def4987f4a49a852bd2e4c9760f05c2ee15216 | MODIFIED |
| `core/cpp/src/attention_state.cpp` | b2d743e30548ba3803671693cca22412ae291199 | b2d743e30548ba3803671693cca22412ae291199 | IDENTICAL |
| `core/cpp/src/brain.cpp` | e9f3758fcc9c0e89b7280ce376db9033d547682d | dec9e5442b3ca4b81a7879855c6146b2619934cc | MODIFIED |
| `core/cpp/src/brain_action_execution.cpp` | — | 3b66bafb438cd28790e6f25611b96c86f1eff05c | DONOR-ONLY |
| `core/cpp/src/brain_affective_planning.cpp` | — | 2a9406257c23f3a66a64071842be7d6448799406 | DONOR-ONLY |
| `core/cpp/src/brain_novelty.cpp` | 92f93b6e21eed69444011804c047a19f95693722 | 92f93b6e21eed69444011804c047a19f95693722 | IDENTICAL |
| `core/cpp/src/brain_prediction_context.cpp` | — | b3ceff150f3fe8223dc3f76f4c298ac264d72dae | DONOR-ONLY |
| `core/cpp/src/brain_restored_api.cpp` | 618deb6976eed951eae02b7f0da741e6d730bb0c | 7155d4d9c8eef527836fb79bf901aa32ddbae38b | MODIFIED |
| `core/cpp/src/capability_evaluator.cpp` | c26199c03c544a700d3b5154930afba10d3253cd | c26199c03c544a700d3b5154930afba10d3253cd | IDENTICAL |
| `core/cpp/src/capability_execution.cpp` | 5fef6077caf96c77eef6bda2eedd57540759d4e7 | 5fef6077caf96c77eef6bda2eedd57540759d4e7 | IDENTICAL |
| `core/cpp/src/capability_registry.cpp` | e8565f666a0d34906e21409dc72c4b50935196c2 | e8565f666a0d34906e21409dc72c4b50935196c2 | IDENTICAL |
| `core/cpp/src/causal_model.cpp` | f873d0a6e7fa0676bb88bf7a1f66436bc88a3c0d | b7e1e6e6aeb929f09af33b9d17c80a6eed34948c | MODIFIED |
| `core/cpp/src/cognitive_cycle.cpp` | 3df14c552f2048b0394dc362f7ee7a654a93fb32 | f191dd610d6cbe1621756c35e7c13af2054a7266 | MODIFIED |
| `core/cpp/src/cognitive_runtime.cpp` | 1a1383cedc42e357dc9efce117328b8d55e30bca | cf00acb6abd52308343f3a0e7016e6173b945603 | MODIFIED |
| `core/cpp/src/cognitive_trigger.cpp` | 3eee892e6c5da55614f1202b7841eaec4cf7e625 | 3eee892e6c5da55614f1202b7841eaec4cf7e625 | IDENTICAL |
| `core/cpp/src/cognitive_workspace.cpp` | fbd2321d9cd1c98217389beced292654e33a906e | fbd2321d9cd1c98217389beced292654e33a906e | IDENTICAL |
| `core/cpp/src/decision.cpp` | 6a49e0f1f80c3c6b0955ddf98182fc6611c0e84c | 012025bc2ef66b1b9555b9b9f2b220b49c8d36c4 | MODIFIED |
| `core/cpp/src/developmental_learning.cpp` | — | dbf5f43271dfa0a3c57236e2faa82eb88d15490d | DONOR-ONLY |
| `core/cpp/src/evolution.cpp` | 3860a5a59495460c44e49b8539adff637d7ae65d | 7a3bc311034c48181cc9b9d4df81c308ebaa8f3d | MODIFIED |
| `core/cpp/src/evolution_adoption.cpp` | b62153de36395b3ef46e25a1af0520e15af85e3f | 836216bb567e2c87d14b6442bd363e9861ac6974 | MODIFIED |
| `core/cpp/src/evolution_adoption_journal.cpp` | a9e141ac0b784466e86575eefdb3260b2e15dfc0 | d8df30a2902d3dac734fb1a571cbbecdd881b76f | MODIFIED |
| `core/cpp/src/evolution_canary.cpp` | b40c2eec58db1a3f7d3007781f0a5e6abe8c70a9 | 8773507b4bc5842c60b78bcb384f09ea4c4caa2b | MODIFIED |
| `core/cpp/src/evolution_candidate_generator.cpp` | c953448fde4f5b61a117cdbf08317a71f11d1692 | c953448fde4f5b61a117cdbf08317a71f11d1692 | IDENTICAL |
| `core/cpp/src/evolution_controller.cpp` | 01484ebf12fc3902bce749030a1f54610b26236a | 4e77ec2e5daa09a964132ca486b8c5ee1cebf2f5 | MODIFIED |
| `core/cpp/src/evolution_experiment.cpp` | 6c4c8272b72f7685230870147dd362ad3c6dd363 | 6c4c8272b72f7685230870147dd362ad3c6dd363 | IDENTICAL |
| `core/cpp/src/evolution_experiment_coordinator.cpp` | c689d16b31c039a7be9ab5c9bde0de49e677b32d | 93d2e01c785ed4867efec07673cd802afbe27427 | MODIFIED |
| `core/cpp/src/evolution_experiment_runner.cpp` | 83d3c26e589cd16151818774a81ccb62f9d514fc | 0545662ea0ef865feb0527207fc4c32ecb50566e | MODIFIED |
| `core/cpp/src/evolution_history.cpp` | 4c023ab4a726efb07f563c2b5425b824e19aeee9 | e394042ba7fc6db85e4663722f735918aa1ce7fb | MODIFIED |
| `core/cpp/src/evolution_learning.cpp` | 55030a497cdb96cd748f88612617dacb326f6617 | 55030a497cdb96cd748f88612617dacb326f6617 | IDENTICAL |
| `core/cpp/src/evolution_monitor.cpp` | 568798a562a4c14877adaf2a08d303405ff77f7e | 568798a562a4c14877adaf2a08d303405ff77f7e | IDENTICAL |
| `core/cpp/src/evolution_opportunity.cpp` | db48c582f12565261318333337341bef2ad7653f | db48c582f12565261318333337341bef2ad7653f | IDENTICAL |
| `core/cpp/src/evolution_orchestrator.cpp` | efd55281ba7d2edf95c6a9f6537ed2944022617e | c913ff0f42fc4647605376579b3f343b5c12c387 | MODIFIED |
| `core/cpp/src/evolution_rollback.cpp` | b6d941d7388a95bf9fa0831cbf71ea39adafade1 | b6d941d7388a95bf9fa0831cbf71ea39adafade1 | IDENTICAL |
| `core/cpp/src/evolution_safety.cpp` | 6c930ebbe69ad92fe155e3c169e3e996442f22cf | 5a4669de9296958eacc77534bad87ce7c30ae52d | MODIFIED |
| `core/cpp/src/evolution_sandbox.cpp` | 837ab2adb087284fb370b623371693660b47624a | 364641cf3616db100dd54853d12293341d609116 | MODIFIED |
| `core/cpp/src/evolution_scheduler.cpp` | 142cfcab2d973e94c827d8d8b014df78fda70efb | 142cfcab2d973e94c827d8d8b014df78fda70efb | IDENTICAL |
| `core/cpp/src/evolution_strategy.cpp` | 09119ffd3991f57106b1e9dbd783357ac9c5edef | 09119ffd3991f57106b1e9dbd783357ac9c5edef | IDENTICAL |
| `core/cpp/src/evolution_trials.cpp` | 4e6192c3d06560c826f8beaf507a546d4c56952a | 4e6192c3d06560c826f8beaf507a546d4c56952a | IDENTICAL |
| `core/cpp/src/goals.cpp` | 778a829de8314e83b095af2f2c2a6b83baa769f4 | afaedcfb0f2f68ff88b3a20e474fce04bb59815c | MODIFIED |
| `core/cpp/src/intent.cpp` | 4283a4255284c51257df6bad12734782f2a6cde9 | 9707d5b6da4ddede4dfc99d52f30e7cdc7eed032 | MODIFIED |
| `core/cpp/src/knowledge.cpp` | 25ecf822e6132f576266c1f86a964a227c7fb75f | 21de8abbcd4426cb4ead70cb089e7d7c4ed0e81a | MODIFIED |
| `core/cpp/src/learning_loop.cpp` | bc9a6aaca38d060667bcdf82f2b1a1f72c5936ba | bc9a6aaca38d060667bcdf82f2b1a1f72c5936ba | IDENTICAL |
| `core/cpp/src/memory.cpp` | ba72a897306d4761246d0deab2fbab37c49d372f | ab42bba1d32d6f48d091787491c72294a4a55bb5 | MODIFIED |
| `core/cpp/src/perception_pipeline.cpp` | ab9a745bb68e416d4e32c9d0c26a2d0b2016ab17 | ab9a745bb68e416d4e32c9d0c26a2d0b2016ab17 | IDENTICAL |
| `core/cpp/src/planning.cpp` | aab022b7cbc06f380413395757d590b56a1f3a20 | 9fcc2317e5acf0bfc24865a89eb9a54b80f8a80a | MODIFIED |
| `core/cpp/src/process_isolation.cpp` | eac7a12fafe36b6c5f463ad0a41caa3bb835a61c | 8bb621fc986b4957f079bfdf99f4a1038949bc72 | MODIFIED |
| `core/cpp/src/reasoning.cpp` | feec78b2e8a1f2b0b58733fd509e4e5a750258fc | 18bf2facc9f95c6bd2e8d9a559a0e5b1c5ae06e1 | MODIFIED |
| `core/cpp/src/reflection.cpp` | 06f34e20f35aad535a2c606b3669b2127ef7a480 | fe7dd1fada300300673b90caffa128384c65bde1 | MODIFIED |
| `core/cpp/src/representation.cpp` | 0e53bfaa0c1114cb7390d9f7ce577c87d6bc6169 | 054bd9ecee3ef3da83dd405dc5785464d874fa21 | MODIFIED |
| `core/cpp/src/resilience.cpp` | ec02b31ed08dc7ac5d9337f92091bb202988cc03 | ec02b31ed08dc7ac5d9337f92091bb202988cc03 | IDENTICAL |
| `core/cpp/src/self_model.cpp` | 3c6a375eadd6894a635d2e18023a7079cba97c86 | c1beeec968fa62fce8fb037f8b95a869031331ce | MODIFIED |
| `core/cpp/src/self_state.cpp` | 01684a46b29fc827beadbd4c05178521085df476 | 01684a46b29fc827beadbd4c05178521085df476 | IDENTICAL |
| `core/cpp/src/self_testing.cpp` | 30b5af95ba1785120a10097767e28a9f3b67a8ce | 30b5af95ba1785120a10097767e28a9f3b67a8ce | IDENTICAL |
| `core/cpp/src/strategy.cpp` | 5406a341cd4b3f42e16166f6122a0cb580aee298 | 5406a341cd4b3f42e16166f6122a0cb580aee298 | IDENTICAL |
| `core/cpp/src/threat.cpp` | b9b7258b9540b30588aa4e7c0002d24a28a3e7b4 | b9b7258b9540b30588aa4e7c0002d24a28a3e7b4 | IDENTICAL |
| `core/cpp/src/world_model.cpp` | 5b68e8fe37d99732557237e347ae02234a3de172 | 5b68e8fe37d99732557237e347ae02234a3de172 | IDENTICAL |
| `core/cpp/src/world_state.cpp` | 84658ee6e1a4485e1fe0f24ebb40eb3e281670f0 | 84658ee6e1a4485e1fe0f24ebb40eb3e281670f0 | IDENTICAL |
| `core/cpp/tests/CMakeLists.txt` | dab0c52ab4dfe15e1e2cbccfa9e6c904abdf54e3 | cbfd1fde52fffa6eeac025da2b7ddcb5ab493261 | MODIFIED |
| `core/cpp/tests/action_authorization_suite.cpp` | cf0cd95ec6fd83da756c305c54439a018cad796b | 66127a2b574d5c44571332733edb800fb558bcaf | MODIFIED |
| `core/cpp/tests/action_execution_phase7_suite.cpp` | b4a0060596c91c67080ac0a2db324f720d760fbe | db11ac95d26a97b01dfeb67cfb85194dc284ffb8 | MODIFIED |
| `core/cpp/tests/action_model_architecture_suite.cpp` | 24f419a4ff469995bbc5961974c7ee3b869c9911 | e2e0ecf121ab866f5793bb63c2f605ec5f68dafa | MODIFIED |
| `core/cpp/tests/affective_brain_decision_suite.cpp` | — | 9ff9c0480fa34fa4f5600e514af419b2bbc79765 | DONOR-ONLY |
| `core/cpp/tests/affective_decision_learning_suite.cpp` | — | 920ddcbc8a422783bb8724093afd952cc885e6b6 | DONOR-ONLY |
| `core/cpp/tests/affective_decision_suite.cpp` | — | 982b11e117b8f59cce3719a5253cb52e96304c0d | DONOR-ONLY |
| `core/cpp/tests/affective_evidence_suite.cpp` | — | c8a401cab1a29d57506f990043a1f82536fd9029 | DONOR-ONLY |
| `core/cpp/tests/affective_goal_outcome_suite.cpp` | — | 06d72304fa0c4ea67eb4a27b91c484007f231199 | DONOR-ONLY |
| `core/cpp/tests/affective_learning_suite.cpp` | — | bfbbca315c60c9b1c941dbc553a0cabba304581c | DONOR-ONLY |
| `core/cpp/tests/affective_planning.cmake` | — | e3a52416b2538791a93666e5124b1f34ad1b082a | DONOR-ONLY |
| `core/cpp/tests/affective_planning_suite.cpp` | — | 32e5f04cfb6e4764cb205744266375367228bedf | DONOR-ONLY |
| `core/cpp/tests/affective_state_model_suite.cpp` | — | 29f15bdd1a5d55afd5170a9d21bc3572befc97f0 | DONOR-ONLY |
| `core/cpp/tests/affective_state_suite.cpp` | — | 3956eec2ed9885e80ada1d038de6c581338b8f8c | DONOR-ONLY |
| `core/cpp/tests/association_causality_phase5_suite.cpp` | d520025258805b02c1b3fbb2dbebe32e01562fbf | 0d31349857e85a019467e9864bbe6625a6ecdef7 | MODIFIED |
| `core/cpp/tests/attention_architecture_suite.cpp` | 3a5609ed29e117c2241ce3f23543c8042f5815b2 | 4b6f4ad50b9706e372c51e21803e57438d99d155 | MODIFIED |
| `core/cpp/tests/attention_learning_brain_suite.cpp` | — | 1fa972d9ecffdae8dce49b17356f6f4dc274d1a3 | DONOR-ONLY |
| `core/cpp/tests/brain_10_suite.cpp` | be220d6bdaf1af2a584f6c628fd03b9aea12811c | 1da00539509824ba282d05501307febd27e21219 | MODIFIED |
| `core/cpp/tests/brain_action_consequence_integration_suite.cpp` | — | 7616082579d53e3579cae8e87895bdb3dadba66f | DONOR-ONLY |
| `core/cpp/tests/brain_contract.cpp` | 54340d74eca3d8613db1763f8e01e3bc6fc221ba | 3536648d901b004a644db79e9d50ff9a765182ed | MODIFIED |
| `core/cpp/tests/brain_deep_suite.cpp` | ca8e7012c92822608c3be0539784d281b0578bfd | 1314123ea3b524b24fd6693fc6fb4873b6c550d5 | MODIFIED |
| `core/cpp/tests/brain_failure_suite.cpp` | b0e5cb3dd436b5507be10f554c5b850b3fb73df2 | b0e5cb3dd436b5507be10f554c5b850b3fb73df2 | IDENTICAL |
| `core/cpp/tests/brain_smoke.cpp` | 0c61c6f9e1bb35e40d0d8c4d7eb17744998c3e68 | 0c61c6f9e1bb35e40d0d8c4d7eb17744998c3e68 | IDENTICAL |
| `core/cpp/tests/capability_evaluator_suite.cpp` | 16fa37cc0209d7e7e91de78f92f84491f0850705 | 16fa37cc0209d7e7e91de78f92f84491f0850705 | IDENTICAL |
| `core/cpp/tests/capability_execution_suite.cpp` | e7ac00dc0b51e9b3135c6072a65f980c6a796375 | e7ac00dc0b51e9b3135c6072a65f980c6a796375 | IDENTICAL |
| `core/cpp/tests/capability_registry_suite.cpp` | 3333ac6049da4422073263e13a053fcc85980a5b | 3333ac6049da4422073263e13a053fcc85980a5b | IDENTICAL |
| `core/cpp/tests/cognitive_cycle_stress_suite.cpp` | b1f73ca14ac7a82eb4054b88c6f75f997eb6d9f3 | b1f73ca14ac7a82eb4054b88c6f75f997eb6d9f3 | IDENTICAL |
| `core/cpp/tests/cognitive_cycle_suite.cpp` | 38ff2c7d6e851b4745e9dc7c01f968b7245400a2 | 3e762cdec8b27030cf94478a1a68a4605a38c8c5 | MODIFIED |
| `core/cpp/tests/cognitive_runtime_goal_feedback_suite.cpp` | — | 15a6bdffe37ae7df6c625ea9737fda4c0bf08a7f | DONOR-ONLY |
| `core/cpp/tests/cognitive_runtime_learning_integration_suite.cpp` | — | 656de56b1368e40afb090778a7a5504ab4208056 | DONOR-ONLY |
| `core/cpp/tests/cognitive_runtime_suite.cpp` | 48cac9cb0e27e2dc8a15323429d1f7158ee427a0 | 361cba84a6fc6e07e31d14b5fa618c3f0a7848fa | MODIFIED |
| `core/cpp/tests/cognitive_trigger_suite.cpp` | a817221e2dda72b9a6e45b4b00039f506ff9dc61 | a817221e2dda72b9a6e45b4b00039f506ff9dc61 | IDENTICAL |
| `core/cpp/tests/cognitive_workspace_runtime_suite.cpp` | ae938f5df02d8f907a548c446c01e17fbd2f1470 | b29e75aa8b0e289c01f2e9188d26c639cfa1f22d | MODIFIED |
| `core/cpp/tests/decision_planning_architecture_suite.cpp` | 16934f99898c3ffffcf5ac04a7a031e0845da050 | 3ed85a1acc55f47eb266599d809525ef08ba0b11 | MODIFIED |
| `core/cpp/tests/developmental_brain_integration_suite.cpp` | — | 760162dd6d1e669162e0bf22223a437491f5e262 | DONOR-ONLY |
| `core/cpp/tests/developmental_environment_suite.cpp` | — | a3fa73f78b56a3ea04cdfb6b1bf16739f0894d5d | DONOR-ONLY |
| `core/cpp/tests/developmental_learning_suite.cpp` | — | 8e94932b40c109f1c73470418d85ca2020a2e198 | DONOR-ONLY |
| `core/cpp/tests/developmental_learning_tests.cpp` | — | 553b3253462344a00d9fbcff1ff682a2788262d2 | DONOR-ONLY |
| `core/cpp/tests/developmental_training_environment_suite.cpp` | — | 62a0ee4f8ec966e48a45848217ba7a6d6e96196f | DONOR-ONLY |
| `core/cpp/tests/developmental_world_integration_suite.cpp` | — | 4290fcfde741f1be9a4a69adc70699ade6fe7922 | DONOR-ONLY |
| `core/cpp/tests/developmental_world_suite.cpp` | — | bd8f6767cdcf6513674730f24c184bac6600e116 | DONOR-ONLY |
| `core/cpp/tests/dlt_001_long_run.cpp` | — | 896caa7e4d14ce6e4f12e453181a14bbb74c62fd | DONOR-ONLY |
| `core/cpp/tests/dlt_001_trial.cpp` | — | deca50aec499a04d46cbc7aed429e335fff18f72 | DONOR-ONLY |
| `core/cpp/tests/dlt_002_long_run.cpp` | — | cbd80951c2f331fa4893c1805fff45a4035d5d24 | DONOR-ONLY |
| `core/cpp/tests/dlt_002_persistence.cpp` | — | d818a75cff936bffc8a383e032302f51ac8a1034 | DONOR-ONLY |
| `core/cpp/tests/evolution_adoption_journal_suite.cpp` | 24a1be9541cc038518065724aef1968efc4dc595 | fc8ae17bb837831fef7bf69873ec0e5243e2bc22 | MODIFIED |
| `core/cpp/tests/evolution_brain_integration_suite.cpp` | 3164cbc19bfb056cdccfdd58f0be047226d41a86 | 59d7dd68c42eea18d488d8e5e6aa9f7a9a327ded | MODIFIED |
| `core/cpp/tests/evolution_canary_controller_suite.cpp` | 6acd8aedb7520aebe745b15a2a10c527262f28e0 | 80cac5df347987a9074e1ced43202f8759f797d7 | MODIFIED |
| `core/cpp/tests/evolution_experiment_coordinator_suite.cpp` | 83d884dd97cbcf2d002249a70e44bb29e6ac0560 | 5b410197e3c5e48acb381e274ae22e8ba037aa84 | MODIFIED |
| `core/cpp/tests/evolution_experiment_runner_suite.cpp` | 08888276d875ce5e55f421e828f1bb4f061d1ea5 | 307fe75b42f804d9bb2b0e8199df1e9cf773e3c6 | MODIFIED |
| `core/cpp/tests/evolution_experiment_suite.cpp` | f5aa9ee8fc68e8a2f9f0dd0466ff5e26a77423d2 | f5aa9ee8fc68e8a2f9f0dd0466ff5e26a77423d2 | IDENTICAL |
| `core/cpp/tests/evolution_experiment_test.cpp` | fdc3cacd71690b96939f201b3ac804d7868fa76c | fdc3cacd71690b96939f201b3ac804d7868fa76c | IDENTICAL |
| `core/cpp/tests/evolution_learning_suite.cpp` | 41e2fa3532efa4de3521ca889bb6558711340299 | 41e2fa3532efa4de3521ca889bb6558711340299 | IDENTICAL |
| `core/cpp/tests/evolution_monitor_suite.cpp` | fd54357414ee680c73f97e731989b6f2b7578754 | fd54357414ee680c73f97e731989b6f2b7578754 | IDENTICAL |
| `core/cpp/tests/evolution_opportunity_orchestration_suite.cpp` | 4ef1dc80a85a8e9247c5816bdb73c6876d3a1b22 | 24d6dd905cb537cc6c14e329db6a7d52d49c97b8 | MODIFIED |
| `core/cpp/tests/evolution_scheduler_suite.cpp` | f590c4e068789acd06dbb3c75af606bf01d08902 | f590c4e068789acd06dbb3c75af606bf01d08902 | IDENTICAL |
| `core/cpp/tests/evolution_trials_suite.cpp` | 643273ae753b289a7ea578724f6c554682567e8c | 643273ae753b289a7ea578724f6c554682567e8c | IDENTICAL |
| `core/cpp/tests/experience_memory_test.cpp` | — | fe69fed346c9f843101fc3379d6d474f4a082651 | DONOR-ONLY |
| `core/cpp/tests/goal_directed_cognition_suite.cpp` | — | 7fe6cf6c4dd2dc2a54bb9f48fcdd3c3d91d7c282 | DONOR-ONLY |
| `core/cpp/tests/goal_outcome_model_suite.cpp` | — | c9f19978d6d2df45028cb824e835144dc45c70e7 | DONOR-ONLY |
| `core/cpp/tests/goals_architecture_suite.cpp` | 14a52aa606b53f8529aa5c54861c11902deb7c97 | 0b99d090b400d0af50b186cd3a416fa28a177b99 | MODIFIED |
| `core/cpp/tests/judgment_intent_strategy_phase6_suite.cpp` | 05b6c3f4c331e035dc9276025ae1d03bfe931a71 | 05b6c3f4c331e035dc9276025ae1d03bfe931a71 | IDENTICAL |
| `core/cpp/tests/knowledge_memory_phase3_suite.cpp` | f796977fd116418b3cf0a5f9c8d33ed7a48f811e | e33b9813edbfaf02a91a3f94988f5c7a54ceed8f | MODIFIED |
| `core/cpp/tests/learning_adaptation_phase8_suite.cpp` | 79cb7b8146686b35273628de213d33edd4328cff | 59859480a6d09aaab70eaf09ffc94c731484d2ff | MODIFIED |
| `core/cpp/tests/learning_loop_architecture_suite.cpp` | 1b01fc772f525619fb635579ccf7831187fee08a | 1b01fc772f525619fb635579ccf7831187fee08a | IDENTICAL |
| `core/cpp/tests/memory_architecture_suite.cpp` | 2a9eb061427c622260304d09f45089e1debef294 | ecabc6af76c52ed1e4175b151e76fadecae7729d | MODIFIED |
| `core/cpp/tests/memory_learning_evolution_persistence_suite.cpp` | — | 98e6598f60912714234f2dfabfbe52fa5eb77044 | DONOR-ONLY |
| `core/cpp/tests/perception_pipeline_suite.cpp` | 2312d9f86763a05d7eef9e341d7b1d60bfe845e9 | 2312d9f86763a05d7eef9e341d7b1d60bfe845e9 | IDENTICAL |
| `core/cpp/tests/phase4_notes.md` | bf77a7805cc292bdbbd80b5d31566877f67ddf4b | bf77a7805cc292bdbbd80b5d31566877f67ddf4b | IDENTICAL |
| `core/cpp/tests/prediction_feedback_phase10_suite.cpp` | e72da8e7653aee775cfade9060064231c7a01630 | 973350623e52bd9609ebaf1e01082ee52aeb480b | MODIFIED |
| `core/cpp/tests/process_isolation_suite.cpp` | 78b764368de4d427c3196b26b57255edc422bf50 | 6539da294b55e537ed28c08f3f72aff5f6b869e2 | MODIFIED |
| `core/cpp/tests/process_isolation_syscall_suite.cpp` | cd347d277c84376c3a90ce4d95b31b4dbafde583 | cd347d277c84376c3a90ce4d95b31b4dbafde583 | IDENTICAL |
| `core/cpp/tests/reasoning_architecture_suite.cpp` | a7119afd091e045d6294aa1b15c20de349ed6a1c | ceb6d471b3283f4a89fe243ac3c9e79f52f137a2 | MODIFIED |
| `core/cpp/tests/representation_suite.cpp` | 1ee7663934f067de4fdd31832719b06274ae6171 | 07c515018eca0f34f496e85608f504620fd07306 | MODIFIED |
| `core/cpp/tests/self_model_health_phase4_suite.cpp` | 46fdbb1325159999e7e3ac7e223e9a2a2703b5f5 | 46fdbb1325159999e7e3ac7e223e9a2a2703b5f5 | IDENTICAL |
| `core/cpp/tests/self_state_suite.cpp` | 2d6a9e51393a5e144d4920a06d5fee5606c5ad71 | 2d6a9e51393a5e144d4920a06d5fee5606c5ad71 | IDENTICAL |
| `core/cpp/tests/self_testing_healing_phase9_suite.cpp` | 1e0c13c6de2843771d63389ddc338617a04af632 | 1e0c13c6de2843771d63389ddc338617a04af632 | IDENTICAL |
| `core/cpp/tests/world_self_model_phase4_suite.cpp` | f375f6e36c16fbb038d2ce3ba5c4cd18adf1860c | f375f6e36c16fbb038d2ce3ba5c4cd18adf1860c | IDENTICAL |
| `core/cpp/tests/world_state_suite.cpp` | bc6539059a8cc856572f3b01358085f27b1673a9 | bc6539059a8cc856572f3b01358085f27b1673a9 | IDENTICAL |

## 9. Exact architecture revision reviewed for this inventory

- PR #173 HEAD: `a8be408921afaa7a417cc972e891155bbcd11d19`.
- Architecture blob: `50b5c6e471df797d490b314c542e8d2bdce71c42`.
- Completion matrix blob: `9938fa331e06c91cce15e33fa6bd97d613ea9659`.
- PR #171 source/architecture baseline: `b05434758ad4fe72815503f89bd5d2990ccb658b`.
- PR #172 accepted investigation engineering-evidence baseline: `1273ddbcd0087d189e01388ded2d362fb1e058d2`.
- PR #97 donor source revision: `c1da222e6c94aeb3f2ad000392c21fe4fc81ab25`.

**Final Builder disposition:** the cross-baseline inventory and mechanism-level architectural dispositions required by CF-26 Option A are recorded. CF-26 remains open until the owned remediation/evaluation specifications are completed and independently challenged; this report does not authorize their runtime implementation.
