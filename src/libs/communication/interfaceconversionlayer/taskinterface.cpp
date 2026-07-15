#include "taskinterface.h"
#include <QDebug>
#include "communication.h"
#include "IController.h"
#include "metatypeconversion.h"
#include "cobotlogex.h"
#include "modulesutils.h"

QVector<InoTaskInfo> TaskInterface::getTaskList()
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    std::vector<MultiTaskInfo> taskInfos = comm()->project()->GetTaskManageConfig();
    #if defined(INOCOBOTTP_MSVC_QT5)
    QVector<InoTaskInfo> taskInfoList = MetaTypeConversion::tp2InoApi_taskInfo(taskInfos);
    #else
    QList<InoTaskInfo> taskInfoList = MetaTypeConversion::tp2InoApi_taskInfo(taskInfos);
    #endif

    comm()->setMultiTaskNameList(taskInfoList);

    FREQ_LOG_PRINT_TIMESTAMP
    return taskInfoList;
}

InoTaskStatus TaskInterface::getTaskStatus(int taskId)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    InoTaskStatus taskStatus = TaskStatus_Finished;

    InoRobBusiness::TaskStatus status;
    int nRet = _ITask->getTaskStatus(status, taskId);
    if (ERR_OK == nRet) {
        taskStatus = MetaTypeConversion::tp2InoApi_taskStatus(status);
    }

    FREQ_LOG_PRINT_TIMESTAMP
    return taskStatus;
}

bool TaskInterface::activeTask(int nTaskId, bool isActive)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    int nRet = _ITask->setTaskActiveFlag(nTaskId, isActive);
    FREQ_LOG_PRINT_TIMESTAMP
    return (ERR_OK == nRet);
}

bool TaskInterface::isTaskExist(int nTaskId)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    bool ret = comm()->project()->IsTaskExisted(nTaskId);
    FREQ_LOG_PRINT_TIMESTAMP

    return ret;
}

bool TaskInterface::addTask(int nTaskId, int nTaskType, const QString &taskFileName)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    bool bRet = comm()->project()->IsTaskExisted(nTaskId);
    if (bRet) {
        int nRet = comm()->project()->ModifyTaskInfo(nTaskId, nTaskType,
                                                     taskFileName.toStdString());
        if (ERR_OK == nRet) {
            bRet = true;
        }
    } else {
        MultiTaskInfo info;
        info.taskId = nTaskId;
        info.taskType = nTaskType;
        info.enterProgramFile = std::string(taskFileName.toStdString());
        info.isActive = true;

        int nRet = comm()->project()->AddTask(info);
        if (ERR_OK == nRet) {
            bRet = true;
        }
    }

    if (bRet) {
        getTaskList();
    }

    FREQ_LOG_PRINT_TIMESTAMP
    return bRet;
}

bool TaskInterface::deleteTask(int nTaskId)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    int nRet = comm()->project()->DelTask(nTaskId);
    if (ERR_OK == nRet) {
        getTaskList();
    }

    FREQ_LOG_PRINT_TIMESTAMP
    return (nRet == ERR_OK);
}
