#include "i2cinterface.h"

I2cInterface::I2cInterface(int dev, int addr, int reg) : i2c_device(dev), i2c_address(addr), i2c_register(reg)
{
}

double I2cInterface::read()
{

}
