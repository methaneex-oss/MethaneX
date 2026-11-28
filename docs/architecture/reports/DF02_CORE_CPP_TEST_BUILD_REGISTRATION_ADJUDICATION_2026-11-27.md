# DF-02 Core C++ Test Build/Registration Reachability Adjudication — 2026-11-27

**Scope:** frozen candidate/donor `core/cpp/tests/CMakeLists.txt` exact target and CTest registration comparison, source-path reachability and CI execution limits.  
**Candidate:** PR #192 frozen SHA `caf87986dfea7aca75728818651c8687e9f5faf0`. **Donor:** PR #97 `c1da222e6c94aeb3f2ad000392c21fe4fc81ab25`.  
**Disposition:** donor expands registered test build substantially and keeps assertion checks enabled in Release. Registration is verified; execution is not.

## 1. Exact CMake refs

- Candidate `core/cpp/tests/CMakeLists.txt`: `dab0c52ab4dfe15e1e2cbccfa9e6c904abdf54e3`.
- Donor: `cbfd1fde52fffa6eeac025da2b7ddcb5ab493261`.
- Discovery artifact has 40 distinct CMake blobs across 212 branch-tip sightings; this report compares frozen candidate/donor.

## 2. Target/test-set reconciliation

| Frozen version | Executables | CTest entries |
|---|---:|---:|
| Candidate | 45 | 45 |
| Donor | 71 | 70 |

Donor adds 26 executable targets and 25 CTest entries. No candidate-only executable or CTest name was found in the exact set comparison. No duplicate target/test names were found. All CTest command names map to registered executable targets.

The donor CMake defines three targets without a direct single CTest entry:
- `jarvis_dlt_001_long_run` — explicitly invoked by its dedicated long-run workflow;
- `jarvis_dlt_002_long_run` — explicitly invoked by the dedicated long-run/overnight workflows;
- `jarvis_dlt_002_persistence` — registered as two CTest fixture commands (`train` then `verify`) running in separate OS processes; fixture setup/required ordering enforces verification after training.

Thus the raw target/test count difference is intentional in the source: two long-running targets are workflow-driven, and the persistence target has two test invocations. No unregistered ordinary suite was identified in this comparison.

## 3. Test-source reachability

All 71 donor `add_executable` source paths were reconciled against the captured exact file inventory; 20 paths absent from the variant-discovery table were individually fetched at the donor SHA and confirmed present. Remaining target source paths were in the captured inventory. This verifies path existence, not compile correctness or test completeness.

The donor file:
- links every suite to `jarvis_core`;
- enables CTest with `include(CTest)`;
- registers tests under `if(BUILD_TESTING)`;
- adds DLT-002 train/verify fixture ordering;
- explicitly applies `-UNDEBUG` (GNU/Clang) or `/UNDEBUG` (MSVC) to executable test targets, so `assert` remains active in Release builds.

This is a useful assertion-preservation mechanism, but it does not make assert-based test setup safe/complete by itself.

## 4. CI execution qualification

Previously recorded successful native Brain workflow evidence at SHA `fa6c7152c27b7a93f34f1dbfdfd0b371b58030ef` covers configure/build only, not CTest. It is not the frozen donor HEAD and is not behavioral verification of all 70 registered tests. No CTest run is available from the current GitHub connector.

The PR #203 documentation-only commits do not change CMake or test source.

## 5. Five review lenses

1. **Build:** candidate/donor target registration and source reachability compared.
2. **Test:** 70 CTest entries reconciled; two long-run tests intentionally workflow-driven, DLT-002 persistence has train/verify fixture.
3. **Integrity:** assertions remain enabled for Release test executables.
4. **Capability:** test target count indicates coverage mechanisms, not demonstrated cognition or runtime capability.
5. **Hostile review:** registration not equated with execution; older build evidence SHA and scope explicitly qualified.

## 6. Open obligations / disposition

| Item | State |
|---|---|
| Candidate/donor target sets | Compared |
| 71 donor target source paths | Confirmed present |
| 70 CTest registrations | Reconciled |
| Long-run workflow-driven targets | Source comments/registration reconciled |
| Release assertions | Enabled by CMake options |
| Native configure/build at frozen donor | Not executed here |
| CTest/behavioral run | Not executed |
| Full test semantic adequacy | Open |
| DF-02 | OPEN |

Test-build registration remains **OPEN / NO AUTHORITY DECISION** for semantic adequacy and execution. No DF-02 closure, Foundation clearance or Stage A authorization.
