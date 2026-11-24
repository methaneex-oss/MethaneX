# Gate A — Independent Technical Review of Final Baseline Recommendation

**Review date:** 2026-11-04  
**Review target:** PR #175 — `plan/brain-implementation-roadmap-20261103`  
**Live PR head inspected:** `55092a48dc7c0bc2f4deee1a9a994c8db30b7de4`  
**Final Builder report:** `13_GATE_A_FINAL_BASELINE_RECOMMENDATION_2026-11-04.md`  
**Report blob SHA:** `2ca7ed87f2acf8373264d371ee5e525541a6411c`  
**Report source branch:** `plan/brain-implementation-roadmap-20261103`  
**Governing specification:** PR #174 accepted HEAD `0811a59e46bf934e32e794f90e4e7d18d4e2bd97`  
**Candidate donor:** PR #156 code-bearing parent `15d49e5fdeb5723c475922ab78fb92f97c4b3b84`  
**Review type:** Independent technical/documentary review; not a submitted GitHub review

---

## 1. Executive verdict

**VERDICT: NOT CLEARED — technical integration recommendation is defensible, but Gate A evidence closure is incomplete.**

The Builder's central recommendation is sound as a *direction for a future integration strategy*:

- Use accepted PR #174 HEAD `0811a59e46bf934e32e794f90e4e7d18d4e2bd97` as the specification-governed integration starting point.
- Treat PR #156 code-bearing parent `15d49e5fdeb5723c475922ab78fb92f97c4b3b84` as a donor/source reference.
- Do not merge or adopt PR #156 wholesale.
- Port mechanisms selectively, with source attribution, specification mapping, defect treatment and acceptance evidence for each work package.

I find this substantially more defensible than either wholesale branch adoption or discarding the candidate implementation. The recommendation preserves the accepted design authority while retaining potentially valuable existing mechanisms.

However, **a defensible strategy is not the same thing as a reconciled and approved implementation baseline**. The report itself records open API compatibility, workflow continuity, historical attribution and candidate defect obligations. Two confirmed candidate defects remain unfixed. The PR description also remains stale relative to the final report and current PR head. Therefore I do not clear Gate A or select a baseline on the Project Director's behalf.

This verdict does not authorize runtime implementation.

## 2. Exact evidence snapshot and review method

I inspected the live PR #175 metadata and fetched the final report from the planning branch. The live PR head at review time was:

`55092a48dc7c0bc2f4deee1a9a994c8db30b7de4`

The final report fetched from that branch had blob SHA:

`2ca7ed87f2acf8373264d371ee5e525541a6411c`

The live PR remained open, draft and unmerged. Its base ref resolved to the accepted specification commit `0811a59e46bf934e32e794f90e4e7d18d4e2bd97`.

I reviewed the final report against the supporting Gate A artifacts, including the semantic reconciliation addendum, provenance matrix, API compatibility matrix, workflow continuity matrix, candidate defect disposition and independent-review packet. I also checked the PR's current description and submitted review list.

This is a static evidence review. It is not a fresh local clone, full re-execution of every historical comparison, build, test run, workflow run, ABI inspection or exhaustive repository-wide symbol search. I distinguish what the supplied artifacts establish from what remains unverified.

## 3. Findings independently supported

### 3.1 The baseline strategy is coherent

The comparison described in report 13 gives a rational basis for rejecting wholesale adoption:

- Candidate PR #156 and current `main` have materially divergent histories and final trees.
- The candidate is reported as 1,428 commits ahead of current `main`, while current `main` is nine commits ahead of the candidate code-bearing parent.
- The accepted specification commit is reported as 12 commits ahead of current `main`, with the net additions consisting of accepted architecture/specification documentation.
- The candidate code-bearing parent predates the accepted specification point.

These facts support the conclusion that PR #156 is not a clean forward upgrade and should not be adopted as a whole branch.

Using the accepted specification commit as the integration starting point also preserves a clear authority relationship: the implementation work is brought into alignment with an accepted specification rather than allowing a pre-specification candidate branch to define the architecture implicitly.

**Disposition: ACCEPT the strategy as the preferred integration direction, not as a completed baseline selection.**

