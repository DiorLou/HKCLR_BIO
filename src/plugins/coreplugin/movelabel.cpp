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
    QLabel::mouseReleaseEvent(event);
}
#endif
