#pragma once
#include <QAbstractButton>
#include <QStyleOption>
#include "customcomponent_global.h"

class CUSTOMCOMPONENT_EXPORT ToolBoxButton : public QAbstractButton
{
    Q_OBJECT
public:
    ToolBoxButton(QWidget *parent)
        : QAbstractButton(parent), selected(false), indexInPage(-1)
    {
        setBackgroundRole(QPalette::Window);
        setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
        setFocusPolicy(Qt::NoFocus);
    }

    virtual ~ToolBoxButton()
    {

    }

    inline void setSelected(bool b) { selected = b; update(); }
    inline void setIndex(int newIndex) { indexInPage = newIndex; }

    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;

protected:
    void initStyleOption(QStyleOptionToolBox *opt) const;
    void paintEvent(QPaintEvent *) override;

private:
    bool selected;
    int indexInPage;
};
