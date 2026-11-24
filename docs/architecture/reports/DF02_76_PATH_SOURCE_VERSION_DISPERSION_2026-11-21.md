# DF-02 — Source-version dispersion across the 76 divergent candidate paths

**Date:** 2026-11-21  
**Candidate branch tip:** `84dd10094cac675b97b1ab2d45b36618d61efe38`  
**Donor PR #97 HEAD:** `c1da222e6c94aeb3f2ad000392c21fe4fc81ab25`  
**Scan artifact:** PR #199 run 44799437811 / artifact 14659828741; SHA-256 `3a7d90b475564097a2ccf1de3f4492659b4417a7d46d3e193d9c95ff7b78ab22`

## 1. Exact version-dispersion result

The refined scan's `donor_path_presence.csv` reports each donor path's unique blob-version count across 213 unique branch tips, plus counts of tips holding the donor-identical blob and tips holding a divergent blob. For the 76 candidate-branch paths whose same-path artifact differs from the donor:

- 17 paths have exactly two unique blob versions.
- 59 paths have three or more unique blob versions.
- The maximum is 40 distinct blob versions for `core/cpp/tests/CMakeLists.txt`.
- Other high-dispersion paths include `core/cpp/src/brain.cpp` (35), `core/cpp/tests/evolution_brain_integration_suite.cpp` (24), `core/cpp/CMakeLists.txt` (22), `core/cpp/include/jarvis/core/brain.hpp` (21), `core/cpp/src/brain_restored_api.cpp` (20), `core/cpp/src/evolution_controller.cpp` (19) and `core/cpp/tests/evolution_experiment_runner_suite.cpp` (18).

This confirms that the 76 divergent files are not a simple two-snapshot comparison across the repository. Numerous branches contain materially different versions of the same path. A branch name or the fact that a path exists is therefore not enough to identify the implementation owner.

## 2. Why the current scan cannot close exact ownership

The artifact provides:
- the number of unique blob versions per donor path;
- the number of branch tips holding the donor-identical blob;
- the number of branch tips holding a divergent blob;
- the complete set of branch names on which the path exists;
- the unique branch-tip SHA inventory.

It does **not** provide a direct join from each branch name/tip SHA to the exact blob SHA for each donor path. Therefore the current artifact cannot prove which specific branch owns each divergent blob version. The counts above are exact, but assigning the 76 files to specific source owners from the current columns would be inference, not evidence.

## 3. Scanner correction prepared

The read-only scanner now has an additional `path_blob_ownership.csv` output in commit `40504187e45ce2e5dbafb6c6caad9e1c47e42dc9` on `audit/df02-all-ref-consumer-scan-20261120`. The new output groups each donor path by exact blob SHA and lists the branch tips and branch names that contain that exact version. It also pins the candidate SHA to the candidate branch snapshot used for the next scan.

The scanner enhancement is committed but **not executed**. The installed GitHub connector exposes read, file/commit/ref writes, artifact retrieval and job reruns, but no workflow-dispatch operation. The existing all-ref workflow is a manual-dispatch workflow on the audit branch; updating the branch through the connector did not create a new workflow run. The previous run at commit `8179bafcc5cb681a8abc73a0bf9819bbdd6a0b9e` is the old scan and does not exercise the new output. The scanner change is therefore not represented as tested.

## 4. DF-02 disposition

The 76 paths have complete focused-report cross-reference coverage, and the 35 absent-path cases are individually adjudicated. The remaining Builder-owned technical task is to execute the exact branch-to-blob ownership scan and reconcile the resulting clusters into donor-identical copies, candidate successors, distinct implementations and stale/unowned variants. Until that evidence exists, DF-02 cannot truthfully be marked fully closed.

No source/runtime code was changed. No branch is declared owner merely because it contains the donor blob. No source baseline, merge, retirement or non-adoption decision is made here; those decisions remain with the Project Director.


## 5. Superseding exact branch-to-blob scan — 2026-11-21

The statement in §§2–4 that the available scan could not map a branch/tip to the exact blob is superseded.

