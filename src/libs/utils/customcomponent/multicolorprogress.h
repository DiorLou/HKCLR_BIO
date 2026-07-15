#ifndef MULTICOLORPROGRESS_H
#define MULTICOLORPROGRESS_H

#include <QWidget>

class MultiColorProgress : public QWidget
{
    Q_OBJECT
public:
    explicit MultiColorProgress(QWidget *parent = nullptr);

    void setCurValuePair(QPair<double, QColor> value);
    void setMaxValue(double value);
    void setMaxShow(bool bMaxShow);

protected:
    void paintEvent(QPaintEvent *event);

signals:

private:
    QPair<double, QColor> m_curValue {0, qRgb(39, 182, 123)};
    QPair<double, QColor> m_maxValue {100, qRgb(41, 90, 176)};
    QPair<double, QColor> m_totalValue {150, "#00000000"};
    bool m_bMaxShow = true;
};

#endif  // MULTICOLORPROGRESS_H
