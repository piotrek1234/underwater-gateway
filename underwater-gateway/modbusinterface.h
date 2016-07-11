#ifndef MODBUSINTERFACE_H
#define MODBUSINTERFACE_H

#include "modbusmaster.h"
#include "handler.h"

class ModbusInterface : public Handler
{
    Q_OBJECT
public:
    ModbusInterface();
    void setModbus(ModbusMaster* modbus);
protected:
    ModbusMaster* modbus_;
};

#endif // MODBUSINTERFACE_H
