#pragma once
#include <string>
#include <QObject>
#include "dllspec.h"
#include "DataTypeDef.h"
#include "signal_slot.h"

namespace InoRobBusiness
{
/*
    脚本化编程
    Create by xiongriwei at 2023/11/2
*/
class INOROBBUSINESS_CLASS IScriptExtension : public QObject
{
    Q_OBJECT

public:
    virtual ~IScriptExtension() {}
    /*!
     * \brief 初始化
     */
    virtual void init() = 0;
    // 开始
    virtual bool Start() = 0;
    // 暂停
    virtual bool Pause() = 0;
    // 暂停
    virtual bool Step() = 0;
    // 终止
    virtual bool Abort() = 0;
    // 块单步
#if (defined(_WIN32) && defined(__GNUC__)) || defined(__ANDROID__)
    virtual bool StepBlock() = 0;
#endif // 协作示教器平台
};

}  // namespace InoRobBusiness