#pragma once

#include <cstdint>
#include <string>
#include <unordered_map>
#include <vector>

namespace jarvis::core {

// DevelopmentalLearning supplies mechanisms for acquiring behavior from experience.
// It deliberately contains no domain-specific "if X then Y" behavioral rules.
struct LearningSignal {
    double prediction_error{0.0};
    double reward{0.0};
    double salience{0.0};
    double novelty{0.0};
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

    // Bounded consolidation prevents unbounded growth while preserving highly
    // salient/repeated experiences. Forgetting is based on learned state, not
    // hard-coded domain meanings.
    void consolidate(double retention_threshold = 0.05);

private:
    static double learning_rate(const LearningSignal& signal) noexcept;
    static double bounded(double value) noexcept;

    std::unordered_map<std::string, LearnedAssociation> associations_;
    std::unordered_map<std::string, LearnedStrategy> strategies_;
};

} // namespace jarvis::core
