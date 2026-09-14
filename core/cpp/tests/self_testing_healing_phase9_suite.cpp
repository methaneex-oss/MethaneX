#include "jarvis/core/brain.hpp"

#include <cassert>
#include <filesystem>
#include <string>

using namespace jarvis::core;

int main() {
    const auto path = std::filesystem::temp_directory_path() / "jarvis_phase9_self_healing.bin";
    std::error_code ec;
    std::filesystem::remove(path, ec);
    std::filesystem::remove(path.string() + ".meta", ec);

    Brain brain(path);
    brain.observe(Event{0, 0, "sensor", "observation", {{"temperature", 25.0}, {"health", 1.0}}});

    const auto healthy = brain.self_test();
    assert(healthy.checks >= 6);
    assert(healthy.failures == 0);
    assert(healthy.healthy());

    brain.observe(Event{0, 0, "database", "observation", {{"health", 0.1}}});
    const auto degraded = brain.recovery_options();
    assert(!degraded.empty());

    bool repaired = false;
    const auto healed = brain.self_heal(
        "database",
        [&](const std::string& component) {
            repaired = component == "database";
            return repaired;
        },
        [&](const std::string& component) {
            const auto* health = brain.self_model().capability(component);
            (void)health;
            return component == "database" && repaired;
        });
    assert(healed.state == HealingState::Recovered);
    assert(repaired);

    Brain restored(path);
    const auto restored_options = restored.recovery_options();
    for (const auto& plan : restored_options) assert(plan.component != "database");
    const auto restored_report = restored.self_test();
    assert(restored_report.healthy());

    std::filesystem::remove(path, ec);
    std::filesystem::remove(path.string() + ".meta", ec);
    return 0;
}
