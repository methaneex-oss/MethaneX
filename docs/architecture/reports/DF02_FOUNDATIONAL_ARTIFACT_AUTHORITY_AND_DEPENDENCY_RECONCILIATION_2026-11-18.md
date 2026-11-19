# DF-02 — Foundational Artifact Authority and Dependency Reconciliation
**Prepared:** 2026-11-18  
**Repository:** `methaneex-oss/MethaneX`  
**Documentation Foundation PR:** #192  
**Source PR #192 HEAD inspected:** `3c9e512947412ea0ca8776a77b2e0e71c0f7af42`  
**Source inventory blob:** `dc7a5dc5eb1c0807e54998c9657a3e33bf107713`  
**Purpose:** Reconcile the principal JARVIS planning artifacts against live pull-request metadata, exact source revisions, recorded Project Director decisions, independent-review targets, and material dependencies.  
**Status:** Builder reconciliation evidence; **DF-02 remains OPEN** pending completion of the wider historical/branch inventory and independent verification.

---

## 1. Scope and method

This pass addresses the specific DF-02 deficiency identified in the xAI review of PR #192: a changed-path/blob manifest is not a semantic inventory of each artifact's authority, revision, status, and dependencies.

For each principal artifact below, the Builder:
1. fetched live PR metadata on 2026-11-18 (state, draft/merged status, head SHA, base branch and base SHA);
2. fetched the named document at its identified commit and recorded the returned blob SHA;
3. inspected the relevant PR discussion records for exact-revision Project Director decisions and independent-review outcomes;
4. distinguished the accepted historical baseline from a later proposal or successor revision; and
5. recorded material predecessor/consumer relationships and the authorization boundary.

A PR being open or draft does not negate a separate, exact-scope Director decision. Conversely, a PR title, a document header, a prior handoff, or a later branch head does not expand an earlier acceptance. A review verdict applies only to the exact revision named by that review. No PR, branch, or document is treated as accepted merely because it is present in this register.

This is a bounded reconciliation of the principal JARVIS planning lineages and their controlling dependencies. It is not yet a complete census of every historical artifact, every README/fragment reference, every donor branch, or every cross-branch dependency. It does not recommend deletion, relocation, merge, rebase, retargeting, or source-baseline selection.

## 2. Authority vocabulary

| Classification | Meaning |
|---|---|
| **Approved within stated scope** | A Project Director decision explicitly approves the identified artifact/revision for the stated scope. It does not transfer to materially changed content or a wider deliverable. |
| **Accepted planning input / decision** | Explicit acceptance permits use in a named subsequent planning stage or settles specified decisions; it is not architecture-wide acceptance or implementation authority. |
| **Proposed / unaccepted** | A submitted proposal or later successor for which the required approval is absent. |
| **Independent review — exact revision only** | A technical/reader verdict is attached only to the exact SHA identified in the review record. It is not Director acceptance. |
| **Historical / donor / reference** | Retained as source evidence or a bounded comparison; not a selected implementation baseline or governing architecture. |
| **Merged into named base** | Repository integration occurred into the exact base branch stated. It does not imply merge to `main`, phase acceptance, or implementation authorization. |
| **Open / unresolved** | Required provenance, review, acceptance, gate, or technical disposition remains outstanding. |

## 3. Reconciled artifact and authority register

### 3.1 Whole-system foundation and bounded research

| Artifact / lineage | Exact revision and content identity verified | Authority and live status (2026-11-18) | Dependencies / consumers and boundary |
|---|---|---|---|
| PR #171 — Document 00, `00_JARVIS_SYSTEM_ARCHITECTURE_FOUNDATION.md` | Approved content revision: commit `8490737429b052b65fed3b998e0320d8834f640f`; approval comment #6555976534. The later PR #171 administrative record identifies approved content blob `ff0e57f2f9a266466687dca2c4cbcda6a64cb7d7`. Fetched current PR head `b05434758ad4fe72815503f89bd5d2990ccb658b`, current blob `db0f136b3aaa338fb7d06d7be9e50bb42fc82821`. | **Approved within stated scope** at the named approved revision. PR #171 remains open/draft/unmerged. The later current blob contains approval/status administration; it must not be described as a separately approved new architectural revision. | Parent foundation for Document 01, the PR #171 research package, and subsequent whole-system / Brain-first planning. It defines project principles and the no-implementation boundary; it does not itself complete the architecture. |
| PR #171 — Document 01, `01_JARVIS_WHOLE_SYSTEM_ANATOMY_AND_RESPONSIBILITY_MAP.md` | Approved revision: commit `f32d2c9ede71676759b55c87c783253bd23ebbae`, blob `15c9bfc06f5f094d396f8a9dc625c22ac0d1b279`; Director approval comment #6556276653. Fetched current PR head `b05434758ad4fe72815503f89bd5d2990ccb658b`, current blob `2b595af4fefb54c7f8dc81fb997d4d391f2250e0`. | **Approved within stated scope** at the exact approved revision. PR remains open/draft/unmerged. Current administrative successor is not a fresh approval of changed architectural content. | Depends on Document 00. Provides the whole-system SYS-01–SYS-11 functional responsibility map and ownership boundaries. It is a functional anatomy, not a completed computational/runtime architecture. Brain-specific work must remain subordinate to this whole-system scope. |
| PR #171 — Comparative Brain Foundation Research Log | Current PR #171 head `b05434758ad4fe72815503f89bd5d2990ccb658b`; blob `f84077179f9fa8e151b5faca39940e43a13db2a2`. | **Working research / provisional**, not an approved architecture. PR #171 remains open/draft/unmerged. | Depends on the approved foundation as research framing; supplies comparative evidence, alternatives, assumptions, and unresolved questions to later Brain architecture. Length or inclusion in the approved-documents PR does not confer approval. |
| PR #171 — Brain Foundation Mechanism Gap Analysis | Same PR #171 head; blob `a90204f28c09dd9c1e2e0e1b24d108a58dc82b46`. | **Working research / provisional**. | Companion to the comparative research log; identifies representational, perceptual-grounding, integration and learning gaps. It informs subsequent research/specification but is not itself a specification or acceptance decision. |
| PR #172 — Foundational Brain Capability Investigation | Accepted exact head `d7d676b79dbf3269f7fd3ebdb4363a6df19f255d`; report blob `410edf234f79d9a370fb63deffaaf22cfed9ec9c). Director acceptance and authorization of the next planning stage recorded in PR #172 comment #6598249449. | **Accepted planning input**. PR #172 remains open/draft/unmerged. Its report is not an architecture specification. | Explicitly based on PR #171 approved foundation and main engineering baseline `1273ddbcd0087d189e01388ded2d362fb1e058d2`. It informs PR #173 Brain Foundation Architecture Planning. Test source was inspected, not executed; no runtime learning capability is established by this report. |

### 3.2 Brain Foundation Architecture and mechanism specification

| Artifact / lineage | Exact revision and content identity verified | Authority and live status (2026-11-18) | Dependencies / consumers and boundary |
|---|---|---|---|
| PR #173 — Brain Foundation Architecture | Historical proposal/initial inspection: `97191111bc2573c14d391c0af9628db7b11f194b`. Director accepted BFA-C01–BFA-C14 only at exact PR #173 HEAD `f8dd67fc866242d29298ffc6a03a8782a4e6982c`, matrix blob `4f297f7da7c8d9c8b0312bcc32dba353bcc0be66`, in comment #6894239520. Current live PR #173 HEAD: `a96af5b18d3a1d580ff56cff6191240893bceeb5`; architecture blob `cc4922ac0973ad7aaeee4b2b43d2ec93193f54e6`. | **BFA-C01–C14 accepted as discrete decisions only. Whole architecture remains proposed/unaccepted.** PR #173 is open/draft/unmerged. xAI returned **PARTIALLY CLEAR** against exact earlier HEAD `1f137cbaed985821bbc32408151911b18418f713` (comment #6950255396); that verdict does not assess current HEAD `a96af5b...`. | Depends on accepted PR #172 capability investigation and PR #171 whole-system foundation. It is the proposed Brain-level architecture input to PR #174 and later Phase 2 mapping. CF-26 and CF-27 remain open; whole-architecture Director acceptance, Stage A and implementation are not granted. |
| PR #173 — Completion and Decision Matrix | Current PR #173 HEAD `a96af5b18d3a1d580ff56cff6191240893bceeb5`; blob `0ba7c132152128319d14e72b49a7bd1a56985f45`. | **Proposed completion/decision evidence**, not final acceptance. The matrix distinguishes accepted BFA-C01–C14 from outstanding CF-26/CF-27 and architecture-wide gates. | Authoritative traceability companion to the proposed PR #173 architecture. Must be read at the same exact revision as the architecture, not mixed with earlier matrix snapshots. |
| PR #173 — Inherited Mechanism Source Compatibility Audit | Current PR #173 HEAD `a96af5b18d3a1d580ff56cff6191240893bceeb5`; blob `50269e8159c58ed4b30f11a463f4ab72fc0727ea`. | **Scoped source-compatibility inventory complete as a planning artifact; CF-26 overall remains OPEN.** Director selected Option A in comment #6899575912. The inventory is not runtime compatibility proof. | Compares approved engineering baselines and PR #97 donor lineage; records mechanism-level PRESERVE / ADAPT / REPLACE / DEFER dispositions and seven remediation/evaluation outputs. Consumed by the PR #173 architecture/matrix and independent re-review. No build or runtime tests were executed for this inventory. |
| PR #173 — CF-26 remediation/evaluation specifications | At PR #173 current HEAD `a96af5b18d3a1d580ff56cff6191240893bceeb5`, specification blob `53bb15edc1060297f1c0279fc548fc46c1898eb7` at current PR #173 HEAD `a96af5b18d3a1d580ff56cff6191240893bceeb5` (identified in Builder continuation comment #6909874390). | **Specifications authored; independent challenge pending; CF-26 overall OPEN.** | Seven architecture-level remediation specifications consume the source-compatibility inventory. The current file was re-fetched at the live PR #173 HEAD for this reconciliation; its current blob is recorded above (the earlier Builder continuation comment #6909874390 recorded the preceding blob at an older PR #173 head). They define ownership, lifecycle, failure/recovery, evaluation and acceptance requirements. They do not select implementation technologies or authorize code/tests. |
| PR #174 — Integrated Brain Mechanism Specification | Historically accepted baseline: exact HEAD `0811a59e46bf934e32e794f90e4e7d18d4e2bd97`, accepted by Director comment #6604790481. Current live PR #174 HEAD: `c34472354e4122fc1d78dc25bf45d81f1eb4dc69`; current specification blob `cfdda9e6e7070cd5533b076e9bd77c2904694a32`. | **Historical baseline accepted; current expanded proposal is not separately accepted.** xAI returned **PARTIALLY CLEAR** against earlier exact HEAD `7cb6271531f3e80a45728756273218132499722e` (comment #6896098398). The current `c344723...` successor has no verdict inherited from that review. | Depends on PR #173 Brain architecture. The accepted `0811a59...` baseline remains valid for its scope; the current expanded proposal includes 54 scenarios and follow-on F-02/F-03 corrections. Preserve this two-revision distinction. The later proposal is used as a non-operative planning source by PR #175, not as a silently substituted accepted baseline. |
| PR #174 — Existing Mechanism Source Audit | Current PR #174 HEAD `c34472354e4122fc1d78dc25bf45d81f1eb4dc69`; blob `4479874476715fd59a4c3ba6c908f06c43a1c6c2`. | **Static source audit / supporting evidence**, not implementation proof or independent review. | Supports the mechanism specification by describing the engineering baseline `1273ddbcd0087d189e01388ded2d362fb1e058d2`. Keep its source baseline distinct from later donor and Phase 2 branch snapshots. |
| PR #174 — Independent technical re-review | Report blob `de3bf393d5fedf0d80f75bc09250f0244ad6f176` at current PR #174 head; report targets exact HEAD `7cb6271531f3e80a45728756273218132499722e`. | **PARTIALLY CLEAR for that exact earlier target only**. Original F-02/F-03 review provenance is recovered as a source transcription/pointer; it is not a verbatim immutable reviewer export. | Review evidence informs corrections to current proposal. It does not accept the current proposal or authorize implementation. |

### 3.3 Implementation planning, donor evidence, and whole-Brain Phase 2

| Artifact / lineage | Exact revision and content identity verified | Authority and live status (2026-11-18) | Dependencies / consumers and boundary |
|---|---|---|---|
| PR #175 — Brain Implementation Roadmap | Current PR #175 HEAD `4d0cfe729e64c718dd4f21ba95a0167166252e6e`; plan blob `9511cda1389e47c94dcaf9373423570d8177a3c7`. | **Proposed / non-operative planning**, PR open/draft/unmerged. Gate A remains NOT CLEARED; no implementation baseline selected; Gate B not passed; no implementation authorization. | Historically derives from accepted PR #174 baseline `0811a59...` and the PR #173 architecture planning lineage. Its present supplementary planning also references the expanded, unaccepted PR #174 proposal `c344723...`; these sources must remain separately labelled. |
| PR #175 — Parallel Non-Operative Planning Supplement | Current PR #175 HEAD `4d0cfe729e64c718dd4f21ba95a0167166252e6e`; blob `a8c8ff0ca1ef6a7008e206662e05a202ffa743fe`. | **Narrowly authorized, non-operative planning only**, under the Director's 2026-11-17 exception recorded in PR #175 discussion. | Organizes BM-01–BM-12 dependencies, eight proposed increments, work-package definitions and verification portfolio. It does not activate work packages or authorize implementation. |
| PR #175 — Capability-to-Acceptance-Scenario Traceability Matrix | Same current PR #175 HEAD; blob `faa2b88947cdd9604e4a0c2d240d931926425a57`. | **Non-operative proposed planning artifact.** 54 rows are structurally mapped; no scenario is thereby passed. | Maps the 54 scenarios in current proposed PR #174 HEAD `c344723...` to BM-01–BM-12 owners, increments I0–I7 and minimum evidence classes. Five owner-boundary clarifications were recorded in comment #6963723759. |
| PR #156 — Developmental Brain donor | Live HEAD `7fe212bbb0bd61116ea56581435e03b06c69b673`; open/draft/unmerged; base `integration/knowledge-composition-20261031`. | **Unmerged candidate donor; not selected baseline.** | Contains developmental Brain implementation and supporting plan. PR #175 records PR #156 as a conditional/selective donor only. No wholesale donor adoption, cherry-pick or integration is authorized. |
| PR #176 — Gate A D1/D2 donor corrections | HEAD `4cf017e073da980c9f77d739fde6f92ef1a2fbc1`; open/draft/unmerged; base `integration/priority-one-20261031`. | **Separate donor-correction evidence; unmerged and not integrated.** | Relates to PR #156 donor defect evidence. Its test results, if any, apply to that donor branch/revision and cannot be attributed to main, PR #173, or a future integrated Brain. |
| PR #178 — JARVIS Project Governance Rules | HEAD `39fe09dcf13496f5f0005ccf3f00739303e29f88`; open/draft/unmerged; base `main`. | **Proposed / unaccepted branch snapshot.** | Governance predecessor in the PR #179 Phase 2 documentation lineage. Do not conflate this draft with PR #196's separately accepted governance amendment. |
| PR #179 — Phase 2 Whole-Brain Capability-to-Source Integration Map | HEAD `ea64607ef94f142a6142a013e119a7225bc95c1c`; blob `a703e96c9aa813324b9b607300fa1dc9030d2307`; open/draft/unmerged; base PR #178 branch. | **Working Phase 2 integration map; Phase 2 not accepted.** Gate A NOT CLEARED; Gate B not cleared. | Consumes the accepted PR #174 historical specification baseline and PR #173 Brain planning inputs while reconciling the whole-Brain capability map to actual source. It is a Phase 2 planning/integration map, not proof of complete implementation or a selected runtime baseline. |
| PR #180 — Overlapping Phase 2 research proposal | HEAD `6ca140300b914ed981a50301bbf1d82a5bfe4d8b`; closed/unmerged. | **Closed historical/overlapping proposal**, not canonical Phase 2 map. | Its overlapping report path was identified against PR #179. Preserve as history; do not treat it as a parallel current authority. |
| PR #188 — Phase 2 independent-review follow-up | HEAD `36b843f6959628a689d81bc1e12e523e17227073`; open/non-draft/unmerged; base main. | **Review report lineage**, not an independent formal review of PR #179 by a separate GitHub reviewer. PR #179 discussion records a self-review identity limitation. | Reports mainline persistence/state-consistency defects. No production code, tests or failure injections were changed/executed by that report. It is a defect-evidence input to Phase 2 reconciliation, not a gate pass. |
| PR #191 — Human/MCU comparison | Exact HEAD `609d38ede50bbdd98a93dfed112781eacabee9fd`; open/draft/unmerged; base historical PR #179 snapshot. | **Director disposition: retain as separate bounded reference artifact**, comment #6836333027. Not whole-Brain acceptance. | Human-cognition and MCU J.A.R.V.I.S. comparison is a bounded reference for BM-01–BM-12. Director explicitly prohibited replay/cherry-pick/rebase/retarget/merge or history rewrite absent a new decision. |
| PR #193 — Whole-Brain planning roadmap hold | HEAD `fa2bd50d6fb0bb77dc3cbaab684f51d606e94bb5`; open/draft/unmerged; base PR #175 historical snapshot. | **Hold / continuity documentation**, not an implementation authorization or accepted roadmap. | Records the separation between Brain implementation planning and the wider whole-Brain architecture. Keep its lineage separate from PR #192 and PR #179; no integration order is selected. |

### 3.4 Documentation Foundation and governance controls

