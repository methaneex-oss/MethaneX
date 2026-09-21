#include "jarvis/engineering/model_coordinator.hpp"

#include <cassert>

using namespace jarvis::engineering;

int main() {
    EngineeringModelCoordinator coordinator;
    ModelRequest request{"implement", "context", {"source"}, 4096};
    std::vector<ModelDescriptor> models{
        {"slow", "test", "slow", {"source"}, 2.0, 0.5},
        {"fast", "test", "fast", {"source"}, 0.1, 0.9},
        {"wrong", "test", "wrong", {"chat"}, 0.0, 1.0}
    };

    const auto ranked = coordinator.rank(request, models);
    assert(ranked.size() == 3);
    assert(ranked[0].eligible);
    assert(ranked[0].model.id == "fast");
    assert(!ranked[2].eligible);
    return 0;
}
