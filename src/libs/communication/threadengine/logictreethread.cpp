#include "communicationthread.h"
#include <QSet>
#include <QList>
#include "treemodel.h"
#include <QFontMetrics>
#include <QWidget>
#include "cobotlog.h"
#include "metalogictree.h"
#include "communication.h"
#include "metapath.h"
#include "udf.h"
#include "InoRobBusiness/Project/IProject.h"
#include "modulesutils.h"
#include "communication.h"
#include "fileutils.h"
#ifdef INOCOBOTTP_MSVC_QT5
    #include <QElapsedTimer>
#endif
using namespace Utils;

static unsigned int gCurrentLineNumber = 0;
static unsigned int gLevelIndention = 32;
static unsigned int gLevelCount = 0;
static unsigned int gTreeWidthRes = 0;
static unsigned int gItemExpandCount = 0;
static unsigned int gExpandTooMuchNeedMsgCount = 0;
static bool gLastIsNeedMsg = true;
static bool gIsNeedCalLineNumber = false;
static bool gIsNeedCalTreeWidth = false;
static bool gParentIsVisiable = true;
static bool gIsNeedOperationAll = false;
static bool gIsExpandAll = false;
void calTreeNodeLineNum(TreeItem *item)
{
    if (gIsNeedOperationAll)
        item->setData(1, gIsExpandAll, Qt::UserRole);
    if (gIsNeedCalLineNumber) {
        ++gCurrentLineNumber;
        if(!item->setData(1, gCurrentLineNumber, Qt::DisplayRole))
            --gCurrentLineNumber;
    }
    // qDebug()<<item->data(1, Qt::UserRole).toBool()<<item->data(0, Qt::DisplayRole).toString()<<gParentIsVisiable;
    int tempWidth = gLevelCount * gLevelIndention + 550 /*item->data(LogictreeMetaType::Column_Node, Qt::UserRole).toInt()*/;
    if (gIsNeedCalTreeWidth && gParentIsVisiable && gTreeWidthRes <= tempWidth) {
        gTreeWidthRes = tempWidth;
    }
    QVector<TreeItem *> children = item->children();
    bool temp = gParentIsVisiable;
    ++gLevelCount;
    gParentIsVisiable &= item->data(1, Qt::UserRole).toBool();
    if (gParentIsVisiable)
        gItemExpandCount++;
    for (auto &child : children) {
        calTreeNodeLineNum(child);
    }
    --gLevelCount;
    gParentIsVisiable = temp;
}

void CommunicationThread::calLineNum(AbstractCmd *absCmd)
{
    auto [lineNumber, itemWidth, operationAll, isExpand] = BIND(absCmd, bool, bool, bool, bool);
    gIsNeedCalLineNumber = true;
    gIsNeedCalTreeWidth = itemWidth;
    gCurrentLineNumber = 0;
    gTreeWidthRes = 0;
    gLevelCount = 0;
    gItemExpandCount = 0;
    gParentIsVisiable = true;
    gIsNeedOperationAll = operationAll;
    gIsExpandAll = isExpand;
    QElapsedTimer timer;
    timer.start();
    TreeModel *model = static_cast<TreeModel *>(Instance::logicTreeModel());
    QVector<TreeItem *> children = model->rootItem()->children();
    for (auto &child : children) {
        calTreeNodeLineNum(child);
    }

    QFontMetrics fontMetrics(((QWidget *)(Instance::mainWidget()))->font());
    int textWidth = fontMetrics.horizontalAdvance(QString::number(gCurrentLineNumber)) + 1;
    if (!itemWidth)
        gTreeWidthRes = -1;
    emit CommunicationEngine::instance()
        ->signal_rowCountMaxWidth(absCmd->m_object, textWidth, gTreeWidthRes);

    if (gItemExpandCount > 5000) {
        if (gLastIsNeedMsg) {
            ++gExpandTooMuchNeedMsgCount;
        } else
            gExpandTooMuchNeedMsgCount = 0;
        gLastIsNeedMsg = true;
    }

    if (gExpandTooMuchNeedMsgCount == 10) {
        gExpandTooMuchNeedMsgCount = 0;
        PRINT_MSG(tr("Too many items are expanded. Collapse unused ones to improve performance."));
    }

    LOG_INFO(QString("cal line number time elapsed : %1s ").arg(timer.elapsed() / 1000.0));
}

