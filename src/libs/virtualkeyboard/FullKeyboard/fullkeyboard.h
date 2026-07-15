#pragma once

#include "abstractwidget.h"
#include "virtualkeyboard_global.h"
#include "virtualkeyboard.h"
namespace Ui
{
class FullKeyboard;
}
class PromptCompletionTableModel;
class QLineEdit;
class QTextEdit;
class QPlainTextEdit;

class VIRTUALKEYBOARD_EXPORT FullKeyboard : public AbstractWidget<Ui::FullKeyboard>
{
    Q_OBJECT

public:
    explicit FullKeyboard(QWidget *parent = 0);
    ~FullKeyboard();

signals:
    void signal_keyClicked(QString key);
    void signal_funcKeyClicked(int key);

public slots:
    void showKeyboard(
        QObject *focusObject,
        int inputPartHeight,
        int inputPartLeftTopGlobalCoordX,
        int inputPartLeftTopGlobalCoordY);

    bool hideKeyboard();

    void showKeyboardWithCompletion(
        QObject *focusObject, int inputPartHeight,
        int inputPartLeftTopGlobalCoordX,
        int inputPartLeftTopGlobalCoordY);
    void slot_propertyChanged(QObject *object);

protected:
    virtual void retranslateUi();

private slots:
    void on_pbn_capsLock_clicked(bool checked);

    void on_pbn_leftShift_clicked(bool checked);

    void on_pbn_rightShift_clicked(bool checked);

    void slot_keyClicked();

    void slot_keyClickedNoShift();

    void on_pbn_cancel_clicked();

    void on_pbn_clear_clicked();

    void on_pbn_backspace_clicked();

    void on_pbn_enter_clicked();

    void on_pbn_space_clicked();

    void on_pbn_left_clicked();

    void on_pbn_right_clicked();

    void on_pbn_table_clicked();

    void on_pbn_ok_clicked();

    void slot_textEdited(const QString &str);
    void slot_textChanged();
    void slot_tableViewClicked(const QModelIndex &index);

private:
    Ui::FullKeyboard *ui;

    void capsLockEnable(bool enable);

    QSet<QString>* m_currentDataSource = 0;
    PromptCompletionTableModel* m_promptModel = 0;
    ComponentType m_inputType = NoInputType;//NoInputType
    QLineEdit *m_lineEdit;
    QTextEdit *m_textEdit;
    QPlainTextEdit *m_plainTextEdit;

};
