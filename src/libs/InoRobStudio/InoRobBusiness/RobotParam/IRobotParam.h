#pragma once
#include "dllspec.h"
#include <QObject>
#include "RobotParamRange/IRobotParamRange.h"
#include "GeneralMatch/IGeneralMatch.h"

namespace InoRobBusiness
{
/**
 * @brief 机型参数
 */
class INOROBBUSINESS_CLASS IRobotParam : public QObject
{
    Q_OBJECT

public:
    virtual ~IRobotParam()
    {
    }
    /*!
     * \brief 初始化
     */
    virtual void init() = 0;
    /**
     * @brief 获取通配对象
     */
    virtual IGeneralMatch *getGeneralMatch() const = 0;

    /**
     * @brief 获取机型参数范围对象
     */
    virtual IRobotParamRange *getRobotParamRange() const = 0;
};
}  // namespace InoRobBusiness
