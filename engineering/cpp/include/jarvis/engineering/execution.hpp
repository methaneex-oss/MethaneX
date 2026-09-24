#pragma once

#include "agent.hpp"

namespace jarvis::engineering {

class EngineeringAuthorizer {
public:
    virtual ~EngineeringAuthorizer() = default;
    virtual bool authorize(const EngineeringTask& task,
                           const AgentDescriptor& agent) const = 0;
};

class EngineeringExecutionBoundary {
public:
    virtual ~EngineeringExecutionBoundary() = default;
    virtual AgentResult run(const EngineeringTask& task,
                            EngineeringAgent& agent) = 0;
};

class DirectExecutionBoundary final : public EngineeringExecutionBoundary {
public:
    AgentResult run(const EngineeringTask& task, EngineeringAgent& agent) override;
};

class AllowAllAuthorizer final : public EngineeringAuthorizer {
public:
    bool authorize(const EngineeringTask&, const AgentDescriptor&) const override {
        return true;
    }
};

} // namespace jarvis::engineering
