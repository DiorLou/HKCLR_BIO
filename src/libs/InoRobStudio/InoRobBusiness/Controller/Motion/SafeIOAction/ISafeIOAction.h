#pragma once
#include <QObject>
#include "dllspec.h"
#include <string>
#include <vector>

namespace InoRobBusiness
{
constexpr int SAFE_IO_ACTION_MAX_NUM = 16;         // 允许的动作最大数量
constexpr int SAFE_IO_ACTION_EXEC_TIMEOUT = 3000;  // 动作默认执行超时时间（毫秒）

/**
 * @brief 安全IO动作到位动作IO项（多个IO项组成一个条件项）
 */
struct SafeIOActionFinishIOItem
{
    int ioIndex = 0;   // IO编号
    int ioValue = 0;   // IO值
    int relation = 1;  // 与其它项的关系（1:AND，2:OR）

    SafeIOActionFinishIOItem()
    {
        ioIndex = 0;
        ioValue = 0;
        relation = 1;
    }

    SafeIOActionFinishIOItem(int _ioIndex, int _ioValue, int _relation)
    {
        ioIndex = _ioIndex;
        ioValue = _ioValue;
        relation = _relation;
    }
};

/**
 * @brief 安全IO动作到位动作IO项（多个IO项组成一个条件项）
 */
struct SafeIOActionFinishItem
{
    int index = 0;                                  // 序号
    std::string desc;                               // 备注
    std::vector<SafeIOActionFinishIOItem> ioItems;  // 值（IO项列表）
};

struct SafeIOActionExecItem
{
    int index = 0;     // 序号
    std::string desc;  // 备注
    int ioIndex = 0;   // IO编号
    int ioValue = 0;   // IO值
};

/**
 * @brief 安全IO动作安全区域
 */
struct SafeIOActionSafeArea
{
    bool enable = true;          // 是否启用安全区域
    double x = 0.000;            // 空间X坐标
    double y = 0.000;            // 空间Y坐标
    double z = 0.000;            // 空间Z坐标
    float sideLength = 100.000;  // 正文体边长
};

/**
 * @brief 安全IO动作项
 */
struct SafeIOActionItem
{
    int index = 0;                                    // 序号
    std::string desc;                                 // 备注
    std::string cmd;                                  // 指令
    int cmdFlag = 0;                                  // 指令标识
    SafeIOActionSafeArea safeArea;                    // 安全区域
    std::vector<SafeIOActionExecItem> execItems;      // 执行动作
    std::vector<SafeIOActionFinishItem> finishItems;  // 动作到位判断
};

/**
 * @brief 安全IO动作数据
 */
struct SafeIOActionData
{
    bool enable = false;                            // 是否开启自定义动作功能
    int maxNumber = SAFE_IO_ACTION_MAX_NUM;         // 用户增加的动作最大数量
    int execTimeout = SAFE_IO_ACTION_EXEC_TIMEOUT;  // 动作执行超时时间（毫秒）
    std::vector<SafeIOActionItem> items;            // 动作列表
};

class INOROBBUSINESS_CLASS ISafeIOAction
{
public:
    virtual ~ISafeIOAction(){};

    /**
     * @brief 刷新安全IO数据（与控制器通信）
     * @param data 安全IO数据
     * @return true成功 false失败
     */
    virtual bool refreshSafeIOAction(SafeIOActionData &data) = 0;

    /**
     * @brief 保存安全IO数据（与控制器通信）
     * @param data 安全IO数据
     * @return true成功 false失败
     */
    virtual bool saveSafeIOAction(const SafeIOActionData &data) = 0;

    /**
     * @brief 执行安全IO动作（与控制器通信）
     * @param cmd 命令
     * @param cmdFlag 命令下标
     * @return true成功 false失败
     */
    virtual bool execSafeIOAction(const std::string &cmd, const unsigned char cmdFlag) = 0;

    /**
     * @brief 从文件中导入安全IO动作
     * @param fileName 文件名（包含完整路径）
     * @param[out] data 安全IO动作数据
     * @return true成功 false失败
     */
    virtual bool importSafeIOActionFromFile(const std::string &fileName, SafeIOActionData &data) = 0;

    /**
     * @brief 导出安全IO动作数据到文件中
     * @param fileName fileName 文件名（包含完整路径）
     * @param data 安全IO动作数据
     * @return true成功 false失败
     */
    virtual bool exportSafeIOActionToFile(const std::string &fileName, const SafeIOActionData &data) = 0;
};
}  // namespace InoRobBusiness
