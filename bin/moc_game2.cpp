/****************************************************************************
** Meta object code from reading C++ file 'game2.h'
**
** Created: Thu Apr 13 22:22:05 2017
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../game2/game2.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'game2.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Game2[] = {

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
       7,    6,    6,    6, 0x0a,
      22,    6,    6,    6, 0x0a,
      32,    6,    6,    6, 0x0a,
      41,    6,    6,    6, 0x0a,
      52,   48,    6,    6, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_Game2[] = {
    "Game2\0\0goToMainMenu()\0endGame()\0"
    "replay()\0save()\0bar\0closeEvent(QCloseEvent*)\0"
};

void Game2::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        Game2 *_t = static_cast<Game2 *>(_o);
        switch (_id) {
        case 0: _t->goToMainMenu(); break;
        case 1: _t->endGame(); break;
        case 2: _t->replay(); break;
        case 3: _t->save(); break;
        case 4: _t->closeEvent((*reinterpret_cast< QCloseEvent*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData Game2::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject Game2::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_Game2,
      qt_meta_data_Game2, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Game2::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Game2::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Game2::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Game2))
        return static_cast<void*>(const_cast< Game2*>(this));
    return QWidget::qt_metacast(_clname);
}

int Game2::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
