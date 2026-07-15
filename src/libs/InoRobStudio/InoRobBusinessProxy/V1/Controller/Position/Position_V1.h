#pragma once
#include "dllspec.h"
#include "IInoRobBusiness.h"
#include "../../InoRobUtil/CommonEnum_V1.h"
#include "../../GlobalDataTypes_V1.h"
#include "../../DataService/DataSrvGlobal_V1.h"
#include "../../Project/Project_V1.h"

using namespace InoRobBusiness;

namespace InoRobBusinessProxy
{

/*
    位置
    2024/08/20
*/

// 读取当前点的结果状态
enum ReadCurPosState_V1 : int8s
{
    READ_POS_ERR_V1 = -1,   // 读取失败
    READ_POS_ING_V1 = 0,    // 读取中
    READ_POS_OK_V1 = 1,     // 读取完成，且成功
    READ_POS_SINGULAR_V1 = 2,  // 读取完成，但是奇异点
};

class INOROBBUSINESSPROXY_CLASS Position_V1
{

#pragma region 数据转换

public:
    static ReadCurPosState_V1 ReadCurPosState_ToProxy(ReadCurPosState readCurPosState);
    static ReadCurPosState ReadCurPosState_FromProxy(ReadCurPosState_V1 readCurPosState_V1);

#pragma endregion

#pragma region 构造与析构

private:
    IPosition *_position = nullptr;

public:
    Position_V1(IPosition *position);
    ~Position_V1();

#pragma endregion

#pragma region 业务逻辑

public:
    // 根据坐标系类型枚举获取对应的名称
    string CoordTypeName(CoordType_V1 coordType);

    // 设定当前坐标系类型
    bool SetCurrentCoordType(CoordType_V1 coordType);

    // 根据位置格式枚举获取对应的名称
    string PosFormatName(PosFormat_V1 posFormat);

    // 设定当前位置格式
    bool SetPosFormat(PosFormat_V1 posFormat);

    // 设置homed点触发IO信号
    int setHomeTriggerOutData(const JHomeTriggertOutData_V1 &data);

    // 读取homed点触发IO信号
    int getHomeTriggerOutData(JHomeTriggertOutData_V1 &data);

    // 检查保存权限
    bool checkSaveHomeTriggerPermission();

#pragma endregion

#pragma region 取当前点

public:
    // 获取当前关节点
    // jPos :返回的当前关节值
    bool GetCurJPos(JPos_V1 &jPos);

    /**
     * @brief 获取当前位置点
     * @param robPos 输出，位置点数据
     * @param isAllowSingular 输入，是否允许取奇异点
     * @return 成功返回true，失败返回false
     */
    bool getCurRPos(RobPos_V1 &robPos, bool isAllowSingular = false);

    // 获取当前直角点
    // toolId 传入的工具号（并不一定是当前的，例如中间点标定）
    // referObj 传入的参考对象（-2：Base，-1：flange，0至15：工件号等）
    // status 返回的取点状态
    // robPos 返回的当前直角值
    // isAllowSingular 是否允许取奇异点
    bool GetCurPos(int16u toolId, ReferObj_V1 referObj, ReadCurPosState_V1 &status, RobPos_V1 &robPos, bool isAllowSingular = false);

    // 获取当前直角点(协作接口)
    // toolId 传入的工具号（并不一定是当前的，例如中间点标定）
    // referObj 传入的参考对象（-3：(特殊标识)直接获取世界坐标点位，-2：Base，-1：flange，0至15：工件号等）
    // status 返回的取点状态
    // jPos 返回的当前关节位置值
    // pose 返回的当前手臂的位姿值
    // isAllowSingular 是否允许取奇异点
    bool GetCurPos(int16u toolId, ReferObj_V1 referObj, ReadCurPosState_V1 &status, JPos_V1 &jPos, RobPos_V1 &pose, bool isAllowSingular = false);

    /**
     * @brief 检查位置点位数据是否合格
     * @param robPos 输入，位置点位
     * @return 合格返回true，非法返回false
     */
    bool isRPosValid(const RobPos_V1 &robPos);

#pragma endregion

#pragma region 计算平移变量

public:
    // 获取平移变量的值
    bool GetPrValue(RobPos_V1 pos1, RobPos_V1 pos2, Pose_V1 &Pr);

#pragma endregion

public:
    // 运动学逆解
    // toolId-工具号
    // wobjId-工件号
    // loadId-负载号
    // p-需要逆解的位置点
    // retCode-返回的值,-1， 逆解失败；0，逆解成功；1，逆解成功，但为奇异点
    // jp-逆解得到的关节位置点
    bool KineInverseSolution(int16s toolId, int16s wobjId, int16s loadId, RobPos_V1 p, int32s &retCode, JPos_V1 &jp);

#pragma region 点位赋值指令相关

public:
    /**
     * @brief 解析并判断是否为点位赋值相关指令
     * @param type 输出，点位类型
     * @param pointNo 输出，点位序号
     * @param note 输出，注释
     * @param instructionText 输入，单条指令文本
     * @return 是否为点位赋值指令
     */
    bool isAssignValuesToPtInstruction(PointType_V1 &type, int &pointNo, std::string &note, const std::string &instructionText);
    /**
     * @brief 从点位赋值指令中解析出位置点位数据
     * @param pos 输入，位置点位数据
     * @param instructionText 输入，单条指令文本
     * @return 成功返回0，其他请见错误码
     */
    int parsePDataInAssignInstruction(RobPos_V1 &pos, const std::string &instructionText);
    /**
     * @brief 从点位赋值指令中解析出位置点位数据
     * @param pos 输入，关节点位数据
     * @param instructionText 输入，单条指令文本
     * @return 成功返回0，其他请见错误码
     */
    int parseJPDataInAssignInstruction(JPos_V1 &pos, const std::string &instructionText);
    /**
     * @brief 生成位置点位类型的赋值指令(P或者LP)，点位数据由当前点数据填充
     * @param type 输入，点位类型
     * @param pointNo 输入，点位序号
     * @return 点位赋值指令文本(单条)，如果失败则返回空
     */
    std::string genAssignValuesToPtInstruction(const PointType_V1 &type, int pointNo);
    /**
     * @brief 生成全局关节点位类型的赋值指令，点位数据由当前点数据填充
     * @param pos 输入，点位数据
     * @param pointNo 输入，点位序号
     * @return 点位赋值指令文本(单条)，如果失败则返回空
     */
    std::string genAssignValuesToJPtInstruction(int pointNo);

#pragma endregion

};
}  // namespace InoRobBusinessProxy
