#pragma once

#include "utils_global.h"
#include <QLineEdit>

namespace Utils
{

class UTILS_EXPORT CompletingLineEdit : public QLineEdit
{
    Q_OBJECT

public:
    explicit CompletingLineEdit(QWidget *parent = 0);

protected:
    bool event(QEvent *e);
    void keyPressEvent(QKeyEvent *e);
};

}  // namespace Utils
