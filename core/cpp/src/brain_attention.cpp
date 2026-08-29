#include "jarvis/core/brain.hpp"

#include <mutex>

namespace jarvis::core {

std::vector<AttentionContext> Brain::attention_focus(std::size_t limit) const {
    std::shared_lock lock(mutex_);
    return attention_memory_.focus(limit);
}

void Brain::reinforce_attention(const std::string& key, double reward) {
    std::unique_lock lock(mutex_);
    attention_memory_.reinforce(key, reward);
}

void Brain::suppress_attention(const std::string& key, double penalty) {
    std::unique_lock lock(mutex_);
    attention_memory_.suppress(key, penalty);
}

} // namespace jarvis::core
