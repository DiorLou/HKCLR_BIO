#pragma once

#include <QLabel>
#include <QTimer>
#include "customcomponent_global.h"

class CUSTOMCOMPONENT_EXPORT ClickableLabel : public QLabel
{
    Q_OBJECT

public:
    explicit ClickableLabel(QWidget *parent = 0);
    virtual ~ClickableLabel();

    void setLimit(int nIntervalTime, int nMaxCount); // nIntervalTime 单位:秒

protected:
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;

Q_SIGNALS:
    void signal_Clicked();

private:
    QTimer *m_timer;
    int m_nIntervalTime ; // s
    int m_nMaxCount;
    int m_nClickCount;
};
