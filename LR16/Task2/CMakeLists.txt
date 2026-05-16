cmake_minimum_required(VERSION 3.16)
project(Task2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)

# Find Qt
find_package(Qt6 REQUIRED COMPONENTS Core Widgets)

# Статическая библиотека для ArrayHeap
add_library(array_heap STATIC 
    array_heap.cpp
)

target_include_directories(array_heap PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# Динамическая библиотека для ListHeap
add_library(list_heap SHARED 
    list_heap.cpp
)

target_include_directories(list_heap PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# Qt приложение
add_executable(heap_gui
    main.cpp
    mainwindow.cpp
)

target_link_libraries(heap_gui
    Qt6::Core
    Qt6::Widgets
    array_heap
    list_heap
)

target_include_directories(heap_gui PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)