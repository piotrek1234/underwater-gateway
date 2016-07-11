#ifndef MODBUSCOMMAND_H
#define MODBUSCOMMAND_H

#include <QObject>
//#include "modbusmaster.h"
#include <QStringList>
#include <QDateTime>

class ModbusMaster;

class ModbusCommand : public QObject
{
    Q_OBJECT
public:
    ModbusCommand(QStringList context, int address) : context_(context), address_(address)
    {
        created_ = QDateTime::currentDateTime();
    }
    virtual ~ModbusCommand() {}
    virtual void execute(ModbusMaster* modbus) = 0;
    QDateTime getCreateTime() { return created_; }
protected:
    QStringList context_;
    int address_;
    QDateTime created_;
signals:
    void done(QStringList context, QStringList effect);
    void error(QString);
};

#endif // MODBUSCOMMAND_H




