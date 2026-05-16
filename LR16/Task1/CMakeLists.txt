cmake_minimum_required(VERSION 3.16)
project(Task1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_executable(Task1
    main.cpp
    BSTree.h
    BSTree.cpp
    mainwindow.h
    mainwindow.cpp
)

target_link_libraries(Task1 PRIVATE Qt6::Widgets)