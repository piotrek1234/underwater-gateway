#ifndef MODBUSCOMMANDPING_H
#define MODBUSCOMMANDPING_H

#include "modbuscommand.h"
#include "modbusinterface.h"

class ModbusCommandPing : public ModbusCommand
{
    Q_OBJECT
public:
    ModbusCommandPing(/*int address*/);
    virtual ~ModbusCommandPing() {}
    virtual void execute(ModbusMaster *modbus);
};

#endif // MODBUSCOMMANDPING_H
