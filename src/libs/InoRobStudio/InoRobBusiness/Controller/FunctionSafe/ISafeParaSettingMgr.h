#pragma once
#include <string>
#include <memory>
#include <QObject>
#include "DataTypeDef.h"
#include "signal_slot.h"
#include "DataSrvGlobal.h"
#include "ParaData.h"
#include "UParaData.h"

using namespace std;

#define SPARA_INOBUS_MULTIPLE (4)  // 适配Inobus整除
#define SPARA_INOBUS_TAIL     (2)  // 适配Inobus尾部填充

#define SPARA_RWFLAG_LEN        (1)                                                       //A40I通讯协议读写标志长度
#define SPARA_DYNBUF_LEN        (2)                                                       //A40I通讯协议数据区动态长度
#define SPARA_OFFSET_LEN        (1)                                                       //A40I通讯协议偏移值长度
#define SPARA_A40I_PROTO_HEADER (SPARA_RWFLAG_LEN + SPARA_DYNBUF_LEN + SPARA_OFFSET_LEN)  //A40I协议头长度

#define SPARA_FILLER      (0XFF)  //MCU协议帧头填充内容
#define SPARA_FILLER_LEN  (1)     //MCU协议帧头填充长度
#define SPARA_RES_ADDR    (4)     //MCU协议返回标志地址
#define SPARA_NEEDLECHECK (5)     //MCU协议穿刺校验位偏移
#define SPARA_HEADER      (7)     //MCU帧头长度
#define SPARA_DATA_LEN    (243)   //MCU协议数据区长度
#define SPARA_CRC_LEN     (2)                                              //CRC校验位尾部长度
#define SPARA_TOTAL_LEN (SPARA_HEADER + SPARA_DATA_LEN + SPARA_CRC_LEN)    //MCU协议数据总长

#define SPARA_WRITREQ   (0x01)  // 写相关
#define SPARA_WRITRES   (0x02)
#define SPARA_WRITERR   (0x03)
#define SPARA_READREQ   (0x04)  // 读相关
#define SPARA_READRES   (0x05)
#define SPARA_READERR   (0x06)
#define SPARA_REREADREQ (0x07)  // 回读相关
#define SPARA_REREADRES (0x08)
#define SPARA_REREADERR (0x09)

#define SAFE_PARA_MAP (iController->GetSafeParaSettingMgr()->GetSafeParaMap())

