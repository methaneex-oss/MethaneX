#include "evolution_test_evaluator.hpp"

int main(int argc, char** argv) {
    return jarvis::core::test_support::run_evolution_evaluator_fixture(argc, argv)
        ? 0 : 64;
}
