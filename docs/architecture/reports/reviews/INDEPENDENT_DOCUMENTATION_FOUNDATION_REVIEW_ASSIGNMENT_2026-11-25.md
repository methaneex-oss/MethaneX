# Independent Documentation Foundation Review Assignment — 2026-11-25

**Status:** ACTIVE NEW ASSIGNMENT. This is not the withdrawn 2026-11-18 request and does not amend or revive it.
**Requesting role:** Project Builder
**Reviewing role:** Independent Reviewer / Blind Fresh Tester
**Repository:** `methaneex-oss/MethaneX`
**Frozen foundation target:** PR #192, `caf87986dfea7aca75728818651c8687e9f5faf0`
**Correction follow-up:** PR #201, branch `docs/pr192-consistency-corrections-20261125`; correction commit anchor before this assignment file: `ecd0295132c328f673ea47cf9a149eb0199b83ac`
**Review method:** Independent repository inspection. No prior chat context is required or authoritative.

## 1. Assignment and review order

Perform two explicitly separate assessments.

### Assessment A — blind fresh read of PR #192

Review the frozen Documentation Foundation at exactly `caf87986dfea7aca75728818651c8687e9f5faf0`. This SHA is immutable for this assignment. Do not substitute the PR branch's current head, PR #201, a later commit, or a historical review target.

Begin with a fresh-reader pass before reading prior Builder conclusions, review comments, or PR-body summaries. Use the repository's actual entry points and documents. Determine whether a competent new Project Builder can accurately reconstruct:

- what JARVIS is and is not;
- the controlling architecture and governance sources;
- which decisions are accepted, proposed, historical, superseded, waived, deferred, blocked, or still open;
- the exact current gate state and why;
- what is and is not authorized next;
- where the evidence for each material status claim lives.

Record confusing, contradictory, missing, misleading, or unsupported information with exact file paths and line/section references. Do not repair or silently reinterpret it during the assessment.

Then perform the technical/documentation evidence review of the same exact SHA.

### Assessment B — independent review of PR #201 corrections

Review the complete PR #201 diff against its base, which is the frozen PR #192 revision. The intended correction scope is four substantive documentation files:

1. `docs/architecture/00_JARVIS_PLANNING_DOCUMENTATION_INDEX_2026-11-07.md`
2. `docs/architecture/reports/DF02_76_PATH_SOURCE_VERSION_DISPERSION_2026-11-21.md`
3. `docs/architecture/reports/DF06_BUILDER_LINK_AND_NAVIGATION_AUDIT_2026-11-17.md`
4. `docs/architecture/inventory/00_JARVIS_DOCUMENTATION_AND_ARTIFACT_INVENTORY_2026-11-04.md`

This assignment file is an additional review-handoff artifact, not a fifth substantive gate correction. Confirm the live PR #201 head and base before review; record both full SHAs in your report. Do not assume the correction commit anchor is still the live PR head.

Check that each correction is accurate against the underlying evidence, that all cross-document status/evidence references agree, that no old current-status snapshot is presented as controlling, and that the correction did not silently alter the frozen PR #192 branch or expand scope. Independently inspect the full diff, not just the four intended file summaries.

## 2. Exact revision acquisition — mandatory

Before reaching a verdict:

1. Fetch live metadata for PR #192 and confirm its head is exactly `caf87986dfea7aca75728818651c8687e9f5faf0`. If not, stop and report target-integrity failure.
2. Fetch PR #192's complete changed-file list and recursive tree at that exact SHA. Record changed-path count and whether the tree is complete/untruncated.
3. Fetch the controlling documents and evidence artifacts from the exact SHA, not from mutable branch names.
4. Fetch live metadata for PR #201. Record its exact head SHA, base branch and base SHA, state, mergeability, and changed-file count.
5. Confirm PR #201's base is the frozen PR #192 line and independently compare the entire PR #201 diff.
6. If either target moves during review, stop the affected assessment and request a new exact-revision assignment. Never transfer a verdict to a successor SHA.

