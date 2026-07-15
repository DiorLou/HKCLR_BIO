#pragma once

#include "customcomponent_global.h"
#include <QObject>
#include <QWidget>
#include <QTextEdit>

#define i2s(x) QString::number(x)

class QPropertyAnimation;

class CUSTOMCOMPONENT_EXPORT TextEditNoFocus : public QTextEdit
{
    Q_OBJECT
    Q_PROPERTY(double time READ getShowTime WRITE setShowTime)
public:
    explicit TextEditNoFocus(QWidget *parent = nullptr);

    void setCursorPosition(int pos);
    int cursorPosition();
    void setSelected(int start, int end);

public Q_SLOTS:
    double getShowTime();
    void setShowTime(double time);

protected:
    void paintEvent(QPaintEvent *ev) override;

    void contextMenuEvent(QContextMenuEvent *ev) override;

private:
    QPropertyAnimation *m_animation;
    double m_currentTime = 0;
};
