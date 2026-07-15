#pragma once

#include <QApplication>
#include <QScreen>
#include <QDir>
#include <QMetaEnum>
#include <QStandardPaths>
#include <QSysInfo>
#include <QMetaType>
#ifdef INOCOBOTTP_MSVC_QT5
#include <QSet>
#include <QString>
#endif
#include "metatype_global.h"

#define PACKED __attribute__((__packed__))
#define MSTIME QDateTime::currentDateTime().toString("hh:mm:ss:zzz")

const int ERROR_OK = 0;

const char XML_FILE_NAME_SUFFIX[] = ".xml";
const char XML_LEVEL_FILE_NAME_SUFFIX[] = "level.xml";
const char BREAKPOINT_FILE_NAME_SUFFIX[] = ".breakPoint";
const char PROJECT_FILE_NAME_SUFFIX[] = ".prj";
const char SCRIPT_FILE_NAME_SUFFIX[] = ".lua";

const char FuncName_GetFunctionEnabledList[] = "FuncName_GetfunctionEnabledList";
const char FuncName_SetFunctionEnabledList[] = "FuncName_SetFunctionEnabledList";

const char FuncName_AddXmlConfigToActiveProjectWhenSaveProject[] = "FuncName_AddXmlConfigToActiveProjectWhenSaveProject";
const char TIMER_START[] = "TimerStart";
const char TIMER_VALUE[] = "TimerValue";

const int INVALID_INDEX = -1;

#if CommonLib_Metatype_DOF7_Enabled == 1
    const int ROBOT_AXIS_NUM = 7;
#else
    const int ROBOT_AXIS_NUM = 6;
#endif


const int REQUEST_RETRY_TIMES = 5;

const char BASE_COORD_NAME[] = "Base";
const char FLANGE_CENTER_NAME[] = "flange_center";

#if CommonLib_Metatype_DOF7_Enabled == 1
const int ROBOT_DOF = 7;
#else
const int ROBOT_DOF = 6;
#endif
const int ROBOT_ARM_NUM = 4;

// const char AsyncTaskType_LoadRobotModel[] = "LoadRobotModel";

const int TPBOX_LISTENING_PORT = 9206;
const int TPBOXSHELL_LISTENING_PORT = 0410;
const int COBOT_TP_MONITORING_PORT = 1206;

const double DOUBLE_MIN_VALUE_WHEN_EMPTY_NODE = -999999999.999;
const double DOUBLE_MAX_VALUE_WHEN_EMPTY_NODE = 999999999.999;

const double INT_MIN_VALUE_WHEN_EMPTY_NODE = -9999999;
const double INT_MAX_VALUE_WHEN_EMPTY_NODE = 9999999;

const char LogicTreeItem_Editor[] = "LogicTreeItem_Editor";

inline const QString ConditionCategory_Basic = "Basic";
inline const QString ConditionCategory_Advanced = "Advanced";

inline const QString InsertType_Child = "Child";
inline const QString InsertType_Peer = "Peer";

inline const QString ConditionEnable_Disabled = "Disabled";
inline const QString ConditionEnable_General = "General";
inline const QString ConditionEnable_Root = "Root";
inline const QString ConditionEnable_Loop_Termination = "Loop_Termination";
inline const QString ConditionEnable_Next_Not_ElseIfOrElse = "Next_Not_ElseIfOrElse";
inline const QString ConditionEnable_Next_Not_ElseIfOrElse_Loop = "Next_Not_ElseIfOrElse_Loop";
inline const QString ConditionEnable_Next_ElseIfOrElse = "Next_ElseIfOrElse";
inline const QString ConditionEnable_Switch_Disabled_Default = "Switch_Disabled_Default";
inline const QString ConditionEnable_Switch_Enabled_Default = "Switch_Enabled_Default";
inline const QString ConditionEnable_Waypoint = "Waypoint";
inline const QString ConditionEnable_Movs = "Movs";

inline bool doubleIsEqual(double a, double b, int dec = 3)
{
    return abs(a-b) < pow(0.1,dec);
}

enum InputMethodType {
    Imt_None,
    Imt_FormattedNumbersOnly,
    Imt_LogicExpressionOnly,
    Imt_LatinOnly,
    Imt_LatinCompletion,
    Imt_Chinese,
};

