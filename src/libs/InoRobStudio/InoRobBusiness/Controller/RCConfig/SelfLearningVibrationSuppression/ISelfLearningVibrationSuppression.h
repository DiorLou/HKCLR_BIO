#pragma once
#include <string>
#include <QObject>
#include "dllspec.h"
#include "DataTypeDef.h"
#include "signal_slot.h"
#include "InoRobUtil.h"

namespace InoRobBusiness
{
#pragma region 常量与数据类型

#define SLVS_FILE_TYPE          "SelfLearningData"                              // 自学习振动抑制文件类型
#define SLVS_FILE_NAME          "SelfLearningData.dat"                          // 自学习振动抑制文件名称
#define SLVS_FILE_CTRL_PATH     "/robotConfParameter/SelfLearningData.dat"      // 自学习振动抑制文件控制器路径
#define SLVS_FILE_CTRL_PATH_TMP "/robotConfParameter/SelfLearningData.dat.tmp"  // 自学习振动抑制文件控制器临时路径

/**
 * @brief 控制器将自学习振动抑制数据写入到文件的状态
 */
enum class SlvsDataWriteFileState : int
{
    // 失败
    FAILED = 0,
    // 成功
    SUCCEED,
};

/**
 * @brief 控制器更新自学习振动抑制数据的状态
 */
enum class SlvsDataUpdateState : int
{
    // 数据无效不合法
    INVALID = -1,
    // 未开始
    NOSTART,
    // 检验中
    CHECKING,
    // 已完成
    FINISHED,
};

/**
 * @brief 文件机型检查结果（与控制器机型比较）
 */
enum class SlvsFileRobotNameCheckResult : int
{
    // 匹配
    MATCH = 0,
    // 本体参数相同，但具体机型不同，需用户确认
    NEED_CONFIRM,
    // 不匹配
    MISMATCH,
};

#pragma endregion

/*
    自学习振动抑制基类
    Create by lcm at 2024/04/09 创建。
*/
class INOROBBUSINESS_CLASS ISelfLearningVibrationSuppression : public QObject
{
    Q_OBJECT

public:
    virtual ~ISelfLearningVibrationSuppression()
    {
    }

    /**
     * @brief 自学习振动抑制文件在控制器中的路径
     */
    virtual std::string fileCtrlPath() = 0;
    /**
     * @brief 自学习振动抑制文件在控制器中的临时路径
     */
    virtual std::string fileCtrlTempPath() = 0;
    /**
     * @brief 检查状态
     */
    virtual bool checkStatus() = 0;
    /**
     * @brief 备份自学习振动抑制文件到本地
     * @param localPath 输入，本地文件夹路径
     * @param ctrlPath 输入，控制器路径
     * @return 成功返回0，其他请见错误码
     */
    virtual int backupFile(const std::string &localFolder, const std::string &ctrlPath) = 0;
    /**
     * @brief 上传自学习振动抑制文件到控制器
     * @param localPath 输入，本地路径
     * @param ctrlPath 输入，控制器路径
     * @return 成功返回0，其他请见错误码
     */
    virtual int uploadFile(const std::string &localPath, const std::string &ctrlPath) = 0;
    /**
     * @brief 通知控制器将自学习振动抑制数据写入到文件
     * @param state 输出，数据写入到文件的状态
     * @return 成功返回0，其他请见错误码
     */
    virtual int sendWriteDataToFileCmd(SlvsDataWriteFileState &state) = 0;
    /**
     * @brief 通知控制器更新自学习振动抑制数据
     * @return 成功返回0，其他请见错误码
     */
    virtual int sendUpdateDataCmd() = 0;
    /**
     * @brief 读取控制器更新自学习振动抑制数据的状态
     * @param state 输出，更新状态
     * @return 成功返回0，其他请见错误码
     */
    virtual int readUpdateDataState(SlvsDataUpdateState &state) = 0;
    /**
     * @brief 将控制器中的自学习振动抑制数据恢复默认
     * @return 成功返回0，其他请见错误码
     */
    virtual int resetData() = 0;
    /**
     * @brief 将控制器中的自学习振动抑制数据清空
     * @return 成功返回0，其他请见错误码
     */
    virtual int clearData() = 0;

    /**
     * @brief 解析自学习振动抑制文件
     * @param localPath 输入，文件本地路径
     * @param info 输出，文件头信息
     * @param data 输出，二进制数据
     * @param dataSize 输出，数据大小
     * @return 成功返回0，其他请见错误码
     */
    virtual int analysisFile(const std::string &localPath) = 0;

    /**
     * @brief 获取自学振动抑制文件机型名称匹配结果
     */
    virtual SlvsFileRobotNameCheckResult getRobotNameCheckResult() const = 0;

    /**
     * @brief 修改自学习振动抑制文件中机型名
     * @param localPath 输入，文件本地路径
     * @return 成功返回0，其他请见错误码
     */
    virtual int changeFileRobotName(const std::string &localPath) = 0;

    /**
     * @brief 设置编程调试页面中清除自学习振动抑制数据按钮的可见性（重启软件后重置为不可见）
     */
    virtual void setClearBtnVisible(bool visible) = 0;
    /**
     * @brief 获取编程调试页面中清除自学习振动抑制数据按钮的可见性
     */
    virtual bool getClearBtnVisible() = 0;
};
}  // namespace InoRobBusiness
