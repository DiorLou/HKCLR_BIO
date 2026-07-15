#pragma once
#include "dllspec.h"
#include "IInoRobBusiness.h"
using namespace InoRobBusiness;

namespace InoRobBusinessProxy
{
#pragma region 数据（结构体与枚举）

constexpr int IR_RTU_MAX_V1 = 5;            // RTU最大数量
constexpr int IR_MODULE_MAX_V1 = 26;        // 总模块数最大数
constexpr int IR_RTU_MODULE_MAX_V1 = 10;    // 模块内部IO模块个数
constexpr int IR_IO_MAX_V1 = 2;             // 模块内部IO模块个数
constexpr int IR_RTU_POWER_MAX_V1 = 15000;  // 单个RTU的功率限制(单位0.001W)
constexpr int POWER_0808_V1 = 1440;         // 0808模块功率
constexpr int POWER_16DO_V1 = 1250;         // 16DO模块功率
constexpr int POWER_16DI_V1 = 1250;         // 16DI模块功率
constexpr int POWER_4DA_V1 = 1440;          // 4DA模块功率
constexpr int POWER_4AD_V1 = 0;             // 4AD模块功率
constexpr int POWER_8AD_V1 = 2880;          // 8AD模块功率
constexpr int POWER_2ENC_V1 = 2880;         // 2ENC模块功率
constexpr int POWER_3232_V1 = 0;            // 3232模块功率
constexpr int DI_MAX_V1 = 128;              // DI最大通道数
constexpr int DO_MAX_V1 = 128;              // DO最大通道数
constexpr int DAC_MAX_V1 = 16;              // DAC最大通道数
constexpr int ADC_MAX_V1 = 16;              // ADC最大通道数
constexpr int ENC_MAX_V1 = 8;               // ENC最大通道数

/**
 * @brief IRLink模块类型
 */
enum IRLink_Module_Type_V1
{
    IR_MODULE_UNKNOWN_V1 = 0,  // 未知
    IR_MODULE_0808_V1 = 1,     // 0808
    IR_MODULE_16DO_V1 = 2,     // 0016
    IR_MODULE_16DI_V1 = 3,     // 1600
    IR_MODULE_4DA_V1 = 4,      // 4DA
    IR_MODULE_4AD_V1 = 5,      // 4AD
    IR_MODULE_8AD_V1 = 6,      // 8AD
    IR_MODULE_2ENC_V1 = 7,     // 2ENC
    IR_MODULE_3232_V1 = 8      // 1616
};

/**
 * @brief IRLink模块中IO类型
 */
enum IRLink_IO_Type_V1
{
    IR_IO_UNKNOWN_V1 = 0,  // 未知
    IR_IO_DO_V1 = 1,       // digital output
    IR_IO_DI_V1 = 2,       // digital input
    IR_IO_DAC_V1 = 3,      // analog digital output
    IR_IO_ADC_V1 = 4,      // analog digital input
    IR_IO_ENC_V1 = 5,      // analog temperature
    IR_IO_32DO_V1 = 8,
    IR_IO_32DI_V1 = 9,
    IR_IO_4AD_V1 = 10,  // 4AD专用
};

/**
 * @brief IRLink中RTU、模块数量
 */
struct IRLinkRtuModuleNum_V1
{
    int8u rtuNum = 0;                              // rtu数量
    int8u moduleNumArr[IR_MODULE_MAX_V1] = { 0 };  // 每个rtu中模块数量列表
};

/**
 * @brief 模块IO配置
 */
struct IRLink_Module_Config_V1
{
    int8u ioNum = 0;                            // 模块内IO数
    IRLink_IO_Type_V1 ioTypeArr[IR_IO_MAX_V1];  // 模块内IO类型数组
};

/**
 * @brief 所有模块IO配置
 */
struct IRLink_All_Module_Config_V1
{
    int8u totalModuleNum = 0;                                   // 总模块数
    IRLink_Module_Config_V1 moduleConfigArr[IR_MODULE_MAX_V1];  // 模块IO配置数组
};

/**
 * @brief DAC参数
 */
struct IRLink_DAC_Param_V1
{
    int8u cha_range = 0;  // da cha range
    int8u chb_range = 0;  // da chb range
    int8u chc_range = 0;  // da chc range
    int8u chd_range = 0;  // da chd range

