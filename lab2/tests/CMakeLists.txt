add_executable(unit_tests
    functional_tests.cpp
)

target_link_libraries(unit_tests PRIVATE
    core
    gtest
    gtest_main
    gmock
    gmock_main
)

include(GoogleTest)
gtest_discover_tests(unit_tests)
