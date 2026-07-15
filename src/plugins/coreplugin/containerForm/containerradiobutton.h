#pragma once
#include "core_global.h"
#include <QObject>
#include <QRadioButton>

class CORE_EXPORT ContainerRadioButton : public QRadioButton
{
    Q_OBJECT
public:
    //explicit RadioButton(QWidget *parent = nullptr);
    explicit ContainerRadioButton(const QString &text, QWidget *parent = nullptr);
    explicit ContainerRadioButton(const QString &objectName,const QString &text, QWidget *parent = nullptr);
    ~ContainerRadioButton();
protected:
    void initialize();
signals:
};

