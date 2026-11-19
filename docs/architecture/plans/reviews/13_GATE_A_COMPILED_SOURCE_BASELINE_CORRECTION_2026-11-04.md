# Gate A — Compiled-Source Baseline Correction

**Date:** 2026-11-04  
**Planning PR:** #175  
**Candidate:** PR #156 code-bearing parent `15d49e5fdeb5723c475922ab78fb92f97c4b3b84`  
**Current-main source comparison:** current default-branch source snapshot inspected on 2026-11-04  
**Governing specification:** PR #174 HEAD `0811a59e46bf934e32e794f90e4e7d18d4e2bd97`  
**Status:** Static correction to the Gate A comparison method; no runtime changes or tests

## 1. Why this correction is necessary

The earlier semantic addendum compared candidate `core/cpp/src/brain_restored_api.cpp` against the same-named file on current main and treated both as active implementation sources.

That assumption was wrong.

The build configurations show:

- Candidate `core/cpp/CMakeLists.txt` blob `bc264ce7b4ae489404ca03ea6d9676d0330a6a56` includes both `src/brain.cpp` and `src/brain_restored_api.cpp` in the `jarvis_core` library.
- Current-main `core/cpp/CMakeLists.txt` blob `c51816888e1bddb7bc00c59e72529524e27a0717` includes `src/brain.cpp` but does **not** include `src/brain_restored_api.cpp`.
- The current-main file `core/cpp/src/brain_restored_api.cpp` exists (blob `618deb6976eed951eae02b7f0da741e6d730bb0c`) but is not listed as a source of `jarvis_core`.

Therefore, the same-named current-main file is not the compiled comparator for the candidate's active implementation. Its contents cannot be used as evidence of current-main runtime behavior unless another build target is shown to compile it. No such target was established in this inspection.

**Correction:** the 24-function semantic table in review artifact 06 must not be read as a verified comparison of the two compiled implementations. Its source-file observations remain historical evidence, but its active-baseline comparison needs to be reclassified against current-main `brain.cpp`.

## 2. Exact source evidence

| Item | Candidate | Current main |
|---|---|---|
| Build source list | `core/cpp/CMakeLists.txt`, blob `bc264ce7b4ae489404ca03ea6d9676d0330a6a56` | `core/cpp/CMakeLists.txt`, blob `c51816888e1bddb7bc00c59e72529524e27a0717` |
| Brain header | `core/cpp/include/jarvis/core/brain.hpp`, blob `ca718aa4603bbdd0abc7de26ed296bcf8c6562fe` | Same path, blob `8268ef84e0b361ead536724ba7761904b30ee58f` |
| Compiled Brain implementation | `core/cpp/src/brain.cpp`, blob `93a10a5021a5775a3a239037cbb0b58a1e0c67a9` | Same path, blob `e9f3758fcc9c0e89b7280ce376db9033d547682d` |
| Additional compiled Brain implementation | `core/cpp/src/brain_restored_api.cpp`, blob `00d69ab2eb3811d453a643ef18dc69741109cbc8` | Not included in the `jarvis_core` source list |

The candidate CMake source list also includes additional dedicated Brain/action/prediction/affective implementation files not present in the current-main list. This is a build-input difference, not proof by itself that every added subsystem is correct.

## 3. Corrected method inventory

A source-text inventory of the active Brain implementation files found:

- Candidate: 84 `Brain::` definition occurrences across `brain.cpp` and `brain_restored_api.cpp`, covering 78 method names (including overloads and private helpers).
- Current main: 49 occurrences across 47 method names in the compiled `brain.cpp`.
- All 47 method names found in current-main `brain.cpp` were also found in the candidate's two compiled Brain source files.
- The candidate source set contains 31 additional method names relative to current-main `brain.cpp`. This is a file-scoped inventory, not a complete library-wide linker map; some names may be supplied elsewhere or inline in current main.

Two especially important examples:

1. `assimilate_goal_outcome` is declared in the candidate Brain header and defined in the candidate compiled `brain_restored_api.cpp`. Current main does not declare it in its Brain header; a definition exists only in the uncompiled same-named source file.
2. `choose_with_affect` is likewise declared and compiled in the candidate, but is not declared in the current-main Brain header; its same-named definition exists only in the uncompiled current-main `brain_restored_api.cpp`.

These are candidate capabilities relative to the active current-main build, not common APIs whose bodies can be compared as if both versions were compiled.

The source inventory is intentionally bounded. It does not claim that every additional candidate method is absent from every other current-main translation unit, nor does it establish link compatibility without compilation.

## 4. Confirmed signature difference against the active build

`register_evolution_parameter(std::string, double)` is declared and defined as:

- Candidate: returns `bool`; rejects empty keys, non-finite initial values, and duplicate keys before journaling; returns whether registration is present after replay.
- Current main: returns `void`; rejects an empty key, appends the event, then registers the parameter.

This difference is confirmed in the active candidate header/source and active current-main header/source. Ordinary call statements that ignore the candidate's return value are source-level compatible in shape, but function-pointer/member-pointer and downstream ABI/build compatibility remain unverified.

## 5. Consequence for the earlier 24-function table

The 24 names in artifact 06 must be divided before any baseline conclusion:

- **22 names have definitions in both active source sets** and require comparison of candidate implementation against current-main `brain.cpp`, not against current-main's uncompiled `brain_restored_api.cpp`.
- **`assimilate_goal_outcome` and `choose_with_affect` are candidate additions relative to the active current-main header/build**, despite same-named definitions in the uncompiled current-main file.
- The old per-function dispositions are not accepted as completed compiled-source reconciliation until rechecked against the active source pair.
- The direct source inspection already confirms representative candidate differences: candidate goal transitions validate and journal/replay before applying model changes, while current-main methods such as `abandon_goal` and `activate_goal` mutate the model before journaling. The full 22-method semantic classification still needs to be rewritten against the active sources rather than inferred from these examples.

## 6. Gate A impact and next bounded action

This correction does not select or reject PR #156.

It does change the evidence standard: compare the source files actually included by each build target. The candidate appears to contain a broader and more integrated Brain implementation surface than current main, but it also carries the two confirmed candidate defects, unresolved failure-ordering risks, workflow gaps, and unverified build/API compatibility.

**Next action:** replace the old 24-function comparison with a 22-method active-source comparison; classify the two candidate additions separately; complete the bounded caller inventory for candidate-only APIs and the `register_evolution_parameter` return change.

**Gate A remains NOT CLEARED. PR #156 remains a candidate only. No implementation baseline is selected.**

No runtime code, tests, builds, workflows, dependencies, or APIs were changed or executed in this review.
