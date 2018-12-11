/****************************************************************************
** Meta object code from reading C++ file 'consoleinterface.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../SmartVehicleServer/consoleinterface.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'consoleinterface.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ConsoleInterface_t {
    QByteArrayData data[7];
    char stringdata0[100];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ConsoleInterface_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ConsoleInterface_t qt_meta_stringdata_ConsoleInterface = {
    {
QT_MOC_LITERAL(0, 0, 16), // "ConsoleInterface"
QT_MOC_LITERAL(1, 17, 18), // "signalConsoleStart"
QT_MOC_LITERAL(2, 36, 0), // ""
QT_MOC_LITERAL(3, 37, 17), // "signalConsoleStop"
QT_MOC_LITERAL(4, 55, 17), // "signalConsoleSend"
QT_MOC_LITERAL(5, 73, 7), // "message"
QT_MOC_LITERAL(6, 81, 18) // "slotConsoleMessage"

    },
    "ConsoleInterface\0signalConsoleStart\0"
    "\0signalConsoleStop\0signalConsoleSend\0"
    "message\0slotConsoleMessage"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ConsoleInterface[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   34,    2, 0x06 /* Public */,
       3,    0,   35,    2, 0x06 /* Public */,
       4,    1,   36,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    1,   39,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    5,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    5,

       0        // eod
};

void ConsoleInterface::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ConsoleInterface *_t = static_cast<ConsoleInterface *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signalConsoleStart(); break;
        case 1: _t->signalConsoleStop(); break;
        case 2: _t->signalConsoleSend((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->slotConsoleMessage((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (ConsoleInterface::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ConsoleInterface::signalConsoleStart)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (ConsoleInterface::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ConsoleInterface::signalConsoleStop)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (ConsoleInterface::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ConsoleInterface::signalConsoleSend)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ConsoleInterface::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_ConsoleInterface.data,
      qt_meta_data_ConsoleInterface,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *ConsoleInterface::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ConsoleInterface::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ConsoleInterface.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int ConsoleInterface::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void ConsoleInterface::signalConsoleStart()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void ConsoleInterface::signalConsoleStop()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void ConsoleInterface::signalConsoleSend(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
