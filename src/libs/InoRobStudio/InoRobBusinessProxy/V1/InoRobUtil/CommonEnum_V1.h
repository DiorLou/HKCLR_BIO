#pragma once
#include "IInoRobBusiness.h"

namespace InoRobBusinessProxy
{
#define MIN_POS_NO_V1 (0)
#define MAX_POS_NO_V1 (9999)

// 任务状态
enum TaskState_V1
{
    TASK_STOP_V1 = 0,         // 停止
    TASK_RUNNING_V1 = 1,      // 运行中
    TASK_STEP_V1 = 2,         // 单步
    TASK_PAUSED_V1 = 4,       // 暂停
    TASK_FINISHED_V1 = 10,    // 结束
    TASK_INACTIVED_V1 = 100,  // 未激活
    TASK_FREE_V1 = 255        // 空闲
};

TaskState_V1 TaskState_ToProxy(TaskState taskState);
TaskState TaskState_FromProxy(TaskState_V1 taskState_V1);

// Modbus 新旧版本
enum ModBusVision_V1
{
    OLD_MODBUS_VISION_V1 = 0,  // 旧版本
    NEW_MODBUS_VISION_V1 = 1,  // 新版本
};

ModBusVision_V1 ModBusVision_ToProxy(ModBusVision modBusVision);
ModBusVision ModBusVision_FromProxy(ModBusVision_V1 modBusVision_V1);

// 坐标系
enum CoordType_V1
{
    COORD_FLANGLE_V1 = -1,  // 法兰（对准功能使用）
    COORD_UNKNOW_V1 = 0,    // 未知
    COORD_JOINT_V1 = 1,     // 关节
    COORD_BASE_V1 = 2,      // 基
    COORD_TOOL_V1 = 3,      // 工具
    COORD_WOBJ_V1 = 4,      // 工件
    COORD_WORLD_V1 = 5,     // 世界
};

CoordType_V1 CoordType_ToProxy(CoordType coordType);
CoordType CoordType_FromProxy(CoordType_V1 coordType_V1);

// 位置显示格式
enum PosFormat_V1
{
    FORMAT_JOINT_V1 = 1,    // 关节坐标格式
    FORMAT_BASE_V1 = 2,     // 基坐标格式
    FORMAT_FLANGLE_V1 = 3,  // 法兰坐标格式
    FORMAT_WOBJ_V1 = 4,     // 工件坐标格式
    FORMAT_WORLD_V1 = 5,    // 世界坐标格式
};

PosFormat_V1 PosFormat_ToProxy(PosFormat posFormat);
PosFormat PosFormat_FromProxy(PosFormat_V1 posFormat_V1);

// 　对准状态
enum AlignState_V1
{
    ALIGN_STATE_STOP_V1 = 0,   // 停止
    ALIGN_STATE_START_V1 = 1,  // 开始
};

AlignState_V1 AlignState_ToProxy(AlignState alignState);
AlignState AlignState_FromProxy(AlignState_V1 alignState_V1);

enum ToolObjMatch_V1
{
    NO_MATCH_V1 = 0,  // 0 就是不匹配
    IS_MATCH_V1 = 1,  // 1 就是匹配
};

ToolObjMatch_V1 ToolObjMatch_ToProxy(ToolObjMatch toolObjMatch);
ToolObjMatch ToolObjMatch_FromProxy(ToolObjMatch_V1 toolObjMatch_V1);

// 软件版本
#define SOFTWARE_VERSION_V1 "V4R24C1"

// 工程文件的宏

// 普通工程文件夹
#define PRJ_TEACH_PROGRAM_FOLDER_V1 "TeachProgram"

// 当前激活的工程所在的文件夹
#define PRJ_ACTIVE_FOLDER_V1 "/robot/TeachProgram/"

// data 文件夹
#define PRJ_DATA_FOLDER_V1 "Data"

// main 程序
#define PRJ_MAIN_PRO_NAME_V1 "main.pro"
#define PRJ_MAIN_LUA_NAME_V1 "main.lua"
// 点 P 文件
#define PRJ_P_NAME_V1 "P.pts"
// 点 JP 文件
#define PRJ_JP_NAME_V1 "JP.pts"
// 标签
#define PRJ_LABEL_NAME_V1 "Labels.jsn"
// 用户自定义报警
#define PRJ_USER_WARN_NAME_V1 "UserDefineWarning.jsn"
// ftp用户
#define FTP_USER_V1 "robot"
// ftp密码
#define FTP_PASSWORD_V1 "123456"
// ftp端口号
#define FTP_PORT_V1 (7777)
// 臂参数
#define ARM_TYPE_NUM_V1 (4)
// 机器人位置维度
#define POSE_AXIS_NUM_V1 (6)
// 外部轴数
#define EXT_AXIS_NUM_V1 (6)
// 独立轴数
#define IND_AXIS_NUM_V1 (7)
// 机器人关节轴数
#define JOINT_AXIS_NUM_V1 (8)
// 质心位置（Cog）
#define POSIT_DIMENT_V1 (3)
// 质心的姿态（Orient）
#define ORIENT_DIMENT_V1 (3)
// 惯量（Inertia）
#define INERTIA_DIMENT_V1 (3)

// 机器单元最大数量
#define MAX_MECHUNIT_NUM_V1 (36)
// 机械单元名称最大长度
#define MECHUNIT_NAME_LENGTH_V1 (18)
// 机械单元轴映射关系数目
#define MECHUNIT_AXIS_MAP_COUNT_V1 (6)
// 机械单元转换关系数目
#define MECHUNIT_TRANSFORMAT_COUNT_V1 (6)
// 外部机械单元数量
#define EXT_MECHUNIT_COUNT_V1 (6)
// 机械单元标定过程点最大数量
#define MECHUNIT_CALIB_MID_POS_MAX_COUNT_V1 (9)
// 机械单元标定方法
#define MECHUNIT_CALIB_METHOD_COUNT_V1 (2)

// TCP连接数量上限(包含16)
#define TCP_MAX_NUM_V1 (16)
// 串口号
#define TCP_CLIENT_COM_ID_V1 (1)
// TCP客户端端口号最小序号(包含2)
#define TCP_CLIENT_PORT_MIN_ID_V1 (2)
// TCP客户端端口号最大序号(包含17)
#define TCP_CLIENT_PORT_MAX_ID_V1 (17)
// TCP客户端&服务器端口号最小值(包含1024)
#define TCP_PORT_MIN_VALUE_V1 (1024)
// TCP客户端&服务器端口号最大值(包含65535)
#define TCP_PORT_MAX_VALUE_V1 (65535)

// 对应StrSerFileInfo.h
typedef struct tagFileInfo_V1
{
    std::string FileType;  // 文件类型

    unsigned short MajVersion;  // 文件格式主版本
    unsigned short MinVersion;  // 文件格式次版本

    std::string SystemVersion;  // 系统软件主版本

    std::string RobotName;  // 机型名
    std::string Time;       // 修改时间

    bool CheckFlag;          // 有的文件不需要校验，这时为flase，默认为需要校验
    unsigned int CheckCode;  // 32位文件校验码
    bool CheckResult;

    tagFileInfo_V1()
    {
        MajVersion = 0;
        MinVersion = 0;

        CheckFlag = true;
        CheckCode = 0;
        CheckResult = false;
    }

    tagFileInfo_V1 &operator=(const tagFileInfo_V1 &other)
    {
        this->FileType = other.FileType;
        this->MajVersion = other.MajVersion;
        this->MinVersion = other.MinVersion;
        this->SystemVersion = other.SystemVersion;
        this->RobotName = other.RobotName;
        this->Time = other.Time;

        this->CheckFlag = other.CheckFlag;
        this->CheckCode = other.CheckCode;
        this->CheckResult = other.CheckResult;

        return (*this);
    }

    void CopyFrom(tagFileInfo_V1 &other)
    {
        this->FileType = other.FileType;
        this->MajVersion = other.MajVersion;
        this->MinVersion = other.MinVersion;
        this->SystemVersion = other.SystemVersion;
        this->RobotName = other.RobotName;
        this->Time = other.Time;
        this->CheckCode = other.CheckCode;
        this->CheckResult = other.CheckResult;
    }

} FileInfo_V1;

bool FileInfo_ToProxy(const FileInfo &fileInfo, FileInfo_V1 &fileInfo_V1);
bool FileInfo_FromProxy(const FileInfo_V1 &fileInfo_V1, FileInfo &fileInfo);

}  // namespace InoRobBusinessProxy
