#include "editgroupmanger.h"
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include "cc_lineedit/lineedit.h"
#include "roadpoint.h"
#include "metatype.h"
#include "pointdata.h"

inline const QString LINK_SIGN_FOR_RANGE = "~";

EditGroupManager::EditGroupManager(QList<LineEdit *> editGroup, QObject *parent) :
    QObject(parent),
    m_editGroup(editGroup)
{
    for (auto edit : m_editGroup) {
        ValueType type = edit->getValueType();
        if (type == String) {
            m_editGroup.clear();
            break;
        }
    }
}

void EditGroupManager::setLabelRangeGroup(QList<QLabel *> labelGroup)
{
    m_labelRangeGroup = labelGroup;
}

void EditGroupManager::setbtnGroup(QList<QPushButton *> btnGroup)
{
    m_buttonGroup = btnGroup;
}

void EditGroupManager::setLabelShowFormat(EditManagerTextFormat type)
{
    m_lableShowFormat = type;
}

void EditGroupManager::setLabelShowType(EditManagerShowType type)
{
    m_lableShowType = type;
}

void EditGroupManager::setLabelSpecialShowContentWhenReachLimit(double min, double max,
                                                                QString showStrWhenReachPositiveLimit,
                                                                QString showStrWhenReachNegitaveLimit)
{
    m_min = min;
    m_max = max;
    m_showStrWhenReachPositiveLimit = showStrWhenReachPositiveLimit;
    m_showStrWhenReachNegitaveLimit = showStrWhenReachNegitaveLimit;
}

void EditGroupManager::setLabelShowDecimals(unsigned int num)
{
    m_labelShowDecimalNum = num;
}

void EditGroupManager::setEditInputDecimals(unsigned int num)
{
    m_editInputDecimalNum = num;
    for (auto edit : m_editGroup)
        edit->setShowAndInputDecimals(num);
}

void EditGroupManager::setShowAndInputDecimals(unsigned int num)
{
    m_labelShowDecimalNum = num;
    m_editInputDecimalNum = num;
    for (auto edit : m_editGroup)
        edit->setShowAndInputDecimals(num);
}

void EditGroupManager::clearEditText()
{
    for (auto edit : m_editGroup)
        edit->setText("");
}

void EditGroupManager::setEditEnabled(const bool isEnable, const unsigned int start, const int count)
{
    if (start == 0 && count < 0) {
        for (auto edit : m_editGroup)
            edit->setEnabled(isEnable);
    } else {
        int size = m_editGroup.size();
        if (start >= size)
            return;
        int tempEnd = start + count;
        if (tempEnd > size)
            tempEnd = size;
        for (int i = start; i < tempEnd; ++i) {
            m_editGroup[i]->setEnabled(isEnable);
        }
    }
}

QList<double> EditGroupManager::getEditDoubleValue()
{
    QList<double> ans;
    for (auto edit : m_editGroup) {
#ifndef INOCOBOTTP_MSVC_QT5
        qDebug() << "double = " << edit->text();
#endif
        ans.push_back(edit->getQVariant().toDouble());
    }
    return ans;
}

QList<int> EditGroupManager::getEditIntValueByRound()
{
    QList<int> ans;
    for (auto edit : m_editGroup)
        ans.push_back(edit->getQVariant().toInt());
    return ans;
}

QList<int> EditGroupManager::getEditIntValueByTruncation()
{
    QList<int> ans;
    for (auto edit : m_editGroup)
        ans.push_back(edit->getQVariant().toInt());
    return ans;
}

void EditGroupManager::getInoJPos(InoJPos *data, unsigned int JNum, unsigned int ENum)
{
    int size = m_editGroup.size();
    if (size <= JNum) {
        for (int i = 0; i < size; ++i) {
            data->JointData[i] = m_editGroup[i]->text().toDouble();
        }
    } else if (size > JNum && size <= JNum + ENum) {
        for (int i = 0; i < JNum; ++i) {
            data->JointData[i] = m_editGroup[i]->text().toDouble();
        }
        for (int i = JNum; i < size; ++i) {
            data->EPosData[i - JNum] = m_editGroup[i]->text().toDouble();
        }
    } else {
        for (int i = 0; i < JNum; ++i) {
            data->JointData[i] = m_editGroup[i]->text().toDouble();
        }
        for (int i = JNum; i < ENum; ++i) {
            data->EPosData[i - JNum] = m_editGroup[i]->text().toDouble();
        }
    }
}

void EditGroupManager::setInoJPos(const InoJPos *data, unsigned int JNum, unsigned int ENum)
{
    QList<double> num;
    for (int i = 0; i < JNum; ++i) {
        num.push_back(data->JointData[i]);
    }
    for (int i = 0; i < ENum; ++i) {
        num.push_back(data->EPosData[i]);
    }
    setEditValue(num);
}

void EditGroupManager::setRoadPoint(const RoadPoint *data)
{
    QList<double> num;
    for (int i = 0; i < ROBOT_DOF; ++i) {
        num.push_back(data->m_jointAngle[i]);
    }
    setEditValue(num);
}

