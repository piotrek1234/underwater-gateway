#include "computedmeasure.h"

ComputedMeasure::ComputedMeasure(Measure *measure) : measure_(measure)
{
}

double ComputedMeasure::read()
{
    return measure_->get();
}