// MCU内存数据, 此处与ParaData数据地图相同, 数据操作颗粒度精确到这个枚举
enum SafeParaEnum : int16s
{
    EEP_CRC = 0,                 // CRC
    EEP_PASSWORD = 1,            // 密码
    EEP_STOPCONF = 2,            // 停机配置, stopConf STOPCONF
    EEP_LOW_SPEED = 3,           // 安全低速, safeLowSpeed SAFELOWSPEED
    EEP_DI = 4,                  // 安全IO DI, safeIO.DI S_IO
    EEP_DO = 5,                  // 安全IO DO, safeIO.DO S_IO
    EEP_APOSWAY = 6,             // 轴位置生效方式, axisParas.u8APosWay int8u
    EEP_AVELWAY = 7,             // 轴速度生效方式, axisParas.u8AVelWay int8u
    EEP_APOS_0 = 8,              // 轴位置0, axisParas.APosGroup S_APOS
    EEP_APOS_1 = 9,              // 轴位置1
    EEP_APOS_2 = 10,             // 轴位置2
    EEP_APOS_3 = 11,             // 轴位置3
    EEP_APOS_4 = 12,             // 轴位置4
    EEP_APOS_5 = 13,             // 轴位置5
    EEP_APOS_6 = 14,             // 轴位置6
    EEP_APOS_7 = 15,             // 轴位置7
    EEP_AVEL_0 = 16,             // 轴速度0, axisParas.AVelGroup S_AVEL
    EEP_CVELWAY = 24,            // 笛卡尔速度生效方式, carteParas.u8CVelWay int8u
    EEP_CPOSWAY = 25,            // 笛卡尔位置生效方式, carteParas.u8CPosWay int8u
    EEP_CVEL_0 = 26,             // 笛卡尔速度0, carteParas.CVelGroup S_CVEL
    EEP_IZONE_STATUS_0 = 34,     // 干涉区状态0, carteParas.CPosGroup INTERFER_ZONE_STATUS
    EEP_ITOOL_STATUS_0 = 50,     // 末端监测对象状态状态0, INTERFER_ZONE_STATUS
    EEP_IZONE_PARA_0 = 66,       // 干涉区配置参数0, INTERFER_ZONE
    EEP_IZONE_WOBJ_0 = 82,       // 干涉区工件参数0, INTERFER_ZONE_WOBJPARAM
    EEP_ITOOL_PARA_0 = 98,       // 末端监测对象配置参数0, INTERFER_TOOL
    EEP_ITOOL_MTCPTOOL_0 = 114,  // 末端监测对象, MTCP工具参数0, INTERFER_ZONE_MTCPTOOLPARAM
    EEP_ITOOL_MTCPTOOL_F = 129,  // 末端监测对象, MTCP工具参数15
    EEP_SAFEIO_DITRIGGER = 130,  // 安全IO DI阈值, u32DITrigerValue
    EEP_TOOLPARA_0 = 131,        // 工具参数, toolWobjMgr.ToolDataGroup ToolData
    EEP_TOOLPARA_15 = 146,
    EEP_WOBJPARA_0 = 147,        // 工件参数, toolWobjMgr.WobjDataGroup WobjData
    EEP_WOBJPARA_15 = 162,
    EEP_SAFETOOLMODE = 163,  // 安全工具设置, safeToolMode SafeToolSetting, 同步保存到EEPROM
#ifdef COBOT
    EEP_CTCPFORCE = 164,         // 笛卡尔力
    EEP_STATICWAY = 165,         // 安全静止生效方式
    EEP_STATIC_0 = 166,          // 安全静止0
    EEP_STATIC_1 = 167,          // 安全静止1
    EEP_STATIC_2 = 168,          // 安全静止2
    EEP_STATIC_3 = 169,          // 安全静止3
    EEP_STATIC_4 = 170,          // 安全静止4
    EEP_STATIC_5 = 171,          // 安全静止5
    EEP_STATIC_6 = 172,          // 安全静止6
    EEP_STATIC_7 = 173,          // 安全静止7
    EEP_HOMING = 174,            // 安全原点
    EEP_BODYMOMENTUM = 175,      // 整机动量
    EEP_BODYPOWER = 176,         // 整机功率
    EEP_TCPDIRECTIONWAY = 177,   // TCP方向生效方式
    EEP_TCPDIRECTION_0 = 178,    // TCP方向0
    EEP_TCPDIRECTION_1 = 179,    // TCP方向1
    EEP_TCPDIRECTION_2 = 180,    // TCP方向2
    EEP_TCPDIRECTION_3 = 181,    // TCP方向3
    EEP_TCPDIRECTION_4 = 182,    // TCP方向4
    EEP_TCPDIRECTION_5 = 183,    // TCP方向5
    EEP_TCPDIRECTION_6 = 184,    // TCP方向6
    EEP_TCPDIRECTION_7 = 185,    // TCP方向7
    EEP_STOPDISTANCE = 186,      // 停机距离
    EEP_STOPTIME = 187,          // 停机时间
    EEP_STOP_TOLERANCE = 188,    // 停机抖动容差
    EEP_REDUCEMODE_APOS_0 = 189, // 缩减模式轴位置
    EEP_REDUCEMODE_APOS_1 = 190, // 缩减模式轴位置
    EEP_REDUCEMODE_APOS_2 = 191, // 缩减模式轴位置
    EEP_REDUCEMODE_APOS_3 = 192, // 缩减模式轴位置
    EEP_REDUCEMODE_APOS_4 = 193, // 缩减模式轴位置
    EEP_REDUCEMODE_APOS_5 = 194, // 缩减模式轴位置
    EEP_REDUCEMODE_APOS_6 = 195, // 缩减模式轴位置
    EEP_REDUCEMODE_APOS_7 = 196, // 缩减模式轴位置
    EEP_REDUCEMODE_AVEL_0 = 197, // 缩减模式轴速度
    EEP_REDUCEMODE_AVEL_1 = 198, // 缩减模式轴速度
    EEP_REDUCEMODE_AVEL_2 = 199, // 缩减模式轴速度
    EEP_REDUCEMODE_AVEL_3 = 200, // 缩减模式轴速度
    EEP_REDUCEMODE_AVEL_4 = 201, // 缩减模式轴速度
    EEP_REDUCEMODE_AVEL_5 = 202, // 缩减模式轴速度
    EEP_REDUCEMODE_AVEL_6 = 203, // 缩减模式轴速度
    EEP_REDUCEMODE_AVEL_7 = 204, // 缩减模式轴速度
    EEP_REDUCEMODE_CVEL = 205,   // 缩减模式笛卡尔速度
    EEP_ELBOW_SWITCH = 206,      // 肘部监控开关
    EEP_POSITIONDISMATCHWAY = 207,   // 位置不匹配生效方式
    EEP_POSITIONDISMATCH_0 = 208,    // 位置不匹配0
    EEP_POSITIONDISMATCH_1 = 209,    // 位置不匹配1
    EEP_POSITIONDISMATCH_2 = 210,    // 位置不匹配2
    EEP_POSITIONDISMATCH_3 = 211,    // 位置不匹配3
    EEP_POSITIONDISMATCH_4 = 212,    // 位置不匹配4
    EEP_POSITIONDISMATCH_5 = 213,    // 位置不匹配5
    EEP_POSITIONDISMATCH_6 = 214,    // 位置不匹配6
    EEP_POSITIONDISMATCH_7 = 215,    // 位置不匹配7
    EEP_DRAGTEACH = 216,             // 拖动示教
    EEP_CHECKYES = 217,          // 数据同步到EEPROM
    RAM_TCP_DIRECT_GET_VECTOR_0 = 218,    // 获取组末端向量0
    RAM_TCP_DIRECT_GET_VECTOR_1 = 219,    // 获取组末端向量1
    RAM_TCP_DIRECT_GET_VECTOR_2 = 220,    // 获取组末端向量2
    RAM_TCP_DIRECT_GET_VECTOR_3 = 221,    // 获取组末端向量3
    RAM_TCP_DIRECT_GET_VECTOR_4 = 222,    // 获取组末端向量4
    RAM_TCP_DIRECT_GET_VECTOR_5 = 223,    // 获取组末端向量5
    RAM_TCP_DIRECT_GET_VECTOR_6 = 224,    // 获取组末端向量6
    RAM_TCP_DIRECT_GET_VECTOR_7 = 225,    // 获取组末端向量7
    RAM_ACTIVE_SAFETY_MONITOR   = 226,    // 激活安全监控
    RAM_CHECKYES = 227,          // 数据同步RAM
    EEP_SYSTEM_READY = 228,      // EEP握手成功
    RAM_RESEST = 229,
    RAM_RESEST_STATUS = 230,
    SPARA_MEMBER_NUM = 231,      // 数据地图长度(内存变量个数)
#else
    EEP_CHECKYES = 164,      // 数据同步到EEPROM
    RAM_CHECKYES = 165,      // 数据同步RAM
    EEP_SYSTEM_READY = 166,  // EEP握手成功
    RAM_RESEST = 167,
    RAM_RESEST_STATUS = 168,
    SPARA_MEMBER_NUM = 169,  //数据地图长度(内存变量个数)
#endif   
};

