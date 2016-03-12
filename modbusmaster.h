#ifndef MODBUSMASTER_H
#define MODBUSMASTER_H

#include <QObject>
#include <QString>
#include <modbus/modbus.h>

class ModbusMaster : public QObject
{
    Q_OBJECT
public:
    ModbusMaster(QString device, int slave, int baud);
    ~ModbusMaster();
    void write(int reg, int value);
    int read(int reg);
private:
    QString device_;
    int slave_;
    int baud_;
    modbus_t* modbus;
};

#endif // MODBUSMASTER_H
