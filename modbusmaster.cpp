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

void ModbusMaster::writeMulti(int first, int n, QVector<int> values)
{
    u_int16_t* vals = new u_int16_t[values.size()];
    for(int i=0; i<values.size(); ++i)
        vals[i] = values.at(i);

    if(modbus_write_registers(modbus, first, n, vals) == n)
    {
        QThread::msleep(delay_);
        delete [] vals;
        return;
    }
    std::cerr << "Writing modbus registers failed.\n";
    delete [] vals;
}

int ModbusMaster::read(int reg)
{
    u_int16_t val;
    if(modbus_read_registers(modbus, reg, 1, &val) == 1)
    {
        QThread::msleep(delay_);
        return static_cast<int16_t>(val);
    }
    std::cerr << "Reading modbus register failed.\n";
    return 0;
}

QVector<int> ModbusMaster::readMulti(int first, int n)
{
    u_int16_t* val = new u_int16_t[n];
    if(modbus_read_registers(modbus, first, 1, val) == n)
    {
        QVector<int> values;
        for(int i=0; i<n; ++i)
            values.push_back(static_cast<int>(val[i]));
        delete [] val;
        QThread::msleep(delay_);
        return values;
    }
    std::cerr << "Reading modbus register failed.\n";
    delete [] val;
    return QVector<int>();
}
