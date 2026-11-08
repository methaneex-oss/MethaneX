# JARVIS Phase 1 — Existing Documentation and Artifact Inventory

**Status:** Working inventory; not an approval, architecture decision, archive operation, or implementation authorization.  
**Prepared:** 2026-11-04  
**Repository:** `methaneex-oss/MethaneX`  
**Inventory baseline:** `main` at `1273ddbcd0087d189e01388ded2d362fb1e058d2` (the base SHA recorded by PRs #171–#175 at inspection).  
**Inventory branch:** `docs/jarvis-phase-1-preservation-inventory-20261104`  
**Governing principle:** **Engineer the mechanisms; let behavior be acquired through experience.**

---

## 1. Purpose

This inventory is the first preservation and continuity artifact for the current planning effort.

Its purpose is to establish what already exists before further JARVIS research and architecture work proceeds. It prevents a new planning effort from unknowingly duplicating, contradicting, discarding, or treating provisional work as approved.

The project destination remains the complete JARVIS system. The Brain is the first implementation target, not the entire product.

This document does not declare the existing architecture complete. It does not freeze every previous decision. It does not authorize implementation, migration, deletion, document relocation, merge, or baseline selection.

## 2. Inventory rules

Every artifact must be classified by both content and authority. A file's presence, branch, pull request, title, or apparent completeness does not make it authoritative.

Use these statuses:

- **Approved within stated scope:** an explicit Project Director approval exists for the exact artifact/revision and only for its stated scope.
- **Accepted planning input:** the Project Director has accepted the work for use in a subsequent planning stage; this does not imply merge or implementation authorization.
- **Proposed / draft:** submitted for review or decision but not accepted as authoritative.
- **Working research:** evidence and hypotheses to inspect; not an approved architecture.
- **Historical / superseded candidate:** retained as evidence or prior work; not automatically governing.
- **Unverified:** the available evidence does not establish its status or underlying claim.

No file is to be deleted or moved during this inventory. Historical preservation must be established before any later archive relocation. Any eventual relocation must preserve Git history and update references.

## 3. Whole-system architecture foundation — PR #171

**PR:** [#171 — JARVIS System Architecture Foundation](https://github.com/methaneex-oss/MethaneX/pull/171)  
**Branch:** `docs/jarvis-system-architecture-foundation-20261101`  
**Inspected HEAD:** `b05434758ad4fe72815503f89bd5d2990ccb658b`  
**PR state at inspection:** open, draft, unmerged.  
**Important authority distinction:** Documents 00 and 01 have separate Project Director approvals recorded in the PR discussion for exact earlier revisions. Those approvals are limited to their stated scopes. The research package and the PR as a whole are not thereby approved.

### 3.1 Document 00 — System Architecture Foundation

Path: `docs/architecture/00_JARVIS_SYSTEM_ARCHITECTURE_FOUNDATION.md`  
Blob at inspected PR HEAD: `db0f136b3aaa338fb7d06d7be9e50bb42fc82821`  
Length: 348 lines.

Classification: **Approved within stated scope**, subject to its own recorded exact-revision qualification.

Established principles include:

- JARVIS is the complete intended intelligent system; Brain-first is construction order, not product scope.
- Engineer mechanisms rather than hardcode learned conclusions, preferences, associations, emotions, strategies, or behavior.
- Deterministic engineering remains appropriate for integrity, validation, protocols, security, permissions, resource limits, and explicit invariants.
- Biological organization is an inspiration, not a literal software blueprint.
- One coherent cognitive authority; cognitive intent is distinct from governance authorization and execution.
- Evidence must distinguish concepts, proposals, approved decisions, specifications, implementations, tests, and demonstrated capabilities.

Crucially, Section 6 explicitly says this is a documentation reset, not destruction of history. It requires a separate document inventory and disposition review before old documents are treated as governing references. That is the work this Phase 1 inventory begins.

### 3.2 Document 01 — Whole-System Anatomy and Responsibility Map

Path: `docs/architecture/01_JARVIS_WHOLE_SYSTEM_ANATOMY_AND_RESPONSIBILITY_MAP.md`  
Blob at inspected PR HEAD: `2b595af4fefb54c7f8dc81fb997d4d391f2250e0`  
Length: 873 lines.

Classification: **Approved within stated scope**, subject to its own recorded exact-revision qualification.

It maps eleven proposed system responsibility domains (SYS-01 through SYS-11), cross-system interactions, ownership boundaries, and staged approval gates.

Important limitation: the document explicitly describes a **functional architecture**, not a final code/module decomposition. Its top-level map is proposed anatomy and responsibility allocation. It is not yet a complete executable system architecture with all computational dynamics, timing, concurrency, failure, deployment, resource, and lifecycle semantics settled.

This document is a governing whole-system input, not proof that complete JARVIS planning is finished.

### 3.3 Research package in PR #171

- `docs/architecture/research/00_BRAIN_FOUNDATION_COMPARATIVE_RESEARCH_AND_DECISION_LOG.md` — blob `f84077179f9fa8e151b5faca39940e43a13db2a2`, 2,402 lines.
- `docs/architecture/research/01_BRAIN_FOUNDATION_MECHANISM_GAP_ANALYSIS.md` — blob `a90204f28c09dd9c1e2e0e1b24d108a58dc82b46`, 277 lines.
- `docs/review-records/brain-foundation/2026-11-02_REVIEW_CORRECTION_EVIDENCE.md` — included in PR #171; correction evidence, not architecture authority.

Classification: **Working research / provisional**. The comparative log contains investigations A–G and cross-investigation synthesis. It includes human-cognition and MCU J.A.R.V.I.S. comparisons, integration questions, provisional directions, alternatives, references, and unresolved issues. The gap analysis identifies representational, perceptual-grounding, integration, and learning questions.

These are substantial prior research assets. They must be audited for depth, evidence quality, coverage, contradictions, and remaining unknowns before deciding what further research is necessary. Do not repeat them blindly, and do not assume their length establishes completeness.

PR #171's description also records that the actual execution start/end and completion receipts for a later authorized 60-minute investigation were not established. Do not treat that particular session as verified merely because its intended work is described.

## 4. Foundational capability investigation — PR #172

**PR:** [#172 — Foundational Brain Capability Investigation](https://github.com/methaneex-oss/MethaneX/pull/172)  
**Branch:** `research/brain-capability-investigation-20261103`  
**Inspected HEAD:** `d7d676b79dbf3269f7fd3ebdb4363a6df19f255d`  
**Document:** `docs/architecture/research/02_BRAIN_FOUNDATIONAL_CAPABILITY_INVESTIGATION_2026-11-03.md`  
**Blob:** `410edf234f79d9a370fb63deffaaf22cfed9ec9c`  
**Length:** 318 lines.  
**PR state:** open, draft, unmerged.  
**Project status:** accepted by the Project Director as a planning input, according to the recorded project handoff; the PR's open/draft state is separate from that acceptance.

The report compares three references: MCU J.A.R.V.I.S., human cognition, and inspected JARVIS engineering reality. It distinguishes initial, acquired, and hybrid capability; emphasizes that learning is a property of the whole cognitive system; and explicitly warns that a capability table is not a decision to create one software module per row.

It is a bounded capability investigation, not a complete neuroscience review or whole-system architecture. Its own unresolved questions must feed later research and architecture.

## 5. Brain foundation architecture — PR #173

**PR:** [#173 — Integrated Brain Foundation Architecture](https://github.com/methaneex-oss/MethaneX/pull/173)  
**Branch:** `architecture/brain-foundation-planning-20261103`  
**Inspected HEAD:** `97191111bc2573c14d391c0af9628db7b11f194b`  
**Document:** `docs/architecture/02_BRAIN_FOUNDATION_ARCHITECTURE.md`  
**Blob:** `364aa3b5fabdab527c169ab170dd72e23c502438`  
**Length:** 594 lines.  
**PR state:** open, draft, unmerged.  
**Historical status claim:** later project handoff material reports that this exact revision was accepted as a Brain architecture planning baseline. The current documentation audit did not recover the primary exact-revision Project Director decision record from PR #173's discussion. Treat the acceptance provenance as unresolved pending recovery or an explicit authority disposition; do not promote this historical handoff claim to independently verified acceptance.

The proposal includes one cognitive authority, recurrent/branching/concurrent cognition, authoritative state ownership with shared context, plural representations, epistemic distinctions, experience-dependent development, intent/authorization separation, and capability-level acceptance criteria.

It is a Brain foundation architecture, not the complete JARVIS whole-system architecture. It must remain an input to the wider JARVIS design, not a substitute for it.

## 6. Integrated Brain mechanism specification — PR #174

**PR:** [#174 — Integrated Brain Mechanism Specification](https://github.com/methaneex-oss/MethaneX/pull/174)  
**Branch:** `spec/brain-mechanism-specification-20261103`  
**Live PR HEAD at inspection:** `0811a59e46bf934e32e794f90e4e7d18d4e2bd97`  
**Primary document:** `docs/architecture/specifications/00_BRAIN_MECHANISM_SPECIFICATION.md`  
**Blob:** `3b6a53c8a295fa0d9fc29bbb6c7688b61d1dcdb1`  
**Length:** 893 lines.  
**PR state:** open, draft, unmerged.

Other files:
- Existing mechanism source audit: `docs/architecture/specifications/research/00_BRAIN_EXISTING_MECHANISM_SOURCE_AUDIT_2026-11-03.md`.
- Review correction record: `docs/architecture/specifications/reviews/00_BRAIN_MECHANISM_SPECIFICATION_REVIEW_CORRECTIONS_2026-11-03.md`.

The specification describes twelve logical mechanism responsibilities, cross-mechanism contracts, recurrent interaction patterns, failure semantics, and acceptance scenarios. It is useful work and must not be discarded.

**Current review qualification:** the Project Director supplied a subsequent independent re-review outcome identifying F-02 (contextual language/operator-intent grounding) and F-03 (downstream reasoning integration) as unresolved. PR #175's description currently calls PR #174 accepted. These records conflict. Until the exact reviewer report, current PR discussion, and Project Director decision are reconciled, PR #174 must not be represented as unconditionally accepted or final.

The live PR metadata showed no submitted GitHub review records at the time of this inventory. The user-supplied independent report is a separate review artifact and must be preserved/linked when its authoritative location is established.

## 7. Brain implementation roadmap and Gate A — PR #175

**PR:** [#175 — Brain Implementation Roadmap](https://github.com/methaneex-oss/MethaneX/pull/175)  
**Branch:** `plan/brain-implementation-roadmap-20261103`  
**Live PR HEAD at inspection:** `874c732973b6ab303d65a503f5a215b0af8e1153`  
**PR state:** open, draft, unmerged; mergeability reported false at inspection.

Primary documents:
- `docs/architecture/plans/00_BRAIN_IMPLEMENTATION_PLAN.md` — blob `9511cda1389e47c94dcaf9373423570d8177a3c7`, 500 lines.
- `docs/architecture/plans/JARVIS_PROJECT_CONTINUITY_AND_RECOVERY_HANDOFF.md` — blob `23d7ebf2a287b8d1c4cd049dce2f96181fdd0ae6`, 331 lines.
- Gate A reports and evidence matrices 02–16 are under `docs/architecture/plans/reviews/`.

The latest PR description states:
- Gate A is **NOT CLEARED**.
- No implementation baseline has been selected.
- PR #156 is a conditional selective donor, not a wholesale baseline.
- Gate B capability acceptance has not passed.
- PR #176 donor corrections are separate and unmerged.
- No implementation authorization is claimed.

The independent technical review artifact (Report 14) is a review document, not a submitted GitHub review. It identifies remaining provenance, API, workflow, and defect-verification obligations. PR #175's report and metadata must be kept as evidence, but its implementation roadmap is subordinate to the eventual complete JARVIS architecture and may require reconciliation.

## 8. Earlier October 31 planning work — PRs #166–#170

These are separate draft branches and must be preserved as prior work, not silently treated as approved decisions.

| PR | Branch / principal artifact | Scope and status |
|---|---|---|
| #166 | `docs/jarvis-project-command-governance-20261031`; `docs/JARVIS_PROJECT_GOVERNANCE.md` | Project command structure and Builder/Tester/Reviewer role boundaries. Open, draft, unmerged. |
| #167 | `docs/brain-layer-language-ownership-map-20261031`; `docs/BRAIN_LAYER_LANGUAGE_OWNERSHIP_MAP.md` | Proposed Brain-only language ownership map. Open, draft, unmerged. |
| #168 | `docs/brain-polyglot-engineering-governance-20261031`; `docs/BRAIN_POLYGLOT_ENGINEERING_GOVERNANCE.md` | Proposed polyglot engineering rules. Open, draft, unmerged. |
| #169 | `docs/jarvis-mcu-brain-target-analysis-20261031`; `docs/JARVIS_MCU_BEHAVIORAL_REFERENCE_AND_BRAIN_TARGET.md` | 542-line MCU J.A.R.V.I.S. behavioral target analysis across multiple MCU films; open, draft, unmerged. |
| #170 | `docs/brain-constitution-planning-readiness-20261031`; constitution, Layer 0–19 traceability matrix, review reconciliation, updated master blueprint | Proposed constitution/readiness consolidation and traceability. Open, draft, unmerged. |

At inspection, PRs #167–#170 had no submitted GitHub review records. Their contents may contain useful work, but proposed language allocations, rules, layer constraints, and target requirements are not binding merely because they are documented.

### 8.1 Important prior artifacts

- `docs/BRAIN_LAYER_LANGUAGE_OWNERSHIP_MAP.md` — 239 lines; proposed Brain-only allocation.
- `docs/BRAIN_POLYGLOT_ENGINEERING_GOVERNANCE.md` — 647 lines; proposed language and integration governance.
- `docs/JARVIS_MCU_BEHAVIORAL_REFERENCE_AND_BRAIN_TARGET.md` — 542 lines; MCU behavior, inference limits, whole-system destination, Brain-first construction, and no-hardcoding principles.
- `docs/JARVIS_BRAIN_FOUNDATION_CONSTITUTION_AND_PLANNING_READINESS.md` — 412 lines; proposed constitution and planning-gap register.
- `docs/BRAIN_LAYER_0_19_TRACEABILITY_MATRIX.md` — 173 lines; proposed mapping of the existing Brain layers to targets, candidate mechanisms, source and evidence.
- `docs/BRAIN_PLANNING_REVIEW_RECONCILIATION.md` — 123 lines; reconciliation of earlier planning-review findings.
- Updated `docs/JARVIS_BRAIN_MASTER_BLUEPRINT.md` — same Layer 0–19 structure, but PR #170's branch revision differs from the main-branch revision.

The PR #170 readiness register explicitly says that several subjects are already partially documented and that the task is to reconcile and formalize them rather than create redundant documents. It also lists unresolved cross-layer contracts and architecture questions. This is valuable gap evidence, not an approved final architecture.

## 9. Existing main-branch documents and historical implementation artifacts

The following files were fetched from the inspected main baseline and remain in the ordinary `docs/` area:

| Path | Blob at main baseline | Observed content/status |
|---|---|---|
| `docs/JARVIS_BRAIN_MASTER_BLUEPRINT.md` | `9958b8a596e172488b21fce1cdc256ccde419cfe` | 365-line Layer 0–19 Brain construction blueprint; status says “Architecture/build plan.” |
| `docs/ARCHITECTURE.md` | `819544194e080f1210a32efc05867c6220f9e6fd` | 52-line high-level cognitive flow, continuity, learning, evolution, resilience and language boundaries. |
| `docs/JARVIS_PHASE_2_COMPLETION.md` | `7e001e63703bf07efe95c321c1f6c4272ae626f7` | 30-line Phase 2 Perception & Representation completion declaration and stated exit boundary. |

These files are not in a verified separate historical archive in the inspected main tree; they remain in the main `docs/` area. Their content, age, continuing authority, README links, and relationship to newer planning work must be reconciled before any move or supersession decision.

PR #170 updates the master blueprint on its own unmerged branch (blob `11eb3d3abbba94116e5f4d1288856495ea0ac9e4`). That version retains the Layer 0–19 sequence and changes wording around provider/source dependency. The branch version must not be silently substituted for the main version.

### 9.1 Developmental implementation plan and donor branch

PR #156's branch contains `docs/DEVELOPMENTAL_BRAIN_PLAN.md` (399 lines; blob `1db14e73ecc4ff4fded2791df17f34d20958c329` at the inspected code-bearing/documentation checkpoint). It records the October 30–31 developmental Brain work, priority order, implementation evidence, source-provenance and replay safeguards, and handoffs.

PR #156 remains an unmerged candidate donor. The plan is historical and engineering evidence; it is not automatically the current architecture or the selected implementation baseline.

PR #176 is a separate draft correction branch for D1/D2 and journal failure-boundary work. Its stated tested head is `4cf017e073da980c9f77d739fde6f92ef1a2fbc1`. Its results apply to that donor branch, not automatically to the accepted Brain specification or an integrated JARVIS implementation. It remains unmerged.

## 10. Review and approval snapshot

At the time of this inventory, GitHub review-submission lists for PRs #167–#176 returned no submitted reviews. This does not erase separate Project Director approvals or decisions recorded in PR conversations, but it means draft PR status must not be mistaken for a formal GitHub review approval.

Known project authority from the recorded handoff:
- PR #171 Documents 00 and 01: separate, scope-limited Project Director approvals for their recorded revisions.
- PR #172: accepted as a capability-investigation planning input.
- PR #173: accepted as the Brain Foundation Architecture planning baseline.
- PR #174: current independent re-review outcome supplied by the Project Director reports F-02 and F-03 unresolved; conflict with PR #175's “accepted” wording requires explicit reconciliation.
- PR #175: Gate A remains NOT CLEARED; no implementation baseline selected.
- PR #176: donor correction branch, draft and unmerged.

This inventory does not independently validate every earlier approval statement. Exact approval comments and their revision pins remain part of the authority register to be verified.

## 11. Initial conflicts, risks and open questions

1. **Whole-system scope versus Brain-only planning artifacts:** PR #171 establishes whole-JARVIS responsibility domains, but much subsequent planning is Brain-only. The final architecture must connect the complete JARVIS system to the Brain-first implementation strategy.
2. **Functional anatomy versus complete architecture:** PR #171 Document 01 is not a complete computational architecture. The system-level organization, dynamic operation, timing, concurrency, resource control, lifecycle, failure containment, security, and integration behavior still require architectural treatment.
3. **Mechanism decomposition risk:** PR #174's twelve mechanism responsibilities must not be treated as the architecture itself. Their interactions must be derived from a coherent computational organization, not merely documented as interfaces.
4. **Layer 0–19 authority:** the master blueprint and PR #170 readiness work retain a Layer 0–19 construction map, but the blueprint's formal approval status is not established by its “Architecture/build plan” label. Any constraint against changing layer order must be explicitly checked against Project Director authority and the completed architecture.
5. **Polyglot decisions:** PRs #167 and #168 contain proposed Brain-only language allocations and rules. They are unreviewed drafts, not binding technology decisions for complete JARVIS.
6. **MCU research completeness:** PR #169 provides a substantial behavioral analysis, but it must be checked against primary film evidence, source reliability, missing capabilities, and the distinction between observed behavior and inferred mechanisms.
7. **Human-cognition research completeness:** PR #171 and #172 contain useful scientific comparisons, but they are not yet a comprehensive, evidence-graded investigation of neural organization, dynamics, development, efficiency, and cognitive function.
8. **PR #174 authority discrepancy:** the latest user-supplied review and PR #175's accepted-baseline wording conflict.
9. **Gate A scope:** PR #175's source-baseline reconciliation is Brain-implementation-specific. It must not be mistaken for the complete JARVIS architectural audit.
10. **Historical document placement:** older master blueprint, architecture summary, and phase-completion artifacts remain in `docs/` on main. A complete archive inventory and disposition has not yet been verified.
11. **No evidence for wholesale deletion:** no document or source component is recommended for deletion by this inventory. Retain, adapt, supersede, or archive decisions require per-artifact rationale and dependency/reference analysis.

## 12. Preservation decision

For this Phase 1 snapshot:

- Preserve all inspected PR branches and their commit history.
- Preserve all current-main documentation files.
- Preserve the PR #156 developmental plan and PR #176 donor correction evidence.
- Do not merge, rebase, cherry-pick, rewrite, delete, rename, or relocate any existing artifact.
- Do not treat unreviewed drafts as approved.
- Do not let a prior implementation plan constrain the complete JARVIS architecture without explicit reconciliation.
- Keep the user-supplied PR #174 independent review outcome as a required authority record to reconcile.

## 13. Phase 1 remaining work and exit criteria

This is an initial inventory, not yet Phase 1 completion.

Remaining work:
1. Complete a broader documentation and PR/branch inventory, including older JARVIS branches and any linked artifacts not yet inspected.
2. Verify exact approval comments and revision pins for the separately approved PR #171 documents and accepted PR #172/#173 planning decisions.
3. Reconcile PR #174's latest independent report against PR metadata, PR discussion and PR #175's governing-baseline statement.
4. Inspect README/document links and identify documents still presented as current when they are provisional or historical.
5. Identify October implementation and planning artifacts across relevant branches; classify each as current, historical, superseded, or unresolved.
6. Create a document authority/dependency register and a separate archive disposition proposal. Do not move anything until the proposal is reviewed and accepted.
7. Record the exact repository snapshot and verify that this inventory branch introduces only this inventory artifact.

Phase 1 is complete only when the inventory is sufficiently comprehensive to prevent accidental loss, duplication, authority confusion, and planning conflicts. No architecture redesign or comparative research conclusions are authorized by this inventory.

## 14. Timing record

Initial Phase 1 estimate: **2–4 focused working hours**.

After discovery of the additional unmerged PR #166–#170 planning chain, the 2,402-line comparative research log, the separate MCU target analysis, the PR #175 evidence packet, and historical donor documents, the estimate is revised to **3–5 focused working hours** for a defensible Phase 1 inventory and authority/archive register.

This is focused working time, not elapsed calendar time. The estimate excludes the later human-cognition/MCU comparative research phase, full architecture design, independent review, and implementation.

No elapsed-time claim is made in this artifact because a continuously running stopwatch was not available for the repository operations. Subsequent work reports should record the start/end timestamps and active work duration for each phase.

---

**End of initial inventory.**


## 15. Additional historical planning and implementation artifacts — PRs #96, #97 and #164

A broader PR/branch search identified an earlier planning and implementation chain that must also be preserved and reconciled. These are not part of the PR #171–#175 sequence, and their existence means the archive/disposition inventory must cover more than the latest architecture documents.

### 15.1 PR #97 — JARVIS cognitive + affective development

**PR:** [#97 — JARVIS cognitive + affective development](https://github.com/methaneex-oss/MethaneX/pull/97)  
**Branch:** `feat/jarvis-affective-state`  
**HEAD:** `c1da222e6c94aeb3f2ad000392c21fe4fc81ab25`  
**Base:** `main` at `4ba84b8b5ccf0e41530c46fdb8101551254ba864`  
**Created:** 2026-10-02  
**PR state:** open, draft, unmerged; mergeability reported false.  
**Size at inspection:** 1,244 commits, 159 changed files, 18,788 additions and 1,644 deletions.

This is a substantial historical code-bearing branch, not merely an old document branch. It contains cognitive/affective implementation and tests plus the following documentation:

- `docs/developmental-training-environment.md` — 56 lines.
- `docs/superpowers/plans/2026-09-25-cognitive-action-feedback-loop.md` — 255 lines.
- `docs/superpowers/plans/2026-09-26-concept-context-prediction.md` — 114 lines.
- `docs/superpowers/plans/2026-09-30-developmental-cognition.md` — 248 lines.
- `docs/superpowers/plans/2026-10-01-affective-state.md` — 124 lines.
- `docs/superpowers/specs/2026-09-25-cognitive-action-feedback-loop-design.md` — 185 lines.
- `docs/superpowers/specs/2026-09-26-concept-context-prediction-design.md` — 77 lines.
- `docs/superpowers/specs/2026-09-30-developmental-cognition.md` — 186 lines.
- `docs/superpowers/specs/2026-10-01-affective-state.md` — 88 lines.

These artifacts describe the cognitive action/feedback loop, concept-context-prediction integration, developmental cognition, affective-state design, and a controlled developmental training environment. They are historically important and must be examined as evidence of prior design intent and implementation rationale.

They must not be treated as current authoritative architecture merely because they are detailed or attached to a large implementation branch. PR #97 is not merged. Its branch and commit history must remain preserved while its code and documents are evaluated against the accepted architecture and the eventual complete JARVIS design.

### 15.2 PR #96 — Integrated cognitive action feedback loop

**PR:** [#96 — Connect JARVIS cognitive action feedback loop](https://github.com/methaneex-oss/MethaneX/pull/96)  
**Branch:** `feat/jarvis-cognitive-action-loop`  
**HEAD:** `16abca97caf77ce65d5ac901513eb2790f04c68c`  
**Created:** 2026-09-25  
**PR state:** open, draft, unmerged.

PR #96 includes earlier versions of the 2026-09-25/26/30 planning and design documents, alongside code for the cognitive runtime/action/outcome feedback loop. Its documentation overlaps with the later PR #97 artifact set.

Preservation rule: do not create duplicate archive copies until the relationship between the PR #96 and PR #97 versions is compared. Preserve both Git histories and identify which document revisions were carried forward, changed, or superseded.

### 15.3 PR #164 — Polyglot Brain technology audit

**PR:** [#164 — Audit polyglot Brain foundation technology](https://github.com/methaneex-oss/MethaneX/pull/164)  
**Branch:** `docs/brain-polyglot-foundation-audit-20261031`  
**HEAD:** `5433b0d0ae6ea7ff9d0991e84c8a6a8a2506c1cb`  
**Document:** `docs/BRAIN_POLYGLOT_FOUNDATION_TECHNOLOGY_AUDIT.md` (280 lines).  
**PR state:** open, draft, unmerged.

The document records a repository-grounded technology audit and proposed polyglot direction. It reports a substantial C++20 cognitive core, a minimal Rust runtime, TypeScript interface work, no verified integrated Python/PyTorch learning subsystem in its inspected baseline, and no verified CUDA/Triton integration. It proposes possible future responsibilities, but it does not constitute approved language allocation or implementation authorization.

It must be reconciled with PRs #167 and #168 rather than treated as a separate binding technology decision.

## 16. Updated preservation and archive observations

The historical document inventory now includes at least three distinct classes:

1. **Current-main documentation:** older master blueprint, architecture summary, and phase-completion records remain in `docs/` on main.
2. **Unmerged planning branches:** PRs #164 and #166–#170 contain proposed technology, governance, language, MCU target, constitution, and traceability documents.
3. **Unmerged implementation branches:** PRs #96, #97, #148 and #156 contain code-bearing histories and dated planning/specification artifacts, including September/October documents.

The PR #96 and #97 documents are already preserved by their respective Git branches, but they are not thereby placed in a dedicated archive directory. The current-main documents listed in Section 9 remain in the ordinary `docs/` area. No completed archive relocation has been verified.

**Do not archive by copying files indiscriminately.** First compare revisions, identify canonical historical versions, check links/references, and preserve source branch/commit provenance. Some documents may remain in their original PR branches as the primary historical record; others may warrant a curated archive index in the current documentation tree. This is a later disposition decision, not an action taken by this inventory.

## 17. Historical preservation follow-up estimate

The additional PR #96/#97 historical branches, nine dated planning/specification artifacts, the 1,244-commit PR #97 history, and PR #164 technology audit expand the preservation scope beyond the initial estimate.

Revised estimate for the **historical documentation and branch-preservation follow-up**: **4–6 focused working hours**. This includes a bounded inventory of relevant documentation, branches and PRs, authority verification, link/dependency checks, and a defensible archive/disposition register. It does not mean exhaustively reviewing all 1,244 commits or auditing all 159 changed files; that would be a separate source-baseline investigation.

This estimate is not a statement that the completed Phase 1 technical repository inventory/reuse investigation is unfinished. It applies only to the remaining historical branch and artifact preservation tasks, which remain provisional until those bounded checks are complete.


## 18. Main documentation directory and branch inventory evidence

A direct directory listing was obtained for `docs/` at the inspected main baseline `1273ddbcd0087d189e01388ded2d362fb1e058d2`.

The returned `docs/` entries were exactly:

- `docs/ARCHITECTURE.md`
- `docs/JARVIS_BRAIN_MASTER_BLUEPRINT.md`
- `docs/JARVIS_PHASE_2_COMPLETION.md`

No `docs/archive/` directory appeared in that main-branch directory listing. This establishes that the three files above remain in the ordinary docs root at this snapshot; it does not establish that no archive exists elsewhere in the repository or on another branch.

A branch search for `jarvis` returned 33 matching branch names. In addition to the current planning branches, it exposed a family of historical affective planning/implementation branches, including:

- `docs/jarvis-affective-plan`
- `feat/jarvis-affective-plan`
- `feat/jarvis-affective-state`
- `feat/jarvis-affective-state-impl`
- `feat/jarvis-affective-state-plan` and numbered plan variants through `plan20`, plus `plan-final`
- `feat/jarvis-affective-state-work`
- `feat/jarvis-affective-impl`
- `feat/jarvis-cognitive-action-loop`
- `feat/jarvis-learning-mechanisms-probe`
- `feat/jarvis-build-agents-clean`

This branch list is a discovery result, not a complete branch-to-PR disposition. Mapping each relevant historical branch to its PR, unique artifacts, overlap, and preservation status remains open work. Do not delete or rewrite branches as an archive shortcut.

## 19. Chronological correction to PR #174 authority status

The repository discussion confirms that PR #174 was formally accepted by the Project Director in comment [#6604790481](https://github.com/methaneex-oss/MethaneX/pull/174#issuecomment-6604790481), dated 2026-11-03 13:14:28 UTC, for exact HEAD `0811a59e46bf934e32e794f90e4e7d18d4e2bd97`, after F-01 clearance. The comment explicitly limits acceptance to the planning baseline, states the BM-07/SYS-05/SYS-08 clarification is non-blocking, and grants no implementation authorization.

A subsequent review report supplied in the conversation identifies F-02 and F-03 as unresolved. This is later evidence requiring targeted specification correction; it does not erase the historical acceptance event. PR #175's “accepted” wording accurately records that earlier event but does not capture the later F-02/F-03 obligations, so its current-readiness wording must be treated as incomplete.

The GitHub PR #174 review-list endpoint returned an empty array at this inspection. The formal Project Director acceptance is visible in the issue discussion; the later F-02/F-03 review report is not represented as a submitted GitHub PR review. Do not describe that later report as a GitHub review submission unless such a record is subsequently created and verified.

**Current disposition:** PR #174 remains the formally accepted planning baseline at the exact accepted revision, with F-02/F-03 correction obligations open. Use it for traceability and analysis; do not treat affected requirements as implementation-ready until the later findings are resolved and the required authority/review decision is recorded. No implementation authorization is implied.

## 20. Expanded historical-review status

GitHub review-submission lists also returned zero submitted reviews for PRs #96, #97, #148, #156 and #164 at the time of inspection. Their open/draft PR status and historical CI claims must therefore remain distinct from independent approval.

The following remain open preservation/reconciliation tasks:
- map the 33 JARVIS-related branches to their PRs and current relevance;
- compare the duplicated dated plans/specifications across PR #96 and PR #97;
- identify which documents were changed or superseded across PR #97, PR #148, PR #156 and PR #170;
- verify the README and cross-document links for every candidate authoritative document;
- establish whether each October artifact should remain solely in its historical branch, be represented in a curated archive index, or be formally superseded by a newer document.

No files or branches were moved, deleted, renamed, merged, or rewritten by this inventory update.


## 21. Phase 1 technical completion versus preservation follow-up

The Phase 1 technical repository inventory and reuse/conflict investigation is complete within the scope defined by its report: the full tracked tree at the pinned baseline, critical cognitive source paths, build/test registration, donor line, polyglot boundaries, architecture and Gate A evidence were examined.

The following preservation tasks remain open and must not be represented as complete:
- map all 33 JARVIS-related branches to PRs, unique artifacts and current relevance;
- compare duplicated dated plans/specifications across PR #96/#97 and related donor history;
- reconcile historical document revisions across PR #97, PR #148, PR #156 and PR #170;
- verify README and cross-document links for candidate authoritative documents;
- decide which historical artifacts remain in source branches, receive a curated archive index, or are formally superseded.

These tasks form a bounded documentation/preservation follow-up. They do not invalidate the completed technical inventory or require restarting Phase 1's technical investigation.

A reproducible exact-baseline file list is now published at [PHASE_1_TRACKED_FILE_INVENTORY_2026-11-05.md](PHASE_1_TRACKED_FILE_INVENTORY_2026-11-05.md). Selected donor implementation paths are traced in [PHASE_1_PR97_DONOR_CAPABILITY_TRACEABILITY_2026-11-05.md](PHASE_1_PR97_DONOR_CAPABILITY_TRACEABILITY_2026-11-05.md). The complete correction disposition is in [PHASE_1_REVIEW_CORRECTIONS_AND_SCOPE_RECONCILIATION_2026-11-05.md](../reports/PHASE_1_REVIEW_CORRECTIONS_AND_SCOPE_RECONCILIATION_2026-11-05.md).

---

## 22. Whole-Brain planning scope correction — 2026-11-07

This inventory is a preservation and authority-discovery artifact. It does not prove that the complete future Brain has been architecturally defined.

The PR #171 whole-system foundation, PR #172 capability investigation, PR #173 Brain Foundation Architecture, PR #174 BM-01–BM-12 specification, Phase 1 repository audit and Phase 2 source map are substantial prior inputs. Their exact approval scopes must be respected, but none should be treated as a substitute for the newly clarified whole-Brain capability definition and completeness assessment.

The next Builder must preserve these artifacts and analyze them as evidence. The Builder must not assume that twelve mechanisms exhaust the Brain, and must not select implementation order or repository reuse until whole-Brain architecture and its completeness review are accepted.

See [Whole-Brain Planning Scope and Builder Correction](../reports/WHOLE_BRAIN_PLANNING_SCOPE_AND_BUILDER_CORRECTION_2026-11-07.md) for the corrected sequence, reference lenses, authority boundaries and explicit Builder error record.



## 23. Initial Documentation Foundation package — 2026-11-07

The following documents form the proposed initial documentation-foundation correction package. They are not accepted merely because they are present on PR #192.

| Artifact | Location | Current classification | Purpose / boundary |
|---|---|---|---|
| Planning Documentation Index | `docs/architecture/00_JARVIS_PLANNING_DOCUMENTATION_INDEX_2026-11-07.md`, PR #192 | Proposed; awaiting independent review and authority decision | Canonical navigation and authority/status map |
| Whole-Brain Planning Scope and Builder Correction | `docs/architecture/reports/WHOLE_BRAIN_PLANNING_SCOPE_AND_BUILDER_CORRECTION_2026-11-07.md`, PR #192 | Proposed correction | Corrects whole-Brain scope and planning sequence; now places the documentation foundation gate before Stage A |
| Initial Documentation Foundation Audit | `docs/architecture/reports/INITIAL_DOCUMENTATION_FOUNDATION_AUDIT_AND_COMPLETION_GATE_2026-11-07.md`, PR #192 | Builder audit; not independently reviewed or accepted | Records live repository snapshot, branch topology, authority/provenance findings, blockers, and DF-01–DF-13 exit criteria |
| Documentation Phase Builder Self-Review | `docs/architecture/reports/WHOLE_BRAIN_DOCUMENTATION_PHASE_BUILDER_SELF_REVIEW_2026-11-07.md`, PR #192 | Builder self-review only | Records limitations and confirms the package is not ready for acceptance |
| Project Continuity and Recovery Handoff | `docs/architecture/plans/JARVIS_PROJECT_CONTINUITY_AND_RECOVERY_HANDOFF.md`, PR #193 | Proposed; updated to align with PR #192 documentation gate | Carries historical evidence and the current operational handoff; independent review and cross-link verification remain pending |
| Brain Implementation Plan | `docs/architecture/plans/00_BRAIN_IMPLEMENTATION_PLAN.md`, PR #193 | Deferred/non-operative proposal | Preserved as a candidate input for later development planning; no phase or first increment is operative |

### 23.1 Live dependency and authority qualifications

- PR #192 is based on PR #179 head `61311fe5b44c81c4409c8ba8dc581a83bdd5dd2c`.
- PR #193 is based on PR #175 head `874c732973b6ab303d65a503f5a215b0af8e1153`.
- These are separate lineages. Neither branch alone represents the complete integrated documentation state.
- PR #191 is based on an earlier PR #179 snapshot 22 commits behind the current line; its comparison report remains a single-path artifact in PR #191.
- PR #178's governance rules remain proposed and unaccepted. They are not to be silently promoted to project-wide authority.
- PR #173's acceptance claim requires exact decision-record reconciliation; the current PR #173 discussion did not expose an explicit acceptance decision.
- PR #192 and PR #193 remain open/draft/unmerged and have no submitted formal review records at the audited snapshot.

### 23.2 Current phase and preservation boundary

The current task is the **Initial Documentation Foundation Completion Gate**. Stage A is held until the gate's measurable exit criteria are met, independently reviewed, and accepted.

The historical preservation follow-up recorded in Sections 20–21 remains open. This addendum does not claim that all historical branches, duplicated documents, or archive decisions have been reconciled. It also does not restart the completed Phase 1 technical source investigation.

No historical file or branch was deleted, moved, renamed, merged, or rewritten by this addendum.


---

## 24. Live documentation-foundation refresh — 2026-11-07

This addendum refreshes the documentation-package branch heads after the first corrective pass. It does not replace the historical snapshots in Sections 19–23.

| Artifact / branch | Current verified revision | Status |
|---|---|---|
| PR #192 — whole-Brain scope correction, index, audit and inventory | `86cb082b54d541ffcd374100acee81b2f2068182` | Open, draft, unmerged; no formal review submission |
| PR #193 — roadmap hold and continuity handoff | `15fe766dca5fd9225d7576e5466df6a7fecb9d94` | Open, draft, unmerged; no formal review submission |
| PR #192 base / PR #179 head | `61311fe5b44c81c4409c8ba8dc581a83bdd5dd2c` | Separate #179-derived lineage |
| PR #193 base / PR #175 head | `874c732973b6ab303d65a503f5a215b0af8e1153` | Separate #175-derived lineage |
| `main` | `1273ddbcd0087d189e01388ded2d362fb1e058d2` | Contains only the three legacy top-level documentation files under `docs/`; the proposed planning package remains on unmerged branches |

The refreshed PR #192 and PR #193 formal review lists are empty, and their discussion timelines returned no comments/review submissions at this refresh. Neither PR has been merged, retargeted, rebased, or cherry-picked.

The PR #193 continuity handoff's unsupported claim that the user had identified themselves as Project Director has been removed. The handoff now records bounded user-delegated Builder authority and explicitly prohibits inferring a Project Director role from that delegation or from GitHub identity/permissions. The PR #193 description and PR #192 scope-correction report now attribute the relevant planning sequence to the user's instruction without assigning the user a formal Project Director role.

The current-phase corrections are present in the current package revisions: the Initial Documentation Foundation Completion Gate is the current task; Stage A remains not started and held; implementation remains unauthorized. The PR #178 governance document remains a proposed, unaccepted governance input, not a binding project-wide authority.

**Remaining documentation work:** validate all cross-branch links, reconcile exact authority/provenance where unresolved (especially PR #173), complete the historical preservation follow-up, refresh the index/inventory/self-review together, conduct a fresh-reader continuity test, and obtain independent review plus the required exact-revision authority decision. No Stage A planning is included in this addendum.


## 25. Reader navigation and documentation maintenance — 2026-11-07

A human-facing portal is proposed at `docs/README.md` on PR #192. It provides role-specific routes for general readers, Builders, independent reviewers, testers, researchers and documentation maintainers. The root README points to that portal; the Planning Documentation Index remains the canonical catalog of planning artifacts, authority/status distinctions and dependencies.

The portal adds navigation and contribution guidance; it does not create new architecture, governance or implementation authority. Its content explicitly distinguishes:
- authored, submitted, independently reviewed, accepted within exact scope, merged, gate-cleared and implementation-authorized;
- test definitions, registered targets, executed runs, observed results and accepted capability;
- the Builder's self-review from a genuinely independent review;
- the PR #179-derived PR #192 documentation line from the separate PR #175-derived PR #193 handoff/roadmap line.

The inventory remains a preservation record, not an approval register. Any subsequent change to artifact location, status, revision, authority or dependency must update this inventory and the Planning Documentation Index in the same reviewed change.


## 26. Reusable documentation templates — 2026-11-07

A proposed template set is added under `docs/templates/`:
- `README.md` — template directory guide and usage boundaries;
- `PLANNING_DOCUMENT_TEMPLATE.md` — metadata, scope, evidence, analysis, proposed decisions, risks, verification and authority limitations;
- `INDEPENDENT_REVIEW_REPORT_TEMPLATE.md` — exact-revision review, independence disclosure, evidence, findings, closure criteria and formal-review distinction;
- `TEST_EVIDENCE_REPORT_TEMPLATE.md` — reproducible test context, exact commands, outcomes, failure analysis, coverage limits and provenance.

The templates support consistent contributions from Builders, reviewers and testers. They are not accepted governance rules and do not replace the formal review or authority process. New substantive artifacts should be added to this inventory and the Planning Documentation Index in the same reviewed change.


## 27. Authority-status qualification for PR #173 — 2026-11-07

Section 5's historical handoff claim has been qualified. Later documents report that PR #173's exact Brain Foundation Architecture revision was accepted as a planning baseline, but the primary exact-revision Project Director decision record was not recovered from the available PR #173 discussion during the current audit. The inventory must therefore distinguish the recorded claim from independently verified provenance. Until the primary record is recovered or the designated authority explicitly dispositions the gap, the acceptance provenance remains unresolved.

This qualification does not erase the historical claim, invalidate the technical content, or authorize implementation. It prevents the inventory from presenting an unverified authority claim as settled fact.


## 28. Live branch-head correction after navigation validation — 2026-11-07

The older branch-head tables in Sections 23–24 are retained as historical snapshots. A live re-fetch on 2026-11-07 established the following pre-correction state:

| Item | Verified revision / state |
|---|---|
| PR #192 parent HEAD before this inventory update | `f831faef6d031776e0cee116d1986c3160faffb5` |
| PR #193 live HEAD | `976aa33f89cc02225296f59246f47982300f5b39` |
| PR #192 | Open, draft, unmerged; this corrective commit advances its head |
| PR #193 | Open, draft, unmerged; based on PR #175 head `874c732973b6ab303d65a503f5a215b0af8e1153` |

The portal's prior snapshot in Section 9 named PR #192 `273c2c0ac1d9d6a2291d339387ea6e88dae037d7` and PR #193 `03502c5719b320b9e323cb1d040ae38737fc7b81`. Those values did not match the live refs fetched immediately before this correction and must not be used as current branch heads. The live refs above supersede those snapshot values for present navigation.

The exact PR #192 HEAD resulting from this update must be re-fetched after the commit is created; do not predict its SHA. This section records the pre-update parent and PR #193 live head to avoid a self-referential commit claim.

This correction does not alter PR bases, integrate PR #192 and PR #193, or change any acceptance, review, gate or implementation status.


## 29. Expanded repository-relative link-path check — 2026-11-07

A repository-relative Markdown link-path check was completed across all 24 Markdown documents under the repository root and `docs/` in the PR #192 tree at parent `1901d5f39d788d7ad928cc1045065d7b32f120c1`. The check covered the root README, the documentation portal, legacy architecture pages, the planning index, inventories, Phase 1/Phase 2 reports, the provenance record, the governance proposal, the Builder self-review, and all documentation templates.

**Result:** 63 repository-relative Markdown link targets checked; zero missing repository paths.

This is path-existence validation only. It does not validate fragment anchors, semantic correctness, external URL availability, or authority/status claims in linked documents. Those remain separate review obligations.

The PR #192 parent used for this check is `1901d5f39d788d7ad928cc1045065d7b32f120c1`; PR #193 live HEAD at the time of the check was `976aa33f89cc02225296f59246f47982300f5b39`. The commit containing this addendum advances PR #192 and must be fetched before a later exact-revision review. No PR integration, base change, merge, or authority decision is implied.


## 30. Exact documentation-package revision and blob register — 2026-11-08

This is an immutable evidence snapshot fetched from live GitHub metadata and the complete changed-file lists at PR #192 HEAD `f615e11bf54fb3776d3e6ece4f74179f61c848f8`, immediately before this inventory correction. It records the exact parent revision inspected. This update creates a later commit; the inventory's own listed blob is therefore its pre-update blob. The resulting inventory blob and final PR HEAD are verified after the write. Do not mistake this parent snapshot for the resulting commit.

### 30.1 Pull-request state and dependency register

| Item | Exact revision / state |
|---|---|
| PR #192 | HEAD `f615e11bf54fb3776d3e6ece4f74179f61c848f8`; base branch `docs/jarvis-phase-2-whole-brain-integration-map-20261105`; base SHA `61311fe5b44c81c4409c8ba8dc581a83bdd5dd2c`; open, draft, unmerged; 19 changed files |
| PR #193 | HEAD `976aa33f89cc02225296f59246f47982300f5b39`; base branch `plan/brain-implementation-roadmap-20261103`; base SHA `874c732973b6ab303d65a503f5a215b0af8e1153`; open, draft, unmerged; 2 changed files |
| PR #192 formal reviews / inline threads / conversation comments | 0 / 0 / 0 returned in live GitHub queries |
| PR #193 formal reviews / inline threads / conversation comments | 0 / 0 / 0 returned in live GitHub queries |
| PR #192 and PR #193 relationship | Separate #179-derived and #175-derived lineages; no integration, rebase, retarget or ancestry change performed |
| `main` | `1273ddbcd0087d189e01388ded2d362fb1e058d2` as recorded in the inventory baseline context; no main-branch write performed |

### 30.2 PR #192 changed-file blob register

All 20 paths returned by the paginated PR #192 changed-file endpoint were fetched at exact parent HEAD `06bc2741e7c5ea9b4be7b3bfe46a4f3b6f3169a3`. The inventory row records its pre-update blob; the follow-up review report is explicitly included.

| # | Repository path | Blob SHA |
|---:|---|---|
| 1 | `README.md` | `780651b804b491781fdcac8e248eaca9243797a4` |
| 2 | `docs/ARCHITECTURE.md` | `3c6692b52059e43947d1fd2e7e84debb2362023f` |
| 3 | `docs/JARVIS_BRAIN_MASTER_BLUEPRINT.md` | `0e49d313bf3929aa30140cb7149ebab038918378` |
| 4 | `docs/JARVIS_PHASE_2_COMPLETION.md` | `e0e57a44216fc36c52d469a79abfc8df058515a3` |
| 5 | `docs/README.md` | `00d6a5996b1f76aeefc7fcda5e07a95de4c77288` |
| 6 | `docs/architecture/00_JARVIS_PLANNING_DOCUMENTATION_INDEX_2026-11-07.md` | `b963c9cea549feca0353b2d48e7eb307930f2dcf` |
| 7 | `docs/architecture/inventory/00_JARVIS_DOCUMENTATION_AND_ARTIFACT_INVENTORY_2026-11-04.md` | `5200d93c90b0c559eef65639774d799a4e4b3c59` (pre-update inventory blob) |
| 8 | `docs/architecture/reports/INDEPENDENT_DOCUMENTATION_FOUNDATION_REVIEW_2026-11-08.md` | `ecd11354a858eb6e46cbd85b816836a2f88973c9` |
| 9 | `docs/architecture/reports/INDEPENDENT_REVIEWER_HANDOFF_2026-11-08.md` | `8ee2075ac87a45854c73b587f50a9800d651906d` |
| 10 | `docs/architecture/reports/INDEPENDENT_RE_REVIEW_BUILDER_FOLLOW_UP_2026-11-08.md` | `2d63ed93344a7081dcedb44247536c416322c793` |
| 11 | `docs/architecture/reports/INITIAL_DOCUMENTATION_FOUNDATION_AUDIT_AND_COMPLETION_GATE_2026-11-07.md` | `921314e637afcd4203fca209cb57775af3386347` |
| 12 | `docs/architecture/reports/PHASE_1_REVIEW_CORRECTIONS_AND_SCOPE_RECONCILIATION_2026-11-05.md` | `a459cdfd02d850d455ca526e6823e68525776ba3` |
| 13 | `docs/architecture/reports/PHASE_1_WHOLE_REPOSITORY_INVESTIGATION_AND_REUSE_AUDIT_2026-11-04.md` | `f725eda1e23d6558d90f6f7c87302019ef3a0dfc` |
| 14 | `docs/architecture/reports/PHASE_2_WHOLE_BRAIN_CAPABILITY_TO_SOURCE_INTEGRATION_MAP_2026-11-05.md` | `7cf312f6cc6fd880473a0b6ccc86cf53bf3b3533` |
| 15 | `docs/architecture/reports/WHOLE_BRAIN_DOCUMENTATION_PHASE_BUILDER_SELF_REVIEW_2026-11-07.md` | `af7b620061a8c4adf1d4645150e80553ef1ecc69` |
| 16 | `docs/architecture/reports/WHOLE_BRAIN_PLANNING_SCOPE_AND_BUILDER_CORRECTION_2026-11-07.md` | `0187a0ac71bd0c95e94beb3bf006da9cc7c3605f` |
| 17 | `docs/templates/INDEPENDENT_REVIEW_REPORT_TEMPLATE.md` | `f3176cf1a1f45735a3ad62fa4a865806edc24e08` |
| 18 | `docs/templates/PLANNING_DOCUMENT_TEMPLATE.md` | `b9f71a923b0d717a3b29655574c89c10e0801115` |
| 19 | `docs/templates/README.md` | `7209fd0fcda239349af602490d26b8c708b743da` |
| 20 | `docs/templates/TEST_EVIDENCE_REPORT_TEMPLATE.md` | `9c6bbae48a22beb7c4e95858282d7d8d7b2159c2` |

### 30.3 PR #193 changed-file blob register

Both changed paths returned by the PR #193 changed-file endpoint were fetched at exact HEAD `976aa33f89cc02225296f59246f47982300f5b39`.

| Repository path | Blob SHA |
|---|---|
| `docs/architecture/plans/00_BRAIN_IMPLEMENTATION_PLAN.md` | `d065e833d2211753985784d9de6e562e0f72bc2b` |
| `docs/architecture/plans/JARVIS_PROJECT_CONTINUITY_AND_RECOVERY_HANDOFF.md` | `9eae4ffc1e4cc1f4673abecb880aa37558935026` |

### 30.4 Reviewer findings and Builder disposition

The repository review report at `docs/architecture/reports/INDEPENDENT_DOCUMENTATION_FOUNDATION_REVIEW_2026-11-08.md`, blob `ecd11354a858eb6e46cbd85b816836a2f88973c9`, was retrieved directly. The Builder's response is:

- **DF-F01 — correction applied.** This Section 30 replaces the stale register with the exact 19-path PR #192 snapshot at `f615e11...`, including all fetched blob SHAs, the review report, updated index, updated audit protocol and updated self-review. PR #193's two-file register remains separate.
- **DF-F02 — corrected, limited scope.** The audit's top-level headings are sequential 1–19. This is not a complete semantic or historical cross-reference audit.
- **PR #193 link freshness — corrected.** Three index links were updated from older commit `03502c5719b320b9e323cb1d040ae38737fc7b81` to verified PR #193 HEAD `976aa33f89cc02225296f59246f47982300f5b39`; both destination files were fetched at that revision.
- **DF-09 — NOT MET.** A fixed 17-question test protocol is now recorded in audit Section 19. No genuinely uninvolved participant or session evidence exists.
- **DF-11 — NOT MET.** The received report identifies its author as ChatGPT (GPT-6), the same model identity recorded as Builder. It does not satisfy the project's separate-reviewer requirement.
- **DF-12 — NOT MET.** No exact-revision Project Director decision is recorded or inferred.
- **Other open findings:** PR #173 acceptance provenance; PR #174 accepted-revision header contradiction and follow-on F-02/F-03; PR #178 governance remains proposed/unaccepted; PR #191 stale-base disposition; broader DF-06 link validation; DF-07 cross-lineage status consistency; and DF-08 historical preservation.

No fresh-reader result is fabricated. No acceptance decision is inferred. No PR was merged, rebased, retargeted, cherry-picked or integrated. No source/runtime file was changed. Stage A remains held and implementation remains unauthorized.

## 30A. Documentation-package revision and blob register — refreshed snapshot

This immutable snapshot was fetched from live GitHub metadata and the complete PR #192 changed-file endpoint at parent HEAD `326da3927cd3cd6b34144b3cfad56fe53e137a15`, immediately before this inventory update. The PR changed-file endpoint returned 20 paths, and every path was fetched at that exact branch ref. This inventory update creates the next commit; its own listed blob is therefore the pre-update blob. The resulting inventory blob and final PR HEAD must be verified after the write.

### 30A.1 Pull-request state and dependency register

| Item | Exact revision / state |
|---|---|
| PR #192 | HEAD `326da3927cd3cd6b34144b3cfad56fe53e137a15`; base branch `docs/jarvis-phase-2-whole-brain-integration-map-20261105`; base SHA `61311fe5b44c81c4409c8ba8dc581a83bdd5dd2c`; open, draft, unmerged; 20 changed files |
| PR #193 | HEAD `976aa33f89cc02225296f59246f47982300f5b39`; base branch `plan/brain-implementation-roadmap-20261103`; base SHA `874c732973b6ab303d65a503f5a215b0af8e1153`; open, draft, unmerged; 2 changed files |
| PR #192 formal reviews / inline threads / conversation comments | 0 / 0 / 0 returned in live GitHub queries at this snapshot |
| PR #192 and PR #193 relationship | Separate #179-derived and #175-derived lineages; no integration, rebase, retarget or ancestry change performed |
| PR #191 dependency | PR #191 base `f6267456560a08054d69f7960d2951452b14017c`; PR #179 HEAD `61311fe5b44c81c4409c8ba8dc581a83bdd5dd2c`; compare reports 22 commits ahead, 0 behind |
| `main` | `1273ddbcd0087d189e01388ded2d362fb1e058d2` as recorded in the inventory baseline context; no main-branch write performed |

### 30A.2 PR #192 changed-file blob register

All 20 paths returned by the paginated PR #192 changed-file endpoint were fetched at exact parent HEAD `326da3927cd3cd6b34144b3cfad56fe53e137a15`.

| # | Repository path | Blob SHA |
|---:|---|---|
| 1 | `README.md` | `780651b804b491781fdcac8e248eaca9243797a4` |
| 2 | `docs/ARCHITECTURE.md` | `3c6692b52059e43947d1fd2e7e84debb2362023f` |
| 3 | `docs/JARVIS_BRAIN_MASTER_BLUEPRINT.md` | `0e49d313bf3929aa30140cb7149ebab038918378` |
| 4 | `docs/JARVIS_PHASE_2_COMPLETION.md` | `e0e57a44216fc36c52d469a79abfc8df058515a3` |
| 5 | `docs/README.md` | `00d6a5996b1f76aeefc7fcda5e07a95de4c77288` |
| 6 | `docs/architecture/00_JARVIS_PLANNING_DOCUMENTATION_INDEX_2026-11-07.md` | `b963c9cea549feca0353b2d48e7eb307930f2dcf` |
| 7 | `docs/architecture/inventory/00_JARVIS_DOCUMENTATION_AND_ARTIFACT_INVENTORY_2026-11-04.md` | `3ed6232dd2be077cd1e86fde5fe504b27f9701b0` (pre-update inventory blob) |
| 8 | `docs/architecture/reports/INDEPENDENT_DOCUMENTATION_FOUNDATION_REVIEW_2026-11-08.md` | `ecd11354a858eb6e46cbd85b816836a2f88973c9` |
| 9 | `docs/architecture/reports/INDEPENDENT_REVIEWER_HANDOFF_2026-11-08.md` | `8ee2075ac87a45854c73b587f50a9800d651906d` |
| 10 | `docs/architecture/reports/INDEPENDENT_RE_REVIEW_BUILDER_FOLLOW_UP_2026-11-08.md` | `2d63ed93344a7081dcedb44247536c416322c793` |
| 11 | `docs/architecture/reports/INITIAL_DOCUMENTATION_FOUNDATION_AUDIT_AND_COMPLETION_GATE_2026-11-07.md` | `921314e637afcd4203fca209cb57775af3386347` |
| 12 | `docs/architecture/reports/PHASE_1_REVIEW_CORRECTIONS_AND_SCOPE_RECONCILIATION_2026-11-05.md` | `a459cdfd02d850d455ca526e6823e68525776ba3` |
| 13 | `docs/architecture/reports/PHASE_1_WHOLE_REPOSITORY_INVESTIGATION_AND_REUSE_AUDIT_2026-11-04.md` | `f725eda1e23d6558d90f6f7c87302019ef3a0dfc` |
| 14 | `docs/architecture/reports/PHASE_2_WHOLE_BRAIN_CAPABILITY_TO_SOURCE_INTEGRATION_MAP_2026-11-05.md` | `7cf312f6cc6fd880473a0b6ccc86cf53bf3b3533` |
| 15 | `docs/architecture/reports/WHOLE_BRAIN_DOCUMENTATION_PHASE_BUILDER_SELF_REVIEW_2026-11-07.md` | `af7b620061a8c4adf1d4645150e80553ef1ecc69` |
| 16 | `docs/architecture/reports/WHOLE_BRAIN_PLANNING_SCOPE_AND_BUILDER_CORRECTION_2026-11-07.md` | `0187a0ac71bd0c95e94beb3bf006da9cc7c3605f` |
| 17 | `docs/templates/INDEPENDENT_REVIEW_REPORT_TEMPLATE.md` | `f3176cf1a1f45735a3ad62fa4a865806edc24e08` |
| 18 | `docs/templates/PLANNING_DOCUMENT_TEMPLATE.md` | `b9f71a923b0d717a3b29655574c89c10e0801115` |
| 19 | `docs/templates/README.md` | `7209fd0fcda239349af602490d26b8c708b743da` |
| 20 | `docs/templates/TEST_EVIDENCE_REPORT_TEMPLATE.md` | `9c6bbae48a22beb7c4e95858282d7d8d7b2159c2` |

### 30A.3 PR #193 changed-file blob register

Both changed paths returned by the PR #193 changed-file endpoint were fetched at exact HEAD `976aa33f89cc02225296f59246f47982300f5b39`.

| Repository path | Blob SHA |
|---|---|
| `docs/architecture/plans/00_BRAIN_IMPLEMENTATION_PLAN.md` | `d065e833d2211753985784d9de6e562e0f72bc2b` |
| `docs/architecture/plans/JARVIS_PROJECT_CONTINUITY_AND_RECOVERY_HANDOFF.md` | `9eae4ffc1e4cc1f4673abecb880aa37558935026` |

### 30A.4 Reviewer findings and Builder disposition

The original report `INDEPENDENT_DOCUMENTATION_FOUNDATION_REVIEW_2026-11-08.md` (blob `ecd11354a858eb6e46cbd85b816836a2f88973c9`) and the follow-up report `INDEPENDENT_RE_REVIEW_BUILDER_FOLLOW_UP_2026-11-08.md` (blob `2d63ed93344a7081dcedb44247536c416322c793`) were retrieved directly.

- **DF-F01 — corrected for this parent snapshot.** The previous 19-file register omitted the follow-up report and no longer matched live PR #192. This refreshed register lists all 20 changed paths and exact fetched blobs at parent HEAD `326da392...`. The inventory's own row intentionally records its pre-update blob; it is not a mismatch.
- **DF-F02 — corrected, limited scope.** Audit top-level section numbering is sequential through Section 20. This does not establish a complete semantic or historical cross-reference audit.
- **Follow-up review scope:** The follow-up report reviewed PR #192 HEAD `5f204e3ea72d991ccc5d5695d824dc356fee0700`, not the live parent HEAD `326da392...`. It verifies the prior corrections at its target and recommends NOT CLEARED.
- **DF-09 — NOT MET.** The 17-question protocol is prepared; no genuinely uninvolved participant/session evidence exists.
- **DF-11 — NOT MET.** The follow-up reviewer discloses the same GPT-6 model identity as the Builder. It is useful technical scrutiny but not the qualifying independent review.
- **DF-12 — NOT MET.** No exact-revision Project Director decision is recorded or inferred.
- **PR #173:** Primary PR discussion evidence inspected contains Builder handoff/resubmission comments, not an attributable Project Director acceptance decision for exact architecture revision `97191111...`. Status remains unresolved.
- **PR #174:** Project Director comment `6604790481` accepts exact specification revision `0811a59...` as a planning baseline, not implementation authorization. The document header still says draft for independent review; later comment `6628850155` records further documentation corrections but does not itself close follow-on F-02/F-03 or provide a new Project Director decision.
- **Other open/partial findings:** PR #178 governance remains proposed/unaccepted; PR #191 dependency disposition remains unauthorized; DF-06 broader fragment/external/historical-link validation remains partial; DF-07 cross-lineage status consistency remains partial; DF-08 historical preservation remains partial.

No fresh-reader result is fabricated. No acceptance decision is inferred. No PR was merged, rebased, retargeted, cherry-picked or integrated. No source/runtime file was changed. Stage A remains held and implementation remains unauthorized.

## 30B. Documentation-package revision and blob register — corrected live snapshot

This immutable snapshot was fetched from live GitHub metadata and the complete PR #192 changed-file endpoint at parent HEAD `c1f4a0df600314ef04b2b09b103c7eaca625c9d2`, immediately before this inventory update. The endpoint returned 20 paths; all 20 are listed below. Each path was fetched at the parent revision. This update creates the next commit; its own listed blob is therefore the pre-update blob. The resulting inventory blob and final PR HEAD must be verified after the write.

### 30B.1 Pull-request state and dependency register

| Item | Exact revision / state |
|---|---|
| PR #192 | HEAD `c1f4a0df600314ef04b2b09b103c7eaca625c9d2`; base branch `docs/jarvis-phase-2-whole-brain-integration-map-20261105`; base SHA `61311fe5b44c81c4409c8ba8dc581a83bdd5dd2c`; open, draft, unmerged; 20 changed files |
| PR #193 | HEAD `976aa33f89cc02225296f59246f47982300f5b39`; base branch `plan/brain-implementation-roadmap-20261103`; base SHA `874c732973b6ab303d65a503f5a215b0af8e1153`; open, draft, unmerged; 2 changed files |
| PR #192 formal reviews / inline threads / conversation comments | 0 / 0 / 0 returned in live GitHub queries |
| PR #192 and PR #193 relationship | Separate #179-derived and #175-derived lineages; no integration, rebase, retarget or ancestry change performed |
| PR #191 dependency | PR #191 base `f6267456560a08054d69f7960d2951452b14017c`; PR #179 HEAD `61311fe5b44c81c4409c8ba8dc581a83bdd5dd2c`; compare reports 22 commits ahead, 0 behind |
| `main` | `1273ddbcd0087d189e01388ded2d362fb1e058d2` as recorded in the inventory baseline context; no main-branch write performed |

### 30B.2 PR #192 changed-file blob register

All 20 paths returned by the paginated PR #192 changed-file endpoint were fetched at exact parent HEAD `c1f4a0df600314ef04b2b09b103c7eaca625c9d2`.

| # | Repository path | Blob SHA |
|---:|---|---|
| 1 | `README.md` | `780651b804b491781fdcac8e248eaca9243797a4` |
| 2 | `docs/ARCHITECTURE.md` | `3c6692b52059e43947d1fd2e7e84debb2362023f` |
| 3 | `docs/JARVIS_BRAIN_MASTER_BLUEPRINT.md` | `0e49d313bf3929aa30140cb7149ebab038918378` |
| 4 | `docs/JARVIS_PHASE_2_COMPLETION.md` | `e0e57a44216fc36c52d469a79abfc8df058515a3` |
| 5 | `docs/README.md` | `00d6a5996b1f76aeefc7fcda5e07a95de4c77288` |
| 6 | `docs/architecture/00_JARVIS_PLANNING_DOCUMENTATION_INDEX_2026-11-07.md` | `b963c9cea549feca0353b2d48e7eb307930f2dcf` |
| 7 | `docs/architecture/inventory/00_JARVIS_DOCUMENTATION_AND_ARTIFACT_INVENTORY_2026-11-04.md` | `c975a20b5dda44b316e58082572287e751b02319` (pre-update inventory blob) |
| 8 | `docs/architecture/reports/INDEPENDENT_DOCUMENTATION_FOUNDATION_REVIEW_2026-11-08.md` | `ecd11354a858eb6e46cbd85b816836a2f88973c9` |
| 9 | `docs/architecture/reports/INDEPENDENT_REVIEWER_HANDOFF_2026-11-08.md` | `8ee2075ac87a45854c73b587f50a9800d651906d` |
| 10 | `docs/architecture/reports/INDEPENDENT_RE_REVIEW_BUILDER_FOLLOW_UP_2026-11-08.md` | `2d63ed93344a7081dcedb44247536c416322c793` |
| 11 | `docs/architecture/reports/INITIAL_DOCUMENTATION_FOUNDATION_AUDIT_AND_COMPLETION_GATE_2026-11-07.md` | `921314e637afcd4203fca209cb57775af3386347` |
| 12 | `docs/architecture/reports/PHASE_1_REVIEW_CORRECTIONS_AND_SCOPE_RECONCILIATION_2026-11-05.md` | `a459cdfd02d850d455ca526e6823e68525776ba3` |
| 13 | `docs/architecture/reports/PHASE_1_WHOLE_REPOSITORY_INVESTIGATION_AND_REUSE_AUDIT_2026-11-04.md` | `f725eda1e23d6558d90f6f7c87302019ef3a0dfc` |
| 14 | `docs/architecture/reports/PHASE_2_WHOLE_BRAIN_CAPABILITY_TO_SOURCE_INTEGRATION_MAP_2026-11-05.md` | `7cf312f6cc6fd880473a0b6ccc86cf53bf3b3533` |
| 15 | `docs/architecture/reports/WHOLE_BRAIN_DOCUMENTATION_PHASE_BUILDER_SELF_REVIEW_2026-11-07.md` | `af7b620061a8c4adf1d4645150e80553ef1ecc69` |
| 16 | `docs/architecture/reports/WHOLE_BRAIN_PLANNING_SCOPE_AND_BUILDER_CORRECTION_2026-11-07.md` | `0187a0ac71bd0c95e94beb3bf006da9cc7c3605f` |
| 17 | `docs/templates/INDEPENDENT_REVIEW_REPORT_TEMPLATE.md` | `f3176cf1a1f45735a3ad62fa4a865806edc24e08` |
| 18 | `docs/templates/PLANNING_DOCUMENT_TEMPLATE.md` | `b9f71a923b0d717a3b29655574c89c10e0801115` |
| 19 | `docs/templates/README.md` | `7209fd0fcda239349af602490d26b8c708b743da` |
| 20 | `docs/templates/TEST_EVIDENCE_REPORT_TEMPLATE.md` | `9c6bbae48a22beb7c4e95858282d7d8d7b2159c2` |

### 30B.3 PR #193 changed-file blob register

Both changed paths returned by the PR #193 changed-file endpoint were fetched at exact HEAD `976aa33f89cc02225296f59246f47982300f5b39`.

| Repository path | Blob SHA |
|---|---|
| `docs/architecture/plans/00_BRAIN_IMPLEMENTATION_PLAN.md` | `d065e833d2211753985784d9de6e562e0f72bc2b` |
| `docs/architecture/plans/JARVIS_PROJECT_CONTINUITY_AND_RECOVERY_HANDOFF.md` | `9eae4ffc1e4cc1f4673abecb880aa37558935026` |

### 30B.4 Reviewer findings and Builder disposition

The original report `INDEPENDENT_DOCUMENTATION_FOUNDATION_REVIEW_2026-11-08.md` (blob `ecd11354a858eb6e46cbd85b816836a2f88973c9`) and follow-up report `INDEPENDENT_RE_REVIEW_BUILDER_FOLLOW_UP_2026-11-08.md` (blob `2d63ed93344a7081dcedb44247536c416322c793`) were retrieved directly.

- **DF-F01 — corrected for this parent snapshot.** The previous 19-file register omitted the follow-up report and did not match the live 20-file PR. This corrected register includes all 20 paths and their fetched blobs at parent HEAD `c1f4a0d...`. The inventory's own row intentionally records its pre-update blob; it is not a discrepancy.
- **DF-F02 — corrected, limited scope.** Audit top-level numbering is sequential through Section 20. This does not establish a complete semantic or historical cross-reference audit.
- **Follow-up review scope:** The follow-up report reviewed PR #192 HEAD `5f204e3ea72d991ccc5d5695d824dc356fee0700`, not the live parent HEAD `c1f4a0d...`. It verifies prior corrections at its target and recommends NOT CLEARED.
- **DF-09 — NOT MET.** The 17-question protocol is prepared; no genuinely uninvolved participant/session evidence exists.
- **DF-11 — NOT MET.** The follow-up reviewer discloses the same GPT-6 model identity as the Builder. It is useful technical scrutiny but not the qualifying independent review.
- **DF-12 — NOT MET.** No exact-revision Project Director decision is recorded or inferred.
- **PR #173:** The primary PR discussion evidence inspected contains Builder handoff/resubmission comments, not an attributable Project Director acceptance decision for exact architecture revision `97191111...`. Status remains unresolved.
- **PR #174:** Project Director comment `6604790481` accepts exact specification revision `0811a59...` as a planning baseline, not implementation authorization. The accepted-revision document header still says draft for independent review; later comment `6628850155` records further documentation corrections but does not itself close follow-on F-02/F-03 or provide a new Project Director decision.
- **Other open/partial findings:** PR #178 governance remains proposed/unaccepted; PR #191 dependency disposition remains unauthorized; DF-06 broader fragment/external/historical-link validation remains partial; DF-07 cross-lineage status consistency remains partial; DF-08 historical preservation remains partial.

No fresh-reader result is fabricated. No acceptance decision is inferred. No PR was merged, rebased, retargeted, cherry-picked or integrated. No source/runtime file was changed. Stage A remains held and implementation remains unauthorized.

### 30B.5 Snapshot and self-reference limitations

This register is a snapshot at PR #192 parent HEAD `c1f4a0df600314ef04b2b09b103c7eaca625c9d2`, immediately before this inventory update. The listed inventory blob is its pre-update blob `c975a20b5dda44b316e58082572287e751b02319`. The resulting inventory write creates a later PR head and a new inventory blob; that returned blob and live head must be checked after the write. Future reviewers must fetch live metadata and changed-file paths rather than assume this snapshot remains current.


## 31. Exact documentation-package revision and blob register — 2026-11-08 (superseding live snapshot)

This section supersedes earlier §30 snapshots for the exact PR #192 changed-path register. It was assembled from the complete paginated PR #192 changed-file endpoint and exact file fetches at immutable parent HEAD `70dc6b30e21716cfdc6846f0a77903e177e1046b`, immediately before this inventory update. PR #192 returned 20 changed paths; every path below was fetched at that exact parent. This inventory's own row records its pre-update blob. The inventory update creates the next commit and therefore a new inventory blob; this section does not claim that its parent SHA is the resulting final PR HEAD.

### 31.1 Live PR state at parent snapshot

| Item | Exact state |
|---|---|
| PR #192 | Open, draft, unmerged; branch `docs/whole-brain-planning-scope-correction-20261107` |
| PR #192 parent HEAD | `70dc6b30e21716cfdc6846f0a77903e177e1046b` |
| PR #192 base | `61311fe5b44c81c4409c8ba8dc581a83bdd5dd2c` |
| PR #192 changed paths | 20 |
| PR #193 | Open, draft, unmerged; separate branch `docs/whole-brain-planning-roadmap-hold-20261107` |
| PR #193 HEAD / base | `976aa33f89cc02225296f59246f47982300f5b39` / `874c732973b6ab303d65a503f5a215b0af8e1153` |
| PR #193 changed paths | 2 |
| PR #192 / PR #193 relationship | Separate PR #179-derived and PR #175-derived lineages; no integration, merge, rebase or retarget performed |

### 31.2 PR #192 changed-path and blob register

| # | Repository path | Blob SHA at parent HEAD |
|---:|---|---|
| 1 | `README.md` | `780651b804b491781fdcac8e248eaca9243797a4` |
| 2 | `docs/ARCHITECTURE.md` | `3c6692b52059e43947d1fd2e7e84debb2362023f` |
| 3 | `docs/JARVIS_BRAIN_MASTER_BLUEPRINT.md` | `0e49d313bf3929aa30140cb7149ebab038918378` |
| 4 | `docs/JARVIS_PHASE_2_COMPLETION.md` | `e0e57a44216fc36c52d469a79abfc8df058515a3` |
| 5 | `docs/README.md` | `00d6a5996b1f76aeefc7fcda5e07a95de4c77288` |
| 6 | `docs/architecture/00_JARVIS_PLANNING_DOCUMENTATION_INDEX_2026-11-07.md` | `b963c9cea549feca0353b2d48e7eb307930f2dcf` |
| 7 | `docs/architecture/inventory/00_JARVIS_DOCUMENTATION_AND_ARTIFACT_INVENTORY_2026-11-04.md` | `b7b57b58e957cd3f4929b40b9f7b2f9028b77b67` |
| 8 | `docs/architecture/reports/INDEPENDENT_DOCUMENTATION_FOUNDATION_REVIEW_2026-11-08.md` | `ecd11354a858eb6e46cbd85b816836a2f88973c9` |
| 9 | `docs/architecture/reports/INDEPENDENT_REVIEWER_HANDOFF_2026-11-08.md` | `b452855b39580abd4439a5e1b2a69a7e2e772513` |
| 10 | `docs/architecture/reports/INDEPENDENT_RE_REVIEW_BUILDER_FOLLOW_UP_2026-11-08.md` | `2d63ed93344a7081dcedb44247536c416322c793` |
| 11 | `docs/architecture/reports/INITIAL_DOCUMENTATION_FOUNDATION_AUDIT_AND_COMPLETION_GATE_2026-11-07.md` | `3a2324cfaab48adbeb677f37eb78471fe8d5e31d` |
| 12 | `docs/architecture/reports/PHASE_1_REVIEW_CORRECTIONS_AND_SCOPE_RECONCILIATION_2026-11-05.md` | `a459cdfd02d850d455ca526e6823e68525776ba3` |
| 13 | `docs/architecture/reports/PHASE_1_WHOLE_REPOSITORY_INVESTIGATION_AND_REUSE_AUDIT_2026-11-04.md` | `f725eda1e23d6558d90f6f7c87302019ef3a0dfc` |
| 14 | `docs/architecture/reports/PHASE_2_WHOLE_BRAIN_CAPABILITY_TO_SOURCE_INTEGRATION_MAP_2026-11-05.md` | `7cf312f6cc6fd880473a0b6ccc86cf53bf3b3533` |
| 15 | `docs/architecture/reports/WHOLE_BRAIN_DOCUMENTATION_PHASE_BUILDER_SELF_REVIEW_2026-11-07.md` | `f340170b00c55b5c452e98431a37e07c7cde1746` |
| 16 | `docs/architecture/reports/WHOLE_BRAIN_PLANNING_SCOPE_AND_BUILDER_CORRECTION_2026-11-07.md` | `0187a0ac71bd0c95e94beb3bf006da9cc7c3605f` |
| 17 | `docs/templates/INDEPENDENT_REVIEW_REPORT_TEMPLATE.md` | `f3176cf1a1f45735a3ad62fa4a865806edc24e08` |
| 18 | `docs/templates/PLANNING_DOCUMENT_TEMPLATE.md` | `b9f71a923b0d717a3b29655574c89c10e0801115` |
| 19 | `docs/templates/README.md` | `7209fd0fcda239349af602490d26b8c708b743da` |
| 20 | `docs/templates/TEST_EVIDENCE_REPORT_TEMPLATE.md` | `9c6bbae48a22beb7c4e95858282d7d8d7b2159c2` |

### 31.3 PR #193 separate-lineage snapshot

Both paths were fetched at exact PR #193 HEAD `976aa33f89cc02225296f59246f47982300f5b39`:

| Repository path | Blob SHA |
|---|---|
| `docs/architecture/plans/00_BRAIN_IMPLEMENTATION_PLAN.md` | `d065e833d2211753985784d9de6e562e0f72bc2b` |
| `docs/architecture/plans/JARVIS_PROJECT_CONTINUITY_AND_RECOVERY_HANDOFF.md` | `9eae4ffc1e4cc1f4673abecb880aa37558935026` |

### 31.4 Review findings and gate disposition

The independent review report at parent blob `ecd11354a858eb6e46cbd85b816836a2f88973c9` recommends **CLEARANCE NOT RECOMMENDED**. Its author identifies as ChatGPT (GPT-6), the same model identity as the Builder; it is not qualifying independent review. The Builder follow-up report also shares that identity. Therefore DF-11 remains NOT MET. The 17-question fresh-reader protocol is prepared but no genuine uninvolved participant/session evidence exists; DF-09 remains NOT MET. No exact-revision Project Director acceptance decision is recorded; DF-12 remains NOT MET.

PR #173 exact-revision acceptance provenance remains unresolved. PR #174's exact planning-baseline acceptance event is distinct from its stale draft header and unresolved follow-on F-02/F-03 obligations. PR #178 remains proposed/unaccepted. PR #191's historical-base disposition remains for explicit authority. DF-06, DF-07 and DF-08 remain partial (broader fragment/external/historical link validation, cross-lineage status consistency and historical preservation are not complete). DF-02's section-number correction is recorded in the audit; this does not imply that every semantic/history cross-reference has been exhaustively verified. DF-13 remains PASS: Stage A is held.

### 31.5 Snapshot and self-reference rules

This is a parent-snapshot register, not a mutable claim about the live PR head. The inventory row intentionally records pre-update blob `b7b57b58e957cd3f4929b40b9f7b2f9028b77b67`. After this update, the Builder must fetch the resulting PR #192 HEAD and inventory blob, then fetch the registered paths again at that resulting HEAD to verify that no concurrent change invalidated the snapshot. Any subsequent PR commit makes this register historical until refreshed. A reviewer must always fetch live PR metadata and changed paths before review; do not assume the snapshot remains current.

**Gate status: NOT CLEARED.** Stage A remains NOT STARTED and HELD. Implementation remains unauthorized. This inventory is not a Project Director decision and does not authorize merge, rebase, retarget, cherry-pick or integration.


---

## 32. Exact documentation-package revision and blob register — 2026-11-08

This register supersedes §31 for the PR #192 changed-path snapshot. It was assembled from the complete paginated PR #192 changed-file endpoint and exact file fetches at immutable parent HEAD `d8a92f9cf09d792311764077dc28c24034054ae2`. The endpoint returned 22 paths; all 22 are listed below. This inventory's own row records its pre-update blob. The inventory update creates a new PR commit and blob, so the parent snapshot is intentionally not represented as the resulting PR HEAD.

### 32.1 Live PR state at parent snapshot

| Item | Exact state |
|---|---|
| PR #192 | Open, draft, unmerged; branch `docs/whole-brain-planning-scope-correction-20261107` |
| PR #192 parent HEAD | `d8a92f9cf09d792311764077dc28c24034054ae2` |
| PR #192 base | `61311fe5b44c81c4409c8ba8dc581a83bdd5dd2c` |
| PR #192 changed paths | 22 |
| PR #193 | Open, draft, unmerged; separate PR #175-derived lineage |
| PR #193 HEAD / base | `31f8cafcb0547e70f47e03b503d3125e4573de4b` / `874c732973b6ab303d65a503f5a215b0af8e1153` |
| PR #193 changed paths | 2 |
| PR #192 / PR #193 relationship | Separate lineages; no merge, rebase, retarget or integration performed |

### 32.2 PR #192 exact changed-path and blob register

| # | Repository path | Blob SHA at parent HEAD |
|---:|---|---|
| 1 | `README.md` | `780651b804b491781fdcac8e248eaca9243797a4` |
| 2 | `docs/ARCHITECTURE.md` | `3c6692b52059e43947d1fd2e7e84debb2362023f` |
| 3 | `docs/JARVIS_BRAIN_MASTER_BLUEPRINT.md` | `0e49d313bf3929aa30140cb7149ebab038918378` |
| 4 | `docs/JARVIS_PHASE_2_COMPLETION.md` | `e0e57a44216fc36c52d469a79abfc8df058515a3` |
| 5 | `docs/README.md` | `22a9e9049c5757db3ac51b49dbbdb8b6aa1066ca` |
| 6 | `docs/architecture/00_JARVIS_PLANNING_DOCUMENTATION_INDEX_2026-11-07.md` | `1f4703ac0d894d19992def5a09d20ca7a588d48e` |
| 7 | `docs/architecture/inventory/00_JARVIS_DOCUMENTATION_AND_ARTIFACT_INVENTORY_2026-11-04.md` | `9e41f1fc457515166734234da0f78f98494468b6` (pre-update inventory blob) |
| 8 | `docs/architecture/inventory/HISTORICAL_DOCUMENTATION_PRESERVATION_REGISTER_2026-11-08.md` | `a4421db1c3bf0ef69ece3d32256b9422f1d4abe1` |
| 9 | `docs/architecture/reports/DOCUMENTATION_FOUNDATION_PRESERVATION_AND_LINK_VALIDATION_2026-11-08.md` | `43f3548c0a02c605b52dbd0c5d62c1e9821ef54e` |
| 10 | `docs/architecture/reports/INDEPENDENT_DOCUMENTATION_FOUNDATION_REVIEW_2026-11-08.md` | `ecd11354a858eb6e46cbd85b816836a2f88973c9` |
| 11 | `docs/architecture/reports/INDEPENDENT_REVIEWER_HANDOFF_2026-11-08.md` | `deb092522e10b1b4eaa84e201f7a5c706f5955d6` |
| 12 | `docs/architecture/reports/INDEPENDENT_RE_REVIEW_BUILDER_FOLLOW_UP_2026-11-08.md` | `2d63ed93344a7081dcedb44247536c416322c793` |
| 13 | `docs/architecture/reports/INITIAL_DOCUMENTATION_FOUNDATION_AUDIT_AND_COMPLETION_GATE_2026-11-07.md` | `543c7e79d4e7273f93e2208db30293dc5a4a5928` |
| 14 | `docs/architecture/reports/PHASE_1_REVIEW_CORRECTIONS_AND_SCOPE_RECONCILIATION_2026-11-05.md` | `a459cdfd02d850d455ca526e6823e68525776ba3` |
| 15 | `docs/architecture/reports/PHASE_1_WHOLE_REPOSITORY_INVESTIGATION_AND_REUSE_AUDIT_2026-11-04.md` | `f725eda1e23d6558d90f6f7c87302019ef3a0dfc` |
| 16 | `docs/architecture/reports/PHASE_2_WHOLE_BRAIN_CAPABILITY_TO_SOURCE_INTEGRATION_MAP_2026-11-05.md` | `7cf312f6cc6fd880473a0b6ccc86cf53bf3b3533` |
| 17 | `docs/architecture/reports/WHOLE_BRAIN_DOCUMENTATION_PHASE_BUILDER_SELF_REVIEW_2026-11-07.md` | `791fa9a806458bd5c8b28706a41cb57151aa4c62` |
| 18 | `docs/architecture/reports/WHOLE_BRAIN_PLANNING_SCOPE_AND_BUILDER_CORRECTION_2026-11-07.md` | `0187a0ac71bd0c95e94beb3bf006da9cc7c3605f` |
| 19 | `docs/templates/INDEPENDENT_REVIEW_REPORT_TEMPLATE.md` | `f3176cf1a1f45735a3ad62fa4a865806edc24e08` |
| 20 | `docs/templates/PLANNING_DOCUMENT_TEMPLATE.md` | `b9f71a923b0d717a3b29655574c89c10e0801115` |
| 21 | `docs/templates/README.md` | `7209fd0fcda239349af602490d26b8c708b743da` |
| 22 | `docs/templates/TEST_EVIDENCE_REPORT_TEMPLATE.md` | `9c6bbae48a22beb7c4e95858282d7d8d7b2159c2` |

### 32.3 PR #193 separate-lineage register

Both changed paths were fetched at exact PR #193 HEAD `31f8cafcb0547e70f47e03b503d3125e4573de4b`:

| Repository path | Blob SHA |
|---|---|
| `docs/architecture/plans/00_BRAIN_IMPLEMENTATION_PLAN.md` | `24075b459355cb35e6d940a916aaa809b826bf6e` |
| `docs/architecture/plans/JARVIS_PROJECT_CONTINUITY_AND_RECOVERY_HANDOFF.md` | `e91acaed28761b09854117d85ecb5a971c817395` |

### 32.4 Gate and evidence disposition

- The preservation report closes only its stated branch-tip grouping and selected duplicate-document comparisons. It leaves broader JARVIS PR lineage, two unmatched branch refs, distinct Developmental Brain Plan revisions, and archive/supersession decisions open.
- The report does not establish exhaustive fragment or external-link validation. DF-06 remains partial.
- Cross-lineage status and integration order remain unresolved; PR #192 and PR #193 remain separate. DF-07 remains partial.
- Historical preservation mapping has materially advanced but is not complete. DF-08 remains partial.
- PR #191's base `f6267456560a08054d69f7960d2951452b14017c` is an ancestor of PR #179 HEAD `61311fe5b44c81c4409c8ba8dc581a83bdd5dd2c`; compare reports 22 commits ahead and 0 behind. This is a historical-base lag, not demonstrated divergence. No rebase/retarget is authorized.
- PR #173 acceptance provenance remains unresolved. PR #174's exact planning-baseline acceptance remains evidenced by comment `6604790481`; its stale draft header and F-02/F-03 follow-on obligations remain visible and unresolved. PR #178 remains proposed/unaccepted.
- DF-09 remains NOT MET (no actual uninvolved fresh-reader session); DF-11 remains NOT MET (no qualifying separate reviewer); DF-12 remains NOT MET (no exact-revision authority decision).

**Gate status: NOT CLEARED.** Stage A remains NOT STARTED and HELD. Implementation remains unauthorized.

### 32.5 Snapshot and self-reference

This section records parent HEAD `d8a92f9cf09d792311764077dc28c24034054ae2`. The inventory row intentionally records its pre-update blob `9e41f1fc457515166734234da0f78f98494468b6`. The inventory update creates a new PR commit and blob. The resulting live PR HEAD, inventory blob, changed-path count and registered blobs must be re-fetched after the write. Any later commit makes this snapshot historical. Reviewers must always fetch live metadata and changed paths before review.


---

## 33. Superseded documentation-package revision and blob register — 2026-11-08

This section supersedes §32 for the PR #192 changed-path snapshot. The complete paginated PR #192 changed-file endpoint returned 23 paths. Every path below was fetched at immutable parent HEAD `0a3963012c7b9c8647c02f1bd4e3cbe496f471ac`. This inventory's row records its pre-update blob. The inventory update creates a new commit and blob, so the parent snapshot is not the resulting PR HEAD.

### 33.1 Live PR state at parent snapshot

| Item | Exact state |
|---|---|
| PR #192 | Open, draft, unmerged; branch `docs/whole-brain-planning-scope-correction-20261107` |
| PR #192 parent HEAD | `0a3963012c7b9c8647c02f1bd4e3cbe496f471ac` |
| PR #192 base | `61311fe5b44c81c4409c8ba8dc581a83bdd5dd2c` |
| PR #192 changed paths | 23 |
| PR #193 | Open, draft, unmerged; separate PR #175-derived lineage |
| PR #193 HEAD / base | `31f8cafcb0547e70f47e03b503d3125e4573de4b` / `874c732973b6ab303d65a503f5a215b0af8e1153` |
| PR #193 changed paths | 2 |
| PR #192 / PR #193 | Separate lineages; no integration, merge, rebase, retarget or cherry-pick performed |

### 33.2 PR #192 exact changed-path and blob register

| # | Repository path | Blob SHA at parent HEAD |
|---:|---|---|
| 1 | `README.md` | `780651b804b491781fdcac8e248eaca9243797a4` |
| 2 | `docs/ARCHITECTURE.md` | `3c6692b52059e43947d1fd2e7e84debb2362023f` |
| 3 | `docs/JARVIS_BRAIN_MASTER_BLUEPRINT.md` | `0e49d313bf3929aa30140cb7149ebab038918378` |
| 4 | `docs/JARVIS_PHASE_2_COMPLETION.md` | `e0e57a44216fc36c52d469a79abfc8df058515a3` |
| 5 | `docs/README.md` | `eb8011d298d73e1437e6a38e4c36f89d977592ad` |
| 6 | `docs/architecture/00_JARVIS_PLANNING_DOCUMENTATION_INDEX_2026-11-07.md` | `d217152d2d7f24a5dfe85911bed2649456878696` |
| 7 | `docs/architecture/inventory/00_JARVIS_DOCUMENTATION_AND_ARTIFACT_INVENTORY_2026-11-04.md` | `870315cc136edc91e5b82d9760b47c31ebc606ca` (pre-update inventory blob) |
| 8 | `docs/architecture/inventory/HISTORICAL_DOCUMENTATION_PRESERVATION_REGISTER_2026-11-08.md` | `238160a8bf7510d3648ee5d9fb4518c88f90e49e` |
| 9 | `docs/architecture/reports/DOCUMENTATION_FOUNDATION_PRESERVATION_AND_LINK_VALIDATION_2026-11-08.md` | `81ae9ceab355b63997f47aee24a9e5e01ecfe724` |
| 10 | `docs/architecture/reports/INDEPENDENT_DOCUMENTATION_FOUNDATION_REVIEW_2026-11-08.md` | `ecd11354a858eb6e46cbd85b816836a2f88973c9` |
| 11 | `docs/architecture/reports/INDEPENDENT_REVIEWER_HANDOFF_2026-11-08.md` | `1d14b760bf942c0e0fd2227860585b105585616f` |
| 12 | `docs/architecture/reports/INDEPENDENT_RE_REVIEW_BUILDER_FOLLOW_UP_2026-11-08.md` | `2d63ed93344a7081dcedb44247536c416322c793` |
| 13 | `docs/architecture/reports/INITIAL_DOCUMENTATION_FOUNDATION_AUDIT_AND_COMPLETION_GATE_2026-11-07.md` | `d65023b16987deb779e6eeee3344e00c9a653dec` |
| 14 | `docs/architecture/reports/PHASE_1_REVIEW_CORRECTIONS_AND_SCOPE_RECONCILIATION_2026-11-05.md` | `a459cdfd02d850d455ca526e6823e68525776ba3` |
| 15 | `docs/architecture/reports/PHASE_1_WHOLE_REPOSITORY_INVESTIGATION_AND_REUSE_AUDIT_2026-11-04.md` | `f725eda1e23d6558d90f6f7c87302019ef3a0dfc` |
| 16 | `docs/architecture/reports/PHASE_2_WHOLE_BRAIN_CAPABILITY_TO_SOURCE_INTEGRATION_MAP_2026-11-05.md` | `7cf312f6cc6fd880473a0b6ccc86cf53bf3b3533` |
| 17 | `docs/architecture/reports/PR_174_FOLLOW_ON_REVIEW_PROVENANCE_RECOVERY_2026-11-06.md` | `f85c0e48dba9fc693d8debeb5dbbb21d023e40c6` |
| 18 | `docs/architecture/reports/WHOLE_BRAIN_DOCUMENTATION_PHASE_BUILDER_SELF_REVIEW_2026-11-07.md` | `3cd2c1d7d6eacdf3b47047fee3144044e32877b2` |
| 19 | `docs/architecture/reports/WHOLE_BRAIN_PLANNING_SCOPE_AND_BUILDER_CORRECTION_2026-11-07.md` | `0187a0ac71bd0c95e94beb3bf006da9cc7c3605f` |
| 20 | `docs/templates/INDEPENDENT_REVIEW_REPORT_TEMPLATE.md` | `f3176cf1a1f45735a3ad62fa4a865806edc24e08` |
| 21 | `docs/templates/PLANNING_DOCUMENT_TEMPLATE.md` | `b9f71a923b0d717a3b29655574c89c10e0801115` |
| 22 | `docs/templates/README.md` | `7209fd0fcda239349af602490d26b8c708b743da` |
| 23 | `docs/templates/TEST_EVIDENCE_REPORT_TEMPLATE.md` | `9c6bbae48a22beb7c4e95858282d7d8d7b2159c2` |

### 33.3 PR #193 separate-lineage register

Both changed paths were fetched at exact PR #193 HEAD `31f8cafcb0547e70f47e03b503d3125e4573de4b`:

| Repository path | Blob SHA |
|---|---|
| `docs/architecture/plans/00_BRAIN_IMPLEMENTATION_PLAN.md` | `24075b459355cb35e6d940a916aaa809b826bf6e` |
| `docs/architecture/plans/JARVIS_PROJECT_CONTINUITY_AND_RECOVERY_HANDOFF.md` | `e91acaed28761b09854117d85ecb5a971c817395` |

### 33.4 Corrected dependency and authority findings

- PR #191 base `f6267456560a08054d69f7960d2951452b14017c` is an ancestor of PR #179 HEAD `61311fe5b44c81c4409c8ba8dc581a83bdd5dd2c` (22 ahead, 0 behind). PR #191 HEAD `609d38ede50bbdd98a93dfed112781eacabee9fd` compared with PR #179 HEAD is **diverged: 1 ahead, 22 behind**. Retargeting alone does not reconcile the branch histories. An authority decision is required before a dependent revision is prepared.
- PR #173 exact-revision acceptance remains unestablished from primary PR discussion evidence.
- PR #174 exact planning-baseline acceptance is evidenced by Project Director comment `6604790481`. The later follow-on F-02/F-03 report is only partially recovered; its original report is unavailable verbatim, both obligations remain open, and the provenance limitation awaits Project Director disposition.
- PR #178 governance remains proposed/unaccepted.
- The historical preservation report closes only its enumerated branch-tip and selected duplicate-document comparisons. Broader historical lineage and archive/supersession work remains partial.
- DF-06 remains partial: repository-relative path coverage is bounded; fragment, full external reachability/semantic and exhaustive historical cross-branch validation remain unproven.
- DF-07 remains partial: PR #192 and #193 remain separate lineages; status consistency needs independent confirmation.
- DF-08 remains partial: preservation mapping has materially advanced but broader lineage, unmatched refs and archive/supersession decisions remain open.
- DF-09 remains NOT MET (no actual uninvolved fresh-reader session); DF-11 remains NOT MET (no qualifying separate reviewer); DF-12 remains NOT MET (no exact-revision authority decision).

**Gate status: NOT CLEARED.** Stage A remains NOT STARTED and HELD. Implementation remains unauthorized.

### 33.5 Snapshot and self-reference

This register records parent PR #192 HEAD `0a3963012c7b9c8647c02f1bd4e3cbe496f471ac`. The inventory row intentionally records its pre-update blob `870315cc136edc91e5b82d9760b47c31ebc606ca`. The inventory update creates a new commit and blob. Re-fetch live PR metadata, changed paths and the resulting inventory blob after the write. Any subsequent PR commit makes this snapshot historical. Reviewers must fetch the actual live review target rather than treating this register as permanently current.


---

## 33A. Corrected documentation-package revision and blob register — 2026-11-08 (remediation snapshot)

This section supersedes earlier PR #192 changed-path registers for the exact parent snapshot below. The complete paginated PR #192 changed-file endpoint returned 23 paths. Every path was fetched at exact parent HEAD `0a3963012c7b9c8647c02f1bd4e3cbe496f471ac`. The inventory row records its pre-update blob. This update creates the next commit; the resulting inventory blob and final live PR HEAD must be verified afterward.

### 33A.1 Parent snapshot and PR state

| Item | Exact state at parent snapshot |
|---|---|
| PR #192 | Open, draft, unmerged |
| PR #192 branch | `docs/whole-brain-planning-scope-correction-20261107` |
| PR #192 parent HEAD | `0a3963012c7b9c8647c02f1bd4e3cbe496f471ac` |
| PR #192 base | `61311fe5b44c81c4409c8ba8dc581a83bdd5dd2c` |
| PR #192 changed paths | 23 |
| PR #193 | Open, draft, unmerged; separate PR #175-derived lineage |
| PR #193 HEAD / base | `3fc4c12add3656578da949689955aafd3b2b83af` / `874c732973b6ab303d65a503f5a215b0af8e1153` |
| PR #193 changed paths | 2 |
| PR #192 / PR #193 relationship | Separate PR #179-derived and PR #175-derived lineages; no integration, merge, rebase or retarget performed |

### 33A.2 PR #192 changed-path and blob register

All 23 changed paths returned by the PR #192 endpoint were fetched at exact parent HEAD `0a3963012c7b9c8647c02f1bd4e3cbe496f471ac`.

| # | Repository path | Blob SHA at parent HEAD |
|---:|---|---|
| 1 | `README.md` | `780651b804b491781fdcac8e248eaca9243797a4` |
| 2 | `docs/ARCHITECTURE.md` | `3c6692b52059e43947d1fd2e7e84debb2362023f` |
| 3 | `docs/JARVIS_BRAIN_MASTER_BLUEPRINT.md` | `0e49d313bf3929aa30140cb7149ebab038918378` |
| 4 | `docs/JARVIS_PHASE_2_COMPLETION.md` | `e0e57a44216fc36c52d469a79abfc8df058515a3` |
| 5 | `docs/README.md` | `eb8011d298d73e1437e6a38e4c36f89d977592ad` |
| 6 | `docs/architecture/00_JARVIS_PLANNING_DOCUMENTATION_INDEX_2026-11-07.md` | `d217152d2d7f24a5dfe85911bed2649456878696` |
| 7 | `docs/architecture/inventory/00_JARVIS_DOCUMENTATION_AND_ARTIFACT_INVENTORY_2026-11-04.md` | `870315cc136edc91e5b82d9760b47c31ebc606ca` (pre-update inventory blob) |
| 8 | `docs/architecture/inventory/HISTORICAL_DOCUMENTATION_PRESERVATION_REGISTER_2026-11-08.md` | `238160a8bf7510d3648ee5d9fb4518c88f90e49e` |
| 9 | `docs/architecture/reports/DOCUMENTATION_FOUNDATION_PRESERVATION_AND_LINK_VALIDATION_2026-11-08.md` | `81ae9ceab355b63997f47aee24a9e5e01ecfe724` |
| 10 | `docs/architecture/reports/INDEPENDENT_DOCUMENTATION_FOUNDATION_REVIEW_2026-11-08.md` | `ecd11354a858eb6e46cbd85b816836a2f88973c9` |
| 11 | `docs/architecture/reports/INDEPENDENT_REVIEWER_HANDOFF_2026-11-08.md` | `1d14b760bf942c0e0fd2227860585b105585616f` |
| 12 | `docs/architecture/reports/INDEPENDENT_RE_REVIEW_BUILDER_FOLLOW_UP_2026-11-08.md` | `2d63ed93344a7081dcedb44247536c416322c793` |
| 13 | `docs/architecture/reports/INITIAL_DOCUMENTATION_FOUNDATION_AUDIT_AND_COMPLETION_GATE_2026-11-07.md` | `d65023b16987deb779e6eeee3344e00c9a653dec` |
| 14 | `docs/architecture/reports/PHASE_1_REVIEW_CORRECTIONS_AND_SCOPE_RECONCILIATION_2026-11-05.md` | `a459cdfd02d850d455ca526e6823e68525776ba3` |
| 15 | `docs/architecture/reports/PHASE_1_WHOLE_REPOSITORY_INVESTIGATION_AND_REUSE_AUDIT_2026-11-04.md` | `f725eda1e23d6558d90f6f7c87302019ef3a0dfc` |
| 16 | `docs/architecture/reports/PHASE_2_WHOLE_BRAIN_CAPABILITY_TO_SOURCE_INTEGRATION_MAP_2026-11-05.md` | `7cf312f6cc6fd880473a0b6ccc86cf53bf3b3533` |
| 17 | `docs/architecture/reports/PR_174_FOLLOW_ON_REVIEW_PROVENANCE_RECOVERY_2026-11-06.md` | `f85c0e48dba9fc693d8debeb5dbbb21d023e40c6` |
| 18 | `docs/architecture/reports/WHOLE_BRAIN_DOCUMENTATION_PHASE_BUILDER_SELF_REVIEW_2026-11-07.md` | `3cd2c1d7d6eacdf3b47047fee3144044e32877b2` |
| 19 | `docs/architecture/reports/WHOLE_BRAIN_PLANNING_SCOPE_AND_BUILDER_CORRECTION_2026-11-07.md` | `0187a0ac71bd0c95e94beb3bf006da9cc7c3605f` |
| 20 | `docs/templates/INDEPENDENT_REVIEW_REPORT_TEMPLATE.md` | `f3176cf1a1f45735a3ad62fa4a865806edc24e08` |
| 21 | `docs/templates/PLANNING_DOCUMENT_TEMPLATE.md` | `b9f71a923b0d717a3b29655574c89c10e0801115` |
| 22 | `docs/templates/README.md` | `7209fd0fcda239349af602490d26b8c708b743da` |
| 23 | `docs/templates/TEST_EVIDENCE_REPORT_TEMPLATE.md` | `9c6bbae48a22beb7c4e95858282d7d8d7b2159c2` |

### 33A.3 PR #193 separate-lineage blob register

Both changed paths were fetched at exact PR #193 HEAD `3fc4c12add3656578da949689955aafd3b2b83af`.

| Repository path | Blob SHA |
|---|---|
| `docs/architecture/plans/00_BRAIN_IMPLEMENTATION_PLAN.md` | `86d35317d9e41297fc47a4fbc5850b43c456a8bf` |
| `docs/architecture/plans/JARVIS_PROJECT_CONTINUITY_AND_RECOVERY_HANDOFF.md` | `a2f2e20655a7315fb5539f956c3fd2ddd3558dd4` |

### 33A.4 Corrected authority, dependency and gate disposition

- **PR #173:** its exact-revision Project Director acceptance remains unestablished in the primary PR discussion evidence. The architecture remains proposed/unverified; no later PR's statement is substituted.
- **PR #174:** exact HEAD `0811a59e46bf934e32e794f90e4e7d18d4e2bd97` was accepted as a planning baseline by Project Director comment `6604790481`. The stale draft header was corrected in later documentation-only PR #174 HEAD `89cc526d735a645a848e84d5a67dde810819f96f`. Follow-on F-02/F-03 remain open, and the original report was not recovered verbatim.
- **PR #178:** governance remains proposed/unaccepted.
- **PR #191:** direct comparison of PR #179 HEAD `61311fe5b44c81c4409c8ba8dc581a83bdd5dd2c` to PR #191 HEAD `609d38ede50bbdd98a93dfed112781eacabee9fd` is diverged: 1 ahead / 22 behind, merge base `f6267456560a08054d69f7960d2951452b14017c`. Retargeting alone is insufficient. The Project Director must choose historical-base review or authorize a dependent revision; no history rewrite has occurred.
- **DF-06:** remains partial. Prior 63-relative-link path validation is bounded to its exact earlier revision. External URL occurrences, heading fragments and exhaustive historical cross-branch links remain unverified.
- **DF-07 / DF-08:** remain partial. PR #192/#193 are separate lineages; the broader historical PR/branch map, unmatched branch provenance, distinct Developmental Brain Plan revisions and archive/supersession disposition remain open.
- **DF-09:** NOT MET; no genuine uninvolved reader has completed the 17-question protocol.
- **DF-11:** NOT MET; the available reviewer reports share the Builder's GPT-6 identity and do not qualify.
- **DF-12:** NOT MET; no exact-revision Project Director decision has been recorded.
- **DF-13:** PASS for the hold only; Stage A remains not started and held.

**Gate status: NOT CLEARED.** The PR #174 status-header and PR-description corrections are complete. They do not complete the human reader, separate reviewer, remaining provenance/dependency/link/preservation evidence, or Project Director decision requirements.

### 33A.5 Snapshot and self-reference boundary

This section records parent PR #192 HEAD `0a3963012c7b9c8647c02f1bd4e3cbe496f471ac`. The inventory row intentionally records its pre-update blob `870315cc136edc91e5b82d9760b47c31ebc606ca`. This inventory update creates the next PR commit and a new inventory blob. The resulting PR #192 HEAD, inventory blob, changed-path count and registered file blobs must be re-fetched after the write. Any later commit makes this snapshot historical. Reviewers must always fetch live PR metadata and changed paths before review.


---

## 34. Post-correction exact revision refresh — 2026-11-08

This section supersedes §33A for the PR #192 parent snapshot. Sections §33 and §33A remain historical snapshots. After §33 was written, the Planning Documentation Index and foundation audit received further corrections. The live PR #192 changed-file endpoint still returned the same 23 paths. The updated index and audit blobs were fetched at parent HEAD `7eade1395de5fd205c8f537ab46978a4e276b582`; all other PR #192 changed-path blobs remain as registered in §33.

### 34.1 Exact parent and current related revisions

| Item | Exact state |
|---|---|
| PR #192 parent HEAD | `7eade1395de5fd205c8f537ab46978a4e276b582` |
| PR #192 base | `61311fe5b44c81c4409c8ba8dc581a83bdd5dd2c` |
| PR #192 changed paths | 23 |
| PR #193 HEAD / base | `3fc4c12add3656578da949689955aafd3b2b83af` / `874c732973b6ab303d65a503f5a215b0af8e1153` |
| PR #193 changed paths | 2 |
| PR #174 current HEAD at this refresh | `922912283d173e24df891ba23d0e2dfc17e0f4b4` |
| PR #174 current specification blob | `ac1621c43d60b2a556438371287c07ab2b20c8aa` |

### 34.2 Updated PR #192 blobs

Only the following two registered paths changed after the §33 parent snapshot:

| Repository path | Updated blob SHA at parent HEAD |
|---|---|
| `docs/architecture/00_JARVIS_PLANNING_DOCUMENTATION_INDEX_2026-11-07.md` | `0b5d6143a715f4c71b1ffa7cd14189016c4c9e15` |
| `docs/architecture/reports/INITIAL_DOCUMENTATION_FOUNDATION_AUDIT_AND_COMPLETION_GATE_2026-11-07.md` | `5d4be0db6ca8320eddb9df1636f9faf3f0e1a00e` |

All remaining 21 PR #192 paths retain the exact blobs listed in §33A.2 at this parent snapshot. The inventory itself retains its pre-update blob `29aea598d6658414b919379b1cafff79ad3e7d78`; this update creates its next blob and PR commit.

### 34.3 Authority and status corrections

The updated audit §26 now records:
- PR #174's follow-on F-02/F-03 recovery details and their still-open status;
- the correct PR #191 head graph: PR #191 is one commit ahead and 22 behind PR #179, with merge base `f6267456560a08054d69f7960d2951452b14017c`;
- 63 relative target paths resolved at the earlier bounded validation snapshot, while fragments, 143 external URL occurrences and exhaustive historical cross-branch links remain unverified;
- the historical preservation report and supplemental register materially advance DF-08 without completing it;
- DF-09, DF-11 and DF-12 remain NOT MET.

The PR #174 specification at current HEAD `922912283d173e24df891ba23d0e2dfc17e0f4b4` preserves acceptance of exact planning baseline `0811a59e46bf934e32e794f90e4e7d18d4e2bd97`, explicitly labels PR #173 as an unverified parent proposal, and removes the stale draft footer. Its blob is `ac1621c43d60b2a556438371287c07ab2b20c8aa`. These are status/provenance wording corrections only; they do not change the accepted substantive specification or authorize implementation.

**Gate status remains NOT CLEARED.** Stage A remains NOT STARTED and HELD. Implementation remains unauthorized.

### 34.4 Snapshot and self-reference

This section records PR #192 parent HEAD `7eade1395de5fd205c8f537ab46978a4e276b582`. The inventory row intentionally records pre-update blob `29aea598d6658414b919379b1cafff79ad3e7d78`. After this write, fetch the resulting live PR #192 HEAD, inventory blob and changed-file list. Any subsequent commit makes this register historical; reviewers must use live metadata.


> **Superseded snapshot:** This initial §33 register predates the corrected PR #191 head comparison and the later PR #193 navigation refresh. Its PR #191 status wording is superseded. Retain it as historical evidence only; use §§33A and 34 for later snapshots.
## 35. Final documentation-package changed-path/blob register — 2026-11-08

This section supersedes §34 for the live PR #192 changed-path snapshot. It was assembled from the complete PR #192 changed-file endpoint and exact file fetches at immutable parent HEAD `0b4fbd42c44dd9f4e63bc4a25bff0782890c99b4`. The endpoint returned **23 changed paths**; all 23 were fetched successfully at this exact parent. The inventory row below records its own pre-update blob. This update creates the next PR commit, so the parent snapshot is intentionally distinct from the resulting PR HEAD.

### 35.1 Live lineage and review state at parent snapshot

| Item | Exact state |
|---|---|
| PR #192 | Open, draft, unmerged; branch `docs/whole-brain-planning-scope-correction-20261107` |
| PR #192 parent HEAD | `0b4fbd42c44dd9f4e63bc4a25bff0782890c99b4` |
| PR #192 base | `61311fe5b44c81c4409c8ba8dc581a83bdd5dd2c` |
| PR #192 changed paths | 23 |
| PR #192 formal reviews / inline threads / conversation comments | 0 / 0 / 0 returned at the final pre-inventory query |
| PR #193 | Open, draft, unmerged; separate PR #175-derived lineage |
| PR #193 HEAD / base | `d2ccbbb26595f28fb7488db4dbe778e7ddd58c7a` / `874c732973b6ab303d65a503f5a215b0af8e1153` |
| PR #193 changed paths | 2 |
| PR #174 current status-clarification HEAD | `922912283d173e24df891ba23d0e2dfc17e0f4b4`; accepted planning-baseline event remains tied to exact earlier HEAD `0811a59e46bf934e32e794f90e4e7d18d4e2bd97` |
| PR #192 / PR #193 relationship | Separate lineages; immutable snapshot links only; no merge, rebase, retarget, cherry-pick or integration |

### 35.2 PR #192 exact changed-path and blob register

| # | Repository path | Blob SHA at parent HEAD |
|---:|---|---|
| 1 | `README.md` | `780651b804b491781fdcac8e248eaca9243797a4` |
| 2 | `docs/ARCHITECTURE.md` | `3c6692b52059e43947d1fd2e7e84debb2362023f` |
| 3 | `docs/JARVIS_BRAIN_MASTER_BLUEPRINT.md` | `0e49d313bf3929aa30140cb7149ebab038918378` |
| 4 | `docs/JARVIS_PHASE_2_COMPLETION.md` | `e0e57a44216fc36c52d469a79abfc8df058515a3` |
| 5 | `docs/README.md` | `36a1723943bb7ff3575cd336206126f47324b8b5` |
| 6 | `docs/architecture/00_JARVIS_PLANNING_DOCUMENTATION_INDEX_2026-11-07.md` | `6dc312c1055a32af6ece0ed3f4cb44834b1e2ef8` |
| 7 | `docs/architecture/inventory/00_JARVIS_DOCUMENTATION_AND_ARTIFACT_INVENTORY_2026-11-04.md` | `8d7f8e3dbc293d679ae29610c44688b56bfffd1b` (pre-update inventory blob) |
| 8 | `docs/architecture/inventory/HISTORICAL_DOCUMENTATION_PRESERVATION_REGISTER_2026-11-08.md` | `96539183fab3a2b630a8e9154f183b0bfada9016` |
| 9 | `docs/architecture/reports/DOCUMENTATION_FOUNDATION_PRESERVATION_AND_LINK_VALIDATION_2026-11-08.md` | `81ae9ceab355b63997f47aee24a9e5e01ecfe724` |
| 10 | `docs/architecture/reports/INDEPENDENT_DOCUMENTATION_FOUNDATION_REVIEW_2026-11-08.md` | `ecd11354a858eb6e46cbd85b816836a2f88973c9` |
| 11 | `docs/architecture/reports/INDEPENDENT_REVIEWER_HANDOFF_2026-11-08.md` | `207b72706e9c6c82e27be25ee9c3ad15a18a19a9` |
| 12 | `docs/architecture/reports/INDEPENDENT_RE_REVIEW_BUILDER_FOLLOW_UP_2026-11-08.md` | `2d63ed93344a7081dcedb44247536c416322c793` |
| 13 | `docs/architecture/reports/INITIAL_DOCUMENTATION_FOUNDATION_AUDIT_AND_COMPLETION_GATE_2026-11-07.md` | `71fc6aa1f0bab767a673467f68cbb617b3b432a6` |
| 14 | `docs/architecture/reports/PHASE_1_REVIEW_CORRECTIONS_AND_SCOPE_RECONCILIATION_2026-11-05.md` | `a459cdfd02d850d455ca526e6823e68525776ba3` |
| 15 | `docs/architecture/reports/PHASE_1_WHOLE_REPOSITORY_INVESTIGATION_AND_REUSE_AUDIT_2026-11-04.md` | `f725eda1e23d6558d90f6f7c87302019ef3a0dfc` |
| 16 | `docs/architecture/reports/PHASE_2_WHOLE_BRAIN_CAPABILITY_TO_SOURCE_INTEGRATION_MAP_2026-11-05.md` | `7cf312f6cc6fd880473a0b6ccc86cf53bf3b3533` |
| 17 | `docs/architecture/reports/PR_174_FOLLOW_ON_REVIEW_PROVENANCE_RECOVERY_2026-11-06.md` | `d01fa6170b87254619d469d276ba57e813c08ff3` |
| 18 | `docs/architecture/reports/WHOLE_BRAIN_DOCUMENTATION_PHASE_BUILDER_SELF_REVIEW_2026-11-07.md` | `c7892d54fce8fc27e43ba92240be306884d49cf9` |
| 19 | `docs/architecture/reports/WHOLE_BRAIN_PLANNING_SCOPE_AND_BUILDER_CORRECTION_2026-11-07.md` | `0187a0ac71bd0c95e94beb3bf006da9cc7c3605f` |
| 20 | `docs/templates/INDEPENDENT_REVIEW_REPORT_TEMPLATE.md` | `f3176cf1a1f45735a3ad62fa4a865806edc24e08` |
| 21 | `docs/templates/PLANNING_DOCUMENT_TEMPLATE.md` | `b9f71a923b0d717a3b29655574c89c10e0801115` |
| 22 | `docs/templates/README.md` | `7209fd0fcda239349af602490d26b8c708b743da` |
| 23 | `docs/templates/TEST_EVIDENCE_REPORT_TEMPLATE.md` | `9c6bbae48a22beb7c4e95858282d7d8d7b2159c2` |

### 35.3 PR #193 separate-lineage register

Both PR #193 changed paths were fetched at exact HEAD `d2ccbbb26595f28fb7488db4dbe778e7ddd58c7a`:

| Repository path | Blob SHA |
|---|---|
| `docs/architecture/plans/00_BRAIN_IMPLEMENTATION_PLAN.md` | `d001ba9a3e2b8ffbc0fd2f5cba9e573f5af93c74` |
| `docs/architecture/plans/JARVIS_PROJECT_CONTINUITY_AND_RECOVERY_HANDOFF.md` | `cc426df109b795a97fd06aef2ee8d4ecd613a780` |

### 35.4 PR #191 exact graph disposition

PR #191 base is `f6267456560a08054d69f7960d2951452b14017c`; PR #179 HEAD is `61311fe5b44c81c4409c8ba8dc581a83bdd5dd2c`; PR #191 HEAD is `609d38ede50bbdd98a93dfed112781eacabee9fd`.

- Base-to-PR #179 comparison: 22 commits ahead, 0 behind; PR #191 base is an ancestor of current PR #179.
- PR #179 HEAD to PR #191 HEAD comparison: **diverged**, 1 commit ahead and 22 commits behind; merge base `f6267456560a08054d69f7960d2951452b14017c`.
- Retargeting alone does not reconcile the histories. The Project Director must decide whether PR #191 remains a historical-base review artifact or whether a dependent revision may replay its single unique document commit onto the current PR #179 line. No rebase, cherry-pick or retarget is authorized or performed.

### 35.5 Authority, preservation and gate status

- PR #173 primary exact-revision Project Director acceptance remains unverified. Its architecture document must remain proposed/unverified unless primary evidence or an explicit Director disposition is recorded.
- PR #174's accepted planning-baseline event remains tied to exact HEAD `0811a59e46bf934e32e794f90e4e7d18d4e2bd97`. Its later administrative status revision `922912283d173e24df891ba23d0e2dfc17e0f4b4` is not a new approval and does not change the substantive mechanism specification. Follow-on F-02/F-03 remain open.
- The recovered F-02/F-03 review summary is secondary and partial; the original full report and exact inline annotations remain unavailable.
- PR #178 governance remains proposed/unaccepted. PR #175 Gate A remains not cleared. PR #179 does not establish whole-Brain completeness.
- The 68-path historical preservation register and the earlier selected PR #96/#97/#148/#156/#170 comparison report materially advance DF-08, but broader non-JARVIS PR lineage, unmatched branch refs, Developmental Brain Plan revision disposition and archive/supersession decisions remain open.
- **DF-06 remains PARTIAL:** at exact parent HEAD `0b4fbd42c44dd9f4e63bc4a25bff0782890c99b4`, 76 relative Markdown link occurrences across all 23 changed files were resolved against a complete, non-truncated 252-path repository tree, with zero missing relative targets. The same files contained 143 external URL occurrences; their reachability/semantics and heading fragments were not exhaustively checked, nor were all historical cross-branch links. This is bounded path validation, not full link validation.
- DF-09 remains NOT MET (no actual uninvolved fresh-reader session); DF-11 remains NOT MET (no qualifying separate reviewer); DF-12 remains NOT MET (no exact-revision Project Director decision).

**Gate status: NOT CLEARED.** Stage A remains NOT STARTED and HELD. Implementation remains unauthorized.

### 35.6 Snapshot and self-reference

This section records parent HEAD `0b4fbd42c44dd9f4e63bc4a25bff0782890c99b4`. The inventory row intentionally records its pre-update blob `8d7f8e3dbc293d679ae29610c44688b56bfffd1b`. The inventory update creates a new PR commit and new inventory blob. The resulting live PR HEAD, inventory blob and all 23 changed paths must be re-fetched after the write. Any later PR commit makes this snapshot historical. Reviewers must always fetch live metadata and changed paths before review.
