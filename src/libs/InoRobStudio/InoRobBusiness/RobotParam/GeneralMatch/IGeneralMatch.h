#pragma once
#include "dllspec.h"
#include <string>

namespace InoRobBusiness
{
constexpr int MATCH_DB_SIZE_MAX = 8;  // 通配DB电阻最大数量

/**
 * @brief 通配
 */
class INOROBBUSINESS_CLASS IGeneralMatch
{
public:
    /**
     * @brief 通配匹配状态
     */
    enum MatchType
    {
        Checking = 0,                // 检查中
        Matching,                    // 匹配
        ParameterUnMatching,         // 参数不匹配
        FPGASoftAndHardNoSat,        // FPGA软硬件不满足要求
        PowerUnMatching,             // 本体与控制器功率不匹配
        DBResistorUnMatching,        // 本体与控制器DB电阻不匹配
        BrakeTypeUnMatching,         // 本体与控制器励磁抱闸不匹配
        ParameterVersionUnMatching,  // 本体与控制器参数版本不一致
        ModelUnMatching,             // 本体与控制器机型不一致
        ControllerBrush              // 控制器刷机
    };

    /**
     * @brief 通配信息
     */
    struct GeneralMatchInfo
    {
        std::string bodyRobotName;                        // 本体名
        std::string controllerRobotName;                  // 控制器当前适配本体名
        int matchState = -1;                              // 0：检查中，1：匹配，2：不匹配，3：FPGA软硬件不满足要求，
                                                          // 4：本体与控制器功率不匹配，5：本体与控制器参数版本不一致，
                                                          // 6：本体与控制器机型不一致，7：控制器刷机
        int factoryFlag = -1;                             // 出厂标志 1：出厂，0：非出厂
        int direction = -1;                               // 同步方向 0：本体同步到控制器，1：控制器同步到本体
        std::string bodyHardwareVersion;                  // 本体存储器硬件版本
        std::string bodySoftwareVersion;                  // 本体存储器软件版本
        std::string bodySN;                               // 本体SN码
        std::string mainFPGAHardwareVersion;              // 核心板FPGA硬件版本
        std::string mainFPGASoftwareVersion;              // 核心板FPGA软件版本
        std::string controllerSN;                         // 控制器SN码
        int bodyDB[MATCH_DB_SIZE_MAX] = { -1 };           // 本体DB电阻
        int bodyBrakeType[MATCH_DB_SIZE_MAX] = { -1 };    // 本体励磁抱闸
        int bodyPower[MATCH_DB_SIZE_MAX] = { -1 };        // 本体功率
        std::string bodyParamVersion;                     // 本体参数版本
        std::string bodyParamCompatibilityVersion;        // 本体参数兼容版本
        std::string controllerParamCompatibilityVersion;  // 控制器软件兼容版本
        int generalOpen = -1;                             // 通配开启状态  0：关闭，1：开启

        GeneralMatchInfo()
        {
            for (int i = 0; i < MATCH_DB_SIZE_MAX; i++)
            {
                bodyDB[i] = -1;
                bodyBrakeType[i] = -1;
                bodyPower[i] = -1;
            }
        }
    };

    /**
     * @brief 机型参数同步状态
     */
    struct RobotParamSyncStatus
    {
        int bodyStatus = 255;        // 本体状态 0-100百分比，255不需要更新
        int servoStatus = 255;       // 伺服状态 0-100百分比，255不需要更新
        int controllerStatus = 255;  // 控制器状态 0-100百分比，255不需要更新
        bool isValid = false;        // 是否有效 true参数有效，false参数无效
    };

    virtual ~IGeneralMatch()
    {
    }

    /**
     * @brief 与控制器通信 读取机型参数匹配信息
     * @param info 信息
     * @return ERR_OK成功 其它见错误码
     */
    virtual int readRobotParamMatchInfo(std::string &info) = 0;

    /**
     * @brief 与控制器通信 读取机型参数同步信息
     * @param info 信息
     * @return ERR_OK成功 其它见错误码
     */
    virtual int readRobotParamSyncStatus(std::string &info) = 0;

    /**
     * @brief 与控制器通信 启动机型参数同步
     * @param info 信息
     * @return ERR_OK成功 其它见错误码
     */
    virtual int startRobotParamSync(const std::string &info) = 0;

    /**
     * @brief 与控制器通信 设置通配状态
     * @param status 通配状态
     * @return ERR_OK成功 其它见错误码
     */
    virtual int setGeneralMatchStatus(const std::string &status) = 0;

    /**
     * @brief 与控制器通信 控制器获取本体通配记录
     * @return ERR_OK成功 其它见错误码
     */
    virtual int startControllerGetBodyMatchRecord() = 0;

    /**
     * @brief 与控制器通信 本体通配记录获取状态
     * @param[in] status状态
     * @return ERR_OK成功 其它见错误码
     */
    virtual int readBodyMatchRecordStatus(std::string &status) = 0;

    /**
     * @brief 获取通配信息（读取控制器）
     * @param[out] matchInfo 通配信息
     * @return true成功 false失败
     */
    virtual bool getGeneralMatchInfo(GeneralMatchInfo &matchInfo) = 0;

    /**
     * @brief 获取机型参数同步状态（读取控制器）
     * @param[out] status 状态
     * @return true成功 false失败
     */
    virtual bool getRobotParamSyncStatus(RobotParamSyncStatus &status) = 0;

    /**
     * @brief 获取通配是否开启（读取控制器）
     * @return true成功 false失败
     */
    virtual bool getGeneralMatchOpen() = 0;

    /**
     * @brief 设置通配开启
     * @param open true开启 false关闭
     * @return true成功 false失败
     */
    virtual bool setGeneralMatchOpen(bool open) = 0;

    /**
     * @brief 是否允许通配溯源
     * @return true允许 false不允许
     */
    virtual bool allowTracingGeneralMatch() = 0;

    /**
     * @brief 通过ftp 获取控制器本体通配记录
     * @param fileName 导出文件名（完整路径）
     * @return 0成功 -1导出路径不存在 -2控制器获取本体通配信息失败 -3Ftp登录失败 - 4控制器路径不存在
     *         -5本体通配信息文件不存在 -6控制器通配信息文件不存在
     *         -7下载本体通配信息文件失败 -8下载控制器通配信息文件失败
     */
    virtual int getGeneralMatchRecord(const std::string &fileName) = 0;
};
}  // namespace InoRobBusiness
