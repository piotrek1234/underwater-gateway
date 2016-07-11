#include "modbuscommandping.h"

ModbusCommandPing::ModbusCommandPing() : ModbusCommand(QStringList(), 0)
{
}

void ModbusCommandPing::execute(ModbusMaster *modbus)
{
    modbus->ping();
}
