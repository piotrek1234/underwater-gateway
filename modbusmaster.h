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
    ModbusMaster(QString device, int slave, int baud=57600, unsigned long delay=50);   //todo: sprawdzić optymalny delay
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
    unsigned long delay_;
    modbus_t* modbus_;
    QList<ModbusCommand*> commands_;
    QTimer timer_;
    bool busy_;
private slots:
    void process();
    void reactivate();
signals:
    void error(QString);
};

#endif // MODBUSMASTER_H
