#pragma once

#include <QPushButton>
#include <QStack>
#include "abstractwidget.h"
#include "dialog_global.h"
class QStackedWidget;
class Application;


typedef struct registDialogInfo
{
    int width;
    int height;
    QWidget *widget;
    bool isExit;

    registDialogInfo()
    {
        width = 0;
        height = 0;
        widget = nullptr;
        isExit = false;
    }
} registDialogInfo;
namespace Ui
{
class ModellessDialogContainerForm;
}

class DIALOG_EXPORT ModellessDialogContainerForm
    : public AbstractWidget<Ui::ModellessDialogContainerForm>
{
    Q_OBJECT
public:
    static ModellessDialogContainerForm *instance();

    explicit ModellessDialogContainerForm(QWidget *parent = 0);
    ~ModellessDialogContainerForm();

    void showDialog(const QString &name);

    bool isVisible() const;

    void registDialog(const QString &name,QWidget *widget,int width,int height, bool isExit = false);

    bool isExit(const QString &pluginName);

    QWidget* replacePluginWidget(const QString &pluginName, QWidget *newWidget);

protected:
    virtual void retranslateUi();

    void showEvent(QShowEvent *event) override;
    void hideEvent(QHideEvent *event) override;

    bool eventFilter(QObject *obj, QEvent *event) override;

    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private slots:
    void slot_FoucusChanged(QWidget *old, QWidget *now);

private:
    Ui::ModellessDialogContainerForm *ui;

    QMap<QString, registDialogInfo> m_mapDialogs;

    QPoint m_dragPos;
    bool m_isDragging = false;
};

class Ui_ModellessDialogContainerForm
{
public:
    QVBoxLayout *mainLayout;
    QWidget *widget_tools;
    QHBoxLayout *hLayout_tools;
    QPushButton *pbn_close;
    QStackedWidget *m_stackedWidget;

    void setupUi(QWidget *MonitoringContainerForm);
    void retranslateUi(QWidget *MonitoringContainerForm);
};

namespace Ui
{
class ModellessDialogContainerForm : public Ui_ModellessDialogContainerForm
{
};
}  // namespace Ui
