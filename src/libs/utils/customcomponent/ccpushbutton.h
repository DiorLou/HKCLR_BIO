#pragma once

#include <QRadioButton>
#include <QPushButton>
#include <QTimer>
#include "customcomponent_global.h"

class CUSTOMCOMPONENT_EXPORT CCPushButtonWhite : public QPushButton
{
    Q_OBJECT

public:
    explicit CCPushButtonWhite(QWidget *parent = 0);
    virtual ~CCPushButtonWhite();
};

class CUSTOMCOMPONENT_EXPORT CCPushButtonDark : public QPushButton
{
    Q_OBJECT

public:
    explicit CCPushButtonDark(QWidget *parent = 0);
    virtual ~CCPushButtonDark();
};


class CUSTOMCOMPONENT_EXPORT CCRadioButtonWithoutIndicator : public QRadioButton
{
    Q_OBJECT

public:
    explicit CCRadioButtonWithoutIndicator(QWidget *parent = 0);
    virtual ~CCRadioButtonWithoutIndicator();
};
