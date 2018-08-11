# Name of the project
TARGET = versionTest

# Application (executable)
TEMPLATE = app
QT += testlib
QT += gui
QT += websockets
# Include default settings
include(../../defaults.pri)

# Some settings
CONFIG += console # see console output
CONFIG += c++14 # use the C++14 standard
CONFIG -= qt # no Qt libraries used
CONFIG += qt warn_on depend_includepath testcase

# Include files for this project
SOURCES += \
    main.cpp \
    abstractVersionTest.cpp \
    versionControllerTest.cpp \
    versiondata.cpp \
    versionInstallTest.cpp \
    versionNoInstallTest.cpp

# Use the dynamically linked library
LIBS += -L../../src -ltemplate

HEADERS += \
    abstractVersionTest.h \
    versionControllerTest.h \
    versiondata.h \
    versionInstallTest.h \
    versionNoInstallTest.h

RESOURCES += \
    ../data.qrc
