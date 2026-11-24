#pragma once

#include "operator_console.hpp"

#include <cstddef>
#include <functional>
#include <string>
#include <vector>

namespace jarvis::engineering {

struct OperatorTurn {
    std::uint64_t sequence{0};
    std::string message_id;
    std::string sender_id;
    std::string recipient_id;
    std::string correlation_id;
    AgentMessageType type{AgentMessageType::status};
    std::string payload;
};

struct OperatorDialoguePolicy {
    std::size_t maximum_transcript_entries{1024};
    bool accept_unsolicited_messages{true};
};

class EngineeringOperatorDialogue {
public:
    EngineeringOperatorDialogue(EngineeringOperatorConsole& console,
                                 OperatorDialoguePolicy policy = {});

    MessageBusResult send(const std::string& recipient_id,
                          const std::string& correlation_id,
                          const std::string& payload,
                          AgentMessageType type = AgentMessageType::request);

    std::vector<OperatorTurn> receive();
    const std::vector<OperatorTurn>& transcript() const noexcept;
    std::size_t pending() const noexcept;

private:
    void append(const AgentMessage& message);

    EngineeringOperatorConsole& console_;
    OperatorDialoguePolicy policy_;
    std::vector<OperatorTurn> transcript_;
};

} // namespace jarvis::engineering
