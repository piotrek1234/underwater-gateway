#ifndef MODBUSCOMMANDREAD_H
#define MODBUSCOMMANDREAD_H

#include "modbuscommand.h"
#include "modbusinterface.h"

class ModbusCommandRead : public ModbusCommand
{
public:
    ModbusCommandRead(QStringList context, int address);
    virtual ~ModbusCommandRead() {}
    virtual void execute(ModbusMaster *modbus);
};

#endif // MODBUSCOMMANDREAD_H
