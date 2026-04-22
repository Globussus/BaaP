cmake_minimum_required(VERSION 3.16)
project(Task1 VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

add_executable(Task2
    src/main.cpp
    src/mainwindow.cpp
    src/userinputdialog.cpp
    include/mainwindow.h
    include/ship.h
    include/userinputdialog.h
)

target_include_directories(Task2 PRIVATE include)

target_link_libraries(Task2 PRIVATE Qt6::Core Qt6::Gui Qt6::Widgets)