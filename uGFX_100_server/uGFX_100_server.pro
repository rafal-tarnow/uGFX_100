TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -lglfw
LIBS += -lGL

INCLUDEPATH += . ../libs

SOURCES += \
        main.cpp \
    frame.cpp \
    camera.cpp

HEADERS += \
    opengl_includes.hpp \
    frame.hpp \
    glm_includes.hpp \
    camera.hpp
