#ifndef MODBUSCOMMANDMULTIWRITE_H
#define MODBUSCOMMANDMULTIWRITE_H

#include "modbuscommand.h"
#include "modbusinterface.h"

class ModbusCommandMultiwrite : public ModbusCommand
{
public:
    ModbusCommandMultiwrite(QStringList context, int address, int num, QVector<int> values);
    virtual ~ModbusCommandMultiwrite() {}
    virtual void execute(ModbusMaster *modbus);
private:
    QVector<int> values_;
    int num_;
};

#endif // MODBUSCOMMANDMULTIWRITE_H
