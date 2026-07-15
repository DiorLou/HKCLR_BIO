#pragma once

#include <QWidget>
#include <QTimer>
#include "customcomponent_global.h"

class CUSTOMCOMPONENT_EXPORT LoadingBar : public QWidget
{
    Q_OBJECT
public:
    explicit LoadingBar(QWidget* parent = nullptr);
    ~LoadingBar();

    // 设置进度宽
    void setLoadingWidth(int width);

    //设置环道线宽
    void setPipeWidth(int width);

    //设置环道颜色
    void setPipeColor(QColor staColor, QColor endColor,
                      double stop1, double stop2);
    // 背景色
    void setBgColor(QColor bgColor);

    // 文字
    void setShowText(const QString &text);

protected:
    void showEvent(QShowEvent *);
    void hideEvent(QHideEvent *);
    void paintEvent(QPaintEvent *);

private:
    void startProcessTimer();
    void stopProcessTimer();

    void startLoadingTimer();
    void stopLoadingTimer();

    void slot_waitTimeout();
    void slot_loadingTimeout();

private:
    QTimer *m_processTimer;     // 窗口执行定时器，超时自动隐藏
    QTimer *m_loadingTimer;     // 加载进度条刷新定时器

    QColor m_bgColor = QColor(255, 255, 255);
    QString m_showText;

    int m_loadingWidth = 20;
    int m_pipeWidth = 3;
    int m_staAng = 0;
    int m_endAng = 360;
    QColor m_staColor = QColor(255, 255, 255);
    QColor m_endColor = QColor(0, 0, 0);
    double m_stop1 = 0;
    double m_stop2 = 0;
};
