#include "adapter.h"

Adapter::Adapter(QObject *parent) : QObject(parent) {

}

QString Adapter::getStatusStr(const qint8 &state)  {
    QString stateString;
    switch (state)    {
        case 0: {
            stateString = "FAULT";
            break;
        }
        case 1: {
            stateString = "RUN";
            break;
        }
        case 2: {
            stateString = "STOP";
            break;
        }
        case 3: {
            stateString = "WAIT";
            break;
        }
        default:    {
            stateString = "UNKNOWN";
        }
    }
    return stateString;
}

void Adapter::clearCharts() {

    if (encoderSeries)
        encoderSeries->clear();
    if (potentiometerSeries)
        potentiometerSeries->clear();

    encoderChartArray.clear();
    potentiometerChartArray.clear();

    chartAxisStart = 0;
    chartStartTime = 0;
    chartEncAmpl = chartStartAmp;
    chartPotAmpl = chartStartAmp;
}

void Adapter::slotTest()    {
    qDebug() << "Test slot was called.";
}

void Adapter::log(const QString &message)   {
    emit signalUILog(message);
}

void Adapter::slotUISetSerieses(QObject *encoderSeries, QObject *potentiometerSeries)   {
    this->encoderSeries = qobject_cast<QtCharts::QLineSeries*>(encoderSeries);
    this->potentiometerSeries = qobject_cast<QtCharts::QLineSeries*>(potentiometerSeries);
    qDebug() << "Chart serieses initialized";
}

void Adapter::slotUISearch()    {
    emit signalSearch();
}

void Adapter::slotUIConnect(QString address, QString portStr)    {
    qDebug() << "Adapter: incoming connect signal";
    log("Connecting to " + address + "...");
    quint16 port = static_cast<quint16>(portStr.toInt());
    emit signalConnect(address, port);
}

void Adapter::slotUIDisconnect()    {
    emit signalDisconnect();
}

void Adapter::slotUISettingsLoad(float p, float i, float d, float zero)  {
    log("Loading settings...");
    SetPackage set(p, i, d, zero);
    emit signalSettingsLoad(set);
}

void Adapter::slotUISettingsUpload()    {
    log("Uploading settings...");
    emit signalSettingsUpload();
}

void Adapter::slotUICommandForward(float const& distantion) {
    TaskPackage task(COI, 1, {static_cast<qint32>(distantion)});
    log("Command move forward for distantion: " + QString::number(distantion) + ", COI: " + QString::number(COI));
    COI++;
    if (COI >= 127)
        COI = 1;
    emit signalCommand(task);
}

void Adapter::slotUICommandWheels(float const& angle) {
    TaskPackage task(COI, 2, {static_cast<qint32>(angle)});
    log("Command rotate wheels for angle: " + QString::number(angle) + ", COI: " + QString::number(COI));
    COI++;
    if (COI >= 127)
        COI = 1;
    emit signalCommand(task);
}

void Adapter::slotUICommandFlick() {
    TaskPackage task(COI, 3);
    log("Command flick, COI: " + QString::number(COI));
    COI++;
    if (COI >= 127)
        COI = 1;
    emit signalCommand(task);
}

void Adapter::slotAddresses(QList<QString> const& addresses)    {
    emit signalUIAddresses(addresses);
}

void Adapter::slotConnected(qint8 const& state)   {
    qDebug() << "Adapter: Connected";
    emit signalUIConnected();
    emit signalUIStatus(getStatusStr(state));

    clearCharts();

    log("Connected.");
}

void Adapter::slotDisconnected()    {
    qDebug() << "Adapter: Disconnected";
    emit signalUIDisconnected();
    log("Disconnected.");
}

void Adapter::slotConnectionError(QString message) {
    qDebug() << "Adapter: Connection error";
    emit signalUIConnectionError();
    log("Connection error: " + message);
}

QVector<QPointF> Adapter::getChartData(const QVector<QPointF> &allPoints)  {
    QVector<QPointF> points;
    int size = allPoints.size();
    float rangeStart = allPoints.last().x() - chartTimeRange;
    if (rangeStart < 0)
        return allPoints;

    QVector<QPointF>::const_reverse_iterator it = allPoints.rend();
    while (it != allPoints.rbegin())   {
        points.push_front(*it);
        it--;
    }

    return points;
}

void Adapter::updateCharts(const int &msec, const float &encVal, const float &potVal) {
    if (!chartStartTime)
        chartStartTime = msec;
    float deltaTime = (msec - chartStartTime) / 1000.0f;
    float sec = msec / 1000.0f;
    if (deltaTime > chartTimeRange + chartAxisStart)
        chartAxisStart += chartTimeInc;

    encoderChartArray.append(QPointF(deltaTime, encVal));
    potentiometerChartArray.append(QPointF(deltaTime, potVal));

    QVector<QPointF> encoderChartPoints = getChartData(encoderChartArray);
    QVector<QPointF> potentiometerChartPoints = getChartData(potentiometerChartArray);

    if (encoderSeries)  {
        encoderSeries->replace(encoderChartPoints);
        if (deltaTime > chartTimeRange) {
            encoderSeries->attachedAxes().first()->setMax(chartAxisStart + chartTimeRange);
            encoderSeries->attachedAxes().first()->setMin(chartAxisStart);
        }
        if (encVal >= chartEncAmpl) {
            chartEncAmpl = static_cast<int>(encVal) + 2;
            encoderSeries->attachedAxes().at(1)->setMax(chartEncAmpl);
            encoderSeries->attachedAxes().at(1)->setMin(-chartEncAmpl);
        }
    }
    if (potentiometerSeries)    {
        potentiometerSeries->replace(potentiometerChartPoints);
        if (deltaTime > chartTimeRange) {
            potentiometerSeries->attachedAxes().first()->setMax(chartAxisStart + chartTimeRange);
            potentiometerSeries->attachedAxes().first()->setMin(chartAxisStart);
        }
        if (potVal >= chartPotAmpl) {
            chartPotAmpl = static_cast<int>(potVal) + 2;
            potentiometerSeries->attachedAxes().at(1)->setMax(chartPotAmpl);
            potentiometerSeries->attachedAxes().at(1)->setMin(-chartPotAmpl);
        }
    }
}

void Adapter::slotData(DataPackage const& data) {
    qDebug() << "Adapter: incoming data package";

    qint8 state = data.stateType;
    QString stateString = getStatusStr(state);
    emit signalUIStatus(stateString);
    emit signalUIUpdateData(data.m_encoderValue, data.m_steeringAngle, data.m_motorBatteryPerc, data.m_compBatteryPerc);

    QTime time = QTime::fromMSecsSinceStartOfDay(data.timeStamp);
    if (time.isValid())
        updateCharts(data.timeStamp, data.m_encoderValue, data.m_steeringAngle);
}

void Adapter::slotDone(qint8 const& COI, qint8 const& answerCode) {
    switch (answerCode) {
    case 0: {
        log("Task interrupted. Error. COI: " + QString::number(COI));
        break;
    }
    case 1: {
        log("Starting task...");
        break;
    }
    case 2: {
        log("Task done. COI: " + QString::number(COI));
        break;
    }
    }
}

void Adapter::slotSettings(SetPackage const& set)   {
    emit signalUISettings(set.p, set.i, set.d, set.servoZero);
    log("Settings uploaded.");
}
