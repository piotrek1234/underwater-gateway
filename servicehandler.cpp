#include "servicehandler.h"

ServiceHandler::ServiceHandler()
{
}

void ServiceHandler::set(QStringList frame)
{
    /* S,S,..
     * m,nr - ustawienie trybu na nr
     * c,r  - reset sterownika
     * c,z  - zerowanie osi manipulatora
     */

    if(frame.length() == 2)
    {
        ModbusCommand* cmd;
        QStringList context = QStringList() << QString(handlerType()) << frame.at(0);

        if(frame.at(0) == QString("m"))
        {
            cmd = new ModbusCommandWrite(context, MB_CTRL_MODE, frame.at(1).toInt());
        }
        else if(frame.at(0) == QString("c"))
        {
            int val;
            if(frame.at(1) == QString("r"))
                val = MB_CTRL_CMD_DRIVER_RESET; //todo: to ma być flaga a nie wartość
            else if(frame.at(1) == QString("z"))
                val = MB_CTRL_CMD_RESET_STEPPERS; //todo: to ma być flaga a nie wartość
            else
            {
                emit error("(ServiceHandler) Command not known:" + frame.at(1));
                return;
            }
            cmd = new ModbusCommandWrite(context, MB_CTRL_CMD, val);
        }
        else
        {
            emit error("(ServiceHandler) Service type not known for set: " + frame.at(0));
            return;
        }

        connect(cmd, SIGNAL(done(QStringList,QStringList)), this, SLOT(finish(QStringList,QStringList)));
        connect(cmd, SIGNAL(error(QString)), this, SLOT(failure(QString)));
        modbus_->addCommand(cmd);
    }
    else
    {
        emit error("(ServiceHandler) Arguments count not valid for set. Required 2, given "+QString::number(frame.length()));
        return;
    }
}

void ServiceHandler::get(QStringList frame)
{
    QStringList context = QStringList() << QString(handlerType());
    ModbusCommand* cmd;

    if(frame.length() == 1)
    {
        context << frame.at(0);

        if(frame.at(0) == QString("m"))
        {
            cmd = new ModbusCommandRead(context, MB_CTRL_MODE);
        }
        else if(frame.at(0) == QString("c"))
        {
            cmd = new ModbusCommandRead(context, MB_STAT_DRIVER);
        }
        else if(frame.at(0) == QString("t"))
        {
            cmd = new ModbusCommandRead(context, MB_STAT_RUNTIME);
        }
        else
        {
            emit error("(ServiceHandler) Service type not known for get: " + frame.at(0));
            return;
        }
    }
    else
    {
        emit error("(ServiceHandler) Arguments count not valid for get. Required 1, given "+QString::number(frame.length()));
        return;
    }

    connect(cmd, SIGNAL(done(QStringList,QStringList)), this, SLOT(finish(QStringList,QStringList)));
    connect(cmd, SIGNAL(error(QString)), this, SLOT(failure(QString)));
    modbus_->addCommand(cmd);
}

void ServiceHandler::finish(QStringList context, QStringList args)
{
    //todo: poprzerabiać flagi na z lub r jeśli było zapytanie o CMD
    emit response(context << args); //tymczasowo
}
