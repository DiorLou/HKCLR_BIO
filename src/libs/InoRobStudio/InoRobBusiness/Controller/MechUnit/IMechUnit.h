#pragma once
#include <string>
#include <vector>
#include <QObject>
#include "dllspec.h"
#include "DataTypeDef.h"

namespace InoRobBusiness
{
/*
    机械单元：
    1、机械单元为控制器的外部扩展单元
    2、机械单元的类型包括机器人、导轨、变位机、以及后续的其它扩展
*/
class INOROBBUSINESS_CLASS IMechUnit : public QObject
{
    Q_OBJECT

public:
    virtual ~IMechUnit()
    {
    }
    /*!
     * \brief 初始化
     */
    virtual void init() = 0;
    // 激活机械单元
    virtual bool MechUnitActive(std::string name) = 0;

};  // end class
}  // namespace InoRobBusiness
