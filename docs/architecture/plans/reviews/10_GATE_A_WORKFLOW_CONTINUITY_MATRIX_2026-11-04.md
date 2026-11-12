# Gate A — Workflow Continuity Matrix

**Date:** 2026-11-04  
**Comparison:** Five current-main workflows against the candidate PR #156 integration tree  
**Status:** Static workflow disposition; no workflow execution or CI equivalence claim

| Current-main workflow | Candidate state/evidence | Capability preserved? | Required disposition |
|---|---|---|---|
| `.github/workflows/dlt-002-four-hour.yml` | Exact same blob `52d08751d29c1b7c7b60e07834ac1bfdc4eba626` | Yes, file identity only; runtime pass not established | Unchanged; retain |
| `.github/workflows/jbp-mem-001.yml` | Candidate blob `82cec28819357a26881584b4ceb951c258ea24ac`; main blob `9e1efd73a9a91a70c1d9ceda0d6b458f9bdd7f7f` | Partial; candidate lacks `source_ref` input and explicit tested-commit metadata | Adapt reproducibility controls if candidate selected |
| `.github/workflows/jarvis-learning-mechanisms.yml` | Absent in candidate. Main has 35 mechanism/test gates plus integrated changing-environment trial. All 35 target names occur in candidate CMake blob `0251936730f82a7a8c928fa31dfe1d7effc83d91` | Target-name registration only; build/pass equivalence not established | Preserve workflow capability or explicitly replace with equivalent trigger, test set, changing-environment trial, and artifacts |
| `.github/workflows/jbp-brain-int-001.yml` | Absent in candidate. Main runs five integrated suites plus persistence and DLT-002. Candidate JBP-001 overlaps persistence/DLT-002 but not the five integration suites | Partial, not equivalent | Preserve five integrated suites and matching run semantics through an explicit adaptation |
| `.github/workflows/jbp-learning-002.yml` | Absent in candidate. Main runs three independent DLT-002 trials with configurable source ref and seed base. Candidate seed sweep uses same long-run executable with three fixed seeds but lacks source-ref and seed-base controls | Partial, not identical | Preserve independent trials and reproducibility controls; document any deliberate replacement |

## Per-workflow evidence requirements

For each workflow, the final implementation decision must compare:
- event triggers and branch/ref filters;
- source-ref and tested-commit identity;
- runner/environment and dependency setup;
- configure/build commands and target set;
- test arguments, trial count, seeds and changing-environment behavior;
- timeout/retry/failure semantics;
- artifact/log publication and retention;
- permissions and secrets exposure;
- workflow dependencies and required status checks.

## Precision limits

- Presence of 35 target names in candidate CMake is static registration evidence only.
- Same workflow blob is file-identity evidence only, not proof it ran or passed on the candidate.
- A candidate workflow with overlapping commands is not equivalent unless trigger, ref, seed, suite, trial, failure and artifact semantics are also preserved.
- No workflow was edited or executed under the current authorization.

**Disposition:** One exact file match, one reproducibility-control adaptation, and three absent workflows with only partial or target-level overlap. Workflow continuity is not yet closed. Gate A remains NOT CLEARED.


## 5. Workflow-by-workflow preservation/adaptation specification — 2026-11-04

The five current-main workflow files were fetched from main and compared with the candidate code-bearing parent 15d49e5fdeb5723c475922ab78fb92f97c4b3b84. This section is the required future-preservation specification. It does not claim that the candidate has executed these workflows.

### 5.1 DLT-002 four-hour/overnight trial

- Current-main blob: 52d08751d29c1b7c7b60e07834ac1bfdc4eba626.
- Candidate blob: same exact SHA; no file adaptation required.
- Trigger: manual workflow_dispatch only; no automatic push or PR multi-hour run.
- Input: deterministic numeric seed, default 20261026.
- Runner/timeout: ubuntu-latest; 360-minute job timeout.
- Build targets: jarvis_dlt_002_persistence and jarvis_dlt_002_long_run.
- Gates: overwrite guard; separate-process train/verify persistence CTest; six-phase 60-second smoke test.
- Trial: 19,800 seconds (330 minutes), 60-second checkpoints, partial observation, 20% noisy outcomes, two context reversals, unseen-context transfer.
- Evidence: exact GITHUB_SHA, run ID and attempt in metadata; console/build/smoke/persistence logs, checkpoints, episode records and brain journal uploaded as a run artifact.
- Preservation requirement: retain single uninterrupted execution semantics, seed validation, exact commit metadata, overwrite protection, cross-process persistence gate, all six phases, 330-minute duration and complete artifact set. Interrupted runs remain incomplete; do not claim safe resume.

