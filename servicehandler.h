#ifndef SERVICEHANDLER_H
#define SERVICEHANDLER_H

#include "modbusinterface.h"
#include "modbus_regs.h"

class ServiceHandler : public ModbusInterface
{
public:
    ServiceHandler();
    virtual ~ServiceHandler() {}
    virtual void set(QStringList frame);
    virtual void get(QStringList frame);
    virtual char handlerType() const { return 'S'; }
private slots:
    virtual void finish(QStringList context, QStringList args);
};

#endif // SERVICEHANDLER_H
