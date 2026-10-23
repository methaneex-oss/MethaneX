#include "jarvis/core/developmental_learning.hpp"

#include <algorithm>
#include <cctype>
#include <cmath>
#include <limits>
#include <unordered_set>

namespace jarvis::core {
namespace {
std::string association_id(const std::string& left, const std::string& right) {
    return left + '\x1f' + right;
}
std::string strategy_id(const std::string& context, const std::string& action) {
    return context + '\x1f' + action;
}

std::vector<std::string> context_tokens(const std::string& context) {
    std::vector<std::string> tokens;
    std::string token;
    for (const unsigned char character : context) {
        if (std::isalnum(character) || character == '\'') {
            token.push_back(static_cast<char>(std::tolower(character)));
        } else if (!token.empty()) {
            tokens.push_back(std::move(token));
            token.clear();
        }
    }
    if (!token.empty()) tokens.push_back(std::move(token));
    return tokens;
}

bool has_negation(const std::vector<std::string>& tokens) {
    // Conservative guard: contexts with different polarity should not transfer
    // strategies solely because they share the same descriptive words.
    static const std::unordered_set<std::string> negators{
        "no", "not", "never", "neither", "nor", "without", "cannot", "can't",
        "dont", "don't", "doesnt", "doesn't", "isnt", "isn't", "unsafe",
        "untrue", "false"};
    return std::any_of(tokens.begin(), tokens.end(),
                       [](const std::string& token) { return negators.contains(token); });
}

double context_similarity(const std::string& left, const std::string& right) {
    if (left == right && !left.empty()) return 1.0;
    const auto left_tokens = context_tokens(left);
    const auto right_tokens = context_tokens(right);
    if (has_negation(left_tokens) != has_negation(right_tokens)) return 0.0;
    if (left_tokens.empty() || right_tokens.empty()) return 0.0;

    std::unordered_set<std::string> left_set(left_tokens.begin(), left_tokens.end());
    std::unordered_set<std::string> right_set(right_tokens.begin(), right_tokens.end());
    std::size_t intersection = 0;
    for (const auto& token : left_set) if (right_set.contains(token)) ++intersection;
    const std::size_t union_size = left_set.size() + right_set.size() - intersection;
    return union_size == 0 ? 0.0 : static_cast<double>(intersection) / static_cast<double>(union_size);
}
}

double DevelopmentalLearning::bounded(double value) noexcept {
    return std::clamp(std::isfinite(value) ? value : 0.0, -1.0, 1.0);
}

double DevelopmentalLearning::learning_rate(const LearningSignal& signal) noexcept {
    // Ignore non-finite sensor/appraisal values instead of allowing NaN to
    // poison the learning rate and permanently corrupt stored values.
    const auto unit_signal = [](double value) noexcept {
        return std::clamp(std::isfinite(value) ? value : 0.0, 0.0, 1.0);
    };
    const double error = unit_signal(std::isfinite(signal.prediction_error)
                                         ? std::abs(signal.prediction_error) : 0.0);
    const double reward = unit_signal(std::isfinite(signal.reward)
                                          ? std::abs(signal.reward) : 0.0);
    const double salience = unit_signal(signal.salience);
    const double novelty = unit_signal(signal.novelty);
    const double affect = unit_signal(signal.affective_significance);
    const double reliability = unit_signal(signal.reliability);
    if (reliability <= 0.0) return 0.0;
    const double base_rate = std::clamp(
        0.10 + 0.30 * error + 0.20 * reward + 0.15 * salience +
            0.10 * novelty + 0.15 * affect,
        0.05, 0.95);
    return base_rate * reliability;
}

void DevelopmentalLearning::observe_association(std::string left, std::string right, const LearningSignal& signal) {
    if (left.empty() || right.empty()) return;
    const double rate = learning_rate(signal);
    if (rate <= 0.0) return;
    // Prediction error controls how strongly experience is learned; it is not
    // itself a signed outcome. Keep reward as the learned target so a
    // surprising positive outcome does not become a negative association.
    // Reliability already scales learning_rate(). Applying it to the target
    // as well would discount evidence twice, and the first observation would
    // bypass the learning rate entirely. Keep the outcome target unbiased;
    // confidence and update magnitude carry evidence reliability separately.
    const double evidence = bounded(signal.reward);
    auto& association = associations_[association_id(left, right)];
    if (association.observations == 0) {
        association.left = std::move(left);
        association.right = std::move(right);
        association.strength = evidence * rate;
    } else {
        association.strength = bounded(association.strength + rate * (evidence - association.strength));
    }
    ++association.observations;
}

void DevelopmentalLearning::observe_strategy(std::string context, std::string action, const LearningSignal& signal) {
    if (context.empty() || action.empty()) return;
    const double rate = learning_rate(signal);
    if (rate <= 0.0) return;
    // Prediction error is a learning-strength signal, not a penalty on the
    // outcome target. Reliability controls update magnitude and confidence.
    // learning_rate() already weights the update by evidence reliability.
    // Keep the target itself unbiased so confidence controls influence rather
    // than silently changing the observed outcome's valence.
    const double target = bounded(signal.reward);
    auto& strategy = strategies_[strategy_id(context, action)];
    if (strategy.uses == 0) {
        strategy.context = std::move(context);
        strategy.action = std::move(action);
        // Preserve the observed outcome's valence and magnitude. With no
        // prior estimate there is no existing value to interpolate from;
        // confidence carries evidence quality and downstream decision scoring
        // weights the value by confidence rather than distorting the target.
        strategy.value = target;
        strategy.confidence = rate;
    } else {
        strategy.value = bounded(strategy.value + rate * (target - strategy.value));
        strategy.confidence = std::clamp(strategy.confidence + rate * (1.0 - strategy.confidence), 0.0, 1.0);
    }
    ++strategy.uses;
}

std::vector<LearnedAssociation> DevelopmentalLearning::associations() const {
    std::vector<LearnedAssociation> result;
    result.reserve(associations_.size());
    for (const auto& [_, association] : associations_) result.push_back(association);
    return result;
}

std::vector<LearnedStrategy> DevelopmentalLearning::strategies() const {
    std::vector<LearnedStrategy> result;
    result.reserve(strategies_.size());
    for (const auto& [_, strategy] : strategies_) result.push_back(strategy);
    return result;
}

const LearnedStrategy* DevelopmentalLearning::best_strategy(const std::string& context) const noexcept {
    const LearnedStrategy* best = nullptr;
    for (const auto& [_, strategy] : strategies_) {
        if (strategy.context != context) continue;
        if (best == nullptr || strategy.value > best->value ||
            (strategy.value == best->value && strategy.confidence > best->confidence)) {
            best = &strategy;
        }
    }
    return best;
}

const LearnedStrategy* DevelopmentalLearning::best_related_strategy(const std::string& context,
                                                                      double minimum_similarity) const noexcept {
    const double threshold = std::clamp(std::isfinite(minimum_similarity) ? minimum_similarity : 0.5, 0.0, 1.0);
    const LearnedStrategy* best = nullptr;
    double best_score = -std::numeric_limits<double>::infinity();
    double best_similarity = -1.0;
    for (const auto& [_, strategy] : strategies_) {
        const double similarity = context_similarity(context, strategy.context);
        if (similarity < threshold) continue;
        const double value = std::clamp(strategy.value, -1.0, 1.0);
        // Preserve the sign of learned outcomes. Mapping values into [0, 1]
        // makes every negative outcome indistinguishable during retrieval,
        // so a harmful strategy can win arbitrarily when all evidence is bad.
        // Signed utility ranks positive evidence first and, when all relevant
        // evidence is negative, prefers the less harmful learned alternative.
        const double score = similarity * std::clamp(strategy.confidence, 0.0, 1.0) * value;
        // strategies_ is unordered: equal scores must not make action selection
        // depend on hash iteration order. Prefer the more similar context, then
        // use stable lexical ordering so replay and fresh runs agree on ties.
        const bool stable_tie_break =
            best != nullptr && score == best_score &&
            (similarity > best_similarity ||
             (similarity == best_similarity &&
              (strategy.context < best->context ||
               (strategy.context == best->context && strategy.action < best->action))));
        if (best == nullptr || score > best_score || stable_tie_break) {
            best = &strategy;
            best_score = score;
            best_similarity = similarity;
        }
    }
    return best;
}


std::vector<RelatedLearnedStrategy> DevelopmentalLearning::related_strategies(
    const std::string& context, double minimum_similarity) const {
    const double threshold = std::clamp(
        std::isfinite(minimum_similarity) ? minimum_similarity : 0.5, 0.0, 1.0);
    std::vector<RelatedLearnedStrategy> result;
    for (const auto& [_, strategy] : strategies_) {
        const double similarity = context_similarity(context, strategy.context);
        if (similarity < threshold) continue;
        result.push_back(RelatedLearnedStrategy{strategy, similarity});
    }
    std::sort(result.begin(), result.end(), [](const auto& left, const auto& right) {
        const double left_score = left.similarity * left.strategy.confidence * left.strategy.value;
        const double right_score = right.similarity * right.strategy.confidence * right.strategy.value;
        if (left_score != right_score) return left_score > right_score;
        if (left.similarity != right.similarity) return left.similarity > right.similarity;
        if (left.strategy.context != right.strategy.context)
            return left.strategy.context < right.strategy.context;
        return left.strategy.action < right.strategy.action;
    });
    return result;
}

void DevelopmentalLearning::consolidate(double retention_threshold) {
    const double threshold = std::clamp(retention_threshold, 0.0, 1.0);
    for (auto it = associations_.begin(); it != associations_.end();) {
        const double retention = std::clamp(std::abs(it->second.strength) * 0.7 +
                                            std::min(1.0, it->second.observations / 10.0) * 0.3,
                                            0.0, 1.0);
        if (retention < threshold) it = associations_.erase(it); else ++it;
    }
    for (auto it = strategies_.begin(); it != strategies_.end();) {
        const double retention = std::clamp(std::abs(it->second.value) * 0.7 +
                                            std::min(1.0, it->second.uses / 10.0) * 0.3,
                                            0.0, 1.0);
        if (retention < threshold) it = strategies_.erase(it); else ++it;
    }
}

} // namespace jarvis::core
