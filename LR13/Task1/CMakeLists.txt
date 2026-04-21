cmake_minimum_required(VERSION 3.16)
project(Task1 VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

set(SOURCES
    src/main.cpp
    src/mainwindow.cpp
    src/key.cpp
    src/keyboard.cpp
    src/letter.cpp
    src/text.cpp
)

set(HEADERS
    include/mainwindow.h
    include/layout.h
    include/key.h
    include/keyboard.h
    include/letter.h
    include/text.h
)

add_executable(Task1 ${SOURCES} ${HEADERS})

target_include_directories(Task1 PRIVATE src include)

target_link_libraries(Task1 PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
)
