#pragma once
#include "labeldata.h"
#include <QObject>
#include <QString>
#include <QHash>
#include <QSet>
#include <QVariant>
#include <QThreadStorage>
#include "virtualkeyboard_global.h"
#include "logicalexpressionparser.h"


#define i2s(x) QString::number(x)

struct ExpressJudge {
    // Input parameters
    QString beforeAllExp = "";              // Original full expression
    QString inputExp = "";                  // New input expression fragment
    int selectStart = 0;                    // Start position of the selected text
    int selectLength = 0;                   // Length of the selected text
    int selectEnd = 0;                      // End position of the selected text (= selectStart + selectLength)
    int beforeCursorPos = 0;                // Cursor position before processing

     // Output parameters
    QSet<QString> *strSelectableAddress = 0;// Pointer to a set of selectable strings (for intelligent suggestions)
    QString rangeStr;                       // Expression range string (may be used for display or validation)
    QString tableStr = "";                  // Tabular form of the expression (for structured display)
    QString afterAllExp = "";               // Full expression after processing
    int afterCursorPos = 0;                 // Cursor position after processing
    bool isChangeSelectIndex = false;       // Whether the selection area has been changed
};


// 参数信息结构
struct FunctionParameter {
    QString name;           				// 参数名称
    VariableParamsType type;          		// 参数类型
    QString defaultValue;  					// 默认值（可选）

    FunctionParameter(const QString& n, const VariableParamsType& t, const QString& d = "")
        : name(n), type(t), defaultValue(d) {}
};

// 函数元信息结构
struct FunctionMeta {
    QString name;                        // 函数名称
    VariableParamsType returnType;       // 返回值类型
    QString luaTransferFormat;           //lua 表达式类型
    QList<FunctionParameter> parameters; // 参数列表
    QString description;                 // 函数描述（可选）

    // 获取参数数量
    int paramCount() const {
        return parameters.size();
    }

    // 获取指定索引的参数类型
    VariableParamsType getParamType(int index) const {
        if (index >= 0 && index < parameters.size()) {
            return parameters[index].type;
        }
        return VariableParamsType::var_type_unknown;
    }
};



enum class InputTextExpressionItemType {
    other_logical_signal_type = 0,
    function_expression_type,
    local_param_type
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
struct TypeCheckError;
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

    Q_INVOKABLE bool expressIsValid(const QString &express ,QList<TypeCheckError>* errors = nullptr/*,bool *res = 0*/);

    QString getCommandByCurrentAndNewIndex(QString currentStr,
                                           QString index);

    bool obatinCommandTableIndexWithNoSign(QString currentStr,
                                           QString &index);

    /***
     *提取特殊远算符表达式的前缀和索引
     ***/
    bool obatinCommandTableIndexWithSign(QString currentStr,
                                         QString &prefix,
                                         QString &index);

    int currentSelectIsSuitable(ExpressJudge &data);

    InputState currentCursorIsAllowInput(InputTextExpressionItemType inputType,ExpressJudge &data);


    bool getCursorExpPromoteMsg(ExpressJudge &data);

    void processExcessZero(int &pos,
                           QString &afterStr,
                           QString &tableStr);

    bool expIsValid(QString str);
    bool expIsSign(QString str);
    bool expIsNum(QString num);

    /**
     * Finds the start and end positions of a new sub-expression within a given text.
     * 通过前后空格确定光标当前字符串的前后位置
     * This function searches for spaces in the text to determine the start and end
     * positions of the sub-expression surrounding the specified position. It is
     * primarily used to locate the boundaries of the current sub-expression based
     * on the cursor position.
     *
     * @param allText The complete text in which to search for the expression.
     * @param pos The position of cursor
     * @param start Reference to an integer variable to store the start position of the sub-expression.
     * @param end Reference to an integer variable to store the end position of the sub-expression.
     * @return void
     */
    void getExpStartAndEnd(QString allText, int pos, int &start, int &end);


    Q_INVOKABLE void slot_refreshAllLabels(const QObject *obj,
                                           const QList<AllLabelType> typeList,
                                           const QList<QStringList> dataList);


    // 获取函数元信息
    const FunctionMeta* getFunctionMeta(const QString& funcName) const;

    VariableParamsType getVariableType(const QString& varName) const;
    VariableParamsType getGlobalVariableType(const QString& varName) const;


    QString getVariableLuaExpression(const QString& varName);
    QString getFunctionLuaExpression(const QString& funcName);
    QStringList getFunctionNameList();
    VariableParamsType getExpressionResultType(const QString &express);



signals:
    void signalVariableTypeRegistered(const QString &type);
    void signalFunctionRegistered(VariableParamsType functionType, const QString& formattedFunction);

public:
    //outside register
    void registerVariableType(const QString &VarName,const QString &VarLuaExp = "",const VariableParamsType VarReturnType = VariableParamsType::var_type_int);

    void updateRegisteredVariables(const QString &type,const QSet<QString> &variableSet);

    void registerFunctionType(const QString& name,
                              VariableParamsType returnType,
                              const QString& luaExpression,
                              const QList<FunctionParameter>& params,
                              const QString& description = "");

private slots:

    void slot_signalLabelChanged(const AllLabelType type,
                                 const QString oldLabel,
                                 const QString newLabel);

    void slot_refreshAllLabelsWhenProjectChanged();

private:
    bool isFunctionExpresstion(const QString &exp);
    void parseFunctionExpresstion(const QString &exp,QString &name,QString &params);
    int  countFunctionParameters(const QString &params);
    bool containsRegisteredFunction(const QString& originalExpression, const QStringList& registeredFunctions);
    bool isCursorInFunction(const QString& originalExpression, int cursorPosition,QString& matchedFunctionName) const;
    bool isCursorOnFunctionName(const QString& originalExpression, int cursorPosition) const;
    bool isCursorOnParamName(const QString& originalExpression, int cursorPosition) const;
    bool isParameterInFunction(const QString& originalExpression, const QString& currentParam,int cursorPosition) const;
    int  findMatchingParenthesis(const QString& expression, int startPos) const;
    // 判断范围[start, end]是否在函数参数列表内
    bool isRangeInFunctionParams(const QString& expression, int start, int end) const;
    bool isRangeInFunction(const QString& originalExpression, int start, int end) const;
    QStringList extractFunctionSignatures(const QStringList& functionNames);
    QString formatFunctionString(const QString& funcName) const;

    void registerDefaultFunction();


    /**
     * 判断表达式是否包含注册的前缀模式或符号
     * @param expression 待检查的表达式
     * @param prefixHash 前缀到模式的映射
     * @param signList 符号列表
     * @return 包含任意模式或符号时返回true
     */
    bool containsPrefixPattern(const QString& expression,
                               const QHash<QString, QString>& prefixHash,
                               const QStringList& signList);

    //first check
    QList<TypeCheckError> checkExpression(const LogicalExpressionItem& root);

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


    QStringList m_signList;
    QStringList mRegisterFunction;
    QStringList mRegisterFunctionName;
    QStringList mRegisterParamName;

    QMap<QString,  FunctionMeta> m_metaData;
    QMap<QString, QPair<QString,VariableParamsType>> m_paramTypeMap;


    QThreadStorage<QString> mLastExpression;     // 线程局部存储表达式
    QThreadStorage<VariableParamsType> mExpLastType; // 线程局部存储结果类型

};


