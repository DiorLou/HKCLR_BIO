#pragma once
#include <string>
#include <vector>
#include <map>
#include "DetailDef.h"
#include "GlobalDataTypes.h"
#include "IInoRobUtil.h"

using std::string;

/**************************************
/错误码定义
***************************************/
// 通信错误码
#define ERR_OK               0     // 执行成功
#define ERR_DEV_OFFLINE      -1    // 设备不在线
#define ERR_SEND_FAIL        -2    // 发送下行帧失败
#define ERR_ECHO_ERRO        -3    // 查询回应失败：无回应、数据长度非法
#define ERR_RECV_FAIL        -4    // 接收上行帧失败
#define ERR_FRAME_ERRO       -5    // 帧格式有误
#define ERR_FRAME_ID_ERRO    -6    // 帧号检测失败
#define ERR_RET_VALUE_ERRO   -7    // 返回值非法,超出有效范围
#define ERR_TASK_BUSY        (-8)  // 优先级低的任务因通讯忙被过滤
#define ERR_RECV_BUSY        (-9)  // 接收上行帧超时
#define ERR_STRUCT_OVER_SIZE -10   // 拷贝结构体时 结构体大小超过当前帧大小

// 用户参数引起的错误
#define ERR_INPUT_ERRO     -11  // 用户输入参数非法
#define ERR_OPEN_FILE_ERRO -12  // 打开或者创建本地文件失败
#define ERR_BREAD          -13  // 设备端返回的错误码
#define ERR_DATA_SIZE_OUT_CMD_DEFINE  -14  // 传入数据大小超过通讯方式大小限制

#define ERR_CRC -20  // CRC校验出错

#define ERR_DIR_EXIST          0x1001  // 目录存在，重复创建
#define ERR_PRE_DIR_INEXIST    0x1002  // 内存中搜索不到前级目录, 创建失败
#define ERR_RENAME_DIR_INEXIST 0x1003  // 重命名原目录不存在
#define ERR_DEL_DIR_INEXIST    0x1004  // 要删除的目录不存在
#define ERR_DIR_INVALID        0x1005  // 目标目录无效(不是目录、或目录不存在)

#define ERR_CREATE_FILE_FAIL    0x1006  // 创建文件出错：内存错误，或路径无效
#define ERR_REANME_FILE_INEXIST 0x1007  // 重命名原文件不存在
#define ERR_DEL_FILE_INEXIST    0x1008  // 要删除的文件不存在、路径有误
#define ERR_FILE_PATH_INVALID   0x1009  // 目标文件路径无效(包含的目录不存在，或者文件名无效)
#define ERR_FILE_NAME_INVALID   0x100a  // 文件名称非法(必需有后缀)
#define ERR_DIR_NAME_INVALID    0x100b  // 文件夹名称非法(不能有后缀)
#define ERR_FRAME_INDEX_ERRO    0x100c  // 帧顺序错误
#define ERR_DEV_RUN_ERRO        0x100d  // 设备运行异常,主动断开网络连接
#define ERR_TIME_FORMAT_ERRO    0x100e  // 时间格式错误
#define ERR_SYSTIME_ADJ_ERRO    0x100f  // 系统校时出错
#define ERR_RTCTIME_ADJ_ERRO    0x1010  // RTC校时出错
#define ERR_COPY_FILE_ERRO      0x1011  // 执行复制出错
#define ERR_COUT_FILE_ERRO      0x1012  // 执行剪切出错
#define ERR_FILE_ENCRYPT        0x1014  // 文件加密错误

#define ERR_NOREPONSE     0x1015  // 下位机没有该通讯码
#define ERR_SYSTEMTORESET (0x00FF)

#define ERR_CRC_CHECK 0x6001  // CRC校验错误
#define STA_ASYN_BUSY 0x6002  // 控制器异步通讯线程忙碌

#define ERR_CMD_ACTION_FAILED 0xEEEE  // 通讯业务执行失败，用于写命令时能返回状态

#define MAX_TEMP_BUF_LEN 1024  // 最大临时BUF大小

// 轴个数
#define AXIS_NUMB 8
#define MAX_IONUM 10
#define AXIS_NUM  (AXIS_NUMB)

// 备用参数个数
#define INT_BACKUP_PARAM_NUMB 8  // INT16
#define DB_BACKUP_PARAM_NUMB  8  // DOUBLE

// 调试信息长度
#define DEBUG_INFO_LEN 120

// 密码长度
#define ALL_PWD_SIZE 40  // 所有密码数据总长
#define MAX_PWD_SIZE 6   // 单个密码长度

// 最大原点数
#define MAX_ORIGINPTS_CNT (10)

// R变量
#define R_VAR_NUMB     256  // 总个数
#define R_VAR_ARR_SIZE 10   // 每帧数据

// D变量
#define D_VAR_NUMB     256  // 总个数
#define D_VAR_ARR_SIZE 10   // 每帧数据

// B变量
#define B_VAR_NUMB     256  // 总个数
#define B_VAR_ARR_SIZE 256  // 每帧数据

// LB变量
#define LB_VAR_NUMB     256  // 总个数
#define LB_VAR_ARR_SIZE 256  // 每帧数据

// LR变量
#define LR_VAR_NUMB     256  // 总个数
#define LR_VAR_ARR_SIZE 10   // 每帧数据

// LD变量
#define LD_VAR_NUMB     256  // 总个数
#define LD_VAR_ARR_SIZE 10   // 每帧数据

#define P_VAR_NUMB     10
#define P_VAR_ARR_SIZE 5  // 每帧数据

// PR变量
#define PALLET_VAR_NUMB     256
#define PALLET_VAR_ARR_SIZE 5  // 每帧数据
#define PR_VAR_NUMB         256
#define PR_VAR_ARR_SIZE     10  // 每帧数据

#define STR_VAR_NUMB     256
#define STR_VAR_ARR_SIZE 10  // 每帧数据

// 版本信息长度
#define VER_INFO_LEN 40

// 错误码数组大小
#define MAX_ERRO_NUMB 32  // 128/4= 32

// 错误文件标识
#define ERR_FILE_HAD_READ  1                // 文件已读
#define ERR_FILE_READABLE  2                // 文件可读
#define ERR_FILE_READ_INTV (60 * 1000 * 3)  // 3分钟

#define MAX_SERVO_STATEDATA_LEN     (12)
#define MAX_SERVO_AXISSTATE_ITEMCNT (32)

#define MODULE_NUM 8  // 控制器模块数量

#define AXIS_NUM_SIX 6  // 六关节零点校准轴数

#define LINK_PARM_NUM 8
#define COM_PARM_NUM  16
#define STIF_PARM_NUM 16

#define MAX_WROKPIECE_LOAD_NUM (16)

#ifndef POS_ITION
    #define POS_ITION

typedef struct _Position
{
    struct _Position &operator=(const struct _Position &other)
    {
        if (this == &other)
            return *this;

        Coord = other.Coord;
        ToolNo = other.ToolNo;
        UserNo = other.UserNo;

        memcpy(&ArmParm[0], &(other.ArmParm[0]), sizeof(int) * 4);
        memcpy(&PosData[0], &(other.PosData[0]), sizeof(double) * AXIS_NUM);

        return *this;
    }

    int Coord;                 // 坐标系号
    int ToolNo;                // 工具号
    int UserNo;                // 用户坐标系号
    int ArmParm[4];            // 臂参数
    double PosData[AXIS_NUM];  // 坐标值
} Position;

#endif

// 模式类型
typedef enum
{
    MODE_UNKNOW = -1,      // 未知
    MODE_TEACH = 1,        // 示教
    MODE_REAPPEAR = 2,     // 再现
    MODE_TEACH_CHECK = 3,  // 单步示教检查
    MODE_FOUR = 4,
    MODE_TEACH_RUN = 5,  // 连续示教运行
    MODE_HOMING = 6,     // 回零

    MODE_TYPE_BUTT
} MODE_TYPE;

// 旋转方向
typedef enum
{
    POSITIVE = 0,
    REVERSE,
} ROTATE_DIR;

// 按下状态
typedef enum
{
    BTN_DOWN = 1,
    BTN_UP = 0,
} PRESS_STATE;

enum ReferObj : int16s
{
    ReferNoSense = -3,
    ReferBase = -2,
    ReferFlange = -1,
    ReferObj0 = 0,
    ReferObj1 = 1,
    ReferObj2 = 2,
    ReferObj3 = 3,
    ReferObj4 = 4,
    ReferObj5 = 5,
    ReferObj6 = 6,
    ReferObj7 = 7,
    ReferObj8 = 8,
    ReferObj9 = 9,
    ReferObj10 = 10,
    ReferObj11 = 11,
    ReferObj12 = 12,
    ReferObj13 = 13,
    ReferObj14 = 14,
    ReferObj15 = 15,
};

// 模式
typedef enum
{
    UI_MODE_UNKNOW = 0,
    UI_MODE_LOW_EDIT = 1,  // 手动低速编辑模式
    UI_MODE_LOW_DEBUG,     // 手动低速调试模式
    UI_MODE_HIGH,          // 手动高速模式
    UI_MODE_AUTO           // 自动模式
} UI_MODE_TYPE;

// 用户模式类型
typedef enum
{
    USER_UNKNOW = -1,
    USER_CUSTOMER = 1,
    USER_EDIT,
    USER_MANAGE,
    USER_FACTORY,
} EUSER_MODE;

// 开发者调试类型
typedef enum
{
    DEVELOPER_CLOSE,
    DEVELOPER_OPEN,
} DEVELOPER_DEBUG;

// EtherCAT版本设置
enum class EtherCATVersion
{
    CAT_VER_UNKNOW = 0,
    CAT_VER_RELEASE,
    CAT_VER_DEBUG,
    CAT_VER_TEST,
};

typedef enum
{
    IR_VER_UNKNOW = 0,
    IR_VER_RELEASE,
    IR_VER_DEBUG,
    IR_VER_TEST,
} IR_VER;

