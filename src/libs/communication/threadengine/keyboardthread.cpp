#include "communicationthread.h"
#include "communication.h"
#include <QSet>
#include <QList>
#include "keyboard.h"
#include "instance.h"
#include "cobotlog.h"
void CommunicationThread::processNewStr(AbstractCmd *absCmd)
{
    // 和类成员保持一致命名，方便对比
    auto [jumpThisCommand, m_currentDepth, oldStr, newStr,
          m_setAllRes,
          m_vectorAllRes,
          m_datasMap,
          m_empty]
        = ((CmdDatas<bool *, int *, QString *, QString,
                     QList<QSet<QString *>> *,
                     QList<QList<QString *>> *,
                     QList<QList<QList<QString *>>> *,
                     QList<QList<QString *>> *> *)absCmd)
              ->m_data;
    if (*jumpThisCommand)
        return;
    int oldSize = oldStr->size();
    int newSize = newStr.size();
    // 一致
    if (newStr == *oldStr) {
        return;
    }
    // 超过已有map最大限制
    if (newSize > m_datasMap->size()) {
        if (newSize < *m_currentDepth) {
            // 删除多余层级
            int deleteCount = *m_currentDepth - newSize;
            if (deleteCount > *m_currentDepth)
                deleteCount = *m_currentDepth;
            for (int i = 0; i < deleteCount; ++i) {
                m_setAllRes->pop_back();
                m_vectorAllRes->pop_back();
            }
            *m_currentDepth -= deleteCount;
        } else {
            // 添加多余层级
            for (int i = *m_currentDepth; i < newSize; ++i) {
                m_vectorAllRes->push_back(QList<QString *>());
                m_setAllRes->push_back(QSet<QString *>());
                ++(*m_currentDepth);
            }
        }
        *oldStr = newStr;
        emit CommunicationEngine::instance()
            ->signal_updateKeyBoardTableModelData(absCmd->m_object, (*m_vectorAllRes)[*m_currentDepth]);
        return;
    }
    // 确定需要进行的操作
    bool needDelete = false;
    int processIndex = 0;
    for (int i = 0; i < (newSize < oldSize ? newSize : oldSize); ++i) {
        processIndex = i;
        if (newStr[i] != oldStr[i]) {
            needDelete = true;
            break;
        }
    }
    if (needDelete || oldSize > newSize) {
        int deleteCount = oldSize - processIndex;
        // 删除操作
        if (deleteCount > *m_currentDepth)
            deleteCount = *m_currentDepth;
        for (int i = 0; i < deleteCount; ++i) {
            m_setAllRes->pop_back();
            m_vectorAllRes->pop_back();
        }
        *m_currentDepth -= deleteCount;
    } else if (oldSize > 0) {
        ++processIndex;
    }
    // 处理添加
    for (int i = processIndex; i < newSize; ++i) {
        unsigned char byte = newStr[i].unicode();
        QSet<QString *> setAllInthisIndex;
        QSet<QString *> setAns;
        QList<QString *> vectorAns;
        int depth = (*m_currentDepth) == 0 ? 0 : *m_currentDepth;
        for (int j = 0; j < (*m_datasMap)[depth][byte].size(); ++j)
            setAllInthisIndex.insert((*m_datasMap)[depth][byte][j]);
        for (auto it = (*m_setAllRes)[*m_currentDepth].constBegin();
             it != (*m_setAllRes)[*m_currentDepth].constEnd();
             ++it) {
            if (*it == 0) {
                LOG_ERROR(tr("String address error."));
                return;
            }
            if (setAllInthisIndex.contains(*it)) {
                vectorAns.push_back(*it);
                setAns.insert(*it);
            }
        }
        // for (auto it = setAllInthisIndex.constBegin();
        //      it != setAllInthisIndex.constEnd();
        //      ++it)
        // {
        //     if((*m_setAllRes)[*m_currentDepth].contains(*it))
        //     {
        //         vectorAns.push_back(*it);
        //         setAns.insert(*it);
        //     }
        // }
        m_setAllRes->push_back(setAns);
        m_vectorAllRes->push_back(vectorAns);
        ++(*m_currentDepth);
    }
    *oldStr = newStr;

    std::sort(((*m_vectorAllRes)[*m_currentDepth]).begin(),
              ((*m_vectorAllRes)[*m_currentDepth]).end(),
              [=](QString *str, QString *str2) {
                  int size1 = str->size();
                  int size2 = str2->size();
                  if(size1 > 0 && size2 >0){
                      if((*str)[0]<= '9' && (*str)[0]>='0'
                          &&((*str2)[0]>'9' || (*str2)[0]<'0'))
                          return false;
                      if(((*str)[0] > '9' || (*str)[0]<'0')
                          && (*str2)[0] <= '9' && (*str2)[0]>='0'){
                          return true;
                      }
                  }
                  if(size1 < size2)
                      return true;
                  else if(size1 >size2)
                      return false;
                  return *str < *str2; });

    emit CommunicationEngine::instance()
        ->signal_updateKeyBoardTableModelData(absCmd->m_object, (*m_vectorAllRes)[*m_currentDepth]);
}

