#pragma once
#include <QProxyStyle>
#include <QStyleOptionTabWidgetFrame>
#include <QStylePainter>
#include <QTabWidget>
#include "customcomponent_global.h"
#include "resolutionutils.h"

const int TAB_ICON_TEXT_SPACE = 4;
const int SPACE_LINE_WIDTH = 1;

#ifdef Q_OS_WIN
    const int SPACE_LINE_HEIGHT = 40;
#else
    const int SPACE_LINE_HEIGHT = 32;
#endif

class CUSTOMCOMPONENT_EXPORT InoTabBar : public QTabBar {
public:
    InoTabBar(QWidget *parent = nullptr) : QTabBar(parent)
    {
    }

protected:
    void paintEvent(QPaintEvent *) override
    {
        QStylePainter painter(this);
        bool isEnabled = true;
        for (int index = 0; index < this->count(); ++index) {
            QStyleOptionTab opt;
            initStyleOption(&opt, index);

            painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);

            painter.save();
            if (opt.state & QStyle::State_Enabled) { // 可操作
                if (opt.state & QStyle::State_Selected) { // 选中状态
                    painter.setPen(QColor(255, 255, 255));
                    painter.fillRect(opt.rect, QColor(31, 68, 133));
#if defined(Q_OS_WIN) || (defined(Q_OS_LINUX) && !defined(Q_OS_ANDROID))
                } else if (opt.state & QStyle::State_MouseOver) { // 鼠标停留状态
                    painter.setPen(QColor(255, 255, 255));
                    painter.fillRect(opt.rect, QColor(33, 72, 141));
#endif
                } else { // 常态（默认）
                    painter.setPen(QColor(255, 255, 255));
                    painter.fillRect(opt.rect, QColor(41, 90, 176));
                }

                painter.setOpacity(1.0);
            } else { // 禁用状态
                painter.setPen(QColor(255, 255, 255, 153));
                painter.fillRect(opt.rect, QColor(84, 123, 192));

                painter.setOpacity(153.0/255.0);
            }

            int iconTextWidth = opt.iconSize.width()
                              + opt.fontMetrics.horizontalAdvance(opt.text)
                              + TAB_ICON_TEXT_SPACE;

            int x = (opt.rect.width() - iconTextWidth) / 2 + opt.rect.width() * index;
            QRect iconRect(x, (opt.rect.height() - opt.iconSize.height()) / 2,
                           opt.iconSize.width(), opt.iconSize.height());
            painter.drawPixmap(iconRect, opt.icon.pixmap(opt.iconSize));

            QRect textRect(iconRect.right() + TAB_ICON_TEXT_SPACE, 0,
                           opt.rect.width() * (index + 1) - iconRect.right() - TAB_ICON_TEXT_SPACE,
                           opt.rect.height());
            painter.drawText(textRect, Qt::AlignVCenter | Qt::AlignLeft, opt.text);
            painter.restore();

            if (index != this->count() - 1) {
                painter.save();
                painter.setPen(QColor(33, 72, 141));
                painter.drawLine(opt.rect.width() * (index + 1),
                                 opt.rect.y() + (opt.rect.height() - SPACE_LINE_HEIGHT) / 2,
                                 opt.rect.width() * (index + 1),
                                 opt.rect.y() + (opt.rect.height() + SPACE_LINE_HEIGHT) / 2);
                painter.restore();
            }
        }
    }
};

class CUSTOMCOMPONENT_EXPORT InoTabWidget : public QTabWidget
{
    Q_OBJECT
public:
    explicit InoTabWidget(QWidget *parent) : QTabWidget(parent)
    {
        this->setTabBar(new InoTabBar(this));
    }

protected:
    void paintEvent(QPaintEvent *) override
    {
        QStylePainter p(this);

        QStyleOptionTabWidgetFrame option;
        initStyleOption(&option);
        option.lineWidth = 0;
        option.rect = style()->subElementRect(QStyle::SE_TabWidgetTabPane, &option, this);
        p.drawPrimitive(QStyle::PE_FrameTabWidget, option);

        int index = tabBar()->currentIndex();
        QRect rect = tabBar()->tabRect(index);

        p.save();
        p.fillRect(QRect(option.rect.x(), rect.y(), option.rect.width(),
                         rect.y() + rect.height()),
                   QColor(41, 90, 176));
        p.restore();
    }
};
