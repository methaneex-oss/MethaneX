#pragma once

#include "agent.hpp"
#include <filesystem>
#include <mutex>
#include <optional>
#include <string>
#include <unordered_map>
#include <vector>

namespace jarvis::engineering {

enum class EngineeringTaskStatus : std::uint8_t {
    queued, claimed, running, blocked, completed, failed
};

struct EngineeringTaskRecord {
    EngineeringTask task;
    EngineeringTaskStatus status{EngineeringTaskStatus::queued};
    std::string assigned_agent_id;
    std::string base_revision;
    std::string result_revision;
    std::string detail;
    std::vector<AgentEvidence> evidence;
    std::uint64_t version{1};
};

// Append-only task history with compare-and-swap transitions. The latest valid
// snapshot for each task is reconstructed on startup; a torn final write is ignored.
class EngineeringTaskLedger {
public:
    explicit EngineeringTaskLedger(std::filesystem::path journal_path);

    bool ready() const noexcept;
    bool create(EngineeringTask task);
    bool claim(const std::string& task_id, std::uint64_t expected_version,
               const std::string& agent_id, const std::string& base_revision);
    bool start(const std::string& task_id, std::uint64_t expected_version,
               const std::string& agent_id);
    bool complete(const std::string& task_id, std::uint64_t expected_version,
                  const std::string& agent_id, const std::string& result_revision,
                  std::vector<AgentEvidence> evidence = {}, std::string detail = {});
    bool fail(const std::string& task_id, std::uint64_t expected_version,
              const std::string& agent_id, std::string detail,
              std::vector<AgentEvidence> evidence = {});
    bool block(const std::string& task_id, std::uint64_t expected_version,
               const std::string& agent_id, std::string detail);
    bool requeue(const std::string& task_id, std::uint64_t expected_version,
                 const std::string& actor_id, std::string detail);

    std::optional<EngineeringTaskRecord> get(const std::string& task_id) const;
    std::vector<EngineeringTaskRecord> list() const;

private:
    bool load();
    bool load_locked() const;
    bool append_record(const EngineeringTaskRecord& record);
    bool commit_record(EngineeringTaskRecord record);
    bool dependencies_completed(const EngineeringTask& task) const;
    std::filesystem::path journal_path_;
    mutable std::mutex mutex_;
    mutable std::unordered_map<std::string, EngineeringTaskRecord> records_;
    mutable bool ready_{true};
};

} // namespace jarvis::engineering
