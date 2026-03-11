cmake_minimum_required(VERSION 3.16)

project(Task2 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
    main.cpp
    mainwindow.cpp
    mainwindow.h
    student.cpp
    student.h
    file_functions.cpp
    file_functions.h
)

qt_add_executable(Task2 
    ${PROJECT_SOURCES}
)

target_link_libraries(Task2 PRIVATE
    Qt6::Widgets
)

include(GNUInstallDirs)
install(TARGETS Task2
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