enum SafeParaNumEnum
{
    EEP_DO_NUM = 5,
    EEP_DI_NUM = 8,
    EEP_AXIS_ITEMSNUM = 8,
    EEP_IZONE_STATUS_NUM = 16,
};

enum SafeParaStatus : int8u
{
    SPS_INITIAL = 0,  // 初始化
    SPS_READED = 1,   // 已读取
    SPS_EDITED = 2,   // 编辑未保存
    SPS_SYNC = 3,     // 已同步
    SPS_WRITED = 4,   // 已下发
};

#ifdef COBOT
enum SafeInterferenceZoneSendStatus
{
    SAFETYINTERZONESENDSTATUS_SENDING,      // 下发中
    SAFETYINTERZONESENDSTATUS_SENDSUCCESS,  // 下发成功
    SAFETYINTERZONESENDSTATUS_SENDFAILED    // 下发失败
};
#endif

enum SafeParaRetVal : int32s
{
    SPR_SUC = 0,
    SPR_INDEX = 1,           // 地图索引错误
    SPR_POINTER = 2,         // 变量指针错误
    SPR_STATUS = 3,          // 错误的数据状态
    SPR_ERRFUNC = 4,         // 查询功能得到 否的结果
    SPR_INITIAL = 5,         // 初始化一个错误的返回值
    SPR_NONEMOVE = 6,        // 没有执行过
    SPR_SYSREADY = 7,        // systemReady标志位为0
    SPR_LOCALCHECK = 9,      // 本地校验失败
    SPR_IOOCCUPIED = 10,     // IO占用错误
    SPR_CRCERR = 108,        // 工业安全CRC错误
    SPR_READBACK = 109,      // 回读错误
    SPR_RETBIT = 110,        // 回应位置错误
    SPR_MCURET_FAIL = 30583  // 从MCU获取数据失败, 0x7777
};

