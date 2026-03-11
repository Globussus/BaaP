cmake_minimum_required(VERSION 3.16)
project(RecursiveTasks VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)
qt_standard_project_setup()

qt_add_executable(Task1
    main.cpp
    tools.cpp
    tools.h
    contextmenu.cpp
    contextmenu.h
)

target_link_libraries(Task1 PRIVATE Qt6::Widgets)
