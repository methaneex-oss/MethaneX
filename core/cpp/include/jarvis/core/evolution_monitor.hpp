#pragma once
#include <cstddef>
#include <string>
namespace jarvis::core {
enum class EvolutionMonitorState { Healthy, Degraded, RollbackRequired };
struct EvolutionMonitorPolicy { double maximum_fitness_drop{0.05}; std::size_t minimum_observations{3}; };
struct EvolutionMonitorSnapshot { std::string experiment_id; double baseline_fitness{0.0}; double observed_fitness{0.0}; std::size_t observations{0}; EvolutionMonitorState state{EvolutionMonitorState::Healthy}; };
class EvolutionMonitor { public: explicit EvolutionMonitor(EvolutionMonitorPolicy policy = {}); EvolutionMonitorSnapshot observe(const std::string& experiment_id,double baseline_fitness,double observed_fitness,std::size_t observations) const noexcept; private: EvolutionMonitorPolicy policy_; };
} // namespace jarvis::core
