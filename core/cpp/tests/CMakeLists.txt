add_executable(jarvis_brain_contract brain_contract.cpp)
target_link_libraries(jarvis_brain_contract PRIVATE jarvis_core)
target_compile_features(jarvis_brain_contract PRIVATE cxx_std_20)

include(CTest)
if(BUILD_TESTING)
    add_test(NAME jarvis_brain_contract COMMAND jarvis_brain_contract)
endif()
