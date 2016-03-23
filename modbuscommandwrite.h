#ifndef MODBUSCOMMANDWRITE_H
#define MODBUSCOMMANDWRITE_H

#include "modbuscommand.h"
#include "modbusinterface.h"

class ModbusCommandWrite : public ModbusCommand
{
public:
    ModbusCommandWrite(QStringList context, int address, int value);
    virtual ~ModbusCommandWrite() {}
    virtual void execute(ModbusMaster *modbus);
private:
    int value_;
};

#endif // MODBUSCOMMANDWRITE_H
