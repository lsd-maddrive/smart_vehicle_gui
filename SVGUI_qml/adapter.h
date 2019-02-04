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
public:
    explicit Adapter(QObject *root, QObject *parent = nullptr);
    void log(QString const& message);
    void data(DataPackage const& data);
signals:
    //void signalCommandForward();
    //void signalCommandWheels(float degrees);

    void signalConnect(QString const& address, quint16 const& port);
    void signalDisconnect();

    void signalUILog(QString const& message);
    void signalUIConnected();
    void signalUIDisconnected();
    void signalUIConnectionError();
    void signalUIStatus(QString const& str);
    void signalUIPotentiometerData(qint32 const& potValue);
    void signalUIEncoderData(qint32 const& encValue);

public slots:
    void slotTest();
    void slotUIConnect(QString address, QString port);
    void slotUIDisconnect();

    void slotConnected(qint8 const& state);
    void slotDisconnected();
    void slotConnectionError(QString message);
    void slotData(DataPackage const& data);

    //void slotCommandForward();
    //void slotCommandWheels(float const& degrees);
};

#endif // ADAPTER_H
