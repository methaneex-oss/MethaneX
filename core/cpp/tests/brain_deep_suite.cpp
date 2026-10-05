#include "jarvis/core/brain.hpp"

#include <cassert>
#include <cmath>
#include <cstdint>
#include <filesystem>
#include <string>
#include <vector>

using namespace jarvis::core;

static Event event(std::uint64_t seq, std::string source, std::string kind,
                   std::string topic, double value) {
    return Event{seq, seq, std::move(source), std::move(kind),
                 {{"topic", Scalar{std::move(topic)}}, {"value", Scalar{value}}}};
}

int main() {
    const auto root = std::filesystem::temp_directory_path() / "jarvis_brain_deep_suite";
    std::error_code ec;
    std::filesystem::remove_all(root, ec);
    std::filesystem::create_directories(root, ec);

    Brain brain(root / "continuity.bin");
    const auto observed = brain.observe(event(0, "test", "observation", "persistent", 42.0));
    assert(observed.event.sequence == 1);
    assert(observed.novelty == 1.0);
    assert(brain.memory().size() == 1);

    assert(brain.learn(Evidence{"trusted", "temperature", Scalar{25.0}, 0.9}) >= 0.0);
    assert(brain.knowledge_source("trusted") != nullptr);

    const std::vector<CandidateAction> actions{{"safe", 0.9, 0.9, 0.05, 0.9}, {"risky", 0.95, 0.2, 0.9, 0.8}};
    const auto decisions = brain.choose(actions);
    assert(!decisions.empty());
    assert(!brain.plan(actions, 4).steps.empty());

    const auto assessments = brain.assess_actions(decisions, ActionConstraints{0.5, false});
    assert(!assessments.empty());
    const auto& executable = assessments.front();
    const auto action_result = brain.execute_action(
        executable,
        [](const CandidateAction& action) { return action.name == "safe"; },
        [](const CandidateAction& action) { return action.name == "safe"; });
    assert(action_result.authorized);
    assert(action_result.executed);
    assert(action_result.verified);
    assert(brain.memory().by_kind("action_outcome", 1).size() == 1);
    assert(brain.memory().by_kind("learning", 1).size() == 1);

    const auto affect_before_failure = brain.affective_state();
    const auto learning_before_failure = brain.affective_learning_updates();
    const auto failed_action = brain.execute_action(
        executable,
        [](const CandidateAction&) { return false; },
        [](const CandidateAction&) { return false; });
    assert(failed_action.authorized);
    assert(!failed_action.executed);
    assert(brain.memory().by_kind("action_outcome", 2).size() == 2);

    // Failed execution is part of the cognitive experience stream. It must
    // reach affective processing and affective learning, not remain test-local.
    const auto affect_after_failure = brain.affective_state();
    assert(std::isfinite(affect_after_failure.valence));
    assert(std::isfinite(affect_after_failure.tension));
    assert(brain.affective_learning_updates() > learning_before_failure);
    assert(affect_after_failure.valence != affect_before_failure.valence ||
           affect_after_failure.tension != affect_before_failure.tension ||
           affect_after_failure.arousal != affect_before_failure.arousal ||
           affect_after_failure.uncertainty != affect_before_failure.uncertainty);

    // The learned affective appraisal must be visible to future decisions.
    const CandidateAction probe{"probe", 0.0, 1.0, 0.2, 1.0};
    const auto before_decision = brain.choose_with_affect({probe}).front().score;
    brain.observe(event(0, "feedback", "observation", "consequence", -1.0));
    const auto after_decision = brain.choose_with_affect({probe}).front().score;
    assert(std::isfinite(before_decision));
    assert(std::isfinite(after_decision));
    assert(before_decision != after_decision);

    std::filesystem::remove_all(root, ec);
    return 0;
}
