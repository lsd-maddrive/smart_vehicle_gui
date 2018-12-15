#ifndef DATAPACKAGE_H
#define DATAPACKAGE_H

#include <QString>
#include <QVector>
#include <QTime>
#include <QDebug>

struct Package
{
    virtual QString toString() const;
    virtual size_t size() const;
    virtual ~Package();
};

struct AuthAnswerPackage : public Package
{
    static const quint8 packageType = 2;
    quint8 deviceType;
    quint8 deviceID;
    quint8 stateType;

    explicit AuthAnswerPackage(quint8 deviceType = 0, quint8 deviceID = 0, quint8 stateType = 0);
    QString toString() const;
    size_t size() const;
};

struct TaskPackage : public Package
{
    static const quint8 packageType = 3;
    quint8 COI;
    quint8 taskType;
    quint8 paramBlockSize;
    QVector<quint32> params;

    explicit TaskPackage(quint8 COI = 0, quint8 taskType = 0, QVector<quint32> params = QVector<quint32>());
    QString toString() const;
    size_t size() const;
};

struct SetPackage : public Package
{
    static const quint8 packageType = 4;
    quint8 COI;
    quint8 paramBlockSize;
    QVector<std::pair<quint8, quint32>> params;

    explicit SetPackage(quint8 COI = 0, QVector<std::pair<quint8, quint32>> params = QVector<std::pair<quint8, quint32>>());
    QString toString() const;
    size_t size() const;
};

struct AnswerPackage : public Package
{
    static const quint8 packageType = 5;
    quint8 COI;
    quint8 answerType;

    explicit AnswerPackage(quint8 COI = 0, quint8 answerType = 0);
    QString toString() const;
    size_t size() const;
};

struct DataPackage : public Package
{
    static const quint8 packageType = 6;
    quint8 stateType;
    quint8 dataBlockSize;
    QVector<std::pair<quint8, quint32>> data;

    explicit DataPackage(quint8 stateType = 0, QVector<std::pair<quint8, quint32>> data = QVector<std::pair<quint8, quint32>>());
    QString toString() const;
    size_t size() const;
};

/*
 *  packageType:
 *      0 - Empty
 *      1 - Auth / AuthAnswer
 *      2 - Task / TaskAnswer
 *      3 - Set / SetAnser
 *      4 - DataPackage
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
