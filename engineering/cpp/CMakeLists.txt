cmake_minimum_required(VERSION 3.24)
project(jarvis_engineering LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(jarvis_engineering STATIC
    src/agent.cpp
    src/coordinator.cpp
    src/execution.cpp
    src/worker.cpp
)

target_include_directories(jarvis_engineering PUBLIC include)
target_compile_features(jarvis_engineering PUBLIC cxx_std_20)

if (MSVC)
    target_compile_options(jarvis_engineering PRIVATE /W4 /permissive-)
else()
    target_compile_options(jarvis_engineering PRIVATE -Wall -Wextra -Wpedantic)
endif()

include(CTest)
if(BUILD_TESTING)
    add_executable(jarvis_engineering_agent_suite tests/agent_suite.cpp)
    target_link_libraries(jarvis_engineering_agent_suite PRIVATE jarvis_engineering)
    add_executable(jarvis_engineering_coordinator_suite tests/coordinator_suite.cpp)
    target_link_libraries(jarvis_engineering_coordinator_suite PRIVATE jarvis_engineering)
    add_executable(jarvis_engineering_worker_suite tests/worker_suite.cpp)
    target_link_libraries(jarvis_engineering_worker_suite PRIVATE jarvis_engineering)
    add_test(NAME jarvis_engineering_agent_suite COMMAND jarvis_engineering_agent_suite)
    add_test(NAME jarvis_engineering_coordinator_suite COMMAND jarvis_engineering_coordinator_suite)
    add_test(NAME jarvis_engineering_worker_suite COMMAND jarvis_engineering_worker_suite)
endif()
