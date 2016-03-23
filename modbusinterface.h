#ifndef MODBUSINTERFACE_H
#define MODBUSINTERFACE_H

#include "modbusmaster.h"
#include "handler.h"

/**
 * @brief The regType enum indicates Modbus register type (read only, write only)
 */
enum class regType{
    read,
    write,
};

class ModbusInterface : public Handler
{
public:
    ModbusInterface();
    void setModbus(ModbusMaster* modbus);
protected:
    ModbusMaster* modbus_;
};

#endif // MODBUSINTERFACE_H
