#pragma once

#include "model_provider.hpp"
#include "workspace.hpp"

namespace jarvis::engineering {

class ModelAssessmentAgent final : public EngineeringAgent {
public:
    ModelAssessmentAgent(
        AgentDescriptor descriptor,
        EngineeringModelProvider& provider,
        EngineeringWorkspace& workspace) noexcept;

    AgentDescriptor descriptor() const override;
    AgentResult execute(const EngineeringTask& task) override;

private:
    static std::size_t context_bytes(const std::string& context) noexcept;
    static bool safe_relative_path(std::string_view path) noexcept;

    AgentDescriptor descriptor_;
    EngineeringModelProvider& provider_;
    EngineeringWorkspace& workspace_;
};

} // namespace jarvis::engineering
