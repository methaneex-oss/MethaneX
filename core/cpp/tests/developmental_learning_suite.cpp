#include "jarvis/core/developmental_learning.hpp"

#include <cassert>
#include <cmath>
#include <iostream>
#include <limits>

using namespace jarvis::core;

int main() {
    DevelopmentalLearning learning;

    learning.observe_strategy("context", "action_a", LearningSignal{0.0, 1.0, 0.8, 0.2});
    learning.observe_strategy("context", "action_b", LearningSignal{1.0, -1.0, 0.8, 0.2});

    const auto* best = learning.best_strategy("context");
    assert(best != nullptr);
    assert(best->action == "action_a");
    assert(best->value > 0.0);

    learning.observe_association("a", "b", LearningSignal{0.0, 1.0, 1.0, 1.0});
    learning.observe_association("a", "b", LearningSignal{1.0, -1.0, 1.0, 1.0});

    const auto associations = learning.associations();
    assert(associations.size() == 1);
    assert(associations.front().observations == 2);
    assert(std::isfinite(associations.front().strength));

    // Affective significance is a continuous learning modifier, not an
    // emotion-to-action rule. With identical evidence, stronger internal
    // significance produces a larger initial update.
    DevelopmentalLearning low_affect;
    DevelopmentalLearning high_affect;
    const LearningSignal low{0.2, 0.6, 0.4, 0.3, 0.0};
    const LearningSignal high{0.2, 0.6, 0.4, 0.3, 1.0};
    low_affect.observe_association("experience", "outcome", low);
    high_affect.observe_association("experience", "outcome", high);

    const auto low_associations = low_affect.associations();
    const auto high_associations = high_affect.associations();
    assert(low_associations.size() == 1);
    assert(high_associations.size() == 1);
    assert(std::abs(high_associations.front().strength) >
           std::abs(low_associations.front().strength));

    low_affect.observe_strategy("context", "action", low);
    high_affect.observe_strategy("context", "action", high);
    assert(high_affect.best_strategy("context") != nullptr);
    assert(low_affect.best_strategy("context") != nullptr);
    assert(high_affect.best_strategy("context")->confidence >
           low_affect.best_strategy("context")->confidence);

    // Prediction error should increase adaptation strength without turning
    // a positive outcome into a negative learned value.
    DevelopmentalLearning surprising_success;
    surprising_success.observe_strategy("surprise", "successful-action", LearningSignal{1.0, 1.0, 0.8, 0.2});
    const auto* surprising = surprising_success.best_strategy("surprise");
    assert(surprising != nullptr);
    assert(surprising->value > 0.0);

    // Malformed/non-finite appraisal values must not poison persistent
    // learning state. They are ignored as modifiers, and learned values stay
    // finite so later valid experience can still update them.
    DevelopmentalLearning resilient_to_invalid_signals;
    const double nan = std::numeric_limits<double>::quiet_NaN();
    const double infinity = std::numeric_limits<double>::infinity();
    resilient_to_invalid_signals.observe_strategy(
        "sensor calibration", "recalibrate",
        LearningSignal{nan, 0.8, infinity, nan, nan});
    const auto* after_invalid_signal =
        resilient_to_invalid_signals.best_strategy("sensor calibration");
    assert(after_invalid_signal != nullptr);
    assert(std::isfinite(after_invalid_signal->value));
    assert(std::isfinite(after_invalid_signal->confidence));
    assert(after_invalid_signal->value > 0.0);
    resilient_to_invalid_signals.observe_strategy(
        "sensor calibration", "recalibrate",
        LearningSignal{0.2, -0.5, 0.4, 0.1, 0.2});
    const auto* after_valid_signal =
        resilient_to_invalid_signals.best_strategy("sensor calibration");
    assert(after_valid_signal != nullptr);
    assert(std::isfinite(after_valid_signal->value));
    assert(std::isfinite(after_valid_signal->confidence));
    assert(after_valid_signal->uses == 2);

    resilient_to_invalid_signals.observe_association(
        "sensor", "drift", LearningSignal{nan, infinity, nan, nan, nan});
    const auto resilient_associations =
        resilient_to_invalid_signals.associations();
    assert(resilient_associations.size() == 1);
    assert(std::isfinite(resilient_associations.front().strength));

    // Related retrieval must prefer genuinely positive learned value over a
    // more similar but strongly negative strategy. Negative value remains
    // usable when it is the only relevant evidence, but must not outrank
    // positive evidence merely because of magnitude.
    DevelopmentalLearning related;
    related.observe_strategy("navigation route", "good-route", LearningSignal{0.0, 1.0, 0.8, 0.2});
    related.observe_strategy("navigation", "bad-route", LearningSignal{1.0, -1.0, 0.8, 0.2});
    const auto* related_best = related.best_related_strategy("navigation route variant");
    assert(related_best != nullptr);
    assert(related_best->action == "good-route");

    // Generalization must be bounded by context similarity. A strategy learned
    // for navigation must not leak into an unrelated task merely because it
    // is the only experience currently stored.
    assert(related.best_related_strategy("orbital cooking", 0.5) == nullptr);

    // If all related experiences were harmful, retrieval must preserve the
    // negative signal and prefer the less harmful alternative rather than
    // treating every negative outcome as a tied zero.
    DevelopmentalLearning negative_only;
    negative_only.observe_strategy("navigation route", "very-bad-route",
                                   LearningSignal{1.0, -1.0, 0.8, 0.2});
    negative_only.observe_strategy("navigation variant", "less-bad-route",
                                   LearningSignal{0.5, -0.3, 0.8, 0.2});
    const auto* least_harmful = negative_only.best_related_strategy("navigation route variant");
    assert(least_harmful != nullptr);
    assert(least_harmful->action == "less-bad-route");

    // Strategy values must change with repeated experience rather than
    // freezing after the first observation. Contradictory evidence should
    // reverse the preference, and later evidence should be able to revise it.
    DevelopmentalLearning changing_experience;
    changing_experience.observe_strategy(
        "bridge repair", "reinforce bridge",
        LearningSignal{0.1, 0.9, 0.7, 0.2});
    const auto* initial_strategy = changing_experience.best_strategy("bridge repair");
    assert(initial_strategy != nullptr);
    assert(initial_strategy->value > 0.0);
    assert(initial_strategy->uses == 1);
    const double initial_confidence = initial_strategy->confidence;

    changing_experience.observe_strategy(
        "bridge repair", "reinforce bridge",
        LearningSignal{0.9, -0.9, 0.7, 0.2});
    const auto* revised_negative = changing_experience.best_strategy("bridge repair");
    assert(revised_negative != nullptr);
    assert(revised_negative->value < 0.0);
    assert(revised_negative->uses == 2);

    changing_experience.observe_strategy(
        "bridge repair", "reinforce bridge",
        LearningSignal{0.8, 0.9, 0.7, 0.2});
    const auto* revised_positive = changing_experience.best_strategy("bridge repair");
    assert(revised_positive != nullptr);
    assert(revised_positive->value > 0.0);
    assert(revised_positive->uses == 3);
    assert(revised_positive->confidence > initial_confidence);

    // Outcome confidence must control both the learned value and the
    // amount of adaptation. A weakly supported success must not be treated
    // like a directly verified one; zero-confidence evidence must not create
    // a strategy or association.
    DevelopmentalLearning reliable_evidence;
    DevelopmentalLearning uncertain_evidence;
    reliable_evidence.observe_strategy(
        "robot arm", "grasp object",
        LearningSignal{0.2, 1.0, 0.5, 0.2, 0.5, 1.0});
    uncertain_evidence.observe_strategy(
        "robot arm", "grasp object",
        LearningSignal{0.2, 1.0, 0.5, 0.2, 0.5, 0.1});
    const auto* reliable_strategy = reliable_evidence.best_strategy("robot arm");
    const auto* uncertain_strategy = uncertain_evidence.best_strategy("robot arm");
    assert(reliable_strategy != nullptr);
    assert(uncertain_strategy != nullptr);
    assert(reliable_strategy->value > uncertain_strategy->value);
    assert(reliable_strategy->confidence > uncertain_strategy->confidence);

    DevelopmentalLearning untrusted_evidence;
    untrusted_evidence.observe_strategy(
        "robot arm", "grasp object",
        LearningSignal{1.0, -1.0, 1.0, 1.0, 1.0, 0.0});
    untrusted_evidence.observe_association(
        "robot arm", "object moved",
        LearningSignal{1.0, 1.0, 1.0, 1.0, 1.0, 0.0});
    assert(untrusted_evidence.strategies().empty());
    assert(untrusted_evidence.associations().empty());

    // Legacy four-field evidence now derives deterministic affective
    // significance from prediction error, reward, salience and novelty.
    const LearningSignal derived{0.9, -0.8, 0.7, 0.6};
    const LearningSignal neutral{0.0, 0.0, 0.0, 0.0};
    assert(derived.affective_significance > neutral.affective_significance);
    assert(derived.affective_significance <= 1.0);

    learning.consolidate(0.05);
    std::cout << "developmental learning suite passed\n";
    return 0;
}