A new all-ref scan was executed by workflow 44931803411 on candidate PR #192 source snapshot 19c1c168fdbdab58ed9732cd250d2ae4624936eb and donor PR #97 HEAD c1da222e6c94aeb3f2ad000392c21fe4fc81ab25. Scanner commit b8a594ea514ff44cadb5342986c68b1eac6e22ed; artifact 14717933378; SHA-256 189f65b26b78e3811fb5b2c9fef6cfc97a8f6a24c8f62f80b0f6c1e7c9d70e7f.

The new artifact includes path_blob_ownership.csv, directly joining each donor path and exact blob SHA to branch names and unique tip SHAs. It contains 798 path/blob ownership rows and 1,938 exact path-reference rows. The full scan covers 254 branch refs / 213 unique tips, 1,415 text blobs, 40,041 lexical candidate rows, and 1,226 consumer-blob/path/category occurrences. The 76 divergent candidate paths remain 76; the new scan resolves which exact branch tips hold each version.

The earlier 76-path dispersion counts (17 paths with two versions, 59 with three or more, maximum 40 versions for core/cpp/tests/CMakeLists.txt) remain valid as counts. The old statement that exact ownership could not be established is no longer current. The new exact ownership map is an input to semantic reconciliation, not a source-baseline decision.

**DF02 remains OPEN:** exact branch ownership is now available, but each material divergent path still requires semantic successor/duplicate-owner/retirement disposition, and source-baseline authority remains with the Project Director.

## 6. Exact-path coverage and artifact integrity correction — 2026-11-24

A Builder cross-reference pass matched the 76 divergent candidate-branch paths against the existing focused DF-02 source/build/test reports by exact repository path. **Coverage is 76/76: 70 core paths and six engineering paths.** The engineering subset is covered by `DF02_ENGINEERING_AGENT_DELIVERY_AND_TASK_LEDGER_GAP_2026-11-21.md`; the core subset is distributed across the action-feedback, affective/developmental, attention/self-model, causal/persistence, cognitive-cycle, runtime/memory/association, evolution-isolation, goal-outcome, prediction-identity, representation/canary and supporting cognitive-contract reports.

Together with the existing per-path reports for the 35 absent-path cohort and the 48 no-symbol cohort, all 159 PR #97 donor paths now have candidate-path-level semantic coverage. This corrects the older blanket statement that all 76 divergent candidate paths still lacked focused semantic reports. It does **not** claim that every alternate-branch blob variant or every lexical consumer match has been semantically adjudicated.

The exact all-ref artifact identity is corrected here. Workflow run `44931803411`, artifact `14717933378`, has SHA-256 `189f65acfc5561c71da652ac32b71d308aa47ea8737793381af3a17cae45676a`. The earlier digest `189f65b26b78e3811fb5b2c9fef6cfc97a8f6a24c8f62f80b0f6c1e7c9d70e7f` recorded in §5 was incorrect and is superseded.

The artifact records 254 branch refs / 213 unique tips, 1,415 unique text blobs, 40,041 symbol-match rows, 1,938 exact path-reference rows, 798 exact path/blob ownership rows, and 1,226 matched consumer-blob contents. A separate parse of the complete artifact identifies 413 distinct consumer paths. These are lexical/path-reference discovery candidates, not 1,226 proven dependencies.

The candidate source snapshot in the artifact is `19c1c168fdbdab58ed9732cd250d2ae4624936eb`. Exact comparison to current PR #192 HEAD `437c26939db515f8fbabdab238a8e6042848eec1` is eight commits ahead / zero behind and changes 12 documentation, workflow, index, inventory, checkpoint and audit-script paths; no C++ or engineering source path changed. The candidate source/build/test blob identities therefore remain applicable to the current PR #192 source baseline.

**DF-02 remains OPEN.** Candidate-path semantic coverage and exact ownership mapping are now reconciled. Remaining work is limited to material alternate-branch implementation/consumer clusters and historical authority/retention dispositions. Do not re-review duplicate branch names when their exact blob SHA is identical; do not promote incidental lexical matches, documentation mentions, tests or workflows into runtime dependency claims.
