cmake_minimum_required(VERSION 3.16)
project(Task3 VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

set(SOURCES
    main.cpp
    mainwindow.cpp
)

set(HEADERS
    BinarySearchTree.h
    BstMap.h
    BstSet.h
    UnorderedMap.h
    mainwindow.h
)

add_executable(Task3 ${SOURCES} ${HEADERS})

target_include_directories(Task3 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(Task3 PRIVATE Qt6::Widgets)