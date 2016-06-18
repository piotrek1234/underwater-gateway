#ifndef ADCINTERFACE_H
#define ADCINTERFACE_H

#include <QFile>
#include <QTextStream>
#include "measureinterface.h"

class AdcInterface : public MeasureInterface
{
    Q_OBJECT
public:
    AdcInterface(QString device, int channel);
    virtual double read();
private:
    QString device_;
    int channel_;
signals:

public slots:

};

#endif // ADCINTERFACE_H
