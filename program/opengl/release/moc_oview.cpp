/****************************************************************************
** Meta object code from reading C++ file 'oview.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../oview.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'oview.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_OView[] = {

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
       6,   32,   37,   37, 0x0a,
      38,   32,   37,   37, 0x0a,
      65,   32,   37,   37, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_OView[] = {
    "OView\0GetTransParameter(float*)\0para\0"
    "\0GetExtendParameter(float*)\0"
    "GetRollParameter(float*)\0"
};

void OView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        OView *_t = static_cast<OView *>(_o);
        switch (_id) {
        case 0: _t->GetTransParameter((*reinterpret_cast< float*(*)>(_a[1]))); break;
        case 1: _t->GetExtendParameter((*reinterpret_cast< float*(*)>(_a[1]))); break;
        case 2: _t->GetRollParameter((*reinterpret_cast< float*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData OView::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject OView::staticMetaObject = {
    { &QGLWidget::staticMetaObject, qt_meta_stringdata_OView,
      qt_meta_data_OView, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &OView::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *OView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *OView::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_OView))
        return static_cast<void*>(const_cast< OView*>(this));
    return QGLWidget::qt_metacast(_clname);
}

int OView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGLWidget::qt_metacall(_c, _id, _a);
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
