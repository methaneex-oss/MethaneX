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
    return 0;
}
