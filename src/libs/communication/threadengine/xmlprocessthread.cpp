#include <QSet>
#include <QList>
#include <QBuffer>
#include <QXmlStreamWriter>
#include <QMutex>
#include <QHash>
#include <QMap>

#include "communicationthread.h"
#include "communication.h"
#include "treemodel.h"
#include "cobotlog.h"
#include "metalogictree.h"

#ifdef INOCOBOTTP_MSVC_QT5
    #include <QRegularExpression>
    #include <QDateTime>
#endif

#define TIME QDateTime::currentDateTime().toString("hh:mm:ss:zzz")
using namespace Utils;
static QList<TreeItem *> gWriteXmlTreeItemList;
static QStringList gReadXmlNodesCache;
static QHash<QString, QStringList> gHashParentUuidToChildrenUuids = {};
static QHash<QString, TreeItem *> gHashUuidToItemAdd = {};
QMutex gLockHashUuidToItemAdd;

static void parseSplitXmlInfo(QXmlStreamWriter *writer, const QString &xmlInfo)
{
    writer->writeStartElement("Attribute");
    if (!xmlInfo.isEmpty()) {
        QJsonObject jsonObj = QJsonDocument::fromJson(xmlInfo.toUtf8()).object();
        int conditionModeIndex = jsonObj.keys().indexOf(QRegularExpression(".*ConditionMode"));
        if (conditionModeIndex >= 0) {
            QString conditionModeKey = jsonObj.keys().at(conditionModeIndex);
            writer->writeTextElement(conditionModeKey,
                                     jsonObj.take(conditionModeKey).toVariant().toString());
        }
        for (QJsonObject::iterator i = jsonObj.begin(); i != jsonObj.end(); i++)
            writer->writeTextElement(i.key(), i.value().toVariant().toString());
        writer->writeEndElement();
    } else
        writer->writeEndElement();
}

static void wirteSplitXml(QXmlStreamWriter *writer, TreeItem *item)
{
    writer->writeStartElement("Condition");
    writer->writeAttribute("ConditionType",
                           LogictreeMetaType::condType2Name(item->data(LogictreeMetaType::Column_CondType, Qt::DisplayRole).toString()));
    writer->writeAttribute("ConditionAlias", item->data(LogictreeMetaType::Column_Alias, Qt::DisplayRole).toString());
    writer->writeAttribute("ConditionUuid", item->data(LogictreeMetaType::Column_Uuid, Qt::DisplayRole).toString());
    writer->writeAttribute("Comment", item->data(LogictreeMetaType::Column_Comment, Qt::UserRole).toString());
    writer->writeAttribute("ModifyEnable", item->data(LogictreeMetaType::Column_ModifyEnable, Qt::UserRole).toString());
    QString addState = item->data(LogictreeMetaType::Column_AddState, Qt::UserRole).toString();
    writer->writeAttribute("AddState", addState);
    writer->writeAttribute("ManagedByOthers", item->data(LogictreeMetaType::Column_ManagedByOthers, Qt::UserRole).toString());
    writer->writeStartElement("Attribute");
    QString attribute = item->data(LogictreeMetaType::Column_CondInfo, Qt::DisplayRole).toString();
    if (!attribute.isEmpty()) {
        QJsonObject jsonObj = QJsonDocument::fromJson(attribute.toUtf8()).object();
        int conditionModeIndex = jsonObj.keys().indexOf(QRegularExpression(".*ConditionMode"));
        if (conditionModeIndex >= 0) {
            QString conditionModeKey = jsonObj.keys().at(conditionModeIndex);
            writer->writeTextElement(conditionModeKey, jsonObj.take(conditionModeKey).toVariant().toString());
        }
        for (QJsonObject::iterator i = jsonObj.begin(); i != jsonObj.end(); i++)
            writer->writeTextElement(i.key(), i.value().toVariant().toString());
    }
    writer->writeEndElement();
    writer->writeEndElement();
}

static void getAllItem(TreeItem *parent)
{
    QString condType = parent->data(LogictreeMetaType::Column_CondType, Qt::DisplayRole).toString();
    if (condType != "Add_ConditionType") {
        gWriteXmlTreeItemList.push_back(parent);
#if defined(INOCOBOTTP_MSVC_QT5)
    QVector<TreeItem *> children = parent->children();
#else
    QList<TreeItem *> children = parent->children();
#endif
        for (auto &child : children) {
            getAllItem(child);
        }
    } else {
        LOG_INFO("Do not append, condType == Add_ConditionType ");
    }
}

