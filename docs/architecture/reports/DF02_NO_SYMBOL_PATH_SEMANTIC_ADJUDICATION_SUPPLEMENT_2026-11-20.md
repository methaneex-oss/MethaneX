# DF-02 — No-symbol donor-path semantic adjudication supplement

**Date:** 2026-11-20  
**Repository:** `methaneex-oss/MethaneX`  
**Donor:** PR #97, `c1da222e6c94aeb3f2ad000392c21fe4fc81ab25`  
**Candidate source baseline inspected:** PR #192 base `61311fe5b44c81c4409c8ba8dc581a83bdd5dd2c`  
**Candidate documentation branch snapshot:** `cbc51e2b10f1fc976257653adf773735a2b27d49`  
**Current PR #192 branch after matrix refresh:** `e441e56467fa9d3fa56d4f354cf9ec119053db2b`

This supplement records exact source/build/test/workflow comparisons for the 41 donor paths that produced no remaining lexical symbol-consumer candidates in the refined all-ref scan. It is a semantic review of this bounded subset, not closure of all 159 donor paths or all 1,134 exact consumer versions.

## 1. Refined scan provenance and integrity

The refined scanner ran as workflow [#44799437811](https://github.com/methaneex-oss/MethaneX/actions/runs/44799437811) at scanner revision `8179bafcc5cb681a8abc73a0bf9819bbdd6a0b9e`. Artifact `14659828741` has SHA-256 `3a7d90b475564097a2ccf1de3f4492659b4417a7d46d3e193d9c95ff7b78ab22`; the downloaded ZIP was independently hashed and matched.

The scan covered 254 remote branch refs / 213 unique tips, 159 donor paths, and 1,397 unique text blobs. It extracted 724 donor API-like identifiers and produced 40,032 lexical candidate rows, 1,208 exact consumer-blob contents (17,489,565 UTF-8 bytes), and 1,134 exact consumer-blob/path/category versions: 649 source, 388 test, 58 build, 38 workflow, and 1 other. 118 donor paths had at least one lexical candidate; 41 did not.

The scanner candidate input was `32722f104f76817983b0156cca821949e406b8c1`. The subsequent PR #192 changes through `cbc51e2b10f1fc976257653adf773735a2b27d49` were documentation/workflow-audit changes only; no Brain C++, engineering C++, CMake, test-source, or Brain CI workflow blobs changed. The exact 159-path matrix was refreshed to the `cbc51e2b10f1fc976257653adf773735a2b27d49` tree and independently compared against donor tree `c1da222e6c94aeb3f2ad000392c21fe4fc81ab25`: 1 identical, 95 divergent, 63 absent. The matrix refresh is committed as `e441e56467fa9d3fa56d4f354cf9ec119053db2b`.

## 2. Eight workflow entrypoints

| Donor path | Candidate evidence | Disposition |
|---|---|---|
| `.github/workflows/brain-ci.yml` | Same-path divergent workflow retains Release configure/build/CTest and ASan/UBSan configure/build/CTest. Push branch filter is narrowed to `main`; PR trigger remains path-based. Candidate also has `brain-tests.yml` and `brain-tsan.yml`. | Core CI function retained across current workflows; historical branch-trigger scope changed. Not byte-identical. |
| `.github/workflows/dlt-001-long-run.yml` | Absent at candidate path. Current `jarvis-learning-mechanisms.yml` and `jbp-learning-002.yml` provide shorter multi-phase learning probes, not the donor's two-hour DLT-001 protocol. | No exact successor established; do not call retired or equivalent. |
| `.github/workflows/dlt-002-four-hour.yml` | Candidate blob is byte-identical to donor blob `52d08751d29c1b7c7b60e07834ac1bfdc4eba626`. | Exact retained artifact. |
| `.github/workflows/dlt-002-overnight-validation.yml` | Absent. The same-path DLT-002 four-hour workflow remains and exercises persistence, six phases, and a 330-minute run, but is not the same full-suite repeated-soak workflow. | Related successor evidence exists; full repeated-soak contract not proven equivalent. |
| `.github/workflows/jarvis-brain-probe-001.yml` | Absent. `jbp-brain-int-001.yml` performs short integration/persistence gates and a six-phase run; `jarvis-learning-mechanisms.yml` adds explicit mechanism gates. | Related probes exist; not an exact replacement for the donor probe's specific run protocol. |
| `.github/workflows/jarvis-core.yml` | Absent. Current `brain-ci.yml` and `brain-tests.yml` cover build/test; `brain-tsan.yml` adds TSAN. | Core build/test responsibility has successor workflows; original trigger/branch semantics differ. |
| `.github/workflows/jarvis-learning-seed-sweep.yml` | Absent. `jbp-learning-002.yml` runs three independent seeds through the six-phase changing-world challenge. | Strong related successor, but protocol/duration and evidence outputs differ; not declared identical. |
| `.github/workflows/jbp-mem-001.yml` | Same-path divergent candidate retains the 30-minute memory and fresh-process persistence checks and adds a required selectable `source_ref`, records the tested commit, and checks the same memory suites. | Semantic successor with improved source-revision provenance; exact content differs. |

## 3. Four build/example configuration paths

- `core/cpp/examples/CMakeLists.txt`: absent. Candidate `core/cpp/CMakeLists.txt` has no `JARVIS_BUILD_EXAMPLES` option or `add_subdirectory(examples)`; no registered `jarvis_developmental_world` executable is established.
- `core/cpp/examples/README.md`: absent. The donor README documents the runnable controlled world, hidden route quality, consequence feedback, reversal episodes, journal reuse, and expected learned strategy changes. No candidate README or runnable example entrypoint is established by the inspected CMake.
- `core/cpp/tests/affective_planning.cmake`: absent. Candidate top-level CMake does not include this file; the donor's affective-planning test registration is not preserved at this path.
- `engineering/cpp/CMakeLists.txt`: divergent. Candidate omits `src/task_ledger.cpp` from the library and `tests/task_ledger_suite.cpp` from CTest, while the donor registers both and links the suite with Threads. This matches the separately inspected absent task-ledger implementation/header finding.

## 4. Four production-source paths

- `core/cpp/src/action_execution.cpp`: divergent candidate implementation does not preserve the donor's expected-consequence initialization and independent post-execution consequence observation/error calculation. This breaks part of the donor's action-outcome feedback contract.
- `core/cpp/src/affective_learning.cpp`: absent candidate translation unit. Donor file is a header-only compilation boundary with no independent learning implementation; absence of this .cpp alone is not a missing subsystem.
- `core/cpp/src/affective_state.cpp`: absent candidate translation unit. Donor contains a stateful appraisal/update model with bounded weights, temporal integration and persistent internal state. No candidate equivalent was established in the inspected source/build graph.
- `core/cpp/src/evolution_adoption.cpp`: divergent candidate helper adopts on execution plus safety-gate approval without establishing durable matching evaluation history, replay protection or controller-mediated lifecycle authorization. Donor helper fails closed and requires the controller path. Candidate helper is not a semantic successor.

## 5. Twenty-two test artifacts

The exact donor and candidate files were fetched and compared. Donor `core/cpp/tests/CMakeLists.txt` declares 71 executable targets / 70 CTest entries; candidate declares 45 / 45. Within this 22-file subset, 11 same-path suites remain registered in the candidate; nine donor-registered suites are absent from the candidate registration; `developmental_learning_tests.cpp` and `representation_suite.cpp` are not donor CMake targets in the inspected donor file and therefore are not counted as donor CTest coverage.

| Test path | Exact comparison and disposition |
|---|---|
| `action_authorization_suite.cpp` | Present and registered. Nine assertions retained; same permission-denial, allowed-action, risk-limit and execution-authorization checks. |
| `action_model_architecture_suite.cpp` | Present and registered. Eleven assertions retained; aggregate fields changed with the candidate API. Core action disposition, permission, reversibility and finite-confidence checks remain. |
| `affective_decision_suite.cpp` | Absent and no candidate target. No affective decision test successor established. |
| `affective_learning_suite.cpp` | Absent and no candidate target. No affective-learning calibration/update suite successor established. |
| `affective_state_model_suite.cpp` | Absent and no candidate target. No state-update/decay/restore suite successor established. |
| `affective_state_suite.cpp` | Absent and no candidate target. No equivalent affective-state suite established. |
| `attention_architecture_suite.cpp` | Present and registered; 15 donor assertions reduced to 12. Candidate removes the internal-activation scoring/reinforcement checks. Partial successor with a specific coverage loss. |
| `brain_10_suite.cpp` | Present and registered; 32 assertions reduced to 29. Candidate removes the donor's unique journal-path setup and related persistence isolation assertions. Partial successor. |
| `cognitive_workspace_runtime_suite.cpp` | Present and registered; 8 assertions reduced to 6. Candidate removes representation-node and attention-key assertions while retaining runtime submission/result/workspace cycle checks. Partial successor. |
| `decision_planning_architecture_suite.cpp` | Present and registered; 20 assertions become 21. Candidate expands and retains ranking, policy weighting, finite-score and deterministic tie-break checks. Successor with expanded coverage in the inspected areas. |
| `developmental_environment_suite.cpp` | Absent and no candidate target. No equivalent hidden-state transition/consequence environment suite established. |
| `developmental_learning_suite.cpp` | Absent and no candidate target. Candidate has adjacent association/strategy mechanisms, but the inspected candidate does not establish the donor suite's developmental-learning contract. |
| `developmental_learning_tests.cpp` | Absent; donor file is not registered in the inspected donor CMake. Historical test artifact only; no CTest regression is inferred from its absence. |
| `developmental_world_suite.cpp` | Absent and no candidate target. No executable developmental-world suite successor established. |
| `evolution_adoption_journal_suite.cpp` | Present and registered; 53 donor assertions reduced to 8. Candidate drops pending/adopted restoration, compensation after journal failure, repeated stage/commit/rollback edge cases and recovery-state assertions. Material adoption-journal coverage regression. |
| `evolution_experiment_coordinator_suite.cpp` | Present and registered; six assertions retained. Candidate omits the donor's explicit final configuration boolean and uses the API default; basic four-trial baseline/candidate comparison remains. |
| `evolution_opportunity_orchestration_suite.cpp` | Present and registered; 21 assertions reduced to 17. Candidate removes explicit simulated-evaluator isolation override and explicit trial configuration; orchestration is still exercised but coverage/configuration is narrower. |
| `experience_memory_test.cpp` | Absent and no candidate target. The donor test verifies independent prediction records, per-sequence resolution and non-destructive resolution. No equivalent standalone test or Brain-loop integration is established. |
| `goal_outcome_model_suite.cpp` | Absent and no candidate target. No evidence-driven GoalOutcome model test successor established; manual GoalModel progress operations are not equivalent evidence. |
| `knowledge_memory_phase3_suite.cpp` | Present and registered; 14 assertions retained. Candidate renames `KnowledgeEvidence` to `Evidence` while retaining source reliability assimilation/scoring checks. Semantic test successor for this bounded contract. |
| `process_isolation_suite.cpp` | Present and registered; eight assertions retained. Resource limit changes from 256 MiB to 64 MiB, a tighter bound; timeout, output-limit, required-isolation and no-network checks remain. |
| `representation_suite.cpp` | Candidate file exists but is not registered in candidate CMake; donor file was also not a target in the inspected donor CMake. Assertions reduce from 22 to 10; deterministic node-ID stability and confidence/novelty/salience/world-step metadata checks are removed. This is a source-level test reduction, not a proven CTest target loss. |

## 6. Three historical design/documentation paths

- `docs/developmental-training-environment.md`
- `docs/superpowers/specs/2026-09-26-concept-context-prediction-design.md`
- `docs/superpowers/specs/2026-09-30-developmental-cognition.md`

All three are absent at the candidate paths and have no lexical symbol-consumer candidates. They are historical planning/design artifacts, not compiled runtime components. Their absence from the candidate tree is not evidence that the described mechanisms were retired, nor does it authorize deleting their Git history. Their current authority/successor status must be reconciled against the historical-preservation register and accepted planning baselines; no Project Director non-adoption decision is inferred here.

## 7. Bounded conclusion

This supplement closes the source-content inspection of the 41 no-symbol paths to the extent described above. It identifies exact retained workflow/test successors, partial successors with test-coverage reductions, and specific missing registrations or unproven successors. It does **not** close the remaining 118 donor paths with lexical candidates, the complete all-ref semantic consumer/dependency/duplicate-owner graph, historical authority for every artifact, or the Project Director-reserved retirement/non-adoption/source-baseline decisions.

DF-02 therefore remains **OPEN** under the Project Director's Option A standard. No donor adoption, source-baseline selection, runtime implementation, merge, rebase, retarget or Stage A authorization is inferred.
