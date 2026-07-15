/****************************************************************
 * File Descrip : 碰撞检测基类
 ****************************************************************/
#pragma once
#include <string>
#include "dllspec.h"
#include "DataTypeDef.h"
#include "signal_slot.h"

namespace InoRobBusiness
{

// 碰撞检测参数
typedef struct tagColDetectPara
{
    tagColDetectPara()
    {
        iTrigEvent = 0;
        i32CollDict = 0;
        i32ColliFlag = 0;
        for (int i = 0; i < 8; i++)
        {
            iActive[i] = 0;
            dDegree[i] = 0;
        }
    }
    int8u iActive[8];   // 8个轴的开关 0-关 1-开
    double dDegree[8];  // 每个轴的灵敏度 25-300
    int8u iTrigEvent;   // 碰撞触发事件 0-继续运行;1-轻微警告;2-暂停警告;3-规划停止;4-报警急停;5-报警返回;7-立即回退;8-立即停止
    int i32CollDict;    // 回退距离5-100mm
    int i32ColliFlag;   // IO触发碰撞检测
} ColDetectPara;

#ifdef COBOT
typedef struct tagCobotColDetectPara
{
    tagCobotColDetectPara()
    {
        level = 0;
        strategy = 0;
        collDict = 0;
    }
    int16s level;     // 碰撞检测等级
    int16s strategy;  // 碰撞检测应对策略
    int32s collDict; // 回退距离5-100mm
} CobotColDetectPara;
#endif

class INOROBBUSINESS_CLASS ICrashDetection
{
public:
    /**
     * @brief 设备模式
     */
    enum class DevModeEnum : int
    {
        // 无效
        MODE_UNKNOW = -1,
        // 手动模式
        MODE_MANUAL,
        // 自动模式
        MODE_AUTO,
        // 静态碰撞监测
        MODE_STATIC,
    };

    virtual ~ICrashDetection()
    {
    }

    /**
     * @brief 读碰撞检测参数
     * @param mode 输入，模式
     * @param para 输出，碰撞检测参数
     * @return 0:成功 其他:错误码
     */
    virtual int readColDetectPara(DevModeEnum mode, ColDetectPara &para) = 0;

    /**
     * @brief 写碰撞检测参数
     * @param mode 输入，模式
     * @param para 输入，碰撞检测参数
     * @return 0:成功 其他:错误码
     */
    virtual int writeColDetectPara(DevModeEnum mode, ColDetectPara &para) = 0;

    /**
     * @brief 读推荐灵敏度
     * @param mode 输入，模式
     * @param degree 输出，灵敏度值
     * @return 0:成功 其他:错误码
     */
    virtual int readColDetectRecommadDegree(DevModeEnum mode, std::vector<double> &degree) = 0;

    /**
     * @brief 重置推荐灵敏度
     * @param mode 输入，模式
     * @return 0:成功 其他:错误码
     */
    virtual int resetColDetectRecommadDegree(DevModeEnum mode) = 0;

    /*!
     * \brief 读取静态碰撞检测等级
     * \param para 碰撞等级
     * \return
     */
    virtual int readColDetectLevelPara(int16u &para) = 0;

    /*!
     * \brief 写入静态碰撞检测等级
     * \param para 碰撞等级
     * \return
     */
    virtual int writeColDetectLevelPara(int16u para) = 0;

#ifdef COBOT
    /**
     * @brief 读碰撞检测参数
     * @param para 输出，碰撞检测参数
     * @return 0:成功 其他:错误码
     */
    virtual int readColDetectPara(CobotColDetectPara &para) = 0;

    /**
     * @brief 写碰撞检测参数
     * @param para 输入，碰撞检测参数
     * @return 0:成功 其他:错误码
     */
    virtual int writeColDetectPara(CobotColDetectPara para) = 0;

    /**
     * @brief 读推荐等级
     * @param degree 输出，等级值
     * @return 0:成功 其他:错误码
     */
    virtual int readColDetectRecommadLevel(int16s &level) = 0;

    /**
     * @brief 重置推荐灵敏度
     * @return 0:成功 其他:错误码
     */
    virtual int resetColDetectRecommadLevel() = 0;
#endif
};
}  // namespace InoRobBusiness
