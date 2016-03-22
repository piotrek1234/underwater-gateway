#include "modbusmaster.h"

ModbusMaster::ModbusMaster(QString device, int slave, int baud, unsigned long delay) : \
    device_(device), baud_(baud), slave_(slave), delay_(delay)
{
    modbus = modbus_new_rtu(device.toStdString().c_str(), baud, 'N', 8, 1);
    if(modbus == NULL)
        return; //lipa, nie udało się

    modbus_set_slave(modbus, slave);

    if (modbus_connect(modbus) == -1)
    {
        //fprintf(stderr, "Connection failed: %s\n", modbus_strerror(errno));
        modbus_free(modbus);
        return;
    }
}

ModbusMaster::~ModbusMaster()
{
    modbus_close(modbus);
    modbus_free(modbus);
}

void ModbusMaster::write(int reg, int value)
{
    if(modbus_write_register(modbus, reg, value) == 1)
    {
        QThread::msleep(delay_);
        return;
    }
    std::cerr << "Writing modbus register failed.\n";
}

int ModbusMaster::read(int reg)
{
    //todo: sprawdzić co się dzieje przy ujemnych liczbach
    u_int16_t val;
    if(modbus_read_registers(modbus, reg, 1, &val) == 1)
    {
        QThread::msleep(delay_);
        return val;
    }
    std::cerr << "Reading modbus register failed.\n";
}
