# Gate A — Risk-Based Final-Tree Provenance Matrix

**Date:** 2026-11-04  
**Candidate context:** PR #175 / candidate PR #156 integration under review  
**Source inventory:** `02_GATE_A_REPOSITORY_BASELINE_RECONCILIATION_2026-11-03.md`, Appendix A and D  
**Status:** Initial path-level reconciliation; semantic/hunk attribution remains selective and incomplete

## 1. Coverage statement

The recorded net tree inventory contains 165 paths. This matrix enumerates each path and assigns it to the previously reconciled origin class:
- PR #97-only net path: 145
- Modified in both PR #97 and post-PR #97 segments: 14
- First introduced after PR #97: 6

These are path-set/origin-segment classifications, not proof of per-commit semantic correctness. The 145-path class means present in PR #97's net diff and not changed again in the 172-commit post-PR #97 segment. It does not mean unchanged across every earlier commit or semantically validated.

## 2. Risk-based review rule

Deeper commit/hunk attribution is required for:
- all 14 overlapping paths;
- all 6 paths first introduced after PR #97 where they carry candidate-specific functionality;
- public Brain API, persistence/journal/replay, goal/intent, learning/evolution, action evidence, and workflow/test orchestration paths where semantic changes could affect baseline selection;
- any path with unexplained replacement, deletion, conflict resolution, or divergent integration.

A path classified PR #97-only is not automatically low-risk. Its subsystem criticality still determines whether it requires deeper review. The inventory does not yet provide a complete per-path semantic review disposition; do not mark this matrix as full semantic closure.

## 3. Complete path inventory

