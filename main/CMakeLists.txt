project(main)
add_executable(main main.cpp )
add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/config ${CMAKE_BINARY_DIR}/bin)
target_link_libraries(main ps sql )
