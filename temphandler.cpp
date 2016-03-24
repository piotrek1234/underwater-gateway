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
    /*double temp = modbus_->read(assignedRegister);
    emit response(QStringList() << QString(handlerType()) << QString::number(temp, 'f', 2));*/

    QStringList context = QStringList() << QString(handlerType());
    ModbusCommand* cmd = new ModbusCommandRead(context, getRegister());
    connect(cmd, SIGNAL(done(QStringList,QStringList)), this, SLOT(finish(QStringList,QStringList)));
    connect(cmd, SIGNAL(error(QString)), this, SLOT(failure(QString)));
    modbus_->addCommand(cmd);
}

void TempHandler::assignRegister(int regAddr)
{
    assignedRegister = regAddr;
}

int TempHandler::getRegister()
{
    return assignedRegister;
}

void TempHandler::finish(QStringList context, QStringList args)
{
    emit response(context << QString::number(args.at(0).toDouble()/TEMP_DIV));
}