| Path | Net status | Origin class | Risk/next action |
|---|---|---|---|
| `.github/workflows/brain-ci.yml` | modified | PR #97-only net path | Inspect semantic diff where high-risk; per-commit hunk attribution only where origin/overlap/effect is decision-relevant |
| `.github/workflows/dlt-001-long-run.yml` | added | PR #97-only net path | Inspect semantic diff where high-risk; per-commit hunk attribution only where origin/overlap/effect is decision-relevant |
| `.github/workflows/dlt-002-four-hour.yml` | added | PR #97-only net path | Inspect semantic diff where high-risk; per-commit hunk attribution only where origin/overlap/effect is decision-relevant |
| `.github/workflows/dlt-002-overnight-validation.yml` | added | PR #97-only net path | Inspect semantic diff where high-risk; per-commit hunk attribution only where origin/overlap/effect is decision-relevant |
| `.github/workflows/jarvis-brain-probe-001.yml` | added | PR #97-only net path | Inspect semantic diff where high-risk; per-commit hunk attribution only where origin/overlap/effect is decision-relevant |
| `.github/workflows/jarvis-core.yml` | added | PR #97-only net path | Inspect semantic diff where high-risk; per-commit hunk attribution only where origin/overlap/effect is decision-relevant |
| `.github/workflows/jarvis-learning-seed-sweep.yml` | added | PR #97-only net path | Inspect semantic diff where high-risk; per-commit hunk attribution only where origin/overlap/effect is decision-relevant |
| `.github/workflows/jbp-mem-001.yml` | added | PR #97-only net path | Inspect semantic diff where high-risk; per-commit hunk attribution only where origin/overlap/effect is decision-relevant |
| `core/cpp/CMakeLists.txt` | modified | PR #97-only net path | Inspect semantic diff where high-risk; per-commit hunk attribution only where origin/overlap/effect is decision-relevant |
| `core/cpp/examples/CMakeLists.txt` | added | PR #97-only net path | Inspect semantic diff where high-risk; per-commit hunk attribution only where origin/overlap/effect is decision-relevant |
| `core/cpp/examples/developmental_world.cpp` | added | PR #97-only net path | Inspect semantic diff where high-risk; per-commit hunk attribution only where origin/overlap/effect is decision-relevant |
| `core/cpp/examples/README.md` | added | PR #97-only net path | Inspect semantic diff where high-risk; per-commit hunk attribution only where origin/overlap/effect is decision-relevant |
| `core/cpp/include/jarvis/core/action_execution.hpp` | modified | PR #97-only net path | Inspect semantic diff where high-risk; per-commit hunk attribution only where origin/overlap/effect is decision-relevant |
| `core/cpp/include/jarvis/core/action_model.hpp` | modified | PR #97-only net path | Inspect semantic diff where high-risk; per-commit hunk attribution only where origin/overlap/effect is decision-relevant |
| `core/cpp/include/jarvis/core/adaptation.hpp` | modified | PR #97-only net path | Inspect semantic diff where high-risk; per-commit hunk attribution only where origin/overlap/effect is decision-relevant |
| `core/cpp/include/jarvis/core/affective_learning.hpp` | added | PR #97-only net path | Inspect semantic diff where high-risk; per-commit hunk attribution only where origin/overlap/effect is decision-relevant |
| `core/cpp/include/jarvis/core/affective_state.hpp` | added | PR #97-only net path | Inspect semantic diff where high-risk; per-commit hunk attribution only where origin/overlap/effect is decision-relevant |
| `core/cpp/include/jarvis/core/association_model.hpp` | modified | PR #97-only net path | Inspect semantic diff where high-risk; per-commit hunk attribution only where origin/overlap/effect is decision-relevant |
| `core/cpp/include/jarvis/core/attention.hpp` | modified | PR #97-only net path | Inspect semantic diff where high-risk; per-commit hunk attribution only where origin/overlap/effect is decision-relevant |
| `core/cpp/include/jarvis/core/brain.hpp` | modified | PR #97 + post-PR #97 overlap | Inspect semantic diff where high-risk; per-commit hunk attribution only where origin/overlap/effect is decision-relevant |
| `core/cpp/include/jarvis/core/causal_link_codec.hpp` | added | PR #97-only net path | Inspect semantic diff where high-risk; per-commit hunk attribution only where origin/overlap/effect is decision-relevant |
| `core/cpp/include/jarvis/core/causal_model.hpp` | modified | PR #97-only net path | Inspect semantic diff where high-risk; per-commit hunk attribution only where origin/overlap/effect is decision-relevant |
| `core/cpp/include/jarvis/core/cognition.hpp` | modified | PR #97-only net path | Inspect semantic diff where high-risk; per-commit hunk attribution only where origin/overlap/effect is decision-relevant |
| `core/cpp/include/jarvis/core/cognitive_cycle.hpp` | modified | PR #97-only net path | Inspect semantic diff where high-risk; per-commit hunk attribution only where origin/overlap/effect is decision-relevant |
| `core/cpp/include/jarvis/core/cognitive_goal_outcome.hpp` | added | PR #97-only net path | Inspect semantic diff where high-risk; per-commit hunk attribution only where origin/overlap/effect is decision-relevant |
| `core/cpp/include/jarvis/core/cognitive_runtime.hpp` | modified | PR #97-only net path | Inspect semantic diff where high-risk; per-commit hunk attribution only where origin/overlap/effect is decision-relevant |
| `core/cpp/include/jarvis/core/cognitive_workspace.hpp` | modified | PR #97-only net path | Inspect semantic diff where high-risk; per-commit hunk attribution only where origin/overlap/effect is decision-relevant |
| `core/cpp/include/jarvis/core/decision.hpp` | modified | PR #97-only net path | Inspect semantic diff where high-risk; per-commit hunk attribution only where origin/overlap/effect is decision-relevant |
| `core/cpp/include/jarvis/core/developmental_environment.hpp` | added | PR #97-only net path | Inspect semantic diff where high-risk; per-commit hunk attribution only where origin/overlap/effect is decision-relevant |
| `core/cpp/include/jarvis/core/developmental_learning.hpp` | added | PR #97 + post-PR #97 overlap | Inspect semantic diff where high-risk; per-commit hunk attribution only where origin/overlap/effect is decision-relevant |
| `core/cpp/include/jarvis/core/developmental_world.hpp` | added | PR #97-only net path | Inspect semantic diff where high-risk; per-commit hunk attribution only where origin/overlap/effect is decision-relevant |
| `core/cpp/include/jarvis/core/evolution_adoption_journal.hpp` | modified | PR #97-only net path | Inspect semantic diff where high-risk; per-commit hunk attribution only where origin/overlap/effect is decision-relevant |
| `core/cpp/include/jarvis/core/evolution_canary.hpp` | modified | PR #97-only net path | Inspect semantic diff where high-risk; per-commit hunk attribution only where origin/overlap/effect is decision-relevant |
| `core/cpp/include/jarvis/core/evolution_controller.hpp` | modified | PR #97-only net path | Inspect semantic diff where high-risk; per-commit hunk attribution only where origin/overlap/effect is decision-relevant |
| `core/cpp/include/jarvis/core/evolution_experiment_coordinator.hpp` | modified | PR #97-only net path | Inspect semantic diff where high-risk; per-commit hunk attribution only where origin/overlap/effect is decision-relevant |
| `core/cpp/include/jarvis/core/evolution_experiment_runner.hpp` | modified | PR #97-only net path | Inspect semantic diff where high-risk; per-commit hunk attribution only where origin/overlap/effect is decision-relevant |
| `core/cpp/include/jarvis/core/evolution_experiment.hpp` | modified | PR #97-only net path | Inspect semantic diff where high-risk; per-commit hunk attribution only where origin/overlap/effect is decision-relevant |
| `core/cpp/include/jarvis/core/evolution_orchestrator.hpp` | modified | PR #97-only net path | Inspect semantic diff where high-risk; per-commit hunk attribution only where origin/overlap/effect is decision-relevant |
| `core/cpp/include/jarvis/core/evolution.hpp` | modified | PR #97-only net path | Inspect semantic diff where high-risk; per-commit hunk attribution only where origin/overlap/effect is decision-relevant |
| `core/cpp/include/jarvis/core/experience_memory.hpp` | added | PR #97-only net path | Inspect semantic diff where high-risk; per-commit hunk attribution only where origin/overlap/effect is decision-relevant |
| `core/cpp/include/jarvis/core/goals.hpp` | modified | PR #97-only net path | Inspect semantic diff where high-risk; per-commit hunk attribution only where origin/overlap/effect is decision-relevant |
| `core/cpp/include/jarvis/core/intent.hpp` | modified | PR #97-only net path | Inspect semantic diff where high-risk; per-commit hunk attribution only where origin/overlap/effect is decision-relevant |
| `core/cpp/include/jarvis/core/knowledge.hpp` | modified | PR #97 + post-PR #97 overlap | Inspect semantic diff where high-risk; per-commit hunk attribution only where origin/overlap/effect is decision-relevant |
| `core/cpp/include/jarvis/core/memory.hpp` | modified | PR #97-only net path | Inspect semantic diff where high-risk; per-commit hunk attribution only where origin/overlap/effect is decision-relevant |
| `core/cpp/include/jarvis/core/planning.hpp` | modified | PR #97-only net path | Inspect semantic diff where high-risk; per-commit hunk attribution only where origin/overlap/effect is decision-relevant |
| `core/cpp/include/jarvis/core/reflection.hpp` | modified | PR #97-only net path | Inspect semantic diff where high-risk; per-commit hunk attribution only where origin/overlap/effect is decision-relevant |
| `core/cpp/include/jarvis/core/self_model.hpp` | modified | PR #97-only net path | Inspect semantic diff where high-risk; per-commit hunk attribution only where origin/overlap/effect is decision-relevant |
| `core/cpp/include/jarvis/core/world_model.hpp` | modified | post-PR #97 first introduced | Inspect semantic diff where high-risk; per-commit hunk attribution only where origin/overlap/effect is decision-relevant |
| `core/cpp/src/action_execution.cpp` | modified | PR #97-only net path | Inspect semantic diff where high-risk; per-commit hunk attribution only where origin/overlap/effect is decision-relevant |
| `core/cpp/src/adaptation.cpp` | modified | PR #97-only net path | Inspect semantic diff where high-risk; per-commit hunk attribution only where origin/overlap/effect is decision-relevant |
| `core/cpp/src/affective_learning.cpp` | added | PR #97-only net path | Inspect semantic diff where high-risk; per-commit hunk attribution only where origin/overlap/effect is decision-relevant |
| `core/cpp/src/affective_state.cpp` | added | PR #97-only net path | Inspect semantic diff where high-risk; per-commit hunk attribution only where origin/overlap/effect is decision-relevant |
| `core/cpp/src/association_model.cpp` | modified | PR #97-only net path | Inspect semantic diff where high-risk; per-commit hunk attribution only where origin/overlap/effect is decision-relevant |
| `core/cpp/src/attention.cpp` | modified | PR #97-only net path | Inspect semantic diff where high-risk; per-commit hunk attribution only where origin/overlap/effect is decision-relevant |
| `core/cpp/src/brain_action_execution.cpp` | added | PR #97-only net path | Inspect semantic diff where high-risk; per-commit hunk attribution only where origin/overlap/effect is decision-relevant |
| `core/cpp/src/brain_affective_planning.cpp` | added | PR #97-only net path | Inspect semantic diff where high-risk; per-commit hunk attribution only where origin/overlap/effect is decision-relevant |
| `core/cpp/src/brain_prediction_context.cpp` | added | PR #97-only net path | Inspect semantic diff where high-risk; per-commit hunk attribution only where origin/overlap/effect is decision-relevant |
| `core/cpp/src/brain_restored_api.cpp` | added | PR #97 + post-PR #97 overlap | Inspect semantic diff where high-risk; per-commit hunk attribution only where origin/overlap/effect is decision-relevant |
| `core/cpp/src/brain.cpp` | modified | PR #97 + post-PR #97 overlap | Inspect semantic diff where high-risk; per-commit hunk attribution only where origin/overlap/effect is decision-relevant |
| `core/cpp/src/causal_model.cpp` | modified | PR #97 + post-PR #97 overlap | Inspect semantic diff where high-risk; per-commit hunk attribution only where origin/overlap/effect is decision-relevant |
| `core/cpp/src/cognitive_cycle.cpp` | modified | PR #97 + post-PR #97 overlap | Inspect semantic diff where high-risk; per-commit hunk attribution only where origin/overlap/effect is decision-relevant |
| `core/cpp/src/cognitive_runtime.cpp` | modified | PR #97-only net path | Inspect semantic diff where high-risk; per-commit hunk attribution only where origin/overlap/effect is decision-relevant |
| `core/cpp/src/decision.cpp` | modified | PR #97-only net path | Inspect semantic diff where high-risk; per-commit hunk attribution only where origin/overlap/effect is decision-relevant |
| `core/cpp/src/developmental_learning.cpp` | added | PR #97 + post-PR #97 overlap | Inspect semantic diff where high-risk; per-commit hunk attribution only where origin/overlap/effect is decision-relevant |
| `core/cpp/src/evolution_adoption_journal.cpp` | modified | PR #97-only net path | Inspect semantic diff where high-risk; per-commit hunk attribution only where origin/overlap/effect is decision-relevant |
| `core/cpp/src/evolution_adoption.cpp` | modified | PR #97-only net path | Inspect semantic diff where high-risk; per-commit hunk attribution only where origin/overlap/effect is decision-relevant |
| `core/cpp/src/evolution_canary.cpp` | modified | PR #97-only net path | Inspect semantic diff where high-risk; per-commit hunk attribution only where origin/overlap/effect is decision-relevant |
| `core/cpp/src/evolution_controller.cpp` | modified | PR #97-only net path | Inspect semantic diff where high-risk; per-commit hunk attribution only where origin/overlap/effect is decision-relevant |
| `core/cpp/src/evolution_experiment_coordinator.cpp` | modified | PR #97-only net path | Inspect semantic diff where high-risk; per-commit hunk attribution only where origin/overlap/effect is decision-relevant |
| `core/cpp/src/evolution_experiment_runner.cpp` | modified | PR #97-only net path | Inspect semantic diff where high-risk; per-commit hunk attribution only where origin/overlap/effect is decision-relevant |
| `core/cpp/src/evolution_history.cpp` | modified | PR #97-only net path | Inspect semantic diff where high-risk; per-commit hunk attribution only where origin/overlap/effect is decision-relevant |
| `core/cpp/src/evolution_orchestrator.cpp` | modified | PR #97-only net path | Inspect semantic diff where high-risk; per-commit hunk attribution only where origin/overlap/effect is decision-relevant |
| `core/cpp/src/evolution_safety.cpp` | modified | PR #97-only net path | Inspect semantic diff where high-risk; per-commit hunk attribution only where origin/overlap/effect is decision-relevant |
| `core/cpp/src/evolution_sandbox.cpp` | modified | PR #97-only net path | Inspect semantic diff where high-risk; per-commit hunk attribution only where origin/overlap/effect is decision-relevant |
| `core/cpp/src/evolution.cpp` | modified | PR #97-only net path | Inspect semantic diff where high-risk; per-commit hunk attribution only where origin/overlap/effect is decision-relevant |
| `core/cpp/src/goals.cpp` | modified | PR #97-only net path | Inspect semantic diff where high-risk; per-commit hunk attribution only where origin/overlap/effect is decision-relevant |
| `core/cpp/src/intent.cpp` | modified | PR #97-only net path | Inspect semantic diff where high-risk; per-commit hunk attribution only where origin/overlap/effect is decision-relevant |
| `core/cpp/src/knowledge.cpp` | modified | PR #97 + post-PR #97 overlap | Inspect semantic diff where high-risk; per-commit hunk attribution only where origin/overlap/effect is decision-relevant |
| `core/cpp/src/memory.cpp` | modified | PR #97-only net path | Inspect semantic diff where high-risk; per-commit hunk attribution only where origin/overlap/effect is decision-relevant |
| `core/cpp/src/planning.cpp` | modified | PR #97-only net path | Inspect semantic diff where high-risk; per-commit hunk attribution only where origin/overlap/effect is decision-relevant |
| `core/cpp/src/process_isolation.cpp` | modified | PR #97-only net path | Inspect semantic diff where high-risk; per-commit hunk attribution only where origin/overlap/effect is decision-relevant |
| `core/cpp/src/reasoning.cpp` | modified | PR #97-only net path | Inspect semantic diff where high-risk; per-commit hunk attribution only where origin/overlap/effect is decision-relevant |
| `core/cpp/src/reflection.cpp` | modified | PR #97-only net path | Inspect semantic diff where high-risk; per-commit hunk attribution only where origin/overlap/effect is decision-relevant |
| `core/cpp/src/representation.cpp` | modified | PR #97-only net path | Inspect semantic diff where high-risk; per-commit hunk attribution only where origin/overlap/effect is decision-relevant |
| `core/cpp/src/self_model.cpp` | modified | PR #97-only net path | Inspect semantic diff where high-risk; per-commit hunk attribution only where origin/overlap/effect is decision-relevant |
| `core/cpp/src/world_model.cpp` | modified | post-PR #97 first introduced | Inspect semantic diff where high-risk; per-commit hunk attribution only where origin/overlap/effect is decision-relevant |
| `core/cpp/tests/action_authorization_suite.cpp` | modified | PR #97-only net path | Inspect semantic diff where high-risk; per-commit hunk attribution only where origin/overlap/effect is decision-relevant |
| `core/cpp/tests/action_execution_phase7_suite.cpp` | modified | PR #97-only net path | Inspect semantic diff where high-risk; per-commit hunk attribution only where origin/overlap/effect is decision-relevant |
| `core/cpp/tests/action_model_architecture_suite.cpp` | modified | PR #97-only net path | Inspect semantic diff where high-risk; per-commit hunk attribution only where origin/overlap/effect is decision-relevant |
| `core/cpp/tests/affective_brain_decision_suite.cpp` | added | PR #97-only net path | Inspect semantic diff where high-risk; per-commit hunk attribution only where origin/overlap/effect is decision-relevant |
| `core/cpp/tests/affective_decision_learning_suite.cpp` | added | PR #97-only net path | Inspect semantic diff where high-risk; per-commit hunk attribution only where origin/overlap/effect is decision-relevant |
| `core/cpp/tests/affective_decision_suite.cpp` | added | PR #97-only net path | Inspect semantic diff where high-risk; per-commit hunk attribution only where origin/overlap/effect is decision-relevant |
| `core/cpp/tests/affective_evidence_suite.cpp` | added | PR #97-only net path | Inspect semantic diff where high-risk; per-commit hunk attribution only where origin/overlap/effect is decision-relevant |
| `core/cpp/tests/affective_goal_outcome_suite.cpp` | added | PR #97-only net path | Inspect semantic diff where high-risk; per-commit hunk attribution only where origin/overlap/effect is decision-relevant |
| `core/cpp/tests/affective_learning_suite.cpp` | added | PR #97-only net path | Inspect semantic diff where high-risk; per-commit hunk attribution only where origin/overlap/effect is decision-relevant |
| `core/cpp/tests/affective_planning_suite.cpp` | added | PR #97-only net path | Inspect semantic diff where high-risk; per-commit hunk attribution only where origin/overlap/effect is decision-relevant |
| `core/cpp/tests/affective_planning.cmake` | added | PR #97-only net path | Inspect semantic diff where high-risk; per-commit hunk attribution only where origin/overlap/effect is decision-relevant |
| `core/cpp/tests/affective_state_model_suite.cpp` | added | PR #97-only net path | Inspect semantic diff where high-risk; per-commit hunk attribution only where origin/overlap/effect is decision-relevant |
| `core/cpp/tests/affective_state_suite.cpp` | added | PR #97-only net path | Inspect semantic diff where high-risk; per-commit hunk attribution only where origin/overlap/effect is decision-relevant |
| `core/cpp/tests/association_causality_phase5_suite.cpp` | modified | PR #97 + post-PR #97 overlap | Inspect semantic diff where high-risk; per-commit hunk attribution only where origin/overlap/effect is decision-relevant |
| `core/cpp/tests/attention_architecture_suite.cpp` | modified | PR #97-only net path | Inspect semantic diff where high-risk; per-commit hunk attribution only where origin/overlap/effect is decision-relevant |
| `core/cpp/tests/attention_learning_brain_suite.cpp` | added | PR #97-only net path | Inspect semantic diff where high-risk; per-commit hunk attribution only where origin/overlap/effect is decision-relevant |
| `core/cpp/tests/brain_10_suite.cpp` | modified | PR #97-only net path | Inspect semantic diff where high-risk; per-commit hunk attribution only where origin/overlap/effect is decision-relevant |
| `core/cpp/tests/brain_action_consequence_integration_suite.cpp` | added | PR #97-only net path | Inspect semantic diff where high-risk; per-commit hunk attribution only where origin/overlap/effect is decision-relevant |
| `core/cpp/tests/brain_contract.cpp` | modified | PR #97-only net path | Inspect semantic diff where high-risk; per-commit hunk attribution only where origin/overlap/effect is decision-relevant |
| `core/cpp/tests/brain_deep_suite.cpp` | modified | PR #97-only net path | Inspect semantic diff where high-risk; per-commit hunk attribution only where origin/overlap/effect is decision-relevant |
| `core/cpp/tests/CMakeLists.txt` | modified | PR #97 + post-PR #97 overlap | Inspect semantic diff where high-risk; per-commit hunk attribution only where origin/overlap/effect is decision-relevant |
| `core/cpp/tests/cognitive_cycle_suite.cpp` | modified | PR #97-only net path | Inspect semantic diff where high-risk; per-commit hunk attribution only where origin/overlap/effect is decision-relevant |
| `core/cpp/tests/cognitive_runtime_goal_feedback_suite.cpp` | added | PR #97-only net path | Inspect semantic diff where high-risk; per-commit hunk attribution only where origin/overlap/effect is decision-relevant |
| `core/cpp/tests/cognitive_runtime_learning_integration_suite.cpp` | added | PR #97-only net path | Inspect semantic diff where high-risk; per-commit hunk attribution only where origin/overlap/effect is decision-relevant |
| `core/cpp/tests/cognitive_runtime_suite.cpp` | modified | PR #97-only net path | Inspect semantic diff where high-risk; per-commit hunk attribution only where origin/overlap/effect is decision-relevant |
| `core/cpp/tests/cognitive_workspace_runtime_suite.cpp` | modified | PR #97-only net path | Inspect semantic diff where high-risk; per-commit hunk attribution only where origin/overlap/effect is decision-relevant |
| `core/cpp/tests/decision_planning_architecture_suite.cpp` | modified | PR #97-only net path | Inspect semantic diff where high-risk; per-commit hunk attribution only where origin/overlap/effect is decision-relevant |
| `core/cpp/tests/developmental_brain_integration_suite.cpp` | added | PR #97 + post-PR #97 overlap | Inspect semantic diff where high-risk; per-commit hunk attribution only where origin/overlap/effect is decision-relevant |
| `core/cpp/tests/developmental_environment_suite.cpp` | added | PR #97-only net path | Inspect semantic diff where high-risk; per-commit hunk attribution only where origin/overlap/effect is decision-relevant |
| `core/cpp/tests/developmental_learning_suite.cpp` | added | PR #97-only net path | Inspect semantic diff where high-risk; per-commit hunk attribution only where origin/overlap/effect is decision-relevant |
| `core/cpp/tests/developmental_learning_tests.cpp` | added | PR #97-only net path | Inspect semantic diff where high-risk; per-commit hunk attribution only where origin/overlap/effect is decision-relevant |
| `core/cpp/tests/developmental_training_environment_suite.cpp` | added | PR #97-only net path | Inspect semantic diff where high-risk; per-commit hunk attribution only where origin/overlap/effect is decision-relevant |
| `core/cpp/tests/developmental_world_integration_suite.cpp` | added | PR #97-only net path | Inspect semantic diff where high-risk; per-commit hunk attribution only where origin/overlap/effect is decision-relevant |
| `core/cpp/tests/developmental_world_suite.cpp` | added | PR #97-only net path | Inspect semantic diff where high-risk; per-commit hunk attribution only where origin/overlap/effect is decision-relevant |
| `core/cpp/tests/dlt_001_long_run.cpp` | added | PR #97-only net path | Inspect semantic diff where high-risk; per-commit hunk attribution only where origin/overlap/effect is decision-relevant |
| `core/cpp/tests/dlt_001_trial.cpp` | added | PR #97-only net path | Inspect semantic diff where high-risk; per-commit hunk attribution only where origin/overlap/effect is decision-relevant |
| `core/cpp/tests/dlt_002_long_run.cpp` | added | PR #97-only net path | Inspect semantic diff where high-risk; per-commit hunk attribution only where origin/overlap/effect is decision-relevant |
| `core/cpp/tests/dlt_002_persistence.cpp` | added | PR #97-only net path | Inspect semantic diff where high-risk; per-commit hunk attribution only where origin/overlap/effect is decision-relevant |
| `core/cpp/tests/dlt_003_mapping_generalization.cpp` | added | post-PR #97 first introduced | Inspect semantic diff where high-risk; per-commit hunk attribution only where origin/overlap/effect is decision-relevant |
| `core/cpp/tests/dlt_004_feature_composition.cpp` | added | post-PR #97 first introduced | Inspect semantic diff where high-risk; per-commit hunk attribution only where origin/overlap/effect is decision-relevant |
| `core/cpp/tests/evolution_adoption_journal_suite.cpp` | modified | PR #97-only net path | Inspect semantic diff where high-risk; per-commit hunk attribution only where origin/overlap/effect is decision-relevant |
| `core/cpp/tests/evolution_brain_integration_suite.cpp` | modified | PR #97 + post-PR #97 overlap | Inspect semantic diff where high-risk; per-commit hunk attribution only where origin/overlap/effect is decision-relevant |
| `core/cpp/tests/evolution_canary_controller_suite.cpp` | modified | PR #97-only net path | Inspect semantic diff where high-risk; per-commit hunk attribution only where origin/overlap/effect is decision-relevant |
| `core/cpp/tests/evolution_experiment_coordinator_suite.cpp` | modified | PR #97-only net path | Inspect semantic diff where high-risk; per-commit hunk attribution only where origin/overlap/effect is decision-relevant |
| `core/cpp/tests/evolution_experiment_runner_suite.cpp` | modified | PR #97-only net path | Inspect semantic diff where high-risk; per-commit hunk attribution only where origin/overlap/effect is decision-relevant |
| `core/cpp/tests/evolution_opportunity_orchestration_suite.cpp` | modified | PR #97-only net path | Inspect semantic diff where high-risk; per-commit hunk attribution only where origin/overlap/effect is decision-relevant |
| `core/cpp/tests/experience_memory_test.cpp` | added | PR #97-only net path | Inspect semantic diff where high-risk; per-commit hunk attribution only where origin/overlap/effect is decision-relevant |
| `core/cpp/tests/goal_directed_cognition_suite.cpp` | added | PR #97-only net path | Inspect semantic diff where high-risk; per-commit hunk attribution only where origin/overlap/effect is decision-relevant |
| `core/cpp/tests/goal_outcome_model_suite.cpp` | added | PR #97-only net path | Inspect semantic diff where high-risk; per-commit hunk attribution only where origin/overlap/effect is decision-relevant |
| `core/cpp/tests/goals_architecture_suite.cpp` | modified | PR #97-only net path | Inspect semantic diff where high-risk; per-commit hunk attribution only where origin/overlap/effect is decision-relevant |
| `core/cpp/tests/knowledge_memory_phase3_suite.cpp` | modified | PR #97 + post-PR #97 overlap | Inspect semantic diff where high-risk; per-commit hunk attribution only where origin/overlap/effect is decision-relevant |
| `core/cpp/tests/knowledge_source_feedback_suite.cpp` | added | post-PR #97 first introduced | Inspect semantic diff where high-risk; per-commit hunk attribution only where origin/overlap/effect is decision-relevant |
| `core/cpp/tests/learning_adaptation_phase8_suite.cpp` | modified | PR #97-only net path | Inspect semantic diff where high-risk; per-commit hunk attribution only where origin/overlap/effect is decision-relevant |
| `core/cpp/tests/memory_architecture_suite.cpp` | modified | PR #97-only net path | Inspect semantic diff where high-risk; per-commit hunk attribution only where origin/overlap/effect is decision-relevant |
| `core/cpp/tests/memory_learning_evolution_persistence_suite.cpp` | added | PR #97-only net path | Inspect semantic diff where high-risk; per-commit hunk attribution only where origin/overlap/effect is decision-relevant |
| `core/cpp/tests/prediction_feedback_phase10_suite.cpp` | modified | PR #97-only net path | Inspect semantic diff where high-risk; per-commit hunk attribution only where origin/overlap/effect is decision-relevant |
| `core/cpp/tests/process_isolation_suite.cpp` | modified | PR #97-only net path | Inspect semantic diff where high-risk; per-commit hunk attribution only where origin/overlap/effect is decision-relevant |
| `core/cpp/tests/reasoning_architecture_suite.cpp` | modified | PR #97-only net path | Inspect semantic diff where high-risk; per-commit hunk attribution only where origin/overlap/effect is decision-relevant |
| `core/cpp/tests/representation_suite.cpp` | modified | PR #97-only net path | Inspect semantic diff where high-risk; per-commit hunk attribution only where origin/overlap/effect is decision-relevant |
| `docs/DEVELOPMENTAL_BRAIN_PLAN.md` | added | post-PR #97 first introduced | Inspect semantic diff where high-risk; per-commit hunk attribution only where origin/overlap/effect is decision-relevant |
| `docs/developmental-training-environment.md` | added | PR #97-only net path | Inspect semantic diff where high-risk; per-commit hunk attribution only where origin/overlap/effect is decision-relevant |
| `docs/superpowers/plans/2026-09-25-cognitive-action-feedback-loop.md` | added | PR #97-only net path | Inspect semantic diff where high-risk; per-commit hunk attribution only where origin/overlap/effect is decision-relevant |
| `docs/superpowers/plans/2026-09-26-concept-context-prediction.md` | added | PR #97-only net path | Inspect semantic diff where high-risk; per-commit hunk attribution only where origin/overlap/effect is decision-relevant |
| `docs/superpowers/plans/2026-09-30-developmental-cognition.md` | added | PR #97-only net path | Inspect semantic diff where high-risk; per-commit hunk attribution only where origin/overlap/effect is decision-relevant |
| `docs/superpowers/plans/2026-10-01-affective-state.md` | added | PR #97-only net path | Inspect semantic diff where high-risk; per-commit hunk attribution only where origin/overlap/effect is decision-relevant |
| `docs/superpowers/specs/2026-09-25-cognitive-action-feedback-loop-design.md` | added | PR #97-only net path | Inspect semantic diff where high-risk; per-commit hunk attribution only where origin/overlap/effect is decision-relevant |
| `docs/superpowers/specs/2026-09-26-concept-context-prediction-design.md` | added | PR #97-only net path | Inspect semantic diff where high-risk; per-commit hunk attribution only where origin/overlap/effect is decision-relevant |
| `docs/superpowers/specs/2026-09-30-developmental-cognition.md` | added | PR #97-only net path | Inspect semantic diff where high-risk; per-commit hunk attribution only where origin/overlap/effect is decision-relevant |
| `docs/superpowers/specs/2026-10-01-affective-state.md` | added | PR #97-only net path | Inspect semantic diff where high-risk; per-commit hunk attribution only where origin/overlap/effect is decision-relevant |
| `engineering/cpp/CMakeLists.txt` | modified | PR #97-only net path | Inspect semantic diff where high-risk; per-commit hunk attribution only where origin/overlap/effect is decision-relevant |
| `engineering/cpp/include/jarvis/engineering/agent.hpp` | modified | PR #97-only net path | Inspect semantic diff where high-risk; per-commit hunk attribution only where origin/overlap/effect is decision-relevant |
| `engineering/cpp/include/jarvis/engineering/coordinator.hpp` | modified | PR #97-only net path | Inspect semantic diff where high-risk; per-commit hunk attribution only where origin/overlap/effect is decision-relevant |
| `engineering/cpp/include/jarvis/engineering/message_bus.hpp` | modified | PR #97-only net path | Inspect semantic diff where high-risk; per-commit hunk attribution only where origin/overlap/effect is decision-relevant |
| `engineering/cpp/include/jarvis/engineering/task_ledger.hpp` | added | PR #97-only net path | Inspect semantic diff where high-risk; per-commit hunk attribution only where origin/overlap/effect is decision-relevant |
| `engineering/cpp/src/coordinator.cpp` | modified | PR #97-only net path | Inspect semantic diff where high-risk; per-commit hunk attribution only where origin/overlap/effect is decision-relevant |
| `engineering/cpp/src/message_bus.cpp` | modified | PR #97-only net path | Inspect semantic diff where high-risk; per-commit hunk attribution only where origin/overlap/effect is decision-relevant |
| `engineering/cpp/src/task_ledger.cpp` | added | PR #97-only net path | Inspect semantic diff where high-risk; per-commit hunk attribution only where origin/overlap/effect is decision-relevant |
| `engineering/cpp/tests/agent_and_console_suite.cpp` | modified | PR #97-only net path | Inspect semantic diff where high-risk; per-commit hunk attribution only where origin/overlap/effect is decision-relevant |
| `engineering/cpp/tests/task_ledger_suite.cpp` | added | PR #97-only net path | Inspect semantic diff where high-risk; per-commit hunk attribution only where origin/overlap/effect is decision-relevant |

