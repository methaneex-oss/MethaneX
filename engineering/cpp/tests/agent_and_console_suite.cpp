#include "jarvis/engineering/agent.hpp"
#include "jarvis/engineering/coordinator.hpp"
#include "jarvis/engineering/operator_console.hpp"
#include "jarvis/engineering/task_ledger.hpp""
#include <cassert>
#include <filesystem>
#include <string>
using namespace jarvis::engineering;
class Builder final : public EngineeringAgent { public: AgentDescriptor descriptor() const override { return {"builder","Builder","test","engineering builder",{"code.edit"},{"workspace.write"},{"source"},{"patch"},0.1,0.95,AgentRisk::medium,AgentAvailability::available,true}; } AgentResult execute(const EngineeringTask&t) override{return {true,descriptor().id,t.id,"built",{},{{"test","passed"}},"rev-2"};} };
int main(){Builder builder; EngineeringCoordinator c; DirectExecutionBoundary boundary; AllowAllAuthorizer auth; EngineeringTask task{"task-1","implement change",{"code.edit"},{"workspace.write"},{"source"},{"patch"},AgentRisk::medium,1.0}; auto ranked=c.rank(task,{builder.descriptor()}); assert(ranked.size()==1&&ranked.front().eligible); auto result=c.dispatch(task,builder,auth,boundary); assert(result.accepted);
    // Tracked dispatch joins the durable task record to agent execution and
    // records the exact revision and evidence before reporting completion.
    const auto task_journal = std::filesystem::temp_directory_path() / "engineering_tracked_dispatch.log";
    std::error_code task_ec;
    std::filesystem::remove(task_journal, task_ec);
    {
        EngineeringTaskLedger ledger(task_journal);
        EngineeringTask tracked_task = task;
        tracked_task.id = "tracked-task";
        tracked_task.objective = "run a tracked engineering task";
        assert(ledger.create(tracked_task));
        auto tracked = c.dispatch_tracked("tracked-task", builder, auth, boundary, ledger, 1, "rev-1");
        assert(tracked.accepted);
        const auto record = ledger.get("tracked-task");
        assert(record && record->status == EngineeringTaskStatus::completed);
        assert(record->assigned_agent_id == "builder");
        assert(record->base_revision == "rev-1");
        assert(record->result_revision == "rev-2");
        assert(record->evidence.size() == 1 && record->evidence.front().value == "passed");
        assert(record->version == 4);
        auto duplicate_dispatch = c.dispatch_tracked("tracked-task", builder, auth, boundary, ledger, 1, "rev-1");
        assert(!duplicate_dispatch.accepted);
    }
    {
        EngineeringTaskLedger restored(task_journal);
        const auto record = restored.get("tracked-task");
        assert(restored.ready() && record);
        assert(record->status == EngineeringTaskStatus::completed);
        assert(record->result_revision == "rev-2");
    }
    std::filesystem::remove(task_journal, task_ec);
AgentMessageBus bus; EngineeringOperatorConsole console(bus,"operator","run-1","workspace-1",[](const std::string&s,const std::string&r,AgentMessageType t){return s=="operator"&&r=="builder"&&t==AgentMessageType::request;}); AgentCommunicationEndpoint peer(bus,"builder","run-1","workspace-1"); assert(console.connected()&&peer.registered()); auto sent=console.send({"m1","task-1","builder",AgentMessageType::request,"inspect and build"}); assert(sent.accepted); auto incoming=peer.drain(); assert(incoming.size()==1&&incoming.front().sender_id=="operator"); auto reply=peer.send("m2","operator","task-1",AgentMessageType::result,"build complete"); assert(reply.accepted); auto received=console.receive(); assert(received.size()==1&&received.front().sender_id=="builder");
    // Bounded queues apply backpressure instead of silently evicting earlier
    // work. A rejected message remains the sender's responsibility to retry.
    AgentCommunicationEndpoint bounded(bus,"bounded","run-1","workspace-1",1);
    AgentCommunicationEndpoint bounded_sender(bus,"bounded-sender","run-1","workspace-1");
    assert(bounded.registered()&&bounded_sender.registered());
    auto first=bounded_sender.send("m3","bounded","task-2",AgentMessageType::request,"first");
    assert(first.accepted);
    auto overflow=bounded_sender.send("m4","bounded","task-3",AgentMessageType::request,"second");
    assert(!overflow.accepted);
    assert(overflow.reason.find("backpressure")!=std::string::npos);
    auto preserved=bounded.drain();
    assert(preserved.size()==1&&preserved.front().message_id=="m3");
    auto after_drain=bounded_sender.send("m5","bounded","task-4",AgentMessageType::request,"third");
    assert(after_drain.accepted);
    auto recovered=bounded.drain();
    assert(recovered.size()==1&&recovered.front().message_id=="m5");
    return 0; }