## 3. Review criteria

### A. Fresh-reader usability and consistency

- Can a new reader find the authoritative entry point and follow the reading order without chat memory?
- Is there one unambiguous controlling current-status snapshot?
- Do the index, inventory, focused reports, continuity checkpoint, governance source, PR descriptions and relevant comments agree on the same exact revisions and gate states?
- Are historical snapshots clearly labelled as historical rather than competing current truth?
- Are Builder claims, CI evidence, independent findings and Project Director decisions visibly distinguished?
- Are all links and references sufficiently precise to reproduce the underlying evidence?

### B. DF-01 through DF-12 gate adjudication

For every gate, state the controlling criterion, exact evidence, independent verification performed, findings, status, and authority owner. Do not infer one gate's completion from another.

| Gate | Required scrutiny |
|---|---|
| DF-01 | Canonical entry point, navigation route, reading order and current phase. |
| DF-02 | The 159 PR #97 donor paths, semantic successors/retirements/non-adoption dispositions, artifact authority, exact blob/revision provenance, cross-branch consumers/dependencies/duplicate ownership. Distinguish lexical discovery from semantic proof. |
| DF-03 | Exact decision provenance, authority owner, accepted scope, and separation of primary decisions from recovered summaries. |
| DF-04 | Accepted governance versus proposed governance; no authority inflation. |
| DF-05 | Branch bases, ancestry, divergence, dependency and integration claims; no unauthorized branch operation. |
| DF-06 | Exact-target Markdown parsing, local paths/fragments, external status/redirect/final destination and semantic relevance, and rendered GitHub heading/line/comment anchors where authenticated access permits. State access limitations honestly. |
| DF-07 | Cross-document status and revision consistency across index, inventory, reports, checkpoint, PR metadata and relevant comments. |
| DF-08 | Historical preservation, discoverability, provenance and clear historical/current labelling. |
| DF-09 | Exact-target blind fresh-reader evidence. A successful build/workflow or PARTIALLY CLEAR result is not a CLEAR reader verdict. |
| DF-10 | Exact parent/successor ancestry, one-commit/one-file inventory-only comparison, blob identity and complete-tree evidence. |
| DF-11 | Preserve the Project Director's historical waiver of DF-11 as a mandatory gate. Treat this assignment as a separate independent challenge; do not rewrite the waiver. |
| DF-12 | Project Director final acceptance only. Reviewer recommendation is not acceptance. |

### C. Exact evidence claims to challenge

- DF-02 workflow run #45470173876, artifact #14956148301, SHA-256 `9902957475c76f4840d1d280c7d4f50537941e9445810afb805132374a328f38`.
- DF-06 workflow run #45470173876, artifact #14956697074, SHA-256 `becc106d0bf538fd3f69fb291ebd4713bfc242d187c9c352f706a2f4ed7d8fbf`.
- DF-10 parent `a099ce6f6faa3756b26c8b8728f05ad15745cc7a` and successor `caf87986dfea7aca75728818651c8687e9f5faf0`.
- PR #201 correction commit anchor `ecd0295132c328f673ea47cf9a149eb0199b83ac`; independently establish the actual live PR #201 head and diff before reviewing it.

Verify the artifacts, hashes, run conclusions and stated limitations where accessible. Do not repeat counts or conclusions merely because they appear here. If an artifact cannot be retrieved, mark that verification unavailable.

## 4. Required findings format

For every finding include:

- Finding ID and severity: BLOCKER / HIGH / MEDIUM / LOW / NOTE.
- Exact target SHA, file path and line/section (or PR diff hunk).
- What is wrong, with a concise evidence-based explanation.
- Impact on reader comprehension, gate correctness, authority, reproducibility or project safety.
- Required correction and the evidence needed to close it.
- Whether it blocks CLEAR, blocks PR #201 acceptance, or is non-blocking.

Do not manufacture findings to fill a quota. Do not suppress a valid finding to reach a positive verdict.

