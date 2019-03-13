#ifndef ADAPTER_H
#define ADAPTER_H

#include <QObject>
#include <QDebug>
#include <QLineSeries>
#include <QList>
#include <QPointF>
#include <QChartView>
#include <QXYSeries>
#include <QLineSeries>
#include <QAbstractSeries>
#include <QtMath>
#include "datapackage.h"

class Adapter : public QObject
{
    Q_OBJECT
private:
    static QString getStatusStr(qint8 const& status);
    qint8 COI = 1;

    static const int chartTimeRange = 60;
    static const int chartTimeInc = 10;
    static const int chartStartAmp = 10;
    int chartEncAmpl = chartStartAmp;
    int chartPotAmpl = chartStartAmp;
    int chartAxisStart = 0;
    int chartStartTime = 0; //msec
    QVector<QPointF> encoderChartArray;
    QVector<QPointF> potentiometerChartArray;
    QVector<QPointF> getChartData(QVector<QPointF> const& list);

    QtCharts::QLineSeries *encoderSeries;
    QtCharts::QLineSeries* potentiometerSeries;
    void updateCharts(int const& msec, float const& encVal, float const& potVal);
    void clearCharts();
    float getSpeed(float currentTime, float currentEncoder) const;

public:
    explicit Adapter(QObject *parent = nullptr);
    void log(QString const& message);
    void data(DataPackage const& data);

signals:
    void signalCommand(TaskPackage const& task);

    void signalSearch();
    void signalConnect(QString const& address, quint16 const& port);
    void signalDisconnect();
    void signalSettingsLoad(SetPackage const& set);
    void signalSettingsUpload();

    void signalUILog(QString const& message);
    void signalUIAddresses(QList<QString> const& addresses);
    void signalUIConnected();
    void signalUIDisconnected();
    void signalUIConnectionError();
    void signalUIStatus(QString const& str);
    void signalUIUpdateData(float const& encValue, float const& potValue, float const& speedValue, quint32 const& firstBatteryValue, quint32 const& secondBatteryValue);
    void signalUISettings(float steering_p, float steering_i, float steering_d, float steering_zero,
                          float forward_p, float forward_i, float forward_d, float forward_int,
                          float backward_p, float backward_i, float backward_d, float backward_int);
    void signalUISetSerieses();
    void signalUIMap(int w, int h, QList<int> const& cellList);

public slots:
    void slotTest();
    void slotUISetSerieses(QObject *encoderSeries, QObject *potentiometerSeries);
    void slotUISearch();
    void slotUIConnect(QString address, QString port = "5556");
    void slotUIDisconnect();
    void slotUISettingsLoad(float steering_p, float steering_i, float steering_d, float steering_zero,
                            float forward_p, float forward_i, float forward_d, float forward_int,
                            float backward_p, float backward_i, float backward_d, float backward_int);
    void slotUISettingsUpload();
    void slotUICommandForward(float const& distantion);
    void slotUICommandWheels(float const& degrees);
    void slotUICommandFlick();
    void slotUIClearCharts();

    void slotAddresses(QList<QString> const& addresses);
    void slotConnected(qint8 const& state);
    void slotDisconnected();
    void slotConnectionError(QString message);
    void slotData(DataPackage const& data);
    void slotDone(qint8 const& COI, qint8 const& answerCode);
    void slotSettings(SetPackage const& set);
    void slotMap(MapPackage const& map);
    void slotBrokenPackage();
};

#endif // ADAPTER_H
