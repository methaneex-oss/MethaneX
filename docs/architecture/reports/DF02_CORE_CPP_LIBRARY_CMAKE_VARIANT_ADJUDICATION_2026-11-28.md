# DF-02 Core C++ Library-CMake Variant Adjudication — 2026-11-28

**Scope:** exact 22-blob historical cohort for `core/cpp/CMakeLists.txt`; source-list variation, target wiring, candidate/donor ownership and C++ standard.  
**Candidate:** frozen PR #192 SHA `caf87986dfea7aca75728818651c8687e9f5faf0`.  
**Donor:** PR #97 HEAD `c1da222e6c94aeb3f2ad000392c21fe4fc81ab25`.  
**Evidence:** discovery artifact #14956148301, re-downloaded and SHA-256 reverified `9902957475c76f4840d1d280c7d4f50537941e9445810afb805132374a328f38`.  
**Disposition:** source-list and build-owner differences confirmed; exact historical versions enumerated; no native build performed.

## 1. Candidate/donor source ownership

Frozen candidate CMake SHA: `c51816888e1bddb7bc00c59e72529524e27a0717` — 57 production .cpp entries.  
Frozen donor CMake SHA: `bc264ce7b4ae489404ca03ea6d9676d0330a6a56` — 64 production .cpp entries.

Donor-only source entries (seven):
- `src/brain_restored_api.cpp`
- `src/brain_action_execution.cpp`
- `src/brain_prediction_context.cpp`
- `src/brain_affective_planning.cpp`
- `src/affective_state.cpp`
- `src/affective_learning.cpp`
- `src/developmental_learning.cpp`

Candidate-only production entries: none. The donor CMake compiles an explicit Brain API/translation-unit split, affective models and developmental learning. This is a compiled-owner distinction; it does not establish that the donor's whole source set is semantically correct or authorized.

Both graphs specify C++20 and warning options. The historical cohort also uses C++20 and common warnings in the source extraction. The donor enables example targets through the examples build option; the frozen candidate does not enable the same example configuration. Build-option differences must be checked against CI/workflow contexts, not interpreted as production behavior.

## 2. Exact 22-blob source-count inventory

Source counts are extracted from CMake path tokens; SHA values are exact.

| Blob SHA | Tip count | Source entries | Restored Brain API TU | Donor-style affective/developmental split |
|---|---:|---:|---|
| `1b43268fa29315895712efc7123762c2c194cbfc` | 1 | 52 | No |
| `1c2b4d40caa549eb9fd5549bad158e266121e3b8` | 1 | 60 | No |
| `29489ac84a3b774482535033429dbc7599a17745` | 2 | 53 | No |
| `33197f92141a241ff0546af1bf81fbf177a1f3ab` | 3 | 64 | Yes |
| `39ea77ecc7360e0dbe59fb8731fdc0a612eb2f48` | 2 | 31 | No |
| `3ad2a7a53664563e2c9750b5a0d8b167efb1685c` | 1 | 56 | No |
| `41eab1319c3025232806930d037d7bdc484c53b3` | 3 | 25 | No |
| `4606fa6579a630b254cd722ef52db6a775336ae9` | 1 | 37 | No |
| `5df67a1b2eb627e141b8408f8349635550d5a0ca` | 11 | 55 | No |
| `6b1d223f2f1114825bfea2ab87d9808e37c33a84` | 2 | 56 | No |
| `6f9a2e5ca615f15a08319d083250834f1e9a7540` | 1 | 34 | No |
| `a446e7ca56f89e9067bd856ae89a325338c0e53e` | 1 | 32 | No |
| `bc264ce7b4ae489404ca03ea6d9676d0330a6a56` | 72 | 64 | Yes — donor |
| `c3c61cfcc9059461421fcafbbbb474d827d61689` | 1 | 35 | No |
| `c51816888e1bddb7bc00c59e72529524e27a0717` | 101 | 57 | Candidate |
| `c7ff4e217311593081cc1a6d78855224a4341dc8` | 2 | 30 | No |
| `ca8b2ffea6da429b232d061a114564440cecd46b` | 1 | 26 | No |
| `d6100df8adc23fc63f2e7205739d7c99d56746bd` | 1 | 49 | No |
| `e0167a19df1dddc39fe749e59a2cbe5115fa7b5b` | 1 | 33 | No |
| `e0722e4fd2723e92766d95edc67a133a94e8fae0` | 1 | 27 | No |
| `f794a688c029dff6cee119c408f326d68e318e5e` | 2 | 29 | No |
| `f82331bb8e078577fc47cf282e2c7764b6d3ac0b` | 1 | 64 | Yes |

Source entries span 25–64 across variants; 22 blobs are distinct content versions. The three historical 64-source variants with the donor-style Brain/affective/developmental split are not automatically equivalent: exact source-list and option diff/authority review remains open. One historical 64-entry blob (`f82331...`) is not frozen donor and needs exact source-level comparison before lineage classification.

## 3. Build-graph implications

- The candidate's 57-source set includes `brain.cpp` and `brain_novelty.cpp`, but excludes `brain_restored_api.cpp`, `brain_action_execution.cpp`, `brain_prediction_context.cpp`, `brain_affective_planning.cpp`, `affective_state.cpp`, `affective_learning.cpp`, and `developmental_learning.cpp`.
- The donor explicitly registers all seven, and moves some Brain methods into separate translation units. The matching header/declaration/consumer evidence is separately documented in the Brain API and developmental cohorts.
- CMake source-list presence establishes compilation intent only. No compile, link, CTest, ABI, platform or example build was run on either frozen graph.
- Historical branches can have fewer or more entries and different feature flags. Their tip counts do not determine authority.

## 4. Five review lenses

1. **Source ownership:** candidate/donor source split reconciled by exact path; donor-only seven are real source-graph deltas.
2. **Build:** C++20 and common warning flags are present; examples and other options differ in historical configurations. No native execution.
3. **Semantic:** a source being registered is not proof of correct behavior, correct API ownership or integration; the restored Brain API has overlapping definitions in candidate source and is unregistered in candidate CMake.
4. **Trust/provenance:** 22 exact blobs and tip ownership counts are recorded. Branch labels do not prove semantic successor or retention authority.
5. **Hostile review:** no donor preference or adoption inferred from the source count. The three historical donor-shaped 64-source graphs need exact source/options diff, and all consumers/build workflows remain open.

## 5. Disposition

| Obligation | State |
|---|---|
| 22 exact CMake blobs/source-count inventory | Complete for this slice |
| Candidate/donor source-set delta | Confirmed |
| C++20/warnings | Source-level presence |
| Historical semantic source/options diffs | Partial |
| Consumers, API compatibility, workflows | Partial/open |
| Native build/link/CTest | Not run |
| Owner authority/provenance/retention | Open |
| DF-02 | OPEN |

**Disposition:** core library-CMake cohort is source-inventoried, not semantically/authority closed. No baseline, donor adoption, source retirement/deletion, runtime implementation or Stage A authorization.
