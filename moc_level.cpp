/****************************************************************************
** Meta object code from reading C++ file 'level.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "level.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'level.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Level[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: signature, parameters, type, tag, flags
      14,    7,    6,    6, 0x05,
      28,    6,    6,    6, 0x05,
      44,    6,    6,    6, 0x05,
      63,    6,    6,    6, 0x05,
      81,    6,    6,    6, 0x05,
      92,    6,    6,    6, 0x05,

 // slots: signature, parameters, type, tag, flags
     101,    6,    6,    6, 0x0a,
     122,    6,    6,    6, 0x0a,
     131,    6,    6,    6, 0x0a,
     144,    6,    6,    6, 0x0a,
     158,    6,    6,    6, 0x0a,
     171,    6,    6,    6, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_Level[] = {
    "Level\0\0points\0scoreDot(int)\0scoreGhost(int)\0"
    "ghostModeChanged()\0lifeDown(QString)\0"
    "gameOver()\0youWin()\0isIntersectReached()\0"
    "goBack()\0isDotEaten()\0switchPhase()\0"
    "playerDies()\0ghostScored()\0"
};

void Level::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        Level *_t = static_cast<Level *>(_o);
        switch (_id) {
        case 0: _t->scoreDot((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->scoreGhost((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->ghostModeChanged(); break;
        case 3: _t->lifeDown((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->gameOver(); break;
        case 5: _t->youWin(); break;
        case 6: _t->isIntersectReached(); break;
        case 7: _t->goBack(); break;
        case 8: _t->isDotEaten(); break;
        case 9: _t->switchPhase(); break;
        case 10: _t->playerDies(); break;
        case 11: _t->ghostScored(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData Level::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject Level::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Level,
      qt_meta_data_Level, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Level::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Level::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Level::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Level))
        return static_cast<void*>(const_cast< Level*>(this));
    return QObject::qt_metacast(_clname);
}

int Level::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    }
    return _id;
}

// SIGNAL 0
void Level::scoreDot(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Level::scoreGhost(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void Level::ghostModeChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void Level::lifeDown(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void Level::gameOver()
{
    QMetaObject::activate(this, &staticMetaObject, 4, 0);
}

// SIGNAL 5
void Level::youWin()
{
    QMetaObject::activate(this, &staticMetaObject, 5, 0);
}
QT_END_MOC_NAMESPACE
