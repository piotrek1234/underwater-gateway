#include "modbusmaster.h"

ModbusMaster::ModbusMaster(QString device, int slave, int baud, unsigned long delay) : \
    device_(device), slave_(slave), baud_(baud), delay_(delay), busy_(false), connected_(false)
{
    // istnienie konsoli uart (/dev/tty*)
    QFileInfo dev(device);
    if(!(dev.exists() && dev.isFile()))
    {
        std::cerr << "(Modbus init) No such device: " << device.toStdString() << "\n";
        return;
    }

    modbus_ = modbus_new_rtu(device.toStdString().c_str(), baud, 'N', 8, 1);
    if(modbus_ == NULL)
    {
        std::cerr << "(Modbus init) Could not initialize modbus rtu\n";
        return;
    }

    if(modbus_set_slave(modbus_, slave) == -1)
    {
        std::cerr << "(Modbus init) Failed to set slave address\n";
        modbus_free(modbus_);
    }

    if (modbus_connect(modbus_) == -1)
    {
        std::cerr << "(Modbus init) Modbus connection failed\n";
        modbus_free(modbus_);
        return;
    }

    connected_ = true;
    timer_.setInterval(delay);
    connect(&timer_, SIGNAL(timeout()), this, SLOT(reactivate()));
}

ModbusMaster::~ModbusMaster()
{
    modbus_close(modbus_);
    modbus_free(modbus_);
}

bool ModbusMaster::write(int reg, int value)
{
    if(connected_ && modbus_write_register(modbus_, reg, value) == 1)
    {
        return true;
    }

    std::cerr << "(Modbus::write) Writing modbus register failed.\n";
    if(!connected_)
        std::cerr << "(Modbus) Not connected\n";
    return false;
}

bool ModbusMaster::writeMulti(int first, int n, QVector<int> values)
{
    u_int16_t* vals = new u_int16_t[values.size()];
    for(int i=0; i<values.size(); ++i)
        vals[i] = values.at(i);

    if(connected_ && modbus_write_registers(modbus_, first, n, vals) == n)
    {
        delete [] vals;
        return true;
    }

    std::cerr << "(Modbus::writeMulti) Writing modbus registers failed.\n";
    delete [] vals;
    if(!connected_)
        std::cerr << "(Modbus) Not connected\n";
    return false;
}

QPair<bool, int> ModbusMaster::read(int reg)
{
    u_int16_t val;
    if(connected_ && modbus_read_registers(modbus_, reg, 1, &val) == 1)
    {
        return QPair<bool, int>(true, static_cast<int16_t>(val));
    }

    std::cerr << "(Modbus::read) Reading modbus register failed.\n";
    if(!connected_)
        std::cerr << "(Modbus) Not connected\n";
    return QPair<bool, int>(false, 0);
}

QPair<bool, QVector<int> > ModbusMaster::readMulti(int first, int n)
{
    u_int16_t* val = new u_int16_t[n];

    if(connected_ && modbus_read_registers(modbus_, first, n, val) == n)
    {
        QVector<int> values;
        for(int i=0; i<n; ++i)
            values.push_back(static_cast<int16_t>(val[i]));

        delete [] val;

        if(!connected_)
            std::cerr << "(Modbus) Not connected\n";

        return QPair<bool, QVector<int> >(true, values);
    }

    std::cerr << "(Modbus::readMulti) Reading modbus registers failed.\n";

    delete [] val;
    return QPair<bool, QVector<int> >(false, QVector<int>());
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
