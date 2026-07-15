#pragma once
#include <string>
#include "IInoRobBusiness.h"

namespace InoRobBusiness
{
class INOROBBUSINESS_CLASS RCConfigDefault : public IRCConfig
{
    Q_OBJECT

#pragma region 构造与析构

private:
    // 依赖注入的IdataService，基于老代码与控制器通信
    IDataSrvBase *_pDataService = nullptr;
    // 连接
    IConnection *_pConnection = nullptr;
    // 应用协议对象
    CProtocol _protocol;
    // 监控
    IMonitor *_pMonitor = nullptr;
    // 用户
    IUser *_pUser = nullptr;
    // 工程
    IProject *_pProject = nullptr;

    // 控制器网络连接状态变更信号处理
    void onConnectionStatusChanged(ControllerConnectionStatus status);

public:
    RCConfigDefault(string name, IDataSrvBase *dataService, QObject *parent = nullptr);
    ~RCConfigDefault();
    void init() override;
    // 常用的权限检查
    bool checkCommonPermission() override;

#pragma endregion

#pragma region PF文件

    bool CheckIsAllowPfSave(bool showMsg = false) override;
    bool WaitPfSaveFinish(int64u timeout = 10000) override;
    bool SavePf() override;

#pragma endregion

#pragma region 网络设置

    // 保存网络配置
    int saveEthConfig(ControllerEthCfg &EthCfg) override;

    // 写网络配置
    int WriteEthConfig(ControllerEthCfg &EthCfg);

    // 获取网络配置
    int getEthConfig(ControllerEthCfg &EthCfg) override;

    // 获取当前的总线类型
    int getCurFieldBusType(int &curType) override;

#pragma endregion

#pragma region 通讯服务管理
    // 读取网络配置
    //  nCommonNetStatus  连接信息    // ServerStatus      服务器是否关闭状态；1 是关闭，0 是开启
    int readCommonNetStatusInfo(CommonNetStatus nCommonNetStatus[TCP_MAX_NUM], int8u &ServerState) override;
    //  nCommonNetStatus  连接信息（V4R24C5之前（不包括V4R24C5）的版本）    // ServerStatus      服务器是否关闭状态；1 是关闭，0 是开启
    int readCommonNetStatusInfoOld(CommonNetStatus nCommonNetStatus[TCP_MAX_NUM / 2], int8u &ServerState) override;

    // 网络参数配置
    int writeEthCommonOperation(CommonNetStatus stCommonNetOp) override;

    // 读取视觉应用模式 0，客户端 1 服务器; serverPort:服务器端口号
    int readVisionMode(int16u &VisionMode, int16u &serverPort) override;

    // 设置视觉应用模式 0，客户端 1 服务器
    int SetVisionMode(int16u VisionMode, int16u serverPort);

    // 保存视觉应用模式
    int saveVisionMode(int16u visionMode, int16u serverPort) override;

    // 保存新的端口号
    int saveNewPort(int currPort, int newPort) override;

    // 检查通讯服务管理的操作权限
    bool checkOperatePermission() override;

    // 检查端口号是否合法
    int checkNetPortIsValid(int netPort, std::string tag, std::string &errInfo) override;

    // 检查服务器端口号是否合法
    int checkSerPortIsValid(int netPort, std::string tag, std::string &errInfo) override;
#pragma endregion

#pragma region 系统参数
public:
    // 保存急停触发方式权限检查
    bool checkPermissionBeforeSaveEmgTrigMethod() override;

    // 保存急停触发方式（0-手持示教器触发 1-PC软急停触发）
    int saveEmgTrigMethod(int16u iMethod) override;

    // 读取急停触发方式（0-手持示教器触发 1-PC软急停触发）
    int readEmgTrigMethod(int8u &iMethod) override;

    // 写入急停触发方式（0-手持示教器触发 1-PC软急停触发）
    int WriteEmgTrigMethod(int16u iMethod);

    // 保存急停停机方式权限检查
    bool checkSaveEmgStopModePermission() override;

    // 保存急停停机方式
    int saveEmgStopMode(int8u nMode, int8u nSecondMode) override;

    // 读取急停停机方式(0,0-0类停机； 1,0-1类停机（关节）； 1,1-1类停机（原轨迹）)
    int readEmgStopMode(int8u &nMode, int8u &nSecondMode) override;

    // 写入急停停机方式(0,0-0类停机； 1,0-1类停机（关节）； 1,1-1类停机（原轨迹）)
    int WriteEmgStopMode(int8u nMode, int8u nSecondMode);

    // 保存钥匙触发方式权限检查
    bool checkPermissionBeforeSaveKeyTrigMethod();

    // 保存钥匙触发方式（0-仅示教器权限有效 1-所有控制权均有效）
    int saveKeyTrigMethod(KeyTrigMethod iMethod);

    // 读取钥匙触发方式（0-仅示教器权限有效 1-所有控制权均有效）
    int readKeyTrigMethod(KeyTrigMethod &iMethod);

    // 写入钥匙触发方式（0-仅示教器权限有效 1-所有控制权均有效）
    int WriteKeyTrigMethod(KeyTrigMethod iMethod);

    // 检查控制器保存文件标志
    bool checkFileSaveFlag();

    // 向ARM发送保存文件命令
    void saveFileCommond();

    // 向ARM发送保存文件命令(网络配置)
    void saveFileCommondForEthConfig(bool &isSave);

    // nMark: 1-save, 0-No parameter need save //ARM收到1之后进行保存，完成保存置0, 错误置-1
    int readFileSaveFlag(int &nMark) override;

