# Project Director Decision Provenance and Documentation-Gate Reconciliation — 2026-11-09

**Repository:** `methaneex-oss/MethaneX`  
**Prepared against:** PR #192 HEAD `c166e7d955293f1108f71b123d0a92f5941bdabd`  
**Purpose:** Reconcile newly recovered prior Project Director decision evidence with live PR metadata, reviewer submissions, branch ancestry and remaining documentation-foundation blockers.  
**Authority boundary:** This report records existing decisions and repository evidence. It does not create new architecture approval, accept missing review provenance, choose PR integration order, clear a gate, start Stage A, or authorize implementation.

---

## 1. PR #173 — prior Project Director acceptance recovered

The exact Project Director decision was recovered from prior ChatGPT conversation history:

- **Decision timestamp:** 2026-11-03 08:18:21 UTC.
- **Accepted artifact:** PR #173 Brain Foundation Architecture.
- **Exact accepted HEAD:** `97191111bc2573c14d391c0af9628db7b11f194b`.
- **Decision:** accepted as the **Brain Foundation Architecture planning baseline**.
- **Authorized next stage:** Detailed Brain Mechanism Specification.
- **Not authorized:** runtime implementation, runtime tests, technology or algorithm selection, merge, deployment, or any later stage requiring separate authorization.

The user response was recorded as “Yes I do / Proceed” to the explicit acceptance question. The recovered history distinguishes this direct Project Director decision from the Independent Reviewer's earlier approval/recommendation.

PR #173's own discussion had contained only Builder-authored handoff/resubmission comments. Therefore the previous repository audit was correct about the absence of an acceptance comment *inside PR #173*, but its broader classification of the architecture as unaccepted/unverified was incomplete because it had not recovered the prior conversation decision.

A repository-side transcription of the historical decision was added to PR #173 as comment [#6752144835](https://github.com/methaneex-oss/MethaneX/pull/173#issuecomment-6752144835). This records the existing decision; it does not create a new decision or change PR #173's open/draft/unmerged state.

**Disposition:** The PR #173 acceptance question is resolved. The accepted planning baseline remains exact HEAD `97191111bc2573c14d391c0af9628db7b11f194b`. Later references should cite the recovered decision and repository comment rather than continue calling the architecture unaccepted.

## 2. PR #174 — accepted baseline versus later follow-on findings

Live PR metadata at this reconciliation:

- PR #174 remains open, draft and unmerged.
- Parent/base: PR #173 exact HEAD `97191111bc2573c14d391c0af9628db7b11f194b`.
- Exact planning-baseline revision accepted by Project Director: `0811a59e46bf934e32e794f90e4e7d18d4e2bd97`, by PR #174 comment [#6604790481](https://github.com/methaneex-oss/MethaneX/pull/174#issuecomment-6604790481).
- Current PR #174 HEAD: `922912283d173e24df891ba23d0e2dfc17e0f4b4`.
- Current HEAD is three commits ahead of the accepted revision. The bounded compare reports one modified file with five additions and five deletions: a status/authority clarification in the specification, not a substantive mechanism redesign.

The later independent follow-on review remains distinct from the accepted baseline:

- **Follow-on F-02:** contextual language and operator-intent grounding. Recovered severity: HIGH / CONFIRMED.
- **Follow-on F-03:** enforceable downstream reasoning integration. Recovered severity: MEDIUM / CONFIRMED as a specification weakness.

The original full reviewer report and inline annotations remain unavailable. The checked-in provenance-recovery document explicitly states that the exact full wording, rationale and line-by-line annotations were not recovered. A prior shared-chat URL was not retrievable during this reconciliation. The available recovery is secondary evidence, not the original report.

The recovered F-02 themes include contextual intent, reference grounding, speech-act/source attribution, uncertainty, clarification when context is insufficient, trusted/untrusted content separation and continuity. F-03 concerns whether accepted reasoning results, uncertainty and alternatives materially affect downstream cognitive processing, including rejection/invalidation and traceable end-to-end behavior.

The Project Director previously rejected situation-specific/hardcoded language mechanisms: requirements must describe general capacities, not fixed mappings or an exhaustive list of situations. Any correction must preserve that constraint.

**Disposition:** F-02 and F-03 remain OPEN. No speculative correction has been made to the accepted specification. The Project Director must decide whether to accept the missing-original-report condition as a bounded provenance limitation and authorize a correction/re-review based on the recovered requirement themes, or require further recovery of the original artifact first. The technical obligations do not disappear if the provenance limitation is accepted.

## 3. PR #191 — exact ancestry and integration facts

Live refs:

- PR #191 base: `f6267456560a08054d69f7960d2951452b14017c`.
- PR #191 head: `609d38ede50bbdd98a93dfed112781eacabee9fd`.
- PR #179 head: `61311fe5b44c81c4409c8ba8dc581a83bdd5dd2c`.

Exact comparisons:

1. PR #191 base to PR #179 head: PR #179 is 22 commits ahead; PR #191's base is an ancestor of PR #179.
2. PR #179 head to PR #191 head: histories are **diverged**; PR #191 has one unique commit and is 22 commits behind the PR #179 line.
3. The unique PR #191 contribution is the human/MCU comparison report.

