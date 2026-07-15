#pragma once

#include <QEvent>
#include <QWidget>
#include <QMap>
#include <QDebug>
#include <QLayout>
// #include <QTableWidget>
#include <QLineEdit>
#include <QListWidget>
#include <QHeaderView>
#include <QFocusEvent>
#include <QGuiApplication>
#include <QStylePainter>
#include <QWidget>
#include "resolutionutils.h"
#include "customcomponent_global.h"
#include "toolbox.h"

class AutoResizeOriginalData
{
public:
    QRect dataRect;
    int minimumWidth;
    int minimumHeight;
    int maximumWidth;
    int maximumHeight;
};

enum LayoutTypeEnum { GridLayout,
                      HBoxLayout,
                      VBoxLayout };

class AutoLayoutOriginalData
{
    void initAllComponents(QWidget *widget);

public:
    LayoutTypeEnum layoutType = GridLayout;
    int leftMargin = 0;
    int topMargin = 0;
    int rightMargin = 0;
    int bottomMargin = 0;
    int horSpacing = 0;
    int verSpacing = 0;
};

class CUSTOMCOMPONENT_EXPORT AbstractWidgetBase : public QWidget
{
public:
    AbstractWidgetBase(QWidget *parent,
                       const int &minimumWidth,
                       const int &minimumHeight,
                       int maximumWidth = -1,
                       int maximumHeight = -1);

    void initAllComponents(QWidget *parent);
    void processAfterInitUi(QWidget *parent);

    void onlySetFocusObjectAddress(QObject *obj);
    void setFocusObject(QObject *obj);
    void setObjectFocusIn();
    // #if defined(Q_OS_LINUX)
    QObject *focusObject() const;
    // #endif
    virtual void setFunctionEnabledList(const QVariant &params);

    bool m_showMenu = false;
    bool m_delayInit = false;
    ToolBox *m_toolBox = nullptr;

public slots:
    void hide();

protected:
    virtual void retranslateUi() = 0;
    virtual void changeEvent(QEvent *event);
    virtual void resizeEvent(QResizeEvent *ev);
    virtual void showEvent(QShowEvent *ev);
    virtual void hideEvent(QHideEvent *ev);
    virtual void operationWhenShowOrHide(bool isSHow);

protected:
    void setObjectFocusOut();
    void autoResize();

private:
    QObject *m_focusObject = nullptr;
    QMap<QWidget *, AutoResizeOriginalData> m_componentMap;
    QMap<QLayout *, AutoLayoutOriginalData> m_layoutMap;
    double m_horRatio;
    double m_verRatio;
    int m_minimumWidth;
    int m_minimumHeight;
    int m_maximumWidth;
    int m_maximumHeight;
};

#ifdef INOCOBOTTP_MSVC_QT5
template <class UI>
class AbstractWidget : public AbstractWidgetBase
{
public:
    AbstractWidget(QWidget *parent,
                   const int &minimumWidth = 1088, const int &minimumHeight = 648,
                   const int maximumWidth = -1, const int maximumHeight = -1);
    ~AbstractWidget();

    void setupUi(QWidget *widget);

    UI *ui;
};
#else
template <class UI>
class AbstractWidget : public AbstractWidgetBase
{
public:
    AbstractWidget(QWidget *parent,
                   const int &minimumWidth = 1088, const int &minimumHeight = 648,
                   const int maximumWidth = -1, const int maximumHeight = -1) :
        AbstractWidgetBase(parent, minimumWidth, minimumHeight,
                           maximumWidth, maximumHeight)
    {
        ui = new UI;
    }
    void setupUi(QWidget *widget)
    {
        ui->setupUi(widget);
        if(!m_delayInit)
            processAfterInitUi(widget);
    }
    UI *ui;
};
#endif

#ifdef INOCOBOTTP_MSVC_QT5
#include "abstractwidget_impl.h"
#endif
