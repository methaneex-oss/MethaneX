#include "jarvis/engineering/message_bus.hpp"

#include <algorithm>
#include <utility>

namespace jarvis::engineering {

AgentMessageBus::AgentMessageBus(MessageBusConfig config) : config_(config) {
    if (config_.maximum_deduplication_entries == 0)
        config_.maximum_deduplication_entries = 1;
}

bool AgentMessageBus::valid_message(const AgentMessage& message) const noexcept {
    return !message.run_id.empty() && !message.sender_id.empty() &&
           !message.recipient_id.empty() && !message.message_id.empty() &&
           !message.correlation_id.empty() &&
           message.payload.size() <= config_.maximum_payload_bytes;
}

std::string AgentMessageBus::delivery_key(const AgentMessage& message) {
    // Length-prefix each field to avoid collisions from delimiters inside IDs.
    std::string key;
    const auto append = [&key](const std::string& field) {
        key += std::to_string(field.size());
        key += ':';
        key += field;
    };
    append(message.run_id);
    append(message.workspace_id);
    append(message.sender_id);
    append(message.recipient_id);
    append(message.message_id);
    return key;
}

bool AgentMessageBus::same_content(const AgentMessage& left,
                                   const AgentMessage& right) noexcept {
    return left.message_id == right.message_id &&
           left.run_id == right.run_id &&
           left.workspace_id == right.workspace_id &&
           left.sender_id == right.sender_id &&
           left.recipient_id == right.recipient_id &&
           left.correlation_id == right.correlation_id &&
           left.type == right.type &&
           left.payload == right.payload;
}

MessageBusResult AgentMessageBus::register_agent(std::string id,
                                                  AgentMessageHandler handler) {
    if (id.empty() || !handler) return {false, 0, "invalid agent registration"};
    std::lock_guard lock(mutex_);
    if (subscribers_.contains(id)) return {false, 0, "agent already registered"};
    subscribers_.emplace(std::move(id), Subscriber{std::move(handler)});
    return {true, 0, "agent registered"};
}

MessageBusResult AgentMessageBus::unregister_agent(const std::string& id) {
    if (id.empty()) return {false, 0, "invalid agent id"};
    std::lock_guard lock(mutex_);
    if (subscribers_.erase(id) == 0) return {false, 0, "agent not registered"};
    return {true, 0, "agent unregistered"};
}

MessageBusResult AgentMessageBus::send(AgentMessage message) {
    AgentMessageHandler handler;
    std::string key;
    {
        std::lock_guard lock(mutex_);
        if (!valid_message(message)) return {false, 0, "invalid message"};
        key = delivery_key(message);
        if (const auto accepted = accepted_messages_.find(key);
            accepted != accepted_messages_.end()) {
            if (!same_content(accepted->second, message))
                return {false, accepted->second.sequence,
                        "message ID was reused with different content"};
            return {true, accepted->second.sequence,
                    "duplicate retry acknowledged without redelivery"};
        }
        if (in_flight_messages_.contains(key))
            return {false, 0, "message with this ID is already being delivered"};

        const auto subscriber = subscribers_.find(message.recipient_id);
        if (subscriber == subscribers_.end())
            return {false, 0, "recipient not registered"};

        message.sequence = next_sequence_++;
        in_flight_messages_.insert(key);
        handler = subscriber->second.handler;
    }

    bool delivered = false;
    try {
        delivered = handler(message);
    } catch (...) {
        // A failed receiver call must release the in-flight reservation so the
        // sender can retry; it must never strand this message ID indefinitely.
        delivered = false;
    }

    {
        std::lock_guard lock(mutex_);
        in_flight_messages_.erase(key);
        if (delivered) {
            accepted_messages_.emplace(key, message);
            accepted_order_.push_back(key);
            while (accepted_order_.size() > config_.maximum_deduplication_entries) {
                accepted_messages_.erase(accepted_order_.front());
                accepted_order_.pop_front();
            }
        }
    }
    if (!delivered)
        return {false, message.sequence,
                "recipient rejected message; retry after resolving backpressure"};
    return {true, message.sequence, "message delivered"};
}

std::size_t AgentMessageBus::registered_agents() const noexcept {
    std::lock_guard lock(mutex_);
    return subscribers_.size();
}
AgentCommunicationEndpoint::AgentCommunicationEndpoint(AgentMessageBus&b,std::string id,std::string run,std::string ws,std::size_t max):bus_(b),agent_id_(std::move(id)),run_id_(std::move(run)),workspace_id_(std::move(ws)),state_(std::make_shared<State>()){state_->maximum_pending_messages=max;if(agent_id_.empty()||run_id_.empty()||max==0){state_->accepting=false;return;}const auto state=state_;const auto run_copy=run_id_;const auto ws_copy=workspace_id_;auto r=bus_.register_agent(agent_id_,[state,run_copy,ws_copy](const AgentMessage&m){return AgentCommunicationEndpoint::receive(state,m,run_copy,ws_copy);});registered_=r.accepted;if(!registered_)state_->accepting=false;}
AgentCommunicationEndpoint::~AgentCommunicationEndpoint(){ {std::lock_guard lock(state_->mutex);state_->accepting=false;} if(registered_)bus_.unregister_agent(agent_id_); }
bool AgentCommunicationEndpoint::registered()const noexcept{return registered_;} const std::string& AgentCommunicationEndpoint::agent_id()const noexcept{return agent_id_;} const std::string& AgentCommunicationEndpoint::run_id()const noexcept{return run_id_;} const std::string& AgentCommunicationEndpoint::workspace_id()const noexcept{return workspace_id_;}
MessageBusResult AgentCommunicationEndpoint::send(std::string mid,std::string rid,std::string cid,AgentMessageType type,std::string payload){if(!registered_)return{false,0,"communication endpoint is not registered"};return bus_.send(AgentMessage{std::move(mid),0,run_id_,workspace_id_,agent_id_,std::move(rid),std::move(cid),type,std::move(payload)});}
bool AgentCommunicationEndpoint::receive(const std::shared_ptr<State>&s,const AgentMessage&m,const std::string&run,const std::string&ws){if(m.run_id!=run||(!ws.empty()&&m.workspace_id!=ws))return false;std::lock_guard lock(s->mutex);if(!s->accepting||s->pending_messages.size()>=s->maximum_pending_messages)return false;s->pending_messages.push_back(m);return true;}
std::vector<AgentMessage> AgentCommunicationEndpoint::drain(){std::lock_guard lock(state_->mutex);std::vector<AgentMessage> out;out.reserve(state_->pending_messages.size());while(!state_->pending_messages.empty()){out.push_back(std::move(state_->pending_messages.front()));state_->pending_messages.pop_front();}return out;}
std::size_t AgentCommunicationEndpoint::pending()const noexcept{std::lock_guard lock(state_->mutex);return state_->pending_messages.size();}
} // namespace jarvis::engineering
