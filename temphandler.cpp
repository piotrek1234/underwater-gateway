#include "temphandler.h"

TempHandler::TempHandler()
{

}

TempHandler::~TempHandler()
{

}

void TempHandler::set(QStringList)
{
    emit error("Temperature is not settable");
}

void TempHandler::get(QStringList)
{
    //niezależnie od liczby parametrów wysłać pomiar temperatury
    //double temp = 20.4;
    double temp = modbus_->read(assignedRegister);
    emit response(QStringList() << QString(handlerType()) << QString::number(temp, 'f', 2));
}

void TempHandler::assignRegister(int regAddr)
{
    assignedRegister = regAddr;
}

int TempHandler::getRegister()
{
    return assignedRegister;
}

