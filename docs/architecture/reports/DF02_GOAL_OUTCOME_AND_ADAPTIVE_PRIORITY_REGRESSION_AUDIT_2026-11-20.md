# DF-02 — Goal-outcome learning and adaptive-priority regression audit

> **Scope clarification:** This is a capability-gap comparison between the pre-PR-#97 candidate source baseline and the unmerged PR #97 donor implementation line. It does **not** claim the candidate previously integrated these donor mechanisms and then lost them. The term “regression” in this historical report filename means a functional delta relative to the donor, not a post-integration code regression. The donor is not an adopted baseline; the Project Director retains source selection and adoption authority.

**Date:** 2026-11-20  
**Candidate baseline:** PR #192 base/merge-base `61311fe5b44c81c4409c8ba8dc581a83bdd5dd2c`. Every candidate source/test blob cited in this report was re-fetched at that exact PR base and matched the blob previously inspected at `cbc51e2b10f1fc976257653adf773735a2b27d49`.  
**Donor snapshot:** PR #97 HEAD `c1da222e6c94aeb3f2ad000392c21fe4fc81ab25`

## 1. Goal progress no longer changes priority from observed outcome direction

| Artifact | Candidate blob | Donor blob |
|---|---|---|
| `core/cpp/include/jarvis/core/goals.hpp` | `803fdd34130c71f54912b23fcba2f9eed23dd4f2` | `66f8cd436a18a0bca8039205f682fc929c32b6a5` |
| `core/cpp/src/goals.cpp` | `778a829de8314e83b095af2f2c2a6b83baa769f4` | `afaedcfb0f2f68ff88b3a20e474fce04bb59815c` |
| `core/cpp/tests/goals_architecture_suite.cpp` | `14a52aa606b53f8529aa5c54861c11902deb7c97` | `0b99d090b400d0af50b186cd3a416fa28a177b99` |

The donor `Goal` stores an `outcome_momentum` value. On every valid progress update, the donor calculates the signed progress delta, updates a smoothed momentum value and adapts goal priority according to the direction of observed progress. The candidate `Goal` has no `outcome_momentum`; candidate `update_progress` changes progress/status only and does not revise priority from outcome direction.

This means the candidate does not retain the donor's persistent, experience-derived momentum signal for future goal appraisal. A deteriorating goal's priority cannot be revised through this mechanism based on the observed negative progress delta.

## 2. Separate goal-outcome evidence model and test are absent from candidate

The donor contains `core/cpp/include/jarvis/core/cognitive_goal_outcome.hpp` (donor blob `c986480d82b9951177031f3387169819c3856234`) and a dedicated `goal_outcome_model_suite.cpp` (blob `c9f19978d6d2df45028cb824e835144dc45c70e7`, 15 assertions / 44 lines). The suite checks normalized progress deltas, positive and negative outcome counts, confidence aggregation, completion evidence and rejection of unrelated goal IDs.

The candidate snapshot has no `cognitive_goal_outcome.hpp` or `goal_outcome_model_suite.cpp`. Its candidate `goals_architecture_suite.cpp` has 34 assertions / 72 lines versus 45 assertions / 100 lines in the donor. The candidate's uncompiled `brain_restored_api.cpp` contains a `Brain::assimilate_goal_outcome` definition, but that translation unit is excluded from candidate CMake and the candidate public Brain header does not expose that API. It is not an integrated candidate successor.

## 3. Design caution

The donor goal-priority update uses fixed coefficients for momentum smoothing and priority adaptation. This report records the capability gap, not a recommendation to copy those coefficients. The correct mechanism must allow goal priority to respond to accumulated outcome evidence without hardcoding specific goal IDs or mapping a particular outcome to a fixed behavior. Its update dynamics should be independently tested, persisted and replayed.

## 4. Builder disposition

The candidate goal system supports goal creation, prerequisites, deadlines, progress and status transitions. This finding is narrower: it lacks the donor's outcome-derived momentum/priority adaptation and separate outcome evidence model with its test coverage.

No runtime or CMake files were changed. No donor code was copied. DF-02 remains OPEN pending remaining candidate paths and dependency/ownership/authority adjudication.
