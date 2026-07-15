#pragma once

#include <QObject>
#include "communication_global.h"
#include "task.h"

namespace InoRobBusiness
{
class IController;
}  // namespace InoRobBusiness

class Communication;

class COMMUNICATION_EXPORT TaskInterface
{
public:
    TaskInterface()
    {
    }

    virtual Communication *comm() = 0;
    virtual InoRobBusiness::IController *controller() = 0;

    QVector<InoTaskInfo> getTaskList();
    InoTaskStatus getTaskStatus(int taskId);
    bool activeTask(int nTaskId, bool isActive);

    bool isTaskExist(int nTaskId);
    bool addTask(int nTaskId, int nTaskType, const QString &taskFileName);
    bool deleteTask(int nTaskId);
};
