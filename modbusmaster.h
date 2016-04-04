#ifndef MODBUSMASTER_H
#define MODBUSMASTER_H

#include <QObject>
#include <QString>
#include <QThread>
#include <QVector>
#include <QPair>
#include <QList>
#include <QTimer>
#include <iostream>
#include <QFileInfo>
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
    bool write(int reg, int value);
    bool writeMulti(int first, int n, QVector<int> values);
    QPair<bool, int> read(int reg);
    QPair<bool, QVector<int> > readMulti(int first, int n);
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
    bool connected_;
private slots:
    void process();
    void reactivate();
signals:
    void error(QString);
};

#endif // MODBUSMASTER_H
