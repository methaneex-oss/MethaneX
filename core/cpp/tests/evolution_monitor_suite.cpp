#include "jarvis/core/evolution_monitor.hpp"
#include <cassert>
using namespace jarvis::core;
int main(){EvolutionMonitor m(EvolutionMonitorPolicy{0.05,3});auto h=m.observe("e",0.8,0.81,3);assert(h.state==EvolutionMonitorState::Healthy);auto d=m.observe("e",0.8,0.78,3);assert(d.state==EvolutionMonitorState::Degraded);auto r=m.observe("e",0.8,0.70,3);assert(r.state==EvolutionMonitorState::RollbackRequired);auto i=m.observe("e",0.8,0.1,2);assert(i.state==EvolutionMonitorState::Healthy);return 0;}