void CommunicationThread::logicTreeBreakPointOperation(AbstractCmd *absCmd)
{
    LOG_INFO("logicTreeBreakPointOperation start");
    auto [uuidList, address, targetType, isNeedSetType] = BIND(absCmd, QStringList, QVariant, LogictreeMetaType::LogicTreeBreakPointsType, bool);
    QString name = Communication::instance()->getActiveProjectName();
    QString localPath = CONTROLLER_PROJECT_PATH(name) + "/Data/breakpoint.data";
    std::string remotePath = "./TeachProgram/" + name.toStdString() + "/Data/breakpoint.data";
    bool isLocalAddress = Communication::instance()->isConnectVirtualController();
    if (isLocalAddress) {
        remotePath = ProjectHelper::VirtualControllerDataFolder(name.toStdString()) + "breakpoint.data";
    }
    QString localPathTemp = "./breakpoint.data.tmp";
    QFile file(localPathTemp);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        LOG_ERROR("Open file failed when write breakpoints");
        emit CommunicationEngine::instance()->signal_setLogicTreeItemBreakPointsAns(false, address, targetType, isNeedSetType);
        return;
    }
    int size = uuidList.size();
    QByteArray data;
    for (int i = 0; i < size; ++i) {
        data.append(uuidList[i].toUtf8());
        data.append("\n");
    }
    file.write(data);
    file.close();
    UDF udf;

    if (isLocalAddress) {
        if (FileExist(remotePath)) {
            FileDelete(remotePath);
        }
        if (!FileCopy(localPathTemp.toStdString(), remotePath)) {
            emit CommunicationEngine::instance()->signal_setLogicTreeItemBreakPointsAns(false, address, targetType, isNeedSetType);
            return;
        }
    } else {
        if (!udf.uploadFile(remotePath, localPathTemp.toStdString())) {
            emit CommunicationEngine::instance()->signal_setLogicTreeItemBreakPointsAns(false, address, targetType, isNeedSetType);
            return;
        }
    }

    int ret = Communication::instance()->project()->requireControllerReloadBreakPointsFile();
    if(ret != ERROR_OK){
        if (isLocalAddress) {
            if (!FileCopy(localPath.toStdString(), remotePath)) {
                PRINT_ERROR(tr("Failed to restore the breakpoint file."));
            }
        } else {
            if(!udf.uploadFile(remotePath, localPath.toStdString())){
                PRINT_ERROR(tr("Failed to restore the breakpoint file."));
            }
        }
        PRINT_ERROR(tr("Failed to set the controller breakpoint status, return value is %1.").arg(QString::number(ret)));
        emit CommunicationEngine::instance()->signal_setLogicTreeItemBreakPointsAns(false, address, targetType, isNeedSetType);
        return;
    }
    if(!FileUtils::copyFile(localPathTemp, localPath)){
        LOG_ERROR("Copy breakpoint file failed.");
    }
    emit CommunicationEngine::instance()->signal_setLogicTreeItemBreakPointsAns(true, address, targetType, isNeedSetType);
    LOG_INFO("logicTreeBreakPointOperation end");
}

void CommunicationThread::setEnabledAllBreakPoints(AbstractCmd *absCmd)
{
    auto [enable] = BIND(absCmd, bool);
    int target = enable ? 1 : 0;
    bool ans = (Communication::instance()->project()->setControllerEnableAllBreakPointsState(target) == ERROR_OK);
    if(ans){
        SHOW_MSG(enable ? tr("Sent command to enable all breakpoints") : tr("Sent command to disable all breakpoints"));
    }else{
        emit CommunicationEngine::instance()->signal_needMainWidgetError("Failed to set breakpoint status.");
    }
    emit CommunicationEngine::instance()->signal_setBreakPointsEnabledIsSuccess(ans, enable);
}

void CommunicationThread::getEnabledAllBreakPoints(AbstractCmd *absCmd)
{
    int target = 0;
    bool ans = (Communication::instance()->project()->getControllerEnableAllBreakPointsState(target) == ERROR_OK);
    bool enable = (target != 0);
    if(!ans){
        LOG_ERROR("read breakpoints status failed.");
        emit CommunicationEngine::instance()->signal_needMainWidgetError(tr("Failed to get breakpoint status. Please try to set break points status."));
        return;
    }
    emit CommunicationEngine::instance()->signal_setBreakPointsEnabledIsSuccess(ans, enable);
}

void CommunicationThread::setLogicTreeStartLine(AbstractCmd *absCmd)
{
    auto [exeFlow, uuid] = BIND(absCmd, std::vector<int>, QString);

    LOG_INFO(QString("setLogicTreeStartLine, start, uuid = %1").arg(uuid));

    int ret = Communication::instance()->project()->setControllerStartLine(exeFlow, uuid.toStdString());
    if (ret != ERROR_OK) {
        emit CommunicationEngine::instance()->signal_setLogicTreeStartLine_result(false, uuid);
    } else {
        emit CommunicationEngine::instance()->signal_setLogicTreeStartLine_result(true, uuid);
    }
    LOG_INFO("setLogicTreeStartLine, end");
}

void CommunicationThread::getLogicTreeStartLine(AbstractCmd *absCmd)
{
    std::string uuid;
    bool ans = (Communication::instance()->project()->getControllerStartLine(uuid) == ERROR_OK);
    LOG_INFO(QString("getLogicTreeStartLine, start, uuid=%1, ans=%2").arg(QString::fromStdString(uuid), QString::number(ans)));
    emit CommunicationEngine::instance()->signal_getLogicTreeStartLine_result(QString::fromStdString(uuid));
    LOG_INFO("getLogicTreeStartLine, end");
}

void CommunicationThread::setRGB(AbstractCmd *absCmd)
{
    auto [data] = BIND(absCmd, uint32_t);
    // bool ans = (Communication::instance()->project()->setRGB(data) == ERROR_OK);
}

