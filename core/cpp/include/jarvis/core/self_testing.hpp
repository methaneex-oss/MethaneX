#pragma once

#include <cstdint>
#include <functional>
#include <string>
#include <vector>

namespace jarvis::core {

enum class DiagnosticState { Passed, Failed };

enum class HealingState { NotRequired, Isolated, Recovered, RecoveryFailed };

struct DiagnosticResult {
    std::string component;
    std::string check;
    DiagnosticState state{DiagnosticState::Passed};
    std::string detail;
};

struct SelfTestReport {
    std::uint64_t checks{0};
    std::uint64_t failures{0};
    std::vector<DiagnosticResult> results;
    bool healthy() const noexcept { return failures == 0; }
};

struct SelfHealingResult {
    std::string component;
    HealingState state{HealingState::NotRequired};
    std::string detail;
};

struct DiagnosticCheck {
    std::string component;
    std::string name;
    std::function<bool()> check;
};

class SelfTestingModel {
public:
    SelfTestReport run(const std::vector<DiagnosticCheck>& checks) const;
    SelfHealingResult heal(const std::string& component,
                           const std::function<bool()>& repair,
                           const std::function<bool()>& verify) const;
};

} // namespace jarvis::core