| Artifact / lineage | Exact revision and content identity verified | Authority and live status (2026-11-18) | Dependencies / consumers and boundary |
|---|---|---|---|
| PR #192 — Documentation Foundation | Current PR #192 HEAD `3c9e512947412ea0ca8776a77b2e0e71c0f7af42`; open/non-draft/unmerged; base branch `docs/jarvis-phase-2-whole-brain-integration-map-20261105`, base SHA `61311fe5b44c81c4409c8ba8dc581a83bdd5dd2c`; 42 changed paths. | **Documentation Foundation not accepted.** xAI review PARTIALLY CLEAR at prior exact HEAD `beb4d5a...`; current successor not reviewed. DF-02 OPEN; DF-06 NOT MET; DF-09 NOT MET; DF-11 WAIVED; DF-12 pending Director; Stage A held. | Depends on the existing PR #179 Phase 2 documentation lineage and preserves multiple prior branches/artifacts without merging them. PR #192 base SHA is a historical snapshot and must not be assumed to equal the current base-branch head. |
| PR #192 — Planning Documentation Index | Current PR #192 HEAD; blob `6c61e6abb2de4e099c21d9eac0ea9f049988cd48`. | **Controlling navigation/status index for this Documentation Foundation proposal**, not Director acceptance. | Links the inventory, preservation register, reports and planning artifacts. Its current-status block must distinguish live metadata from historical snapshots and must not overstate exact-revision review coverage. |
| PR #192 — Historical Documentation Preservation Register | Current PR #192 HEAD; blob `95cd280295c86c6d33278aa667de1d72048026ea`. | **Preservation evidence**, not disposition approval. | Provides immutable locations and lineage references for prior documentation. It does not by itself establish semantic authority or authorize moving/deleting artifacts. |
| PR #194 — Documentation Foundation AI reader workflow predecessor | HEAD `9b457e35c601719d9b213fb843dd5876976b35b9`; closed/draft/unmerged; base main snapshot `73a4deb7e532277e390da6a1d7d2c81be26b63bb`; changed path `.github/workflows/documentation-foundation-ai-reader.yml`. | **Closed without merge; historical workflow proposal.** | Separate predecessor to the later PR #195 workflow correction. Its unmerged workflow file must not be treated as deployed/active mainline behavior; PR #195 is the merged correction lineage. |
| PR #195 — AI role terminology / documentation reader workflow correction | Merged into `main` at merge commit `4f07d772beae03c99a8dd58b174201a3aa3074b2`; PR closed/merged. xAI workflow review was against exact earlier HEAD `6b8e6fce342397b17f0ed237ccc5a09fb38034df`, verdict APPROVED WITH DOCUMENTED NON-BLOCKING ISSUES; report-only successor is separate. | **Merged into main.** F-195-07 live negative-path evidence remained open in the review record. No automatic DF-09 or DF-12 clearance. | Supports Documentation Foundation review tooling and terminology. The merged workflow source is available on main, but static review is not evidence that all negative-path executions were run. |
| PR #196 — Builder Operating Controls / project governance amendment | Accepted governance content blob `9c17d2870047cc1d58afea745cd7160d15e216c3`; Director acceptance record comment #6833435191; independent verification comment #6833511900. Merged into the existing Phase 2 base branch at `c151e52781e56e6481424f774c19ea30128debb0`, not main. | **Accepted project-wide governance standard; merged into the Phase 2 base branch only.** | Governs Builder process and authorization boundaries. It does not accept the Brain architecture, clear Gate A/B, authorize runtime implementation, or merge PR #192 into main. |

### 3.5 Earlier proposal chain and legacy main-branch artifacts

| Artifact / lineage | Exact revision / evidence verified | Authority and status | Dependencies / disposition |
|---|---|---|---|
| PRs #166–#170 | Live heads: #166 `c803e9873df1c22111156d894853ef2d8832a8ea`; #167 `e7227919c13cc65c0e3915fdc7b6491465be1921`; #168 `004e8753d01c9b18bb243b257591657f9b19d7db`; #169 `bdc980f3dcf322541556c0756aeee4eb1ff955a1`; #170 `abf3303c04638a89146a4161b91a439910235add`. All open/draft/unmerged; they form a chained proposal lineage. | **Proposed / unaccepted** language ownership, polyglot rules, MCU target analysis, and constitution/readiness materials. | Preserve as prior planning inputs. Their draft branch sequence is not authority to impose Brain-only language or layer constraints on whole JARVIS. Reconcile useful content with approved whole-system ownership and later architecture; no silent adoption. |
| Main-branch Brain Master Blueprint | Main baseline `1273ddbcd0087d189e01388ded2d362fb1e058d2`; blob `9958b8a596e172488b21fce1cdc256ccde419cfe`. | **Existing main-branch planning document; authority beyond its stated “Architecture/build plan” status is not established by its title.** | Layer 0–19 construction plan. Must be reconciled with whole-system architecture and later Brain decisions before treating layer order or content as binding. |
| Main-branch `docs/ARCHITECTURE.md` | Same main baseline; blob `819544194e080f1210a32efc05867c6220f9e6fd`. | **Existing high-level architecture summary; authority/currentness requires reconciliation.** | Summarizes cognitive flow, continuity, learning and evolution. Keep as historical/current-main evidence until link and authority audit determines its relationship to approved Document 00/01 and newer planning. |
| Main-branch `docs/JARVIS_PHASE_2_COMPLETION.md` | Same main baseline; blob `7e001e63703bf07efe95c321c1f6c4272ae626f7`. | **Historical completion declaration on main; not sufficient evidence of current Phase 2 acceptance.** | Its stated Perception & Representation completion is bounded to its recorded scope. It must not override the later whole-Brain Phase 2 map, outstanding persistence findings, or Gate A/B status. |
| PR #156 donor `DEVELOPMENTAL_BRAIN_PLAN.md` | PR #156 live head `7fe212bbb0bd61116ea56581435e03b06c69b673`; PR open/draft/unmerged. Historical inventory records the file at blob `1db14e73ecc4ff4fded2791df17f34d20958c329` in a prior donor checkpoint. | **Historical donor planning artifact; not selected baseline.** | Retain as donor evidence and compare only under the PR #173/PR #175 compatibility and Gate A process. The prior blob SHA is not a current-head blob verification. |

### 3.6 Additional inherited documentation present in the PR #192 base snapshot

A recursive Git tree was fetched for exact PR #192 HEAD `832a7734001937330856e8bcc980dd6044c1c201`. The response was complete (`truncated=false)): 244 tracked files total, of which 48 were repository documentation paths (`README.md` plus `docs/**`). The 43 PR #192 changed paths are all within that documentation set. Five additional documentation artifacts are inherited unchanged from PR #192's recorded base snapshot and therefore do not appear in the PR changed-path manifest:

| Inherited artifact | Exact branch-snapshot blob | Authority / status | Dependency and reconciliation |
|---|---|---|---|
| `docs/architecture/inventory/PHASE_1_PR97_DONOR_CAPABILITY_TRACEABILITY_2026-11-05.md` | `0b54de626cc6bd5dff049ac60dbec14cee756144` | Static traceability report, explicitly limited to selected PR #97 donor capabilities; not an exhaustive 159-path audit, build/test rerun, independent review, merge approval or implementation authorization. | Uses PR #97 donor HEAD `c1da222e6c94aeb3f2ad000392c21fe4fc81ab25`; informs Phase 1 reuse/compatibility analysis. Its donor findings must not be presented as current mainline runtime behavior. |
| `docs/architecture/inventory/PHASE_1_TRACKED_FILE_INVENTORY_2026-11-05.md` | `f199526e81c462a9855f1a3fe02ae76edc19c4f1` | Exact-baseline inventory generated from recursive Git tree at main baseline `1273ddbcd0087d189e01388ded2d362fb1e058d2`; reports 200 tracked blobs at that historical baseline. | Structural source inventory underpinning Phase 1 investigation. It is not a live inventory of the current PR branch or a substitute for semantic authority/dependency reconciliation. |
| `docs/architecture/reports/PHASE_2_DONOR_RUNTIME_RELIABILITY_ACCEPTANCE_CONTRACT_2026-11-06.md` | `3abf1fb93009a1de79942bea5aad4d8ff2f037e3` | Documentation-level acceptance contract; implementation and execution tests explicitly remain unauthorized by its stated Phase 2 boundary. | Derives from PR #97 donor source and Phase 2 findings P2-I-023, P2-I-028, P2-I-029, P2-I-030, P2-I-035, P2-I-036 and IR-03. It defines evidence/acceptance expectations; it is not proof those controls are implemented or tested. |
| `docs/architecture/reports/PHASE_2_PROJECT_DIRECTOR_CLOSURE_DECISION_PACKET_2026-11-06.md` | `715b123fe09e4b33f2e8fb2e23b3cf04680b44d2` | Decision packet prepared for the Project Director; its own header explicitly says it is not an approval record. | Points to PR #179 Phase 2 working report, accepted historical PR #174 specification baseline `0811a59...`, and main source baseline `1273ddb...`. Do not infer a closure decision from the existence of the packet. |
| `docs/governance/JARVIS_PROJECT_GOVERNANCE_AND_BUILDER_RULES.md` | `e4315956cfb1ed075b508af3053601fed345f0a5` | Inherited PR #192 base-snapshot version labels itself a proposed project-wide governance baseline. | PR #196's later accepted governance amendment is a separate artifact/revision merged into the Phase 2 base branch at `c151e52781e56e6481424f774c19ea30128debb0`. PR #192's recorded base SHA `61311fe...` predates that merge and this branch snapshot does not contain the later merged amendment. Do not claim the PR #192 branch already includes PR #196's accepted governance content; the current base branch has advanced beyond the PR's recorded base snapshot. |

The tree census is complete for the exact PR #192 branch snapshot and resolves the five unchanged inherited documentation paths. It does not establish a complete cross-branch census: artifacts that exist only on PR #171–#196 branches, historical commits, donor branches, or other refs are not all represented in this one tree. The principal lineage table and explicit remaining-work section continue to delimit that outstanding scope.

### 3.7 Separate Phase 2 research, closeout and independent-review branches (#181–#190)

The following live PR metadata and exact branch-head documents were inspected because they form a parallel Phase 2 evidence lineage not fully represented by the PR #192 branch tree. These are not additional approvals of PR #179 and must not be collapsed into one canonical report.

| PR | Exact head / base and document identity | State and authority | Dependency / disposition |
|---|---|---|---|
| #181 — initial Phase 2 research map | HEAD `cf3f8db7e5e5ca5eb1c0345bafdb704e92d70f25`; base PR #174 accepted baseline `0811a59e46bf934e32e794f90e4e7d18d4e2bd97`; report blob `82f7479bc0bc9170932b7b6e8d0eb989d94d965b`. | Open/draft/unmerged; static investigation report, not implementation plan or authorization. | Early Phase 2 capability-to-source map. PR #179 is the later whole-Brain integration map lineage; #181 remains historical research evidence, not the current canonical Phase 2 report. |
| #182 — source challenge of #181 | HEAD `1ffc2d66c3c0b389eaddae992318d53eeab8416b`; base PR #181 head `cf3f8db7e5e5ca5eb1c0345bafdb704e92d70f25`; review blob `7eeea7907e8bf79bfccc9e0871568e6a55ab8558`. | Open/draft/unmerged; adversarial source challenge, not an approval. | Targets exact PR #181 head/report blob. Its challenge supports the decision to expand and correct the Phase 2 map; it is not a verdict on later PR #179 revisions. |
| #183 — first independent Phase 2 review | HEAD `30eaefe3bee02e2038f66fb18c907673026ebe76`; base main `1273ddbcd0087d189e01388ded2d362fb1e058d2`; review blob `8f82c3a4a1e4457ff4c65d2c86e7e42be8e3397d`. | Open/non-draft/unmerged; verdict **REVISE**. | Reviews PR #179's earlier Phase 2 map and identifies material omissions in main perception call-path integration, preservation of distinct PR #174 follow-on findings, donor runtime fairness/shutdown/result handling, and human/MCU comparison ownership. |
| #184 — second independent Phase 2 corrections review | HEAD `8ba6dfcb17f2aab409f58cbd8bc57898edd60405`; base main `1273ddbcd0087d189e01388ded2d362fb1e058d2`; review blob `8340a149206a92a7060c61931adfb4d27f80e636`. | Open/non-draft/unmerged; verdict **REVISE**. | Targets PR #179 head `6f2c2cf05196e69a48f5deefcc3f4609e258c19a` and report blob `cc772cf571a7f9bf3ee3df2c1e392a8a392903a3`. IR-01 documentary correction, IR-03 source analysis/acceptance criteria and IR-04 ownership correction were assessed positively; IR-02 provenance/Director authority remained partial, human/MCU comparison remained outstanding, and tests remained unexecuted. This is not Phase 2 acceptance. |
| #185 — Phase 2 closeout evidence/contracts | HEAD `cb7b0877bcdd82b88dd387c99a9442997e0220ce`; base Phase 2 branch snapshot `6f2c2cf05196e69a48f5deefcc3f4609e258c19a`. Blobs: donor reliability contract `377952cc08d2e16e89e420290180628c24827232`; human/MCU comparison `d7a1f6c7ad52bae4b89c34dd8a3c0b9540a91f9f`; Phase 2 map `a703e96c9aa813324b9b607300fa1dc9030d2307` (at PR #179 current head this map has a different blob). | Open/non-draft/unmerged; documentation closeout preparation, not closure approval. | Contract explicitly prohibits implementation/tests under its then-current review boundary. Human/MCU comparison was awaiting independent review and Director disposition. This branch is based on an earlier PR #179 snapshot, not the later current PR #179 head. |
| #186 — Phase 2 closeout evidence and review handoff | HEAD `53278d5918163b286247f608efcadd5ef0afd232`; same historical base snapshot `6f2c2cf05196e69a48f5deefcc3f4609e258c19a`. Blobs: alternate donor runtime reliability contract `a5ec880b6ec2c856bc5a3085eddce618abcc6dc9`; human/MCU comparison `d7a1f6c7ad52bae4b89c34dd8a3c0b9540a91f9f`; Phase 2 map, PR #174 provenance recovery and closeout handoff are additional changed artifacts. | Open/non-draft/unmerged; separate closeout/handoff proposal. | Contains an alternate filename/version of the donor reliability contract relative to PR #185. The overlapping files and branch snapshots must be reconciled explicitly; neither branch is assumed merged or authoritative over the other. |
| #187 — IR-02/03/04 builder follow-through | HEAD `8e18f5eb2f8921e4bcd5d8441d432b5923d28da8`; same historical base snapshot `6f2c2cf05196e69a48f5deefcc3f4609e258c19a`. Blobs: fairness/recovery test contract `4dcb63afc3db9e7a10ffee97e6ffb399ca4154de`; human/MCU comparison and Phase 2 map are also changed. | Open/non-draft/unmerged; proposed builder follow-through, not test execution or acceptance. | Its fairness/recovery contract is explicitly preparation only; no runtime source changed and no test was executed. It is a distinct successor branch, not a merged replacement for #185/#186. |
| #188 — independent Phase 2 follow-up review | HEAD `36b843f6959628a689d81bc1e12e523e17227073`; base main `1273ddbcd0087d189e01388ded2d362fb1e058d2`; review blob `1b9c691d80a315e2d13bf95975644e895c8495da`. | Open/non-draft/unmerged; the document presents a **REVISE** follow-up assessment, but the PR #179 discussion records a reviewer-identity limitation; do not count this as a qualifying independent-review clearance. | Adds mainline persistence/state-consistency findings: live Brain state may mutate before event append succeeds; journal rollback/malformed-tail repair has weaknesses. These are conditional source-derived failure paths, not reproduced incidents or test results. |
| #189 — independent review of the whole-Brain map | HEAD `46796725fd656628f7b6e47a57929b87f79a6d8d`; base main `1273ddbcd0087d189e01388ded2d362fb1e058d2`; review blob `870481186434027414ba35a90cf8833810b1e527`. | Open/non-draft/unmerged; verdict **REVISE**. | Reviews the PR #179 Phase 2 map against pinned source, specification, governance and PR #180; it is a separate independent assessment, not a current PR #179 approval. |
| #190 — third independent Phase 2 review | HEAD `a1df22531765b7022f6bfbcfd9f3f5251cf5adf5`; base main `1273ddbcd0087d189e01388ded2d362fb1e058d2`; review blob `d3c3e79f38e90a86968261578eaebaf3194d2387`. | Open/non-draft/unmerged; independent review artifact, not acceptance. | Targets PR #179 exact head `6f2c2cf05196e69a48f5deefcc3f4609e258c19a`. Its review is historical and does not assess the later current PR #179 head. |

The review-document titles and verdict labels are recorded as artifact content, not as independent-review qualification. In particular, PR #188 is not counted as a qualifying independent reviewer because its reviewer-identity limitation is recorded in PR #179 discussion. These PRs demonstrate why PR #192's own tree census is not a complete historical/cross-branch census. In particular, PRs #185–#187 are parallel closeout branches sharing an earlier PR #179 base and overlapping file paths with differing document versions. PRs #183, #184, and #188–#190 are independent review documents on main-based branches. Their verdicts are bounded to the exact PR #179 snapshots stated in their headers. The later PR #179 head and current Phase 2 disposition must be checked separately before any of these findings can be treated as closed.

### 3.8 Earlier Brain planning and governance proposal chain (#166–#170)

These chained proposals are separate from the approved whole-system foundation in PR #171 and the later PR #173/#174 planning line. All five PRs were live open/draft/unmerged at the inspected heads; no Director acceptance of the current contents was identified in the decision records used for this reconciliation.

