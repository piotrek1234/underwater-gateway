#ifndef TEMPHANDLER_H
#define TEMPHANDLER_H

#include "modbusinterface.h"

class TempHandler : public ModbusInterface
{
public:
    TempHandler();
    virtual ~TempHandler();
    virtual void set(QStringList);
    virtual void get(QStringList);
    virtual char handlerType() const { return 'T'; }
    void assignRegister(int regAddr);
    int getRegister();
private:
    int assignedRegister_;
    static const int TEMP_DIV = 100;
private slots:
    virtual void finish(QStringList context, QStringList args);
};

#endif // TEMPHANDLER_H