// 伺服工作模式
typedef enum
{
    SERVO_UNKNOW = 0,
    SERVO_CSP = 8,
    SERVO_CSV = 9,
    SERVO_CST = 10,
} SERVO_MODE;

// I/O模块类型
typedef enum
{
    UNKNOWN_IO = 0, /**< unknown io module */
    DO_TYPE_IO,     /**< digital output module */
    DI_TYPE_IO,     /**< digital input module */
    DA_TYPE_IO,     /**< analog output module */
    AD_TYPE_IO,     /**< analog input module */
    AT_TYPE_IO,     /**< analog temperature module */
} IO_MOD_TYPE;

#define MAXIONUM     128  // 64
#define MAXDANUM     16
#define MAXIRLINKNUM 4

//// 系统控制权（参数配置权）
// typedef enum _CTL_AUTHORITY
//{
//     AUTHORITY_UNKNOW = -1,
//     AUTHORITY_TEACHPAD = 0,
//     AUTHORITY_INOROBSHOP,
//     AUTHORITY_RMT_ETHERNET,
//     AUTHORITY_RMT_IO,
//     AUTHORITY_RMT_MODBUS,
//     AUTHORITY_CTL_NULL
// } CTL_AUTHORITY;

// IO状态控制权
typedef enum _IO_CTRL_STATE
{
    IO_RC_ACTIVE = 0,
    IO_RC_STATIC_CFG = 1,
    IO_PLC_ACTIVE = 2,
    IO_DEFAULT_VOID = -1
} IO_CTRL_STATE;

// IRlink配置权
typedef enum _IR_CTRL_SET
{
    IR_RC_ACTIVE = 0,
    IR_PLC_ACTIVE = 1,
} IR_CTRL_SET;

// ftp I/O type
typedef enum _FTP_IO_TYPE
{
    FTP_GET = 1,
    FTP_PUT = 2,
    FTP_DEL = 3,
    FTP_LIST = 4,
} FTP_IO_TYPE;

enum eElectricCabinetType
{
    ELECTRICCTRLCABINET_NORMAL = 0x0001,
    ELECTRICCTRLCABINET_MULTIPASS = 0x0002,
    ELECTRICCTRLCABINET_J620KGV = 0x0003,
};

// #pragma pack(4)
// 实时指令配置信息
typedef struct tagRealCmdInfo
{
    tagRealCmdInfo()
    {
        nStart = REALRUNSTAT_STOP;
        nCursorLine = 0;
        memset(&szLastFile[0], 0, 100);
        nEmerg = 0;
        nReset = 0;
        nEnable = 0;
        nMode = 0;
        nSpeedGrade = 0;
        nCoord = 0;
        nTeachstrError = 0;
        nHmState = 0;
        nCleanWarn = 0;
        nToolId = 1;
        nUserId = 1;
    }

    tagRealCmdInfo &operator=(const tagRealCmdInfo &other)
    {
        this->nStart = other.nStart;
        this->nCursorLine = other.nCursorLine;
        memcpy(&this->szLastFile[0], &other.szLastFile[0], 100);
        this->nEmerg = other.nEmerg;
        this->nReset = other.nReset;
        this->nEnable = other.nEnable;
        this->nMode = other.nMode;
        this->nSpeedGrade = other.nSpeedGrade;
        this->nCoord = other.nCoord;
        this->nTeachstrError = other.nTeachstrError;
        this->nHmState = other.nHmState;
        this->nCleanWarn = other.nCleanWarn;
        this->nToolId = other.nToolId;
        this->nUserId = other.nUserId;
        memcpy(&this->uCommState[0], &other.uCommState[0], 8 * sizeof(int16u));

        return (*this);
    }

    int32s nStart;          // 0 停止，1 启动，2 前进，3 后退，4暂停
    int32s nCursorLine;     // 当前光标所在行号
    char szLastFile[100];   // 最后一次保存的示教文件名称及路径
    int32s nEmerg;          // 1 急停, 0 非急停
    int32s nReset;          // 1 复位, 0 非复位
    int32s nEnable;         // 1 使能, 0 非使能
    int32s nMode;           // 模式设置 1->示教 2->再现 3->单步示教检查 5-> 连续示教检查 6-> 回零;
    int32s nSpeedGrade;     // 1 2 3 4 速度等级
    int32s nCoord;          // 1 2 3 4 关节，直角，工具，工件(用户)
    int32s nTeachstrError;  // 示教盒故障
    int32s nHmState;        // 是否启动回零
    int32s nCleanWarn;      // 清除告警
    int32s nToolId;         // 工具坐标系号
    int32s nUserId;         // 用户坐标系号
    int16u uCommState[8];   // 控制器端各个模块的通信状态
} REALCMD_INFO;

// 实时指令配置信息
typedef struct tagRCStsInfo
{
    tagRCStsInfo()
    {
        ResetData();
    }

    tagRCStsInfo &operator=(const tagRCStsInfo &other)
    {
        if (this == &other)
            return *this;

        this->nStart = other.nStart;
        this->nEmerg = other.nEmerg;
        this->nEnable = other.nEnable;
        this->nMode = other.nMode;
        this->nSpeed = other.nSpeed;
        this->nCoord = other.nCoord;
        this->nToolId = other.nToolId;
        this->nUserId = other.nUserId;
        this->nGripLoadId = other.nGripLoadId;
        memcpy(&this->szLastFile[0], &other.szLastFile[0], 100);
        this->nErrId = other.nErrId;
        this->nWarnId = other.nWarnId;
        memcpy(&this->dCurJpos[0], &other.dCurJpos[0], AXIS_NUMB * sizeof(double));
        memcpy(&this->uCommState[0], &other.uCommState[0], 8 * sizeof(int16u));
        memcpy(&this->OutState[0], &other.OutState[0], MAXIONUM * sizeof(int));
        memcpy(&this->DAState[0], &other.DAState[0], MAXDANUM * sizeof(int));
        this->iSafeDoorSts = other.iSafeDoorSts;
        this->iDynBrake = other.iDynBrake;
        this->iPowerLv = other.iPowerLv;
        // memcpy(&this->unDefinedSign[0], &other.unDefinedSign[0], 54);
        return (*this);
    }

    void ResetData()
    {
        nStart = REALRUNSTAT_STOP;
        nEmerg = 0;
        nEnable = 0;
        nMode = 0;
        nSpeed = 0;
        nCoord = -1;
        nToolId = 1;
        nUserId = 1;
        nGripLoadId = 1;
        memset(&szLastFile[0], 0, 100);
        nErrId = 0;
        nWarnId = 0;
        memset(&dCurJpos[0], 0, AXIS_NUMB * sizeof(double));
        memset(&uCommState[0], 0, 8 * sizeof(int16u));
        memset(&OutState[0], 0, MAXIONUM * sizeof(int));
        memset(&DAState[0], 0, MAXDANUM * sizeof(int));
        iSafeDoorSts = 0;
        iDynBrake = 0;
        iPowerLv = 0;
        // memset(unDefinedSign, 0, 54);
    }

    int32s nStart;         // 0 停止，1 启动，2 前进，3 后退，4暂停
    int32s nEmerg;         // 1 急停, 0 非急停
    int32s nEnable;        // 1 使能, 0 非使能
    int32s nMode;          // 1->示教 2->再现 3->单步示教检查 5-> 连续示教检查 6-> 回零
    int32s nSpeed;         // 速度值
    int32s nCoord;         // 1 2 3 4 关节，直角，工具，工件(用户)
    int32s nToolId;        // 工具坐标系号
    int32s nUserId;        // 用户坐标系号
    int32s nGripLoadId;    // 工件（夹持负载）号
    char szLastFile[100];  // 最后一次保存的示教文件名称及路径

    int32s nErrId;   // 报警号
    int32s nWarnId;  // 警告号

    double dCurJpos[AXIS_NUMB];  // 当前关节坐标

    int16u uCommState[8];    // 控制器端各个模块的通信状态(通信状态页面，某些检测USB、存储卡状态)
    int OutState[MAXIONUM];  // 0-RC激活 1-RC静态（IO配置使用） 3-PLC激活 参见枚举IO_CTRL_STATE
    int DAState[MAXDANUM];   // 0-RC激活 1-RC静态（IO配置使用） 3-PLC激活 参见枚举IO_CTRL_STATE

    int8u iSafeDoorSts;  // 安全门警示状态 0-无警示 1-有警示
    int8u iDynBrake;     // 动态制动，0关闭，1打开，默认为打开

    int8u iPowerLv;  // 0-低功率  1-高功率
    // char unDefinedSign[54];	//预留
} RCSTS_INFO;