enum SafeHardAddrType
{
    SHAT_NEUTRAL = 0,
    SHAT_EEPROM = 1,
    SHAT_RAM = 2,
};

struct SafeParaMapEle
{
    int8u *mem;          // 上位机内存
    int16u addr;         // 安全MCU地址
    int16u length;       // 数据长度
    int16s index;        // 索引
    int16u commui;       // 通讯码
    int8u status;        // 数据状态
    int8u MCUAddrType;   // 安全MCU地址类型

    SafeParaMapEle(
    int8u *paramem = NULL,
    int16u paraaddr = 0x0000,
    int16u paralength = 0x0000,
    int16s paraindex = 0,
    int16u paracommui = 0x0000,
    int8u parastatus = 0,
    int8u paraMCUAddrType = 0)
    {
        mem = paramem;
        addr = paraaddr;
        length = paralength;
        index = paraindex;
        commui = paracommui;
        status = parastatus;
        MCUAddrType = paraMCUAddrType;
    }
};

namespace InoRobBusiness
{
enum SafeIOCfgItem
{
    SIOC_NONE = 0,

    SIOC_DI_STARTENUM = 1,
    SIOC_DI_EMERSTOP = 1,                       // 急停触发
    SIOC_DI_SAFEDOOR = 2,                       // 安全门
    SIOC_DI_APOS = 3,                           // 轴位置监控触发
    SIOC_DI_AVEL = 4,                           // 轴速度监控触发
    SIOC_DI_CPOS = 5,                           // 笛卡尔位置监控触发
    SIOC_DI_CVEL = 6,                           // 笛卡尔速度监控触发
    SIOC_DI_SAFELOWSPEED = 7,                   // 安全低速监控触发
    SIOC_DI_TCPORECP = 8,                       // 工具模式
    SIOC_DI_BIT0 = 9,                           // Bit0
    SIOC_DI_BIT1 = 10,                          // Bit1
    SIOC_DI_BIT2 = 11,                          // Bit2
    SIOC_DI_BIT3 = 12,                          // Bit3
#ifdef COBOT
    SIOC_DI_SPEEDREDUCING_LEVEL1 = 13,          // 缩减模式速度缩减等级1
    SIOC_DI_SPEEDREDUCING_LEVEL2 = 14,          // 缩减模式速度缩减等级2
    SIOC_DI_PROTECTION_STOP_RESET = 15,         // 保护性停止复位
    SIOC_DI_TCP_FORCE = 16,                     // TCP力监控
    SIOC_DI_TCP_DIRECTION = 17,                 // TCP力方向监控
    SIOC_DI_JOINT_TORQUE = 28,                  // 关节转矩监控
    SIOC_DI_JOINT_POWER = 29,                   // 关节功率监控
    SIOC_DI_BODY_POWER = 20,                    // 整机功率监控
    SIOC_DI_BODY_MOMENTUM = 21,                 // 整机动量监控
    SIOC_DI_STATIC = 22,                        // 安全静止监控
    SIOC_DI_POSITION_NOT_MATCH = 23,            // 位置不匹配监控
    SIOC_DI_SAFETY_ORIGIN = 24,                 // 安全原点到位
    SIOC_DI_LASTENUM = 25,
# else
    SIOC_DI_LASTENUM = 12,
#endif

