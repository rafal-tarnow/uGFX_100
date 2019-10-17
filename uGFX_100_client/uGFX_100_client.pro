include(../libs/library_api/library_api.pri)

TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    client_application.cpp

HEADERS += \
    client_application.h