// typedef struct tagInitData
//{
//	tagInitData()
//	{
//		memset(szRobotName, 0, 128);
//		eleType = 1;
//		powerDownSave = 0;
//		sysAuthority = 0;
//		irAuthority = 0;
//		di_num = 0;
//		do_num = 0;
//		ad_num = 0;
//		da_num = 0;
//		lockFlag = 0;
//		robotType = 6;
//		memset(&linkParm[0], 0, 8 * sizeof(double));
//		memset(&compParm[0], 0, 16 * sizeof(double));
//		memset(&negLimt[0], 0, AXIS_NUMB*sizeof(double));
//		memset(&posLimt[0], 0, AXIS_NUMB*sizeof(double));
//		memset(&cServoAxisType, 0, 8 * sizeof(char));
//		memset(&nCabinetFPGAVer, 0, sizeof(int32u));
//		memset(szRobotStructType, 0, 128);
//		memset(filedBusInstall, 0, 4);
//		memset(unDefinedSign, 0, 152);
//		memset(&toolPara[0], 0, 16 * 8 * sizeof(double));
//		memset(&userPara[0], 0, 16 * 8 * sizeof(double));
//	}
//	char	szRobotName[128];		//机器人名
//	UINT16	eleType;				//电柜类型 1-普通，2-小多传
//	UINT16	powerDownSave;			//掉电保存  0-无 1-有
//	int16s	sysAuthority;			//控制权 0-示教器 1-InoRobShop 2-远程EtherNet 3-远程IO 4-Modbus 参见枚举CTL_AUTHORITY
//	int		irAuthority;			//IRLINK配置权限 0-RC 1-PLC 参见枚举IR_CTRL_SET
//	int	di_num;						//IN个数
//	int	do_num;						//OUT个数
//	int	ad_num;						//AD个数
//	int	da_num;						//DA个数
//	int		lockFlag;				//机械锁定  0-未锁定, 1-锁定
//	int		robotType;				//机型
//	double	linkParm[8];			//结构参数
//	double	compParm[16];			//内部补偿参数
//	double	negLimt[AXIS_NUMB];		//负极限
//	double  posLimt[AXIS_NUMB];		//正极限
//	char	cServoAxisType[8];		//伺服轴类型
//	int32u	nCabinetFPGAVer;		//电柜FPGA类型
//	char szRobotStructType[128];	//本体机型（带有内部信息）
//	char filedBusInstall[4];        //总线安装标志(char[0].0表示EtherCAT)
//	int32u hardwareVersion;         //硬件版本
//	char unDefinedSign[152];		//预留
//	double toolPara[16][8];			//工具坐标系
//	double userPara[16][8];			//用户坐标系
//     double stiffParm[STIF_PARM_NUM];        //刚度参数
//
//	// TODO 还没有改过来
// }INIT_DATA;

///////////////////////////////////////////////////////////////////////////////////////
// 初始化数据结构体,用于连接成功后的数据读取
// 连接成功后：
// 1.控制器版本信息文件
// 2.分别读取 实时数据（1帧），该结构体（共5帧），自定义报警（1帧）
// 3.其它文件数据和写操作.
///////////////////////////////////////////////////////////////////////////////////////
typedef struct tagInitData
{
    tagInitData()
    {
        memset(szRobotName, 0, 128);
        eleType = 1;
        powerDownSave = 0;
        sysAuthority = 0;
        irAuthority = 0;
        di_num = 0;
        do_num = 0;
        ad_num = 0;
        da_num = 0;
        lockFlag = 0;
        robotType = 6;
        memset(&structPara[0], 0, 8 * sizeof(double));
        memset(&robRotPara[0], 0, 16 * sizeof(double));
        memset(&negLimt[0], 0, JOINT_AXIS_NUM * sizeof(double));
        memset(&posLimt[0], 0, JOINT_AXIS_NUM * sizeof(double));
        memset(&cServoAxisType, 0, 8 * sizeof(char));
        memset(&nCabinetFPGAVer, 0, sizeof(int32u));
        memset(szRobotStructType, 0, 128);
        memset(filedBusInstall, 0, 4);
        memset(&hardWareVer, 0, sizeof(int32u));
        memset(unDefinedSign, 0, 152);
        memset(&toolPara[0], 0, 16 * 8 * sizeof(double));
        memset(&userPara[0], 0, 16 * 8 * sizeof(double));
    }
    char szRobotName[128];           // 机器人名
    UINT16 eleType;                  // 电柜类型 1-普通，2-小多传,3-20kg 6关节 4-驱控一体
    UINT16 powerDownSave;            // 掉电保存  0-无 1-有
    int16s sysAuthority;             // 控制权 0-示教器 1-InoRobShop 2-远程EtherNet 3-远程IO 4-Modbus 参见枚举CTL_AUTHORITY
    int irAuthority;                 // IRLINK配置权限 0-RC 1-PLC 参见枚举IR_CTRL_SET
    int di_num;                      // IN个数
    int do_num;                      // OUT个数
    int ad_num;                      // AD个数
    int da_num;                      // DA个数
    int lockFlag;                    // 机械锁定  0-未锁定, 1-锁定
    int robotType;                   // 机型
    double structPara[8];            // 结构参数
    double robRotPara[16];           // 内部补偿参数
    double negLimt[JOINT_AXIS_NUM];  // 负极限
    double posLimt[JOINT_AXIS_NUM];  // 正极限
    char cServoAxisType[8];          // 伺服轴类型 1-IS620N 2-IS820N 3-IS660N
    int32u nCabinetFPGAVer;          // 电柜FPGA类型
    char szRobotStructType[128];     // 本体机型（带有内部信息）
    char filedBusInstall[4];         // 总线安装标志(char[0].0表示EtherCAT，char[0].1表示... 每一位表示一个总线是否安装的标识)最多支持存储 32 种总线的安装方式
    int32u hardWareVer;              // 电控柜硬件版本
    char unDefinedSign[152];         // 预留
    double toolPara[16][8];          // 工具坐标系
    double userPara[16][8];          // 用户坐标系
} INIT_DATA;

// 设备告警,每个错误码四个字节,而且是一个组合值
typedef struct tagErroInfo
{
    tagErroInfo()
    {
        nErroType = 0;
        nNumb = 0;
        for (int i = 0; i < MAX_ERRO_NUMB; i++)
        {
            uErroCode[i] = 0;
        }
    }

    int nErroType;
    int nNumb;
    int32u uErroCode[MAX_ERRO_NUMB];  // MAX: 128/4 = 32
} ERRO_INFO;

// 设备版本信息
typedef struct tagVerInfo
{
    tagVerInfo()
    {
        strDspVer = "";
        strFpgaVer = "";
        strArmVer = "";
    }

    string strDspVer;
    string strFpgaVer;
    string strArmVer;

} VER_INFO;

typedef struct tagEthCfg
{
    tagEthCfg()
    {
        strDHCP = "0";
        strIP = "0.0.0.0";
    }
    string strDHCP;
    string strIP;
} EthCfg;

typedef struct tagControllerEthCfg
{
    EthCfg strcEth0;
    EthCfg strcEth1;
} ControllerEthCfg;

// 轴空间结构参数(Double型)
struct AXIS_DBPARAM
{
    AXIS_DBPARAM()
    {
        Reset();
    }
    // 拷贝构造函数
    AXIS_DBPARAM(const AXIS_DBPARAM &other)
    {
        for (int i = 0; i < AXIS_NUMB; i++)
        {
            dbValue[i] = other.dbValue[i];
        }
    }
    // 赋值函数
    AXIS_DBPARAM &operator=(const AXIS_DBPARAM &other)
    {
        if (this == &other)
        {
            return *this;
        }
        for (int i = 0; i < AXIS_NUMB; i++)
        {
            dbValue[i] = other.dbValue[i];
        }
        return *this;
    }
    // 重置
    void Reset(void)
    {
        memset(this, 0, sizeof(AXIS_DBPARAM));
    }
    // operator ==
    bool operator==(const AXIS_DBPARAM &other)
    {
        if (this == &other)
        {
            return true;
        }

        bool bEqual = true;
        for (int i = 0; i < AXIS_NUMB; i++)
        {
            if (dbValue[i] != other.dbValue[i])
            {
                return false;
            }
        }
        return bEqual;
    }
    double dbValue[AXIS_NUMB];
};

// 轴空间结构参数(Int型)
typedef struct tagAxisIntParam
{
    tagAxisIntParam()
    {
        for (int i = 0; i < AXIS_NUMB; i++)
        {
            IntValue[i] = 0;
        }
    }

    int IntValue[AXIS_NUMB];

} AXIS_INTPARAM;

// 备用参数(INT16型)
typedef struct tagIntBackupParam
{
    tagIntBackupParam()
    {
        for (int i = 0; i < INT_BACKUP_PARAM_NUMB; i++)
        {
            IntValue[i] = 0;
        }
    }

    int16s IntValue[INT_BACKUP_PARAM_NUMB];

} INT_BACKUPPARAM;

// 备用参数(double型)
typedef struct tagDbBackupParam
{
    tagDbBackupParam()
    {
        for (int i = 0; i < DB_BACKUP_PARAM_NUMB; i++)
        {
            dbValue[i] = 0.0;
        }
    }

    double dbValue[DB_BACKUP_PARAM_NUMB];

} DB_BACKUPPARAM;

// 备用参数(double型)
typedef struct tagDebugInfo
{
    tagDebugInfo()
    {
        memset(szBuf, 0, sizeof(szBuf));
    }

    char szBuf[DEBUG_INFO_LEN];
} DEBUG_INFO;

// 权限密码
typedef struct tagUesrPwd
{
    tagUesrPwd()
    {
        eUserMode = USER_UNKNOW;
        memset(szPwd, 0, sizeof(szPwd));
    }

    EUSER_MODE eUserMode;
    char szPwd[MAX_PWD_SIZE + 1];
} USER_PWD;

// 机器人类型名
typedef struct tagRobotName
{
    tagRobotName()
    {
        memset(szRobotName, 0, sizeof(szRobotName));
    }
    char szRobotName[128];
} ROBOT_NAME;

// B变量值
typedef struct tagBVar
{
    tagBVar()
    {
        for (int i = 0; i < B_VAR_NUMB; i++)
        {
            IntValue[i] = 0;
        }

        nCurPageId = 0;
        MaxPageId = 25;
    }
    unsigned char IntValue[B_VAR_NUMB];

    int nCurPageId;  //= 0;
    int MaxPageId;   // = 25;
} B_VAR;

// D变量值
typedef struct tagDVar
{
    tagDVar()
    {
        for (int i = 0; i < D_VAR_ARR_SIZE; i++)
        {
            DbValue[i] = 0;
        }

        nCurPageId = 0;
        MaxPageId = 25;
    }
    int nOffset;  // 从第几个变量开始读写
    double DbValue[D_VAR_ARR_SIZE];

    int nCurPageId;  //= 0;
    int MaxPageId;   // = 25;
} D_VAR;

