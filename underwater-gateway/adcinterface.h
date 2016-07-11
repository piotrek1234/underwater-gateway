#ifndef ADCINTERFACE_H
#define ADCINTERFACE_H

// https://github.com/angeloc/linux_iio_mcp3422

#include <QFile>
#include <QTextStream>
#include <deque>
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
    std::deque<double> queue;
signals:

public slots:

};

#endif // ADCINTERFACE_H
