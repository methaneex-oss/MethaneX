#pragma once

#include "jarvis/core/evolution_canary.hpp"
#include "jarvis/core/evolution_history.hpp"

#include <string>

namespace jarvis::core {

struct RollbackRecord {
    std::string experiment_id;
    std::string parameter_key;
    std::string reason;
    double observed_delta{0.0};
};

class EvolutionRollback {
public:
    static bool should_rollback(const CanaryDecision& decision) noexcept;
    static bool record(EvolutionHistory& history, const RollbackRecord& rollback);
};

} // namespace jarvis::core
