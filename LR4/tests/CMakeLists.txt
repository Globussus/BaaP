cmake_minimum_required(VERSION 3.14)
project(test1)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
  test_case
  test_case.cc
)
# to link the executable with GoogleTest main library
target_link_libraries(
  test_case
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(test_case)