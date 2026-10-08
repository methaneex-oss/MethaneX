#include "jarvis/core/evolution_adoption_journal.hpp"
#include "jarvis/core/evolution_controller.hpp"
#include "jarvis/core/evolution_history.hpp"
#include "jarvis/core/evolution.hpp"
#include <cassert>
using namespace jarvis::core;
int main(){ EvolutionAdoptionJournal j; EvolutionExperiment e{}; e.id="exp-1"; e.proposal.key="candidate"; e.baseline_fitness=0.5; e.candidate_fitness=0.8; e.confidence=0.9; assert(j.stage(e)); auto staged=j.get("exp-1"); assert(staged && staged->state==AdoptionState::Pending); assert(j.commit("exp-1")); assert(j.commit("exp-1")); auto adopted=j.get("exp-1"); assert(adopted && adopted->state==AdoptionState::Adopted); assert(j.rollback("exp-1")); assert(j.rollback("exp-1")); auto rolled=j.get("exp-1"); assert(rolled && !j.stage(e)); assert(rolled && rolled->state==AdoptionState::RolledBack); assert(j.restore_adopted("exp-1")); auto restored=j.get("exp-1"); assert(restored && restored->state==AdoptionState::Adopted); assert(j.rollback("exp-1", "rollback_again")); 

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
 assert(controller.adopt(experiment));
 const auto* adopted_parameter=model.parameter("transactional");
 assert(adopted_parameter && adopted_parameter->value==experiment.proposal.proposed);
 assert(controller.rollback("transactional", experiment.id, "test_rollback", 0.6));
 const auto* rolled_parameter=model.parameter("transactional");
 assert(rolled_parameter && rolled_parameter->value==rolled_parameter->baseline);

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