Retargeting PR #191 alone would not incorporate the 22 intervening commits.

**Decision required:** choose either (a) review PR #191 as a historical-base, bounded comparison artifact, or (b) authorize a new dependent revision that replays its one unique report commit onto the current PR #179 line and is independently reviewed. No rebase, cherry-pick, retarget or merge was performed.

## 4. PR #192 and PR #193 — separate lineages

Live refs:

| PR | Base | Head | State |
|---|---|---|---|
| #192 | PR #179 head `61311fe5b44c81c4409c8ba8dc581a83bdd5dd2c` | `c166e7d955293f1108f71b123d0a92f5941bdabd` | Open, non-draft, unmerged |
| #193 | PR #175 head `874c732973b6ab303d65a503f5a215b0af8e1153` | `65220543416da9b368f24e226aefe24bcdbc7870` | Open, draft, unmerged |

PR #192 contains the documentation portal, planning index, inventory, foundation audit and related documentation closeout. PR #193 changes two paths: the implementation plan and project continuity/recovery handoff. Its branch is derived from PR #175, not PR #179, and it explicitly links readers to the PR #192 documentation index. Both PR #193 files still carry the older PR #173 UNVERIFIED/PROPOSED wording. That wording is now superseded by the recovered decision in PR #173 comment #6752144835; correcting the two files should be part of the authorized cross-lineage reconciliation so their pinned links and the PR #192 index do not drift independently.

**Decision required:** authorize an integration order. A reasonable candidate is to integrate/reconcile the PR #192 documentation foundation first, then replay/reconcile the two PR #193 handoff/plan documents against that resulting state. This is only a recommendation; no integration order is inferred or executed.

## 5. PR #192 independent review — actual submission and qualification

A formal GitHub review submission exists on PR #192:

- **Review state:** COMMENTED.
- **Submitted:** 2026-11-09 10:59:55 UTC.
- **Declared reviewer:** Grok (xAI).
- **Declared model independence:** distinct model identity from the Builder (ChatGPT / GPT-6).
- **Exact revision examined:** `9e0c342dcfbbe1d7a51a6b3a2b7574c9cdf480dc`.
- **Current PR #192 HEAD:** `c166e7d955293f1108f71b123d0a92f5941bdabd`.
- **Determination:** NOT CLEAR TO PROCEED.

The formal review was submitted through the same GitHub account (`methaneex-oss`) used for the repository's Builder activity. The review body declares a distinct Grok model identity, but GitHub does not attribute it to a separately authenticated reviewer account. The review also targets the parent revision `9e0c342...`, not the current HEAD `c166e7d...`, which adds the report artifact.

**Decision required:** determine whether the declared distinct model identity is sufficient for the project's “genuinely separate reviewer” requirement despite the shared GitHub account, and whether a short exact-current-HEAD re-review is required. Do not claim DF-11 fully satisfied until this is decided and the exact-revision requirement is met.

The reviewer's substantive determination remains **NOT CLEAR TO PROCEED**. The review does not accept the package or authorize Stage A.

## 6. Documentation-foundation evidence status

| Area | Current evidence | Remaining boundary |
|---|---|---|
| DF-03 / PR #173 authority | Prior explicit acceptance recovered; exact head and scope recorded in PR #173 comment #6752144835 | Update dependent indexes/registers so they no longer repeat the stale unverified classification |
| DF-06 / links | Bounded current-package path, anchor and external-reference validation is recorded | Not proof of semantic suitability or exhaustive validation of every historical/external reference |
| DF-08 / preservation | Bounded branch/PR discovery and 108-path / 28-PR documentation register are recorded | Broader historical source mapping and archive/supersession decisions remain incomplete |
| DF-09 / fresh reader | Fixed 17-question protocol exists | No actual uninvolved human session or raw evidence; remains OPEN |
| DF-11 / independent review | Formal Grok-declared COMMENTED review submitted against `9e0c342...` | Separate-account identity is not established; current HEAD `c166e7d...` was not the exact reviewed revision; qualification requires Project Director decision |
| DF-12 / authority | No final documentation-foundation acceptance decision | Project Director exact-revision decision remains required |
| DF-13 / planning hold | Stage A remains not started and held | Must remain held until all required evidence, review and acceptance conditions are met |

The 2026-11-09 Grok review's “DF-06 / DF-08 PARTIAL” finding and the later Builder's bounded-validation completion claims are not mutually exclusive: bounded checks have been completed, but exhaustive semantic/historical coverage and preservation disposition have not.

## 7. Project Director decisions still required

1. **PR #174 provenance:** accept the unavailable original F-02/F-03 review as a bounded provenance limitation and authorize correction/re-review from the recovered themes, or require further recovery before correction.
2. **PR #191:** review as-is on its historical base, or authorize a new dependent revision on the current PR #179 line.
3. **PR #192 / #193:** choose the integration order; the recommended sequence is #192 foundation first, then #193 handoff/plan reconciliation.
4. **DF-11:** decide whether Grok's declared distinct model identity is sufficient despite the same GitHub account, and require/waive only through explicit governance whether the current #192 HEAD must receive a fresh review.
5. **DF-09:** remains open until an uninvolved human completes the protocol. An LLM-only exercise is not substituted for the specified human test.
6. **DF-12:** accept, reject or conditionally accept the exact final documentation-foundation revision only after the required evidence and review are complete.

