#pragma once
#include "core_global.h"
//#include "pointdata.h"
#include <QObject>
#include "metatype.h"

class DoubleLineEdit;
class LineEdit;
class QLabel;
class QPushButton;
class RoadPoint;
#ifdef INOCOBOTTP_MSVC_QT5
struct InoJPos;
    #else
class InoJPos;
    #endif
class CORE_EXPORT EditGroupManager : public QObject
{
    Q_OBJECT
public:
    //只针对label
    enum EditManagerTextFormat {
        None,                //是多少显示多少 小数位数受DecimalNum限制
        ScientificNotation,  //科学计数法 小数位数受DecimalNum限制
    };
    enum EditManagerShowType {
        INT,
        DOUBLE,
    };
    explicit EditGroupManager(QList<LineEdit *> editGroup, QObject *parent = nullptr);

    void setLabelRangeGroup(QList<QLabel *> labelGroup);
    void setbtnGroup(QList<QPushButton *> btnGroup);

    void setLabelShowType(EditManagerShowType type);
    void setLabelShowFormat(EditManagerTextFormat type);
    void setLabelSpecialShowContentWhenReachLimit(double min = DOUBLE_MIN_VALUE_WHEN_EMPTY_NODE,
                                                  double max = DOUBLE_MAX_VALUE_WHEN_EMPTY_NODE,
                                                  QString showStrWhenReachPositiveLimit = "∞",
                                                  QString showStrWhenReachNegitaveLimit = "-∞");

    void setLabelShowDecimals(unsigned int num);
    void setEditInputDecimals(unsigned int num);
    void setShowAndInputDecimals(unsigned int num);
    void setEditEnabled(const bool isEnable, const unsigned int start = 0, const int count = -1);
    void clearEditText();

    QList<double> getEditDoubleValue();
    //注意 如果输入是double获取是int 会进行四舍五入
    QList<int> getEditIntValueByRound();
    //注意 如果输入是double获取是int 会进行整数截断
    QList<int> getEditIntValueByTruncation();

    void getInoJPos(InoJPos *data, unsigned int JNum = 6, unsigned int ENum = 6);

    void setRoadPoint(const RoadPoint *data);
    void setInoJPos(const InoJPos *data, unsigned int JEditNum = 6, unsigned int EEditNum = 6);
    // QString是多少显示多少 不额外处理 但是受正则限制
    void setEditValue(const QList<QString> &value);
    void setEditValueLimit(const QList<QString> &min,
                           const QList<QString> &max);
    void setEditValueLimit(const QList<QString> &value,
                           const QList<QString> &min,
                           const QList<QString> &max);

    void setEditValue(const QList<double> &value);
    void setEditValueLimit(const QList<double> &min,
                           const QList<double> &max);
    void setEditValueLimit(const QList<double> &value,
                           const QList<double> &min,
                           const QList<double> &max);

    void setEditValue(const QList<int> &value);
    void setEditValueLimit(const QList<int> &value,
                           const QList<int> &min,
                           const QList<int> &max);
    void setEditValueLimit(const QList<int> &min,
                           const QList<int> &max);

    void setEditValue(const QList<QVariant> &value);
    void setEditValueLimit(const QList<QVariant> &value,
                           const QList<QVariant> &min,
                           const QList<QVariant> &max);
    void setEditValueLimit(const QList<QVariant> &min,
                           const QList<QVariant> &max);

    void setLabelValueLimit(const QList<int> &min,
                            const QList<int> &max);

private:
    int m_labelShowDecimalNum = 3;
    int m_editInputDecimalNum = 3;
    QList<LineEdit *> m_editGroup;
    QList<QLabel *> m_labelRangeGroup;
    QList<QPushButton *> m_buttonGroup;
    //整数 小数
    EditManagerShowType m_lableShowType = DOUBLE;
    //显示格式
    EditManagerTextFormat m_lableShowFormat = None;

    QString m_showStrWhenReachPositiveLimit;
    QString m_showStrWhenReachNegitaveLimit;

    template <typename T1, typename T2>
    int getMinSize(QList<T1> l1, QList<T2> l2)
    {
        return l1.size() < l2.size() ? l1.size() : l2.size();
    }
    double m_min, m_max;
};
