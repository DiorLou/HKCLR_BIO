#pragma once
#include "dllspec.h"
#include "IInoRobBusiness.h"
#include "../../Project/ProjectHelper_V1.h"

using namespace InoRobBusiness;

#pragma region 常量与数据类型

#define MAX_TASK_NUM_V1 16  // 最大任务数量

/// <summary>
/// 任务状态
/// </summary>
enum class TaskStatus_V1 : int8u
{
    /// <summary>
    /// 停止
    /// </summary>
    TASK_STOP_V1 = 0,
    /// <summary>
    /// 运行
    /// </summary>
    TASK_RUNNING_V1 = 1,
    /// <summary>
    /// 单步
    /// </summary>
    TASK_STEP_V1 = 2,
    /// <summary>
    /// 暂停
    /// </summary>
    TASK_PAUSED_V1 = 4,
    /// <summary>
    /// 结束
    /// </summary>
    TASK_FINISHED_V1 = 10,
    /// <summary>
    /// 未激活
    /// </summary>
    TASK_INACTIVED_V1 = 100,
    /// <summary>
    /// 空闲
    /// </summary>
    TASK_FREE_V1 = 255,
};

/// <summary>
/// 断点命中状态
/// </summary>
enum class BreakpointFlag_V1 : int8u
{
    /// <summary>
    /// 未命中
    /// </summary>
    NO_HITTING_V1 = 0,
    /// <summary>
    /// 命中
    /// </summary>
    HITTING_V1,
};

/// <summary>
/// 单个任务的信息
/// </summary>
#pragma pack(1)
typedef struct _TaskRunInfoItem_V1
{
    _TaskRunInfoItem_V1()
    {
        Initialize();
    }

    void Initialize()
    {
        startLineNum = 0;
        runLineNum = 0;
        status = (int8u)TaskStatus_V1::TASK_STOP_V1;
        breakpointFlag = (int8u)BreakpointFlag_V1::NO_HITTING_V1;
        memset(&startLineProgram[0], 0, 32 * sizeof(char));
        memset(&runLineProgram[0], 0, 32 * sizeof(char));
    }

    _TaskRunInfoItem_V1 &operator=(const _TaskRunInfoItem_V1 &other)
    {
        this->startLineNum = other.startLineNum;
        this->runLineNum = other.runLineNum;
        this->status = other.status;
        this->breakpointFlag = other.breakpointFlag;
        for (size_t i = 0; i < 32; i++)
        {
            this->startLineProgram[i] = other.startLineProgram[i];
        }
        for (size_t i = 0; i < 32; i++)
        {
            this->runLineProgram[i] = other.runLineProgram[i];
        }
        return (*this);
    }

    bool operator==(const _TaskRunInfoItem_V1 &other)
    {
        return ((this->startLineNum == other.startLineNum)
                && (this->runLineNum == other.runLineNum)
                && (this->status == other.status)
                && (this->breakpointFlag == other.breakpointFlag)
                && (std::strcmp(this->startLineProgram, other.startLineProgram) == 0)
                && (std::strcmp(this->runLineProgram, other.runLineProgram) == 0));
    }

    int16u startLineNum;        // 启动行（对应PC编程平台界面黄色光标）
    int16u runLineNum;          // 运行行（对应机器人光标）
    int8u status;               // 任务状态（对应枚举TaskStatus）
    int8u breakpointFlag;       // 断点标志，0未进入断点，1进入断点
    char startLineProgram[32];  // 启动行所在程序名称，如main.pro
    char runLineProgram[32];    // 运行行所在程序名称，如main.pro
} TaskRunInfoItem_V1;
#pragma pack()

