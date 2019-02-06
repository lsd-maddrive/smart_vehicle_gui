#ifndef ADAPTER_H
#define ADAPTER_H

#include <QObject>
#include <QDebug>
#include "datapackage.h"

class Adapter : public QObject
{
    Q_OBJECT
private:
    QObject *root;
    static QString getStatusStr(qint8 const& status);
    qint8 COI = 1;
public:
    explicit Adapter(QObject *root, QObject *parent = nullptr);
    void log(QString const& message);
    void data(DataPackage const& data);
signals:
    void signalCommand(TaskPackage const& task);

    void signalConnect(QString const& address, quint16 const& port);
    void signalDisconnect();

    void signalUILog(QString const& message);
    void signalUIConnected();
    void signalUIDisconnected();
    void signalUIConnectionError();
    void signalUIStatus(QString const& str);
    void signalUIPotentiometerData(qint32 const& potValue);
    void signalUIEncoderData(qint32 const& encValue);
    void signalUIBatteryData(qint32 const& number, qint32 const& value);

public slots:
    void slotTest();
    void slotUIConnect(QString address, QString port);
    void slotUIDisconnect();
    void slotUICommandForward(float const& distantion);
    void slotUICommandWheels(float const& degrees);
    void slotUICommandFlick();

    void slotConnected(qint8 const& state);
    void slotDisconnected();
    void slotConnectionError(QString message);
    void slotData(DataPackage const& data);
    void slotDone(qint8 const& COI, qint8 const& answerCode);
};

#endif // ADAPTER_H