## 8. Non-actions and hold

No PR was merged, rebased, retargeted, cherry-picked or closed. No branch was deleted or consolidated. No runtime source, tests, build configuration, dependencies, workflows or runtime state were changed. No baseline/donor, algorithm, provider, technology or implementation sequence was selected.

**Stage A remains HELD. Implementation remains unauthorized.**

**End of reconciliation.**


---

## 9. Final repository reconciliation before Project Director decisions — 2026-11-09

This addendum records the final bounded work performed after the initial reconciliation. Its **parent snapshot** is PR #192 HEAD `696f24d728be2bb243b57bc595a4e14128528004`; the addendum commit advances PR #192 beyond that parent. The exact resulting commit is the commit containing this addendum.

### 9.1 Recovered PR #173 acceptance corrected in dependent documents

The recovered Project Director acceptance is no longer described as unresolved in the active downstream planning artifacts:

- PR #174 specification branch was updated to `be46b3858102c31022128522c4b3506aad4dff8a`. Its parent-architecture reference now identifies PR #173 exact HEAD `97191111bc2573c14d391c0af9628db7b11f194b` as the accepted planning baseline and links the provenance transcription in PR #173 comment #6752144835.
- PR #193 implementation-plan branch was updated to `b23f7751a0ba39f9cb9295e264a3b2ed539cc438`.
- PR #193 continuity/recovery handoff was updated to `ee508c09be9d848c7baa9533bb6f88f9cc27f94a`.

These are documentation-status corrections only. They do not alter the accepted PR #173 baseline, clear F-02/F-03, activate the implementation roadmap or authorize implementation.

### 9.2 Current PR metadata snapshot

| PR | Base SHA | Head SHA at this snapshot | State | Draft | Merged | Mergeable |
|---|---|---|---|---|---|---|
| #173 | `1273ddbcd0087d189e01388ded2d362fb1e058d2` | `97191111bc2573c14d391c0af9628db7b11f194b` | Open | Yes | No | Yes |
| #174 | `97191111bc2573c14d391c0af9628db7b11f194b` | `be46b3858102c31022128522c4b3506aad4dff8a` | Open | Yes | No | Yes |
| #191 | `f6267456560a08054d69f7960d2951452b14017c` | `609d38ede50bbdd98a93dfed112781eacabee9fd` | Open | Yes | No | Yes |
| #192 | `61311fe5b44c81c4409c8ba8dc581a83bdd5dd2c` | `696f24d728be2bb243b57bc595a4e14128528004` (parent of this addendum) | Open | No | No | Yes |
| #193 | `874c732973b6ab303d65a503f5a215b0af8e1153` | `ee508c09be9d848c7baa9533bb6f88f9cc27f94a` | Open | Yes | No | Yes |

All five PRs remain unmerged. PR #192 is non-draft and GitHub currently reports it mergeable; mergeability is not acceptance or authorization. The branch lineages remain distinct: #192 is based on the #179 integration-map line, while #193 is based on the #175 implementation-plan line.

### 9.3 F-02/F-03 technical comparison against the current specification

The original full reviewer report remains unavailable. The following is a bounded technical comparison against the secondary recovered themes, not a claim to reproduce the original reviewer's complete rationale.

**F-02 — HIGH / CONFIRMED: contextual language and operator-intent grounding.**

The current specification has relevant general foundations:
- BM-02 preserves multiple interpretations, contextual assumptions, evidence links and uncertainty (specification §§4, 5).
- BM-08 distinguishes supplied goals, experience-acquired candidate goals and governance constraints, and requires context/evidence lineage (§§4, 5).
- However, the specification does not yet make the recovered language-specific obligations explicit as an enforceable capability: contextual reference resolution, speech-act/intent attribution, source attribution across quoted or relayed content, clarification when context is insufficient, and trusted/untrusted language separation with continuity across turns.

The current wording is directionally compatible but not demonstrably sufficient to close F-02. Any correction must specify general capacities and observable tests, not hardcoded phrase lists, source-to-intent mappings or fixed stimulus-response behavior.

**F-03 — MEDIUM / CONFIRMED: enforceable downstream reasoning integration.**

The current specification already has substantial integration content:
- BM-12 receives retrieved memory with context/provenance and publishes provisional conclusions with premise lineage (§5.12).
- Section 6.3 explicitly routes qualified conclusions to BM-04, BM-05 and BM-08 and says memory retrieval without downstream inference effect is not integrated cognition.
- Scenarios 27–34 test premise lineage, insufficient evidence, contradiction, memory influence, defeated assumptions, counterexamples, alternatives and stale/out-of-scope premises.
- Section 10 requires retrieved evidence to materially affect downstream inference or decision.

