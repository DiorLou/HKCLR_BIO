#pragma once
#include <string>
#include "dllspec.h"
#include "DataTypeDef.h"
#include "signal_slot.h"

namespace InoRobBusiness
{
class INOROBBUSINESS_CLASS ICmdMessageBox
{
public:
    // MessageBox弹框信息
    typedef struct _MessageBoxInfo_
    {
        _MessageBoxInfo_()
        {
            taskid = 0;
            memset(caption, 0, sizeof(caption));
            memset(content, 0, sizeof(content));
            btnType = 0;
        }

        int taskid;
        char caption[32];
        char content[256];
        int btnType;
    } MessageBoxInfo;

    virtual ~ICmdMessageBox()
    {
    }

    // 获取弹框信息
    virtual int readMessageBoxInfo(int taskId, ICmdMessageBox::MessageBoxInfo &msgBoxInfo) = 0;

    // 写弹框返回值信息
    virtual int WriteMessageBoxRet(int taskId, int nMessRet) = 0;
};
}  // namespace InoRobBusiness
