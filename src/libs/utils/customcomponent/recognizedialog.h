#pragma once
#include <QDialog>
#include <QLabel>
#include <QProgressBar>
#include <QPushButton>
#include <QVBoxLayout>
#include "customcomponent_global.h"

class CUSTOMCOMPONENT_EXPORT RecognizeDialog : public QDialog

{
    Q_OBJECT

public:

    enum RecognizeType : int {
        RecognizeType_Friction,
        RecognizeType_Backlash,
    };

    RecognizeDialog(RecognizeType type, QWidget *parent = nullptr);
    ~RecognizeDialog();

    void setTitleLabel(QString text);
    void setWorningLabel(QString text);

signals:
    void signal_StopRecognize(QObject *obj);
    void signal_ComfirmRecognize(QObject *obj);

private slots:
    // 终止辨识按钮点击槽函数，可在此添加业务逻辑
    // void onStopRecognize();

private:
    void initUI();    // 初始化界面布局
    void initStyle(); // 初始化样式表

    // 界面控件
    QLabel *m_titleLabel;
    QProgressBar *m_loadingBar;
    QWidget *m_warningWidget;
    QLabel *m_warningIconLabel;
    QLabel *m_warningTextLabel;
    QPushButton *m_stopBtn;
    QPushButton *m_comfirmBtn;

    QVBoxLayout *m_mainLayout;

    RecognizeType m_type;
};
