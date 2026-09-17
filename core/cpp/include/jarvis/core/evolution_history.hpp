#pragma once

#include "jarvis/core/evolution_experiment.hpp"

#include <cstdint>
#include <mutex>
#include <string>
#include <vector>

namespace jarvis::core {

enum class EvolutionRecordAction { Evaluated, Adopted, Rejected, RolledBack };

struct EvolutionHistoryRecord {
    std::string experiment_id;
    std::string parameter_key;
    EvolutionRecordAction action{EvolutionRecordAction::Evaluated};
    ExperimentOutcome outcome{ExperimentOutcome::Pending};
    double baseline_fitness{0.0};
    double candidate_fitness{0.0};
    double confidence{0.0};
    std::uint64_t sequence{0};
};

class EvolutionHistory {
public:
    bool append(EvolutionHistoryRecord record);
    std::vector<EvolutionHistoryRecord> records() const;
    std::vector<EvolutionHistoryRecord> for_parameter(const std::string& key) const;
    std::size_t size() const;

private:
    mutable std::mutex mutex_;
    std::vector<EvolutionHistoryRecord> records_;
    std::uint64_t next_sequence_{1};
};

} // namespace jarvis::core