/// <summary>
/// 所有任务的信息集合
/// </summary>
#pragma pack(1)
typedef struct _TaskRunInfo_V1
{
    _TaskRunInfo_V1()
    {
        Initialize();
    }

    void Initialize()
    {
        for (size_t i = 0; i < MAX_TASK_NUM_V1; i++)
        {
            this->infos[i].Initialize();
        }
    }

    _TaskRunInfo_V1 &operator=(const _TaskRunInfo_V1 &other)
    {
        for (size_t i = 0; i < MAX_TASK_NUM_V1; i++)
        {
            this->infos[i] = other.infos[i];
        }
        return (*this);
    }

    bool operator==(const _TaskRunInfo_V1 &other)
    {
        bool isEqual = true;
        for (size_t i = 0; i < MAX_TASK_NUM_V1; i++)
        {
            if (!(this->infos[i] == other.infos[i]))
            {
                isEqual = false;
                break;
            }
        }
        return isEqual;
    }

    TaskRunInfoItem_V1 infos[MAX_TASK_NUM_V1];  // 所有任务集合
} TaskRunInfo_V1;
#pragma pack()

typedef struct _TaskStatusArr_V1
{
    _TaskStatusArr_V1()
    {
        Initialize();
    }

    void Initialize()
    {
        for (size_t i = 0; i < MAX_TASK_NUM_V1; i++)
        {
            this->isChanged[i] = false;
            this->status[i] = TaskStatus_V1::TASK_STOP_V1;
        }
    }

    bool isChanged[MAX_TASK_NUM_V1];        // 所有任务状态是否变化的标志集合
    TaskStatus_V1 status[MAX_TASK_NUM_V1];  // 所有任务状态集合
} TaskStatusArr_V1;

#pragma endregion

namespace InoRobBusinessProxy
{
class INOROBBUSINESSPROXY_CLASS Task_V1 : public QObject
{
    Q_OBJECT
#pragma region 数据转换

public:
    static TaskStatus_V1 TaskStatus_ToProxy(TaskStatus taskStatus);
    static TaskStatus TaskStatus_FromProxy(TaskStatus_V1 taskStatus_V1);

    static BreakpointFlag_V1 BreakpointFlag_ToProxy(BreakpointFlag breakpointFlag);
    static BreakpointFlag BreakpointFlag_FromProxy(BreakpointFlag_V1 breakpointFlag_V1);

    static bool TaskRunInfoItem_ToProxy(const _TaskRunInfoItem &taskRunInfoItem, TaskRunInfoItem_V1 &taskRunInfoItem_V1);
    static bool TaskRunInfoItem_FromProxy(const TaskRunInfoItem_V1 &taskRunInfoItem_V1, _TaskRunInfoItem &taskRunInfoItem);

    static bool TaskRunInfo_ToProxy(const TaskRunInfo &taskRunInfo, TaskRunInfo_V1 &taskRunInfo_V1);
    static bool TaskRunInfo_FromProxy(const TaskRunInfo_V1 &taskRunInfo_V1, TaskRunInfo &taskRunInfo);

    static bool TaskStatusArr_ToProxy(const TaskStatusArr &taskStatusArr, TaskStatusArr_V1 &taskStatusArr_V1);
    static bool TaskStatusArr_FromProxy(const TaskStatusArr_V1 &taskStatusArr_V1, TaskStatusArr &taskStatusArr);

#pragma endregion

#pragma region 构造与析构

private:
    ITask *_task = nullptr;

public:
    Task_V1(ITask *task);
    ~Task_V1();

#pragma endregion

#pragma region 业务逻辑

public:
    /// <summary>
    /// 设置当前调试的任务id
    /// </summary>
    /// <param name="taskId">输入，任务id</param>
    void setDebuggingTask(int taskId);
    /// <summary>
    /// 获取当前正在调试的任务id
    /// </summary>
    int getDebuggingTask();
    // 任务运行信息变化信号(只发送当前正在调试的任务的运行信息)
    rsignal<TaskRunInfoItem_V1> sigTaskRunInfoChanged;
    void sigTaskRunInfoChangedHandler(_TaskRunInfoItem sigTaskRunInfoChangedData);

    // 任务运行状态变化信号
    rsignal<TaskStatusArr_V1> sigTaskRunStatusChanged;
    void sigTaskRunStatusChangedHandler(TaskStatusArr sigTaskRunStatusChangedData);

