#pragma once
#include "IInterferenceArea.h"
#include "IInoRobBusiness.h"

namespace InoRobBusiness
{

class INOROBBUSINESS_CLASS InterferenceAreaDefault : public IInterferenceArea
{
    Q_OBJECT

private:
    // 依赖注入
    IDataSrvBase *_pDataService = nullptr;
    IRobotArm *_pRobotArm = nullptr;
    ITool *_pTool = nullptr;          // 工具
    IWobj *_pWobj = nullptr;          // 工件
    IPosition *_pPosition = nullptr;  // 位置

public:
    InterferenceAreaDefault(IDataSrvBase *dataService, IRobotArm *robotArm, ITool *pTool, IWobj *pWobj, IPosition *pPosition);
    ~InterferenceAreaDefault();

#pragma region 逻辑函数
    // 读取干涉区设置中当前点位置
    int readCurrPointPosOfInterAreaSetting(RobPos &pos);

    // 读取末端监测对象当前点位置
    int readCurrPointPosOfToolObjSetting(RobPos &pos);

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
    // 读取单个干涉区
    int readInterferenceZoneSingle(INTERFER_ZONE &buf);

    // 保存单个干涉区
    int writeInterferenceZoneSingle(INTERFER_ZONE &buf);

    // 读取单个末端监测对象
    int readInterferenceToolSingle(INTERFER_TOOL &buf);

    // 保存单个末端监测对象
    int writeInterferenceToolSingle(INTERFER_TOOL &buf);

    // 读取所有干涉区激活状态
    int readInterferenceZoneActivateStatus(INTERFER_ZONES_STATUS &buf);

    // 保存所有干涉区激活状态
    int writeInterferenceZoneActivateStatus(INTERFER_ZONES_STATUS &buf);

    // 读取所有末端监测对象激活状态
    int readInterferenceToolActivateStatus(INTERFER_ZONES_STATUS &buf);

    // 保存所有末端监测对象激活状态
    int writeInterferenceToolActivateStatus(INTERFER_ZONES_STATUS &buf);

    // 读取 干涉区工件参数相关
    int readInterferenceZoneWobjParam(int8u no, INTERFER_ZONE_WOBJPARAM &buf);

    // 保存 干涉区工件参数相关
    int writeInterferenceZoneWobjParam(int8u no, INTERFER_ZONE_WOBJPARAM &buf);

    // 读取MTCP工具参数
    int readInterToolMTCPToolParam(int8u no, INTERFER_ZONE_MTCPTOOLPARAM &buf);

    // 保存MTCP工件参数
    int writeInterToolMTCPToolParam(int8u no, INTERFER_ZONE_MTCPTOOLPARAM &buf);
#pragma endregion
};
}  // namespace InoRobBusiness
