#include "pressurehandler.h"

PressureHandler::PressureHandler()
{

}

PressureHandler::~PressureHandler()
{

}

void PressureHandler::set(QStringList)
{
    emit error("Pressure is not settable");
}

void PressureHandler::get(QStringList)
{
    //niezależnie od liczby parametrów wysłać pomiar ciśnienia
    //double press = 1234.56;
    double press = modbus_->read(assignedRegister);
    emit response(QStringList() << QString(handlerType()) << QString::number(press, 'f', 2));
}

void PressureHandler::assignRegister(int regAddr)
{
    assignedRegister = regAddr;
}

int PressureHandler::getRegister()
{
    return assignedRegister;
}



