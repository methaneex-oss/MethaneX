# Implementation Planning Run 02 — Readiness and Activation Decision Map

**Status:** Non-operative planning artifact; proposed for independent challenge and Project Director disposition  
**Repository:** `methaneex-oss/MethaneX`  
**Planning PR:** #175 — `plan/brain-implementation-roadmap-20261103`  
**Exact planning parent:** `d98c9e0ef964f52b8aa9647834092210438c6458`  
**Date:** 2026-11-18  
**Governing principle:** **Engineer the mechanisms; let behavior be acquired through experience.**

---

## 1. Purpose and relationship to existing planning

This is a continuation of the existing JARVIS implementation-planning work, not a new roadmap and not a restart. It consolidates the current planning package into one decision map: what is already planned, what evidence is still missing, what can proceed as non-operative preparation, and what must remain blocked until explicit authority is recorded.

It supplements, and does not replace:

- `00_BRAIN_IMPLEMENTATION_PLAN.md` — dependency graph, phases, principles and verification strategy.
- `17_PARALLEL_NON_OPERATIVE_IMPLEMENTATION_PLANNING_SUPPLEMENT_2026-11-17.md` — bounded parallel-planning exception and integrated increments.
- `18_CAPABILITY_TO_ACCEPTANCE_SCENARIO_TRACEABILITY_MATRIX_2026-11-18.md` — 54-scenario mapping to BM owners and increments for the current proposed specification.
- `19_IMPLEMENTATION_PLANNING_KICKOFF_AND_STARTER_LEARNING_WORK_PACKAGES_2026-11-18.md` — WP-00 through WP-08.
- `20_STARTER_LEARNING_RUN_PROTOCOL_AND_EVALUATION_DESIGN_2026-11-18.md` — R0 through R6 controlled learning-run protocol.

The existing planning outputs are substantive. Recreating them as a second generic plan would add duplication, not readiness.

## 2. Exact upstream state used for this planning pass

| Area | Exact current revision / status | Planning treatment |
|---|---|---|
| Brain Foundation Architecture — PR #173 | HEAD `a96af5b18d3a1d580ff56cff6191240893bceeb5`; open/draft/unmerged; xAI re-review of `1f137cbaed985821bbc32408151911b18418f713` returned **PARTIALLY CLEAR** | Use the reviewed responsibility model as planning input only. Whole-architecture acceptance, CF-26 independent challenge and CF-27 final gate remain open. |
| Brain Mechanism Specification — PR #174 | HEAD `c34472354e4122fc1d78dc25bf45d81f1eb4dc69`; open/draft/unmerged; xAI review of `7cb6271531f3e80a45728756273218132499722e` returned **PARTIALLY CLEAR** | Current 54-scenario proposal is traceability input, not accepted authority. The historical accepted baseline is `0811a59e46bf934e32e794f90e4e7d18d4e2bd97` with 34 scenarios. Do not merge the two sets or silently upgrade the proposal. |
| Implementation planning — PR #175 | HEAD `d98c9e0ef964f52b8aa9647834092210438c6458`; open/draft/unmerged | Continue documentation/planning and decision preparation only. |
| Documentation Foundation — PR #192 | HEAD `4b4a3d71dd8ed28dc0b39766e323253289255741`; open/non-draft/unmerged; 43 changed paths | DF-02 OPEN; DF-06 NOT MET; DF-09 NOT MET; DF-10 Builder-verified only for exact inventory §121 parent/successor pair; DF-11 WAIVED; DF-12 pending Director decision. Stage A held. |
| Reader workflow correction — PR #197 | HEAD `2b2bfd9afe6e1325119f7ccee507bb04e71aa343`; open/non-draft/unmerged; one workflow file | xAI exact-HEAD request posted; no independent verdict or new assessment run is recorded. No dispatch or integration is claimed. |
| Phase 2 capability map — PR #179 | HEAD `ea64607ef94f142a6142a013e119a7225bc95c1c`; open/draft/unmerged | Retain as the current Phase 2 mapping input; do not retarget or merge planning branches. |
| Donor candidates — PR #97/#156/#176 | Exact revisions and bounded findings are recorded in PR #192's DF-02 report §9 | Treat as evidence for future path-specific Gate A review only. No wholesale donor selection or selective port is authorized. |

**Freshness rule:** these are exact references observed for this planning pass. Before any later decision or activation, re-fetch live PR metadata and verify that each referenced revision is still the intended target. A branch name is not an immutable source identity.

## 3. What is already planned

The current package already defines:

- **WP-00:** planning control, exact-revision intake and decision traceability.
- **WP-01:** experience and provenance.
- **WP-02:** continuity, memory and retrieval.
- **WP-03:** representation and belief revision.
- **WP-04:** memory-supported reasoning.
- **WP-05:** prediction and feedback.
- **WP-06:** owner-approved learning and persistence.
- **WP-07:** attention, appraisal, goals and metacognitive integration.
- **WP-08:** integrated starter-training and evaluation protocol.

