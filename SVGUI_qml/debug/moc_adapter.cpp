/****************************************************************************
** Meta object code from reading C++ file 'adapter.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../adapter.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'adapter.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Adapter_t {
    QByteArrayData data[27];
    char stringdata0[342];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Adapter_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Adapter_t qt_meta_stringdata_Adapter = {
    {
QT_MOC_LITERAL(0, 0, 7), // "Adapter"
QT_MOC_LITERAL(1, 8, 13), // "signalConnect"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 7), // "address"
QT_MOC_LITERAL(4, 31, 4), // "port"
QT_MOC_LITERAL(5, 36, 16), // "signalDisconnect"
QT_MOC_LITERAL(6, 53, 11), // "signalUILog"
QT_MOC_LITERAL(7, 65, 7), // "message"
QT_MOC_LITERAL(8, 73, 17), // "signalUIConnected"
QT_MOC_LITERAL(9, 91, 20), // "signalUIDisconnected"
QT_MOC_LITERAL(10, 112, 23), // "signalUIConnectionError"
QT_MOC_LITERAL(11, 136, 14), // "signalUIStatus"
QT_MOC_LITERAL(12, 151, 3), // "str"
QT_MOC_LITERAL(13, 155, 25), // "signalUIPotentiometerData"
QT_MOC_LITERAL(14, 181, 8), // "potValue"
QT_MOC_LITERAL(15, 190, 19), // "signalUIEncoderData"
QT_MOC_LITERAL(16, 210, 8), // "encValue"
QT_MOC_LITERAL(17, 219, 8), // "slotTest"
QT_MOC_LITERAL(18, 228, 13), // "slotUIConnect"
QT_MOC_LITERAL(19, 242, 16), // "slotUIDisconnect"
QT_MOC_LITERAL(20, 259, 13), // "slotConnected"
QT_MOC_LITERAL(21, 273, 5), // "state"
QT_MOC_LITERAL(22, 279, 16), // "slotDisconnected"
QT_MOC_LITERAL(23, 296, 19), // "slotConnectionError"
QT_MOC_LITERAL(24, 316, 8), // "slotData"
QT_MOC_LITERAL(25, 325, 11), // "DataPackage"
QT_MOC_LITERAL(26, 337, 4) // "data"

    },
    "Adapter\0signalConnect\0\0address\0port\0"
    "signalDisconnect\0signalUILog\0message\0"
    "signalUIConnected\0signalUIDisconnected\0"
    "signalUIConnectionError\0signalUIStatus\0"
    "str\0signalUIPotentiometerData\0potValue\0"
    "signalUIEncoderData\0encValue\0slotTest\0"
    "slotUIConnect\0slotUIDisconnect\0"
    "slotConnected\0state\0slotDisconnected\0"
    "slotConnectionError\0slotData\0DataPackage\0"
    "data"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Adapter[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       9,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   94,    2, 0x06 /* Public */,
       5,    0,   99,    2, 0x06 /* Public */,
       6,    1,  100,    2, 0x06 /* Public */,
       8,    0,  103,    2, 0x06 /* Public */,
       9,    0,  104,    2, 0x06 /* Public */,
      10,    0,  105,    2, 0x06 /* Public */,
      11,    1,  106,    2, 0x06 /* Public */,
      13,    1,  109,    2, 0x06 /* Public */,
      15,    1,  112,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      17,    0,  115,    2, 0x0a /* Public */,
      18,    2,  116,    2, 0x0a /* Public */,
      19,    0,  121,    2, 0x0a /* Public */,
      20,    1,  122,    2, 0x0a /* Public */,
      22,    0,  125,    2, 0x0a /* Public */,
      23,    1,  126,    2, 0x0a /* Public */,
      24,    1,  129,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::UShort,    3,    4,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    7,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   12,
    QMetaType::Void, QMetaType::Int,   14,
    QMetaType::Void, QMetaType::Int,   16,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    3,    4,
    QMetaType::Void,
    QMetaType::Void, QMetaType::SChar,   21,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    7,
    QMetaType::Void, 0x80000000 | 25,   26,

       0        // eod
};

void Adapter::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Adapter *_t = static_cast<Adapter *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signalConnect((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const quint16(*)>(_a[2]))); break;
        case 1: _t->signalDisconnect(); break;
        case 2: _t->signalUILog((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: _t->signalUIConnected(); break;
        case 4: _t->signalUIDisconnected(); break;
        case 5: _t->signalUIConnectionError(); break;
        case 6: _t->signalUIStatus((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 7: _t->signalUIPotentiometerData((*reinterpret_cast< const qint32(*)>(_a[1]))); break;
        case 8: _t->signalUIEncoderData((*reinterpret_cast< const qint32(*)>(_a[1]))); break;
        case 9: _t->slotTest(); break;
        case 10: _t->slotUIConnect((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 11: _t->slotUIDisconnect(); break;
        case 12: _t->slotConnected((*reinterpret_cast< const qint8(*)>(_a[1]))); break;
        case 13: _t->slotDisconnected(); break;
        case 14: _t->slotConnectionError((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 15: _t->slotData((*reinterpret_cast< const DataPackage(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Adapter::*)(QString const & , quint16 const & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Adapter::signalConnect)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (Adapter::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Adapter::signalDisconnect)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (Adapter::*)(QString const & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Adapter::signalUILog)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (Adapter::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Adapter::signalUIConnected)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (Adapter::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Adapter::signalUIDisconnected)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (Adapter::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Adapter::signalUIConnectionError)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (Adapter::*)(QString const & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Adapter::signalUIStatus)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (Adapter::*)(qint32 const & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Adapter::signalUIPotentiometerData)) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (Adapter::*)(qint32 const & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Adapter::signalUIEncoderData)) {
                *result = 8;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Adapter::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Adapter.data,
      qt_meta_data_Adapter,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *Adapter::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Adapter::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Adapter.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int Adapter::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 16)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 16;
    }
    return _id;
}

// SIGNAL 0
void Adapter::signalConnect(QString const & _t1, quint16 const & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Adapter::signalDisconnect()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void Adapter::signalUILog(QString const & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void Adapter::signalUIConnected()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void Adapter::signalUIDisconnected()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void Adapter::signalUIConnectionError()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void Adapter::signalUIStatus(QString const & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void Adapter::signalUIPotentiometerData(qint32 const & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void Adapter::signalUIEncoderData(qint32 const & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
