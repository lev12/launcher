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
    ui/settings.cpp \
    ui/menu.cpp \
    ui/general.cpp \
    ui/versionmanager.cpp \
    ui/settingsmenu.cpp \
    ui/sendmassage.cpp \
    ui/updatelauncher.cpp \
    ui/dialogUpdateLauncher.cpp \
    network/uploader.cpp \
    ui/menuGeneral.cpp \
    application.cpp \
    config.cpp \
    network/downloader.cpp \
    network/downloaderForFile.cpp \
    network/downloaderForVersion.cpp \
    log.cpp \
    network/network.cpp \
    version.cpp \
    versionController.cpp \
    electricalsimulator.cpp \
    ui/uiapplication.cpp \
    ui/menuvertical.cpp \
    ui/uigeneralapplication.cpp \
    applicationcontroller.cpp \
    ui/uiApplicationItem.cpp \
    network/abstractRequest.cpp \
    network/requestApplicationList.cpp \
    network/abstractRequestForVersion.cpp \
    network/requestCheckVersion.cpp \
    network/abstractRequestForApplication.cpp \
    network/requestVersionInfo.cpp \
    network/requestVersionsList.cpp \
    network/requestCheckApplication.cpp \
    network/requestAppicationInfo.cpp \
    network/resqustActualVersion.cpp

HEADERS  += mainwindow.h \
    ui/settings.h \
    ui/menu.h \
    ui/general.h \
    ui/versionmanager.h \
    ui/settingsmenu.h \
    ui/sendmassage.h \
    ui/updatelauncher.h \
    ui/dialogupdatelauncher.h \
    network/uploader.h \
    ui/menuGeneral.h \
    globalVariable.h \
    log.h \
    network/network.h \
    application.h \
    config.h \
    network/downloader.h \
    network/downloaderForFile.h \
    network/downloaderForVersion.h \
    version.h \
    versionController.h \
    electricalsimulator.h \
    ui/uiapplication.h \
    ui/menuvertical.h \
    ui/uigeneralapplication.h \
    applicationcontroller.h \
    ui/uiApplicationItem.h \
    network/abstractRequest.h \
    network/requestApplicationList.h \
    network/abstractRequestForVersion.h \
    network/requestCheckVersion.h \
    network/abstractRequestForApplication.h \
    network/requestVersionInfo.h \
    network/requestVersionsList.h \
    network/requestCheckApplication.h \
    network/requestAppicationInfo.h \
    network/resqustActualVersion.h


FORMS    += mainwindow.ui \
    ui/settings.ui \
    ui/menu.ui \
    ui/general.ui \
    ui/versionmanager.ui \
    ui/settingsmenu.ui \
    ui/sendmassage.ui \
    ui/updatelauncher.ui \
    ui/dialogUpdateLauncher.ui \
    ui/menuGeneral.ui \
    ui/uiapplication.ui \
    ui/menuvertical.ui \
    ui/uigeneralapplication.ui \
    ui/uiApplicationItem.ui

RESOURCES += rec/rec.qrc \
