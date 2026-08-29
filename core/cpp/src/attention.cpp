#include "jarvis/core/attention.hpp"

#include <algorithm>

namespace jarvis::core {

namespace {

double normalized_weight(double value) noexcept {
    return std::max(0.0, value);
}

double adaptive_component(double feature, double weight, double total_weight) noexcept {
    if (total_weight <= 0.0) return 0.0;
    return std::clamp(feature, 0.0, 1.0) * normalized_weight(weight) / total_weight;
}

} // namespace

AttentionSignal AttentionModel::score(const Event& event, double novelty, double strongest_belief) const {
    const double uncertainty = 1.0 - std::clamp(strongest_belief, 0.0, 1.0);
    double urgency = 0.0;
    if (const auto it = event.data.find("urgency"); it != event.data.end()) {
        if (const auto p = std::get_if<double>(&it->second)) urgency = std::clamp(*p, 0.0, 1.0);
        else if (const auto p = std::get_if<std::int64_t>(&it->second)) urgency = std::clamp(static_cast<double>(*p), 0.0, 1.0);
        else if (const auto p = std::get_if<bool>(&it->second)) urgency = *p ? 1.0 : 0.0;
    }
    const double total = normalized_weight(policy_.novelty_weight)
        + normalized_weight(policy_.uncertainty_weight)
        + normalized_weight(policy_.urgency_weight);
    const double salience = std::clamp(
        adaptive_component(novelty, policy_.novelty_weight, total)
        + adaptive_component(uncertainty, policy_.uncertainty_weight, total)
        + adaptive_component(urgency, policy_.urgency_weight, total), 0.0, 1.0);
    return AttentionSignal{event.kind, salience, novelty, uncertainty, urgency};
}

std::vector<AttentionSignal> AttentionModel::focus(const std::vector<Event>& events,
                                                    double strongest_belief) const {
    std::vector<AttentionSignal> result;
    result.reserve(events.size());
    for (const auto& event : events) result.push_back(score(event, 1.0, strongest_belief));
    std::sort(result.begin(), result.end(), [](const auto& a, const auto& b) {
        return a.salience > b.salience;
    });
    return result;
}

void AttentionModel::reinforce(const AttentionSignal& signal, double reward) {
    const double r = std::clamp(reward, 0.0, 1.0);
    if (r <= 0.0) return;
    policy_.novelty_weight += r * signal.novelty;
    policy_.uncertainty_weight += r * signal.uncertainty;
    policy_.urgency_weight += r * signal.urgency;
}

void AttentionModel::suppress(const AttentionSignal& signal, double penalty) {
    const double p = std::clamp(penalty, 0.0, 1.0);
    if (p <= 0.0) return;
    policy_.novelty_weight = std::max(0.0, policy_.novelty_weight - p * signal.novelty);
    policy_.uncertainty_weight = std::max(0.0, policy_.uncertainty_weight - p * signal.uncertainty);
    policy_.urgency_weight = std::max(0.0, policy_.urgency_weight - p * signal.urgency);
}

AttentionPolicy AttentionModel::policy() const noexcept {
    return policy_;
}

} // namespace jarvis::core
