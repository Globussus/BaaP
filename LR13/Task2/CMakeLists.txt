cmake_minimum_required(VERSION 3.16)
project(Task2 VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

add_library(StringLib SHARED
    src/myString.cpp
    src/iterator.cpp
    src/reverseIterator.cpp
)
target_include_directories(StringLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(Task2
    src/main.cpp
    src/mainwindow.cpp
    include/mainwindow.h
)
target_include_directories(Task2 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(Task2 PRIVATE StringLib Qt6::Widgets)