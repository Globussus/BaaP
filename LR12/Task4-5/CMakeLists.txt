cmake_minimum_required(VERSION 3.16)
project(VectorQtProject LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(MyVector STATIC 
    include/libs/vector.cpp
    include/libs/vector.h
    include/libs/pair.h
    include/libs/exceptions.h
    include/libs/iterator.h
    include/libs/reverse_iterator.h
)

target_include_directories(MyVector PUBLIC include/libs)

add_executable(Task4-5 
    src/main.cpp 
    src/mainwindow.cpp
    include/mainwindow.h
)

target_include_directories(Task4-5  PRIVATE include)

target_link_libraries(Task4-5  PRIVATE 
    MyVector 
    Qt6::Widgets
)