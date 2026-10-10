#pragma once

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <string>
#include <unordered_map>
#include <vector>

namespace jarvis::core {

struct LearningSignal {
    double prediction_error{0.0};
    double reward{0.0};
    double salience{0.0};
    double novelty{0.0};
    double affective_significance{0.0};

    LearningSignal() = default;
    LearningSignal(double prediction_error_value,
                   double reward_value,
                   double salience_value,
                   double novelty_value)
        : prediction_error(prediction_error_value),
          reward(reward_value),
          salience(salience_value),
          novelty(novelty_value),
          affective_significance(derive_affective_significance(
              prediction_error_value, reward_value, salience_value, novelty_value)) {}

    LearningSignal(double prediction_error_value,
                   double reward_value,
                   double salience_value,
                   double novelty_value,
                   double affective_significance_value)
        : prediction_error(prediction_error_value),
          reward(reward_value),
          salience(salience_value),
          novelty(novelty_value),
          affective_significance(affective_significance_value) {}

private:
    static double derive_affective_significance(double prediction_error_value,
                                                double reward_value,
                                                double salience_value,
                                                double novelty_value) noexcept {
        const double error = std::clamp(std::isfinite(prediction_error_value) ? std::abs(prediction_error_value) : 0.0, 0.0, 1.0);
        const double reward_abs = std::clamp(std::isfinite(reward_value) ? std::abs(reward_value) : 0.0, 0.0, 1.0);
        const double salience_abs = std::clamp(std::isfinite(salience_value) ? salience_value : 0.0, 0.0, 1.0);
        const double novelty_abs = std::clamp(std::isfinite(novelty_value) ? novelty_value : 0.0, 0.0, 1.0);
        return std::clamp(0.35 * error + 0.25 * reward_abs + 0.25 * salience_abs + 0.15 * novelty_abs, 0.0, 1.0);
    }
};

struct LearnedAssociation {
    std::string left;
    std::string right;
    double strength{0.0};
    std::uint64_t observations{0};
};

struct LearnedStrategy {
    std::string context;
    std::string action;
    double value{0.0};
    double confidence{0.0};
    std::uint64_t uses{0};
};

class DevelopmentalLearning {
public:
    void observe_association(std::string left, std::string right, const LearningSignal& signal);
    void observe_strategy(std::string context, std::string action, const LearningSignal& signal);

    std::vector<LearnedAssociation> associations() const;
    std::vector<LearnedStrategy> strategies() const;

    const LearnedStrategy* best_strategy(const std::string& context) const noexcept;
    const LearnedStrategy* best_related_strategy(const std::string& context,
                                                 double minimum_similarity = 0.5) const;

    void consolidate(double retention_threshold = 0.05);

private:
    static double learning_rate(const LearningSignal& signal) noexcept;
    static double bounded(double value) noexcept;

    std::unordered_map<std::string, LearnedAssociation> associations_;
    std::unordered_map<std::string, LearnedStrategy> strategies_;
};

} // namespace jarvis::core
