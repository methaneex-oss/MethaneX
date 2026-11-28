# DF-02 Core C++ Source Build-Registration Adjudication — 2026-11-27

**Scope:** exact candidate/donor `core/cpp/CMakeLists.txt` source registration, compiler standard/options, test and example wiring.  
**Candidate:** PR #192 frozen SHA `caf87986dfea7aca75728818651c8687e9f5faf0`. **Donor:** PR #97 `c1da222e6c94aeb3f2ad000392c21fe4fc81ab25`.  
**Disposition:** donor registers seven new Brain/affective/developmental translation units with no candidate-only source removal. Build configuration source-inspected; no native execution at frozen donor SHA.

## 1. Exact CMake refs

- Candidate `core/cpp/CMakeLists.txt`: `c51816888e1bddb7bc00c59e72529524e27a0717`.
- Donor: `bc264ce7b4ae489404ca03ea6d9676d0330a6a56`.
- Discovery has 22 exact CMake blobs across 212 branch-tip sightings.

## 2. Source registration comparison

| | Candidate | Donor |
|---|---:|---:|
| `jarvis_core` static-library source entries | 57 | 64 |
| Removed candidate source entries | 0 | — |
| Added donor source entries | — | 7 |
| Duplicate source entries | 0 | 0 |

Donor-only source registrations:
- `brain_restored_api.cpp`
- `brain_action_execution.cpp`
- `brain_prediction_context.cpp`
- `brain_affective_planning.cpp`
- `affective_state.cpp`
- `affective_learning.cpp`
- `developmental_learning.cpp`

All seven files are present at the frozen donor tree. This confirms source reachability, not semantic ownership/duplicate-API closure. The restored Brain API report separately notes candidate test-CMake omission and donor integration.

## 3. Build configuration

Both versions require CMake 3.24, C++20, standard required, extensions disabled; static `jarvis_core`; public include directory; compile features C++20; warnings `-Wall -Wextra -Wpedantic` (GNU/Clang) and `/W4 /permissive-` (MSVC). Neither enables `-Werror`.

Donor wiring:
- CTest and `tests/` subdirectory under `BUILD_TESTING`;
- affective planning CMake test fragment included;
- `JARVIS_BUILD_EXAMPLES` option defaults **ON**, and adds `examples/` subdirectory when enabled.

The examples default means a normal core build includes examples unless CI/users disable it; example build dependencies and CI matrix coverage should be separately checked. No source/test code changed by PR #203.

## 4. Verification boundary

Previously recorded native Brain build evidence is successful configure/build at older SHA `fa6c7152c27b7a93f34f1dbfdfd0b371b58030ef`; it does not verify exact frozen donor HEAD or CTest. The connector cannot dispatch a workflow or execute native build here. No compile/test claim is made.

## 5. Five review lenses

1. **Build:** seven donor translation units registered; no duplicate source entries.
2. **Test:** CTest/test subdirectory wiring confirmed; CTest not executed.
3. **Portability:** C++20 and compiler warning flags confirmed; examples default-on and no Werror.
4. **Capability:** source reachability is not evidence that a feature works.
5. **Hostile review:** no source ownership closure or build pass claimed from CMake alone.

## 6. Open obligations / disposition

| Item | State |
|---|---|
| Candidate/donor source set | Compared |
| Seven donor additions present | Confirmed |
| Duplicate/missing source entry | None found |
| Compiler standard/options | Source inspected |
| Example build default | ON |
| Native build at frozen donor SHA | Not performed |
| CTest/behavioral verification | Not performed |
| Full source ownership/consumer/authority | Open |
| DF-02 | OPEN |

Core source build registration remains **OPEN / NO AUTHORITY DECISION**. No DF-02 closure, Foundation clearance or Stage A authorization.
