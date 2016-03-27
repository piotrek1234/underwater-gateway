#include "modbusmaster.h"

ModbusMaster::ModbusMaster(QString device, int slave, int baud, unsigned long delay) : \
    device_(device), slave_(slave), baud_(baud), delay_(delay), busy_(false)
{
    modbus_ = modbus_new_rtu(device.toStdString().c_str(), baud, 'N', 8, 1);
    if(modbus_ == NULL)
    {
        std::cerr << "Could not initialize modbus\n";
        return;
    }

    modbus_set_slave(modbus_, slave);

    if (modbus_connect(modbus_) == -1)
    {
        std::cerr << "Modbus connection failed\n";
        modbus_free(modbus_);
        return;
    }

    timer_.setInterval(delay);
    connect(&timer_, SIGNAL(timeout()), this, SLOT(reactivate()));
}

ModbusMaster::~ModbusMaster()
{
    modbus_close(modbus_);
    modbus_free(modbus_);
}

void ModbusMaster::write(int reg, int value)
{
    if(modbus_write_register(modbus_, reg, value) == 1)
    {
        //QThread::msleep(delay_);
        return;
    }
    std::cerr << "Writing modbus register failed.\n";
}

void ModbusMaster::writeMulti(int first, int n, QVector<int> values)
{
    u_int16_t* vals = new u_int16_t[values.size()];
    for(int i=0; i<values.size(); ++i)
        vals[i] = values.at(i);

    if(modbus_write_registers(modbus_, first, n, vals) == n)
    {
        //QThread::msleep(delay_);
        delete [] vals;
        return;
    }
    std::cerr << "Writing modbus registers failed.\n";
    delete [] vals;
}

int ModbusMaster::read(int reg)
{
    u_int16_t val;
    if(modbus_read_registers(modbus_, reg, 1, &val) == 1)
    {
        //QThread::msleep(delay_);
        return static_cast<int16_t>(val);
    }
    std::cerr << "Reading modbus register failed.\n";
    return 0;
}

QVector<int> ModbusMaster::readMulti(int first, int n)
{
    u_int16_t* val = new u_int16_t[n];
    if(modbus_read_registers(modbus_, first, n, val) == n)
    {
        QVector<int> values;
        for(int i=0; i<n; ++i)
            values.push_back(static_cast<int16_t>(val[i]));
        delete [] val;
        //QThread::msleep(delay_);
        return values;
    }
    std::cerr << "Reading modbus registers failed.\n";
    delete [] val;
    return QVector<int>();
}

void ModbusMaster::addCommand(ModbusCommand *cmd)
{
    commands_.push_back(cmd);

    if(!busy_)
        process();
}

void ModbusMaster::process()
{
    if(!commands_.isEmpty())
    {
        busy_ = true;
        ModbusCommand* cmd = commands_.front();
        commands_.pop_front();

        cmd->execute(this);
        timer_.start();

        cmd->deleteLater();
    }
    else
    {
        timer_.stop();
    }


}

void ModbusMaster::reactivate()
{
    timer_.stop();

    if(!commands_.isEmpty())
    {
        process();
    }
    else
        busy_ = false;
}
