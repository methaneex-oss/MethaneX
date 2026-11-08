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

This register refreshes the documentation package against the live PR metadata fetched for the Builder response. The values below are exact pre-update branch heads and blob SHAs fetched from those commits. They supersede earlier branch-head snapshots for this review pass only; earlier snapshots remain as historical audit evidence.

### 30.1 Pull-request state and dependency register

| Item | Exact revision / state |
|---|---|
| PR #192 | HEAD `cd61ace37206ed4621f84dbe0e3ca2a22c86947e`; base branch `docs/jarvis-phase-2-whole-brain-integration-map-20261105`; base SHA `61311fe5b44c81c4409c8ba8dc581a83bdd5dd2c`; open, draft, unmerged; 17 changed files |
| PR #193 | HEAD `976aa33f89cc02225296f59246f47982300f5b39`; base branch `plan/brain-implementation-roadmap-20261103`; base SHA `874c732973b6ab303d65a503f5a215b0af8e1153`; open, draft, unmerged; 2 changed files |
| PR #192 formal reviews / threads / conversation comments | 0 / 0 / 0 returned |
| PR #193 formal reviews / threads / conversation comments | 0 / 0 / 0 returned |
| PR #192 and PR #193 relationship | Separate #179-derived and #175-derived lineages; no integration or ancestry change performed |
| `main` | `1273ddbcd0087d189e01388ded2d362fb1e058d2` as recorded in the live PR metadata context; no main-branch write performed |

### 30.2 PR #192 changed-file blob register

Every changed path returned by the live PR #192 changed-file endpoint was fetched at exact HEAD `cd61ace37206ed4621f84dbe0e3ca2a22c86947e`.

| Repository path | Blob SHA |
|---|---|
| `README.md` | `780651b804b491781fdcac8e248eaca9243797a4` |
| `docs/ARCHITECTURE.md` | `3c6692b52059e43947d1fd2e7e84debb2362023f` |
| `docs/JARVIS_BRAIN_MASTER_BLUEPRINT.md` | `0e49d313bf3929aa30140cb7149ebab038918378` |
| `docs/JARVIS_PHASE_2_COMPLETION.md` | `e0e57a44216fc36c52d469a79abfc8df058515a3` |
| `docs/README.md` | `00d6a5996b1f76aeefc7fcda5e07a95de4c77288` |
| `docs/architecture/00_JARVIS_PLANNING_DOCUMENTATION_INDEX_2026-11-07.md` | `1318ea9af7455a19fae1e67f669e176518b2696b` |
| `docs/architecture/inventory/00_JARVIS_DOCUMENTATION_AND_ARTIFACT_INVENTORY_2026-11-04.md` | `b91d03ecb738be0fefa83a0902c80cb8da056211` |
| `docs/architecture/reports/INITIAL_DOCUMENTATION_FOUNDATION_AUDIT_AND_COMPLETION_GATE_2026-11-07.md` | `1ed4c34f1444112f4a184dbe0e3ca2a22c86947e` |
| `docs/architecture/reports/PHASE_1_REVIEW_CORRECTIONS_AND_SCOPE_RECONCILIATION_2026-11-05.md` | `a459cdfd02d850d455ca526e6823e68525776ba3` |
| `docs/architecture/reports/PHASE_1_WHOLE_REPOSITORY_INVESTIGATION_AND_REUSE_AUDIT_2026-11-04.md` | `f725eda1e23d6558d90f6f7c87302019ef3a0dfc` |
| `docs/architecture/reports/PHASE_2_WHOLE_BRAIN_CAPABILITY_TO_SOURCE_INTEGRATION_MAP_2026-11-05.md` | `7cf312f6cc6fd880473a0b6ccc86cf53bf3b3533` |
| `docs/architecture/reports/WHOLE_BRAIN_DOCUMENTATION_PHASE_BUILDER_SELF_REVIEW_2026-11-07.md` | `370456c7f0699e54bf7fe8979abe8eb0de551996` |
| `docs/architecture/reports/WHOLE_BRAIN_PLANNING_SCOPE_AND_BUILDER_CORRECTION_2026-11-07.md` | `0187a0ac71bd0c95e94beb3bf006da9cc7c3605f` |
| `docs/templates/INDEPENDENT_REVIEW_REPORT_TEMPLATE.md` | `f3176cf1a1f45735a3ad62fa4a865806edc24e08` |
| `docs/templates/PLANNING_DOCUMENT_TEMPLATE.md` | `b9f71a923b0d717a3b29655574c89c10e0801115` |
| `docs/templates/README.md` | `7209fd0fcda239349af602490d26b8c708b743da` |
| `docs/templates/TEST_EVIDENCE_REPORT_TEMPLATE.md` | `9c6bbae48a22beb7c4e95858282d7d8d7b2159c2` |

### 30.3 PR #193 changed-file blob register

Both changed paths returned by the live PR #193 changed-file endpoint were fetched at exact HEAD `976aa33f89cc02225296f59246f47982300f5b39`.

| Repository path | Blob SHA |
|---|---|
| `docs/architecture/plans/00_BRAIN_IMPLEMENTATION_PLAN.md` | `d065e833d2211753985784d9de6e562e0f72bc2b` |
| `docs/architecture/plans/JARVIS_PROJECT_CONTINUITY_AND_RECOVERY_HANDOFF.md` | `9eae4ffc1e4cc1f4673abecb880aa37558935026` |

### 30.4 Builder correction and status boundary

The independent reviewer identified two direct Builder corrections: stale revision/blob synchronization (DF-F01) and duplicate top-level numbering in the foundation audit (DF-F02). Both findings are accepted. The audit has been updated to renumber its later chronological sections and record the finding-by-finding disposition. This inventory and the Builder self-review are being updated to this same exact parent snapshot.

The following remain unresolved and are not converted to passes by this update:
- PR #173 exact-revision acceptance provenance;
- PR #174's contradictory draft header and the open F-02/F-03 follow-on obligations;
- PR #191 stale-base disposition;
- full fragment-anchor, external-URL, and historical cross-branch link verification;
- historical preservation follow-up;
- DF-09 genuine fresh-reader test;
- DF-11 qualifying independent review against the final resulting revision;
- DF-12 exact-revision authority decision.

No fresh-reader result is fabricated. No acceptance decision is inferred. No PR was merged, rebased, retargeted, cherry-picked, or integrated. No source/runtime file was changed. Stage A remains held and implementation remains unauthorized.

The update commits for the audit, inventory and self-review are sequential. Their final branch HEAD and final blob SHAs must be fetched after the last write; the pre-update SHAs above are evidence for the exact inspected snapshot, not claims about the resulting commit.
