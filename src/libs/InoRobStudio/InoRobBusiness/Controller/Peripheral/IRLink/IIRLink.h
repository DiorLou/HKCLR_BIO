#pragma once
#include "dllspec.h"
#include "DataTypeDef.h"
#include <vector>

namespace InoRobBusiness
{
constexpr int IR_RTU_MAX = 5;            // RTU最大数量
constexpr int IR_MODULE_MAX = 26;        // 总模块数最大数
constexpr int IR_RTU_MODULE_MAX = 10;    // 模块内部IO模块个数
constexpr int IR_IO_MAX = 2;             // 模块内部IO模块个数
constexpr int IR_RTU_POWER_MAX = 15000;  // 单个RTU的功率限制(单位0.001W)
constexpr int POWER_0808 = 1440;         // 0808模块功率
constexpr int POWER_16DO = 1250;         // 16DO模块功率
constexpr int POWER_16DI = 1250;         // 16DI模块功率
constexpr int POWER_4DA = 1440;          // 4DA模块功率
constexpr int POWER_4AD = 0;             // 4AD模块功率
constexpr int POWER_8AD = 2880;          // 8AD模块功率
constexpr int POWER_2ENC = 2880;         // 2ENC模块功率
constexpr int POWER_3232 = 0;            // 3232模块功率
constexpr int DI_MAX = 128;              // DI最大通道数
constexpr int DO_MAX = 128;              // DO最大通道数
constexpr int DAC_MAX = 16;              // DAC最大通道数
constexpr int ADC_MAX = 16;              // ADC最大通道数
constexpr int ENC_MAX = 8;               // ENC最大通道数

/**
 * @brief IRLink模块类型
 */
enum IRLink_Module_Type
{
    IR_MODULE_UNKNOWN = 0,  // 未知
    IR_MODULE_0808 = 1,     // 0808
    IR_MODULE_16DO = 2,     // 0016
    IR_MODULE_16DI = 3,     // 1600
    IR_MODULE_4DA = 4,      // 4DA
    IR_MODULE_4AD = 5,      // 4AD
    IR_MODULE_8AD = 6,      // 8AD
    IR_MODULE_2ENC = 7,     // 2ENC
    IR_MODULE_3232 = 8      // 1616
};

/**
 * @brief IRLink模块中IO类型
 */
enum IRLink_IO_Type
{
    IR_IO_UNKNOWN = 0,  // 未知
    IR_IO_DO = 1,       // digital output
    IR_IO_DI = 2,       // digital input
    IR_IO_DAC = 3,      // analog digital output
    IR_IO_ADC = 4,      // analog digital input
    IR_IO_ENC = 5,      // analog temperature
    IR_IO_32DO = 8,
    IR_IO_32DI = 9,
    IR_IO_4AD = 10,  // 4AD专用
};

/**
 * @brief IRLink中RTU、模块数量
 */
struct IRLinkRtuModuleNum
{
    int8u rtuNum = 0;                           // rtu数量
    int8u moduleNumArr[IR_MODULE_MAX] = { 0 };  // 每个rtu中模块数量列表
};

/**
 * @brief 模块IO配置
 */
struct IRLink_Module_Config
{
    int8u ioNum = 0;                      // 模块内IO数
    IRLink_IO_Type ioTypeArr[IR_IO_MAX];  // 模块内IO类型数组
};

/**
 * @brief 所有模块IO配置
 */
struct IRLink_All_Module_Config
{
    int8u totalModuleNum = 0;                             // 总模块数
    IRLink_Module_Config moduleConfigArr[IR_MODULE_MAX];  // 模块IO配置数组
};

/**
 * @brief DAC参数
 */
struct IRLink_DAC_Param
{
    int8u cha_range = 0;  // da cha range
    int8u chb_range = 0;  // da chb range
    int8u chc_range = 0;  // da chc range
    int8u chd_range = 0;  // da chd range

    IRLink_DAC_Param &operator=(const IRLink_DAC_Param &other)
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
struct IRLink_ADC_Param
{
    int8u range = 0;     // ad range
    int8u oversamp = 0;  // ad oversamp

    IRLink_ADC_Param &operator=(const IRLink_ADC_Param &other)
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
struct IRLink_ENC_Param
{
    int8u ch0reverse = 0;  // encoder ch0 AB phase reverse
    int8u ch1reverse = 0;  // encoder ch1 AB phase reverse
    int8u sampdepth = 0;   // encoder samp depth
    int8u samptime = 0;    // encoder samptime

    IRLink_ENC_Param &operator=(const IRLink_ENC_Param &other)
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
struct IRLink_IO_Param
{
    IRLink_IO_Type type = IR_IO_UNKNOWN;  // IO类型
    IRLink_DAC_Param DACParam;
    IRLink_ADC_Param ADCParam;
    IRLink_ENC_Param ENCParam;

    IRLink_IO_Param &operator=(const IRLink_IO_Param &other)
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
struct IRLinkModuleInfo
{
    IRLink_Module_Type type = IR_MODULE_UNKNOWN;
    std::vector<IRLink_IO_Param> params;

