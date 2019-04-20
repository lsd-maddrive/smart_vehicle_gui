#ifndef ADAPTER_H
#define ADAPTER_H

#include <QObject>
#include <QDebug>
#include <QList>
#include <QPointF>
#include "datapackage.h"
#include "svseries.h"

class Adapter : public QObject
{
    Q_OBJECT
private:
    QString getStatusStr(qint8 const& status);

    int chartStartTime = 0;
    QPointF encoderLast;
    SVSeries speedSeries;
    SVSeries speedSeriesFilter;
    SVSeries steeringSeries;
    SVSeries tempSeries;
    SVSeries tempSeriesFilter;

    void clearCharts();
    float getSpeed(float currentTime, float currentEncoder);

public:
    explicit Adapter(QObject *parent = nullptr);
    void log(QString const& message);

signals:
    void signalSearch();
    void signalConnect(QString const& address, quint16 const& port);
    void signalDisconnect();
    void signalSettingsLoad(SetPackage const& set);
    void signalSettingsUpload();
    void signalControl(ControlPackage const& data);

    void signalUILog(QString const& message);
    void signalUIAddresses(QList<QString> const& addresses);
    void signalUIConnected();
    void signalUIDisconnected();
    void signalUIConnectionError();
    void signalUIStatus(QString const& str);
    void signalUIUpdatePosition(float const& x, float const& y, float const& angle);
    void signalUIUpdateHighFreqData(float const& encValue, float const& potValue, float const& speedValue);
    void signalUIUpdateLowFreqData(quint32 const& firstBatteryValue, quint32 const& secondBatteryValue, float const& temp);
    void signalUISettings(float steering_p, float steering_i, float steering_d, float steering_zero,
                          float forward_p, float forward_i, float forward_d, float forward_int,
                          float backward_p, float backward_i, float backward_d, float backward_int);
    void signalUIMap(int w, int h, QList<int> const& cellList);

public slots:
    void slotUISetSerieses(QObject *speedSeries, QObject* speedSeiresFilter,
                           QObject *potentiometerSeries, QObject *tempSeries, QObject *tempSeriesFilter);
    void slotUISearch();
    void slotUIConnect(QString address, QString port = "5556");
    void slotUIDisconnect();
    void slotUISettingsLoad(float steering_p, float steering_i, float steering_d, float steering_zero,
                            float forward_p, float forward_i, float forward_d, float forward_int,
                            float backward_p, float backward_i, float backward_d, float backward_int);
    void slotUISettingsUpload();
    void slotUIClearCharts();
    void slotUIControl(float const& xAxis, float const& yAxis);
    void slotUISetFilter(int filterType);
    void slotUISetFilterK(float k);

    void slotAddresses(QList<QString> const& addresses);
    void slotConnected(qint8 const& state);
    void slotDisconnected();
    void slotConnectionError(QString message);
    void slotData(LowFreqDataPackage const& data);
    void slotData(HighFreqDataPackage const& data);
    void slotDone(qint8 const& answerCode);
    void slotSettings(SetPackage const& set);
    void slotMap(MapPackage const& map);
    void slotBrokenPackage();
};

#endif // ADAPTER_H
