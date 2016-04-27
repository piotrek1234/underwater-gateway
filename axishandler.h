#ifndef AXISHANDLER_H
#define AXISHANDLER_H

#include <QVector>
#include "modbusinterface.h"

enum class regType{
    read,
    write,
    speed,
    gear
};

class AxisHandler : public ModbusInterface
{
    Q_OBJECT
public:
    AxisHandler() : axesCount_(0) {}
    AxisHandler(unsigned int axesCount);
    virtual ~AxisHandler() {}
    virtual void set(QStringList frame);
    virtual void get(QStringList frame);
    void setAxesCount(unsigned int count);
    unsigned int getAxesCount() { return axesCount_; }
    void assignRegister(unsigned int axisNr, regType type, int regAddr);
    int getRegister(unsigned int axisNr, regType type);
    virtual char handlerType() const { return 'A'; }
    virtual QString description();
private:
    QVector<int> assignedReadRegisters_;
    QVector<int> assignedWriteRegisters_;
    QVector<int> assignedSpeedRegisters_;
    QVector<int> assignedGearRegisters_;
    unsigned int axesCount_;
};

#endif // AXISHANDLER_H
