#pragma once
#include "DataSrvGlobal.h"
#include "FrameDef.h"
#include "dllspec.h"

struct GSYSTEMTIME
{
    WORD wYear;
    WORD wMonth;
    WORD wDayOfWeek;
    WORD wDay;
    WORD wHour;
    WORD wMinute;
    WORD wSecond;
    WORD wMilliseconds;
};

class DATASRV_CLASS CProtocol
{
public:
    CProtocol(void);
    virtual ~CProtocol(void);

public:
    // 通过文件长度，计算出总帧数
    void ParseFileDataLen(int nFileLen, int &nTotalFrame, int &nFirstLen, int &nLastLen);

    // 通过总长度，计算出帧数
    void ParseDataLen(int nFileLen, int &nTotalFrame, int &nFirstLen, int &nLastLen);

    // 获取示教指令
    int16u GetTeachCmd(int AxisId, ROTATE_DIR TurnDir);

    // ECat本版枚举类型<--->字节
    void Int8uToECatVer(int8u uVer, EtherCATVersion &eECatVer);

    void ECatVerToInt8u(EtherCATVersion eECatVer, int8u &uVer);

    // 回零参数<--->字节流
    void Int8uToAxisHmParam(int8u *pBuf, AXIS_HOMINGPARAM &AxisHmParam);

    void AxisHmParamToInt8u(AXIS_HOMINGPARAM &AxisHmParam, int8u *pBuf);

    // DA参数<--->字节流
    void Int8uToDAParam(int8u *pBuf, DA_PARAM *pDAParam);

    void DAParamToInt8u(int nIndex, DA_PARAM *pDAParam, int8u *pBuf);

    // AD参数<--->字节流
    void Int8uToADParam(int8u *pBuf, AD_PARAM *pADParam);

    void ADParamToInt8u(int nIndex, AD_PARAM *pADParam, int8u *pBuf);

    // AT参数<--->字节流
    void Int8uToATParam(int8u *pBuf, AT_PARAM *pATParam);

    void ATParamToInt8u(int nIndex, AT_PARAM *pATParam, int8u *pBuf);

    // ECat本版枚举类型<--->字节
    void Int8uToIRVer(int8u uVer, IR_VER &eECatVer);

    void IRVerToInt8u(IR_VER eECatVer, int8u &uVer);

    // DAC参数<--->字节流
    void Int8uToDACParam(int8u *pBuf, DAC_PARAM *pParam);

    void DACParamToInt8u(DAC_PARAM *pParam, int8u *pBuf);

    // ADC参数<--->字节流
    void Int8uToADCParam(int8u *pBuf, ADC_PARAM *pParam);

    void ADCParamToInt8u(ADC_PARAM *pParam, int8u *pBuf);

    // ENCODER参数<--->字节流
    void Int8uToENCParam(int8u *pBuf, ENC_PARAM *pParam);

    void ENCParamToInt8u(ENC_PARAM *pParam, int8u *pBuf);

    // GSYSTEMTIME<--->字节流
    void Int8uToSysTime(int8u *pBuf, GSYSTEMTIME &sysTime);

    void SysTimeToInt8u(const GSYSTEMTIME &sysTime, int8u *pBuf);

    // GSYSTEMTIME<--->tm
    void SysTimeToTm(const GSYSTEMTIME &sysTime, tm &tmTime);

    /************************************************************************/
    /*组帧*/
    /************************************************************************/
    // 实时指令
    int PackRealCmd(int8u *pBuf, REALTIME_CMD RealCmd);

    // 非实时指令
    int PackUnRealCmd(int8u *pBuf, const UNREALTIME_CMD &UnRealCmd);

    // 附加数据
    int PackExtraData(int8u *pBuf, const EXTRA_DATA &ExtraData);

    /************************************************************************/
    /*解帧*/
    /************************************************************************/
    // 实时指令
    int ParseRealCmd(int8u *pBuf, RESP_INFO &RespInfo);  // 返回设备错误信息

    // 非实时指令
    int ParseUnRealCmd(int8u *pBuf, UNREALTIME_CMD &UnRealCmd, RESP_INFO &RespInfo);

    // 附加数据
    int ParseExtraData(int8u *pBuf, EXTRA_DATA &ExtraData, RESP_INFO &RespInfo, IO_TYPE nIoType);

    // 检查是否为上行帧的帧头，参数为int8u[2]
    bool CheckUpHeader(int8u *pBuf);

    // 检查上行的帧头及ID，pBuf为int8u[11]
    bool CheckUpHeaderAndId(int8u *pBuf, int16u id);
};
