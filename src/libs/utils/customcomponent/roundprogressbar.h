#ifndef ROUNDPROGRESSBAR_H
#define ROUNDPROGRESSBAR_H

#include <QWidget>
#include <QColor>

#include "customcomponent_global.h"

class CUSTOMCOMPONENT_EXPORT RoundProgressBar : public QWidget
{
    Q_OBJECT
public:
    explicit RoundProgressBar(QWidget *parent = nullptr);

public:
    int GetValue() const;
    void SetValue(int value);
    void SetPixMap(const QPixmap &pixmap);
    void SetColor(const QColor &cDoing, const QColor &cDone,
                  const QColor &cAbort);
    void SetAbort(bool abort);
    void SetDone(bool bDone);

protected:
    void paintEvent(QPaintEvent *event) override;

signals:

private:
    int m_value = 0;            // 单位%
    QPixmap m_pixmap;
    QColor m_cDoing = Qt::blue;
    QColor m_cDone = Qt::green;
    QColor m_cAbort = Qt::red;
    bool m_bAbort = false;
    bool m_bDone = false;
};

#endif  // ROUNDPROGRESSBAR_H
