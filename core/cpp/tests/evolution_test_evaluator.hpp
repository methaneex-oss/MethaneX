#pragma once

#include <cmath>
#include <cstdlib>
#include <iostream>
#include <map>
#include <string>

namespace jarvis::core::test_support {

// Test-only compiled C++ evaluator. It exists to exercise the evaluator protocol;
// production evaluation must use a locally registered evaluator for its workload.
inline bool run_evolution_evaluator_fixture(int argc, char** argv) {
    if (argc < 4 || std::string(argv[1]) != "--test-evaluator") return false;
    double baseline = 0.0;
    double candidate = 0.0;
    try {
        baseline = std::stod(argv[2]);
        candidate = std::stod(argv[3]);
    } catch (...) {
        return true;
    }
    std::map<std::string, std::string> fields;
    for (int i = 4; i < argc; ++i) {
        const std::string argument(argv[i]);
        const auto separator = argument.find('=');
        if (separator == std::string::npos) continue;
        const auto key = argument.substr(0, separator);
        if (key == "--experiment-id" || key == "--parameter-key" ||
            key == "--parameter-value" || key == "--role" ||
            key == "--procedure-id" || key == "--artifact-id")
            fields[key] = argument.substr(separator + 1);
    }
    const auto get = [&](const char* key) -> const std::string& {
        static const std::string empty;
        const auto it = fields.find(key);
        return it == fields.end() ? empty : it->second;
    };
    const std::string role = get("--role");
    if (get("--experiment-id").empty() || get("--parameter-key").empty() ||
        get("--parameter-value").empty() || get("--procedure-id").empty() ||
        get("--artifact-id").empty() || (role != "baseline" && role != "candidate"))
        return true;
    const double parameter_value = std::stod(get("--parameter-value"));
    const double fitness = role == "baseline" ? baseline : candidate;
    if (!std::isfinite(parameter_value) || !std::isfinite(fitness)) return true;
    std::cout << "JARVIS_EVALUATION_V1\\n"
              << "experiment_id=" << get("--experiment-id") << "\\n"
              << "parameter_key=" << get("--parameter-key") << "\\n"
              << "parameter_value=" << get("--parameter-value") << "\\n"
              << "role=" << role << "\\n"
              << "procedure_id=" << get("--procedure-id") << "\\n"
              << "artifact_id=" << get("--artifact-id") << "\\n"
              << "fitness=" << fitness << "\\n";
    return true;
}

} // namespace jarvis::core::test_support
