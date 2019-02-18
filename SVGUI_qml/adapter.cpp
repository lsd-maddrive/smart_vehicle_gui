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

void Adapter::slotUISearch()    {
    emit signalSearch();
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

    emit signalUIEncoderData(data.m_encoderValue);
    emit signalUIPotentiometerData(static_cast<qint32>(data.m_steeringAngle));
    emit signalUIBatteryData(1, data.m_motorBatteryPerc);
    emit signalUIBatteryData(2, data.m_compBatteryPerc);
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
