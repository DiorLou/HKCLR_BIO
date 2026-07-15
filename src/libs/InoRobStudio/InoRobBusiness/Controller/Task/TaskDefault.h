#pragma once
#include <string>
#include <mutex>
#include "IInoRobBusiness.h"

namespace InoRobBusiness
{
class INOROBBUSINESS_CLASS TaskDefault : public ITask
{
    Q_OBJECT

public:
    TaskDefault(string name, IDataSrvBase *dataService, QObject *parent = nullptr);
    virtual ~TaskDefault();
    void init() override;

public:
    virtual void setDebuggingTask(int taskId) override;
    virtual int getDebuggingTask() override;
    virtual void OnTaskRunInfoChanged(const TaskRunInfoItem &info) override;
    virtual void OnTaskRunStatusChanged(const TaskRunInfo &infos) override;

    virtual int returnStartLineAll() override;
    virtual int returnStartLineSingle(int taskId) override;
    virtual int setStartLine(int taskId, int lineNum, const std::string &fileName) override;

    virtual int getAllTaskInfo(TaskRunInfo &infos, bool isPrintErr = true) override;
    virtual int getFileNameById(int taskId, std::string &fileName) override;
    virtual int getTaskInfo(TaskRunInfoItem &info, int taskId) override;
    virtual int getTaskStatus(TaskStatus &status, int taskId) override;

    virtual int setTaskActiveFlag(int8u flags[MAX_TASK_NUM]) override;
    virtual int setTaskActiveFlag(int taskId, bool flag) override;
    virtual int getTaskActiveFlag(int8u flags[MAX_TASK_NUM]) override;

    virtual int getProgramsInTask(int taskId, std::vector<std::string> &programs) override;

    virtual bool checkStartRunStatus() override;
    virtual bool checkTaskStartPermission(int taskId) override;

    virtual std::string getTaskTypeName(TaskType type) override;
    virtual std::string getTaskStatusDescription(TaskStatus status) override;

    // 检测是否有非静态任务运行中
    virtual bool checkTaskRunning() override;

private:
    // 初始化程序最新运行信息，在设置起始行和重置起始行前，确保信号的发送，触发UI刷新
    void initTaskRunInfoItem();

private:
    IDataSrvBase *_pDataSrv = nullptr;
    IProject *_pProject = nullptr;
    ITransfor *_pTransfor = nullptr;

    int _debuggingTaskId;              // 当前正在调试的任务id（即界面选中的任务id）
    std::mutex _taskIdMtx;             // 任务id互斥锁
    std::mutex _taskStatusMtx;         // 任务状态互斥锁
    std::mutex _taskRunLineFlagMtx;    // 任务运行行号是否判断变化的标志位互斥锁
    TaskRunInfoItem _taskRunInfoItem;  // 当前正在调试的任务的最新运行信息
    TaskStatusArr _taskStatus;         // 任务状态
};
}  // namespace InoRobBusiness
