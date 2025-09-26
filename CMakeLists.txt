cmake_minimum_required(VERSION 3.16)
project(DataBase C CXX)


set(BINARY_DIR ${CMAKE_BINARY_DIR})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${BINARY_DIR}/lib)

add_subdirectory(bd/implementation/ps)
add_subdirectory(bd/implementation/sql)
add_subdirectory(bd/interface)
add_subdirectory(main)
