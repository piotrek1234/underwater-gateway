#ifndef MEASURE_H
#define MEASURE_H

#include <QObject>
#include "measureinterface.h"
#include <iostream>

class Measure : public QObject
{
    Q_OBJECT
public:
    Measure(MeasureInterface* interface, double multiplier, double offset) : \
        interface_(interface), multiplier_(multiplier), offset_(offset) {}
    double get() { return value_; }
    void setInterface(MeasureInterface* interface) { interface_ = interface; }
    void setOffset(double offset) { offset_ = offset; }
    void setMultiplier(double multiplier) { multiplier_ = multiplier; }
protected:
    MeasureInterface* interface_;
    double value_;
    double multiplier_;
    double offset_;
signals:

public slots:
    void update();
};

#endif // MEASURE_H
