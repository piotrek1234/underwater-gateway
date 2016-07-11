#include "modbuscommandmultiread.h"

ModbusCommandMultiread::ModbusCommandMultiread(QStringList context, int address, int num) \
    : ModbusCommand(context, address), num_(num)
{

}

void ModbusCommandMultiread::execute(ModbusMaster *modbus)
{
    QPair<bool, QVector<int> > vals_i = modbus->readMulti(address_, num_);

    if(vals_i.first)
    {
        QStringList vals;
        for(int i : vals_i.second)
            vals << QString::number(i);

        emit done(context_, vals);
    }
    else
    {
        emit error("(ModbusCmdMultiread) Reading registers failed. Context: " + context_.join(","));
    }
}
