#pragma once

#include <QWidget>
#include "abstractwidget.h"
#include "firstcontainerform.h"
#include "containformdefine.h"

class QVBoxLayout;
class QRadioButton;
namespace Ui
{
class SecondContainerForm;
}

class CORE_EXPORT SecondContainerForm
    : public AbstractWidget<Ui::SecondContainerForm>
{
    Q_OBJECT

public:
    explicit SecondContainerForm(const ContainerFormMsg &msg,
                               FirstContainerForm *parent);
    ~SecondContainerForm();
    virtual void initialize();
    void addPluginPbn(const int &layoutIndex, QRadioButton *pbnPlugin);
    QString getCurrentThirdIndexText();
protected:
    virtual void retranslateUi();
    virtual void operationWhenShowOrHide(bool isSHow);

public:
    QList<int> m_listRadioBtnCurrentIndex;
    QList<QRadioButton*> m_listWidgetAddress;

private:
    Ui::SecondContainerForm *ui;
    ContainerFormMsg m_containerFormMsg;
    FirstContainerForm* m_parent_firstContainerForm;
};

class CORE_EXPORT Ui_SecondContainerForm
{
public:
    QWidget *page;
    QVBoxLayout *vLayout;

    void setupUi(QWidget *widget);
    void retranslateUi(QWidget *widget);
};

namespace Ui
{
class CORE_EXPORT SecondContainerForm : public Ui_SecondContainerForm
{
};
}  // namespace Ui
