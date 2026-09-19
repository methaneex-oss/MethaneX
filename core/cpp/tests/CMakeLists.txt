add_executable(jarvis_evolution_adoption_journal_suite evolution_adoption_journal_suite.cpp)
target_link_libraries(jarvis_evolution_adoption_journal_suite PRIVATE jarvis_core)
target_compile_features(jarvis_evolution_adoption_journal_suite PRIVATE cxx_std_20)

# Existing test targets are defined above in the repository's evolution/cognitive suites.
include(CTest)
if(BUILD_TESTING)
    add_test(NAME jarvis_evolution_adoption_journal_suite COMMAND jarvis_evolution_adoption_journal_suite)
endif()
