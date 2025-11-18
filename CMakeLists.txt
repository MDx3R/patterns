cmake_minimum_required(VERSION 3.16)

project(MyProject VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(strategy  INTERFACE)
target_include_directories(strategy  INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/strategy 
)

add_subdirectory(app)
