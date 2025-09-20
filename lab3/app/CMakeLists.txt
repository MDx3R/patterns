add_executable(app main.cpp)
target_link_libraries(app PRIVATE absfactory)
target_link_libraries(app PRIVATE factory)
target_link_libraries(app PRIVATE builder)

add_custom_command(TARGET app POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_SOURCE_DIR}/article.txt
        $<TARGET_FILE_DIR:app>)