#pragma once

#include <QPushButton>
#include "antishakebutton.h"

class QLabel;

class CUSTOMCOMPONENT_EXPORT ThreeStatusButton : public AntiShakeButton
{
    Q_OBJECT

public:
    explicit ThreeStatusButton(QWidget *parent = nullptr);

protected:
    void initStyleOption(QStyleOptionButton* pOption) const;
    void paintEvent(QPaintEvent* pPaintEvent);
};
