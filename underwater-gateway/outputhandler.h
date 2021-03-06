#ifndef OUTPUTHANDLER_H
#define OUTPUTHANDLER_H

#include "modbusinterface.h"

class OutputHandler : public ModbusInterface
{
    Q_OBJECT
public:
    OutputHandler() : outputsCount_(0) {}
    OutputHandler(unsigned int outputsCount);
    virtual ~OutputHandler() {}
    virtual void set(QStringList frame);
    virtual void get(QStringList frame);
    void setOutputsCount(unsigned int count);
    unsigned int getOutputsCount() { return outputsCount_; }
    void assignRegister(unsigned int outputNr, int regAddr);
    int getRegister(unsigned int outputNr);
    virtual char handlerType() const { return 'O'; }
    virtual QString description();
private:
    int outputsCount_;
    QVector<int> assignedRegisters_;
};

#endif // OUTPUTHANDLER_H
