add_executable(unit_tests
    absfactory_tests.cpp
    factory_tests.cpp
    builder_tests.cpp
)

target_link_libraries(unit_tests PRIVATE
    absfactory
    factory
    builder
    gtest
    gtest_main
    gmock
    gmock_main
)

include(GoogleTest)
gtest_discover_tests(unit_tests)
