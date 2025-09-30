if (NOT TEST_OUTPUT_PATH)
    set(TEST_OUTPUT_PATH ${CMAKE_BINARY_DIR}/test)
endif ()


file(GLOB SRC ${CMAKE_CURRENT_SOURCE_DIR}/test/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/test/*.h)

add_executable(${PROJECT_NAME}_gtest ${SRC})

target_link_libraries(${PROJECT_NAME}_gtest ${PROJECT_NAME} gtest)
set_target_properties(${PROJECT_NAME}_gtest PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${TEST_OUTPUT_PATH})
add_test(NAME ${PROJECT_NAME}_gtest COMMAND ${PROJECT_NAME}_gtest WORKING_DIRECTORY ${TEST_OUTPUT_PATH})