// R变量值
typedef struct tagRVar
{
    tagRVar()
    {
        for (int i = 0; i < R_VAR_ARR_SIZE; i++)
        {
            IntValue[i] = 0;
        }

        nCurPageId = 0;
        MaxPageId = 25;
    }
    int nOffset;  // 从第几个变量开始读写
    int IntValue[R_VAR_ARR_SIZE];
    //
    int nCurPageId;  //= 0;
    int MaxPageId;   // = 25;
} R_VAR;

// LB变量值
typedef struct tagLBVar
{
    tagLBVar()
    {
        for (int i = 0; i < LB_VAR_NUMB; i++)
        {
            IntValue[i] = 0;
        }

        nCurPageId = 0;
        MaxPageId = 25;
    }
    unsigned char IntValue[LB_VAR_NUMB];

    //
    int nCurPageId;  //= 0;
    int MaxPageId;   // = 25;
} LB_VAR;

// LD变量值
typedef struct tagLDVar
{
    tagLDVar()
    {
        for (int i = 0; i < LD_VAR_ARR_SIZE; i++)
        {
            DbValue[i] = 0;
        }

        nCurPageId = 0;
        MaxPageId = 25;
    }
    int nOffset;  // 从第几个变量开始读写
    double DbValue[LD_VAR_ARR_SIZE];

    //
    int nCurPageId;  //= 0;
    int MaxPageId;   // = 25;
} LD_VAR;

// LR变量值
typedef struct tagLRVar
{
    tagLRVar()
    {
        for (int i = 0; i < LR_VAR_ARR_SIZE; i++)
        {
            IntValue[i] = 0;
        }

        nCurPageId = 0;
        MaxPageId = 25;
    }
    int nOffset;  // 从第几个变量开始读写
    int IntValue[LR_VAR_ARR_SIZE];

    //
    int nCurPageId;  //= 0;
    int MaxPageId;   // = 25;
} LR_VAR;

////////////////////////////////////////////////////////////////
// 功能：B\R\D数值查询类
// 特性：查询1个值，可用数组，查询不连续的一组值
// 作者：zhangyan 2017.06.02
////////////////////////////////////////////////////////////////
typedef struct tagSearchBVal
{
    tagSearchBVal()
    {
        nIndex = -1;
        nValue = 0;
    }

    void Reset()
    {
        nIndex = -1;
        nValue = 0;
    }
    int nIndex;
    unsigned char nValue;
} SearchB;

typedef struct tagSearchRVal
{
    tagSearchRVal()
    {
        nIndex = -1;
        nValue = 0;
    }

    void Reset()
    {
        nIndex = -1;
        nValue = 0;
    }
    int nIndex;
    int nValue;
} SearchR;

typedef struct tagSearchDVal
{
    tagSearchDVal()
    {
        nIndex = -1;
        nValue = 0;
    }

    void Reset()
    {
        nIndex = -1;
        nValue = 0;
    }
    int nIndex;
    double nValue;
} SearchD;

// 混合查询BRD，可用数组查询不连续而且不同类型的值
typedef struct tagMixSearchVal
{
    tagMixSearchVal()
    {
        nType = 0;
        nIndex = -1;
        nValueB = 0;
        nValueR = 0;
        nValueD = 0;
    }

    void Reset()
    {
        nType = 0;
        nIndex = -1;
        nValueB = 0;
        nValueR = 0;
        nValueD = 0;
    }
    int nType;  // 1-B 2-R 3-D
    int nIndex;
    unsigned char nValueB;
    int nValueR;
    double nValueD;
} MixSearchV;

typedef struct
{
    int Coord;                 // 坐标系号
    int ToolNo;                // 工具号
    int UserNo;                // 用户坐标系号
    int ArmParm[4];            // 臂参数
    double PosData[AXIS_NUM];  // 坐标值
} PointData;

typedef struct tagPalletInfo
{
    tagPalletInfo()
    {
        isdefined = 0;
        LayerNum = 0;   // 层数
        NumPerLay = 0;  // 每层个数
        IsLabel = 0;    // 标签朝外
        IsReverse = 0;  // 奇偶层反向
        ToolNo = 0;
        memset(PalletName, 0, 20);
        memset(ModelName, 0, 20);
        LayerHi = 0;       // 层高
        ProductLen = 0;    // 货物长
        ProductWidth = 0;  // 货物高
        TrayLen = 0;       // 托盘长
        TrayWidth = 0;     // 托盘高
        LimitHi = 0;       // 限制高
        Distance = 0;      // 间距
        dBaseA = 0;
    }

    struct tagPalletInfo &operator=(const struct tagPalletInfo &other)
    {
        isdefined = other.isdefined;
        LayerNum = other.LayerNum;
        NumPerLay = other.NumPerLay;
        IsLabel = other.IsLabel;
        IsReverse = other.IsReverse;
        ToolNo = other.ToolNo;
        memcpy(PalletName, other.PalletName, 20);
        memcpy(ModelName, other.ModelName, 20);

        LayerHi = other.LayerHi;
        ProductLen = other.ProductLen;
        ProductWidth = other.ProductWidth;
        TrayLen = other.TrayLen;
        TrayWidth = other.TrayWidth;
        LimitHi = other.LimitHi;
        Distance = other.Distance;
        dBaseA = other.dBaseA;

        return *this;
    }

    int isdefined;
    int LayerNum;   // 层数
    int NumPerLay;  // 每层个数
    int IsLabel;    // 标签朝外
    int IsReverse;  // 奇偶层反向
    int ToolNo;
    char PalletName[20];  // 托盘名
    char ModelName[20];   // 垛型名
    double LayerHi;       // 层高
    double ProductLen;    // 货物长
    double ProductWidth;  // 货物宽
    double TrayLen;       // 托盘长
    double TrayWidth;     // 托盘宽
    double LimitHi;       // 限制高
    double Distance;      // 间距
    double dBaseA;        // 托盘原点的角度值
} PalletInfo;

// PR变量值
typedef struct tagPalletVar
{
    tagPalletVar()
    {
        nOffset = 0;
    }
    int nOffset;  // 从第几个变量开始读写
    PalletInfo PalletArr[PALLET_VAR_NUMB];
} Pallet_VAR;
#ifndef POS_ITEM
    #define POS_ITEM
typedef struct
{
    int PointNo;
    PointData mPos;
} POSITEM;
#endif
// P变量值
typedef struct tagPVar
{
    tagPVar()
    {
        nOffset = 0;
    }
    int nOffset;  // 从第几个变量开始读写
    POSITEM PArr[P_VAR_NUMB];
} P_VAR;

// Str变量值
typedef struct tagSTRVar
{
    tagSTRVar()
    {
        nOffset = 0;
    }
    int nOffset;  // 从第几个变量开始读写
    string Str[STR_VAR_NUMB];
} STR_VAR;

struct stLockData
{
    stLockData()
    {
        xPos = 0;
        yPos = 0;
    }
    int xPos;
    int yPos;
};
typedef struct stLockData LOCKDATA_T;

typedef struct tagLockDataArr
{
    tagLockDataArr()
    {
        PosNum = 0;
    }
    int PosNum;
    LOCKDATA_T m_LockData[255];
} LOCKDATA_ARR;

// 直接运动/寸动参数
typedef struct tagMotionParam
{
    tagMotionParam()
    {
        uModeFlag = 0;
        dbJogDistan = 0;

        for (int i = 0; i < AXIS_NUMB; i++)
        {
            dbJointPos[i] = 0.0;
        }
    }

    int16u uModeFlag;  // 模式:0-非直接运动,1-直接运行, 2-寸动
    // 非直接运动/寸动 需将此模式恢复为 0

    double dbJogDistan;            // 寸动长度 [选择寸动模式时（仅示教模式）下发，并设置模式为：2寸动]
    double dbJointPos[AXIS_NUMB];  // 关节数据 [位置变量直接运行时（仅示教模式）下发，并设置模式为：1直接运行]
} MOTION_PARAM;

// EMC测试监控参数
typedef struct tagEmcTestParam
{
    EMC_MOD EmcMode;
    EMC_PING PingParam;
    EMC_TEACHBOX TeachBoxParam;
    EMC_CAN CanParam;
    EMC_USB UsbParam;
    EMC_SD SdParam;
    EMC_DIDO DIDOParam;
    EMC_RS485 Rs485Param;
    EMC_RS422 Rs422Param;
} EMCTEST_PARAM;

// 轴回零参数
typedef struct tgaAxisHomingParam
{
    tgaAxisHomingParam()
    {
        uAxisId = 0;
        uHomingSeq = 0;
        sMethod = 0;
        sOffset = 0;
        uSpeed = 0;
        uZeroSpeed = 0;
        uAcc = 0;
    }

    int16u uAxisId;     // 轴号
    int16u uHomingSeq;  // 顺序
    int8s sMethod;      // 模式
    int32s sOffset;     // 偏移
    int32u uSpeed;      // 速度
    int32u uZeroSpeed;  // 接近零点速度
    int32u uAcc;        // 加速度
} AXIS_HOMINGPARAM;

// 回零参数设置状态
typedef struct tagHmSetStatus
{
    tagHmSetStatus()
    {
        for (int i = 0; i < AXIS_NUMB; i++)
        {
            uSetStatus[i] = 0;
        }
    }

    int16u uSetStatus[AXIS_NUMB];  // 0-设置失败, 1-设置成功
} HM_SETSTATUS;

// 回零状态
typedef struct tagHomingStatus
{
    tagHomingStatus()
    {
        for (int i = 0; i < AXIS_NUMB; i++)
        {
            uHmStatus[i] = 0;
        }
    }

    int16u uHmStatus[AXIS_NUMB];  // 回零状态: 0 未知, 1 失败, 2 成功
} HM_STATUS;