void CommunicationThread::setQStringListSource(AbstractCmd *absCmd)
{
    // 和类成员保持一致命名，方便对比
    auto [m_currentDepth, m_oldStr,
          m_currentStr,
          m_stringSourceAddress,
          m_setAllRes,
          m_vectorAllRes,
          m_datasMap,
          m_empty,
          m_selectMode,
          removeList]
        = ((CmdDatas<int *, QString *, QString,
                     QSet<QString> *,
                     QList<QSet<QString *>> *,
                     QList<QList<QString *>> *,
                     QList<QList<QList<QString *>>> *,
                     QList<QList<QString *>> *,
                     QString,
                     QStringList> *)absCmd)
              ->m_data;
    (*m_oldStr) = "";
    m_datasMap->clear();
    m_vectorAllRes->clear();
    m_setAllRes->clear();
    if (m_stringSourceAddress == 0 /*|| m_stringSourceAddress->size() == 0*/) {
        emit CommunicationEngine::instance()
            ->signal_updateKeyBoardTableModelData(absCmd->m_object, QList<QString *>());
        return;
    }
    int size = m_stringSourceAddress->size();
    QList<QString *> vectorAns;
    QSet<QString *> setAns;
    for (auto &str : *m_stringSourceAddress) {
        if(removeList.contains(str))
            continue;
        int strSize = str.size();
        QString *t = const_cast<QString *>(&str);
        if (t == 0) {
            LOG_ERROR(tr("String address error."));
            return;
        }
        for (int j = m_datasMap->size(); j < strSize; ++j)
            m_datasMap->push_back(*m_empty);
        for (int j = 0; j < strSize; ++j) {
            (*m_datasMap)[j][str[j].unicode()].push_back(t);
        }
        vectorAns.push_back(t);
        setAns.insert(t);
    }
    m_vectorAllRes->push_back(vectorAns);
    m_setAllRes->push_back(setAns);
    *m_currentDepth = 0;

    std::sort(((*m_vectorAllRes)[*m_currentDepth]).begin(),
              ((*m_vectorAllRes)[*m_currentDepth]).end(),
              [=](QString *str, QString *str2) {
                  int size1 = str->size();
                  int size2 = str2->size();
                  if(size1 > 0 && size2 >0){
                      if((*str)[0]<= '9' && (*str)[0]>='0'
                          &&((*str2)[0]>'9' || (*str2)[0]<'0'))
                          return false;
                      if(((*str)[0] > '9' || (*str)[0]<'0')
                          && (*str2)[0] <= '9' && (*str2)[0]>='0'){
                          return true;
                      }
                  }
                  if(size1 < size2)
                      return true;
                  else if(size1 >size2)
                      return false;
                  return *str < *str2; });

    if (m_selectMode == SELECTMODE_ONLYNUMBER) {
        for (QList<QString *> &strList : *m_vectorAllRes) {
            int nStartIndex = 0;
            int nCount = 0;
            int nSize = strList.size();
            for (int i = 0; i < nSize; ++i) {
                bool ok = false;
                (*strList.at(i)).toDouble(&ok);
                if (!ok) {
                    nCount++;
                }
            }
#if defined(INOCOBOTTP_MSVC_QT5)
	if (nStartIndex >= 0 && nCount > 0 && nStartIndex < strList.size()) {
                for (int i = 0; i < nCount && nStartIndex < strList.size(); ++i) {
                    strList.removeAt(nStartIndex);
                }
            }
#else
    strList.remove(nStartIndex, nCount);
#endif
        }
    } else if (m_selectMode == SELECTMODE_ONLYLABEL) {
        for (QList<QString *> &strList : *m_vectorAllRes) {
            int nStartIndex = 0;
            int nCount = 0;
            int nSize = strList.size();
            for (int i = 0; i < nSize; ++i) {
                bool ok = false;
                (*strList.at(i)).toDouble(&ok);
                if (ok) {
                    nCount++;
                } else {
                    nStartIndex++;
                }
            }
#if defined(INOCOBOTTP_MSVC_QT5)
            if (nStartIndex >= 0 && nCount > 0 && nStartIndex < strList.size()) {
                for (int i = 0; i < nCount && nStartIndex < strList.size(); ++i) {
                    strList.removeAt(nStartIndex);
                }
            }
#else
        strList.remove(nStartIndex, nCount);
#endif

        }
    }

    if (m_currentStr.size() == 0)
        emit CommunicationEngine::instance()
            ->signal_updateKeyBoardTableModelData(absCmd->m_object, (*m_vectorAllRes)[*m_currentDepth]);
}

