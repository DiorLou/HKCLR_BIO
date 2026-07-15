#pragma once

#include <QDialog>
#include <QVBoxLayout>
#include <QLabel>
#include <QTimer>
#include <QPainter>
#include "customcomponent_global.h"

class CUSTOMCOMPONENT_EXPORT RotatingProgressDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RotatingProgressDialog(int durationMs, const QString &message = "处理中...", QWidget *parent = nullptr);
    ~RotatingProgressDialog();

    void start();
    void stop();
    void setMessage(const QString &message);
    void setStatusMessage(const QString &message);
    void setTime(const int &time);

protected:
    void paintEvent(QPaintEvent *event) override;
    void showEvent(QShowEvent *event) override;

private slots:
    void updateAnimation();
    void checkTimeout();

private:
    void setupUI();

    QTimer *m_animationTimer;
    QTimer *m_timeoutTimer;
    int m_durationMs;
    int m_angle;
    QString m_message;
    QLabel *m_messageLabel;
    QLabel *m_statusLab;
    QWidget *m_parent;
};
