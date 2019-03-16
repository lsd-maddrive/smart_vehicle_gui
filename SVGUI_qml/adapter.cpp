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

    if (speedSeries)
        speedSeries->clear();
    if (steeringSeries)
        steeringSeries->clear();

    speedChartArray.clear();
    steeringChartArray.clear();

    chartAxisStart = 0;
    chartStartTime = 0;
    chartSpeedAmpl = chartStartSpeedAmp;
    chartSteeringAmpl = chartStartSteeringAmp;

    speedSeries->attachedAxes().at(1)->setMax(chartSpeedAmpl);
    speedSeries->attachedAxes().at(1)->setMin(-chartSpeedAmpl);
    steeringSeries->attachedAxes().at(1)->setMax(chartSpeedAmpl);
    steeringSeries->attachedAxes().at(1)->setMin(-chartSpeedAmpl);

    speedSeries->attachedAxes().at(0)->setMax(chartTimeRange);
    speedSeries->attachedAxes().at(0)->setMin(0);
    steeringSeries->attachedAxes().at(0)->setMax(chartTimeRange);
    steeringSeries->attachedAxes().at(0)->setMin(0);
}


void Adapter::log(const QString &message)   {
    emit signalUILog(message);
}

void Adapter::slotUISetSerieses(QObject *speedSeries, QObject *steeringSeries)   {
    if (speedSeries && steeringSeries)  {
        this->speedSeries = qobject_cast<QtCharts::QLineSeries*>(speedSeries);
        this->steeringSeries = qobject_cast<QtCharts::QLineSeries*>(steeringSeries);
        qDebug() << "Chart serieses initialized";
    }   else {
        qDebug() << "Chart initializing error. Nullptr detected";
    }
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

void Adapter::slotUISettingsLoad(float steering_p, float steering_i, float steering_d, float steering_zero,
                                 float forward_p, float forward_i, float forward_d, float forward_int,
                                 float backward_p, float backward_i, float backward_d, float backward_int)  {
    log("Loading settings...");
    SetPackage set;

    set.steering_p = steering_p;
    set.steering_i = steering_i;
    set.steering_d = steering_d;
    set.steering_servoZero = steering_zero;

    set.forward_p = forward_p;
    set.forward_i = forward_i;
    set.forward_d = forward_d;
    set.forward_int = forward_int;

    set.backward_p = backward_p;
    set.backward_i = backward_i;
    set.backward_d = backward_d;
    set.backward_int = backward_int;


    emit signalSettingsLoad(set);
}

void Adapter::slotUISettingsUpload()    {
    log("Uploading settings...");
    emit signalSettingsUpload();
}

void Adapter::slotUICommandForward(float const& distantion) {
    TaskPackage task(COI, 1, {distantion});
    log("Command move forward for distantion: " + QString::number(distantion) + ", COI: " + QString::number(COI));
    COI++;
    if (COI >= 127)
        COI = 1;
    emit signalCommand(task);
}

void Adapter::slotUICommandWheels(float const& angle) {
    TaskPackage task(COI, 2, {angle});
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

void Adapter::slotUIClearCharts()   {
    clearCharts();
}

void Adapter::slotUIControl(float const& xAxis, float const& yAxis) {
    ControlPackage data;
    data.xAxis = xAxis;
    data.yAxis = yAxis;
    emit signalControl(data);
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

void Adapter::updateCharts(const quint32 &msec, const float &encoder, const float &speed, const float &steering) {
    if (!chartStartTime)
        chartStartTime = msec;
    float deltaTime = (msec - chartStartTime) / 1000.0f;
    if (deltaTime > chartTimeRange + chartAxisStart)
        chartAxisStart += chartTimeInc;

    encoderArray.append(QPointF(deltaTime, encoder));
    speedChartArray.append(QPointF(deltaTime, speed));
    steeringChartArray.append(QPointF(deltaTime, steering));

    if (speedSeries)  {
        speedSeries->replace(speedChartArray);
        if (deltaTime > chartTimeRange) {
            speedSeries->attachedAxes().first()->setMax(chartAxisStart + chartTimeRange);
            speedSeries->attachedAxes().first()->setMin(chartAxisStart);
        }
        if (abs(speed)>= chartSpeedAmpl) {
            chartSpeedAmpl = static_cast<int>(abs(speed)) + 2;
            speedSeries->attachedAxes().at(1)->setMax(chartSpeedAmpl);
            speedSeries->attachedAxes().at(1)->setMin(-chartSpeedAmpl);
        }
    }
    if (steeringSeries)    {
        steeringSeries->replace(steeringChartArray);
        if (deltaTime > chartTimeRange) {
            steeringSeries->attachedAxes().first()->setMax(chartAxisStart + chartTimeRange);
            steeringSeries->attachedAxes().first()->setMin(chartAxisStart);
        }
        if (abs(steering) >= chartSteeringAmpl) {
            chartSteeringAmpl = static_cast<int>(abs(steering)) + 2;
            steeringSeries->attachedAxes().at(1)->setMax(chartSteeringAmpl);
            steeringSeries->attachedAxes().at(1)->setMin(-chartSteeringAmpl);
        }
    }
}

float Adapter::getSpeed(quint32 msec, float currentEncoder) const {
    if (encoderArray.empty())   {
        return 0;
    }
    float deltaTime = (msec - chartStartTime) / 1000.0f;
    QPointF encoderPrev = encoderArray.last();
    float speed = (currentEncoder - encoderPrev.y()) / (deltaTime - encoderPrev.x());
    return speed;
}

void Adapter::slotData(HighFreqDataPackage const& data) {
    qDebug() << "Adapter: incoming high freq data package";

    float speed = getSpeed(data.timeStamp, data.m_encoderValue);

    emit signalUIUpdateHighFreqData(data.m_encoderValue, data.m_steeringAngle, speed);
    emit signalUIUpdatePosition(data.x, data.y, data.angle);

    QTime time = QTime::fromMSecsSinceStartOfDay(static_cast<int>(data.timeStamp));
    if (time.isValid())
        updateCharts(data.timeStamp, data.m_encoderValue, speed, data.m_steeringAngle);
}

void Adapter::slotData(LowFreqDataPackage const& data) {
    qDebug() << "Adapter: incoming low freq data package";

    qint8 state = data.stateType;
    QString stateString = getStatusStr(state);

    emit signalUIStatus(stateString);
    emit signalUIUpdateLowFreqData(data.m_motorBatteryPerc, data.m_compBatteryPerc, data.m_temp);
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
    emit signalUISettings(set.steering_p, set.steering_i, set.steering_d, set.steering_servoZero,
                          set.forward_p, set.forward_i, set.forward_d, set.forward_int,
                          set.backward_p, set.backward_i, set.backward_d, set.backward_int);
    log("Settings uploaded.");
}

void Adapter::slotMap(MapPackage const& map)    {
    QList<int> cellsList;
    for (auto const& line : map.cells())
        for (auto const& cell : line)
            cellsList.push_back(cell);

    emit signalUIMap(map.getWidth(), map.getHeight(), cellsList);
}

void Adapter::slotBrokenPackage()   {
    log("Incoming broken package.");
}
