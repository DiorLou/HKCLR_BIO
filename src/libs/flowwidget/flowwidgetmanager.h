#pragma once
#include <QQueue>
#include <QObject>
#include "flowwidget_global.h"
class FlowWidget;
class QTimer;
class FLOWWIDGET_EXPORT FlowWidgetManager : public QObject
{
    Q_OBJECT
public:
    static FlowWidgetManager* instance();
    explicit FlowWidgetManager(QObject *parent = nullptr);
    ~FlowWidgetManager();
    void updateGeometry();
    void setMainWidgetShow(bool isSHow);
private:
    QList<FlowWidget*> m_listWidget;
    int m_currentShowCount = 0;
    int m_currentShowIndex = -1;
    void showOneFlowWidget(const QString& str, const int type);
    bool m_mainIsShow = false;
    // bool m_applicationIsActive = false;
    void hideAllFlowWidget();
signals:
};

