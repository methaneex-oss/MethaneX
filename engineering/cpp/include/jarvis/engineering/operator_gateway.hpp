#pragma once

#include "message_bus.hpp"

#include <cstddef>
#include <functional>
#include <string>
#include <vector>

namespace jarvis::engineering {

struct OperatorMessage {
    std::string message_id;
    std::string correlation_id;
    AgentMessageType type{AgentMessageType::query};
    std::string payload;
};

struct OperatorGatewayPolicy {
    std::size_t maximum_message_bytes{64 * 1024};
    bool allow_broadcast{false};
    std::function<bool(const OperatorMessage&, const std::string&)> authorize;
};

struct OperatorGatewayResult {
    bool accepted{false};
    std::string reason;
    std::uint64_t sequence{0};
};

class OperatorGateway {
public:
    OperatorGateway(
        AgentMessageBus& bus,
        std::string operator_id,
        std::string run_id,
        std::string workspace_id,
        OperatorGatewayPolicy policy = {});

    ~OperatorGateway();

    OperatorGateway(const OperatorGateway&) = delete;
    OperatorGateway& operator=(const OperatorGateway&) = delete;

    bool connected() const noexcept;
    const std::string& operator_id() const noexcept;
    const std::string& run_id() const noexcept;
    const std::string& workspace_id() const noexcept;

    OperatorGatewayResult send_to_agent(
        const OperatorMessage& message,
        const std::string& agent_id);

    OperatorGatewayResult broadcast(
        const OperatorMessage& message,
        const std::vector<std::string>& agent_ids);

    std::vector<AgentMessage> receive();
    std::size_t pending() const noexcept;

private:
    static bool valid_message(const OperatorMessage& message,
                              std::size_t maximum_bytes) noexcept;

    AgentMessageBus& bus_;
    AgentCommunicationEndpoint endpoint_;
    OperatorGatewayPolicy policy_;
};

} // namespace jarvis::engineering