void CommunicationThread::getAllLabelsForVirtualKeyBoard()
{
    QList<QStringList> lablList;
    QList<AllLabelType> typeList;

    QList<QList<InoLabelAndDescriItem>> labelAndDescriList;
    QList<AllLabelType> labelAndDescriTypeList;
    // intput和output
    for (int i = 0; i < ShowType_Size; ++i) {
        m_commInstance->setInputShowType((ShowType)i);
        int radio = 1;
        if (i == ShowType_Bit)
            radio = 16;
        else if (i == ShowType_Byte)
            radio = 2;
        else
            radio = 1;
        QVector<InoLabelItem> data;
        if (m_commInstance->getInputLabelAndRemarkForCurrentShow(data)) {
            QStringList standard, tool, fieldbus, memory, common;
            for (auto &every : data) {
                if (every.sLabel.isEmpty())
                    continue;
                if (every.nIndex < STANDARD_IO_COUNT / 2 * radio)
                    standard << every.sLabel;
                else if (every.nIndex < (TOOL_IO_START_INDEX + TOOL_IO_COUNT) / 2 * radio)
                    tool << every.sLabel;
                else if (every.nIndex < (FIELDBUS_IO_START_INDEX + FIELDBUS_IO_COUNT) / 2 * radio)
                    fieldbus << every.sLabel;
                else
                    memory << every.sLabel;
                common << every.sLabel;
            }
            lablList.push_back(standard);
            typeList.push_back((AllLabelType)(LabelType_Input_Standard_Bit + i));
            lablList.push_back(tool);
            typeList.push_back((AllLabelType)(LabelType_Input_Tool_Bit + i));
            lablList.push_back(fieldbus);
            typeList.push_back((AllLabelType)(LabelType_Input_FieldBus_Bit + i));
            lablList.push_back(memory);
            typeList.push_back((AllLabelType)(LabelType_Input_Memory_Bit + i));
            lablList.push_back(common);
            typeList.push_back((AllLabelType)(LabelType_Input_Common_Bit + i));

            QList<InoLabelAndDescriItem> standardList, toolList, fieldbusList, memoryList, commonList;
            for (auto &every : data) {
                if (every.sLabel.isEmpty() && every.sDescription.isEmpty())
                    continue;
                InoLabelAndDescriItem item;
                item.nIndex = every.nIndex;
                item.sLabel = every.sLabel;
                item.sDescription = every.sDescription;
                if (every.nIndex < STANDARD_IO_COUNT / 2 * radio) {
                    standardList.append(item);
                } else if (every.nIndex < (TOOL_IO_START_INDEX + TOOL_IO_COUNT) / 2 * radio) {
                    toolList.append(item);
                } else if (every.nIndex < (FIELDBUS_IO_START_INDEX + FIELDBUS_IO_COUNT) / 2 * radio) {
                    fieldbusList.append(item);
                } else {
                    memoryList.append(item);
                }
                commonList.append(item);
            }
            labelAndDescriList.push_back(standardList);
            labelAndDescriList.push_back(toolList);
            labelAndDescriList.push_back(fieldbusList);
            labelAndDescriList.push_back(memoryList);
            labelAndDescriList.push_back(commonList);
            labelAndDescriTypeList.push_back((AllLabelType)(LabelType_Input_Standard_Bit + i));
            labelAndDescriTypeList.push_back((AllLabelType)(LabelType_Input_Tool_Bit + i));
            labelAndDescriTypeList.push_back((AllLabelType)(LabelType_Input_FieldBus_Bit + i));
            labelAndDescriTypeList.push_back((AllLabelType)(LabelType_Input_Memory_Bit + i));
            labelAndDescriTypeList.push_back((AllLabelType)(LabelType_Input_Common_Bit + i));
        }
    }

    for (int i = 0; i < ShowType_Size; ++i) {
        m_commInstance->setOutputShowType((ShowType)i);
        int radio = 1;
        if (i == ShowType_Bit)
            radio = 16;
        else if (i == ShowType_Byte)
            radio = 2;
        else
            radio = 1;
        QVector<InoLabelItem> data;
        if (m_commInstance->getOutputLabelAndRemarkForCurrentShow(data)) {
            QStringList standard, tool, fieldbus, memory, common;
            for (auto &every : data) {
                if (every.sLabel.isEmpty())
                    continue;
                if (every.nIndex < STANDARD_IO_COUNT / 2 * radio)
                    standard << every.sLabel;
                else if (every.nIndex < (TOOL_IO_START_INDEX + TOOL_IO_COUNT) / 2 * radio)
                    tool << every.sLabel;
                else if (every.nIndex < (FIELDBUS_IO_START_INDEX + FIELDBUS_IO_COUNT) / 2 * radio)
                    fieldbus << every.sLabel;
                else
                    memory << every.sLabel;
                common << every.sLabel;
            }
            lablList.push_back(standard);
            typeList.push_back((AllLabelType)(LabelType_Output_Standard_Bit + i));
            lablList.push_back(tool);
            typeList.push_back((AllLabelType)(LabelType_Output_Tool_Bit + i));
            lablList.push_back(fieldbus);
            typeList.push_back((AllLabelType)(LabelType_Output_FieldBus_Bit + i));
            lablList.push_back(memory);
            typeList.push_back((AllLabelType)(LabelType_Output_Memory_Bit + i));
            lablList.push_back(common);
            typeList.push_back((AllLabelType)(LabelType_Output_Common_Bit + i));

            QList<InoLabelAndDescriItem> standardList, toolList, fieldbusList, memoryList, commonList;
            for (auto &every : data) {
                if (every.sLabel.isEmpty() && every.sDescription.isEmpty())
                    continue;
                InoLabelAndDescriItem item;
                item.nIndex = every.nIndex;
                item.sLabel = every.sLabel;
                item.sDescription = every.sDescription;
                if (every.nIndex < STANDARD_IO_COUNT / 2 * radio) {
                    standardList.append(item);
                } else if (every.nIndex < (TOOL_IO_START_INDEX + TOOL_IO_COUNT) / 2 * radio) {
                    toolList.append(item);
                } else if (every.nIndex < (FIELDBUS_IO_START_INDEX + FIELDBUS_IO_COUNT) / 2 * radio) {
                    fieldbusList.append(item);
                } else {
                    memoryList.append(item);
                }
                commonList.append(item);
            }
            labelAndDescriList.push_back(standardList);
            labelAndDescriList.push_back(toolList);
            labelAndDescriList.push_back(fieldbusList);
            labelAndDescriList.push_back(memoryList);
            labelAndDescriList.push_back(commonList);
            labelAndDescriTypeList.push_back((AllLabelType)(LabelType_Output_Standard_Bit + i));
            labelAndDescriTypeList.push_back((AllLabelType)(LabelType_Output_Tool_Bit + i));
            labelAndDescriTypeList.push_back((AllLabelType)(LabelType_Output_FieldBus_Bit + i));
            labelAndDescriTypeList.push_back((AllLabelType)(LabelType_Output_Memory_Bit + i));
            labelAndDescriTypeList.push_back((AllLabelType)(LabelType_Output_Common_Bit + i));
        }
    }
    // AD
    QList<Ino_AD_DA_Data> ADdata;
    if (m_commInstance->getDatasAD(ADdata)) {
        QStringList labelData;
        for (auto &every : ADdata) {
            if (every.labs.isEmpty())
                continue;
            labelData << every.labs;
        }
        lablList.push_back(labelData);
        typeList.push_back(LabelType_AD);
    }
    // DA
    QList<Ino_AD_DA_Data> DAdata;
    if (m_commInstance->getDatasAD(DAdata)) {
        QStringList labelData;
        for (auto &every : DAdata) {
            if (every.labs.isEmpty())
                continue;
            labelData << every.labs;
        }
        lablList.push_back(labelData);
        typeList.push_back(LabelType_DA);
    }

    // 全局变量BRD
    QVector<QVector<QVariant>> dest;
    QStringList labelData;
    if (m_commInstance->getGlobalVar_B_everyCol(dest) && dest.size() > 2) {
        for (int i = 0; i < dest[2].size(); ++i) {
            QString temp = dest[2][i].toString();
            if (temp.isEmpty())
                continue;
            labelData << temp;
        }
        lablList.push_back(labelData);
        typeList.push_back(LabelType_GlobalVar_B);
    }
    dest.clear();
    labelData.clear();
    if (m_commInstance->getGlobalVar_R_everyCol(dest) && dest.size() > 2) {
        for (int i = 0; i < dest[2].size(); ++i) {
            QString temp = dest[2][i].toString();
            if (temp.isEmpty())
                continue;
            labelData << temp;
        }
        lablList.push_back(labelData);
        typeList.push_back(LabelType_GlobalVar_R);
    }
    dest.clear();
    labelData.clear();
    if (m_commInstance->getGlobalVar_D_everyCol(dest) && dest.size() > 2) {
        for (int i = 0; i < dest[2].size(); ++i) {
            QString temp = dest[2][i].toString();
            if (temp.isEmpty())
                continue;
            labelData << temp;
        }
        lablList.push_back(labelData);
        typeList.push_back(LabelType_GlobalVar_D);
    }
    // p
    //  QVector<InoRPointInfo> vecRPointInfos;

    // bool isOk = m_commInstance->isConnected();
    // if (!isOk) {
    //     sErrMsg = tr("Controller not connected, "
    //                  "Please connect the controller first.");
    // }

    // if (isOk) {
    //     vecRPointInfos = m_commInstance->readRPoints();
    // }

    QVector<InoRPointInfo> PData = m_commInstance->readAllRPoints();
    QStringList PLabelData;
    for (int i = 0; i < PData.size(); ++i) {
        if (!PData[i].label.isEmpty())
            PLabelData.push_back(PData[i].label);
        PLabelData.push_back(QString::number(PData[i].pointNo));
    }
    lablList.push_back(PLabelData);
    typeList.push_back(LabelType_GlobalVar_P);
    // JP
    QVector<InoJPointInfo> JPData = m_commInstance->readAllJPoints();
    QStringList JPLabelData;
    for (int i = 0; i < JPData.size(); ++i) {
        if (!JPData[i].label.isEmpty())
            JPLabelData.push_back(JPData[i].label);
        JPLabelData.push_back(QString::number(JPData[i].pointNo));
    }
    lablList.push_back(JPLabelData);
    typeList.push_back(LabelType_GlobalVar_JP);

    QMetaObject::invokeMethod(Instance::logicalExpressKeyBoardPropertySource(),
                              "slot_refreshAllLabels",
                              Qt::BlockingQueuedConnection,
                              Q_ARG(const QObject *, Instance::logicalExpressKeyBoardPropertySource()),
                              Q_ARG(const QList<AllLabelType>, typeList),
                              Q_ARG(const QList<QStringList>, lablList));

    QMetaObject::invokeMethod(Instance::setConditionForm(),
                              "slot_refreshAllDescriptions",
                              Qt::BlockingQueuedConnection,
                              Q_ARG(const QObject *, Instance::setConditionForm()),
                              Q_ARG(const QList<AllLabelType>, labelAndDescriTypeList),
                              Q_ARG(const QList<QList<InoLabelAndDescriItem>>, labelAndDescriList));

    QStringList listFiles;
    std::vector<std::string> vecFiles = m_commInstance->getRPointFileList();
    for (const std::string &file : vecFiles) {
        listFiles << QString::fromStdString(file);
    }
    emit CommunicationEngine::instance()->signal_pPorintFileChanged(listFiles, ActiveNewProject);
}

