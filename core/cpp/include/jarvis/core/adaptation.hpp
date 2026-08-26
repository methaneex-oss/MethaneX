#pragma once

#include <cstdint>
#include <string>
#include <unordered_map>

namespace jarvis::core {

struct AdaptiveMetric {
    double estimate{0.5};
    double mean_error{1.0};
    std::uint64_t observations{0};
};

class AdaptationModel {
public:
    AdaptiveMetric observe(const std::string& key, double predicted, double actual);
    const AdaptiveMetric* metric(const std::string& key) const noexcept;
    double confidence(const std::string& key) const noexcept;

private:
    std::unordered_map<std::string, AdaptiveMetric> metrics_;
};

} // namespace jarvis::core