void CommunicationThread::getAllTreeItems(AbstractCmd *absCmd)
{
    qDebug() << "getAllTreeItems(AbstractCmd *absCmd)";
    auto [item] = BIND(absCmd, TreeItem *);
    gWriteXmlTreeItemList.clear();
    gWriteXmlTreeItemList.reserve(10000);
    TreeItem *temp = item;
    getAllItem(item);
    qDebug() << "absCmd->m_object" << absCmd->m_object->objectName();
    emit CommunicationEngine::instance()->signal_logicTreeItemStandBy(absCmd->m_object, gWriteXmlTreeItemList.size());
}

void CommunicationThread::wirteLogicTreeNodes(AbstractCmd *absCmd)
{
    qDebug() << "CommunicationThread::wirteLogicTreeNodes(AbstractCmd *absCmd)";
    auto [start, end, file, lock] = BIND(absCmd, int, int, QFile *, QMutex *);
    if (start == end) {
        emit CommunicationEngine::instance()->signal_WriteLogicTreeThreadAns(absCmd->m_object, true);
        return;
    }
    QByteArray byteArray;
    QBuffer buffer(&byteArray);
#if defined(INOCOBOTTP_MSVC_QT5)
    if (!buffer.open(QIODevice::Text | QIODevice::WriteOnly)) {
        qDebug() << "can not open";
        emit CommunicationEngine::instance()->signal_WriteLogicTreeThreadAns(absCmd->m_object, false);
        return;
    }
#else
    if (!buffer.open(QIODeviceBase::Text | QIODeviceBase::WriteOnly)) {
        emit CommunicationEngine::instance()->signal_WriteLogicTreeThreadAns(absCmd->m_object, false);
        return;
    }
#endif

    QXmlStreamWriter xmlWriter;
    xmlWriter.setDevice(&buffer);
    xmlWriter.setAutoFormatting(true);
    bool writeSplitStart = false;
    if (start == 0) {
        xmlWriter.writeStartDocument();
        xmlWriter.writeStartElement("Version");
        xmlWriter.writeAttribute("TeachPadVersion", Instance::common()->property("TeachPadVersion").toString());
        xmlWriter.writeEndElement();
        xmlWriter.writeStartElement("SplitChips");
        xmlWriter.writeEndElement();
        xmlWriter.writeStartElement("Conditions");
        start = 1;
    }
    for (int i = start; i < end; i++) {
        if (i % LogictreeMetaType::LogicTreeNodeChipSize == 0) {
            xmlWriter.writeStartDocument();
            xmlWriter.writeStartElement("Conditions");
            wirteSplitXml(&xmlWriter, gWriteXmlTreeItemList[i]);
        } else if ((i % LogictreeMetaType::LogicTreeNodeChipSize) == (LogictreeMetaType::LogicTreeNodeChipSize - 1)) {
            wirteSplitXml(&xmlWriter, gWriteXmlTreeItemList[i]);
            xmlWriter.writeEndElement();
            xmlWriter.writeStartElement("SplitChips");
            xmlWriter.writeEndElement();
            xmlWriter.writeEndDocument();
        } else {
            wirteSplitXml(&xmlWriter, gWriteXmlTreeItemList[i]);
        }
    }
    if (end % LogictreeMetaType::LogicTreeNodeChipSize != 0) {
        xmlWriter.writeEndElement();
        xmlWriter.writeStartElement("SplitChips");
        xmlWriter.writeEndElement();
        xmlWriter.writeEndDocument();
    }
    buffer.close();
    byteArray.replace("\r\n", "\n");
    lock->lock();
    file->write(byteArray);
    lock->unlock();
    emit CommunicationEngine::instance()->signal_WriteLogicTreeThreadAns(absCmd->m_object, true);
}

