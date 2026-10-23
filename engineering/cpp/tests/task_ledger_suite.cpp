#include "jarvis/engineering/task_ledger.hpp"

#include <cassert>
#include <filesystem>
#include <fstream>
#include <string>

using namespace jarvis::engineering;

int main() {
    const auto path = std::filesystem::temp_directory_path() / "engineering_task_ledger.log";
    std::error_code ec;
    std::filesystem::remove(path, ec);
    EngineeringTask dependency{"inspect", "inspect the current component", {"review"},
        {"repo.read"}, {"source"}, {"report"}, AgentRisk::low, 1.0};
    EngineeringTask followup{"implement", "implement the verified correction", {"code.edit"},
        {"repo.write"}, {"source"}, {"patch"}, AgentRisk::medium, 2.0};
    followup.dependencies = {"inspect"};

    {
        EngineeringTaskLedger ledger(path);
        assert(ledger.ready());
        assert(ledger.create(dependency));
        assert(ledger.create(followup));
        assert(!ledger.claim("implement", 1, "builder", "rev-a"));
        assert(ledger.claim("inspect", 1, "reviewer", "rev-a"));
        assert(!ledger.claim("inspect", 1, "other-reviewer", "rev-a")); // stale CAS
        assert(ledger.start("inspect", 2, "reviewer"));
        assert(ledger.complete("inspect", 3, "reviewer", "rev-b",
                               {{"test", "inspection verified"}}, "ready for implementation"));
        assert(!ledger.complete("inspect", 3, "reviewer", "rev-b")); // stale CAS
        assert(ledger.claim("implement", 1, "builder", "rev-b"));
        assert(ledger.start("implement", 2, "builder"));
        assert(ledger.block("implement", 3, "builder", "waiting for an external dependency"));
        assert(ledger.requeue("implement", 4, "coordinator", "dependency became available"));
        assert(ledger.claim("implement", 5, "builder-2", "rev-b"));
    }

    // A process restart reconstructs the latest task states and evidence.
    {
        EngineeringTaskLedger restored(path);
        assert(restored.ready());
        const auto inspection = restored.get("inspect");
        const auto implementation = restored.get("implement");
        assert(inspection && inspection->status == EngineeringTaskStatus::completed);
        assert(inspection->result_revision == "rev-b");
        assert(inspection->evidence.size() == 1);
        assert(inspection->evidence.front().value == "inspection verified");
        assert(implementation && implementation->status == EngineeringTaskStatus::claimed);
        assert(implementation->assigned_agent_id == "builder-2");
        assert(implementation->base_revision == "rev-b");
        assert(implementation->version == 6);
        assert(restored.list().size() == 2);
    }

    // Ignore only an incomplete final append; preserve every complete record.
    {
        std::ofstream out(path, std::ios::binary | std::ios::app);
        out << "partial-record";
    }
    {
        EngineeringTaskLedger recovered(path);
        assert(recovered.ready());
        assert(recovered.get("inspect")->status == EngineeringTaskStatus::completed);
        assert(recovered.get("implement")->version == 6);
    }
    std::filesystem::remove(path, ec);

    // Independently constructed agent processes can hold stale local snapshots.
    // Mutations must refresh under a shared journal lock before compare-and-swap.
    const auto shared_path =
        std::filesystem::temp_directory_path() / "engineering_task_ledger_shared.log";
    std::filesystem::remove(shared_path, ec);
    std::filesystem::remove(shared_path.string() + ".lock", ec);
    {
        EngineeringTaskLedger coordinator(shared_path);
        EngineeringTask shared_task{"shared-task", "coordinate a shared task", {"review"},
            {"repo.read"}, {"source"}, {"report"}, AgentRisk::low, 1.0};
        assert(coordinator.create(shared_task));
        EngineeringTaskLedger peer(shared_path);
        assert(peer.get("shared-task")->version == 1);

        assert(coordinator.claim("shared-task", 1, "agent-a", "rev-1"));
        assert(!peer.claim("shared-task", 1, "agent-b", "rev-1"));
        const auto peer_view = peer.get("shared-task");
        assert(peer_view && peer_view->version == 2);
        assert(peer_view->status == EngineeringTaskStatus::claimed);
        assert(peer_view->assigned_agent_id == "agent-a");

        EngineeringTask new_task{"visible-task", "share newly created task", {"review"},
            {"repo.read"}, {"source"}, {"report"}, AgentRisk::low, 1.0};
        assert(coordinator.create(new_task));
        assert(peer.get("visible-task").has_value());
        assert(peer.list().size() == 2);
    }
    std::filesystem::remove(shared_path, ec);
    std::filesystem::remove(shared_path.string() + ".lock", ec);
    return 0;
}
