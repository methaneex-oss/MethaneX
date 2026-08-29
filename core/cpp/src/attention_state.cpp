#include "jarvis/core/attention_state.hpp"

#include <algorithm>
#include <utility>

namespace jarvis::core {

void AttentionState::ingest(const AttentionSignal& signal, std::uint64_t cycle) {
    if (signal.key.empty()) return;
    auto& context = contexts_[signal.key];
    context.key = signal.key;
    const double incoming = std::clamp(signal.salience, 0.0, 1.0);
    context.salience = std::clamp(0.7 * context.salience + 0.3 * incoming, 0.0, 1.0);
    context.priority = std::clamp(
        0.5 * context.priority + 0.5 * (incoming + signal.urgency) * 0.5, 0.0, 1.0);
    context.last_seen = cycle;
    ++context.observations;
}

void AttentionState::reinforce(const std::string& key, double reward) {
    if (key.empty()) return;
    auto it = contexts_.find(key);
    if (it == contexts_.end()) return;
    it->second.priority = std::clamp(it->second.priority + std::clamp(reward, 0.0, 1.0) * 0.2, 0.0, 1.0);
    it->second.salience = std::clamp(it->second.salience + std::clamp(reward, 0.0, 1.0) * 0.1, 0.0, 1.0);
}

void AttentionState::suppress(const std::string& key, double penalty) {
    if (key.empty()) return;
    auto it = contexts_.find(key);
    if (it == contexts_.end()) return;
    const double p = std::clamp(penalty, 0.0, 1.0);
    it->second.priority = std::clamp(it->second.priority * (1.0 - 0.2 * p), 0.0, 1.0);
    it->second.salience = std::clamp(it->second.salience * (1.0 - 0.1 * p), 0.0, 1.0);
}

std::vector<AttentionContext> AttentionState::focus(std::size_t limit) const {
    std::vector<AttentionContext> result;
    result.reserve(contexts_.size());
    for (const auto& [_, context] : contexts_) result.push_back(context);
    std::sort(result.begin(), result.end(), [](const auto& a, const auto& b) {
        const double as = a.salience + a.priority;
        const double bs = b.salience + b.priority;
        return as > bs;
    });
    if (result.size() > limit) result.resize(limit);
    for (auto& context : result) context.focused = true;
    return result;
}

const AttentionContext* AttentionState::get(const std::string& key) const noexcept {
    const auto it = contexts_.find(key);
    return it == contexts_.end() ? nullptr : &it->second;
}

void AttentionState::clear() {
    contexts_.clear();
}

} // namespace jarvis::core
