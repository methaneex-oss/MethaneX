#include "jarvis/core/brain.hpp"

#include <cassert>
#include <cmath>
#include <filesystem>
#include <iostream>

using namespace jarvis::core;

int main() {
    const auto path = std::filesystem::temp_directory_path() / "jarvis_attention_learning.bin";
    std::error_code ec;
    std::filesystem::remove(path, ec);
    std::filesystem::remove(path.string() + ".meta", ec);

    Brain brain(path);
    const auto before = brain.attention_policy();

    const auto prediction = brain.predict("temperature", Scalar{0.2}, 0.8);
    assert(prediction.created_sequence != 0);
    assert(!brain.resolve_prediction(prediction.created_sequence, Scalar{0.9}));

    const auto learned = brain.attention_policy();
    assert(learned.novelty_weight >= before.novelty_weight);
    assert(learned.uncertainty_weight >= before.uncertainty_weight);
    assert(learned.novelty_weight <= 4.0);
    assert(learned.uncertainty_weight <= 4.0);

    Brain restored(path);
    const auto replayed = restored.attention_policy();
    assert(std::abs(replayed.novelty_weight - learned.novelty_weight) < 1e-9);
    assert(std::abs(replayed.uncertainty_weight - learned.uncertainty_weight) < 1e-9);

    std::filesystem::remove(path, ec);
    std::filesystem::remove(path.string() + ".meta", ec);
    std::cout << "attention_learning_brain_suite: PASS\n";
    return 0;
}
