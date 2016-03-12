#include "modbusinterface.h"

ModbusInterface::ModbusInterface()
{
}

void ModbusInterface::setModbus(ModbusMaster *modbus)
{
    modbus_ = modbus;
}
