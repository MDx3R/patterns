add_executable(unit_tests
    facade_tests.cpp
    adapter_tests.cpp
)

target_link_libraries(unit_tests PRIVATE
    adapter
    facade
    gtest
    gtest_main
    gmock
    gmock_main
)

include(GoogleTest)
gtest_discover_tests(unit_tests)
