# DF-02 Core Test-CMake Variant and Registration Adjudication — 2026-11-28

**Scope:** exact 40-blob historical cohort for `core/cpp/tests/CMakeLists.txt`, including target/CTest registration, Release assertion behavior, and donor/candidate graphs.  
**Candidate:** frozen PR #192 SHA `caf87986dfea7aca75728818651c8687e9f5faf0`.  
**Donor:** PR #97 HEAD `c1da222e6c94aeb3f2ad000392c21fe4fc81ab25`.  
**Evidence:** artifact #14956148301 / workflow #45470173876; archive SHA-256 `9902957475c76f4840d1d280c7d4f50537941e9445810afb805132374a328f38`.  
**Disposition:** 40-blob test-subdirectory cohort enumerated; candidate/donor parent-level CMake reachability reconciled. Historical alternate e737cae7 has 71/71 native/sanitizer/TSAN test execution; current PR #203 candidate has no CTest execution in this sprint.

## 1. Candidate/donor registration

| tests/CMakeLists subdirectory only | Executable targets | CTest registrations | Exact-name unregistered targets |
|---|---:|---:|---|
| Candidate | 45 | 45 | 0 |
| Donor | 71 | 70 | 3 |

Candidate blob: `dab0c52ab4dfe15e1e2cbccfa9e6c904abdf54e3`. Donor blob: `cbfd1fde52fffa6eeac025da2b7ddcb5ab493261`.

Donor exact-name target/CTest mismatches:
- `jarvis_dlt_002_persistence` is represented by separate `jarvis_dlt_002_persistence_train` and `jarvis_dlt_002_persistence_verify` CTest entries. It is a split workflow contract, not a simple absent test.
- `jarvis_dlt_001_long_run` and `jarvis_dlt_002_long_run` have executable targets but no direct CTest entries; these are workflow/manual long-run paths. They must not be counted as routine CTest coverage.

The donor test CMake explicitly adds Release assertion preservation:
- GNU/Clang: `-UNDEBUG`
- MSVC: `/UNDEBUG`

The candidate graph does not contain this override. This matters because many test suites use C/C++ `assert`; without override, Release builds can compile those assertions away. The target's assertion behavior still requires build-configuration verification.

## 2. All 40 distinct CMake blobs

The table below records the exact blob SHA and source-text extraction: executable targets, CTest names, executable names not exactly matched by a CTest name, and Release assertion override. “Mismatch” is a lexical name comparison, not a semantic failure; train/verify aliases and workflow-only long-run targets need intentional classification.