    IRLinkModuleInfo &operator=(const IRLinkModuleInfo &other)
    {
        this->type = other.type;
        this->params = other.params;
        return *this;
    }
};

class INOROBBUSINESS_CLASS IIRLink
{
public:
    virtual ~IIRLink()
    {
    }

    /**
     * @brief 与控制器通信 读取总模块数量
     * @param[out] num RTU数量
     * @return true成功 false失败
     */
    virtual bool readTotalModuleNum(short &num) = 0;

    /**
     * @brief 与控制器通信 设置总模块数量
     * @param num 从站数量
     * @return true成功 false失败
     */
    virtual bool writeTotalModuleNum(const short num) = 0;

    /**
     * @brief 与控制器通信 读取RTU、模块数量
     * @param[out] rtuModuleNum RTU、模块数量
     * @return true成功 false失败
     */
    virtual bool readRtuModuleNum(IRLinkRtuModuleNum &rtuModuleNum) = 0;

    /**
     * @brief 与控制器通信 设置RTU、模块数量
     * @param rtuModuleNum RTU、模块数量
     * @return true成功 false失败
     */
    virtual bool writeRtuModuleNum(const IRLinkRtuModuleNum &rtuModuleNum) = 0;

    /**
     * @brief 读取所有IO配置
     * @param[out] ioConfig IO配置
     * @return true成功 false失败
     */
    virtual bool readAllModuleConfig(IRLink_All_Module_Config &moduleConfig) = 0;

    /**
     * @brief 与控制器通信 读取模块参数
     * @param moduleId 模块Id
     * @param IONum IO数量
     * @param IOId IOId
     * @param[out] modParam 模块参数
     * @return true成功 false失败
     */
    virtual int readModuleParam(const short moduleId, const short IONum, const short IOId, IRLink_IO_Param &ioParam) = 0;

    /**
     * @brief 与控制器通信 设置模块参数
     * @param moduleId 模块Id
     * @param IONum IO数量
     * @param IOId IOId
     * @param[out] modParam 模块参数
     * @return true成功 false失败
     */
    virtual int writeModuleParam(const short moduleId, const short IONum, const short IOId, const IRLink_IO_Param &ioParam) = 0;

    /**
     * @brief 增加一个RTU
     * @param index rtu下标
     * @return true成功 false失败
     */
    virtual bool addRTU(const int index) = 0;

    /**
     * @brief 删除一个RTU
     * @param index rtu下标
     * @return true成功 false失败
     */
    virtual bool deleteRTU(const int index) = 0;

    /**
     * @brief 增加一个模块
     * @param rtuIndex rtu下标
     * @param moduleIndex 模块下标
     * @param moduleType 模块类型
     * @return true成功 false失败
     */
    virtual bool addModule(const int rtuIndex, const int moduleIndex, const IRLink_Module_Type moduleType) = 0;

    /**
     * @brief 删除一个模块
     * @param rtuIndex rtu下标
     * @param moduleIndex 模块下标
     * @return 成功 false失败
     */
    virtual bool deleteModule(const int rtuIndex, const int moduleIndex) = 0;

    /**
     * @brief 设置4DA模块参数
     * @param rtuIndex rtu下标
     * @param moduleIndex 模块下标
     * @param ioIndex io下标
     * @param[in] ioParam 模块参数
     * @return true成功 false失败
     */
    virtual bool set4DAParam(const int rtuIndex, const int moduleIndex, const int ioIndex, const IRLink_IO_Param &ioParam) = 0;

    /**
     * @brief 设置4AD模块参数
     * @param rtuIndex rtu下标
     * @param moduleIndex 模块下标
     * @param ioIndex io下标
     * @param[in] ioParam 模块参数
     * @return true成功 false失败
     */
    virtual bool set4ADParam(const int rtuIndex, const int moduleIndex, const int ioIndex, const IRLink_IO_Param &ioParam) = 0;

    /**
     * @brief 设置8AD模块参数
     * @param rtuIndex rtu下标
     * @param moduleIndex 模块下标
     * @param ioIndex io下标
     * @param[in] ioParam 模块参数
     * @return true成功 false失败
     */
    virtual bool set8ADParam(const int rtuIndex, const int moduleIndex, const int ioIndex, const IRLink_IO_Param &ioParam) = 0;

    /**
     * @brief 设置2ENC模块参数
     * @param rtuIndex rtu下标
     * @param moduleIndex 模块下标
     * @param ioIndex io下标
     * @param[in] ioParam 模块参数
     * @return true成功 false失败
     */
    virtual bool set2ENCParam(const int rtuIndex, const int moduleIndex, const int ioIndex, const IRLink_IO_Param &ioParam) = 0;

    /**
     * @brief 更新所有模块信息（读取控制器中数据）
     * @return true成功 false失败
     */
    virtual bool updateAllModuleInfos() = 0;

    /**
     * @brief 获取所有模块信息
     */
    virtual std::vector<std::vector<IRLinkModuleInfo>> getAllModuleInfos() const = 0;

    /**
     * @brief 保存IRLink
     * @return true成功 false失败
     */
    virtual bool saveIRLink() = 0;
};
}  // namespace InoRobBusiness
