#include "jarvis/engineering/message_bus.hpp"
#include "jarvis/engineering/agent_conversation.hpp"

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <memory>
#include <mutex>
#include <string>
#include <thread>
#include <vector>

using namespace jarvis::engineering;

int main() {
    AgentMessageBus bus({64});

    std::vector<AgentMessage> received;
    std::mutex received_mutex;

    const auto registration = bus.register_agent(
        "reviewer",
        [&](const AgentMessage& message) {
            std::lock_guard lock(received_mutex);
            received.push_back(message);
        });
    assert(registration.accepted);
    assert(bus.registered_agents() == 1);

    const auto duplicate = bus.register_agent("reviewer", [](const AgentMessage&) {});
    assert(!duplicate.accepted);

    AgentMessage message{
        "message-1", 0, "run-1", "workspace-1", "implementation", "reviewer",
        "task-1", AgentMessageType::review, "inspect this"};
    const auto delivered = bus.send(message);
    assert(delivered.accepted);
    assert(delivered.sequence == 1);

    {
        std::lock_guard lock(received_mutex);
        assert(received.size() == 1);
        assert(received.front().sequence == 1);
        assert(received.front().sender_id == "implementation");
        assert(received.front().payload == "inspect this");
    }

    AgentMessage oversized = message;
    oversized.message_id = "message-oversized";
    oversized.payload.assign(65, 'x');
    assert(!bus.send(oversized).accepted);

    AgentMessage unknown = message;
    unknown.message_id = "message-unknown";
    unknown.recipient_id = "missing";
    assert(!bus.send(unknown).accepted);

    AgentMessage invalid = message;
    invalid.message_id.clear();
    assert(!bus.send(invalid).accepted);

    constexpr std::size_t threads = 8;
    constexpr std::size_t messages_per_thread = 50;
    std::vector<std::thread> workers;
    workers.reserve(threads);
    for (std::size_t thread_index = 0; thread_index < threads; ++thread_index) {
        workers.emplace_back([&, thread_index] {
            for (std::size_t i = 0; i < messages_per_thread; ++i) {
                AgentMessage concurrent{
                    "concurrent-" + std::to_string(thread_index) + "-" + std::to_string(i),
                    0, "run-1", "workspace-1", "builder-" + std::to_string(thread_index),
                    "reviewer", "task-concurrent", AgentMessageType::status, "ok"};
                assert(bus.send(std::move(concurrent)).accepted);
            }
        });
    }
    for (auto& worker : workers) worker.join();

    {
        std::lock_guard lock(received_mutex);
        assert(received.size() == 1 + threads * messages_per_thread);
        std::vector<std::uint64_t> sequences;
        sequences.reserve(received.size());
        for (const auto& item : received) sequences.push_back(item.sequence);
        std::sort(sequences.begin(), sequences.end());
        for (std::size_t i = 0; i < sequences.size(); ++i) assert(sequences[i] == i + 1);
    }

    AgentCommunicationEndpoint implementation(bus, "implementation", "run-2", "workspace-2");
    AgentCommunicationEndpoint review(bus, "review", "run-2", "workspace-2");
    assert(implementation.registered());
    assert(review.registered());

    const auto peer_message = implementation.send(
        "peer-1", "review", "task-peer", AgentMessageType::request, "please inspect");
    assert(peer_message.accepted);
    assert(review.pending() == 1);
    const auto peer_messages = review.drain();
    assert(peer_messages.size() == 1);
    assert(peer_messages.front().sender_id == "implementation");
    assert(peer_messages.front().payload == "please inspect");

    const auto wrong_run = bus.send(AgentMessage{
        "peer-2", 0, "run-3", "workspace-2", "external", "review", "task-peer",
        AgentMessageType::feedback, "different run"});
    assert(wrong_run.accepted);
    assert(review.pending() == 0);

    AgentConversation operator_channel(
        bus, "operator", "run-2", "workspace-2",
        [](const std::string& sender, const std::string& recipient, AgentMessageType) {
            return sender == "operator" && recipient == "review";
        });
    assert(operator_channel.connected());
    assert(operator_channel.run_id() == "run-2");
    assert(operator_channel.workspace_id() == "workspace-2");

    const auto operator_message = operator_channel.send(
        "review", "human-task-1", AgentMessageType::request, "Review latest implementation.");
    assert(operator_message.accepted);
    const auto operator_received = review.drain();
    assert(operator_received.size() == 1);
    assert(operator_received.front().sender_id == "operator");
    assert(operator_received.front().correlation_id == "human-task-1");
    assert(operator_received.front().payload == "Review latest implementation.");

    const auto denied = operator_channel.send(
        "implementation", "human-task-2", AgentMessageType::request, "write code");
    assert(!denied.accepted);

    const auto response = review.send(
        "operator-response", "operator", "human-task-1", AgentMessageType::result,
        "Review completed; evidence is ready.");
    assert(response.accepted);
    const auto operator_responses = operator_channel.receive();
    assert(operator_responses.size() == 1);
    assert(operator_responses.front().sender_id == "review");
    assert(operator_responses.front().correlation_id == "human-task-1");
    assert(operator_responses.front().payload == "Review completed; evidence is ready.");

    auto transient = std::make_unique<AgentCommunicationEndpoint>(
        bus, "transient", "run-race", "workspace-race");
    assert(transient->registered());
    std::thread sender([&] {
        for (std::size_t i = 0; i < 1000; ++i) {
            bus.send(AgentMessage{
                "race-" + std::to_string(i), 0, "run-race", "workspace-race", "sender",
                "transient", "race", AgentMessageType::status, "payload"});
        }
    });
    transient.reset();
    sender.join();
    assert(bus.registered_agents() == 4);

    assert(bus.unregister_agent("reviewer").accepted);
    assert(!bus.unregister_agent("reviewer").accepted);
    return 0;
}