| Blob SHA | Exec | CTest | Name mismatch | Release assert override |
|---|---:|---:|---:|---|
| `00fd97a0fd43891947f14830c18ff3f34352fa93` | 30 | 30 | 0 | No |
| `0251936730f82a7a8c928fa31dfe1d7effc83d91` | 73 | 72 | 3 | Yes |
| `03674e40cbd47c60d0d93c9efc32937e97e210a1` | 73 | 72 | 3 | Yes |
| `0576d5b8c77b9b77d8ccef6cb5dad9bd6e12ccae` | 70 | 70 | 4 | Yes |
| `07a6421fe425b3a86f414c5923854d8a1ce4bc7e` | 70 | 69 | 3 | Yes |
| `1bd451f8338ba12f63cb7da7ace0299c0508ce69` | 43 | 43 | 0 | No |
| `22c3fe3043741baf3bc47b57c3dc4fe3b488e47a` | 18 | 18 | 0 | No |
| `23bc866d866c5f40d66a957e738b80841360fab6` | 51 | 51 | 0 | No |
| `40f7556b9b574903465b5f1146b8240f9dd5bf0f` | 23 | 23 | 0 | No |
| `40fd77f0f865721b5ad056ace9a9a961ec7e9e0b` | 40 | 40 | 0 | No |
| `446e952590780b81f8bccf78b5604cd0268e8844` | 22 | 22 | 0 | No |
| `4bd7eb44443723e7b4b23e958bbcda379f18a741` | 72 | 71 | 3 | Yes |
| `4c034eefa3547cd6d070d24406f0ff159163fd6f` | 74 | 73 | 3 | Yes |
| `50ddc67e98f8ef24ecbe5fa72e4cf6833bf69aa2` | 70 | 70 | 4 | Yes |
| `56b9b92614585a3c6188d8b9e16fe2fe24b94e57` | 29 | 29 | 0 | No |
| `660752e9222495f2f2e2d6a7d4c6ac9a275e2127` | 25 | 25 | 0 | No |
| `6660a0a196a06f6805985574764fefc70284d93a` | 42 | 42 | 0 | No |
| `6b7793e5e8dd9dab4a7b71e1bc487868bd926d84` | 70 | 69 | 3 | Yes |
| `6c41c98d9967d6730c0c5a964d55c9afdf83e33c` | 27 | 27 | 0 | No |
| `7c379ba06920226c66096e869e2b70258a2d69a4` | 20 | 20 | 0 | No |
| `87edb5195f14afa6a73bd6f7aadbd02c4bd68c9c` | 69 | 68 | 3 | Yes |
| `8d0d24a2094be02dac9f57a37c3fdf504439ab53` | 24 | 24 | 0 | No |
| `92d8dac34cee2d1da961e9e3cee9e316c778a0b1` | 70 | 68 | 4 | Yes |
| `9a15c936d103e4633faa6a9cf18493a2ce1b9e20` | 72 | 70 | 4 | Yes |
| `a4e72494be4629002182684229acfeeb3b3f413d` | 41 | 41 | 0 | No |
| `a51175cffbbe5deb862d9f88dd96ac77f3f44505` | 70 | 68 | 4 | Yes |
| `a6950319fa932693bb6fe4721909ed447a2c5549` | 32 | 32 | 0 | No |
| `b193b9f860c894ce6a3494828ddc3d0d86d052ac` | 17 | 17 | 0 | No |
| `b8ca96bd39133676e2dfa32a6a54b27450ac112e` | 73 | 72 | 3 | Yes |
| `c80921dc5e2fff271bfcc367cb647505b6d5ed5d` | 28 | 28 | 0 | No |
| `c80a89d326bd8b495a61af523f1e9335b270bdb7` | 26 | 26 | 0 | No |
| `cbfd1fde52fffa6eeac025da2b7ddcb5ab493261` | 71 | 70 | 3 | Yes |
| `d21f87ed4896b3768d0f76adda41f70ca71cf45c` | 44 | 44 | 0 | No |
| `dab0c52ab4dfe15e1e2cbccfa9e6c904abdf54e3` | 45 | 45 | 0 | No |
| `db6e5c39c40cf619d89d6ffdd333b65b50135283` | 21 | 21 | 0 | No |
| `db893cb4a992b98d8533ca91686c13942fa639bc` | 70 | 69 | 3 | Yes |
| `dcb54a25af2ebd6a6a999ec403817b02cd7e3746` | 43 | 43 | 0 | No |
| `e301cf24fda5633fec10e7a8a3487a76f1b3ce1a` | 39 | 39 | 0 | No |
| `e843b22930c9e1a4f65a46f09d35703928500e76` | 42 | 42 | 0 | No |
| `f546d85987145e5638d8a24bf1ae7256169b09b5` | 72 | 71 | 3 | Yes |

## 3. Cohort-level feature findings

- Target count ranges 17–74; CTest registration count ranges 17–73 across the 40 unique blobs.
- 16/40 variants contain explicit Release assertion-preservation flags. Candidate frozen blob lacks them; donor frozen blob contains them.
- The larger CMake family adds eight affective suites, six developmental suites (one variant has seven), feedback suites, learning/evolution persistence integration, DLT trials and long-run workflow targets. Older compact versions do not register those features.
- The CMake evolution is not monotonic: different branches introduce, remove, rename, split, or omit suites. Some historical variants contain extra persistence/unseen-transfer integration targets; other variants do not. Branch chronology cannot select authority.
- Same-name mismatch extraction flags 16 versions with at least one target/CTest name discrepancy; some discrepancies are intentional custom train/verify or workflow-driven long-run operations. Exact semantics of every mismatch and owner-tip retention remain open.

## 4. Review lenses and remaining work

1. **Build graph:** exact candidate/donor target and test registration compared; all 40 historical blobs feature-extracted.
2. **Behavioral verification:** CMake declares targets and tests; it does not prove the source compiles, tests execute, or assertions are active in a real Release build.
3. **CI/workflow authority:** long-run and persistence targets are not equivalent to routine CTest. Their workflow/manual invocation and artifact validation must be traced to exact workflows.
4. **Hostile review:** Release-assert override is a positive safeguard in donor, but CMake flags alone cannot prove the compiler/target inherits the flag. Registration count is not test quality or independence.
5. **Provenance:** owner branches/tip counts remain pointers; authority and retention dispositions are unresolved.

