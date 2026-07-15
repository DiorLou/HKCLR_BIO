#pragma once

#include <QObject>
#include "communication_global.h"
#include "safety/safetydefines.h"

namespace InoRobBusiness
{
class IController;
}  // namespace InoRobBusiness

class Communication;

/// @brief 控制器接口
class COMMUNICATION_EXPORT SafetyInterface
{
public:
    SafetyInterface()
    {
    }

    virtual Communication *comm() = 0;
    virtual InoRobBusiness::IController *controller() = 0;

    int QuerySafeParaCabinet();
    int QuerySafeParaCabinetProcess(bool printFlag);

    /**
     * @brief  : 传入一个密码并向安全MCU校验该密码
     * @param  password: 用户输入待校验的密码
     * @return int: 0 - 密码校验通过
     */
    int CheckSafeParaPassword(const unsigned int password);

    /**
     * @brief  : 返回上次密码校验的结果
     * @return int: 0 - 上次密码校验通过
     */
    int CheckSafeParaPassword();

    /**
     * @brief  : 从安全MCU读取数据到模型层
     * @param  key: 功能安全功能特性枚举值, 详见SafeParaEnum
     * @param  offset: 该数据相对首个同类数据的偏移
     * @param  num: 基于key + offset位置, 获取num个数据
     * @return int: 0 - 读取过程成功
     */
    int SafetyReadParams(int key, int offset, int num);

    /**
     * @brief  : 获取模型层数据至界面
     * @param  key: 功能安全功能特性枚举值, 详见SafeParaEnum
     * @param  offset: 该数据相对首个同类数据的偏移
     * @param  length: 该数据长度
     * @param  buf: 将该数据放入buf
     * @param  forceFlag: 若该数据部位SYNC状态, 则从SafeMCU获取, 该逻辑耗时较长
     * @return int: 0 - 获取过程成功
     */
    int GetSafeParaCommon(int key, int offset, int length, unsigned char *buf,
                          bool forceFlag = false);

    /**
     * @brief  : 将界面数据下发模型层, 并将数据status设置为SPS_EDITED
     * @param  key: 功能安全功能特性枚举值, 详见SafeParaEnum
     * @param  offset: 该数据相对首个同类数据的偏移
     * @param  length: 该数据长度
     * @param  buf: 将该数据放入buf
     * @param  forceFlag: 强制写入
     * @return int: 0 - 写入成功
     */
    int SetSafeParaCommon(int key, int offset, int length, unsigned char *buf,
                          bool forceFlag = false);

    /**
     * @brief  : 保存status为SPS_EDITED的变量至SafeMCU, A40I
     * @param  key: 功能安全功能特性枚举值, 详见SafeParaEnum
     * @param  offset: 该数据相对首个同类数据的偏移
     * @param  num: 基于key + offset位置, 获取num个数据
     * @return int: 0 - 写入成功
     */
    int SafetyWriteParams(int key, int offset, int num);

    /**
     * @brief Write : 一次性从模型层写多条数据到mcu
     * @param range : 数据键值列表
     * @param num   : 数量
     * @return int  : 0 - 写入成功
     */
    int SafetyWriteParams(int *range, int num);

    /**
     * @brief  : 初始化所有功能安全参数, 并开启一线程轮询结果
     * @return int: 0 - 启动初始化过程成功
     */
    int SafeParaReset();

    /**
     * @brief  : 检查数据地图中的某状态
     * @param  key: 功能安全功能特性枚举值, 详见SafeParaEnum
     * @param  offset: 该数据相对首个同类数据的偏移
     * @param  num: 基于key + offset位置, 获取num个数据
     * @param  status: 状态
     * @return int: 0 - 检查成功
     */
    int CheckAStatus(int key, int offset, int num, int status);

    // int SafeToolModeOccupied(const short DO[DO_NUM]);

    /**
     * @brief  : 获取安全MCU版本信息
     * @param  system: 系统软件版本
     * @param  moni: 监控软件版本
     * @param  commu: 通信软件版本
     * @return int: 0 - 操作成功
     */
    int GetSafeHardVer(std::string &system, std::string &moni, std::string &commu);

    /**
     * @brief  : 开启轮询线程, 询问安全IO电平状态
     * @param  switchFlag: false-关闭线程 true-开启线程
     * @return int: 0 - 操作成功
     */
    int QuerySafeIORealTime(bool switchFlag);

    /**
     * @brief : 一次性写入多条数据到安全mcu
     * @param : 多条数据参数
     * @return : true - 成功 false - 失败
     */
    bool WriteParamsDirect2Mcu(const QVector<SafeReadWriteCmdParam> &vecParams);

    /**
     * @brief : 一次性直接从安全mcu读取多条数据
     * @param : 多条数据参数
     * @return : true - 成功 false - 失败
     */
    bool ReadParamsDirectFromMcu(QVector<SafeReadWriteCmdParam> &vecParams);

    /**
     * @brief : 设置干涉区下发状态
     * @param : 0 - 下发中 1 - 下发成功 2 - 下发失败
     * @return : 0 - 设置成功
     */
    int SetInterZoneSendStatus(quint8 status);

    /**
     * @brief : 写入缩减等级配置信息
     * @param : 缩减等级速度缩减百分比数据
     * @return : 0 - 写入成功
     */
    int WriteSpeedReducing(const SpeedReducingConf &conf);

    /**
     * @brief : 读取缩减等级配置信息
     * @param : 缩减等级速度缩减百分比数据
     * @return : 0 - 读取成功
     */
    int ReadSpeedReducing(SpeedReducingConf &conf);

    int ExportFunctionSafeParaFile(const std::string exportRoute);
    int ImportFunctionSafeParaFile(const std::string importRoute);
};
