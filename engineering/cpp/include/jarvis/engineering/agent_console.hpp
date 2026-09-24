#pragma once

#include "agent.hpp"

#include <cstdint>
#include <deque>
#include <mutex>
#include <string>
#include <vector>

namespace jarvis::engineering {

// Human/JARVIS-to-agent communication is deliberately provider-neutral.
// The console is a transport-facing boundary; it does not decide which
// capability or agent should be used.
enum class AgentConsoleMessageKind : std::uint8_t {
    instruction,
    clarification,
    status_request,
    result,
    evidence,
    error,
};

struct AgentConsoleMessage {
    std::string id;
    std::string run_id;
    std::string sender;
    std::string recipient;
    AgentConsoleMessageKind kind{AgentConsoleMessageKind::instruction};
    std::string body;
};

class AgentConsole {
public:
    virtual ~AgentConsole() = default;

    virtual bool send(AgentConsoleMessage message) = 0;
    virtual std::vector<AgentConsoleMessage> receive(
        const std::string& recipient,
        const std::string& run_id) = 0;
};

class InMemoryAgentConsole final : public AgentConsole {
public:
    bool send(AgentConsoleMessage message) override;

    std::vector<AgentConsoleMessage> receive(
        const std::string& recipient,
        const std::string& run_id) override;

private:
    std::mutex mutex_;
    std::deque<AgentConsoleMessage> messages_;
};

// Adapter used by the orchestration layer. It allows the human operator or
// the JARVIS cognitive layer to communicate with a specific agent without
// embedding provider-specific routing into the agent itself.
class AgentConversation {
public:
    AgentConversation(AgentConsole& console,
                      std::string sender,
                      std::string agent_id,
                      std::string run_id)
        : console_(console), sender_(std::move(sender)),
          agent_id_(std::move(agent_id)), run_id_(std::move(run_id)) {}

    bool send(AgentConsoleMessageKind kind, std::string body);
    std::vector<AgentConsoleMessage> receive();

private:
    AgentConsole& console_;
    std::string sender_;
    std::string agent_id_;
    std::string run_id_;
};

} // namespace jarvis::engineering