#define MAX_MAPIO_CNT      (17)
#define MAX_SUBPRG_CNT     (5)
#define MAX_SUBPRG_OUT_CNT (6)
#define MAX_PRG_PATH       (100)
#define MAX_PRG_ID         (4)
#define MIN_PRG_ID         (0)
typedef struct IOMapInfo
{
    IOMapInfo()
    {
        for (int i = 0; i < MAX_MAPIO_CNT; i++)
            IOIndex[i] = -1;

        memset(&sFunction[0][0], 0x00, MAX_SUBPRG_CNT * MAX_PRG_PATH);
    }

    INT16 IOIndex[MAX_MAPIO_CNT];
    char sFunction[MAX_SUBPRG_CNT][MAX_PRG_PATH];
} IOMapInfo;

#define MAX_AXIS_TYPE_CNT (128)
struct AxisNumMap
{
    UINT16 u16RobotType;
    UINT16 u16ActAxisNum;
};
typedef struct AxisNumMap AXISNUMMAP;

typedef enum
{
    RBTYPE_INVALID = 0,
    // 3轴
    RBTYPE_SCARA_C = 46,            // 3关节串联scara无Z轴；
    RBTYPE_SCARA_E = 47,            // 3关节串联scara无A轴；
    RBTYPE_DELTA_A = 41,            // 3轴对称并联+1轴旋转的delta
    RBTYPE_DELTA_B = 45,            // 3轴对称并联的delta
    RBTYPE_SCARA_SCREW_THREE = 48,  // 3轴+外司电批轴（三轴挂于EtherCat总线上，电批独立）
    RBTYPE_SCARA_SCREW_FOUR = 44,   // 3轴+本司电批轴（全部挂于EtherCat总线上，电批非独立）
    // 4轴
    RBTYPE_SCARA_A = 4,      // 4关节串联scara
    RBTYPE_SCARA_R = 4110,   // 倒装scara
    RBTYPE_PALLET_A = 42,    // 码垛一型
    RBTYPE_PALLET_B = 43,    // 码垛二型
    RBTYPE_SCARA_D = 4140,   // 平面SCARA，不联动
    RBTYPE_TRIPOD_A = 4710,  // tripod，3D打印机械手A
    RBTYPE_TRIPOD_B = 4720,  // tripod，3D打印机械手B
    RBTYPE_PUNCH_A = 4800,   // 冲压机械手
    RBTYPE_FOUR_NA = 4900,   // 四轴联动，无模型 PPRR
    // 5轴
    RBTYPE_FIVE_A = 5,   // 3p2r
    RBTYPE_FIVE_B = 51,  // 3p2r
    // 6轴
    RBTYPE_SIXR_A = 6,   // 通用串联6R
    RBTYPE_SIXR_B = 61,  // 通用串联6R减去两轴
    RBTYPE_SIXR_C = 62,  // 变异SCARA+2直线轴 科瑞
    RBTYPE_SIXR_D = 63,  // 6轴并联机器人 Stewart
#ifdef COBOT
    RBTYPE_COBOT = 6410  // 协作机器人
#endif
} RBTTYPE_E;

typedef struct stPosition
{
    stPosition()
    {
        memset(&dPos[0], 0x00, sizeof(double) * 6);
    }

    struct stPosition &operator=(const struct stPosition &other)
    {
        memcpy(&dPos[0], &other.dPos[0], sizeof(double) * 6);

        return (*this);
    }

    bool operator==(const struct stPosition &other)
    {
        if (this == &other)
            return true;

        bool bEqual = true;
        for (int i = 0; i < 6; i++)
        {
            if (dPos[i] != other.dPos[i])
            {
                bEqual = false;
                break;
            }
        }

        return bEqual;
    }

    bool operator!=(const struct stPosition &other)
    {
        if (this == &other)
            return false;

        bool bNotEqual = false;
        for (int i = 0; i < 6; i++)
        {
            if (dPos[i] != other.dPos[i])
            {
                bNotEqual = true;
                break;
            }
        }

        return bNotEqual;
    }

    double dPos[6];

} CPOSITION;

typedef struct tagDAState
{
    tagDAState()
    {
        bFavorite = 0;
        DAKind = 0;
        MinValue = 0;
        MaxValue = 20;  // 默认电流 0-20mA
        ActualValue = 0;
        bDOut = 0;
    }
    int bFavorite;
    int DAKind;          // 0 电流  1 电压
    double MinValue;     // 范围 最小值
    double MaxValue;     // 范围最大值
    double ActualValue;  // 实际的值
    int bDOut;           // 输出开关 0 不输出 1 输出
} DA_STATE;

//////////////////锁螺丝结构体
typedef struct stLockScrewSetPara
{
    stLockScrewSetPara()
    {
        memset(name, 0x00, 20);
        ValidFlag = 0;
        SearchSpeed = 0;
        SearchTorque = 0;
        HighSpeed = 0;
        HighTorque = 0;
        TarSpeed = 0;
        TarTorque = 0;
        LockMinCircle = 0;
        LockMaxCircle = 0;
        SoftStartTime = 0;
        SearchTimeOut = 0;
        TarTorqueHT = 0;
    }

    char name[20];      // 备注名
    int ValidFlag;      // 是否有效
    int SearchSpeed;    // 搜索速度
    int SearchTorque;   // 搜索转矩
    int HighSpeed;      // 高速速度
    int HighTorque;     // 高速转矩
    int TarSpeed;       // 目标速度
    int TarTorque;      // 目标转矩
    int LockMinCircle;  // 锁付最小圈数
    int LockMaxCircle;  // 锁付最大圈数
    int SoftStartTime;  // 软启动时间
    int SearchTimeOut;  // 搜索超时时间
    int TarTorqueHT;    // 目标转矩保持时间

} LOCK_SCREW_SET_PARAMS;

typedef struct stUnLockScrewSetPara
{
    stUnLockScrewSetPara()
    {
        memset(name, 0x00, 20);
        ValidFlag = 0;
        UnLockSearchSpeed = 0;
        UnLockSearchTorque = 0;
        ScrewToothPitch = 0;
        UnLockCircle = 0;
        UnLockWaitTime = 0;
    }
    char name[20];           // 备注名
    int ValidFlag;           // 是否有效
    int UnLockSearchSpeed;   // 搜索速度 	rpm
    int UnLockSearchTorque;  // 搜索转矩 	0.1%NM
    int ScrewToothPitch;     // 螺丝牙距 0.01mm
    int UnLockCircle;        // 拆螺丝圈数 0.001NM
    int UnLockWaitTime;      // 拆螺丝等待时间 ms

} UNLOCK_SCREW_SET_PARAMS;

typedef struct stScrewDriver_FACTORY_SETTING
{
    int MotorDir;  // 电机方向:拧紧方向
} SCREWDRIVER_FACTORY_SETTING;

typedef struct stSCREWDRIVER_PROJECT_STR
{
    char ProFileName[64];
    SCREWDRIVER_FACTORY_SETTING ScrewdriverFacSetting;
    LOCK_SCREW_SET_PARAMS LockScrewSetParms[16];
    UNLOCK_SCREW_SET_PARAMS UnLockScrewSetParms[16];
} SCREWDRIVER_PROJECT;

typedef struct stScrewMonPara
{
    stScrewMonPara()
    {
        LockScrewCount = 0;
        QFCount = 0;
        NGCount = 0;
        SlippageCount = 0;
        FloatLockCount = 0;
        LockPeriod = 0;
        LockCircle = 0;
    }
    int LockScrewCount;  // 锁螺丝计数
    int QFCount;         // 锁好个数
    int NGCount;         // NG个数
    int SlippageCount;   // 滑牙计数
    int FloatLockCount;  // 浮锁计数
    int LockPeriod;      // 锁付周期ms
    int LockCircle;      // 锁付圈数
    int EndTorque;       // 终点扭矩
} SCREW_MON;

// PING功能
// ping to check net state
typedef struct net_check_para
{
    net_check_para()
    {
        memset(addr, 0x00, 16);
        term = 0;
        total = 0;
        size = 0;
    }

    char addr[16];  // IP地址
    int term;       // 周期
    int total;      // 总数
    int size;       // 每包大小
} net_check_para_t;

typedef struct net_check_ret
{
    int nsend;    // 已发送
    int nrec;     // 已接受
    double loss;  // 丢失率
    double min;   // 最小往返时间
    double max;   // 最长往返时间
    double avg;   // 平均往返时间

} net_check_ret_t;

typedef struct _servo_param
{
    _servo_param()
        : mass(0)
    {
        memset(Kp, 0, sizeof(Kp));
        memset(Kv, 0, sizeof(Kv));
        memset(Ki, 0, sizeof(Ki));
        memset(loadInertiaRatio, 0, sizeof(loadInertiaRatio));
    }
    UINT16 index;                        // 当前使用的参数组号
    double mass;                         // 当前工具与手持工件质量之和
    UINT16 Kp[AXIS_NUMB];                // 伺服 位置环 增益
    UINT16 Kv[AXIS_NUMB];                // 伺服 速度环 增益
    UINT16 Ki[AXIS_NUMB];                // 伺服 电流环 增益
    UINT16 loadInertiaRatio[AXIS_NUMB];  // 平均负载转动惯量
} _SERVO_PARAM;

// 伺服参数设置结构体定义
typedef struct servo_param
{
    typedef enum SERVO_PARAM_SET_MODE : UINT16
    {
        INVALID_MODE,   // 无效模式
        ADAPTIVE_MODE,  // 自适应模式
        CUSTOM_MODE,    // 自定义模式
    } SERVO_PARAM_SET_MODE;
    typedef enum ISRECOMMEND : UINT16
    {
        NORECOMMEND,  // 使用推荐参数
        RECOMMEND,
    } ISRECOMMEND;
    // 参数初始化
    servo_param()
        : setMode(INVALID_MODE),
          usedIndex(0),
          isRecommend(NORECOMMEND)
    {
        servoParam.index = usedIndex;
    }
    SERVO_PARAM_SET_MODE setMode;  // 伺服参数设置模式
    UINT16 usedIndex;              // 当前使用的参数组号，与index相同
    ISRECOMMEND isRecommend;       // 是否使用推荐值 0--推荐，1--不推荐
    _SERVO_PARAM servoParam;       // 伺服参数
} SERVO_PARAM;

