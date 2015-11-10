TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    images.cpp
LIBS+=`sdl-config --libs` -lSDL -lSDL_image -lSDL_ttf
INCLUDEPATH+=-I/usr/include/SDL/

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    images.h

