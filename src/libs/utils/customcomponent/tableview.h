#pragma once

#include <QTableView>
#include <QTouchEvent>
#include "customcomponent_global.h"

class CUSTOMCOMPONENT_EXPORT TableView : public QTableView
{
    Q_OBJECT
public:
    TableView(QWidget *parent = nullptr);

protected:
    bool event(QEvent *event) override;

    // signals:
    //     void doubleClicked(const QPoint &position);
signals:
    void tableViewHide();
protected:
    void hideEvent(QHideEvent *ev) override;
private:
    QPointF m_lastTouchPoint;
    int  m_lastTimeMs = -1;

};
