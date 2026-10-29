#include "jarvis/core/evolution_evaluation_protocol.hpp"

#include <cmath>
#include <cstdint>
#include <iostream>
#include <random>
#include <sstream>
#include <string>
#include <vector>

using namespace jarvis::core;
using namespace jarvis::core::evolution_eval_detail;

namespace {
bool parse_double(const char* text, double& value) {
    try {
        std::size_t used = 0;
        value = std::stod(text, &used);
        return used == std::string(text).size() && std::isfinite(value);
    } catch (...) {
        return false;
    }
}

bool parse_u64(const char* text, std::uint64_t& value) {
    try {
        std::size_t used = 0;
        const auto parsed = std::stoull(text, &used);
        if (used != std::string(text).size()) return false;
        value = static_cast<std::uint64_t>(parsed);
        return true;
    } catch (...) {
        return false;
    }
}

bool parse_csv(const char* text, std::vector<double>& values) {
    std::stringstream stream(text);
    std::string item;
    while (std::getline(stream, item, ',')) {
        double value = 0.0;
        if (item.empty() || !parse_double(item.c_str(), value)) return false;
        values.push_back(value);
    }
    return !values.empty() && values.size() <= 256;
}
} // namespace

int main(int argc, char** argv) {
    // Protocol:
    // --evaluate-v1 EXPERIMENT KEY CANDIDATE_ID CANDIDATE_DIGEST BASELINE_DIGEST
    // PROCEDURE PROCEDURE_DIGEST BASELINE_VALUE CANDIDATE_VALUE ROLE TRIAL SEED
    // INPUTS_CSV TARGETS_CSV REQUEST_DIGEST
    if (argc != 17 || std::string(argv[1]) != "--evaluate-v1") return 64;

    const std::string experiment_id = argv[2];
    const std::string key = argv[3];
    const std::string candidate_id = argv[4];
    const std::string candidate_digest = argv[5];
    const std::string baseline_digest = argv[6];
    const std::string procedure_id = argv[7];
    const std::string procedure_hash = argv[8];
    const std::string role = argv[11];
    if (!safe_token(experiment_id) || !safe_token(key) ||
        !safe_token(candidate_id) || !safe_token(procedure_id) ||
        (role != "baseline" && role != "candidate")) return 65;

    double baseline_value = 0.0;
    double candidate_value = 0.0;
    if (!parse_double(argv[9], baseline_value) ||
        !parse_double(argv[10], candidate_value)) return 66;
    std::uint64_t trial_index_u64 = 0;
    std::uint64_t seed = 0;
    if (!parse_u64(argv[12], trial_index_u64) ||
        !parse_u64(argv[13], seed) ||
        trial_index_u64 > 100000U) return 67;
    const auto trial_index = static_cast<std::size_t>(trial_index_u64);

    std::vector<double> inputs;
    std::vector<double> targets;
    if (!parse_csv(argv[14], inputs) || !parse_csv(argv[15], targets) ||
        inputs.size() != targets.size()) return 68;
    for (const double value : inputs) if (!std::isfinite(value)) return 69;
    for (const double value : targets) if (!std::isfinite(value)) return 69;

    const auto descriptor = procedure_descriptor(procedure_id);
    if (descriptor.empty() || sha256(descriptor) != procedure_hash) return 70;
    const auto expected_candidate_digest =
        configuration_digest(key, candidate_value, procedure_id, inputs, targets);
    const auto expected_baseline_digest =
        configuration_digest(key, baseline_value, procedure_id, inputs, targets);
    if (candidate_digest != expected_candidate_digest ||
        baseline_digest != expected_baseline_digest ||
        candidate_id != "candidate:" + expected_candidate_digest) return 71;

    const auto expected_request = trial_request_digest(
        experiment_id, key, candidate_id, candidate_digest, baseline_digest,
        procedure_id, procedure_hash, baseline_value, candidate_value,
        role, trial_index, seed, inputs, targets);
    if (expected_request != argv[16]) return 72;

    // This is the registered local evaluation procedure. It consumes the actual
    // proposed scalar configuration, the baseline configuration, the fixed
    // data set and a paired trial seed. It does not accept fitness from stdout,
    // the caller, a plugin, or a remote service.
    const double parameter = role == "baseline" ? baseline_value : candidate_value;
    std::mt19937_64 generator(seed);
    std::uniform_int_distribution<std::size_t> pick(0, inputs.size() - 1);
    long double squared_error = 0.0L;
    for (std::size_t i = 0; i < inputs.size(); ++i) {
        const auto sample = pick(generator);
        const long double prediction =
            static_cast<long double>(parameter) * static_cast<long double>(inputs[sample]);
        const long double error = prediction - static_cast<long double>(targets[sample]);
        squared_error += error * error;
    }
    const double fitness = -static_cast<double>(squared_error / inputs.size());
    if (!std::isfinite(fitness)) return 73;

    std::cout << "JEVR1|" << expected_request << "|" << role << "|"
              << trial_index << "|" << format_double(parameter) << "|"
              << format_double(fitness) << "\n";
    return std::cout.good() ? 0 : 74;
}
