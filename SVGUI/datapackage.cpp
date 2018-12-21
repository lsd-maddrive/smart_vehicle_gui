#include "datapackage.h"

const char AuthPackage::authRequest[10] = {'k', 'o', 'n', 'n', 'i', 'c', 'h', 'i', 'w', 'a'};

AuthPackage::AuthPackage() {}

QByteArray AuthPackage::toBytes() const {
    QByteArray bytes;
    bytes.append(packageType);
    bytes.append(authRequest);
    return bytes;
}

size_t AuthPackage::size() const    {
    return 11;
}

AuthAnswerPackage::AuthAnswerPackage(qint8 deviceType, qint8 deviceID, qint8 stateType) :
    deviceType(deviceType), deviceID(deviceID), stateType(stateType)   {}

QByteArray AuthAnswerPackage::toBytes() const   {
    QByteArray bytes;
    bytes.append(packageType);
    bytes.append(deviceType);
    bytes.append(deviceID);
    bytes.append(stateType);
    return bytes;
}

size_t AuthAnswerPackage::size() const  {
    return 4;
}

TaskPackage::TaskPackage(qint8 COI, qint8 taskType, QVector<qint32> params) :
    COI(COI), taskType(taskType), paramBlockSize(static_cast<qint8>(params.size())), params(params)    {}

QByteArray TaskPackage::toBytes() const   {
    QByteArray bytes;
    bytes.append(packageType);
    bytes.append(COI);
    bytes.append(taskType);
    bytes.append(paramBlockSize);
    foreach (qint32 const& param, params) {
        bytes.append(param & 0x000000FF);
        bytes.append(param & 0x0000FF00 >> 8);
        bytes.append(param & 0x00FF0000 >> 16);
        bytes.append(param & 0xFF000000 >> 24);
    }
    return bytes;
}

size_t TaskPackage::size() const    {
    return static_cast<size_t>(4 + 4 * params.size());
}

SetPackage::SetPackage(qint8 COI, QVector<std::pair<qint8, qint32>> params) :
    COI(COI), paramBlockSize(static_cast<qint8>(params.size())), params(params) {}

QByteArray SetPackage::toBytes() const    {
    QByteArray bytes;
    bytes.append(packageType);
    bytes.append(COI);
    bytes.append(paramBlockSize);
    for (std::pair<qint8, qint32> const& param : params) {
        bytes.append(param.first);
        bytes.append(param.second & 0x000000FF);
        bytes.append(param.second & 0x0000FF00 >> 8);
        bytes.append(param.second & 0x00FF0000 >> 16);
        bytes.append(param.second & 0xFF000000 >> 24);
    }
    return bytes;
}

size_t SetPackage::size() const {
    return static_cast<size_t>(3 + 5 * params.size());
}

AnswerPackage::AnswerPackage(qint8 COI, qint8 answerType) :
    COI(COI), answerType(answerType) {}

QByteArray AnswerPackage::toBytes() const {
    QByteArray bytes;
    bytes.append(packageType);
    bytes.append(COI);
    bytes.append(answerType);
    return bytes;
}

size_t AnswerPackage::size() const  {
    return 3;
}

DataPackage::DataPackage(qint8 stateType, QVector<std::pair<qint8, qint32>> data) :
    stateType(stateType), dataBlockSize(static_cast<qint8>(data.size())), data(data)   {}

QByteArray DataPackage::toBytes() const   {
    QByteArray bytes;

    bytes.append(packageType);
    bytes.append(stateType);
    int msec = QTime::currentTime().msecsSinceStartOfDay();
    bytes.append(msec & 0x000000ff);
    bytes.append(msec & 0x0000ff00 >> 8);
    bytes.append(msec & 0x00ff0000 >> 16);
    bytes.append(msec & 0xff000000 >> 24);
    bytes.append(dataBlockSize);
    for (std::pair<qint8, qint32> const& value : data) {
        bytes.append(value.first);
        bytes.append(value.second & 0x000000FF);
        bytes.append(value.second & 0x0000FF00 >> 8);
        bytes.append(value.second & 0x00FF0000 >> 16);
        bytes.append(value.second & 0xFF000000 >> 24);
    }
    return bytes;
}

size_t DataPackage::size() const    {
    return static_cast<size_t>(7 + 5 * data.size());
}