The first intended capability claim is deliberately bounded: attributable experience enters the system; representations and context are formed; relevant memory and beliefs are used; predictions are resolved against correctly attributed outcomes; candidate changes are evaluated by the appropriate state owners; accepted changes persist across reconstruction and measurably influence later relevant behavior. The claim must also survive held-out related cases and avoid unjustified transfer or regression.

The R0–R6 protocol defines fixture integrity, pre-training baseline, controlled exposure, immediate evaluation, reconstruction, sealed transfer/regression and longitudinal replication. No training curriculum may preload the desired answer, belief, emotion, goal, association or strategy.

## 4. Run 02 decision map — remaining prerequisites

### D-01 — Documentation Foundation exact-revision closure

**Owner:** Documentation Foundation Builder; independent evidence sources where the criteria require them; Project Director for DF-12.

Required sequence:

1. Finish the DF-02 residual historical artifact and cross-branch consumer/reference census. The bounded PR #97/#156/#176 donor audit is useful but explicitly does not close the full 159-file semantic disposition or all historical/cross-branch dependencies.
2. Complete DF-06 parser reconciliation by reproducing the prior 331/125/206, 332/131/201 and newer 348/129/219 results with the exact parser versions, inclusion rules and exact source revisions. Preserve the differing snapshots; do not pick a convenient count.
3. Complete DF-06 external destination validation and authenticated rendered GitHub heading, line and comment-anchor checks, or obtain the exact Project Director disposition permitted by the governing DF-06 criterion for any demonstrably inaccessible evidence.
4. Resolve the packet reader-visible exact-SHA correction in PR #197 through its own independent exact-HEAD review and authorized integration path. Then run the approved blind fresh-reader workflow against the final frozen PR #192 SHA. The existing run #44192302873 is **PARTIALLY CLEAR (31/32)** against `beb4d5a174a1dd613878f89132e97b5e6052c7d3`; it is not evidence for a successor.
5. Reconcile the controlling index, runbook, DF reports, PR description and exact-parent inventory so that all live gate statuses agree. Any PR #192 write reopens the inventory snapshot cycle.
6. Present the exact final package and all remaining authority decisions to the Project Director. DF-12 is not a Builder decision.

**Exit evidence:** each applicable DF criterion has an exact-revision evidence record and disposition; no stale verdict is attributed to a successor; the controlling index and inventory agree; the Project Director records the exact-revision DF-12 decision.

### D-02 — Architecture and specification authority

**Owner:** independent reviewer for technical challenge; Project Director for acceptance/disposition.

- PR #173 must resolve whole-architecture acceptance, CF-26 and CF-27 at exact revisions. The prior PARTIALLY CLEAR verdict is not a CLEAR result.
- PR #174's current corrected proposal must receive exact-head review and explicit Project Director disposition. The historical accepted 34-scenario baseline remains distinct from the current proposed 54-scenario revision.
- Any unresolved conflict between architecture, mechanism ownership, SYS boundaries, or specification scenarios must be resolved before affected work packages become executable.

**Exit evidence:** exact accepted architecture and specification revisions, with a decision record that states what is accepted, what remains deferred, and which scenarios govern.

### D-03 — Gate A source-baseline reconciliation

**Owner:** Builder evidence preparation; independent technical reviewer; Project Director for baseline selection.

- Revalidate repository ancestry, code-bearing candidate trees, API compatibility, current-main workflow continuity, D1/D2 corrections and partial-failure/replay semantics against the exact candidate revisions.
- Reconcile the PR #156/#176 branch divergence and all proposed correction evidence without assuming that a declared base branch means the current tip is contained.
- Compare candidate mechanisms against the accepted specification and current main; classify each relevant path as retain, adapt, replace or reject with evidence.
- Do not select PR #156 wholesale. The old Builder recommendation is not a Director decision.

**Exit evidence:** exact target source revision, complete risk-based path disposition, API/build compatibility evidence required by the Gate A criteria, independent challenge, and explicit Project Director baseline decision.

### D-04 — Gate B capability acceptance

**Owner:** mechanism owners and integration evidence preparation; Project Director for gate disposition.

- The 54-scenario matrix is a proposed-specification traceability map, not 54 passing tests and not accepted authority.
- Establish the governing scenario set after PR #174 disposition.
- Define cross-mechanism evidence for the integrated loop, including memory materially affecting reasoning, prediction/outcome attribution, owner-controlled multi-state learning, persistence/reconstruction, held-out transfer, negative transfer and regression.
- Do not equate static source mapping, a green build, 73/73 historical CTest, or module presence with capability acceptance.