| PR | Exact head, base and principal artifact blob | Authority and dependency |
|---|---|---|
| #166 — project command and role governance | HEAD `c803e9873df1c22111156d894853ef2d8832a8ea`; base `integration/priority-one-memory-bool-hardening-20261031` @ `b627dcc6a0ec849386425c785ba567ff2d2198dc`; `docs/JARVIS_PROJECT_GOVERNANCE.md` blob `a02befaffdbbd7cabee1ce4fa0bc2342e3409ecf`. | Open/draft/unmerged; proposed role/command governance. Its branch-specific README and governance text do not override later accepted PR #196 governance controls or the approved whole-system foundation. |
| #167 — Brain layer-to-language ownership | HEAD `e7227919c13cc65c0e3915fdc7b6491465be1921`; base PR #166 head `c803e9873df1c22111156d894853ef2d8832a8ea`; `docs/BRAIN_LAYER_LANGUAGE_OWNERSHIP_MAP.md` blob `003915f52d778e5374af2566958469e50710d617`. | Open/draft/unmerged; document explicitly proposed and scoped to Brain only, not whole JARVIS or future device/deployment ecosystem. Not an approved whole-system language allocation. |
| #168 — Brain polyglot engineering governance | HEAD `004e8753d01c9b18bb243b257591657f9b19d7db`; base PR #167 head `e7227919c13cc65c0e3915fdc7b6491465be1921`; `docs/BRAIN_POLYGLOT_ENGINEERING_GOVERNANCE.md` blob `3c7c72a6e70c93fad76068d989ff2bb4d882c129`. | Open/draft/unmerged; explicitly proposed and subject to independent review/owner approval. Applies to Brain foundation only and does not authorize wider product/device/deployment implementation. |
| #169 — MCU behavioral reference and Brain target | HEAD `bdc980f3dcf322541556c0756aeee4eb1ff955a1`; base PR #168 head `004e8753d01c9b18bb243b257591657f9b19d7db`; `docs/JARVIS_MCU_BEHAVIORAL_REFERENCE_AND_BRAIN_TARGET.md` blob `4d3d45f63e2cf5b231e94f4684867654d59db0ed`. | Open/draft/unmerged; research-backed target analysis and proposed foundation specification, explicitly not approved. It informs Brain-first planning but does not replace whole-system scope. |
| #170 — Brain constitution and planning readiness | HEAD `abf3303c04638a89146a4161b91a439910235add`; base PR #169 head `bdc980f3dcf322541556c0756aeee4eb1ff955a1`; principal blobs: layer 0–19 traceability matrix `e354332be06d17dba87fcf85deb5868aa2277f74`; planning review reconciliation `64d62c3f70290d583bab5467b09ecf6a44a8925b`; Brain foundation constitution/readiness `fe0488878a305346538a71b5c2bad3c5fd225cdb`; proposed branch master blueprint `11eb3d3abbba94116e5f4d1288856495ea0ac9e4`. | Open/draft/unmerged; proposed consolidation/traceability/readiness package, explicitly requires independent review and Project Director approval. The branch blueprint is a separate historical version from main's `docs/JARVIS_BRAIN_MASTER_BLUEPRINT.md` blob `9958b8a596e172488b21fce1cdc256ccde419cfe`; neither the PR #170 title nor its presence establishes acceptance. |

