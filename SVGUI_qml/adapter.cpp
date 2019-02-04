#include "adapter.h"

Adapter::Adapter(QObject* root, QObject *parent) : QObject(parent) {
    this->root = root;
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

void Adapter::slotTest()    {
    qDebug() << "Test slot was called.";
}

void Adapter::log(const QString &message)   {
    emit signalUILog(message);
}

void Adapter::slotUIConnect(QString address, QString portStr)    {
    qDebug() << "Adapter: incoming connect signal";
    log("Connecting to " + address + "...");
    quint16 port = portStr.toInt();
    emit signalConnect(address, port);
}

void Adapter::slotUIDisconnect()    {
    emit signalDisconnect();
}

void Adapter::slotConnected(qint8 const& state)   {
    qDebug() << "Adapter: Connected";
    emit signalUIConnected();
    emit signalUIStatus(getStatusStr(state));
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

void Adapter::slotData(DataPackage const& data) {
    qDebug() << "Adapter: incoming data package";
    log("Incoming data package.");
    qint8 state = data.stateType;
    QString stateString = getStatusStr(state);
    emit signalUIStatus(stateString);
    qint8 dataBlockSize = data.dataBlockSize;
    for (std::pair<qint8, qint32> const& data : data.data)  {
        switch (data.first) {
        case 0: {
            break;
        }
        case 1: {
            emit signalUIEncoderData(data.second);
            log("Encoder: " + QString::number(data.second));
            break;
        }
        case 2: {
            emit signalUIPotentiometerData(data.second);
            log("Potentiometer: " + QString::number(data.second));
            break;
        }
        case 3: {
            break;
        }
        }
    }
}
