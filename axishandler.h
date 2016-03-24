#ifndef AXISHANDLER_H
#define AXISHANDLER_H

#include <QVector>
#include "modbusinterface.h"

/**
 * @brief The regType enum indicates Modbus register type (read only, write only)
 */
enum class regType{
    read,
    write,
    speed
};

class AxisHandler : public ModbusInterface
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
    QVector<int> assignedSpeedRegisters_;
    unsigned int axesCount_;
};

#endif // AXISHANDLER_H
