#pragma once

#include "jarvis/core/evolution_experiment.hpp"
#include "jarvis/core/evolution_history.hpp"

#include <cstdint>
#include <mutex>
#include <string>
#include <unordered_map>
#include <vector>

namespace jarvis::core {

enum class AdoptionState { Pending, Adopted, Rejected, RolledBack };

struct AdoptionRecord {
    std::string experiment_id;
    std::string parameter_key;
    std::string parent_experiment_id;
    AdoptionState state{AdoptionState::Pending};
    std::uint64_t revision{0};
    double baseline_fitness{0.0};
    double candidate_fitness{0.0};
    double confidence{0.0};
    std::string reason;
};

class EvolutionAdoptionJournal {
public:
    bool stage(const EvolutionExperiment& experiment);
    bool commit(const std::string& experiment_id, std::string reason = "adopted");
    bool reject(const std::string& experiment_id, std::string reason = "rejected");
    bool rollback(const std::string& experiment_id, std::string reason = "rolled_back");
    AdoptionRecord* get(const std::string& experiment_id) noexcept;
    const AdoptionRecord* get(const std::string& experiment_id) const noexcept;
    std::vector<AdoptionRecord> records() const;

private:
    mutable std::mutex mutex_;
    std::unordered_map<std::string, AdoptionRecord> records_;
    std::uint64_t next_revision_{1};
};

} // namespace jarvis::core
