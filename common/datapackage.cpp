#include "datapackage.h"

const char AuthPackage::authRequest[10] = {'k', 'o', 'n', 'n', 'i', 'c', 'h', 'i', 'w', 'a'};

AuthPackage::AuthPackage() {}

QByteArray AuthPackage::toBytes() const {
    QByteArray bytes;
    bytes.append(packageType);
    bytes.append(authRequest, sizeof(AuthPackage::authRequest));
    return bytes;
}

size_t AuthPackage::size() const    {
    return static_cast<size_t>(toBytes().size());
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
    return static_cast<size_t>(toBytes().size());
}

TaskPackage::TaskPackage(QByteArray &bytes) {
    QDataStream stream(&bytes, QIODevice::ReadOnly);

    stream.skipRawData(sizeof (TaskPackage::packageType));
    stream >> COI;
    stream >> taskType;
    stream >> paramBlockSize;
    for (int i = 0; i < paramBlockSize; i++)    {
        float param;
        stream >> param;
        params.push_back(param);
    }
}

TaskPackage::TaskPackage(qint8 COI, qint8 taskType, QVector<float> params) :
    COI(COI), taskType(taskType), paramBlockSize(static_cast<qint8>(params.size())), params(params)    {}

QByteArray TaskPackage::toBytes() const   {
    QByteArray bytes;
    QDataStream stream(&bytes, QIODevice::WriteOnly);

    stream << COI;
    stream << taskType;
    stream << paramBlockSize;
    for (float const& param : params)
        stream << param;

    return bytes;
}

size_t TaskPackage::size() const    {
    return static_cast<size_t>(toBytes().size());
}

SetPackage::SetPackage(QByteArray& bytes)   {
    QDataStream stream(&bytes, QIODevice::ReadOnly);

    stream.skipRawData(sizeof( SetPackage::packageType ));
    stream >> steering_p;
    stream >> steering_i;
    stream >> steering_d;
    stream >> steering_servoZero;
    stream >> forward_p;
    stream >> forward_i;
    stream >> forward_d;
    stream >> forward_int;
    stream >> backward_p;
    stream >> backward_i;
    stream >> backward_d;
    stream >> backward_int;
}

SetPackage::SetPackage() {}

QByteArray SetPackage::toBytes() const    {
    QByteArray bytes;
    QDataStream stream(&bytes, QIODevice::WriteOnly);

    stream << packageType;
    stream << steering_p;
    stream << steering_i;
    stream << steering_d;
    stream << steering_servoZero;
    stream << forward_p;
    stream << forward_i;
    stream << forward_d;
    stream << forward_int;
    stream << backward_p;
    stream << backward_i;
    stream << backward_d;
    stream << backward_int;

    return bytes;
}

size_t SetPackage::size() const {
    return static_cast<size_t>(toBytes().size());
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
    return static_cast<size_t>(toBytes().size());
}

SetRequestPackage::SetRequestPackage()  {}

QByteArray SetRequestPackage::toBytes() const   {
    QByteArray bytes;
    bytes.append(packageType);
    return bytes;
}

size_t SetRequestPackage::size() const   {
    return static_cast<size_t>(toBytes().size());
}

MapPackage::MapPackage()    {}


/*
 * cells for this constructor must contain full rectangle matrix
 */
MapPackage::MapPackage(QVector<QVector<qint8>> const& cells)    {
    _cells = cells;

    mapHeight = static_cast<qint8>(cells.size());
    if (mapHeight)  {
        mapWidth = static_cast<qint8>(cells.first().size());
    }
}

MapPackage::MapPackage(QByteArray &bytes)    {
    QDataStream stream(&bytes, QIODevice::ReadOnly);

    stream.skipRawData(sizeof(packageType));
    stream >> mapWidth;
    stream >> mapHeight;

    stream >> _cells;
}

void MapPackage::clear()    {
    mapWidth = 0;
    mapHeight = 0;
    _cells.clear();
}

int MapPackage::getWidth() const    {
    return mapWidth;
}

int MapPackage::getHeight() const   {
    return mapHeight;
}

size_t MapPackage::size() const   {
    return static_cast<size_t>(toBytes().size());
}

qint8 MapPackage::at(int i, int j) const   {
    return _cells[i][j];
}

QVector<QVector<qint8>> MapPackage::cells() const   {
    return _cells;
}

QByteArray MapPackage::toBytes() const  {
    QByteArray bytes;
    QDataStream stream(&bytes, QIODevice::WriteOnly);

    stream << packageType;
    stream << mapWidth;
    stream << mapHeight;

    stream << _cells;

    return bytes;
}

LowFreqDataPackage::LowFreqDataPackage() {
    timeStamp = static_cast<quint32>(QTime::currentTime().msecsSinceStartOfDay());
}

LowFreqDataPackage::LowFreqDataPackage(State state) {
    stateType = state;
    timeStamp = static_cast<quint32>(QTime::currentTime().msecsSinceStartOfDay());
}

LowFreqDataPackage::LowFreqDataPackage(QByteArray& bytes) {
    QDataStream stream(&bytes, QIODevice::ReadOnly);

    stream.skipRawData(sizeof(packageType));
    stream >> stateType;
    stream >> timeStamp;
    stream.skipRawData(sizeof(DataType));
    stream >> m_motorBatteryPerc;
    stream.skipRawData(sizeof(DataType));
    stream >> m_compBatteryPerc;
    stream.skipRawData(sizeof(DataType));
    stream >> m_temp;
}

QByteArray LowFreqDataPackage::toBytes() const  {
    QByteArray bytes;
    QDataStream stream(&bytes, QIODevice::WriteOnly);

    stream << packageType;
    stream << stateType;
    stream << timeStamp;
    stream << DataType::MOTOR_BATTERY;
    stream << m_motorBatteryPerc;
    stream << DataType::COMP_BATTERY;
    stream << m_compBatteryPerc;
    stream << DataType::TEMPERATURE;
    stream << m_temp;

    return bytes;
}

size_t LowFreqDataPackage::size() const {
    return static_cast<size_t>(toBytes().size());
}

HighFreqDataPackage::HighFreqDataPackage() {
    timeStamp = static_cast<quint32>(QTime::currentTime().msecsSinceStartOfDay());
}

HighFreqDataPackage::HighFreqDataPackage(QByteArray& bytes) {
    QDataStream stream(&bytes, QIODevice::ReadOnly);

    stream.skipRawData(sizeof(packageType));
    stream >> timeStamp;
    stream.skipRawData(sizeof(DataType));
    stream >> m_encoderValue;
    stream.skipRawData(sizeof(DataType));
    stream >> m_steeringAngle;
    stream.skipRawData(sizeof(DataType));
    stream >> x;
    stream.skipRawData(sizeof(DataType));
    stream >> y;
}

QByteArray HighFreqDataPackage::toBytes() const  {
    QByteArray bytes;
    QDataStream stream(&bytes, QIODevice::WriteOnly);

    stream << packageType;
    stream << timeStamp;
    stream << DataType::ENCODER;
    stream << m_encoderValue;
    stream << DataType::STEERING;
    stream << m_steeringAngle;
    stream << DataType::X;
    stream << x;
    stream << DataType::Y;
    stream << y;

    return bytes;
}

size_t HighFreqDataPackage::size() const {
    return static_cast<size_t>(toBytes().size());
}
