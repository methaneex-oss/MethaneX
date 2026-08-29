#pragma once

#include "representation.hpp"

#include <cstdint>
#include <memory>
#include <string>
#include <vector>

namespace jarvis::core {

struct PerceptionInput {
    std::uint64_t timestamp_ns{0};
    std::string source;
    std::string kind;
    Attributes payload;
};

struct PerceptionContext {
    std::uint64_t sequence{0};
    std::string session_id;
    Attributes hints;
};

class PerceptionProvider {
public:
    virtual ~PerceptionProvider() = default;
    virtual bool supports(const PerceptionInput& input) const noexcept = 0;
    virtual PerceptualRepresentation perceive(const PerceptionInput& input,
                                               const PerceptionContext& context) const = 0;
};

class PerceptionPipeline {
public:
    void add_provider(std::shared_ptr<const PerceptionProvider> provider);
    PerceptualRepresentation process(const PerceptionInput& input,
                                     const PerceptionContext& context = {}) const;
    bool validate(const PerceptualRepresentation& representation) const noexcept;
    std::size_t provider_count() const noexcept;

private:
    std::vector<std::shared_ptr<const PerceptionProvider>> providers_;
    RepresentationEngine representation_{};
};

} // namespace jarvis::core
