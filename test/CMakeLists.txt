project(tests)

add_subdirectory(lib)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(check Bfloat16Tests.cpp)

target_link_libraries(check bfloat16_lib)

target_include_directories(check PRIVATE ${CMAKE_SOURCE_DIR})

target_link_libraries(check gtest gtest_main)
