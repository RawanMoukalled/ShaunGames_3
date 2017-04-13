/****************************************************************************
** Meta object code from reading C++ file 'gameselection.h'
**
** Created: Thu Apr 13 21:48:06 2017
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../gui/gameselection.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'gameselection.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_GameSelection[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      15,   14,   14,   14, 0x0a,
      31,   14,   14,   14, 0x0a,
      42,   14,   14,   14, 0x0a,
      54,   14,   14,   14, 0x0a,
      66,   14,   14,   14, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_GameSelection[] = {
    "GameSelection\0\0goToMyAccount()\0"
    "goToMain()\0goToGame1()\0goToGame2()\0"
    "goToGame3()\0"
};

void GameSelection::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        GameSelection *_t = static_cast<GameSelection *>(_o);
        switch (_id) {
        case 0: _t->goToMyAccount(); break;
        case 1: _t->goToMain(); break;
        case 2: _t->goToGame1(); break;
        case 3: _t->goToGame2(); break;
        case 4: _t->goToGame3(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData GameSelection::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject GameSelection::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_GameSelection,
      qt_meta_data_GameSelection, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &GameSelection::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *GameSelection::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *GameSelection::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_GameSelection))
        return static_cast<void*>(const_cast< GameSelection*>(this));
    return QWidget::qt_metacast(_clname);
}

int GameSelection::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