    IRLink_DAC_Param_V1 &operator=(const IRLink_DAC_Param_V1 &other)
    {
        this->cha_range = other.cha_range;
        this->chb_range = other.chb_range;
        this->chc_range = other.chc_range;
        this->chd_range = other.chd_range;
        return *this;
    }

    // int8u数据转为参数
    void int8uToParam(int8u *pBuf)
    {
        this->cha_range = pBuf[0];
        this->chb_range = pBuf[1];
        this->chc_range = pBuf[2];
        this->chd_range = pBuf[3];
    }

    // 参数转为int8u数据
    void paramToIn8u(int8u *pBuf) const
    {
        pBuf[0] = this->cha_range;
        pBuf[1] = this->chb_range;
        pBuf[2] = this->chc_range;
        pBuf[3] = this->chd_range;
    }
};

/**
 * @brief ADC参数
 */
struct IRLink_ADC_Param_V1
{
    int8u range = 0;     // ad range
    int8u oversamp = 0;  // ad oversamp

    IRLink_ADC_Param_V1 &operator=(const IRLink_ADC_Param_V1 &other)
    {
        this->range = other.range;
        this->oversamp = other.oversamp;
        return *this;
    }

    // int8u数据转为参数
    void int8uToParam(int8u *pBuf)
    {
        this->range = pBuf[0];
        this->oversamp = pBuf[1];
    }

    // 参数转为int8u数据
    void paramToIn8u(int8u *pBuf) const
    {
        pBuf[0] = this->range;
        pBuf[1] = this->oversamp;
    }
};

/**
 * @brief ENC参数
 */
struct IRLink_ENC_Param_V1
{
    int8u ch0reverse = 0;  // encoder ch0 AB phase reverse
    int8u ch1reverse = 0;  // encoder ch1 AB phase reverse
    int8u sampdepth = 0;   // encoder samp depth
    int8u samptime = 0;    // encoder samptime

    IRLink_ENC_Param_V1 &operator=(const IRLink_ENC_Param_V1 &other)
    {
        this->ch0reverse = other.ch0reverse;
        this->ch1reverse = other.ch1reverse;
        this->sampdepth = other.sampdepth;
        this->samptime = other.samptime;
        return *this;
    }

    // int8u数据转为参数
    void int8uToParam(int8u *pBuf)
    {
        this->ch0reverse = pBuf[0];
        this->ch1reverse = pBuf[1];
        this->sampdepth = pBuf[2];
        this->samptime = pBuf[3];
    }

    // 参数转为int8u数据
    void paramToIn8u(int8u *pBuf) const
    {
        pBuf[0] = this->ch0reverse;
        pBuf[1] = this->ch1reverse;
        pBuf[2] = this->sampdepth;
        pBuf[3] = this->samptime;
    }
};

/**
 * @brief IRLink模块中IO参数
 */
struct IRLink_IO_Param_V1
{
    IRLink_IO_Type_V1 type = IR_IO_UNKNOWN_V1;  // IO类型
    IRLink_DAC_Param_V1 DACParam;
    IRLink_ADC_Param_V1 ADCParam;
    IRLink_ENC_Param_V1 ENCParam;

    IRLink_IO_Param_V1 &operator=(const IRLink_IO_Param_V1 &other)
    {
        this->type = other.type;
        this->DACParam = other.DACParam;
        this->ADCParam = other.ADCParam;
        this->ENCParam = other.ENCParam;
        return *this;
    }
};

/**
 * @brief IRLink模块信息
 */
struct IRLinkModuleInfo_V1
{
    IRLink_Module_Type_V1 type = IR_MODULE_UNKNOWN_V1;
    std::vector<IRLink_IO_Param_V1> params;

    IRLinkModuleInfo_V1 &operator=(const IRLinkModuleInfo_V1 &other)
    {
        this->type = other.type;
        this->params = other.params;
        return *this;
    }
};

#pragma endregion

class INOROBBUSINESSPROXY_CLASS IRLink_V1
{
#pragma region 构造与析构

private:
    IIRLink *_irLink = nullptr;

public:
    IRLink_V1(IIRLink *irLink);
    ~IRLink_V1();

#pragma endregion

#pragma region 数据转换

public:
    static IRLink_Module_Type_V1 IRLink_Module_Type_ToProxy(IRLink_Module_Type irLink_Module_Type);
    static IRLink_Module_Type IRLink_Module_Type_FromProxy(IRLink_Module_Type_V1 irLink_Module_Type_V1);

