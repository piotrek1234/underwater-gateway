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
    /*double press = modbus_->read(assignedRegister);
    emit response(QStringList() << QString(handlerType()) << QString::number(press, 'f', 2));*/
    QStringList context = QStringList() << QString(handlerType());
    ModbusCommand* cmd = new ModbusCommandRead(context, getRegister());
    connect(cmd, SIGNAL(done(QStringList,QStringList)), this, SLOT(finish(QStringList,QStringList)));
    connect(cmd, SIGNAL(error(QString)), this, SLOT(failure(QString)));
    modbus_->addCommand(cmd);
}

void PressureHandler::assignRegister(int regAddr)
{
    assignedRegister_ = regAddr;
}

int PressureHandler::getRegister()
{
    return assignedRegister_;
}

QString PressureHandler::description()
{
    return QString(handlerType())+"/"+QString::number(getRegister());
}

void PressureHandler::finish(QStringList context, QStringList args)
{
    emit response(context << QString::number(args.at(0).toDouble()/PRESS_DIV));
}



