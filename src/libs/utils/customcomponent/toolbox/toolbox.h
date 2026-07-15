#pragma once
#include <QFrame>
#ifdef INOCOBOTTP_MSVC_QT5
    #include <QIcon>
#endif
#include "customcomponent_global.h"

class ToolBoxPrivate;

class CUSTOMCOMPONENT_EXPORT ToolBox : public QFrame
{
    Q_OBJECT
    Q_PROPERTY(int currentIndex READ currentIndex WRITE setCurrentIndex NOTIFY currentChanged)
    Q_PROPERTY(int count READ count)

public:
    explicit ToolBox(QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
    ~ToolBox();

    int addItem(QWidget *widget, const QString &text);
    int addItem(QWidget *widget, const QIcon &icon, const QString &text);
    int insertItem(int index, QWidget *widget, const QString &text);
    int insertItem(int index, QWidget *widget, const QIcon &icon, const QString &text);

    void removeItem(int index);

    void setItemEnabled(int index, bool enabled);
    bool isItemEnabled(int index) const;

    void setItemText(int index, const QString &text);
    QString itemText(int index) const;

    void setItemIcon(int index, const QIcon &icon);
    QIcon itemIcon(int index) const;

    void setItemButtonVisible(int index, QWidget *widget, bool visible);
    bool isItemButtonVisible(int index, QWidget *widget) const;

    int currentIndex() const;
    QWidget *currentWidget() const;
    QWidget *widget(int index) const;
    int indexOf(const QWidget *widget) const;
    int count() const;

public Q_SLOTS:
    void setCurrentIndex(int index);
    void setCurrentWidget(QWidget *widget);

Q_SIGNALS:
    void currentChanged(int index);

protected:
    bool event(QEvent *e) override;
    virtual void itemInserted(int index);
    virtual void itemRemoved(int index);
    void showEvent(QShowEvent *e) override;
    void changeEvent(QEvent *) override;

private:
    ToolBoxPrivate *d_ptr = Q_NULLPTR;
};


inline int ToolBox::addItem(QWidget *item, const QString &text)
{
    return insertItem(-1, item, QIcon(), text);
}

inline int ToolBox::addItem(QWidget *item, const QIcon &iconSet,
                            const QString &text)
{
    return insertItem(-1, item, iconSet, text);
}

inline int ToolBox::insertItem(int index, QWidget *item, const QString &text)
{
    return insertItem(index, item, QIcon(), text);
}
