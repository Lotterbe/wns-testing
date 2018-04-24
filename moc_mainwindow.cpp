/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[19];
    char stringdata0[167];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 7), // "actFunc"
QT_MOC_LITERAL(2, 19, 0), // ""
QT_MOC_LITERAL(3, 20, 8), // "QAction*"
QT_MOC_LITERAL(4, 29, 6), // "action"
QT_MOC_LITERAL(5, 36, 6), // "addRow"
QT_MOC_LITERAL(6, 43, 6), // "addTab"
QT_MOC_LITERAL(7, 50, 1), // "i"
QT_MOC_LITERAL(8, 52, 19), // "addTabButtonclicked"
QT_MOC_LITERAL(9, 72, 9), // "changeRow"
QT_MOC_LITERAL(10, 82, 8), // "clickAll"
QT_MOC_LITERAL(11, 91, 9), // "fillTable"
QT_MOC_LITERAL(12, 101, 8), // "fileName"
QT_MOC_LITERAL(13, 110, 8), // "loadFile"
QT_MOC_LITERAL(14, 119, 5), // "fName"
QT_MOC_LITERAL(15, 125, 9), // "removeRow"
QT_MOC_LITERAL(16, 135, 9), // "removeTab"
QT_MOC_LITERAL(17, 145, 8), // "saveFile"
QT_MOC_LITERAL(18, 154, 12) // "transmitData"

    },
    "MainWindow\0actFunc\0\0QAction*\0action\0"
    "addRow\0addTab\0i\0addTabButtonclicked\0"
    "changeRow\0clickAll\0fillTable\0fileName\0"
    "loadFile\0fName\0removeRow\0removeTab\0"
    "saveFile\0transmitData"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   84,    2, 0x0a /* Public */,
       5,    0,   87,    2, 0x0a /* Public */,
       6,    1,   88,    2, 0x0a /* Public */,
       8,    1,   91,    2, 0x0a /* Public */,
       9,    1,   94,    2, 0x0a /* Public */,
      10,    1,   97,    2, 0x0a /* Public */,
      11,    1,  100,    2, 0x0a /* Public */,
      13,    1,  103,    2, 0x0a /* Public */,
      13,    0,  106,    2, 0x2a /* Public | MethodCloned */,
      15,    0,  107,    2, 0x0a /* Public */,
      16,    1,  108,    2, 0x0a /* Public */,
      17,    1,  111,    2, 0x0a /* Public */,
      17,    0,  114,    2, 0x2a /* Public | MethodCloned */,
      18,    0,  115,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void, QMetaType::QString,   12,
    QMetaType::Void, QMetaType::QString,   14,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void, QMetaType::QString,   12,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->actFunc((*reinterpret_cast< QAction*(*)>(_a[1]))); break;
        case 1: _t->addRow(); break;
        case 2: _t->addTab((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->addTabButtonclicked((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->changeRow((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->clickAll((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->fillTable((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 7: _t->loadFile((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 8: _t->loadFile(); break;
        case 9: _t->removeRow(); break;
        case 10: _t->removeTab((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 11: _t->saveFile((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 12: _t->saveFile(); break;
        case 13: _t->transmitData(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAction* >(); break;
            }
            break;
        }
    }
}

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
