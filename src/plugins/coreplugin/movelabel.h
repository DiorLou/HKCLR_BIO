#pragma once

#include <QObject>
#include <QLabel>

class MoveLabel : public QLabel
{
    Q_OBJECT
public:
    explicit MoveLabel(QWidget *parent);
    ~MoveLabel();
    bool m_isMove = false;
#ifdef PLATFORM_COBOT_TP_WINDOWS
protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *);

private:
    QPointF m_startPos;
#endif
};

