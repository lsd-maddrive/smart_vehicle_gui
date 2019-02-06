/****************************************************************************
** Meta object code from reading C++ file 'svserver.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../SVServer/svserver.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'svserver.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_SVServer_t {
    QByteArrayData data[35];
    char stringdata0[412];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SVServer_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SVServer_t qt_meta_stringdata_SVServer = {
    {
QT_MOC_LITERAL(0, 0, 8), // "SVServer"
QT_MOC_LITERAL(1, 9, 11), // "signalUILog"
QT_MOC_LITERAL(2, 21, 0), // ""
QT_MOC_LITERAL(3, 22, 7), // "message"
QT_MOC_LITERAL(4, 30, 19), // "signalUIChangeState"
QT_MOC_LITERAL(5, 50, 9), // "listening"
QT_MOC_LITERAL(6, 60, 17), // "signalTaskForward"
QT_MOC_LITERAL(7, 78, 10), // "distantion"
QT_MOC_LITERAL(8, 89, 16), // "signalTaskWheels"
QT_MOC_LITERAL(9, 106, 5), // "angle"
QT_MOC_LITERAL(10, 112, 15), // "signalTaskFlick"
QT_MOC_LITERAL(11, 128, 12), // "signalSetPID"
QT_MOC_LITERAL(12, 141, 1), // "p"
QT_MOC_LITERAL(13, 143, 1), // "i"
QT_MOC_LITERAL(14, 145, 1), // "d"
QT_MOC_LITERAL(15, 147, 18), // "signalSetServoZero"
QT_MOC_LITERAL(16, 166, 4), // "zero"
QT_MOC_LITERAL(17, 171, 17), // "slotNewConnection"
QT_MOC_LITERAL(18, 189, 15), // "slotAcceptError"
QT_MOC_LITERAL(19, 205, 28), // "QAbstractSocket::SocketError"
QT_MOC_LITERAL(20, 234, 5), // "error"
QT_MOC_LITERAL(21, 240, 22), // "slotClientDisconnected"
QT_MOC_LITERAL(22, 263, 13), // "slotReadyRead"
QT_MOC_LITERAL(23, 277, 11), // "slotUIStart"
QT_MOC_LITERAL(24, 289, 6), // "adress"
QT_MOC_LITERAL(25, 296, 4), // "port"
QT_MOC_LITERAL(26, 301, 10), // "slotUIStop"
QT_MOC_LITERAL(27, 312, 13), // "slotUISendAll"
QT_MOC_LITERAL(28, 326, 16), // "slotUITestAnswer"
QT_MOC_LITERAL(29, 343, 14), // "slotUITestData"
QT_MOC_LITERAL(30, 358, 12), // "slotTaskDone"
QT_MOC_LITERAL(31, 371, 10), // "answerType"
QT_MOC_LITERAL(32, 382, 12), // "slotSendData"
QT_MOC_LITERAL(33, 395, 11), // "DataPackage"
QT_MOC_LITERAL(34, 407, 4) // "data"

    },
    "SVServer\0signalUILog\0\0message\0"
    "signalUIChangeState\0listening\0"
    "signalTaskForward\0distantion\0"
    "signalTaskWheels\0angle\0signalTaskFlick\0"
    "signalSetPID\0p\0i\0d\0signalSetServoZero\0"
    "zero\0slotNewConnection\0slotAcceptError\0"
    "QAbstractSocket::SocketError\0error\0"
    "slotClientDisconnected\0slotReadyRead\0"
    "slotUIStart\0adress\0port\0slotUIStop\0"
    "slotUISendAll\0slotUITestAnswer\0"
    "slotUITestData\0slotTaskDone\0answerType\0"
    "slotSendData\0DataPackage\0data"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SVServer[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      18,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       7,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,  104,    2, 0x06 /* Public */,
       4,    1,  107,    2, 0x06 /* Public */,
       6,    1,  110,    2, 0x06 /* Public */,
       8,    1,  113,    2, 0x06 /* Public */,
      10,    0,  116,    2, 0x06 /* Public */,
      11,    3,  117,    2, 0x06 /* Public */,
      15,    1,  124,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      17,    0,  127,    2, 0x08 /* Private */,
      18,    1,  128,    2, 0x08 /* Private */,
      21,    0,  131,    2, 0x08 /* Private */,
      22,    0,  132,    2, 0x08 /* Private */,
      23,    2,  133,    2, 0x0a /* Public */,
      26,    0,  138,    2, 0x0a /* Public */,
      27,    1,  139,    2, 0x0a /* Public */,
      28,    0,  142,    2, 0x0a /* Public */,
      29,    2,  143,    2, 0x0a /* Public */,
      30,    1,  148,    2, 0x0a /* Public */,
      32,    1,  151,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::Bool,    5,
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void, QMetaType::Int,    9,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int,   12,   13,   14,
    QMetaType::Void, QMetaType::Int,   16,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 19,   20,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::UShort,   24,   25,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    2,    2,
    QMetaType::Void, QMetaType::UChar,   31,
    QMetaType::Void, 0x80000000 | 33,   34,

       0        // eod
};

