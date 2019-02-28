#ifndef DATAPACKAGE_H
#define DATAPACKAGE_H

#include <QString>
#include <QVector>
#include <QTime>
#include <QDebug>
#include <QDataStream>

struct Package
{
    virtual QByteArray toBytes() const = 0;
    virtual size_t size() const = 0;
    virtual ~Package() {}
};

struct AuthPackage : public Package
{
    static const qint8 packageType = 1;
    static const char authRequest[10];

    explicit AuthPackage();
    QByteArray toBytes() const;
    size_t size() const;
};

struct AuthAnswerPackage : public Package
{
    static const qint8 packageType = 2;
    qint8 deviceType;
    qint8 deviceID;
    qint8 stateType;

    explicit AuthAnswerPackage(qint8 deviceType = 0, qint8 deviceID = 0, qint8 stateType = 0);
    QByteArray toBytes() const;
    size_t size() const;
};

struct TaskPackage : public Package
{
    static const qint8 packageType = 3;
    qint8 COI;
    qint8 taskType;
    qint8 paramBlockSize;
    QVector<qint32> params;

    explicit TaskPackage(qint8 COI = 0, qint8 taskType = 0, QVector<qint32> params = QVector<qint32>());
    QByteArray toBytes() const;
    size_t size() const;
};

struct SetPackage : public Package
{
    static const qint8 packageType = 4;
    float p;
    float i;
    float d;
    float servoZero;

    explicit SetPackage(QByteArray& bytes);
    explicit SetPackage(float p = 0, float i = 0, float d = 0, float servoZero = 0);
    QByteArray toBytes() const;
    size_t size() const;
};

struct AnswerPackage : public Package
{
    static const qint8 packageType = 5;
    qint8 COI;
    qint8 answerType;

    explicit AnswerPackage(qint8 COI = 0, qint8 answerType = 0);
    QByteArray toBytes() const;
    size_t size() const;
};

struct DataPackage : public Package
{
    static const qint8 packageType = 6;
    qint8 stateType;
    //qint8 dataBlockSize;
    quint32 timeStamp;

    enum State {
        FAULT = 0,
        RUN = 1,
        STOP = 2,
        WAIT = 3
    };

    enum DataType {
        ENCODER = 1,
        STEERING = 2,
        MOTOR_BATTERY = 3,
        COMP_BATTERY = 4
    };

    explicit DataPackage();
    explicit DataPackage(State state);
    explicit DataPackage(QByteArray &bytes);
    QByteArray toBytes() const;
    size_t size() const;

public:
    /* As you asked, removed Getters/Setters */
//    bool setEncoderValue(quint32 value);
//    bool setSteeringValue(float value);
//    bool setMotorBatteryValue(quint32 value);
//    bool setComputerBatteryValue(quint32 value);
    /* Required for internal conversion from State to qint8 */
    bool setState(State state);

//private:
    /* Should be private, but now is opened for Adapter class */
    float  m_encoderValue;
    float   m_steeringAngle;
    quint32 m_motorBatteryPerc;
    quint32 m_compBatteryPerc;
};

/* Declaration for external slot */
Q_DECLARE_METATYPE(DataPackage);

struct SetRequestPackage : public Package   {
    static const qint8 packageType = 7;
    explicit SetRequestPackage();
    QByteArray toBytes() const;
    size_t size() const;
};

/*
 *  packageType:
 *      0 - Empty
 *      1 - Auth
 *      2 - AuthAnswer
 *      3 - Task
 *      4 - Set
 *      5 - Answer
 *      6 - Data
 *
 *  stateType:
 *      0 - FAULT
 *      1 - RUN
 *      2 - STOP
 *      3 - WAIT
 *
 *  TaskType:
 *      0 - checkConnection
 *      1 - goForward
 *      2 - rotateWheels
 *      3 - getSettings
 *
 *  AnswerType:
 *      0 - Error
 *      1 - StartingTask
 *      2 - FinishTask
 *
 *  SetType:
 *      0 - p
 *      1 - i
 *      2 - d
 *      3 - servoZero
 *
 *  DataType:
 *      0 - odometric(4)
 *      1 - encoder(4)
 *      2 - potentiometer(4)
 *      3 - battery_1(1)
 *      4 - battery_2(1)
 *
 */

#endif // DATAPACKAGE_H
