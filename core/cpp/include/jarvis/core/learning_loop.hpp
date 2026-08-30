#pragma once

#include "adaptation.hpp"
#include "evolution.hpp"

#include <cstddef>
#include <string>
#include <vector>

namespace jarvis::core {

struct LearningFeedback {
    std::string key;
    double predicted{0.0};
    double actual{0.0};
    double fitness{0.0};
};

struct LearningCycle {
    AdaptiveMetric adaptation{};
    double confidence{0.0};
    std::vector<EvolutionProposal> proposals;
    std::size_t adopted{0};
};

class LearningLoop {
public:
    LearningCycle process(const LearningFeedback& feedback,
                          AdaptationModel& adaptation,
                          EvolutionModel& evolution) const;
};

} // namespace jarvis::core
