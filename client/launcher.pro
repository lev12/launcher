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
    settings.cpp \
    background.cpp \
    menu.cpp \
    general.cpp \
    versionmanager.cpp \
    settingsmenu.cpp \
    sendmassage.cpp \
    updatelauncher.cpp \
    dialogupdatelauncher.cpp \
    uploader.cpp \
    menuGeneral.cpp \
    application.cpp \
    config.cpp \
    downloader.cpp \
    downloaderForFile.cpp \
    downloaderForVersion.cpp \
    electricalAssistant.cpp \
    log.cpp \
    network.cpp \
    version.cpp \
    versionController.cpp \
    electricalsimulator.cpp \
    uielectricalsimulator.cpp \
    uiapplication.cpp \
    menuvertical.cpp \
    uigeneralapplication.cpp \
    applicationcontroller.cpp

HEADERS  += mainwindow.h \
    settings.h \
    background.h \
    menu.h \
    general.h \
    versionmanager.h \
    settingsmenu.h \
    sendmassage.h \
    updatelauncher.h \
    dialogupdatelauncher.h \
    uploader.h \
    menuGeneral.h \
    globalVariable.h \
    log.h \
    network.h \
    application.h \
    config.h \
    downloader.h \
    downloaderForFile.h \
    downloaderForVersion.h \
    electricalAssistant.h \
    version.h \
    versionController.h \
    electricalsimulator.h \
    uielectricalsimulator.h \
    uiapplication.h \
    menuvertical.h \
    uigeneralapplication.h \
    applicationcontroller.h


FORMS    += mainwindow.ui \
    settings.ui \
    menu.ui \
    general.ui \
    versionmanager.ui \
    settingsmenu.ui \
    sendmassage.ui \
    updatelauncher.ui \
    dialogupdatelauncher.ui \
    menuGeneral.ui \
    electricalAssistant.ui \
    uielectricalsimulator.ui \
    uiapplication.ui \
    menuvertical.ui \
    uigeneralapplication.ui

RESOURCES += rec.qrc \
