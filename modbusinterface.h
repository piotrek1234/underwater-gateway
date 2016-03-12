#ifndef MODBUSINTERFACE_H
#define MODBUSINTERFACE_H

#include "modbusmaster.h"

class ModbusInterface
{
public:
    ModbusInterface();
    void setModbus(ModbusMaster* modbus);
protected:
    ModbusMaster* modbus_;
};

#endif // MODBUSINTERFACE_H
