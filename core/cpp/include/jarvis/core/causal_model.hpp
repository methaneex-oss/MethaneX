#pragma once

#include "cognition.hpp"

#include <optional>
#include <string>
#include <unordered_map>
#include <vector>

namespace jarvis::core {

class CausalModel {
public:
    void observe_transition(const std::vector<Belief>& before, const std::vector<Belief>& after);
    std::vector<CausalLink> links() const;
    std::vector<std::pair<std::string, Scalar>> predict(const std::vector<Belief>& assumptions) const;

private:
    std::unordered_map<std::string, CausalLink> links_;
};

} // namespace jarvis::core