void CommunicationThread::wirteLogicTreeLevel(AbstractCmd *absCmd)
{
    auto [path] = BIND(absCmd, QString);
    QFile file(path);


#if defined(INOCOBOTTP_MSVC_QT5)
    if (!file.open(QIODevice::Text | QIODevice::WriteOnly)) {
        emit CommunicationEngine::instance()->signal_WriteLogicTreeThreadAns(absCmd->m_object, false);
    }
#else
    if (!file.open(QIODeviceBase::Text | QIODeviceBase::WriteOnly)) {
        emit CommunicationEngine::instance()->signal_WriteLogicTreeThreadAns(absCmd->m_object, false);
    }
#endif
    QXmlStreamWriter xmlWriter(&file);
    xmlWriter.setAutoFormatting(true);
    xmlWriter.writeStartDocument();
    xmlWriter.writeStartElement("Parents");
    for (auto &parent : gWriteXmlTreeItemList) {
        QString condType = parent->data(LogictreeMetaType::Column_CondType, Qt::DisplayRole).toString();
#if defined(INOCOBOTTP_MSVC_QT5)
        QVector<TreeItem *> children = parent->children();
#else
        QList<TreeItem *> children = parent->children();
#endif

        if (children.size() == 0)
            continue;
        xmlWriter.writeStartElement("Parent");
        xmlWriter.writeAttribute("Uuid", parent->data(LogictreeMetaType::Column_Uuid, Qt::DisplayRole).toString());
        for (auto &child : children) {
            QString condType = child->data(LogictreeMetaType::Column_CondType, Qt::DisplayRole).toString();
            xmlWriter.writeStartElement("Child");
            xmlWriter.writeCharacters(child->data(LogictreeMetaType::Column_Uuid, Qt::DisplayRole).toString());
            xmlWriter.writeEndElement();
        }
        xmlWriter.writeEndElement();
    }
    xmlWriter.writeEndElement();
    xmlWriter.writeEndDocument();
    file.close();
    emit CommunicationEngine::instance()->signal_WriteLogicTreeThreadAns(absCmd->m_object, true);
}

void CommunicationThread::createLogicTreeNodesXmlCache(AbstractCmd *absCmd)
{
    auto [path] = BIND(absCmd, QString);
    gReadXmlNodesCache.clear();
    gHashUuidToItemAdd.clear();
    QFile file(path);
#if defined(INOCOBOTTP_MSVC_QT5)
    if (!file.open(QIODevice::Text | QIODevice::ReadOnly)) {
        qDebug() << "createLogicTreeNodesXmlCache(AbstractCmd *absCmd)11111";
        emit CommunicationEngine::instance()->signal_ReadLogicTreeNodesCacheAns(absCmd->m_object, false, 0);
        return;
    }
#else
    if (!file.open(QIODeviceBase::Text | QIODeviceBase::ReadOnly)) {
        emit CommunicationEngine::instance()->signal_ReadLogicTreeNodesCacheAns(absCmd->m_object, false, 0);
        return;
    }
#endif

    gReadXmlNodesCache = QString(file.readAll()).split("<SplitChips/>\n");
    for (int i = gReadXmlNodesCache.size() - 1; i >= 0; --i)
        if (gReadXmlNodesCache[i].size() == 0 || gReadXmlNodesCache[i] == "\n") {
#if defined(INOCOBOTTP_MSVC_QT5)
            gReadXmlNodesCache.erase(gReadXmlNodesCache.begin() + i);
#else
            gReadXmlNodesCache.erase(gReadXmlNodesCache.cbegin() + i);
#endif
        }
    emit CommunicationEngine::instance()->signal_ReadLogicTreeNodesCacheAns(absCmd->m_object, true, gReadXmlNodesCache.size());
}

