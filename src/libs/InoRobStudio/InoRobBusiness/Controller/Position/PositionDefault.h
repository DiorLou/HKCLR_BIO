#pragma once
#include <string>
#include "IInoRobBusiness.h"

namespace InoRobBusiness
{
class INOROBBUSINESS_CLASS PositionDefault : public IPosition
{
    Q_OBJECT

#pragma region 构造与析构

private:
    // 依赖注入的IdataService，基于老代码与控制器通信
    IDataSrvBase *m_DataService;
    // 连接
    IConnection *m_Connection;
    // 监控
    IMonitor *m_Monitor;

public:
    PositionDefault(string name, IDataSrvBase *dataService, QObject *parent = nullptr);
    ~PositionDefault();
    void init() override;
    // 设置homed点触发IO信号
    int setHomeTriggerOutData(const JHomeTriggertOutData &data);

    // 读取homed点触发IO信号
    int getHomeTriggerOutData(JHomeTriggertOutData &data);

    // 检查保存权限
    bool checkSaveHomeTriggerPermission();

#pragma endregion

    // 当前坐标系类型
    bool SetCurrentCoordType(InoRobUtil::CoordType coordType);
    string CoordTypeName(InoRobUtil::CoordType coordType);

    // 当前显示的位置格式
    string PosFormatName(InoRobUtil::PosFormat posFormat);
    bool SetPosFormat(InoRobUtil::PosFormat posFormat);

#pragma region 取当前点

public:
    bool GetCurJPos(JPos &jPos);
    virtual bool getCurRPos(RobPos &robPos, bool isAllowSingular = false) override;
    bool GetCurPos(int16u toolId, ReferObj referObj, ReadCurPosState &status, RobPos &robPos, bool isAllowSingular = false);
    bool GetCurPos(int16u toolId, ReferObj referObj, ReadCurPosState &status, JPos &jPos, RobPos &pose, bool isAllowSingular = false);
    virtual bool isRPosValid(const RobPos &robPos) override;

#pragma endregion

#pragma region 获取平移变量的值

    // 获取平移变量的值
    bool GetPrValue(RobPos pos1, RobPos pos2, Pose &Pr);

#pragma endregion

    // 运动学逆解
    bool KineInverseSolution(int16s toolId, int16s wobjId, int16s loadId, RobPos p, int32s &retCode, JPos &jp);

#pragma region 点位赋值指令相关

    virtual bool isAssignValuesToPtInstruction(PointType &type, int &pointNo, std::string &note, const std::string &instructionText) override;
    virtual int parsePDataInAssignInstruction(RobPos &pos, const std::string &instructionText) override;
    virtual int parseJPDataInAssignInstruction(JPos &pos, const std::string &instructionText) override;
    virtual std::string genAssignValuesToPtInstruction(const PointType &type, int pointNo) override;
    virtual std::string genAssignValuesToJPtInstruction(int pointNo) override;

#pragma endregion
};
}  // namespace InoRobBusiness
