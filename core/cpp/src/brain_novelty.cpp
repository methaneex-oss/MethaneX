#include "jarvis/core/brain.hpp"

#include <algorithm>

namespace jarvis::core {

double Brain::compute_novelty(const Event& event, const std::vector<Event>& history) {
    if (event.data.empty()) return 0.0;
    if (history.empty()) return 1.0;

    double best_similarity = 0.0;
    for (const auto& previous : history) {
        if (previous.data.empty()) continue;
        std::size_t matches = 0;
        std::size_t comparable = 0;
        for (const auto& [key, value] : event.data) {
            const auto it = previous.data.find(key);
            if (it == previous.data.end()) continue;
            ++comparable;
            if (it->second == value) ++matches;
        }
        if (comparable != 0) {
            best_similarity = std::max(
                best_similarity,
                static_cast<double>(matches) / static_cast<double>(comparable));
        }
    }
    return std::clamp(1.0 - best_similarity, 0.0, 1.0);
}

} // namespace jarvis::core
