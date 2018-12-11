/****************************************************************************
** Meta object code from reading C++ file 'svserver.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../SmartVehicleServer/svserver.h"
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
    QByteArrayData data[13];
    char stringdata0[194];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SVServer_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SVServer_t qt_meta_stringdata_SVServer = {
    {
QT_MOC_LITERAL(0, 0, 8), // "SVServer"
QT_MOC_LITERAL(1, 9, 20), // "signalConsoleMessage"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 7), // "message"
QT_MOC_LITERAL(4, 39, 17), // "slotNewConnection"
QT_MOC_LITERAL(5, 57, 15), // "slotAcceptError"
QT_MOC_LITERAL(6, 73, 28), // "QAbstractSocket::SocketError"
QT_MOC_LITERAL(7, 102, 5), // "error"
QT_MOC_LITERAL(8, 108, 22), // "slotClientDisconnected"
QT_MOC_LITERAL(9, 131, 13), // "slotReadyRead"
QT_MOC_LITERAL(10, 145, 16), // "slotConsoleStart"
QT_MOC_LITERAL(11, 162, 15), // "slotConsoleStop"
QT_MOC_LITERAL(12, 178, 15) // "slotConsoleSend"

    },
    "SVServer\0signalConsoleMessage\0\0message\0"
    "slotNewConnection\0slotAcceptError\0"
    "QAbstractSocket::SocketError\0error\0"
    "slotClientDisconnected\0slotReadyRead\0"
    "slotConsoleStart\0slotConsoleStop\0"
    "slotConsoleSend"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SVServer[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   54,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,   57,    2, 0x0a /* Public */,
       5,    1,   58,    2, 0x0a /* Public */,
       8,    0,   61,    2, 0x0a /* Public */,
       9,    0,   62,    2, 0x0a /* Public */,
      10,    0,   63,    2, 0x0a /* Public */,
      11,    0,   64,    2, 0x0a /* Public */,
      12,    1,   65,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    3,

       0        // eod
};

void SVServer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        SVServer *_t = static_cast<SVServer *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signalConsoleMessage((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->slotNewConnection(); break;
        case 2: _t->slotAcceptError((*reinterpret_cast< QAbstractSocket::SocketError(*)>(_a[1]))); break;
        case 3: _t->slotClientDisconnected(); break;
        case 4: _t->slotReadyRead(); break;
        case 5: _t->slotConsoleStart(); break;
        case 6: _t->slotConsoleStop(); break;
        case 7: _t->slotConsoleSend((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 2:
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
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SVServer::signalConsoleMessage)) {
                *result = 0;
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
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void SVServer::signalConsoleMessage(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