### 3.2 The candidate contains meaningful reusable work, but is not specification-complete

The final report identifies candidate mechanisms across experience/event journaling, representation, memory, belief/world state, association and prediction, attention, affective appraisal, goals and intent, developmental learning, metacognition, reasoning, coordination, evolution and training infrastructure.

The report also correctly distinguishes source presence from demonstrated capability. In particular, it does not claim that:
- memory retrieval is already demonstrated as provenance-bearing reasoning premises that materially change inference;
- current causal/prediction mechanisms establish general causal discovery;
- attention structures prove reliable multi-context control;
- goal lifecycle support proves experience-derived candidate-goal formation;
- reflection proves a complete diagnose/correct/re-evaluate loop;
- additive feature composition proves parity/XOR or general compositional reasoning;
- the historical 73/73 CTest result proves all 34 accepted specification scenarios.

This is an important and technically correct distinction. The candidate should be treated as a mechanism donor whose components must earn acceptance through integrated evidence-dependent behavior.

**Disposition: ACCEPT the characterization as a reusable but incomplete mechanism set.**

### 3.3 D1 — learned-strategy context defect

The evidence in artifacts 06 and 11 describes a concrete identity mismatch:

- `GoalModel::eligible()` can include pending and active goals.
- `IntentModel::select()` selects among active goals using its own scoring.
- `Brain::choose()` and `Brain::choose_with_affect()` derive the learned-strategy lookup context from `eligible.front().id`, rather than the identity of the intent actually selected.

Those identities are not guaranteed to match. A pending goal can therefore supply the strategy context for a decision made under a different active goal.

The required invariant is correctly stated: strategy context must follow the selected intent identity, with an explicit fallback when no intent is selected.

**Disposition: CONFIRMED CORRECTNESS DEFECT; NOT FIXED.** This must be corrected and regression-tested before the affected decision/learning mechanism is accepted. It does not, by itself, require discarding the entire candidate donor.

### 3.4 D2 — non-finite goal input can be journaled before rejection

The report and defect disposition identify the ordering problem in `Brain::create_goal()`: numeric values are clamped and the event can be appended before `GoalModel::create()` rejects non-finite values. NaN can survive the clamping operation and enter the journal without a corresponding valid model state.

The required invariant is also correct: reject non-finite inputs before event construction, append, replay or state mutation, and ensure rejection is side-effect free.

**Disposition: CONFIRMED INPUT/PERSISTENCE-INTEGRITY DEFECT; NOT FIXED.** It must be corrected and tested for NaN and both infinities across fresh and restored/replayed state before the affected path is accepted.

### 3.5 Multi-event and evolution failure ordering

The report correctly keeps goal progress/completion and evolution evidence/rollback ordering as unresolved risks rather than promoting them to confirmed defects without failure-injection evidence.

The risks are material because event-sourced or journal-backed state must remain coherent when a later append, controller transition, restart or replay fails. The implementation plan must define whether these transitions are atomic, compensating, resumable or explicitly partial, and must prove the chosen contract.

**Disposition: OPEN.** Do not call these defects confirmed yet; do not silently waive them either.

## 4. Findings that prevent Gate A clearance

### 4.1 Historical provenance: risk-based approach is acceptable in principle, but its completion is not demonstrated

The evidence records a 165-path net tree inventory and enumerates 1,416 inherited commits. It also records 145 PR #97-only paths, 14 overlap paths and six post-PR #97 paths, with additional integration-path analysis.

I agree with the Builder's argument that mechanically producing a hunk-by-hunk ledger for every inherited commit is not automatically the best use of effort. A risk-based provenance standard can be more defensible if it identifies every final path, classifies its origin, prioritizes high-impact semantic changes and provides adequate evidence for every ambiguous or high-risk integration.

But the final report does not establish that the risk-based substitute is complete. It acknowledges that exhaustive per-commit origin/path/hunk attribution remains incomplete. The provenance matrix also records that high-risk semantic attribution is not fully closed.

The key issue is not whether all 1,416 commits have been exhaustively narrated. It is whether the final tree's high-risk behavior and integration changes are sufficiently explained to trust the donor selection. The report does not yet demonstrate that to a Gate A closure standard.

