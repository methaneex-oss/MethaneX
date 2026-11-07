# JARVIS Planning Documentation Index — 2026-11-07

**Status:** Proposed navigation and document-governance index; awaiting independent review and Project Director acceptance.  
**Repository:** `methaneex-oss/MethaneX`  
**Purpose:** One entry point for understanding the current whole-Brain planning effort, locating its governing inputs, and distinguishing current work from historical evidence and deferred development planning.  
**Governing principle:** **ENGINEER THE MECHANISMS; LET BEHAVIOR BE ACQUIRED THROUGH EXPERIENCE.**

> **Start here.** Read this index first, then follow the reading order below. Do not infer authority from a filename, directory, PR state, document length, or the word “approved” appearing in an older handoff. Exact-scope acceptance, independent review, GitHub merge state, gate clearance, and implementation authorization are separate facts.

## 1. Current objective and immediate next work

The project must define and challenge the **entire future Brain** before choosing a development starting point or deciding which repository code to use.

The planning sequence is:

1. Define the whole-Brain capability and responsibility space.
2. Derive the mechanism architecture and explain its interactions, ownership, and boundaries.
3. Challenge completeness and reconcile existing architecture/specifications.
4. Obtain independent review and Project Director acceptance of the whole-Brain planning baseline.
5. Only then plan development order and candidate increments.
6. Only then assess repository source for reuse, adaptation, replacement, or new development against those increments.
7. Prepare implementation work packages and obtain explicit implementation authorization.

**Immediate planning task:** Stage A — whole-Brain capability and responsibility definition.

**Not current tasks:** implementation sequencing, source/donor selection, baseline selection, runtime changes, or implementation. The implementation roadmap is deferred pending completion and acceptance of whole-Brain planning.

## 2. Read in this order

| Order | Document | Why it is read here | Authority / status |
|---|---|---|---|
| 1 | [Whole-Brain Planning Scope and Builder Correction](reports/WHOLE_BRAIN_PLANNING_SCOPE_AND_BUILDER_CORRECTION_2026-11-07.md) | Governs the corrected objective, three reference lenses, planning stages, prior-work interpretation, Builder error record, and authorization boundary. | Proposed controlling correction; independent review and Project Director acceptance pending. |
| 2 | [Project Continuity and Recovery Handoff](plans/JARVIS_PROJECT_CONTINUITY_AND_RECOVERY_HANDOFF.md) | Conversation/restart handoff and operational continuity. Read its 2026-11-07 scope banner first; historical status sections are not automatically current. | Updated in separate PR #193; proposed, not accepted. |
| 3 | [Documentation and Artifact Inventory](inventory/00_JARVIS_DOCUMENTATION_AND_ARTIFACT_INVENTORY_2026-11-04.md) | Detailed preservation inventory, historical artifact descriptions, exact-revision qualifications, and recorded authority conflicts. | Working inventory; evidence, not blanket approval. |
| 4 | [Whole-System Architecture Foundation](00_JARVIS_SYSTEM_ARCHITECTURE_FOUNDATION.md) | Approved-within-scope whole-system principles and boundaries, subject to its exact-revision record. | Exact-scope prior approval is recorded in PR #171; verify exact revision and discussion before relying on it. |
| 5 | [Whole-System Anatomy and Responsibility Map](01_JARVIS_WHOLE_SYSTEM_ANATOMY_AND_RESPONSIBILITY_MAP.md) | Proposed system-domain responsibilities and boundaries around the Brain. | Exact-scope prior approval is recorded in PR #171; not a complete executable architecture. |
| 6 | [Brain Foundation Architecture](02_BRAIN_FOUNDATION_ARCHITECTURE.md) | Existing Brain-level architecture proposal and its recurrent/integrated cognition concepts. | Historically recorded as accepted planning input; verify exact revision and current review qualifications. |
| 7 | [Foundational Brain Capability Investigation](research/02_BRAIN_FOUNDATIONAL_CAPABILITY_INVESTIGATION_2026-11-03.md) | Prior capability research across human cognition, MCU J.A.R.V.I.S., and engineering reality. | Historically recorded as accepted planning input; bounded investigation, not whole-Brain completeness proof. |
| 8 | [Brain Mechanism Specification](specifications/00_BRAIN_MECHANISM_SPECIFICATION.md) | Existing BM-01–BM-12 mechanism decomposition, contracts, interactions, and scenarios. | **Authority qualification required:** historically treated as accepted at a specific HEAD, but the inventory records later unresolved F-02/F-03 review findings and conflicting status descriptions. Do not treat acceptance as settled without checking the exact reviewer record and Project Director decision. |
| 9 | [Phase 1 Whole-Repository Investigation and Reuse Audit](reports/PHASE_1_WHOLE_REPOSITORY_INVESTIGATION_AND_REUSE_AUDIT_2026-11-04.md) and [Phase 1 Review Corrections](reports/PHASE_1_REVIEW_CORRECTIONS_AND_SCOPE_RECONCILIATION_2026-11-05.md) | Existing repository/source investigation, baseline, preservation and reuse/conflict evidence. | Bounded repository investigation; not whole-Brain capability architecture and not a source-selection authorization. |
| 10 | [Phase 2 Whole-Brain Capability-to-Source Integration Map](reports/PHASE_2_WHOLE_BRAIN_CAPABILITY_TO_SOURCE_INTEGRATION_MAP_2026-11-05.md) | Existing BM-01–BM-12 source, ownership, dataflow, persistence/replay, and test mapping. | Useful partial mechanism-to-source investigation; not proof of whole-Brain completeness. |
| 11 | [Phase 2 Human and MCU Reference Comparison](reports/PHASE_2_HUMAN_AND_MCU_REFERENCE_COMPARISON_2026-11-06.md) | Comparison of the existing BM-01–BM-12 set against human-cognition and fictional MCU reference lenses. | Separate proposed artifact in PR #191; bounded comparison, not the whole-Brain capability inventory. |

