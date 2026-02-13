cmake_minimum_required(VERSION 3.22.1)
project(test_project)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0")

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
  run_tests
  test_case.cc
)

target_compile_options(run_tests PRIVATE -fsanitize=address)
target_link_options(run_tests PRIVATE -fsanitize=address)

target_link_libraries(
  run_tests
  PRIVATE GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(run_tests)