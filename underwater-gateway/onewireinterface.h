#ifndef ONEWIREINTERFACE_H
#define ONEWIREINTERFACE_H

//http://mikrokontroler.pl/2013/08/05/pierwsze-kroki-z-raspberry-pi-obsluga-magistrali-1-wire/2/

#include "measureinterface.h"
#include <QFile>
#include <QTextStream>

class OneWireInterface : public MeasureInterface
{
    Q_OBJECT
public:
    OneWireInterface(QString device);
    virtual double read();
private:
    QString device_;
signals:

public slots:

};

#endif // ONEWIREINTERFACE_H
