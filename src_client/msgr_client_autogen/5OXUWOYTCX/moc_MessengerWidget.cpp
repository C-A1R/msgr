/****************************************************************************
** Meta object code from reading C++ file 'MessengerWidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../main_window/messenger_widget/MessengerWidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MessengerWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MessengerWidget_t {
    QByteArrayData data[21];
    char stringdata0[398];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MessengerWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MessengerWidget_t qt_meta_stringdata_MessengerWidget = {
    {
QT_MOC_LITERAL(0, 0, 15), // "MessengerWidget"
QT_MOC_LITERAL(1, 16, 25), // "slot_outputMessageRequest"
QT_MOC_LITERAL(2, 42, 0), // ""
QT_MOC_LITERAL(3, 43, 9), // "contactId"
QT_MOC_LITERAL(4, 53, 11), // "std::string"
QT_MOC_LITERAL(5, 65, 4), // "text"
QT_MOC_LITERAL(6, 70, 26), // "slot_outputMessageResponse"
QT_MOC_LITERAL(7, 97, 28), // "std::shared_ptr<MessageInfo>"
QT_MOC_LITERAL(8, 126, 7), // "message"
QT_MOC_LITERAL(9, 134, 24), // "slot_inputMessageRequest"
QT_MOC_LITERAL(10, 159, 21), // "slot_getUsersResponse"
QT_MOC_LITERAL(11, 181, 39), // "std::vector<std::shared_ptr<U..."
QT_MOC_LITERAL(12, 221, 8), // "contacts"
QT_MOC_LITERAL(13, 230, 22), // "slot_newUserRegistered"
QT_MOC_LITERAL(14, 253, 25), // "std::shared_ptr<UserInfo>"
QT_MOC_LITERAL(15, 279, 7), // "contact"
QT_MOC_LITERAL(16, 287, 24), // "slot_getMessagesResponse"
QT_MOC_LITERAL(17, 312, 42), // "std::vector<std::shared_ptr<M..."
QT_MOC_LITERAL(18, 355, 8), // "messages"
QT_MOC_LITERAL(19, 364, 15), // "slot_changeChat"
QT_MOC_LITERAL(20, 380, 17) // "updateContactList"

    },
    "MessengerWidget\0slot_outputMessageRequest\0"
    "\0contactId\0std::string\0text\0"
    "slot_outputMessageResponse\0"
    "std::shared_ptr<MessageInfo>\0message\0"
    "slot_inputMessageRequest\0slot_getUsersResponse\0"
    "std::vector<std::shared_ptr<UserInfo> >\0"
    "contacts\0slot_newUserRegistered\0"
    "std::shared_ptr<UserInfo>\0contact\0"
    "slot_getMessagesResponse\0"
    "std::vector<std::shared_ptr<MessageInfo> >\0"
    "messages\0slot_changeChat\0updateContactList"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MessengerWidget[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    2,   54,    2, 0x08 /* Private */,
       6,    1,   59,    2, 0x08 /* Private */,
       9,    1,   62,    2, 0x08 /* Private */,
      10,    1,   65,    2, 0x08 /* Private */,
      13,    1,   68,    2, 0x08 /* Private */,
      16,    1,   71,    2, 0x08 /* Private */,
      19,    0,   74,    2, 0x08 /* Private */,
      20,    0,   75,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int, 0x80000000 | 4,    3,    5,
    QMetaType::Void, 0x80000000 | 7,    8,
    QMetaType::Void, 0x80000000 | 7,    8,
    QMetaType::Void, 0x80000000 | 11,   12,
    QMetaType::Void, 0x80000000 | 14,   15,
    QMetaType::Void, 0x80000000 | 17,   18,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MessengerWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MessengerWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->slot_outputMessageRequest((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const std::string(*)>(_a[2]))); break;
        case 1: _t->slot_outputMessageResponse((*reinterpret_cast< const std::shared_ptr<MessageInfo>(*)>(_a[1]))); break;
        case 2: _t->slot_inputMessageRequest((*reinterpret_cast< const std::shared_ptr<MessageInfo>(*)>(_a[1]))); break;
        case 3: _t->slot_getUsersResponse((*reinterpret_cast< const std::vector<std::shared_ptr<UserInfo> >(*)>(_a[1]))); break;
        case 4: _t->slot_newUserRegistered((*reinterpret_cast< const std::shared_ptr<UserInfo>(*)>(_a[1]))); break;
        case 5: _t->slot_getMessagesResponse((*reinterpret_cast< const std::vector<std::shared_ptr<MessageInfo> >(*)>(_a[1]))); break;
        case 6: _t->slot_changeChat(); break;
        case 7: _t->updateContactList(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< std::shared_ptr<MessageInfo> >(); break;
            }
            break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< std::shared_ptr<MessageInfo> >(); break;
            }
            break;
        case 3:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< std::vector<std::shared_ptr<UserInfo> > >(); break;
            }
            break;
        case 4:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< std::shared_ptr<UserInfo> >(); break;
            }
            break;
        case 5:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< std::vector<std::shared_ptr<MessageInfo> > >(); break;
            }
            break;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MessengerWidget::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_MessengerWidget.data,
    qt_meta_data_MessengerWidget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MessengerWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MessengerWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MessengerWidget.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int MessengerWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE