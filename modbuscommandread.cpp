#include "modbuscommandread.h"
#include <iostream>


ModbusCommandRead::ModbusCommandRead(QStringList context, int address) : ModbusCommand(context, address)
{

}

void ModbusCommandRead::execute(ModbusMaster *modbus)
{
    QPair<bool, int> val = modbus->read(address_);
    if(val.first)
        emit done(context_, QStringList(QString::number(val.second)));
    else
        emit error("(ModbusCmdRead) Reading register failed. Context: " + context_.join(","));
}
