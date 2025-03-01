cmake_minimum_required(VERSION 3.30)
project(bfloat16)

set(CMAKE_CXX_STANDARD 23)

add_executable(bfloat16 src/main.cpp src/bfloat16.cpp)
target_include_directories(bfloat16 PRIVATE src)
