#include "measure.h"

void Measure::update()
{
    value_ = multiplier_*(interface_->read()) + offset_;
    std::cout << value_ << std::endl;
}
