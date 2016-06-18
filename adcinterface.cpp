#include "adcinterface.h"

AdcInterface::AdcInterface(QString device, int channel) :
    device_(device), channel_(channel)
{
}

double AdcInterface::read()
{
    QFile file("/sys/bus/i2c/devices/"+device_+"/iio:device0/in_voltage"+QString::number(channel_)+"_raw"); //może być zonk z ":"
    if(!file.open(QIODevice::ReadOnly))
    {
        //błąd otwierania
        return -1;
    }

    QTextStream stream(&file);
    double val = stream.readLine().toDouble();

    return val;
}
