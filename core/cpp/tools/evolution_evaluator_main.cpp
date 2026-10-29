#include <cmath>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

// Local, dependency-free evaluator for a scalar linear strategy parameter.
// Inputs are held-out observations (feature, target); fitness is derived from
// measured prediction error rather than supplied by the caller.
int main(int argc, char** argv) {
    if (argc < 5 || std::string(argv[1]) != "--linear-weight-mse-v1" ||
        (argc - 3) % 2 != 0) {
        std::cerr << "invalid evaluator request";
        return 2;
    }
    char* end = nullptr;
    const double weight = std::strtod(argv[2], &end);
    if (end == argv[2] || *end != '\0' || !std::isfinite(weight)) return 2;
    long double squared_error = 0.0L;
    std::size_t count = 0;
    for (int i = 3; i + 1 < argc; i += 2) {
        char* feature_end = nullptr;
        char* target_end = nullptr;
        const double feature = std::strtod(argv[i], &feature_end);
        const double target = std::strtod(argv[i + 1], &target_end);
        if (feature_end == argv[i] || *feature_end != '\0' ||
            target_end == argv[i + 1] || *target_end != '\0' ||
            !std::isfinite(feature) || !std::isfinite(target)) return 2;
        const long double error = static_cast<long double>(weight) * feature - target;
        squared_error += error * error;
        ++count;
    }
    if (count == 0 || !std::isfinite(squared_error)) return 2;
    const long double mse = squared_error / static_cast<long double>(count);
    const long double fitness = 1.0L / (1.0L + mse);
    if (!std::isfinite(fitness)) return 2;
    std::cout << std::setprecision(17) << static_cast<double>(fitness) << '\n';
    return 0;
}
