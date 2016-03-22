#ifndef AXISHANDLER_H
#define AXISHANDLER_H

#include <QVector>
#include "handler.h"
#include "modbusinterface.h"

class AxisHandler : public Handler, public ModbusInterface
{
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
private:
    QVector<int> assignedReadRegisters_;
    QVector<int> assignedWriteRegisters_;
    unsigned int axesCount_;
};

#endif // AXISHANDLER_H
