/****************************************************************************
** Meta object code from reading C++ file 'IClientProcessor.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../client_processor/IClientProcessor.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'IClientProcessor.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_IClientProcessor_t {
    QByteArrayData data[10];
    char stringdata0[158];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_IClientProcessor_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_IClientProcessor_t qt_meta_stringdata_IClientProcessor = {
    {
QT_MOC_LITERAL(0, 0, 16), // "IClientProcessor"
QT_MOC_LITERAL(1, 17, 17), // "signal_stopClient"
QT_MOC_LITERAL(2, 35, 0), // ""
QT_MOC_LITERAL(3, 36, 25), // "signal_sendToClientThread"
QT_MOC_LITERAL(4, 62, 11), // "std::string"
QT_MOC_LITERAL(5, 74, 16), // "signal_sendToGui"
QT_MOC_LITERAL(6, 91, 18), // "signal_sendRequest"
QT_MOC_LITERAL(7, 110, 21), // "signal_signUpResponse"
QT_MOC_LITERAL(8, 132, 16), // "slot_getResponse"
QT_MOC_LITERAL(9, 149, 8) // "response"

    },
    "IClientProcessor\0signal_stopClient\0\0"
    "signal_sendToClientThread\0std::string\0"
    "signal_sendToGui\0signal_sendRequest\0"
    "signal_signUpResponse\0slot_getResponse\0"
    "response"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_IClientProcessor[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   44,    2, 0x06 /* Public */,
       3,    1,   45,    2, 0x06 /* Public */,
       5,    1,   48,    2, 0x06 /* Public */,
       6,    1,   51,    2, 0x06 /* Public */,
       7,    1,   54,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       8,    1,   57,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4,    2,
    QMetaType::Void, 0x80000000 | 4,    2,
    QMetaType::Void, 0x80000000 | 4,    2,
    QMetaType::Void, 0x80000000 | 4,    2,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 4,    9,

       0        // eod
};

void IClientProcessor::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<IClientProcessor *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signal_stopClient(); break;
        case 1: _t->signal_sendToClientThread((*reinterpret_cast< const std::string(*)>(_a[1]))); break;
        case 2: _t->signal_sendToGui((*reinterpret_cast< const std::string(*)>(_a[1]))); break;
        case 3: _t->signal_sendRequest((*reinterpret_cast< const std::string(*)>(_a[1]))); break;
        case 4: _t->signal_signUpResponse((*reinterpret_cast< const std::string(*)>(_a[1]))); break;
        case 5: _t->slot_getResponse((*reinterpret_cast< const std::string(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (IClientProcessor::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&IClientProcessor::signal_stopClient)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (IClientProcessor::*)(const std::string & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&IClientProcessor::signal_sendToClientThread)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (IClientProcessor::*)(const std::string & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&IClientProcessor::signal_sendToGui)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (IClientProcessor::*)(const std::string & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&IClientProcessor::signal_sendRequest)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (IClientProcessor::*)(const std::string & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&IClientProcessor::signal_signUpResponse)) {
                *result = 4;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject IClientProcessor::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_IClientProcessor.data,
    qt_meta_data_IClientProcessor,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *IClientProcessor::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *IClientProcessor::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_IClientProcessor.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int IClientProcessor::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void IClientProcessor::signal_stopClient()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void IClientProcessor::signal_sendToClientThread(const std::string & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void IClientProcessor::signal_sendToGui(const std::string & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void IClientProcessor::signal_sendRequest(const std::string & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void IClientProcessor::signal_signUpResponse(const std::string & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
