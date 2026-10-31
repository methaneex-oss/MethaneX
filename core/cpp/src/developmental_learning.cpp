#include "jarvis/core/developmental_learning.hpp"

#include <algorithm>
#include <cmath>

namespace jarvis::core {
namespace {
std::string association_id(const std::string& left, const std::string& right) {
    return left + '\x1f' + right;
}
std::string strategy_id(const std::string& context, const std::string& action) {
    return context + '\x1f' + action;
}
}

double DevelopmentalLearning::bounded(double value) noexcept {
    return std::clamp(std::isfinite(value) ? value : 0.0, -1.0, 1.0);
}

double DevelopmentalLearning::learning_rate(const LearningSignal& signal) noexcept {
    const double error = std::clamp(std::abs(signal.prediction_error), 0.0, 1.0);
    const double reward = std::clamp(std::abs(signal.reward), 0.0, 1.0);
    const double salience = std::clamp(signal.salience, 0.0, 1.0);
    const double novelty = std::clamp(signal.novelty, 0.0, 1.0);
    return std::clamp(0.10 + 0.35 * error + 0.25 * reward + 0.20 * salience + 0.10 * novelty, 0.05, 0.95);
}

void DevelopmentalLearning::observe_association(std::string left, std::string right, const LearningSignal& signal) {
    if (left.empty() || right.empty()) return;
    const double rate = learning_rate(signal);
    const double evidence = bounded(signal.reward - signal.prediction_error);
    auto& association = associations_[association_id(left, right)];
    if (association.observations == 0) {
        association.left = std::move(left);
        association.right = std::move(right);
        association.strength = evidence * rate;
    } else {
        association.strength = bounded(association.strength + rate * (evidence - association.strength));
    }
    ++association.observations;
}

void DevelopmentalLearning::observe_strategy(std::string context, std::string action, const LearningSignal& signal) {
    if (context.empty() || action.empty()) return;
    const double rate = learning_rate(signal);
    const double target = bounded(signal.reward - signal.prediction_error);
    auto& strategy = strategies_[strategy_id(context, action)];
    if (strategy.uses == 0) {
        strategy.context = std::move(context);
        strategy.action = std::move(action);
        strategy.value = target;
        strategy.confidence = rate;
    } else {
        strategy.value = bounded(strategy.value + rate * (target - strategy.value));
        strategy.confidence = std::clamp(strategy.confidence + rate * (1.0 - strategy.confidence), 0.0, 1.0);
    }
    ++strategy.uses;
}

std::vector<LearnedAssociation> DevelopmentalLearning::associations() const {
    std::vector<LearnedAssociation> result;
    result.reserve(associations_.size());
    for (const auto& [_, association] : associations_) result.push_back(association);
    return result;
}

std::vector<LearnedStrategy> DevelopmentalLearning::strategies() const {
    std::vector<LearnedStrategy> result;
    result.reserve(strategies_.size());
    for (const auto& [_, strategy] : strategies_) result.push_back(strategy);
    return result;
}

const LearnedStrategy* DevelopmentalLearning::best_strategy(const std::string& context) const noexcept {
    const LearnedStrategy* best = nullptr;
    for (const auto& [_, strategy] : strategies_) {
        if (strategy.context != context) continue;
        if (best == nullptr || strategy.value > best->value ||
            (strategy.value == best->value && strategy.confidence > best->confidence)) {
            best = &strategy;
        }
    }
    return best;
}

void DevelopmentalLearning::consolidate(double retention_threshold) {
    const double threshold = std::clamp(retention_threshold, 0.0, 1.0);
    for (auto it = associations_.begin(); it != associations_.end();) {
        const double retention = std::clamp(std::abs(it->second.strength) * 0.7 +
                                            std::min(1.0, it->second.observations / 10.0) * 0.3,
                                            0.0, 1.0);
        if (retention < threshold) it = associations_.erase(it); else ++it;
    }
    for (auto it = strategies_.begin(); it != strategies_.end();) {
        const double retention = std::clamp(std::abs(it->second.value) * 0.7 +
                                            std::min(1.0, it->second.uses / 10.0) * 0.3,
                                            0.0, 1.0);
        if (retention < threshold) it = strategies_.erase(it); else ++it;
    }
}

} // namespace jarvis::core
