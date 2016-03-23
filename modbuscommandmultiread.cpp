#include "modbuscommandmultiread.h"

ModbusCommandMultiread::ModbusCommandMultiread(QStringList context, int address, int num) \
    : ModbusCommand(context, address), num_(num)
{

}

void ModbusCommandMultiread::execute(ModbusMaster *modbus)
{
    QVector<int> vals_i = modbus->readMulti(address_, num_);
    QStringList vals;
    for(int i : vals_i)
        vals << QString::number(i);

    emit done(context_, vals);
}
