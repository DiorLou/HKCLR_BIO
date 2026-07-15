#pragma once
#include <string>
#include <QObject>
#include "dllspec.h"
#include "DataTypeDef.h"
#include "signal_slot.h"
#include "../../Project/ProjectHelper.h"

/*
    Create by LiaoChuanMing at 2023/11/13，任务处理类
*/
namespace InoRobBusiness
{

#pragma region 常量与数据类型

#define MAX_TASK_NUM 16  // 最大任务数量

/// <summary>
/// 任务状态
/// </summary>
enum class TaskStatus : int8u
{
    /// <summary>
    /// 停止
    /// </summary>
    TASK_STOP = 0,
    /// <summary>
    /// 运行
    /// </summary>
    TASK_RUNNING = 1,
    /// <summary>
    /// 单步
    /// </summary>
    TASK_STEP = 2,
    /// <summary>
    /// 暂停
    /// </summary>
    TASK_PAUSED = 4,
    /// <summary>
    /// 结束
    /// </summary>
    TASK_FINISHED = 10,
    /// <summary>
    /// 未激活
    /// </summary>
    TASK_INACTIVED = 100,
    /// <summary>
    /// 空闲
    /// </summary>
    TASK_FREE = 255,
};

/// <summary>
/// 断点命中状态
/// </summary>
enum class BreakpointFlag : int8u
{
    /// <summary>
    /// 未命中
    /// </summary>
    NO_HITTING = 0,
    /// <summary>
    /// 命中
    /// </summary>
    HITTING,
};

/// <summary>
/// 单个任务的信息
/// </summary>
#pragma pack(1)
typedef struct _TaskRunInfoItem
{
    _TaskRunInfoItem()
    {
        Initialize();
    }

    void Initialize()
    {
        startLineNum = 0;
        runLineNum = 0;
        status = (int8u)TaskStatus::TASK_STOP;
        breakpointFlag = (int8u)BreakpointFlag::NO_HITTING;
        memset(&startLineProgram[0], 0, 32 * sizeof(char));
        memset(&runLineProgram[0], 0, 32 * sizeof(char));
    }

    _TaskRunInfoItem &operator=(const _TaskRunInfoItem &other)
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

    bool operator==(const _TaskRunInfoItem &other)
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
} TaskRunInfoItem;
#pragma pack()

/// <summary>
/// 所有任务的信息集合
/// </summary>
#pragma pack(1)
typedef struct _TaskRunInfo
{
    _TaskRunInfo()
    {
        Initialize();
    }

    void Initialize()
    {
        for (size_t i = 0; i < MAX_TASK_NUM; i++)
        {
            this->infos[i].Initialize();
        }
    }

    _TaskRunInfo &operator=(const _TaskRunInfo &other)
    {
        for (size_t i = 0; i < MAX_TASK_NUM; i++)
        {
            this->infos[i] = other.infos[i];
        }
        return (*this);
    }

    bool operator==(const _TaskRunInfo &other)
    {
        bool isEqual = true;
        for (size_t i = 0; i < MAX_TASK_NUM; i++)
        {
            if (!(this->infos[i] == other.infos[i]))
            {
                isEqual = false;
                break;
            }
        }
        return isEqual;
    }

    TaskRunInfoItem infos[MAX_TASK_NUM];  // 所有任务集合
} TaskRunInfo;
#pragma pack()

typedef struct _TaskStatusArr
{
    _TaskStatusArr()
    {
        Initialize();
    }

    void Initialize()
    {
        for (size_t i = 0; i < MAX_TASK_NUM; i++)
        {
            this->isChanged[i] = false;
            this->status[i] = TaskStatus::TASK_STOP;
        }
    }

    bool isChanged[MAX_TASK_NUM];     // 所有任务状态是否变化的标志集合
    TaskStatus status[MAX_TASK_NUM];  // 所有任务状态集合
} TaskStatusArr;

#pragma endregion 常量与数据类型

class INOROBBUSINESS_CLASS ITask : public QObject
{
    Q_OBJECT

public:
    virtual ~ITask()
    {
    }
    /*!
     * \brief 初始化
     */
    virtual void init() = 0;
    /// <summary>
    /// 设置当前调试的任务id
    /// </summary>
    /// <param name="taskId">输入，任务id</param>
    virtual void setDebuggingTask(int taskId) = 0;
    /// <summary>
    /// 获取当前正在调试的任务id
    /// </summary>
    virtual int getDebuggingTask() = 0;
    // 任务运行信息变化信号(只发送当前正在调试的任务的运行信息)
    virtual void OnTaskRunInfoChanged(const TaskRunInfoItem &info) = 0;
    // 任务运行状态变化信号
    virtual void OnTaskRunStatusChanged(const TaskRunInfo &infos) = 0;