    SIOC_DO_STARTENUM = 201,
    SIOC_DO_EMERSTOP = 201,     //急停状态
    SIOC_DO_STATUS_RUN = 202,   //运行状态
    SIOC_DO_STATUS_STOP = 203,  //停止状态
    SIOC_DO_APOS = 204,         //轴位置监控状态
    SIOC_DO_AVEL = 205,         //轴速度监控状态
    SIOC_DO_CPOS = 206,         //笛卡尔位置监控状态
    SIOC_DO_CVEL = 207,         //笛卡尔速度监控状态
    SIOC_DO_SAFELOWSPEED = 208, //安全低速监控状态
    SIOC_DO_SAFESTATUS = 209,   //安全状态
#ifdef COBOT
    SIOC_DO_SPEEDREDUCING_LEVEL1 = 210,     // 缩减模式速度缩减等级1
    SIOC_DO_SPEEDREDUCING_LEVEL2 = 211,     // 缩减模式速度缩减等级2
    SIOC_DO_SYSTEM_EMERGECY_STOP = 212,     // 系统急停状态  
    SIOC_DO_SYSTEM_PROTECTION_STOP = 213,   // 系统保护性停止状态
    SIOC_DO_STOP_NOT = 214,                 // 非停止状态
    SIOC_DO_REDUCING_MODE_NOT = 215,        // 非缩减模式状态
    SIOC_DO_REDUCING_MODE = 216,            // 缩减模式状态
    SIOC_DO_SAFETY_ORIGIN = 217,            // 安全原点到位状态
    SIOC_DO_TCP_FORCE = 218,                // TCP力监控状态
    SIOC_DO_TCP_DIRECTION = 219,            // TCP方向监控状态
    SIOC_DO_JOINT_TORQUE = 220,             // 关节转矩监控状态
    SIOC_DO_JOINT_POWER = 221,              // 关节功率监控状态
    SIOC_DO_BODY_POWER = 222,               // 整机功率监控状态
    SIOC_DO_BODY_MOMENTUM = 223,            // 整机动量监控状态
    SIOC_DO_STATIC = 224,                   // 安全静止监控状态
    SIOC_DO_POSITION_NOT_MATCH = 225,       // 位置不匹配监控状态
    SIOC_DO_DRAGTEACH_SPEED = 226,          // 拖动示教速度监控状态
    SIOC_DO_LASTENUM = 227,
# else
    SIOC_DO_LASTENUM = 209,
#endif
};

enum SafeActivateCombbox
{
    UNACT = 0,
    ACTIVATED = 1,
};

enum SafeStopCatCombbox
{
    STOPCAT_0 = 0,
    STOPCAT_1 = 1,
};

enum SafeTriggerCombbox
{
    NO_TRIGGER = 0,
    FOREVER = 1,
    IO_TRIGGER = 2,
};

enum SafeToolModeCombbox
{
    FOLLOW_SYSTEM = 0,
    REGULAR = 1,
    MANUL_SWITCH = 2
};

class INOROBBUSINESS_CLASS ISafeParaSettingMgr : public QObject
{
    Q_OBJECT

public:
    virtual ~ISafeParaSettingMgr() {}
    /*!
     * \brief 初始化
     */
    virtual void init() = 0;
#pragma region 查询SafeMCU
    /// <summary>
    /// 询问上位机内存中, 上次SafeMCU查询结果
    /// </summary>
    /// <returns>0 - 上次查询结果为 SafeMCU存在且正常</returns>
    virtual int QuerySafeParaCabinet() = 0;
    /// <summary>
    /// 查询工业安全硬件是否存在, 成功返回0
    /// </summary>
    virtual int QuerySafeParaHardWareExist() = 0;
    /// <summary>
    /// 查询工业安全芯片握手成功状态, 成功返回0
    /// </summary>
    virtual int QuerySafeParaHardWareSynchro() = 0;
    /// <summary>
    /// 查询SafeMCU状态
    /// </summary>
    /// <param name="printFlag">查询过程信息打印</param>
    /// <returns>0 - 查询过程成功无异常</returns>
    virtual int QuerySafeParaCabinetProcess(bool printFlag) = 0;
#pragma endregion

#pragma region 功能安全密码
    /// <summary>
    /// 传入一个密码并向SafeMCU校验该密码
    /// </summary>
    /// <param name="password"></param>
    /// <returns>0 - 密码校验通过</returns>
    virtual int CheckSafeParaPassword(const unsigned int password) = 0;
    /// <summary>
    /// 返回上次密码校验的结果
    /// </summary>
    /// <returns>0 - 上次密码校验通过</returns>
    virtual int CheckSafeParaPassword() = 0;
#pragma endregion

#pragma region 读取功能安全参数
    /// <summary>
    /// 从SafeMCU读取数据 至 模型层
    /// </summary>
    /// <param name="key"> 该数据在SafeParaEnum中枚举值 </param>
    /// <param name="offset"> 该数据相对于首个同类数据的偏移 </param>
    /// <param name="num"> 基于key + offset位置, 获取num个数据 </param>
    /// <returns>0 - 读取过程成功</returns>
    virtual int Read(int key, int offset, int num) = 0;
    /// <summary>
    /// 获取模型层数据 至 界面
    /// </summary>
    /// <param name="key"> 该数据在SafeParaEnum中枚举值 </param>
    /// <param name="offset"> 该数据相对于首个同类数据的偏移 </param>
    /// <param name="length"> 该数据长度(byte) </param>
    /// <param name="buf"> 将该数据的值放入buf </param>
    /// <param name="forceFlag"> 若该数据部位SYNC状态, 则从SafeMCU获取, 该逻辑耗时较长 </param>
    /// <returns>0 - 获取过程成功</returns>
    virtual int GetSafeParaCommon(int key, int offset, int length, unsigned char *buf, bool forceFlag = false) = 0;
#pragma endregion

#pragma region 保存功能安全参数
    /// <summary>
    /// 将界面数据 下发 模型层, 并将数据status设置为 SPS_EDITED
    /// </summary>
    /// <param name="key"> 该数据在SafeParaEnum中枚举值 </param>
    /// <param name="offset"> 该数据相对于首个同类数据的偏移 </param>
    /// <param name="length"> 该数据长度(byte) </param>
    /// <param name="buf"> 从buf中获取length长度内存填入该数据 </param>
    /// <param name="forceFlag"></param>
    /// <returns></returns>
    virtual int SetSafeParaCommon(int key, int offset, int length, unsigned char *buf, bool forceFlag = false) = 0;
    /// <summary>
    /// 保存status为SPS_EDITED的变量 至 SafeMCU, A40I
    /// </summary>
    /// <returns>0 - 保存过程成功</returns>
    virtual int Write(int *range, int num) = 0;
    virtual int Write(int key, int offset, int num) = 0;
#pragma endregion

#pragma region 数据地图
    /// <summary>
    /// 数据地图构造
    /// </summary>
    /// <returns></returns>
    virtual int SafeParaMapBuild() = 0;
    /// <summary>
    /// 获取数据地图
    /// </summary>
    /// <returns></returns>
    virtual vector<SafeParaMapEle> &GetSafeParaMap() = 0;
#pragma endregion

#pragma region 功能安全副本 导入/导出
    /// <summary>
    /// 导出至路径
    /// </summary>
    /// <param name="exportRoute"></param>
    /// <returns>0 - 导出成功</returns>
    virtual int ExportFunctionSafeParaFile(const string exportRoute) = 0;
    /// <summary>
    /// 从路径导入
    /// </summary>
    /// <param name="importRoute"></param>
    /// <returns>0 - 导入成功</returns>
    virtual int ImportFunctionSafeParaFile(const string importRoute) = 0;
#pragma endregion

#pragma region 功能安全初始化
    /// <summary>
    ///  初始化所有功能安全参数, 并开启一线程轮询结果
    /// </summary>
    /// <param name="flag"> 已废弃不用的参数 </param>
    /// <returns>0 - 启动初始化过程成功</returns>
    virtual int SafeParaReset(unsigned char flag) = 0;
#pragma endregion

#pragma region 其他
    /// <summary>
    /// 检查数据地图中的某状态
    /// </summary>
    /// <param name="status"></param>
    /// <returns></returns>
    virtual int CheckAStatus(int8u status = SPS_EDITED) = 0;
    virtual int CheckAStatus(int key, int offset, int num, int8u status = SPS_EDITED) = 0;
    /// <summary>
    /// 保存安全工具模式前, 检查IO占用情况
    /// </summary>
    /// <param name="DO">传入配置项</param>
    /// <returns>0 - 无占用</returns>
    virtual int SafeToolModeOccupied(const short DO[DO_NUM]) = 0;
    /// <summary>
    /// 拼接 功能安全数据读写返回信息, 一适配多国语言;
    /// </summary>
    /// <param name="caption">界面名称</param>
    /// <param name="ret">返回值</param>
    /// <param name="readFlag">0 - 读过程; 1 - 写过程</param>
    /// <returns> 界面打印词条 </returns>
    virtual string GetErrorText(string caption, int ret, int readFlag) = 0;
    virtual int PrintErrorText(string caption, int ret, int readFlag) = 0;
    /// <summary>
    /// 查询功能安全版本信息
    /// </summary>
    /// <param name="system">系统软件版本</param>
    /// <param name="moni">监控软件版本</param>
    /// <param name="commu"><通讯软件版本/param>
    /// <returns> 0 - 查询成功</returns>
    virtual int GetSafeHardVer(string &system, string &moni, string &commu) = 0;
    /// <summary>
    /// 开启轮训线程, 询问安全IO电平状态
    /// </summary>
    /// <param name="switchFlag">false - 停止轮询; true - 开启轮询</param>
    /// <returns>0 - 开启/关闭 动作成功</returns>
    virtual int QuerySafeIORealTime(bool switchFlag) = 0;
#ifdef COBOT
    /// <summary>
    /// 下发干涉区参数发送状态
    /// </summary>
    /// <param name="status"></param>
    /// <returns>0 - 状态设置成功</returns>
    virtual int SetInterZoneSendStatus(int8u status = SAFETYINTERZONESENDSTATUS_SENDING) = 0;

