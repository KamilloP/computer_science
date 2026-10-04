cmake_minimum_required(VERSION 3.14)
project(test_rmq)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
    argparse
    GIT_REPOSITORY https://github.com/p-ranav/argparse.git
)

FetchContent_MakeAvailable(argparse)

add_executable(test_rmq test_rmq.cpp)

target_link_libraries(test_rmq PRIVATE argparse)