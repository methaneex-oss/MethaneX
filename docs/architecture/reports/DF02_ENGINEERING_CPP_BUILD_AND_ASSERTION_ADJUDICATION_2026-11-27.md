# DF-02 Engineering C++ Source/Test Registration and Release-Assertion Adjudication — 2026-11-27

**Scope:** exact candidate/donor `engineering/cpp/CMakeLists.txt` source and test target registration.  
**Candidate:** PR #192 frozen SHA `caf87986dfea7aca75728818651c8687e9f5faf0`. **Donor:** PR #97 `c1da222e6c94aeb3f2ad000392c21fe4fc81ab25`.  
**Disposition:** donor registers the durable task ledger and a second suite. A test assertion configuration gap remains.

## 1. Exact refs

- Candidate CMake: `7e2621c8678ad784d6e8c9e777b22b7c5310b855`.
- Donor CMake: `44ad82199248b9a6a53d996d046e2e3eb8265f1c`.
- Engineering CMake lineage: 35 blobs across 185 tip sightings in the frozen artifact.

## 2. Build/test delta

Candidate:
- `jarvis_engineering` static library has five source files;
- one agent/console executable and CTest registration.

Donor:
- adds `src/task_ledger.cpp` to the library;
- adds task-ledger suite and CTest entry;
- finds/links `Threads::Threads` for task-ledger test;
- keeps C++20 and warning options `-Wall -Wextra -Wpedantic` / `/W4 /permissive-`;
- has no `-UNDEBUG` or `/UNDEBUG` override.

## 3. Test assertion configuration risk

Both donor engineering suites use `assert`-based checks. Unlike the core C++ test CMake, engineering CMake does not explicitly re-enable assertions for Release. With `NDEBUG` in a Release configuration, assertions are compiled out; the registered tests may execute setup/actions but lose their behavioral checks. This is a source-confirmed configuration difference, not a test-run result.

## 4. Verification boundary

No native engineering configure/build/CTest was executed here. Existing core build evidence does not establish that the standalone engineering project was built or its Release assertions active. PR #203 changes documentation only.

## 5. Open obligations / disposition

| Item | State |
|---|---|
| Candidate/donor source/test target sets | Compared |
| Task ledger source/test registration | Confirmed donor |
| Threads dependency | Confirmed donor test wiring |
| Release assertion preservation | Gap |
| Native test execution | Not performed |
| Full semantics/consumer/authority | Open |
| DF-02 | OPEN |

Engineering CMake remains **OPEN / NO AUTHORITY DECISION**. No DF-02 closure, Foundation clearance or Stage A authorization.
