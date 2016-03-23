#include "modbuscommandwrite.h"

ModbusCommandWrite::ModbusCommandWrite(QStringList context, int address, int value) \
    : ModbusCommand(context, address), value_(value)
{
}

void ModbusCommandWrite::execute(ModbusMaster *modbus)
{
    modbus->write(address_, value_);
    emit done(context_, QStringList(QString::number(value_)));
}
