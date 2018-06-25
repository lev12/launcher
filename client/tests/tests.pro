# Name of the project
TARGET = test

# Application (executable)
TEMPLATE = app
QT += testlib
QT += gui
QT += websockets
# Include default settings
include(../defaults.pri)

# Some settings
CONFIG += console # see console output
CONFIG += c++14 # use the C++14 standard
CONFIG -= qt # no Qt libraries used
CONFIG += qt warn_on depend_includepath testcase

# Include files for this project
SOURCES +=  tst_testcase.cpp

# Use the dynamically linked library
LIBS += -L../src -ltemplate
