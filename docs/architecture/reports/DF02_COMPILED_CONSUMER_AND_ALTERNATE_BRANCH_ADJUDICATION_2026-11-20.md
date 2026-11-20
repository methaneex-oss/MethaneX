# DF-02 — Compiled-consumer and alternate-branch adjudication

**Date:** 2026-11-20  
**Donor PR #97:** `c1da222e6c94aeb3f2ad000392c21fe4fc81ab25`  
**Candidate source snapshot:** PR #192 base `61311fe5b44c81c4409c8ba8dc581a83bdd5dd2c`  
**Candidate branch scan tip:** `84dd10094cac675b97b1ab2d45b36618d61efe38`  
**Refined scan artifact:** `14659828741`, SHA-256 `3a7d90b475564097a2ccf1de3f4492659b4417a7d46d3e193d9c95ff7b78ab22`

## 1. Candidate-branch consumer refinement

The refined scan's 118 donor paths with lexical candidates across all refs reduce to 111 paths with at least one candidate on the PR #192 documentation branch snapshot `84dd100...`. That snapshot's source/build/test/workflow content is unchanged through the candidate snapshot `cbc51e2...` and the terminal PR #192 HEAD `5a730316...`; the intervening compare shows documentation/audit-only paths, not Brain C++, engineering C++, CMake or test-source changes.

On the candidate snapshot:

- 107 donor paths have source-category lexical matches; 85 have at least one match in a compiled translation unit.
- 123 candidate source/header consumer paths were present in the artifact. A bounded include-graph walk from the 62 CMake-compiled translation units (57 core + 5 engineering) reaches all 123 paths, including 61 headers. This establishes compile-time reachability, not runtime behavior.
- 50 test-category consumer paths were found; 45 core test executables and one engineering test executable are registered. The other three actual test files (`brain_smoke.cpp`, `evolution_experiment_test.cpp`, `representation_suite.cpp`) are not CTest targets; the fourth path in the 50 includes the CMake test file itself.
- 11 workflow files and four build files have candidate-branch lexical references.

The candidate CMake evidence is exact:
- `core/cpp/CMakeLists.txt` blob `c51816888e1bddb7bc00c59e72529524e27a0717`: 57 source translation units; no `brain_affective_planning.cpp`, no `brain_prediction_context.cpp`, no affective-planning include, and no examples subdirectory.
- `core/cpp/tests/CMakeLists.txt` blob `dab0c52ab4dfe15e1e2cbccfa9e6c904abdf54e3`: 45 executables / 45 CTest registrations.
- `engineering/cpp/CMakeLists.txt` blob `7e2621c8678ad784d6e8c9e777b22b7c5310b855`: five library sources / one test executable / one CTest registration; task-ledger source and test are omitted.

The seven additional donor paths found only on other branch refs are not candidate-branch integrations. Their exact dispositions follow.

## 2. Seven other-ref-only donor paths

### 2.1 Affective planning implementation

`core/cpp/src/brain_affective_planning.cpp` is absent from the candidate tree but byte-identical to donor blob `2a9406257c23f3a66a64071842be7d6448799406` at alternate integration tip `52c367a4b53fdfe9b29776795200555076e8cb49` (`integration/knowledge-composition-20261031`).

That branch's core CMake blob `bc264ce7b4ae489404ca03ea6d9676d0330a6a56` is also donor-identical and compiles this source. It declares `Brain::plan_with_affect` and `Brain::choose_with_developmental_learning`; the latter applies confidence/similarity-weighted developmental evidence to candidate action utility before decision selection. The branch's `tests/affective_planning.cmake` blob `e3a52416b2538791a93666e5124b1f34ad1b082a` registers `affective_planning_suite`.

**Disposition:** genuine alternate-branch implementation and test registration; absent from the candidate baseline. This is not a candidate successor and is not adopted.

### 2.2 Contextual prediction implementation

`core/cpp/src/brain_prediction_context.cpp` is absent from the candidate tree but byte-identical to donor blob `b3ceff150f3fe8223dc3f76f4c298ac264d72dae` at the same alternate integration tip. The donor-identical core CMake compiles it.

The implementation exposes `Brain::predict_with_context`: it uses generalized/contextual associations, optionally calibrates numeric predictions from adaptation metrics, appends the prediction event to memory, replays it, consolidates experience and synchronizes self-state. The alternate branch's test CMake includes association-causality and prediction-feedback suites.