void CommunicationThread::readLogicTreeLevel(AbstractCmd *absCmd)
{
    auto [path] = BIND(absCmd, QString);
    gHashParentUuidToChildrenUuids.clear();
    QFile file(path);
#if defined(INOCOBOTTP_MSVC_QT5)
    if (!file.open(QIODevice::Text | QIODevice::ReadOnly)) {
        qDebug() << "readLogicTreeLevel1111";
        emit CommunicationEngine::instance()->signal_CreateLogicTreeStrucheThreadAns(absCmd->m_object, false);
    }
#else
    if (!file.open(QIODeviceBase::Text | QIODeviceBase::ReadOnly)) {
        emit CommunicationEngine::instance()->signal_CreateLogicTreeStrucheThreadAns(absCmd->m_object, false);
    }
#endif
    QXmlStreamReader xmlReader(&file);
    while (!xmlReader.atEnd() && !xmlReader.hasError()) {
        xmlReader.readNext();
        if (xmlReader.isStartElement()) {
            if (xmlReader.name() == QString("Parent")) {
                QString uuid = xmlReader.attributes().value("Uuid").toString();
                gHashParentUuidToChildrenUuids[uuid] = QStringList();
                while (!(xmlReader.isEndElement() && xmlReader.name() == QString("Parent"))) {
                    xmlReader.readNext();
                    if (xmlReader.isStartElement() && xmlReader.name() == QString("Child")) {
                        gHashParentUuidToChildrenUuids[uuid] << xmlReader.readElementText();
                    }
                }
            }
        }
    }
    emit CommunicationEngine::instance()->signal_CreateLogicTreeStrucheThreadAns(absCmd->m_object, !xmlReader.hasError());
    qDebug() << "!xmlReader.hasError()" << !xmlReader.hasError();
}

static void deleteFailedTreeItem(QList<TreeItem *> &item)
{
    for(int i=0;i<item.size();++i){
        delete item[i];
    }
    item.clear();
}


