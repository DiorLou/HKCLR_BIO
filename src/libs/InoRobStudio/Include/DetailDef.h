#pragma once
#include "DataTypeDef.h"

/***************************
/EMC 测试
****************************/
// EMC测试模块使能配置
struct EMC_MOD
{
    int8u nModNumb = 0;
    int8u nPingEnable = 0;  // 1:使能, 0:不使能
    int8u nTeachBoxEnable = 0;
    int8u nCanEnable = 0;
    int8u nUsbEnable = 0;
    int8u nSdEnable = 0;
    int8u nDIDOEnable = 0;
    int8u nRS485Enable = 0;
    int8u nRS422 = 0;
};

// Ping参数
struct EMC_PING
{
    int32u uErroNumb = 0;
    int32u uDataLen = 0;
    char szIpAddr[16] = { 0 };
    int32u uSendNumb = 0;
    int32u uRecvNumb = 0;
    double dbLossRate = 0;
    double dbRttAve = 0;  // RTT平均值
};

// TeachBox参数
typedef struct tagEmcTeachBox
{
    tagEmcTeachBox()
    {
        uErroNumb = 0;
    }

    int32u uErroNumb;
} EMC_TEACHBOX;

// CAN参数
typedef struct tagEmcCan
{
    tagEmcCan()
    {
        uErroNumb = 0;
        uSendNumb = 0;
        uRecvNumb = 0;
    }

    int32u uErroNumb;
    int32u uSendNumb;
    int32u uRecvNumb;
} EMC_CAN;

// U盘参数
typedef struct tagEmcUsb
{
    tagEmcUsb()
    {
        uErroNumb = 0;
    }

    int32u uErroNumb;
} EMC_USB;

// 存储卡参数
typedef struct tagEmcSd
{
    tagEmcSd()
    {
        uErroNumb = 0;
    }

    int32u uErroNumb;
} EMC_SD;

// DI/DO参数
typedef struct tagEmcDIDO
{
    tagEmcDIDO()
    {
        uErroNumb = 0;
        u64DOValue = 0;
        u64DIValue = 0;
    }

    int32u uErroNumb;
    int64u u64DOValue;
    int64u u64DIValue;
} EMC_DIDO;

// RS485参数
typedef struct tagEmcRs485
{
    tagEmcRs485()
    {
        uErroNumb = 0;
        uSendNumb = 0;
        uRecvNumb = 0;
    }

    int32u uErroNumb;
    int32u uSendNumb;
    int32u uRecvNumb;
} EMC_RS485;

// RS422参数
typedef struct tagEmcRs422
{
    tagEmcRs422()
    {
        uDIDOErroNumb = 0;
        for (int i = 0; i < 4; i++)
        {
            uDAADChnErroNumb[i] = 0;
        }

        uCoder1Value = 0;
        uCoder2Value = 0;
        uOfflineNumb = 0;
    }

    int32u uDIDOErroNumb;        // 出错次数
    int32u uDAADChnErroNumb[4];  // 通道1--通道4出错次数
    int32u uCoder1Value;         // 编码器1的值
    int32u uCoder2Value;         // 编码器2的值
    int32u uOfflineNumb;         // 离线次数
} EMC_RS422;

/******************************ecat DA module parameter  declaratio*************************/
typedef struct tagDAParam
{
    tagDAParam()
    {
        uTranMod = 0;
        uCfgUnit = 0;
        uStopOutState = 0;
        uStopOutValL = 0;
        uStopOutValH = 0;
    }
    // int8u	uSlotId;        //从1= 索引值+1
    int32u uTranMod;      /**< transform mode */
    int8u uCfgUnit;       /**< user config unit */
    int32u uStopOutState; /**< stop out state */
    int32u uStopOutValL;  /**< stop out value low */
    int32u uStopOutValH;  /**< stop out value high */
} DA_PARAM;

