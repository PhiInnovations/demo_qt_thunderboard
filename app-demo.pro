#-------------------------------------------------
#
# Project created by QtCreator 2015-07-13T14:01:51
#
#-------------------------------------------------

QT       += core gui

TARGET = app-demo
TEMPLATE = app

#DEFINES += HOST_DBG


SOURCES += main.cpp\
        mygui.cpp \
    leds.cpp \
    gpio_ctrl.cpp \
    keys.cpp

HEADERS  += mygui.h \
    leds.h \
    gpio_ctrl.h \
    keys.h

FORMS    += mygui.ui \
    keys.ui

RESOURCES += \
    Images.qrc
