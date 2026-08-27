#pragma once

#include <cstdint>
#include <string>
#include <unordered_map>
#include <vector>

namespace jarvis::core {

struct StrategyParameter {
    std::string key;
    double value{0.0};
    double fitness{0.0};
    std::uint64_t observations{0};
    double baseline{0.0};
    double previous_value{0.0};
};

struct EvolutionProposal {
    std::string key;
    double current{0.0};
    double proposed{0.0};
    double expected_gain{0.0};
    double confidence{0.0};
};

class EvolutionModel {
public:
    void register_parameter(std::string key, double initial);
    void observe_fitness(const std::string& key, double fitness);
    std::vector<EvolutionProposal> propose() const;
    bool adopt(const EvolutionProposal& proposal);
    bool rollback(const std::string& key);
    const StrategyParameter* parameter(const std::string& key) const noexcept;

private:
    std::unordered_map<std::string, StrategyParameter> parameters_;
};

} // namespace jarvis::core
