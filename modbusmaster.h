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
    void writeMulti(int first, int n, u_int16_t *values);
    int read(int reg);
    u_int16_t* readMulti(int first, int n);
private:
    QString device_;
    int slave_;
    int baud_;
    modbus_t* modbus;
    unsigned long delay_;
};

#endif // MODBUSMASTER_H
