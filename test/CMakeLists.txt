project(tests)

add_subdirectory(lib)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(run_tests Bfloat16Tests.cpp)

target_link_libraries(run_tests bfloat16_lib)

target_link_libraries(run_tests gtest gtest_main)
