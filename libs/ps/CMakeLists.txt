project(ps)

file(GLOB_RECURSE SOURCE_FILES
        ${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/include/${PROJECT_NAME}/*.h)

add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} PUBLIC interface)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/${PROJECT_NAME})
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/)