enum InoCoRobotBodyPowerState : unsigned char {
    ROBOT_BODY_POWER_DISENABLE = 0,  //工业机器人 未启用该功能
    ROBOT_BODY_POWER_OFF = 1,        //协作 未上电
    ROBOT_BODY_POWERING_ON_IN_PROCESS = 2,         //协作 正在上电
    ROBOT_BODY_POWER_ON = 3,         //协作 已上电
    ROBOT_BODY_DISCONNECTED_STATE = 4,    //未连接时的默认值
    ROBOT_BODY_POWER_STATE_CONTROLLER_RESEREVE1 = 5,    //控制柜内部状态1
    ROBOT_BODY_POWER_STATE_CONTROLLER_RESEREVE2 = 6, //控制柜内部状态2
    ROBOT_BODY_POWER_STATE_CONTROLLER_RESEREVE3 = 7,  //控制柜内部状态3
    ROBOT_BODY_POWER_OFF_IN_PROCESS = 8,         //协作 正在下电
};

enum ControllerConnectionState {
    ControllerConnectionState_Closed,
    ControllerConnectionState_Connecting,
    ControllerConnectionState_Connected
};
Q_DECLARE_METATYPE(ControllerConnectionState)

enum ControllerState {
    ControllerState_OFFLINE,
    ControllerState_ENABLE,
    ControllerState_ESTOP,
    ControllerState_ERR,
    ControllerState_WARN,
    ControllerState_STANDBY,
};

enum InoPosType
{
    InoPosType_P,
    InoPosType_JP
};

enum InoWifiPasswordModifyResult
{
    WifiPasswordModifyResult_Unknown = -1,
    WifiPasswordModifyResult_Fail,
    WifiPasswordModifyResult_Success,
    WifiPasswordModifyResult_Equal
};

class METATYPE_EXPORT MetaType : public QObject
{
    Q_OBJECT

public:
    MetaType()
    {
    }
    virtual ~MetaType()
    {
    }

    enum RobotType {
        RobotType_invalid,

        RobotType_I3s,
        RobotType_I3,
        RobotType_I3S,
        RobotType_I5s,
        RobotType_I5,
        RobotType_I5l,
        RobotType_I5AAC,
        RobotType_I5S,
        RobotType_I5H,
        RobotType_I7,
        RobotType_I10,
        RobotType_I10S,
        RobotType_I10b,
        RobotType_I16,
        RobotType_I20,
        RobotType_I20td,
    };
    Q_ENUM(RobotType)

    enum RobotDeviceMode {
        RobotDeviceMode_Unknow,
        RobotDeviceMode_Manual_Low,
        RobotDeviceMode_Manual_High,
        RobotDeviceMode_Auto
    };

    enum CobotControllerRunStatus
    {
        COBOT_CONTROLLER_RUN_STATUS_STOP = 0,     // 停止
        COBOT_CONTROLLER_RUN_STATUS_START = 1,    // 启动
        COBOT_CONTROLLER_RUN_STATUS_FORWARD = 2,  // 前进
        COBOT_CONTROLLER_RUN_STATUS_BACK = 3,     // 后退
        COBOT_CONTROLLER_RUN_STATUS_PAUSE = 4,    // 暂停
    };

    enum RobotDebugMode {
        RobotDebugMode_Edit,
        RobotDebugMode_Debug
    };

    enum ElectricControlCabinetType
    {
        ELECTRIC_CONTROL_CABINET_TYPE_UNKNOW = 0,      // 未知
        ELECTRIC_CONTROL_CABINET_TYPE_NORMAL = 1,      // 默认老电柜
        ELECTRIC_CONTROL_CABINET_TYPE_MULTI_PASS = 2,  // 小多传
        ELECTRIC_CONTROL_CABINET_TYPE_J6_20KGV = 3,    // 20公斤6关节立柜
        ELECTRIC_CONTROL_CABINET_TYPE_UNIT = 4,        // 驱控一体
        ELECTRIC_CONTROL_CABINET_TYPE_JIUZHOU = 6,     // 九州电柜
        ELECTRIC_CONTROL_CABINET_TYPE_UROBOT = 8,      // 协作U8电柜类型
    };

    template <typename T>
    static T str2Enum(const QString &str)
    {
        std::string temp = str.toStdString();
        return static_cast<T>(
            QMetaEnum::fromType<T>()
                .keyToValue(temp.c_str()));
    }

    template <typename T>
    static QString enum2Str(const T &enumType)
    {
        QString ret = QMetaEnum::fromType<T>().valueToKey(enumType);
        if (ret.isEmpty())
            ret = "";
        return ret;
    }
};

enum EthConnectState {
    Disconnected = 0,
    Connected = 1,
    DisEnable = 2
};

typedef struct InopTagEthCfg {
    InopTagEthCfg()
    {
        strDHCP = "0";
        strIP = "0.0.0.0";
    }
    QString strDHCP;
    QString strIP;
} InoEthCfg;

typedef struct InoTagControllerEthCfg {
    InopTagEthCfg strcEth0;
    InopTagEthCfg strcEth1;
} InoControllerEthCfg;