**Required closure:** provide a concise, evidence-backed list of high-risk final paths and their source/integration attribution, including overlap/conflict-resolution paths and the PR #97-only Brain mechanisms. For each, identify the source commit(s), relevant semantic change, final candidate location and any integration adaptation. Explain why any remaining unattributed history cannot change the baseline decision. A full historical ledger is not automatically required if this alternative is complete and independently checkable.

### 4.2 API compatibility: source-level comparison is advanced, caller compatibility is not closed

The semantic addendum establishes useful facts:
- 64 unique current-main Brain API names are present in the candidate.
- The candidate has seven additional unique API names.
- 24 common method-body differences have been classified.
- `beliefs()` was manually confirmed identical.
- `register_evolution_parameter()` changes from `void` to `bool`.

The report correctly avoids claiming ABI compatibility. It notes that inspected current-main direct calls ignore the return value, but function/member pointers, callbacks, type-erased references and downstream consumers have not been exhaustively inventoried. It also records that three candidate-only developmental strategy accessors had no occurrence in seven targeted test files; that is bounded no-hit evidence, not repository-wide proof of dead or unreachable APIs.

The 24 body classifications are useful, but they do not substitute for declaration/overload/caller compatibility. This is particularly important where signatures, ownership or lifecycle contracts differ.

**Required closure:** complete a static declaration/overload/call-site inventory for the signature-sensitive API and the seven candidate-only APIs, plus the remaining explicitly open caller inventory for the 24 changed methods. If full compatibility cannot be proven without a build, record the exact unverified boundary and make compilation/linkage a mandatory verification gate before any port is accepted. Do not claim the API workstream complete prematurely.

### 4.3 Workflow continuity: dispositions exist, equivalent coverage does not

The workflow matrix correctly classifies:
- one exact workflow-file match;
- one workflow requiring source-ref/tested-commit reproducibility controls;
- three workflows absent from the candidate, with only partial or target-level overlap.

It correctly states that CMake target-name presence is not build/pass equivalence and that a matching workflow blob is not evidence of a successful run on the candidate.

The final report says the five current-main validation workflows must be preserved or replaced with demonstrably equivalent workflows. That is the correct requirement, but the actual adaptations have not been implemented or validated, and no workflow execution was authorized.

**Required closure:** before treating validation continuity as complete, produce a workflow-by-workflow preservation/adaptation specification covering triggers/ref filters, tested commit identity, runner/dependencies, target and suite set, trial/seed controls, changing-environment behavior, timeout/failure semantics and artifacts. The five capabilities must remain traceable to an executable future validation plan. This review does not require running those workflows now.

### 4.4 D1 and D2 remain unfixed

The defects are documented well, but documentation is not remediation. The report itself says they remain unfixed and that runtime work was not authorized.

They therefore remain mandatory donor-port prerequisites. No one should import the affected behavior and mark it accepted before correction and regression evidence exist.

### 4.5 PR metadata and evidence index are inconsistent with the final report

At the live PR head inspected, the PR description still listed the earlier planning/review artifacts and said Gate A remained NOT CLEARED, but it did not list report 13 or the new closure artifacts 07–12. It also continued to present earlier Gate A blockers as if the final recommendation document had not been added.

This does not invalidate the report's technical content, but it weakens audit navigation and creates ambiguity about which evidence packet is current.

The independent-review packet 12 also contains stale commit pins from its preparation snapshot. The live PR head is `55092a48dc7c0bc2f4deee1a9a994c8db30b7de4`, not the older head recorded in that packet. The packet must be treated as a historical review guide, not as a current exact-head manifest, unless refreshed.

**Required correction:** update the PR description and review packet/evidence index to identify report 13 and this review, state the exact live head, and clearly label historical candidate source pins separately from the current planning-branch head.

## 5. Assessment of the Builder's final recommendation

