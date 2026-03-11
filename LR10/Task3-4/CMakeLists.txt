cmake_minimum_required(VERSION 3.10)

project(Task3 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES
    binaryoperation.cpp
    main.cpp
    number.cpp
    tools.cpp
)

set(HEADERS
    binaryoperation.h
    expression.h
    number.h
    tools.h
)

add_executable(Task3 ${SOURCES} ${HEADERS})
