#ifndef MODBUSMASTER_H
#define MODBUSMASTER_H

#include <QObject>
#include <QString>
#include <QThread>
#include <iostream>
#include <modbus/modbus.h>

class ModbusMaster : public QThread
{
    Q_OBJECT
public:
    ModbusMaster(QString device, int slave, int baud=57600, unsigned long delay=100);   //todo: sprawdzić optymalny delay
    ~ModbusMaster();
    void write(int reg, int value);
    int read(int reg);
private:
    QString device_;
    int slave_;
    int baud_;
    modbus_t* modbus;
    unsigned long delay_;
};

#endif // MODBUSMASTER_H
