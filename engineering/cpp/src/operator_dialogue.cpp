#include "jarvis/engineering/operator_dialogue.hpp"

#include <utility>

namespace jarvis::engineering {

EngineeringOperatorDialogue::EngineeringOperatorDialogue(
    EngineeringOperatorConsole& console, OperatorDialoguePolicy policy)
    : console_(console), policy_(policy) {}

MessageBusResult EngineeringOperatorDialogue::send(
    const std::string& recipient_id,
    const std::string& correlation_id,
    const std::string& payload,
    AgentMessageType type) {
    OperatorMessage message;
    message.correlation_id = correlation_id;
    message.recipient_id = recipient_id;
    message.type = type;
    message.payload = payload;

    const auto result = console_.send(message);
    if (result.accepted) {
        AgentMessage sent;
        sent.sequence = result.sequence;
        sent.sender_id = console_.operator_id();
        sent.recipient_id = recipient_id;
        sent.correlation_id = correlation_id;
        sent.type = type;
        sent.payload = payload;
        append(sent);
    }
    return result;
}

std::vector<OperatorTurn> EngineeringOperatorDialogue::receive() {
    const auto messages = console_.receive();
    std::vector<OperatorTurn> received;
    received.reserve(messages.size());
    for (const auto& message : messages) {
        if (!policy_.accept_unsolicited_messages &&
            message.correlation_id.empty()) {
            continue;
        }
        append(message);
        received.push_back(transcript_.back());
    }
    return received;
}

const std::vector<OperatorTurn>& EngineeringOperatorDialogue::transcript() const noexcept {
    return transcript_;
}

std::size_t EngineeringOperatorDialogue::pending() const noexcept {
    return console_.pending();
}

void EngineeringOperatorDialogue::append(const AgentMessage& message) {
    if (policy_.maximum_transcript_entries == 0) return;
    if (transcript_.size() >= policy_.maximum_transcript_entries) {
        transcript_.erase(transcript_.begin());
    }
    transcript_.push_back({message.sequence,
                           message.message_id,
                           message.sender_id,
                           message.recipient_id,
                           message.correlation_id,
                           message.type,
                           message.payload});
}

} // namespace jarvis::engineering
