#pragma once

#include "attention.hpp"

#include <cstdint>
#include <string>
#include <unordered_map>
#include <vector>

namespace jarvis::core {

struct AttentionContext {
    std::string key;
    double salience{0.0};
    double priority{0.0};
    std::uint64_t last_seen{0};
    std::uint64_t observations{0};
    bool focused{false};
};

class AttentionState {
public:
    void ingest(const AttentionSignal& signal, std::uint64_t cycle);
    void reinforce(const std::string& key, double reward);
    void suppress(const std::string& key, double penalty);
    std::vector<AttentionContext> focus(std::size_t limit) const;
    const AttentionContext* get(const std::string& key) const noexcept;
    void clear();

private:
    std::unordered_map<std::string, AttentionContext> contexts_;
};

} // namespace jarvis::core
