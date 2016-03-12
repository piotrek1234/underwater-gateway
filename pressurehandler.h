#ifndef PRESSUREHANDLER_H
#define PRESSUREHANDLER_H

#include "handler.h"
#include "modbusinterface.h"

class PressureHandler : public Handler, public ModbusInterface
{
public:
    PressureHandler();
    virtual ~PressureHandler();
    virtual void set(QStringList);
    virtual void get(QStringList);
    virtual char handlerType() const { return 'P'; }
    void assignRegister(int regAddr);
    int getRegister();
private:
    int assignedRegister;
};

#endif // PRESSUREHANDLER_H
