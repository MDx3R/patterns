add_executable(app main.cpp)
target_link_libraries(app PRIVATE adapter)
target_link_libraries(app PRIVATE facade)