/****************************************************************************
** Meta object code from reading C++ file 'CHistoSortedView.h'
**
** Created: Fri 17. Jan 11:44:57 2014
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../CHistoSortedView.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'CHistoSortedView.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CHistoSortedView[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      18,   17,   17,   17, 0x0a,
      35,   17,   17,   17, 0x0a,
      50,   17,   17,   17, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_CHistoSortedView[] = {
    "CHistoSortedView\0\0slotChangePage()\0"
    "slotNextPage()\0slotPrevPage()\0"
};

void CHistoSortedView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        CHistoSortedView *_t = static_cast<CHistoSortedView *>(_o);
        switch (_id) {
        case 0: _t->slotChangePage(); break;
        case 1: _t->slotNextPage(); break;
        case 2: _t->slotPrevPage(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData CHistoSortedView::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject CHistoSortedView::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_CHistoSortedView,
      qt_meta_data_CHistoSortedView, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CHistoSortedView::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CHistoSortedView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CHistoSortedView::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CHistoSortedView))
        return static_cast<void*>(const_cast< CHistoSortedView*>(this));
    return QWidget::qt_metacast(_clname);
}

int CHistoSortedView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
