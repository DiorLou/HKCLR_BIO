#pragma once

#include <QPushButton>
#include <QTimer>
#include "customcomponent_global.h"

class QLabel;

class CUSTOMCOMPONENT_EXPORT DebounceButton : public QPushButton
{
    Q_OBJECT

public:
    explicit DebounceButton(QWidget *parent = nullptr);

    void setButtonEnabled(bool isEnabled);

protected:
    void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;

private:
    bool m_isButtonEnabled = true;
};
