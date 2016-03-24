#include "axishandler.h"

AxisHandler::AxisHandler(unsigned int axesCount)
{
    axesCount_ = 0;
    setAxesCount(axesCount);
}

void AxisHandler::set(QStringList frame)
{
    /*if(frame.at(0) == QString("*"))
    {
        if(frame.length() == axesCount_+1)
        {
            QVector<int> values;
            for(int i=1; i<=axesCount_; ++i)
                values.push_back(frame.at(i).toInt());
            modbus_->writeMulti(getRegister(frame.at(0).toUInt(), regType::write), axesCount_, values);
        }
        else
            emit error("mało argsów");
    }
    else if(frame.length() == 2)
    {
        modbus_->write(getRegister(frame.at(0).toUInt(), regType::write), frame.at(1).toInt());
        emit response(QStringList() << QString(handlerType()) << frame);
    }
    else
        emit error("Wrong parameters count for Axis:set. Required 2, given "+QString::number(frame.length()));*/
    ModbusCommand* cmd;
    QStringList context = QStringList() << QString(handlerType());
    bool ok = false;

    if(frame.at(0) == QString("*")) // (S,A,*,...)
    {
        if(frame.length() == axesCount_+1)  // (S,A,*,pierwsza,druga,...)
        {
            context << QString("*");
            ok = true;
            QVector<int> values;

            for(int i=1; i<=axesCount_; ++i)
                values.push_back(frame.at(i).toInt());
            //rejestr kroków
            cmd = new ModbusCommandMultiwrite(context, getRegister(0, regType::write), axesCount_, values);
        }
        else
        {
            emit error("Not enough arguments to set all axes at once");
            return;
        }
    }
    else if(frame.at(0) == QString("s"))    // (S,A,s,...)
    {
        context << QString("s");
        if(frame.at(1) == QString("*")) // (S,A,s,*,...)
        {
            if(frame.length() == axesCount_+2)  // (S,A,s,*,piersza,druga,...)
            {
                context << QString("*");
                ok = true;
                QVector<int> values;

                for(int i=2; i<axesCount_+2; ++i)
                    values.push_back(frame.at(i).toInt());
                //rejestr prędkości
                cmd = new ModbusCommandMultiwrite(context, getRegister(0, regType::write), axesCount_, values);
            }
            else
            {
                emit error("Not enough arguments to set all axes' speed at once");
                return;
            }
        }
        else if(frame.length() == 3)    // (S,A,s,nr,wartość)
        {
            ok = true;
            //rejestr prędkości
            cmd = new ModbusCommandWrite(context, getRegister(frame.at(1).toInt(), regType::write), frame.at(2).toInt());
        }
        else
        {

        }
    }
    else if(frame.length() == 2)    // (S,A,nr,wartość)
    {
        ok = true;
        //rejestr kroków
        cmd = new ModbusCommandWrite(context, getRegister(frame.at(0).toInt(), regType::write), frame.at(1).toInt());
    }
    else
        emit error("Arguments count not valid. Required 2 or " + QString::number(axesCount_+1) + \
                   " (+1 for speed), given " + QString::number(frame.length()));
    if(ok)
    {
        connect(cmd, SIGNAL(done(QStringList,QStringList)), this, SLOT(finish(QStringList,QStringList)));
        connect(cmd, SIGNAL(error(QString)), this, SLOT(failure(QString)));
        modbus_->addCommand(cmd);
    }
}

void AxisHandler::get(QStringList frame)
{
    if(frame.length() == 0)
    {
        //wysłać wszystkie osie
    }
    else if(frame.length() == 1)
    {
        if(frame.at(0).toInt() < axesCount_ && frame.at(0).toInt() >= 0)
        {
            //pobranie z modbusa
            int value = modbus_->read(getRegister(frame.at(0).toUInt(), regType::read));
            //int value = 10;
            //jeśli się udało, to wysyłamy dane:
            emit response(QStringList() << QString(handlerType()) << frame.at(0) << QString::number(value));
        }
        else
        {
            emit error("Axis index out of range ("+frame.at(0)+" vs 0.."+QString::number(axesCount_));
            return;
        }
    }
    else
        emit error("Wrong parameters count for Axis:get. Required 1, given "+QString::number(frame.length()));
}

void AxisHandler::setAxesCount(unsigned int count)
{
    if(count < axesCount_)
    {
        assignedReadRegisters_.erase(assignedReadRegisters_.begin()+count, assignedReadRegisters_.end());
        assignedWriteRegisters_.erase(assignedWriteRegisters_.begin()+count, assignedWriteRegisters_.end());
        assignedSpeedRegisters_.erase(assignedSpeedRegisters_.begin()+count, assignedSpeedRegisters_.end());
    }
    else if(count > axesCount_)
    {
        for(unsigned int i=0; i<count-axesCount_; ++i)
        {
            assignedReadRegisters_.append(0);
            assignedWriteRegisters_.append(0);
            assignedSpeedRegisters_.append(0);
        }
    }
    axesCount_ = count;
}

void AxisHandler::assignRegister(unsigned int axisNr, regType type, int regAddr)
{
    if((axisNr <= axesCount_) && (axisNr <= assignedReadRegisters_.size()))
    {
        if(type == regType::read)
            assignedReadRegisters_[axisNr] = regAddr;
        else if(type == regType::write)
            assignedWriteRegisters_[axisNr] = regAddr;
        else if(type == regType::speed)
            assignedSpeedRegisters_[axisNr] = regAddr;
    }
    /*else
        emit error("Axis index out of range");*/
}

int AxisHandler::getRegister(unsigned int axisNr, regType type)
{
    if((axisNr <= axesCount_) && (axisNr <= assignedReadRegisters_.size()))
    {
        if(type == regType::read)
            return assignedReadRegisters_.at(axisNr);
        else if(type == regType::write)
            return assignedWriteRegisters_.at(axisNr);
        else if(type == regType::speed)
            return assignedSpeedRegisters_.at(axisNr);
    }
    /*else
    {
        emit error("Axis index out of range");
        return -1;
    }*/
}

