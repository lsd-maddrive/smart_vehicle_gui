#ifndef SVSERIES_H
#define SVSERIES_H

#include <QObject>
#include <QPointF>
#include <QLineSeries>
#include "filter.h"

class SVSeries
{
private:
    static const int chartTimeRange = 60;
    static const int chartTimeInc = 10;
    static const int chartStartAmp = 10;
    static const int chartAmpInc = 2;
    bool autoScale = true;

    QtCharts::QLineSeries *series;
    QVector<QPointF> points;
    int chartAmp = chartStartAmp;
    int chartAxisStart = 0;
    quint32 chartStartTime = 0; //msec

    Filter* filter = nullptr;
public:
    SVSeries();
    SVSeries(QObject *series, Filter::FilterType type = Filter::NONE);
    ~SVSeries();

    void setSeriesObj(QObject *series);
    QtCharts::QLineSeries* getSeriesPtr();
    void addPoint(QPointF const& point);
    QPointF at(long pos) const;
    QPointF last() const;
    void clear();
    int size() const;
    void setAutoScale(bool autoScale);

    void setFilter(Filter::FilterType type);
    bool setFilterK(float k);
    Filter::FilterType filterType() const;
};

#endif // SVSERIES_H
