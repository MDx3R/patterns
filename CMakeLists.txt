cmake_minimum_required(VERSION 3.16)

project(MyProject VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(BUILD_TESTING "Build unit tests" ON)

add_library(absfactory  INTERFACE)
target_include_directories(absfactory  INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/absfactory 
)

add_library(factory  INTERFACE)
target_include_directories(factory  INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/factory 
)

add_subdirectory(app)

if(BUILD_TESTING)
    enable_testing()
    # add_subdirectory(external/googletest)
    # add_subdirectory(tests)
endif()
