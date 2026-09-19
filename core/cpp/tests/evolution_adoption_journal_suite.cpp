#include "jarvis/core/evolution_adoption_journal.hpp"
#include <cassert>
using namespace jarvis::core;
int main(){ EvolutionAdoptionJournal j; EvolutionExperiment e{}; e.id="exp-1"; e.proposal.key="candidate"; e.baseline_fitness=0.5; e.candidate_fitness=0.8; e.confidence=0.9; assert(j.stage(e)); auto staged=j.get("exp-1"); assert(staged && staged->state==AdoptionState::Pending); assert(j.commit("exp-1")); assert(j.commit("exp-1")); auto adopted=j.get("exp-1"); assert(adopted && adopted->state==AdoptionState::Adopted); assert(j.rollback("exp-1")); assert(j.rollback("exp-1")); auto rolled=j.get("exp-1"); assert(rolled && rolled->state==AdoptionState::RolledBack); return 0; }
