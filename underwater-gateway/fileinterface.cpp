#include "fileinterface.h"

double FileInterface::read()
{
    QFile file(file_);
    if(!file.open(QIODevice::ReadOnly))
    {
        //błąd otwierania
        return -1;
    }

    QTextStream stream(&file);
    double val = stream.readLine().toDouble();

    return val;
}
