#pragma once

#include <QWidget>
#include "dialog_global.h"
namespace Ui
{
class GeneralCustomWidget;
}

class DIALOG_EXPORT GeneralCustomWidget : public QWidget
{
    Q_OBJECT

public:
    explicit GeneralCustomWidget(QWidget *parent = 0);

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *);

private:
    bool m_isMove;
    QPointF m_startPos;
};
