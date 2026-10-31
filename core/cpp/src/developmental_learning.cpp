#include "jarvis/core/developmental_learning.hpp"

#include <algorithm>
#include <charconv>
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

std::vector<std::string> context_path_segments(const std::string& context) {
    std::vector<std::string> segments;
    std::size_t start = 0;
    while (start <= context.size()) {
        const auto separator = context.find('/', start);
        const auto end = separator == std::string::npos ? context.size() : separator;
        std::size_t first = start;
        std::size_t last = end;
        while (first < last && std::isspace(static_cast<unsigned char>(context[first]))) ++first;
        while (last > first && std::isspace(static_cast<unsigned char>(context[last - 1]))) --last;
        std::string segment = context.substr(first, last - first);
        // A slash defines a context level, while spaces separate words within
        // that level. Keep those words visible to prefix comparison so
        // "route-selection alternate" remains close to "route-selection"
        // without also treating it as equally close to "route-variant".
        std::string word;
        for (const unsigned char character : segment) {
            if (std::isspace(character)) {
                if (!word.empty()) {
                    segments.push_back(std::move(word));
                    word.clear();
                }
            } else {
                word.push_back(static_cast<char>(std::tolower(character)));
            }
        }
        if (!word.empty()) segments.push_back(std::move(word));
        if (separator == std::string::npos) break;
        start = separator + 1;
    }
    return segments;
}

std::size_t context_values_marker(const std::string& context) {
    constexpr std::size_t marker_size = 8; // "/values/"
    const auto features = context.find("/features/");
    if (features == std::string::npos) return context.find("/values/");

    // Older persisted contexts may contain a feature label or value literally
    // named "values". In the inferred schema format, the real delimiter is the
    // occurrence that divides an equal number of encoded feature labels and
    // encoded values. Segment escaping guarantees neither side contains a raw
    // slash inside an individual label/value, so this also disambiguates legacy
    // records without rewriting the journal.
    const std::size_t labels_start = features + 10; // "/features/"
    auto marker = context.find("/values/", labels_start);
    while (marker != std::string::npos) {
        const auto label_path = context.substr(labels_start, marker - labels_start);
        const auto value_path = context.substr(marker + marker_size);
        if (!label_path.empty() && !value_path.empty()) {
            const auto segment_count = [](const std::string& path) {
                return static_cast<std::size_t>(
                    1 + std::count(path.begin(), path.end(), '/'));
            };
            if (segment_count(label_path) == segment_count(value_path)) return marker;
        }
        marker = context.find("/values/", marker + 1);
    }
    return std::string::npos;
}

std::vector<std::string> context_path_values(const std::string& context) {
    const auto marker = context_values_marker(context);
    if (marker == std::string::npos) return {};
    std::vector<std::string> values;
    std::size_t start = marker + 8;
    while (start <= context.size()) {
        const auto separator = context.find('/', start);
        const auto end = separator == std::string::npos ? context.size() : separator;
        std::string value = context.substr(start, end - start);
        std::transform(value.begin(), value.end(), value.begin(),
                       [](unsigned char c) { return static_cast<char>(std::tolower(c)); });
        values.push_back(std::move(value));
        if (separator == std::string::npos) break;
        start = separator + 1;
    }
    return values;
}

std::vector<std::pair<std::string, std::string>> context_feature_pairs(
    const std::string& context) {
    const auto features = context.find("/features/");
    const auto values_marker = context_values_marker(context);
    if (features == std::string::npos || values_marker == std::string::npos ||
        values_marker <= features + 10) return {};

    std::vector<std::string> labels;
    const std::size_t labels_start = features + 10;
    std::size_t start = labels_start;
    while (start < values_marker) {
        const auto separator = context.find('/', start);
        const auto end = separator == std::string::npos || separator > values_marker
            ? values_marker : separator;
        if (end == start) return {};
        labels.push_back(context.substr(start, end - start));
        if (end == values_marker) break;
        start = end + 1;
    }

    const auto values = context_path_values(context);
    if (labels.empty() || labels.size() != values.size()) return {};
    std::vector<std::pair<std::string, std::string>> result;
    result.reserve(labels.size());
    for (std::size_t i = 0; i < labels.size(); ++i)
        result.emplace_back(labels[i], values[i]);
    return result;
}

std::string feature_strategy_key(const std::string& label,
                                 const std::string& value) {
    return label + '\x1e' + value;
}

