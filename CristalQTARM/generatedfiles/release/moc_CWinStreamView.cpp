/****************************************************************************
** Meta object code from reading C++ file 'CWinStreamView.h'
**
** Created: Fri 17. Jan 11:44:59 2014
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../CWinStreamView.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'CWinStreamView.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CWinStreamView[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      57,   16,   15,   15, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_CWinStreamView[] = {
    "CWinStreamView\0\0"
    "arg_numStream,arg_numMeasure,argnNumPage\0"
    "loadPage(int,int,int)\0"
};

void CWinStreamView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        CWinStreamView *_t = static_cast<CWinStreamView *>(_o);
        switch (_id) {
        case 0: _t->loadPage((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData CWinStreamView::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject CWinStreamView::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_CWinStreamView,
      qt_meta_data_CWinStreamView, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CWinStreamView::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CWinStreamView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CWinStreamView::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CWinStreamView))
        return static_cast<void*>(const_cast< CWinStreamView*>(this));
    return QWidget::qt_metacast(_clname);
}

int CWinStreamView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
