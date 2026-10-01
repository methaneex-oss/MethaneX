#pragma once

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <string>

namespace jarvis::core {

// Continuous internal valuation state. It is not an emotion label or an
// action rule: downstream cognition consumes these dimensions as signals.
struct AffectiveState {
    double valence{0.0};
    double arousal{0.0};
    double uncertainty{0.0};
    double tension{0.0};
    double stability{1.0};
    std::uint64_t updates{0};
};

struct AffectiveSignal {
    double outcome{0.0};
    double prediction_error{0.0};
    double novelty{0.0};
    double salience{0.0};
    double uncertainty{0.0};
    double confidence{0.5};
};

class AffectiveStateModel {
public:
    AffectiveState update(const AffectiveSignal& signal, double dt = 1.0) noexcept;
    AffectiveState decay(double dt = 1.0) noexcept;
    AffectiveState state() const noexcept { return state_; }
    void restore(AffectiveState state) noexcept { state_ = sanitize(state); }

private:
    static double clamp(double v) noexcept { return std::clamp(std::isfinite(v) ? v : 0.0, -1.0, 1.0); }
    static double unit(double v) noexcept { return std::clamp(std::isfinite(v) ? v : 0.0, 0.0, 1.0); }
    static AffectiveState sanitize(AffectiveState s) noexcept {
        s.valence = clamp(s.valence); s.arousal = unit(s.arousal);
        s.uncertainty = unit(s.uncertainty); s.tension = unit(s.tension);
        s.stability = unit(s.stability); return s;
    }
    AffectiveState state_{};
};

} // namespace jarvis::core
