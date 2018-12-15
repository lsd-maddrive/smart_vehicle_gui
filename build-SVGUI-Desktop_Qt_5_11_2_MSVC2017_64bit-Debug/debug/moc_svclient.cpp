/****************************************************************************
** Meta object code from reading C++ file 'svclient.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../SVGUI/svclient.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'svclient.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_SVClient_t {
    QByteArrayData data[16];
    char stringdata0[211];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SVClient_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SVClient_t qt_meta_stringdata_SVClient = {
    {
QT_MOC_LITERAL(0, 0, 8), // "SVClient"
QT_MOC_LITERAL(1, 9, 17), // "signalUIConnected"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 20), // "signalUIDisconnected"
QT_MOC_LITERAL(4, 49, 13), // "signalUIError"
QT_MOC_LITERAL(5, 63, 7), // "message"
QT_MOC_LITERAL(6, 71, 13), // "slotConnected"
QT_MOC_LITERAL(7, 85, 16), // "slotDisconnected"
QT_MOC_LITERAL(8, 102, 9), // "slotError"
QT_MOC_LITERAL(9, 112, 28), // "QAbstractSocket::SocketError"
QT_MOC_LITERAL(10, 141, 11), // "socketError"
QT_MOC_LITERAL(11, 153, 13), // "slotReadyRead"
QT_MOC_LITERAL(12, 167, 13), // "slotUIConnect"
QT_MOC_LITERAL(13, 181, 7), // "address"
QT_MOC_LITERAL(14, 189, 4), // "port"
QT_MOC_LITERAL(15, 194, 16) // "slotUIDisconnect"

    },
    "SVClient\0signalUIConnected\0\0"
    "signalUIDisconnected\0signalUIError\0"
    "message\0slotConnected\0slotDisconnected\0"
    "slotError\0QAbstractSocket::SocketError\0"
    "socketError\0slotReadyRead\0slotUIConnect\0"
    "address\0port\0slotUIDisconnect"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SVClient[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   59,    2, 0x06 /* Public */,
       3,    0,   60,    2, 0x06 /* Public */,
       4,    1,   61,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    0,   64,    2, 0x08 /* Private */,
       7,    0,   65,    2, 0x08 /* Private */,
       8,    1,   66,    2, 0x08 /* Private */,
      11,    0,   69,    2, 0x08 /* Private */,
      12,    2,   70,    2, 0x0a /* Public */,
      15,    0,   75,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    5,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 9,   10,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::UShort,   13,   14,
    QMetaType::Void,

       0        // eod
};

void SVClient::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        SVClient *_t = static_cast<SVClient *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signalUIConnected(); break;
        case 1: _t->signalUIDisconnected(); break;
        case 2: _t->signalUIError((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->slotConnected(); break;
        case 4: _t->slotDisconnected(); break;
        case 5: _t->slotError((*reinterpret_cast< QAbstractSocket::SocketError(*)>(_a[1]))); break;
        case 6: _t->slotReadyRead(); break;
        case 7: _t->slotUIConnect((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< quint16(*)>(_a[2]))); break;
        case 8: _t->slotUIDisconnect(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 5:
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
            using _t = void (SVClient::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SVClient::signalUIConnected)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (SVClient::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SVClient::signalUIDisconnected)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (SVClient::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SVClient::signalUIError)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject SVClient::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_SVClient.data,
      qt_meta_data_SVClient,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *SVClient::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SVClient::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_SVClient.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int SVClient::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void SVClient::signalUIConnected()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void SVClient::signalUIDisconnected()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void SVClient::signalUIError(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
