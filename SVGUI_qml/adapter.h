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
    void signalUIPotentiometerData(qint32 const& potValue);
    void signalUIEncoderData(qint32 const& encValue);
    void signalUIBatteryData(quint32 const& number, quint32 const& value);
    void signalUISettings(float p, float i, float d, float zero);

public slots:
    void slotTest();
    void slotUISearch();
    void slotUIConnect(QString address, QString port = "5556");
    void slotUIDisconnect();
    void slotUISettingsLoad(float p, float i, float d, float zero);
    void slotUISettingsUpload();
    void slotUICommandForward(float const& distantion);
    void slotUICommandWheels(float const& degrees);
    void slotUICommandFlick();

    void slotAddresses(QList<QString> const& addresses);
    void slotConnected(qint8 const& state);
    void slotDisconnected();
    void slotConnectionError(QString message);
    void slotData(DataPackage const& data);
    void slotDone(qint8 const& COI, qint8 const& answerCode);
    void slotSettings(SetPackage const& set);
};

#endif // ADAPTER_H
