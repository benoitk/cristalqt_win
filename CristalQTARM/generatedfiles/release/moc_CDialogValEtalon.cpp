/****************************************************************************
** Meta object code from reading C++ file 'CDialogValEtalon.h'
**
** Created: Fri 17. Jan 11:45:03 2014
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../CDialogValEtalon.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'CDialogValEtalon.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CDialogValEtalon[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      18,   17,   17,   17, 0x0a,
      35,   17,   17,   17, 0x0a,
      50,   17,   17,   17, 0x0a,
      68,   17,   17,   17, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_CDialogValEtalon[] = {
    "CDialogValEtalon\0\0btValuePressed()\0"
    "valueChanged()\0btValuePressed2()\0"
    "valueChanged2()\0"
};

void CDialogValEtalon::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        CDialogValEtalon *_t = static_cast<CDialogValEtalon *>(_o);
        switch (_id) {
        case 0: _t->btValuePressed(); break;
        case 1: _t->valueChanged(); break;
        case 2: _t->btValuePressed2(); break;
        case 3: _t->valueChanged2(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData CDialogValEtalon::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject CDialogValEtalon::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_CDialogValEtalon,
      qt_meta_data_CDialogValEtalon, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CDialogValEtalon::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CDialogValEtalon::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CDialogValEtalon::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CDialogValEtalon))
        return static_cast<void*>(const_cast< CDialogValEtalon*>(this));
    return QDialog::qt_metacast(_clname);
}

int CDialogValEtalon::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
