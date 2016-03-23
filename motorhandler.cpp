#include "motorhandler.h"

MotorHandler::MotorHandler(unsigned int motorsCount)
{
    motorsCount_ = 0;
    setMotorsCount(motorsCount);
}

MotorHandler::~MotorHandler()
{

}

void MotorHandler::set(QStringList frame)
{
    if(frame.at(0) == QString("*"))
    {
        if(frame.length() == motorsCount_+1)
        {
            QVector<int> values;
            for(int i=1; i<=motorsCount_; ++i)
                values.push_back(frame.at(i).toInt());
            modbus_->writeMulti(getRegister(frame.at(0).toUInt()), motorsCount_, values);

            //delete [] values;
        }
        else
            emit error("mało argsów");
    }
    else if(frame.length() == 2)
    {
        modbus_->write(getRegister(frame.at(0).toUInt()), frame.at(1).toInt());
    }
    else
        emit error("Arguments count not valid. Required 2 or 6, given "+QString::number(frame.length()));
}

void MotorHandler::get(QStringList frame)
{
    if(frame.length() == 1)
    {
        int val = modbus_->read(getRegister(frame.at(0).toUInt()));
        emit response(QStringList() << QString(handlerType()) << frame.at(0) << QString::number(val));
    }
    else if(frame.at(0) == QString("*"))
    {
        //wszystkie silniki

    }
    else
        emit error("Arguments count not valid. Required 1, given "+QString::number(frame.length()));
}

void MotorHandler::setMotorsCount(unsigned int count)
{
    if(count < motorsCount_)
    {
        assignedRegisters.erase(assignedRegisters.begin()+count, assignedRegisters.end());
    }
    else if(count > motorsCount_)
    {
        for(unsigned int i=0; i<count-motorsCount_; ++i)
            assignedRegisters.append(0);
    }
    motorsCount_ = count;
}

void MotorHandler::assignRegister(unsigned int motorNr, int regAddr)
{
    if((motorNr <= motorsCount_) && (motorNr <= assignedRegisters.size()))
        assignedRegisters[motorNr] = regAddr;
    else
        emit error("Motor index out of range");
}

int MotorHandler::getRegister(unsigned int motor)
{
    if((motor <= motorsCount_) && (motor <= assignedRegisters.size()))
        return assignedRegisters.at(motor);
    emit error("Motor index out of range");
}

