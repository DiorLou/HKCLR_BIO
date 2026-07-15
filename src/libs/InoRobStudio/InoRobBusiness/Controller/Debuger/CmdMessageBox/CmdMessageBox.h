#pragma once
#include <string>
#include <QObject>
//// #include "dllspec.h"
#include "DataTypeDef.h"
#include "signal_slot.h"
#include "IInoRobBusiness.h"
#include "ICmdMessageBox.h"

using namespace std;

namespace InoRobBusiness
{
class INOROBBUSINESS_CLASS CmdMessageBox : public ICmdMessageBox
{
public:
    // 构造与析构
    CmdMessageBox();
    CmdMessageBox(IDataSrvBase *pDataSrv, IRobotControllerEvents *pEvents);
    ~CmdMessageBox();

    // 获取弹框信息
    virtual int readMessageBoxInfo(int taskId, ICmdMessageBox::MessageBoxInfo &msgBoxInfo) override;

    // 写弹框返回值信息
    virtual int WriteMessageBoxRet(int taskId, int nMessRet) override;

    IDataSrvBase *_pDataService = nullptr;
    IRobotControllerEvents *_pEvents = nullptr;
};
}  // namespace InoRobBusiness
