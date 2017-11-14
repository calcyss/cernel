cmake_minimum_required(version 3.0)
project(cernel_test)

file(glob_recurse source_files src/*.cpp)

add_executable(test ${source_files})
