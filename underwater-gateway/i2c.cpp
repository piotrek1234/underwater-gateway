#include "i2c.h"

I2C::I2C(int address) : address(address)
{
}

void I2C::prepare()
{
    handle = wiringPiI2CSetup(address);
}
