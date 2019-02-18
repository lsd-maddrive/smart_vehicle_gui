#include "datapackage.h"

void writeToBytes(QByteArray *bytes, qint32 const& value) {
    bytes->append(value & 0x000000FF);
    bytes->append((value & 0x0000FF00) >> 8);
    bytes->append((value & 0x00FF0000) >> 16);
    bytes->append((value & 0xFF000000) >> 24);
}

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

TaskPackage::TaskPackage(qint8 COI, qint8 taskType, QVector<qint32> params) :
    COI(COI), taskType(taskType), paramBlockSize(static_cast<qint8>(params.size())), params(params)    {}

QByteArray TaskPackage::toBytes() const   {
    QByteArray bytes;
    bytes.append(packageType);
    bytes.append(COI);
    bytes.append(taskType);
    bytes.append(paramBlockSize);
    foreach (qint32 const& param, params) {
        writeToBytes(&bytes, param);
    }
    return bytes;
}

size_t TaskPackage::size() const    {
    return static_cast<size_t>(toBytes().size());
}

SetPackage::SetPackage(qint8 COI, qint32 p, qint32 i, qint32 d, qint32 servoZero) :
    COI(COI), p(p), i(i), d(d), servoZero(servoZero) {}

QByteArray SetPackage::toBytes() const    {
    QByteArray bytes;
    bytes.append(packageType);
    bytes.append(COI);
    writeToBytes(&bytes, p);
    writeToBytes(&bytes, i);
    writeToBytes(&bytes, d);
    writeToBytes(&bytes, servoZero);
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

DataPackage::DataPackage() :
    m_encoderValue( 0 ), m_steeringAngle( 0.0f ),
    m_motorBatteryPerc( 0 ), m_compBatteryPerc( 0 )
{
    timeStamp = static_cast<quint32>(QTime::currentTime().msecsSinceStartOfDay());
    stateType = State::WAIT;
}

DataPackage::DataPackage(DataPackage::State state) :
    m_encoderValue( 0 ), m_steeringAngle( 0.0f ),
    m_motorBatteryPerc( 0 ), m_compBatteryPerc( 0 )
{
    timeStamp = static_cast<quint32>(QTime::currentTime().msecsSinceStartOfDay());
    stateType = state;
}

DataPackage::DataPackage(QByteArray &bytes)
{
    QDataStream stream(&bytes, QIODevice::ReadOnly);

    stream.skipRawData(sizeof( DataPackage::packageType ));

    stream >> stateType;
    stream >> timeStamp;

    /* Maybe exclude this field? Really we don`t need to vary data package width */
    //stream >> dataBlockSize;

    stream.skipRawData(sizeof(DataType));
    stream >> m_encoderValue;
    stream.skipRawData(sizeof(DataType));
    stream >> m_steeringAngle;
    stream.skipRawData(sizeof(DataType));
    stream >> m_motorBatteryPerc;
    stream.skipRawData(sizeof(DataType));
    stream >> m_compBatteryPerc;
}

QByteArray DataPackage::toBytes() const {

    QByteArray bytes;
    QDataStream stream(&bytes, QIODevice::WriteOnly);

    stream << packageType;
    stream << stateType;
    stream << timeStamp;

    /* Maybe exclude this field? Really we don`t need to vary data package width */
    //stream << dataBlockSize;

    stream << ENCODER;
    stream << m_encoderValue;
    stream << STEERING;
    stream << m_steeringAngle;
    stream << MOTOR_BATTERY;
    stream << m_motorBatteryPerc;
    stream << COMP_BATTERY;
    stream << m_compBatteryPerc;

    return bytes;
}

size_t DataPackage::size() const    {
    return static_cast<size_t>(toBytes().size());
}

/*
bool DataPackage::setEncoderValue(quint32 value)
{
    m_encoderValue = value;
    return true;
}

bool DataPackage::setSteeringValue(float value)
{
    m_steeringAngle = value;
    return true;
}

bool DataPackage::setMotorBatteryValue(quint32 value)
{
    m_motorBatteryPerc = value;
    return true;
}

bool DataPackage::setComputerBatteryValue(quint32 value)
{
    m_compBatteryPerc = value;
    return true;
}
*/

bool DataPackage::setState(DataPackage::State state)
{
    stateType = state;

    return true;
}
