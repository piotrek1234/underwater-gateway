#-------------------------------------------------
#
# Project created by QtCreator 2016-04-27T15:34:22
#
#-------------------------------------------------

QT       += core network

QT       -= gui

TARGET = underwater-gateway-control
CONFIG   += console
CONFIG   -= app_bundle
CONFIG += c++11
QMAKE_CXXFLAGS += -std=c++0x

TEMPLATE = app

# modbus
LIBS += -lmodbus

SOURCES += main.cpp \
    ../underwater-gateway/axishandler.cpp \
    ../underwater-gateway/frame.cpp \
    ../underwater-gateway/frameparser.cpp \
    ../underwater-gateway/handler.cpp \
    ../underwater-gateway/modbuscommandmultiread.cpp \
    ../underwater-gateway/modbuscommandmultiwrite.cpp \
    ../underwater-gateway/modbuscommandping.cpp \
    ../underwater-gateway/modbuscommandread.cpp \
    ../underwater-gateway/modbuscommandwrite.cpp \
    ../underwater-gateway/modbusinterface.cpp \
    ../underwater-gateway/modbusmaster.cpp \
    ../underwater-gateway/motorhandler.cpp \
    ../underwater-gateway/outputhandler.cpp \
    ../underwater-gateway/servicehandler.cpp \
    ../underwater-gateway/tcpserver.cpp \

HEADERS += \
    ../underwater-gateway/axishandler.h \
    ../underwater-gateway/frame.h \
    ../underwater-gateway/frameparser.h \
    ../underwater-gateway/handler.h \
    ../underwater-gateway/modbuscommand.h \
    ../underwater-gateway/modbuscommandmultiread.h \
    ../underwater-gateway/modbuscommandmultiwrite.h \
    ../underwater-gateway/modbuscommandping.h \
    ../underwater-gateway/modbuscommandread.h \
    ../underwater-gateway/modbuscommandwrite.h \
    ../underwater-gateway/modbusinterface.h \
    ../underwater-gateway/modbusmaster.h \
    ../underwater-gateway/modbus_regs.h \
    ../underwater-gateway/motorhandler.h \
    ../underwater-gateway/outputhandler.h \
    ../underwater-gateway/servicehandler.h \
    ../underwater-gateway/tcpserver.h \
