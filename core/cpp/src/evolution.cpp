#include "jarvis/core/evolution.hpp"

#include <algorithm>
#include <cmath>
#include <utility>

namespace jarvis::core {

EvolutionModel::EvolutionModel(EvolutionPolicy policy) : policy_(policy) {
    if (!std::isfinite(policy_.proposal_step_fraction) || policy_.proposal_step_fraction < 0.0) policy_.proposal_step_fraction = 0.10;
    if (!std::isfinite(policy_.minimum_gain) || policy_.minimum_gain < 0.0) policy_.minimum_gain = 0.0;
    if (!std::isfinite(policy_.minimum_confidence) || policy_.minimum_confidence < 0.0 || policy_.minimum_confidence > 1.0) policy_.minimum_confidence = 0.0;
    if (!std::isfinite(policy_.parameter_minimum) || !std::isfinite(policy_.parameter_maximum) || policy_.parameter_minimum > policy_.parameter_maximum) { policy_.parameter_minimum = -1.0; policy_.parameter_maximum = 1.0; }
}
void EvolutionModel::register_parameter(std::string key, double initial) { if (key.empty() || !std::isfinite(initial)) return; initial = std::clamp(initial, policy_.parameter_minimum, policy_.parameter_maximum); const std::string stable_key = key; parameters_.try_emplace(stable_key, StrategyParameter{stable_key, initial, 0.0, 0, initial, initial}); }
void EvolutionModel::observe_fitness(const std::string& key, double fitness) { auto it = parameters_.find(key); if (it == parameters_.end() || !std::isfinite(fitness)) return; auto& p = it->second; const double value = std::clamp(fitness, -1.0, 1.0); p.fitness = (p.fitness * static_cast<double>(p.observations) + value) / static_cast<double>(p.observations + 1); ++p.observations; }
std::vector<EvolutionProposal> EvolutionModel::propose() const { std::vector<EvolutionProposal> result; for (const auto& [key, p] : parameters_) { if (p.observations < policy_.minimum_observations) continue; const double confidence = 1.0 - std::exp(-static_cast<double>(p.observations) / 8.0); const double magnitude = std::clamp(std::abs(p.fitness) * policy_.proposal_step_fraction, 0.0, std::abs(policy_.parameter_maximum - policy_.parameter_minimum)); const double direction = p.fitness >= 0.0 ? 1.0 : -1.0; const double proposed = std::clamp(p.value + direction * magnitude, policy_.parameter_minimum, policy_.parameter_maximum); const double gain = std::abs(p.fitness) * magnitude; if (gain > policy_.minimum_gain && proposed != p.value && confidence >= policy_.minimum_confidence) result.push_back(EvolutionProposal{key, p.value, proposed, gain, confidence}); } return result; }
EvolutionEvaluation EvolutionModel::evaluate(const EvolutionProposal& proposal) const { const auto it = parameters_.find(proposal.key); if (it == parameters_.end() || !std::isfinite(proposal.current) || !std::isfinite(proposal.proposed) || !std::isfinite(proposal.expected_gain) || !std::isfinite(proposal.confidence)) return {}; EvolutionEvaluation result; result.gain = proposal.expected_gain; result.confidence = proposal.confidence; result.improvement = proposal.expected_gain > policy_.minimum_gain && proposal.proposed != proposal.current && proposal.current == it->second.value; result.eligible = result.improvement && proposal.confidence >= policy_.minimum_confidence; return result; }
bool EvolutionModel::adopt(const EvolutionProposal& proposal) { const auto evaluation = evaluate(proposal); if (!evaluation.eligible) return false; auto& parameter = parameters_.at(proposal.key); parameter.previous_value = parameter.value; parameter.value = std::clamp(proposal.proposed, policy_.parameter_minimum, policy_.parameter_maximum); return parameter.value != parameter.previous_value; }
bool EvolutionModel::rollback(const std::string& key) { auto it = parameters_.find(key); if (it == parameters_.end() || it->second.previous_value == it->second.value) return false; std::swap(it->second.value, it->second.previous_value); return true; }
bool EvolutionModel::restore_baseline(const std::string& key) noexcept { auto it = parameters_.find(key); if (it == parameters_.end() || !std::isfinite(it->second.baseline)) return false; it->second.value = it->second.baseline; it->second.previous_value = it->second.baseline; return true; }
const StrategyParameter* EvolutionModel::parameter(const std::string& key) const noexcept { const auto it = parameters_.find(key); return it == parameters_.end() ? nullptr : &it->second; }
} // namespace jarvis::core
