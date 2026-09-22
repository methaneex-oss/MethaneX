#include "jarvis/engineering/scheduler.hpp"

#include <atomic>
#include <cassert>
#include <chrono>
#include <string>
#include <thread>
#include <utility>
#include <vector>

using namespace jarvis::engineering;

namespace {

class SchedulerAgent final : public EngineeringAgent {
public:
    explicit SchedulerAgent(std::string id, bool concurrent, bool accept = true)
        : id_(std::move(id)), concurrent_(concurrent), accept_(accept) {}

    AgentDescriptor descriptor() const override {
        return AgentDescriptor{
            id_, id_, "test", "scheduler fixture",
            {"engineering"}, {"workspace.read"}, {"source"}, {"report"},
            0.1, 1.0, AgentRisk::low, AgentAvailability::available, concurrent_};
    }

    AgentResult execute(const EngineeringTask& task) override {
        saw_prior_artifact_ = !task.prior_stage_artifacts.empty();
        if (!accept_) return {false, id_, task.id, "intentional failure", {}, {}};
        return {true, id_, task.id, "ok",
                {{"report", "memory/report", "digest"}},
                {{"scheduler", "executed"}}};
    }

    bool saw_prior_artifact() const noexcept { return saw_prior_artifact_; }

private:
    std::string id_;
    bool concurrent_;
    bool accept_;
    bool saw_prior_artifact_{false};
};

class ParallelSchedulerAgent final : public EngineeringAgent {
public:
    ParallelSchedulerAgent(
        std::string id,
        std::atomic<int>& active,
        std::atomic<int>& maximum_active)
        : id_(std::move(id)), active_(active), maximum_active_(maximum_active) {}

    AgentDescriptor descriptor() const override {
        return AgentDescriptor{
            id_, id_, "test", "parallel scheduler fixture",
            {"engineering"}, {"workspace.read"}, {"source"}, {"report"},
            0.1, 1.0, AgentRisk::low, AgentAvailability::available, true};
    }

    AgentResult execute(const EngineeringTask& task) override {
        const int current = active_.fetch_add(1) + 1;
        int observed = maximum_active_.load();
        while (current > observed &&
               !maximum_active_.compare_exchange_weak(observed, current)) {
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(40));
        active_.fetch_sub(1);
        return {true, id_, task.id, "parallel ok", {}, {}};
    }

private:
    std::string id_;
    std::atomic<int>& active_;
    std::atomic<int>& maximum_active_;
};

EngineeringStageTask stage(
    std::string id,
    std::string agent,
    std::vector<std::string> dependencies,
    std::vector<std::string> files) {
    EngineeringTask task{
        std::move(id), "work", {"engineering"}, {"workspace.read"},
        {"source"}, {"report"}, AgentRisk::low, 1.0};
    task.dependencies = std::move(dependencies);
    task.workspace_files = std::move(files);
    return {EngineeringStage::implementation, std::move(task), std::move(agent)};
}

} // namespace

int main() {
    SchedulerAgent a("agent.a", true);
    SchedulerAgent b("agent.b", true);
    SchedulerAgent c("agent.c", true);
    EngineeringScheduler scheduler;

    const auto parallel = scheduler.plan(
        {stage("a", "agent.a", {}, {"src/a.cpp"}),
         stage("b", "agent.b", {}, {"src/b.cpp"}),
         stage("c", "agent.c", {"a", "b"}, {"src/c.cpp"})},
        {&a, &b, &c});
    assert(parallel.status == EngineeringScheduleStatus::valid);
    assert(parallel.waves.size() == 2);
    assert(parallel.waves[0].stage_indices.size() == 2);
    assert(parallel.waves[0].parallel_safe);
    assert(parallel.waves[1].stage_indices.size() == 1);

    const auto overlap = scheduler.plan(
        {stage("a", "agent.a", {}, {"src/shared.cpp"}),
         stage("b", "agent.b", {}, {"src/shared.cpp"})},
        {&a, &b});
    assert(overlap.status == EngineeringScheduleStatus::valid);
    assert(!overlap.waves[0].parallel_safe);

    SchedulerAgent serial("agent.serial", false);
    const auto serial_plan = scheduler.plan(
        {stage("a", "agent.a", {}, {"src/a.cpp"}),
         stage("b", "agent.serial", {}, {"src/b.cpp"})},
        {&a, &serial});
    assert(serial_plan.status == EngineeringScheduleStatus::valid);
    assert(!serial_plan.waves[0].parallel_safe);

    const auto missing = scheduler.plan(
        {stage("a", "agent.a", {"missing"}, {"src/a.cpp"})}, {&a});
    assert(missing.status == EngineeringScheduleStatus::invalid);
    assert(missing.reason == "engineering stage dependency not found");

    const auto cycle = scheduler.plan(
        {stage("a", "agent.a", {"b"}, {"src/a.cpp"}),
         stage("b", "agent.b", {"a"}, {"src/b.cpp"})},
        {&a, &b});
    assert(cycle.status == EngineeringScheduleStatus::invalid);
    assert(cycle.reason == "engineering stage dependency cycle detected");

    AllowAllAuthorizer authorizer;
    DirectExecutionBoundary boundary;
    SchedulerAgent producer("producer", true);
    SchedulerAgent consumer("consumer", true);
    const auto execution = scheduler.execute(
        {stage("producer", "producer", {}, {"src/producer.cpp"}),
         stage("consumer", "consumer", {"producer"}, {"src/consumer.cpp"})},
        {&producer, &consumer}, authorizer, boundary);
    assert(execution.accepted);
    assert(execution.nodes.size() == 2);
    assert(execution.nodes[0].status == EngineeringNodeStatus::completed);
    assert(execution.nodes[1].status == EngineeringNodeStatus::completed);
    assert(consumer.saw_prior_artifact());

    std::atomic<int> active{0};
    std::atomic<int> maximum_active{0};
    ParallelSchedulerAgent parallel_a("parallel.a", active, maximum_active);
    ParallelSchedulerAgent parallel_b("parallel.b", active, maximum_active);
    const auto concurrent_execution = scheduler.execute(
        {stage("parallel.a", "parallel.a", {}, {"src/parallel_a.cpp"}),
         stage("parallel.b", "parallel.b", {}, {"src/parallel_b.cpp"})},
        {&parallel_a, &parallel_b}, authorizer, boundary,
        EngineeringSchedulerPolicy{2, true});
    assert(concurrent_execution.accepted);
    assert(concurrent_execution.nodes.size() == 2);
    assert(maximum_active.load() == 2);

    SchedulerAgent failing("failing", true, false);
    SchedulerAgent blocked("blocked", true);
    const auto failed = scheduler.execute(
        {stage("failing", "failing", {}, {"src/failing.cpp"}),
         stage("blocked", "blocked", {"failing"}, {"src/blocked.cpp"})},
        {&failing, &blocked}, authorizer, boundary);
    assert(!failed.accepted);
    assert(failed.nodes.size() == 2);
    assert(failed.nodes[0].status == EngineeringNodeStatus::rejected);
    assert(failed.nodes[1].status == EngineeringNodeStatus::blocked);
    assert(failed.nodes[1].blocking_dependencies.size() == 1);
    assert(failed.nodes[1].blocking_dependencies[0] == "failing");

    return 0;
}
