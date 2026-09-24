#include "jarvis/engineering/operator_console.hpp"
#include <utility>
namespace jarvis::engineering {
EngineeringOperatorConsole::EngineeringOperatorConsole(AgentMessageBus&b,std::string id,std::string run,std::string ws,Authorization a,OperatorConsolePolicy p):endpoint_(b,std::move(id),std::move(run),std::move(ws),p.maximum_pending_messages),authorization_(std::move(a)),policy_(p){}
EngineeringOperatorConsole::~EngineeringOperatorConsole()=default;
bool EngineeringOperatorConsole::connected()const noexcept{return endpoint_.registered();} const std::string& EngineeringOperatorConsole::operator_id()const noexcept{return endpoint_.agent_id();} const std::string& EngineeringOperatorConsole::run_id()const noexcept{return endpoint_.run_id();} const std::string& EngineeringOperatorConsole::workspace_id()const noexcept{return endpoint_.workspace_id();}
bool EngineeringOperatorConsole::allowed(AgentMessageType t)const noexcept{switch(t){case AgentMessageType::request:return policy_.allow_requests;case AgentMessageType::query:return policy_.allow_queries;case AgentMessageType::feedback:return policy_.allow_feedback;default:return false;}}
MessageBusResult EngineeringOperatorConsole::send(const OperatorMessage&m){if(!connected())return{false,0,"operator console is not connected"};if(m.recipient_id.empty()||m.correlation_id.empty())return{false,0,"recipient and correlation id are required"};if(!allowed(m.type))return{false,0,"operator message type is not permitted"};if(authorization_&&!authorization_(operator_id(),m.recipient_id,m.type))return{false,0,"operator authorization denied"};const std::string id=m.message_id.empty()?operator_id()+":"+m.correlation_id:m.message_id;return endpoint_.send(id,m.recipient_id,m.correlation_id,m.type,m.payload);}
std::vector<AgentMessage> EngineeringOperatorConsole::receive(){return endpoint_.drain();} std::size_t EngineeringOperatorConsole::pending()const noexcept{return endpoint_.pending();}
} // namespace jarvis::engineering
