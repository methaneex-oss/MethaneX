# JARVIS Documentation Portal

**Status:** Proposed documentation-navigation layer in PR #192; not yet independently reviewed or accepted.  
**Repository:** methaneex-oss/MethaneX  
**Snapshot:** 2026-11-07  
**Current task:** Initial Documentation Foundation Completion Gate  
**Stage A:** Not started; held pending completion, independent review and exact-revision acceptance of the documentation foundation.

This page is the human-facing entry point to the JARVIS documentation system. It is designed for people arriving with different responsibilities. It does not replace the planning index, architecture decisions, governance records, technical specifications, test evidence, or pull-request review history.

> **Navigation rule:** Start with this portal, follow the route for your role, then use the Planning Documentation Index as the canonical catalog of planning artifacts and their status. Never infer authority from a filename, folder, PR title, draft/merged state, or an old handoff.

## 1. Start here by role

### New reader, stakeholder or occasional contributor

1. Read the [repository README](../README.md) for the project objective and high-level engineering principles.
2. Read the [Whole-Brain Planning Scope and Builder Correction](architecture/reports/WHOLE_BRAIN_PLANNING_SCOPE_AND_BUILDER_CORRECTION_2026-11-07.md) to understand what the project is and is not trying to build.
3. Read the [Planning Documentation Index](architecture/00_JARVIS_PLANNING_DOCUMENTATION_INDEX_2026-11-07.md) for the reading order, document classifications, authority status and PR dependencies.
4. Use the [Documentation and Artifact Inventory](architecture/inventory/00_JARVIS_DOCUMENTATION_AND_ARTIFACT_INVENTORY_2026-11-04.md) when you need to locate historical work or understand why an artifact is retained.
5. Use the [Documentation Templates Guide](templates/README.md) when creating a planning document, independent review report or test-evidence report.

You do not need to read every historical report to understand the current task. Follow the relevant role route below.

### Builder / implementation engineer

**Current boundary:** The active work is documentation-foundation correction. Do not begin Stage A, select source baselines or donors, change runtime code, or treat the deferred implementation plan as operative.

Read in this order:

