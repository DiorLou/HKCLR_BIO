// abstractwidget_impl.h
#ifndef ABSTRACTWIDGET_IMPL_H
#define ABSTRACTWIDGET_IMPL_H

#include "abstractwidget.h"

template <class UI>
AbstractWidget<UI>::AbstractWidget(QWidget *parent,
                                   const int &minimumWidth, const int &minimumHeight,
                                   const int maximumWidth, const int maximumHeight) :
    AbstractWidgetBase(parent, minimumWidth, minimumHeight,
                       maximumWidth, maximumHeight)
{
    ui = nullptr;
}

template <class UI>
AbstractWidget<UI>::~AbstractWidget()
{
    if (ui) {
        delete ui;
        ui = nullptr;
    }
}

template <class UI>
void AbstractWidget<UI>::setupUi(QWidget *widget)
{
    Q_UNUSED(widget);
}

#endif // ABSTRACTWIDGET_IMPL_H
