cmake_minimum_required(VERSION 3.16)
project(Task4)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_executable(Task4
    main.cpp
    mainwindow.cpp
    graphwidget.cpp
)

target_link_libraries(Task4
    Qt6::Widgets
)