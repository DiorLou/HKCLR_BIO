/**
 * @File Name: toolcalibrateinterface.h
 * @brief  : Tool Calibrate Interface For GUI
 * @Author : yangchao email:yangchaoD@inovance.com
 * @Version : 1.0
 * @Creat Date : 2024-02-27
 *
 * @Copyright (C), 2023-2024 inovance. Co., Ltd. All rights
 */
#pragma once

#include "communication_global.h"
#include "toolparams.h"

namespace InoRobBusiness
{
class IController;
}  // namespace InoRobBusiness

class Communication;

/// @brief 负载辨识接口类
class COMMUNICATION_EXPORT LoadInterface
{
public:
    LoadInterface()
    {
    }

    virtual Communication *comm() = 0;
    virtual InoRobBusiness::IController *controller() = 0;

    /**
     * @brief  : 获取负载总数量
     * @return quint16: 负载总数量
     */
    quint16 GetLoadCount();

    /**
     * @brief  : 获取负载参数
     * @param  loadNo: 负载号
     * @param  loadParam: 输出参数，负载参数
     * @return true: 操作成功
     * @return false: 操作失败
     */
    bool GetLoadParam(quint16 loadNo, LoadParams &loadParam);

    /**
     * @brief  : 设置负载参数
     * @param  loadNo: 负载号
     * @param  loadParam: 负载参数
     * @return true: 操作成功
     * @return false: 操作失败
     */
    bool SetLoadParam(quint16 loadNo, const LoadParams &loadParam);

    /**
     * @brief  : 负载参数保存
     * @param  loadId: 负载号
     * @param  params: 负载参数
     * @return true: 操作成功
     * @return false: 操作失败
     */
    bool LoadSave(quint16 loadId, const LoadParams &params, bool bSaveNeed = false);

    /**
     * @brief  : 刷新负载参数
     * @param  loadId: 负载号
     * @param  params: 负载参数
     * @return true: 操作成功
     * @return false: 操作失败
     */
    bool LoadRefresh(quint16 loadId, LoadParams &params);

    /**
     * @brief  : 负载参数清零
     * @param  loadId: 负载号
     * @return true: 操作成功
     * @return false: 操作失败
     */
    bool LoadClear(quint16 loadId);

    /**
     * @brief  : 获取负载最小质量
     * @return double: 负载最小质量
     */
    double GetMinMass();

    /**
     * @brief  : 获取负载最大质量
     * @return double: 负载最大质量
     */
    double GetMaxMass();

    /**
     * @brief  : 获取负载最小质心
     * @return double: 负载最小质心
     */
    double GetMinCentroid();

    /**
     * @brief  : 获取负载最大质心
     * @return double: 负载最大质心
     */
    double GetMaxCentroid();

    /**
     * @brief  : 获取负载最小转动惯量
     * @return double: 负载最小转动惯量
     */
    double GetMinInertia();

    /**
     * @brief  : 获取负载最大转动惯量
     * @return double: 负载最大转动惯量
     */
    double GetMaxInertia();

    /**
     * @brief  : 检查负载参数是否有效
     * @param  params: 负载参数
     * @return true: 操作成功
     * @return false: 操作失败
     */
    bool CheckCurLoadValid(const LoadParams &params);

    /**
     * @brief  : 根据负载号查找对应的负载名称
     * @param  loadId: 负载号
     * @return QString: 负载名称
     */
    QString LoadIDNameSearch(quint16 loadId);
};

/// @brief 工具标定接口类
class COMMUNICATION_EXPORT ToolCalibrateInterface
{
public:
    ToolCalibrateInterface()
    {
    }

    virtual Communication *comm() = 0;
    virtual InoRobBusiness::IController *controller() = 0;

    /**
     * @brief  : 设置当前标定的工具ID号
     * @param  currentId: 工具ID号
     * @return true: 操作成功
     * @return false: 操作失败
     */
    bool SetCurrentId(quint16 currentId);

    /**
     * @brief  : 该标定工具是否被夹持
     * @param  result: 输出参数，true-被夹持 false-非夹持
     * @return true: 操作成功
     * @return false: 操作失败
     */
    bool CurrentIsRobotHold(bool &result);

    /**
     * @brief  : 获取所有可标定工具名列表
     * @param  vecItems: 输出参数，可标定工具名列表
     */
    void GetToolItem(QVector<QString> &vecItems);

