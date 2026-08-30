cmake_minimum_required(VERSION 3.24)
project(jarvis_core LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(jarvis_core STATIC
    src/brain.cpp
    src/memory.cpp
    src/world_model.cpp
    src/causal_model.cpp
    src/decision.cpp
    src/adaptation.cpp
    src/attention.cpp
    src/attention_state.cpp
    src/threat.cpp
    src/resilience.cpp
    src/evolution.cpp
    src/planning.cpp
    src/reasoning.cpp
    src/action_model.cpp
    src/learning_loop.cpp
    src/reflection.cpp
    src/knowledge.cpp
    src/self_model.cpp
    src/self_state.cpp
    src/representation.cpp
    src/perception_pipeline.cpp
    src/world_state.cpp
)

target_include_directories(jarvis_core PUBLIC include)
target_compile_features(jarvis_core PUBLIC cxx_std_20)

if (MSVC)
    target_compile_options(jarvis_core PRIVATE /W4 /permissive-)
else()
    target_compile_options(jarvis_core PRIVATE -Wall -Wextra -Wpedantic)
endif()

include(CTest)
if(BUILD_TESTING)
    add_subdirectory(tests)
endif()
