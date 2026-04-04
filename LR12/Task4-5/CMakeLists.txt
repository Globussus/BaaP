cmake_minimum_required(VERSION 3.16)

project(Task4-5 VERSION 0.1 LANGUAGES CXX)

# Включаем автоматическую обработку Qt ресурсов и форм
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Ищем Qt6
find_package(Qt6 REQUIRED COMPONENTS Widgets)

# --- Сборка библиотеки MyVector ---
# Указываем только .cpp файлы в исходники, .h лучше подхватывать через include_directories
add_library(MyVector STATIC 
    include/libs/vector.cpp
    include/libs/vector.h
    include/libs/pair.h
    include/libs/exceptions.h
    include/libs/iterator.h
    include/libs/reverse_iterator.h
)

# Указываем путь к заголовкам для библиотеки
target_include_directories(MyVector PUBLIC include/libs)

# --- Сборка основного приложения ---
add_executable(Task4-5
    src/main.cpp
    src/mainwindow.cpp
    include/mainwindow.h
)

# Указываем путь к заголовкам приложения
target_include_directories(Task4-5 PRIVATE include)

# Линовка (связывание) библиотек
target_link_libraries(Task4-5 PRIVATE 
    MyVector
    Qt6::Widgets
)