## 4. Required targeted attribution

### 4.1 Overlap paths — all require deeper review

- `core/cpp/include/jarvis/core/brain.hpp`
- `core/cpp/include/jarvis/core/developmental_learning.hpp`
- `core/cpp/include/jarvis/core/knowledge.hpp`
- `core/cpp/src/brain.cpp`
- `core/cpp/src/brain_restored_api.cpp`
- `core/cpp/src/causal_model.cpp`
- `core/cpp/src/cognitive_cycle.cpp`
- `core/cpp/src/developmental_learning.cpp`
- `core/cpp/src/knowledge.cpp`
- `core/cpp/tests/CMakeLists.txt`
- `core/cpp/tests/association_causality_phase5_suite.cpp`
- `core/cpp/tests/developmental_brain_integration_suite.cpp`
- `core/cpp/tests/evolution_brain_integration_suite.cpp`
- `core/cpp/tests/knowledge_memory_phase3_suite.cpp`

### 4.2 Post-PR #97 first-introduced paths — origin segment confirmed; assess semantic risk

- `core/cpp/include/jarvis/core/world_model.hpp`
- `core/cpp/src/world_model.cpp`
- `core/cpp/tests/dlt_003_mapping_generalization.cpp`
- `core/cpp/tests/dlt_004_feature_composition.cpp`
- `core/cpp/tests/knowledge_source_feedback_suite.cpp`
- `docs/DEVELOPMENTAL_BRAIN_PLAN.md`

