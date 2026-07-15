#pragma once

#include <QLineEdit>
#include "cc_define/valuestructdefine.h"
#include "customcomponent_global.h"
#include <QKeyEvent>
class QRegularExpressionValidator;
class CUSTOMCOMPONENT_EXPORT LineEdit  : public QLineEdit
{
    Q_OBJECT
public:
    LineEdit(QWidget *parent = 0);
    LineEdit(const ValueLimit limit,QWidget *parent = 0);

    void setValueLimit(const ValueLimit &limit);

    void setValueMax(const QVariant &max);
    void setValueMin(const QVariant &min);
    void setRange(const QVariant &min, const QVariant &max);
    ValueType getValueType();

    void setValueMaxOpenOrClose(bool isClose);
    void setValueMinOpenOrClose(bool isClose);

    QVariant getValueMax();
    QVariant getValueMin();

    void setAutoResize(bool autoResize);
    void setMaxWidth(int maxWidth);
    void setMinWidth(int minWidth);

    void setShowDecimals(const unsigned int num);
    void setInputDecimals(const unsigned int num);
    void setShowAndInputDecimals(const unsigned int num);

    //setQVariant = setQVariantDirect
    void setQVariant(const QVariant &);
    void setQVariantWhenNotInEdit(const QVariant &);

    QVariant getQVariant();
    void setDefaultText(const QString &value);
    void triggerValueLimit();
    void setRegex(const QString &);

    void setBlockSignalsWhenValueLimit(bool);
    void setShowDoubleValueNoLimit(bool);

    void clear();

public Q_SLOTS:
    void setTextWhenNotInEdit(const QString &);

private:
    QRegularExpressionValidator * m_validator;
    ValueLimit m_valueLimit;
    bool isInitValueLimit = false;
    bool m_blockSignalsWhenValueLimit = true;
    bool m_showDoubleValueNoLimit{false};
protected:
    void focusInEvent(QFocusEvent *ev) override;
    void focusOutEvent(QFocusEvent *ev) override;
#ifdef Q_OS_WIN
    void keyPressEvent(QKeyEvent *event) override;
#endif

private Q_SLOTS:
    void slot_valueLimit(const QString &text);
signals:
    void focusIn();
    void focusOut();

private:
    void autoTransferEmptyValue();

    void resizeWidth(const QString &text);

private:
    void valueLimit(const QString &text);
    void setKeyBoardProperty();
    bool m_isInEdit = false;
    bool m_valueMaxIsClose = true;
    bool m_valueMinIsClose = true;
    QString m_defultValue = "";
    int count = 0;

    bool m_autoResize = false;
    int m_maxWidth = 200;
    int m_minWidth = 20;
};

class CUSTOMCOMPONENT_EXPORT PPointLineEdit : public LineEdit
{
    Q_OBJECT
public:
    PPointLineEdit(QWidget *parent = 0)
        :LineEdit(VALUE_LIMIT_POINT_P,parent)
    {
        ;
    }
};

class CUSTOMCOMPONENT_EXPORT JPPointLineEdit : public LineEdit
{
    Q_OBJECT
public:
    JPPointLineEdit(QWidget *parent = 0)
        :LineEdit(VALUE_LIMIT_POINT_JP,parent)
    {
        ;
    }
};

class CUSTOMCOMPONENT_EXPORT IntLineEdit : public LineEdit
{
    Q_OBJECT
public:
    IntLineEdit(QWidget *parent = 0)
        :LineEdit(VALUE_LIMIT_INT,parent)
    {
        ;
    }
};

class CUSTOMCOMPONENT_EXPORT UIntLineEdit : public LineEdit
{
    Q_OBJECT
public:
    UIntLineEdit(QWidget *parent = 0)
        :LineEdit(VALUE_LIMIT_UINT, parent)
    {
        ;
    }
};

class CUSTOMCOMPONENT_EXPORT UcharLineEdit : public LineEdit
{
    Q_OBJECT
public:
    UcharLineEdit(QWidget *parent = 0)
        :LineEdit(VALUE_LIMIT_UCHAR,parent)
    {
        ;
    }
};

class CUSTOMCOMPONENT_EXPORT BoolLineEdit : public LineEdit
{
    Q_OBJECT
public:
    BoolLineEdit(QWidget *parent = 0)
        :LineEdit(VALUE_LIMIT_BOOL,parent)
    {
        ;
    }
};

class CUSTOMCOMPONENT_EXPORT DoubleLineEdit : public LineEdit
{
    Q_OBJECT
public:
    DoubleLineEdit(QWidget *parent = 0)
        :LineEdit(VALUE_LIMIT_DOUBLE,parent)
    {
        ;
    }
};

class CUSTOMCOMPONENT_EXPORT UDoubleLineEdit : public LineEdit
{
    Q_OBJECT
public:
    UDoubleLineEdit(QWidget *parent = 0)
        :LineEdit(VALUE_LIMIT_DOUBLE,parent)
    {
        setValueMin(0);
    }
};
