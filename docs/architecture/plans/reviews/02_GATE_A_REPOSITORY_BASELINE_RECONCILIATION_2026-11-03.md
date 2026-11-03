# Gate A — Repository Baseline Reconciliation
**Checkpoint:** 1 — PR/branch lineage and immediate-delta reconciliation  
**Date:** 2026-11-03  
**Status:** IN PROGRESS — NOT CLOSED  
**Governing specification:** PR #174, accepted HEAD `0811a59e46bf934e32e794f90e4e7d18d4e2bd97`  
**Planning PR:** #175  
**Candidate implementation PR:** #156

## 1. Executive disposition

Gate A has established the current PR topology, exact candidate PR delta, major common-ancestor divergence, and several important non-ancestry relationships between component PRs and their integration PRs.

**Gate A is not complete.** The 1,416 commits already present at the candidate integration base have not yet been exhaustively classified commit-by-commit and file-by-file. The present document is a verified checkpoint, not an accepted implementation-baseline decision.

No implementation baseline is selected. PR #156 remains a candidate only.

## 2. Authority and inspection boundaries

This checkpoint is limited to GitHub metadata, commit graph comparisons, changed-file inventories, commit records and static source diffs. No local build, runtime test, benchmark, sanitizer, rebase, cherry-pick, merge, branch rewrite or deployment was performed.

The governing design invariant remains:

**ENGINEER THE MECHANISMS; LET BEHAVIOR BE ACQUIRED THROUGH EXPERIENCE.**

PR #174 is a documentation/specification baseline, not an implementation branch. Existing code is evidence and potential reusable material; it is not automatically the required final architecture.

## 3. Exact current refs

| Role | PR / ref | Exact SHA | State |
|---|---|---|---|
| Accepted Brain mechanism specification | PR #174 | `0811a59e46bf934e32e794f90e4e7d18d4e2bd97` | Open, draft, unmerged; Project Director accepted |
| Candidate PR documentation HEAD | PR #156 | `7fe212bbb0bd61116ea56581435e03b06c69b673` | Open, draft, unmerged |
| Candidate code-bearing parent | PR #156 | `15d49e5fdeb5723c475922ab78fb92f97c4b3b84` | Parent of documentation HEAD |
| PR #156 immediate base / PR #155 head | `integration/knowledge-composition-20261031` | `52c367a4b53fdfe9b29776795200555076e8cb49` | Open PR #155, draft, unmerged |
| Shared ancestor for candidate/spec comparison | — | `af09cf28d35e4a7b75c3c019e9f97893d8e19364` | Merge base |
| Current main at inspection | `main` | `1273ddbcd0087d189e01388ded2d362fb1e058d2` | Current main ref returned by GitHub |

## 4. Correct interpretation of the 1,429 / 21 divergence

The accepted specification HEAD compared with PR #156 documentation HEAD returns:

- Status: `diverged`
- Candidate ahead of merge base: **1,429 commits**
- Accepted specification ahead of merge base: **21 commits**
- Merge base: `af09cf28d35e4a7b75c3c019e9f97893d8e19364`

Comparing the accepted specification HEAD with the code-bearing parent returns **1,428 ahead / 21 behind**. The one-commit difference is the documentation-only PR #156 HEAD commit `7fe212b`.

**The 1,429 count is inherited branch ancestry, not the number of commits introduced by PR #156.** PR #156 itself is 13 commits ahead of its immediate base `52c367a`. Its exact PR delta is 8 files, 345 additions and 76 deletions. The 12 code-bearing commits touch 7 files (298 additions, 76 deletions); the final documentation commit adds 47 lines to `docs/DEVELOPMENTAL_BRAIN_PLAN.md`.

The immediate PR delta is therefore small relative to the accumulated history. The history risk is in the inherited candidate base and its relationship to the accepted specification line.

### 4.1 Decomposition of the 21 commits missing from candidate ancestry

The shared ancestor `af09cf28` is 9 commits behind current `main`. The accepted PR #174 HEAD is 12 commits ahead of current `main`, with no commits behind it. Therefore the 21 commits by which PR #156 is behind PR #174 decompose as:

- **9 commits on current main after the shared ancestor**, including one Brain API restoration and workflow/test-infrastructure changes.
- **12 documentation commits from the accepted architecture/specification stack**, represented by five added architecture/specification/review documents in the main-to-PR-174 comparison.

This is not a claim that all 21 commits have equal implementation significance. The nine main commits include both source and workflow/test infrastructure changes; the 12 accepted specification commits are documentation-only.

### 4.2 Why this distinction matters

Do not describe PR #156 as a 1,429-commit change set. Do not interpret the 21-commit behind count as 21 missing runtime features. The comparison is between two histories that diverged at `af09cf28`; the commit graph and file deltas must be inspected separately.

## 5. PR lineage and integration matrix

The following PRs are related to the candidate's knowledge, feature-learning and evolution-replay scope. They are all unmerged at inspection. PR status is not the same as independent acceptance.

| PR | Base → head | PR commit count | Changed files | Status | Contribution / relationship |
|---|---|---:|---:|---|---|
| #97 | `main@4ba84b8` → `c1da222` | 1,244 | 159 | Open, draft, unmerged | Long-lived cognitive/affective development branch; primary inherited candidate history |
| #135 | `c1da222` → `58acf23` | 6 | 2 | Open, unmerged | Causal-learning correction; base of PR #150 |
| #148 | `94d0297` → `be848d3` | 153 | 13 | Open, draft, unmerged | Knowledge conflict resolution, source calibration/provenance, trusted feedback boundary, passive legacy import and replay protections |
| #151 | `94d0297` → `8c8889f` | 32 | 8 | Open, not draft, unmerged | Additive feature-based action learning and DLT-004 |
| #150 | `58acf23` → `ec1ce13` | 12 | 7 | Open, not draft, unmerged | Evolution replay evidence validation and replay/adoption safeguards |
| #155 | `be848d3` → `52c367a` | 9 | 8 | Open, draft, unmerged | Conflict-resolved integration of PR #151's feature learning on top of PR #148 |
| #156 | `52c367a` → `7fe212b` | 13 | 8 | Open, draft, unmerged | Integration of evolution replay safeguards and feedback-source binding on top of PR #155 |

All short SHAs above are prefixes of the exact SHAs recorded in Section 3 or the PR metadata. PR #148 and #151 share merge base `94d02976ef4bcf36ad2e7a67f53cfc09d7018494`, but their branches diverge: PR #151 is 32 commits ahead and 153 behind PR #148's head. PR #155 is a nine-commit integration branch based directly on PR #148's head.


### 5.0 Primary inherited history: PR #97

PR #97 is the long-lived `feat/jarvis-affective-state` branch at `c1da222e6c94aeb3f2ad000392c21fe4fc81ab25`. Current PR metadata reports 1,244 commits, 159 changed files, 18,788 additions and 1,644 deletions. It remains open, draft and unmerged.

The exact graph comparisons establish:

- Shared ancestor `af09cf28` → PR #97 head `c1da222`: 1,244 commits ahead.
- PR #97 declared base `4ba84b8` → PR #97 head: 1,244 ahead / 1 behind, merge base `af09cf28`. Therefore the PR head does not contain its declared base commit as an ancestor.
- Current `main@1273ddb` → PR #97 head: 1,244 ahead / 9 behind, same merge base. PR #97 is not based on the current main history despite its PR base field naming main.
- PR #97 head `c1da222` → PR #156 immediate base `52c367`: 172 commits ahead, zero behind.
- PR #97 head `c1da222` → PR #156 code-bearing parent `15d49e5`: 184 commits ahead, zero behind.
- PR #97 head `c1da222` → PR #156 documentation HEAD `7fe212`: 185 commits ahead, zero behind.

