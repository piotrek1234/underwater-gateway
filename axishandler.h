#ifndef AXISHANDLER_H
#define AXISHANDLER_H

#include <QVector>
#include "handler.h"
#include "modbusmaster.h"

class AxisHandler : public Handler
{
public:
    AxisHandler() : axesCount_(0) {}
    AxisHandler(unsigned int axesCount);
    virtual ~AxisHandler();
    virtual void set(QStringList frame);
    virtual void get(QStringList frame);
    void setModbus(ModbusMaster* modbus);
    void setAxesCount(unsigned int count);
    unsigned int getAxesCount() { return axesCount_; }
    void assignRegister(unsigned int axisNr, int regAddr);
    int getRegister(unsigned int axisNr);
    virtual char handlerType() const { return 'A'; }
private:
    QVector<int> assignedRegisters;
    unsigned int axesCount_;
    ModbusMaster* modbus_;
};

#endif // AXISHANDLER_H
