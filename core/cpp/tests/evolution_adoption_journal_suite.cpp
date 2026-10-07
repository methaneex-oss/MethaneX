#include "jarvis/core/evolution_adoption_journal.hpp"
#include "jarvis/core/evolution_history.hpp"
#include <cassert>
using namespace jarvis::core;
int main(){ EvolutionAdoptionJournal j; EvolutionExperiment e{}; e.id="exp-1"; e.proposal.key="candidate"; e.baseline_fitness=0.5; e.candidate_fitness=0.8; e.confidence=0.9; assert(j.stage(e)); auto staged=j.get("exp-1"); assert(staged && staged->state==AdoptionState::Pending); assert(j.commit("exp-1")); assert(j.commit("exp-1")); auto adopted=j.get("exp-1"); assert(adopted && adopted->state==AdoptionState::Adopted); assert(j.rollback("exp-1")); assert(j.rollback("exp-1")); auto rolled=j.get("exp-1"); assert(rolled && !j.stage(e)); assert(rolled && rolled->state==AdoptionState::RolledBack);
 EvolutionHistory history;
 EvolutionHistoryRecord record{"exp-history", "candidate", EvolutionRecordAction::Adopted,
                              ExperimentOutcome::Improved, 0.5, 0.8, 0.9, 0, "adopted", {}};
 assert(history.append(record));
 assert(history.append(record));
 assert(history.size() == 1);
 return 0; }