The remaining enforceability question is whether the contract and scenarios adequately prove downstream owners actually consume, reject, invalidate or re-evaluate reasoning outputs under changing evidence, rather than merely record a traceable conclusion and state that it may be consumed. A correction would need end-to-end acceptance evidence for positive influence, explicit rejection/non-consumption, stale-output invalidation, and re-evaluation after premise/assumption changes. This is a technical obligation; accepting the missing report as a provenance limitation would not close it.

### 9.4 Remaining Project Director decisions

The repository investigation and bounded documentation corrections are complete up to these authority boundaries:

1. **PR #174 provenance choice:** either (A) accept the unavailable original F-02/F-03 report as a bounded provenance limitation only, retaining both technical findings as open and authorizing a correction/re-review based on the recovered themes; or (B) require further recovery of the original report before authorizing corrections. No F-02/F-03 correction has been made.
2. **PR #191 disposition:** either review it as a historical-base comparison artifact without changing ancestry, or authorize a new dependent revision that replays its single unique report commit onto the current PR #179 line and receives fresh review. No history-changing operation has been performed.
3. **PR #192 / #193 order:** choose whether to reconcile/accept the #192 documentation foundation first and only then reconcile #193's deferred implementation-plan/handoff documents, or specify another order. Recommended order is #192 first, #193 second.
4. **DF-11 reviewer qualification:** decide whether Grok's declared distinct model identity is sufficient despite the same GitHub account attribution. The submitted review examined `9e0c342dcfbbe1d7a51a6b3a2b7574c9cdf480dc`, not the later PR #192 revisions; if exact-current-HEAD review is required, authorize that re-review after the reviewer's qualification is settled.
5. **DF-09:** no uninvolved human has completed the 17-question fresh-reader protocol. This remains open; no LLM substitute is claimed.
6. **DF-12:** final documentation-foundation acceptance remains a separate Project Director decision after the required review and human evidence.

No PR was merged, rebased, retargeted, cherry-picked or closed. No runtime source, tests, build configuration, dependencies, workflows or runtime state were changed. No implementation baseline, donor, algorithm, provider, technology or sequence was selected.

**Disposition remains NOT CLEARED. Stage A remains HELD. Implementation remains unauthorized.**


---

## 10. Corrected live-state addendum — 2026-11-09

This addendum supersedes stale current-head values in §§2–5 and §9. The following are exact live GitHub results re-fetched after those earlier snapshots.

### PR #174

- Current PR HEAD: `be46b3858102c31022128522c4b3506aad4dff8a`.
- Current specification blob: `b366564b3f68e674ae5f5f9fc5a6c90d8b4f454d`.
- State: open, draft, unmerged.
- Accepted planning-baseline HEAD remains `0811a59e46bf934e32e794f90e4e7d18d4e2bd97`, by Project Director comment #6604790481.
- Current document header correctly states that the accepted baseline is the earlier exact revision and that follow-on F-02/F-03 remain open.
- Current formal-review and inline-thread endpoints return zero records. The recovery record is partial: original review title, overall verdict, finding identities, severity and themes were recovered, but the original full report, complete rationale and exact inline annotations remain unavailable.

The two findings are independently documented:
- **PR #174 follow-on F-02:** HIGH / CONFIRMED — contextual language and operator-intent grounding, including contextual intent, reference grounding, speech-act/source attribution, uncertainty, clarification, trusted/untrusted content separation and interaction continuity.
- **PR #174 follow-on F-03:** MEDIUM / CONFIRMED as a specification weakness — accepted reasoning must materially influence authoritative downstream computation; rejection/invalidation must be explicit; end-to-end effects must be traceable.

The recovered requirement themes are sufficient to identify the obligations, but not to reconstruct the reviewer's exact rationale or line-by-line correction request. No correction was guessed or applied. The Project Director must decide whether to accept the missing original artifact as a bounded provenance limitation and authorize corrections/re-review from the recovered themes, or require further recovery first.

### PR #191

- Base: `f6267456560a08054d69f7960d2951452b14017c`.
- Head: `609d38ede50bbdd98a93dfed112781eacabee9fd`.
- One changed file: `docs/architecture/reports/PHASE_2_HUMAN_AND_MCU_REFERENCE_COMPARISON_2026-11-06.md`, blob `eac3cb443b5c6a2b9c0d9ad9f5fd552b79d8a0e2`.
- The file is absent at PR #179 HEAD `61311fe5b44c81c4409c8ba8dc581a83bdd5dd2c`; it is a unique artifact, not an existing duplicate.
- Comparing PR #191 HEAD to PR #179 HEAD returns DIVERGED: one unique PR #191 commit and 22 commits on the #179 line. PR #191's base remains an ancestor of #179.

The artifact can be read and reviewed as a historical-base document without rewriting history. If the intended requirement is that it live on the current #179 line, a dependent revision must be explicitly authorized. The choice remains with the Project Director.

### PR #193

- State: open, draft, unmerged.
- Base: `874c732973b6ab303d65a503f5a215b0af8e1153`.
- Current HEAD: `ee508c09be9d848c7baa9533bb6f88f9cc27f94a`.
- Compare against its own base: 31 commits ahead, 0 behind.
- Current implementation-plan blob: `7df34fed59c1c8577ddcd23c02f772f366d46d39`.
- Current continuity-handoff blob: `0392ff59c6ae48d3c78e571c905550dfc77a5965`.