    static IRLink_IO_Type_V1 IRLink_IO_Type_ToProxy(IRLink_IO_Type irLink_IO_Type);
    static IRLink_IO_Type IRLink_IO_Type_FromProxy(IRLink_IO_Type_V1 irLink_IO_Type_V1);

    static bool IRLinkRtuModuleNum_ToProxy(const IRLinkRtuModuleNum &irLinkRtuModuleNum, IRLinkRtuModuleNum_V1 &irLinkRtuModuleNum_V1);
    static bool IRLinkRtuModuleNum_FromProxy(const IRLinkRtuModuleNum_V1 &irLinkRtuModuleNum_V1, IRLinkRtuModuleNum &irLinkRtuModuleNum);

    static bool IRLink_Module_Config_ToProxy(const IRLink_Module_Config &irLink_Module_Config, IRLink_Module_Config_V1 &irLink_Module_Config_V1);
    static bool IRLink_Module_Config_FromProxy(const IRLink_Module_Config_V1 &irLink_Module_Config_V1, IRLink_Module_Config &irLink_Module_Config);

    static bool IRLink_All_Module_Config_ToProxy(const IRLink_All_Module_Config &irLink_All_Module_Config, IRLink_All_Module_Config_V1 &irLink_All_Module_Config_V1);
    static bool IRLink_All_Module_Config_FromProxy(const IRLink_All_Module_Config_V1 &irLink_All_Module_Config_V1, IRLink_All_Module_Config &irLink_All_Module_Config);

    static bool IRLink_DAC_Param_ToProxy(const IRLink_DAC_Param &irLink_DAC_Param, IRLink_DAC_Param_V1 &irLink_DAC_Param_V1);
    static bool IRLink_DAC_Param_FromProxy(const IRLink_DAC_Param_V1 &irLink_DAC_Param_V1, IRLink_DAC_Param &irLink_DAC_Param);

    static bool IRLink_ADC_Param_ToProxy(const IRLink_ADC_Param &irLink_ADC_Param, IRLink_ADC_Param_V1 &irLink_ADC_Param_V1);
    static bool IRLink_ADC_Param_FromProxy(const IRLink_ADC_Param_V1 &irLink_ADC_Param_V1, IRLink_ADC_Param &irLink_ADC_Param);

    static bool IRLink_ENC_Param_ToProxy(const IRLink_ENC_Param &irLink_ENC_Param, IRLink_ENC_Param_V1 &irLink_ENC_Param_V1);
    static bool IRLink_ENC_Param_FromProxy(const IRLink_ENC_Param_V1 &irLink_ENC_Param_V1, IRLink_ENC_Param &irLink_ENC_Param);

    static bool IRLink_IO_Param_ToProxy(const IRLink_IO_Param &irLink_IO_Param, IRLink_IO_Param_V1 &irLink_IO_Param_V1);
    static bool IRLink_IO_Param_FromProxy(const IRLink_IO_Param_V1 &irLink_IO_Param_V1, IRLink_IO_Param &irLink_IO_Param);

    static bool IRLinkModuleInfo_ToProxy(const IRLinkModuleInfo &irLinkModuleInfo, IRLinkModuleInfo_V1 &irLinkModuleInfo_V1);
    static bool IRLinkModuleInfo_FromProxy(const IRLinkModuleInfo_V1 &irLinkModuleInfo_V1, IRLinkModuleInfo &irLinkModuleInfo);

#pragma endregion

#pragma region 业务逻辑

public:
    /**
     * @brief 与控制器通信 读取总模块数量
     * @param[out] num RTU数量
     * @return true成功 false失败
     */
    bool readTotalModuleNum(short &num);

    /**
     * @brief 与控制器通信 设置总模块数量
     * @param num 从站数量
     * @return true成功 false失败
     */
    bool writeTotalModuleNum(const short num);