    /**
     * @brief  : 获取工具参数
     * @param  toolNo: 工具ID号
     * @param  toolParam: 输出参数，返回获取到的工具详细参数结构体
     * @return true: 操作成功
     * @return false: 操作失败
     */
    bool GetToolParam(quint16 toolNo, ToolParams &toolParam);

    /**
     * @brief  : 设置工具参数
     * @param  toolNo: 工具ID号
     * @param  toolParam: 需要设置到控制器的工具参数结构体
     * @return true: 操作成功
     * @return false: 操作失败
     */
    bool SetToolParam(quint16 toolNo, const ToolParams &toolParam);

    /**
     * @brief  : 将工具参数保存到控制器
     * @param  toolNo: 工具ID号
     * @param  toolParam: 工具参数
     * @return true: 操作成功
     * @return false: 操作失败
     */
    bool Save(int toolNo, ToolParams *toolParam, bool bSaveNeed = false);

    /**
     * @brief  : 从控制器取出工具参数刷新界面
     * @param  toolNo: 工具ID号
     * @param  toolParam: 输出参数，工具参数指针
     * @return true: 操作成功
     * @return false: 操作失败
     */
    bool Refresh(int toolNo, ToolParams *toolParam);

    /**
     * @brief  : 清零控制器已设置的工具参数
     * @param  toolNo: 需要清空已设置的工具参数的工具ID号
     * @return true: 操作成功
     * @return false: 操作失败
     */
    bool Clear(int toolNo);

    /**
     * @brief  : 根据工具ID号获取工具名称
     * @param  id: 工具ID号
     * @return QString: 工具名称
     */
    QString ToolIdNameSearch(quint16 id);

    /**
     * @brief  : 根据工具类型获取工具可用的标定方法
     * @param  type: 工具类型
     * @param  vecMethods: 输出参数，工具可用的标定方法名
     */
    void HoldTypeCalibMethodSearch(Robot_ToolType type,
                                   QVector<QString> &vecMethods);

    /**
     * @brief  : 根据标定方法索引获取标定方法名称
     * @param  method: 标定方法索引
     * @return QString: 工具方法名称
     */
    QString CalibMethodNameSearch(Robot_ToolCalibrateType method);

    /**
     * @brief  : 工具标定
     * @param  midPos: 工具标定中间点
     * @param  calResultPos: 输出参数，工具标定结果位置信息
     * @param  calResultOri: 输出参数，工具标定结果姿态信息
     * @return true: 操作成功
     * @return false: 操作失败
     */
    bool Calibrate(const CalibratePoints &midPos, Pos &calResultPos,
                   Ori &calResultOri);

    /**
     * @brief  : 保存工具标定中间点信息
     * @param  toolNo: 工具ID号
     * @param  point: 工具标定中间点信息结构
     * @return true: 操作成功
     * @return false: 操作失败
     */
    bool SaveCalibratePoints(quint16 toolNo, const CalibratePoints &point);

    /**
     * @brief  : 从控制器取出工具标定中间点信息刷新界面
     * @param  toolNo: 工具ID号
     * @param  points: 输出参数，工具标定中间点
     * @return true: 操作成功
     * @return false: 操作失败
     */
    bool RefreshCalibratePoints(quint16 toolNo, CalibratePoints &points);

    /**
     * @brief  : 运动到点
     * @param  method: 工具标定方法
     * @param  pos: 目标点位置信息
     * @param  ori: 目标点姿态信息
     * @param  type: 运动方式
     * @return true: 操作成功
     * @return false: 操作失败
     */
    bool MoveToPoint(Robot_ToolCalibrateType method, const Pos &pos,
                     const Ori &ori, Robot_MoveType type);

    /**
     * @brief  : 根据运动方式索引获取运动方式名称
     * @param  type: 运动方式索引
     * @return QString: 运动方式名称
     */
    QString ToolExcuteMoveTypeNameSearch(Robot_MoveType type);

    /**
     * @brief  : 获取标定中间点点名称
     * @param  method: 工具标定方法
     * @param  vecPointsName: 输出参数，中间点点名称列表
     */
    void ToolPointsNameQuery(Robot_ToolCalibrateType method,
                             QVector<QString> &vecPointsName);

    /**
     * @brief  : 根据标定名称获取标定方法索引
     * @param  name: 标定名称
     * @return int: 标定方法索引
     */
    int CalibMethodByName(const QString &name);

    // 界面提示查询
    std::string ToolCalibrateTipSearch(Robot_ToolCalibrateType method);
};