Both documents still contain historical PR #173 UNVERIFIED/PROPOSED wording in parts of their history/current text. The recovered PR #173 acceptance supersedes that status. Updating those files should occur as part of an authorized cross-lineage reconciliation, not by silently editing PR #193 or changing its base.

### PR #192 and gate

PR #192 remains open, non-draft and unmerged on base `61311fe5b44c81c4409c8ba8dc581a83bdd5dd2c`. Its latest exact HEAD and 28-path artifact manifest are recorded in the inventory's subsequent §45 snapshot.

The following decisions remain reserved to the Project Director:
1. Accept the missing original PR #174 F-02/F-03 report as a bounded provenance limitation and authorize correction/re-review from the recovered themes, or require further recovery first.
2. Choose historical-base review or authorize a dependent PR #191 revision.
3. Set PR #192/#193 integration order.
4. Decide whether Grok's declared distinct model identity suffices for DF-11 despite shared GitHub account attribution, and whether exact-current-HEAD re-review is required.

DF-09 still requires an uninvolved human to complete the 17-question test. DF-12 still requires the final exact-revision acceptance decision. Stage A remains HELD; implementation remains unauthorized.


---

## 11. PR #193 current-file authority wording recheck — 2026-11-09

The PR #193 current-file status statement in §§4 and 10 is superseded by this exact-current-file recheck.

At PR #193 HEAD `ee508c09be9d848c7baa9533bb6f88f9cc27f94a`, the two changed files were fetched directly:

- `docs/architecture/plans/00_BRAIN_IMPLEMENTATION_PLAN.md`, blob `7df34fed59c1c8577ddcd23c02f772f366d46d39`: its current authority header and planning-baseline references identify PR #173 exact HEAD `97191111bc2573c14d391c0af9628db7b11f194b` as accepted and cite decision comment #6752144835.
- `docs/architecture/plans/JARVIS_PROJECT_CONTINUITY_AND_RECOVERY_HANDOFF.md`, blob `0392ff59c6ae48d3c78e571c905550dfc77a5965`: its current handoff and recovery sections identify the recovered PR #173 acceptance, its limited planning-baseline scope and the same decision comment.

Accordingly, the prior statement that both current PR #193 files still contain PR #173 UNVERIFIED/PROPOSED wording was stale. Other uses of “unverified” in the files refer to unrelated technical evidence or derived state, not PR #173's acceptance status.

This is a factual documentation correction only. PR #193 remains on its existing PR #175-derived branch; no cross-lineage integration or history operation was performed. The Project Director's PR #192/#193 order decision remains outstanding.

---

## 10. Current-run recheck and stale-snapshot correction — 2026-11-09

**Reviewed pre-update PR #192 HEAD:** 400be7f87a5db5c978819aaa85f84853422384d2 (open, non-draft, unmerged; base 61311fe5b44c81c4409c8ba8dc581a83bdd5dd2c; 28 changed paths). This addendum supersedes the earlier live-state values in §§4, 5, 9 and the earlier PR #193 wording where newer exact evidence is recorded below. Those earlier statements remain historical snapshots.

### 10.1 Current PR and document references

| Item | Verified current reference | Result |
|---|---|---|
| PR #192 | 400be7f87a5db5c978819aaa85f84853422384d2 | Open, non-draft, unmerged; 28 changed paths |
| Planning index | Blob 1e896ae07ceda0bc200ef26bb9cf123a62521200 at the preceding index commit 0796ff8c3ef7057a19c4565fa2d158a6f0bd97ce | Updated active PR #193 links and corrected stale PR #193 status wording; added current-run DF-09/DF-11 supersession note |
| Authority register | Blob 989c991267a6a3e61dd55b2ffb3ec95774778702 at preceding commit 400be7f87a5db5c978819aaa85f84853422384d2 | Added current-run PR, F-02/F-03, DF-06/08/09/11/12 evidence and decisions |
| PR #174 | HEAD be46b3858102c31022128522c4b3506aad4dff8a; spec blob b366564b3f68e674ae5f5f9fc5a6c90d8b4f454d | Open/draft/unmerged; accepted baseline remains 0811a59e46bf934e32e794f90e4e7d18d4e2bd97 |
| PR #191 | HEAD 609d38ede50bbdd98a93dfed112781eacabee9fd; report blob eac3cb443b5c6a2b9c0d9ad9f5fd552b79d8a0e2 | One unique added report path; no reviews/comments/inline threads |
| PR #193 | HEAD ee508c09be9d848c7baa9533bb6f88f9cc27f94a; plan/handoff blobs 7df34fed59c1c8577ddcd23c02f772f366d46d39 / 0392ff59c6ae48d3c78e571c905550dfc77a5965 | Both current files correctly state PR #173 acceptance; previous statement in §§4/9 that they still contain UNVERIFIED/PROPOSED wording is superseded |
| PR #179 Phase 2 map | Blob e7c85d74a1051a40a10b0318da739c6b1b0c2ad7 at HEAD 61311fe5b44c81c4409c8ba8dc581a83bdd5dd2c | Exact map revision to use for any future PR #191 replay review |

