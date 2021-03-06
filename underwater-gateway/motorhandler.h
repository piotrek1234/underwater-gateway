#ifndef MOTORHANDLER_H
#define MOTORHANDLER_H

#include <QVector>
#include <QString>
#include "modbusinterface.h"

class MotorHandler : public ModbusInterface
{
    Q_OBJECT
public:
    MotorHandler() : motorsCount_(0), neutral(0) {}
    MotorHandler(unsigned int motorsCount);
    virtual ~MotorHandler();
    virtual void set(QStringList frame);
    virtual void get(QStringList frame);
    void setMotorsCount(unsigned int count);
    unsigned int getMotorsCount() { return motorsCount_; }
    void assignRegister(unsigned int motorNr, int regAddr);
    int getRegister(unsigned int motor);
    virtual char handlerType() const { return 'M'; }
    virtual QString description();
private:
    int rescale(int value);
    QVector<int> assignedRegisters_;
    unsigned int motorsCount_;
    int neutral;
};

#endif // MOTORHANDLER_H