    /// <summary>
    /// 写入缩减模式速度缩减数值到A40i
    /// </summary>
    /// <param name="status"></param>
    /// <returns>0 - 写入成功</returns>
    virtual int WriteSpeedReducing(const S_SPEEDREDUCINGCONF &conf) = 0;

    /// <summary>
    /// 从A40i读取缩减模式速度缩减数值
    /// </summary>
    /// <param name="status"></param>
    /// <returns>0 - 读取成功</returns>
    virtual int ReadSpeedReducing(S_SPEEDREDUCINGCONF &conf) = 0;
#endif // COBOT

#pragma endregion

Q_SIGNALS:
    /// <summary>
    /// SafeMCU状态已更改, 通知界面变化显示策略
    /// </summary>
    void safeParaCabinetStatusUpdate(bool status);
    /// <summary>
    /// 返回初始化过程结果, 0 - 成功
    /// </summary>
    void safeResetStatusUpdate(int status);
    /// <summary>
    /// 返回实时的功能安全IO电平状态
    /// </summary>
    void safeIOStatusUpdate(S_SAFEIO status);

public:
    STOPCONF _stopConf;                      /// > 停机配置, EEPROM
    SAFELOWSPEED _safeLowSpeed;              /// > 安全低速, EEPROM
    SAFEIO _safeIO;                          /// > 安全IO, EEPROM
    AXIS _axisParas;                         /// > 轴位置 轴速度监控, EEPROM
    std::shared_ptr<CARTESIAN> _pCarteParas;/// > 笛卡尔位置 笛卡尔速度 监控, EEPROM
    ToolWobjMgr _toolWobjMgr;                /// > 工具工件参数, RAM
    SafeToolSetting _safeToolMode;           /// > 安全工具模式, RAM
    int32u _u32DITrigerValue;                /// > DI触发阈值, EEPROM
#ifdef COBOT
    S_SPEEDREDUCINGCONF _speedReducingConf;  /// > 缩减模式
    S_A_JOINT_TORQUE _jointtorqueParas;      /// > 关节转矩
    S_A_JOINT_POWER _jointpowerParas;        /// > 关节功率
    S_A_TCP_FORCE _tcpforceParas;            /// > TCP力
    S_A_SAFE_BASE_POINT_STATUS _homingParas; /// > 安全原点
    S_A_SAFE_BODY_STATIC _staticParas;       /// > 安全静止监控
    S_A_BODY_MOMENTUM _bodyMomentumParas;    /// > 整机动量
    S_A_BODY_POWER _bodyPowerParas;          /// > 整机功率
    S_A_STOP_DISTANCE _stopDistanceParas;    /// > 停机距离
    S_A_STOP_TIME _stopTimeParas;            /// > 停机时间
    S_A_TCP_DIRECTION _tcpDirectionParas;    /// > TCP方向
    S_A_REDUCE_MODE _reducemodeParas;        /// > 缩减模式参数
    INTERFER_TOOL_EXTRAL _elbowSwitchParas;  /// > 肘部检测开关参数
    S_A_STOP_TOLERANCE _stopToloranceParas;  /// > 容差阈值
    S_A_POS_MATCH _postionDismatchParas;     /// > 位置不匹配
    S_A_DRAG_TEACH_INTERFACE _tragteach;     /// > 拖动示教
    int8u _activeSafetyMonitor;              /// > 激活安全监控
#endif // COBOT

protected:
    bool _safeParaCabinet;
    bool _alreadyCheckPassword;
    unsigned int _password;

    int8u _checkYesFlag;
    int8u _checkYesFlagRAM;
    int8u _systemReadyFlag;
};

}  // namespace InoRobBusiness