void CommunicationThread::readLogicTreeNodes(AbstractCmd *absCmd)
{
    auto [obj, start, end] = BIND(absCmd, QObject *, int, int);
#if defined(INOCOBOTTP_MSVC_QT5)
    if (!obj) {
        qDebug() << "CommunicationThread::readLogicTreeNodes(AbstractCmd *absCmd)111";
        emit CommunicationEngine::instance()->signal_CreateLogicTreeNodesThreadAns(absCmd->m_object, false);
        return;
    }
#endif
    QXmlStreamReader xmlReader;
    QList<QString> uuidCache;
    QList<TreeItem *> addressCache;
    for (int i = start; i < end; ++i) {
        xmlReader.clear();
        if (gReadXmlNodesCache[i].startsWith("\n"))
            xmlReader.addData(gReadXmlNodesCache[i].mid(1));
        else
            xmlReader.addData(gReadXmlNodesCache[i]);
        const int maxTry = LogictreeMetaType::LogicTreeNodeChipSize * 50;
        while (!xmlReader.atEnd() && !xmlReader.hasError()) {
            xmlReader.readNext();
            if (xmlReader.hasError()) {
                LOG_ERROR("xmlReader.hasError 1 start");
                deleteFailedTreeItem(addressCache);
                LOG_ERROR("xmlReader.hasError 1 end");
                 qDebug() << "CommunicationThread::readLogicTreeNodes(AbstractCmd *absCmd)222";
                emit CommunicationEngine::instance()->signal_CreateLogicTreeNodesThreadAns(absCmd->m_object, false);
                return;
            }

            if (xmlReader.isStartElement()) {
                if (xmlReader.name() == QString("Version")) {
                    QString projectVersion = xmlReader.attributes().value("TeachPadVersion").toString();
                    LOG_INFO(QString("has readed version:%1").arg(projectVersion));
                    Instance::common()->setProperty("CurrentProjectVersion", projectVersion);
                }
            }

            if (xmlReader.isStartElement()) {
                if (xmlReader.name() == QString("Condition")) {
                    QString conditionType = xmlReader.attributes().value("ConditionType").toString();
                    QString conditionAlias = xmlReader.attributes().value("ConditionAlias").toString();
                    QString conditionUuid = xmlReader.attributes().value("ConditionUuid").toString();
                    bool isComment = (0 == xmlReader.attributes().value("Comment").toString().compare("true"));
                    bool isModifyEnable = (0 != xmlReader.attributes().value("ModifyEnable").toString().compare("false"));
                    QString addState = xmlReader.attributes().value("AddState").toString();
                    if(addState.isEmpty()){
                        addState = "Normal";
                    }
                    QString managedByOthers = xmlReader.attributes().value("ManagedByOthers").toString();
                    conditionType = LogictreeMetaType::condName2Type(conditionType);
                    if (conditionAlias.endsWith(SCRIPT_FILE_NAME_SUFFIX)) {
                        conditionAlias = conditionAlias.left(conditionAlias.length() - QString(SCRIPT_FILE_NAME_SUFFIX).length());
                    }
                    Utils::TreeItem *item = nullptr;
#ifdef INOCOBOTTP_MSVC_QT5
                    const bool invokeOk = QMetaObject::invokeMethod(
                        obj,
                        "creatNewLogicTreeItem",
                        Qt::DirectConnection,
                        Q_RETURN_ARG(Utils::TreeItem *, item),
                        Q_ARG(QString, conditionAlias),
                        Q_ARG(QString, conditionType),
                        Q_ARG(bool, isComment),
                        Q_ARG(bool, isModifyEnable),
                        Q_ARG(QString, addState),
                        Q_ARG(QString, conditionUuid),
                        Q_ARG(QString, managedByOthers));
                    if (!invokeOk || !item) {
                        LOG_ERROR(QString("creatNewLogicTreeItem failed, invokeOk=%1, uuid=%2")
                                      .arg(invokeOk)
                                      .arg(conditionUuid));

                        deleteFailedTreeItem(addressCache);
                        emit CommunicationEngine::instance()->signal_CreateLogicTreeNodesThreadAns(absCmd->m_object, false);
                        return;
                    }

#else
                    QMetaObject::invokeMethod(
                        obj,
                        "creatNewLogicTreeItem",
                        Qt::DirectConnection,
                        Q_RETURN_ARG(TreeItem *, item),
                        Q_ARG(QString, conditionAlias),
                        Q_ARG(QString, conditionType),
                        Q_ARG(bool, isComment),
                        Q_ARG(bool, isModifyEnable),
                        Q_ARG(QString, addState),
                        Q_ARG(QString, conditionUuid),
                        Q_ARG(QString, managedByOthers));
#endif

                    uuidCache << conditionUuid;
                    addressCache << item;
                    while (!xmlReader.atEnd() && xmlReader.readNextStartElement()) {
                        if (xmlReader.hasError()) {
                            LOG_ERROR("xmlReader.hasError 2 start");
                            deleteFailedTreeItem(addressCache);
                            LOG_ERROR("xmlReader.hasError 2 end");
                            emit CommunicationEngine::instance()->signal_CreateLogicTreeNodesThreadAns(absCmd->m_object, false);
                            return;
                        }
                        if (QString("Condition") == xmlReader.name()) {
                            continue;
                        } else if (QString("Attribute") == xmlReader.name()) {
                            xmlReader.readNextStartElement();
                            QJsonObject jsonObj;
                            while (!xmlReader.isEndElement()) {
                                if (xmlReader.isStartElement())
                                    jsonObj.insert(xmlReader.name().toString(),
                                                   xmlReader.readElementText());
                                xmlReader.readNext();
                                if (xmlReader.hasError()) {
                                    LOG_ERROR("xmlReader.hasError 4 start");
                                    deleteFailedTreeItem(addressCache);
                                    LOG_ERROR("xmlReader.hasError 4 end");
                                     qDebug() << "CommunicationThread::readLogicTreeNodes(AbstractCmd *absCmd)444";
                                    emit CommunicationEngine::instance()->signal_CreateLogicTreeNodesThreadAns(absCmd->m_object, false);
                                    return;
                                }
                            }
                            item->setData(LogictreeMetaType::Column_CondInfo,
                                          QString(QJsonDocument(jsonObj).toJson(QJsonDocument::Compact)),
                                          Qt::DisplayRole);
                        }
                    }
                }
            }
        }
        if (xmlReader.hasError()) {
            LOG_ERROR("xmlReader.hasError 5 start");
            deleteFailedTreeItem(addressCache);
            LOG_ERROR("xmlReader.hasError 5 end");
             qDebug() << "CommunicationThread::readLogicTreeNodes(AbstractCmd *absCmd)555";
            emit CommunicationEngine::instance()->signal_CreateLogicTreeNodesThreadAns(absCmd->m_object, false);
            return;
        }
    }
    int size = uuidCache.size();
    gLockHashUuidToItemAdd.lock();
    for (int i = 0; i < size; ++i)
        gHashUuidToItemAdd[uuidCache[i]] = addressCache[i];
    gLockHashUuidToItemAdd.unlock();
    emit CommunicationEngine::instance()->signal_CreateLogicTreeNodesThreadAns(absCmd->m_object, true);
}

