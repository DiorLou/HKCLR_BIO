#include "containerradiobutton.h"
#include "resolutionutils.h"
#include "containformdefine.h"
ContainerRadioButton::ContainerRadioButton(const QString &text,QWidget *parent) : QRadioButton(text,parent)
{
    setObjectName("pbn_"+text);
    initialize();
}

ContainerRadioButton::ContainerRadioButton(const QString &objectName,const QString &text, QWidget *parent)
    : QRadioButton(text,parent)
{
    setObjectName(objectName);
    initialize();
}

void ContainerRadioButton::initialize()
{
    setFixedSize(ResolutionUtils::getRatioSize(CONTAINER_RADIOBUTTON_WIDTH,
                                              CONTAINER_RADIOBUTTON_HEIGHT));
}

ContainerRadioButton::~ContainerRadioButton()
{

}
