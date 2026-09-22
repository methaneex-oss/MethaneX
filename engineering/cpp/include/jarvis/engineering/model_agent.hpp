#pragma once

#include "agent_conversation.hpp"
#include "model_provider.hpp"
#include "workspace.hpp"

namespace jarvis::engineering {

class ModelBackedEngineeringAgent final : public EngineeringAgent,\n                                       public ConversationalEngineeringAgent {
public:
    ModelBackedEngineeringAgent(
        AgentDescriptor descriptor,
        EngineeringModelProvider& provider,
        EngineeringWorkspace& workspace) noexcept;

    AgentDescriptor descriptor() const override;
    AgentResult execute(const EngineeringTask& task) override;\n    AgentConversationResponse converse(\n        const AgentConversationRequest& request) override;

private:
    static bool safe_relative_path(std::string_view path) noexcept;
    static std::string digest(std::string_view content);
    static std::size_t response_bytes(const ModelResponse& response) noexcept;

    AgentDescriptor descriptor_;
    EngineeringModelProvider& provider_;
    EngineeringWorkspace& workspace_;
};

} // namespace jarvis::engineering