double inferred_value_similarity(const std::string& left, const std::string& right) {
    if (left == right) return 1.0;

    // Numeric descriptors are logarithmic bands. Adjacent bands are related,
    // but a farther band should contribute progressively less similarity.
    const auto numeric_band = [](const std::string& value,
                                 std::string& sign, int& scale) {
        const auto marker = value.find("-scale-");
        if (marker == std::string::npos) return false;
        sign = value.substr(0, marker);
        if (sign != "positive" && sign != "negative") return false;
        const auto number = value.data() + marker + 7;
        const auto finish = value.data() + value.size();
        const auto parsed = std::from_chars(number, finish, scale);
        return parsed.ec == std::errc{} && parsed.ptr == finish;
    };
    std::string left_sign;
    std::string right_sign;
    int left_scale = 0;
    int right_scale = 0;
    if (numeric_band(left, left_sign, left_scale) &&
        numeric_band(right, right_sign, right_scale)) {
        if (left_sign != right_sign) return 0.0;
        const auto distance = std::abs(static_cast<long long>(left_scale) -
                                       static_cast<long long>(right_scale));
        return 1.0 / (1.0 + static_cast<double>(distance));
    }

    // For categorical/text values, compare the value itself rather than the
    // shared context hierarchy. This prevents schema labels from inflating
    // similarity between observations whose actual values are unrelated.
    const auto left_tokens = context_tokens(left);
    const auto right_tokens = context_tokens(right);
    if (left_tokens.empty() || right_tokens.empty()) return 0.0;
    std::unordered_set<std::string> left_set(left_tokens.begin(), left_tokens.end());
    std::unordered_set<std::string> right_set(right_tokens.begin(), right_tokens.end());
    std::size_t intersection = 0;
    for (const auto& token : left_set) if (right_set.contains(token)) ++intersection;
    const std::size_t union_size = left_set.size() + right_set.size() - intersection;
    return union_size == 0 ? 0.0 :
        static_cast<double>(intersection) / static_cast<double>(union_size);
}

double inferred_context_value_similarity(const std::string& left, const std::string& right) {
    const auto left_values = context_path_values(left);
    const auto right_values = context_path_values(right);
    if (left_values.empty() || left_values.size() != right_values.size()) return 0.0;
    double total = 0.0;
    for (std::size_t i = 0; i < left_values.size(); ++i)
        total += inferred_value_similarity(left_values[i], right_values[i]);
    return total / static_cast<double>(left_values.size());
}

