#-------------------------------------------------
#
# Project created by QtCreator 2016-04-27T15:24:34
#
#-------------------------------------------------

QT       += core network

QT       -= gui

TARGET = underwater-gateway-cam
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app
CONFIG += c++11
QMAKE_CXXFLAGS += -std=c++0x

# opencv
LIBS += -L/usr/local/lib
LIBS += -lopencv_core
LIBS += -lopencv_imgproc
LIBS += -lopencv_highgui
LIBS += -lopencv_features2d

SOURCES += main.cpp \
    ../underwater-gateway/udp-stream/PracticalSocket.cpp \
    ../underwater-gateway/camerahandler.cpp \
    ../underwater-gateway/cameraworker.cpp \
    ../underwater-gateway/frame.cpp \
    ../underwater-gateway/frameparser.cpp \
    ../underwater-gateway/handler.cpp \
    ../underwater-gateway/tcpserver.cpp

HEADERS += \
    ../underwater-gateway/udp-stream/PracticalSocket.h \
    ../underwater-gateway/camerahandler.h \
    ../underwater-gateway/cameraworker.h \
    ../underwater-gateway/frame.h \
    ../underwater-gateway/frameparser.h \
    ../underwater-gateway/handler.h \
    ../underwater-gateway/tcpserver.h
