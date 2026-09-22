#include "jarvis/engineering/agent_chat.hpp"

#include <utility>

namespace jarvis::engineering {

namespace {

AgentChatResponse to_response(const AgentMessage& message) {
    return {
        true,
        message.message_id,
        message.sender_id,
        message.recipient_id,
        message.correlation_id,
        message.payload,
        message.sequence,
        "message received"
    };
}

} // namespace

EngineeringAgentChat::EngineeringAgentChat(
    AgentMessageBus& bus,
    std::string run_id,
    std::string workspace_id,
    AgentChatConfig config)
    : bus_(bus),
      run_id_(std::move(run_id)),
      workspace_id_(std::move(workspace_id)),
      config_(std::move(config)),
      endpoint_(
          bus_,
          config_.participant_id,
          run_id_,
          workspace_id_,
          config_.maximum_pending_messages) {}

bool EngineeringAgentChat::connected() const noexcept {
    return endpoint_.registered();
}

const std::string& EngineeringAgentChat::participant_id() const noexcept {
    return endpoint_.agent_id();
}

AgentChatResponse EngineeringAgentChat::send(const AgentChatRequest& request) {
    if (!connected()) {
        return {false, {}, {}, {}, {}, {}, 0, "chat participant is not registered"};
    }
    if (request.message_id.empty() || request.agent_id.empty() ||
        request.correlation_id.empty() || request.text.empty()) {
        return {false, {}, {}, {}, {}, {}, 0, "invalid chat request"};
    }
    if (request.run_id != run_id_ || request.workspace_id != workspace_id_) {
        return {false, {}, {}, {}, {}, {}, 0, "chat scope mismatch"};
    }
    if (request.text.size() > config_.maximum_message_bytes) {
        return {false, {}, {}, {}, {}, {}, 0, "chat message exceeds configured size"};
    }

    const auto result = endpoint_.send(
        request.message_id,
        request.agent_id,
        request.correlation_id,
        AgentMessageType::query,
        request.text);

    if (!result.accepted) {
        return {
            false,
            request.message_id,
            config_.participant_id,
            request.agent_id,
            request.correlation_id,
            {},
            result.sequence,
            result.reason
        };
    }

    return {
        true,
        request.message_id,
        config_.participant_id,
        request.agent_id,
        request.correlation_id,
        {},
        result.sequence,
        "message sent"
    };
}

std::vector<AgentChatResponse> EngineeringAgentChat::receive() {
    std::vector<AgentChatResponse> responses;
    for (const auto& message : endpoint_.drain()) {
        responses.push_back(to_response(message));
    }
    return responses;
}

} // namespace jarvis::engineering
