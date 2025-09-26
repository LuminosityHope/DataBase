project(main)
find_package(nlohmann_json REQUIRED)
add_executable(${PROJECT_NAME} main.cpp )
add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/config ${CMAKE_BINARY_DIR}/bin)
target_link_libraries(${PROJECT_NAME} ps sql )
target_link_libraries(${PROJECT_NAME} nlohmann_json::nlohmann_json)