PR #193 remains on the PR #175-derived lineage; PR #192 remains on the PR #179-derived lineage. The PR #193 plan and handoff link back to PR #192 commit db5968bfbddf77590cd9303539abda00dd961ab7. That pinned snapshot was fetched successfully for docs/README.md, the planning index and the whole-Brain scope correction. These are valid immutable historical links, not links to the current PR #192 head. PR #192 and PR #193 have no changed-path overlap. The recommended sequencing remains PR #192 foundation first, then a separately authorized refresh/reconciliation and review of PR #193's two files. No integration operation is authorized.

### 10.2 PR #174 original-review recovery status

The current PR #174 discussion contains four issue comments. The formal review list returned zero submissions and the inline review-thread endpoint returned zero threads. The comments record Builder handoffs, the exact planning-baseline acceptance, and a Builder correction submission; they do not contain the later F-02/F-03 report. Bounded commit-message searches for F-02, F-03 and “follow-on review” returned no matches. The checked-in recovery record remains secondary and partial; the original report, complete rationale and exact inline annotations are not available from the retrieved sources.

Current affected specification locations, at blob b366564b3f68e674ae5f5f9fc5a6c90d8b4f454d:
- F-02: BM-02 lines 196–218 and BM-08 lines 357–389.
- F-03: §6.3 lines 641–653; scenarios 27–34 at lines 803–810; §10 at lines 814–835.

The themes recovered from secondary context remain contextual intent/reference grounding and enforceable downstream use of qualified reasoning. No speculative correction was made. Project Director disposition is still required on whether to accept the missing original artifact as a bounded provenance limitation and authorize corrections/re-review, or require further recovery first. F-02 and F-03 remain open.

### 10.3 PR #191 and replay implications

PR #191's unique contribution is one 220-line report added at blob eac3cb443b5c6a2b9c0d9ad9f5fd552b79d8a0e2. It is absent from PR #179 HEAD 61311fe5b44c81c4409c8ba8dc581a83bdd5dd2c. The PR #191 base is an ancestor of PR #179, but the PR #191 head diverges by one unique commit versus 22 commits on the PR #179 line. No PR #191 comments, formal reviews or inline threads exist. A replay would add the single absent path without overwriting an existing target file; the residual risk is semantic freshness because the report describes its source map as the current PR #179 branch without pinning the exact map revision. Any authorized replay should be checked against the exact Phase 2 map blob above and independently reviewed. The Project Director must choose historical-base review or authorize a dependent replay.

### 10.4 DF-06 / DF-08 validation status

The bounded inline-Markdown relative-target scan was run at pre-update PR #192 HEAD 98a01381f11e08dd1f682e662bf714a5ad434945: the complete changed-file endpoint returned 28 paths, all 28 were fetched, the recursive tree contained 257 entries and was not truncated, and no missing repository-relative targets were found. The same parser found no fragment-bearing inline Markdown links in those scanned files. After the index/register/report updates, all 28 changed paths were fetched again at parent HEAD 6d761a06209dba8bc4b1e191b15fb32349fed0eb for inventory §46; that later pass verified the parent blob manifest, not a second link scan. Inventory §46 is an immutable parent snapshot, not the resulting live PR head. Raw HTML links, reference-style link definitions, semantic relevance and exhaustive historical links were not established by these bounded checks.

The earlier preservation report's bounded evidence remains: 89 immutable source links across 45 exact commit/path pairs; 76 line-anchor ranges checked; 189 external URL occurrences classified/checked within its then-current scope; one historical ChatGPT shared-conversation pointer remains access-limited/unverified. Those checks were not rerun exhaustively against this newer head. DF-06 remains PARTIAL.

DF-08 remains PARTIAL. The existing bounded discovery records 245 branches, 184 PRs and 108 documentation paths across 28 PRs. Broader historical mapping and archive/supersession decisions remain unresolved. No archive or destructive action was taken.

### 10.5 DF-09 / DF-11 / DF-12 and final gate

- **DF-09:** no uninvolved human session exists. The exact 17-question list was not recoverable from the repository or accessible Library files in this run. The reviewer handoff contains a 16-versus-17 count inconsistency. Therefore the test package is not fully portable/volunteer-ready until the authoritative list is restored and the count reconciled. No volunteer was contacted and no LLM was substituted.
- **DF-11:** a formal Grok-declared COMMENTED review exists, submitted at 2026-11-09 10:59:55 UTC against PR #192 HEAD 9e0c342dcfbbe1d7a51a6b3a2b7574c9cdf480dc. It declares a distinct model identity from Builder GPT-6 but was submitted through the same methaneex-oss GitHub account. Current PR #192 HEAD is 400be7f87a5db5c978819aaa85f84853422384d2; no exact-head review exists. Reviewer qualification and exact-head re-review remain Project Director decisions. No separate authenticated reviewer identity was available in this run.
- **DF-12:** exact-revision Project Director acceptance remains outstanding.
- **DF-13:** Stage A remains NOT STARTED and HELD; implementation remains unauthorized.

