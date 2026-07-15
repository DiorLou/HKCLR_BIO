#pragma once
#include "dllspec.h"
#include "IInoRobBusiness.h"
using namespace InoRobBusiness;

namespace InoRobBusinessProxy
{

/****************************************************************
 * File Descrip : 碰撞检测基类
 * 2024/08/20
 ****************************************************************/

// 碰撞检测参数
typedef struct tagColDetectPara_V1
{
    tagColDetectPara_V1()
    {
        iTrigEvent = 0;
        i32CollDict = 0;
        i32ColliFlag = 0;
        for (size_t i = 0; i < 8; i++)
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
} ColDetectPara_V1;

class INOROBBUSINESSPROXY_CLASS CrashDetection_V1
{
#pragma region 枚举

public:
    /**
     * @brief 设备模式
     */
    enum class DevModeEnum_V1 : int
    {
        // 无效
        MODE_UNKNOW_V1 = -1,
        // 手动模式
        MODE_MANUAL_V1,
        // 自动模式
        MODE_AUTO_V1,
    };

#pragma endregion

#pragma region 数据转换

public:
    static bool ColDetectPara_ToProxy(const ColDetectPara &colDetectPara, ColDetectPara_V1 &colDetectPara_V1);
    static bool ColDetectPara_FromProxy(const ColDetectPara_V1 &colDetectPara_V1, ColDetectPara &colDetectPara);

    static DevModeEnum_V1 DevModeEnum_ToProxy(ICrashDetection::DevModeEnum devModeEnum);
    static ICrashDetection::DevModeEnum DevModeEnum_FromProxy(DevModeEnum_V1 devModeEnum_V1);

#pragma endregion

#pragma region 构造与析构

private:
    ICrashDetection *_crashDetection = nullptr;

public:
    CrashDetection_V1(ICrashDetection *crashDetection);
    ~CrashDetection_V1();

#pragma endregion

#pragma region 业务逻辑

public:
    /**
     * @brief 读碰撞检测参数
     * @param mode 输入，模式
     * @param para 输出，碰撞检测参数
     * @return 0:成功 其他:错误码
     */
    int readColDetectPara(DevModeEnum_V1 mode, ColDetectPara_V1 &para);

    /**
     * @brief 写碰撞检测参数
     * @param mode 输入，模式
     * @param para 输入，碰撞检测参数
     * @return 0:成功 其他:错误码
     */
    int writeColDetectPara(DevModeEnum_V1 mode, ColDetectPara_V1 &para);

    /**
     * @brief 读推荐灵敏度
     * @param mode 输入，模式
     * @param degree 输出，灵敏度值
     * @return 0:成功 其他:错误码
     */
    int readColDetectRecommadDegree(DevModeEnum_V1 mode, std::vector<double> &degree);

    /**
     * @brief 重置推荐灵敏度
     * @param mode 输入，模式
     * @return 0:成功 其他:错误码
     */
    int resetColDetectRecommadDegree(DevModeEnum_V1 mode);

#pragma endregion
};
}  // namespace InoRobBusinessProxy