double context_similarity(const std::string& left, const std::string& right) {
    if (left == right && !left.empty()) return 1.0;
    const auto left_tokens = context_tokens(left);
    const auto right_tokens = context_tokens(right);
    if (has_negation(left_tokens) != has_negation(right_tokens)) return 0.0;
    if (left_tokens.empty() || right_tokens.empty()) return 0.0;

    // Slash-delimited contexts express a hierarchy (for example,
    // navigation/clear and navigation/canyon). Shared parent segments are
    // meaningful evidence for cautious transfer, while the distinct leaf
    // segments preserve context specificity. Do not reduce a shared parent
    // to one token in a flat Jaccard set: that artificially scores sibling
    // contexts below the default transfer threshold.
    if (left.find('/') != std::string::npos && right.find('/') != std::string::npos) {
        // Featureless inferred observations have no value evidence to justify
        // generalization. Their goal suffix preserves identity for exact recall,
        // but their shared kind/source prefix alone must not make unrelated
        // experiences appear similar enough to transfer a strategy.
        const auto is_featureless_observation = [](const std::string& context) {
            return context.rfind("observation/", 0) == 0 &&
                   context.find("/goal/") != std::string::npos &&
                   context.find("/values/") == std::string::npos;
        };
        if ((is_featureless_observation(left) ||
             is_featureless_observation(right)) && left != right) {
            return 0.0;
        }

        // Automatically inferred observation contexts encode a stable feature
        // schema before "/values/". Transfer between different schemas is unsafe:
        // matching only the sensor/source prefix can make an action learned for
        // one feature appear relevant to a different feature. Require the same
        // identity and feature schema, then compare the value-bearing leaves.
        const auto left_values = context_values_marker(left);
        const auto right_values = context_values_marker(right);
        if ((left_values != std::string::npos) !=
            (right_values != std::string::npos)) return 0.0;
        if (left_values != std::string::npos &&
            context_path_segments(left.substr(0, left_values)) !=
                context_path_segments(right.substr(0, right_values))) {
            return 0.0;
        }

        if (left_values != std::string::npos)
            return inferred_context_value_similarity(left, right);

        const auto left_segments = context_path_segments(left);
        const auto right_segments = context_path_segments(right);
        if (left_segments.empty() || right_segments.empty()) return 0.0;
        std::size_t common_prefix = 0;
        while (common_prefix < left_segments.size() &&
               common_prefix < right_segments.size() &&
               left_segments[common_prefix] == right_segments[common_prefix]) {
            ++common_prefix;
        }
        const auto maximum_depth = std::max(left_segments.size(), right_segments.size());
        return maximum_depth == 0 ? 0.0 :
            static_cast<double>(common_prefix) / static_cast<double>(maximum_depth);
    }

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

void DevelopmentalLearning::observe_strategy(std::string context, std::string action,
                                                const LearningSignal& signal,
                                                bool update_feature_model) {
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

    // Learn the contribution of each observed feature-value independently of
    // the complete context string. A small online linear model per action lets
    // later decisions combine previously experienced factors in a novel
    // configuration instead of selecting only the nearest stored context.
    const auto features = update_feature_model
        ? context_feature_pairs(strategy.context)
        : std::vector<std::pair<std::string, std::string>>{};
    if (!features.empty()) {
        auto& model = feature_strategy_models_[strategy.action];
        double prediction = model.bias;
        for (const auto& [label, value] : features) {
            const auto weight = model.weights.find(feature_strategy_key(label, value));
            if (weight != model.weights.end()) prediction += weight->second;
        }
        prediction = bounded(prediction);
        const double error = target - prediction;
        const double step = std::clamp(rate * 0.4, 0.02, 0.25);
        const double normalization = std::sqrt(static_cast<double>(features.size()));
        model.bias = bounded(model.bias + step * error * 0.2);
        for (const auto& [label, value] : features) {
            const auto key = feature_strategy_key(label, value);
            auto& weight = model.weights[key];
            weight = bounded(weight + step * error / normalization);
            ++model.feature_observations[key];
            auto& supporting_contexts = model.feature_contexts[key];
            if (supporting_contexts.size() < 3)
                supporting_contexts.insert(strategy.context);
        }
        ++model.observations;
    }
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
    double best_score = -std::numeric_limits<double>::infinity();
    for (const auto& [_, strategy] : strategies_) {
        if (strategy.context != context) continue;

        // Rank an exact-context strategy by confidence-weighted learned utility,
        // matching related-context retrieval. A single weakly supported success
        // must not outrank a better-supported alternative solely because its
        // unweighted value is larger. Confidence scales influence; it does not
        // rewrite the observed outcome stored in strategy.value.
        const double value = std::clamp(
            std::isfinite(strategy.value) ? strategy.value : 0.0, -1.0, 1.0);
        const double confidence = std::clamp(
            std::isfinite(strategy.confidence) ? strategy.confidence : 0.0, 0.0, 1.0);
        const double score = value * confidence;

        // The container is unordered. Stable tie-breaking keeps retrieval
        // reproducible across runs and journal replay.
        const bool stable_tie_break =
            best != nullptr && score == best_score &&
            (strategy.action < best->action ||
             (strategy.action == best->action && strategy.context < best->context));
        if (best == nullptr || score > best_score || stable_tie_break) {
            best = &strategy;
            best_score = score;
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

FeatureStrategyEstimate DevelopmentalLearning::feature_strategy_estimate(
    const std::string& context, const std::string& action) const {
    FeatureStrategyEstimate estimate;
    if (context.empty() || action.empty()) return estimate;
    const auto features = context_feature_pairs(context);
    if (features.empty()) return estimate;
    estimate.feature_count = features.size();

    const auto model_it = feature_strategy_models_.find(action);
    if (model_it == feature_strategy_models_.end()) return estimate;
    const auto& model = model_it->second;
    estimate.observations = model.observations;
    double prediction = model.bias;
    std::size_t minimum_independent_contexts =
        std::numeric_limits<std::size_t>::max();
    for (const auto& [label, value] : features) {
        const auto key = feature_strategy_key(label, value);
        const auto weight = model.weights.find(key);
        const auto contexts = model.feature_contexts.find(key);
        if (weight == model.weights.end() ||
            contexts == model.feature_contexts.end()) continue;
        prediction += weight->second;
        ++estimate.matched_features;
        minimum_independent_contexts = std::min(
            minimum_independent_contexts, contexts->second.size());
    }
    if (estimate.matched_features == 0) return estimate;
    estimate.value = bounded(prediction);
    const double coverage = static_cast<double>(estimate.matched_features) /
                            static_cast<double>(estimate.feature_count);
    // Confidence is limited by the least-supported feature across distinct
    // full contexts. Repeating the same situation cannot inflate support.
    const double support = std::min(
        1.0, static_cast<double>(minimum_independent_contexts) / 3.0);
    estimate.confidence = std::clamp(coverage * support, 0.0, 1.0);
    return estimate;
}

void DevelopmentalLearning::consolidate(double retention_threshold) {
    // Invalid caller input must not silently disable forgetting. Match the
    // documented default threshold when a non-finite value is supplied.
    const double threshold = std::clamp(
        std::isfinite(retention_threshold) ? retention_threshold : 0.05,
        0.0, 1.0);
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