// TCP
typedef struct tagModbusTCP_Para
{
    tagModbusTCP_Para()
    {
        owner = 0;
        sts = 0;
        port = 502;
        framedelay = 1;
    }
    unsigned char owner;        // 控制权 0-未开启，1-二次开发，2-控制器
    unsigned char sts;          // 运行情况 0-未运行，1-运行
    unsigned short port;        // 端口号
    unsigned short framedelay;  // 帧间隔
} ModbusTCP_Para;

// RTU
typedef struct tagModbusRTU_Para
{
    tagModbusRTU_Para()
    {
        owner = 0;
        sts = 0;
        baud = 5;
        stopbits = 0;
        databits = 0;
        parity = 0;
        tmode = 0;
        slaveid = 1;
        framedelay = 5;
        timeout = 0;
    }
    unsigned char owner;        // Modbus控制权 0-未开启，1-二次开发，2-控制器
    unsigned char sts;          // Modbus 运行情况 0-未运行，1-运行
    unsigned char baud;         // 波特率，索引值，其具体值见Baud数组
    unsigned char stopbits;     // 停止位 0-1位 1-2位
    unsigned char databits;     // 数据位 0-7位 1-8位
    unsigned char parity;       // 奇偶校验 0-无校验 1-奇校验 2-偶校验
    unsigned char tmode;        // 传输模式 0-RTU 1-ASCII
    unsigned char slaveid;      // 站点号
    unsigned short framedelay;  // 帧间隔
    unsigned short timeout;     // 超时时间
} ModbusRTU_Para;

// Modbus写入总结构体
typedef struct MODBUS_PARA_CONFIG
{
    MODBUS_PARA_CONFIG()
    {
        ModbusAddrType = 0;  // 0-旧版地址
    };
    unsigned char ModbusAddrType;    // Modbus地址类型 0-旧版地址，1-新版地址
    ModbusTCP_Para stModbusTcpPara;  // Modbus配置结构体
    ModbusRTU_Para stModbusRtuPara;  // ModbusRtu配置结构体
} ModbusParaConfig;

// Modbus读取总结构体
typedef struct MODBUS_CONNECT_STS
{
    MODBUS_CONNECT_STS()
    {
        ModbusAddrType = 0;
        for (int i = 0; i < 16; i++)
        {
            ModbusTcpConnectFlag[i] = 0;  // 0表示未连接
            ModbusTcpClientPort[i] = 502;
            memset(&ModbusTcpClientIP[i], 0, 16 * sizeof(unsigned char));
        }
    }

    unsigned char ModbusAddrType;            // Modbus地址类型 0-旧版地址，1-新版地址
    ModbusTCP_Para stModbusTcpPara;          // Modbus配置结构体
    ModbusRTU_Para stModbusRtuPara;          // ModbusRtu配置结构
    char ModbusTcpConnectFlag[16];           // modbusTcp连接状态，0表示未连接，1表示已连
    char ModbusTcpClientIP[16][16];          // 主站IP地址（第一行表示第一个连接上的主站的IP）
    unsigned short ModbusTcpClientPort[16];  // 主站端口（第一元素表示第一个连接上的主站的端口）
} ModbusConnectSts;

// EthernetIp 写入状态
typedef struct _ETHERNET_IP_PARA_
{
    _ETHERNET_IP_PARA_()
    {
        ActiveCmd = 0;  // 0表示关闭
    }
    unsigned char ActiveCmd;  // 0表示关闭，1表示激活
} EthernetIpPara;

// EthernetIp 读取状态
typedef struct _ETHERNET_IP_STS_
{
    _ETHERNET_IP_STS_()
    {
        ActiveSts = 0;  // 0-未开启
        ConnectSts = 0;
        for (int i = 0; i < 16; i++)
        {
            MsterIp[i] = 0;  // 0-未连接
        }
        MasterPort = 502;   // EIP主站(客户端)的端口
        SlavePort = 44818;  // 固定为44818
    }
    unsigned char ActiveSts;    // EIP激活状态:0-未开启，1-已开启
    unsigned char ConnectSts;   // EIP连接状态:0-未连接，1-已连接
    char MsterIp[16];           // EIP主站(客户端)IP地址
    unsigned short MasterPort;  // EIP主站(客户端)的端口
    unsigned short SlavePort;   // EIP从站(服务器)端口,暂时固定为44818
} EthernetIpSts;

// 写入Ethcat
typedef struct _ETHCAT_PARA_
{
    _ETHCAT_PARA_()
    {
        ActiveCmd = 0;
        SiteAlias = 0;
        MaxFramLossTimes = 0;
    };

    unsigned char ActiveCmd;          // 0表示关闭，1表示激活
    unsigned short SiteAlias;         // 站点别名（默认值为0）
    unsigned short MaxFramLossTimes;  // 最大丢站次数（默认值为8次，最小值为8，最大值为65535）
} EthcatPara;

// 读取Ethcat
typedef struct _ETHCAT_STS_
{
    _ETHCAT_STS_()
    {
        ActiveSts = 0;   // 0-未开启
        ConnectSts = 0;  // 0-未连接
        SiteAlias = 0;
        MaxFramLossTimes = 8;
    }
    unsigned char ActiveSts;          // Ethcat激活状态:0-未开启，1-已开启
    unsigned char ConnectSts;         // Ethcat连接状态:0 - 未连接，1 - 已连接
    unsigned short SiteAlias;         // 站点别名（默认值为0）
    unsigned short MaxFramLossTimes;  // 最大丢站次数（默认值为8次）
} EthcatSts;

typedef struct ETHCAT_PROP
{
    ETHCAT_PROP()
    {
        u8LinkState = 0;
        u8EscState = 0;
        u16AppFaultCode = 0;
        u16AppStateCode = 0;
        u8Port0InvFraCount = 0;
        u8Port0AptErrFraCount = 0;
        u8Port1InvFraCount = 0;
        u8Port1AptErrFraCount = 0;
        u8Port0ForErrCount = 0;
        u8Port1ForErrCount = 0;
        u8DataFrmProcessingErrCount = 0;
        u8PIDErrCount = 0;
        u8Port0LinkLostCount = 0;
        u8Port1LinkLostCount = 0;
        u16MCUUpSlaveLost = 0;
        u16SlaveAdderss = 0;
        u16ESCVerInfor = 0;
        u16MCUUpXMLVerInfor = 0;
        u16SoftVersion = 0;
        u16ARMSetLinkEnhanSwitch = 0;
        u16EtherCATXMLReset = 0;
    }

    int8u u8LinkState;                 /* PHY - link状态(Bit0为端口0,Bit1为端口1，0:No Link，1:Link) */
    int8u u8EscState;                  /* EtherCAT状态机(1：Init 2：PreOP 4：SafeOP 8：OP) */
    int16u u16AppFaultCode;            /* 通信故障码 */
    int16u u16AppStateCode;            /* 应用层状态码 */
    int8u u8Port0InvFraCount;          /* 端口0无效帧计数 */
    int8u u8Port0AptErrFraCount;       /* 端口0接收错误帧计数 */
    int8u u8Port1InvFraCount;          /* 端口1无效帧计数 */
    int8u u8Port1AptErrFraCount;       /* 端口1接收错误帧计数 */
    int8u u8Port0ForErrCount;          /* [7:0]: 端口0转发错误计数 */
    int8u u8Port1ForErrCount;          /* [15:8]: 端口1转发错误计数 */
    int8u u8DataFrmProcessingErrCount; /* [7:0]: 数据帧处理单元错误计数 */
    int8u u8PIDErrCount;               /* [15:8]: PDI错误计数 */
    int8u u8Port0LinkLostCount;        /* [7:0]: 端口0链接丢失计数 */
    int8u u8Port1LinkLostCount;        /* [15:8]: 端口1链接丢失计数 */
    int16u u16MCUUpSlaveLost;          /* MCU上传从站累积丢帧计数; ARM读 */
    int16u u16SlaveAdderss;            /* MCU上传主站设置的站点正名; ARM读 */
    int16u u16ESCVerInfor;             /* MCU上传ESC的版本信息; ARM读 */
    int16u u16MCUUpXMLVerInfor;        /* MCU上传XML版本信息; ARM读 */
    int16u u16SoftVersion;             /* MCU上传软件版本号; ARM读 */
    int16u u16ARMSetLinkEnhanSwitch;      //ARM设定链路增强开关, ARM可读可写(0-open; 1-close)
    int16u u16EtherCATXMLReset;           //ARM设定执行XML复位(0-open; 1-close)
} ETHCAT_PROP;

typedef enum
{
    NOPE = -1,  // 不显示
    PART = 0,   // 部分显示
    WHOLE = 1   // 整个显示
}ETHCAT_PROP_SHOWSTRATEGY;

// 现场总线从站配置信息
typedef struct MODBUS_ADDRASSIGN_CONFIG
{
    MODBUS_ADDRASSIGN_CONFIG()
    {
        inputSize = 256;
        outputSize = 256;
        modbusInputCoilSize = 20;
        modbusInputRegSize = 236;
        modbusOutputCoilSize = 20;
        modbusOutputRegSize = 236;
    };
    unsigned short inputSize;
    unsigned short outputSize;
    unsigned short modbusInputCoilSize;
    unsigned short modbusInputRegSize;
    unsigned short modbusOutputCoilSize;
    unsigned short modbusOutputRegSize;
} ModbusAddrassignConfig;

struct EIP_ADDRASSIGN_CONFIG
{
    EIP_ADDRASSIGN_CONFIG()
    {
        inputSize = 256;
        outputSize = 256;
    };
    unsigned short inputSize;
    unsigned short outputSize;
};

