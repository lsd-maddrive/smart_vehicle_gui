#include "svseries.h"

SVSeries::SVSeries()
{

}

SVSeries::SVSeries(QObject *series) {
    this->series = dynamic_cast<QtCharts::QLineSeries*>(series);
}

void SVSeries::setSeriesObj(QObject *series)    {
    this->series = dynamic_cast<QtCharts::QLineSeries*>(series);
}

QtCharts::QLineSeries* SVSeries::getSeriesPtr() {
    return series;
}

void SVSeries::addPoint(QPointF const &point)  {
    double time = point.x();
    double value = point.y();
    points.append(point);

    if (time > chartTimeRange + chartAxisStart)
        chartAxisStart += chartTimeInc;

    if (series)  {
        series->replace(points);
        if (time > chartTimeRange) {
            series->attachedAxes().first()->setMax(chartAxisStart + chartTimeRange);
            series->attachedAxes().first()->setMin(chartAxisStart);
        }
        if (abs(value) >= chartAmp) {
            chartAmp = static_cast<int>(abs(value)) + chartAmpInc;
            series->attachedAxes().at(1)->setMax(chartAmp);
            series->attachedAxes().at(1)->setMin(-chartAmp);
        }
    }
}

QPointF SVSeries::at(long pos) const    {
    return points.at(pos);
}

QPointF SVSeries::last() const  {
    return points.last();
}

void SVSeries::clear()    {
    if (series != nullptr)
        series->clear();

    points.clear();

    chartAxisStart = 0;
    chartStartTime = 0;
    chartAmp = chartStartAmp;

    series->attachedAxes().at(1)->setMax(chartAmp);
    series->attachedAxes().at(1)->setMin(-chartAmp);

    series->attachedAxes().at(0)->setMax(chartTimeRange);
    series->attachedAxes().at(0)->setMin(0);
}

int SVSeries::size() const    {
    return points.size();
}
