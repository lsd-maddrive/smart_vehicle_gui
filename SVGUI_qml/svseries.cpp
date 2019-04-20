#include "svseries.h"

SVSeries::SVSeries()
{

}

SVSeries::SVSeries(QObject *series, Filter::FilterType type) {
    this->series = dynamic_cast<QtCharts::QLineSeries*>(series);
    switch (type)   {
    case Filter::NONE:   {
        break;
    }
    case Filter::KALMAN:    {
        filter = new FilterKalman();
        break;
    }
    case Filter::GAF:   {
        filter = new FilterGA();
        break;
    }
    }
}

SVSeries::~SVSeries()   {
    delete filter;
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

    if (filter && !points.empty()) {
        value = filter->calculate(points.last().y(), value);
        points.append(QPointF(time, value));
    }   else {
        points.append(point);
    }

    if (time > chartTimeRange + chartAxisStart)
        chartAxisStart += chartTimeInc;

    if (series)  {
        series->replace(points);
        if (time > chartTimeRange) {
            series->attachedAxes().first()->setMax(chartAxisStart + chartTimeRange);
            series->attachedAxes().first()->setMin(chartAxisStart);
        }
        if (abs(value) >= chartAmp && autoScale) {
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
    if (autoScale)  {
        series->attachedAxes().at(1)->setMax(chartAmp);
        series->attachedAxes().at(1)->setMin(-chartAmp);
    }


    series->attachedAxes().at(0)->setMax(chartTimeRange);
    series->attachedAxes().at(0)->setMin(0);
}

int SVSeries::size() const    {
    return points.size();
}

void SVSeries::setAutoScale(bool autoScale) {
    this->autoScale = autoScale;
}

void SVSeries::setFilter(Filter::FilterType type)   {
    delete filter;

    switch (type)   {
    case Filter::NONE:   {
        break;
    }
    case Filter::KALMAN:    {
        filter = new FilterKalman();
        break;
    }
    case Filter::GAF:   {
        filter = new FilterGA();
        break;
    }
    }
}

bool SVSeries::setFilterK(float k)    {
    if (filter) {
        switch (filter->getType())  {
        case Filter::NONE:  {
            return false;
        }
        case Filter::KALMAN: {
            dynamic_cast<FilterKalman*>(filter)->setK(k);
            return true;
        }
        case Filter::GAF:   {
            return false;
        }
    }
    }
    return false;
}

Filter::FilterType SVSeries::filterType() const {
    return filter->getType();
}