    // 参数配置文件保存标示
    int writeFileSaveFlag(int nMark) override;

    // 当前运动模式
    int ReadCurMotionMode(int &nMode);

    // 读取参数
    int UnRealReadData(int &nOutput, const int16u nCmdId);
#pragma endregion

#pragma region 串口开关

    // 保存串口设置
    int saveComSwitch(int nMark) override;

    // 读取串口状态
    int readComSwitch(int &nMark) override;

    // 写入串口状态
    int WriteComSwitch(int nMark);

    // 检查串口保存权限
    bool checkComSwitchPermission() override;

#pragma endregion

#pragma region 飞拍IO

    // 保存飞拍IO设置
    int saveFlyShotIO(int16u outIndex) override;

    // 读取飞拍IO设置(14-OUT14；15-OUT15)
    int readFlyShotIO(int16u &outIndex) override;

    // 写入飞拍IO设置(14-OUT14；15-OUT15)
    int WriteFlyShotIO(int16u outIndex);

    // 飞拍IO保存权限检查
    bool checkFlyShotIOSavePermission() override;

#pragma endregion

#pragma region 安全门
    // 安全门停机方式(0,0-0类停机； 1,0-1类停机（关节）； 1,1-1类停机（原轨迹）； 2,0-2类停机停止；3-2类停机暂停)
    int readSafeDoorConifg(int8u &nMode, int8u &nSecondMode) override;

    // 写入安全门的停机方式
    int writeSafeDoorConifg(int8u nMode, int8u nSecondMode);

    // 保存安全门停机方式
    int saveSafeDoorConifg(int8u nMode, int8u nSecondMode) override;

    // 旧安全门配置(nSwitch:0-关，1-开；nMode：0-停止，1-暂停)
    int readSafeDoorCfg(int8u &nSwitch, int8u &nMode) override;

    // 旧安全门配置(nSwitch:0-关，1-开；nMode：0-停止，1-暂停)
    int writeSafeDoorCfg(int8u nSwitch, int8u nMode);

    // 保存旧安全门配置(nSwitch:0-关，1-开；nMode：0-停止，1-暂停)
    int saveSafeDoorCfg(int8u nSwitch, int8u nMode) override;

    // 安全门保存权限检查
    bool checkSafeDoorSavePermission() override;

    // 旧安全门保存权限检查
    bool checkOldSafeDoorSavePermission() override;
#pragma endregion

#pragma region 恢复出厂设置和格式化存储卡
    // 恢复默认值标识
    int writeDefValueMark(int nMark) override;

    int readDefValueMark(int &nMark) override;

    // SD卡格式化, nCmd: 1-格式化,其他值非法(开放参数便于扩展)
    int writeSDFormatCmd(int nCmd = 1) override;

    // 读取格式化状态, nState: 0-无操作, 2-格式化完成
    int readSDFormatState(int &nState) override;

    // 清除历史报警
    int writeHisWarning(int nLineFlg) override;
#pragma endregion

#pragma region 加载点文件
    // 写入.pro以外的文件
    int writeFileOthers(string strFileSrc, string strFileDest) override;

    // 删除文件
    int delFile(string strFileName) override;

    // 检测文件路径、目录合法性
    bool IsPathValid(string strPath);
#pragma endregion

#pragma region 系统备份与加载权限检查
    // 检查配置文件备份与加载权限
    bool checkProfileBackupAndLoadPermission() override;

    // 检查存储卡加载备份
    bool checkCardBackupAndLoadPermission() override;

    // 检查加载点文件权限
    bool checkLoadPointFilePermission() override;

    // 检查恢复出厂设置权限
    bool checkRestoreFactoryiPermission() override;

    // 检查存储卡格式化权限
    bool checkInitialCardPermission() override;

    // 检查控制器USB是否挂载
    bool checkControllerUSBIsConnected() override;

    // 检查系统升级权限
    bool checkUpgradeSystemPermission() override;

    // 检查清除历史报警权限
    bool checkClearHisWarningPermission() override;

#pragma endregion

#pragma region 系统备份与加载到本地
    // 检查状态是否OK
    bool checkSystemIsReadyForBackupConfigFile() override;
    // 导出配置文件到本地
    int exportConfigFileToLocal() override;
    // 导入配置文件到控制器
    int importConfigFileToController() override;
    // 读取导出/导入状态 100进行中 1成功 其他失败
    int checkConfigFileStatus(int &flag) override;
#pragma endregion

#pragma region 自学习振动抑制

private:
    ISelfLearningVibrationSuppression *_pSlvs = nullptr;  // 自学习振动抑制操作对象

public:
    /**
     * @brief 获取自学习振动抑制操作对象
     */
    virtual ISelfLearningVibrationSuppression *getSlvsObject() override;
#pragma endregion

public:
#pragma region 电柜RS485与工具IORS485配置
    // 读末端 485复用模式
    virtual int readCobotToolRs485ReuseMode(std::string &) override;

    // 设置末端 485复用模式
    virtual int writeCobotToolRs485ReuseMode(const std::string &) override;

    // 读电柜 485开启状态
    virtual int readCobotRcRs485State(bool &state) override;

    // 写电柜 485开启状态
    virtual int writeCobotRcRs485State(const bool state) override;

    // 写485配置 末端+电柜
    virtual int writeCobotToolRs485Config(const std::string &) override;

    // 读485配置 末端+电柜
    virtual int readCobotToolRs485Config(std::string &) override;

    // 485调试  末端+电柜
    virtual int writeCobotToolRs485Debugging(int8u *in, int size, std::vector<int8u> &out) override;
#pragma endregion
};
}  // namespace InoRobBusiness
