#include "modbuscommandmultiwrite.h"

ModbusCommandMultiwrite::ModbusCommandMultiwrite(QStringList context, int address, int num, QVector<int> values) \
    : ModbusCommand(context, address), num_(num), values_(values)
{

}

void ModbusCommandMultiwrite::execute(ModbusMaster *modbus)
{
    QStringList vals;
    for(int i : values_)
        vals << QString::number(i);

    if(modbus->writeMulti(address_, num_, values_))
        emit done(context_, vals);
    else
        emit error("(ModbusCmdMultiwrite) Writing multiple registers failed. Context: " + context_.join(","));
}
