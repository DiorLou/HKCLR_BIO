#pragma once

#include <QWidget>
#include <QPushButton>
#include "customcomponent_global.h"

class QButtonGroup;

class CUSTOMCOMPONENT_EXPORT PairCheckableButton : public QWidget
{
    Q_OBJECT

public:
    explicit PairCheckableButton(QWidget *parent = nullptr);
    virtual ~PairCheckableButton();

    void setButtonText(const QStringList &texts);

Q_SIGNALS:
    void signal_leftButtonChecked(bool checked);

private slots:
    void slot_buttonToggled(QAbstractButton *button, bool checked);

private:
    QButtonGroup *m_pButtonGroup;

    QPushButton *m_pLeftCheckableButton;
    QPushButton *m_pRightCheckableButton;

};
