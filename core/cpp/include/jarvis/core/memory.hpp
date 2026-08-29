#pragma once

#include "event.hpp"

#include <array>
#include <cstddef>
#include <cstdint>
#include <filesystem>
#include <optional>
#include <shared_mutex>
#include <string>
#include <unordered_map>
#include <vector>

namespace jarvis::core {

enum class MemoryTier : std::uint8_t {
    Working = 0,
    Episodic = 1,
    Semantic = 2,
    Procedural = 3,
};

struct MemoryRecord {
    Event event;
    MemoryTier tier{MemoryTier::Episodic};
    double salience{0.5};
    double confidence{0.5};
};

// Memory is continuity. Tier selection, salience and retrieval are learned
// from memory feedback rather than encoded as event-kind rules or fixed
// cognitive weights.
class Memory {
public:
    explicit Memory(std::size_t working_limit = 256,
                    std::filesystem::path journal_path = "data/brain/continuity.bin");

    std::uint64_t append(Event event);
    std::optional<Event> latest() const;
    std::vector<Event> recent(std::size_t limit) const;
    std::vector<Event> recall(const Attributes& query, std::size_t limit = 8) const;
    std::vector<Event> all() const;
    std::vector<Event> by_source(const std::string& source, std::size_t limit = 0) const;
    std::vector<Event> by_kind(const std::string& kind, std::size_t limit = 0) const;

    MemoryTier tier_of(const Event& event) const noexcept;
    std::vector<MemoryRecord> recall_ranked(const Attributes& query, std::size_t limit = 8) const;
    std::vector<MemoryRecord> salient(std::size_t limit = 8, MemoryTier tier = MemoryTier::Episodic) const;
    bool promote(std::uint64_t sequence, MemoryTier tier, double salience, double confidence);
    bool forget_working(std::size_t keep = 0);

    std::size_t size() const noexcept;
    std::size_t working_size() const noexcept;
    std::uint64_t next_sequence() const noexcept;
    const std::filesystem::path& journal_path() const noexcept { return journal_path_; }

private:
    void load();
    bool persist(const Event& event) const;
    static double default_salience(const Event& event) noexcept;
    static double default_confidence(const Event& event) noexcept;
    static std::size_t tier_index(MemoryTier tier) noexcept;

    mutable std::shared_mutex mutex_;
    std::vector<Event> continuity_;
    std::vector<MemoryRecord> metadata_;
    std::size_t working_limit_;
    std::uint64_t next_sequence_{1};
    std::filesystem::path journal_path_;
    std::unordered_map<std::string, std::array<double, 4>> learned_tiers_;
};

} // namespace jarvis::core
