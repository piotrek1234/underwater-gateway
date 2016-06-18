#include "onewireinterface.h"

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
    double val;
    QString a = stream.readAll();
    //todo: sparsować i wyciągnąć t=wartość

    return val;
}
