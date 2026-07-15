#pragma once

#include <QObject>
#include <QRadioButton>
#include "customcomponent_global.h"

class CUSTOMCOMPONENT_EXPORT RadioButton : public QRadioButton
{
    Q_OBJECT
public:
    //explicit RadioButton(QWidget *parent = nullptr);
    explicit RadioButton(const QString &text, QWidget *parent = nullptr);
    explicit RadioButton(const QString &objectName,const QString &text, QWidget *parent = nullptr);
    ~RadioButton();
protected:
    void initialize();
signals:
};

