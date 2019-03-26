#ifndef FILTER_H
#define FILTER_H


class Filter
{
public:
    enum FilterType { NONE , KALMAN };

    Filter();
    virtual double calculate(double prev, double current) = 0;
    virtual FilterType getType() const = 0;
    virtual ~Filter();

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

#endif // FILTER_H
