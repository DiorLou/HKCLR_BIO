#include "generalcustomwidget.h"
#include <QMouseEvent>
#include "instance.h"
#define MAX_PIX 0
GeneralCustomWidget::GeneralCustomWidget(QWidget *parent) :
    QWidget(parent)
{
    m_isMove = false;
}

void GeneralCustomWidget::mousePressEvent(QMouseEvent *event)
{
#ifdef INOCOBOTTP_MSVC_QT5
   m_startPos = QPointF(event->globalPos()) - QPointF(this->pos());
#else
    m_startPos = event->globalPosition() - this->pos();
#endif


    if (Qt::LeftButton == event->button())
        m_isMove = true;

    QWidget::mousePressEvent(event);
}

void GeneralCustomWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (m_isMove) {
        #ifdef INOCOBOTTP_MSVC_QT5
        QPointF move_pos = event->globalPos();
        #else
        QPointF move_pos = event->globalPosition();
        #endif
        int width = Instance::common()->property("actualAppWidth").value<int>();
        int height = Instance::common()->property("actualAppHeight").value<int>();
        int startX = Instance::common()->property("actualAppX").value<int>();
        int startY = Instance::common()->property("actualAppY").value<int>();
#ifdef PLATFORM_COBOT_TP_ANDROID
        height += 16;
#endif
        double x = move_pos.x() - m_startPos.x(), y = move_pos.y() - m_startPos.y();
        int tempx = startX + width + MAX_PIX - this->width();
        if (x < startX - MAX_PIX) {
            x = startX - MAX_PIX;
        } else if (x > tempx) {
            x = tempx;
        }
        int tempy = startY + height - this->height() + MAX_PIX;
        if (y < startY - MAX_PIX) {
            y = startY - MAX_PIX;
        } else if (y > tempy) {
            y = tempy;
        }
        move(x, y);
    }

    QWidget::mouseMoveEvent(event);
}

void GeneralCustomWidget::mouseReleaseEvent(QMouseEvent *event)
{
    m_isMove = false;

    QWidget::mouseReleaseEvent(event);
}
