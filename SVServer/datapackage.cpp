#include "datapackage.h"

AuthAnswerPackage::AuthAnswerPackage(quint8 deviceType, quint8 deviceID, quint8 stateType) :
    deviceType(deviceType), deviceID(deviceID), stateType(stateType)   {}

QString AuthAnswerPackage::toString() const {
    QString str;
    str.append(deviceType);
    str.append(deviceID);
    str.append(stateType);
    return str;
}

size_t AuthAnswerPackage::size() const  {
    return 4;
}

TaskPackage::TaskPackage(quint8 COI, quint8 taskType, QVector<quint32> params) :
    COI(COI), taskType(taskType), paramBlockSize(static_cast<quint8>(params.size())), params(params)    {}

QString TaskPackage::toString() const   {
    QString str;
    str.append(packageType);
    str.append(COI);
    str.append(taskType);
    str.append(paramBlockSize);
    foreach (quint32 const& param, params) {
        str.append(param);
    }
    return str;
}

size_t TaskPackage::size() const    {
    return static_cast<size_t>(4 + 4 * params.size());
}

SetPackage::SetPackage(quint8 COI, QVector<std::pair<quint8, quint32>> params) : COI(COI), paramBlockSize(static_cast<quint8>(params.size())), params(params) {}

QString SetPackage::toString() const    {
    QString str;
    str.append(packageType);
    str.append(COI);
    str.append(paramBlockSize);
    for (std::pair<quint8, quint32> const& param : params) {
        str.append(param.first);
        str.append(param.second);
    }
    return str;
}

size_t SetPackage::size() const {
    return static_cast<size_t>(3 + 5 * params.size());
}

AnswerPackage::AnswerPackage(quint8 COI, quint8 answerType) :
    COI(COI), answerType(answerType) {}

QString AnswerPackage::toString() const {
    QString str;
    str.append(packageType);
    str.append(COI);
    str.append(answerType);
    return str;
}

size_t AnswerPackage::size() const  {
    return 3;
}

DataPackage::DataPackage(quint8 stateType, QVector<std::pair<quint8, quint32>> data) :
    stateType(stateType), dataBlockSize(static_cast<quint8>(data.size())), data(data)   {}

QString DataPackage::toString() const   {
    QString str;
    str.append(packageType);
    str.append(stateType);
    str.append(static_cast<quint32>(QTime::currentTime().second()));
    str.append(dataBlockSize);
    for (std::pair<quint8, quint32> const& value : data) {
        str.append(value.first);
        str.append(value.second);
    }
    return str;
}

size_t DataPackage::size() const    {
    return static_cast<size_t>(7 + 5 * data.size());
}
