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
    ModbusCommand* cmd;
    QStringList context = QStringList() << QString(handlerType()) << frame.at(0);
    bool ok = false;

    if(frame.at(0) == QString("z"))
    {
        if(frame.length() == 2)
        {
            neutral = frame.at(1).toInt();
        }
    }
    else if(frame.at(0) == QString("*"))
    {
        if(frame.length() == motorsCount_+1)
        {
            ok = true;
            QVector<int> values;
            bool conv_ok;

            for(int i=1; i<=motorsCount_; ++i)
            {
                values.push_back(rescale(static_cast<int>(frame.at(i).toFloat(&conv_ok))));
                if(!conv_ok)
                {
                    emit error("(MotorHandler::set) Invalid int conversion");
                }
            }

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
        cmd = new ModbusCommandWrite(context, getRegister(frame.at(0).toInt()), rescale(frame.at(1).toInt()));
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

QString MotorHandler::description()
{
    QString addresses("");

    for(int i=0; i<assignedRegisters_.size(); ++i)
    {
        addresses += QString::number(getRegister(i));
        if(i < assignedRegisters_.size()-1)
            addresses += ",";
    }

    return QString(handlerType())+"/"+QString::number(motorsCount_)+"/"+addresses;
}

int MotorHandler::rescale(int value)
{
    if(value == 0)
        return 0;
    int ret = 100*(abs(value)-neutral)/(100-neutral);
    if(value > 0)
        return ret;
    //else
        return -ret;
}

