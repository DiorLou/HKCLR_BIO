#pragma once
#include "DataTypeDef.h"

/*************************************************************
/以下部分为通信协议内部数据结构定义，数据服务
/模块调用者无需关心
***************************************************************/
// 下行帧:帧头
#define SEND_HEAD_0 0xAF
#define SEND_HEAD_1 0x80

// 上行帧:帧头
#define RECV_HEAD_0 0xAF
#define RECV_HEAD_1 0x90

// 发送帧长度
#define REAL_CMD_LEN   (3 + 10)
#define UNREAL_CMD_LEN (3 + 133)
#define EXTRA_DATA_LEN (3 + 878)

// 响应帧长
#define REAL_RESP_LEN   9          // 实时响应帧长(总是有)
#define UNREAL_RESP_LEN (9 + 130)  // 非实时指令帧长

// 指令内容长
#define CMD_CONTENT_LEN       128  // 指令内容长度
#define DATA_CONTENT_LEN      864  // 数据内容长度
#define BIG_FILE_AVA_DATA_LEN 863  // 大文件中去掉预留之后的可用数据长度，首byte放读写标志

// 文件名称、路径最大长度
#define MAX_FILE_DIR_LEN 100

// 心跳帧间隔(ms)
#define HEARTBEAT_INTVL 1500

// 帧响应超时(ms)
#define FRAME_TIMEOUT   1000  // 2000//实时指令、非实时指令响应超时
#define FRAME_TIMEOUT_L 1000  // 2000//大文件数据帧超时

// 通信类型
#define REALCMD_COMM   0x01
#define UNREALCMD_COMM 0x02
#define EXTRADATA_COMM 0x04

// 非实时指令:参数读写类型
typedef enum
{
    READ_DATA = 1,
    WRITE_DATA,
} IO_TYPE;

// 通信帧:下行帧或上行帧(打印类型)
typedef enum
{
    SEND_DATA = 1,
    RECV_DATA,
} IO_DATA_TYPE;

// #pragma pack(4)
// 实时指令
typedef struct tagRealTimeCmd
{
    tagRealTimeCmd()
    {
        nId = 0;
        nState = 0;
    }

    int16u nId;     // 指令ID
    int64u nState;  // 指令状态

} REALTIME_CMD;

// 非实时指令
typedef struct tagUnRealTimeCmd
{
    tagUnRealTimeCmd()
    {
        nId = 0;
        nState = 1;
        nAssitCmd = 0;
        memset(&nContent[0], 0, CMD_CONTENT_LEN);
    }

    int16u nId;                       // 非实时指令
    int8u nState;                     // 指令状态
    int16u nAssitCmd;                 // 非时协指令
    int8u nContent[CMD_CONTENT_LEN];  // 指令内容
} UNREALTIME_CMD;

// 附加数据
typedef struct tagExtraData
{
    tagExtraData()
    {
        nType = 0;
        nTotalFrame = 0;
        nCurFrameId = 1;
        nDataLen = 0;
        memset(&nContent[0], 0, DATA_CONTENT_LEN);
    }

    int16u nType;                      // 数据类型
    int32u nTotalFrame;                // 总帧数
    int32u nCurFrameId;                // 当前帧号
    int32u nDataLen;                   // 当前数据长度
    int8u nContent[DATA_CONTENT_LEN];  // 数据内容
} EXTRA_DATA;

// 下行数据帧
typedef struct tagCmdFrame
{
    // 通讯类型
    int8u nCommType;

    // 实时指令
    REALTIME_CMD RealCmd;

    // 非实时指令
    UNREALTIME_CMD UnRealCmd;

    // 附加数据
    EXTRA_DATA ExtraData;

} CMD_FRAME;

// 响应帧信息
typedef struct tagRespInfo
{
    tagRespInfo()
    {
        ErroCode = 0;
        FrameNumb = 0;
    }

    int16u ErroCode;   // 错误码
    int32u FrameNumb;  // 帧号
} RESP_INFO;

// 通信错误信息
typedef struct tagCommErro
{
    tagCommErro()
    {
        nErroCount = 0;
        dwErroTime = 0;
    }

    int nErroCount;    // 错误次数
    DWORD dwErroTime;  // 发生错误的时刻
} COMM_ERRO;

// #pragma pack()