// void CommunicationThread::processSingleElement(QString *str)
// {
//     int size = str->size();
//     for(int i = m_datasMap.size();i<size;++i)
//         m_datasMap.push_back(m_empty);
//     for(int i=0;i<size;++i){
//         m_datasMap[i][(*str)[i].unicode()].push_back(str);
//     }
// }
// void CommunicationThread::processDelete(int deleteCount)
// {
//     if(deleteCount > m_currentDepth)
//         deleteCount = m_currentDepth;
//     for(int i=0;i<deleteCount;++i){
//         m_setAllRes.pop_back();
//         m_vectorAllRes.pop_back();
//     }
// }

// void CommunicationThread::processInput(unsigned char byte)
// {
//     QSet<QString *> setAllInthisIndex;
//     QSet<QString*> setAns;
//     QList<QString*> vectorAns;
//     int depth = m_currentDepth == 0 ? 0 : m_currentDepth;
//     for(int i=0;i<m_datasMap[depth][byte].size();++i)
//         setAllInthisIndex.insert(m_datasMap[depth][byte][i]);

//     for (auto it = setAllInthisIndex.constBegin();
//          it != setAllInthisIndex.constEnd();
//          ++it)
//     {
//         if(m_setAllRes[m_currentDepth].contains(*it))
//         {
//             vectorAns.push_back(*it);
//             setAns.insert(*it);
//         }
//     }
//     m_setAllRes.push_back(setAns);
//     m_vectorAllRes.push_back(vectorAns);
// }
