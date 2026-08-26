#include "jarvis/core/memory.hpp"

#include <algorithm>
#include <cstdint>
#include <fstream>
#include <mutex>
#include <type_traits>

namespace jarvis::core {
namespace {

void write_string(std::ostream& out, const std::string& value) {
    const auto size = static_cast<std::uint64_t>(value.size());
    out.write(reinterpret_cast<const char*>(&size), sizeof(size));
    out.write(value.data(), static_cast<std::streamsize>(value.size()));
}

bool read_string(std::istream& in, std::string& value) {
    std::uint64_t size{};
    if (!in.read(reinterpret_cast<char*>(&size), sizeof(size))) return false;
    if (size > (1ULL << 30)) return false;
    value.resize(static_cast<std::size_t>(size));
    return static_cast<bool>(in.read(value.data(), static_cast<std::streamsize>(size)));
}

void write_scalar(std::ostream& out, const Scalar& value) {
    const std::uint8_t tag = static_cast<std::uint8_t>(value.index());
    out.write(reinterpret_cast<const char*>(&tag), sizeof(tag));
    if (const auto p = std::get_if<bool>(&value)) out.write(reinterpret_cast<const char*>(p), sizeof(*p));
    else if (const auto p = std::get_if<std::int64_t>(&value)) out.write(reinterpret_cast<const char*>(p), sizeof(*p));
    else if (const auto p = std::get_if<double>(&value)) out.write(reinterpret_cast<const char*>(p), sizeof(*p));
    else if (const auto p = std::get_if<std::string>(&value)) write_string(out, *p);
}

bool read_scalar(std::istream& in, Scalar& value) {
    std::uint8_t tag{};
    if (!in.read(reinterpret_cast<char*>(&tag), sizeof(tag))) return false;
    switch (tag) {
        case 0: value = std::monostate{}; return true;
        case 1: { bool v{}; if (!in.read(reinterpret_cast<char*>(&v), sizeof(v))) return false; value = v; return true; }
        case 2: { std::int64_t v{}; if (!in.read(reinterpret_cast<char*>(&v), sizeof(v))) return false; value = v; return true; }
        case 3: { double v{}; if (!in.read(reinterpret_cast<char*>(&v), sizeof(v))) return false; value = v; return true; }
        case 4: { std::string v; if (!read_string(in, v)) return false; value = std::move(v); return true; }
        default: return false;
    }
}

void write_event(std::ostream& out, const Event& event) {
    out.write(reinterpret_cast<const char*>(&event.sequence), sizeof(event.sequence));
    out.write(reinterpret_cast<const char*>(&event.timestamp_ns), sizeof(event.timestamp_ns));
    write_string(out, event.source);
    write_string(out, event.kind);
    const auto count = static_cast<std::uint64_t>(event.data.size());
    out.write(reinterpret_cast<const char*>(&count), sizeof(count));
    for (const auto& [key, value] : event.data) {
        write_string(out, key);
        write_scalar(out, value);
    }
}

bool read_event(std::istream& in, Event& event) {
    if (!in.read(reinterpret_cast<char*>(&event.sequence), sizeof(event.sequence))) return false;
    if (!in.read(reinterpret_cast<char*>(&event.timestamp_ns), sizeof(event.timestamp_ns))) return false;
    if (!read_string(in, event.source) || !read_string(in, event.kind)) return false;
    std::uint64_t count{};
    if (!in.read(reinterpret_cast<char*>(&count), sizeof(count)) || count > (1ULL << 20)) return false;
    event.data.clear();
    for (std::uint64_t i = 0; i < count; ++i) {
        std::string key;
        Scalar value;
        if (!read_string(in, key) || !read_scalar(in, value)) return false;
        event.data.emplace(std::move(key), std::move(value));
    }
    return true;
}

} // namespace

Memory::Memory(std::size_t working_limit, std::filesystem::path journal_path)
    : working_limit_(std::max<std::size_t>(1, working_limit)), journal_path_(std::move(journal_path)) {
    load();
}

std::uint64_t Memory::append(Event event) {
    std::unique_lock lock(mutex_);
    if (event.sequence == 0) event.sequence = next_sequence_++;
    else next_sequence_ = std::max(next_sequence_, event.sequence + 1);
    continuity_.push_back(event);
    persist(continuity_.back());
    return continuity_.back().sequence;
}

void Memory::load() {
    std::unique_lock lock(mutex_);
    std::ifstream in(journal_path_, std::ios::binary);
    if (!in) return;
    Event event;
    while (read_event(in, event)) {
        next_sequence_ = std::max(next_sequence_, event.sequence + 1);
        continuity_.push_back(std::move(event));
        event = Event{};
    }
}

void Memory::persist(const Event& event) const {
    std::error_code error;
    if (!journal_path_.parent_path().empty())
        std::filesystem::create_directories(journal_path_.parent_path(), error);
    if (error) return;
    std::ofstream out(journal_path_, std::ios::binary | std::ios::app);
    if (out) write_event(out, event);
}

std::optional<Event> Memory::latest() const {
    std::shared_lock lock(mutex_);
    if (continuity_.empty()) return std::nullopt;
    return continuity_.back();
}

std::vector<Event> Memory::recent(std::size_t limit) const {
    std::shared_lock lock(mutex_);
    const auto count = std::min(limit == 0 ? working_limit_ : limit, continuity_.size());
    return std::vector<Event>(continuity_.end() - static_cast<std::ptrdiff_t>(count), continuity_.end());
}

std::vector<Event> Memory::by_source(const std::string& source, std::size_t limit) const {
    std::shared_lock lock(mutex_);
    std::vector<Event> result;
    for (auto it = continuity_.rbegin(); it != continuity_.rend(); ++it) {
        if (it->source == source) result.push_back(*it);
        if (limit != 0 && result.size() >= limit) break;
    }
    std::reverse(result.begin(), result.end());
    return result;
}

std::vector<Event> Memory::by_kind(const std::string& kind, std::size_t limit) const {
    std::shared_lock lock(mutex_);
    std::vector<Event> result;
    for (auto it = continuity_.rbegin(); it != continuity_.rend(); ++it) {
        if (it->kind == kind) result.push_back(*it);
        if (limit != 0 && result.size() >= limit) break;
    }
    std::reverse(result.begin(), result.end());
    return result;
}

std::size_t Memory::size() const noexcept {
    std::shared_lock lock(mutex_);
    return continuity_.size();
}

std::uint64_t Memory::next_sequence() const noexcept {
    std::shared_lock lock(mutex_);
    return next_sequence_;
}

} // namespace jarvis::core
