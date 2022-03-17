/****************************************************************************
** Meta object code from reading C++ file 'AuthorizationWidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../main_window/AuthorizationWidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'AuthorizationWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_AuthorizationWidget_t {
    QByteArrayData data[9];
    char stringdata0[132];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_AuthorizationWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_AuthorizationWidget_t qt_meta_stringdata_AuthorizationWidget = {
    {
QT_MOC_LITERAL(0, 0, 19), // "AuthorizationWidget"
QT_MOC_LITERAL(1, 20, 17), // "signal_changeSign"
QT_MOC_LITERAL(2, 38, 0), // ""
QT_MOC_LITERAL(3, 39, 11), // "MainWidgets"
QT_MOC_LITERAL(4, 51, 22), // "slot_sign_pBtn_clicked"
QT_MOC_LITERAL(5, 74, 18), // "slot_SignInRequest"
QT_MOC_LITERAL(6, 93, 19), // "slot_SignInResponse"
QT_MOC_LITERAL(7, 113, 11), // "std::string"
QT_MOC_LITERAL(8, 125, 6) // "status"

    },
    "AuthorizationWidget\0signal_changeSign\0"
    "\0MainWidgets\0slot_sign_pBtn_clicked\0"
    "slot_SignInRequest\0slot_SignInResponse\0"
    "std::string\0status"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_AuthorizationWidget[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   34,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,   37,    2, 0x08 /* Private */,
       5,    0,   38,    2, 0x08 /* Private */,
       6,    1,   39,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 7,    8,

       0        // eod
};

void AuthorizationWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<AuthorizationWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signal_changeSign((*reinterpret_cast< MainWidgets(*)>(_a[1]))); break;
        case 1: _t->slot_sign_pBtn_clicked(); break;
        case 2: _t->slot_SignInRequest(); break;
        case 3: _t->slot_SignInResponse((*reinterpret_cast< const std::string(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< MainWidgets >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (AuthorizationWidget::*)(MainWidgets );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AuthorizationWidget::signal_changeSign)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject AuthorizationWidget::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_AuthorizationWidget.data,
    qt_meta_data_AuthorizationWidget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *AuthorizationWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *AuthorizationWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_AuthorizationWidget.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int AuthorizationWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void AuthorizationWidget::signal_changeSign(MainWidgets _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