## 5. Required report and verdict

Publish the report in `docs/architecture/reports/reviews/` and link it in the PR #192 and PR #201 conversations.

The report must contain:

- reviewer role and independence basis (use role labels, not vendor/model names as project roles);
- acquisition time/method and exact full SHAs for both assessments;
- PR #192 changed-path count and recursive-tree completeness;
- PR #201 base/head, changed-path count and complete diff scope;
- documents/artifacts inspected and unavailable items;
- reproducible checks performed;
- fresh-reader observations made before reading Builder conclusions;
- DF-01–DF-12 adjudication;
- numbered findings with evidence and required correction;
- direct overall verdict for Assessment A and separate verdict for Assessment B;
- explicit statement that each verdict applies only to its exact SHA.

Use exactly one of these verdicts for each assessment:

- **CLEAR** — no material blocker remains for the assessed scope.
- **PARTIALLY CLEAR** — useful progress is independently verified, but one or more material issues remain.
- **NOT CLEAR TO PROCEED** — material correctness, authority, integrity or comprehension failures remain.

A verdict of CLEAR on PR #192 does not automatically approve PR #201. A verdict on PR #201 does not constitute DF-12 acceptance.

## 6. Builder response and correction loop

After the report is published:

1. The Project Builder will classify each finding as accepted, disputed with evidence, or not applicable with evidence.
2. The Builder will fix all valid Builder-owned findings within the authorized documentation scope, without changing the frozen PR #192 branch or expanding into runtime/architecture redesign.
3. The Builder will rerun the relevant checks and publish exact commit, blob, workflow and test evidence.
4. The Independent Reviewer must re-check every corrected finding against the new exact SHA and publish a follow-up verdict. A Builder statement that a finding is fixed is not independent closure.
5. Unresolved, disputed, externally blocked or authority-owned findings must remain visible; do not hide them to obtain a pass.

## 7. Authority boundaries

This assignment authorizes review and report publication only. It does not authorize:

- merging, closing, rebasing, retargeting, cherry-picking, rewriting or deleting branches;
- changing the frozen PR #192 branch;
- runtime source, tests, training, deployment or architecture implementation;
- source-baseline selection, donor adoption or integration;
- Stage A activation;
- DF-12 acceptance.

The Builder may correct valid documentation findings on the existing PR #201 follow-up branch. The reviewer may publish findings and verdicts but may not accept the work for the Project Director. The Project Director retains final acceptance and merge decisions.

**Stage A remains NOT STARTED / HELD until the required evidence and Project Director decision are recorded.**

---

## Copy/paste reviewer prompt

You are acting as the Independent Reviewer and Blind Fresh Tester for `methaneex-oss/MethaneX`. Execute this assignment from the repository itself; do not rely on private chat history or accept the Builder's claims without reproducing them.

First, perform a blind fresh-reader assessment of PR #192 at exactly `caf87986dfea7aca75728818651c8687e9f5faf0`. Verify the live PR head matches before starting. Begin at the repository entry points, reconstruct the project and gate state, and record comprehension failures before reading prior Builder conclusions. Then independently inspect the documentation evidence and adjudicate DF-01 through DF-12.

Second, independently inspect the complete PR #201 correction diff against its frozen PR #192 base. Verify the canonical index, DF-02 report, DF-06 report and inventory corrections against the underlying source artifacts. Record the actual live PR #201 base/head SHAs and all changed paths.

Publish a detailed report under `docs/architecture/reports/reviews/`, link it on both PRs, provide separate CLEAR / PARTIALLY CLEAR / NOT CLEAR TO PROCEED verdicts for the two exact targets, and list every finding with severity, path/line evidence, impact and required correction. If access or tooling prevents a required check, report it as unavailable or blocked; never simulate a result. Do not edit source branches, merge anything, start Stage A, or make the Project Director's DF-12 decision. The Builder will address valid Builder-owned findings and request your independent re-check.
