#include "jarvis/engineering/task_ledger.hpp"

#include <algorithm>
#include <cmath>
#include <fstream>
#include <iterator>
#include <iomanip>
#include <limits>
#include <sstream>
#include <system_error>
#ifdef _WIN32
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <windows.h>
#else
#include <fcntl.h>
#include <sys/file.h>
#include <unistd.h>
#endif

namespace jarvis::engineering {
namespace {

class JournalFileLock {
public:
    explicit JournalFileLock(const std::filesystem::path& journal_path) {
        auto lock_path = journal_path;
        lock_path += ".lock";
#ifdef _WIN32
        handle_ = CreateFileW(lock_path.c_str(), GENERIC_READ | GENERIC_WRITE,
                              FILE_SHARE_READ | FILE_SHARE_WRITE, nullptr,
                              OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
        if (handle_ == INVALID_HANDLE_VALUE) return;
        if (LockFileEx(handle_, LOCKFILE_EXCLUSIVE_LOCK, 0, MAXDWORD, MAXDWORD,
                       &overlapped_) != 0) {
            locked_ = true;
        } else {
            CloseHandle(handle_);
            handle_ = INVALID_HANDLE_VALUE;
        }
#else
        descriptor_ = ::open(lock_path.c_str(), O_CREAT | O_RDWR, 0600);
        if (descriptor_ < 0) return;
        if (::flock(descriptor_, LOCK_EX) == 0) {
            locked_ = true;
        } else {
            ::close(descriptor_);
            descriptor_ = -1;
        }
#endif
    }

    ~JournalFileLock() {
#ifdef _WIN32
        if (handle_ != INVALID_HANDLE_VALUE) {
            if (locked_) UnlockFileEx(handle_, 0, MAXDWORD, MAXDWORD, &overlapped_);
            CloseHandle(handle_);
        }
#else
        if (descriptor_ >= 0) {
            if (locked_) ::flock(descriptor_, LOCK_UN);
            ::close(descriptor_);
        }
#endif
    }

    JournalFileLock(const JournalFileLock&) = delete;
    JournalFileLock& operator=(const JournalFileLock&) = delete;
    bool locked() const noexcept { return locked_; }

private:
#ifdef _WIN32
    HANDLE handle_{INVALID_HANDLE_VALUE};
    OVERLAPPED overlapped_{};
#else
    int descriptor_{-1};
#endif
    bool locked_{false};
};

std::string hex_encode(const std::string& value) {
    static constexpr char digits[] = "0123456789abcdef";
    std::string out;
    out.reserve(value.size() * 2);
    for (unsigned char c : value) {
        out.push_back(digits[c >> 4]);
        out.push_back(digits[c & 0x0f]);
    }
    return out;
}

bool hex_decode(const std::string& value, std::string& out) {
    if (value.size() % 2 != 0) return false;
    auto nibble = [](char c) -> int {
        if (c >= '0' && c <= '9') return c - '0';
        if (c >= 'a' && c <= 'f') return c - 'a' + 10;
        if (c >= 'A' && c <= 'F') return c - 'A' + 10;
        return -1;
    };
    out.clear();
    out.reserve(value.size() / 2);
    for (std::size_t i = 0; i < value.size(); i += 2) {
        const int high = nibble(value[i]), low = nibble(value[i + 1]);
        if (high < 0 || low < 0) return false;
        out.push_back(static_cast<char>((high << 4) | low));
    }
    return true;
}

std::vector<std::string> split_fields(const std::string& line) {
    std::vector<std::string> fields;
    std::size_t begin = 0;
    for (;;) {
        const auto end = line.find('|', begin);
        if (end == std::string::npos) {
            fields.push_back(line.substr(begin));
            break;
        }
        fields.push_back(line.substr(begin, end - begin));
        begin = end + 1;
    }
    return fields;
}

std::string number(double value) {
    std::ostringstream out;
    out << std::setprecision(std::numeric_limits<double>::max_digits10) << value;
    return out.str();
}

template <typename T>
bool parse_integer(const std::string& value, T& out) {
    try {
        std::size_t used = 0;
        const auto parsed = std::stoull(value, &used);
        if (used != value.size()) return false;
        out = static_cast<T>(parsed);
        return true;
    } catch (...) { return false; }
}

bool parse_double(const std::string& value, double& out) {
    try {
        std::size_t used = 0;
        out = std::stod(value, &used);
        return used == value.size() && std::isfinite(out);
    } catch (...) { return false; }
}

void append_list(std::vector<std::string>& fields,
                 const std::vector<std::string>& values) {
    fields.push_back(std::to_string(values.size()));
    fields.insert(fields.end(), values.begin(), values.end());
}

bool read_list(const std::vector<std::string>& fields, std::size_t& index,
               std::vector<std::string>& values) {
    if (index >= fields.size()) return false;
    std::size_t count = 0;
    if (!parse_integer(fields[index++], count) || count > fields.size() - index) return false;
    values.clear();
    values.reserve(count);
    for (std::size_t i = 0; i < count; ++i) values.push_back(fields[index++]);
    return true;
}

std::string serialize(const EngineeringTaskRecord& r) {
    std::vector<std::string> fields{
        "1", r.task.id, r.task.objective,
        std::to_string(static_cast<unsigned>(r.task.maximum_risk)),
        number(r.task.maximum_cost)
    };
    append_list(fields, r.task.required_capabilities);
    append_list(fields, r.task.required_permissions);
    append_list(fields, r.task.input_artifacts);
    append_list(fields, r.task.expected_artifacts);
    append_list(fields, r.task.dependencies);
    fields.push_back(std::to_string(static_cast<unsigned>(r.status)));
    fields.push_back(r.assigned_agent_id);
    fields.push_back(r.base_revision);
    fields.push_back(r.result_revision);
    fields.push_back(r.detail);
    fields.push_back(std::to_string(r.version));
    fields.push_back(std::to_string(r.evidence.size()));
    for (const auto& e : r.evidence) {
        fields.push_back(e.kind);
        fields.push_back(e.value);
    }
    std::ostringstream out;
    for (std::size_t i = 0; i < fields.size(); ++i) {
        if (i) out << '|';
        out << hex_encode(fields[i]);
    }
    return out.str();
}

bool deserialize(const std::string& line, EngineeringTaskRecord& r) {
    std::vector<std::string> fields;
    for (const auto& encoded : split_fields(line)) {
        std::string decoded;
        if (!hex_decode(encoded, decoded)) return false;
        fields.push_back(std::move(decoded));
    }
    std::size_t i = 0;
    if (fields.size() < 17 || fields[i++] != "1") return false;
    r.task.id = fields[i++];
    r.task.objective = fields[i++];
    unsigned risk = 0;
    if (!parse_integer(fields[i++], risk) ||
        risk > static_cast<unsigned>(AgentRisk::critical) ||
        !parse_double(fields[i++], r.task.maximum_cost)) return false;
    r.task.maximum_risk = static_cast<AgentRisk>(risk);
    if (!read_list(fields, i, r.task.required_capabilities) ||
        !read_list(fields, i, r.task.required_permissions) ||
        !read_list(fields, i, r.task.input_artifacts) ||
        !read_list(fields, i, r.task.expected_artifacts) ||
        !read_list(fields, i, r.task.dependencies) || i >= fields.size()) return false;
    unsigned status = 0;
    if (!parse_integer(fields[i++], status) ||
        status > static_cast<unsigned>(EngineeringTaskStatus::failed) ||
        fields.size() - i < 6) return false;
    r.status = static_cast<EngineeringTaskStatus>(status);
    r.assigned_agent_id = fields[i++];
    r.base_revision = fields[i++];
    r.result_revision = fields[i++];
    r.detail = fields[i++];
    if (!parse_integer(fields[i++], r.version) || r.version == 0) return false;
    std::size_t evidence_count = 0;
    if (!parse_integer(fields[i++], evidence_count) ||
        evidence_count > (fields.size() - i) / 2 ||
        fields.size() - i != evidence_count * 2) return false;
    r.evidence.clear();
    r.evidence.reserve(evidence_count);
    for (std::size_t n = 0; n < evidence_count; ++n)
        r.evidence.push_back({fields[i++], fields[i++]});
    return valid_task(r.task) && !r.task.id.empty();
}

} // namespace

EngineeringTaskLedger::EngineeringTaskLedger(std::filesystem::path path)
    : journal_path_(std::move(path)) {
    if (journal_path_.empty()) { ready_ = false; return; }
    std::error_code ec;
    const auto parent = journal_path_.parent_path();
    if (!parent.empty()) std::filesystem::create_directories(parent, ec);
    if (ec) { ready_ = false; return; }
    ready_ = load();
}

bool EngineeringTaskLedger::ready() const noexcept {
    std::lock_guard lock(mutex_);
    return ready_;
}

bool EngineeringTaskLedger::load() {
    JournalFileLock file_lock(journal_path_);
    return file_lock.locked() && load_locked();
}

bool EngineeringTaskLedger::load_locked() const {
    records_.clear();
    std::ifstream input(journal_path_, std::ios::binary);
    if (!input) {
        std::error_code ec;
        if (std::filesystem::exists(journal_path_, ec) || ec) return false;
        return true;
    }
    const std::string contents((std::istreambuf_iterator<char>(input)),
                               std::istreambuf_iterator<char>());
    if (input.bad()) return false;
    const bool has_torn_tail = !contents.empty() && contents.back() != '\n';
    const auto complete_size = has_torn_tail ? contents.rfind('\n') + 1 : contents.size();
    std::size_t begin = 0;
    while (begin < contents.size()) {
        const auto end = contents.find('\n', begin);
        if (end == std::string::npos) break;
        const auto line = contents.substr(begin, end - begin);
        begin = end + 1;
        if (line.empty()) continue;
        EngineeringTaskRecord record;
        if (!deserialize(line, record)) return false;
        const auto it = records_.find(record.task.id);
        if (it == records_.end()) {
            if (record.version != 1 || record.status != EngineeringTaskStatus::queued ||
                !record.assigned_agent_id.empty()) return false;
        } else {
            if (record.version != it->second.version + 1 ||
                record.task.id != it->second.task.id ||
                record.task.objective != it->second.task.objective ||
                record.task.dependencies != it->second.task.dependencies) return false;
        }
        records_[record.task.id] = std::move(record);
    }
    if (has_torn_tail) {
        std::error_code ec;
        std::filesystem::resize_file(journal_path_, complete_size, ec);
        if (ec) return false;
    }
    return true;
}

bool EngineeringTaskLedger::append_record(const EngineeringTaskRecord& record) {
    std::ofstream output(journal_path_, std::ios::binary | std::ios::app);
    if (!output) return false;
    output << serialize(record) << '\n';
    output.flush();
    return output.good();
}

bool EngineeringTaskLedger::commit_record(EngineeringTaskRecord record) {
    if (!ready_ || !append_record(record)) {
        ready_ = false;
        return false;
    }
    records_[record.task.id] = std::move(record);
    return true;
}

bool EngineeringTaskLedger::dependencies_completed(const EngineeringTask& task) const {
    for (const auto& id : task.dependencies) {
        const auto it = records_.find(id);
        if (it == records_.end() || it->second.status != EngineeringTaskStatus::completed)
            return false;
    }
    return true;
}

bool EngineeringTaskLedger::create(EngineeringTask task) {
    std::lock_guard lock(mutex_);
    if (!ready_) return false;
    JournalFileLock file_lock(journal_path_);
    if (!file_lock.locked()) return false;
    if (!load_locked()) { ready_ = false; return false; }
    if (!valid_task(task) || records_.contains(task.id)) return false;
    std::vector<std::string> unique;
    for (const auto& dependency : task.dependencies) {
        if (dependency.empty() || dependency == task.id ||
            std::find(unique.begin(), unique.end(), dependency) != unique.end() ||
            !records_.contains(dependency)) return false;
        unique.push_back(dependency);
    }
    EngineeringTaskRecord record;
    record.task = std::move(task);
    return commit_record(std::move(record));
}

bool EngineeringTaskLedger::claim(const std::string& id, std::uint64_t expected,
                                  const std::string& agent, const std::string& revision) {
    std::lock_guard lock(mutex_);
    if (!ready_) return false;
    JournalFileLock file_lock(journal_path_);
    if (!file_lock.locked()) return false;
    if (!load_locked()) { ready_ = false; return false; }
    auto it = records_.find(id);
    if (!ready_ || it == records_.end() || it->second.version != expected ||
        it->second.status != EngineeringTaskStatus::queued || agent.empty() ||
        !dependencies_completed(it->second.task)) return false;
    auto record = it->second;
    record.status = EngineeringTaskStatus::claimed;
    record.assigned_agent_id = agent;
    record.base_revision = revision;
    ++record.version;
    return commit_record(std::move(record));
}

bool EngineeringTaskLedger::start(const std::string& id, std::uint64_t expected,
                                  const std::string& agent) {
    std::lock_guard lock(mutex_);
    if (!ready_) return false;
    JournalFileLock file_lock(journal_path_);
    if (!file_lock.locked()) return false;
    if (!load_locked()) { ready_ = false; return false; }
    auto it = records_.find(id);
    if (!ready_ || it == records_.end() || it->second.version != expected ||
        it->second.status != EngineeringTaskStatus::claimed ||
        it->second.assigned_agent_id != agent) return false;
    auto record = it->second;
    record.status = EngineeringTaskStatus::running;
    ++record.version;
    return commit_record(std::move(record));
}

bool EngineeringTaskLedger::complete(const std::string& id, std::uint64_t expected,
                                     const std::string& agent, const std::string& revision,
                                     std::vector<AgentEvidence> evidence, std::string detail) {
    std::lock_guard lock(mutex_);
    if (!ready_) return false;
    JournalFileLock file_lock(journal_path_);
    if (!file_lock.locked()) return false;
    if (!load_locked()) { ready_ = false; return false; }
    auto it = records_.find(id);
    if (!ready_ || it == records_.end() || it->second.version != expected ||
        it->second.status != EngineeringTaskStatus::running ||
        it->second.assigned_agent_id != agent) return false;
    auto record = it->second;
    record.status = EngineeringTaskStatus::completed;
    record.result_revision = revision;
    record.evidence = std::move(evidence);
    record.detail = std::move(detail);
    ++record.version;
    return commit_record(std::move(record));
}

bool EngineeringTaskLedger::fail(const std::string& id, std::uint64_t expected,
                                 const std::string& agent, std::string detail,
                                 std::vector<AgentEvidence> evidence) {
    std::lock_guard lock(mutex_);
    if (!ready_) return false;
    JournalFileLock file_lock(journal_path_);
    if (!file_lock.locked()) return false;
    if (!load_locked()) { ready_ = false; return false; }
    auto it = records_.find(id);
    if (!ready_ || it == records_.end() || it->second.version != expected ||
        (it->second.status != EngineeringTaskStatus::running &&
         it->second.status != EngineeringTaskStatus::claimed) ||
        it->second.assigned_agent_id != agent) return false;
    auto record = it->second;
    record.status = EngineeringTaskStatus::failed;
    record.detail = std::move(detail);
    record.evidence = std::move(evidence);
    ++record.version;
    return commit_record(std::move(record));
}

bool EngineeringTaskLedger::block(const std::string& id, std::uint64_t expected,
                                  const std::string& agent, std::string detail) {
    std::lock_guard lock(mutex_);
    if (!ready_) return false;
    JournalFileLock file_lock(journal_path_);
    if (!file_lock.locked()) return false;
    if (!load_locked()) { ready_ = false; return false; }
    auto it = records_.find(id);
    if (!ready_ || it == records_.end() || it->second.version != expected ||
        (it->second.status != EngineeringTaskStatus::running &&
         it->second.status != EngineeringTaskStatus::claimed) ||
        it->second.assigned_agent_id != agent) return false;
    auto record = it->second;
    record.status = EngineeringTaskStatus::blocked;
    record.detail = std::move(detail);
    ++record.version;
    return commit_record(std::move(record));
}

bool EngineeringTaskLedger::requeue(const std::string& id, std::uint64_t expected,
                                    const std::string& actor, std::string detail) {
    std::lock_guard lock(mutex_);
    if (!ready_) return false;
    JournalFileLock file_lock(journal_path_);
    if (!file_lock.locked()) return false;
    if (!load_locked()) { ready_ = false; return false; }
    auto it = records_.find(id);
    if (!ready_ || it == records_.end() || it->second.version != expected ||
        (it->second.status != EngineeringTaskStatus::blocked &&
         it->second.status != EngineeringTaskStatus::failed) || actor.empty()) return false;
    auto record = it->second;
    record.status = EngineeringTaskStatus::queued;
    record.assigned_agent_id.clear();
    record.base_revision.clear();
    record.result_revision.clear();
    record.detail = std::move(detail);
    ++record.version;
    return commit_record(std::move(record));
}

std::optional<EngineeringTaskRecord> EngineeringTaskLedger::get(const std::string& id) const {
    std::lock_guard lock(mutex_);
    if (!ready_) return std::nullopt;
    JournalFileLock file_lock(journal_path_);
    if (!file_lock.locked()) return std::nullopt;
    if (!load_locked()) { ready_ = false; return std::nullopt; }
    const auto it = records_.find(id);
    if (it == records_.end()) return std::nullopt;
    return it->second;
}

std::vector<EngineeringTaskRecord> EngineeringTaskLedger::list() const {
    std::lock_guard lock(mutex_);
    if (!ready_) return {};
    JournalFileLock file_lock(journal_path_);
    if (!file_lock.locked()) return {};
    if (!load_locked()) { ready_ = false; return {}; }
    std::vector<EngineeringTaskRecord> out;
    out.reserve(records_.size());
    for (const auto& item : records_) out.push_back(item.second);
    std::sort(out.begin(), out.end(), [](const auto& a, const auto& b) {
        return a.task.id < b.task.id;
    });
    return out;
}

} // namespace jarvis::engineering
