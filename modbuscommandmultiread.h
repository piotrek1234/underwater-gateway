#ifndef MODBUSCOMMANDMULTIREAD_H
#define MODBUSCOMMANDMULTIREAD_H

#include "modbuscommand.h"
#include "modbusinterface.h"

class ModbusCommandMultiread : public ModbusCommand
{
public:
    ModbusCommandMultiread(QStringList context, int address, int num);
    virtual ~ModbusCommandMultiread() {}
    virtual void execute(ModbusMaster *modbus);
private:
    int num_;
};

#endif // MODBUSCOMMANDMULTIREAD_H
