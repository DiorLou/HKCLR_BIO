#pragma once

#include <QPushButton>
#include "customcomponent_global.h"

class QLabel;

class CUSTOMCOMPONENT_EXPORT TipButton : public QPushButton
{
    Q_OBJECT

public:
    explicit TipButton(QWidget *parent = nullptr);
    virtual ~TipButton();

    void setIconText(const QString &iconPathName, const QString &text,
                     const QString &tip);

    void setButtonEnabled(bool enabled);

private:
    QLabel *m_iconLabel;
    QLabel *m_textLabel;
    QLabel *m_tipLabel;
};
