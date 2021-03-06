# Name of the project
TARGET = template

# Library, so that the application and the tests can use it
TEMPLATE = lib
CONFIG += c++14
# Include default settings
include(../defaults.pri)

# Standard GUI applications can be built without further configuration
QT       += core gui websockets
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

# Include files for this project
SOURCES += mainwindow.cpp \
    ui/settings.cpp \
    ui/versionmanager.cpp \
    ui/sendmassage.cpp \
    ui/updatelauncher.cpp \
    ui/dialogUpdateLauncher.cpp \
    network/uploader.cpp \
    config.cpp \
    log.cpp \
    network/network.cpp \
    versionController.cpp \
    ui/uigeneralapplication.cpp \
    network/abstractRequest.cpp \
    network/requestApplicationList.cpp \
    network/abstractRequestForVersion.cpp \
    network/requestCheckVersion.cpp \
    network/abstractRequestForApplication.cpp \
    network/requestVersionInfo.cpp \
    network/requestVersionsList.cpp \
    network/requestCheckApplication.cpp \
    network/requestFile.cpp \
    network/requestVersion.cpp \
    network/requestFileListVersion.cpp \
    network/requestActualVersion.cpp \
    abstractVersion.cpp \
    versionInstall.cpp \
    versionNoInstall.cpp \
    applicationController.cpp \
    versionException.cpp \
    versionControllerException.cpp \
    exception.cpp \
    network/requestApplicationInfo.cpp \
    ui/uiApplication.cpp \
    ui/uiApplicationItem.cpp \
    ui/uiHomePage.cpp \
    ui/uiMainMenu.cpp \
    ui/uiApplicationRequiremets.cpp \
    ui/uiApplicationVersionManager.cpp \
    ui/uiApplicationOverview.cpp \
    applicationInstall.cpp \
    applicationNoInstall.cpp \
    abstractApplication.cpp \
    cacheOnDirve.cpp \
    ui/settings/settingLanguges.cpp \
    ui/settings/settingCheckBox.cpp \
    ui/settings/settingGeneral.cpp \
    ui/settings/settingWrapper.cpp \
    launcherConfig.cpp \
    ui/settings/settingSpinBox.cpp \
    ui/abstractWindow.cpp

HEADERS  += mainwindow.h \
    ui/settings.h \
    ui/versionmanager.h \
    ui/sendmassage.h \
    ui/updatelauncher.h \
    ui/dialogupdatelauncher.h \
    network/uploader.h \
    globalVariable.h \
    log.h \
    network/network.h \
    config.h \
    versionController.h \
    ui/uigeneralapplication.h \
    network/abstractRequest.h \
    network/requestApplicationList.h \
    network/abstractRequestForVersion.h \
    network/requestCheckVersion.h \
    network/abstractRequestForApplication.h \
    network/requestVersionInfo.h \
    network/requestVersionsList.h \
    network/requestCheckApplication.h \
    network/requestFile.h \
    network/requestVersion.h \
    network/requestFileListVersion.h \
    network/requestActualVersion.h \
    abstractVersion.h \
    versionInstall.h \
    versionNoInstall.h \
    versionType.h \
    platformType.h \
    network/networkData.h \
    versionException.h \
    versionControllerException.h \
    exception.h \
    network/requestApplicationInfo.h \
    ui/uiApplication.h \
    ui/uiApplicationItem.h \
    ui/uiHomePage.h \
    ui/uiMainMenu.h \
    applicationController.h \
    ui/uiApplicationRequiremets.h \
    ui/uiApplicationVersionManager.h \
    ui/uiApplicationOverview.h \
    applicationInstall.h \
    applicationNoInstall.h \
    abstractApplication.h \
    network/networkKeys.h \
    cacheOnDirve.h \
    ui/settings/settingCheckBox.h \
    ui/settings/settingGeneral.h \
    ui/settings/settingWrapper.h \
    ui/settings/settingLanguge.h \
    launcherConfig.h \
    ui/settings/settingSpinBox.h \
    ui/abstractWindow.h


FORMS    += mainwindow.ui \
    ui/settings.ui \
    ui/versionmanager.ui \
    ui/sendmassage.ui \
    ui/updatelauncher.ui \
    ui/dialogUpdateLauncher.ui \
    ui/uigeneralapplication.ui \
    ui/uiApplicationItem.ui \
    ui/uiApplication.ui \
    ui/uiHomePage.ui \
    ui/uiMainMenu.ui \
    ui/uiApplicationRequiremets.ui \
    ui/uiApplicationVersionManager.ui \
    ui/uiApplicationOverview.ui \
    ui/settings/settingLanguges.ui \
    ui/settings/settingCheckBox.ui \
    ui/settings/settingWrapper.ui

RESOURCES += rec/rec.qrc \

TRANSLATIONS +=
