#include "jarvis/core/knowledge.hpp"

#include <cassert>
#include <cmath>
#include <string>

using namespace jarvis::core;

int main() {
    KnowledgeModel knowledge;

    const auto first = knowledge.assimilate(Evidence{"sensor-a", "temperature", 20.0, 0.8});
    assert(std::abs(first - 0.8) < 1e-12);
    const auto* metric = knowledge.source_metric("sensor-a");
    assert(metric != nullptr);
    assert(metric->observations == 1);
    assert(std::abs(metric->reliability - 0.8) < 1e-12);

    const auto second = knowledge.assimilate(Evidence{"sensor-a", "temperature", 21.0, 0.4});
    assert(std::abs(second - 0.6) < 1e-12);
    metric = knowledge.source_metric("sensor-a");
    assert(metric != nullptr);
    assert(metric->observations == 2);
    assert(std::abs(metric->reliability - 0.6) < 1e-12);

    knowledge.score_source("sensor-a", true);
    metric = knowledge.source_metric("sensor-a");
    assert(metric != nullptr);
    assert(metric->observations == 3);
    assert(std::abs(metric->reliability - (0.6 * 2.0 + 1.0) / 3.0) < 1e-12);

    knowledge.score_source("sensor-a", false);
    metric = knowledge.source_metric("sensor-a");
    assert(metric != nullptr);
    assert(metric->observations == 4);
    assert(metric->reliability >= 0.0 && metric->reliability <= 1.0);

    return 0;
}
