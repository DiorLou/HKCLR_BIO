#pragma once
#include "abstractwidget.h"
#include "logicexpresspropertysource.h"
#include "virtualkeyboard.h"
#include <QStack>

class QElapsedTimer;
class ComboBox;
class LogicExpressPropertySource;
class PromptCompletionTableModel;
class LineEditNoFocus;
class QTextEdit;
class QPlainTextEdit;
class QButtonGroup;
class QPushButton;
class QAbstractButton;
namespace Ui
{
class LogicalExpressionKeyboard;
}

class VIRTUALKEYBOARD_EXPORT LogicalExpressionKeyboard
    : public AbstractWidget<Ui::LogicalExpressionKeyboard>
{
    Q_OBJECT
    Q_PROPERTY(bool isHide MEMBER m_isHide)
public:
    enum KeyType {
        DecimalPointKey,

        PositiveOrNegative,
        OperatorKey,
        BackspaceKey,
        SpaceKey,
        PoseFunctionKey,
        PoseParaKey,

        DigitalKey,
        OperationLineEdit
    };

    enum IOTypeEnum {
        IO_Type_DI,
        IO_Type_DO,
        IO_Type_AI,
        IO_Type_AO
    };

    enum StateSynKind {
        Cursor,
        Selection
    };
    enum StateSynDirection {
        FromMainWidget_To_SoftKeyBoard,
        FromSoftKeyBoard_To_MainWidget
    };

    static LogicalExpressionKeyboard *instance();

    explicit LogicalExpressionKeyboard(QWidget *parent = 0);
    ~LogicalExpressionKeyboard();

    Q_INVOKABLE void setObjectFocusIn();

signals:
    void signal_funcKeyClicked(int key);

    void signal_expressionKeyClicked(int keyType, QString expression);

public slots:
    void showKeyboard(
        QObject *focusObject,
        int inputPartHeight,
        int inputPartLeftTopGlobalCoordX,
        int inputPartLeftTopGlobalCoordY);

    bool hideKeyboard();

    void processWhenInput(InputTextExpressionItemType inputType, QString expression);

protected:
    virtual void retranslateUi();

private slots:
    void slot_btnClicked(QAbstractButton* button = nullptr, const QString& text = "");
    void slot_tableViewClicked(const QModelIndex &index);

    void slot_mainWidget_cursorPositionChanged();
    void slot_mainWidget_cursorPositionChanged2(int before, int after);

    void mainWidget_selectionChanged();
    void slot_mainWidget_textChanged();

    void setSoftKeyBoardEditSelect(int start, int end);
    void setSoftKeyBoardEditCursorPosition(int pos);

    void slotVariableTypeRegistered(const QString &type);
    void slotFunctionTypeRegistered(VariableParamsType functionType, const QString &name);



    void on_comboBox_funType_currentIndexChanged(int index);

private:
    void requireStateSyn(StateSynDirection, StateSynKind);

    void createSpecialText(const QString &comText, const QString &sizeType);

    bool getMainWidgetEditSelection(int &start, int &end);
    bool getMainWidgetEditCursorPos(int &pos);
    void getMainWidgetEditState(ExpressJudge &data);
    void setMainWidgetEditText(const QString &str);
    void setMainWidgetEditSelect(int start, int end);
    void setMainWidgetEditCursorPos(int pos);
    void setBothEdit(int m_lastInputState, ExpressJudge &data);
    void processMainWidget_cursorPositionChanged();
    void updateComboBoxState(bool isEnabled);

    bool eventFilter(QObject *obj, QEvent *event) override;
    void initKeyboard();

    void updateFunctionSelectComb();

public:
    bool m_isHide = true;
    LineEditNoFocus *m_edit;
#if defined(Q_OS_LINUX)
    QElapsedTimer *m_hideAllAntishakeTimer;
#endif

private:
    Ui::LogicalExpressionKeyboard *ui;

    LogicExpressPropertySource *m_dataSource;
    PromptCompletionTableModel *m_promptModel;

    int m_lastInputState = AllowInput;
    QString m_rawInputData;

    QVariant emptyAddress = QVariant::fromValue((QStringList *)0);
    ComponentType m_inputType = NoInputType;
    QLineEdit *m_lineEdit;
    QTextEdit *m_textEdit;
    QPlainTextEdit *m_plainTextEdit;

    QButtonGroup *m_allBtnGroup;
    QHash<QAbstractButton *, QString> m_hashSpecialBtnText;

    QStack<QPair<int, ExpressJudge>> m_stackUndo;
    QStack<QPair<int, ExpressJudge>> m_stackRedo;

    QMap<VariableParamsType, QStringList> functionMap;
};
