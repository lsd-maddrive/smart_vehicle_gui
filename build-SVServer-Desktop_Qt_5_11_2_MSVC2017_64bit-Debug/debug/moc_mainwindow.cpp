/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../SVServer/mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[21];
    char stringdata0[285];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 17), // "signalServerStart"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 6), // "adress"
QT_MOC_LITERAL(4, 37, 4), // "port"
QT_MOC_LITERAL(5, 42, 16), // "signalServerStop"
QT_MOC_LITERAL(6, 59, 19), // "signalServerSendAll"
QT_MOC_LITERAL(7, 79, 4), // "data"
QT_MOC_LITERAL(8, 84, 22), // "signalServerTestAnswer"
QT_MOC_LITERAL(9, 107, 20), // "signalServerTestData"
QT_MOC_LITERAL(10, 128, 12), // "encoderValue"
QT_MOC_LITERAL(11, 141, 18), // "potentiometerValue"
QT_MOC_LITERAL(12, 160, 17), // "slotConnectButton"
QT_MOC_LITERAL(13, 178, 14), // "slotSendButton"
QT_MOC_LITERAL(14, 193, 16), // "slotAnswerButton"
QT_MOC_LITERAL(15, 210, 14), // "slotDataButton"
QT_MOC_LITERAL(16, 225, 7), // "slotLog"
QT_MOC_LITERAL(17, 233, 7), // "message"
QT_MOC_LITERAL(18, 241, 21), // "slotServerChangeState"
QT_MOC_LITERAL(19, 263, 5), // "state"
QT_MOC_LITERAL(20, 269, 15) // "slotRefreshData"

    },
    "MainWindow\0signalServerStart\0\0adress\0"
    "port\0signalServerStop\0signalServerSendAll\0"
    "data\0signalServerTestAnswer\0"
    "signalServerTestData\0encoderValue\0"
    "potentiometerValue\0slotConnectButton\0"
    "slotSendButton\0slotAnswerButton\0"
    "slotDataButton\0slotLog\0message\0"
    "slotServerChangeState\0state\0slotRefreshData"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       7,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   84,    2, 0x06 /* Public */,
       1,    1,   89,    2, 0x26 /* Public | MethodCloned */,
       1,    0,   92,    2, 0x26 /* Public | MethodCloned */,
       5,    0,   93,    2, 0x06 /* Public */,
       6,    1,   94,    2, 0x06 /* Public */,
       8,    0,   97,    2, 0x06 /* Public */,
       9,    2,   98,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      12,    0,  103,    2, 0x08 /* Private */,
      13,    0,  104,    2, 0x08 /* Private */,
      14,    0,  105,    2, 0x08 /* Private */,
      15,    0,  106,    2, 0x08 /* Private */,
      16,    1,  107,    2, 0x0a /* Public */,
      18,    1,  110,    2, 0x0a /* Public */,
      20,    0,  113,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::UShort,    3,    4,
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    7,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   10,   11,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   17,
    QMetaType::Void, QMetaType::Bool,   19,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signalServerStart((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< quint16(*)>(_a[2]))); break;
        case 1: _t->signalServerStart((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->signalServerStart(); break;
        case 3: _t->signalServerStop(); break;
        case 4: _t->signalServerSendAll((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 5: _t->signalServerTestAnswer(); break;
        case 6: _t->signalServerTestData((*reinterpret_cast< qint32(*)>(_a[1])),(*reinterpret_cast< qint32(*)>(_a[2]))); break;
        case 7: _t->slotConnectButton(); break;
        case 8: _t->slotSendButton(); break;
        case 9: _t->slotAnswerButton(); break;
        case 10: _t->slotDataButton(); break;
        case 11: _t->slotLog((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 12: _t->slotServerChangeState((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 13: _t->slotRefreshData(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (MainWindow::*)(QString , quint16 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::signalServerStart)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::signalServerStop)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::signalServerSendAll)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::signalServerTestAnswer)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)(qint32 , qint32 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::signalServerTestData)) {
                *result = 6;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MainWindow::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 14;
    }
    return _id;
}

// SIGNAL 0
void MainWindow::signalServerStart(QString _t1, quint16 _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 3
void MainWindow::signalServerStop()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void MainWindow::signalServerSendAll(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void MainWindow::signalServerTestAnswer()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void MainWindow::signalServerTestData(qint32 _t1, qint32 _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