This chain is sequentially based (#167 on #166, #168 on #167, #169 on #168, #170 on #169). It must be treated as one historical proposal lineage, not five independent approvals. Its Brain-only language and governance constraints remain proposed; later whole-system architecture and accepted governance decisions control where they explicitly supersede or constrain these proposals.

## 4. Dependency and authority graph

The principal planning dependencies, without implying merge or automatic approval, are:

```text
Main engineering baseline (1273ddb...)
        │
        ├── PR #171 Document 00 (approved exact scope)
        │       └── PR #171 Document 01 (approved exact scope)
        │               └── PR #171 comparative research + gap analysis (working research)
        │                       └── PR #172 capability investigation (accepted planning input)
        │                               └── PR #173 Brain Foundation Architecture (proposed)
        │                                      ├── BFA-C01–C14 (accepted decisions only)
        │                                      ├── CF-26 compatibility/remediation (OPEN)
        │                                      └── CF-27 exact-revision decision ledger (OPEN)
        │
        ├── PR #174 mechanism specification
        │       ├── accepted historical baseline 0811a59... (planning baseline only)
        │       └── expanded current proposal c344723... (not separately accepted)
        │
        └── PR #156 donor evidence ── PR #176 donor corrections (separate/unmerged)

PR #173 + accepted historical PR #174 baseline
        └── PR #179 Phase 2 whole-Brain capability/source map (not accepted)
                 ├── PR #191 bounded comparison (retain separately)
                 ├── PR #196 accepted governance amendment (merged into this base)
                 └── PR #192 Documentation Foundation proposal (base snapshot is historical)

PR #175 Brain implementation roadmap (non-operative / Gate A NOT CLEARED)
        ├── consumes accepted historical PR #174 baseline
        ├── references expanded PR #174 proposal only as proposed source
        ├── parallel non-operative supplement + 54-scenario matrix
        └── PR #193 roadmap hold / continuity branch (separate lineage)
```

The graph represents content dependencies and planning relationships, not a Git merge graph. PR #192 and PR #193 remain separate lineages. PR #196's merge target is the existing Phase 2 base branch, not `main`. PR #195 is a separate merged workflow/terminology correction on `main`.

## 5. Reconciliation findings and corrections required in the controlling inventory

1. **PR #173 authority must be stated at two levels.** The Director accepted BFA-C01–C14 at exact revision `f8dd67f...`; that did not accept the whole architecture. The latest xAI verdict is PARTIALLY CLEAR at `1f137cb...`, and the current live PR head `a96af5b...` is a later successor. Do not label the current whole architecture accepted or carry the prior review verdict forward.
2. **PR #174 has two valid but different authority states.** The exact historical baseline `0811a59...` was accepted. The expanded current proposal `c344723...` has not been separately accepted; its earlier xAI review was PARTIALLY CLEAR at `7cb6271...`. The header is not a contradiction when it accurately distinguishes historical acceptance from current proposal.
3. **PR #172 acceptance is exact and scoped.** The accepted capability investigation report is a planning input; PR open/draft state does not negate that decision, and the decision does not accept the architecture that followed.
4. **PR #171 approvals are document-specific.** Document 00 and Document 01 have separate exact-revision approvals. The PR #171 research package remains working research; current administrative successor blobs do not retroactively expand those approvals.
5. **PR #175 planning work remains non-operative.** The 54-row matrix maps the expanded PR #174 proposal, which is explicitly unaccepted. Structural completeness does not pass scenarios, clear Gate A/B, select a source baseline, or authorize implementation.
6. **PR #179 is not a phase acceptance.** It remains open/draft/unmerged, and its source integration map records unresolved persistence/recovery and independent-review obligations. A successful Configure/Build-only CI run is not CTest or failure-injection evidence.
7. **PR #191 is a separate bounded reference by Director disposition.** Its historical base and explicit no-rewrite instruction must be preserved.
8. **PR #195 and #196 have distinct merge targets and effects.** #195 merged into main; #196 merged into the existing Phase 2 base branch. Neither clears architecture gates or authorizes implementation.
9. **Legacy main docs remain present.** Their continued presence is preservation evidence, not proof of current authority. PR #192 proposed navigation updates are not yet merged.
10. **The donor lineage remains unselected.** PR #156 and #176 are separate unmerged candidate/evidence branches. Do not treat their artifacts or tests as integrated mainline capabilities.
11. **Snapshot staleness is material.** PR #192's base SHA `61311fe...` is a recorded base snapshot, not a claim that the named branch still points there. All review/merge decisions must fetch current branch and PR metadata at decision time.

## 6. Remaining DF-02 work

This reconciliation now covers the complete PR #192 documentation tree, the PR #166–#170 Brain-planning proposal chain, the principal PR #171–#196 foundation/architecture/Phase 2/documentation lineages, and the identified parallel Phase 2 review/closeout branches #181–#190. It still does not satisfy DF-02. The remaining work is:

- Complete the historical branch/artifact census beyond the explicitly enumerated PR #156 and PR #166–#196 lineages, including earlier donor/implementation branches and standalone artifacts retained in the preservation register.
- A bounded exact-revision donor review is now recorded in §9: all 159 PR #97 changed paths are classified by subsystem, the critical learning loop and selected tests are inspected at exact blobs, and PR #156/#176 file overlap, ancestry and CI evidence are reconciled. Full per-file semantic disposition across all 159 PR #97 paths and a complete cross-file dependency/duplication graph remain outstanding.
- Resolve status/header/README claims across the relevant repository trees against exact authority records. This pass records the complete PR #192 documentation tree but is not a repository-wide semantic scan of every historical branch.
- Verify complete dependency/reference closure for every retained, superseded, or historical artifact, including all consumers on separate branches and exact current base/head relationships.
- Record explicit disposition for any remaining unresolved provenance claim rather than converting a transcribed/handoff claim into verified acceptance.
- Obtain independent verification of this register and the resulting inventory update. DF-02 remains OPEN until the remaining scope is complete and the evidence is accepted through the applicable process.

## 7. Explicit non-authorizations

This report does not authorize PR merge, rebase, retarget, cherry-pick, branch rewrite, archive relocation, deletion, source-baseline selection, Gate A/B clearance, Stage A, runtime implementation, runtime testing, technology selection, deployment, or Project Director acceptance. It records Builder-side source inspection and repository evidence only.

## 8. Primary repository decision/evidence pointers

- PR #171 Document 00 approval: https://github.com/methaneex-oss/MethaneX/pull/171#issuecomment-6555976534
- PR #171 Document 01 approval: https://github.com/methaneex-oss/MethaneX/pull/171#issuecomment-6556276653
- PR #172 accepted planning input: https://github.com/methaneex-oss/MethaneX/pull/172#issuecomment-6598249449
- PR #173 BFA-C01–C14 decision: https://github.com/methaneex-oss/MethaneX/pull/173#issuecomment-6894239520
- PR #173 CF-26 Option A: https://github.com/methaneex-oss/MethaneX/pull/173#issuecomment-6899575912
- PR #173 latest xAI re-review: https://github.com/methaneex-oss/MethaneX/pull/173#issuecomment-6950255396
- PR #174 accepted historical baseline: https://github.com/methaneex-oss/MethaneX/pull/174#issuecomment-6604790481
- PR #174 xAI technical re-review: https://github.com/methaneex-oss/MethaneX/pull/174#issuecomment-6896098398
- PR #191 Director disposition: https://github.com/methaneex-oss/MethaneX/pull/191#issuecomment-6836333027
- PR #192 exact-HEAD xAI review: https://github.com/methaneex-oss/MethaneX/pull/192#issuecomment-6963581974
- PR #196 governance acceptance: https://github.com/methaneex-oss/MethaneX/pull/196#issuecomment-6833435191


## 9. Donor lineage and learning-mechanism audit — exact revisions, 2026-11-18

This section narrows the donor-lineage gap using live PR metadata, complete changed-path listings, commit comparisons, exact-revision source reads, and exact-head CI evidence. It is a bounded audit, not donor adoption or acceptance.

### PR #97 — broad cognitive/affective learning baseline

- **Exact HEAD:** `c1da222e6c94aeb3f2ad000392c21fe4fc81ab25`; **base:** `4ba84b8b5ccf0e41530c46fdb8101551254ba864`; open, draft, unmerged; 159 changed paths.
- Changed-path classification: 8 workflow files; 35 core headers; 37 core source files; 56 core tests; 9 documentation files; 10 engineering files; 2 build-configuration files; 2 other files. The full exact path list remains available through PR #97's changed-files endpoint.
- Exact-head GitHub checks: `cpp-core`, `sanitizer`, and `native-brain` all completed successfully on 2026-10-28. This does not establish broad held-out learning quality or resolve the semantic defects below.
- The PR #97 learning-machinery audit comment is [issue comment #6521585791](https://github.com/methaneex-oss/MethaneX/pull/97#issuecomment-6521585791). It records the baseline as a learning-development stack, not a completed learning brain.

**Direct source inspection at PR #97 HEAD** confirms a real connected mechanism path rather than a disconnected set of modules:

| Mechanism | Exact source evidence |
|---|---|
| Pre-observation memory retrieval | `core/cpp/src/cognitive_cycle.cpp`, blob `f191dd610d6cbe1621756c35e7c13af2054a7266`: recalls prior observation memories and action-outcome memories before committing the current observation; uses salient episodic fallback when neither retrieval channel returns a match. |
| Prediction resolution from new experience | Same `cognitive_cycle.cpp` blob: captures unresolved forecasts made after the prior observation and resolves only against a matching belief updated by the newly committed observation. Action-consequence forecasts use a separate execution-feedback path. |
| Durable memory | `core/cpp/src/memory.cpp`, blob `ab42bba1d32d6f48d091787491c72294a4a55bb5`: append persists the event before updating in-memory metadata/continuity; ranked recall is implemented. |
| Runtime feedback | `core/cpp/src/cognitive_runtime.cpp`, blob `cf00acb6abd52308343f3a0e7016e6173b945603`: validates prediction/evidence/goal feedback, queues it, and routes it through `cycle_.process_outcome`; failed/stale updates are counted as failures, not successful processing. |
| Brain replay | `core/cpp/src/brain.cpp`, blob `dec9e5442b3ca4b81a7879855c6146b2619934cc`: constructor reloads journal history and replays events to reconstruct Brain state. |
| Experience-dependent learning | `core/cpp/src/developmental_learning.cpp`, blob `dbf5f43271dfa0a3c57236e2faa82eb88d15490d`: learning rate depends on prediction error, reward, salience, novelty, affective significance and reliability; association/strategy estimates update from observed reward and confidence. |
| Action-consequence integration | `core/cpp/tests/cognitive_runtime_learning_integration_suite.cpp`, blob `656de56b1368e40afb090778a7a5504ab4208056`, and `core/cpp/tests/brain_action_consequence_integration_suite.cpp`, blob `7616082579d53e3579cae8e87895bdb3dadba66f`: test resolved consequence predictions and resulting learning metrics. |
| Restart persistence | `core/cpp/tests/memory_learning_evolution_persistence_suite.cpp`, blob `98e6598f60912714234f2dfabfbe52fa5eb77044`: checks prediction resolution, learning observations, strategy evidence and evolution history after journal replay. |

**Confirmed limitations at this exact baseline:**

1. `CausalModel::observe_transition` in `core/cpp/src/causal_model.cpp`, blob `b7e1e6e6aeb929f09af33b9d17c80a6eed34948c`, uses the post-transition `current.value` as the cause rather than the pre-transition `prior->value`; it also iterates all post-state facts as effects, including unchanged facts. This creates invalid causal associations. The previously recorded PR #135 correction addresses pre-state cause semantics and excludes unchanged effects; do not attribute that fix to PR #97.
2. DLT-003 tests changing context/action mappings, reversal and restart, but all tested contexts are trained before evaluation. Held-out transfer to an unseen combination is not established.
3. DLT-002 prediction feedback plumbing does not establish improving prediction quality; the earlier long-run report recorded final MAE worse than early MAE. Require held-out error curves and regime-change evaluation before claiming predictive competence.
4. The PR #97 world model does not accumulate and compare support for competing fact/relation alternatives sufficiently to resolve contradictions; PR #148 supplies a later correction, not a capability already proven by PR #97.
5. Evolution replay is a supporting trust mechanism, not the learning objective. Production cryptographic trust configuration, key lifecycle, authenticated journal integrity and complete paired-trial evidence remain separate concerns.

### PR #156 — integrated knowledge/action/evolution replay candidate

- **Exact current HEAD:** `7fe212bbb0bd61116ea56581435e03b06c69b673`; **base:** `52c367a4b53fdfe9b29776795200555076e8cb49`; open, draft, unmerged; 8 changed paths.
- The PR #97 HEAD is an ancestor of PR #156's base: comparing `52c367a...` against `c1da222...` shows PR #97 is 172 commits behind that base. PR #156 HEAD is 185 commits ahead of PR #97 HEAD, with 22 net changed paths in that broader comparison. PR #156 is therefore a later descendant of the PR #97 development line, not an independent competing donor.
- PR #156's eight changed paths are: `core/cpp/include/jarvis/core/brain.hpp`; `core/cpp/src/brain.cpp`; `core/cpp/src/brain_restored_api.cpp`; `core/cpp/src/evolution_controller.cpp`; `core/cpp/tests/evolution_brain_integration_suite.cpp`; `core/cpp/tests/evolution_canary_controller_suite.cpp`; `core/cpp/tests/knowledge_source_feedback_suite.cpp`; and `docs/DEVELOPMENTAL_BRAIN_PLAN.md`. Six overlap PR #97's changed-path set; the knowledge-source feedback suite and plan are additional paths relative to PR #97.
- The PR description still cites older combined HEAD `da9d77361ae6f1e12fe47168d843b8bedfec6301`; live HEAD `7fe212b...` is 9 commits later, with a six-file delta from that cited snapshot. Do not use the stale body SHA as current.
- Four exact-head workflows completed successfully on `7fe212b...`: Native Brain Build [#41174439433](https://github.com/methaneex-oss/MethaneX/actions/runs/41174439433), Brain ThreadSanitizer [#41174439446](https://github.com/methaneex-oss/MethaneX/actions/runs/41174439446), Brain CI [#41174439557](https://github.com/methaneex-oss/MethaneX/actions/runs/41174439557), and JARVIS Brain Tests [#41174439423](https://github.com/methaneex-oss/MethaneX/actions/runs/41174439423). The JARVIS Brain Tests log records **73/73 CTest tests passed** on this exact HEAD.
- Its scope combines knowledge contradiction/evidence handling, compositional action-feature learning and evolution replay-evidence safeguards. Its own PR description preserves important non-claims: production cryptographic signature verification, protected evaluator trust configuration/key rotation/revocation, deterministic historical verification, cryptographic journal integrity, and end-to-end calibration of ordinary factual-source feedback into belief/world-model weighting remain unproven. The compositional action learner is not evidence that ordinary factual feedback changes the world model.

### PR #176 — D1/D2 and journal-failure correction candidate

- **Exact HEAD:** `4cf017e073da980c9f77d739fde6f92ef1a2fbc1`; declared **base branch:** PR #156, whose live HEAD is `7fe212bbb0bd61116ea56581435e03b06c69b673`; open, draft, unmerged; 4 changed paths.
- Changed paths: `core/cpp/src/brain_restored_api.cpp`; `core/cpp/tests/developmental_brain_integration_suite.cpp`; `core/cpp/tests/evolution_brain_integration_suite.cpp`; `core/cpp/tests/goals_architecture_suite.cpp`. Two overlap PR #156's changed paths; all four overlap PR #97's broader changed-path set.
- The Git graph is not a clean descendant relationship against the live PR #156 HEAD: comparing PR #156 HEAD to PR #176 HEAD reports divergence (PR #176 is 15 commits ahead and 1 behind; merge base `15d49e5fdeb5723c475922ab78fb92f97c4b3b84`). PR #156 itself is one commit ahead of that merge base, a documentation-plan update. The PR #176 branch must not be assumed to contain the live PR #156 tip simply because its declared base branch is PR #156.
- Four exact-head workflows passed: Native Brain Build [#41808525486](https://github.com/methaneex-oss/MethaneX/actions/runs/41808525486), Brain ThreadSanitizer [#41808525492](https://github.com/methaneex-oss/MethaneX/actions/runs/41808525492), Brain CI [#41808525499](https://github.com/methaneex-oss/MethaneX/actions/runs/41808525499), and JARVIS Brain Tests [#41808525557](https://github.com/methaneex-oss/MethaneX/actions/runs/41808525557). The JARVIS Brain Tests log records **73/73 CTest tests passed** on this exact HEAD.
- PR #176 corrects learned-strategy context selection (D1), rejects non-finite goal priority/progress before mutation (D2), and tests goal-completion/evolution-rollback journal-append failure plus restart after a durable rollback event. It explicitly does not inject failures inside every compensating operation of EvolutionController rollback, and it does not establish external ABI compatibility or accepted-baseline integration. Its own body says PR #156 remains unchanged until the correction is independently reviewed and merged or its fixes are selectively ported.

### Donor disposition

The evidence confirms that PR #97 contains real connected learning machinery and durable experience-dependent behavior, but also confirms material limitations; it is not a completed learning brain. PR #156 is a later integrated candidate with exact-head CI and 73/73 CTest, but retains explicit trust, journal-integrity and ordinary-factual-feedback gaps. PR #176 supplies additional correctness/failure-boundary corrections, but its branch ancestry diverges from the live PR #156 tip and its own rollback-compensation limitation remains. All three PRs remain open/draft/unmerged; none is accepted or authorized for selective porting by this report.

This review closes only the **bounded donor path and selected-file evidence** recorded above. It does not complete semantic review of every one of PR #97's 159 changed files, the full cross-file dependency graph, complete duplicated-material analysis, or the historical branch census. DF-02 remains OPEN.


## 10. Historical cognitive and learning lineage supplement

A further bounded historical census was added at:

`docs/architecture/reports/DF02_HISTORICAL_COGNITIVE_LEARNING_LINEAGE_SUPPLEMENT_2026-11-18.md`

The supplement records exact live PR metadata (head SHA, base branch/base SHA, merge state, changed-file count) for the early cognitive/memory line (#1–#15), evolution/controlled experimentation (#16–#22 and #29), prediction correction (#38), and selected later learning/test/correction branches (#95, #97, #99, #101, #107, #109, #111, #118, #121, #137, #146, #149, #151, #156, #157 and #165).

It identifies important authority distinctions that the earlier bounded report did not make explicit:
- PRs #1–#5 and #8–#15 are historical merges into `main`; #6 remains open, #7 is a closed unmerged duplicate sharing #6's head, and #8 is the distinct merged successor.
- PR #16 and #29 remain open/unmerged; PR #20 is closed unmerged while #21 is its merged rebased successor.
- Several later learning tests/corrections are branch-scoped or unmerged. In particular, #101 and #121 were merged into named feature/integration branches, not `main`; #107/#109/#111/#137/#146/#149/#151/#156/#157/#165 remain open; #118 is closed unmerged.
- PR #97 remains an unmerged 159-path developmental candidate. PR #156 remains an unmerged integration candidate; neither is a selected baseline.

This supplement is evidence of a bounded PR metadata census, not a semantic audit of all files or a complete dependency closure. DF-02 remains OPEN. The explicit remaining work and non-authorizations in §6–§7 remain in force.


## 10. Complete repository PR metadata census — 2026-11-18

A complete live pull-request collection census was fetched on 2026-11-18, while PR #192 was at exact HEAD `d0755a6e41d005263de74e1fec6eb1149ed5eec5`. It returned 188 existing PRs numbered 1–197; missing numbers: 24, 25, 26, 27, 28, 74, 82, 85, 177. State totals: 57 merged into their declared base branch (50 with `main` as declared base; 7 with a non-main base), 84 open (44 draft), and 47 closed without a merge date. Exact head SHA, declared base branch/base SHA, state/merge date and changed-file count for each returned PR are recorded in the historical lineage supplement §8.

This closes repository **PR metadata enumeration** for the returned range and snapshot only. It does not complete all-branch discovery, changed-path retrieval for every PR, semantic review of every changed file, current source-presence verification, cross-branch consumer/reference closure, or the dependency/duplication graph. The selected cognitive/learning semantic review and PR #97/#156/#176 donor analysis remain bounded as stated in the report. DF-02 remains OPEN until those path-level, semantic, dependency and independent-verification requirements are satisfied.

## 11. Exact branch-ancestry reconciliation — 2026-11-18

A bounded exact-SHA graph check was added to historical lineage supplement §8.2. It verifies material relationships including: #6/#7/#8 are duplicate-plus-divergent-sibling rather than a linear chain; #16 and #17 diverge from their common base; #29 and #87 diverge; #84 and #87 diverge; #101–#104 form a feature-branch test chain; #107–#112 are based on earlier feature snapshots; #119's merge commit equals open PR #97 head and is a merge to the feature branch only; #120/#121 are integration-branch scoped; #122–#139 and #148–#165 form multiple correction/test branches; and #176 is based on #156 head. PR #149's immediate parent remains unresolved because its declared base does not match a PR head in the enumerated collection.

The comparisons support branch-ancestry statements only. They do not establish semantic equivalence, source correctness, test acceptance, mainline presence, or Director approval. The #6/#7/#8 description in the supplement was corrected to state that #8 is a merged sibling/alternative, not a descendant of #6. DF-02 remains OPEN pending changed-path/semantic audits of the material unreviewed PRs, current source-presence and cross-branch consumer closure, and independent verification.


## 12. Builder continuation — exact PR #192 status recheck (2026-11-18)

**Live source revision for this continuation:** PR #192 HEAD `5bc0cfa4266ee387bccf26f6b0e6f95c6a1a6509`, fetched before the Builder documentation corrections in this continuation. PR #192 was open, non-draft and unmerged; its changed-file endpoint returned 45 paths. The PR base remained `docs/jarvis-phase-2-whole-brain-integration-map-20261105` @ `61311fe5b44c81c4409c8ba8dc581a83bdd5dd2c`.

The previously recorded metadata census and exact ancestry evidence remain bounded to the census scope stated in §§10–11. The current Builder pass did not convert that metadata census into an exhaustive all-branch semantic audit. The DF-02 residuals below therefore remain explicit:

1. **Historical artifact/branch closure:** the 188-PR metadata census covers the returned GitHub PR collection at its stated snapshot, not every standalone artifact, branch ref, tag, commit, fork or historical working copy. Earlier donor/implementation lineages outside the bounded reviewed sets remain to be discovered and dispositioned.
2. **PR #97 semantic disposition:** the 159 changed paths have subsystem classification and selected critical source/test evidence. This is not a complete semantic review of every path, complete source dependency closure, or duplicate-lineage analysis. Those remain outstanding.
3. **Cross-branch consumers and references:** the complete dependency/consumer graph is not yet proven. The current PR #192 tree census does not inspect every other branch's references to retained, superseded or historical artifacts.
4. **Repository-wide authority consistency:** the current PR #192 documentation tree has been examined as a bounded set, but a repository-wide semantic scan of every README/header/status statement across all historical branches remains incomplete.
5. **Independent verification:** the exact-target DF-02 review request was previously posted for SHA `5bc0cfa4266ee387bccf26f6b0e6f95c6a1a6509`. That review target becomes stale when this continuation advances PR #192. A superseding exact-HEAD assignment must be issued after final inventory closure; no verdict is claimed here.

The Builder has made no donor adoption, source-baseline selection, architecture or algorithm choice, branch-history operation, merge, Stage A start, runtime source/test change, training run or deployment. **DF-02 remains OPEN** and is not presented as ready for Project Director closure until the residual work and exact-revision review are completed.

This addendum is Builder evidence only. It does not alter the authority of PR #171/172/173/174/179/191, does not broaden their approvals, and does not make a current proposal an accepted baseline.

## 13. PR #97 changed-path and current-tree presence recheck — 2026-11-18

This addendum strengthens the bounded donor-lineage evidence in §9. It does not claim the remaining 159-path semantic audit is complete.

### 13.1 Exact source and patch evidence

- PR #97 was re-fetched as **open / draft / unmerged**, HEAD `c1da222e6c94aeb3f2ad000392c21fe4fc81ab25`, base `main` @ `4ba84b8b5ccf0e41530c46fdb8101551254ba864`, with **159** changed paths.
- The recursive PR #97 tree is complete (`truncated=false), with 287 entries / 260 blobs. The connector returned a patch for all 159 changed paths; no changed path lacked a patch. The retrieved patch corpus totals 1,240,387 characters.
- The path classification is: 8 workflow files; 35 core public headers; 37 core implementation files; 56 core test files; 3 core example files; 1 core CMake file; 9 documentation files; and 10 engineering files. Total: 159. This is structural classification, not a per-file semantic disposition.
- The exact-head Check Runs API returned three completed successful checks at `c1da222...`: `cpp-core`, `sanitizer` and `native-brain`, completed on 2026-10-28. The two underlying Actions workflow runs are #40788714735 and #40788714686. These results establish only the recorded build/check executions at that SHA; they do not establish held-out learning quality, generalization, semantic correctness or donor acceptance.

### 13.2 Current source-path presence comparison

The following recursive trees were independently fetched with `truncated=false`:

| Tree | Exact commit | Blobs | PR #97 changed paths present | Absent | Present paths with identical PR #97 blob | Present paths with a different blob |
|---|---|---:|---:|---:|---:|---:|
| PR #97 donor | `c1da222e6c94aeb3f2ad000392c21fe4fc81ab25` | 260 | 159 / 159 | 0 | 159 / 159 (identity baseline) | 0 |
| Current `main` | `4f07d772beae03c99a8dd58b174201a3aa3074b2` | 211 | 96 / 159 | 63 | 1 / 159 | 95 / 159 |
| Current Phase 2 base branch | `ea64607ef94f142a6142a013e119a7225bc95c1c` | 213 | 96 / 159 | 63 | 1 / 159 | 95 / 159 |
| PR #192 closeout-start tree | `bc4dbde5b25a96546b7b90273d06a7d72f7962a0` | 247 | 96 / 159 | 63 | 1 / 159 | 95 / 159 |

**Interpretation:** 63 PR #97 changed paths are not present under the same path in the current `main`, Phase 2 base or PR #192 trees. Of the 96 paths still present, 95 have different blob contents from PR #97; only `.github/workflows/dlt-002-four-hour.yml` retains the same blob. Path absence does not prove that a capability was deleted: a renamed, split, consolidated or superseding implementation may exist elsewhere. Conversely, path presence does not prove semantic equivalence. The 63 absent paths and 95 changed blobs therefore require explicit source-to-successor/retirement disposition before the DF-02 donor/authority graph can be called complete.

### 13.3 Reconfirmed lineage boundary

Live PR metadata still identifies PR #156 as open / draft / unmerged at HEAD `7fe212bbb0bd61116ea56581435e03b06c69b673`, based on `52c367a4b53fdfe9b29776795200555076e8cb49`; PR #176 remains open / draft / unmerged at HEAD `4cf017e073da980c9f77d739fde6f92ef1a2fbc1`, with declared base branch `integration/priority-one-20261031` at `7fe212bbb0bd61116ea56581435e03b06c69b673`. Exact comparison confirms PR #97 HEAD is an ancestor of PR #156's declared base (172 commits ahead, zero behind). Comparing PR #156 HEAD to PR #176 HEAD remains **DIVERGED** (15 ahead, one behind; merge base `15d49e5fdeb5723c475922ab78fb92f97c4b3b84`). The live #176 branch must not be described as containing the current #156 tip solely because its base field names that branch.

The PR #97 causal-transition defect, pre-state cause requirement, held-out generalization limitations, worsening DLT-002 MAE history, world-model contradiction limitations, and evolution/trust boundaries recorded in §9 remain applicable. PR #135, #148 and later correction branches must retain their own exact source attribution; their corrections must not be credited retroactively to PR #97.

### 13.4 DF-02 disposition after this recheck

The Builder has now re-fetched the complete PR #97 changed-path list, all 159 patch bodies, the exact PR #97 tree and Check Runs, plus the current `main`, Phase 2 and PR #192 trees. This closes the **bounded source-path presence measurement** for those exact snapshots. It does **not** close:

1. semantic classification of every PR #97 path and mapping of all 63 absent / 95 changed paths to successors, replacements or explicit retirement;
2. full changed-path and dependency analysis for every material historical cognitive/learning PR and standalone artifact beyond the selected lineages;
3. all-branch consumers, duplicates, historical source references and cross-branch dependency closure;
4. repository-wide active README/header/status consistency across all relevant branches;
5. Independent Reviewer verification of the exact final PR #192 inventory and authority/dependency claims.

**DF-02 remains OPEN.** No donor adoption, source-baseline selection, merge, port, branch rewrite, Gate A/B clearance, Stage A start or runtime implementation is authorized or implied by these measurements.


## 14. Complete PR #97 changed-path semantic-role and exact-tree comparison — 2026-11-18

**Evidence target:** PR #97 exact HEAD `c1da222e6c94aeb3f2ad000392c21fe4fc81ab25`; PR #192 exact HEAD `e6ee04a8a4052a72943a820217aa0d306b2e6b0a`. Both recursive trees were fetched from GitHub with `truncated=false`. The PR #97 changed-file endpoint returned 159 unique paths over two pages; the patch endpoint returned 159 path patches. The current PR #192 tree contains 279 entries.

### 14.1 Structural/semantic-role classification

The full 159-path set is classified by repository area, path and file type, with the corresponding PR patch set inspected to confirm the file's broad responsibility. This is a structural/functional-role classification, not a claim that every function, test assertion, or behavioral requirement has been semantically validated.

| Role | Paths |
|---|---:|
| CI workflow / controlled trial orchestration | 8 |
| Build/test registration | 3 |
| Executable developmental-world example | 3 |
| Core public API / mechanism contract | 35 |
| Core mechanism implementation | 37 |
| Behavioral, integration, persistence or regression test | 54 |
| Design / planning / training documentation | 9 |
| Engineering agent coordination, messaging or durable task ledger | 10 |
| **Total** | **159** |

### 14.2 Exact path/blob disposition against current PR #192

| Relationship | Paths |
|---|---:|
| Donor path absent from current PR #192 tree | 63 |
| Same path present with identical donor blob | 1 |
| Same path present with a different blob | 95 |
| **Total** | **159** |

The following table is the complete path-by-path evidence record. Blob equality is exact content identity. A different blob establishes divergence only; it does not establish whether the current file is a successor, partial port, independent implementation, regression, or unrelated rewrite. An absent path establishes only that no same-path file exists in this exact tree; it does not establish capability deletion or nonexistence under another name.

| PR #97 changed path | PR #97 change type | Role classification | Same path in PR #192 tree | Evidence disposition |
|---|---|---|---|---|
| `.github/workflows/brain-ci.yml` | modified | CI workflow / controlled trial orchestration | Present | Different blob; semantic successor not yet proven |
| `.github/workflows/dlt-001-long-run.yml` | added | CI workflow / controlled trial orchestration | Absent | No same-path successor identified |
| `.github/workflows/dlt-002-four-hour.yml` | added | CI workflow / controlled trial orchestration | Present | Identical blob |
| `.github/workflows/dlt-002-overnight-validation.yml` | added | CI workflow / controlled trial orchestration | Absent | No same-path successor identified |
| `.github/workflows/jarvis-brain-probe-001.yml` | added | CI workflow / controlled trial orchestration | Absent | No same-path successor identified |
| `.github/workflows/jarvis-core.yml` | added | CI workflow / controlled trial orchestration | Absent | No same-path successor identified |
| `.github/workflows/jarvis-learning-seed-sweep.yml` | added | CI workflow / controlled trial orchestration | Absent | No same-path successor identified |
| `.github/workflows/jbp-mem-001.yml` | added | CI workflow / controlled trial orchestration | Present | Different blob; semantic successor not yet proven |
| `core/cpp/CMakeLists.txt` | modified | Build/test registration | Present | Different blob; semantic successor not yet proven |
| `core/cpp/examples/CMakeLists.txt` | added | Executable developmental-world example | Absent | No same-path successor identified |
| `core/cpp/examples/README.md` | added | Executable developmental-world example | Absent | No same-path successor identified |
| `core/cpp/examples/developmental_world.cpp` | added | Executable developmental-world example | Absent | No same-path successor identified |
| `core/cpp/include/jarvis/core/action_execution.hpp` | modified | Core public API / mechanism contract | Present | Different blob; semantic successor not yet proven |
| `core/cpp/include/jarvis/core/action_model.hpp` | modified | Core public API / mechanism contract | Present | Different blob; semantic successor not yet proven |
| `core/cpp/include/jarvis/core/adaptation.hpp` | modified | Core public API / mechanism contract | Present | Different blob; semantic successor not yet proven |
| `core/cpp/include/jarvis/core/affective_learning.hpp` | added | Core public API / mechanism contract | Absent | No same-path successor identified |
| `core/cpp/include/jarvis/core/affective_state.hpp` | added | Core public API / mechanism contract | Absent | No same-path successor identified |
| `core/cpp/include/jarvis/core/association_model.hpp` | modified | Core public API / mechanism contract | Present | Different blob; semantic successor not yet proven |
| `core/cpp/include/jarvis/core/attention.hpp` | modified | Core public API / mechanism contract | Present | Different blob; semantic successor not yet proven |
| `core/cpp/include/jarvis/core/brain.hpp` | modified | Core public API / mechanism contract | Present | Different blob; semantic successor not yet proven |
| `core/cpp/include/jarvis/core/causal_link_codec.hpp` | added | Core public API / mechanism contract | Absent | No same-path successor identified |
| `core/cpp/include/jarvis/core/causal_model.hpp` | modified | Core public API / mechanism contract | Present | Different blob; semantic successor not yet proven |
| `core/cpp/include/jarvis/core/cognition.hpp` | modified | Core public API / mechanism contract | Present | Different blob; semantic successor not yet proven |
| `core/cpp/include/jarvis/core/cognitive_cycle.hpp` | modified | Core public API / mechanism contract | Present | Different blob; semantic successor not yet proven |
| `core/cpp/include/jarvis/core/cognitive_goal_outcome.hpp` | added | Core public API / mechanism contract | Absent | No same-path successor identified |
| `core/cpp/include/jarvis/core/cognitive_runtime.hpp` | modified | Core public API / mechanism contract | Present | Different blob; semantic successor not yet proven |
| `core/cpp/include/jarvis/core/cognitive_workspace.hpp` | modified | Core public API / mechanism contract | Present | Different blob; semantic successor not yet proven |
| `core/cpp/include/jarvis/core/decision.hpp` | modified | Core public API / mechanism contract | Present | Different blob; semantic successor not yet proven |
| `core/cpp/include/jarvis/core/developmental_environment.hpp` | added | Core public API / mechanism contract | Absent | No same-path successor identified |
| `core/cpp/include/jarvis/core/developmental_learning.hpp` | added | Core public API / mechanism contract | Absent | No same-path successor identified |
| `core/cpp/include/jarvis/core/developmental_world.hpp` | added | Core public API / mechanism contract | Absent | No same-path successor identified |
| `core/cpp/include/jarvis/core/evolution.hpp` | modified | Core public API / mechanism contract | Present | Different blob; semantic successor not yet proven |
| `core/cpp/include/jarvis/core/evolution_adoption_journal.hpp` | modified | Core public API / mechanism contract | Present | Different blob; semantic successor not yet proven |
| `core/cpp/include/jarvis/core/evolution_canary.hpp` | modified | Core public API / mechanism contract | Present | Different blob; semantic successor not yet proven |
| `core/cpp/include/jarvis/core/evolution_controller.hpp` | modified | Core public API / mechanism contract | Present | Different blob; semantic successor not yet proven |
| `core/cpp/include/jarvis/core/evolution_experiment.hpp` | modified | Core public API / mechanism contract | Present | Different blob; semantic successor not yet proven |
| `core/cpp/include/jarvis/core/evolution_experiment_coordinator.hpp` | modified | Core public API / mechanism contract | Present | Different blob; semantic successor not yet proven |
| `core/cpp/include/jarvis/core/evolution_experiment_runner.hpp` | modified | Core public API / mechanism contract | Present | Different blob; semantic successor not yet proven |
| `core/cpp/include/jarvis/core/evolution_orchestrator.hpp` | modified | Core public API / mechanism contract | Present | Different blob; semantic successor not yet proven |
| `core/cpp/include/jarvis/core/experience_memory.hpp` | added | Core public API / mechanism contract | Absent | No same-path successor identified |
| `core/cpp/include/jarvis/core/goals.hpp` | modified | Core public API / mechanism contract | Present | Different blob; semantic successor not yet proven |
| `core/cpp/include/jarvis/core/intent.hpp` | modified | Core public API / mechanism contract | Present | Different blob; semantic successor not yet proven |
| `core/cpp/include/jarvis/core/knowledge.hpp` | modified | Core public API / mechanism contract | Present | Different blob; semantic successor not yet proven |
| `core/cpp/include/jarvis/core/memory.hpp` | modified | Core public API / mechanism contract | Present | Different blob; semantic successor not yet proven |
| `core/cpp/include/jarvis/core/planning.hpp` | modified | Core public API / mechanism contract | Present | Different blob; semantic successor not yet proven |
| `core/cpp/include/jarvis/core/reflection.hpp` | modified | Core public API / mechanism contract | Present | Different blob; semantic successor not yet proven |
| `core/cpp/include/jarvis/core/self_model.hpp` | modified | Core public API / mechanism contract | Present | Different blob; semantic successor not yet proven |
| `core/cpp/src/action_execution.cpp` | modified | Core mechanism implementation | Present | Different blob; semantic successor not yet proven |
| `core/cpp/src/adaptation.cpp` | modified | Core mechanism implementation | Present | Different blob; semantic successor not yet proven |
| `core/cpp/src/affective_learning.cpp` | added | Core mechanism implementation | Absent | No same-path successor identified |
| `core/cpp/src/affective_state.cpp` | added | Core mechanism implementation | Absent | No same-path successor identified |
| `core/cpp/src/association_model.cpp` | modified | Core mechanism implementation | Present | Different blob; semantic successor not yet proven |
| `core/cpp/src/attention.cpp` | modified | Core mechanism implementation | Present | Different blob; semantic successor not yet proven |
| `core/cpp/src/brain.cpp` | modified | Core mechanism implementation | Present | Different blob; semantic successor not yet proven |
| `core/cpp/src/brain_action_execution.cpp` | added | Core mechanism implementation | Absent | No same-path successor identified |
| `core/cpp/src/brain_affective_planning.cpp` | added | Core mechanism implementation | Absent | No same-path successor identified |
| `core/cpp/src/brain_prediction_context.cpp` | added | Core mechanism implementation | Absent | No same-path successor identified |
| `core/cpp/src/brain_restored_api.cpp` | added | Core mechanism implementation | Present | Different blob; semantic successor not yet proven |
| `core/cpp/src/causal_model.cpp` | modified | Core mechanism implementation | Present | Different blob; semantic successor not yet proven |
| `core/cpp/src/cognitive_cycle.cpp` | modified | Core mechanism implementation | Present | Different blob; semantic successor not yet proven |
| `core/cpp/src/cognitive_runtime.cpp` | modified | Core mechanism implementation | Present | Different blob; semantic successor not yet proven |
| `core/cpp/src/decision.cpp` | modified | Core mechanism implementation | Present | Different blob; semantic successor not yet proven |
| `core/cpp/src/developmental_learning.cpp` | added | Core mechanism implementation | Absent | No same-path successor identified |
| `core/cpp/src/evolution.cpp` | modified | Core mechanism implementation | Present | Different blob; semantic successor not yet proven |
| `core/cpp/src/evolution_adoption.cpp` | modified | Core mechanism implementation | Present | Different blob; semantic successor not yet proven |
| `core/cpp/src/evolution_adoption_journal.cpp` | modified | Core mechanism implementation | Present | Different blob; semantic successor not yet proven |
| `core/cpp/src/evolution_canary.cpp` | modified | Core mechanism implementation | Present | Different blob; semantic successor not yet proven |
| `core/cpp/src/evolution_controller.cpp` | modified | Core mechanism implementation | Present | Different blob; semantic successor not yet proven |
| `core/cpp/src/evolution_experiment_coordinator.cpp` | modified | Core mechanism implementation | Present | Different blob; semantic successor not yet proven |
| `core/cpp/src/evolution_experiment_runner.cpp` | modified | Core mechanism implementation | Present | Different blob; semantic successor not yet proven |
| `core/cpp/src/evolution_history.cpp` | modified | Core mechanism implementation | Present | Different blob; semantic successor not yet proven |
| `core/cpp/src/evolution_orchestrator.cpp` | modified | Core mechanism implementation | Present | Different blob; semantic successor not yet proven |
| `core/cpp/src/evolution_safety.cpp` | modified | Core mechanism implementation | Present | Different blob; semantic successor not yet proven |
| `core/cpp/src/evolution_sandbox.cpp` | modified | Core mechanism implementation | Present | Different blob; semantic successor not yet proven |
| `core/cpp/src/goals.cpp` | modified | Core mechanism implementation | Present | Different blob; semantic successor not yet proven |
| `core/cpp/src/intent.cpp` | modified | Core mechanism implementation | Present | Different blob; semantic successor not yet proven |
| `core/cpp/src/knowledge.cpp` | modified | Core mechanism implementation | Present | Different blob; semantic successor not yet proven |
| `core/cpp/src/memory.cpp` | modified | Core mechanism implementation | Present | Different blob; semantic successor not yet proven |
| `core/cpp/src/planning.cpp` | modified | Core mechanism implementation | Present | Different blob; semantic successor not yet proven |
| `core/cpp/src/process_isolation.cpp` | modified | Core mechanism implementation | Present | Different blob; semantic successor not yet proven |
| `core/cpp/src/reasoning.cpp` | modified | Core mechanism implementation | Present | Different blob; semantic successor not yet proven |
| `core/cpp/src/reflection.cpp` | modified | Core mechanism implementation | Present | Different blob; semantic successor not yet proven |
| `core/cpp/src/representation.cpp` | modified | Core mechanism implementation | Present | Different blob; semantic successor not yet proven |
| `core/cpp/src/self_model.cpp` | modified | Core mechanism implementation | Present | Different blob; semantic successor not yet proven |
| `core/cpp/tests/CMakeLists.txt` | modified | Build/test registration | Present | Different blob; semantic successor not yet proven |
| `core/cpp/tests/action_authorization_suite.cpp` | modified | Behavioral, integration, persistence or regression test | Present | Different blob; semantic successor not yet proven |
| `core/cpp/tests/action_execution_phase7_suite.cpp` | modified | Behavioral, integration, persistence or regression test | Present | Different blob; semantic successor not yet proven |
| `core/cpp/tests/action_model_architecture_suite.cpp` | modified | Behavioral, integration, persistence or regression test | Present | Different blob; semantic successor not yet proven |
| `core/cpp/tests/affective_brain_decision_suite.cpp` | added | Behavioral, integration, persistence or regression test | Absent | No same-path successor identified |
| `core/cpp/tests/affective_decision_learning_suite.cpp` | added | Behavioral, integration, persistence or regression test | Absent | No same-path successor identified |
| `core/cpp/tests/affective_decision_suite.cpp` | added | Behavioral, integration, persistence or regression test | Absent | No same-path successor identified |
| `core/cpp/tests/affective_evidence_suite.cpp` | added | Behavioral, integration, persistence or regression test | Absent | No same-path successor identified |
| `core/cpp/tests/affective_goal_outcome_suite.cpp` | added | Behavioral, integration, persistence or regression test | Absent | No same-path successor identified |
| `core/cpp/tests/affective_learning_suite.cpp` | added | Behavioral, integration, persistence or regression test | Absent | No same-path successor identified |
| `core/cpp/tests/affective_planning.cmake` | added | Build/test registration | Absent | No same-path successor identified |
| `core/cpp/tests/affective_planning_suite.cpp` | added | Behavioral, integration, persistence or regression test | Absent | No same-path successor identified |
| `core/cpp/tests/affective_state_model_suite.cpp` | added | Behavioral, integration, persistence or regression test | Absent | No same-path successor identified |
| `core/cpp/tests/affective_state_suite.cpp` | added | Behavioral, integration, persistence or regression test | Absent | No same-path successor identified |
| `core/cpp/tests/association_causality_phase5_suite.cpp` | modified | Behavioral, integration, persistence or regression test | Present | Different blob; semantic successor not yet proven |
| `core/cpp/tests/attention_architecture_suite.cpp` | modified | Behavioral, integration, persistence or regression test | Present | Different blob; semantic successor not yet proven |
| `core/cpp/tests/attention_learning_brain_suite.cpp` | added | Behavioral, integration, persistence or regression test | Absent | No same-path successor identified |
| `core/cpp/tests/brain_10_suite.cpp` | modified | Behavioral, integration, persistence or regression test | Present | Different blob; semantic successor not yet proven |
| `core/cpp/tests/brain_action_consequence_integration_suite.cpp` | added | Behavioral, integration, persistence or regression test | Absent | No same-path successor identified |
| `core/cpp/tests/brain_contract.cpp` | modified | Behavioral, integration, persistence or regression test | Present | Different blob; semantic successor not yet proven |
| `core/cpp/tests/brain_deep_suite.cpp` | modified | Behavioral, integration, persistence or regression test | Present | Different blob; semantic successor not yet proven |
| `core/cpp/tests/cognitive_cycle_suite.cpp` | modified | Behavioral, integration, persistence or regression test | Present | Different blob; semantic successor not yet proven |
| `core/cpp/tests/cognitive_runtime_goal_feedback_suite.cpp` | added | Behavioral, integration, persistence or regression test | Absent | No same-path successor identified |
| `core/cpp/tests/cognitive_runtime_learning_integration_suite.cpp` | added | Behavioral, integration, persistence or regression test | Absent | No same-path successor identified |
| `core/cpp/tests/cognitive_runtime_suite.cpp` | modified | Behavioral, integration, persistence or regression test | Present | Different blob; semantic successor not yet proven |
| `core/cpp/tests/cognitive_workspace_runtime_suite.cpp` | modified | Behavioral, integration, persistence or regression test | Present | Different blob; semantic successor not yet proven |
| `core/cpp/tests/decision_planning_architecture_suite.cpp` | modified | Behavioral, integration, persistence or regression test | Present | Different blob; semantic successor not yet proven |
| `core/cpp/tests/developmental_brain_integration_suite.cpp` | added | Behavioral, integration, persistence or regression test | Absent | No same-path successor identified |
| `core/cpp/tests/developmental_environment_suite.cpp` | added | Behavioral, integration, persistence or regression test | Absent | No same-path successor identified |
| `core/cpp/tests/developmental_learning_suite.cpp` | added | Behavioral, integration, persistence or regression test | Absent | No same-path successor identified |
| `core/cpp/tests/developmental_learning_tests.cpp` | added | Behavioral, integration, persistence or regression test | Absent | No same-path successor identified |
| `core/cpp/tests/developmental_training_environment_suite.cpp` | added | Behavioral, integration, persistence or regression test | Absent | No same-path successor identified |
| `core/cpp/tests/developmental_world_integration_suite.cpp` | added | Behavioral, integration, persistence or regression test | Absent | No same-path successor identified |
| `core/cpp/tests/developmental_world_suite.cpp` | added | Behavioral, integration, persistence or regression test | Absent | No same-path successor identified |
| `core/cpp/tests/dlt_001_long_run.cpp` | added | Behavioral, integration, persistence or regression test | Absent | No same-path successor identified |
| `core/cpp/tests/dlt_001_trial.cpp` | added | Behavioral, integration, persistence or regression test | Absent | No same-path successor identified |
| `core/cpp/tests/dlt_002_long_run.cpp` | added | Behavioral, integration, persistence or regression test | Absent | No same-path successor identified |
| `core/cpp/tests/dlt_002_persistence.cpp` | added | Behavioral, integration, persistence or regression test | Absent | No same-path successor identified |
| `core/cpp/tests/evolution_adoption_journal_suite.cpp` | modified | Behavioral, integration, persistence or regression test | Present | Different blob; semantic successor not yet proven |
| `core/cpp/tests/evolution_brain_integration_suite.cpp` | modified | Behavioral, integration, persistence or regression test | Present | Different blob; semantic successor not yet proven |
| `core/cpp/tests/evolution_canary_controller_suite.cpp` | modified | Behavioral, integration, persistence or regression test | Present | Different blob; semantic successor not yet proven |
| `core/cpp/tests/evolution_experiment_coordinator_suite.cpp` | modified | Behavioral, integration, persistence or regression test | Present | Different blob; semantic successor not yet proven |
| `core/cpp/tests/evolution_experiment_runner_suite.cpp` | modified | Behavioral, integration, persistence or regression test | Present | Different blob; semantic successor not yet proven |
| `core/cpp/tests/evolution_opportunity_orchestration_suite.cpp` | modified | Behavioral, integration, persistence or regression test | Present | Different blob; semantic successor not yet proven |
| `core/cpp/tests/experience_memory_test.cpp` | added | Behavioral, integration, persistence or regression test | Absent | No same-path successor identified |
| `core/cpp/tests/goal_directed_cognition_suite.cpp` | added | Behavioral, integration, persistence or regression test | Absent | No same-path successor identified |
| `core/cpp/tests/goal_outcome_model_suite.cpp` | added | Behavioral, integration, persistence or regression test | Absent | No same-path successor identified |
| `core/cpp/tests/goals_architecture_suite.cpp` | modified | Behavioral, integration, persistence or regression test | Present | Different blob; semantic successor not yet proven |
| `core/cpp/tests/knowledge_memory_phase3_suite.cpp` | modified | Behavioral, integration, persistence or regression test | Present | Different blob; semantic successor not yet proven |
| `core/cpp/tests/learning_adaptation_phase8_suite.cpp` | modified | Behavioral, integration, persistence or regression test | Present | Different blob; semantic successor not yet proven |
| `core/cpp/tests/memory_architecture_suite.cpp` | modified | Behavioral, integration, persistence or regression test | Present | Different blob; semantic successor not yet proven |
| `core/cpp/tests/memory_learning_evolution_persistence_suite.cpp` | added | Behavioral, integration, persistence or regression test | Absent | No same-path successor identified |
| `core/cpp/tests/prediction_feedback_phase10_suite.cpp` | modified | Behavioral, integration, persistence or regression test | Present | Different blob; semantic successor not yet proven |
| `core/cpp/tests/process_isolation_suite.cpp` | modified | Behavioral, integration, persistence or regression test | Present | Different blob; semantic successor not yet proven |
| `core/cpp/tests/reasoning_architecture_suite.cpp` | modified | Behavioral, integration, persistence or regression test | Present | Different blob; semantic successor not yet proven |
| `core/cpp/tests/representation_suite.cpp` | modified | Behavioral, integration, persistence or regression test | Present | Different blob; semantic successor not yet proven |
| `docs/developmental-training-environment.md` | added | Design / planning / training documentation | Absent | No same-path successor identified |
| `docs/superpowers/plans/2026-09-25-cognitive-action-feedback-loop.md` | added | Design / planning / training documentation | Absent | No same-path successor identified |
| `docs/superpowers/plans/2026-09-26-concept-context-prediction.md` | added | Design / planning / training documentation | Absent | No same-path successor identified |
| `docs/superpowers/plans/2026-09-30-developmental-cognition.md` | added | Design / planning / training documentation | Absent | No same-path successor identified |
| `docs/superpowers/plans/2026-10-01-affective-state.md` | added | Design / planning / training documentation | Absent | No same-path successor identified |
| `docs/superpowers/specs/2026-09-25-cognitive-action-feedback-loop-design.md` | added | Design / planning / training documentation | Absent | No same-path successor identified |
| `docs/superpowers/specs/2026-09-26-concept-context-prediction-design.md` | added | Design / planning / training documentation | Absent | No same-path successor identified |
| `docs/superpowers/specs/2026-09-30-developmental-cognition.md` | added | Design / planning / training documentation | Absent | No same-path successor identified |
| `docs/superpowers/specs/2026-10-01-affective-state.md` | added | Design / planning / training documentation | Absent | No same-path successor identified |
| `engineering/cpp/CMakeLists.txt` | modified | Engineering agent coordination, messaging or durable task ledger | Present | Different blob; semantic successor not yet proven |
| `engineering/cpp/include/jarvis/engineering/agent.hpp` | modified | Engineering agent coordination, messaging or durable task ledger | Present | Different blob; semantic successor not yet proven |
| `engineering/cpp/include/jarvis/engineering/coordinator.hpp` | modified | Engineering agent coordination, messaging or durable task ledger | Present | Different blob; semantic successor not yet proven |
| `engineering/cpp/include/jarvis/engineering/message_bus.hpp` | modified | Engineering agent coordination, messaging or durable task ledger | Present | Different blob; semantic successor not yet proven |
| `engineering/cpp/include/jarvis/engineering/task_ledger.hpp` | added | Engineering agent coordination, messaging or durable task ledger | Absent | No same-path successor identified |
| `engineering/cpp/src/coordinator.cpp` | modified | Engineering agent coordination, messaging or durable task ledger | Present | Different blob; semantic successor not yet proven |
| `engineering/cpp/src/message_bus.cpp` | modified | Engineering agent coordination, messaging or durable task ledger | Present | Different blob; semantic successor not yet proven |
| `engineering/cpp/src/task_ledger.cpp` | added | Engineering agent coordination, messaging or durable task ledger | Absent | No same-path successor identified |
| `engineering/cpp/tests/agent_and_console_suite.cpp` | modified | Engineering agent coordination, messaging or durable task ledger | Present | Different blob; semantic successor not yet proven |
| `engineering/cpp/tests/task_ledger_suite.cpp` | added | Engineering agent coordination, messaging or durable task ledger | Absent | No same-path successor identified |

### 14.3 Required semantic follow-through — still open

The complete 159-path enumeration and role classification close the prior *structural classification gap*, but do not close DF-02's semantic and dependency obligations. Specifically:

1. The 95 divergent same-path files still require symbol/API/behavior comparison to establish which donor responsibilities are preserved, adapted, replaced, or intentionally not carried forward.
2. The 63 absent paths require successor-name searches and reverse-consumer checks across relevant branches before any retirement or replacement conclusion can be recorded.
3. The 1 identical path must still be interpreted in its workflow and branch context; identical content is not evidence of authorization, execution, or acceptance.
4. The 56 core tests and long-run/training artifacts require outcome provenance to remain bound to the exact PR #97 or descendant branch and SHA. Their existence or historical green CI does not establish current-main acceptance or generalization.
5. The 9 documentation paths are historical donor specifications/plans. They must be reconciled with approved PR #171 SYS-01–SYS-11 and later accepted planning decisions without copying or creating duplicate architecture documents.
6. Engineering task-ledger and messaging changes are a distinct engineering coordination subsystem. They are not JARVIS Brain cognitive mechanisms and must not be conflated with the Brain's learning loop.
7. All-branch consumer/reference closure and semantic disposition of other material historical PRs/standalone artifacts remain open.

**DF-02 remains OPEN.** This update is Builder evidence only. It does not approve donor adoption, select a source baseline, declare a capability complete, authorize a merge/port/history operation, close Gate A/B, start Stage A, or authorize runtime implementation. Independent verification and applicable Project Director authority remain separate.



## 15. Project Director Option A — expanded PR #97 structural inventory, semantic closure still outstanding (2026-11-19)

**Exact PR #192 source snapshot:** `d8efba1d99cc0017e27d6915cfb8c6e8bf384da1`; live PR #192 was re-fetched immediately before this documentation update and matched that SHA. PR #97 donor HEAD remains `c1da222e6c94aeb3f2ad000392c21fe4fc81ab25`. Its patch endpoint returned 159 patches. The complete path inventory groups as follows:

| File family | Paths | What the family represents | Semantic closure status |
|---|---:|---|---|
| CI/workflows | 8 | Core CI, long-run trials, memory persistence and probe/seed-sweep workflows | Exact run-to-source provenance and operational status still require per-workflow reconciliation |
| Core build/config | 1 | Core CMake source/target integration | Build graph and downstream target compatibility not fully compared |
| Core examples | 3 | Developmental-world example and its build/readme | Example behavior and successor mapping not fully compared |
| Core public headers | 35 | Public cognitive, memory, learning, action, affect and evolution interfaces | API/symbol/contract comparison for every path remains outstanding |
| Core implementation | 37 | Brain, cognitive cycle/runtime, memory, prediction, decision, developmental learning, affect, evolution and supporting mechanisms | Function/behavior and state-ownership comparison for every path remains outstanding |
| Core tests | 56 | Unit, integration, persistence, developmental and long-run tests | Test registration, assertion semantics, exact run provenance and successor mapping remain outstanding |
| Documentation/specifications | 9 | Developmental environment and dated plans/specifications | Authority, supersession and relationship to approved PR #171 SYS-01–SYS-11 require per-artifact disposition |
| Engineering coordination | 10 | Agent/coordinator/message-bus/task-ledger subsystem | Must be reconciled separately; do not misclassify it as a Brain cognitive mechanism |
| **Total** | **159** |  |  |

The existing PR #97 donor capability traceability document gives deeper source-level analysis for seven capability groups: continuous affective state; affective appraisal adaptation; action execution/consequence feedback; developmental strategy learning/contextual transfer; contextual prediction feedback; event-journal reconstruction/persistence; and evolution evaluation/adoption control. It is explicitly a selected high-impact sample, not a semantic disposition of all 159 paths.

The existing PR #97 → PR #192 same-path comparison remains: 1 identical blob, 95 divergent same-path blobs, 63 absent same-path entries. The live branch census remains 251 refs / 210 distinct tips / eight duplicate-tip groups. Neither structural comparison nor ref census identifies a semantic successor, proves retirement, or closes reverse consumers/dependencies.

**DF-02 remains OPEN under the Project Director's Option A.** The next substantive work is a per-path semantic disposition matrix across all 159 paths, with exact donor and candidate-successor revisions/blobs; symbol/API/behavior changes; reverse consumers; test/CI evidence bound to exact commits; historical provenance; and an explicit disposition (preserved, adapted, replaced, retired with evidence, not adopted with rationale, or unresolved). For absent paths, search successor candidates and reverse consumers across the relevant branch/PR lineages. Do not select/adopt a donor baseline or claim closure from naming or blob similarity.


## 16. Bounded semantic source audit — cognitive learning and persistence path (2026-11-19)

**Working PR #192 source:** `711ce19e360bb5d4a7c91e9d94092466bb344f89`; report blob before this update: `7ae05a9d02a5c0323182d5775270495f1e53ac47`.  
**Donor:** PR #97 exact HEAD `c1da222e6c94aeb3f2ad000392c21fe4fc81ab25`.  
**Comparison baseline:** main source snapshot `1273ddbcd0087d189e01388ded2d362fb1e058d2`.  
**Scope:** Four core source paths and three test/build-registration paths. This is a bounded semantic tranche, not completion of the 159-path audit.

### 16.1 Core runtime paths

| Path | Donor evidence | Main-baseline evidence | Semantic disposition |
|---|---|---|---|
| `core/cpp/src/cognitive_cycle.cpp` | Blob `f191dd610d6cbe1621756c35e7c13af2054a7266`, 777 lines. The cycle recalls before committing the current observation; performs perception-pipeline processing and attaches provider evidence to the durable observation; resolves eligible prior forecasts against later observed beliefs; performs targeted action-outcome/context recall and uses remembered strategy evidence in planning; retains episodic fallback behavior. | Blob `3df14c552f2048b0394dc362f7ee7a654a93fb32`, 162 lines. The existing cycle already recalls memory, simulates predictions, reflects and exposes outcome-learning/feedback entry points, but does not contain the donor's integrated perception, contextual strategy and cross-observation forecast handling. | **Adaptation candidate, not a proven drop-in successor.** The donor connects several existing mechanisms into a richer cycle. Its new context encoding, recall ranking and prediction lifecycle require contract, concurrency and regression review before adoption. |
| `core/cpp/src/brain.cpp` | Blob `dec9e5442b3ca4b81a7879855c6146b2619934cc`, 889 lines. Adds validated prediction-outcome handling before state mutation, event replay paths for affective and action-consequence learning, prediction-feedback updates, and journal-backed reconstruction of the expanded state. | Blob `e9f3758fcc9c0e89b7280ce376db9033d547682d`, 219 lines. It already constructs from and replays the memory journal and exposes core Brain state/persistence operations, but lacks the donor's expanded event-specific learning and feedback path. | **Substantial behavioral expansion.** Do not equate line-count growth with correctness. Event ordering, duplicate/rejected feedback, replay idempotence and cross-subsystem mutation need explicit verification. |
| `core/cpp/src/memory.cpp` | Blob `ab42bba1d32d6f48d091787491c72294a4a55bb5`, 226 lines. Persists journal events, validates sequence progression on load, preserves a corrupt tail to a quarantine file before truncating to the last valid record, and rebuilds memory tiers/metadata for recall and consolidation. | Blob `ba72a897306d4761246d0deab2fbab37c49d372f`, 429 lines. Main already has journal append/load, metadata, ranked recall, tier promotion, consolidation and working-memory operations. Its load path truncates an invalid tail but the inspected baseline does not show the donor's quarantine preservation step. | **Existing mechanism with materially different recovery implementation.** The donor is not simply a newer replacement: the main implementation has a different organization and broader visible method surface. Compare serialization compatibility, metadata migration, crash recovery and failure rollback before any replacement decision. |
| `core/cpp/src/developmental_learning.cpp` | Blob `dbf5f43271dfa0a3c57236e2faa82eb88d15490d`, 445 lines. Implements association and strategy observation, best/exact and related-context strategy retrieval, and consolidation. | The exact same path is absent at the inspected main baseline (GitHub contents lookup returned NOT_FOUND). | **New donor capability; no same-path successor.** The donor traceability identifies downstream use by the donor cognitive-cycle and affective-planning paths. Reverse consumers and alternate implementations across all relevant branches remain to be searched; absence on main is not evidence that the capability can be safely imported. |

### 16.2 Test and build evidence

| Path | Exact donor evidence | What it establishes | What it does not establish |
|---|---|---|---|
| `core/cpp/tests/cognitive_runtime_learning_integration_suite.cpp` | Blob `656de56b1368e40afb090778a7a5504ab4208056`, 327 lines. | Assertions cover action execution with observed negative consequence, later action selection changing from `calibrate` to `wait`, context-specific strategy transfer, regime reversal, and restored strategy after reconstruction. This is an end-to-end test design for experience-dependent later behavior. | No test execution or held-out generalization result is established by reading the source. |
| `core/cpp/tests/memory_learning_evolution_persistence_suite.cpp` | Blob `98e6598f60912714234f2dfabfbe52fa5eb77044`, 209 lines. | A dedicated test source exists for memory/learning/evolution persistence. | The source's presence alone does not prove all restart, corruption, rollback or evolution invariants pass. |
| `core/cpp/tests/CMakeLists.txt` | Blob `cbfd1fde52fffa6eeac025da2b7ddcb5ab493261`. | The cognitive-runtime learning integration target is declared and linked to `jarvis_core`; the donor test-registration file also declares the memory/learning/evolution persistence target. | Registration is not execution. The bounded commit-workflow lookup returned no PR-triggered workflow runs for the donor SHA; no CI pass is claimed. |

### 16.3 Engineering conclusion and remaining work

This tranche confirms a meaningful distinction: the donor contains a concrete experience-to-outcome-to-later-action-change path, while the inspected main cognitive cycle is materially narrower. The donor's integration test expresses an observable behavioral criterion rather than merely checking that classes exist. However, its assertions are source evidence only until exact-SHA CI/build execution and independent reproduction are available.

The memory comparison also prevents a simplistic “donor is newer, therefore replace main” conclusion. Main already has a substantial journal and memory implementation, while the donor differs in corruption recovery and the cognitive-cycle integration. These paths require compatibility and failure-semantics analysis, not wholesale copying.

**Disposition for this tranche:** retain the four donor source paths and three test/build paths as historical evidence; classify the cognitive-cycle and Brain changes as adaptation candidates, memory as an existing-mechanism comparison, and developmental learning as a donor-only capability candidate. No donor path is adopted, retired, or selected as a baseline by this audit.

**DF-02 remains OPEN.** The remaining 152 PR #97 paths still require equivalent semantic disposition, along with complete reverse-consumer/dependency searches, exact CI provenance for relevant tests/workflows, historical artifact authority and cross-branch duplication/retirement analysis. This bounded tranche does not close Gate A or Gate B and does not authorize runtime implementation.


## 17. Bounded semantic source audit — causal, association, adaptation, reasoning, representation and evolution controls (2026-11-19)

**Exact PR #192 source snapshot:** `d13b3ab81f543fe08e048e6d42a3ad19fdafb86a`. The two commits after source snapshot `711ce19e360bb5d4a7c91e9d94092466bb344f89` changed documentation only; the source blobs below were re-fetched at this exact current PR revision.  
**Donor:** PR #97 exact HEAD `c1da222e6c94aeb3f2ad000392c21fe4fc81ab25`.  
**Comparison baseline:** main source snapshot `1273ddbcd0087d189e01388ded2d362fb1e058d2`.  
**Scope:** Seven core implementation paths and seven donor test paths. This extends §16; it is not the full 159-path semantic audit.

### 17.1 Core implementation comparison

| Path | PR #97 donor blob and behavior | Current PR #192 blob and behavior | Semantic disposition |
|---|---|---|---|
| `core/cpp/src/causal_model.cpp` | `b7e1e6e6aeb929f09af33b9d17c80a6eed34948c`. Adds typed causal-link encoding/decoding and evaluates existing causal predictions against each new transition, weakening links after failed predictions. However, the inspected learning loop still encodes the **post-transition** value as the cause and considers every other post-state fact as an effect, including unchanged facts. | `f873d0a6e7fa0676bb88bf7a1f66436bc88a3c0d`. Retains the same post-state-cause and unchanged-effect defect; it lacks the donor's outcome-based weakening and typed codec. | **Neither version is safe to accept as-is.** The donor does not fix the causal semantics defect. PR #135 (`58acf23c9cc4594284062465ed658daf7f99e9a2`) proposes the correct pre-transition cause and excludes unchanged effects, but PR #135 is open/unmerged and based on the donor branch. It is a correction candidate, not an integrated fix or accepted baseline. |
| `core/cpp/src/association_model.cpp` | `80bc2e94d8cab4e5a48ead18ba9efcad4ed785b6`. Adds contradiction counters/penalties, graph-context inference, and generalized concept matching; newly introduced beliefs can participate in associations. | `b378d4237527dfbb4c65f43545f7f0fc7c42669b`. Associates changed beliefs with observed context using transition reliability and retained confidence; no equivalent contradiction penalty, contextual graph traversal or generalized-concept matcher was found in this file. | **Adaptation candidate.** The added retrieval/contradiction behavior is meaningful, but thresholds, evidence weighting, persistence and interference between related contexts require direct evaluation. Do not infer safe transfer from graph reachability alone. |
| `core/cpp/src/adaptation.cpp` | `51b91a52c20f71a1be462f660c45bee9199259c3`. Supports real-valued estimates, normalized error, first-observation initialization, a recent-error signal and consecutive-surprise tracking that increases update rate during sustained regime change. | `7e07a491a5b13379a5719882a834ecc2452a54ef`. Clamps predictions and observations to `[0,1]` and uses a cumulative-average estimate/error; it has no separate recent-error or surprise-streak signal. | **Adaptation candidate.** The donor better accommodates unbounded numeric quantities and regime changes, but its normalization and streak thresholds are engineered priors. Require outlier, scale, noisy-regime and held-out calibration evidence. |
| `core/cpp/src/attention.cpp` | `67def4987f4a49a852bd2e4c9760f05c2ee15216`. Adds internal activation and prediction-error features and weights to attention scoring. | `58f734dbe9772675d687752026231297f289e770`. Scores novelty, uncertainty and urgency; no internal-activation or prediction-error channels are present in this implementation. | **Bounded extension candidate.** Verify that activation/error signals are independently grounded, do not create a circular feedback loop, and improve attention allocation on controlled tasks. |
| `core/cpp/src/reasoning.cpp` | `18bf2facc9f95c6bd2e8d9a559a0e5b1c5ae06e1`. Uses the typed causal-link codec, excludes disputed beliefs from authoritative inference, and constrains solve confidence to supported premises/conclusions. | `feec78b2e8a1f2b0b58733fd509e4e5a750258fc`. Uses the legacy delimiter-based causal-link representation and does not apply the donor's disputed-premise filtering in the inspected inference path. | **Adaptation candidate.** Preserve backward decoding for existing journal/link data; test delimiter collisions, disputed evidence, confidence propagation and replay before changing the representation contract. |
| `core/cpp/src/representation.cpp` | `054bd9ecee3ef3da83dd405dc5785464d874fa21`. Uses deterministic sequence/key-based node identifiers rather than process-dependent `std::hash`, reads confidence from event evidence, excludes appraisal metadata from represented world attributes, and rejects non-finite confidence values. | `0e53bfaa0c1114cb7390d9f7ce577c87d6bc6169`. Uses `std::hash` for node identity and range checks that do not explicitly reject NaN/Inf. | **Adaptation candidate plus integration gap.** Stable identity and finite-value validation are concrete improvements. However, the production `CognitiveCycle` at this source revision does not call the representation/perception pipeline; the standalone engine and tests therefore do not establish that observations are represented before Brain belief updates. |
| `core/cpp/src/evolution_controller.cpp` | `4e77ec2e5daa09a964132ca486b8c5ee1cebf2f5`. Adds finite/range validation, recomputation of experiment outcome, isolation-attestation checks, durable matching evaluation requirements, replay handling and compensating state restoration when adoption-history writes fail. | `01484ebf12fc3902bce749030a1f54610b26236a`. The inspected controller stages evaluation and writes history with materially fewer input/evidence checks; adoption/rollback compensation is less explicit. | **Safety-critical adaptation candidate, not permission for autonomous self-modification.** PR #176 adds D1/D2 and selected journal-failure corrections, but its branch diverges from the live PR #156 tip and leaves deeper rollback-compensation failure injection open. Preserve the adoption gate and require exact-branch failure tests before any adoption. |

### 17.2 Exact donor test evidence

| Test path | Exact donor blob | Source-level evidence inspected | Evidence boundary |
|---|---|---|---|
| `core/cpp/tests/association_causality_phase5_suite.cpp` | `0d31349857e85a019467e9864bbe6625a6ecdef7` | Contextual association traversal, path-strength decay, and association persistence/replay including contradiction counters. | Source assertions only; no new execution claim in this tranche. |
| `core/cpp/tests/learning_adaptation_phase8_suite.cpp` | `59859480a6d09aaab70eaf09ffc94c731484d2ff` | Recent-error change response, reduced confidence after a regime shift, restart persistence and invalid-sample handling. | Does not establish held-out prediction improvement or robust calibration across arbitrary scales. |
| `core/cpp/tests/reasoning_architecture_suite.cpp` | `ceb6d471b3283f4a89fe243ac3c9e79f52f137a2` | Disputed-premise handling, confidence constraints, delimiter-bearing values and legacy causal-link decoding. | Source assertions only; cross-version journal compatibility still requires integration testing. |
| `core/cpp/tests/representation_suite.cpp` | `07c515018eca0f34f496e85608f504620fd07306` | Stable repeated node identity, confidence/evidence grounding, and rejection of out-of-range/non-finite representations. | Does not establish that the production cycle invokes this engine. |
| `core/cpp/tests/evolution_brain_integration_suite.cpp` | `59d7dd68c42eea18d488d8e5e6aa9f7a9a327ded` | Brain-level evaluation/adoption and legacy replay behavior, including rejection of unverified legacy adoption. | Does not establish full crash-window or rollback-compensation coverage. |
| `core/cpp/tests/evolution_canary_controller_suite.cpp` | `80cac5df347987a9074e1ced43202f8759f797d7` | Canary observation, rollback to baseline, and idempotent replay of evaluation history. | Does not prove every compensation operation is failure-safe. |
| `core/cpp/tests/evolution_adoption_journal_suite.cpp` | `fc8ae17bb837831fef7bf69873ec0e5243e2bc22` | Pending/adopted/rolled-back journal transitions and selected compensation/replay paths. | Does not replace PR #176's disclosed deeper rollback-failure-injection requirement. |

### 17.3 Cross-path findings and disposition

1. The donor's association, adaptation, reasoning and representation changes are not isolated declarations: their test sources exercise graph retrieval, prediction-error response, disputed-evidence handling, and stable evidence representation. Their integration into the production cycle remains uneven and must be proven at the owning call sites.
2. The representation engine is compiled and tested separately, but the current production cycle consumes raw observation events directly through `Brain::observe`; it does not pass a normalized `PerceptualRepresentation` into the cycle context. This is a material integration gap, not evidence that the standalone representation engine is useless.
3. The causal-learning defect is present in both the inspected donor and current mainline source. PR #135 is a proposed correction on an unmerged donor-derived branch. Do not claim the correction is already integrated.
4. Evolution-controller improvements are safety controls, not a general learning objective. They must remain separate from evidence that ordinary experience improves task performance.
5. No test in this tranche was built or executed. The exact donor blob identities and test assertions are source-inspection evidence only; no CI run is attributed to these seven test files.

**Disposition for this tranche:** preserve all seven source/test pairs as historical evidence; treat association, adaptation, attention, reasoning and representation as selective adaptation candidates; reject the causal implementation as-is pending the pre-state/changed-effect correction; and keep evolution-controller adoption gated pending the PR #156/#176 ancestry and failure-boundary reconciliation. No donor is adopted, retired or selected as the implementation baseline.

**DF-02 remains OPEN.** Sections §16–§17 now provide bounded semantic dispositions for 21 of PR #97's 159 changed paths (4 source + 3 test/build paths in §16; 7 source + 7 test paths in §17). The remaining 138 paths still require per-path semantic disposition, and the complete reverse-consumer/dependency/duplication closure across the relevant branches and historical artifacts remains outstanding. This tranche does not close Gate A/B, select a source baseline, authorize donor adoption, start Stage A or authorize runtime implementation.


## 18. Bounded semantic source audit — action execution, goal feedback, affective planning and runtime integration (2026-11-19)

**Exact PR #192 source snapshot:** `c14b0d7b949957d6456f97235a31e487020cf87d`. Source files were fetched at this exact revision and match the comparison-baseline blobs recorded below.  
**Donor:** PR #97 exact HEAD `c1da222e6c94aeb3f2ad000392c21fe4fc81ab25`.  
**Comparison baseline:** main source snapshot `1273ddbcd0087d189e01388ded2d362fb1e058d2`.  
**Scope:** Eight existing core implementation paths, four donor-only core implementation paths, and eight donor test paths. This is a bounded third semantic tranche, not closure of the 159-path inventory.

### 18.1 Existing-path comparisons

| Path | Donor blob and observed responsibility | Current PR #192 blob and observed responsibility | Semantic disposition |
|---|---|---|---|
| `core/cpp/src/action_execution.cpp` | `af5bed6cec9ed1309b24ed3d50241fb4c0d33bff`. Preserves expected consequence in the result and optionally records a finite, bounded observed consequence/error after the execution callback reports execution. Verification failure and rollback are kept distinct from execution. | `c2f8653eb755fa2790a88e49bc8b0b9c3077e439`. Performs authorization, execution, verification and optional rollback, but has no observed-consequence callback/result path. | **Adaptation candidate.** Consequence observation is useful only when tied to a trustworthy measurement. The donor callback is gated by `result.executed`; it does not establish observation of every partial side effect or failed executor attempt. Failure/rollback/timeout semantics need explicit tests. |
| `core/cpp/src/decision.cpp` | `012025bc2ef66b1b9555b9b9f2b220b49c8d36c4`. Extends candidate ranking and classification with valence, arousal, affective uncertainty, tension and stability, including affect-sensitive exploration and urgency. | `6a49e0f1f80c3c6b0955ddf98182fc6611c0e84c`. Ranks actions using utility, expected value, goal, plan, uncertainty, threat, risk, resource and urgency evidence; no affective dimensions are consumed by this decision implementation. | **Bounded adaptation candidate.** The donor's weights and equations are engineered priors, not learned emotion semantics. Affective input must not bypass authorization, safety constraints or deterministic action policy. |
| `core/cpp/src/planning.cpp` | `9fcc2317e5acf0bfc24865a89eb9a54b80f8a80a`. Adds affective utility, reversibility/exploration, tension-related risk penalty and stability modulation to plan-step scoring. | `aab022b7cbc06f380413395757d590b56a1f3a20`. Builds plans from goal, expected value, risk, resource and deadline context without affective state. | **Bounded adaptation candidate.** Validate that affect changes trade-offs only within existing planning constraints and does not turn internal state into a fixed action mapping. |
| `core/cpp/src/intent.cpp` | `9707d5b6da4ddede4dfc99d52f30e7cdc7eed032`. Uses goal outcome momentum in intent selection and adds affect-aware selection that modifies priority/urgency/uncertainty. | `4283a4255284c51257df6bad12734782f2a6cde9`. Selects intent from eligible goals, threat and uncertainty; it has no outcome-momentum or affect-aware selection path. | **Adaptation candidate.** Progress momentum and affective drive are explicit engineered update terms. Test noisy progress, regressions, stalled goals and competing priorities before accepting their influence. |
| `core/cpp/src/goals.cpp` | `afaedcfb0f2f68ff88b3a20e474fce04bb59815c`. Tracks bounded outcome momentum from progress deltas and uses progress/regression to adjust goal priority. | `778a829de8314e83b095af2f2c2a6b83baa769f4`. Supports goal lifecycle and progress updates but does not retain momentum or adapt priority from outcome history. | **Adaptation candidate.** This is a genuine experience-dependent goal-state update, but its fixed smoothing and priority coefficients need calibration against noisy, delayed and reversible progress signals. |
| `core/cpp/src/knowledge.cpp` | `21de8abbcd4426cb4ead70cb089e7d7c4ed0e81a`. Adds assimilation through a `KnowledgeEvidence` contract. | `25ecf822e6132f576266c1f86a964a227c7fb75f`. Assimilates the existing general `Evidence` contract and maintains source reliability metrics. | **Contract adaptation candidate.** Do not copy the overload without reconciling evidence identity, source reliability, confidence semantics and the Brain's existing event-journal schema. |
| `core/cpp/src/self_model.cpp` | `c1beeec968fa62fce8fb037f8b95a869031331ce`. Adds an explicit observed-performance update for an existing capability. | `3c6a375eadd6894a635d2e18023a7079cba97c86`. Tracks capability availability/performance and isolation/restoration, but lacks the explicit update operation. | **Small adaptation candidate.** Establish who owns the performance measurement and how it is journaled/replayed before exposing another mutation path. |
| `core/cpp/src/cognitive_runtime.cpp` | `cf00acb6abd52308343f3a0e7016e6173b945603`. Registers perception providers, exposes a bounded feedback queue, validates prediction/evidence/goal feedback, transports action-adapter results and updates the shared workspace from current Brain state. | `1a1383cedc42e357dc9efce117328b8d55e30bca`. Owns the cognitive worker/input/result queues and workspace, but does not contain the donor's provider registration, action adapter or structured feedback-queue path. | **Major integration candidate, not a drop-in replacement.** It joins observation, provider evidence, action execution and feedback into the runtime lifecycle. Queue shutdown, ordering, backpressure, replay idempotence and provider failure behavior must be reviewed as one contract. |

### 18.2 Donor-only integration paths

| Path | Exact donor blob | Observed responsibility | Disposition |
|---|---|---|---|
| `core/cpp/src/brain_action_execution.cpp` | `3b66bafb438cd28790e6f25611b96c86f1eff05c` | Implements Brain-owned action execution, consequence prediction/observation, event recording, affective significance and replay/feedback integration. | **New integration candidate.** No same-path implementation exists in the inspected main/PR #192 source. Must be assessed against current Brain event ownership and the existing action authorization/execution boundary. |
| `core/cpp/src/brain_affective_planning.cpp` | `2a9406257c23f3a66a64071842be7d6448799406` | Connects Brain affective state/appraisal, affect-aware planning/intent, and developmental strategy evidence to candidate action selection. | **New integration candidate.** It combines multiple mechanisms, but its weighted influence and state lifecycle require calibration, replay and interference tests. |
| `core/cpp/src/brain_prediction_context.cpp` | `b3ceff150f3fe8223dc3f76f4c298ac264d72dae` | Uses generalized concepts/contextual associations and adaptation metrics to calibrate prediction value/confidence. | **New integration candidate.** Require held-out prediction error improvement and provenance-preserving feedback, not just successful prediction creation. |
| `core/cpp/src/affective_state.cpp` | `563a61cd8f6440f78a084f76a799b2c84bdd6813` | Implements bounded continuous affective state update and decay from outcome, prediction error, novelty, salience, uncertainty and confidence signals. | **New mechanism candidate.** The weighted equations, normalization and decay constants are engineered priors. The affective-learning header is a separate learning component; do not treat the translation unit itself as proof of learned calibration. |

### 18.3 Exact donor test evidence and registration

| Test path | Exact donor blob | Source-level behavior inspected |
|---|---|---|
| `core/cpp/tests/action_execution_phase7_suite.cpp` | `db11ac95d26a97b01dfeb67cfb85194dc284ffb8` | Expected/actual consequence separation, consequence error, authorization rejection, execution failure and verification/rollback status. |
| `core/cpp/tests/affective_decision_learning_suite.cpp` | `920ddcbc8a422783bb8724093afd952cc885e6b6` | Appraisal-weight calibration, affective updates and a Brain-level decision-score change after new evidence. |
| `core/cpp/tests/affective_planning_suite.cpp` | `32e5f04cfb6e4764cb205744266375367228bedf` | Affective state changes intent/planning scores while preserving the selected goal and safe action in the bounded scenario. |
| `core/cpp/tests/goals_architecture_suite.cpp` | `0b99d090b400d0af50b186cd3a416fa28a177b99` | Positive progress reinforces priority, regression reduces it, and goal momentum influences later intent selection. |
| `core/cpp/tests/cognitive_runtime_learning_integration_suite.cpp` | `656de56b1368e40afb090778a7a5504ab4208056` | Runtime action execution receives observed consequences and later action selection changes; the scenario also exercises context-specific learning/reversal/reconstruction. |
| `core/cpp/tests/cognitive_runtime_goal_feedback_suite.cpp` | `15a6bdffe37ae7df6c625ea9737fda4c0bf08a7f` | Asynchronous feedback updates goal progress/completion and records corresponding memory events. |
| `core/cpp/tests/brain_action_consequence_integration_suite.cpp` | `7616082579d53e3579cae8e87895bdb3dadba66f` | Brain action choice before/after consequence feedback and the expected/observed consequence result. |
| `core/cpp/tests/affective_evidence_suite.cpp` | `c8a401cab1a29d57506f990043a1f82536fd9029` | Prediction-sequence validation, affective evidence, decision influence and affect restoration after journal replay. |

The donor test-registration file is `core/cpp/tests/CMakeLists.txt`, blob `cbfd1fde52fffa6eeac025da2b7ddcb5ab493261`. The inspected file declares and registers the action-execution, affective-decision-learning, affective-evidence, goal-feedback, Brain action-consequence and cognitive-runtime learning integration targets, and declares the goal architecture target. The affective-planning test has a separate CMake registration fragment. This verifies donor source-to-target declarations only; it does not prove these targets executed in a specific CI run.

### 18.4 Integrated capability interpretation and limits

1. This tranche shows that the donor's strongest potential value is not the affective state class alone. It is the combined path: action authorization/execution → measured consequence → prediction/goal feedback → affective and strategy updates → later planning/decision changes → replay.
2. The donor action observer is invoked only when the executor reports `result.executed`. The tests distinguish execution failure from a measured consequence; they do not establish complete observation of partial side effects, failed external actions or all rollback outcomes.
3. Affective values influence intent, planning and decision scores through fixed weights and equations. A separate learner adjusts appraisal weights, but that does not make the entire affective model data-discovered or remove its engineered priors.
4. Goal progress momentum is an explicit learned state variable, but its update coefficients and priority changes remain hand-engineered. It needs noisy-progress and competing-goal evaluation.
5. The runtime provider/feedback additions are a real integration proposal. The current production cycle still does not call the perception/representation pipeline; separate compilation and tests do not close that integration gap.
6. No test in this tranche was built or executed. Exact donor source/test identities and CMake declarations are source evidence only. No new CI or held-out capability result is claimed.

**Disposition for this tranche:** retain the eight existing-path comparisons and four donor-only paths as historical evidence; treat action consequence, affective planning, goal feedback and provider-enabled runtime as selective integration candidates; require strict event/persistence/authorization and failure-boundary review; and reject wholesale donor adoption. No source baseline is selected.

**DF-02 remains OPEN.** Sections §16–§18 now provide bounded semantic dispositions for 41 of PR #97's 159 changed paths (21 paths in §16–§17; 20 paths in this tranche). The remaining 118 paths still require per-path semantic disposition, and full reverse-consumer/dependency/duplication closure across the relevant branches and historical artifacts remains outstanding. This tranche does not close Gate A/B, select a source baseline, authorize donor adoption, start Stage A or authorize runtime implementation.


## 19. Bounded semantic source audit — evolution isolation, safety and adoption transaction controls (2026-11-19)

**Exact PR #192 source snapshot:** `4af7bc36112d0e85569bd7bb77c75d6dc247dc75`.  
**Donor:** PR #97 exact HEAD `c1da222e6c94aeb3f2ad000392c21fe4fc81ab25`.  
**Comparison baseline:** main source snapshot `1273ddbcd0087d189e01388ded2d362fb1e058d2`.  
**Scope:** Seven evolution/process-control implementation paths and four additional donor test paths. The adoption-journal and canary test sources were already counted in §17 and are not counted again here.

### 19.1 Safety-critical source comparisons

| Path | Donor blob and behavior | Current PR #192 blob and behavior | Semantic disposition |
|---|---|---|---|
| `core/cpp/src/evolution_sandbox.cpp` | `364641cf3616db100dd54853d12293341d609116`. Treats a callback-provided `isolated=true` as untrusted, forcibly clears isolation, and reserves trusted isolation evidence for the process-isolated command path. | `837ab2adb087284fb370b623371693660b47624a`. Accepts the callback's Boolean isolation claim if true and rejects only when it is false. | **Safety correction candidate.** A callback's assertion is not proof of a process boundary. The current mainline contract can accept a self-asserted isolation flag; the donor closes that trust error for callback execution. |
| `core/cpp/src/evolution_experiment_runner.cpp` | `0545662ea0ef865feb0527207fc4c32ecb50566e`. The callback runner explicitly marks results non-isolated; adds `run_isolated_command`, requiring a started, isolated, completed, non-timeout, non-output-limited, successful process and a fully parsed finite fitness result before issuing isolation attestation. | `83d3c26e589cd16151818774a81ccb62f9d514fc`. Uses the sandbox callback result's `isolated` Boolean as part of the validity decision; no process-command attestation path exists in this file. | **Safety-critical adaptation candidate.** This is a meaningful trust-boundary improvement. The callback path must remain simulation-only; production adoption must require verified process-boundary evidence. |
| `core/cpp/src/evolution_safety.cpp` | `5a4669de9296958eacc77534bad87ce7c30ae52d`. Rejects invalid/non-finite/range-invalid evidence, requires a valid isolation attestation when policy says so, and recomputes the claimed improvement against the minimum-improvement threshold. | `6c930ebbe69ad92fe155e3c169e3e996442f22cf`. Checks the Improved label, finite baseline/candidate values, confidence minimum and maximum regression, but does not enforce the donor's attestation and complete finite/range checks. | **Safety-critical adaptation candidate.** Do not enable autonomous evolution using the current weaker gate. The donor checks are still subject to independent review and failure-injection testing. |
| `core/cpp/src/evolution_adoption_journal.cpp` | `d8df30a2902d3dac734fb1a571cbbecdd881b76f`. Stores the complete experiment identity/evidence, rejects mismatched restaging, and adds explicit `restore_pending` / `restore_adopted` transitions for compensation after failed durable-history writes. | `a9e141ac0b784466e86575eefdb3260b2e15dfc0`. Stores a smaller record, permits a repeated stage on an existing pending record to overwrite evidence, and has no compensation restoration methods. | **Safety-critical adaptation candidate.** This protects experiment identity and transaction recovery. It still requires crash-window testing across model, journal and history writes; an in-memory journal alone is not durable evidence. |
| `core/cpp/src/evolution_canary.cpp` | `8773507b4bc5842c60b78bcb384f09ea4c4caa2b`. Adds a non-mutating preview path alongside observation/evaluation/reset. | `b40c2eec58db1a3f7d3007781f0a5e6abe8c70a9`. Supports observation/evaluation/reset but has no preview operation in this implementation. | **Small adaptation candidate.** Preview can support decision inspection without consuming canary state; confirm it is side-effect free and cannot be mistaken for a committed observation. |
| `core/cpp/src/process_isolation.cpp` | `8bb621fc986b4957f079bfdf99f4a1038949bc72`. Includes the bounded process backend and prepares the argument vector before `fork`, avoiding allocation in the multithreaded child before `exec`; retains timeout/output/resource and required-isolation failure handling. | `eac7a12fafe36b6c5f463ad0a41caa3bb835a61c`. Contains the same broad isolation backend and failure handling, but the donor adds the pre-fork argument preparation hardening. | **Selective hardening candidate.** Preserve platform-specific fail-closed behavior and verify the fork/exec path under sanitizers and multithreaded runtime load. |
| `core/cpp/src/evolution_orchestrator.cpp` | `c913ff0f42fc4647605376579b3f343b5c12c387`. Explicitly evaluates all candidates before selecting at most one winner; requires durable evaluation history before adoption and handles canary rollback lifecycle. | `efd55281ba7d2edf95c6a9f6537ed2944022617e`. Already has scheduling, candidate evaluation and at-most-one adoption structure, but lacks the donor's explicit durable-evaluation precondition commentary/contract at the selection boundary. | **Existing mechanism with a stronger evidence contract candidate.** The orchestrator is not itself the safety boundary; its calls must be backed by the controller, journal and process-isolation invariants. |

### 19.2 Additional exact donor test evidence

| Test path | Exact donor blob | Source-level evidence inspected |
|---|---|---|
| `core/cpp/tests/evolution_experiment_runner_suite.cpp` | `307fe75b42f804d9bb2b0e8199df1e9cf773e3c6` | Real isolated-command attestation, rejection of callback-claimed isolation, and invalidation of timeout/failed process results. |
| `core/cpp/tests/process_isolation_suite.cpp` | `6539da294b55e537ed28c08f3f72aff5f6b869e2` | Process output, output limit, timeout, unavailable required isolation, network isolation and invalid-command behavior. |
| `core/cpp/tests/evolution_opportunity_orchestration_suite.cpp` | `24d6dd905cb537cc6c14e329db6a7d52d49c97b8` | Multi-candidate evaluation and at-most-one adoption lifecycle. **Important limit:** this simulated orchestration test explicitly sets `safety.require_isolation = false`; it is not evidence that production evolution runs with isolation enabled. |
| `core/cpp/tests/evolution_experiment_coordinator_suite.cpp` | `5b410197e3c5e48acb381e274ae22e8ba037aa84` | Baseline/candidate batch execution and fitness comparison in a bounded coordinator scenario. |

The previously inspected donor tests remain relevant to this tranche: `evolution_adoption_journal_suite.cpp` checks pending/adopted/rolled-back compensation transitions, and `evolution_canary_controller_suite.cpp` checks canary rollback and replay. Their blobs are recorded in §17; they are not counted a second time.

### 19.3 Engineering conclusion

1. The most consequential donor improvement in this tranche is the distinction between a candidate callback claiming isolation and a process boundary independently attesting isolation. The current mainline sandbox/runner combination trusts a Boolean supplied by the callback; the donor refuses to do so.
2. The donor safety gate and adoption journal strengthen evidence validation and compensation, but neither makes evolution safe by declaration. The full transaction spans process execution, evaluation, model mutation, journal transition and durable history; every failure window needs explicit injection tests.
3. A simulated orchestration test that disables isolation is useful for testing scheduling/selection logic only. It cannot support a production self-modification readiness claim.
4. No tests in this tranche were built or executed. These are exact donor source/test identities and source-level assertions only. No new CI run or safety acceptance is claimed.

**Disposition for this tranche:** treat sandbox/runner/safety-gate/adoption-journal changes as mandatory safety correction candidates before any autonomous evolution path is enabled; retain the process-isolation hardening selectively; and keep orchestration as a consumer of verified safety controls, not a replacement for them. No donor is adopted or selected as a baseline.

**DF-02 remains OPEN.** Sections §16–§19 now provide bounded semantic dispositions for 52 of PR #97's 159 changed paths. The remaining 107 paths still require per-path semantic disposition, with complete reverse-consumer/dependency/duplication closure across relevant branches and historical artifacts still outstanding. This tranche does not close Gate A/B, select a source baseline, authorize donor adoption, start Stage A or authorize runtime implementation.


## 20. Build-graph and Brain API ownership audit — orphaned restored API versus donor-integrated runtime (2026-11-19)

**Exact PR #192 source snapshot:** `08208091b46353074da84505dbf3a5c194f2c364`.  
**Donor:** PR #97 exact HEAD `c1da222e6c94aeb3f2ad000392c21fe4fc81ab25`.  
**Comparison baseline:** main source snapshot `1273ddbcd0087d189e01388ded2d362fb1e058d2`.  
**Scope:** The Brain public contract, restored-API translation unit and core CMake build graph. These three paths were not included in the earlier semantic tranches.

| Path | Donor evidence | Current PR #192 evidence | Semantic disposition |
|---|---|---|---|
| `core/cpp/include/jarvis/core/brain.hpp` | Blob `671186f4c39879a182f9e511394fc564d86f2988`. Includes developmental-learning and affective-state/learning contracts; exposes affective and contextual-strategy APIs; owns `DevelopmentalLearning`, `AffectiveStateModel` and `AffectiveLearningModel` as Brain state. | Blob `8268ef84e0b361ead536724ba7761904b30ee58f`. Owns the existing memory, association, causal, adaptation, attention, evolution, goal and decision mechanisms, but does not declare the donor's affective/developmental members or APIs. | **Substantial Brain contract expansion candidate.** The donor header makes the additional state ownership explicit. It must be reconciled with existing Brain APIs, event replay and public type contracts before adoption. |
| `core/cpp/src/brain_restored_api.cpp` | Blob `7155d4d9c8eef527836fb79bf901aa32ddbae38b`, 405 lines. Implements the expanded Brain API, including affective/developmental access, affect-aware/developmental action selection, sequence-addressed prediction feedback and related restored operations. | Blob `618deb6976eed951eae02b7f0da741e6d730bb0c`, 77 lines. It contains method definitions that reference affective/developmental members absent from the current `brain.hpp`. The current core CMake target does **not** compile this file. | **Uncompiled orphan/stale fragment in current main, not an executable successor.** Its presence in the repository must not be counted as live runtime capability. Adding it to the current target without the matching header/state contracts would be invalid. The donor pairs it with the expanded Brain header and build graph. |
| `core/cpp/CMakeLists.txt` | Blob `bc264ce7b4ae489404ca03ea6d9676d0330a6a56`. Adds `brain_restored_api.cpp`, `brain_affective_planning.cpp`, `brain_prediction_context.cpp`, `affective_state.cpp`, `affective_learning.cpp` and `developmental_learning.cpp` to `jarvis_core` (alongside existing sources). | Blob `c51816888e1bddb7bc00c59e72529524e27a0717`. Compiles the existing core sources and `perception_pipeline.cpp`, but omits those donor-specific translation units, including the current orphan `brain_restored_api.cpp`. | **Build-graph integration gap.** Donor-only source files are not production capabilities on current main simply because their files exist. Conversely, donor CMake registration is not proof of successful compilation or correct runtime behavior. |

### 20.1 Why this changes the baseline assessment

The current tree contains a misleading same-path artifact: `brain_restored_api.cpp` looks like an implementation of affective/developmental Brain methods, but its matching state members and declarations are absent from the current Brain header and the translation unit is excluded from the production `jarvis_core` target. Those functions are therefore not evidence that current main already runs the donor's affective/developmental mechanisms.

PR #97 is more internally integrated at the source/build-graph level: its header, implementation translation units and CMake source list are aligned. That makes the donor a meaningful integration candidate, not an approved replacement. Its event replay, prediction identity, action feedback, failure ordering and build/test evidence still require exact-SHA validation.

**Disposition for this tranche:** classify the current `brain_restored_api.cpp` as an uncompiled orphan, the donor Brain header/API as a substantial integration candidate, and the donor CMake additions as build-graph changes requiring verification. Do not count uncompiled source as implemented capability or select the donor baseline on this evidence alone.

**DF-02 remains OPEN.** Sections §16–§20 now provide bounded semantic dispositions for 55 of PR #97's 159 changed paths. The remaining 104 paths still require per-path semantic disposition, including the eight workflows, core build/example paths, remaining public headers and implementations, tests, documentation/specifications and engineering-coordination files. Complete reverse-consumer/dependency/duplication closure across relevant branches and historical artifacts remains outstanding. This tranche does not close Gate A/B, select a source baseline, authorize donor adoption, start Stage A or authorize runtime implementation.


## 21. Donor workflow, build graph and runnable developmental-world example audit — 2026-11-19

**Exact PR #192 source:** `a602658bfe488812b882b8c2d15c8d6755c79a1f`.  
**Donor PR #97 exact HEAD:** `c1da222e6c94aeb3f2ad000392c21fe4fc81ab25`.  
**Main comparison baseline:** `1273ddbcd0087d189e01388ded2d362fb1e058d2`.  
**Scope:** all eight donor workflow files, the core CMake source graph, and all three example files (12 of 159 PR #97 changed paths). Exact donor and main/current-PR file blobs were fetched. A NOT_FOUND at main/current is recorded as path absence, not as proof that equivalent behavior is absent elsewhere.

### 21.1 Workflow dispositions

| Workflow path | Donor blob | Main/current PR #192 result | Semantic disposition and material limits |
|---|---|---|---|
| `.github/workflows/brain-ci.yml` | `74182cd073ef4b1eec77f78800f96c337545007e` | Main and current PR #192 both resolve to identical blob `0d5d0c9b9528a418e3c1358420ee2ea708c4dd8c`. | **Preserved exactly.** Runs Release build/CTest plus ASan/UBSan build/CTest. Donor adds `feat/jarvis-affective-state` to push branches; main's workflow is otherwise byte-identical. The branch-filter change is historical branch-specific CI wiring, not a cognitive capability. |
| `.github/workflows/dlt-001-long-run.yml` | `1706d3b41552f43f0e3b172b61da092f8fc053d7` | Absent at main and current PR #192 exact trees. | **Donor-only long-run orchestration.** It automatically starts a two-hour run on pushes to `feat/jarvis-affective-state` when either trial source file changes, as well as allowing manual dispatch. This is a material cost/operational risk: a code push can launch a 130-minute job. No run result or completed trial is established by workflow source. |
| `.github/workflows/dlt-002-four-hour.yml` | `52d08751d29c1b7c7b60e07834ac1bfdc4eba626` | Main and current PR #192 both contain the exact same blob. | **Preserved exactly.** Despite its filename, the job runs a 330-minute challenge (five and a half hours), with manual dispatch, deterministic seed input, existing-journal overwrite guard, cross-process persistence gate, six-phase smoke test and artifact retention. The filename is misleading; the workflow is not a four-hour run. Its manual-only trigger avoids automatic long-run cost. |
| `.github/workflows/dlt-002-overnight-validation.yml` | `7ac465a333a2191cdc76e488bcafac4a8fe08802` | Absent at main and current PR #192 exact trees. | **Donor-only full-suite/soak workflow.** Manual dispatch; accepts a bounded 1–240 minute soak, runs the full registered suite, repeats persistence training and verification in separate processes, and uploads logs. The 290-minute job timeout bounds the maximum 240-minute soak plus setup/test overhead. Source inspection does not prove the executable targets exist or the workflow has passed. |
| `.github/workflows/jarvis-brain-probe-001.yml` | `812a0fdbb706ca4e12a9b31efc4f1e2af0a6e483` | Absent at main and current PR #192 exact trees. | **Donor-only focused probe.** Manual 5–30 minute run; checks six environment phases and requires at least one resolved-prediction evidence field. It reuses the DLT-002 executable and persistence target. The summary line that prints PASS is emitted after CTest, but the actual executable challenge must still pass its log/phase/forecast assertions; no execution is established. |
| `.github/workflows/jarvis-core.yml` | `60e6ec17ad6078bc8ad767c8375540629de0f143` | Absent at main and current PR #192 exact trees. | **Donor-only legacy CI wiring.** Debug configure/build/CTest with actions/checkout@v4 and branch filters for two feature branches. It lacks explicit read-only permissions and timeouts. This overlaps the preserved `brain-ci.yml` verification path and is a candidate for consolidation, not a distinct Brain capability. |
| `.github/workflows/jarvis-learning-seed-sweep.yml` | `f40a859a9b6b4f8138cd14df9fa09ad362f3515c` | Absent at main and current PR #192 exact trees. | **Donor-only multi-seed behavioral evaluation.** Runs three independent seeds, records episode-level optimal-action rates by phase, compares against fixed-action baselines and records unseen-context probe decisions. Important limitation: the control is a fixed action policy, not a matched Brain with learning disabled; results can support descriptive performance, not isolate causal learning benefit. It also has a push trigger on the feature branch, so one qualifying push can launch three parallel jobs. |
| `.github/workflows/jbp-mem-001.yml` | `82cec28819357a26881584b4ceb951c258ea24ac` | Main/current PR #192 blob `9e1efd73a9a91a70c1d9ceda0d6b458f9bdd7f7f`. | **Adapted and improved in main.** The main version adds an explicit `source_ref` input, checks out the requested brain revision, and records both workflow commit and tested commit. Donor version tests the workflow's own checked-out ref. Both run memory suites and separate-process persistence checks in a 30-minute soak. Main is the clearer reusable validation harness; no workflow execution is proven here. |

### 21.2 Build graph and runnable example

| Path | Donor blob | Main/current PR #192 result | Semantic disposition |
|---|---|---|---|
| `core/cpp/CMakeLists.txt` | `bc264ce7b4ae489404ca03ea6d9676d0330a6a56` | Main/current blob `c51816888e1bddb7bc00c59e72529524e27a0717`. | **Build-graph integration candidate.** Donor registers affective/developmental and Brain integration translation units, includes the affective-planning CMake test fragment, and exposes an opt-out `JARVIS_BUILD_EXAMPLES` option defaulting ON. The current main graph already compiles a broad Brain/evolution/perception core but omits these donor-specific units and example subdirectory. Registration does not prove successful compilation or behavior. |
| `core/cpp/examples/CMakeLists.txt` | `31b61c8566062fe5d7c06c3e4dcf8a5f18e0c1eb` | Absent at main/current PR #192 exact trees. | **Donor-only example target registration.** Builds `jarvis_developmental_world` and links it to `jarvis_core`. It is operational wiring, not a cognitive mechanism. |
| `core/cpp/examples/README.md` | `ab5537cfc152a3fb467d256ff9ef749c4a22987b` | Absent at main/current PR #192 exact trees. | **Donor-only usage/evaluation description.** Documents a controlled route-choice world with a context reversal, observable consequence feedback and a persistent journal option. It explicitly limits the example: no open-ended natural-language perception or arbitrary real-world action. Documentation is not execution evidence. |
| `core/cpp/examples/developmental_world.cpp` | `d865c8d66c4529be78c3d7c2cd1a0ed4eb10d3e6` | Absent at main/current PR #192 exact trees. | **Donor-only runnable integration candidate.** Drives 24 sequential episodes through `CognitiveRuntime`, with clear conditions for episodes 0–7 and a reversal for 8–23, observes consequences, and prints learned strategies plus journal event count. The environment's consequence callback supplies outcome feedback but the action adapter's execute/verify callbacks unconditionally return true; this is a simulated world, not external actuation or safety validation. The example source alone does not establish that the selected action improves across the reversal or that a restarted process retrieves the same learned strategy. |

### 21.3 Cross-workflow operational findings

1. Two donor workflows have push triggers that can launch repeated behavioral/long-running trials: DLT-001 can start a two-hour run, while the seed sweep can start three concurrent trials. Before enabling either on a shared/production branch, require manual dispatch or explicit concurrency/budget controls. This is an operational safety finding, not a proposal to change workflow files during this documentation audit.
2. The donor distinguishes short probes, multi-seed sweeps, cross-process persistence and long-duration soak tests. These are complementary evidence channels, but a green workflow cannot by itself establish general learning, robust transfer or causal attribution.
3. The fixed-policy control in the seed sweep is weaker than a matched no-learning control. A stronger experiment would compare the same initialized Brain/environment with learning updates disabled, preserve identical seeds and observations, and evaluate held-out contexts and reversals. This is an evaluation-design requirement, not evidence that the donor currently does so.
4. The DLT-002 filename `dlt-002-four-hour.yml` does not match its 330-minute duration. Preserve the historical file identity; record the mismatch rather than silently renaming a historical artifact.
5. The preserved main `brain-ci.yml` already supplies native and sanitizer verification. The donor-only `jarvis-core.yml` overlaps it and uses older action versions/less restrictive permissions. It should not be counted as additional cognitive capability or automatically imported.

**Disposition for this tranche:** eight workflows and four build/example files now have explicit donor/current-main dispositions. Two are byte-identical in main, one is adapted in main, and nine are absent under the same path in main/current PR #192. The absent files are donor-only artifacts, not automatically deleted capabilities; relevant code/tests and consumer searches remain necessary. No workflow was dispatched, no runtime build/test/training was run, and no donor file was adopted.

**DF-02 remains OPEN.** Sections §16–§21 now provide bounded semantic dispositions for 67 of PR #97's 159 changed paths. The remaining 92 paths require per-path semantic disposition. This tranche does not complete reverse-consumer/dependency/duplication closure across relevant branches or historical artifacts, and it does not close Gate A/B, select a source baseline, authorize donor adoption, start Stage A or authorize runtime implementation.
