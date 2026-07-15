#pragma once
#include "dllspec.h"
#include "IInoRobBusiness.h"
#include "../../../InoRobUtil/CommonEnum_V1.h"
using namespace InoRobBusiness;

namespace InoRobBusinessProxy
{
#pragma region 数据（结构体与枚举）

#define SLVS_FILE_TYPE_V1          "SelfLearningData"                              // 自学习振动抑制文件类型
#define SLVS_FILE_NAME_V1          "SelfLearningData.dat"                          // 自学习振动抑制文件名称
#define SLVS_FILE_CTRL_PATH_V1     "/robotConfParameter/SelfLearningData.dat"      // 自学习振动抑制文件控制器路径
#define SLVS_FILE_CTRL_PATH_TMP_V1 "/robotConfParameter/SelfLearningData.dat.tmp"  // 自学习振动抑制文件控制器临时路径

/**
 * @brief 控制器将自学习振动抑制数据写入到文件的状态
 */
enum class SlvsDataWriteFileState_V1 : int
{
    // 失败
    FAILED_V1 = 0,
    // 成功
    SUCCEED_V1,
};

/**
 * @brief 控制器更新自学习振动抑制数据的状态
 */
enum class SlvsDataUpdateState_V1 : int
{
    // 数据无效不合法
    INVALID_V1 = -1,
    // 未开始
    NOSTART_V1,
    // 检验中
    CHECKING_V1,
    // 已完成
    FINISHED_V1,
};

/**
 * @brief 文件机型检查结果（与控制器机型比较）
 */
enum class SlvsFileRobotNameCheckResult_V1 : int
{
    // 匹配
    MATCH_V1 = 0,
    // 本体参数相同，但具体机型不同，需用户确认
    NEED_CONFIRM_V1,
    // 不匹配
    MISMATCH_V1,
};

#pragma endregion

class INOROBBUSINESSPROXY_CLASS SelfLearningVibrationSuppression_V1
{
#pragma region 构造与析构

private:
    ISelfLearningVibrationSuppression *_selfLearningVibrationSuppression = nullptr;

public:
    SelfLearningVibrationSuppression_V1(ISelfLearningVibrationSuppression *selfLearningVibrationSuppression);
    ~SelfLearningVibrationSuppression_V1();

#pragma endregion

#pragma region 数据转换

public:
    static SlvsDataWriteFileState_V1 SlvsDataWriteFileState_ToProxy(SlvsDataWriteFileState slvsDataWriteFileState);
    static SlvsDataWriteFileState SlvsDataWriteFileState_FromProxy(SlvsDataWriteFileState_V1 slvsDataWriteFileState_V1);
    
    static SlvsDataUpdateState_V1 SlvsDataUpdateState_ToProxy(SlvsDataUpdateState slvsDataUpdateState);
    static SlvsDataUpdateState SlvsDataUpdateState_FromProxy(SlvsDataUpdateState_V1 slvsDataUpdateState_V1);

    static SlvsFileRobotNameCheckResult_V1 SlvsFileRobotNameCheckResult_ToProxy(SlvsFileRobotNameCheckResult slvsFileRobotNameCheckResult);
    static SlvsFileRobotNameCheckResult SlvsFileRobotNameCheckResult_FromProxy(SlvsFileRobotNameCheckResult_V1 slvsFileRobotNameCheckResult_V1);

#pragma endregion

#pragma region 业务逻辑

public:
    /**
     * @brief 自学习振动抑制文件在控制器中的路径
     */
    std::string fileCtrlPath();
    /**
     * @brief 自学习振动抑制文件在控制器中的临时路径
     */
    std::string fileCtrlTempPath();
    /**
     * @brief 检查状态
     */
    bool checkStatus();
    /**
     * @brief 备份自学习振动抑制文件到本地
     * @param localPath 输入，本地文件夹路径
     * @param ctrlPath 输入，控制器路径
     * @return 成功返回0，其他请见错误码
     */
    int backupFile(const std::string &localFolder, const std::string &ctrlPath);
    /**
     * @brief 上传自学习振动抑制文件到控制器
     * @param localPath 输入，本地路径
     * @param ctrlPath 输入，控制器路径
     * @return 成功返回0，其他请见错误码
     */
    int uploadFile(const std::string &localPath, const std::string &ctrlPath);
    /**
     * @brief 通知控制器将自学习振动抑制数据写入到文件
     * @param state 输出，数据写入到文件的状态
     * @return 成功返回0，其他请见错误码
     */
    int sendWriteDataToFileCmd(SlvsDataWriteFileState_V1 &state);
    /**
     * @brief 通知控制器更新自学习振动抑制数据
     * @return 成功返回0，其他请见错误码
     */
    int sendUpdateDataCmd();
    /**
     * @brief 读取控制器更新自学习振动抑制数据的状态
     * @param state 输出，更新状态
     * @return 成功返回0，其他请见错误码
     */
    int readUpdateDataState(SlvsDataUpdateState_V1 &state);
    /**
     * @brief 将控制器中的自学习振动抑制数据恢复默认
     * @return 成功返回0，其他请见错误码
     */
    int resetData();
    /**
     * @brief 将控制器中的自学习振动抑制数据清空
     * @return 成功返回0，其他请见错误码
     */
    int clearData();

    /**
     * @brief 检查文件基本合法性
     * @param info 输入，文件头信息
     * @param data 输入，二进制数据
     * @param dataSize 输入，数据大小
     */
    bool checkFileValid(const FileInfo_V1 &info, const unsigned char *data, int dataSize);
    /**
     * @brief 检查文件机型与控制器机型是否匹配
     * @param robotName 输入，文件头信息中机型名称
     * @param ctrlRobotName 输出，控制器的机型
     * @return 匹配结果
     */
    SlvsFileRobotNameCheckResult_V1 checkRobotName(const std::string &robotName, std::string &ctrlRobotName);
    /**
     * @brief 解析自学习振动抑制文件
     * @param localPath 输入，文件本地路径
     * @param info 输出，文件头信息
     * @param data 输出，二进制数据
     * @param dataSize 输出，数据大小
     * @return 成功返回0，其他请见错误码
     */
    int analysisFile(const std::string &localPath, FileInfo_V1 &info, unsigned char *&data, int &dataSize);
    /**
     * @brief 将数据写入自学习振动抑制文件
     * @param localPath 输入，文件本地路径
     * @param info 输出，文件头信息
     * @param data 输出，二进制数据
     * @param dataSize 输出，数据大小
     * @return 成功返回0，其他请见错误码
     */
    int saveFile(const std::string &localPath, const FileInfo_V1 &info, const unsigned char *data, int dataSize);

    /**
     * @brief 设置编程调试页面中清除自学习振动抑制数据按钮的可见性（重启软件后重置为不可见）
     */
    void setClearBtnVisible(bool visible);
    /**
     * @brief 获取编程调试页面中清除自学习振动抑制数据按钮的可见性
     */
    bool getClearBtnVisible();

#pragma endregion
};
}  // namespace InoRobBusinessProxy
