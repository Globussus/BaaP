cmake_minimum_required(VERSION 3.16)
project(Task2)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

qt_standard_project_setup()

add_executable(Task2
    main.cpp
    mainwindow.cpp
    mainwindow.h
    AVLTree.cpp
    AVLTree.h
)

target_link_libraries(Task2 Qt6::Widgets)