struct ETHERCAT_ADDRASSIGN_CONFIG
{
    ETHERCAT_ADDRASSIGN_CONFIG()
    {
        inputSize = 256;
        outputSize = 256;
    };
    unsigned short inputSize;
    unsigned short outputSize;
};

struct MC_ADDRASSIGN_CONFIG
{
    MC_ADDRASSIGN_CONFIG()
    {
        inputSize = 256;
        outputSize = 256;
        mcInputStartAddr = 1025;
        mcInputRegSize = 2025;
        mcOutputStartAddr = 256;
        mcOutputRegSize = 256;
    };
    unsigned short inputSize;
    unsigned short outputSize;
    unsigned short mcInputStartAddr;
    unsigned short mcInputRegSize;
    unsigned short mcOutputStartAddr;
    unsigned short mcOutputRegSize;
};

struct PN_ADDRASSIGN_CONFIG
{
    PN_ADDRASSIGN_CONFIG()
    {
        inputSize = 127;
        outputSize = 127;
    }
    unsigned short inputSize;
    unsigned short outputSize;
};

struct FIELDBUS_MEM_ASSIGN_CONFIG
{
    FIELDBUS_MEM_ASSIGN_CONFIG()
    {
        memset(Version, 0, sizeof(char) * 8);
        for (int i = 0; i < 4; i++)
        {
            MC_ADDRASSIGN_CONFIG mc;
            mcConfig[i] = mc;
        }
    };
    char Version[8];
    MODBUS_ADDRASSIGN_CONFIG modbusConfig;
    EIP_ADDRASSIGN_CONFIG eipConfig;
    ETHERCAT_ADDRASSIGN_CONFIG etherCATConfig;
    MC_ADDRASSIGN_CONFIG mcConfig[4];
    PN_ADDRASSIGN_CONFIG pnConfig;
};

// MC激活指令
typedef struct _MC_ACTIVE_PARA_
{
    _MC_ACTIVE_PARA_()
    {
        ActiveFlag = 0;  // 0表示关闭，1表示激活
    }
    // 激活指令
    unsigned char ActiveFlag;  // 0表示关闭，1表示激活
} McActivePara;

// MC连接状态
typedef struct _MC_CONNECT_PARA_
{
    _MC_CONNECT_PARA_()
    {
        for (int i = 0; i < 16; i++)
        {
            ServerIp[i] = 0;  // IP地址
        }
        ConnectIndex = 0;
        Port = 0;           // 端口号
        ConnectFlag = 0;    // 0未连接，1已连接
        IsAutoConnect = 0;  // 0-不进行自动重连，1-自动重连
    }
    unsigned char ConnectIndex;   // 连接索引
    unsigned char ServerIp[16];   // MC服务器IP
    unsigned short Port;          // MC端口号
    unsigned char ConnectFlag;    // 连接标识(读的时候标识状态，0-未连接，1-已连接；写的时候表示命令；0-断开，1-连接)
    unsigned char IsAutoConnect;  // 是否自动重连，0-不进行自动重连，1-进行自动重连
} McConnectPara;

// Profinet总线激活指令
typedef struct _BUS_PN_ACTIVE_CFG_
{
    _BUS_PN_ACTIVE_CFG_()
    {
        ActiveCmd = 0;
        MaxFrameDropNumber = 10;
    }
    unsigned char ActiveCmd;            // PN激活指令:0-关闭，1-激活
    unsigned short MaxFrameDropNumber;  // 允许的最大丢帧次数
} PnActiveCfg;

// Profinet总线连接状态
typedef struct _BUS_PN_CONNECT_STS_
{
    _BUS_PN_CONNECT_STS_()
    {
        ActiveSts = 0;
        ConnectSts = 0;
        for (int i = 0; i < 16; i++)
        {
            ProfinetIP[i] = 0;
            DefaultGateWay[i] = 0;
        }
        for (int j = 0; j < 18; j++)
        {
            MacAddress[j] = 0;
        }
        VersionID = 0;
        MaxFrameDropNumber = 10;
    }
    unsigned char ActiveSts;            // PN激活状态:0-未开启，1-已开启
    unsigned char ConnectSts;           // PN连接状态:0-未连接，1-已连接
    char ProfinetIP[16];                // ip地址
    char DefaultGateWay[16];            // 默认网关
    char MacAddress[18];                // MAC地址
    unsigned short VersionID;           // 版本号
    unsigned short MaxFrameDropNumber;  // 已设置的最大丢帧次数
} PnConnectSts;

/// <summary>
/// 自动热机参数
/// </summary>
typedef struct _WarmUpMachineParam_
{
    _WarmUpMachineParam_()
    {
        mode = 0;
        memset(axisEnableArr, 0, sizeof(axisEnableArr));
        threshold = 10;
        time = 10;
        initSpeed = 75;
        intervalTime = 20;
    }

    int16_t mode;                     // 热机策略，0表示关闭，1表示仅考虑热机时间，2表示考虑轴温度与热机时间
    int16_t axisEnableArr[AXIS_NUM];  // 轴号激活状态集合，数据长度为8(预留)，元素值1表示激活，0表示未激活，按轴序号存取
    int16_t threshold;                // 轴温度阈值
    int16_t time;                     // 热机时间
    int16_t initSpeed;                // 热机初始速度
    int16_t intervalTime;             // 重新热机时间间隔

} WarmUpMachineParam;

/// <summary>
/// 自动热机实时信息
/// </summary>
typedef struct _WarmUpMachineInfo_
{
    _WarmUpMachineInfo_()
    {
        state = 0;
        curSpeed = 0;
    }
    int16_t state;     // 热机状态，1表示热机中，0表示未在热机
    int16_t curSpeed;  // 热机时机器人当前速度
} WarmUpMachineInfo;

/// <summary>
/// 软浮动参数
/// </summary>
#pragma pack(1)
typedef struct _SoftMovePara_
{
    _SoftMovePara_()
    {
        i16Switch = 0;
        i16Mode = 0;
        i16RefCoor = 0;
        memset(i16CartSoftMoveRatio, 0, sizeof(i16CartSoftMoveRatio));
        memset(i16JointSoftMoveRatio, 0, sizeof(i16JointSoftMoveRatio));
        f32OperatRangeX = 200;
        f32OperatRangeY = 200;
        f32OperatRangeZ = 200;
    }

    int16s i16Switch;                              // 开关
    int16s i16Mode;                                // 软浮动模式
    int16s i16RefCoor;                             // 参考坐标系
    int16s i16CartSoftMoveRatio[JOINT_AXIS_NUM];   // 笛卡尔软浮动比率
    int16s i16JointSoftMoveRatio[JOINT_AXIS_NUM];  // 关节软浮动比率
    float f32OperatRangeX;                         // 补偿范围X
    float f32OperatRangeY;                         // 补偿范围Y
    float f32OperatRangeZ;                         // 补偿范围Z
} SoftMovePara;
#pragma pack()

// 系统诊断（错误保存和导出）
typedef struct _ErrsaveCmd_
{
    int item[3];  // item[0]系统参数 item[1]-逻辑参数  item[2]轨迹参数 //0-已勾选  1-未勾选
    int saveOpt;  // 0-null 1-保存  2-终止
} ErrsaveCmd;

typedef struct _ErrsaveSta_
{
    int saveRes;       // 诊断结果  -1-保存失败  0-null 1-保存中  2-保存成功  3-保存终止
    int saveProgress;  // 保存进度条值 0-100
} ErrsaveSta;

typedef struct _ErrexportCmd_
{
    int item[3];    // item[0]系统参数 item[1]-逻辑参数  item[2]轨迹参数 //0-已勾选  1-未勾选
    int exportOpt;  // 0-null 1-导出全部  2-导出最后一段轨迹数据
    int exportDst;  // 0-导出至电控柜USB  1-导出至控制器指定目录下待上位机程序自取
} ErrexportCmd;

typedef struct _ErrexportSta_
{
    int exportRes;       // 诊断结果  -1-导出失败 0-null 1-导出中  2-导出成功
    int exportProgress;  // 导出进度条值 0-100
} ErrexportSta;

// user-defined alarm configuration
typedef struct _stUserDefinedAlarmConfig
{
    _stUserDefinedAlarmConfig()
    {
        for (int i = 0; i < 16; i++)
        {
            strUserDefinedAlarmConfig[i] = "";
        }
    }

    struct _stUserDefinedAlarmConfig &operator=(const struct _stUserDefinedAlarmConfig &other)
    {
        if (this == &other)
            return *this;

        for (int i = 0; i < 16; i++)
            strUserDefinedAlarmConfig[i] = other.strUserDefinedAlarmConfig[i];

        return *this;
    }

    string strUserDefinedAlarmConfig[16];
} UserDefinedAlarmConfig;

// servo status item
typedef struct _stServoStateItem
{
    _stServoStateItem()
    {
        memset(cStateItem, 0x00, sizeof(cStateItem));
    }

    void Initialize()
    {
        memset(cStateItem, 0x00, sizeof(cStateItem));
    }

    char cStateItem[MAX_SERVO_STATEDATA_LEN];
} ServoStateItem;

// servo status data (axis)
typedef struct _stServoAxisState
{
    void Initialize()
    {
        for (int i = 0; i < MAX_SERVO_AXISSTATE_ITEMCNT; i++)
            stStateItem[i].Initialize();
    }

    ServoStateItem stStateItem[MAX_SERVO_AXISSTATE_ITEMCNT];
} ServoAxisState;

// servo status data (all)
typedef struct _stServoState
{
    void Initialize()
    {
        for (int i = 0; i < AXIS_NUMB; i++)
            stAxisState[i].Initialize();
    }

    ServoAxisState stAxisState[AXIS_NUMB];
} ServoState;

struct AddrInfo
{
    char IP[16] = { 0 };  // IP信息，位数最多16位：192.168.222.333
    int Port = 0;         // 端口信息
};

