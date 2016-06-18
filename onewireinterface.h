#ifndef ONEWIREINTERFACE_H
#define ONEWIREINTERFACE_H

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
