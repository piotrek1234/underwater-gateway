#include "modbuscommandwrite.h"

ModbusCommandWrite::ModbusCommandWrite(QStringList context, int address, int value) \
    : ModbusCommand(context, address), value_(value)
{
}

void ModbusCommandWrite::execute(ModbusMaster *modbus)
{
    if(modbus->write(address_, value_))
        emit done(context_, QStringList(QString::number(value_)));
    else
        emit error("(ModbusCmdWrite) Writing register failed. Context: " + context_.join(","));
}
