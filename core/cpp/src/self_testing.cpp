#include "jarvis/core/self_testing.hpp"

namespace jarvis::core {

SelfTestReport SelfTestingModel::run(const std::vector<DiagnosticCheck>& checks) const {
    SelfTestReport report;
    report.checks = static_cast<std::uint64_t>(checks.size());
    report.results.reserve(checks.size());
    for (const auto& check : checks) {
        bool passed = false;
        try {
            passed = check.check && check.check();
        } catch (...) {
            passed = false;
        }
        DiagnosticResult result{check.component, check.name,
                                passed ? DiagnosticState::Passed : DiagnosticState::Failed,
                                passed ? "check passed" : "check failed"};
        if (!passed) ++report.failures;
        report.results.push_back(std::move(result));
    }
    return report;
}

SelfHealingResult SelfTestingModel::heal(const std::string& component,
                                         const std::function<bool()>& repair,
                                         const std::function<bool()>& verify) const {
    if (component.empty()) return SelfHealingResult{component, HealingState::RecoveryFailed, "component is empty"};
    if (!repair || !verify) return SelfHealingResult{component, HealingState::RecoveryFailed, "repair and verification are required"};
    if (!repair()) return SelfHealingResult{component, HealingState::RecoveryFailed, "repair attempt failed"};
    if (!verify()) return SelfHealingResult{component, HealingState::RecoveryFailed, "post-repair verification failed"};
    return SelfHealingResult{component, HealingState::Recovered, "repair verified"};
}

} // namespace jarvis::core