void EditGroupManager::setEditValue(const QList<QString> &value)
{
    for (int i = 0; i < getMinSize(value, m_editGroup); ++i) {
        m_editGroup[i]->setText(value[i]);
    }
}

void EditGroupManager::setEditValueLimit(const QList<QString> &min,
                                         const QList<QString> &max)
{
    if (min.size() != max.size())
        return;
    int size = getMinSize(min, m_editGroup);
    for (int i = 0; i < size; ++i) {
        bool okMin = false, okMax = false;
        ;
        double _min = min[i].toDouble(&okMin);
        double _max = max[i].toDouble(&okMax);
        if (okMin && okMax) {
            m_editGroup[i]->setValueMax(_max);
            m_editGroup[i]->setValueMin(_min);
        }
    }
    size = getMinSize(min, m_labelRangeGroup);
    for (int i = 0; i < size; ++i) {
        m_labelRangeGroup[i]->setText("[" + min[i] + LINK_SIGN_FOR_RANGE + max[i] + "]");
    }
}

void EditGroupManager::setEditValueLimit(const QList<QString> &value,
                                         const QList<QString> &min,
                                         const QList<QString> &max)
{
    setEditValueLimit(min, max);
    setEditValue(value);
}

void EditGroupManager::setEditValue(const QList<double> &value)
{
    int size = getMinSize(value, m_editGroup);
    for (int i = 0; i < size; ++i) {
        m_editGroup[i]->setQVariant(value[i]);
    }
}

void EditGroupManager::setEditValueLimit(const QList<double> &min,
                                         const QList<double> &max)
{
    if (min.size() != max.size())
        return;
    int size = getMinSize(min, m_editGroup);
    for (int i = 0; i < size; ++i) {
        m_editGroup[i]->setValueMax(max[i]);
        m_editGroup[i]->setValueMin(min[i]);
    }
    size = getMinSize(min, m_labelRangeGroup);
    for (int i = 0; i < size; ++i) {
        QString minStr, maxStr;
        if (m_lableShowType == DOUBLE) {
            if (m_lableShowFormat == None) {
                minStr = QString::number(min[i], 'f', m_labelShowDecimalNum);
                maxStr = QString::number(max[i], 'f', m_labelShowDecimalNum);
            } else {
                minStr = QString::number(min[i], 'e', m_labelShowDecimalNum);
                maxStr = QString::number(max[i], 'e', m_labelShowDecimalNum);
            }
        } else if (m_lableShowType == INT) {
            if (m_lableShowFormat == None) {
                minStr = QString::number(min[i], 'f', 0);
                maxStr = QString::number(max[i], 'f', 0);
            } else {
                minStr = QString::number(min[i], 'e', m_labelShowDecimalNum);
                maxStr = QString::number(max[i], 'e', m_labelShowDecimalNum);
            }
        }
        if (m_editGroup.size() > i) {
            if (!m_showStrWhenReachNegitaveLimit.isEmpty() && doubleIsEqual(min[i], m_min)) {
                minStr = m_showStrWhenReachNegitaveLimit;
            }
            if (!m_showStrWhenReachPositiveLimit.isEmpty() && doubleIsEqual(max[i], m_max)) {
                maxStr = m_showStrWhenReachPositiveLimit;
            }
        }
        m_labelRangeGroup[i]->setText("[" + minStr + LINK_SIGN_FOR_RANGE + maxStr + "]");
    }
}

void EditGroupManager::setEditValueLimit(const QList<double> &value,
                                         const QList<double> &min,
                                         const QList<double> &max)
{
    setEditValueLimit(min, max);
    setEditValue(value);
}

void EditGroupManager::setEditValue(const QList<int> &value)
{
    int size = getMinSize(value, m_editGroup);
    for (int i = 0; i < size; ++i) {
        m_editGroup[i]->setQVariant(value[i]);
    }
}

void EditGroupManager::setEditValueLimit(const QList<int> &min,
                                         const QList<int> &max)
{
    if (min.size() != max.size())
        return;
    int size = getMinSize(min, m_editGroup);
    for (int i = 0; i < size; ++i) {
        m_editGroup[i]->setValueMax(max[i]);
        m_editGroup[i]->setValueMin(min[i]);
    }
    size = getMinSize(min, m_labelRangeGroup);
    for (int i = 0; i < size; ++i) {
        QString minStr, maxStr;
        if (m_lableShowType == DOUBLE) {
            if (m_lableShowFormat == None) {
                minStr = QString::number(min[i], 'f', m_labelShowDecimalNum);
                maxStr = QString::number(max[i], 'f', m_labelShowDecimalNum);
            } else {
                minStr = QString::number(min[i], 'e', m_labelShowDecimalNum);
                maxStr = QString::number(max[i], 'e', m_labelShowDecimalNum);
            }
        } else if (m_lableShowType == INT) {
            if (m_lableShowFormat == None) {
                minStr = QString::number(min[i], 'f', 0);
                maxStr = QString::number(max[i], 'f', 0);
            } else {
                minStr = QString::number(min[i], 'e', m_labelShowDecimalNum);
                maxStr = QString::number(max[i], 'e', m_labelShowDecimalNum);
            }
        }
        if (m_editGroup.size() > i) {
            if (!m_showStrWhenReachNegitaveLimit.isEmpty() && doubleIsEqual(min[i], m_min)) {
                minStr = m_showStrWhenReachNegitaveLimit;
            }
            if (!m_showStrWhenReachPositiveLimit.isEmpty() && doubleIsEqual(max[i], m_max)) {
                maxStr = m_showStrWhenReachPositiveLimit;
            }
        }
        m_labelRangeGroup[i]->setText("[" + minStr + LINK_SIGN_FOR_RANGE + maxStr + "]");
    }
}