Open obligations: full per-blob diff for all 40; exact test-source and workflow consumers for target/test aliases; verify assertion flags at generated compile commands; build and CTest execution at frozen refs; owner/authority/retention. DF-02 remains OPEN.

**Disposition:** test-CMake cohort is inventoried and reachability-adjudicated at source level only. No source selected, adopted, retired, deleted, or Stage A authorized.

 
## CI-versus-source CTest count discrepancy — 2026-11-28

A further hostile consistency check found an unresolved count mismatch:
- Exact donor tests/CMakeLists.txt blob cbfd1fde52fffa6eeac025da2b7ddcb5ab493261 contains 71 add_executable calls and 70 literal add_test calls.
- The post-fix alternate branch CI at HEAD e737cae7f907696ef787a4e85b0dee3a739d71b1 reports 71/71 CTest tests passed in Brain CI #1826, JARVIS Brain Tests #975 and Brain ThreadSanitizer #957.
- The available job-log payload is truncated at the beginning: test names #10–#71 are visible, but tests #1–#9 are not. No workflow artifact containing generated CTestTestfile.cmake or a complete LastTest.log was attached to the run.
- core/cpp/CMakeLists.txt blob 33197f92141a241ff0546af1bf81fbf177a1f3ab only exposes add_subdirectory(tests) under BUILD_TESTING; no additional literal add_test was found in that file. tests/CMakeLists.txt has no function/macro or include statement that obviously accounts for a generated extra test.

Do not silently reconcile 70 source registrations with 71 executed tests. The 70 count is an exact static count of literal add_test invocations in this file; 71/71 is the actual CI summary. The 71st CTest test was not represented in this file; it is registered by a parent-level included CMake script. See the resolved reconciliation below. The 71 executable / 70 CTest values remain correct for this subdirectory only, not for the full donor graph.

 
### Parent-level CMake inclusion resolves the 71st CTest test — 2026-11-28

The previous count discrepancy is now resolved by inspecting the parent CMake file and the included script:
- Candidate core/cpp/CMakeLists.txt blob c51816888e1bddb7bc00c59e72529524e27a0717 has include(CTest) and add_subdirectory(tests) under BUILD_TESTING (lines 77–79); it does not include affective_planning.cmake.
- Donor core/cpp/CMakeLists.txt blob bc264ce7b4ae489404ca03ea6d9676d0330a6a56 adds include(${CMAKE_CURRENT_SOURCE_DIR}/tests/affective_planning.cmake) after add_subdirectory(tests) (lines 79–82).
- The included script core/cpp/tests/affective_planning.cmake is donor blob e3a52416b2538791a93666e5124b1f34ad1b082a. It adds jarvis_affective_planning_suite and its add_test registration.
- The donor tests/CMakeLists subdirectory contributes 71 executable targets / 70 CTest registrations. The parent include contributes one executable / one CTest registration. The complete donor graph is therefore 72 executable targets / 71 CTest registrations.
- The candidate tests/CMakeLists contributes 45 executable targets / 45 CTest registrations, and the candidate parent has no additional affective_planning include; complete candidate graph remains 45/45.
- The successful historical CI's test #1 is jarvis_affective_planning_suite, exactly the parent-included test. Tests #2–#71 are represented by the subdirectory registrations.

This reconciles the 71/71 CI summary with the CMake graph. The prior "71st test unknown" finding is CLOSED for the inspected donor/alternate graph. The broader 40-blob historical CMake cohort still requires per-variant parent-CMake inclusion analysis; this reconciliation applies to the frozen candidate, frozen donor and e737 alternate refs listed here.

 
### Exact CTest execution attribution

The e737cae7 historical alternate branch used the same donor CMake blobs:
- core/cpp/CMakeLists.txt 33197f92141a241ff0546af1bf81fbf177a1f3ab;
- core/cpp/tests/CMakeLists.txt cbfd1fde52fffa6eeac025da2b7ddcb5ab493261;
- core/cpp/tests/affective_planning.cmake e3a52416b2538791a93666e5124b1f34ad1b082a.

The CI run's first test is jarvis_affective_planning_suite, supplied by the parent include; tests #2–#71 are the tests subdirectory registrations. Brain CI #1826 native/sanitizer, JARVIS Brain Tests #975 brain/sanitizer, and Brain ThreadSanitizer #957 each report 71/71 passed. This is actual execution evidence for the historical alternate graph. The current PR #203 candidate remains 45/45 CTest registrations at source level, but no current-branch CTest run is claimed.
