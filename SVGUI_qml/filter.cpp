#include "filter.h"

Filter::Filter()    {}

Filter::~Filter()   {}

FilterKalman::FilterKalman(float K) : K(K) {}

void FilterKalman::setK(float K)    {
    this->K = K;
}

float FilterKalman::getK() const    {
    return K;
}

double FilterKalman::calculate(double prev, double current)    {
    return K * current + (1 - K) * prev;
}

Filter::FilterType FilterKalman::getType() const    {
    return type;
}

FilterKalman::~FilterKalman() {}
