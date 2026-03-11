cmake_minimum_required(VERSION 3.16)

project(Task1 LANGUAGES CXX)

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
    date.cpp
    date.h
)

qt_add_executable(Task1 
    ${PROJECT_SOURCES}
)

find_package(Threads REQUIRED)

target_link_libraries(Task1 PRIVATE
    Qt6::Widgets
)

include(GNUInstallDirs)
install(TARGETS Task1
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