    /// <summary>
    /// 所有任务返回起始行
    /// </summary>
    /// <returns>成功返回0，失败请查看错误码</returns>
    virtual int returnStartLineAll() = 0;
    /// <summary>
    /// 单个任务返回起始行
    /// </summary>
    /// <param name="taskId">输入，任务id</param>
    /// <returns>成功返回0，失败请查看错误码</returns>
    virtual int returnStartLineSingle(int taskId) = 0;
    /// <summary>
    /// 设置起始行
    /// </summary>
    /// <param name="taskId">输入，任务id</param>
    /// <param name="lineNum">输入，行号</param>
    /// <param name="fileName">输入，程序文件名称</param>
    /// <returns>成功返回0，失败请查看错误码</returns>
    virtual int setStartLine(int taskId, int lineNum, const std::string &fileName) = 0;

    /// <summary>
    /// 获取所有任务的运行信息
    /// </summary>
    /// <param name="infos">输出，运行信息集合</param>
    /// <returns>成功返回0，失败请查看错误码</returns>
    virtual int getAllTaskInfo(TaskRunInfo &infos, bool isPrintErr = true) = 0;
    /// <summary>
    /// 通过任务id获取对应的程序文件名称
    /// </summary>
    /// <param name="taskId">输入，任务id</param>
    /// <param name="fileName">输出，程序文件名称</param>
    /// <returns>成功返回0，失败请查看错误码</returns>
    virtual int getFileNameById(int taskId, std::string &fileName) = 0;
    /// <summary>
    /// 获取单个任务的运行信息
    /// </summary>
    /// <param name="info">输出，单个任务的运行信息</param>
    /// <param name="taskId">输入，任务id</param>
    /// <returns>成功返回0，失败请查看错误码</returns>
    virtual int getTaskInfo(TaskRunInfoItem &info, int taskId) = 0;
    /// <summary>
    /// 获取单个任务的运行状态
    /// </summary>
    /// <param name="status">输出，单个任务的运行状态</param>
    /// <param name="taskId">输入，任务id</param>
    /// <returns>成功返回0，失败请查看错误码</returns>
    virtual int getTaskStatus(TaskStatus &status, int taskId) = 0;

    /// <summary>
    /// 设置所有任务的激活状态
    /// </summary>
    /// <param name="flags">输入，任务激活状态集合，1-激活，0-不激活</param>
    /// <returns>成功返回0，失败请查看错误码</returns>
    virtual int setTaskActiveFlag(int8u flags[MAX_TASK_NUM]) = 0;
    /// <summary>
    /// 设置指定任务的激活状态
    /// </summary>
    /// <param name="taskId">输入，任务id</param>
    /// <param name="flag">输入，true-激活，false-不激活</param>
    /// <returns>成功返回0，失败请查看错误码</returns>
    virtual int setTaskActiveFlag(int taskId, bool flag) = 0;
    /// <summary>
    /// 获取所有任务的激活状态(坑，这里其实获取的是任务类型，暂时弃用)
    /// </summary>
    /// <param name="flags">输出，任务激活状态集合，1-激活，0-不激活</param>
    /// <returns>成功返回0，失败请查看错误码</returns>
    virtual int getTaskActiveFlag(int8u flags[MAX_TASK_NUM]) = 0;

    /// <summary>
    /// 根据任务id获取对应的程序文件集合
    /// </summary>
    /// <param name="taskId">输入，任务id</param>
    /// <param name="programs">输出，程序文件名称集合</param>
    /// <returns>成功返回0，失败请查看错误码</returns>
    virtual int getProgramsInTask(int taskId, std::vector<std::string> &programs) = 0;

    /**
     * @brief 检查是否允许启动运行
     * @return true-允许启动，false-不允许启动
     */
    virtual bool checkStartRunStatus() = 0;
    /// <summary>
    /// 检查是否允许任务启动
    /// </summary>
    /// <param name="taskId">输入，任务id</param>
    /// <returns>true-允许启动，false-不允许启动</returns>
    virtual bool checkTaskStartPermission(int taskId) = 0;

    /// <summary>
    /// 获取任务类型对应的名称
    /// </summary>
    /// <param name="type">输入，任务类型</param>
    virtual std::string getTaskTypeName(TaskType type) = 0;
    /// <summary>
    /// 获取任务状态对应的描述
    /// </summary>
    /// <param name="status">输入，任务状态</param>
    virtual std::string getTaskStatusDescription(TaskStatus status) = 0;

    /*!
     * \brief 检测是否有非静态任务运行中
     * \return 有则返回true, 无则返回false
     */
    virtual bool checkTaskRunning() = 0;

Q_SIGNALS:
    // 任务运行信息变化信号(只发送当前正在调试的任务的运行信息)
    void sigTaskRunInfoChanged(TaskRunInfoItem info);
    // 任务运行状态变化信号
    void sigTaskRunStatusChanged(TaskStatusArr status);
};
}  // namespace InoRobBusiness
