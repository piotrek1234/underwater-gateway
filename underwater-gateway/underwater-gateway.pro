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

# opencv
LIBS += -L/usr/local/lib
LIBS += -lopencv_core
LIBS += -lopencv_imgproc
LIBS += -lopencv_highgui
LIBS += -lopencv_features2d

# wiringPi
LIBS += -lwiringPi

# modbus
LIBS += -lmodbus

TEMPLATE = app

SOURCES += main.cpp \
    tcpserver.cpp \
    frameparser.cpp \
    handler.cpp \
    motorhandler.cpp \
    axishandler.cpp \
    camerahandler.cpp \
    modbusmaster.cpp \
    udp-stream/PracticalSocket.cpp \
    cameraworker.cpp \
    modbusinterface.cpp \
    outputhandler.cpp \
    modbuscommandread.cpp \
    modbuscommandwrite.cpp \
    modbuscommandmultiread.cpp \
    modbuscommandmultiwrite.cpp \
    servicehandler.cpp \
    logger.cpp \
    modbuscommandping.cpp \
    measure.cpp \
    measureinterface.cpp \
    fileinterface.cpp \
    measurehandler.cpp \
    imuinterface.cpp \
    i2c.cpp \
    onewireinterface.cpp \
    adcinterface.cpp \
    computedmeasure.cpp

HEADERS += \
    tcpserver.h \
    frame.h \
    frameparser.h \
    handler.h \
    motorhandler.h \
    axishandler.h \
    camerahandler.h \
    modbusmaster.h \
    udp-stream/PracticalSocket.h \
    cameraworker.h \
    modbusinterface.h \
    modbus_regs.h \
    outputhandler.h \
    modbuscommand.h \
    modbuscommandread.h \
    modbuscommandwrite.h \
    modbuscommandmultiread.h \
    modbuscommandmultiwrite.h \
    servicehandler.h \
    logger.h \
    modbuscommandping.h \
    measure.h \
    measureinterface.h \
    fileinterface.h \
    measurehandler.h \
    imuinterface.h \
    i2c.h \
    onewireinterface.h \
    adcinterface.h \
    computedmeasure.h