void CommunicationThread::sortLogicTreeNodes(AbstractCmd *absCmd)
{
    if (gHashUuidToItemAdd.size() >= LogicTreeNodeMaxCount) {
        SHOW_ERROR(tr("Loading project failure. The number of logic tree nodes in the project exceeds %1.").arg(LogicTreeNodeMaxCount));
        emit CommunicationEngine::instance()->signal_LogicTreeModelSortAns(absCmd->m_object, false);
        return;
    }
    auto [model, map] = BIND(absCmd, TreeModel *, QMap<QString, TreeItem *> *);
    for (auto it = gHashParentUuidToChildrenUuids.begin(); it != gHashParentUuidToChildrenUuids.end(); ++it) {
        if (it.key().isEmpty()) {
            for (auto &child : it.value()) {
                if (gHashUuidToItemAdd.contains(child)) {
                    model->rootItem()->appendChild(gHashUuidToItemAdd[child]);
                } else {
                    LOG_INFO("sortLogicTreeNodes failed 0, parent " + it.key() + " child item " + " uuid " + child);
                    continue;
                    // emit CommunicationEngine::instance()->signal_LogicTreeModelSortAns(absCmd->m_object, false);
                    // return;
                }
            }
        } else if (gHashUuidToItemAdd.contains(it.key())) {
            for (auto &child : it.value()) {
                if (gHashUuidToItemAdd.contains(child)) {
                    gHashUuidToItemAdd[it.key()]->appendChild(gHashUuidToItemAdd[child]);
                } else {
                    LOG_INFO("sortLogicTreeNodes failed 1, parent " + it.key() + " child item " + " uuid " + child);
                    continue;
                    // emit CommunicationEngine::instance()->signal_LogicTreeModelSortAns(absCmd->m_object, false);
                    // return;
                }
            }
        } else {
            qDebug() << "sortLogicTreeNodes failed 2";
            emit CommunicationEngine::instance()->signal_LogicTreeModelSortAns(absCmd->m_object, false);
            return;
        }
    }
    for (auto it = gHashUuidToItemAdd.begin(); it != gHashUuidToItemAdd.end(); ++it)
        (*map)[it.key()] = it.value();
    emit CommunicationEngine::instance()->signal_LogicTreeModelSortAns(absCmd->m_object, true);
}

void CommunicationThread::clearLogicTreeNodesWhenReadXmlFalid(AbstractCmd *absCmd)
{
    LOG_ERROR("clearLogicTreeNodesWhenReadXmlFalid start");
    LOG_ERROR(QString("size is %1").arg(gHashUuidToItemAdd.size()));
    gHashParentUuidToChildrenUuids.clear();
    for (auto it = gHashUuidToItemAdd.begin(); it != gHashUuidToItemAdd.end(); ++it) {
        int count = it.value()->childCount();
        for (int i = 0; i < count; ++i)
            it.value()->takeChild(0);
    }
    QList<TreeItem *> tempCache;
    for (auto it = gHashUuidToItemAdd.begin(); it != gHashUuidToItemAdd.end(); ++it) {
        tempCache.push_back(it.value());
    }
    deleteFailedTreeItem(tempCache);
    gHashUuidToItemAdd.clear();
    LOG_ERROR("clearLogicTreeNodesWhenReadXmlFalid end");
}

void CommunicationThread::checkLogicTreeNodes(AbstractCmd *absCmd)
{
    auto [start, end] = BIND(absCmd, int, int);
    QString temp = QDateTime::currentDateTime().toString("hh:mm:ss:zzz");
    QList<QPair<int, TreeItem *>> errorList;
    // emit CommunicationEngine::instance()->signal_LogicTreeItemCheckAns(absCmd->m_object, errorList);
    // return;
    if (start == 0)
        start = 1;

    qDebug() << "start" << start << "end" << end;
    for (int i = start; i < end; ++i) {
        if (!gWriteXmlTreeItemList[i]->data(LogictreeMetaType::Column_ItemCheckRes, Qt::DisplayRole).toBool()) {
            errorList << QPair<int, TreeItem *>(i, gWriteXmlTreeItemList[i]);
        }
    }
    if (!errorList.isEmpty()) {
        qDebug() << "errorList size is11111 " << errorList.size();
    }
    emit CommunicationEngine::instance()->signal_LogicTreeItemCheckAns(absCmd->m_object, errorList);
}
