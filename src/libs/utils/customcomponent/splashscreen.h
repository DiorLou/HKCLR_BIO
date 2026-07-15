#pragma once
#include <QSplashScreen>
#include "customcomponent_global.h"

class QProgressBar;
class QLabel;

class CUSTOMCOMPONENT_EXPORT SplashScreen : public QSplashScreen
{
    Q_OBJECT
public:
    static SplashScreen *instance();

    explicit SplashScreen(QWidget *parent = nullptr);
    virtual ~SplashScreen();

    void showDialog();
    void hideDialog();

    void setinitAndDelayPluginSum(int sum);
    void setFinshCount(int count);
    void updateFinshCount();

protected:
    void showEvent(QShowEvent *event) Q_DECL_OVERRIDE;
    void hideEvent(QHideEvent *event) Q_DECL_OVERRIDE;

    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;

private:
    void initUi();

private:
    QProgressBar *m_progressBar;
    QLabel *m_pluginLoadInfo;

    int m_initAndDelayPluginSum = 0;
    int m_finshCount = 0;

};
