#include "movelabel.h"
#include "instance.h"
#include <QMouseEvent>
#include "mainwidget.h"
#include "messagebox.h"
MainWidget *instance = 0;

MoveLabel::MoveLabel(QWidget *parent) :
    QLabel(parent)
#ifdef PLATFORM_COBOT_TP_WINDOWS
    ,
    m_isMove(false)
#endif
{
    instance = MainWidget::instance();
    setFocusPolicy(Qt::StrongFocus);
}

MoveLabel::~MoveLabel()
{
}
#ifdef PLATFORM_COBOT_TP_WINDOWS
void MoveLabel::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        QWidget *topLevel = window();
        if (topLevel) {
            // QWidget::move() restores a maximized window to its old normal
            // geometry.  Switch to normal state explicitly, but preserve the
            // current on-screen size so the window can still be dragged
            // without jumping back to the original design resolution.
            if (topLevel->isMaximized()) {
                m_reMaximizeOnRelease = true;
                const QSize maximizedSize = topLevel->size();
                const QPointF globalMousePos = event->globalPosition();
                const qreal horizontalRatio = topLevel->width() > 0
                    ? event->position().x() / topLevel->width()
                    : 0.5;
                const int titleOffsetY = qRound(event->position().y());

                topLevel->showNormal();
                topLevel->resize(maximizedSize);
                topLevel->move(
                    qRound(globalMousePos.x() - maximizedSize.width() * horizontalRatio),
                    qRound(globalMousePos.y() - titleOffsetY));
            }
            m_startPos = event->globalPosition() - topLevel->frameGeometry().topLeft();
            m_isMove = true;
            event->accept();
            return;
        }
    }
    QLabel::mousePressEvent(event);
}

void MoveLabel::mouseMoveEvent(QMouseEvent *event)
{
    if (m_isMove && (event->buttons() & Qt::LeftButton)) {
        QWidget *topLevel = window();
        if (topLevel) {
            topLevel->move((event->globalPosition() - m_startPos).toPoint());
            event->accept();
            return;
        }
    }
    QLabel::mouseMoveEvent(event);
}

void MoveLabel::mouseReleaseEvent(QMouseEvent *event)
{
    m_isMove = false;
    if (m_reMaximizeOnRelease) {
        m_reMaximizeOnRelease = false;
        if (QWidget *topLevel = window())
            topLevel->showMaximized();
    }
    QLabel::mouseReleaseEvent(event);
}
#endif
