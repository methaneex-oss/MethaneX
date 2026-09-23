#include "jarvis/engineering/operator_console.hpp"

namespace jarvis::engineering {

MessageBusResult OperatorAgentConsole::send(const OperatorConsoleRequest& request) {
    return bridge_.send({
        request.recipient_id,
        request.correlation_id,
        AgentMessageType::request,
        request.payload
    });
}

std::vector<OperatorConsoleResponse> OperatorAgentConsole::receive() {
    const auto messages = bridge_.receive();
    std::vector<OperatorConsoleResponse> responses;
    responses.reserve(messages.size());
    for (const auto& message : messages) {
        responses.push_back({
            message.sender_id,
            message.correlation_id,
            message.type,
            message.payload
        });
    }
    return responses;
}

} // namespace jarvis::engineering