**Exit evidence:** every governing scenario has an exact source/owner mapping and executable evidence definition; the integrated capability acceptance criteria are met on an authorized baseline; the Project Director records Gate B disposition.

## 5. First implementation increment — planning definition only

The first planned increment remains the **evidence-to-learning vertical capability**, not a chatbot surface, an autonomous action layer, or a broad collection of disconnected mechanism tickets.

Its intended contract is:

1. An experience is retained with source, temporal, context and integrity lineage.
2. One or more interpretations can be formed without overwriting the original experience.
3. Relevant memory is retrieved with applicability and provenance information.
4. Beliefs and predictions preserve scope, uncertainty, alternatives and resolution criteria.
5. New outcomes are attributed to the correct prediction/experience rather than provider, execution or substrate failure.
6. A candidate learning change is evaluated by the state owner(s) it affects; rejection is a first-class outcome.
7. Accepted changes persist and reconstruct coherently.
8. A later relevant case demonstrates measurable behavioral change; held-out and unrelated cases test transfer boundaries and regression.

**Non-goals for this first increment:** general intelligence claims, broad autonomy, personality scripting, hardcoded affect/goal/action mappings, automatic goal execution, or a claim that all twelve mechanisms are mature.

No concrete algorithm, model/provider, framework, storage technology, schema, API, or deployment topology is selected here.

## 6. Work-package readiness classification

| Package | Planning status | What is needed before activation |
|---|---|---|
| WP-00 | Planning structure exists | Freeze exact accepted inputs and decision log for the authorized implementation target. |
| WP-01 | Contract planning started | Gate A source map, provenance contract approval, authorized implementation scope. |
| WP-02 | Contract planning started | Memory owner contract, retrieval applicability, persistence/recovery and source-baseline evidence. |
| WP-03 | Contract planning started | Accepted representation/belief semantics and competing-claim lifecycle. |
| WP-04 | Contract planning started | BM-12 accepted premise/assumption/lineage contract and proof that retrieved memory is consumed downstream. |
| WP-05 | Contract planning started | Prediction identity/scope/resolution and correct outcome-attribution contract. |
| WP-06 | Contract planning started | Multi-owner approval, atomicity, persistence, containment and negative-transfer criteria. |
| WP-07 | Contract planning started | Accepted ownership boundaries and no deterministic stimulus-to-behavior shortcuts. |
| WP-08 | Protocol drafted (R0–R6) | Approved baseline, frozen fixtures/holdouts/metrics, environment manifest and separate run authorization. |

“Planning started” is not “package activated.” No work package in this table is authorized for runtime execution.

## 7. Change-control and activation rules

A future activation request must identify exactly one bounded package and include:

- exact accepted architecture/specification revisions;
- exact selected source baseline and parent SHA;
- affected paths, symbols and state owners;
- scenario IDs and required evidence classes;
- dependency and concurrency plan;
- compatibility and regression impact;
- negative-path, persistence, recovery and containment tests;
- rollback/stop criteria;
- reviewer and Project Director decision requirements.

The request must fail closed if any required authority, source identity or evidence is missing. A work package must not broaden itself into adjacent implementation, infrastructure, autonomy or deployment work.

## 8. What can proceed now under existing non-operative planning authority

1. Improve scenario-to-source *planning* traceability using exact source evidence without selecting a source baseline.
2. Refine owner contracts and cross-mechanism acceptance definitions, preserving unresolved specification decisions as explicit questions.
3. Reconcile the first learning-run measurement definitions and fixture leakage controls before any run.
4. Prepare a decision-ready Gate A evidence index that identifies exactly which high-risk semantic and API questions remain.
5. Prepare separate exact-revision review assignments for PR #173, PR #174, PR #192 and PR #197; never combine their review scopes or transfer verdicts across SHAs.

No runtime source changes, runtime builds/tests, training runs, donor ports, branch-history operations, merges, releases or deployments are included.

## 9. Planning exit and transition decision

The planning package is ready for a Project Director planning disposition when:

- WP-00–WP-08 have stable owners, dependencies, capability outcomes and evidence classes;
- the first integrated learning capability and R0–R6 evaluation are coherent;
- the 34-scenario accepted historical baseline and 54-scenario current proposal are explicitly separated;
- all upstream architecture/specification/Documentation Foundation/Gate A/Gate B decisions are visible;
- the exact activation checklist in §7 is satisfied for any proposed first package.

This document records that implementation planning is underway and gives it a controlled transition map. It does **not** declare the Documentation Foundation closed, Gate A cleared, Gate B passed, an implementation baseline selected, Stage A started, or runtime implementation authorized.

**Current disposition:** Planning Run 02 opened; non-operative planning may continue. Runtime implementation and starter-training execution remain NOT AUTHORIZED pending the required exact-revision decisions.
