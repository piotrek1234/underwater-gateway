#include "onewireinterface.h"
#include <iostream>

OneWireInterface::OneWireInterface(QString device) : device_(device)
{
}

double OneWireInterface::read()
{
    QFile file("/sys/bus/w1/devices/"+device_+"/w1_slave");
    if(!file.open(QIODevice::ReadOnly))
    {
        //błąd otwierania
        return -1;
    }

    QTextStream stream(&file);
    //double val;
    QString a = stream.readAll();
    int pos = a.indexOf("t=");
    QString val = a.mid(pos+2, 5);
    //std::cout << val.toStdString() << std::endl;

    return val.toDouble();
}
