#include "jarvis/core/affective_learning.hpp"
#include "jarvis/core/brain.hpp"

#include <cassert>
#include <cmath>
#include <iostream>

using namespace jarvis::core;

int main() {
    AffectiveLearningModel learner;
    const auto initial = learner.appraisal();
    const AffectiveSignal signal{0.8, 0.9, 0.8, 0.9, 0.7, 0.2};
    const auto modulated = learner.modulate(signal);
    assert(modulated.prediction_error >= 0.0 && modulated.prediction_error <= 1.0);
    assert(modulated.outcome >= -1.0 && modulated.outcome <= 1.0);

    AffectiveState before{};
    AffectiveState after{};
    after.valence = -0.5;
    learner.learn(signal, before, after, -0.9);
    const auto learned = learner.appraisal();
    assert(learner.updates() == 1);
    assert(std::isfinite(learned.error_weight));
    assert(learned.error_weight >= 0.0 && learned.error_weight <= 2.0);
    assert(learned.uncertainty_weight >= 0.0 && learned.uncertainty_weight <= 2.0);
    assert(learned.error_weight != initial.error_weight || learned.uncertainty_weight != initial.uncertainty_weight);

    const auto path = std::filesystem::temp_directory_path() / "jarvis_affective_decision_suite.bin";
    std::error_code ec;
    std::filesystem::remove(path, ec);
    std::filesystem::remove(path.string() + ".meta", ec);
    Brain brain(path);
    const std::vector<CandidateAction> actions{
        CandidateAction{"safe", 0.4, 0.6, 0.1, 1.0, 0.1, 0.1, 0.2},
        CandidateAction{"risky", 0.8, 0.9, 0.8, 0.2, 0.1, 0.8, 0.8}
    };
    const auto decisions = brain.choose_with_affect(actions);
    assert(decisions.size() == actions.size());
    for (const auto& decision : decisions) assert(std::isfinite(decision.score));

    std::filesystem::remove(path, ec);
    std::filesystem::remove(path.string() + ".meta", ec);
    std::cout << "affective_decision_learning_suite: PASS\n";
    return 0;
}
