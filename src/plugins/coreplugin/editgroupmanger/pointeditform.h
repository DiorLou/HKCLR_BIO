#pragma once

#include <QWidget>
#include "pointdata.h"
#include "core_global.h"

namespace Ui
{
class PointEditForm;
}

class DoubleLineEdit;
class QLabel;
class PointEditManager;
class QPushButton;
class RoadPoint;
class CORE_EXPORT PointEditForm : public QWidget
{
    Q_OBJECT

public:
    explicit PointEditForm(QWidget *parent = nullptr);
    ~PointEditForm();
    QList<double> getPointValue();
    InoJPos getPointValueStruct();
    void setPointValue(const QList<double> &value);
    void setPointValue(const QList<double> &value,
                       const QList<double> &min,
                       const QList<double> &max);

    void setPointValue(const QList<QVariant> &value);
    void setPointValue(const QList<QVariant> &value,
                       const QList<QVariant> &min,
                       const QList<QVariant> &max);

    void setPointValue(const InoJPos &value);
    void setPointValue(const RoadPoint *roadPoint);
    void setPointValue(const InoJPos &value,
                       const QList<double> &min,
                       const QList<double> &max);

    void setPointRange(const QList<double> &min,
                       const QList<double> &max);
    void setPointRange(const QList<QVariant> &min,
                       const QList<QVariant> &max);
    void PointEditForm(const QList<double> &value,
                       const QList<int> &min,
                       const QList<int> &max)

    void setShowDecimals(unsigned int num);
    void setInputDecimals(unsigned int num);
    void setShowAndInputDecimals(unsigned int num);

    void setValueByCurrent();
    void setCurrentValueBtnVisible(bool isVisible);
private:
    Ui::PointEditForm *ui;
    QList<DoubleLineEdit *> m_editGroup;
    QList<QLabel *> m_labelRangeGroup;
    QList<QPushButton *> m_buttonRangeGroup;
    PointEditManager *m_pointEditManager;
};
