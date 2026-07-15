#pragma once
#include "labeldata.h"
#include <QObject>
#include <QString>
#include <QHash>
#include <QSet>
#include <QVariant>
#include "virtualkeyboard_global.h"
#define i2s(x) QString::number(x)

struct ExpressJudge {
    // in
    QString beforeAllExp = "";
    QString inputExp = "";
    int selectStart = 0;
    int selectLength = 0;
    int selectEnd = 0;
    int beforeCursorPos = 0;
    // out
    QSet<QString> *strSelectableAddress = 0;
    QString rangeStr;
    QString tableStr = "";
    QString afterAllExp = "";
    int afterCursorPos = 0;
    bool isChangeSelectIndex = false;
};

enum SelectedState {
    Selected_None = 0,
    Selected_NeedChange,
    Selected_Suitalbe_exp,
    Selected_Suitalbe_suffix,
    // Selected_NeedMore,
    // Selected_NeedLess,
};

enum InputState {
    NewCommond = 0,
    NeedMoveCursor = 1,
    ChangeSelected = 2,
    AllowInput = 3,
    ShouldNoOperation = 4,
    UnknownState = 5
};

const QString BACKSPACE_UID = "$$$$$$$$";
const QString CLEAR_UID = "!!!!!!!!";
const QString DELETE_CURRENT_UID = "@@@@@@@@";
const QString CHANGE_NUM_POSITIVE_UID = "&&&&&&&";
const QString MOVE_CURSOR_LEFT = "########";
const QString MOVE_CURSOR_RIGHT = "%%%%%%%%";

class QLineEdit;
class VIRTUALKEYBOARD_EXPORT LogicExpressPropertySource : public QObject
{
    Q_OBJECT
public:
    static LogicExpressPropertySource *Instance();
    LogicExpressPropertySource();
    ~LogicExpressPropertySource();
    bool getOriginCommand(QString prefix,
                          QVariant &address,
                          QString &rangeAns,
                          QString &showAns,
                          int &cursorPos);

    Q_INVOKABLE bool expressIsValid(const QString &express /*,bool *res = 0*/);

    QString getCommandByCurrentAndNewIndex(QString currentStr,
                                           QString index);

    bool obatinCommandTableIndexWithNoSign(QString currentStr,
                                           QString &index);

    bool obatinCommandTableIndexWithSign(QString currentStr,
                                         QString &prefix,
                                         QString &index);

    int currentSelectIsSuitable(ExpressJudge &data);

    InputState currentCursorIsAllowInput(ExpressJudge &data);

    bool getCursorExpPromoteMsg(ExpressJudge &data);

    void processExcessZero(int &pos,
                           QString &afterStr,
                           QString &tableStr);

    bool expIsValid(QString str);
    bool expIsSign(QString str);
    bool expIsNum(QString num);

    void getExpStartAndEnd(QString allText, int pos, int &start, int &end);

    Q_INVOKABLE void slot_refreshAllLabels(const QObject *obj,
                                           const QList<AllLabelType> typeList,
                                           const QList<QStringList> dataList);

    void registerVariableType(const QString &type,
                              const QString &VarLuaExp = "",
                              const VariableParamsType VarReturnType = VariableParamsType::var_type_int);

    void updateRegisteredVariables(const QString &type,const QSet<QString> &variableSet);

private slots:

    void slot_signalLabelChanged(const AllLabelType type,
                                 const QString oldLabel,
                                 const QString newLabel);

    void slot_refreshAllLabelsWhenProjectChanged();

private:
    QHash<QString, QSet<QString> *> m_hash_prefix_selectableRange;
    QHash<QString, QSet<QString> *> m_hash_prefix_labelSelectableRange;

    QSet<QString> m_set_exitBySigns;
    QHash<int, QString> m_hash_index_prefix;

    QHash<QString, QString> m_hash_prefix_newCommand;
    QHash<QString, QString> m_hash_prefix_rangeForHearder;

    QHash<QString, QString> m_hash_prefix_analysePre;
    // QSet<QString> m_set_canInputNumOnly;

    QStringList *m_addressEmptyQStringList = 0;
    QVariant m_variantEmptyQStringAddress = QVariant::fromValue(m_addressEmptyQStringList);
    QSet<QString> *m_set_qstring_empty = 0;
};
