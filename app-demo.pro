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
    keys.cpp \
    toogler.cpp \
    pwm_ctrl.cpp

HEADERS  += mygui.h \
    leds.h \
    gpio_ctrl.h \
    keys.h \
    toogler.h \
    pwm_ctrl.h

FORMS    += mygui.ui \
    keys.ui

RESOURCES += \
    Images.qrc

#QMAKE_INCDIR += ../tslib/include
#QMAKE_LIBDIR += ../tslib/lib

#QMAKE_LFLAGS += -Wl,-rpath-link=../tslib/lib


#INCLUDEPATH += ../tslib/include
#DEPENDPATH += ../tslib/lib

#LIBS += -L../tslib/lib

#LIBS += -lts
