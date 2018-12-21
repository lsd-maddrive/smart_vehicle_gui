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

//todo
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
    qint8 COI;
    qint8 paramBlockSize;
    QVector<std::pair<qint8, qint32>> params;

    explicit SetPackage(qint8 COI = 0, QVector<std::pair<qint8, qint32>> params = QVector<std::pair<qint8, qint32>>());
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
    qint8 dataBlockSize;
    QVector<std::pair<qint8, qint32>> data;

    explicit DataPackage(qint8 stateType = 0, QVector<std::pair<qint8, qint32>> data = QVector<std::pair<qint8, qint32>>());
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
 *      1 - speed(4)
 *      2 - angle(4)
 *      3 - battery(1)
 *
 */

#endif // DATAPACKAGE_H
