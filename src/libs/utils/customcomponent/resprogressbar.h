#pragma once

#include <QWidget>
#include "customcomponent_global.h"

namespace Ui
{
class ResProgressBar;
}

class CUSTOMCOMPONENT_EXPORT ResProgressBar : public QWidget
{
    Q_OBJECT

public:
    explicit ResProgressBar(QWidget *parent = nullptr);
    ~ResProgressBar();

    void SetValue(double value);
    double GetValue() const;
    void SetMaxValue(double value);
    void SetMaxShow(bool bMaxShow);
    void SetTitle(const QString &title);

private:
    Ui::ResProgressBar *ui;

    QString m_title;
};
