#ifndef IMUINTERFACE_H
#define IMUINTERFACE_H

#include <stdint.h>
#include "measureinterface.h"
#include <wiringPiI2C.h>

class ImuInterface : public MeasureInterface
{
    Q_OBJECT
public:
    ImuInterface(int addr, int reg, int16_t limit, int16_t correction);
    virtual double read();
    void prepare();
private:
    int i2c_address;
    int i2c_register;
    static int handle;
    int16_t limit;
    int16_t correction;
    int16_t repair(int16_t what, int16_t limit, int16_t correction);
signals:

public slots:

};

#endif // IMUINTERFACE_H
