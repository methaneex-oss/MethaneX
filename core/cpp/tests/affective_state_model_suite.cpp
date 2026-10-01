#include "jarvis/core/affective_state.hpp"

#include <cassert>
#include <cmath>
#include <iostream>

using namespace jarvis::core;

int main() {
    AffectiveStateModel model;
    const auto baseline = model.state();
    const auto positive = model.update(AffectiveSignal{0.9, 0.0, 0.1, 0.2, 0.1, 0.95});
    assert(positive.valence > baseline.valence);
    const auto negative = model.update(AffectiveSignal{-0.9, 1.0, 0.9, 0.9, 1.0, 0.1});
    assert(negative.valence < positive.valence);
    assert(negative.tension > positive.tension);
    assert(negative.uncertainty > positive.uncertainty);
    const auto relaxed = model.decay(30.0);
    assert(relaxed.tension < negative.tension);
    assert(relaxed.uncertainty < negative.uncertainty);
    assert(relaxed.stability > negative.stability);

    model.restore(AffectiveState{5.0, -5.0, 5.0, -5.0, 5.0, 7});
    const auto safe = model.state();
    assert(safe.valence == 1.0 && safe.arousal == 0.0);
    assert(safe.uncertainty == 1.0 && safe.tension == 0.0 && safe.stability == 1.0);
    assert(safe.updates == 7);
    std::cout << "affective_state_model_suite: PASS\n";
}