### 4.3 High-risk PR #97-only paths

The PR #97-only complement includes core Brain interfaces and implementation, memory, representation, reasoning, attention, causal/prediction, goals/intent, decision/action, evolution, persistence/replay, CMake/test registry, and CI. These require prioritization by subsystem and final candidate call-path impact; origin class alone is not a waiver.

## 5. Residual limitations

- The 1,416 inherited commit SHAs were enumerated, but a complete per-commit origin/path/hunk ledger was not produced.
- The source tooling limitation remains: no exhaustive paginated commit/file-patch sequence was available in this session, and the prior local clone attempt failed DNS resolution.
- This matrix reconstructs the 165-path inventory and origin classes from the prior reconciliation record. It does not independently re-fetch every historical commit patch.
- Any discrepancy between this matrix and the live candidate tree must be reconciled before Gate A can be recommended for clearance.

**Disposition:** Path-set accounting reproduced from the recorded evidence. High-risk semantic attribution and independent review remain open. Gate A remains NOT CLEARED.


## 6. Targeted blob-level reconciliation of all 14 overlap paths — 2026-11-04

The 14 paths identified in §4.1 were re-fetched at:
- comparison point `af09cf28d35e4a7b75c3c019e9f97893d8e19364`;
- candidate code-bearing parent `15d49e5fdeb5723c475922ab78fb92f97c4b3b84`.

