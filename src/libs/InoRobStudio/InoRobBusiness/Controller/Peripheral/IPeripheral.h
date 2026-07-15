#pragma once
#include <string>
#include <QObject>
#include "dllspec.h"
#include "DataTypeDef.h"
#include "signal_slot.h"
#include "IndexConfig/IIndexConfig.h"
#include "IRLink/IIRLink.h"

namespace InoRobBusiness
{
#pragma region 枚举

#pragma endregion

/*
    外设
    Create by WuJian at 2023/8/11 创建。
*/
class INOROBBUSINESS_CLASS IPeripheral : public QObject
{
    Q_OBJECT

public:
    virtual ~IPeripheral()
    {
    }
    /*!
     * \brief 初始化
     */
    virtual void init() = 0;
#pragma region 序号配置
    /**
     * @brief 获取工程序号配置操作对象
     */
    virtual IIndexConfig *getProjectIndexConfigObject() = 0;
    /**
     * @brief 获取全局位置点位文件序号配置操作对象
     */
    virtual IIndexConfig *getRPFileIndexConfigObject() = 0;
#pragma endregion

#pragma region IRLink
    /**
     * @brief 获取IRLink对象
     */
    virtual IIRLink *getIRLink() const = 0;
#pragma endregion
};
}  // namespace InoRobBusiness
