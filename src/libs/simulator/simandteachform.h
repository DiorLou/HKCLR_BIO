#pragma once
#include "abstractwidget.h"
#include "simulator_global.h"

class SimBaseForm;
class RoadPoint;
class SimContainerForm;
namespace Ui
{
class SimAndTeachForm;
}

class SIMULATOR_EXPORT SimAndTeachForm : public AbstractWidget<Ui::SimAndTeachForm>
{
    Q_OBJECT

public:
    explicit SimAndTeachForm(QWidget *parent = 0);
    ~SimAndTeachForm();
private:
    SimContainerForm *m_simulator;
    Ui::SimAndTeachForm * ui;
protected:
    void resizeEvent(QResizeEvent *ev);
    void retranslateUi();
};
