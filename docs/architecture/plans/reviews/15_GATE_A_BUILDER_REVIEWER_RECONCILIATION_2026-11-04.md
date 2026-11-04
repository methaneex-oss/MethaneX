# Gate A — Builder/Revi​ewer Reconciliation and Remaining Closure Items

**Date:** 2026-11-04  
**PR:** #175 — `plan/brain-implementation-roadmap-20261103`  
**Reconciliation snapshot before this document:** `c873e31d50808f4adc43daa09a25bff99f1b9443`  
**Builder report:** 13 — `2ca7ed87f2acf8373264d371ee5e525541a6411c`  
**Independent technical review:** 14 — `f9a9ff406842362a481a30b8ecbbbd4e58cfaaf6`  
**Governing specification:** accepted PR #174 HEAD `0811a59e46bf934e32e794f90e4e7d18d4e2bd97`

## 1. Purpose and result

This document reconciles the Builder's final baseline recommendation (Report 13) with the independent technical review (Report 14). It distinguishes agreement, additional reviewer findings, previously known open items, and the exact remaining documentation/static closure work.

**Disposition: GATE A REMAINS NOT CLEARED.**

The reviewer independently agrees with the central strategy:
- use accepted PR #174 HEAD as the specification-governed integration starting point;
- treat PR #156 code-bearing parent `15d49e5fdeb5723c475922ab78fb92f97c4b3b84` only as a conditional source donor;
- do not adopt PR #156 wholesale.

This is agreement on an integration direction, not baseline selection or implementation authorization.

## 2. Reconciled findings

| Area | Builder Report 13 | Reviewer Report 14 | Reconciled disposition |
|---|---|---|---|
| Baseline strategy | PR #174 start; PR #156 selective donor | Independently agrees | **AGREED — strategy only** |
| Candidate capability | Reusable mechanisms; not specification-complete | Independently agrees and supports bounded claims | **AGREED — capability acceptance not passed** |
| D1 learned-strategy context | Confirmed defect, unfixed | Independently confirms | **OPEN — mandatory pre-acceptance fix** |
| D2 non-finite goal journaling | Confirmed defect, unfixed | Independently confirms | **OPEN — mandatory pre-acceptance fix** |
| Multi-event goal/evolution ordering | Unresolved risks, not confirmed defects | Agrees they need failure-ordering evidence | **OPEN — define and prove consistency contract** |
| Provenance | 165-path accounting and 14 overlap blob checks; semantic closure incomplete | Risk-based method acceptable in principle, but completion not demonstrated | **OPEN — high-risk path semantic attribution** |
| API compatibility | 24 body differences classified; targeted caller evidence; inventory incomplete | Declaration/overload/caller compatibility remains insufficient | **OPEN — complete bounded static inventory; preserve compile/link gate** |
| Workflow continuity | Five workflows classified; adaptations not proven | Requires explicit workflow-by-workflow preservation/adaptation specification | **OPEN — document equivalence requirements** |
| PR evidence index | Reports 13 and 07–12 added to branch | PR description omits later reports; packet pins an older snapshot | **ADMINISTRATIVE CORRECTION REQUIRED** |
| Formal review | No formal GitHub review claimed | Report 14 is documentary, not submitted review | **NO FORMAL GITHUB REVIEW** |

No substantive finding in Report 14 reverses the baseline strategy in Report 13. The reviewer strengthens the reasons not to clear Gate A yet.

## 3. Additional closure requirements from Report 14

### 3.1 Provenance — high-risk final-path attribution

The existing 165-path inventory and 145 / 14 / 6 origin classes are path-set accounting, not semantic closure. The 14 overlap paths have direct blob checks, but blob differences alone do not explain the changed behaviour.

Required deliverable:
- identify high-risk final paths, including overlap/conflict-resolution paths and PR #97-only Brain mechanisms;
- for each, record source commit(s), relevant semantic change, final candidate path and any integration adaptation;
- cite the source/blob evidence already gathered;
- disposition remaining unattributed history and explain why it cannot alter the donor/baseline recommendation.

A full hunk ledger for all 1,416 commits is not an automatic requirement. The risk-based alternative must nevertheless be complete, bounded and independently checkable.

### 3.2 API — declaration, overload and caller inventory

The 24 common method-body differences have been classified, and the seven candidate-only APIs have been identified. Targeted caller evidence narrowed some questions but did not close the full inventory.

Required deliverable:
- inspect declarations, overloads and call sites for the seven candidate-only APIs;
- close the signature-sensitive `register_evolution_parameter()` return-type change (`void` on current main, `bool` in candidate), including typed references where statically discoverable;
- finish the remaining caller inventory for the 24 changed methods where compatibility can be assessed statically;
- explicitly record any ABI, compile or link property that cannot be established statically.

Do not claim ABI or build compatibility from source-name matching. Compilation/linkage must remain a mandatory later verification gate before affected ports can be accepted.

### 3.3 Workflow continuity — future validation specification

The five current-main workflows must be preserved or replaced with demonstrably equivalent controls. Required specification for each workflow:
- trigger and branch/ref filters;
- exact tested commit identity and source-ref reproducibility;
- runner, dependencies and setup;
- target and suite coverage;
- trial/seed controls and changing-environment behavior;
- timeout and failure semantics;
- artifacts and evidence retention.

The specification must distinguish workflow-file presence, CMake target registration, and actual successful execution. No workflow run is required or authorized in this documentation closure.

### 3.4 Defect and ordering obligations

D1 and D2 remain confirmed, unfixed candidate defects. They are mandatory remediation prerequisites for affected ports; this reconciliation does not authorize fixing them.

The multi-event goal completion and evolution rollback/replay cases remain unresolved risks, not confirmed defects. Define the consistency contract and the failure-injection/replay evidence needed to establish it.

## 4. Evidence synchronization

Report 14 inspected the PR at head `55092a48dc7c0bc2f4deee1a9a994c8db30b7de4`, which was a historical snapshot. Report 14 itself was subsequently committed as `c873e31d50808f4adc43daa09a25bff99f1b9443`.

The independent-review packet's original “latest documentation commit” pin (`e40f2f221875455ec21125eaad80979f0da45b2f`) is historical and must not be presented as the current PR head. The packet is being refreshed to make that distinction explicit. The PR description must index Reports 13, 14 and this reconciliation, and identify the current head after documentation updates are committed.

## 5. Minimum remaining closure checklist

- [ ] Complete risk-based semantic provenance for high-risk final paths and disposition residual unattributed history.
- [ ] Complete the bounded declaration/overload/caller inventory for signature-sensitive and candidate-only APIs, plus remaining changed-method callers.
- [ ] Publish five workflow preservation/adaptation specifications with reproducibility and coverage semantics.
- [ ] Keep D1 and D2 marked confirmed/unfixed; do not accept affected ports until corrected and regression-tested under separate authorization.
- [ ] Define failure consistency and replay/failure-injection acceptance for multi-event goal completion and evolution rollback.
- [ ] Refresh the PR description and review packet evidence index/head-snapshot wording.
- [ ] Obtain a further independent re-check of the updated evidence. A submitted GitHub review remains distinct from this technical document.

## 6. Authority and execution boundary

This reconciliation is documentation/static review only. It does not select the implementation baseline on behalf of the Project Director.

No runtime source changes, builds, tests, benchmarks, workflow executions, ABI checks, rebase, cherry-pick, merge, branch rewrite or deployment were performed or authorized.

**Final status: NOT CLEARED.** The defensible strategy is agreed; evidence closure is not complete; PR #156 remains a conditional source donor only; implementation remains unauthorized.
