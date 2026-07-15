#pragma once
#include <string>
#include "DataTypeDef.h"
#include <QObject>

namespace InoRobBusiness
{
class INOROBBUSINESS_CLASS ITrajectoryRecovery : public QObject
{
    Q_OBJECT

public:
    virtual ~ITrajectoryRecovery(){}
    /*!
     * \brief 初始化
     */
    virtual void init() = 0;
    // 写入轨迹恢复阈值设置参数
    virtual int WriteTrajRecoveryParam(TrajRecoveryParam &param) = 0;
    // 读取轨迹恢复阈值设置参数
    virtual int ReadTrajRecoveryParam(TrajRecoveryParam &param) = 0; 
    // 权限保存检查
    virtual bool checkSavePermission() = 0;
    // 检查操作权限
    virtual bool checkOperationPermission(bool isTip) = 0;
};
}  // namespace InoRobBusiness
