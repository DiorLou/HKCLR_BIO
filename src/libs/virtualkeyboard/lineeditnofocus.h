#pragma once

#include <QObject>
#include <QWidget>
#include <QLineEdit>
#define i2s(x) QString::number(x)
class QPropertyAnimation;
class LineEditNoFocus : public QLineEdit
{
    Q_OBJECT
    Q_PROPERTY(double time READ getShowTime WRITE setShowTime)
public:
    explicit LineEditNoFocus(QWidget *parent = nullptr);

    void setCursorPosition(int pos);
    int cursorPosition();
public Q_SLOTS:
    void insterTextToCurrentCursor(const QString &text);
    void deleteTextFromCurrentCursor(int deleteCount);

    double getShowTime();
    void setShowTime(double time);
protected:
    void paintEvent(QPaintEvent *ev);
    QRectF obtainTextRectF(const QString &text);
private:
    QPropertyAnimation *m_animation;
    double m_currentTime = 0;

    int m_start_x = 5;
    int m_start_y = 15;
    int m_text_y = 3;
signals:
};

