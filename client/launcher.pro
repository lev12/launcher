#-------------------------------------------------
#
# Project created by QtCreator 2016-06-21T22:34:30
#
#-------------------------------------------------

QT       += core gui\
            websockets


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = launcher
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    config.cpp \
    versions.cpp

HEADERS  += mainwindow.h \
    config.h \
    versions.h

FORMS    += mainwindow.ui

RESOURCES +=

DISTFILES += \
    protocol.txt
