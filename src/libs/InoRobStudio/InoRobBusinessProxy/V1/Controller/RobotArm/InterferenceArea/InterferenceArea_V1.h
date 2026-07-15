#pragma once
#include "dllspec.h"
#include "IInoRobBusiness.h"
#include "../../../GlobalDataTypes_V1.h"

using namespace InoRobBusiness;

namespace InoRobBusinessProxy
{

/*!
 * \brief  干涉区（25版本）, 机械臂下的子类
 * 2024/08/20
 */
class INOROBBUSINESSPROXY_CLASS InterferenceArea_V1
{
#pragma region 构造与析构

private:
    IInterferenceArea *_interferenceArea = nullptr;

public:
    InterferenceArea_V1(IInterferenceArea *interferenceArea);
    ~InterferenceArea_V1();

#pragma endregion

#pragma region 逻辑函数

public:
    // 读取干涉区设置中当前点位置
    int readCurrPointPosOfInterAreaSetting(RobPos_V1 &pos);

    // 读取末端监测对象当前点位置
    int readCurrPointPosOfToolObjSetting(RobPos_V1 &pos);

    // 检查输入和输出IO是否有效
    int checkInputAndOutputIOIsValid(int ioValue, bool printFlag);

    // 检查备注是否有效
    int checkInterZoneNotesIsValid(std::string &notes);

    // 检查安全距离1
    int checkSafeDistance1IsValid(float safeDistance);

    // 检查安全距离2
    int checkSafeDistance2IsValid(float safeDistance);

    // 检查偏移类型1是否有效
    int checkOffsetRule1IsValid(float pointValue);

    // 检查偏移类型2是否有效
    int checkOffsetRule2IsValid(float pointValue);

    // 权限保存检查
    bool checkSaveInterferencePermission();

    // 检查操作权限
    bool checkOperationPermission();

#pragma endregion

#pragma region 相关通讯函数

public:
    // 读取单个干涉区
    int readInterferenceZoneSingle(INTERFER_ZONE_V1 &buf);

    // 保存单个干涉区
    int writeInterferenceZoneSingle(INTERFER_ZONE_V1 &buf);

    // 读取单个末端监测对象
    int readInterferenceToolSingle(INTERFER_TOOL_V1 &buf);

    // 保存单个末端监测对象
    int writeInterferenceToolSingle(INTERFER_TOOL_V1 &buf);

    // 读取所有干涉区激活状态
    int readInterferenceZoneActivateStatus(INTERFER_ZONES_STATUS_V1 &buf);

    // 保存所有干涉区激活状态
    int writeInterferenceZoneActivateStatus(INTERFER_ZONES_STATUS_V1 &buf);

    // 读取所有末端监测对象激活状态
    int readInterferenceToolActivateStatus(INTERFER_ZONES_STATUS_V1 &buf);

    // 保存所有末端监测对象激活状态
    int writeInterferenceToolActivateStatus(INTERFER_ZONES_STATUS_V1 &buf);

    // 读取干涉区工件参数相关
    int readInterferenceZoneWobjParam(int8u no, INTERFER_ZONE_WOBJPARAM_V1 &buf);

    // 保存干涉区工件参数相关
    int writeInterferenceZoneWobjParam(int8u no, INTERFER_ZONE_WOBJPARAM_V1 &buf);

    // 读取MTCP工具参数
    int readInterToolMTCPToolParam(int8u no, INTERFER_ZONE_MTCPTOOLPARAM_V1 &buf);

    // 保存MTCP工件参数
    int writeInterToolMTCPToolParam(int8u no, INTERFER_ZONE_MTCPTOOLPARAM_V1 &buf);

#pragma endregion
};
}  // namespace InoRobBusinessProxy