void EditGroupManager::setEditValueLimit(const QList<int> &value,
                                         const QList<int> &min,
                                         const QList<int> &max)
{
    setEditValueLimit(min, max);
    setEditValue(value);
}

void EditGroupManager::setEditValue(const QList<QVariant> &value)
{
    int size = getMinSize(value, m_editGroup);
    for (int i = 0; i < size; ++i) {
        m_editGroup[i]->setQVariant(value[i]);
    }
}

void EditGroupManager::setEditValueLimit(const QList<QVariant> &value,
                                         const QList<QVariant> &min,
                                         const QList<QVariant> &max)
{
    setEditValueLimit(min, max);
    setEditValue(value);
}

void EditGroupManager::setEditValueLimit(const QList<QVariant> &min,
                                         const QList<QVariant> &max)
{
    if (min.size() != max.size())
        return;
    int size = getMinSize(min, m_editGroup);
    for (int i = 0; i < size; ++i) {
        m_editGroup[i]->setValueMax(max[i]);
        m_editGroup[i]->setValueMin(min[i]);
    }
    size = getMinSize(min, m_labelRangeGroup);
    for (int i = 0; i < size; ++i) {
        QString minStr, maxStr;
        if (m_lableShowType == DOUBLE) {
            if (m_lableShowFormat == None) {
                minStr = QString::number(min[i].toDouble(), 'f', m_labelShowDecimalNum);
                maxStr = QString::number(max[i].toDouble(), 'f', m_labelShowDecimalNum);
            } else {
                minStr = QString::number(min[i].toDouble(), 'e', m_labelShowDecimalNum);
                maxStr = QString::number(max[i].toDouble(), 'e', m_labelShowDecimalNum);
            }
        } else if (m_lableShowType == INT) {
            if (m_lableShowFormat == None) {
                minStr = QString::number(min[i].toDouble(), 'f', 0);
                maxStr = QString::number(max[i].toDouble(), 'f', 0);
            } else {
                minStr = QString::number(min[i].toDouble(), 'e', m_labelShowDecimalNum);
                maxStr = QString::number(max[i].toDouble(), 'e', m_labelShowDecimalNum);
            }
        }
        if (m_editGroup.size() > i) {
            if (!m_showStrWhenReachNegitaveLimit.isEmpty() && doubleIsEqual(min[i].toDouble(), m_min)) {
                minStr = m_showStrWhenReachNegitaveLimit;
            }
            if (!m_showStrWhenReachPositiveLimit.isEmpty() && doubleIsEqual(max[i].toDouble(), m_max)) {
                maxStr = m_showStrWhenReachPositiveLimit;
            }
        }
        m_labelRangeGroup[i]->setText("[" + minStr + LINK_SIGN_FOR_RANGE + maxStr + "]");
    }
}

void EditGroupManager::setLabelValueLimit(const QList<int> &min, const QList<int> &max)
{
    if (min.size() != max.size())
        return;
    int size = getMinSize(min, m_labelRangeGroup);
    for (int i = 0; i < size; ++i) {
        QString minStr, maxStr;
        if (m_lableShowType == DOUBLE) {
            if (m_lableShowFormat == None) {
                minStr = QString::number(min[i], 'f', m_labelShowDecimalNum);
                maxStr = QString::number(max[i], 'f', m_labelShowDecimalNum);
            } else {
                minStr = QString::number(min[i], 'e', m_labelShowDecimalNum);
                maxStr = QString::number(max[i], 'e', m_labelShowDecimalNum);
            }
        } else if (m_lableShowType == INT) {
            if (m_lableShowFormat == None) {
                minStr = QString::number(min[i], 'f', 0);
                maxStr = QString::number(max[i], 'f', 0);
            } else {
                minStr = QString::number(min[i], 'e', m_labelShowDecimalNum);
                maxStr = QString::number(max[i], 'e', m_labelShowDecimalNum);
            }
        }
        if (m_editGroup.size() > i) {
            if (!m_showStrWhenReachNegitaveLimit.isEmpty() && doubleIsEqual(min[i], m_min)) {
                minStr = m_showStrWhenReachNegitaveLimit;
            }
            if (!m_showStrWhenReachPositiveLimit.isEmpty() && doubleIsEqual(max[i], m_max)) {
                maxStr = m_showStrWhenReachPositiveLimit;
            }
        }
        m_labelRangeGroup[i]->setText("[" + minStr + LINK_SIGN_FOR_RANGE + maxStr + "]");
    }
}
