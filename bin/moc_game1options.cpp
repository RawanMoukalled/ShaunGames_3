/****************************************************************************
** Meta object code from reading C++ file 'game1options.h'
**
** Created: Thu Apr 13 21:47:38 2017
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../game1/game1options.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'game1options.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Game1Options[] = {

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
      14,   13,   13,   13, 0x0a,
      39,   33,   13,   13, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_Game1Options[] = {
    "Game1Options\0\0gotoGameMainMenu()\0level\0"
    "gotoGame1(int)\0"
};

void Game1Options::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        Game1Options *_t = static_cast<Game1Options *>(_o);
        switch (_id) {
        case 0: _t->gotoGameMainMenu(); break;
        case 1: _t->gotoGame1((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData Game1Options::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject Game1Options::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_Game1Options,
      qt_meta_data_Game1Options, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Game1Options::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Game1Options::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Game1Options::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Game1Options))
        return static_cast<void*>(const_cast< Game1Options*>(this));
    return QWidget::qt_metacast(_clname);
}

int Game1Options::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
