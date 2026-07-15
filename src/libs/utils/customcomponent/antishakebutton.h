#pragma once

#include <QPushButton>
#include "customcomponent_global.h"

class QGraphicsOpacityEffect;

class CUSTOMCOMPONENT_EXPORT AntiShakeButton : public QPushButton
{
    Q_OBJECT

public:
    explicit AntiShakeButton(QWidget *parent = 0);

    int timeout() const;
    void setTimeout(int timeout);

    void startAnimation();

    void setMoveStopSlotDisable();

    QPointF getMousePos();
protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
protected slots:
    void slot_mousePressTimeout();
    void slot_robotMoveStop();

protected:
    QTimer *m_timer;
    QPointF *m_mousePos;
    int m_interval;

    void stopAnimation();
    QGraphicsOpacityEffect *m_pOpacityEffect = Q_NULLPTR;
    QTimer *m_pTimer = Q_NULLPTR;
    bool m_bStatus = true;
    float m_opacityVal = 1.0;
    int m_count = 0;

    bool m_bPressed = false;
    bool m_bReleaseBeforePress = false;
};
