#pragma once

#include <iomanip>
#include <iostream>
#include <string>

namespace jarvis::core::test_support {

// Test-only local evaluator protocol endpoint. It derives fitness from the
// supplied candidate value and procedure, and binds every score to the exact
// parameter/value/artifact tuple requested by the parent process.
inline int run_evolution_test_evaluator(int argc, char** argv) {
    std::string procedure, parameter, artifact, value_text;
    for (int i = 1; i + 1 < argc; ++i) {
        const std::string arg = argv[i];
        if (arg == "--procedure") procedure = argv[++i];
        else if (arg == "--parameter") parameter = argv[++i];
        else if (arg == "--artifact") artifact = argv[++i];
        else if (arg == "--value") value_text = argv[++i];
    }
    if (procedure.empty() || parameter.empty() || artifact.empty() || value_text.empty()) return 2;
    const double value = std::stod(value_text);
    double fitness = 0.70 + value - 0.40;
    if (procedure == "equal-fitness") fitness = 0.70;
    if (procedure == "subthreshold" && artifact.find("candidate") != std::string::npos)
        fitness = 0.74;
    std::cout << "JARVIS_EVAL_V1\nprocedure=" << procedure
              << "\nparameter=" << parameter << "\nvalue=" << value_text
              << "\nartifact=" << artifact << "\nfitness="
              << std::setprecision(17) << fitness << "\n";
    return 0;
}

} // namespace jarvis::core::test_support
