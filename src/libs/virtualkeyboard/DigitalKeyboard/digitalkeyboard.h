#pragma once

#include "abstractwidget.h"
#include "virtualkeyboard.h"
#include "virtualkeyboard_global.h"
namespace Ui
{
class DigitalKeyboard;
}

class QPushButton;
class PromptCompletionTableModel;
class QLineEdit;
class QTextEdit;
class QPlainTextEdit;
class QAbstractButton;
class VIRTUALKEYBOARD_EXPORT DigitalKeyboard : public AbstractWidget<Ui::DigitalKeyboard>
{
    Q_OBJECT

public:
    explicit DigitalKeyboard(QWidget *parent = 0);
    ~DigitalKeyboard();

public slots:
    void showKeyboard(
        QObject *focusObject,
        int inputPartHeight,
        int inputPartLeftTopGlobalCoordX,
        int inputPartLeftTopGlobalCoordY);
    bool hideKeyboard();

protected:
    virtual void retranslateUi() override;

private slots:
    void on_btn_0_clicked();
    void on_btn_1_clicked();
    void on_btn_2_clicked();
    void on_btn_3_clicked();
    void on_btn_4_clicked();
    void on_btn_5_clicked();
    void on_btn_6_clicked();
    void on_btn_7_clicked();
    void on_btn_8_clicked();
    void on_btn_9_clicked();
    void on_btn_minus_clicked();
    void on_btn_decimalPoint_clicked();

    void on_btn_backspace_clicked();

    void on_btn_cancel_clicked();

    void on_btn_ok_clicked();

    void on_btn_clear_clicked();

    void slot_textEdited(const QString &str);
    void slot_textChanged();

    void slot_tableViewClicked(const QModelIndex &index);

    void on_btn_a_clicked();

    void on_btn_b_clicked();

    void on_btn_c_clicked();

    void on_btn_d_clicked();

    void on_btn_e_clicked();

    void on_btn_f_clicked();

    void on_btn_space_clicked();

signals:
    void signal_keyClicked(QString key);
    void signal_funcKeyClicked(int key);

private:
    bool m_isShow = false;
    QString m_lastInputStr;
    Ui::DigitalKeyboard *ui;
    PromptCompletionTableModel *m_promptModel;
    QSet<QString> *m_currentDataSource;
    ComponentType m_inputType = NoInputType;
    QLineEdit *m_lineEdit;
    QTextEdit *m_textEdit;
    QPlainTextEdit *m_plainTextEdit;
    QList<QPushButton*> m_allBtns;
    void noLogWhenEditPassWord(bool enableLog);
    bool m_enableLog = true;
    void widgetStragety(bool isShowHex,bool isShowTableView);
};