struct InoAddrInfo {
    QString IP;    // IP信息，位数最多16位：192.168.222.333
    int port = 0;  // 端口信息
    bool operator==(const InoAddrInfo &b) const
    {
        return (this->IP == b.IP) && (this->port == b.port);
    }
    InoAddrInfo &operator=(const InoAddrInfo &other)
    {
        this->IP = other.IP;
        this->port = other.port;
        return *this;
    }
};

typedef struct stCobotSystemUpdateInfo
{
    stCobotSystemUpdateInfo()
    {
        Initialize();
    }

    void Initialize()
    {
        status = 0;
        progress = 0;
        memset(msg, 0, sizeof(msg));
    }

    stCobotSystemUpdateInfo &operator=(const stCobotSystemUpdateInfo &other)
    {
        this->status = other.status;
        this->progress = other.progress;
        memcpy(&this->msg[0], &other.msg[0], 80 * sizeof(char));

        return (*this);
    }

    short status;    // 下位机通信：0正在升降级；1升降级成功；其它表示失败见文档
    short progress;  // 进度信息 0~100 %
    char msg[80];    // 描述信息
} CobotSystemUpdateInfo;

struct InoCommonNetStatus {
    InoAddrInfo localAddrInfo;  // 本地网络信息
    InoAddrInfo peerAddrInfo;   // 对端网络信息
    int netStatus = 0;          // 0-客户端列表断开连接;1-新建连接;2-关闭服务务器;3-打开服务器 4-服务器列表断开连接
                                // V4R24C5版本（不包括V4R24C5）以前的通讯机制：0:unconnected;1:connected 2:主动关闭服务器端口
    int localNetType = 0;       // 通讯模式:0-客户端模式;1-服务器模式;2-同时作为客户端和服务器
    InoCommonNetStatus(const InoCommonNetStatus &other)
    {
        (*this) = other;
    }
    InoCommonNetStatus()
    {
        reset();
    }
    void reset()
    {
        netStatus = 0;
        localNetType = 0;
        localAddrInfo.IP = "0.0.0.0";
        localAddrInfo.port = 0;
        peerAddrInfo.IP = "0.0.0.0";
        peerAddrInfo.port = 0;
    }
    bool operator==(const InoCommonNetStatus &other) const
    {
        return (this->localAddrInfo == other.localAddrInfo)
            && (this->peerAddrInfo == other.peerAddrInfo)
            && (this->netStatus == other.netStatus)
            && (this->localNetType == other.localNetType);
    }
    InoCommonNetStatus &operator=(const InoCommonNetStatus &other)
    {
        this->localAddrInfo = other.localAddrInfo;
        this->peerAddrInfo = other.peerAddrInfo;
        this->netStatus = other.netStatus;
        this->localNetType = other.localNetType;
        return *this;
    }
};

// DH参数
typedef struct DHParam {
    float a1;
    float a2;
    float a3;
    float d3;
    float d4;
    float df;
    float d1;
    float d5;
    float d6;

    DHParam()
    {
        a1 = 0.0f;
        a2 = 360.0f;
        a3 = 305.0f;
        d3 = 0.0f;
        d4 = 115.5f;
        df = 0.0f;
        d1 = 120.0f;
        d5 = 115.5f;
        d6 = 110.0f;
    }
} DHParam;
Q_DECLARE_METATYPE(DHParam)

struct InoSystemTime {
    unsigned short wYear;
    unsigned short wMonth;
    unsigned short wDayOfWeek;
    unsigned short wDay;
    unsigned short wHour;
    unsigned short wMinute;
    unsigned short wSecond;
    unsigned short wMilliseconds;
};

typedef struct InoCobotWifiInfo
{
    InoCobotWifiInfo()
    {
        Initialize();
    }

    void Initialize()
    {
        memset(wifiName, 0, sizeof(wifiName));
        memset(wifiIp, 0, sizeof(wifiIp));
        wifiLinkStatus = 0;
    }

    InoCobotWifiInfo &operator=(const InoCobotWifiInfo &other)
    {
        memcpy(&this->wifiName[0], &other.wifiName[0], 32 * sizeof(char));
        memcpy(&this->wifiIp[0], &other.wifiIp[0], 16 * sizeof(char));
        this->wifiLinkStatus = other.wifiLinkStatus;

        return (*this);
    }

    char wifiName[32];    // Wifi SSID
    char wifiIp[16];
    int wifiLinkStatus;
}InoCobotWifiInfo;


#ifdef INOCOBOTTP_MSVC_QT5
Q_DECLARE_METATYPE(QSet<QString>*)
Q_DECLARE_METATYPE(QSet<int>*)
Q_DECLARE_METATYPE(QStringList*)
#endif
