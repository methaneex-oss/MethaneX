#include "jarvis/core/evolution_adoption_journal.hpp"
#include <cassert>
using namespace jarvis::core;
int main(){ EvolutionAdoptionJournal j; EvolutionExperiment e{}; e.id="exp-1"; e.proposal.key="candidate"; e.baseline_fitness=0.5; e.candidate_fitness=0.8; e.confidence=0.9; assert(j.stage(e)); assert(j.commit("exp-1")); assert(j.commit("exp-1")); assert(j.rollback("exp-1")); assert(j.rollback("exp-1")); assert(j.get("exp-1")->state==AdoptionState::RolledBack); return 0; }