| Builder conclusion | Independent disposition |
|---|---|
| Do not adopt PR #156 wholesale | **Agree** |
| Use accepted PR #174 HEAD as integration starting point | **Agree as strategy** |
| Treat PR #156 as selective source donor | **Agree, conditional on per-port evidence and defect remediation** |
| Candidate contains substantial reusable mechanisms | **Agree, with capability claims kept bounded** |
| D1 and D2 are confirmed defects | **Agree; both remain unfixed** |
| Full 1,416-commit hunk ledger can be avoided through risk-based attribution | **Agree in principle; current risk-based evidence not yet demonstrated complete** |
| API compatibility is sufficiently closed | **Disagree; caller/declaration compatibility remains partial** |
| Workflow continuity is sufficiently closed | **Disagree; three workflows are absent/partial and adaptations are not yet proven equivalent** |
| Gate A technical recommendation is complete | **Agree only in the narrow sense that a recommendation has been written; evidence closure and formal Gate A clearance are not complete** |

## 6. Minimum remaining work to reach a defensible Gate A decision

The smallest meaningful closure set is:

1. **Provenance:** finish high-risk path-level semantic attribution and explicitly disposition remaining unattributed history using the risk-based standard.
2. **API:** complete the remaining declaration/overload/caller inventory, especially `register_evolution_parameter()` and the seven candidate-only APIs; record exact compile/link verification requirements where static evidence is insufficient.
3. **Workflow continuity:** publish explicit preservation/adaptation requirements for all five workflows, with coverage and reproducibility semantics.
4. **Defect treatment:** retain D1 and D2 as mandatory pre-acceptance fixes for any affected ports; do not represent them as already fixed.
5. **Evidence synchronization:** correct the stale PR description and refresh the exact-head information in the independent-review packet.
6. **Independent re-check:** review the updated evidence snapshot. A formal GitHub review submission is a separate repository operation and requires an authenticated reviewer identity/account; this document is a technical review artifact, not such a submission.

No new runtime implementation is needed to complete these documentation/static closure items. Builds, tests, workflow runs and ABI checks remain later verification gates under separate authorization.

## 7. Final disposition and authority boundary

**Independent technical verdict: NOT CLEARED.**

**Baseline strategy:** accepted PR #174 HEAD is the defensible integration starting point; PR #156 is a conditional selective source donor, not a wholesale baseline.

**Baseline selection:** not made by this reviewer. The Project Director retains that decision.

**Implementation authorization:** not granted. No runtime source changes, builds, tests, workflow executions, merges, rebases or cherry-picks are authorized by this review.

This verdict is not a rejection of all candidate implementation work. It is a refusal to convert a plausible integration strategy into a formally cleared baseline while material provenance, API, workflow and defect obligations remain open.

## 8. Evidence reviewed

The following artifacts were fetched from the PR #175 planning branch during this review:

- `06_GATE_A_SEMANTIC_RECONCILIATION_ADDENDUM_2026-11-04.md` — blob `e7dff67082bb5b40d6fc78866946df2c9a60c257`
- `08_GATE_A_RISK_BASED_PROVENANCE_MATRIX_2026-11-04.md` — see live branch blob; includes 165-path inventory and provenance limitations
- `09_GATE_A_API_COMPATIBILITY_MATRIX_2026-11-04.md` — see live branch blob; API definitions, caller evidence and remaining checklist
- `10_GATE_A_WORKFLOW_CONTINUITY_MATRIX_2026-11-04.md` — blob `0459897e5de121e1ec6dcb819b3c56104bbd18b0`
- `11_GATE_A_CANDIDATE_DEFECT_DISPOSITION_2026-11-04.md` — blob `23d2b1d23b9f95d4786703ec9129ccd9a4cf36db`
- `12_GATE_A_INDEPENDENT_REVIEW_PACKET_2026-11-04.md` — blob `1d10603d8b9dec01da4dde6c8b348dfa3d7ec420`
- `13_GATE_A_FINAL_BASELINE_RECOMMENDATION_2026-11-04.md` — blob `2ca7ed87f2acf8373264d371ee5e525541a6411c`
- Live PR #175 metadata at head `55092a48dc7c0bc2f4deee1a9a994c8db30b7de4`; submitted review list was empty at inspection.

The report and supporting artifacts are evidence inputs. Their existence is not, by itself, proof that every underlying historical or runtime claim has been independently reproduced.

**End of independent technical review.**
