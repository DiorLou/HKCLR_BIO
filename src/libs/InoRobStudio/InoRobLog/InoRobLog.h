#pragma once
#include "Include/IInoRobLog.h"
#include "Container.h"
#include "Log.h"
#include "InoVersion.h"

namespace InoRobLog
{
class INOROBLOG_CLASS IrLog : public IInoRobLog
{
public:
    IrLog();
    virtual ~IrLog();

    void Print(PRINT_TYPE type, const char *fmt, ...);

private:
    char *_buf;  // 打印或者Log的缓冲Buf，目前最大1024
};

INOROBLOG_CLASS extern CContainer<IrLog> gs_IrLog;  // 声明数据服务模块单例对象
}  // namespace InoRobLog
