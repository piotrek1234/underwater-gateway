#include "axishandler.h"

AxisHandler::AxisHandler(unsigned int axesCount)
{
    axesCount_ = 0;
    setAxesCount(axesCount);
}

AxisHandler::~AxisHandler()
{

}

void AxisHandler::set(QStringList frame)
{
    if(frame.length() == 2)
    {
        //0 - numer osi
        //1 - kroki
        //todo: sprawdzić czy frame trzyma inty
        modbus_->write(assignedRegisters.at(frame.at(1).toInt()), frame.at(2).toInt());
        emit response(QStringList() << QString(handlerType()) << frame);
    }
    else
        emit error("Wrong parameters count for Axis::set. Required 2, given "+QString::number(frame.length()));
}

void AxisHandler::get(QStringList frame)
{
    if(frame.length() == 1)
    {
        if(frame.at(0).toInt() < axesCount_ && frame.at(0).toInt() >= 0)
        {
            //pobranie z modbusa
            int value = modbus_->read(assignedRegisters.at(frame.at(1).toInt()));
            //int value = 10;
            //jeśli się udało, to wysyłamy dane:
            emit response(QStringList() << QString(handlerType()) << frame.at(0) << QString::number(value));
        }
        else
        {
            emit error("Axis index out of range");
            return;
        }
    }
    else
        emit error("Wrong parameters count for Axis::get. Required 1, given "+QString::number(frame.length()));
}

void AxisHandler::setAxesCount(unsigned int count)
{
    if(count < axesCount_)
    {
        assignedRegisters.erase(assignedRegisters.begin()+count, assignedRegisters.end());
    }
    else if(count > axesCount_)
    {
        for(unsigned int i=0; i<count-axesCount_; ++i)
            assignedRegisters.append(0);
    }
    axesCount_ = count;
}

void AxisHandler::assignRegister(unsigned int axisNr, int regAddr)
{
    if((axisNr <= axesCount_) && (axisNr <= assignedRegisters.size()))
        assignedRegisters[axisNr] = regAddr;
    else
        emit error("Axis index out of range");
}

int AxisHandler::getRegister(unsigned int axisNr)
{
    if((axisNr <= axesCount_) && (axisNr <= assignedRegisters.size()))
        return assignedRegisters.at(axisNr);
    else
    {
        emit error("Axis index out of range");
        return -1;
    }
}

