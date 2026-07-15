#pragma once
#include <string>
#include <QObject>
#include "dllspec.h"
#include "DataTypeDef.h"
#include "signal_slot.h"
#include "InoRobUtil.h"
#include "../../Project/IProject.h"

/*
    位置
    Create by WuJian at 2022/5/6
*/
namespace InoRobBusiness
{
// 读取当前点的结果状态
enum ReadCurPosState : int8s
{
    READ_POS_ERR = -1,      // 读取失败
    READ_POS_ING = 0,       // 读取中
    READ_POS_OK = 1,        // 读取完成，且成功
    READ_POS_SINGULAR = 2,  // 读取完成，但是奇异点
};

class INOROBBUSINESS_CLASS IPosition : public QObject
{
    Q_OBJECT

public:
    virtual ~IPosition()
    {
    }
    /*!
     * \brief 初始化
     */
    virtual void init() = 0;
    // 根据坐标系类型枚举获取对应的名称
    virtual string CoordTypeName(InoRobUtil::CoordType coordType) = 0;
    // 设定当前坐标系类型
    virtual bool SetCurrentCoordType(InoRobUtil::CoordType coordType) = 0;

    // 根据位置格式枚举获取对应的名称
    virtual string PosFormatName(InoRobUtil::PosFormat posFormat) = 0;
    // 设定当前位置格式
    virtual bool SetPosFormat(InoRobUtil::PosFormat posFormat) = 0;

    // 设置homed点触发IO信号
    virtual int setHomeTriggerOutData(const JHomeTriggertOutData &data) = 0;

    // 读取homed点触发IO信号
    virtual int getHomeTriggerOutData(JHomeTriggertOutData &data) = 0;

    // 检查保存权限
    virtual bool checkSaveHomeTriggerPermission() = 0;

#pragma region 取当前点

    // 获取当前关节点
    // jPos :返回的当前关节值
    virtual bool GetCurJPos(JPos &jPos) = 0;

    /**
     * @brief 获取当前位置点
     * @param robPos 输出，位置点数据
     * @param isAllowSingular 输入，是否允许取奇异点
     * @return 成功返回true，失败返回false
     */
    virtual bool getCurRPos(RobPos &robPos, bool isAllowSingular = false) = 0;

    // 获取当前直角点
    // toolId 传入的工具号（并不一定是当前的，例如中间点标定）
    // referObj 传入的参考对象（-2：Base，-1：flange，0至15：工件号等）
    // status 返回的取点状态
    // robPos 返回的当前直角值
    // isAllowSingular 是否允许取奇异点
    virtual bool GetCurPos(int16u toolId, ReferObj referObj, ReadCurPosState &status, RobPos &robPos, bool isAllowSingular = false) = 0;

    // 获取当前直角点(协作接口)
    // toolId 传入的工具号（并不一定是当前的，例如中间点标定）
    // referObj 传入的参考对象（-3：(特殊标识)直接获取世界坐标点位，-2：Base，-1：flange，0至15：工件号等）
    // status 返回的取点状态
    // jPos 返回的当前关节位置值
    // pose 返回的当前手臂的位姿值
    // isAllowSingular 是否允许取奇异点
    virtual bool GetCurPos(int16u toolId, ReferObj referObj, ReadCurPosState &status, JPos &jPos, RobPos &pose, bool isAllowSingular = false) = 0;

    /**
     * @brief 检查位置点位数据是否合格
     * @param robPos 输入，位置点位
     * @return 合格返回true，非法返回false
     */
    virtual bool isRPosValid(const RobPos &robPos) = 0;

#pragma endregion

#pragma region 计算平移变量

    // 获取平移变量的值
    virtual bool GetPrValue(RobPos pos1, RobPos pos2, Pose &Pr) = 0;

#pragma endregion

    // 运动学逆解
    // toolId-工具号
    // wobjId-工件号
    // loadId-负载号
    // p-需要逆解的位置点
    // retCode-返回的值,-1， 逆解失败；0，逆解成功；1，逆解成功，但为奇异点
    // jp-逆解得到的关节位置点
    virtual bool KineInverseSolution(int16s toolId, int16s wobjId, int16s loadId, RobPos p, int32s &retCode, JPos &jp) = 0;

#pragma region 点位赋值指令相关

    /**
     * @brief 解析并判断是否为点位赋值相关指令
     * @param type 输出，点位类型
     * @param pointNo 输出，点位序号
     * @param note 输出，注释
     * @param instructionText 输入，单条指令文本
     * @return 是否为点位赋值指令
     */
    virtual bool isAssignValuesToPtInstruction(PointType &type, int &pointNo, std::string &note, const std::string &instructionText) = 0;
    /**
     * @brief 从点位赋值指令中解析出位置点位数据
     * @param pos 输入，位置点位数据
     * @param instructionText 输入，单条指令文本
     * @return 成功返回0，其他请见错误码
     */
    virtual int parsePDataInAssignInstruction(RobPos &pos, const std::string &instructionText) = 0;
    /**
     * @brief 从点位赋值指令中解析出位置点位数据
     * @param pos 输入，关节点位数据
     * @param instructionText 输入，单条指令文本
     * @return 成功返回0，其他请见错误码
     */
    virtual int parseJPDataInAssignInstruction(JPos &pos, const std::string &instructionText) = 0;
    /**
     * @brief 生成位置点位类型的赋值指令(P或者LP)，点位数据由当前点数据填充
     * @param type 输入，点位类型
     * @param pointNo 输入，点位序号
     * @return 点位赋值指令文本(单条)，如果失败则返回空
     */
    virtual std::string genAssignValuesToPtInstruction(const PointType &type, int pointNo) = 0;
    /**
     * @brief 生成全局关节点位类型的赋值指令，点位数据由当前点数据填充
     * @param pos 输入，点位数据
     * @param pointNo 输入，点位序号
     * @return 点位赋值指令文本(单条)，如果失败则返回空
     */
    virtual std::string genAssignValuesToJPtInstruction(int pointNo) = 0;

#pragma endregion
};
}  // namespace InoRobBusiness