**Final disposition: DOCUMENTATION FOUNDATION NOT CLEARED.** The Project Director decisions remain PR #174 provenance route, PR #191 disposition, PR #192/#193 order, DF-11 qualification/exact-head review, and DF-12 exact-revision acceptance. DF-09 still requires a real uninvolved human. No PR was merged, rebased, retargeted, cherry-picked or closed. No runtime source, tests, dependencies, build/workflow files or runtime state changed. No Stage A or implementation work was started.


## 11. Live-state reconciliation and revised fresh-reader criterion — 2026-11-09

This addendum records the repository state re-fetched during the immediate continuation run. It supersedes earlier live-head snapshots in this report where the values differ.

### 11.1 Live PR revisions verified

| PR | Base | Current HEAD | State | Verification |
|---|---|---|---|---|
| #173 | main at `1273ddbcd0087d189e01388ded2d362fb1e058d2` | `97191111bc2573c14d391c0af9628db7b11f194b` | Open, draft, unmerged | `get_pr_info`; recovered Project Director decision transcribed in comment [#6752144835](https://github.com/methaneex-oss/MethaneX/pull/173#issuecomment-6752144835) |
| #174 | PR #173 accepted head `97191111bc2573c14d391c0af9628db7b11f194b` | `be46b3858102c31022128522c4b3506aad4dff8a` | Open, draft, unmerged | Live metadata; current specification blob `b366564b3f68e674ae5f5f9fc5a6c90d8b4f454d` |
| #191 | `f6267456560a08054d69f7960d2951452b14017c` | `609d38ede50bbdd98a93dfed112781eacabee9fd` | Open, draft, unmerged | One changed file: human/MCU comparison report, blob `eac3cb443b5c6a2b9c0d9ad9f5fd552b79d8a0e2` |
| #192 | `61311fe5b44c81c4409c8ba8dc581a83bdd5dd2c` | `ac7f860dc257e181a12612bf3e3cb811ce26bd58` | Open, non-draft, unmerged | Live metadata; 28 changed paths returned by paginated changed-file listing |
| #193 | `874c732973b6ab303d65a503f5a215b0af8e1153` | `ee508c09be9d848c7baa9533bb6f88f9cc27f94a` | Open, draft, unmerged | Two changed files: implementation plan blob `7df34fed59c1c8577ddcd23c02f772f366d46d39`; continuity handoff blob `0392ff59c6ae48d3c78e571c905550dfc77a5965` |

PR #174's live review-submission and inline-thread endpoints returned zero records. Its discussion contains four issue comments, including the exact accepted-baseline decision #6604790481, but not the original follow-on F-02/F-03 review. The recovery artifact remains secondary/partial. The current specification's F-02-relevant locations include BM-02 (lines 196–218) and BM-08 (lines 357–389); F-03-relevant locations include §6.3 (lines 641–653), scenarios 27–34 (around lines 803–810), and §10. These are verified locations, not recovered original inline annotations.

PR #191 still contributes one unique 220-line report absent from PR #179 HEAD. Its base is an ancestor of PR #179, while its head diverges by one unique PR #191 commit versus 22 intervening PR #179 commits. No disposition is inferred.

PR #193's current plan and handoff both state the recovered PR #173 acceptance and cite comment #6752144835. They remain on the PR #175-derived lineage. PR #192 and #193 have separate bases; no integration order is inferred.

### 11.2 DF-11 current status

The formal Grok-declared review remains a GitHub `COMMENTED` submission against PR #192 HEAD `9e0c342dcfbbe1d7a51a6b3a2b7574c9cdf480dc`, submitted 2026-11-09 10:59:55 UTC. The review states **NOT CLEAR TO PROCEED**. It declares Grok (xAI) as a model identity distinct from Builder GPT-6, but GitHub attributes the submission to the same `methaneex-oss` account used for Builder activity. PR #192 has since advanced to `ac7f860dc257e181a12612bf3e3cb811ce26bd58`; the formal review is not against this current exact HEAD. The reviewer qualification and exact-head re-review requirements remain unresolved; DF-11 is not unconditionally satisfied.

### 11.3 Project Director's revised DF-09 criterion

The Project Director has now explicitly instructed that the uninvolved-human fresh-reader session be skipped. The accepted substitute is a genuinely different AI model, given only the actual repository entry point and documentation package, with no prior project summary or conversation context. It must independently explain the project, document navigation, current state, architecture/planning boundaries, unresolved work, authority gates and next safe actions, citing exact repository paths and distinguishing explicit statements, inference and unavailable information. Its model identity, prompt, exact repository revision, raw answers, navigation path, ambiguities and unanswered questions must be preserved.

This is an explicit change to the reader-comprehension evidence criterion; it must be labelled an **AI fresh-reader assessment**, not a human session. The user has stated that a different AI's demonstrated ability to understand the repository is sufficient for this criterion. The assessment has **not yet been performed** in this run: no separate-model inference endpoint was available through the connected tools exercised, and an attempted Hugging Face Space discovery call returned a tool-not-found error. Do not simulate a second model, reuse Builder GPT-6 as an independent reader, or claim a pass without actual distinct-model output. If a separate model cannot be invoked, record that technical limitation for the Project Director rather than fabricating evidence.

