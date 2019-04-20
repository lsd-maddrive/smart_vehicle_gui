#include "datapackage.h"

/* Check this! You use many functions for strings, but put array of chars without terminator ymbol \0 */
/* Better use casual string or change to QString with fixed size */
//const char AuthPackage::authRequest[10] = {'k', 'o', 'n', 'n', 'i', 'c', 'h', 'i', 'w', 'a'};
const char AuthPackage::authRequest[] = "konnichiwa";

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

AnswerPackage::AnswerPackage(qint8 answerType) : answerType(answerType) {}

AnswerPackage::AnswerPackage(QByteArray &bytes) {
    QDataStream stream(&bytes, QIODevice::ReadOnly);

    stream.skipRawData(sizeof( AnswerPackage::packageType ));
    stream >> answerType;
}

QByteArray AnswerPackage::toBytes() const {
    QByteArray bytes;
    bytes.append(packageType);    
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

LowFreqDataPackage::LowFreqDataPackage() :
    LowFreqDataPackage( State::WAIT ) /* Delegated to LowFreqDataPackage(State state) */
{

}

LowFreqDataPackage::LowFreqDataPackage(State state) :
    m_motorBatteryPerc( 0 ), m_compBatteryPerc( 0 ), m_temp( 0 )
{
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

HighFreqDataPackage::HighFreqDataPackage() :
    m_encoderValue( 0 ), m_steeringAngle( 0 ), x( 0 ), y( 0 ), angle( 0 )
{
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
    stream.skipRawData(sizeof(DataType));
    stream >> angle;
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
    stream << DataType::ANGLE;
    stream << angle;

    return bytes;
}

size_t HighFreqDataPackage::size() const {
    return static_cast<size_t>(toBytes().size());
}

ControlPackage::ControlPackage()    {

}

ControlPackage::ControlPackage(QByteArray &bytes)   {
    QDataStream stream(&bytes, QIODevice::ReadOnly);

    stream.skipRawData(sizeof(packageType));

    stream.skipRawData(sizeof(DataType));
    stream >> xAxis;
    stream.skipRawData(sizeof(DataType));
    stream >> yAxis;
}

QByteArray ControlPackage::toBytes() const  {
    QByteArray bytes;
    QDataStream stream(&bytes, QIODevice::WriteOnly);

    stream << packageType;
    stream << DataType::XAXIS;
    stream << xAxis;
    stream << DataType::YAXIS;
    stream << yAxis;

    return bytes;
}

size_t ControlPackage::size()   const   {
    return toBytes().size();
}
