#ifndef SVSERIES_H
#define SVSERIES_H

#include <QObject>
#include <QPointF>
#include <QLineSeries>
#include <QtMath>

class SVSeries
{
private:
    static const int chartTimeRange = 60;
    static const int chartTimeInc = 10;
    static const int chartStartAmp = 10;
    static const int chartAmpInc = 2;

    QtCharts::QLineSeries *series;
    QVector<QPointF> points;
    int chartAmp = chartStartAmp;
    int chartAxisStart = 0;
    quint32 chartStartTime = 0; //msec
public:
    SVSeries();
    SVSeries(QObject *series);

    void setSeriesObj(QObject *series);
    QtCharts::QLineSeries* getSeriesPtr();
    void addPoint(QPointF const& point);
    QPointF at(long pos) const;
    QPointF last() const;
    void clear();
    int size() const;
};

#endif // SVSERIES_H
