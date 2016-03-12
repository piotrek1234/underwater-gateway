#-------------------------------------------------
#
# Project created by QtCreator 2016-02-13T19:25:56
#
#-------------------------------------------------

QT       += core network

QT       -= gui

TARGET = underwater-gateway
CONFIG   += console
CONFIG   -= app_bundle
CONFIG += c++11
QMAKE_CXXFLAGS += -std=c++0x

#INCLUDEPATH += /usr/include/opencv2
LIBS += -L/usr/local/lib
LIBS += -lopencv_core
LIBS += -lopencv_imgproc
LIBS += -lopencv_highgui
LIBS += -lopencv_features2d

TEMPLATE = app


SOURCES += main.cpp \
    tcpserver.cpp \
    frame.cpp \
    frameparser.cpp \
    handler.cpp \
    motorhandler.cpp \
    axishandler.cpp \
    camerahandler.cpp \
    temphandler.cpp \
    pressurehandler.cpp \
    modbusmaster.cpp \
    udp-stream/PracticalSocket.cpp \
    cameraworker.cpp

HEADERS += \
    tcpserver.h \
    frame.h \
    frameparser.h \
    handler.h \
    motorhandler.h \
    axishandler.h \
    camerahandler.h \
    temphandler.h \
    pressurehandler.h \
    modbusmaster.h \
    udp-stream/PracticalSocket.h \
    cameraworker.h
