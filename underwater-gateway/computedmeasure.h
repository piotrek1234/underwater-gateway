#ifndef COMPUTEDMEASURE_H
#define COMPUTEDMEASURE_H

#include "measureinterface.h"
#include "measure.h"

class ComputedMeasure : public MeasureInterface
{
    Q_OBJECT
public:
    ComputedMeasure(Measure* measure);
    virtual double read();
    virtual ~ComputedMeasure() {}
private:
    Measure* measure_;

signals:

public slots:

};

#endif // COMPUTEDMEASURE_H
