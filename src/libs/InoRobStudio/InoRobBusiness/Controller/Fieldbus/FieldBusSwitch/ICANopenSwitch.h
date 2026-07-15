/****************************************************************
 * File Descrip : 总线开关
 * Author       : mzw
 ****************************************************************/
#pragma once
#include <QObject>
#include <string>
#include "dllspec.h"
#include "DataTypeDef.h"
#include "signal_slot.h"
#include "GlobalDataTypes.h"
#include "DataSrvGlobal.h"

namespace InoRobBusiness
{
/**
 * @brief CANopen基类
 */
class INOROBBUSINESS_CLASS ICANopenSwitch : public QObject
{
    Q_OBJECT
public:
    virtual ~ICANopenSwitch()
    {
    }

    /**
     * @brief 将CANopen配置文件放入控制器中
     * @param filePath 即将导入的配置文件的完整路径
     * @param fileName 即将导入的配置文件的文件名称
     * @return
     */
    virtual int putCANopenFileIntoController(const std::string &filePath, const std::string &fileName) = 0;

    /**
     * @brief 检查CANopen总线操作权限
     * @return true-权限符合
     */
    virtual bool checkCANopenOperatePermission() = 0;
};
}  // namespace InoRobBusiness
