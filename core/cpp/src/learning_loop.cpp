#include "jarvis/core/learning_loop.hpp"

#include <algorithm>
#include <cmath>

namespace jarvis::core {

LearningCycle LearningLoop::process(const LearningFeedback& feedback,
                                    AdaptationModel& adaptation,
                                    EvolutionModel& evolution) const {
    LearningCycle cycle{};
    if (feedback.key.empty() || !std::isfinite(feedback.predicted) ||
        !std::isfinite(feedback.actual) || !std::isfinite(feedback.fitness)) {
        return cycle;
    }

    cycle.adaptation = adaptation.observe(feedback.key, feedback.predicted, feedback.actual);
    cycle.confidence = adaptation.confidence(feedback.key);
    evolution.observe_fitness(feedback.key, std::clamp(feedback.fitness, -1.0, 1.0));
    cycle.proposals = evolution.propose();

    // Adoption is deliberately gated by measured confidence and positive expected gain.
    // The loop never invents a strategy or bypasses the evolution model's validation.
    for (const auto& proposal : cycle.proposals) {
        if (proposal.key != feedback.key || proposal.confidence < 0.75 || proposal.expected_gain <= 0.0)
            continue;
        if (evolution.adopt(proposal)) ++cycle.adopted;
        break;
    }
    return cycle;
}

} // namespace jarvis::core
