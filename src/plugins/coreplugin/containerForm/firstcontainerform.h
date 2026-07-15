#pragma once
#include "abstractwidget.h"
#include "core_global.h"
#include "containformdefine.h"
class ToolBox;
class QRadioButton;
class QStackedWidget;

namespace Ui
{
class FirstContainerForm;
}

class CORE_EXPORT FirstContainerForm
    : public AbstractWidget<Ui::FirstContainerForm>
{
    Q_OBJECT

public:
    explicit FirstContainerForm(const ContainerFormMsg &msg);
    ~FirstContainerForm();
    virtual void initialize();
    void addDrawerPage(const int &drawerIndex, QWidget *drawerPage);

    void addPluginWidget(const int &drawerIndex,
                         const QString &pluginName,
                         QRadioButton *pbnPlugin, QWidget *widget, int thirdIndex = -1);
    void addPluginWidget(const int &drawerIndex,
                         const QString &pluginName,
                         QWidget *widget);
    void setToolBoxItemEnabled(const int &index,
                               const bool &enabled);
    void setToolBoxItemText(const int &index,
                            const QString &text);
    void setToolBoxButtonVisible(const int index, QRadioButton *pbnPlugin,
                                 bool visible);
    void setDefaultDrawerIndex(const int &drawerIndex);

    void setCurrentStackedWidget(const QString &pluginName);

    void setCurrentToolBoxWidget(const int &secondIndex);
    //获取当前索引
    QString getCurrentIndexText();

    friend class CorePlugin;
public slots:
    void slot_toolBox_itemClicked(int index);

protected:
    virtual void retranslateUi();

private:
    ContainerFormMsg m_containerFormMsg;
    Ui::FirstContainerForm *ui;
    int m_defaultDrawerIndex;
    QList<int> m_vectorCurrentToolBoxDrawIndex;
    QHash<int, int> m_mapDrawerIndexAndStackFormIndex;
    QHash<int, QWidget *> m_mapDrawerIndexAndDrawerPage;

    QHash<QString, int> m_mapPluginNameAndDrawerIndex;
    QHash<QString, int> m_mapPluginNameAndStackFormIndex;
    QHash<QString, QRadioButton *> m_mapPluginNameAndPluginPbn;

    QString m_firstPluginName;
    static QList<FirstContainerForm*> FirstContainerFormInstances();
};

class CORE_EXPORT Ui_FirstContainerForm
{
public:
    QHBoxLayout *mainLayout;
    QStackedWidget *stackedWidget;

    void setupUi(QWidget *MonitoringContainerForm);
    void retranslateUi(QWidget *MonitoringContainerForm);
};

namespace Ui
{
class CORE_EXPORT FirstContainerForm : public Ui_FirstContainerForm
{
};
}  // namespace Ui
