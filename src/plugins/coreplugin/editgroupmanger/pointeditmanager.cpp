#include "pointeditmanager.h"
#include "communicationengine.h"
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include "cc_lineedit/lineedit.h"
#include "roadpoint.h"
#include "metatype.h"
enum GetCurrentPointType {
    Type_J1,
    Type_J2,
    Type_J3,
    Type_J4,
    Type_J5,
    Type_J6,
    Type_ALL
};

PointEditManager::PointEditManager(QList<DoubleLineEdit*> editGroup,
                                   QList<QLabel*> labelRangeGroup,
                                   QList<QPushButton*> buttonGroup,
                                   EditManagerTextFormat format,
                                   double valueLimit,
                                   QString showStrWhenReachLimit,
                                   QObject *parent )
    :QObject (parent),
    m_buttonGroup(buttonGroup),
    m_editGroup(editGroup),
    m_labelRangeGroup(labelRangeGroup),
    m_textModel(format),
    m_showStrWhenReachLimit(showStrWhenReachLimit),
    m_valueLimit(valueLimit)
{
    for(int i=0;i<buttonGroup.size();++i){
        connect(buttonGroup[i],
                &QPushButton::clicked,
                this,
                [=](){
                    CommunicationEngine::instance()->enqueueCmd_setData(
                        this,
                        AbstractCmd::CmdType::CmdType_GetCurJPos,
                        (GetCurrentPointType)i);
                });
    }
    // for(int i=0;i<m_editGroup.size();++i){
    //     m_editGroup[i]->setProperty("Imt",Imt_FormattedNumbersOnly);
    //     m_editGroup[i]->setShowAndInputDecimals(m_decimalNum);
    // }
    connect(CommunicationEngine::instance(),
            &CommunicationEngine::signal_getCurPoint,
            this,
            &PointEditManager::slot_getCurJPointRes);
}

void PointEditManager::slot_getCurJPointRes(QObject *obj,
                                         int getCurrentPointJType,
                                         bool isSucess,
                                         InoJPos pos)
{
    if(obj!=this || !isSucess)
        return;
    switch(getCurrentPointJType){
    case Type_J1:
    case Type_J2:
    case Type_J3:
    case Type_J4:
    case Type_J5:
    case Type_J6:{
        if(getCurrentPointJType < m_editGroup.size())
            m_editGroup[getCurrentPointJType]->
                setText(QString::number(pos.JointData[getCurrentPointJType],'f', m_decimalNum));
        break;
    }
    case Type_ALL:{
        for(int i=0;i<m_editGroup.size();++i){
            m_editGroup[i]->
                setText(QString::number(pos.JointData[i],'f', m_decimalNum));
        }
        break;
    }
    default:break;
    }
}


QList<double> PointEditManager::getPointValue()
{
    QList<double> ans;
    int size = m_editGroup.size();
    for(int i=0;i<size;++i){
        ans.push_back(m_editGroup[i]->text().toDouble());
    }
    return ans;
}

InoJPos PointEditManager::getPointValueStruct()
{
    InoJPos ans;
    int size = m_editGroup.size();
    for(int i=0;i<size;++i){
        ans.JointData[i] = m_editGroup[i]->text().toDouble();
    }
    return ans;
}

void PointEditManager::setPointValue(const QList<double> &value)
{
    if(value.size() < m_editGroup.size())
        return;
    for(int i=0;i<m_editGroup.size();++i){
        m_editGroup[i]->setText(QString::number(value[i],'f', m_decimalNum));
    }

}

void PointEditManager::setPointValue(const QList<QVariant> &value)
{
    if(value.size() < m_editGroup.size())
        return;
    for(int i=0;i<6;++i){
        m_editGroup[i]->setText(QString::number(value[i].toDouble(),'f', m_decimalNum));
    }
}

void PointEditManager::setPointValue(const QList<QVariant> &value,
                                  const QList<QVariant> &min,
                                  const QList<QVariant> &max)
{
    setPointValue(value);
    setPointRange(min,max);
}

void PointEditManager::setPointValue(const QList<double> &value,
                                  const QList<double> &min,
                                  const QList<double> &max)
{
    setPointValue(value);
    setPointRange(min,max);
}

void PointEditManager::setPointValue(const InoJPos &value)
{
    for(int i=0;i<m_editGroup.size();++i){
        m_editGroup[i]->setText(QString::number(value.JointData[i],'f', m_decimalNum));
    }
}
void PointEditManager::setPointValue(const InoJPos &value,
                                  const QList<double> &min,
                                  const QList<double> &max)
{
    setPointValue(value);
    setPointRange(min,max);
}

void PointEditManager::setPointValue(const QList<double> &value,
                   const QList<int> &min,
                   const QList<int> &max)
{
    setPointValue(value);
    setPointRange(min,max);
}

