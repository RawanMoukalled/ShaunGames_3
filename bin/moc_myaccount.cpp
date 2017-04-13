/****************************************************************************
** Meta object code from reading C++ file 'myaccount.h'
**
** Created: Thu Apr 13 21:50:11 2017
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../account/myaccount.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'myaccount.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MyAccount[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      11,   10,   10,   10, 0x0a,
      30,   23,   10,   10, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_MyAccount[] = {
    "MyAccount\0\0goToGames()\0gamenb\0"
    "showGameGraph(int)\0"
};

void MyAccount::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MyAccount *_t = static_cast<MyAccount *>(_o);
        switch (_id) {
        case 0: _t->goToGames(); break;
        case 1: _t->showGameGraph((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData MyAccount::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject MyAccount::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_MyAccount,
      qt_meta_data_MyAccount, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MyAccount::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MyAccount::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MyAccount::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MyAccount))
        return static_cast<void*>(const_cast< MyAccount*>(this));
    return QWidget::qt_metacast(_clname);
}

int MyAccount::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
