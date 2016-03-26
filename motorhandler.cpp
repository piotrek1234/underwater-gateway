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
    /*if(frame.at(0) == QString("*"))
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
        emit error("Arguments count not valid. Required 2 or 6, given "+QString::number(frame.length()));*/
    ModbusCommand* cmd;
    QStringList context = QStringList() << QString(handlerType()) << frame.at(0);
    bool ok = false;

    if(frame.at(0) == QString("*"))
    {
        if(frame.length() == motorsCount_+1)
        {
            ok = true;
            QVector<int> values;

            for(int i=1; i<=motorsCount_; ++i)
                values.push_back(frame.at(i).toInt());

            cmd = new ModbusCommandMultiwrite(context, getRegister(0), motorsCount_, values);
        }
        else
        {
            emit error("Not enough arguments to set all motors at once");
            return;
        }
    }
    else if(frame.length() == 2)
    {
        ok = true;
        cmd = new ModbusCommandWrite(context, getRegister(frame.at(0).toInt()), frame.at(1).toInt());
    }
    else
        emit error("Arguments count not valid. Required 2 or "+QString::number(motorsCount_+1)+\
                   ", given "+QString::number(frame.length()));
    if(ok)
    {
        connect(cmd, SIGNAL(done(QStringList,QStringList)), this, SLOT(finish(QStringList,QStringList)));
        connect(cmd, SIGNAL(error(QString)), this, SLOT(failure(QString)));
        modbus_->addCommand(cmd);
    }
}

void MotorHandler::get(QStringList frame)
{
    /*if(frame.length() == 1)
    {
        int val = modbus_->read(getRegister(frame.at(0).toUInt()));
        emit response(QStringList() << QString(handlerType()) << frame.at(0) << QString::number(val));
    }
    else if(frame.at(0) == QString("*"))
    {
        //wszystkie silniki

    }
    else
        emit error("Arguments count not valid. Required 1, given "+QString::number(frame.length()));*/
    if(frame.length() == 1)
    {
        QStringList context = QStringList() << QString(handlerType()) << frame.at(0);
        ModbusCommand* cmd;

        if(frame.at(0) == QString("*"))
        {
            cmd = new ModbusCommandMultiread(context, getRegister(0), motorsCount_);
        }
        else
        {
            cmd = new ModbusCommandRead(context, getRegister(frame.at(0).toInt()));
        }
        connect(cmd, SIGNAL(done(QStringList,QStringList)), this, SLOT(finish(QStringList,QStringList)));
        connect(cmd, SIGNAL(error(QString)), this, SLOT(failure(QString)));
        modbus_->addCommand(cmd);
    }
    else
        emit error("Arguments count not valid. Required 1, given "+QString::number(frame.length()));
}

void MotorHandler::setMotorsCount(unsigned int count)
{
    if(count < motorsCount_)
    {
        assignedRegisters_.erase(assignedRegisters_.begin()+count, assignedRegisters_.end());
    }
    else if(count > motorsCount_)
    {
        for(unsigned int i=0; i<count-motorsCount_; ++i)
            assignedRegisters_.append(0);
    }
    motorsCount_ = count;
}

void MotorHandler::assignRegister(unsigned int motorNr, int regAddr)
{
    if((motorNr <= motorsCount_) && (motorNr <= assignedRegisters_.size()))
        assignedRegisters_[motorNr] = regAddr;
    else
        emit error("Motor index out of range");
}

int MotorHandler::getRegister(unsigned int motor)
{
    if((motor <= motorsCount_) && (motor <= assignedRegisters_.size()))
        return assignedRegisters_.at(motor);

    emit error("Motor index out of range");
    return -1;
}

