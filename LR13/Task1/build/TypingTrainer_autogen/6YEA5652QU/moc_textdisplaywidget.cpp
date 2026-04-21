/****************************************************************************
** Meta object code from reading C++ file 'textdisplaywidget.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../include/textdisplaywidget.h"
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'textdisplaywidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.4.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
namespace {
struct qt_meta_stringdata_TextDisplayWidget_t {
    uint offsetsAndSizes[22];
    char stringdata0[18];
    char stringdata1[15];
    char stringdata2[1];
    char stringdata3[8];
    char stringdata4[14];
    char stringdata5[11];
    char stringdata6[4];
    char stringdata7[15];
    char stringdata8[4];
    char stringdata9[11];
    char stringdata10[10];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_TextDisplayWidget_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_TextDisplayWidget_t qt_meta_stringdata_TextDisplayWidget = {
    {
        QT_MOC_LITERAL(0, 17),  // "TextDisplayWidget"
        QT_MOC_LITERAL(18, 14),  // "CharacterTyped"
        QT_MOC_LITERAL(33, 0),  // ""
        QT_MOC_LITERAL(34, 7),  // "correct"
        QT_MOC_LITERAL(42, 13),  // "TextCompleted"
        QT_MOC_LITERAL(56, 10),  // "WpmChanged"
        QT_MOC_LITERAL(67, 3),  // "wpm"
        QT_MOC_LITERAL(71, 14),  // "HandleKeyPress"
        QT_MOC_LITERAL(86, 3),  // "key"
        QT_MOC_LITERAL(90, 10),  // "StartTimer"
        QT_MOC_LITERAL(101, 9)   // "StopTimer"
    },
    "TextDisplayWidget",
    "CharacterTyped",
    "",
    "correct",
    "TextCompleted",
    "WpmChanged",
    "wpm",
    "HandleKeyPress",
    "key",
    "StartTimer",
    "StopTimer"
};
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_TextDisplayWidget[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   50,    2, 0x06,    1 /* Public */,
       4,    0,   53,    2, 0x06,    3 /* Public */,
       5,    1,   54,    2, 0x06,    4 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       7,    1,   57,    2, 0x0a,    6 /* Public */,
       9,    0,   60,    2, 0x0a,    8 /* Public */,
      10,    0,   61,    2, 0x0a,    9 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    6,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    8,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject TextDisplayWidget::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_TextDisplayWidget.offsetsAndSizes,
    qt_meta_data_TextDisplayWidget,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_TextDisplayWidget_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<TextDisplayWidget, std::true_type>,
        // method 'CharacterTyped'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'TextCompleted'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'WpmChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'HandleKeyPress'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'StartTimer'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'StopTimer'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void TextDisplayWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<TextDisplayWidget *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->CharacterTyped((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 1: _t->TextCompleted(); break;
        case 2: _t->WpmChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 3: _t->HandleKeyPress((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 4: _t->StartTimer(); break;
        case 5: _t->StopTimer(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (TextDisplayWidget::*)(bool );
            if (_t _q_method = &TextDisplayWidget::CharacterTyped; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (TextDisplayWidget::*)();
            if (_t _q_method = &TextDisplayWidget::TextCompleted; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (TextDisplayWidget::*)(int );
            if (_t _q_method = &TextDisplayWidget::WpmChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
    }
}

const QMetaObject *TextDisplayWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TextDisplayWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_TextDisplayWidget.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int TextDisplayWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void TextDisplayWidget::CharacterTyped(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void TextDisplayWidget::TextCompleted()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void TextDisplayWidget::WpmChanged(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
