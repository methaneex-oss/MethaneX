#include "jarvis/core/evolution_adoption_journal.hpp"
#include "jarvis/core/evolution_controller.hpp"
#include "jarvis/core/evolution_history.hpp"
#include "jarvis/core/evolution.hpp"
#include <cassert>
using namespace jarvis::core;
int main(){ EvolutionAdoptionJournal j; EvolutionExperiment e{}; e.id="exp-1"; e.proposal.key="candidate"; e.baseline_fitness=0.5; e.candidate_fitness=0.8; e.confidence=0.9; assert(j.stage(e)); auto staged=j.get("exp-1"); assert(staged && staged->state==AdoptionState::Pending); assert(j.commit("exp-1")); assert(j.commit("exp-1")); auto adopted=j.get("exp-1"); assert(adopted && adopted->state==AdoptionState::Adopted); assert(j.restore_pending("exp-1", "adoption_history_failed")); auto compensated=j.get("exp-1"); assert(compensated && compensated->state==AdoptionState::Pending); assert(j.commit("exp-1")); assert(j.rollback("exp-1")); assert(j.restore_adopted("exp-1", "rollback_history_failed")); auto restored=j.get("exp-1"); assert(restored && restored->state==AdoptionState::Adopted); assert(j.rollback("exp-1")); assert(j.rollback("exp-1")); auto rolled=j.get("exp-1"); assert(rolled && !j.stage(e)); assert(rolled && rolled->state==AdoptionState::RolledBack); assert(j.restore_adopted("exp-1")); auto restored=j.get("exp-1"); assert(restored && restored->state==AdoptionState::Adopted); assert(j.rollback("exp-1", "rollback_again")); 

 EvolutionModel model;
 model.register_parameter("transactional", 0.2);
 model.observe_fitness("transactional", 0.8);
 model.observe_fitness("transactional", 0.8);
 EvolutionHistory controller_history;
 EvolutionSafetyPolicy test_policy{};
 test_policy.minimum_confidence=0.0;
 EvolutionController controller(model, controller_history, test_policy);
 auto proposals=model.propose();
 assert(!proposals.empty());
 EvolutionExperiment experiment{};
 experiment.id="exp-controller";
 experiment.proposal=proposals.front();
 experiment.baseline_fitness=0.2;
 experiment.candidate_fitness=0.8;
 experiment.confidence=proposals.front().confidence;
 experiment.outcome=ExperimentOutcome::Improved;
 experiment.candidate_executed=true;
 assert(controller.record_evaluation(experiment));
 assert(controller.record_evaluation(experiment));
 EvolutionExperiment pending=experiment;
 pending.id="exp-pending";
 pending.outcome=ExperimentOutcome::Pending;
 assert(!controller.record_evaluation(pending));

 EvolutionExperiment unsafe=experiment;
 unsafe.id="exp-unsafe";
 unsafe.confidence=0.1;
 assert(!controller.adopt(unsafe));
 const auto unsafe_journal=controller.adoption_journal().get("exp-unsafe");
 assert(unsafe_journal && unsafe_journal->state==AdoptionState::Rejected);
 const auto unsafe_history=controller_history.for_experiment("exp-unsafe");
 assert(unsafe_history.size()==1);
 assert(unsafe_history.front().action==EvolutionRecordAction::Rejected);
 assert(unsafe_history.front().reason=="safety_gate_rejected");
 assert(controller.adopt(experiment));
 const auto* adopted_parameter=model.parameter("transactional");
 assert(adopted_parameter && adopted_parameter->value==experiment.proposal.proposed);
 assert(controller.rollback("transactional", experiment.id, "test_rollback", 0.6));
 const auto* rolled_parameter=model.parameter("transactional");
 assert(rolled_parameter && rolled_parameter->value==rolled_parameter->baseline);
 const auto rolled_record=controller.adoption_journal().get(experiment.id);
 assert(rolled_record && rolled_record->state==AdoptionState::RolledBack);
 assert(controller_history.for_experiment(experiment.id).back().action==EvolutionRecordAction::RolledBack);

 EvolutionModel replay_compensation_model;
 replay_compensation_model.register_parameter("replay-compensation", 0.15);
 replay_compensation_model.observe_fitness("replay-compensation", 0.9);
 replay_compensation_model.observe_fitness("replay-compensation", 0.9);
 EvolutionHistory replay_compensation_history;
 EvolutionController replay_compensation_controller(replay_compensation_model, replay_compensation_history, test_policy);
 EvolutionExperiment replay_compensation_experiment=experiment;
 replay_compensation_experiment.id="exp-replay-compensation";
 replay_compensation_experiment.proposal.key="replay-compensation";
 replay_compensation_experiment.proposal.current=0.15;
 replay_compensation_experiment.proposal.proposed=0.25;
 assert(replay_compensation_controller.record_evaluation(replay_compensation_experiment));
 assert(replay_compensation_model.adopt(replay_compensation_experiment.proposal));
 assert(replay_compensation_controller.replay_adoption(replay_compensation_experiment));
 assert(replay_compensation_model.rollback("replay-compensation"));
 assert(replay_compensation_controller.replay_rollback("exp-replay-compensation","replayed"));
 assert(replay_compensation_model.parameter("replay-compensation")->value==replay_compensation_model.parameter("replay-compensation")->baseline);

 EvolutionModel compensation_model;
 compensation_model.register_parameter("compensation", 0.1);
 compensation_model.observe_fitness("compensation", 0.9);
 compensation_model.observe_fitness("compensation", 0.9);
 auto compensation_proposals=compensation_model.propose();
 assert(!compensation_proposals.empty());
 const double original=compensation_model.parameter("compensation")->value;
 assert(compensation_model.adopt(compensation_proposals.front()));
 assert(compensation_model.parameter("compensation")->value!=original);
 assert(compensation_model.restore_previous("compensation"));
 assert(compensation_model.parameter("compensation")->value==original);

 EvolutionHistory history;
 EvolutionHistoryRecord record{"exp-history", "candidate", EvolutionRecordAction::Adopted,
                              ExperimentOutcome::Improved, 0.5, 0.8, 0.9, 0, "adopted", {}};
 assert(history.append(record));
 assert(history.append(record));
 assert(history.size() == 1);
 return 0; }
