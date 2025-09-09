project(main)
find_package(Qt6 REQUIRED COMPONENTS Sql)
target_link_libraries(main PRIVATE Qt6::Sql)
add_executable(main main.cpp)
target_link_libraries(main ps sql)

