#ifndef FILTER_H
#define FILTER_H

#include <QQueue>

class Filter
{
public:
    enum FilterType { NONE , KALMAN , LPF , GAF };

    Filter();
    virtual double calculate(double prev, double current) = 0;
    virtual FilterType getType() const = 0;
    virtual ~Filter();
private:
    static const FilterType type = NONE;
};

class FilterKalman : public Filter
{
private:
    float K;
    static const FilterType type = KALMAN;
public:
    FilterKalman(float K = 0.5);
    void setK(float K);
    float getK() const;
    double calculate(double prev, double current) override;
    FilterType getType() const override;
    ~FilterKalman() override;
};

class FilterLP : public Filter // low-pass filter
{
private:
    float K;
    static const FilterType type = LPF;
public:
    FilterLP(float K = 0.5);
    void setK(float K);
    float getK() const;
    FilterType getType() const override;
    double calculate(double prev, double current) override;
    ~FilterLP() override;
};

class FilterGA : public Filter //filter of gliding average :3
{
private:
    int N;
    QQueue<double> values;
    static const FilterType type = GAF;
public:
    FilterGA(int N = 5);
    void setN(int N);
    int getN() const;
    FilterType getType() const override;
    double calculate(double prev, double current) override;
    ~FilterGA() override;
};

#endif // FILTER_H
