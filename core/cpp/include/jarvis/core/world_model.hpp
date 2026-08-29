#pragma once

#include "event.hpp"
#include <cstdint>
#include <optional>
#include <shared_mutex>
#include <string>
#include <vector>

namespace jarvis::core {

struct Fact {
    std::string subject;
    std::string predicate;
    Scalar value;
    double confidence{0.5};
    std::uint64_t observations{1};
    std::uint64_t first_sequence{0};
    std::uint64_t updated_sequence{0};
    bool disputed{false};
};

struct Relation {
    std::string from;
    std::string type;
    std::string to;
    double confidence{0.5};
    std::uint64_t updated_sequence{0};
    bool disputed{false};
};

class WorldModel {
public:
    void observe(const Fact& fact);
    void relate(const Relation& relation);
    std::optional<Fact> query(const std::string& subject, const std::string& predicate) const;
    std::vector<Relation> relations_from(const std::string& subject) const;
    std::vector<Fact> facts() const;
    std::vector<Fact> disputed_facts() const;
    void clear();

private:
    std::vector<Fact> facts_;
    std::vector<Relation> relations_;
    mutable std::shared_mutex mutex_;
};

} // namespace jarvis::core
