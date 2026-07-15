#pragma once
#include <QObject>
#include "dllspec.h"
#include "DataTypeDef.h"
#include "DataSrvGlobal.h"

namespace InoRobBusiness
{
/*!
 * \brief  干涉区（25版本）, 机械臂下的子类
 */
class INOROBBUSINESS_CLASS IInterferenceArea : public QObject
{
    Q_OBJECT
public:
    virtual ~IInterferenceArea()
    {
    }

#pragma region 逻辑函数
    // 读取干涉区设置中当前点位置
    virtual int readCurrPointPosOfInterAreaSetting(RobPos &pos) = 0;

    // 读取末端监测对象当前点位置
    virtual int readCurrPointPosOfToolObjSetting(RobPos &pos) = 0;

    // 检查输入和输出IO是否有效
    virtual int checkInputAndOutputIOIsValid(int ioValue, bool printFlag) = 0;

    // 检查备注是否有效
    virtual int checkInterZoneNotesIsValid(std::string &notes) = 0;

    // 检查安全距离1
    virtual int checkSafeDistance1IsValid(float safeDistance) = 0;

    // 检查安全距离2
    virtual int checkSafeDistance2IsValid(float safeDistance) = 0;

    // 检查偏移类型1是否有效
    virtual int checkOffsetRule1IsValid(float pointValue) = 0;

    // 检查偏移类型2是否有效
    virtual int checkOffsetRule2IsValid(float pointValue) = 0;

    // 权限保存检查
    virtual bool checkSaveInterferencePermission() = 0;

    // 检查操作权限
    virtual bool checkOperationPermission() = 0;

#pragma endregion

#pragma region 相关通讯函数
    // 读取单个干涉区
    virtual int readInterferenceZoneSingle(INTERFER_ZONE &buf) = 0;

    // 保存单个干涉区
    virtual int writeInterferenceZoneSingle(INTERFER_ZONE &buf) = 0;

    // 读取单个末端监测对象
    virtual int readInterferenceToolSingle(INTERFER_TOOL &buf) = 0;

    // 保存单个末端监测对象
    virtual int writeInterferenceToolSingle(INTERFER_TOOL &buf) = 0;

    // 读取所有干涉区激活状态
    virtual int readInterferenceZoneActivateStatus(INTERFER_ZONES_STATUS &buf) = 0;

    // 保存所有干涉区激活状态
    virtual int writeInterferenceZoneActivateStatus(INTERFER_ZONES_STATUS &buf) = 0;

    // 读取所有末端监测对象激活状态
    virtual int readInterferenceToolActivateStatus(INTERFER_ZONES_STATUS &buf) = 0;

    // 保存所有末端监测对象激活状态
    virtual int writeInterferenceToolActivateStatus(INTERFER_ZONES_STATUS &buf) = 0;

    // 读取干涉区工件参数相关
    virtual int readInterferenceZoneWobjParam(int8u no, INTERFER_ZONE_WOBJPARAM &buf) = 0;

    // 保存干涉区工件参数相关
    virtual int writeInterferenceZoneWobjParam(int8u no, INTERFER_ZONE_WOBJPARAM &buf) = 0;

    // 读取MTCP工具参数
    virtual int readInterToolMTCPToolParam(int8u no, INTERFER_ZONE_MTCPTOOLPARAM &buf) = 0;

    // 保存MTCP工件参数
    virtual int writeInterToolMTCPToolParam(int8u no, INTERFER_ZONE_MTCPTOOLPARAM &buf) = 0;
#pragma endregion
};
}  // namespace InoRobBusiness
