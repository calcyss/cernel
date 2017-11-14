cmake_minimum_required(VERSION 3.0)
project(cernel_test)

include_directories(../)

add_executable(basic src/basic_test.cpp)
add_executable(num_threads src/num_threads.cpp)
target_link_libraries(basic -static)
target_link_libraries(num_threads -static)