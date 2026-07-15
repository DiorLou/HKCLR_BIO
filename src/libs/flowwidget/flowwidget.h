#pragma once

#include "abstractwidget.h"


namespace Ui
{
class FlowWidget;
}
class QTimer ;
class QPropertyAnimation;
class FlowWidget : public AbstractWidget<Ui::FlowWidget>
{
    Q_OBJECT
    Q_PROPERTY(QRect releativeGeometry /*READ getReleativeGeometry*/ WRITE setReleativeGeometry)

public:
    explicit FlowWidget(QWidget *parent = 0);
    void setText(const int type, const QString &str);
    void startHideAnimation();
    void startShowAnimation();
    void startMoveAnimation(int x, int y);
    QPropertyAnimation *m_moveAnimation;
    void setReleativeGeometry(const QRect &rect);
    static void updateMainPos(int x, int y);
protected:
    virtual void retranslateUi() override;
    virtual void operationWhenShowOrHide(bool) override;
    Ui::FlowWidget *ui;
    QTimer *m_timer;

signals:
    void signals_hide();

};

