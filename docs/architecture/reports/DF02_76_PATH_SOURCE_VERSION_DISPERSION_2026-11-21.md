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
