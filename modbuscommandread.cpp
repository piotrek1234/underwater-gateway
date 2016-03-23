#include "modbuscommandread.h"
#include <iostream>


ModbusCommandRead::ModbusCommandRead(QStringList context, int address) : ModbusCommand(context, address)
{

}

void ModbusCommandRead::execute(ModbusMaster *modbus)
{
    int val = modbus->read(address_);
    emit done(context_, QStringList(QString::number(val)));
}
