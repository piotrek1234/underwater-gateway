#include "outputhandler.h"

OutputHandler::OutputHandler(unsigned int outputsCount)
{
    outputsCount_ = 0;
    setOutputsCount(outputsCount);
}

void OutputHandler::assignRegister(unsigned int outputNr, int regAddr)
{
    if((outputNr <= outputsCount_) && (outputNr <= assignedRegisters_.size()))
            assignedRegisters_[outputNr] = regAddr;
        else
        emit error("Output index out of range");
}

int OutputHandler::getRegister(unsigned int outputNr)
{
    if((outputNr <= outputsCount_) && (outputNr <= assignedRegisters_.size()))
            return assignedRegisters_.at(outputNr);

    emit error("Output index out of range");
    return -1;
}

QString OutputHandler::description()
{
    QString addresses("");

    for(int i=0; i<assignedRegisters_.size(); ++i)
    {
        addresses += QString::number(getRegister(i));
        if(i < assignedRegisters_.size()-1)
            addresses += ",";
    }

    return QString(handlerType())+"/"+QString::number(outputsCount_)+"/"+addresses;
}

void OutputHandler::set(QStringList frame)
{
    ModbusCommand* cmd;
    QStringList context = QStringList() << QString(handlerType()) << frame.at(0);
    bool ok = false;

    if(frame.at(0) == QString("*"))
    {
        if(frame.length() == outputsCount_+1)
        {
            ok = true;
            QVector<int> values;

            for(int i=1; i<=outputsCount_; ++i)
                values.push_back(frame.at(i).toInt());

            cmd = new ModbusCommandMultiwrite(context, getRegister(0), outputsCount_, values);
        }
        else
        {
            emit error("Not enough arguments to set all outputs at once");
            return;
        }
    }
    else if(frame.length() == 2)
    {
        ok = true;
        cmd = new ModbusCommandWrite(context, getRegister(frame.at(0).toInt()), frame.at(1).toInt());
    }
    else
        emit error("Arguments count not valid. Required 2 or "+QString::number(outputsCount_+1)+\
                   ", given "+QString::number(frame.length()));
    if(ok)
    {
        connect(cmd, SIGNAL(done(QStringList,QStringList)), this, SLOT(finish(QStringList,QStringList)));
        connect(cmd, SIGNAL(error(QString)), this, SLOT(failure(QString)));
        modbus_->addCommand(cmd);
    }
}

void OutputHandler::get(QStringList frame)
{
    if(frame.length() == 1)
    {
        QStringList context = QStringList() << QString(handlerType()) << frame.at(0);
        ModbusCommand* cmd;

        if(frame.at(0) == QString("*"))
        {
            cmd = new ModbusCommandMultiread(context, getRegister(0), outputsCount_);
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

void OutputHandler::setOutputsCount(unsigned int count)
{
    if(count < outputsCount_)
        {
            assignedRegisters_.erase(assignedRegisters_.begin()+count, assignedRegisters_.end());
        }
        else if(count > outputsCount_)
        {
            for(unsigned int i=0; i<count-outputsCount_; ++i)
                assignedRegisters_.append(0);
        }
        outputsCount_ = count;
}
