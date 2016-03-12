#ifndef MODBUSMASTER_H
#define MODBUSMASTER_H

#include <QObject>

class ModbusMaster : public QObject
{
    Q_OBJECT
public:
    ModbusMaster();
    ~ModbusMaster();
public slots:
    void execute(int reg, int value);
};

#endif // MODBUSMASTER_H