void PointEditManager::setPointRange(const QList<int> &min,
                                     const QList<int> &max)
{
    if(min.size()< m_labelRangeGroup.size() || max.size()<m_labelRangeGroup.size())
        return;
    int size = m_labelRangeGroup.size();
    for(int i=0;i<size;++i){
        QString minStr = QString::number(min[i]);
        QString maxStr = QString::number(max[i]);
        m_labelRangeGroup[i]->setText(minStr + '~' + maxStr);
    }
    size = size < m_editGroup.size() ? size:m_editGroup.size();
    for(int i=0;i<size;++i){
        m_editGroup[i]->setValueMax(max[i]);
        m_editGroup[i]->setValueMin(min[i]);
    }
}

void PointEditManager::setPointRange(const QList<double> &min,
                                     const QList<double> &max)
{
    if(min.size()< m_labelRangeGroup.size() || max.size()<m_labelRangeGroup.size())
        return;
    int size = m_labelRangeGroup.size();
    for(int i=0;i<size;++i){
        QString minStr = QString::number(min[i],'f', m_decimalNum);
        QString maxStr = QString::number(max[i],'f', m_decimalNum);
        switch (m_textModel) {
        case EditManagerTextFormat::ScientificNotation:{
            if(doubleIsEqual(min[i], -m_valueLimit,m_decimalNum)){
                minStr = QString::number(min[i],'e', m_decimalNum);
            }
            if(doubleIsEqual(max[i], m_valueLimit,m_decimalNum)){
                maxStr = QString::number(max[i],'e', m_decimalNum);
            }
            break;
        }
        case EditManagerTextFormat::CustomSimpleStr:{
            if(doubleIsEqual(min[i], -m_valueLimit, m_decimalNum)){
                minStr = "-" + m_showStrWhenReachLimit;
            }
            if(doubleIsEqual(max[i], m_valueLimit, m_decimalNum)){
                maxStr = "+" + m_showStrWhenReachLimit;
            }
            break;
        }
        case EditManagerTextFormat::None:
        default:
            break;
        }
        m_labelRangeGroup[i]->setText(minStr + '~' + maxStr);
    }
    size = size < m_editGroup.size() ? size:m_editGroup.size();
    for(int i=0;i<size;++i){
        m_editGroup[i]->setValueMax(max[i]);
        m_editGroup[i]->setValueMin(min[i]);
    }
}

void PointEditManager::setPointRange(const QList<QVariant> &min,
                                  const QList<QVariant> &max)
{
    if(min.size()< m_labelRangeGroup.size() || max.size()<m_labelRangeGroup.size())
        return;
    bool ok = false;
    QList<double> min_,max_;
    for(int i=0;i<m_labelRangeGroup.size();++i){
        min_.push_back(min[i].toDouble(&ok));
        if(!ok)
            return;
        max_.push_back(max[i].toDouble(&ok));
        if(!ok)
            return;
    }
    if(ok)
        setPointRange(min_,max_);
}

void PointEditManager::setShowDecimals(unsigned int num)
{
    m_decimalNum = num;
    for(int i=0;i<m_editGroup.size();++i){
        m_editGroup[i]->setShowDecimals(m_decimalNum);
    }
}

void PointEditManager::setInputDecimals(unsigned int num)
{
    for(int i=0;i<m_editGroup.size();++i){
        m_editGroup[i]->setInputDecimals(num);
    }
}

void PointEditManager::setShowAndInputDecimals(unsigned int num)
{
    m_decimalNum = num;
    for(int i=0;i<m_editGroup.size();++i){
        m_editGroup[i]->setShowDecimals(num);
        m_editGroup[i]->setInputDecimals(num);
    }
}

void PointEditManager::setValueByCurrent()
{
    CommunicationEngine::instance()->
        enqueueCmd_setData(this,AbstractCmd::CmdType::CmdType_GetCurJPos,Type_ALL);
}
void PointEditManager::setEnabled(bool isEnable)
{
    for(int i=0;i<m_editGroup.size();++i){
        m_editGroup[i]->setEnabled(isEnable);
    }
}

void PointEditManager::setInitValue(){
    for(int i=0;i<m_editGroup.size();++i){
        m_editGroup[i]->setText("");
    }
    for(int i=0;i<m_labelRangeGroup.size();++i){
        m_labelRangeGroup[i]->setText(QString::number(0,'f', m_decimalNum));
    }
}

void PointEditManager::setCurrentValueBtnVisible(bool isVisible)
{
    for(int i=0;i<m_buttonGroup.size();++i){
        m_buttonGroup[i]->setVisible(isVisible);
    }
}

void PointEditManager::setPointValue(const RoadPoint *roadPoint)
{
    int size = m_editGroup.size();
    if(size >  ROBOT_DOF)
        size = ROBOT_DOF;
    for(int i=0;i<size;++i){
        QString value = QString::number(roadPoint->m_jointAngle[i],'f', m_decimalNum);
        m_editGroup[i]->setText(value);
    }
}
