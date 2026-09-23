#pragma once

#include "operator_bridge.hpp"

#include <string>
#include <vector>

namespace jarvis::engineering {

struct OperatorConsoleRequest {
    std::string recipient_id;
    std::string correlation_id;
    std::string payload;
};

struct OperatorConsoleResponse {
    std::string sender_id;
    std::string correlation_id;
    AgentMessageType type{AgentMessageType::status};
    std::string payload;
};

class OperatorAgentConsole {
public:
    explicit OperatorAgentConsole(OperatorBridge& bridge) noexcept : bridge_(bridge) {}

    bool connected() const noexcept { return bridge_.connected(); }

    MessageBusResult send(const OperatorConsoleRequest& request);
    std::vector<OperatorConsoleResponse> receive();

private:
    OperatorBridge& bridge_;
};

} // namespace jarvis::engineering
