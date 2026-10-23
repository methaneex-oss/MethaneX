#include "jarvis/engineering/agent.hpp"
#include "jarvis/engineering/coordinator.hpp"
#include "jarvis/engineering/operator_console.hpp"
#include <cassert>
#include <string>
using namespace jarvis::engineering;
class Builder final : public EngineeringAgent { public: AgentDescriptor descriptor() const override { return {"builder","Builder","test","engineering builder",{"code.edit"},{"workspace.write"},{"source"},{"patch"},0.1,0.95,AgentRisk::medium,AgentAvailability::available,true}; } AgentResult execute(const EngineeringTask&t) override{return {true,descriptor().id,t.id,"built",{},{{"test","passed"}}};} };
int main(){Builder builder; EngineeringCoordinator c; DirectExecutionBoundary boundary; AllowAllAuthorizer auth; EngineeringTask task{"task-1","implement change",{"code.edit"},{"workspace.write"},{"source"},{"patch"},AgentRisk::medium,1.0}; auto ranked=c.rank(task,{builder.descriptor()}); assert(ranked.size()==1&&ranked.front().eligible); auto result=c.dispatch(task,builder,auth,boundary); assert(result.accepted);
AgentMessageBus bus; EngineeringOperatorConsole console(bus,"operator","run-1","workspace-1",[](const std::string&s,const std::string&r,AgentMessageType t){return s=="operator"&&r=="builder"&&t==AgentMessageType::request;}); AgentCommunicationEndpoint peer(bus,"builder","run-1","workspace-1"); assert(console.connected()&&peer.registered()); auto sent=console.send({"m1","task-1","builder",AgentMessageType::request,"inspect and build"}); assert(sent.accepted); auto incoming=peer.drain(); assert(incoming.size()==1&&incoming.front().sender_id=="operator"); auto reply=peer.send("m2","operator","task-1",AgentMessageType::result,"build complete"); assert(reply.accepted); auto received=console.receive(); assert(received.size()==1&&received.front().sender_id=="builder");
    // Bounded queues apply backpressure instead of silently evicting earlier
    // work. A rejected message remains the sender's responsibility to retry.
    AgentCommunicationEndpoint bounded(bus,"bounded","run-1","workspace-1",1);
    assert(bounded.registered());
    auto first=console.send({"m3","task-2","bounded",AgentMessageType::request,"first"});
    assert(first.accepted);
    auto overflow=console.send({"m4","task-3","bounded",AgentMessageType::request,"second"});
    assert(!overflow.accepted);
    assert(overflow.reason.find("backpressure")!=std::string::npos);
    auto preserved=bounded.drain();
    assert(preserved.size()==1&&preserved.front().message_id=="m3");
    auto after_drain=console.send({"m5","task-4","bounded",AgentMessageType::request,"third"});
    assert(after_drain.accepted);
    auto recovered=bounded.drain();
    assert(recovered.size()==1&&recovered.front().message_id=="m5");
    return 0; }
