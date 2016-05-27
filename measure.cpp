#include "measure.h"

void Measure::update()
{
    value_ = multiplier_*interface_->read() + offset_;
}
