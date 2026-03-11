TEMPLATE = app
TARGET = Paint

QT = core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

SOURCES += main.cpp \
    canvas.cpp \
    circle.cpp \
    hexagon.cpp \
    mainwindow.cpp \
    octagon.cpp \
    polygon.cpp \
    rectangle.cpp \
    rhombus.cpp \
    shape.cpp \
    square.cpp \
    star.cpp \
    triangle.cpp

HEADERS += \
    canvas.h \
    circle.h \
    hexagon.h \
    mainwindow.h \
    octagon.h \
    polygon.h \
    rectangle.h \
    rhombus.h \
    shape.h \
    square.h \
    star.h \
    triangle.h
