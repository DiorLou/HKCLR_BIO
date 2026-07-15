#pragma once
#include <QAbstractButton>
#include <QScrollArea>
#include <QVBoxLayout>
#include "customcomponent_global.h"
#include "toolboxbutton.h"
#include "resolutionutils.h"

const int TOOLBOX_BUTTON_WIDTH = 184;
const int TOOLBOX_BUTTON_HEIGHT = 44;

class ToolBox;

class CUSTOMCOMPONENT_EXPORT ToolBoxPrivate : public QWidget
{
public:
    struct Page
    {
        ToolBoxButton *button;
        QScrollArea *sv;
        QWidget *widget;

        inline void setText(const QString &text) { button->setText(text); }
        inline void setIcon(const QIcon &is) { button->setIcon(is); }

        inline QString text() const { return button->text(); }
        inline QIcon icon() const { return button->icon(); }

        inline bool operator==(const Page& other) const
        {
            return widget == other.widget;
        }

        QWidget *pageWidget() const { return widget; }

        inline int itemCount()
        {
            int count = 0;
            if (widget) {
                this->findItem(widget, count);
            }

            return count;
        }

        void findItem(QWidget *widget, int &count)
        {
            QAbstractButton *button = qobject_cast<QAbstractButton*>(widget);
            if (button && button->property("itemVisible").toBool()) {
                ++count;
            }

            // 遍历所有子控件
            const QObjectList& children = widget->children();
            for (QObject* child : children) {
                QWidget* childWidget = qobject_cast<QWidget*>(child);
                if (childWidget) {
                    findItem(childWidget, count);  // 递归调用
                }
            }
        }

        void setSingleItemSelected(bool selected)
        {
            if (itemCount() != 1) {
                return;
            }

            if (widget) {
                this->setItemSelect(widget, selected);
            }
        }

        void setItemSelect(QWidget *widget, bool selected)
        {
            if (QAbstractButton *button = qobject_cast<QAbstractButton*>(widget)) {
                button->setChecked(selected);
            }

            // 遍历所有子控件
            const QObjectList& children = widget->children();
            for (QObject* child : children) {
                QWidget* childWidget = qobject_cast<QWidget*>(child);
                if (childWidget) {
                    setItemSelect(childWidget, selected);  // 递归调用
                }
            }
        }

        void setItemButtonVisible(QWidget *widget, bool visible)
        {
            if (QAbstractButton *button = qobject_cast<QAbstractButton*>(widget)) {
                button->setVisible(visible);
                button->setProperty("itemVisible", visible);
            }
        }

        bool isItemButtonVisible(QWidget *widget) const
        {
            bool visible = true;

            if (QAbstractButton *button = qobject_cast<QAbstractButton*>(widget)) {
                visible = button->isVisible();
            }

            return visible;
        }
    };

    typedef std::vector<std::unique_ptr<Page>> PageList;
    inline ToolBoxPrivate()
        : layout(nullptr)
        , currentPage(nullptr)
        , q_ptr(nullptr)
    {
    }
    void _q_buttonClicked();
    void _q_widgetDestroyed(QObject*);

    const Page *page(const QObject *widget) const;
    const Page *page(int index) const;
    Page *page(int index);

    void updateTabs();
    void relayout();
    void resizePage(Page *page);

    void setAdaptiveHeight(bool isAdaptive);
    bool isAdaptiveHeight() const;

    PageList pageList;
    QVBoxLayout *layout;
    Page *currentPage;
    bool m_isAdaptiveHeight = false;

    ToolBox* q_ptr;
};