The comparison point commit is titled `revert(engineering): remove duplicate agent console implementation`.
The table records blob identity only. A different blob proves that the final file content differs from that comparison point; it does not, by itself, explain which commit introduced each hunk or establish semantic correctness.

| Overlap path | Comparison-point blob | Candidate blob | Blob-level result |
|---|---|---|---|
| `core/cpp/include/jarvis/core/brain.hpp` | `8268ef84e0b361ead536724ba7761904b30ee58f` | `ca718aa4603bbdd0abc7de26ed296bcf8c6562fe` | Different |
| `core/cpp/include/jarvis/core/developmental_learning.hpp` | Absent (404 at comparison point) | `65174400d8c3ce1dea17667ac928767cf3af333a` | Added after comparison point |
| `core/cpp/include/jarvis/core/knowledge.hpp` | `50eb1113a4569c3de05489c421d1cabb1437733d` | `ae1adcffeeb090eb102c05156388bce7c030538f` | Different |
| `core/cpp/src/brain.cpp` | `e9f3758fcc9c0e89b7280ce376db9033d547682d` | `93a10a5021a5775a3a239037cbb0b58a1e0c67a9` | Different |
| `core/cpp/src/brain_restored_api.cpp` | Absent (404 at comparison point) | `00d69ab2eb3811d453a643ef18dc69741109cbc8` | Added after comparison point |
| `core/cpp/src/causal_model.cpp` | `f873d0a6e7fa0676bb88bf7a1f66436bc88a3c0d` | `8b884ed11a1a019d0e52bf7f35b0295edcc912b0` | Different |
| `core/cpp/src/cognitive_cycle.cpp` | `3df14c552f2048b0394dc362f7ee7a654a93fb32` | `989f4d154f07b31bcdab175aefbea6edd61eb930` | Different |
| `core/cpp/src/developmental_learning.cpp` | Absent (404 at comparison point) | `c9a34d562fa1a20641530daba81bfdc1f3621fee` | Added after comparison point |
| `core/cpp/src/knowledge.cpp` | `25ecf822e6132f576266c1f86a964a227c7fb75f` | `c38e0909c220b450502b46fd4a145e63ab6d21a0` | Different |
| `core/cpp/tests/CMakeLists.txt` | `dab0c52ab4dfe15e1e2cbccfa9e6c904abdf54e3` | `0251936730f82a7a8c928fa31dfe1d7effc83d91` | Different |
| `core/cpp/tests/association_causality_phase5_suite.cpp` | `d520025258805b02c1b3fbb2dbebe32e01562fbf` | `9099323d43b5af16d09c9356a239692fab5e136a` | Different |
| `core/cpp/tests/developmental_brain_integration_suite.cpp` | Absent (404 at comparison point) | `e6eba3db6df8da9ecfed21974936908a32ea11c5` | Added after comparison point |
| `core/cpp/tests/evolution_brain_integration_suite.cpp` | `3164cbc19bfb056cdccfdd58f0be047226d41a86` | `d9dc62b1c6aebdb4ab38f3d64150699d96f393c4` | Different |
| `core/cpp/tests/knowledge_memory_phase3_suite.cpp` | `f796977fd116418b3cf0a5f9c8d33ed7a48f811e` | `108e4c07259df599bb7371a2f4b3b497be97f844` | Different |

### 6.1 What this establishes

- All 14 recorded overlap paths were independently re-fetched at both refs where present.
- Ten paths exist at both refs and have different blobs.
- Four paths are absent at the comparison point and present in the candidate tree.
- The prior path-set accounting is therefore supported by direct blob-level checks for this overlap set.

### 6.2 What it does not establish

- It does not attribute every changed line to a particular PR or commit.
- It does not establish that all semantic changes in the ten differing files are safe.
- It does not explain the full introduction history of the four absent files.
- It does not replace targeted diff/hunk review for high-risk code, especially Brain public APIs, journal/replay, knowledge feedback, developmental learning, and integrated tests.

**Updated disposition:** The 14-path overlap set now has direct comparison-point/candidate blob evidence. Semantic and commit/hunk attribution remain open for all materially changed high-risk files. Gate A remains NOT CLEARED.
