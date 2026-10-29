#include "jarvis/core/evolution_adoption_journal.hpp"
#include "jarvis/core/evolution_controller.hpp"
#include "jarvis/core/evolution_history.hpp"
#include "jarvis/core/evolution.hpp"
#include "jarvis/core/evolution_experiment_runner.hpp"
#include "jarvis/core/evolution_digest.hpp"
#include "jarvis/core/process_isolation.hpp"
#include <cmath>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <cassert>
using namespace jarvis::core;
namespace {
std::string evaluator_path, baseline_path, candidate_path;
void write_artifacts(const EvolutionExperiment& e) {
    { std::ofstream out(baseline_path); out << std::setprecision(17) << e.proposal.current; }
    { std::ofstream out(candidate_path); out << std::setprecision(17) << e.proposal.proposed; }
}
ExperimentOutcome attest_isolated(EvolutionExperiment& e) {
    write_artifacts(e);
    ProcessIsolationBackend backend;
    IsolatedEvaluationProcedure procedure{
        IsolatedCommand{evaluator_path, {"--trusted-test-evaluator"}, ""},
        "adoption-journal-local-evaluator-v1", "held-out-linear-regression-v1",
        baseline_path, candidate_path, detail::sha256_file(evaluator_path)};
    return EvolutionExperimentRunner::run_isolated_evaluation(e, backend, procedure, 4, 4, 0.5);
}
}
int main(int argc,char**argv){
 if(argc>1 && std::string(argv[1])=="--trusted-test-evaluator"){
   if(argc!=14 || std::string(argv[2])!="--jarvis-evaluate-v1") return 21;
   std::ifstream artifact(argv[9]); std::string coefficient_text;
   if(!artifact || !(artifact>>coefficient_text)) return 22;
   const double coefficient=std::stod(coefficient_text);
   if(std::abs(coefficient-std::stod(argv[6]))>1e-12) return 23;
   double squared_error=0.0;
   for(double input=1.0;input<=4.0;input+=1.0){const double error=coefficient*input-0.8*input;squared_error+=error*error;}
   const double fitness=1.0/(1.0+squared_error/4.0);
   std::cout<<"JARVIS_EVAL_V1\t"<<argv[3]<<"\t"<<argv[4]<<"\t"<<argv[5]<<"\t"<<argv[6]<<"\t"<<argv[7]<<"\t"<<argv[8]<<"\t"<<argv[10]<<"\t"<<argv[11]<<"\t"<<argv[12]<<"\t"<<argv[13]<<"\t"<<fitness;
   return 0;
 }
 evaluator_path=std::filesystem::absolute(argv[0]).string();
 const auto temp=std::filesystem::temp_directory_path();
 baseline_path=(temp/"jarvis_adoption_journal_baseline.txt").string();
 candidate_path=(temp/"jarvis_adoption_journal_candidate.txt").string(); EvolutionAdoptionJournal j; EvolutionExperiment e{}; e.id="exp-1"; e.proposal.key="candidate"; e.baseline_fitness=0.5; e.candidate_fitness=0.8; e.confidence=0.9; assert(j.stage(e)); auto staged=j.get("exp-1"); assert(staged && staged->state==AdoptionState::Pending); assert(j.commit("exp-1")); assert(j.commit("exp-1")); auto adopted=j.get("exp-1"); assert(adopted && adopted->state==AdoptionState::Adopted); assert(j.restore_pending("exp-1", "adoption_history_failed")); auto compensated=j.get("exp-1"); assert(compensated && compensated->state==AdoptionState::Pending); assert(j.commit("exp-1")); assert(j.rollback("exp-1")); assert(j.restore_adopted("exp-1", "rollback_history_failed")); auto restored=j.get("exp-1"); assert(restored && restored->state==AdoptionState::Adopted); assert(j.rollback("exp-1")); assert(j.rollback("exp-1")); auto rolled=j.get("exp-1"); assert(rolled && !j.stage(e)); assert(rolled && rolled->state==AdoptionState::RolledBack); assert(j.restore_adopted("exp-1")); auto restored_again=j.get("exp-1"); assert(restored_again && restored_again->state==AdoptionState::Adopted); assert(j.rollback("exp-1", "rollback_again")); 

 EvolutionModel model;
 model.register_parameter("transactional", 0.2);
 model.observe_fitness("transactional", 0.8);
 model.observe_fitness("transactional", 0.8);
 EvolutionHistory controller_history;
 auto proposals=model.propose();
 assert(!proposals.empty());
 EvolutionSafetyPolicy test_policy{};
 test_policy.minimum_confidence=proposals.front().confidence;
 test_policy.require_isolation=false; // This suite isolates journal transitions; sandbox attestation is tested separately.
 EvolutionController controller(model, controller_history, test_policy);
 EvolutionExperiment experiment{};
 experiment.id="exp-controller";
 experiment.proposal=proposals.front();
 experiment.baseline_fitness=0.2;
 experiment.candidate_fitness=0.8;
 experiment.confidence=proposals.front().confidence;
 experiment.outcome=ExperimentOutcome::Improved;
 experiment.candidate_executed=true;
 assert(attest_isolated(experiment)==ExperimentOutcome::Improved);
 assert(controller.record_evaluation(experiment));
 assert(controller.record_evaluation(experiment));
 EvolutionExperiment neutral=experiment;
 neutral.id="exp-neutral";
 neutral.minimum_improvement=0.1;
 assert(attest_isolated(neutral)==ExperimentOutcome::Neutral);
 assert(controller.record_evaluation(neutral));
 assert(!controller.adopt(neutral));
 assert(controller_history.for_experiment("exp-neutral").size()==1);
 EvolutionExperiment pending=experiment;
 pending.id="exp-pending";
 pending.outcome=ExperimentOutcome::Pending;
 assert(!controller.record_evaluation(pending));

 EvolutionExperiment unsafe=experiment;
 unsafe.id="exp-unsafe";
 unsafe.confidence=0.1;
 assert(!controller.adopt(unsafe));
 // An unrecorded or mutated experiment is rejected before it can create a
 // pending adoption record or alter the model.
 const auto unsafe_journal=controller.adoption_journal().get("exp-unsafe");
 assert(!unsafe_journal.has_value());
 const auto unsafe_history=controller_history.for_experiment("exp-unsafe");
 assert(unsafe_history.empty());
 assert(model.parameter("transactional")->value ==
        model.parameter("transactional")->baseline);
 assert(controller.adopt(experiment));
 const auto* adopted_parameter=model.parameter("transactional");
 assert(adopted_parameter && adopted_parameter->value==experiment.proposal.proposed);
 assert(controller.compensate_adoption_for_brain(experiment));
 const auto* compensated_parameter=model.parameter("transactional");
 assert(compensated_parameter && compensated_parameter->value==compensated_parameter->baseline);
 const auto compensated_journal=controller.adoption_journal().get(experiment.id);
 assert(compensated_journal && compensated_journal->state==AdoptionState::Pending);
 assert(controller.adopt(experiment));
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
 replay_compensation_experiment.proposal.expected_gain=0.10;
 assert(attest_isolated(replay_compensation_experiment)==ExperimentOutcome::Improved);
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
 std::error_code cleanup_error;
 std::filesystem::remove(baseline_path, cleanup_error);
 std::filesystem::remove(candidate_path, cleanup_error);
 return 0; }
