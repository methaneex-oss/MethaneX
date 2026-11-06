# JARVIS Project Continuity & Recovery Handoff

> **Current scope correction — 2026-11-07 (read before all historical status below):** The older phase/status and next-action instructions in this handoff were written for Brain Implementation Planning and Gate A/Gate B work. They are historical snapshots and are superseded for the immediate next task by the [Whole-Brain Planning Scope and Builder Correction](https://github.com/methaneex-oss/MethaneX/blob/docs/whole-brain-planning-scope-correction-20261107/docs/architecture/reports/WHOLE_BRAIN_PLANNING_SCOPE_AND_BUILDER_CORRECTION_2026-11-07.md). The current next task is whole-Brain capability definition, not implementation planning, source selection or runtime work. Preserve the earlier evidence and gate history; do not silently treat the old "current phase" wording as current.

**Last updated:** 2026-11-07  
**Purpose:** This is the authoritative restart point for any new ChatGPT conversation, collaborator, or agent continuing this project. Read this document before taking action. Do not rely on chat memory as the source of truth.

## 1. Project identity and objective

This is an existing, long-running JARVIS cognitive architecture project in `methaneex-oss/MethaneX`. It is not a new project.

The objective is to engineer a real, integrated cognitive system whose capabilities and behavioral tendencies can improve through experience. The governing principle is:

> **Engineer the mechanisms; let behavior be acquired through experience.**

Do not reduce the project to a chatbot, thin LLM wrapper, fixed rule engine, hardcoded behavior tree, or static knowledge database. Do not restart or generically redesign it.

The human-cognition and MCU J.A.R.V.I.S. comparisons are reference lenses for analysis, not permission to invent fictional internals or copy fictional capabilities as if they were engineering specifications.

## 2. Current phase — read this first

**Current phase: Whole-Brain architectural planning — Stage A capability and responsibility definition. Development planning and implementation are deferred.**

Accepted upstream work:
- **PR #171** — whole-system foundation.
- **PR #172** — foundational Brain capability investigation.
- **PR #173** — integrated Brain foundation architecture.
- **PR #174** — integrated Brain mechanism specification. This is the governing mechanism specification; accepted HEAD: `0811a59e46bf934e32e794f90e4e7d18d4e2bd97`.

Current planning work:
- **PR #175** — Brain implementation roadmap / planning.
- Branch: `plan/brain-implementation-roadmap-20261103`.
- Latest known HEAD: `5088c0644658f573bd18cf579ba426bb51dfb506`.
- PR: https://github.com/methaneex-oss/MethaneX/pull/175

### Exact subphase: Gate A — repository baseline reconciliation

Gate A's final disposition has been documented as:

**NOT CLEARED — NO IMPLEMENTATION BASELINE SELECTED.**

The disposition document is:
`docs/architecture/plans/reviews/03_GATE_A_FINAL_DISPOSITION_2026-11-03.md`

Direct link:
https://github.com/methaneex-oss/MethaneX/blob/plan/brain-implementation-roadmap-20261103/docs/architecture/plans/reviews/03_GATE_A_FINAL_DISPOSITION_2026-11-03.md

Detailed reconciliation checkpoint:
`docs/architecture/plans/reviews/02_GATE_A_REPOSITORY_BASELINE_RECONCILIATION_2026-11-03.md`

PR #156 is a **candidate only**, not an accepted implementation baseline. Do not rebase, cherry-pick, merge, rewrite history, or start implementation from it.

The final-disposition review assignment was posted as PR #175 comment:
https://github.com/methaneex-oss/MethaneX/pull/175#issuecomment-6615019538

Live verification on 2026-11-03 confirms zero submitted reviews on PR #175 and no requested reviewers. The Project Director supplied a reviewer-status report; it accurately states the no-go position but is not a technical independent review verdict. The Builder completed a separately labelled technical re-review in `04_GATE_A_BUILDER_TECHNICAL_REREVIEW_2026-11-03.md`. Do not present that Builder-side review as independent approval.

### Subsequent reviewer-status report supplied by the user

The user supplied a report clarifying the current state. It confirms:
- PR #175 is open.
- Gate A remains not cleared.
- PR #156 remains candidate only.
- No implementation baseline has been selected.
- Gate B and implementation remain unauthorized.
- The next action remains an independent technical review of the Gate A reconciliation evidence.

The report's recommendation is deliberately neutral: do not select PR #156 merely because it contains substantial existing work, and do not reject it merely because its history diverges. The decision must follow technical examination of the history, integration differences, and evidence.

**Classification:** This supplied report is a status/recommendation note, not a completed independent technical verdict. It does not clear Gate A, select a baseline, or authorize the next stage. The review is still pending operationally; no submitted review or formal GitHub reviewer request should be claimed unless live repository metadata confirms it.

## 3. What Gate A found and why it is not cleared

The reconciliation records substantial evidence about candidate history and files, but important questions remain unresolved:
- exhaustive commit-to-file and origin attribution across the inherited history;
- semantic reconciliation of divergent integration files;
- 24 differing Brain API function bodies and two definitions requiring manual alignment;
- a final defensible choice of implementation baseline.

The checkpoint contains a 1,416-commit enumeration and a 165-path net tree inventory. These are recorded evidence, not proof that all semantic reconciliation is complete.

PR #156 remains useful as an evidence-bearing candidate. It is not approved as the base to build on.

## 3A. Combined Gate A / Gate B work completed on 2026-11-03

The Project Director explicitly authorized both gates to proceed together as static review, traceability and documentation work. The main objective remains the JARVIS learning cognitive architecture.

- **Gate A Builder technical re-review:** `docs/architecture/plans/reviews/04_GATE_A_BUILDER_TECHNICAL_REREVIEW_2026-11-03.md`.
  - Confirms the no-go disposition is justified.
  - PR #156 remains a candidate only.
  - The 1,416 inherited commits still lack complete commit-to-origin/path/hunk attribution.
  - Divergent PR #151/#150 integration hunks, 24 Brain API body differences, two unmatched definitions and five workflow files remain unresolved.
  - This is a Builder-side review, not an independent reviewer verdict.

- **Gate B static traceability audit:** `docs/architecture/plans/reviews/05_GATE_B_MECHANISM_TRACEABILITY_AUDIT_2026-11-03.md`.
  - Maps BM-01 through BM-12 to candidate source at exact code-bearing parent `15d49e5fdeb5723c475922ab78fb92f97c4b3b84`.
  - Static traceability is complete for all 12 mechanism owners.
  - Mechanism acceptance is **NOT PASSED**; the audit does not claim all 34 acceptance scenarios pass.
  - No build, runtime test, benchmark or sanitizer was run.

- The main implementation plan was upgraded to include these results and correct the BM-12 integration description.
- Important correction: candidate reasoning conclusions feed forward simulation/prediction. Retrieved memories are still omitted from reasoning premises, and the full BM-12 premise/assumption/provenance/alternative/counterexample/dependency lineage is not demonstrated.

**Combined disposition:** Gate B static traceability complete; capability acceptance not passed. Gate A not cleared; no implementation baseline selected. PR #156 remains a candidate only.

**Still unauthorized:** runtime source changes, builds, tests, benchmarks, technology/schema/API selection, rebase, cherry-pick, merge, history rewrite, deployment and implementation. The combined authorization covered review, traceability and documentation upgrades only.

## 3B. Gate A semantic reconciliation update — 2026-11-04

A separate static addendum was completed:

`docs/architecture/plans/reviews/06_GATE_A_SEMANTIC_RECONCILIATION_ADDENDUM_2026-11-04.md`.

It:
- classifies all 24 common Brain API body differences between candidate and current-main restoration;
- manually confirms `beliefs()` is identical and records the `register_evolution_parameter()` bool-versus-void signature change;
- identifies seven candidate-only APIs;
- reviews PR #151 → #155 and PR #150 → #156 integration fidelity;
- classifies all five current-main workflow paths and verifies all 35 learning-mechanism workflow test target names exist in candidate CMake;
- identifies two confirmed candidate risks: learned-strategy context can be keyed to the wrong goal, and non-finite goal values can be journaled before GoalModel rejects them;
- records unresolved partial-failure/replay ordering questions.

The API restoration is substantially reconciled at source-body level, but caller/build compatibility has not been verified. The candidate risks are recorded for remediation; no runtime changes were made.

**Gate A remains NOT CLEARED.** The full per-commit origin/path/hunk attribution across the 1,416 inherited commits remains incomplete, particularly the 1,244-commit PR #97 history. GitHub tooling available in this session does not expose an exhaustive paginated commit/file-patch inventory, so no false claim of completion is made. Independent review is still absent; no reviewer username/team or CODEOWNERS entry is available to request.

## 4. What happens next — in order

1. **Complete independent Gate A review.** Reviewer must challenge the disposition, reproduce critical refs/blob claims, distinguish verified from unverified claims, and state whether any correction is needed.
2. **Resolve reviewer findings.** Record corrections and their evidence in a separate review/correction document under `docs/architecture/plans/reviews/`, not by silently rewriting the accepted specification or burying findings in the main planning document.
3. **Return the Gate A decision to the Project Director (the user).** Do not treat reviewer approval as Project Director acceptance.
4. **Gate B static traceability is now complete for BM-01 through BM-12.** Its acceptance gaps are recorded; do not call it passed merely because the matrix is complete.
5. **Complete Gate A's remaining commit/path/hunk and semantic reconciliation, then obtain independent review of both audit records.** Present the combined evidence and baseline recommendation to the Project Director.
6. **Only after a baseline decision, accepted implementation plan and separate explicit implementation authorization** may runtime implementation begin.

Do not skip stages to make the project appear to be progressing.

## 5. Non-negotiable engineering principles

- Preserve the accepted PR #174 specification as the governing mechanism contract.
- Analyze the system as an interacting whole. Learning is not a single file or subsystem.
- The meaningful criterion is persistent, experience-dependent change in later prediction, belief, attention, memory, reasoning, valuation, decisions, and/or behavior—not merely code presence or isolated passing tests.
- Do not hardcode mappings such as stimulus → emotion, negative affect → reject, failure → trauma, success → reward, or fixed stimulus → action.
- Do not preload a finished personality, fixed goals, preferences, or behavioral repertoire and call it learning.
- Distinguish initial enabling capacities from competencies acquired through experience.
- Treat cognition as recurrent, interruptible, and potentially parallel—not necessarily one rigid linear pipeline.
- Preserve the separation between cognitive intent, governance permission, execution, and verified consequence.
- Claims of learning must be supported by evidence that experience changes persistent internal state and affects future outcomes under appropriate tests.
- Do not claim human-level cognition, MCU-level capability, consciousness, or general intelligence from subsystem demonstrations.

## 6. Working rules for the assistant / agents

1. **Act as the builder when authorized.** Do not speak about “what the Builder should do” as if you are not the builder. State what you will do.
2. **Inspect the repository before asserting facts.** Use exact branches, commit SHAs, paths, blobs, diffs, and source evidence. Chat memory is context, not repository evidence.
3. **Respect authorization boundaries.** The Project Director has authorized Gate A and Gate B to proceed together as static review/traceability and documentation work. Runtime changes, builds, tests, technology choices, schema/API decisions, rebase/cherry-pick/merge, branch rewriting and deployment remain unauthorized.
4. **Do not claim actions that did not happen.** Distinguish code inspected from code changed, tests run from existing CI evidence, and requested reviews from submitted reviews.
5. **Document work.** Record findings, corrections, exact evidence, and verification in accessible repository documentation. Keep correction/review records separate from the main planning document where appropriate.
6. **Fix root causes.** Do not apply speculative patches or create follow-on changes without understanding the failure and its affected contracts.
7. **Keep communication concise and orienting.** The user has explicitly said lengthy explanations cause confusion. Start with current phase, what changed, what is blocked, and the next action. Expand only when needed.
8. **Avoid unnecessary long-running tool work.** Prefer bounded repository operations. If a local checkout/manual step is materially faster or safer, explain that rather than wasting time.
9. **Never silently change project direction.** No restart, generic redesign, chatbot conversion, premature implementation, or hardcoded behavior shortcuts.
10. **The user's approval is distinct from reviewer approval.** A reviewer assesses evidence; the user decides project direction and grants stage authorization.

## 7. Important interpretation of the 12 mechanisms

The accepted PR #174 specification defines 12 Brain mechanisms (BM-01 through BM-12). Use the exact specification for their names, boundaries, ownership, and acceptance criteria. Do not reconstruct or paraphrase the 12-mechanism list from memory when the source document is available.

Known areas that have required special scrutiny include:
- BM-05 causal attribution and prediction scope/resolution;
- BM-06 active context and attention integration;
- BM-08 experience-acquired candidate-goal formation;
- BM-10 corrective metacognition;
- BM-12 memory-to-reasoning flow and inference lineage.

These are audit priorities, not a substitute for tracing all 12 mechanisms.

## 8. Key repository references

- Repository: https://github.com/methaneex-oss/MethaneX
- Current planning PR: https://github.com/methaneex-oss/MethaneX/pull/175
- Accepted specification PR: https://github.com/methaneex-oss/MethaneX/pull/174
- Gate A detailed checkpoint: https://github.com/methaneex-oss/MethaneX/blob/plan/brain-implementation-roadmap-20261103/docs/architecture/plans/reviews/02_GATE_A_REPOSITORY_BASELINE_RECONCILIATION_2026-11-03.md
- Gate A Builder technical re-review: https://github.com/methaneex-oss/MethaneX/blob/plan/brain-implementation-roadmap-20261103/docs/architecture/plans/reviews/04_GATE_A_BUILDER_TECHNICAL_REREVIEW_2026-11-03.md
- Gate B 12-mechanism traceability audit: https://github.com/methaneex-oss/MethaneX/blob/plan/brain-implementation-roadmap-20261103/docs/architecture/plans/reviews/05_GATE_B_MECHANISM_TRACEABILITY_AUDIT_2026-11-03.md
- Gate A semantic reconciliation addendum: https://github.com/methaneex-oss/MethaneX/blob/plan/brain-implementation-roadmap-20261103/docs/architecture/plans/reviews/06_GATE_A_SEMANTIC_RECONCILIATION_ADDENDUM_2026-11-04.md
- Gate A final disposition: https://github.com/methaneex-oss/MethaneX/blob/plan/brain-implementation-roadmap-20261103/docs/architecture/plans/reviews/03_GATE_A_FINAL_DISPOSITION_2026-11-03.md
- Gate A Builder technical re-review: https://github.com/methaneex-oss/MethaneX/blob/plan/brain-implementation-roadmap-20261103/docs/architecture/plans/reviews/04_GATE_A_BUILDER_TECHNICAL_REREVIEW_2026-11-03.md
- Gate B 12-mechanism traceability audit: https://github.com/methaneex-oss/MethaneX/blob/plan/brain-implementation-roadmap-20261103/docs/architecture/plans/reviews/05_GATE_B_MECHANISM_TRACEABILITY_AUDIT_2026-11-03.md
- Independent review assignment: https://github.com/methaneex-oss/MethaneX/pull/175#issuecomment-6615019538


## 3C. Risk-based Gate A closure assignment — 2026-11-04

The Project Director authorized the focused closure assignment. Read:

`docs/architecture/plans/reviews/07_GATE_A_CLOSURE_ASSIGNMENT_2026-11-04.md`.

The assignment replaces an unbounded requirement to write a per-commit hunk record for all 1,416 inherited commits with a risk-based standard:
- account for all 165 final-tree paths;
- deepen attribution for unexplained, overlapping, conflict-resolved, replaced, or high-risk paths;
- explicitly classify residual gaps by risk and baseline-decision impact;
- do not waive unexplained high-risk changes based on aggregate counts.

Five closure workstreams are now defined: provenance/final-tree integrity; API declaration and caller compatibility; continuity of all five current-main workflows; remediation specifications for the two confirmed candidate defects; and an independent-review packet.

The two defects remain **confirmed, unfixed, and outside current runtime authorization**:
- learned-strategy retrieval can use an eligible goal different from the selected active intent;
- NaN goal values can reach the journal before model rejection; future remediation must reject all non-finite inputs before event creation.

### Current Gate A execution rules

- Work only on documentation and static inspection under the current authorization.
- Create the separate evidence artifacts specified in assignment 07. Do not fill gaps with assumptions.
- Verify the live PR head before each repository write and before assembling the review packet.
- Do not request a GitHub reviewer until an actual username/team with repository access is supplied or otherwise verified.
- Do not claim a formal independent review based on the user's supplied report; it was not a submitted GitHub review.
- Gate A remains NOT CLEARED until all technical closure criteria, actual independent review, and the Project Director's baseline decision are satisfied.
- Runtime changes, builds, tests, history operations, baseline selection, and implementation remain unauthorized.

The next builder action is to produce the provenance, API compatibility, workflow continuity, and defect-disposition evidence artifacts from exact repository sources, then assemble the review packet. Avoid repeating already completed inventories or broad historical reconstruction where it cannot change the decision.


## 3D. Gate A closure evidence package — 2026-11-04

The bounded assignment is in review document 07. Initial separate evidence artifacts are now present:

- 08 — 165-path risk-based provenance matrix. It reconstructs the recorded 145 / 14 / 6 origin classes; it is not full semantic/hunk closure.
- 09 — API compatibility matrix. It records the 24 body differences, seven candidate-only APIs and signature concern; declaration/overload/caller inventory remains open.
- 10 — workflow continuity matrix. It records all five workflow dispositions; no workflow was executed.
- 11 — candidate defect disposition. D1/D2 remain confirmed and unfixed, with future acceptance criteria.
- 12 — independent review packet. It consolidates evidence, review questions, known limits and required verdict format.

These artifacts are initial evidence, not a Gate A clearance. High-risk per-path semantic attribution and API caller compatibility remain open. The independent review packet is assembled, but no reviewer identity has been supplied and no formal reviewer request or submitted review exists.

Continue static inspection/documentation only. Gate A remains NOT CLEARED; PR #156 remains candidate only. No runtime changes, builds, tests, workflow executions, history operations, or baseline selection are authorized.

## 9. Startup instructions for a new chat

When continuing this project:

1. Read this document in full.
2. Read the current PR #175 description and latest comments/reviews.
3. Read the Gate A final-disposition document and detailed Gate A checkpoint.
4. Read the accepted PR #174 specification when mechanism-level questions arise.
5. Verify the live PR head and review state; this handoff may become stale.
6. State the current phase and the single next authorized action to the user.
7. Do not repeat completed work, reopen settled upstream stages without evidence, or start Gate B/implementation without explicit authorization.

### Required first response in a recovery chat

Give the user a short status update in this format:

- **Phase:** Brain Implementation Planning — Gate A reconciliation + Gate B traceability.
- **Last decision:** Gate A not cleared; Gate B static traceability complete but capability acceptance not passed.
- **Current blocker:** per-commit origin/path/hunk attribution for the 1,416 inherited commits remains incomplete; independent review is not submitted.
- **Next action:** Close remaining Gate A evidence gaps and obtain independent review before baseline selection.
- **Not authorized:** Runtime implementation, builds/tests, history rewrites, merge or deployment.

If repository state contradicts this document, trust the verified live repository state, explain the discrepancy, and update this handoff through a documented commit. Never silently assume this snapshot is still current.


## 10. Final Builder-side Gate A recommendation — 2026-11-04

Read `docs/architecture/plans/reviews/13_GATE_A_FINAL_BASELINE_RECOMMENDATION_2026-11-04.md`
for the final evidence-based baseline recommendation.

- **Recommended integration starting point:** accepted PR #174 HEAD
  `0811a59e46bf934e32e794f90e4e7d18d4e2bd97`.
- **Candidate PR #156:** do not merge/cherry-pick/adopt wholesale. Treat code-bearing
  parent `15d49e5fdeb5723c475922ab78fb92f97c4b3b84` as a source donor for
  selective, reviewed ports.
- **Why:** candidate is substantially divergent, predates the accepted spec,
  contains confirmed D1/D2 defects, lacks current-main validation workflows,
  and does not meet all 34 accepted Brain foundation scenarios. It nevertheless
  contains substantial reusable mechanisms and should not be discarded.
- **Mandatory carry-forward:** preserve current validation workflow semantics;
  fix D1/D2 before accepting affected capabilities; prove goal-completion and
  evolution rollback failure/replay boundaries; map each port to BM-01–BM-12
  and the relevant acceptance scenarios.
- **Status:** Builder technical recommendation is complete. Formal Gate A is
  still NOT CLEARED because no independent PR #175 review has been submitted
  and no Project Director baseline decision has been recorded.
- **Authority:** no runtime changes, builds, tests, workflow executions, merge,
  rebase, cherry-pick, history rewrite or deployment were performed or
  authorized by this audit. A separate explicit implementation authorization
  remains required.

### Recovery response update

- **Phase:** Brain Implementation Planning — final Builder-side Gate A recommendation recorded; formal Gate A approval pending.
- **Last technical recommendation:** accepted PR #174 HEAD as integration base; PR #156 as selective source donor only.
- **Current governance blocker:** independent review and Project Director baseline decision.
- **Next action:** review the final recommendation and decide whether to authorize the selective-port implementation plan.
- **Not authorized:** runtime implementation, builds/tests, workflow runs, merge/rebase/cherry-pick or deployment.



## Latest Gate A closure handoff — 4 November 2026

Consolidated evidence: docs/architecture/plans/reviews/16_GATE_A_CLOSURE_EVIDENCE_UPDATE_2026-11-04.md.

### Current evidence state

- Provenance corrected to 143 PR #97-only unchanged, 16 overlap, 2 post-PR #97 modified-existing, 4 post-PR #97 additions. See Report 08 §7.
- Static public Brain API inventory completed within core/cpp: 26 candidate-only public method names, overloads/signature changes and complete exact-identifier call-site scan. External ABI/downstream compatibility remains a later compile/link gate. See Report 09 §7.
- Five current-main workflow preservation/adaptation specifications completed. See Report 10 §5.
- D1/D2 corrections and regression tests are on draft PR #176. PR #156 remains unchanged until the correction is reviewed and merged or the fixes are selectively ported.
- Deterministic tests now cover goal completion's second append failure, evolution canary rollback's second append failure, manual rollback append failure, and restart replay after a durable rollback event. Deeper EvolutionController compensation failure injection remains open.

### PR #176 donor correction verification

- PR: https://github.com/methaneex-oss/MethaneX/pull/176
- Head: 4cf017e073da980c9f77d739fde6f92ef1a2fbc1
- Draft and unmerged; no cherry-pick/merge into PR #175.
- Brain CI: https://github.com/methaneex-oss/MethaneX/actions/runs/41808525499 — passed.
- Native Brain Build: https://github.com/methaneex-oss/MethaneX/actions/runs/41808525486 — passed.
- Brain ThreadSanitizer: https://github.com/methaneex-oss/MethaneX/actions/runs/41808525492 — passed.
- JARVIS Brain Tests: https://github.com/methaneex-oss/MethaneX/actions/runs/41808525557 — passed.
- Native, ASan/UBSan and ThreadSanitizer CTest runs each passed 73/73 tests. The goal and evolution failure/replay tests passed.

### Remaining authority and Gate A boundaries

- Gate A remains NOT CLEARED.
- Report 14 is a technical review document, not a formal GitHub review submission. A separate independent re-check is still required; no distinct reviewer username has been supplied.
- The deeper controller-internal compensation failure boundary remains unverified.
- PR #175 remains documentation-only. Do not merge PR #176, merge PR #175, cherry-pick/rebase, select a baseline or start implementation without explicit Project Director authorization.
- The recommended strategy remains accepted PR #174 as the integration starting point and PR #156 as a selective source donor only.


### PR #176 branch/PR snapshot discrepancy

A follow-up controller-history compensation test was committed to the branch ref as a37add18babf8afc2e9c12ca0449a2ee84ecd60d. However, the live PR #176 metadata and its Actions runs still report head 4cf017e073da980c9f77d739fde6f92ef1a2fbc1; the PR commit list does not include a37add18. Do not count that follow-up test as part of the verified PR until the branch/PR snapshot is synchronized and CI passes at the updated head. The deeper controller compensation boundary therefore remains open.

---

## 11. Current whole-Brain planning direction — 2026-11-07

**Current immediate stage:** Whole-Brain architectural planning — Stage A, capability and responsibility definition.

The Project Director has clarified the required order: plan the entire future Brain first; only after the whole-Brain capability architecture, mechanism architecture and completeness/reconciliation are accepted may the project decide where development should begin and what existing source to use.

The three required reference lenses are:
1. **Human brain and cognition:** investigate functions, interactions, development, limitations and scientific uncertainty; do not copy biological anatomy literally.
2. **MCU J.A.R.V.I.S.:** derive functional aspirations from the fictional assistant; do not invent its internals or treat fiction as scientific evidence.
3. **Developing-Brain analogy:** engineer enabling mechanisms and the capacity to develop; let knowledge, skills, strategies and increasingly capable behavior be acquired through experience rather than preloading a finished personality or behavioral repertoire.

BM-01–BM-12 remain valuable existing specification work, but they are not assumed to exhaust the future Brain. The Phase 2 source map is a partial mechanism-to-source integration investigation, not proof of whole-Brain completeness. Phase 1's technical repository audit remains useful and complete only within its declared static investigation scope; it did not define the complete Brain.

### Immediate instructions

- Read the linked correction document in full.
- Preserve Phase 1/Phase 2 reports, exact evidence and accepted-history records.
- Read PR #171–#174 as existing architecture and research inputs; challenge completeness rather than blindly replacing them.
- Do not choose mechanisms, add arbitrary mechanism counts, select development order, choose source reuse, or select algorithms/languages/providers/databases/APIs at Stage A.
- Produce a whole-Brain capability definition with explicit coverage, gaps, unknowns and reference rationale.
- Derive the mechanism architecture and interaction model only after the capability analysis is sufficiently complete.
- Obtain independent review and Project Director acceptance before moving into development planning.
- No implementation, baseline selection, merge/rebase/cherry-pick, builds, tests, or runtime changes are authorized by this documentation correction.

### Prior Builder error acknowledgement

ChatGPT (GPT-6), the Builder responsible for the earlier planning responses, made a scope error by treating BM-01–BM-12 as the effective boundary for whole-Brain planning, confusing source integration mapping with complete capability definition, and recommending movement toward development planning before whole-Brain completeness had been established. This error is recorded explicitly in the linked correction document. The previous work is not discarded; its authority and completeness claims are corrected.

**Handoff rule:** If any older section in this document conflicts with this §11 or the linked 2026-11-07 correction, follow the newer scope correction while preserving the older section as historical evidence.

