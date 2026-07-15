#pragma once

#include <QTextEdit>
#include "customcomponent_global.h"

class CUSTOMCOMPONENT_EXPORT TextEdit : public QTextEdit
{
    Q_OBJECT

public:
    explicit TextEdit(QWidget *parent = 0);
    virtual ~TextEdit();

    void setMaxLength(int nMaxLen);

protected:
    bool eventFilter(QObject *obj, QEvent *event) override;

public slots:
    void slot_checkMaxLength();

private:
    int m_nMaxLen;
};
