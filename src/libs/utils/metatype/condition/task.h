#pragma once
#include <QMetaType>
#include <QVariant>

const int MAX_TASK_COUNT = 16;

enum TaskCondType {
    TaskCondType_Main = 0,
    TaskCondType_Static = 1,
    TaskCondType_Dynamic
};
Q_DECLARE_METATYPE(TaskCondType)

enum InoTaskStatus {
    TaskStatus_Stop = 0,         // 停止
    TaskStatus_Running = 1,      // 运行
    TaskStatus_Step = 2,         // 单步
    TaskStatus_Paused = 4,       // 暂停
    TaskStatus_Finished = 10,    // 结束
    TaskStatus_InActived = 100,  // 未激活
    TaskStatus_Free = 255        // 空闲
};
Q_DECLARE_METATYPE(InoTaskStatus)

typedef struct InoTaskInfo {
    int nTaskId {0};
    QString sTaskName;
    int nTaskType;
    QString sTaskFileName;
    bool isActive;  // 是否激活
    InoTaskStatus status;

    QVariant getData(int index) const
    {
        switch (index) {
        case 0:
            return this->nTaskId;
        case 1:
            return this->sTaskName;
        case 2:
            return this->isActive;
        case 3:
            return this->status;
        case 4:
            return this->sTaskFileName;
        case 5:
            return this->nTaskType;
        default:
            break;
        }
        return QString();
    }

            // 根据下标设置对应数据
    void setData(int index, bool value)
    {
        switch (index) {
        case 2:
            this->isActive = value;
            break;
        default:
            break;
        }
    }

    bool operator==(const InoTaskInfo &other) const
    {
        return (nTaskId == other.nTaskId
                && sTaskName.compare(other.sTaskName) == 0
                && nTaskType == other.nTaskType
                && sTaskFileName.compare(other.sTaskFileName) == 0);
    }
} InoTaskInfo;
Q_DECLARE_METATYPE(InoTaskInfo)

typedef struct InoTaskStatusArr {
    bool isChanged[MAX_TASK_COUNT] = {false};                       // 所有任务状态是否变化的标志集合
    InoTaskStatus status[MAX_TASK_COUNT] = {TaskStatus_InActived};  // 所有任务状态集合
} InoTaskStatusArr;
Q_DECLARE_METATYPE(InoTaskStatusArr)
