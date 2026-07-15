#pragma once

#include <string>
#include <QMetaType>

constexpr int COBOT_MATCH_DB_SIZE_MAX = 8;  // 通配DB电阻最大数量

typedef struct stCobotGeneralMatchInfo
{
    std::string bodyRobotName;                        // 本体名
    std::string controllerRobotName;                  // 控制器当前适配本体名
    int matchState = -1;                              // 0：检查中，1：匹配，2：不匹配，3：FPGA软硬件不满足要求，
                                                      // 4：本体与控制器功率不匹配，5：本体与控制器参数版本不一致，
                                                      // 6：本体与控制器机型不一致，7：控制器刷机
    int factoryFlag = -1;                             // 出厂标志 1：出厂，0：非出厂
    int direction = -1;                               // 同步方向 0：本体同步到控制柜，1：控制柜同步到本体
    std::string bodyHardwareVersion;                  // 本体存储器硬件版本
    std::string bodySoftwareVersion;                  // 本体存储器软件版本
    std::string bodySN;                               // 本体SN码
    std::string mainFPGAHardwareVersion;              // 核心板FPGA硬件版本
    std::string mainFPGASoftwareVersion;              // 核心板FPGA软件版本
    std::string controllerSN;                         // 控制器SN码
    int bodyDB[COBOT_MATCH_DB_SIZE_MAX] = { -1 };           // 本体DB电阻
    int bodyBrakeType[COBOT_MATCH_DB_SIZE_MAX] = { -1 };    // 本体励磁抱闸
    int bodyPower[COBOT_MATCH_DB_SIZE_MAX] = { -1 };        // 本体功率
    std::string bodyParamVersion;                     // 本体参数版本
    std::string bodyParamCompatibilityVersion;        // 本体参数兼容版本
    std::string controllerParamCompatibilityVersion;  // 控制器软件兼容版本
    int generalOpen = -1;                             // 通配开启状态  0：关闭，1：开启

    stCobotGeneralMatchInfo()
    {
        for (int i = 0; i < COBOT_MATCH_DB_SIZE_MAX; i++)
        {
            bodyDB[i] = -1;
            bodyBrakeType[i] = -1;
            bodyPower[i] = -1;
        }
    }
} CobotGeneralMatchInfo;
Q_DECLARE_METATYPE(CobotGeneralMatchInfo)

typedef struct stCobotRobotParamSyncStatus
{
    int bodyStatus = 255;        // 本体状态 0-100百分比，255不需要更新
    int servoStatus = 255;       // 伺服状态 0-100百分比，255不需要更新
    int controllerStatus = 255;  // 控制器状态 0-100百分比，255不需要更新
    bool isValid = false;        // 是否有效 true参数有效，false参数无效
} CobotRobotParamSyncStatus;
