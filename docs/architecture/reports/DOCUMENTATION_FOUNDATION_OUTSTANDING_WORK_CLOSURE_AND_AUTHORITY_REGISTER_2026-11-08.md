# Documentation Foundation — Outstanding Work Closure and Authority Boundary Report

**Date:** 2026-11-08  
**Repository:** `methaneex-oss/MethaneX`  
**Working PR:** #192  
**Verified PR #192 HEAD at preparation:** `87d40bdda562807d0a13073388d2c6fc5fe402e3`  
**Status:** Builder remediation register; NOT a gate-clearance decision.

## 1. Purpose

This report separates (a) work already completed in repository revisions, (b) technical work that remains within Builder authority, and (c) requirements that cannot truthfully be completed by the Builder. It prevents completed corrections from being repeated and prevents missing human evidence or authority decisions from being represented as completed.

This report does not accept any PR, clear the documentation-foundation gate, authorize Stage A, authorize implementation, or change historical decisions.

## 2. Verified corrections already recorded

The following are already documented in the current PR #192 audit/history and must not be described as outstanding Builder edits:

1. **PR #174 status-header discrepancy:** the specification now identifies the exact accepted planning-baseline revision `0811a59e46bf934e32e794f90e4e7d18d4e2bd97`, preserves the Project Director's acceptance comment `6604790481`, and states that the newer administrative clarification is not a new substantive acceptance or implementation authorization. The PR description was corrected to stop asserting unverified PR #173 acceptance.
2. **PR #174 follow-on F-02/F-03 provenance:** the recovery record now contains a bounded recovered summary. The original full review and inline annotations remain unavailable; both findings remain OPEN and are not treated as cleared.
3. **PR #191 graph:** the exact relationship is documented as DIVERGED: PR #191 has one unique commit and is 22 commits behind PR #179 HEAD. Retargeting alone is not a solution. No rebase, cherry-pick or retarget has been performed.
4. **Historical preservation:** the Historical Documentation Preservation Register records 68 paths across principal PR lineages, each mapped to a source revision and blob. The selected PR #96/#97/#148/#156/#170 comparisons are also recorded.
5. **Developmental Brain Plan revision comparison:** at commit `87d40bdda562807d0a13073388d2c6fc5fe402e3`, the preservation report records that the 352-line PR #148 revision is an exact prefix of the 399-line PR #156 revision, with a 47-line append-only §15. Neither revision is thereby accepted or made canonical.
6. **Fresh-reader protocol:** the protocol is normalized to 17 questions. This corrects the document; it does not constitute execution of the test.

## 3. Current outstanding register

| Item | Current evidence-based disposition | What closes it | Authority |
|---|---|---|---|
| PR #173 acceptance provenance | No attributable Project Director acceptance decision for exact HEAD `97191111bc2573c14d391c0af9628db7b11f194b` was recovered from its complete discussion query. Keep it UNVERIFIED / PROPOSED. | Recover a primary decision record, or the Project Director explicitly decides that the architecture remains unaccepted/unverified. | Project Director |
| PR #174 F-02 | Recovered finding: contextual language/operator-intent grounding; OPEN. Original full report unavailable. | Correct the affected specification requirements in a traceable follow-up, then obtain independent review and an exact-scope decision. | Builder may draft; independent reviewer and Project Director decide clearance |
| PR #174 F-03 | Recovered finding: enforceable downstream reasoning integration; OPEN. Original full report unavailable. | Correct the affected specification requirements in a traceable follow-up, then obtain independent review and an exact-scope decision. | Builder may draft; independent reviewer and Project Director decide clearance |
| PR #191 integration disposition | PR #191 is a one-commit historical-base proposal diverged from current PR #179 by 22 commits. | Project Director chooses historical-base review only, or authorizes a new dependent revision replaying the unique document commit onto current PR #179. Retargeting alone is insufficient. | Project Director |
| PR #192 / PR #193 lineage order | Separate PR #179-derived and PR #175-derived lineages. | Explicitly decide intended review/integration order; do not silently stack, rebase, merge or retarget. | Project Director |
| DF-06 link validation | Earlier check covered 63 relative links on a prior exact parent revision, with 0 missing paths; 143 external URL occurrences were not exhaustively checked. Fragment and cross-branch validation was incomplete. | Re-run against the exact final PR #192 HEAD: relative paths, heading fragments, commit-pinned/cross-branch links, external URL reachability and semantic relevance. Report exclusions and failures. | Builder |
| DF-08 historical preservation | Materially advanced, not complete. The 68-path register covers named principal PRs; broader non-JARVIS-named lineage, unmatched branch provenance and archive/supersession decisions remain open. | Complete bounded discovery with explicit search limits; classify unmatched refs; compare remaining material historical revisions; propose dispositions without moving/deleting anything. | Builder researches; Project Director authorizes destructive or canonical changes |
| DF-09 fresh-reader test | NOT MET. Protocol exists; no uninvolved reader session exists. | A person uninvolved in authoring and not coached completes the exact 17-question protocol. Preserve unedited answers, time, assistance, navigation failures and observations. | Independent human participant; Builder records results |
| DF-10 Builder self-review | Must be tied to the final immutable PR #192 snapshot after all Builder changes. | Final self-review names exact HEAD, changed-file set, blobs, checks performed, exclusions and unresolved findings. | Builder |
| DF-11 qualifying independent review | NOT MET. Existing reviewer and Builder share GPT-6 identity; existing report is useful but not qualifying. | A genuinely separate reviewer identity conducts and submits a formal review against the exact final revision. A repository report alone is not a formal GitHub review. | Independent reviewer |
| DF-12 Project Director decision | NOT MET. | Project Director records accept / reject / conditional acceptance against exact reviewed PR #192 and related revisions, with scope and conditions. | Project Director |
| DF-13 Stage A hold | PASS for the hold only. | Keep Stage A held until all required evidence and the Project Director's decision are complete. | Project Director |

## 4. Builder execution order

The remaining Builder-controlled work should be completed in this order:

1. Re-fetch live metadata and exact changed paths for PRs #192 and #193 immediately before each report update.
2. Run complete PR #192 current-HEAD link validation, separating relative path, fragment, external reachability, cross-branch and semantic checks.
3. Finish the bounded historical branch/PR lineage search and document search limits, unmatched refs and remaining revision relationships.
4. Reconcile the index, portal, inventory and gate audit against one immutable PR #192 snapshot.
5. Produce the final Builder self-review against that exact snapshot.
6. Hand the immutable snapshot to a qualifying separate reviewer.
7. Run the uninvolved fresh-reader protocol.
8. Submit the evidence package to the Project Director for the exact-revision decision.

Do not perform PR #191 rebase/cherry-pick/retarget, PR #192/#193 integration, branch deletion, archive relocation, merge, or implementation without a separate explicit Project Director decision.

## 5. Gate decision

**The documentation-foundation gate remains NOT CLEARED. Stage A remains HELD.**

The Builder can close technical validation, historical discovery, synchronization and self-review. The Builder cannot supply the uninvolved reader, substitute its own GPT-6 identity for an independent reviewer, or make the Project Director's acceptance decision. These are not paperwork gaps to be simulated; they are distinct evidence and authority requirements.

No runtime source, tests, build configuration, dependency, workflow or runtime state is changed by this report.
