#-------------------------------------------------
#
# Project created by QtCreator 2016-06-21T22:34:30
#
#-------------------------------------------------

QT       += core gui\
            websockets\

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = launcher
TEMPLATE = app

CONFIG += c++11

SOURCES += main.cpp\
        mainwindow.cpp \
    config.cpp \
    versions.cpp \
    settings.cpp \
    background.cpp \
    files.cpp \
    application.cpp \
    network.cpp \
    menu.cpp \
    general.cpp \
    electricalsimulator.cpp

HEADERS  += mainwindow.h \
    config.h \
    versions.h \
    global_variable.h \
    settings.h \
    background.h \
    files.h \
    application.h \
    network.h \
    menu.h \
    general.h \
    electricalsimulator.h


FORMS    += mainwindow.ui \
    settings.ui \
    menu.ui \
    general.ui \
    electricalsimulator.ui

RESOURCES += \
    rec.qrc
