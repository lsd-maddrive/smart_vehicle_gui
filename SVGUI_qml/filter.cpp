#include "filter.h"

Filter::~Filter()   {}

FilterKalman::FilterKalman(float K) : K(K) {}

void FilterKalman::setK(float K)    {
    this->K = K;
}

float FilterKalman::getK() const    {
    return K;
}

Filter::FilterType FilterKalman::getType() const    {
    return type;
}

double FilterKalman::calculate(double prev, double current)    {
    return K * current + (1 - K) * prev;
}

FilterKalman::~FilterKalman() {}

FilterGA::FilterGA(int N) : N(N)  {}

void FilterGA::setN(int N)    {
    this->N = N;
}

int FilterGA::getN() const    {
    return N;
}

Filter::FilterType FilterGA::getType() const    {
    return type;
}

double FilterGA::calculate(double prev, double current) {
    values.enqueue(current);
    if (values.isEmpty())   {
        return current;
    }

    if (values.size() < N)  {
        double sum = 0;
        for (double &value : values)    {
            sum += value;
        }
        return 1.0 / values.size() * sum;
    }

    double lastInFilterRange = values.dequeue();
    return prev + 1.0 / N * (current - lastInFilterRange);
}

FilterGA::~FilterGA()   {}