### 5.2 JBP MEM-001 memory persistence trial

- Current-main blob: 9e1efd73a9a91a70c1d9ceda0d6b458f9bdd7f7f.
- Candidate blob: 82cec28819357a26881584b4ceb951c258ea24ac; not equivalent.
- Trigger: manual workflow_dispatch only.
- Input: source_ref, default feat/jarvis-affective-state.
- Runner/timeout: ubuntu-latest; 60-minute job timeout.
- Reproducibility: checkout the selected source_ref; record both source_ref and git rev-parse HEAD as tested_commit. The candidate copy lacks these explicit source_ref/tested_commit controls.
- Trial: 1,800-second memory/restart soak with 300-second checkpoints; persistence verification occurs in separate processes.
- Build/tests: native C++20 configure; memory and persistence targets; initial acceptance gate; repeated CTest/soak cycle.
- Evidence: configure/build/test/soak logs, metadata, memory/journal evidence uploaded even on failure.
- Preservation requirement: port the current-main source_ref and tested_commit controls, separate-process verification, 30-minute soak, checkpoint cadence, exact target/suite set, timeout and artifacts. Do not use workflow_dispatch's selected branch SHA as a substitute for the separately tested source_ref.

### 5.3 JARVIS learning-mechanisms probe

- Current-main blob: 0eac13b1e6a43ea7fa06aaf9e0134f5b6ae27710.
- Candidate: workflow absent.
- Trigger: workflow_dispatch plus pull_request targeting main. The PR path filter currently watches only .github/workflows/jarvis-learning-mechanisms.yml, not core/cpp source changes. Preserve this exact trigger unless a separately approved change expands the code paths.
- Inputs: source_ref (default feat/jarvis-affective-state), duration_minutes in {10,15,20,30}, numeric seed (default 20261026).
- Runner/timeout: ubuntu-latest; 60-minute timeout.
- Reproducibility: checkout source_ref; record source_ref, tested_commit, duration and seed.
- Build: configure native C++20 brain and build all registered mechanism suites.
- Explicit gates: 35 individually named CTest suites covering memory/consolidation, knowledge/evidence, novelty/attention, learning-loop adaptation, association/causality, prediction error/feedback, evolution proposal/coordination/runner/trials/scheduling/monitoring/canary/orchestration/adoption, developmental strategy, affective appraisal/state/goal outcomes/decisions/evidence, cognitive runtime, goal outcome, integrated developmental Brain, experience memory, action consequences, training, environment transitions, world transitions/integration and cross-process persistence.
- Integrated trial: 10–30 minutes in changing environments, six phases, 30-second checkpoints, resolved-prediction evidence and transfer evidence.
- Evidence: per-gate logs, integrated trial console/summary, run metadata and artifact upload.
- Preservation requirement: restore the complete 35-gate list and integrated trial; do not treat CMake target-name presence as test success. Retain source_ref/tested_commit, seed, duration validation, timeout and artifacts.

