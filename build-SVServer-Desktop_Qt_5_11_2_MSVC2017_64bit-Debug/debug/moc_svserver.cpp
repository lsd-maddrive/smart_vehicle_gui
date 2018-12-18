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
    QByteArrayData data[21];
    char stringdata0[262];
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
QT_MOC_LITERAL(6, 60, 17), // "slotNewConnection"
QT_MOC_LITERAL(7, 78, 15), // "slotAcceptError"
QT_MOC_LITERAL(8, 94, 28), // "QAbstractSocket::SocketError"
QT_MOC_LITERAL(9, 123, 5), // "error"
QT_MOC_LITERAL(10, 129, 22), // "slotClientDisconnected"
QT_MOC_LITERAL(11, 152, 13), // "slotReadyRead"
QT_MOC_LITERAL(12, 166, 11), // "slotUIStart"
QT_MOC_LITERAL(13, 178, 6), // "adress"
QT_MOC_LITERAL(14, 185, 4), // "port"
QT_MOC_LITERAL(15, 190, 10), // "slotUIStop"
QT_MOC_LITERAL(16, 201, 13), // "slotUISendAll"
QT_MOC_LITERAL(17, 215, 14), // "slotUITestSend"
QT_MOC_LITERAL(18, 230, 7), // "command"
QT_MOC_LITERAL(19, 238, 12), // "slotTaskDone"
QT_MOC_LITERAL(20, 251, 10) // "answerType"

    },
    "SVServer\0signalUILog\0\0message\0"
    "signalUIChangeState\0listening\0"
    "slotNewConnection\0slotAcceptError\0"
    "QAbstractSocket::SocketError\0error\0"
    "slotClientDisconnected\0slotReadyRead\0"
    "slotUIStart\0adress\0port\0slotUIStop\0"
    "slotUISendAll\0slotUITestSend\0command\0"
    "slotTaskDone\0answerType"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SVServer[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   69,    2, 0x06 /* Public */,
       4,    1,   72,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    0,   75,    2, 0x08 /* Private */,
       7,    1,   76,    2, 0x08 /* Private */,
      10,    0,   79,    2, 0x08 /* Private */,
      11,    0,   80,    2, 0x08 /* Private */,
      12,    2,   81,    2, 0x0a /* Public */,
      15,    0,   86,    2, 0x0a /* Public */,
      16,    1,   87,    2, 0x0a /* Public */,
      17,    1,   90,    2, 0x0a /* Public */,
      19,    1,   93,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::Bool,    5,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 8,    9,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::UShort,   13,   14,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString,   18,
    QMetaType::Void, QMetaType::UChar,   20,

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
        case 2: _t->slotNewConnection(); break;
        case 3: _t->slotAcceptError((*reinterpret_cast< QAbstractSocket::SocketError(*)>(_a[1]))); break;
        case 4: _t->slotClientDisconnected(); break;
        case 5: _t->slotReadyRead(); break;
        case 6: _t->slotUIStart((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< quint16(*)>(_a[2]))); break;
        case 7: _t->slotUIStop(); break;
        case 8: _t->slotUISendAll((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 9: _t->slotUITestSend((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 10: _t->slotTaskDone((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 3:
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
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE
