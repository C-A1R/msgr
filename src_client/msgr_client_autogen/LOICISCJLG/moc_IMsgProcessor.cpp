/****************************************************************************
** Meta object code from reading C++ file 'IMsgProcessor.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../message_processor/IMsgProcessor.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'IMsgProcessor.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_IMsgProcessor_t {
    QByteArrayData data[7];
    char stringdata0[99];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_IMsgProcessor_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_IMsgProcessor_t qt_meta_stringdata_IMsgProcessor = {
    {
QT_MOC_LITERAL(0, 0, 13), // "IMsgProcessor"
QT_MOC_LITERAL(1, 14, 17), // "signal_stopClient"
QT_MOC_LITERAL(2, 32, 0), // ""
QT_MOC_LITERAL(3, 33, 25), // "signal_sendToClientThread"
QT_MOC_LITERAL(4, 59, 3), // "msg"
QT_MOC_LITERAL(5, 63, 16), // "signal_sendToGui"
QT_MOC_LITERAL(6, 80, 18) // "signal_sendRequest"

    },
    "IMsgProcessor\0signal_stopClient\0\0"
    "signal_sendToClientThread\0msg\0"
    "signal_sendToGui\0signal_sendRequest"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_IMsgProcessor[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   34,    2, 0x06 /* Public */,
       3,    1,   35,    2, 0x06 /* Public */,
       5,    1,   38,    2, 0x06 /* Public */,
       6,    1,   41,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    4,
    QMetaType::Void, QMetaType::QString,    4,
    QMetaType::Void, QMetaType::QString,    2,

       0        // eod
};

void IMsgProcessor::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<IMsgProcessor *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signal_stopClient(); break;
        case 1: _t->signal_sendToClientThread((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->signal_sendToGui((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: _t->signal_sendRequest((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (IMsgProcessor::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&IMsgProcessor::signal_stopClient)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (IMsgProcessor::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&IMsgProcessor::signal_sendToClientThread)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (IMsgProcessor::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&IMsgProcessor::signal_sendToGui)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (IMsgProcessor::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&IMsgProcessor::signal_sendRequest)) {
                *result = 3;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject IMsgProcessor::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_IMsgProcessor.data,
    qt_meta_data_IMsgProcessor,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *IMsgProcessor::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *IMsgProcessor::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_IMsgProcessor.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int IMsgProcessor::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void IMsgProcessor::signal_stopClient()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void IMsgProcessor::signal_sendToClientThread(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void IMsgProcessor::signal_sendToGui(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void IMsgProcessor::signal_sendRequest(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