This gives an exact arithmetic decomposition of the candidate-side 1,429 commits ahead of the shared ancestor:

**1,244 (PR #97 inherited history) + 172 (post-PR #97 history through PR #155) + 13 (PR #156 commits) = 1,429.**

The accepted specification's 21 commits ahead of the candidate decompose into 9 commits on current main after the shared ancestor and 12 accepted architecture/specification commits after main. This also explains why PR #97 is nine commits behind current main and why the candidate branch's declared PR base does not guarantee it contains the current base history.

**Implication:** the principal inherited-history risk is not an opaque 1,429-commit PR #156 delta. It is a 1,244-commit, 159-file PR #97 development line, followed by 172 commits of later integration/correction work and 13 PR #156 commits. PR #97 itself is unmerged and draft. The later candidate line is a descendant of PR #97, but that does not confer acceptance on the inherited functionality.


### 5.4 Exact 172-commit post-PR #97 decomposition

The 172 commits between PR #97 head `c1da222` and PR #155 head `52c367a` decompose exactly as follows:

| Segment | Commit count | Exact relationship |
|---|---:|---|
| Pre-PR #148 preparation | 10 | `c1da222` → `94d0297` |
| PR #148 knowledge/provenance work | 153 | `94d0297` → `be848d3` |
| PR #155 conflict-resolved integration | 9 | `be848d3` → `52c367a` |
| **Total** | **172** | `c1da222` → `52c367a` |

The ten preparation commits are individually identified:

| Commit | Subject | Work group |
|---|---|---|
| `c69a15d` | fix(causality): exclude unchanged facts from effect hypotheses | Causal-learning correction |
| `05e3ff1` | test(causality): ensure unchanged facts are not learned as effects | Causal regression |
| `c807ffc` | test(causality): include fixed-width integer type | Test portability |
| `e1b04d7` | fix(causality): learn from pre-transition cause state | Causal-learning correction |
| `8fa5752` | test(causality): predict outcomes from pre-transition states | Causal regression |
| `58acf23` | test(causality): predict from pre-transition state | PR #135 head |
| `d8c7c6c` | test: add multi-seed action mapping learning trial | DLT-003 test |
| `5e953b8` | test: register multi-seed mapping learning trial | DLT-003 registration |
| `9ddb4d3` | test: correct trial count and vary mappings by seed | DLT-003 correction |
| `94d0297` | test: correct restored outcome count | DLT-003 correction / PR #148 base |

This means the candidate-side total can be traced as:

**1,244 (PR #97) + 6 (PR #135 causal correction) + 4 (DLT-003 trial preparation) + 153 (PR #148) + 9 (PR #155 integration) + 13 (PR #156) = 1,429.**

PR #151's 32-commit source branch and PR #150's 12-commit source branch are not additional terms in this ancestry sum. Their functionality is integrated through PR #155 and PR #156 respectively, subject to the blob-level fidelity checks below.

### 5.5 Net file set changed after PR #97

The direct tree comparison `c1da222` → `52c367a` is 172 commits ahead and touches 20 net paths:

- Headers: `brain.hpp`, `developmental_learning.hpp`, `knowledge.hpp`, `world_model.hpp`.
- Sources: `brain.cpp`, `brain_restored_api.cpp`, `causal_model.cpp`, `cognitive_cycle.cpp`, `developmental_learning.cpp`, `knowledge.cpp`, `world_model.cpp`.
- Test registration/suites: `core/cpp/tests/CMakeLists.txt`, `association_causality_phase5_suite.cpp`, `developmental_brain_integration_suite.cpp`, `dlt_003_mapping_generalization.cpp`, `dlt_004_feature_composition.cpp`, `evolution_brain_integration_suite.cpp`, `knowledge_memory_phase3_suite.cpp`, `knowledge_source_feedback_suite.cpp`.
- Documentation: `docs/DEVELOPMENTAL_BRAIN_PLAN.md`.

This 20-path list is the net file delta of the 172-commit segment. It is smaller than the union of every file touched during those commits because multiple commits modify the same files.

### 5.1 Critical ancestry finding: PR #151 is integrated by content, not as a direct ancestor

Comparing PR #151 head `8c8889f` with PR #155 head `52c367a` returns:

- Status: diverged
- PR #155 side: 162 commits ahead of the common ancestor
- PR #151 side: 32 commits ahead of the common ancestor
- Merge base: `94d02976ef4bcf36ad2e7a67f53cfc09d7018494`

PR #155 is nine commits ahead of PR #148 head and its PR description says PR #151's feature was integrated through conflict resolution. The commit graph confirms that PR #151's original 32 commits are **not** direct ancestors of PR #155. The integrated code must be reviewed as the PR #155 result, not assumed equivalent to PR #151 commit-for-commit.

### 5.2 Critical ancestry finding: PR #150 is integrated by content, not as a direct ancestor

Comparing PR #150 head `ec1ce132` with PR #156 code-bearing parent `15d49e5f` returns:

- Status: diverged
- PR #156 code-bearing parent side: 178 commits ahead of the common ancestor
- PR #150 side: 12 commits ahead of the common ancestor
- Merge base: `58acf23c9cc4594284062465ed658daf7f99e9a2`

PR #156's first code commit is based on PR #155 head `52c367a`, not on PR #150 head `ec1ce13`. Thus PR #150's 12 commits are not direct ancestors of PR #156. PR #156 contains separately authored integration/correction commits that implement overlapping replay safeguards. Review the final PR #156 code against PR #150's intended protections; do not claim the source branch was merged unchanged.


### 5.6 PR #155's nine integration commits

The nine PR #155 commits are:

| Commit | Subject | Reconciliation significance |
|---|---|---|
| `78c7fca` | integrate compositional learning with knowledge safeguards | Integrates the feature learner against the knowledge/provenance branch |
| `e322e52` | integrate feature learning into Brain outcome replay | Connects feature learning to Brain outcome processing |
| `66a183a` | expose compositional feature estimate through Brain API | Adds the public feature-estimate query |
| `e456881` | integrate compositional feature learning | Integration correction |
| `09598c8` | integrate compositional feature learning | Integration correction |
| `989727f` | integrate compositional feature learning | Integration correction |
| `4264262` | integrate compositional feature learning | Integration correction |
| `524a3cd` | integrate DLT-004 compositional learning acceptance test | Adds the DLT-004 test to the integrated tree |
| `52c367a` | fix(integration): preserve execution-only outcome block | Prevents an execution-only outcome from being treated as environmental feature-utility evidence |

The last change is material: PR #155 retains operational reliability information but explicitly excludes an execution failure without an observed world consequence from compositional feature-value learning. This is a boundary that must remain intact in any later integration.

### 5.3 Integration topology

```text
Shared historical ancestor: af09cf28
  └── PR #97: 1,244-commit cognitive/affective development line ── c1da222
        └── 172 subsequent commits through PR #155 ── 52c367a
              └── PR #156: 12 code commits + 1 documentation commit ── 7fe212b

PR #148/#151 subgraph (merge base 94d0297):
  ├── PR #148: knowledge/provenance branch (153 commits) ── be848d3
  │     └── PR #155: conflict-resolved integration (9 commits) ── 52c367a
  │           └── PR #156: replay/source-binding integration (12 code commits)
  │                 └── docs checkpoint (1 commit) ── 7fe212b
  └── PR #151: feature-learning source branch (32 commits) ── 8c8889f
        [integrated by content through PR #155; not a direct ancestor]

Separate causal/evolution source line:
PR #135 head: 58acf23
  └── PR #150: evolution replay source branch (12 commits) ── ec1ce13
        [PR #150 head is not a direct ancestor of PR #156]

Accepted architecture/specification line:
main 1273ddb
  └── PR #173 accepted architecture branch
        └── PR #174 accepted specification HEAD 0811a59
```

The diagram is a simplified relationship map. It does not assert that every feature in a source PR was integrated without modification.

## 6. Exact PR #156 incremental commit inventory

GitHub's PR commit endpoint returned the following ordered sequence:

| # | Commit | Message | Classification |
|---:|---|---|---|
| 1 | `1d9ec3a` | integrate authenticated evolution replay validation | Integration |
| 2 | `ef2befd` | integrate evolution replay evidence validation | Integration |
| 3 | `f1f9d32` | integrate evolution replay evidence validation | Integration |
| 4 | `da9d773` | integrate evolution replay evidence validation | Integration |
| 5 | `1cd81a3` | fix(evolution): bind replay rollback to adopted parameter | Runtime correction |
| 6 | `f705a26` | test(evolution): reject mismatched replay rollback target | Regression test |
| 7 | `3a7ddce` | fix(test): use explicit memory capacity for replay fixture | Test-fixture correction |
| 8 | `bd7d7d3` | fix(knowledge): bind feedback attestations to claim source | Runtime correction |
| 9 | `5f6ef27` | fix(knowledge): bind feedback attestations to claim source | Runtime correction |
| 10 | `ecf396d` | fix(knowledge): bind feedback attestations to claim source | Runtime correction |
| 11 | `f79c8f9` | test(knowledge): reject source relabeling with stale attestation | Regression test |
| 12 | `15d49e5` | fix(knowledge): resolve claim source before verifying feedback | Runtime correction |
| 13 | `7fe212b` | docs(plan): record integrated priority-one audit checkpoint | Documentation-only |

The first 12 commits are the code-bearing chain ending at `15d49e5`. The 13th commit changes only `docs/DEVELOPMENTAL_BRAIN_PLAN.md`.

## 7. PR #156 exact changed-file matrix

Comparison of immediate base `52c367a` to code-bearing parent `15d49e5`:

| File | Additions | Deletions | Observed responsibility | Initial disposition |
|---|---:|---:|---|---|
| `core/cpp/include/jarvis/core/brain.hpp` | 1 | 0 | Adds claim source to feedback-verifier request contract | Preserve for review; check all callers/verifier integrations |
| `core/cpp/src/brain.cpp` | 65 | 13 | Restricts external evolution lifecycle replay; validates complete evaluation/adoption evidence; binds rollback to adopted parameter; binds feedback replay to source | Preserve as candidate; verify replay lifecycle and event compatibility |
| `core/cpp/src/brain_restored_api.cpp` | 7 | 7 | Resolves the actual claim source before invoking feedback verifier and includes source in prior-attestation verification | Preserve as candidate; verify source lookup, locking and replay semantics |
| `core/cpp/src/evolution_controller.cpp` | 67 | 9 | Recomputes evaluation outcome; checks finite/ranged evidence, durable matching evaluation, safety gate and adoption-journal fields | Preserve as candidate; check idempotency, historical records and rollback interactions |
| `core/cpp/tests/evolution_brain_integration_suite.cpp` | 75 | 19 | Adds/updates forged lifecycle, rollback-binding and restart regressions | Preserve as evidence; tests are not a substitute for full spec acceptance |
| `core/cpp/tests/evolution_canary_controller_suite.cpp` | 21 | 0 | Adds forged adoption and false-improvement replay cases; requires isolation attestation in fixture | Preserve as evidence; inspect coverage boundaries |
| `core/cpp/tests/knowledge_source_feedback_suite.cpp` | 62 | 28 | Binds feedback attestation to source and tests source relabeling across restart | Preserve as evidence; test verifier is not production cryptography |
| `docs/DEVELOPMENTAL_BRAIN_PLAN.md` | 47 | 0 | Records exact-head audit, corrections, CI and remaining Priority-One gates | Documentation; retain as historical evidence, reconcile with accepted Brain specification |

### 7.1 Source-level change summary

Static diff inspection confirms these changes in the PR #156 delta:

1. Publicly observed external `evolution_*` lifecycle records are rejected during replay unless the source is Brain-authored.
2. Evaluation replay requires complete finite numeric fields, a valid outcome enum and an explicit isolation field; the controller recomputes the outcome rather than trusting the stored label.
3. Adoption replay requires a matching durable evaluation record and a fresh safety-gate approval, then checks the staged journal fields against the replayed experiment.
4. Rollback replay verifies that the experiment's adopted parameter key matches the rollback event's key before mutating the parameter.
5. Knowledge feedback requests now bind the actual source of the referenced claim. The source is resolved before calling the host verifier, and replay verification includes that source.
6. Regression coverage includes mismatched rollback targets, false improvement labels, source relabeling with a stale attestation, and restart behavior.

These are substantive integrity/replay improvements. They do not close the documented external requirements for production cryptographic verification, protected trust configuration, key rotation/revocation, objective adjudication or cryptographic journal integrity.


### 7.2 Exact candidate code-bearing blob identities

The following blob SHAs were fetched at PR #156 code-bearing parent `15d49e5f`:

| File | Blob SHA |
|---|---|
| `core/cpp/include/jarvis/core/brain.hpp` | `ca718aa4603bbdd0abc7de26ed296bcf8c6562fe` |
| `core/cpp/src/brain.cpp` | `93a10a5021a5775a3a239037cbb0b58a1e0c67a9` |
| `core/cpp/src/brain_restored_api.cpp` | `00d69ab2eb3811d453a643ef18dc69741109cbc8` |
| `core/cpp/src/evolution_controller.cpp` | `6d08a04db4886e398e2a15c4e6697f6ace26f459` |
| `core/cpp/tests/evolution_brain_integration_suite.cpp` | `d9dc62b1c6aebdb4ab38f3d64150699d96f393c4` |
| `core/cpp/tests/evolution_canary_controller_suite.cpp` | `f6fbbaa54771aa1ee3665148ce638d4e9aa390ae` |
| `core/cpp/tests/knowledge_source_feedback_suite.cpp` | `66a855dfe2aec24cdc173a1cedafbdbefeb811c3` |

These identities bind the static audit to the exact code-bearing parent, not merely the PR's later documentation HEAD.

## 8. Current-main drift relative to the candidate's common ancestor

Current `main` is nine commits ahead of `af09cf28`. The nine commits are:

| Commit | Message | Net file-level observation |
|---|---|---|
| `4ba84b8` | Restore Brain API definitions after accidental truncation | Adds restored API definitions in `brain_restored_api.cpp` |
| `043bd1b` | ci(dlt-002): expose overnight trial for manual dispatch | Workflow infrastructure |
| `6ce51f6` | test(learning): add explicit learning mechanisms probe | Workflow infrastructure |
| `95afb67` | test(memory): publish JBP MEM-001 manual workflow | Workflow infrastructure |
| `b23f1e9` | test(learning): add parallel multi-seed adversarial stress trial | Workflow infrastructure |
| `35ecf7c` | test(brain): add integrated feedback and persistence validation | Workflow/test infrastructure |
| `a323ce7` | fix(memory-test): test the selected brain revision | Test/workflow correction |
| `1633105` | feat(evolution): add self-contained artifact digest | Later reverted on main |
| `1273ddb` | revert: remove misplaced evolution digest header | Reverts the preceding digest change |

The net comparison from `af09cf28` to current `main` reports six changed files: five workflow files and `core/cpp/src/brain_restored_api.cpp`. The digest add/revert pair leaves no net file change in the current-main tree.

### 8.1 Brain API restoration — preliminary equivalence check

The candidate `brain_restored_api.cpp` blob is `00d69ab2eb3811d453a643ef18dc69741109cbc8`; current-main blob is `618deb6976eed951eae02b7f0da741e6d730bb0c`.

A static function-name inventory found all 69 Brain API function names present in current main in the candidate file, plus additional candidate APIs including prediction feedback, source feedback, related-strategy retrieval and evolution evaluation recording.

A normalized function-body comparison could align 67 of the 69 definitions: 43 bodies were identical after whitespace normalization and **24 bodies differed**. The two remaining definitions (`beliefs` and `register_evolution_parameter`) were present by name in both files but could not be reliably paired by the simple signature extractor because of the file's compact formatting. The 24 differing definitions include prediction, prediction resolution, goal outcome assimilation, action selection, reflection, goal lifecycle, capability/resilience state, and evolution operations.

Representative body differences were inspected directly:

- `predict`: candidate rejects non-finite confidence and numeric values and applies learned adaptation; main only checks an empty key before journaling.
- `resolve_prediction`: candidate routes both overloads through `resolve_prediction_feedback`; main performs the resolution path directly.
- `reflect`: candidate includes affective calibration error/learning data in reflection.
- `assimilate_goal_outcome`: candidate rejects updates to terminal goals before journaling.
- `create_goal`: candidate rejects duplicate goal IDs.
- `observe_evolution_fitness`: candidate routes the event through replay rather than directly mutating the evolution model.
- `adopt_evolution`: candidate deliberately fails closed; adoption must use a completed experiment and controller safety gate. Main still permits the legacy direct proposal-adoption path.
- `rollback_evolution`: candidate ties rollback to an adopted experiment and records a reason; main directly rolls back by parameter key.
- `adopt_evolution_experiment`: candidate validates experiment identity, finite/ranged evidence and controller approval before journaling adoption.
- `observe_evolution_canary`: candidate validates and journals canary observations before applying rollback decisions.

These samples suggest the candidate often contains stricter evidence, replay and lifecycle controls than the restored main version. That is not proof that every difference is correct; it does show that blindly importing the main restoration could reintroduce weaker legacy entry points.

Therefore the earlier function-name result is not enough to declare the main restoration functionally subsumed. **The API restoration remains an unresolved semantic reconciliation item, but it is not an automatic candidate blocker or an automatic cherry-pick.** The 24 body differences require targeted review, the two parser-unmatched definitions require manual alignment, and callers/build configuration must be reconciled before deciding whether the main commit is superseded or whether candidate behavior is missing/changed.

### 8.2 Workflow/test infrastructure drift

The five workflow files present in current main are not part of PR #156's immediate eight-file delta, but a direct path/blob check against candidate base `52c367a` shows three distinct cases:

| Current-main workflow | Current-main blob | Candidate-base state | Reconciliation result |
|---|---|---|---|
| `.github/workflows/dlt-002-four-hour.yml` | `52d08751d29c1b7c7b60e07834ac1bfdc4eba626` | Same path and same blob | Exact match; no content drift |
| `.github/workflows/jbp-mem-001.yml` | `9e1efd73a9a91a70c1d9ceda0d6b458f9bdd7f7f` | Same path, blob `82cec28819357a26881584b4ceb951c258ea24ac` | Different; semantic workflow review required |
| `.github/workflows/jarvis-learning-mechanisms.yml` | `0eac13b1e6a43ea7fa06aaf9e0134f5b6ae27710` | Absent | Missing from candidate base |
| `.github/workflows/jbp-brain-int-001.yml` | `31523dfa6bb5160397ebefd1f25325484461e271` | Absent | Missing from candidate base |
| `.github/workflows/jbp-learning-002.yml` | `4e88b4150eed6e5df3e81dd28a35216a299039e9` | Absent | Missing from candidate base |

The `jbp-mem-001.yml` difference is concrete: current main accepts a `source_ref` input, checks out that selected Brain revision, and records both the selected source ref and resolved tested commit in run metadata. The candidate-base version has no `source_ref` input, checks out the workflow's own ref, and omits those two metadata fields. That is a test-target reproducibility/control difference, not a cosmetic edit.

The three absent workflows provide distinct validation paths: a learning-mechanisms probe, an integrated feedback/persistence probe with source-ref selection, and a short-horizon controlled learning stress test. The candidate's existing `jarvis-learning-seed-sweep.yml` is not a path-level substitute for these workflows; equivalence has not been established.

These workflows are test/CI infrastructure, not runtime Brain mechanisms. Their value, triggers, tested source refs and compatibility with candidate CI must be assessed independently. Preserve the exact-match DLT-002 workflow; do not silently discard the JBP-MEM source-selection control; do not copy the three missing workflows blindly.

## 9. Initial retain/adapt/exclude matrix

| Change group | Current evidence | Preliminary recommendation | Unresolved question |
|---|---|---|---|
| PR #148 knowledge conflict/provenance work | Source branch and PR description; integrated by PR #155 | Retain as candidate functionality, not accepted architecture | Which pieces satisfy BM-01/BM-04, and which need changes to meet the accepted epistemic contracts? |
| PR #151 additive action-feature learner | Source PR, DLT-004 and PR #155 integration | Retain as bounded learning candidate | Does the integrated PR #155 implementation preserve all intended isolation, transfer and restart protections? |
| PR #150 evolution replay safeguards | Source PR plus separately authored PR #156 integration commits | Retain the PR #156 implementation as candidate; compare each safeguard against PR #150 intent | Are all source-branch protections preserved, and are the integration differences deliberate and complete? |
| PR #156 rollback parameter binding | Exact source/test diff | Preserve | Does the invariant cover all replay/rollback orderings and historical records? |
| PR #156 feedback source binding | Exact source/test diff | Preserve | Does the host verifier bind every required claim field and is historical replay policy explicit? |
| Main Brain API restoration | Candidate includes all main function names; blob differs | Likely subsumed; semantic comparison required | Are common signatures and behavior equivalent, and are any callers/configuration dependencies missing? |
| Main workflow/test additions | Five net workflow files absent from PR #156 delta | Evaluate individually; do not automatically import | Which workflows remain needed, safe, and compatible with the accepted verification strategy? |
| Evolution digest add/revert pair | Net no file change on current main | Exclude the reverted feature from current-main baseline unless separate evidence requires it | Verify no dependent artifact remains on candidate line |
| Accepted PR #173/#174 documentation | 12 commits ahead of main, five docs in comparison | Binding planning/specification baseline | Candidate implementation must be mapped against the accepted responsibilities; docs are not code to cherry-pick |

## 10. Reconciliation risks and unresolved work

Gate A still needs the following before it can be declared complete:

1. **Exhaustive inherited-history inventory:** enumerate and classify the 1,416 commits already present at PR #156's immediate base `52c367a` relative to `af09cf28`. The count is not itself a useful inventory.
2. **Origin mapping:** map the inherited history to originating PRs, branches and integration checkpoints. Identify overlapping branches and repeated/reworked commits without double-counting them.
3. **File-level ownership:** for each relevant file, identify which PR/commit first introduced it, later modifications, current candidate blob, current-main blob where applicable, and accepted specification responsibility.
4. **Integration fidelity:** compare PR #148 and #151 source changes with PR #155's conflict-resolved integration, and PR #150's source changes with PR #156's independently authored integration commits.
5. **Current-main semantic reconciliation:** compare the restored API definitions and the workflow/test infrastructure against the candidate tree, including their callers and exact refs.
6. **Unreviewed status:** preserve the fact that PRs #148, #150, #151, #155 and #156 are unmerged. A green CI record or a draft integration PR does not confer independent acceptance.
7. **Baseline recommendation:** only after the above should the Builder recommend a candidate source baseline, an adaptation set and exclusions for Independent Reviewer challenge.

Gate B remains separate: it must produce the complete 12-mechanism source-to-specification traceability matrix. Gate A must not be represented as having completed Gate B.

## 11. Prohibited actions remain prohibited

This checkpoint does not authorize:

- runtime source modifications;
- builds, tests, benchmarks or sanitizers;
- rebase, cherry-pick, merge, branch rewrite or history reconstruction;
- technology, schema, API, framework or database selection;
- deployment or autonomous operation.

PR #156 remains a candidate. No implementation base is selected.

## 12. Checkpoint conclusion

**Gate A checkpoint 1: useful structural reconciliation completed; full repository baseline reconciliation remains OPEN.**

The most important correction is that the 1,429/21 figure describes divergent ancestry, not the PR #156 incremental diff. The next reconciliation work must focus on the inherited 1,416-commit base, the missing 21 commits, and the fact that PR #155 and PR #156 integrate source-PR functionality through new commits rather than direct ancestry.

Do not rebase or reconstruct history. Do not begin implementation. Obtain independent review of this reconciliation checkpoint before making any baseline decision.


## Appendix A — Complete net file inventory at candidate integration base

The 1,416 commits from `af09cf28` to PR #156's immediate base `52c367a` were enumerated through 15 paginated compare responses: 14 pages of 100 commits and one page of 16. The enumeration contains **1,416 unique commit SHAs**, spanning 2026-09-25 14:13:51 UTC through 2026-10-31 04:43:06 UTC. This completes the commit-list enumeration, but not per-commit file attribution or originating-PR classification.

The net tree comparison from `af09cf28` to `52c367a` contains **165 paths**: 70 added and 95 modified. This is the net tree delta at the candidate integration base, not a count of files touched at any point in the 1,416 commits.

| Path group | Files |
|---|---:|
| `.github/workflows` | 8 |
| `core/cpp root and other` | 4 |
| `core/cpp/include` | 36 |
| `core/cpp/src` | 38 |
| `core/cpp/tests` | 59 |
| `docs` | 10 |
| `engineering` | 10 |

### A.1 Full path/status inventory

**.github/workflows (8)**

- `.github/workflows/brain-ci.yml` — modified
- `.github/workflows/dlt-001-long-run.yml` — added
- `.github/workflows/dlt-002-four-hour.yml` — added
- `.github/workflows/dlt-002-overnight-validation.yml` — added
- `.github/workflows/jarvis-brain-probe-001.yml` — added
- `.github/workflows/jarvis-core.yml` — added
- `.github/workflows/jarvis-learning-seed-sweep.yml` — added
- `.github/workflows/jbp-mem-001.yml` — added

**core/cpp root and other (4)**

- `core/cpp/CMakeLists.txt` — modified
- `core/cpp/examples/CMakeLists.txt` — added
- `core/cpp/examples/developmental_world.cpp` — added
- `core/cpp/examples/README.md` — added

**core/cpp/include (36)**

- `core/cpp/include/jarvis/core/action_execution.hpp` — modified
- `core/cpp/include/jarvis/core/action_model.hpp` — modified
- `core/cpp/include/jarvis/core/adaptation.hpp` — modified
- `core/cpp/include/jarvis/core/affective_learning.hpp` — added
- `core/cpp/include/jarvis/core/affective_state.hpp` — added
- `core/cpp/include/jarvis/core/association_model.hpp` — modified
- `core/cpp/include/jarvis/core/attention.hpp` — modified
- `core/cpp/include/jarvis/core/brain.hpp` — modified
- `core/cpp/include/jarvis/core/causal_link_codec.hpp` — added
- `core/cpp/include/jarvis/core/causal_model.hpp` — modified
- `core/cpp/include/jarvis/core/cognition.hpp` — modified
- `core/cpp/include/jarvis/core/cognitive_cycle.hpp` — modified
- `core/cpp/include/jarvis/core/cognitive_goal_outcome.hpp` — added
- `core/cpp/include/jarvis/core/cognitive_runtime.hpp` — modified
- `core/cpp/include/jarvis/core/cognitive_workspace.hpp` — modified
- `core/cpp/include/jarvis/core/decision.hpp` — modified
- `core/cpp/include/jarvis/core/developmental_environment.hpp` — added
- `core/cpp/include/jarvis/core/developmental_learning.hpp` — added
- `core/cpp/include/jarvis/core/developmental_world.hpp` — added
- `core/cpp/include/jarvis/core/evolution_adoption_journal.hpp` — modified
- `core/cpp/include/jarvis/core/evolution_canary.hpp` — modified
- `core/cpp/include/jarvis/core/evolution_controller.hpp` — modified
- `core/cpp/include/jarvis/core/evolution_experiment_coordinator.hpp` — modified
- `core/cpp/include/jarvis/core/evolution_experiment_runner.hpp` — modified
- `core/cpp/include/jarvis/core/evolution_experiment.hpp` — modified
- `core/cpp/include/jarvis/core/evolution_orchestrator.hpp` — modified
- `core/cpp/include/jarvis/core/evolution.hpp` — modified
- `core/cpp/include/jarvis/core/experience_memory.hpp` — added
- `core/cpp/include/jarvis/core/goals.hpp` — modified
- `core/cpp/include/jarvis/core/intent.hpp` — modified
- `core/cpp/include/jarvis/core/knowledge.hpp` — modified
- `core/cpp/include/jarvis/core/memory.hpp` — modified
- `core/cpp/include/jarvis/core/planning.hpp` — modified
- `core/cpp/include/jarvis/core/reflection.hpp` — modified
- `core/cpp/include/jarvis/core/self_model.hpp` — modified
- `core/cpp/include/jarvis/core/world_model.hpp` — modified

**core/cpp/src (38)**

- `core/cpp/src/action_execution.cpp` — modified
- `core/cpp/src/adaptation.cpp` — modified
- `core/cpp/src/affective_learning.cpp` — added
- `core/cpp/src/affective_state.cpp` — added
- `core/cpp/src/association_model.cpp` — modified
- `core/cpp/src/attention.cpp` — modified
- `core/cpp/src/brain_action_execution.cpp` — added
- `core/cpp/src/brain_affective_planning.cpp` — added
- `core/cpp/src/brain_prediction_context.cpp` — added
- `core/cpp/src/brain_restored_api.cpp` — added
- `core/cpp/src/brain.cpp` — modified
- `core/cpp/src/causal_model.cpp` — modified
- `core/cpp/src/cognitive_cycle.cpp` — modified
- `core/cpp/src/cognitive_runtime.cpp` — modified
- `core/cpp/src/decision.cpp` — modified
- `core/cpp/src/developmental_learning.cpp` — added
- `core/cpp/src/evolution_adoption_journal.cpp` — modified
- `core/cpp/src/evolution_adoption.cpp` — modified
- `core/cpp/src/evolution_canary.cpp` — modified
- `core/cpp/src/evolution_controller.cpp` — modified
- `core/cpp/src/evolution_experiment_coordinator.cpp` — modified
- `core/cpp/src/evolution_experiment_runner.cpp` — modified
- `core/cpp/src/evolution_history.cpp` — modified
- `core/cpp/src/evolution_orchestrator.cpp` — modified
- `core/cpp/src/evolution_safety.cpp` — modified
- `core/cpp/src/evolution_sandbox.cpp` — modified
- `core/cpp/src/evolution.cpp` — modified
- `core/cpp/src/goals.cpp` — modified
- `core/cpp/src/intent.cpp` — modified
- `core/cpp/src/knowledge.cpp` — modified
- `core/cpp/src/memory.cpp` — modified
- `core/cpp/src/planning.cpp` — modified
- `core/cpp/src/process_isolation.cpp` — modified
- `core/cpp/src/reasoning.cpp` — modified
- `core/cpp/src/reflection.cpp` — modified
- `core/cpp/src/representation.cpp` — modified
- `core/cpp/src/self_model.cpp` — modified
- `core/cpp/src/world_model.cpp` — modified

**core/cpp/tests (59)**

- `core/cpp/tests/action_authorization_suite.cpp` — modified
- `core/cpp/tests/action_execution_phase7_suite.cpp` — modified
- `core/cpp/tests/action_model_architecture_suite.cpp` — modified
- `core/cpp/tests/affective_brain_decision_suite.cpp` — added
- `core/cpp/tests/affective_decision_learning_suite.cpp` — added
- `core/cpp/tests/affective_decision_suite.cpp` — added
- `core/cpp/tests/affective_evidence_suite.cpp` — added
- `core/cpp/tests/affective_goal_outcome_suite.cpp` — added
- `core/cpp/tests/affective_learning_suite.cpp` — added
- `core/cpp/tests/affective_planning_suite.cpp` — added
- `core/cpp/tests/affective_planning.cmake` — added
- `core/cpp/tests/affective_state_model_suite.cpp` — added
- `core/cpp/tests/affective_state_suite.cpp` — added
- `core/cpp/tests/association_causality_phase5_suite.cpp` — modified
- `core/cpp/tests/attention_architecture_suite.cpp` — modified
- `core/cpp/tests/attention_learning_brain_suite.cpp` — added
- `core/cpp/tests/brain_10_suite.cpp` — modified
- `core/cpp/tests/brain_action_consequence_integration_suite.cpp` — added
- `core/cpp/tests/brain_contract.cpp` — modified
- `core/cpp/tests/brain_deep_suite.cpp` — modified
- `core/cpp/tests/CMakeLists.txt` — modified
- `core/cpp/tests/cognitive_cycle_suite.cpp` — modified
- `core/cpp/tests/cognitive_runtime_goal_feedback_suite.cpp` — added
- `core/cpp/tests/cognitive_runtime_learning_integration_suite.cpp` — added
- `core/cpp/tests/cognitive_runtime_suite.cpp` — modified
- `core/cpp/tests/cognitive_workspace_runtime_suite.cpp` — modified
- `core/cpp/tests/decision_planning_architecture_suite.cpp` — modified
- `core/cpp/tests/developmental_brain_integration_suite.cpp` — added
- `core/cpp/tests/developmental_environment_suite.cpp` — added
- `core/cpp/tests/developmental_learning_suite.cpp` — added
- `core/cpp/tests/developmental_learning_tests.cpp` — added
- `core/cpp/tests/developmental_training_environment_suite.cpp` — added
- `core/cpp/tests/developmental_world_integration_suite.cpp` — added
- `core/cpp/tests/developmental_world_suite.cpp` — added
- `core/cpp/tests/dlt_001_long_run.cpp` — added
- `core/cpp/tests/dlt_001_trial.cpp` — added
- `core/cpp/tests/dlt_002_long_run.cpp` — added
- `core/cpp/tests/dlt_002_persistence.cpp` — added
- `core/cpp/tests/dlt_003_mapping_generalization.cpp` — added
- `core/cpp/tests/dlt_004_feature_composition.cpp` — added
- `core/cpp/tests/evolution_adoption_journal_suite.cpp` — modified
- `core/cpp/tests/evolution_brain_integration_suite.cpp` — modified
- `core/cpp/tests/evolution_canary_controller_suite.cpp` — modified
- `core/cpp/tests/evolution_experiment_coordinator_suite.cpp` — modified
- `core/cpp/tests/evolution_experiment_runner_suite.cpp` — modified
- `core/cpp/tests/evolution_opportunity_orchestration_suite.cpp` — modified
- `core/cpp/tests/experience_memory_test.cpp` — added
- `core/cpp/tests/goal_directed_cognition_suite.cpp` — added
- `core/cpp/tests/goal_outcome_model_suite.cpp` — added
- `core/cpp/tests/goals_architecture_suite.cpp` — modified
- `core/cpp/tests/knowledge_memory_phase3_suite.cpp` — modified
- `core/cpp/tests/knowledge_source_feedback_suite.cpp` — added
- `core/cpp/tests/learning_adaptation_phase8_suite.cpp` — modified
- `core/cpp/tests/memory_architecture_suite.cpp` — modified
- `core/cpp/tests/memory_learning_evolution_persistence_suite.cpp` — added
- `core/cpp/tests/prediction_feedback_phase10_suite.cpp` — modified
- `core/cpp/tests/process_isolation_suite.cpp` — modified
- `core/cpp/tests/reasoning_architecture_suite.cpp` — modified
- `core/cpp/tests/representation_suite.cpp` — modified

**docs (10)**

- `docs/DEVELOPMENTAL_BRAIN_PLAN.md` — added
- `docs/developmental-training-environment.md` — added
- `docs/superpowers/plans/2026-09-25-cognitive-action-feedback-loop.md` — added
- `docs/superpowers/plans/2026-09-26-concept-context-prediction.md` — added
- `docs/superpowers/plans/2026-09-30-developmental-cognition.md` — added
- `docs/superpowers/plans/2026-10-01-affective-state.md` — added
- `docs/superpowers/specs/2026-09-25-cognitive-action-feedback-loop-design.md` — added
- `docs/superpowers/specs/2026-09-26-concept-context-prediction-design.md` — added
- `docs/superpowers/specs/2026-09-30-developmental-cognition.md` — added
- `docs/superpowers/specs/2026-10-01-affective-state.md` — added

**engineering (10)**

- `engineering/cpp/CMakeLists.txt` — modified
- `engineering/cpp/include/jarvis/engineering/agent.hpp` — modified
- `engineering/cpp/include/jarvis/engineering/coordinator.hpp` — modified
- `engineering/cpp/include/jarvis/engineering/message_bus.hpp` — modified
- `engineering/cpp/include/jarvis/engineering/task_ledger.hpp` — added
- `engineering/cpp/src/coordinator.cpp` — modified
- `engineering/cpp/src/message_bus.cpp` — modified
- `engineering/cpp/src/task_ledger.cpp` — added
- `engineering/cpp/tests/agent_and_console_suite.cpp` — modified
- `engineering/cpp/tests/task_ledger_suite.cpp` — added

### A.2 Largest net-delta files

| File | Status | Additions | Deletions |
|---|---|---:|---:|
| `core/cpp/tests/developmental_brain_integration_suite.cpp` | added | 1749 | 0 |
| `core/cpp/src/brain.cpp` | modified | 1136 | 155 |
| `core/cpp/tests/brain_deep_suite.cpp` | modified | 806 | 153 |
| `core/cpp/src/cognitive_cycle.cpp` | modified | 727 | 83 |
| `core/cpp/tests/cognitive_cycle_suite.cpp` | modified | 723 | 33 |
| `core/cpp/src/developmental_learning.cpp` | added | 563 | 0 |
| `core/cpp/src/brain_restored_api.cpp` | added | 529 | 0 |
| `core/cpp/src/memory.cpp` | modified | 149 | 352 |
| `core/cpp/tests/dlt_002_long_run.cpp` | added | 479 | 0 |
| `core/cpp/tests/dlt_004_feature_composition.cpp` | added | 357 | 0 |
| `core/cpp/tests/developmental_training_environment_suite.cpp` | added | 355 | 0 |
| `core/cpp/include/jarvis/core/brain.hpp` | modified | 65 | 277 |
| `core/cpp/tests/cognitive_runtime_learning_integration_suite.cpp` | added | 326 | 0 |
| `core/cpp/tests/dlt_001_trial.cpp` | added | 322 | 0 |
| `core/cpp/tests/evolution_brain_integration_suite.cpp` | modified | 316 | 2 |

**Interpretation boundary:** the path inventory identifies the final tree differences at `52c367a`. It does not assign every path to an individual commit, originating PR, accepted BM mechanism or final ownership. Those joins remain required before Gate A can close.

## Appendix B — Source-branch to integration blob fidelity

Exact file blobs were compared between the source PR heads and the integrated candidate heads. Equality means byte-identical content at those refs; inequality means the integration file requires semantic diff review. It does not by itself indicate a defect.

### B.1 PR #151 source → PR #155 integration

| File | PR #151 blob | PR #155 blob | Result |
|---|---|---|---|
| `core/cpp/include/jarvis/core/brain.hpp` | `196fed5a91bc5e57ae7d3af3b0576210cd17a8be` | `94368254672f17045030a9effa86b0a71c2c4704` | Different — integration review required |
| `core/cpp/include/jarvis/core/developmental_learning.hpp` | `65174400d8c3ce1dea17667ac928767cf3af333a` | same | Identical |
| `core/cpp/src/brain.cpp` | `8232f9a3ca8dcdbda31dad20c14cc798ab85b2ce` | `0f377bf853af866375b35a944862c743c777a4c0` | Different — integration review required |
| `core/cpp/src/brain_restored_api.cpp` | `3a9295be7bfd240585577f7962e16de4c770b655` | `2a49f2aad3a99e74316a068801e3f0f90bf69bad` | Different — integration review required |
| `core/cpp/src/cognitive_cycle.cpp` | `989f4d154f07b31bcdab175aefbea6edd61eb930` | same | Identical |
| `core/cpp/src/developmental_learning.cpp` | `c9a34d562fa1a20641530daba81bfdc1f3621fee` | same | Identical |
| `core/cpp/tests/CMakeLists.txt` | `0251936730f82a7a8c928fa31dfe1d7effc83d91` | same | Identical |
| `core/cpp/tests/dlt_004_feature_composition.cpp` | `e486bedc813c1a70dc48b610133a147283e0d7ef` | same | Identical |

**Result:** five of eight files are byte-identical. Three overlapping Brain API/implementation files differ and require a targeted semantic review. The integration patches show the intended adaptations: `brain.hpp` exposes `developmental_feature_strategy_estimate`; `brain_restored_api.cpp` implements that accessor; and `brain.cpp` keeps execution-failure evidence for operational reliability but passes `false` to the compositional learner so an unobserved world consequence cannot train feature utility. This preserves the distinction between execution reliability and environmental outcome learning. The integration branch is not a wholesale copy of PR #151.

### B.2 PR #150 source → PR #156 code-bearing parent

| File | PR #150 blob | PR #156 blob | Result |
|---|---|---|---|
| `core/cpp/include/jarvis/core/brain.hpp` | `a195bdd00fe5fe376095c55bb2acf0671abea85c` | `ca718aa4603bbdd0abc7de26ed296bcf8c6562fe` | Different — integration review required |
| `core/cpp/src/brain.cpp` | `286c55279bc873094ee85c23108e5dbca838be0f` | `93a10a5021a5775a3a239037cbb0b58a1e0c67a9` | Different — integration review required |
| `core/cpp/src/brain_restored_api.cpp` | `630d6c7f651d4f11cdfa3d8b4779e6b0df519737` | `00d69ab2eb3811d453a643ef18dc69741109cbc8` | Different — integration review required |
| `core/cpp/src/evolution_controller.cpp` | `6d08a04db4886e398e2a15c4e6697f6ace26f459` | same | Identical |
| `core/cpp/tests/developmental_brain_integration_suite.cpp` | `b9dc34b63f7ca0b356a5a2589c39fb8b5862d2f6` | `e6eba3db6df8da9ecfed21974936908a32ea11c5` | Source change subsumed by PR #148 |
| `core/cpp/tests/evolution_brain_integration_suite.cpp` | `d97ea5435baedd7ecad959aa49ec3ce5afff3fc0` | `d9dc62b1c6aebdb4ab38f3d64150699d96f393c4` | Different — integration review required |
| `core/cpp/tests/evolution_canary_controller_suite.cpp` | `f6fbbaa54771aa1ee3665148ce638d4e9aa390ae` | same | Identical |

The PR #150 changes to `developmental_brain_integration_suite.cpp` replace direct mutable-journal appends with the restricted `import_legacy_memory_event` API. The PR #148 head and PR #155 base already contain the exact integrated blob `e6eba3db...`; therefore this source-branch delta is already subsumed before PR #156.

**Result:** two of seven files are byte-identical; one file's source-branch change is already present in PR #148/PR #155; four files differ and require semantic review. The exact identical files are `evolution_controller.cpp` and `evolution_canary_controller_suite.cpp`. The `developmental_brain_integration_suite.cpp` source change is already present at the PR #148 head and PR #155 base: PR #150 replaces direct mutable-journal appends with `import_legacy_memory_event`, and the integrated PR #148 blob already contains that API migration. PR #156 also changes `knowledge_source_feedback_suite.cpp`, which is not one of PR #150's seven changed files, to test source-bound feedback attestations. Its source-binding corrections are additional PR #156 work, not a PR #150 feature.


### B.2 PR #150's two workstreams and their integration paths

PR #150's 12 commits divide into two distinct six-commit workstreams:

**Evolution replay validation (first six commits):**
- `2786fa2f` — reject externally forged lifecycle observations.
- `a600f45a` — validate durable evidence during replay.
- `c8c857e7`, `f1e52819`, `9829878a` — forged replay/adoption/evaluator regression tests.
- `1710c57a` — reject incomplete replayed adoption events.

This workstream is represented in PR #156 through its independently authored replay-validation commits and later rollback/source-binding corrections. The final `evolution_controller.cpp` and `evolution_canary_controller_suite.cpp` blobs are byte-identical to PR #150. The Brain header/source/restored API and evolution integration suite differ and remain subject to semantic review.

**Restricted legacy-memory import (last six commits):**
- `0557ee6a` — expose Brain memory as read-only.
- `09d14f56` — add restricted legacy event import API.
- `3e1cd18c` — implement passive legacy event import.
- `ba0083b8` — keep imported legacy events passive during replay.
- `882b84a6` — update memory tests to use restricted import.
- `ec1ce132` — verify passive legacy import cannot inject evolution.

This workstream is already present through PR #148/PR #155 rather than requiring PR #156 to add it again. The PR #148, PR #155 and PR #156 `brain.hpp` files expose a const-only Memory accessor and the restricted import API. The `Brain::import_legacy_memory_event` implementation exists in all four inspected trees (PR #148, PR #150, PR #155 and PR #156); its executable statements are the same, with only comment wording differing in PR #150. The replay path treats `legacy_import` as passive episodic data. The PR #150 test-only migration in `developmental_brain_integration_suite.cpp` is also subsumed: the PR #148, PR #155 and PR #156 trees share the exact integrated blob `e6eba3db6df8da9ecfed21974936908a32ea11c5`, whereas PR #150's source blob is `b9dc34b63f7ca0b356a5a2589c39fb8b5862d2f6`.

**Result:** PR #150's source branch is not a direct ancestor, but its two workstreams are accounted for through two integration routes: memory-import restrictions via PR #148/PR #155, and evolution replay validation via PR #156. This is a content-level reconciliation, not an ancestry claim.

### B.3 Required disposition

- Do not cherry-pick PR #151 or PR #150 wholesale; the integration branches already contain a mixture of identical, adapted and subsumed changes.
- Preserve the five exact PR #151 file matches and two exact PR #150 file matches as strong evidence of retained source content, not as proof of full acceptance.
- Review the three PR #151 conflict files and four PR #150 divergent files semantically against both source-branch intent and the accepted BM contracts.
- Confirm that PR #150's source-binding and rollback-binding corrections are fully represented in PR #156's integrated diffs and tests.
- Keep all source PRs unmerged/unaccepted in the status matrix until independent review and Project Director decision.



## Appendix C — Exact blob matrix for the 172 commits after PR #97

The following table binds every path in the direct `c1da222` → `52c367a` 20-path net diff to the exact tree blob at PR #97 HEAD and at PR #155/PR #156's immediate base. A dash means the path did not exist in the PR #97 tree and was added in the 172-commit segment.

| Path | PR #97 blob | PR #155 base blob |
|---|---|---|
| `core/cpp/include/jarvis/core/brain.hpp` | `671186f4c39879a182f9e511394fc564d86f2988` | `94368254672f17045030a9effa86b0a71c2c4704` |
| `core/cpp/include/jarvis/core/developmental_learning.hpp` | `e3b9bf8af265b67829fd7deb323d88a3a9dd4b75` | `65174400d8c3ce1dea17667ac928767cf3af333a` |
| `core/cpp/include/jarvis/core/knowledge.hpp` | `3da0d2059331af405bbb0ba98c61308ead99c405` | `ae1adcffeeb090eb102c05156388bce7c030538f` |
| `core/cpp/include/jarvis/core/world_model.hpp` | `1c14f692374b0ab272f05634b7bdd26e358b4f1f` | `26a77fc5f1f04d7066426faf62d049c513cb0ae8` |
| `core/cpp/src/brain.cpp` | `dec9e5442b3ca4b81a7879855c6146b2619934cc` | `0f377bf853af866375b35a944862c743c777a4c0` |
| `core/cpp/src/brain_restored_api.cpp` | `7155d4d9c8eef527836fb79bf901aa32ddbae38b` | `2a49f2aad3a99e74316a068801e3f0f90bf69bad` |
| `core/cpp/src/causal_model.cpp` | `b7e1e6e6aeb929f09af33b9d17c80a6eed34948c` | `8b884ed11a1a019d0e52bf7f35b0295edcc912b0` |
| `core/cpp/src/cognitive_cycle.cpp` | `f191dd610d6cbe1621756c35e7c13af2054a7266` | `989f4d154f07b31bcdab175aefbea6edd61eb930` |
| `core/cpp/src/developmental_learning.cpp` | `dbf5f43271dfa0a3c57236e2faa82eb88d15490d` | `c9a34d562fa1a20641530daba81bfdc1f3621fee` |
| `core/cpp/src/knowledge.cpp` | `21de8abbcd4426cb4ead70cb089e7d7c4ed0e81a` | `c38e0909c220b450502b46fd4a145e63ab6d21a0` |
| `core/cpp/src/world_model.cpp` | `5b68e8fe37d99732557237e347ae02234a3de172` | `f98ef4106af2ba6d9565f77a8a811abe6c20f8d3` |
| `core/cpp/tests/CMakeLists.txt` | `cbfd1fde52fffa6eeac025da2b7ddcb5ab493261` | `0251936730f82a7a8c928fa31dfe1d7effc83d91` |
| `core/cpp/tests/association_causality_phase5_suite.cpp` | `0d31349857e85a019467e9864bbe6625a6ecdef7` | `9099323d43b5af16d09c9356a239692fab5e136a` |
| `core/cpp/tests/developmental_brain_integration_suite.cpp` | `760162dd6d1e669162e0bf22223a437491f5e262` | `e6eba3db6df8da9ecfed21974936908a32ea11c5` |
| `core/cpp/tests/dlt_003_mapping_generalization.cpp` | — | `90c9226a714b020c90fa0dff09790d6997e57a2e` |
| `core/cpp/tests/dlt_004_feature_composition.cpp` | — | `e486bedc813c1a70dc48b610133a147283e0d7ef` |
| `core/cpp/tests/evolution_brain_integration_suite.cpp` | `59d7dd68c42eea18d488d8e5e6aa9f7a9a327ded` | `90b6c6246473428a00d38829495f9877cd1fa05f` |
| `core/cpp/tests/knowledge_memory_phase3_suite.cpp` | `e33b9813edbfaf02a91a3f94988f5c7a54ceed8f` | `108e4c07259df599bb7371a2f4b3b497be97f844` |
| `core/cpp/tests/knowledge_source_feedback_suite.cpp` | — | `3768c0306f9638be48da2342ce299c582e52b656` |
| `docs/DEVELOPMENTAL_BRAIN_PLAN.md` | — | `6b447faa668c2c4a559e55fb40dbd301f53e1704` |

This closes the tree-level blob inventory for the 172-commit post-PR #97 segment. It does **not** yet identify the exact commit that last changed each path, attribute every hunk to its originating PR, or determine whether the resulting implementation satisfies BM acceptance scenarios. Those are the remaining commit-to-file and semantic reconciliation tasks.


## Appendix D — Exact PR #97 / post-PR #97 file-set reconciliation

Three independent tree comparisons were set-reconciled:

- `af09cf28` → `c1da222`: 159 paths (PR #97 inherited line).
- `c1da222` → `52c367a`: 20 paths (the 172-commit post-PR #97 segment).
- `af09cf28` → `52c367a`: 165 paths (the final candidate integration-base tree delta).

The path sets reconcile exactly:

**145 PR #97-only paths + 14 paths modified in both segments + 6 paths first introduced after PR #97 = 165 final paths.**

No path in the PR #97 net diff disappears from the final candidate-base net diff. No path in the post-PR #97 20-path diff disappears from the final candidate-base net diff. The 165-path candidate tree is therefore the exact union of the 159-path PR #97 diff and the 20-path post-PR #97 diff, with 14 overlapping paths.

### D.1 Fourteen paths modified in both segments

- `core/cpp/include/jarvis/core/brain.hpp`
- `core/cpp/include/jarvis/core/developmental_learning.hpp`
- `core/cpp/include/jarvis/core/knowledge.hpp`
- `core/cpp/src/brain.cpp`
- `core/cpp/src/brain_restored_api.cpp`
- `core/cpp/src/causal_model.cpp`
- `core/cpp/src/cognitive_cycle.cpp`
- `core/cpp/src/developmental_learning.cpp`
- `core/cpp/src/knowledge.cpp`
- `core/cpp/tests/CMakeLists.txt`
- `core/cpp/tests/association_causality_phase5_suite.cpp`
- `core/cpp/tests/developmental_brain_integration_suite.cpp`
- `core/cpp/tests/evolution_brain_integration_suite.cpp`
- `core/cpp/tests/knowledge_memory_phase3_suite.cpp`

### D.2 Six paths first introduced after PR #97

- `core/cpp/include/jarvis/core/world_model.hpp`
- `core/cpp/src/world_model.cpp`
- `core/cpp/tests/dlt_003_mapping_generalization.cpp`
- `core/cpp/tests/dlt_004_feature_composition.cpp`
- `core/cpp/tests/knowledge_source_feedback_suite.cpp`
- `docs/DEVELOPMENTAL_BRAIN_PLAN.md`

The remaining 145 paths are present in PR #97's net diff and are not changed again in the 172-commit post-PR #97 segment. This is a path-set statement, not a claim that their behavior is correct or accepted.
