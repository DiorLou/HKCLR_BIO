#pragma once

#include <vector>
#include "IVarMonitor.h"
#include "IInoRobBusiness.h"

namespace InoRobBusiness
{
class VarMonitorDefault : public IVarMonitor, public IDataSubscriber
{
    Q_OBJECT

public:
    VarMonitorDefault(IConnection *connnection, IDataSrvBase *dataService, IDataSubscribe *dataSubscribe, ITask *task, ITransfor *transfor);
    ~VarMonitorDefault();

    std::vector<VarMonitorShowData> getVarMonitorShowDatas() const override;
    bool setCurrentTaskId(const int taskId) override;
    bool addVarMonitor(VarMonitorOperateData data) override;
    bool deleteVarMonitor(const unsigned int index) override;
    bool clearVarMonitor(bool isBtnClicked = true) override;
    bool subcribePickupMonitor(const string &fileName, int lineNo) override;
    bool setVarValueInTask(const VAR_SET_INFO &info) override;

private:
    IConnection *_pConnection = nullptr;
    IDataSrvBase *_pDataService = nullptr;
    IDataSubscribe *_pDataSubscribe = nullptr;
    ITask *_pTask = nullptr;
    ITransfor *_pTransfor = nullptr;

    std::vector<VarMonitorOperateData> _datas;   // 变量监控操作数据
    std::vector<VarMonitorShowData> _showDatas;  // 变量监控展示数据

    unsigned short _lastRcMessageSequenceNum = 0;  // 消息打印，上次的顺序码
    bool _isFirstRcMsg = true;                     // 控制器第一次消息

    std::string _lastVMSubscribeData;  // 上次接收到变量监控订阅信息

    int _curTaskId = 0;  // 当前编程调试界面任务ID

    // 接收数据订阅数据（数据订阅者重写）
    void recvSubscribeData(unsigned int id, std::string data) override;

    // 连接状态改变槽函数
    void onConnectionStatusChanged(ControllerConnectionStatus status);

    /**
     * @brief 生成订阅Json并订阅变量监控
     * @param taskId 任务ID
     */
    void generateSubscribeJson(int taskId);

    // 生成Tool变量订阅Json（generateSubscribeJson()调用）
    void generateSubscribeJsonToolVar(const std::string &name, const int index, VarMonitorTaskItem &varMonitorItem, std::vector<VarMonitorShowData> &showDatas, int &subscribeNum);
    // 生成Wobj变量订阅Json（generateSubscribeJson()调用）
    void generateSubscribeJsonWobjVar(const std::string &name, const int index, VarMonitorTaskItem &varMonitorItem, std::vector<VarMonitorShowData> &showDatas, int &subscribeNum);
    // 生成Load变量订阅Json（generateSubscribeJson()调用）
    void generateSubscribeJsonLoadVar(const std::string &name, const int index, VarMonitorTaskItem &varMonitorItem, std::vector<VarMonitorShowData> &showDatas, int &subscribeNum);

    /**
     * @brief 解析变量监控Json
     * @param json 变量监控Json（通过数据订阅接收）
     */
    void parseVarMonitorJson(const VarMonitorJson &json);

    /**
     * @brief 订阅变量监控
     * @param varMonitor变量监控Json
     * @return true成功 false失败
     */
    bool subscribeVarMonitor(const VarMonitorJson &varMonitor);
};
}  // namespace InoRobBusiness
