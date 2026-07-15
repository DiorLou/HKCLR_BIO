#include "pointeditform.h"
#include "ui_pointeditform.h"
#include "metatype.h"
#include "commandinfo.h"
#include "communicationengine.h"
#include "pointeditmanager.h"

PointEditForm::PointEditForm(QWidget *parent) :
    QWidget(parent),ui(new Ui::PointEditForm)
{
    ui->setupUi(this);

    m_editGroup.push_back(ui->edit_1);
    m_editGroup.push_back(ui->edit_2);
    m_editGroup.push_back(ui->edit_3);
    m_editGroup.push_back(ui->edit_4);
    m_editGroup.push_back(ui->edit_5);
    m_editGroup.push_back(ui->edit_6);
    m_labelRangeGroup.push_back(ui->label_range1);
    m_labelRangeGroup.push_back(ui->label_range2);
    m_labelRangeGroup.push_back(ui->label_range3);
    m_labelRangeGroup.push_back(ui->label_range4);
    m_labelRangeGroup.push_back(ui->label_range5);
    m_labelRangeGroup.push_back(ui->label_range6);
    m_buttonRangeGroup.push_back(ui->pbn_1);
    m_buttonRangeGroup.push_back(ui->pbn_2);
    m_buttonRangeGroup.push_back(ui->pbn_3);
    m_buttonRangeGroup.push_back(ui->pbn_4);
    m_buttonRangeGroup.push_back(ui->pbn_5);
    m_buttonRangeGroup.push_back(ui->pbn_6);

    m_pointEditManager = new EditGpoupManager(m_editGroup);
}

PointEditForm::~PointEditForm()
{
    delete ui;
}

QList<double> PointEditForm::getPointValue()
{
    return m_pointEditManager->getPointValue();
}

InoJPos PointEditForm::getPointValueStruct()
{
    return m_pointEditManager->getPointValueStruct();
}

void PointEditForm::setPointValue(const QList<double> &value)
{
    m_pointEditManager->setPointValue(value);
}

void PointEditForm::setPointValue(const QList<QVariant> &value)
{
    m_pointEditManager->setPointValue(value);
}

void PointEditForm::setPointValue(const QList<QVariant> &value,
                                  const QList<QVariant> &min,
                                  const QList<QVariant> &max)
{
    m_pointEditManager->setPointValue(value,min,max);
}

void PointEditForm::setPointValue(const QList<double> &value,
                                  const QList<double> &min,
                                  const QList<double> &max)
{
    m_pointEditManager->setPointValue(value,min,max);
}

void PointEditForm::setPointValue(const QList<double> &value,
                                  const QList<int> &min,
                                  const QList<int> &max)
{
    m_pointEditManager->setPointValue(value,min,max);
}

void PointEditForm::setPointValue(const InoJPos &value)
{
    m_pointEditManager->setPointValue(value);
}

void PointEditForm::setPointValue(const InoJPos &value,
                   const QList<double> &min,
                   const QList<double> &max)
{
    m_pointEditManager->setPointValue(value,min,max);
}

void PointEditForm::setPointRange(const QList<double> &min,
                                  const QList<double> &max)
{
    m_pointEditManager->setPointRange(min,max);
}

void PointEditForm::setPointRange(const QList<QVariant> &min,
                                  const QList<QVariant> &max)
{
    m_pointEditManager->setPointRange(min,max);
}

void PointEditForm::setShowDecimals(unsigned int num)
{
     m_pointEditManager->setShowDecimals(num);
}

void PointEditForm::setInputDecimals(unsigned int num)
{
     m_pointEditManager->setInputDecimals(num);
}

void PointEditForm::setShowAndInputDecimals(unsigned int num)
{
     m_pointEditManager->setShowAndInputDecimals(num);
}

void PointEditForm::setValueByCurrent()
{
    m_pointEditManager->setValueByCurrent();
}

void PointEditForm::setCurrentValueBtnVisible(bool isVisible)
{
    m_pointEditManager->setCurrentValueBtnVisible(isVisible);
}


void PointEditForm::setPointValue(const RoadPoint *roadPoint)
{
     m_pointEditManager->setPointValue(roadPoint);
}
