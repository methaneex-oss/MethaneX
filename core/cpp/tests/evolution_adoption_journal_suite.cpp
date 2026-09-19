#include "jarvis/core/evolution_adoption_journal.hpp"
#include <cassert>

using namespace jarvis::core;

int main() {
    EvolutionAdoptionJournal journal;
    EvolutionExperiment experiment;
    experiment.id = "exp-1";
    experiment.proposal.key = "latency";
    experiment.baseline_fitness = 0.7;
    experiment.candidate_fitness = 0.8;
    experiment.confidence = 0.95;
    assert(journal.stage(experiment));
    assert(journal.get("exp-1")->state == AdoptionState::Pending);
    assert(journal.commit("exp-1"));
    assert(journal.commit("exp-1"));
    assert(journal.get("exp-1")->state == AdoptionState::Adopted);
    assert(journal.rollback("exp-1"));
    assert(journal.rollback("exp-1"));
    assert(journal.get("exp-1")->state == AdoptionState::RolledBack);
    assert(!journal.commit("exp-1"));
    return 0;
}
