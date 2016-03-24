#ifndef PRESSUREHANDLER_H
#define PRESSUREHANDLER_H

#include "modbusinterface.h"

class PressureHandler : public ModbusInterface
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
    static const int PRESS_DIV = 100;
private slots:
    virtual void finish(QStringList context, QStringList args);
};

#endif // PRESSUREHANDLER_H
