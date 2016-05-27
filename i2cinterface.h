#ifndef I2CINTERFACE_H
#define I2CINTERFACE_H

#include "measureinterface.h"

class I2cInterface : public MeasureInterface
{
    Q_OBJECT
public:
    I2cInterface(int dev, int addr, int reg);
    virtual double read();
private:
    int i2c_device;
    int i2c_address;
    int i2c_register;
signals:

public slots:

};

#endif // I2CINTERFACE_H
