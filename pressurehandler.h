#ifndef PRESSUREHANDLER_H
#define PRESSUREHANDLER_H

#include "modbusinterface.h"

class PressureHandler : public ModbusInterface
{
    Q_OBJECT
public:
    PressureHandler();
    virtual ~PressureHandler();
    virtual void set(QStringList);
    virtual void get(QStringList);
    virtual char handlerType() const { return 'P'; }
    void assignRegister(int regAddr);
    int getRegister();
    virtual QString description();
private:
    int assignedRegister_;
    static const int PRESS_DIV = 100;
private slots:
    virtual void finish(QStringList context, QStringList args);
};

#endif // PRESSUREHANDLER_H
