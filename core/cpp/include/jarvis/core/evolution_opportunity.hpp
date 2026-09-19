#pragma once

#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

namespace jarvis::core {

struct EvolutionSignal {
    std::string source;
    double severity{0.0};
    double recurrence{0.0};
    double confidence{0.0};
    double baseline{0.0};
    double current{0.0};
};

struct EvolutionOpportunity {
    std::string id;
    std::string source;
    double score{0.0};
    double confidence{0.0};
    double baseline{0.0};
    double current{0.0};
    std::size_t evidence_count{0};
    std::uint64_t first_sequence{0};
    std::uint64_t last_sequence{0};
};

struct EvolutionOpportunityPolicy {
    double severity_weight{0.40};
    double recurrence_weight{0.25};
    double confidence_weight{0.20};
    double magnitude_weight{0.15};
    double minimum_score{0.50};
};

class EvolutionOpportunityDetector {
public:
    explicit EvolutionOpportunityDetector(EvolutionOpportunityPolicy policy = {});

    std::vector<EvolutionOpportunity> detect(const std::vector<EvolutionSignal>& signals,
                                             std::uint64_t sequence = 0) const;

private:
    EvolutionOpportunityPolicy policy_;
};

} // namespace jarvis::core
