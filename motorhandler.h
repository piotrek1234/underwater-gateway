#ifndef MOTORHANDLER_H
#define MOTORHANDLER_H

#include <QVector>
#include <QString>
#include "modbusinterface.h"
#include "modbuscommandread.h"
#include "modbuscommandwrite.h"
#include "modbuscommandmultiread.h"
#include "modbuscommandmultiwrite.h"

class MotorHandler : public ModbusInterface
{
public:
    MotorHandler() : motorsCount_(0) {}
    MotorHandler(unsigned int motorsCount);
    virtual ~MotorHandler();
    virtual void set(QStringList frame);
    virtual void get(QStringList frame);
    void setMotorsCount(unsigned int count);
    unsigned int getMotorsCount() { return motorsCount_; }
    void assignRegister(unsigned int motorNr, int regAddr);
    int getRegister(unsigned int motor);
    virtual char handlerType() const { return 'M'; }
private:
    QVector<int> assignedRegisters;
    unsigned int motorsCount_;
};

#endif // MOTORHANDLER_H
