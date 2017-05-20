cmake_minimum_required(VERSION 3.6)
project(Collections)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp )
add_executable(Sets ${SOURCE_FILES})

set(SOURCE_FILES internet.cpp)
add_executable(BinaryTree ${SOURCE_FILES})