The 35 exact target names in the current workflow are:
jarvis_memory_architecture_suite; jarvis_knowledge_memory_phase3_suite; jarvis_attention_learning_brain_suite; jarvis_learning_loop_architecture_suite; jarvis_association_causality_phase5_suite; jarvis_learning_adaptation_phase8_suite; jarvis_prediction_feedback_phase10_suite; jarvis_evolution_learning_suite; jarvis_evolution_experiment_suite; jarvis_evolution_experiment_coordinator_suite; jarvis_evolution_experiment_runner_suite; jarvis_evolution_trials_suite; jarvis_evolution_scheduler_suite; jarvis_evolution_monitor_suite; jarvis_evolution_canary_controller_suite; jarvis_evolution_opportunity_orchestration_suite; jarvis_evolution_brain_integration_suite; jarvis_evolution_adoption_journal_suite; jarvis_developmental_learning_suite; jarvis_affective_learning_suite; jarvis_affective_state_model_suite; jarvis_affective_goal_outcome_suite; jarvis_affective_brain_decision_suite; jarvis_cognitive_runtime_goal_feedback_suite; jarvis_goal_outcome_model_suite; jarvis_affective_evidence_suite; jarvis_affective_decision_learning_suite; jarvis_developmental_brain_integration_suite; jarvis_experience_memory_test; jarvis_brain_action_consequence_integration_suite; jarvis_developmental_training_environment_suite; jarvis_developmental_environment_suite; jarvis_developmental_world_suite; jarvis_developmental_world_integration_suite; jarvis_dlt_002_persistence_verify.

### 5.4 JBP BRAIN-INT-001 integrated feedback and persistence

- Current-main blob: 31523dfa6bb5160397ebefd1f25325484461e271.
- Candidate: workflow absent.
- Trigger: manual workflow_dispatch only.
- Inputs: source_ref (default feat/jarvis-affective-state), smoke_minutes in {3,5,8} (default 5).
- Runner/timeout: ubuntu-latest; 45-minute timeout.
- Reproducibility: checkout source_ref; record source_ref, tested_commit, smoke duration and run ID.
- Build targets: brain_action_consequence_integration_suite, developmental_brain_integration_suite, prediction_feedback_phase10_suite, developmental_training_environment_suite, developmental_learning_suite, dlt_002_long_run and dlt_002_persistence.
- Gates: five integrated CTest suites; separate-process learned-state persistence; short integrated adaptation/reversal challenge.
- Evidence: configure/build/integration/persistence/trial logs and summary artifact.
- Preservation requirement: keep the five integrated suites, persistence boundary, 3/5/8-minute smoke, exact source metadata and artifacts. This workflow is not replaced by the 35 individual learning-mechanism gates.

### 5.5 JBP LEARNING-002 adversarial multi-seed stress

- Current-main blob: 4e88b4150eed6e5df3e81dd28a35216a299039e9.
- Candidate: workflow absent.
- Trigger: manual workflow_dispatch only.
- Inputs: source_ref (default feat/jarvis-affective-state), duration_minutes in {5,10,12,15} (default 10), numeric seed_base (default 20261027).
- Runner/timeout: ubuntu-latest; 45-minute timeout.
- Replication: matrix seed offsets [0,1,2], fail-fast false; each run uses seed_base, seed_base+1 or seed_base+2 and writes an independent result directory/artifact.
- Build target: jarvis_dlt_002_long_run.
- Trial: changing-world partial-observation/noisy-outcome/context-reversal/transfer challenge for the selected duration per seed.
- Reproducibility: checkout source_ref; record tested_commit, duration, seed and seed offset for every independent run.
- Preservation requirement: retain all three independent seeds, non-fail-fast matrix behavior, per-seed metadata/artifacts and exact source commit. A single executable loop with three seeds is not equivalent to three independently scheduled jobs.

### 5.6 Candidate continuity disposition

| Workflow | Candidate state | Required future treatment |
|---|---|---|
| DLT-002 four-hour | Exact blob match | Preserve unchanged |
| JBP MEM-001 | Present but lacks explicit source_ref/tested_commit controls | Adapt to current-main reproducibility contract |
| JARVIS learning mechanisms | Absent | Restore full 35-gate + integrated trial workflow |
| JBP BRAIN-INT-001 | Absent | Restore five integrated suites + persistence + smoke trial |
| JBP LEARNING-002 | Absent | Restore three independent seeded matrix runs |

Candidate CMake target-name presence is not build/pass evidence. The PR #176 donor-correction CI is a bounded native/sanitizer/ThreadSanitizer validation of the corrected donor tree; it does not execute these five workflow contracts.

**Disposition:** the workflow-by-workflow preservation/adaptation specification is complete. Workflow implementation/adaptation and execution remain later integration/validation work and must not be represented as already done.
