#include "jarvis/core/evolution.hpp"

#include <algorithm>
#include <cmath>

namespace jarvis::core {

void EvolutionModel::register_parameter(std::string key, double initial) {
    StrategyParameter parameter{key, initial, 0.0, 0};
    parameters_.try_emplace(std::move(key), parameter);
}

void EvolutionModel::observe_fitness(const std::string& key, double fitness) {
    auto it = parameters_.find(key);
    if (it == parameters_.end()) return;
    auto& p = it->second;
    const double value = std::clamp(fitness, -1.0, 1.0);
    p.fitness = (p.fitness * static_cast<double>(p.observations) + value) /
                static_cast<double>(p.observations + 1);
    ++p.observations;
}

std::vector<EvolutionProposal> EvolutionModel::propose() const {
    std::vector<EvolutionProposal> result;
    for (const auto& [key, p] : parameters_) {
        if (p.observations == 0) continue;
        const double direction = p.fitness >= 0.0 ? 1.0 : -1.0;
        const double magnitude = std::clamp(std::abs(p.fitness) * 0.10, 0.005, 0.10);
        const double proposed = p.value + direction * magnitude;
        result.push_back(EvolutionProposal{key, p.value, proposed, std::abs(p.fitness) * magnitude});
    }
    return result;
}

bool EvolutionModel::adopt(const EvolutionProposal& proposal) {
    auto it = parameters_.find(proposal.key);
    if (it == parameters_.end()) return false;
    it->second.value = proposal.proposed;
    return true;
}

const StrategyParameter* EvolutionModel::parameter(const std::string& key) const noexcept {
    const auto it = parameters_.find(key);
    return it == parameters_.end() ? nullptr : &it->second;
}

} // namespace jarvis::core
