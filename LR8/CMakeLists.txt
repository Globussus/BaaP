cmake_minimum_required(VERSION 3.22.1)

project(LR8)

set(SRC_DIR src)

include_directories(include)

add_library(Library ${SRC_DIR}/Library.cpp)
add_library(Production ${SRC_DIR}/Production.cpp)
add_library(InputChecker ${SRC_DIR}/InputChecker.cpp)

add_executable(Task1 ${SRC_DIR}/Task1/main.cpp)
target_link_libraries(Task1 Production InputChecker)

add_executable(Task2 ${SRC_DIR}/Task2/main.cpp)
target_link_libraries(Task2 Library InputChecker)