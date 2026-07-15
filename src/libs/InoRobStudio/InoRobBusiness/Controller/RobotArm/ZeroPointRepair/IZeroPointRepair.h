#pragma once
#include <QObject>
#include "dllspec.h"
#include "DataTypeDef.h"
#include "DataSrvGlobal.h"

namespace InoRobBusiness
{
// 零点恢复标定方法
enum ZeroPointRepairCalibMethod
{
    P8_POINT_METHOD = 0,   // 8点法
    P15_POINT_METHOD = 1,  // 15点法
};

typedef struct _ZeroPointRepairCalibMethodItem_
{
    ZeroPointRepairCalibMethod calibMethod;
    string ItemName;
} ZeroPointRepairCalibMethodItem;

/*!
 * \brief  零点修复参数抽象类, 机械臂下的子类
 */
class INOROBBUSINESS_CLASS IZeroPointRepair : public QObject
{
    Q_OBJECT

public:
    virtual ~IZeroPointRepair(){};

    /// <summary>
    /// 标定方法名称查询
    /// </summary>
    /// <param name="method">标定方法枚举</param>
    /// <returns>标定方法名称</returns>
    virtual string CalibMethodNameSearch(ZeroPointRepairCalibMethod method) = 0;

    /// <summary>
    /// 获取零点修复标定数据（从文件中获取）
    /// </summary>
    /// <param name="zeroPointRepairCalibData">零点修复标定所有数据</param>
    /// <returns>是否成功</returns>
    virtual bool RefreshCalibData(ZeroPointRepairCalibData &zeroPointRepairCalibData) = 0;

    /// <summary>
    /// 从文件中解析出标定数据
    /// </summary>
    /// <returns>是否成功</returns>
    virtual bool ReadCalibDataFromFile() = 0;

    /// <summary>
    /// 保存标定数据
    /// </summary>
    /// <param name="result">标定数据</param>
    /// <returns>是否成功</returns>
    virtual bool SaveCalibData(ZeroPointRepairCalibData &result) = 0;

    /// <summary>
    /// 写标定数据到文件
    /// </summary>
    /// <returns>是否成功</returns>
    virtual bool WriteCalibDataToFile() = 0;

    /// <summary>
    /// 零点修复标定计算
    /// </summary>
    /// <param name="calibItem">标定数据</param>
    /// <param name="calibResult">标定结果</param>
    /// <returns>标定成功返回true</returns>
    virtual bool ZeroPointRepairCalib(ZeroPointRepairCalibItem calibItem, ZeroPointRepairCalibResult &calibResult) = 0;

    /// <summary>
    /// 获取零点标定页面是否可见
    /// </summary>
    /// <returns>可见返回true,不可见返回false</returns>
    virtual bool ZeroPointRepairCanVisible() = 0;
};

}  // namespace InoRobBusiness