    /**
     * @brief 与控制器通信 读取RTU、模块数量
     * @param[out] rtuModuleNum RTU、模块数量
     * @return true成功 false失败
     */
    bool readRtuModuleNum(IRLinkRtuModuleNum_V1 &rtuModuleNum);

    /**
     * @brief 与控制器通信 设置RTU、模块数量
     * @param rtuModuleNum RTU、模块数量
     * @return true成功 false失败
     */
    bool writeRtuModuleNum(const IRLinkRtuModuleNum_V1 &rtuModuleNum);

    /**
     * @brief 读取所有IO配置
     * @param[out] ioConfig IO配置
     * @return true成功 false失败
     */
    bool readAllModuleConfig(IRLink_All_Module_Config_V1 &moduleConfig);

    /**
     * @brief 与控制器通信 读取模块参数
     * @param moduleId 模块Id
     * @param IONum IO数量
     * @param IOId IOId
     * @param[out] modParam 模块参数
     * @return true成功 false失败
     */
    int readModuleParam(const short moduleId, const short IONum, const short IOId, IRLink_IO_Param_V1 &ioParam);

    /**
     * @brief 与控制器通信 设置模块参数
     * @param moduleId 模块Id
     * @param IONum IO数量
     * @param IOId IOId
     * @param[out] modParam 模块参数
     * @return true成功 false失败
     */
    int writeModuleParam(const short moduleId, const short IONum, const short IOId, const IRLink_IO_Param_V1 &ioParam);

    /**
     * @brief 增加一个RTU
     * @param index rtu下标
     * @return true成功 false失败
     */
    bool addRTU(const int index);

    /**
     * @brief 删除一个RTU
     * @param index rtu下标
     * @return true成功 false失败
     */
    bool deleteRTU(const int index);

    /**
     * @brief 增加一个模块
     * @param rtuIndex rtu下标
     * @param moduleIndex 模块下标
     * @param moduleType 模块类型
     * @return true成功 false失败
     */
    bool addModule(const int rtuIndex, const int moduleIndex, const IRLink_Module_Type_V1 moduleType);

    /**
     * @brief 删除一个模块
     * @param rtuIndex rtu下标
     * @param moduleIndex 模块下标
     * @return 成功 false失败
     */
    bool deleteModule(const int rtuIndex, const int moduleIndex);

    /**
     * @brief 设置4DA模块参数
     * @param rtuIndex rtu下标
     * @param moduleIndex 模块下标
     * @param ioIndex io下标
     * @param[in] ioParam 模块参数
     * @return true成功 false失败
     */
    bool set4DAParam(const int rtuIndex, const int moduleIndex, const int ioIndex, const IRLink_IO_Param_V1 &ioParam);

    /**
     * @brief 设置4AD模块参数
     * @param rtuIndex rtu下标
     * @param moduleIndex 模块下标
     * @param ioIndex io下标
     * @param[in] ioParam 模块参数
     * @return true成功 false失败
     */
    bool set4ADParam(const int rtuIndex, const int moduleIndex, const int ioIndex, const IRLink_IO_Param_V1 &ioParam);

    /**
     * @brief 设置8AD模块参数
     * @param rtuIndex rtu下标
     * @param moduleIndex 模块下标
     * @param ioIndex io下标
     * @param[in] ioParam 模块参数
     * @return true成功 false失败
     */
    bool set8ADParam(const int rtuIndex, const int moduleIndex, const int ioIndex, const IRLink_IO_Param_V1 &ioParam);

    /**
     * @brief 设置2ENC模块参数
     * @param rtuIndex rtu下标
     * @param moduleIndex 模块下标
     * @param ioIndex io下标
     * @param[in] ioParam 模块参数
     * @return true成功 false失败
     */
    bool set2ENCParam(const int rtuIndex, const int moduleIndex, const int ioIndex, const IRLink_IO_Param_V1 &ioParam);

    /**
     * @brief 更新所有模块信息（读取控制器中数据）
     * @return true成功 false失败
     */
    bool updateAllModuleInfos();

    /**
     * @brief 获取所有模块信息
     */
    void getAllModuleInfos(std::vector<std::vector<IRLinkModuleInfo_V1>> &vec);

    /**
     * @brief 保存IRLink
     * @return true成功 false失败
     */
    bool saveIRLink();

#pragma endregion
};
}  // namespace InoRobBusinessProxy
