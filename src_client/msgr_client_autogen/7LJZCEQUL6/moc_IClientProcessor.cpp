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
    QByteArrayData data[20];
    char stringdata0[432];
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
QT_MOC_LITERAL(3, 36, 18), // "signal_sendRequest"
QT_MOC_LITERAL(4, 55, 11), // "std::string"
QT_MOC_LITERAL(5, 67, 19), // "signal_sendResponse"
QT_MOC_LITERAL(6, 87, 21), // "signal_signUpResponse"
QT_MOC_LITERAL(7, 109, 21), // "signal_signInResponse"
QT_MOC_LITERAL(8, 131, 28), // "signal_outputMessageResponse"
QT_MOC_LITERAL(9, 160, 28), // "std::shared_ptr<MessageInfo>"
QT_MOC_LITERAL(10, 189, 7), // "message"
QT_MOC_LITERAL(11, 197, 23), // "signal_getUsersResponse"
QT_MOC_LITERAL(12, 221, 39), // "std::vector<std::shared_ptr<U..."
QT_MOC_LITERAL(13, 261, 26), // "signal_inputMessageRequest"
QT_MOC_LITERAL(14, 288, 24), // "signal_newUserRegistered"
QT_MOC_LITERAL(15, 313, 25), // "std::shared_ptr<UserInfo>"
QT_MOC_LITERAL(16, 339, 26), // "signal_getMessagesResponse"
QT_MOC_LITERAL(17, 366, 42), // "std::vector<std::shared_ptr<M..."
QT_MOC_LITERAL(18, 409, 18), // "slot_parseRecieved"
QT_MOC_LITERAL(19, 428, 3) // "msg"

    },
    "IClientProcessor\0signal_stopClient\0\0"
    "signal_sendRequest\0std::string\0"
    "signal_sendResponse\0signal_signUpResponse\0"
    "signal_signInResponse\0"
    "signal_outputMessageResponse\0"
    "std::shared_ptr<MessageInfo>\0message\0"
    "signal_getUsersResponse\0"
    "std::vector<std::shared_ptr<UserInfo> >\0"
    "signal_inputMessageRequest\0"
    "signal_newUserRegistered\0"
    "std::shared_ptr<UserInfo>\0"
    "signal_getMessagesResponse\0"
    "std::vector<std::shared_ptr<MessageInfo> >\0"
    "slot_parseRecieved\0msg"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_IClientProcessor[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      10,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   69,    2, 0x06 /* Public */,
       3,    1,   70,    2, 0x06 /* Public */,
       5,    1,   73,    2, 0x06 /* Public */,
       6,    1,   76,    2, 0x06 /* Public */,
       7,    1,   79,    2, 0x06 /* Public */,
       8,    1,   82,    2, 0x06 /* Public */,
      11,    1,   85,    2, 0x06 /* Public */,
      13,    1,   88,    2, 0x06 /* Public */,
      14,    1,   91,    2, 0x06 /* Public */,
      16,    1,   94,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      18,    1,   97,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4,    2,
    QMetaType::Void, 0x80000000 | 4,    2,
    QMetaType::Void, 0x80000000 | 4,    2,
    QMetaType::Void, 0x80000000 | 4,    2,
    QMetaType::Void, 0x80000000 | 9,   10,
    QMetaType::Void, 0x80000000 | 12,    2,
    QMetaType::Void, 0x80000000 | 9,    2,
    QMetaType::Void, 0x80000000 | 15,    2,
    QMetaType::Void, 0x80000000 | 17,    2,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 4,   19,

       0        // eod
};

void IClientProcessor::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<IClientProcessor *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signal_stopClient(); break;
        case 1: _t->signal_sendRequest((*reinterpret_cast< const std::string(*)>(_a[1]))); break;
        case 2: _t->signal_sendResponse((*reinterpret_cast< const std::string(*)>(_a[1]))); break;
        case 3: _t->signal_signUpResponse((*reinterpret_cast< const std::string(*)>(_a[1]))); break;
        case 4: _t->signal_signInResponse((*reinterpret_cast< const std::string(*)>(_a[1]))); break;
        case 5: _t->signal_outputMessageResponse((*reinterpret_cast< const std::shared_ptr<MessageInfo>(*)>(_a[1]))); break;
        case 6: _t->signal_getUsersResponse((*reinterpret_cast< const std::vector<std::shared_ptr<UserInfo> >(*)>(_a[1]))); break;
        case 7: _t->signal_inputMessageRequest((*reinterpret_cast< const std::shared_ptr<MessageInfo>(*)>(_a[1]))); break;
        case 8: _t->signal_newUserRegistered((*reinterpret_cast< const std::shared_ptr<UserInfo>(*)>(_a[1]))); break;
        case 9: _t->signal_getMessagesResponse((*reinterpret_cast< const std::vector<std::shared_ptr<MessageInfo> >(*)>(_a[1]))); break;
        case 10: _t->slot_parseRecieved((*reinterpret_cast< const std::string(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 5:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< std::shared_ptr<MessageInfo> >(); break;
            }
            break;
        case 6:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< std::vector<std::shared_ptr<UserInfo> > >(); break;
            }
            break;
        case 7:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< std::shared_ptr<MessageInfo> >(); break;
            }
            break;
        case 8:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< std::shared_ptr<UserInfo> >(); break;
            }
            break;
        case 9:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< std::vector<std::shared_ptr<MessageInfo> > >(); break;
            }
            break;
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
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&IClientProcessor::signal_sendRequest)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (IClientProcessor::*)(const std::string & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&IClientProcessor::signal_sendResponse)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (IClientProcessor::*)(const std::string & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&IClientProcessor::signal_signUpResponse)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (IClientProcessor::*)(const std::string & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&IClientProcessor::signal_signInResponse)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (IClientProcessor::*)(const std::shared_ptr<MessageInfo> & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&IClientProcessor::signal_outputMessageResponse)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (IClientProcessor::*)(const std::vector<std::shared_ptr<UserInfo> > & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&IClientProcessor::signal_getUsersResponse)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (IClientProcessor::*)(const std::shared_ptr<MessageInfo> & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&IClientProcessor::signal_inputMessageRequest)) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (IClientProcessor::*)(const std::shared_ptr<UserInfo> & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&IClientProcessor::signal_newUserRegistered)) {
                *result = 8;
                return;
            }
        }
        {
            using _t = void (IClientProcessor::*)(const std::vector<std::shared_ptr<MessageInfo> > & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&IClientProcessor::signal_getMessagesResponse)) {
                *result = 9;
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
void IClientProcessor::signal_stopClient()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void IClientProcessor::signal_sendRequest(const std::string & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void IClientProcessor::signal_sendResponse(const std::string & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void IClientProcessor::signal_signUpResponse(const std::string & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void IClientProcessor::signal_signInResponse(const std::string & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void IClientProcessor::signal_outputMessageResponse(const std::shared_ptr<MessageInfo> & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void IClientProcessor::signal_getUsersResponse(const std::vector<std::shared_ptr<UserInfo> > & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void IClientProcessor::signal_inputMessageRequest(const std::shared_ptr<MessageInfo> & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void IClientProcessor::signal_newUserRegistered(const std::shared_ptr<UserInfo> & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void IClientProcessor::signal_getMessagesResponse(const std::vector<std::shared_ptr<MessageInfo> > & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
