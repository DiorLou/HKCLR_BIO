#pragma once

#include <QObject>
#include "metatype.h"
#include "virtualkeyboard_global.h"
QT_BEGIN_NAMESPACE

enum ComponentType {
    NoInputType,
    LineEdit,
    TextEdit,
    PlainTextEdit
};

class QLineEdit;
class QTextEdit;
class QPlainTextEdit;
class DigitalKeyboard;
class FullKeyboard;
class LogicalExpressionKeyboard;
class QMouseEvent;
class frmInput;

class VIRTUALKEYBOARD_EXPORT VirtualKeyboard : public QObject
{
    Q_OBJECT
public:
    static VirtualKeyboard *instance();
    VirtualKeyboard();

    void setFocusObject(QObject *object);
    void showInputPanel();
    bool hideInputPanel();

    static void showKeyboard(
        QWidget *widget,
        int inputPartHeight,
        int inputPartLeftTopGlobalCoordX, int inputPartLeftTopGlobalCoordY);

    bool isVisible();

    // bool isAccepMouseEvent(QMouseEvent *event);
Q_SIGNALS:
    void signal_propertyChanged(QObject *object);

private slots:
    void slot_keyClicked(QString key);
    void slot_funcKeyClicked(int key);

    void focusChangedSlot(QWidget *old, QWidget *now);

private:
    QString getText();
    QString getCursorText();
    void setText(QString text);
    int getCursorPosition();
    void setCursorPosition(int cursorPosition);

    DigitalKeyboard *m_digitalKeyboard;
    FullKeyboard *m_fullKeyboard;
    LogicalExpressionKeyboard *m_logicalExpressionKeyboard;

    QString m_rawInputData;
    QLineEdit *m_lineEdit;
    QTextEdit *m_textEdit;
    QPlainTextEdit *m_plainTextEdit;
    ComponentType m_inputType = NoInputType;

    InputMethodType m_inputMethodType;

    QObject *m_focusObject;

    // LogicalExpressionKeyboard func
public:
    enum KeyType {
        DecimalPointKey,
        DigitalKey,
        PositiveOrNegative,
        OperatorKey,
        BackspaceKey,
        SpaceKey,
        PoseFunctionKey,
        PoseParaKey,
        FunKey,
    };

    enum CursorPosition {
        NoneExpression,
        DigitalLeft,
        DigitalMiddle,
        DigitalRight,
        NonDigitalLeft,
        NonDigitalMiddle,
        NonDigitalRight,
        FunctionPos,
        ParaFunctionPos,
        ParaPos
    };

#if defined(Q_OS_LINUX)
    bool m_isFocusSwitch;
#endif

private slots:
    void slot_expressionKeyClicked(int keyType, QString expression);

private:
    void updateCurExpItem();

    int m_leftPosition;
    int m_rightPosition;
    QString m_expItem;
    int m_itemSize;
    CursorPosition m_cursorPosition;

    QSet<QString> m_firstPresixString;
    QSet<QString> m_secondPresixString;
};


QT_END_NAMESPACE
