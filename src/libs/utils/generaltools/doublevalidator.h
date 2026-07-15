#pragma once

#include "generaltools_global.h"
#include <QDoubleValidator>

class GENERALTOOLS_EXPORT DoubleValidator : public QDoubleValidator
{
    Q_OBJECT

public:
    DoubleValidator(
        double bottom, double top, int decimals = 0,
        QObject *parent = 0);
    ~DoubleValidator();

    virtual State validate(QString &str, int &i) const;
    virtual void fixup(QString &input) const;
};
