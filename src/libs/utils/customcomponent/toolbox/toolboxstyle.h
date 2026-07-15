#pragma once
#include <QPainter>
#include <QProxyStyle>
#include <QStyleOptionToolBox>
#include <QStyleOptionTab>
#include "customcomponent_global.h"

class CUSTOMCOMPONENT_EXPORT ToolBoxStyle : public QProxyStyle
{
    Q_OBJECT

public:
    explicit ToolBoxStyle(QStyle *style = 0) :
        QProxyStyle(style)
    {
    }

    ~ToolBoxStyle() {}

    void drawControl(ControlElement element, const QStyleOption *option,
                     QPainter *painter, const QWidget *widget = nullptr) const override
    {
        if (element == QStyle::CE_ToolBoxTabLabel) {
            const QStyleOptionToolBox *toolBoxOption
                = qstyleoption_cast<const QStyleOptionToolBox *>(option);
            if (toolBoxOption) {
                QIcon icon(":/components/image/components/toolbox/expand.svg");
                if (toolBoxOption->state & QStyle::State_Selected) {
                    icon = QIcon(":/components/image/components/toolbox/collapse.svg");
                }

                QSize iconSize = QSize(20, 20);
                painter->drawPixmap(
                    toolBoxOption->rect.right() - icon.actualSize(iconSize).width() - 12,
                    toolBoxOption->rect.center().y() - icon.actualSize(iconSize).height() / 2,
                    icon.pixmap(icon.actualSize(iconSize)));
            } else {
                QProxyStyle::drawControl(element, option, painter, widget);
            }
        }

        QProxyStyle::drawControl(element, option, painter, widget);
    }
};
