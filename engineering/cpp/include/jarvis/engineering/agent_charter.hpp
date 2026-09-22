#pragma once

#include "agent.hpp"

#include <string>
#include <vector>

namespace jarvis::engineering {

struct AgentCharter {
    std::string mission;
    std::string ownership;
    std::vector<std::string> allowed_paths;
    std::vector<std::string> forbidden_operations;
    std::vector<std::string> preserved_contracts;
    std::vector<std::string> mandatory_tests;
    std::vector<std::string> completion_requirements;
};

AgentCharter default_engineering_charter(const AgentDescriptor& descriptor);

} // namespace jarvis::engineering
