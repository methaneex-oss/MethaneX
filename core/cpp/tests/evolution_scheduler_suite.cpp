#include "jarvis/core/evolution_scheduler.hpp"
#include <cassert>
using namespace jarvis::core;
int main() {
    EvolutionScheduler scheduler(EvolutionSchedulePolicy{std::chrono::milliseconds{100},4,true});
    const auto t0=std::chrono::steady_clock::time_point{};
    auto r=scheduler.evaluate(t0,t0,false); assert(!r.allowed);
    r=scheduler.evaluate(t0+std::chrono::milliseconds{50},t0,true); assert(!r.allowed);
    r=scheduler.evaluate(t0+std::chrono::milliseconds{100},t0,true); assert(r.allowed && r.trial_budget==4);
    return 0;
}