    /// <summary>
    /// 所有任务返回起始行
    /// </summary>
    /// <returns>成功返回0，失败请查看错误码</returns>
    int returnStartLineAll();
    /// <summary>
    /// 单个任务返回起始行
    /// </summary>
    /// <param name="taskId">输入，任务id</param>
    /// <returns>成功返回0，失败请查看错误码</returns>
    int returnStartLineSingle(int taskId);
    /// <summary>
    /// 设置起始行
    /// </summary>
    /// <param name="taskId">输入，任务id</param>
    /// <param name="lineNum">输入，行号</param>
    /// <param name="fileName">输入，程序文件名称</param>
    /// <returns>成功返回0，失败请查看错误码</returns>
    int setStartLine(int taskId, int lineNum, const std::string &fileName);

    /// <summary>
    /// 获取所有任务的运行信息
    /// </summary>
    /// <param name="infos">输出，运行信息集合</param>
    /// <returns>成功返回0，失败请查看错误码</returns>
    int getAllTaskInfo(TaskRunInfo_V1 &infos, bool isPrintErr = true);
    /// <summary>
    /// 通过任务id获取对应的程序文件名称
    /// </summary>
    /// <param name="taskId">输入，任务id</param>
    /// <param name="fileName">输出，程序文件名称</param>
    /// <returns>成功返回0，失败请查看错误码</returns>
    int getFileNameById(int taskId, std::string &fileName);
    /// <summary>
    /// 获取单个任务的运行信息
    /// </summary>
    /// <param name="info">输出，单个任务的运行信息</param>
    /// <param name="taskId">输入，任务id</param>
    /// <returns>成功返回0，失败请查看错误码</returns>
    int getTaskInfo(TaskRunInfoItem_V1 &info, int taskId);  //  --  已测
    /// <summary>
    /// 获取单个任务的运行状态
    /// </summary>
    /// <param name="status">输出，单个任务的运行状态</param>
    /// <param name="taskId">输入，任务id</param>
    /// <returns>成功返回0，失败请查看错误码</returns>
    int getTaskStatus(TaskStatus_V1 &status, int taskId);

    /// <summary>
    /// 设置所有任务的激活状态
    /// </summary>
    /// <param name="flags">输入，任务激活状态集合，1-激活，0-不激活</param>
    /// <returns>成功返回0，失败请查看错误码</returns>
    int setTaskActiveFlag(int8u flags[MAX_TASK_NUM_V1]);
    /// <summary>
    /// 设置指定任务的激活状态
    /// </summary>
    /// <param name="taskId">输入，任务id</param>
    /// <param name="flag">输入，true-激活，false-不激活</param>
    /// <returns>成功返回0，失败请查看错误码</returns>
    int setTaskActiveFlag(int taskId, bool flag);
    /// <summary>
    /// 获取所有任务的激活状态(坑，这里其实获取的是任务类型，暂时弃用)
    /// </summary>
    /// <param name="flags">输出，任务激活状态集合，1-激活，0-不激活</param>
    /// <returns>成功返回0，失败请查看错误码</returns>
    int getTaskActiveFlag(int8u flags[MAX_TASK_NUM_V1]);

    /// <summary>
    /// 根据任务id获取对应的程序文件集合
    /// </summary>
    /// <param name="taskId">输入，任务id</param>
    /// <param name="programs">输出，程序文件名称集合</param>
    /// <returns>成功返回0，失败请查看错误码</returns>
    int getProgramsInTask(int taskId, std::vector<std::string> &programs);

    /// <summary>
    /// 检查是否允许任务启动
    /// </summary>
    /// <param name="taskId">输入，任务id</param>
    /// <returns>true-允许启动，false-不允许启动</returns>
    bool checkTaskStartPermission(int taskId);

    /// <summary>
    /// 获取任务类型对应的名称
    /// </summary>
    /// <param name="type">输入，任务类型</param>
    std::string getTaskTypeName(TaskType_V1 type);
    /// <summary>
    /// 获取任务状态对应的描述
    /// </summary>
    /// <param name="status">输入，任务状态</param>
    std::string getTaskStatusDescription(TaskStatus_V1 status);

    /*!
     * \brief 检测是否有非静态任务运行中
     * \return 有则返回true, 无则返回false
     */
    bool checkTaskRunning();

#pragma endregion
};
}  // namespace InoRobBusinessProxy
