#pragma once

#include "cognition.hpp"

#include <cstdint>
#include <optional>
#include <string>
#include <unordered_map>
#include <vector>

namespace jarvis::core {

// ExperienceMemory separates semantic identity from individual experience identity.
// The semantic key answers "what is this about?"; the sequence answers "which
// particular experience was this?". This is a foundational primitive for
// developmental learning and must not encode domain-specific behavior.
class ExperienceMemory {
public:
    struct Experience {
        std::uint64_t sequence{0};
        std::string key;
        Prediction prediction{};
        bool resolved{false};
        std::optional<Scalar> actual;
        double error{0.0};
    };

    bool record_prediction(const Prediction& prediction) {
        if (prediction.created_sequence == 0 || prediction.key.empty()) return false;
        Experience experience{};
        experience.sequence = prediction.created_sequence;
        experience.key = prediction.key;
        experience.prediction = prediction;
        experience.resolved = prediction.resolved;
        experience.error = prediction.error;
        experiences_[experience.sequence] = experience;
        by_key_[experience.key].push_back(experience.sequence);
        return true;
    }

    bool resolve(std::uint64_t sequence, const Scalar& actual, double error) {
        const auto it = experiences_.find(sequence);
        if (it == experiences_.end() || it->second.resolved) return false;
        it->second.resolved = true;
        it->second.actual = actual;
        it->second.error = error;
        it->second.prediction.resolved = true;
        it->second.prediction.error = error;
        return true;
    }

    const Experience* get(std::uint64_t sequence) const noexcept {
        const auto it = experiences_.find(sequence);
        return it == experiences_.end() ? nullptr : &it->second;
    }

    const Experience* latest_unresolved(const std::string& key) const noexcept {
        const auto it = by_key_.find(key);
        if (it == by_key_.end()) return nullptr;
        for (auto sequence = it->second.rbegin(); sequence != it->second.rend(); ++sequence) {
            const auto experience = experiences_.find(*sequence);
            if (experience != experiences_.end() && !experience->second.resolved) return &experience->second;
        }
        return nullptr;
    }

    std::vector<const Experience*> for_key(const std::string& key) const {
        std::vector<const Experience*> result;
        const auto it = by_key_.find(key);
        if (it == by_key_.end()) return result;
        result.reserve(it->second.size());
        for (const auto sequence : it->second) {
            const auto experience = experiences_.find(sequence);
            if (experience != experiences_.end()) result.push_back(&experience->second);
        }
        return result;
    }

    std::size_t size() const noexcept { return experiences_.size(); }
    void clear() noexcept { experiences_.clear(); by_key_.clear(); }

private:
    std::unordered_map<std::uint64_t, Experience> experiences_;
    std::unordered_map<std::string, std::vector<std::uint64_t>> by_key_;
};

} // namespace jarvis::core
