#ifndef STEPGUIDEBUTTON_H
#define STEPGUIDEBUTTON_H

#include <QWidget>
#include <QPaintEvent>

#include "customcomponent_global.h"

class CUSTOMCOMPONENT_EXPORT StepGuideButton : public QWidget
{
    Q_OBJECT
public:
    StepGuideButton(QWidget *parent = nullptr);

    void setTitles(const QStringList &titles);
    void setCurStep(int idx);

protected:
    void paintEvent(QPaintEvent *ev) override;

private:
    QStringList m_titles;
    int m_curIdx = 0;

    int m_nLinks = 0;
    int m_nSteps = 0;

    QBrush m_background = QColor(qRgb(241, 241, 245));
    QBrush m_highLight = QColor(qRgb(202, 219, 249));
    QColor m_text = Qt::black;
};

#endif // STEPGUIDEBUTTON_H