### 11.4 Gate disposition and non-actions

- DF-06 remains **PARTIAL**: bounded relative-path/link checks and earlier pinned-source/anchor/external-reference checks are documented, but the available evidence does not establish exhaustive semantic, raw-HTML, reference-style or all-historical-link validation.
- DF-08 remains **PARTIAL**: bounded discovery and preservation mapping are substantial, but broader historical reconciliation and archive/supersession decisions remain incomplete.
- DF-09 is **REVISED / AI ASSESSMENT PENDING** under the Project Director's explicit instruction above.
- DF-11 remains **UNRESOLVED** as to reviewer qualification and exact-current-head review.
- DF-12 remains **AWAITING PROJECT DIRECTOR EXACT-REVISION DECISION**.
- DF-13 remains **NOT STARTED / HELD**. Runtime implementation remains unauthorized.

No PR was merged or closed; no branch was rebased, retargeted or cherry-picked; no cross-lineage integration was performed; no runtime source, tests, dependencies, build/workflow files or runtime state were changed. The PR #192/#193 integration order, PR #191 disposition, PR #174 missing-original-report route, reviewer qualification and final DF-12 acceptance remain Project Director decisions.


---

## 10. Project Director decision — AI fresh-reader substitution and live-state correction — 2026-11-09

The Project Director explicitly instructed that the uninvolved-human fresh-reader requirement be skipped. The accepted substitute is a fresh-reader assessment by a genuinely different AI model, supplied only the repository's actual entry point and documentation package, with no prior project conversation, memory, Builder handoff or reviewer summary. It must independently navigate the documents, explain the project's purpose/current phase/architecture boundaries/authority gates/open work/next safe actions, cite exact paths and sections, and distinguish explicit statements from inference and unavailable information. Its prompt, declared model identity, exact repository revision, raw answers, navigation trail, ambiguities and unanswered questions must be preserved. This is AI comprehension evidence, not a human session.

The Project Director's substitution decision is recorded; the assessment itself has not been performed or passed. The tools available in this execution expose repository operations and task orchestration but no callable inference endpoint or separately selectable model identity. The current assistant cannot truthfully impersonate another model or label its own reading as independent. A distinct model must actually be invoked before DF-09 can be marked satisfied under the revised criterion. The prior Grok review is not a substitute: it was a reviewer assessment, not a blind fresh-reader test, and examined an earlier PR #192 revision.

### Live PR state recheck

At the time of this addendum, GitHub reports:
- PR #174 open, draft, unmerged; base 97191111bc2573c14d391c0af9628db7b11f194b; head be46b3858102c31022128522c4b3506aad4dff8a.
- PR #191 open, draft, unmerged; base f6267456560a08054d69f7960d2951452b14017c; head 609d38ede50bbdd98a93dfed112781eacabee9fd; one changed file: docs/architecture/reports/PHASE_2_HUMAN_AND_MCU_REFERENCE_COMPARISON_2026-11-06.md.
- PR #192 open, non-draft, unmerged; base 61311fe5b44c81c4409c8ba8dc581a83bdd5dd2c; head 4cdfbda5f428ab8c9f78db8e0bc7a7f42e0bfcd0.
- PR #193 open, draft, unmerged; base 874c732973b6ab303d65a503f5a215b0af8e1153; head ee508c09be9d848c7baa9533bb6f88f9cc27f94a; its two changed paths are the implementation plan and continuity/recovery handoff.

PR #174 review-submission and inline-thread queries returned empty arrays in this check. Its issue-comment timeline contains Builder handoff/resubmission comments and the Project Director acceptance comment #6604790481. The current specification at PR #174 head be46b3858102c31022128522c4b3506aad4dff8a correctly records acceptance of the exact planning baseline 0811a59e46bf934e32e794f90e4e7d18d4e2bd97 and the recovered PR #173 parent acceptance. The earlier accepted revision and current PR head must not be conflated.

The previously cited recovery-report path docs/architecture/reports/PR_174_FOLLOW_ON_REVIEW_PROVENANCE_RECOVERY_2026-11-06.md returned 404 at both the current PR #174 head and default branch during this execution. The original full F-02/F-03 reviewer report and inline annotations therefore remain unrecovered from those locations; the existing reconciliation report's recovered themes remain secondary evidence only.

### Status and limits

- User-approved AI substitution: DECIDED.
- Fresh distinct-model execution: NOT PERFORMED — no separate model invocation is exposed in this execution environment.
- DF-09 under revised criterion: OPEN pending actual blind AI assessment.
- DF-11 remains a separate reviewer-qualification/exact-head issue; the fresh-reader substitution does not waive it.
- PR #174 F-02/F-03, PR #191 disposition, PR #192/#193 integration order, DF-11 qualification, and DF-12 final exact-revision acceptance remain unresolved authority/evidence items.
- No merge, close, rebase, retarget, cherry-pick, implementation, or Stage A release was performed.
