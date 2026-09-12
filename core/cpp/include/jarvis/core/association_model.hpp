#pragma once

#include "cognition.hpp"

#include <cstdint>
#include <string>
#include <vector>

namespace jarvis::core {

struct Association {
    std::string left;
    std::string right;
    double strength{0.0};
    double confidence{0.0};
    std::uint64_t observations{0};
    std::uint64_t last_sequence{0};
};

class AssociationModel {
public:
    void observe(const std::vector<Belief>& before, const std::vector<Belief>& after,
                 std::uint64_t sequence);
    std::vector<Association> all() const;
    std::vector<Association> related(const std::string& key, double minimum_strength = 0.5) const;

private:
    std::vector<Association> associations_;
};

} // namespace jarvis::core