struct CommonNetStatus
{
    AddrInfo LocalAddrInfo;  // 本地网络信息
    AddrInfo PeerAddrInfo;   // 对端网络信息
    int NetStatus = 0;       // 0-客户端列表断开连接;1-新建连接;2-关闭服务务器;3-打开服务器 4-服务器列表断开连接
                             // V4R24C5版本（不包括V4R24C5）以前的通讯机制：0:unconnected;1:connected 2:主动关闭服务器端口
    int LocalNetType = 0;    // 通讯模式:0-客户端模式;1-服务器模式;2-同时作为客户端和服务器
};

struct stDIOComments
{
    stDIOComments()
    {
        for (int i = 0; i < MAXIONUM; i++)
        {
            m_DIComments[i] = "";
            m_DOComments[i] = "";
        }
    }

    string m_DIComments[MAXIONUM];
    string m_DOComments[MAXIONUM];
};
typedef struct stDIOComments DIOComments;

typedef struct stSysMaintenanceInfo
{
    stSysMaintenanceInfo()
    {
        Status = 0;
        Progress = 0;
        memset(Msg, 0, sizeof(Msg));
    }

    short Status;    // 下位机通信：0正在升降级；1升降级成功；其它表示失败见文档
    short Progress;  // 进度信息 0~100 %
    char Msg[80];    // 信息
} SysMaintenanceInfo;

// add 2019.8.29
typedef struct _ONE_SERVO_INFO
{
    unsigned char nAxisNum;  // 当前IP地址下的伺服支持的轴的数量
    char addr[19];
    unsigned short nPort;  // port in IP table
} ONE_SERVO_INFO;

typedef struct _ALL_SERVO_INFO
{
    unsigned char nServoNum;  // 当前在线的伺服数量，1≤servoNum≤4
    char axisName[10];
    char axisNameIndex[10];
    ONE_SERVO_INFO stServoInfo[4];  // 伺服信息数组，目前最多四个伺服
} ALL_SERVO_INFO;
// end

typedef struct _TASK_RUN_INFO_ITEM
{
    int16u StartLineNum;
    int16u RunLineNum;
    //	0:停止,	1:运行中, 2:单步, 4:暂停, 10:结束, 100:未激活, 255:空闲
    int8u State;
    int8u BreakpointFlag;       // 断点标志,0未进入断点，1进入断点；
    char StartLineProgram[32];  // 比如main.pro, sub1.pro，不含路径名
    char RunLineProgram[32];    // 比如main.pro, sub1.pro，不含路径名

    _TASK_RUN_INFO_ITEM()
    {
        StartLineNum = 0;
        RunLineNum = 0;
        State = 0;
        BreakpointFlag = 0;
        memset(StartLineProgram, 0, sizeof(StartLineProgram));
        memset(RunLineProgram, 0, sizeof(RunLineProgram));
    }
} TaskRunInfoItem;

typedef struct _TASKS_RUN_INFO
{
    TaskRunInfoItem Infos[4];
} TasksRunInfo;

typedef struct _SET_START_LINE_STU
{
    int8u TaskId;       // 任务号
    int16u LineNum;     // 起始行号
    char FileName[28];  // 程序名

    _SET_START_LINE_STU()
    {
        TaskId = 0;
        LineNum = 0;
        memset(FileName, 0, sizeof(FileName));
    }
} SetStartLineStu;

typedef struct _LINE_NUM_OPERATION_STU
{
    int8u OperationType;  // 操作类别 1:set;   2:back
    int8u OperateObject;  // 操作对象 1:all    2:single
    SetStartLineStu SetStartLineInfo;

    _LINE_NUM_OPERATION_STU()
    {
        OperationType = 0;
        OperateObject = 0;
    }
} LineNumOperationStu;

typedef unsigned char IndAxisStatusArr[14];

/*******************************************/
/*用于变量设置*/
/*******************************************/
typedef enum
{
    VALUE_ERR,
    VALUE_BOOL,
    VALUE_BYTE,
    VALUE_INT,
    VALUE_FLOAT,
    VALUE_DOUBLE,
    VALUE_CHAR,
    VALUE_SWITCH,
} VALUE_KIND;

typedef struct
{
    VALUE_KIND mValKind;
    union
    {
        bool bVal;
        unsigned char ucVal;
        int iVal;
        float fVal;
        double dVal;
        char spValue[256];
    };
} SETVAR_VALUE;

// 通过通讯设置全局变量的值
typedef struct _BRDP_INFO
{
    char varName[255];
    SETVAR_VALUE varValue;

    _BRDP_INFO()
    {
        memset(&varName[0], 0, 255);
        varValue.mValKind = VALUE_BOOL;
        varValue.bVal = false;
    }
} BRDP_INFO;

typedef struct torqueRectifyAutoLearnPara
{
    torqueRectifyAutoLearnPara()
    {
        learnSts = 0;
        memset(learnRet, 0, sizeof(double) * 8);
    }
    short learnSts;      // 学习状态（0-未开始 1-进行中 2-已完成 -1 出错）
    double learnRet[8];  // 学习结果
} TorqueRectifyAutoLearnPara;

// 总线类型
typedef enum
{
    FB_Unknow = 0,
    FB_Modbus = 1,
    FB_EthernetIp = 2,
    FB_EtherCATSlave = 3,
    FB_FINS = 4,
    FB_MC = 5,
    FB_Profinet = 6,
} E_FieldBusType;

typedef struct tagRobotMechFullPara
{
    tagRobotMechFullPara()
    {
        alpha1 = 0;
        alpha2 = 0;
        alpha3 = 0;
        alpha4 = 0;
        alpha5 = 0;
        beta2 = 0;
        d3 = 0;
        d5 = 0;
        a4 = 0;
        a5 = 0;
        gravAlpha = 0;
        gravBeta = 0;
        gravGamma = 0;
    }
    double alpha1;
    double alpha2;
    double alpha3;
    double alpha4;
    double alpha5;
    double beta2;
    double d3;
    double d5;
    double a4;
    double a5;
    double gravAlpha;
    double gravBeta;
    double gravGamma;
} TRobotMechFullPara;

typedef struct tagMotorProtectPara
{
    tagMotorProtectPara()
    {
        motorProtectFlag = 0;
        for (int i = 0; i < 8; i++)
        {
            maxEnergy[i] = 0;
            maxHighFreqPercent[i] = 0;
            maxStopError[i] = 0;
        }
    }
    int16u motorProtectFlag;       // 电机保护开关 0-关 1-开
    double maxEnergy[8];           // 波动能量
    double maxHighFreqPercent[8];  // 高频占比
    double maxStopError[8];        // 防止误报警参数

} MotorProtectPara;

typedef struct tagRAMGP
{
    tagRAMGP()
    {
        bExist = 0;
        PointNo = 0;
    }
    char bExist;  // 是否存在 0-不存在 1-存在
    int PointNo;
    PointData mPos;
} RAM_GP;

// 激活的工具参数 用于6关节全参
typedef struct _ActiveToolPara_
{
    _ActiveToolPara_()
    {
        mass = 0;
        loadcoordx = 0;
        loadcoordy = 0;
        loadcoordz = 0;
    }
    double mass;
    double loadcoordx;
    double loadcoordy;
    double loadcoordz;
} ActiveToolPara;

// 连接控制设备名称
typedef enum
{
    CONNECT_DEV_INIT = 0,      // 初始值
    CONNECT_DEV_PC_PLATFORM,   // InoRobotLab
    CONNECT_DEV_TEACH_PENDANT  // 示教器
} CONNECT_DEVICE_TYPE;
// #pragma pack()

#define MAINTAIN_KIND   2   // 维护种类
#define DATE_STRING_LEN 11  // 2021.12.07 字符串占用字节长度
// 机器人维护信息

#pragma pack(1)
typedef struct _MAINTAIN_REMINDER_
{
    _MAINTAIN_REMINDER_()
    {
        type = 0;
        showEnable = 0;
        state = 0;
        cycleDaysNum = 0;
        surplusPercentage = 0;
        memset(lastMaintainedTime, 0, sizeof(char) * DATE_STRING_LEN);
        memset(maintainedCutOffTime, 0, sizeof(char) * DATE_STRING_LEN);
    }
    int8u type;       // 组件类型
    bool showEnable;  // 组件是否显示  0 不显示 1：显示
    int8u state;
    // 当前状态：    0：ok   1:error
    int16u cycleDaysNum;                         // 维护周期 （天）
    int8u surplusPercentage;                     // 剩余时间占维护周期百分比 ：0-100
    char lastMaintainedTime[DATE_STRING_LEN];    // 上次维护时间  2021.12.07
    char maintainedCutOffTime[DATE_STRING_LEN];  // 维护有效截止时间
} MaintainReminder;
#pragma pack()

//////////////////////////////////////////////////////////////////////////
// S03.22版本
//////////////////////////////////////////////////////////////////////////
/******************* 点位结构体开始 ******************/
// 臂参数
#define ARM_TYPE_NUM (4)
// 机器人位置维度
#define POSE_AXIS_NUM (6)
// 外部轴数
#define EXT_AXIS_NUM (6)
// 机器人关节轴数
#define JOINT_AXIS_NUM (8)
// 负载参数质心位置（com）
#define POSIT_DIMENT (3)
// 负载参数质心的姿态（orient）
#define ORIENT_DIMENT (3)
// 负载惯量（inertia）
#define INERTIA_DIMENT (3)

typedef struct tagToolCalibError
{
    tagToolCalibError()
    {
        dMax = 0;
        dAve = 0;
        dMin = 0;
    }
    double dMax;
    double dAve;
    double dMin;
} ToolCalibError;

// 模块激活功能相关
typedef unsigned char CHIPROMID[8];
typedef unsigned char CHIPETAG[32];
typedef unsigned char CHIPUSERDATA[32];
typedef unsigned char CHIPSECRET[32];
typedef unsigned char ROBOTCONTROLLERSN[64];
