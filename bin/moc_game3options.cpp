/****************************************************************************
** Meta object code from reading C++ file 'game3options.h'
**
** Created: Thu Apr 13 21:48:54 2017
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../game3/game3options.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'game3options.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Game3Options[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      14,   13,   13,   13, 0x0a,
      33,   13,   13,   13, 0x0a,
      44,   13,   13,   13, 0x0a,
      54,   13,   13,   13, 0x0a,
      68,   13,   13,   13, 0x0a,
      78,   13,   13,   13, 0x0a,
      92,   13,   13,   13, 0x0a,
     107,   13,   13,   13, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_Game3Options[] = {
    "Game3Options\0\0gotoGameMainMenu()\0"
    "gotoGame()\0setEasy()\0setModerate()\0"
    "setHard()\0setSizeFour()\0setSizeEight()\0"
    "setSizeSixteen()\0"
};

void Game3Options::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        Game3Options *_t = static_cast<Game3Options *>(_o);
        switch (_id) {
        case 0: _t->gotoGameMainMenu(); break;
        case 1: _t->gotoGame(); break;
        case 2: _t->setEasy(); break;
        case 3: _t->setModerate(); break;
        case 4: _t->setHard(); break;
        case 5: _t->setSizeFour(); break;
        case 6: _t->setSizeEight(); break;
        case 7: _t->setSizeSixteen(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData Game3Options::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject Game3Options::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_Game3Options,
      qt_meta_data_Game3Options, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Game3Options::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Game3Options::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Game3Options::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Game3Options))
        return static_cast<void*>(const_cast< Game3Options*>(this));
    return QWidget::qt_metacast(_clname);
}

int Game3Options::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
