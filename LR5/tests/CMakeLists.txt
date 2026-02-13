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

add_library(matrixlib STATIC IMPORTED)
add_library(arraylib SHARED IMPORTED)

set_target_properties(matrixlib PROPERTIES
  IMPORTED_LOCATION "${CMAKE_CURRENT_SOURCE_DIR}/../src/Task1/libmatrixlib.a"
)

set_target_properties(arraylib PROPERTIES
  IMPORTED_LOCATION "${CMAKE_CURRENT_SOURCE_DIR}/../src/Task2/libarray_functions.so"
)

target_include_directories(matrixlib INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/../src/Task1/")
target_include_directories(arraylib INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/../src/Task2/")

target_link_libraries(
  test_case 
  PRIVATE matrixlib arraylib GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(test_case)