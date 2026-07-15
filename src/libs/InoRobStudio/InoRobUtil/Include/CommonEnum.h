#pragma once

namespace InoRobUtil
{
#define MIN_POS_NO (0)
#define MAX_POS_NO (9999)

// 任务状态
enum TaskState
{
    TASK_STOP = 0,         // 停止
    TASK_RUNNING = 1,      // 运行中
    TASK_STEP = 2,         // 单步
    TASK_PAUSED = 4,       // 暂停
    TASK_FINISHED = 10,    // 结束
    TASK_INACTIVED = 100,  // 未激活
    TASK_FREE = 255        // 空闲
};

// Modbus 新旧版本
enum ModBusVision
{
    OLD_MODBUS_VISION = 0,  // 旧版本
    NEW_MODBUS_VISION = 1,  // 新版本
};

// 坐标系
enum CoordType
{
    COORD_FLANGLE = -1,  // 法兰（对准功能使用）
    COORD_UNKNOW = 0,    // 未知
    COORD_JOINT = 1,     // 关节
    COORD_BASE = 2,      // 基
    COORD_TOOL = 3,      // 工具
    COORD_WOBJ = 4,      // 工件
    COORD_WORLD = 5,     // 世界
};

// 位置显示格式
enum PosFormat
{
    FORMAT_JOINT = 1,    // 关节坐标格式
    FORMAT_BASE = 2,     // 基坐标格式
    FORMAT_FLANGLE = 3,  // 法兰坐标格式
    FORMAT_WOBJ = 4,     // 工件坐标格式
    FORMAT_WORLD = 5,    // 世界坐标格式
};

// 　对准状态
enum AlignState
{
    ALIGN_STATE_STOP = 0,   // 停止
    ALIGN_STATE_START = 1,  // 开始
};

enum ToolObjMatch
{
    NO_MATCH = 0,  // 0 就是不匹配
    IS_MATCH = 1,  // 1 就是匹配
};

// 工程FTP操作状态
enum PrjFTPState
{
    PROJ_CAN_NOT_FTP = 0,  // 不可进行FTP操作
    PROJ_CAN_FTP = 1,      // 可进行FTP操作
};

// 工程FTP操作进度
enum PrjFTPProgress
{
    PROJ_FINISH_FTP = 0,   // 已经完成FTP操作
    PROJ_READYTO_FTP = 1,  // 准备进行FTP操作
};

// 控制器报警状态
enum RcErrState
{
    RC_NEED_ERR = 0,     // 控制器需要报警
    RC_NOTNEED_ERR = 1,  // 控制器不需要报警
};

// 控制器报警级别
enum RcErrLevel
{
    RC_WARNNING = 0,  // 控制器报警告
    RC_ERROR = 1,     // 控制器报错误
};

// 版本不匹配的标识
enum VersionNotMatchTag
{
    VERSION_MATCH = 0,             // 版本匹配
    V_VERSION_NOTMATCH = -1,       // V版本不匹配返回值
    R_VERSION_NOTMATCH = -2,       // R版本不匹配返回值
    C_VERSION_NOTMATCH = -3,       // C版本不匹配返回值
    UNKNOW_VERSION_NOTMATCH = -4,  // 异常版本
};

// 软件版本
#define SOFTWARE_VERSION "V4R24C1"

// 最低可兼容的控制器版本
#define MIN_CMPT_RCVERSION "V4R24C4"

#define SOFTWARE_VERSION_V4R25 "V4R25"

// 工程文件的宏

// 普通工程文件夹
#define PRJ_TEACH_PROGRAM_FOLDER "TeachProgram"

// 当前激活的工程所在的文件夹
#define PRJ_ACTIVE_FOLDER "/robot/TeachProgram/"

#define PRJ_TEACH_PROGRAM_VIRTUAL_PATH "../VC/Systems/xiezuo/media/sdcard1"
#define PRJ_TEACH_PROGRAM_VIRTUAL_FOLDER "../VC/Systems/xiezuo/media/sdcard1/TeachProgram"

// data 文件夹
#define PRJ_DATA_FOLDER "Data"

// main 程序
#define PRJ_MAIN_PRO_NAME "main.pro"
#define PRJ_MAIN_LUA_NAME "main.lua"
// 点 P 文件
#define PRJ_P_NAME "P.pts"
// 点 JP 文件
#define PRJ_JP_NAME "JP.pts"
// 标签
#define PRJ_LABEL_NAME "Labels.jsn"
// 用户自定义报警
#define PRJ_USER_WARN_NAME "UserDefineWarning.jsn"
// ftp用户
#define FTP_USER "robot"
// ftp密码
#define FTP_PASSWORD "123456"
// ftp端口号
#define FTP_PORT (7777)
// telnet用户
#define TELNET_USER "root"
// telnet密码
#define TELNET_PASSWORD "r"
// telnet端口号
#define TELNET_PORT "23"
// 臂参数
#define ARM_TYPE_NUM (4)
// 机器人位置维度
#define POSE_AXIS_NUM (6)
// 外部轴数
#define EXT_AXIS_NUM (6)
// 独立轴数
#define IND_AXIS_NUM (7)
// 机器人关节轴数
#define JOINT_AXIS_NUM (8)
// 质心位置（Cog）
#define POSIT_DIMENT (3)
// 质心的姿态（Orient）
#define ORIENT_DIMENT (3)
// 惯量（Inertia）
#define INERTIA_DIMENT (3)

// 机器单元最大数量
#define MAX_MECHUNIT_NUM (36)
// 机械单元名称最大长度
#define MECHUNIT_NAME_LENGTH (18)
// 机械单元轴映射关系数目
#define MECHUNIT_AXIS_MAP_COUNT (6)
// 机械单元转换关系数目
#define MECHUNIT_TRANSFORMAT_COUNT (6)
// 外部机械单元数量
#define EXT_MECHUNIT_COUNT (6)
// 机械单元标定过程点最大数量
#define MECHUNIT_CALIB_MID_POS_MAX_COUNT (9)
// 机械单元标定方法
#define MECHUNIT_CALIB_METHOD_COUNT (2)

// TCP连接数量上限(包含32)
#define TCP_MAX_NUM (32)
// 串口号
#define TCP_CLIENT_COM_ID (1)
// TCP客户端端口号最小序号(包含2)
#define TCP_CLIENT_PORT_MIN_ID (2)
// TCP客户端端口号最大序号(包含17)
#define TCP_CLIENT_PORT_MAX_ID (17)
// TCP客户端&服务器端口号最小值(包含1024)
#define TCP_PORT_MIN_VALUE (1024)
// TCP客户端&服务器端口号最大值(包含65535)
#define TCP_PORT_MAX_VALUE (65535)

}  // namespace InoRobUtil
