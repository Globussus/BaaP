cmake_minimum_required(VERSION 3.22.1)

set(CMAKE_CXX_STANDART 17)
set(CMAKE_CXX_STANDART_REQUIRED ON)

project(LR7)
add_executable(LR7 main.cpp)

target_compile_options(LR7 PRIVATE -fsanitize=address)
target_link_options(LR7 PRIVATE -fsanitize=address)