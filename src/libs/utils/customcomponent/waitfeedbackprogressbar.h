#ifndef WAITFEEDBACKPROGRESSBAR_H
#define WAITFEEDBACKPROGRESSBAR_H

#include <QWidget>
#include <QTimer>
#include "customcomponent_global.h"

class CUSTOMCOMPONENT_EXPORT WaitFeedbackProgressBar : public QWidget
{
    Q_OBJECT
public:
    WaitFeedbackProgressBar(QWidget *parent = nullptr);
    ~WaitFeedbackProgressBar();

    void start();
    void stop();

protected:
    void paintEvent(QPaintEvent *event);

private slots:
    void updaterRotation();

private:
    QTimer *m_timer = nullptr;
    int m_rotation = 0;
};

#endif  // WAITFEEDBACKPROGRESSBAR_H