The paths in this table are relative to `docs/architecture/`. The correction and continuity documents link to the same controlling sequence. The inventory remains the detailed catalog; this index is the short navigation and authority map.

## 3. Document classes

Use these classes consistently when adding or reviewing planning material:

- **Controlling planning document:** defines the current objective, scope, sequence, and decision rules. It does not silently override previously accepted architecture or governance decisions.
- **Architecture / specification:** states proposed or accepted responsibilities, contracts, boundaries, and mechanisms. Its exact revision and approval scope must be recorded.
- **Research / reference evidence:** informs decisions and records evidence, hypotheses, alternatives, and uncertainty. It is not architecture authority by itself.
- **Investigation / source map:** reports what exists in the repository at a pinned baseline. It is evidence for later development planning, not a decision to reuse code.
- **Inventory / continuity / governance:** records artifacts, provenance, status, ownership, review, decisions, and handoff.
- **Historical / legacy:** retained to preserve prior work and context. It must not be treated as the current plan where a newer accepted decision supersedes it.
- **Deferred proposal:** a proposed downstream plan that is not operative until its prerequisites are accepted.

A document can have more than one descriptive role, but it must have one clearly stated authority status and scope.

## 4. Existing work and how it fits

### Whole-system and Brain architecture

- PR #171 contains the whole-system foundation, responsibility map, and comparative research. Its exact-scope approvals must not be generalized to every file in the PR.
- PR #172 contains a bounded foundational capability investigation.
- PR #173 contains a Brain foundation architecture proposal.
- PR #174 contains the BM-01–BM-12 mechanism specification. Preserve it; do not assume the twelve mechanisms exhaust the future Brain. Its current acceptance status requires reconciliation against the later F-02/F-03 review evidence.

### Repository investigations

- Phase 1 is a pinned-baseline repository inventory/source investigation. Preserve its findings; do not restart repository archaeology without a demonstrated evidence gap.
- Phase 2 maps the existing twelve-mechanism specification to repository source and tests. It is useful integration evidence, not the first step in defining the whole Brain.
- The human/MCU comparison is likewise bounded to BM-01–BM-12. Its own PR is #191; it must have one authoritative path and must not be duplicated in another PR stack.

### Historical and deferred plans

