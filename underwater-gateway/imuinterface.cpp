#include "imuinterface.h"

int ImuInterface::handle;

ImuInterface::ImuInterface(I2C* i2c, int reg, int16_t limit, int16_t correction) :
    i2c(i2c), i2c_register(reg), limit(limit), correction(correction)
{
    handle = i2c->getHandle();
}

double ImuInterface::read()
{
    int16_t x = (((int16_t)wiringPiI2CReadReg8(handle, i2c_register+1) << 8) | wiringPiI2CReadReg8(handle, i2c_register)) & 0xFFFF;
    x/= 16;
    return repair(x, 360, 2048);
}

void ImuInterface::prepare()
{
    wiringPiI2CWriteReg8(handle, 0x3d, 0b00001100); //tryb NDOF
}

int16_t ImuInterface::repair(int16_t what, int16_t limit, int16_t correction)
{
    if(what>limit)
        return what-correction;
    if(what<-limit)
        return what+correction;
    return what;
}
