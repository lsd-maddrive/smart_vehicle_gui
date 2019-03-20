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
    static const char authRequest[];

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
    QVector<float> params;

    explicit TaskPackage(QByteArray &bytes);
    explicit TaskPackage(qint8 COI = 0, qint8 taskType = 0, QVector<float> params = QVector<float>());
    QByteArray toBytes() const;
    size_t size() const;
};

struct SetPackage : public Package
{
    static const qint8 packageType = 4;
    float steering_p = 0;
    float steering_i = 0;
    float steering_d = 0;
    float steering_servoZero = 0;
    float forward_p = 0;
    float forward_i = 0;
    float forward_d = 0;
    float forward_int = 0;
    float backward_p = 0;
    float backward_i = 0;
    float backward_d = 0;
    float backward_int = 0;

    explicit SetPackage(QByteArray& bytes);
    explicit SetPackage();
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

struct SetRequestPackage : public Package   {
    static const qint8 packageType = 6;
    explicit SetRequestPackage();
    QByteArray toBytes() const;
    size_t size() const;
};

struct MapPackage : public Package  {
    static const qint8 packageType = 7;

    enum Cells {
        EMPTY = 0,
        WALL = 1
    };

    explicit MapPackage();
    explicit MapPackage(QVector<QVector<qint8>> const& cells);
    explicit MapPackage(QByteArray &bytes);

    QByteArray toBytes() const;
    size_t size() const;
    int getWidth() const;
    int getHeight() const;
    qint8 at(int i, int j) const;
    QVector<QVector<qint8>> cells() const;

private:
    qint8 mapWidth = 0;
    qint8 mapHeight = 0;
    QVector<QVector<qint8>> _cells;
    void clear();
};

struct LowFreqDataPackage : Package {
    static const qint8 packageType = 8;
    qint8 stateType;
    quint32 timeStamp;
    quint32 m_motorBatteryPerc;
    quint32 m_compBatteryPerc;
    float m_temp;

    enum State {
        FAULT = 0,
        RUN = 1,
        STOP = 2,
        WAIT = 3
    };

    enum DataType {
        MOTOR_BATTERY = 1,
        COMP_BATTERY = 2,
        TEMPERATURE = 3
    };

    explicit LowFreqDataPackage();
    explicit LowFreqDataPackage(State state);
    explicit LowFreqDataPackage(QByteArray &bytes);
    QByteArray toBytes() const;
    size_t size() const;

};

struct HighFreqDataPackage : Package   {
    static const qint8 packageType = 9;
    quint32 timeStamp;
    float m_encoderValue;
    float m_steeringAngle;
    float x;
    float y;
    float angle;

    enum DataType {
        ENCODER = 1,
        STEERING = 2,
        X = 3,
        Y = 4,
        ANGLE = 5
    };

    explicit HighFreqDataPackage();
    explicit HighFreqDataPackage(QByteArray &bytes);
    QByteArray toBytes() const;
    size_t size() const;
};

struct ControlPackage : Package {
    static const qint8 packageType = 10;
    float xAxis;
    float yAxis;

    enum DataType   {
        XAXIS = 1,
        YAXIS = 2
    };

    explicit ControlPackage();
    explicit ControlPackage(QByteArray &bytes);
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
 *      1 - encoder(4)
 *      2 - potentiometer(4)
 *      3 - battery_1(1)
 *      4 - battery_2(1)
 *
 */

Q_DECLARE_METATYPE(HighFreqDataPackage);
Q_DECLARE_METATYPE(LowFreqDataPackage);
Q_DECLARE_METATYPE(ControlPackage);
Q_DECLARE_METATYPE(MapPackage);

#endif // DATAPACKAGE_H
