#include "imuinterface.h"

int ImuInterface::handle;

ImuInterface::ImuInterface(int addr, int reg, int16_t limit, int16_t correction) :
    i2c_address(addr), i2c_register(reg), limit(limit), correction(correction)
{

}

double ImuInterface::read()
{
    int16_t x = (((int16_t)wiringPiI2CReadReg8(handle, i2c_register+1) << 8) | wiringPiI2CReadReg8(handle, i2c_register)) & 0xFFFF;
    x/= 16;
    return repair(x, 360, 2048);
}

void ImuInterface::prepare()
{
    handle = wiringPiI2CSetup(i2c_address);
    wiringPiI2CWriteReg8(handle, 0x3d, 0b00001100);
}

int16_t ImuInterface::repair(int16_t what, int16_t limit, int16_t correction)
{
    if(what>limit)
        return what-correction;
    if(what<-limit)
        return what+correction;
    return what;
}