void SVServer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        SVServer *_t = static_cast<SVServer *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signalUILog((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->signalUIChangeState((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->signalTaskForward((*reinterpret_cast< qint32(*)>(_a[1]))); break;
        case 3: _t->signalTaskWheels((*reinterpret_cast< qint32(*)>(_a[1]))); break;
        case 4: _t->signalTaskFlick(); break;
        case 5: _t->signalSetPID((*reinterpret_cast< qint32(*)>(_a[1])),(*reinterpret_cast< qint32(*)>(_a[2])),(*reinterpret_cast< qint32(*)>(_a[3]))); break;
        case 6: _t->signalSetServoZero((*reinterpret_cast< qint32(*)>(_a[1]))); break;
        case 7: _t->slotNewConnection(); break;
        case 8: _t->slotAcceptError((*reinterpret_cast< QAbstractSocket::SocketError(*)>(_a[1]))); break;
        case 9: _t->slotClientDisconnected(); break;
        case 10: _t->slotReadyRead(); break;
        case 11: _t->slotUIStart((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< quint16(*)>(_a[2]))); break;
        case 12: _t->slotUIStop(); break;
        case 13: _t->slotUISendAll((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 14: _t->slotUITestAnswer(); break;
        case 15: _t->slotUITestData((*reinterpret_cast< qint32(*)>(_a[1])),(*reinterpret_cast< qint32(*)>(_a[2]))); break;
        case 16: _t->slotTaskDone((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 17: _t->slotSendData((*reinterpret_cast< DataPackage(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 8:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAbstractSocket::SocketError >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (SVServer::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SVServer::signalUILog)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (SVServer::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SVServer::signalUIChangeState)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (SVServer::*)(qint32 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SVServer::signalTaskForward)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (SVServer::*)(qint32 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SVServer::signalTaskWheels)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (SVServer::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SVServer::signalTaskFlick)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (SVServer::*)(qint32 , qint32 , qint32 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SVServer::signalSetPID)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (SVServer::*)(qint32 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SVServer::signalSetServoZero)) {
                *result = 6;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject SVServer::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_SVServer.data,
      qt_meta_data_SVServer,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *SVServer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SVServer::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_SVServer.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int SVServer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 18)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 18;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 18)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 18;
    }
    return _id;
}

// SIGNAL 0
void SVServer::signalUILog(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void SVServer::signalUIChangeState(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void SVServer::signalTaskForward(qint32 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void SVServer::signalTaskWheels(qint32 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void SVServer::signalTaskFlick()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void SVServer::signalSetPID(qint32 _t1, qint32 _t2, qint32 _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void SVServer::signalSetServoZero(qint32 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
