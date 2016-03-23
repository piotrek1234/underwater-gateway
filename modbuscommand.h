#ifndef MODBUSCOMMAND_H
#define MODBUSCOMMAND_H

#include <QObject>
//#include "modbusmaster.h"
#include <QStringList>

class ModbusMaster;

class ModbusCommand : public QObject
{
    Q_OBJECT
public:
    ModbusCommand(QStringList context, int address) : context_(context), address_(address) {}
    virtual ~ModbusCommand() {}
    virtual void execute(ModbusMaster* modbus) = 0;
signals:
    void done(QStringList context, QStringList effect);
    void error(QString);
protected:
    QStringList context_;
    int address_;
};

#endif // MODBUSCOMMAND_H
