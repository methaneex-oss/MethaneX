# Project Director Decision Evidence Extracts — 2026-11-10

**Evidence class:** Repository-fetched GitHub issue-comment records and exact-revision metadata. This document transcribes the relevant primary repository records for reader accessibility; it is not itself a new Project Director decision.
**Repository:** `methaneex-oss/MethaneX`
**Purpose:** Put the exact PR #173 and #174 planning-baseline decisions, their provenance quality, scope, and current branch relationship in one place.

## PR #173 — Brain Foundation Architecture

- **Accepted baseline:** `97191111bc2573c14d391c0af9628db7b11f194b`
- **Decision record:** [PR #173 issue comment #6752144835](https://github.com/methaneex-oss/MethaneX/pull/173#issuecomment-6752144835)
- **Comment author/account:** `methaneex-oss`
- **Comment created:** 2026-11-09 21:38:46 UTC
- **Decision date asserted by the record:** 2026-11-03 08:18:21 UTC
- **Provenance qualification:** The comment explicitly says it is a repository-side transcription of an earlier Project Director decision in prior ChatGPT conversation history. The original contemporaneous decision artifact is not present in this repository record. Therefore the comment is direct evidence that the repository owner recorded the decision and its asserted historical basis; it is not the original contemporaneous decision artifact.

The comment records that PR #173 was accepted as the Brain Foundation Architecture planning baseline at the exact HEAD above, following an independent reviewer recommendation. The recorded authorized scope was to proceed to the Detailed Brain Mechanism Specification stage. It explicitly did not authorize runtime implementation, runtime tests, technology or algorithm selection, merge, deployment, or later stages requiring separate authorization.

## PR #174 — Brain Mechanism Specification

- **Accepted baseline:** `0811a59e46bf934e32e794f90e4e7d18d4e2bd97`
- **Decision record:** [PR #174 issue comment #6604790481](https://github.com/methaneex-oss/MethaneX/pull/174#issuecomment-6604790481)
- **Comment author/account:** `methaneex-oss`
- **Comment created:** 2026-11-03 13:14:28 UTC

The fetched decision comment states: “The Project Director formally accepts PR #174 as the approved Brain Mechanism Specification planning baseline,” following the Independent Reviewer's approval of exact HEAD `0811a59e46bf934e32e794f90e4e7d18d4e2bd97`.

Its recorded acceptance scope:
- The Detailed Brain Mechanism Specification is accepted as the governing planning baseline for subsequent authorized work.
- Independent Review finding F-01 is cleared.
- The BM-07 / SYS-05 / SYS-08 clarification is a non-blocking documentation refinement and must be carried forward explicitly before implementation relies on that boundary.
- No implementation, runtime tests, technology selection, merge, deployment, or later stage is authorized.
- PR #174 remains open, draft and unmerged; no merge was requested.
- Any next stage requires separate explicit Project Director authorization.

### Accepted baseline versus current PR head

- Accepted baseline: `0811a59e46bf934e32e794f90e4e7d18d4e2bd97`.
- Current PR #174 HEAD fetched 2026-11-10: `be46b3858102c31022128522c4b3506aad4dff8a`.
- The current HEAD contains a one-line documentation/header correction that identifies the parent PR #173 revision as an accepted planning baseline and points to its provenance transcription. It does not replace the accepted PR #174 baseline or expand its authorization.
- The accepted baseline's historical header still says “Draft for independent review.” That stale header is an artifact of the accepted historical revision. The current PR #174 HEAD corrects the header; readers should use the accepted baseline for accepted technical content and the current HEAD for the status clarification. The current PR #174 HEAD is not itself a newly accepted replacement baseline.

### Follow-on findings

F-02 and F-03 are recorded as open follow-on obligations in the current documentation foundation records. The original full follow-on review and inline annotations have not been recovered; the checked-in recovery record is explicitly partial secondary evidence. Do not present the recovered summary as the original review, do not close F-02/F-03, and do not infer implementation authorization.

## Interpretation rules

1. A Project Director decision is distinct from an independent review recommendation.
2. Acceptance applies only to the exact revision and scope stated in the decision record.
3. A later documentation-only header correction does not silently change the accepted technical baseline.
4. PR open/draft/unmerged state is a GitHub lifecycle fact, not a contradiction of an exact-scope acceptance decision.
5. Neither accepted planning baseline authorizes implementation or overrides the current whole-Brain planning hold and documentation-foundation gate.
