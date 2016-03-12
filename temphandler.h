#ifndef TEMPHANDLER_H
#define TEMPHANDLER_H

#include "handler.h"
#include "modbusinterface.h"

class TempHandler : public Handler, public ModbusInterface
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
    int assignedRegister;
};

#endif // TEMPHANDLER_H
