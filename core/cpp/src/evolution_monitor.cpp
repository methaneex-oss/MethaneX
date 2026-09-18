#include "jarvis/core/evolution_monitor.hpp"
#include <cmath>
namespace jarvis::core {
EvolutionMonitor::EvolutionMonitor(EvolutionMonitorPolicy policy):policy_(policy){if(!std::isfinite(policy_.maximum_fitness_drop)||policy_.maximum_fitness_drop<0.0)policy_.maximum_fitness_drop=0.05;}
EvolutionMonitorSnapshot EvolutionMonitor::observe(const std::string& id,double baseline,double observed,std::size_t observations) const noexcept { EvolutionMonitorSnapshot r{id,baseline,observed,observations,EvolutionMonitorState::Healthy}; if(id.empty()||!std::isfinite(baseline)||!std::isfinite(observed)){r.state=EvolutionMonitorState::RollbackRequired;return r;} if(observations<policy_.minimum_observations)return r; if(observed<baseline-policy_.maximum_fitness_drop)r.state=EvolutionMonitorState::RollbackRequired; else if(observed<baseline)r.state=EvolutionMonitorState::Degraded; return r; }
} // namespace jarvis::core
