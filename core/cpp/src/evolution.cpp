#include "jarvis/core/evolution.hpp"

#include <algorithm>
#include <cmath>
#include <utility>

namespace jarvis::core {

void EvolutionModel::register_parameter(std::string key, double initial) {
    if (key.empty() || !std::isfinite(initial)) return;
    initial = std::clamp(initial, -1.0, 1.0);
    const std::string stable_key = key;
    parameters_.try_emplace(stable_key,
                            StrategyParameter{stable_key, initial, 0.0, 0, initial, initial});
}

void EvolutionModel::observe_fitness(const std::string& key, double fitness) {
    auto it = parameters_.find(key);
    if (it == parameters_.end() || !std::isfinite(fitness)) return;
    auto& p = it->second;
    const double value = std::clamp(fitness, -1.0, 1.0);
    p.fitness = (p.fitness * static_cast<double>(p.observations) + value) /
                static_cast<double>(p.observations + 1);
    ++p.observations;
}

std::vector<EvolutionProposal> EvolutionModel::propose() const {
    std::vector<EvolutionProposal> result;
    for (const auto& [key, p] : parameters_) {
        if (p.observations < 2) continue;
        const double confidence = 1.0 - std::exp(-static_cast<double>(p.observations) / 8.0);
        const double magnitude = std::clamp(std::abs(p.fitness) * 0.10, 0.005, 0.10);
        const double direction = p.fitness >= 0.0 ? 1.0 : -1.0;
        const double proposed = std::clamp(p.value + direction * magnitude, -1.0, 1.0);
        const double gain = std::abs(p.fitness) * magnitude;
        if (gain > 0.0) {
            result.push_back(EvolutionProposal{key, p.value, proposed, gain, confidence});
        }
    }
    return result;
}

bool EvolutionModel::adopt(const EvolutionProposal& proposal) {
    auto it = parameters_.find(proposal.key);
    if (it == parameters_.end() || !std::isfinite(proposal.proposed) ||
        !std::isfinite(proposal.expected_gain) || !std::isfinite(proposal.confidence)) return false;
    if (proposal.current != it->second.value || proposal.expected_gain <= 0.0 ||
        proposal.confidence <= 0.0) return false;
    it->second.previous_value = it->second.value;
    it->second.value = std::clamp(proposal.proposed, -1.0, 1.0);
    return true;
}

bool EvolutionModel::rollback(const std::string& key) {
    auto it = parameters_.find(key);
    if (it == parameters_.end() || it->second.previous_value == it->second.value) return false;
    std::swap(it->second.value, it->second.previous_value);
    return true;
}

const StrategyParameter* EvolutionModel::parameter(const std::string& key) const noexcept {
    const auto it = parameters_.find(key);
    return it == parameters_.end() ? nullptr : &it->second;
}

} // namespace jarvis::core
