#pragma once

#include <QComboBox>
#include <QWidget>
#include "customcomponent_global.h"

class DropDownList;
class QElapsedTimer;

class CUSTOMCOMPONENT_EXPORT ComboBox : public QComboBox
{
    Q_OBJECT

public:
    explicit ComboBox(QWidget *parent = 0);
    ~ComboBox();

    void setItemHidden(int index, bool bHidden);
    void useAsDigitalIOType();
    void useAsWobjType();
    void useAsToolType();
#if defined(Q_OS_LINUX)
    void setTranslatable(bool isTranslatable);

protected:
    void changeEvent(QEvent *event);
    // void focusInEvent(QFocusEvent *e);
    // void focusOutEvent(QFocusEvent *e);
public slots:
    void setCurrentIndex(int index);
    void setCurrentText(const QString &text);

private:
    int m_preIndex;
    bool m_isTranslatable;

public:
    void showPopup();
    void hidePopup();
    void hideAll();
    void addItem(const QString &text,
                 const QVariant &userData = QVariant());
    void addItem(const QIcon &icon, const QString &text,
                 const QVariant &userData = QVariant());
    void addItems(const QStringList &texts);

    void insertItem(int index, const QString &text,
                    const QVariant &userData = QVariant());
    void insertItem(int index, const QIcon &icon, const QString &text,
                    const QVariant &userData = QVariant());
    void insertItems(int index, const QStringList &texts);

    void setItemText(int index, const QString &text);

    int visiableCount();

public slots:
    void clear();
    void slot_itemClicked(QModelIndex modelIndex);

public:
    DropDownList *m_dropDownList;

    QElapsedTimer *m_showAntishakeTimer;
    QElapsedTimer *m_hideAntishakeTimer;
#elif defined(Q_OS_WIN)
    void showPopup();
    void hidePopup();

    void wheelEvent(QWheelEvent *e);

#endif
    void moveEvent(QMoveEvent *event);
};