**Disposition:** genuine alternate-branch contextual prediction and experience-persistence path; absent from the candidate baseline. No source-baseline adoption is inferred.

### 2.3 Affective-planning test

`core/cpp/tests/affective_planning_suite.cpp` is absent from the candidate tree. The alternate integration branch's `affective_planning.cmake` registers it as a CTest executable. The candidate branch has no corresponding target or verified equivalent suite.

**Disposition:** missing from candidate test registration; retained in the alternate integration branch.

### 2.4 Association-causality suite

The candidate retains a same-path, registered but substantially reduced suite: donor blob `0d31349857e85a019467e9864bbe6625a6ecdef7` has 46 assertions; candidate blob `d520025258805b02c1b3fbb2dbebe32e01562fbf` has 12. The donor tests reliability-weighted association updates and contextual/multi-hop inference in addition to causal simulation and Brain integration. The candidate removes the low-reliability calibration assertions and several contextual checks.

**Disposition:** same-path target retained, but material test coverage reduced (34 fewer assertions); not equivalent coverage.

### 2.5 Reasoning-architecture suite

The candidate retains a same-path, registered but reduced suite: donor blob `ceb6d471b3283f4a89fe243ac3c9e79f52f137a2` has 33 assertions; candidate blob `a7119afd091e045d6294aa1b15c20de349ed6a1c` has 19. The donor explicitly tests disputed-premise propagation and causal-link codec encode/decode behavior; the candidate removes those checks and no longer includes `causal_link_codec.hpp`.

**Disposition:** same-path target retained, but 14 assertions and important provenance/codec coverage removed.

### 2.6 Experience-memory header

`core/cpp/include/jarvis/core/experience_memory.hpp` is absent from the candidate tree. Alternate branches contain the donor header and `experience_memory_test.cpp`, which exercises `ExperienceMemory`, `for_key`, `latest_unresolved` and `record_prediction`. Some scanner hits in production files are only the generic token `resolve`; those are not treated as proof of production integration.

**Disposition:** test-backed alternate-branch artifact; no distinctive production integration is established by the exact consumer evidence. Candidate header and standalone test are absent.

### 2.7 Engineering task ledger

`engineering/cpp/include/jarvis/engineering/task_ledger.hpp` is absent from the candidate tree. At alternate tip `1e7b659ad0fdd9ffc6d77b0566c60e25d75cecf9` (`ci/priority-one-validation-20261031`), the header, `task_ledger.cpp` and `task_ledger_suite.cpp` are byte-identical to donor blobs:
- header `95d3f2e42be742f9e75aed8e55ea389723534a64`;
- source `7acff8990319392c9984035a4a14cc83f7154072`;
- suite `e90c062261c95ff99d4b1bdcb55ce7bfad0512ec`.

The alternate branch's engineering CMake blob `44ad82199248b9a6a53d996d046e2e3eb8265f1c` compiles `task_ledger.cpp` and registers `jarvis_engineering_task_ledger_suite`. Its coordinator calls `dispatch_tracked` through the ledger. The ledger persists task status, agent assignment, base/result revisions and evidence; uses compare-and-swap versioned transitions; checks dependencies; and reconstructs latest valid snapshots on restart. Candidate engineering CMake blob `7e2621c8678ad784d6e8c9e777b22b7c5310b855` omits the source and suite.

**Disposition:** mature, compiled and tested alternate-branch capability; absent from candidate baseline. This is not adopted.

## 3. Source-lineage conclusion

The refined scan is no longer being treated as a flat set of 118 candidate paths. It now distinguishes (a) candidate-branch compile-reachable source/header references, (b) registered versus unregistered test consumers, (c) the seven donor paths visible only on other refs, and (d) exact donor-identical implementations on named alternate branches.

This evidence reveals at least two distinct source lines worth preserving for Project Director comparison: the candidate baseline and the alternate knowledge-composition / priority-one integration branches. The latter contain donor-identical affective planning, contextual prediction and task-ledger implementations with their CMake/test integration. Their existence does not establish that they should replace or be merged into the candidate baseline.

**DF-02 remains OPEN.** This supplement resolves seven previously ambiguous other-ref-only path cases and sharpens the 111 candidate-branch consumer map. The remaining lexical candidates still require per-path semantic successor/retention/retirement/non-adoption, dependency and duplicate-owner review. The Project Director retains source-baseline and adoption authority. No donor code was merged or copied.
