cmake_minimum_required(VERSION 3.16)
project(Task1-3)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

include_directories(include)

add_executable(Task1-3
    src/main.cpp
    src/tools.cpp
    src/mainwindow.cpp
    include/mainwindow.h 
)

target_link_libraries(Task1-3
    Qt6::Widgets
    Qt6::Core
)
