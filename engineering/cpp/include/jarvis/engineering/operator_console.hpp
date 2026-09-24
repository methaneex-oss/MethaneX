#pragma once
#include "message_bus.hpp"
#include <functional>
#include <string>
#include <vector>
namespace jarvis::engineering {
struct OperatorMessage{std::string message_id;std::string correlation_id;std::string recipient_id;AgentMessageType type{AgentMessageType::request};std::string payload;};
struct OperatorConsolePolicy{std::size_t maximum_pending_messages{256};bool allow_requests{true};bool allow_queries{true};bool allow_feedback{true};};
class EngineeringOperatorConsole{public:using Authorization=std::function<bool(const std::string&,const std::string&,AgentMessageType)>;EngineeringOperatorConsole(AgentMessageBus&,std::string,std::string,std::string,Authorization={},OperatorConsolePolicy={});~EngineeringOperatorConsole();EngineeringOperatorConsole(const EngineeringOperatorConsole&)=delete;EngineeringOperatorConsole& operator=(const EngineeringOperatorConsole&)=delete;bool connected()const noexcept;const std::string& operator_id()const noexcept;const std::string& run_id()const noexcept;const std::string& workspace_id()const noexcept;MessageBusResult send(const OperatorMessage&);std::vector<AgentMessage> receive();std::size_t pending()const noexcept;private:bool allowed(AgentMessageType)const noexcept;AgentCommunicationEndpoint endpoint_;Authorization authorization_;OperatorConsolePolicy policy_;};
} // namespace jarvis::engineering
