cmake_minimum_required(VERSION 3.30)
project(bfloat16)

set(CMAKE_CXX_STANDARD 23)

add_executable(bfloat16_run bfloat/main.cpp)

add_subdirectory(bfloat)

target_link_libraries(bfloat16_run bfloat16_lib)
target_include_directories(bfloat16_run PRIVATE bfloat)

add_subdirectory(test)
