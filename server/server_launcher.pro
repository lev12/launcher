QT += core\
      websockets
QT -= gui

CONFIG += c++11

TARGET = server_launcher
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    server.cpp \
    file.cpp \
    client.cpp \
    log.cpp

HEADERS += \
    server.h \
    file.h \
    client.h \
    globalvariable.h \
    log.h
