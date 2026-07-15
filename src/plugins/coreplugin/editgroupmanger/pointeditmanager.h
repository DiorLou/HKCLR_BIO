#pragma once
#include"core_global.h"
#include "pointdata.h"
#include <QObject>
class DoubleLineEdit;
class QLabel;
class QPushButton;
class RoadPoint;

//只针对label
enum EditManagerTextFormat{
    None,//无限制 是多少显示多少
    ScientificNotation,//超过值限制 显示科学计数法 小数位数受DecimalNum限制
    CustomSimpleStr//超过限制 显示特定的字符
};

class CORE_EXPORT PointEditManager : public QObject
{
    Q_OBJECT
public:
    explicit PointEditManager(QList<DoubleLineEdit*> editGroup,
                              QList<QLabel*> labelGroup = QList<QLabel*>(),
                              QList<QPushButton*> buttonGroup = QList<QPushButton*>(),
                              EditManagerTextFormat format = None,
                              double valueLimit = __DBL_MAX__,
                              QString showStrWhenReachLimit = "∞",
                              QObject *parent = nullptr);

    QList<double> getPointValue();
    InoJPos getPointValueStruct();
    void setPointValue(const QList<double> &value);
    void setPointValue(const RoadPoint *roadPoint);

    void setPointValue(const QList<double> &value,
                       const QList<double> &min,
                       const QList<double> &max);
    void setPointValue(const QList<double> &value,
                       const QList<int> &min,
                       const QList<int> &max);
    void setPointValue(const QList<QVariant> &value);
    void setPointValue(const QList<QVariant> &value,
                       const QList<QVariant> &min,
                       const QList<QVariant> &max);


    void setPointValue(const InoJPos &value);
    void setPointValue(const InoJPos &value,
                       const QList<double> &min,
                       const QList<double> &max);

    void setPointRange(const QList<double> &min,
                       const QList<double> &max);
    void setPointRange(const QList<QVariant> &min,
                       const QList<QVariant> &max);
    void setPointRange(const QList<int> &min,
                       const QList<int> &max);
    void setShowDecimals(unsigned int num);
    void setInputDecimals(unsigned int num);
    void setShowAndInputDecimals(unsigned int num);

    void setValueByCurrent();
    void setEnabled(bool isEnable);
    void setInitValue();
    void setCurrentValueBtnVisible(bool isVisible);

private slots:
    void slot_getCurJPointRes(QObject *obj,
                              int getCurrentPointJType,
                              bool isSucess,
                              InoJPos pos);
private:
    int m_decimalNum = 3;
    QList<DoubleLineEdit*> m_editGroup;
    QList<QLabel*> m_labelRangeGroup;
    QList<QPushButton*> m_buttonGroup;
    int m_textModel;
    QString m_showStrWhenReachLimit;
    double m_valueLimit;
signals:
};

