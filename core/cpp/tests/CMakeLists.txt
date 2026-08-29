add_executable(jarvis_brain_contract brain_contract.cpp)
target_link_libraries(jarvis_brain_contract PRIVATE jarvis_core)
target_compile_features(jarvis_brain_contract PRIVATE cxx_std_20)

add_executable(jarvis_brain_10_suite brain_10_suite.cpp)
target_link_libraries(jarvis_brain_10_suite PRIVATE jarvis_core)
target_compile_features(jarvis_brain_10_suite PRIVATE cxx_std_20)

add_executable(jarvis_brain_deep_suite brain_deep_suite.cpp)
target_link_libraries(jarvis_brain_deep_suite PRIVATE jarvis_core)
target_compile_features(jarvis_brain_deep_suite PRIVATE cxx_std_20)

add_executable(jarvis_brain_failure_suite brain_failure_suite.cpp)
target_link_libraries(jarvis_brain_failure_suite PRIVATE jarvis_core)
target_compile_features(jarvis_brain_failure_suite PRIVATE cxx_std_20)

include(CTest)
if(BUILD_TESTING)
    add_test(NAME jarvis_brain_contract COMMAND jarvis_brain_contract)
    add_test(NAME jarvis_brain_10_suite COMMAND jarvis_brain_10_suite)
    add_test(NAME jarvis_brain_deep_suite COMMAND jarvis_brain_deep_suite)
    add_test(NAME jarvis_brain_failure_suite COMMAND jarvis_brain_failure_suite)
endif()
