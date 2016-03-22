#ifndef OUTPUTHANDLER_H
#define OUTPUTHANDLER_H

#include "handler.h"
#include "modbusinterface.h"

class OutputHandler : public Handler, public ModbusInterface
{
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
private:
    int outputsCount_;
};

#endif // OUTPUTHANDLER_H
