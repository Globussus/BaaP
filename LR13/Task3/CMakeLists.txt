cmake_minimum_required(VERSION 3.16)
project(Task3)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets)

set(TASK2_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../Task2)

add_subdirectory(${TASK2_DIR} ${CMAKE_BINARY_DIR}/Task2/build)

add_executable(Task3
    src/main.cpp
    src/mainwindow.cpp
    src/bitset.cpp
    include/mainwindow.h      
    include/bitset.h         
)

target_include_directories(Task3 PRIVATE 
    include
    ${TASK2_DIR}/include
)

target_link_libraries(Task3 
    Qt6::Core 
    Qt6::Widgets 
    StringLib
)

set_target_properties(Task3 PROPERTIES
    BUILD_RPATH "${CMAKE_BINARY_DIR}/task2_build"
)