1. [Planning Documentation Index](architecture/00_JARVIS_PLANNING_DOCUMENTATION_INDEX_2026-11-07.md).
2. [Initial Documentation Foundation Audit](architecture/reports/INITIAL_DOCUMENTATION_FOUNDATION_AUDIT_AND_COMPLETION_GATE_2026-11-07.md).
3. [Whole-Brain Planning Scope and Builder Correction](architecture/reports/WHOLE_BRAIN_PLANNING_SCOPE_AND_BUILDER_CORRECTION_2026-11-07.md).
4. [Project Continuity and Recovery Handoff — PR #193](https://github.com/methaneex-oss/MethaneX/pull/193).
5. [Whole-System Architecture Foundation](https://github.com/methaneex-oss/MethaneX/blob/b05434758ad4fe72815503f89bd5d2990ccb658b/docs/architecture/00_JARVIS_SYSTEM_ARCHITECTURE_FOUNDATION.md) and [Whole-System Anatomy and Responsibility Map](https://github.com/methaneex-oss/MethaneX/blob/b05434758ad4fe72815503f89bd5d2990ccb658b/docs/architecture/01_JARVIS_WHOLE_SYSTEM_ANATOMY_AND_RESPONSIBILITY_MAP.md).
6. [Foundational Brain Capability Investigation](https://github.com/methaneex-oss/MethaneX/blob/d7d676b79dbf3269f7fd3ebdb4363a6df19f255d/docs/architecture/research/02_BRAIN_FOUNDATIONAL_CAPABILITY_INVESTIGATION_2026-11-03.md), [Brain Foundation Architecture](https://github.com/methaneex-oss/MethaneX/blob/97191111bc2573c14d391c0af9628db7b11f194b/docs/architecture/02_BRAIN_FOUNDATION_ARCHITECTURE.md), and [Brain Mechanism Specification](https://github.com/methaneex-oss/MethaneX/blob/0811a59e46bf934e32e794f90e4e7d18d4e2bd97/docs/architecture/specifications/00_BRAIN_MECHANISM_SPECIFICATION.md) with their qualifications in the index.
7. Read the Phase 1 and Phase 2 reports only when the task requires repository/source evidence. They are bounded investigations, not authority to select code or begin implementation.

Before changing anything, establish the exact branch, base, HEAD, target files, authority status and current task. Preserve prior decisions and history. Update the index and inventory when the documentation system itself changes.

### Independent reviewer

The reviewer's job is to challenge claims and verify evidence, not merely confirm that documents exist.

1. Read the [Foundation Audit and DF-01–DF-13 criteria](architecture/reports/INITIAL_DOCUMENTATION_FOUNDATION_AUDIT_AND_COMPLETION_GATE_2026-11-07.md).
2. Read the [Planning Documentation Index](architecture/00_JARVIS_PLANNING_DOCUMENTATION_INDEX_2026-11-07.md) and [scope correction](architecture/reports/WHOLE_BRAIN_PLANNING_SCOPE_AND_BUILDER_CORRECTION_2026-11-07.md).
3. Inspect the exact PR head and base, changed-file list, commit history and immutable file revisions. Do not review a different revision from the one submitted for acceptance.
4. Verify authority records separately from discussion comments, Builder summaries and PR descriptions.
5. Reproduce important links, blob SHAs, source claims and status claims. Record what was checked and what could not be checked.
6. Submit a formal review through the repository's review process. A report stored in the repository or a comment is not automatically a formal GitHub review.
7. State findings, severity, evidence, required correction and whether the reviewed revision is cleared. Do not make the Project Director's decision or claim implementation authorization.

Relevant provenance material: [PR #174 follow-on review provenance recovery](architecture/reports/PR_174_FOLLOW_ON_REVIEW_PROVENANCE_RECOVERY_2026-11-06.md). It is explicitly a partial recovery record, not the original review.

### Tester / verification engineer

**Current boundary:** This documentation phase does not authorize runtime implementation or execution of a new test campaign. The route below is for understanding existing verification evidence and preparing correctly scoped future work after authorization.

1. Read the accepted-revision and status qualifications for the [Brain Mechanism Specification](https://github.com/methaneex-oss/MethaneX/blob/0811a59e46bf934e32e794f90e4e7d18d4e2bd97/docs/architecture/specifications/00_BRAIN_MECHANISM_SPECIFICATION.md).
2. Read the [Phase 2 Whole-Brain Capability-to-Source Integration Map](architecture/reports/PHASE_2_WHOLE_BRAIN_CAPABILITY_TO_SOURCE_INTEGRATION_MAP_2026-11-05.md) to see the bounded BM-01–BM-12 source and test mapping.
3. Read the [Phase 2 Donor Runtime Reliability Acceptance Contract](architecture/reports/PHASE_2_DONOR_RUNTIME_RELIABILITY_ACCEPTANCE_CONTRACT_2026-11-06.md) for its stated reliability evidence boundaries.
4. Read the relevant source-level test, CMake registration and workflow evidence at the exact revision under examination.
5. Distinguish test definitions, registered test targets, executed test runs, passing results, and accepted capability. They are not interchangeable.

A test report must identify the exact commit, environment, command, test selection, result, logs/artifacts, failures and limitations. Do not claim that an integrated learning capability works merely because source files exist, targets are registered, or a historical test run passed.

### Researcher / architect

1. Start with the [scope correction](architecture/reports/WHOLE_BRAIN_PLANNING_SCOPE_AND_BUILDER_CORRECTION_2026-11-07.md).
2. Review the approved-within-scope whole-system foundations and the accepted bounded capability investigation linked in the index.
3. Treat human cognition, the fictional MCU J.A.R.V.I.S. and the developing-brain analogy as distinct reference lenses with different evidentiary limits.
4. Treat BM-01–BM-12 as existing work, not proof of exhaustive future-Brain coverage.
5. Separate empirical evidence, interpretation, hypothesis, engineering constraint and decision. Record uncertainty and competing explanations.

### Documentation maintainer

1. Check whether the information belongs in an existing canonical document before creating a new one.
2. Give each artifact one purpose, one canonical repository path and a clear status.
3. Update the index and inventory in the same reviewed change as any new or materially changed planning artifact.
4. Add exact revision links for cross-branch references and live PR links for review state.
5. Preserve historical artifacts; use explicit supersession or correction records rather than silent deletion or duplicate competing copies.
6. Run the documentation link and consistency checks described below.

## 2. Reusable contribution templates

Use the [Documentation Templates Guide](templates/README.md) for consistent planning-document, independent-review and test-evidence report structures. Templates are aids, not approval or governance authority.

## 3. Canonical navigation map

| Need | Canonical starting point | What it controls |
|---|---|---|
| Understand project objective | [Repository README](../README.md) | High-level identity and engineering principles |
| Find the right document | [Planning Documentation Index](architecture/00_JARVIS_PLANNING_DOCUMENTATION_INDEX_2026-11-07.md) | Reading order, artifact classification, authority and dependency map |
| Understand current phase and boundaries | [Scope correction](architecture/reports/WHOLE_BRAIN_PLANNING_SCOPE_AND_BUILDER_CORRECTION_2026-11-07.md) | Whole-Brain scope and current planning sequence |
| Recover project context | [Continuity handoff — PR #193](https://github.com/methaneex-oss/MethaneX/pull/193) | Historical context and operational restart instructions |
| Locate historical documents | [Artifact inventory](architecture/inventory/00_JARVIS_DOCUMENTATION_AND_ARTIFACT_INVENTORY_2026-11-04.md) | Provenance, preservation and artifact location |\n| Compare historical revisions | [Preservation comparison report](architecture/reports/DOCUMENTATION_FOUNDATION_PRESERVATION_AND_LINK_VALIDATION_2026-11-08.md) | Branch-tip grouping and exact duplicate/divergent Markdown blob comparisons |\n| Locate PR-lineage artifacts | [Historical preservation register](architecture/inventory/HISTORICAL_DOCUMENTATION_PRESERVATION_REGISTER_2026-11-08.md) | Exact paths and blob SHAs across the principal planning PRs |
| Verify current gate | [Foundation audit](architecture/reports/INITIAL_DOCUMENTATION_FOUNDATION_AUDIT_AND_COMPLETION_GATE_2026-11-07.md) | DF-01–DF-13 evidence and blockers |
| Understand authority proposals | [Governance rules — PR #178](https://github.com/methaneex-oss/MethaneX/pull/178) | Proposed rules only; unaccepted at this snapshot |
| Inspect source integration | [Phase 1 report](architecture/reports/PHASE_1_WHOLE_REPOSITORY_INVESTIGATION_AND_REUSE_AUDIT_2026-11-04.md) and [Phase 2 map](architecture/reports/PHASE_2_WHOLE_BRAIN_CAPABILITY_TO_SOURCE_INTEGRATION_MAP_2026-11-05.md) | Bounded repository and source evidence |

## 4. Repository documentation map

The following describes the observed documentation areas. A directory's existence does not imply that every document in it is current or authoritative.

- **docs/** — human-facing documentation portal and legacy top-level material.
- **docs/architecture/** — architecture, planning index and architecture-level decisions.
- **docs/architecture/research/** — research, comparative evidence and capability investigations.
- **docs/architecture/specifications/** — mechanism specifications and contracts.
- **docs/architecture/reports/** — audits, integration maps, review corrections, evidence reports and completion-gate records.
- **docs/architecture/inventory/** — artifact and source inventories.
- **docs/architecture/plans/** — planning proposals and continuity handoffs; check status before execution.
- **docs/architecture/plans/reviews/** — detailed review, reconciliation and gate evidence associated with planning work.
- **docs/templates/** — reusable starting structures for planning documents, independent reviews and test-evidence reports; templates are aids, not approval authority.
- **docs/governance/** — governance proposals and decision-control material; verify acceptance status before treating any rule as binding.
- **core/**, **runtime/**, **interfaces/** and **tests/** — implementation and verification areas. Use the source maps and build/test registration evidence to locate the relevant code; do not infer coverage from directory names.

## 5. Status and authority vocabulary

Use these terms precisely:

- **Draft / proposed:** authored but not accepted.
- **Submitted:** placed into a PR or review process.
- **Independently reviewed:** a qualifying review by someone other than the author is recorded.
- **Accepted within exact scope:** an attributable decision accepts a specific artifact revision for a defined purpose.
- **Merged:** GitHub records that the PR was merged. Merge state alone does not prove that every claim or decision in the PR was accepted.
- **Historical:** retained as evidence of earlier work or decisions; not automatically current.
- **Superseded:** replaced for a stated purpose by an identified later artifact or decision. Preserve the predecessor and explain the boundary.
- **Deferred / non-operative:** retained for context but not authorized for execution.
- **Contested / unresolved:** evidence is incomplete or conflicting; state what is missing.
- **Gate cleared:** the required gate decision is explicitly recorded by the authorized decision-maker.
- **Implementation authorized:** explicit authorization exists for the specified implementation scope.

Never collapse authored, submitted, reviewed, accepted, merged, gate-cleared and implementation-authorized into one status.

## 6. Evidence and linking conventions

Every material technical or governance claim should be traceable to evidence.

For a document, record its canonical path, exact commit/blob revision when relevant, author or responsible role, date, purpose, status, scope and known limitations.

For repository claims, identify the repository, branch/ref, commit SHA, path, and the command or retrieval method used. For review/acceptance claims, link the exact review or decision record and state the accepted scope. For test claims, identify the commit, environment, command, selected tests, result and artifacts.

Use:
- relative links for files guaranteed to exist in the same branch;
- immutable commit-pinned links for files on another branch or historical revision;
- PR links for live discussion, review state and current branch metadata.

Do not use a mutable branch link as proof of what was reviewed. Do not use a PR description as a substitute for an explicit decision record.

## 7. Documentation contribution workflow

For every proposed documentation change:

1. **Locate:** search the index and inventory for an existing artifact with the same purpose.
2. **Classify:** identify whether the change is architecture, specification, research, source investigation, test evidence, governance, inventory, continuity or historical preservation.
3. **Scope:** state what the document does and does not decide.
4. **Trace:** link prerequisites, dependent artifacts and exact evidence revisions.
5. **Edit:** update the canonical artifact; avoid parallel copies.
6. **Synchronize:** update the index and inventory when status, location, authority, dependencies or meaning changes.
7. **Validate:** check links, headings, paths, revision pins, terminology and consistency with current phase/authority.
8. **Self-review:** record the exact files and revisions checked, defects found, checks not performed and unresolved risks.
9. **Independent review:** request review from a reviewer other than the author and submit it through the formal review mechanism.
10. **Decision:** obtain the required exact-revision authority decision. Do not self-approve or treat silence as acceptance.

A correction must preserve the original decision and explain whether it clarifies, narrows, supersedes or reopens it. Never silently rewrite history.

## 8. Minimum document header

New substantive planning artifacts should begin with a compact metadata block containing:

- Title
- Status (draft/proposed/accepted-within-scope/historical/deferred/contested)
- Author or responsible role
- Created and last-updated dates
- Canonical repository path
- Exact baseline/commit, if the content depends on a repository snapshot
- Purpose
- Scope and explicit non-goals
- Prerequisites and dependent artifacts
- Review status and exact decision reference, if any
- Known limitations

Do not write “approved” without naming the exact revision, scope and decision record.

## 9. Current branch and authority boundary

This portal is being introduced on PR #192's PR #179-derived line. The continuity handoff and deferred implementation plan are on PR #193's separate PR #175-derived line. They are not silently combined by this portal.

At the pre-correction repository refresh on 2026-11-07:
- PR #192 parent HEAD: `f831faef6d031776e0cee116d1986c3160faffb5` (this portal correction advances that branch).
- PR #193 live HEAD: `976aa33f89cc02225296f59246f47982300f5b39`.
- PR #192 and PR #193 are open, draft and unmerged at this refresh. Re-fetch live PR metadata before relying on snapshot values.
- PR #191 is a separate comparison proposal based on an earlier PR #179 snapshot.
- PR #178 governance remains proposed and unaccepted.
- PR #173 acceptance provenance remains unresolved in the available PR discussion.
- PR #174's exact-revision acceptance is recorded, but its draft header and follow-on review obligations remain to be reconciled.

The current task is to complete the Initial Documentation Foundation Completion Gate. Stage A remains held. This portal does not accept any proposal, clear any gate, select a source baseline, authorize implementation, or replace the required independent review and authority decision.

## 10. How to improve this portal

If a reader cannot determine where to start, which revision is relevant, what is authoritative, or what action is currently allowed, improve this portal and the canonical index rather than adding another unlinked overview document.

**End of documentation portal.**


## Supplemental historical preservation register

For exact artifact paths and blob identities across the principal JARVIS planning PR lineages, use the [Historical Documentation Preservation Register](architecture/inventory/HISTORICAL_DOCUMENTATION_PRESERVATION_REGISTER_2026-11-08.md). It complements the [Historical Preservation and Cross-Revision Comparison Report](architecture/reports/DOCUMENTATION_FOUNDATION_PRESERVATION_AND_LINK_VALIDATION_2026-11-08.md): the latter covers earlier branch discovery and selected cross-revision comparisons; the register maps the later PR #171–#193 documentation artifacts. Neither document converts a proposal into an accepted decision or authorizes branch integration.