/******************************ecat AD module parameter  declaratio*************************/
typedef struct tagADParam
{
    tagADParam()
    {
        uTranMod = 0;
        uFiltParam = 0;
        wCfgUnit = 0;
        uAdjChn = 0;
        uAdjUnit = 0;
        sAdjUpVal = 0;
        sAdjMidVal = 0;
        sAdjDownVal = 0;
    }

    // int8u	uSlotId;        //从1= 索引值+1
    int32u uTranMod;    /**< transform mode */
    int32u uFiltParam;  /**< filter parameter*/
    int16u wCfgUnit;    /**< user config unit */
    int8u uAdjChn;      /**< adjust channel */
    int8u uAdjUnit;     /**< adjust channel */
    int16s sAdjUpVal;   /**< adjust up value*/
    int16s sAdjMidVal;  /**< adjust middle value */
    int16s sAdjDownVal; /**< adjust down value */
} AD_PARAM;

/******************************ecat AT module parameter  declaratio*************************/
typedef struct tagATParam
{
    tagATParam()
    {
        uMeasMod = 0;
        uFiltParam = 0;
        uAtOffsetValL = 0;
        uAtOffsetValH = 0;
        uAdjUpValL = 0;
        uAdjUpValH = 0;
        uAdjDownValL = 0;
        uAdjDownValH = 0;
        wFlag = 0;
    }

    // int8u	uSlotId;        //从1= 索引值+1
    int32u uMeasMod;      /**< measure mode */
    int32u uFiltParam;    /**< filter parameter */
    int32u uAtOffsetValL; /**< AT offset value low */
    int32u uAtOffsetValH; /**< AT offset value high */
    int32u uAdjUpValL;
    int32u uAdjUpValH;
    int32u uAdjDownValL;
    int32u uAdjDownValH;
    int16u wFlag;
} AT_PARAM;

/******************************IRLink DA module *************************/
typedef struct tagDACParam
{
    tagDACParam()
    {
        cha_range = 0;
        chb_range = 0;
        chc_range = 0;
        chd_range = 0;
    }

    bool operator==(const tagDACParam &other)
    {
        if (this == &other)
            return true;

        if (cha_range != other.cha_range)
            return false;
        if (chb_range != other.chb_range)
            return false;
        if (chc_range != other.chc_range)
            return false;
        if (chd_range != other.chd_range)
            return false;

        return true;
    }

    int8u cha_range; /**< da cha range */
    int8u chb_range; /**< da chb range */
    int8u chc_range; /**< da chc range */
    int8u chd_range; /**< da chd range */
} DAC_PARAM;

/******************************IRLink AD module *************************/
typedef struct tagADCParam
{
    tagADCParam()
    {
        range = 0;
        oversamp = 0;
    }

    bool operator==(const tagADCParam &other)
    {
        if (this == &other)
            return true;

        if (range != other.range)
            return false;
        if (oversamp != other.oversamp)
            return false;

        return true;
    }

    int8u range;    /**< ad range */
    int8u oversamp; /**< ad oversamp */
} ADC_PARAM;

/******************************IRLink Encoder module*************************/
typedef struct tagEncParam
{
    tagEncParam()
    {
        ch0reverse = 0;
        ch1reverse = 0;
        sampdepth = 0;
        samptime = 0;
    }

    bool operator==(const tagEncParam &other)
    {
        if (this == &other)
            return true;

        if (ch0reverse != other.ch0reverse)
            return false;
        if (ch1reverse != other.ch1reverse)
            return false;
        if (sampdepth != other.sampdepth)
            return false;
        if (samptime != other.samptime)
            return false;

        return true;
    }

    int8u ch0reverse; /**< encoder ch0 AB phase reverse */
    int8u ch1reverse; /**< encoder ch1 AB phase reverse */
    int8u sampdepth;  /**< encoder samp depth */
    int8u samptime;   /**< encoder samptime */
} ENC_PARAM;