#pragma once

#include <QListWidget>
#include "customcomponent_global.h"
class CUSTOMCOMPONENT_EXPORT DropDownList : public QListWidget
{
    Q_OBJECT

public:
    explicit DropDownList(QWidget *parent = 0);
    ~DropDownList();

    void rebuilt();
};
