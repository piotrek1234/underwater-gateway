#ifndef MODBUSMASTER_H
#define MODBUSMASTER_H

#include <QObject>
#include <QString>
#include <QThread>
#include <QVector>
#include <QList>
#include <QTimer>
#include <iostream>
#include "modbuscommandread.h"
#include "modbuscommandwrite.h"
#include "modbuscommandmultiread.h"
#include "modbuscommandmultiwrite.h"
#include <modbus/modbus.h>

class ModbusMaster : public QThread
{
    Q_OBJECT
public:
    ModbusMaster(QString device, int slave, int baud=57600, unsigned long delay=100);   //todo: sprawdzić optymalny delay
    ~ModbusMaster();
    void write(int reg, int value);
    void writeMulti(int first, int n, QVector<int> values);
    int read(int reg);
    QVector<int> readMulti(int first, int n);
    void addCommand(ModbusCommand* cmd);
private:
    QString device_;
    int slave_;
    int baud_;
    modbus_t* modbus;
    unsigned long delay_;
    QList<ModbusCommand*> commands_;
    QTimer timer;
private slots:
    void process();
};

#endif // MODBUSMASTER_H
