#-------------------------------------------------
#
# Project created by QtCreator 2016-06-24T02:57:57
#
#-------------------------------------------------

QT       += core network

QT       -= gui

TARGET = underwater-gateway-measure
CONFIG   += console
CONFIG   -= app_bundle
CONFIG += c++11
QMAKE_CXXFLAGS += -std=c++0x

TEMPLATE = app

# wiringPi
LIBS += -lwiringPi

SOURCES += main.cpp \
    ../underwater-gateway/adcinterface.cpp \
    ../underwater-gateway/computedmeasure.cpp \
    ../underwater-gateway/fileinterface.cpp \
    ../underwater-gateway/frame.cpp \
    ../underwater-gateway/frameparser.cpp \
    ../underwater-gateway/handler.cpp \
    ../underwater-gateway/i2c.cpp \
    ../underwater-gateway/imuinterface.cpp \
    ../underwater-gateway/measure.cpp \
    ../underwater-gateway/measurehandler.cpp \
    ../underwater-gateway/measureinterface.cpp \
    ../underwater-gateway/onewireinterface.cpp \
    ../underwater-gateway/tcpserver.cpp

HEADERS += \
    ../underwater-gateway/adcinterface.h \
    ../underwater-gateway/computedmeasure.h \
    ../underwater-gateway/fileinterface.h \
    ../underwater-gateway/frame.h \
    ../underwater-gateway/frameparser.h \
    ../underwater-gateway/handler.h \
    ../underwater-gateway/i2c.h \
    ../underwater-gateway/imuinterface.h \
    ../underwater-gateway/measure.h \
    ../underwater-gateway/measurehandler.h \
    ../underwater-gateway/measureinterface.h \
    ../underwater-gateway/onewireinterface.h \
    ../underwater-gateway/tcpserver.h
