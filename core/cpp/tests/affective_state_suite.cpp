#include "jarvis/core/affective_state.hpp"
#include <cassert>
#include <cmath>
#include <iostream>
using namespace jarvis::core;
int main() {
    AffectiveStateModel model;
    const auto initial=model.state();
    const auto positive=model.update(AffectiveSignal{0.9,0.1,0.2,0.4,0.1,0.9});
    assert(positive.valence>initial.valence);
    assert(positive.updates==1);
    const auto stressed=model.update(AffectiveSignal{-0.9,1.0,0.9,0.9,1.0,0.1});
    assert(stressed.tension>positive.tension);
    assert(stressed.uncertainty>positive.uncertainty);
    assert(stressed.stability<positive.stability);
    const auto decayed=model.decay(20.0);
    assert(std::abs(decayed.tension)<std::abs(stressed.tension));
    assert(decayed.stability>stressed.stability);
    model.restore(AffectiveState{2.0,-1.0,3.0,-2.0,4.0,99});
    const auto safe=model.state();
    assert(safe.valence==1.0&&safe.arousal==0.0&&safe.uncertainty==1.0&&safe.tension==0.0&&safe.stability==1.0&&safe.updates==99);
    std::cout<<"affective_state_suite: PASS\n";
    return 0;
}
