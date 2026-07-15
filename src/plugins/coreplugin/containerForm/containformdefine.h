#pragma once
#include "core_global.h"
#include <QString>
#include <QPoint>
#include <QSize>

const int TOOLBOX_SPACEING = 0;
const int FIRST_MAINLAYOUT_SPACEING = 8;

const QSize FIRST_CONTAINER_SIZE = QSize(1280, 650);

const int CONTAINER_RADIOBUTTON_WIDTH = 180;
const int CONTAINER_RADIOBUTTON_HEIGHT = 44;

const int THIRD_FORM_MINIMUM_WIDTH = 1088;
const int THIRD_FORM_MINIMUM_HEIGHT = 620;

struct CORE_EXPORT ContainerFormMsg
{
    QString objectName;
    QString showText;
    int index;
    QString showIcon;
    bool bNeedShow;

    ContainerFormMsg(const QString &objectName,
                     const QString &showText,
                     const int &index,
                     const QString &showIcon = QString(),
                     bool bNeedShow = true)
    {
        this->objectName = objectName;
        this->showText = showText;
        this->index = index;
        this->showIcon = showIcon;
        this->bNeedShow = bNeedShow;
    }
    ContainerFormMsg()
    {
        index = -1;
        bNeedShow = true;
    }
    ContainerFormMsg& operator = (const ContainerFormMsg &src)
    {
        objectName = src.objectName;
        showText = src.showText;
        index = src.index;
        bNeedShow = src.bNeedShow;
        showIcon = src.showIcon;
        return *this;
    }
};
