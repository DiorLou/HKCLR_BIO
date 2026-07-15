#pragma once

#include <QLabel>
#include <QTimer>
#include "customcomponent_global.h"

class CUSTOMCOMPONENT_EXPORT CCLabel : public QLabel
{
    Q_OBJECT

public:
    explicit CCLabel(QWidget *parent = 0);
    virtual ~CCLabel();

    void setLineHeight(double lineHeight);
public Q_SLOTS:
    void setText(const QString &text);

private:
    double m_lineHeight = 1;
    QString m_format;
};
