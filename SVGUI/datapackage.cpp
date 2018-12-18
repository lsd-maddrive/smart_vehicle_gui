#include "datapackage.h"

const char AuthPackage::authRequest[10] = {'k', 'o', 'n', 'n', 'i', 'c', 'h', 'i', 'w', 'a'};

AuthPackage::AuthPackage()  {}

QByteArray AuthPackage::toBytes() const {
    QByteArray bytes;
    bytes.append(packageType);
    bytes.append(authRequest);
    return bytes;
}

size_t AuthPackage::size() const    {
    return 11;
}

AuthAnswerPackage::AuthAnswerPackage(quint8 deviceType, quint8 deviceID, quint8 stateType) :
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

TaskPackage::TaskPackage(quint8 COI, quint8 taskType, QVector<quint32> params) :
    COI(COI), taskType(taskType), paramBlockSize(static_cast<quint8>(params.size())), params(params)    {}

QByteArray TaskPackage::toBytes() const   {
    QByteArray bytes;
    bytes.append(packageType);
    bytes.append(COI);
    bytes.append(taskType);
    bytes.append(paramBlockSize);
    foreach (quint32 const& param, params) {
        bytes.append(param >> 24 & 0xFF);
        bytes.append(param >> 16 & 0xFF);
        bytes.append(param >> 8 & 0xFF);
        bytes.append(param & 0xFF);
    }
    return bytes;
}

size_t TaskPackage::size() const    {
    return static_cast<size_t>(4 + 4 * params.size());
}

SetPackage::SetPackage(quint8 COI, QVector<std::pair<quint8, quint32>> params) :
    COI(COI), paramBlockSize(static_cast<quint8>(params.size())), params(params) {}

QByteArray SetPackage::toBytes() const    {
    QByteArray bytes;
    bytes.append(packageType);
    bytes.append(COI);
    bytes.append(paramBlockSize);
    for (std::pair<quint8, quint32> const& param : params) {
        bytes.append(param.first);
        bytes.append(param.second >> 24 & 0xFF);
        bytes.append(param.second >> 16 & 0xFF);
        bytes.append(param.second >> 8 & 0xFF);
        bytes.append(param.second & 0xFF);
    }
    return bytes;
}

size_t SetPackage::size() const {
    return static_cast<size_t>(3 + 5 * params.size());
}

AnswerPackage::AnswerPackage(quint8 COI, quint8 answerType) :
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

DataPackage::DataPackage(quint8 stateType, QVector<std::pair<quint8, quint32>> data) :
    stateType(stateType), dataBlockSize(static_cast<quint8>(data.size())), data(data)   {}

QByteArray DataPackage::toBytes() const   {
    QByteArray bytes;
    bytes.append(packageType);
    bytes.append(stateType);
    int msec = QTime::currentTime().msec();
    bytes.append(msec >> 24 & 0xFF);
    bytes.append(msec >> 16 & 0xFF);
    bytes.append(msec >> 8 & 0xFF);
    bytes.append(msec & 0xFF);
    bytes.append(dataBlockSize);
    for (std::pair<quint8, quint32> const& value : data) {
        bytes.append(value.first);
        bytes.append(value.second >> 24 & 0xFF);
        bytes.append(value.second >> 16 & 0xFF);
        bytes.append(value.second >> 8 & 0xFF);
        bytes.append(value.second & 0xFF);
    }
    return bytes;
}

size_t DataPackage::size() const    {
    return static_cast<size_t>(7 + 5 * data.size());
}
