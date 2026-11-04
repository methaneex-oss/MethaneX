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
**Project status:** accepted by the Project Director as a Brain architecture planning baseline, according to the recorded project handoff.

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
