#pragma once

#include "abstractwidget.h"
#include "metatype.h"
#include "dialog_global.h"
namespace Ui
{
class RobotInitForm;
}

class DIALOG_EXPORT RobotInitForm : public AbstractWidget<Ui::RobotInitForm>
{
    Q_OBJECT

public:
    static RobotInitForm *instance();

    explicit RobotInitForm(QWidget *parent = 0);
    ~RobotInitForm();

    Q_INVOKABLE void save();
    Q_INVOKABLE void startUp();

protected:
    virtual void retranslateUi();
    void showEvent(QShowEvent *event);

private slots:
    void on_pbn_save_clicked();
    void on_pbn_startUp_clicked();

    void on_cmb_toolName_currentIndexChanged(int index);

    void on_pbn_shutdown_clicked();

    void on_pbn_close_clicked();

    void on_pbn_logout_clicked();

    void slot_tool_GetItems_result(const QVector<QString> &items);

private:
    Ui::RobotInitForm *ui;

    void initUI();
};
