cmake_minimum_required(VERSION 3.0)
project(cernel_test)

include_directories(../)

add_executable(basic src/basic_test.cpp)
add_executable(num_threads src/num_threads.cpp)

if (UNIX)
    target_link_libraries(basic -lpthread)
endif (UNIX)
if (WIN32)
    target_link_libraries(basic -static)
    target_link_libraries(num_threads -static)
endif (WIN32)