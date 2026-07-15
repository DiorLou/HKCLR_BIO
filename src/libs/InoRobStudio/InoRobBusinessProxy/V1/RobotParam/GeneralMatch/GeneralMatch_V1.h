#pragma once
#include "dllspec.h"
#include "IInoRobBusiness.h"
using namespace InoRobBusiness;

namespace InoRobBusinessProxy
{
constexpr int MATCH_DB_SIZE_MAX_V1 = 8;

// 通配
class INOROBBUSINESSPROXY_CLASS GeneralMatch_V1
{
#pragma region 枚举与结构体

public:
    // 通配匹配状态
    enum MatchType_V1
    {
        Checking_V1 = 0,                    // 检查中
        Matching_V1 = 1,                    // 匹配
        ParameterUnMatching_V1 = 2,         // 参数不匹配
        FPGASoftAndHardNoSat_V1 = 3,        // FPGA软硬件不满足要求
        PowerUnMatching_V1 = 4,             // 本体与控制器功率不匹配
        DBResistorUnMatching_V1 = 5,        // 本体与控制器DB电阻不匹配
        BrakeTypeUnMatching_V1 = 6,         // 本体与控制器励磁抱闸不匹配
        ParameterVersionUnMatching_V1 = 7,  // 本体与控制器参数版本不一致
        ModelUnMatching_V1 = 8,             // 本体与控制器机型不一致
        ControllerBrush_V1 = 9              // 控制器刷机
    };

    // 通配信息
    struct GeneralMatchInfo_V1
    {
        std::string bodyRobotName;                         // 本体名
        std::string controllerRobotName;                   // 控制器当前适配本体名
        int matchState = -1;                               // 0：检查中，1：匹配，2：不匹配，3：FPGA软硬件不满足要求，
                                                           // 4：本体与控制器功率不匹配，5：本体与控制器参数版本不一致，
                                                           // 6：本体与控制器机型不一致，7：控制器刷机
        int factoryFlag = -1;                              // 出厂标志 1：出厂，0：非出厂
        int direction = -1;                                // 同步方向 0：本体同步到控制柜，1：控制柜同步到本体
        std::string bodyHardwareVersion;                   // 本体存储器硬件版本
        std::string bodySoftwareVersion;                   // 本体存储器软件版本
        std::string bodySN;                                // 本体SN码
        std::string mainFPGAHardwareVersion;               // 核心板FPGA硬件版本
        std::string mainFPGASoftwareVersion;               // 核心板FPGA软件版本
        std::string controllerSN;                          // 控制器SN码
        int bodyDB[MATCH_DB_SIZE_MAX_V1] = { -1 };         // 本体DB电阻
        int bodyBrakeType[MATCH_DB_SIZE_MAX_V1] = { -1 };  // 本体励磁抱闸
        int bodyPower[MATCH_DB_SIZE_MAX_V1] = { -1 };      // 本体功率
        std::string bodyParamVersion;                      // 本体参数版本
        std::string bodyParamCompatibilityVersion;         // 本体参数兼容版本
        std::string controllerParamCompatibilityVersion;   // 控制器软件兼容版本
        int generalOpen = -1;                              // 通配开启状态  0：关闭，1：开启

        GeneralMatchInfo_V1()
        {
            for (size_t i = 0; i < MATCH_DB_SIZE_MAX_V1; i++)
            {
                bodyDB[i] = -1;
                bodyBrakeType[i] = -1;
                bodyPower[i] = -1;
            }
        }
    };

    // 机型参数同步状态
    struct RobotParamSyncStatus_V1
    {
        int bodyStatus = 255;        // 本体状态 0-100百分比，255不需要更新
        int servoStatus = 255;       // 伺服状态 0-100百分比，255不需要更新
        int controllerStatus = 255;  // 控制器状态 0-100百分比，255不需要更新
        bool isValid = false;        // 是否有效 true参数有效，false参数无效
    };

#pragma endregion

#pragma region 构造与析构

private:
    IGeneralMatch *_generalMatch = nullptr;

public:
    GeneralMatch_V1(IGeneralMatch *generalMatch);
    ~GeneralMatch_V1();

#pragma endregion

#pragma region 数据转换

public:
    static MatchType_V1 MatchType_ToProxy(IGeneralMatch::MatchType matchType);
    static IGeneralMatch::MatchType MatchType_FromProxy(MatchType_V1 matchType_V1);

    static bool GeneralMatchInfo_ToProxy(const IGeneralMatch::GeneralMatchInfo &generalMatchInfo, GeneralMatchInfo_V1 &generalMatchInfo_V1);
    static bool GeneralMatchInfo_FromProxy(const GeneralMatchInfo_V1 &generalMatchInfo_V1, IGeneralMatch::GeneralMatchInfo &generalMatchInfo);

    static bool RobotParamSyncStatus_ToProxy(const IGeneralMatch::RobotParamSyncStatus &robotParamSyncStatus, RobotParamSyncStatus_V1 &robotParamSyncStatus_V1);
    static bool RobotParamSyncStatus_FromProxy(const RobotParamSyncStatus_V1 &robotParamSyncStatus_V1, IGeneralMatch::RobotParamSyncStatus &robotParamSyncStatus);

#pragma endregion

#pragma region 业务逻辑

public:
    // 与控制器通信 读取机型参数匹配信息
    int readRobotParamMatchInfo(std::string &info);

    // 与控制器通信 读取机型参数同步信息
    int readRobotParamSyncStatus(std::string &info);

    // 与控制器通信 启动机型参数同步
    int startRobotParamSync(const std::string &info);

    // 与控制器通信 设置通配状态
    int setGeneralMatchStatus(const std::string &status);

    // 与控制器通信 控制器获取本体通配记录
    int startControllerGetBodyMatchRecord();

    // 与控制器通信 本体通配记录获取状态
    int readBodyMatchRecordStatus(std::string &status);

    // 获取通配信息（读取控制器）
    bool getGeneralMatchInfo(GeneralMatchInfo_V1 &matchInfo_V1);

    // 获取机型参数同步状态（读取控制器）
    bool getRobotParamSyncStatus(RobotParamSyncStatus_V1 &status_V1);

    // 获取通配是否开启（读取控制器）
    bool getGeneralMatchOpen();

    // 设置通配开启
    bool setGeneralMatchOpen(bool open);

    // 是否允许通配溯源
    bool allowTracingGeneralMatch();

    // 通过ftp 获取控制器本体通配记录
    int getGeneralMatchRecord(const std::string &fileName);

#pragma endregion
};
}  // namespace InoRobBusinessProxy
