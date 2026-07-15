#ifndef LOGICALEXPRESSIONPARSER_H
#define LOGICALEXPRESSIONPARSER_H

#include <QObject>
#include <QString>
#include <QList>
#include <QSharedPointer>
#include <QMutex>
#include <QObject>
#include "virtualkeyboard_global.h"
#include "keyboard.h"

// 表达式元素类型枚举
enum class LogicalExpressionItemType {
    expression_type_mix = 0,       // 混合表达式
    expression_type_param,         // 参数（变量）
    expression_type_num,           // 数字
    expression_type_global,        // 全局变量/系统变量
    expression_type_function,      // 函数
    expression_type_symbol,        // 运算符/逻辑符
    expression_type_letter,        // 纯字符
    expression_type_brackets,      // 括号
    expression_type_unknown        // 未知类型
};

// 语法树节点结构体
struct LogicalExpressionItem {
    QString expression;               // 当前节点的表达式文本
    LogicalExpressionItemType type;   // 节点类型
    QString typeContext;              // 对应类型内容
    int start;                        // 在完整表达式中的起始位置
    int end;                          // 在完整表达式中的结束位置
    LogicalExpressionItem* parentItem = nullptr;  // 父节点
    QList<LogicalExpressionItem> childItemList;   // 子节点列表

    // 构造函数
    LogicalExpressionItem()
        : expression()
        , type(LogicalExpressionItemType::expression_type_unknown)
        , typeContext()
        , start(0)
        , end(0)
        , parentItem(nullptr)
        , childItemList()
    {}

    LogicalExpressionItem(QString exp, LogicalExpressionItemType t, QString context,
                          int s, int e, LogicalExpressionItem* parent = nullptr)
        : expression(exp), type(t), typeContext(context), start(s), end(e), parentItem(parent) {}

     // 添加子节点
    void addChild(const LogicalExpressionItem& item);

    // 查找包含指定位置的最近函数节点
    const LogicalExpressionItem* findFunctionAtPosition(int pos) const;

    // 生成树形结构字符串表示
    QString toTreeString(int indent = 0) const;

    // 获取节点类型的字符串表示
    QString typeToString() const;

     // 判断是否是叶子节点
    bool isLeaf() const { return childItemList.isEmpty(); }

     // 获取子节点数量
    int childCount() const { return childItemList.size(); }

private:

    // 判断节点是否包含指定位置
    bool containsPosition(int pos) const {
        return pos >= start && pos <= end;
    }

    // 检查函数节点的参数列表中是否有逗号在指定位置
    bool hasCommaAtPosition(int pos) const {
        if (type != LogicalExpressionItemType::expression_type_function) return false;

        for (const auto& child : childItemList) {
            if (child.type == LogicalExpressionItemType::expression_type_symbol &&
                child.typeContext == "," &&
                child.containsPosition(pos)) {
                return true;
            }
        }
        return false;
    }
public:
    const LogicalExpressionItem* findSmallestNodeAtPosition(int pos) const;

    const LogicalExpressionItem* findDeepestFunction(int pos) const;
};

class VIRTUALKEYBOARD_EXPORT LogicalExpressionParser : public QObject {
    Q_OBJECT
public:
    // 获取单例实例
    static LogicalExpressionParser& instance();

    // 设置注册函数列表
    void setRegisteredFunctions(const QStringList& functions);
     // 添加注册函数
    void addRegisteredFunction(const QString& function);

    void addRegisteredParam(const QString& param);
    void setRegisteredParams(const QStringList& params);

    void addRegisteredVariable(const QString &var);
    void setRegisteredVariable(const QStringList& vars);
                                                          // 生成树形结构字符串
    QString toTreeString(const QSharedPointer<LogicalExpressionItem>& root);

     // 解析表达式，返回语法树根节点
    QSharedPointer<LogicalExpressionItem> parseExpression(const QString& expression);

    /**
     * @brief 查找指定位置的节点
     * @param root 表达式树根节点（生命周期需覆盖返回值的使用周期）
     * @param pos 目标位置
     * @return 指向目标节点的原始指针（仅作引用，不管理内存，root析构后指针失效）
     */
   LogicalExpressionItem* findItemAtPosition(
        const QSharedPointer<LogicalExpressionItem>& root, int pos);

   /**
    * @brief 查找指定位置最深层的函数节点
    * @param root 表达式树根节点（生命周期需覆盖返回值的使用周期）
    * @param pos 目标位置
    * @return 指向目标节点的原始指针（仅作引用，不管理内存，root析构后指针失效）
    */
     LogicalExpressionItem* findFunctionAtPosition(
        const QSharedPointer<LogicalExpressionItem>& root, int pos);
    /**
     * @brief 查找指定位置的最小节点（最深层节点）
     * @param root 表达式树根节点（生命周期需覆盖返回值的使用周期）
     * @param pos 目标位置
     * @return 指向目标节点的原始指针（仅作引用，不管理内存，root析构后指针失效）
     */
     LogicalExpressionItem* findSmallestNodeAtPosition(
        const QSharedPointer<LogicalExpressionItem>& root, int pos) const;


private:
    // 私有构造函数
    explicit LogicalExpressionParser(QObject* parent = nullptr);
    // 禁用拷贝构造和赋值
    LogicalExpressionParser(const LogicalExpressionParser&) = delete;
    LogicalExpressionParser& operator=(const LogicalExpressionParser&) = delete;

private:

    // 内部解析器实现（递归下降解析）
    class LogicalExpressionParserInner;

private:
    
    struct LogicalExpressionSharedData {
        QStringList registeredFunctions;
        QStringList registeredParams;
        QStringList globalVariables;
    };
    QSharedPointer<const LogicalExpressionSharedData> m_itemMangerData;  // 共享不可变数据
    
};

#endif  // LOGICALEXPRESSIONPARSER_H
