cmake_minimum_required(VERSION 3.20)
project(cpp_strings)

set(CMAKE_CXX_STANDARD 17)

include_directories(tests/third_party .)

add_library(Catch2 STATIC strings.h tests/third_party/catch2/catch_amalgamated.cpp)

add_executable(cpp-strings-test tests/src/strings.test.cc)
target_link_libraries(cpp-strings-test PRIVATE Catch2)