TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    menu.cpp \
    show.cpp \
    images.cpp \
    init.cpp \
    getEvents.cpp \
    switchSprite.cpp \
    mouvements.cpp \
    shot.cpp \
    relancerPartie.cpp

LIBS+=`sdl-config --libs` -lSDL -lSDL_image -lSDL_ttf
INCLUDEPATH+=-I/usr/include/SDL/

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    main.h

