#ifndef LOGICALEXPRESSIONTYPEINFERRER_H
#define LOGICALEXPRESSIONTYPEINFERRER_H

#include <QObject>
#include "virtualkeyboard_global.h"
#include "keyboard.h"

// 类型检查错误信息
struct TypeCheckError {
    QString message;                      // 错误消息
    int start = 0;                        // 错误位置起点
    int end   = 0;                        // 错误位置终点
    QString functionName;                 // 相关函数名
    int paramIndex = -1;                  // 参数索引


   explicit TypeCheckError() = default;


    explicit TypeCheckError(const QString& msg)
        : message(msg)
    {}


    TypeCheckError(const QString& msg, int s, int e)
        : message(msg), start(s), end(e)
    {}

    TypeCheckError(const QString& msg, int s, int e, const QString& func, int paramIdx = -1)
        : message(msg), start(s), end(e), functionName(func), paramIndex(paramIdx)
    {}

    // QString toString() const {
    //     QString posStr = start >= 0 && end >= 0
    //                        ? QObject::tr(" position at:[%1-%2]").arg(start).arg(end)
    //                          : "";

    //     QString funcStr = !functionName.isEmpty()
    //                         ? QObject::tr(" in function '%1'").arg(functionName)
    //                           : "";

    //     QString paramStr = paramIndex >= 0
    //                          ? QObject::tr(" parameter %1").arg(paramIndex + 1)
    //                            : "";

    //     return message + posStr + funcStr + paramStr;
    // }

    QString toString() const {
        return QString("%1,%2%3%4")
            .arg(message)
            .arg(QObject::tr("the error position of the logical expression string is located at:[%1-%2]").arg(start).arg(end))
            .arg(functionName.isEmpty() ? "" : QObject::tr(" in function '%1'").arg(functionName))
            .arg(paramIndex >= 0 ? QObject::tr(" parameter %1").arg(paramIndex + 1) : "");
    }
};

Q_DECLARE_METATYPE(TypeCheckError)
Q_DECLARE_METATYPE(QList<TypeCheckError>)

struct LogicalExpressionItem;
class LogicExpressPropertySource;
class VIRTUALKEYBOARD_EXPORT logicalExpressionTypeInferrer : public QObject
{
    Q_OBJECT
public:
    explicit logicalExpressionTypeInferrer(QObject *parent = nullptr,
                                           const LogicExpressPropertySource* context = nullptr);
    // 推断表达式类型并收集错误信息
    VariableParamsType inferType(const LogicalExpressionItem& item,
                                 QList<TypeCheckError>& errors);

private:

    VariableParamsType inferNumberType(const LogicalExpressionItem& item);
    VariableParamsType inferFunctionType(const LogicalExpressionItem& item,
                                         QList<TypeCheckError>& errors);
    VariableParamsType inferSymbolType(const LogicalExpressionItem& item,
                                       QList<TypeCheckError>& errors);
    // 推断混合表达式类型
    VariableParamsType inferMixType(const LogicalExpressionItem& item,
                                    QList<TypeCheckError>& errors);

    // 处理逻辑混合表达式（and/or/not）
    VariableParamsType handleLogicalMix(const LogicalExpressionItem& item,
                                        QList<TypeCheckError>& errors);

    // 处理比较混合表达式（<, >, ==等）
    VariableParamsType handleComparisonMix(const LogicalExpressionItem& item,
                                           QList<TypeCheckError>& errors);

    // 处理算术混合表达式（+, -, *, /等）
    VariableParamsType handleArithmeticMix(const LogicalExpressionItem& item,
                                           QList<TypeCheckError>& errors);

    // 推断括号表达式类型
    VariableParamsType inferBracketsType(const LogicalExpressionItem& item,
                                         QList<TypeCheckError>& errors);


    VariableParamsType inferLetterType(const LogicalExpressionItem& item);



    bool isNonOperationalType(VariableParamsType type) const;


    void checkNonOperationalType(const LogicalExpressionItem& item,
                                 VariableParamsType type,
                                 QList<TypeCheckError>& errors);

    // 创建类型错误信息（重载版本）
    TypeCheckError createTypeError(const QString& message,
                                   const LogicalExpressionItem& item) const;

    TypeCheckError createTypeError(const QString& message,
                                   const LogicalExpressionItem& item,
                                   VariableParamsType expected,
                                   VariableParamsType actual) const;

    TypeCheckError createTypeError(const QString& message,
                                   const LogicalExpressionItem& item,
                                   const QString& funcName,
                                   int paramIndex = -1) const;

    QString typeToString(VariableParamsType type) const;

    bool isCompatible(VariableParamsType expected, VariableParamsType actual) const ;


private:
    const LogicExpressPropertySource* m_context = nullptr;  // 保存对上下文的引用
signals:
};

#endif  // LOGICALEXPRESSIONTYPEINFERRER_H
