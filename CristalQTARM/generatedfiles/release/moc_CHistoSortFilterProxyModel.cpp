/****************************************************************************
** Meta object code from reading C++ file 'CHistoSortFilterProxyModel.h'
**
** Created: Fri 17. Jan 11:44:57 2014
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../CHistoSortFilterProxyModel.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'CHistoSortFilterProxyModel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CHistoSortFilterProxyModel[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      28,   27,   27,   27, 0x05,

 // slots: signature, parameters, type, tag, flags
      42,   27,   27,   27, 0x0a,
      57,   27,   27,   27, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_CHistoSortFilterProxyModel[] = {
    "CHistoSortFilterProxyModel\0\0pageChanged()\0"
    "slotNextPage()\0slotPrevPage()\0"
};

void CHistoSortFilterProxyModel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        CHistoSortFilterProxyModel *_t = static_cast<CHistoSortFilterProxyModel *>(_o);
        switch (_id) {
        case 0: _t->pageChanged(); break;
        case 1: _t->slotNextPage(); break;
        case 2: _t->slotPrevPage(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData CHistoSortFilterProxyModel::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject CHistoSortFilterProxyModel::staticMetaObject = {
    { &QSortFilterProxyModel::staticMetaObject, qt_meta_stringdata_CHistoSortFilterProxyModel,
      qt_meta_data_CHistoSortFilterProxyModel, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CHistoSortFilterProxyModel::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CHistoSortFilterProxyModel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CHistoSortFilterProxyModel::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CHistoSortFilterProxyModel))
        return static_cast<void*>(const_cast< CHistoSortFilterProxyModel*>(this));
    return QSortFilterProxyModel::qt_metacast(_clname);
}

int CHistoSortFilterProxyModel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QSortFilterProxyModel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void CHistoSortFilterProxyModel::pageChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
