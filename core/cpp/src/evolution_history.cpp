#include "jarvis/core/evolution_history.hpp"

#include <cmath>

namespace jarvis::core {

bool EvolutionHistory::append(EvolutionHistoryRecord record) {
    if (record.experiment_id.empty() || record.parameter_key.empty()) return false;
    if (!std::isfinite(record.baseline_fitness) || !std::isfinite(record.candidate_fitness) ||
        !std::isfinite(record.confidence) || record.confidence < 0.0 || record.confidence > 1.0) return false;

    std::lock_guard lock(mutex_);
    record.sequence = next_sequence_++;
    records_.push_back(std::move(record));
    return true;
}

std::vector<EvolutionHistoryRecord> EvolutionHistory::records() const {
    std::lock_guard lock(mutex_);
    return records_;
}

std::vector<EvolutionHistoryRecord> EvolutionHistory::for_parameter(const std::string& key) const {
    std::lock_guard lock(mutex_);
    std::vector<EvolutionHistoryRecord> result;
    for (const auto& record : records_) {
        if (record.parameter_key == key) result.push_back(record);
    }
    return result;
}

std::vector<EvolutionHistoryRecord> EvolutionHistory::for_experiment(const std::string& id) const {
    std::lock_guard lock(mutex_);
    std::vector<EvolutionHistoryRecord> result;
    for (const auto& record : records_) {
        if (record.experiment_id == id) result.push_back(record);
    }
    return result;
}

std::size_t EvolutionHistory::size() const {
    std::lock_guard lock(mutex_);
    return records_.size();
}

} // namespace jarvis::core