- [JARVIS Brain Master Blueprint](../JARVIS_BRAIN_MASTER_BLUEPRINT.md): historical Layer 0–19 proposal, not an approved current development order.
- [Legacy Phase 2 Completion Note](../JARVIS_PHASE_2_COMPLETION.md): describes the bounded Perception & Representation work package, not the current whole-Brain Phase 2 investigation.
- [Brain Implementation Plan](plans/00_BRAIN_IMPLEMENTATION_PLAN.md): deferred proposal in PR #193's separate PR #175-derived stack; not the operative next task until whole-Brain planning is accepted.

## 5. Current documentation change set and dependency boundaries

Repository state checked on **2026-11-07**:

| PR | Purpose | State at check | Relationship |
|---|---|---|---|
| [#191](https://github.com/methaneex-oss/MethaneX/pull/191) | Adds the human/MCU comparison report. | Open, draft, unmerged. | Owns the comparison-report addition in its PR stack. |
| [#192](https://github.com/methaneex-oss/MethaneX/pull/192) | Corrects whole-Brain planning scope, preserves prior work, and adds this navigation index. | Open, draft, unmerged. | Based on the PR #179 integration-map branch. |
| [#193](https://github.com/methaneex-oss/MethaneX/pull/193) | Defers the implementation roadmap and corrects the continuity handoff. | Open, draft, unmerged. | Separate PR #175-derived stack; kept separate because it has a different base lineage. |

No reviewer was requested on these PRs at the time of the check. These are point-in-time observations, not durable status guarantees. Re-fetch the live PRs before acting.

**Duplicate-path rule:** the comparison report belongs in the PR #191 stack. PR #192 must not add a second copy of that same path. The PR #192 scope correction may link to PR #191 and describe its bounded scope, but must not create a competing version.

**Do not merge the PRs merely to make the tree look tidy.** First verify their base/head ancestry, changed-file sets, dependency order, and independent review findings. Do not retarget, rebase, merge, or close a PR without the required authorization.

## 6. Authority and status vocabulary

Never collapse these distinct states:

1. **Authored** — a document or code change exists.
2. **Submitted** — a PR or review request exists.
3. **Independently reviewed** — a reviewer other than the author has submitted a qualifying review.
4. **Project Director accepted** — the Project Director explicitly accepts a defined artifact/revision and scope.
5. **Merged** — GitHub has merged the PR; this is a repository state, not a substitute for the earlier decision record.
6. **Gate cleared / baseline selected** — the designated governance decision is explicitly recorded.
7. **Implementation authorized** — explicit authorization exists for the specified work.

A Builder self-review is not an independent review. An open or draft PR is not a merge. An accepted planning input is not implementation authorization. No gate or implementation status should be inferred from this documentation reorganization.

## 7. Rules for future documentation

1. Add new planning documents to this index and the detailed inventory in the same change.
2. Give each document a unique purpose; prefer updating an existing authoritative document over creating another overlapping report.
3. State status, scope, author, date, exact baseline/revision where applicable, and approval limits near the top.
4. Link prerequisites and downstream artifacts explicitly.
5. Mark historical, superseded, deferred, or contested material in the document itself and in this index.
6. Keep one authoritative repository path for each artifact. If a document must evolve across PR stacks, use a deliberate dependency and history-preserving change rather than parallel copies.
7. Preserve original findings and decisions; record corrections as traceable addenda or reviewed replacements.
8. Update this index when authority, dependencies, or current next work changes.
9. Do not use this index to create architecture decisions, approve a source baseline, or authorize implementation.

## 8. Immediate handoff

The next Builder should:

1. Read Sections 1–3 of the [Whole-Brain Planning Scope and Builder Correction](reports/WHOLE_BRAIN_PLANNING_SCOPE_AND_BUILDER_CORRECTION_2026-11-07.md).
2. Read the whole-system and Brain architecture inputs and research listed above, checking their exact revisions and authority.
3. Inspect existing capability research for gaps before repeating research.
4. Begin Stage A: construct and challenge the whole-Brain capability/responsibility definition.
5. Keep development order and repository source selection out of scope until Stages A–C are independently reviewed and accepted.

**No implementation, source selection, baseline selection, merge, rebase, gate clearance, or runtime change is authorized by this index.**
