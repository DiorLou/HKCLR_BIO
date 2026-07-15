#pragma once
#include <string>
#include <QObject>
#include "dllspec.h"
#include "DataTypeDef.h"
#include "signal_slot.h"
#include "GlobalDataTypes.h"
#include "DataSrvGlobal.h"
#include "SelfLearningVibrationSuppression/ISelfLearningVibrationSuppression.h"
#include "../Control/IControl.h"

namespace InoRobBusiness
{
#pragma region 枚举

#pragma endregion

/*
    控制器配置
    Create by WuJian at 2023/8/3 创建。
*/
class INOROBBUSINESS_CLASS IRCConfig : public QObject
{
    Q_OBJECT

public:
    virtual ~IRCConfig()
    {
    }
    /*!
     * \brief 初始化
     */
    virtual void init() = 0;
    // 常用的权限检查
    virtual bool checkCommonPermission() = 0;

#pragma region PF文件

    // 判断PF是否允许PF保存
    virtual bool CheckIsAllowPfSave(bool showMsg = false) = 0;
    // 等待PF保存完成(超时时间10秒)
    virtual bool WaitPfSaveFinish(int64u timeout = 10000) = 0;
    // 保存Pf文件
    virtual bool SavePf() = 0;

    // 读取文件的保存标志
    virtual int readFileSaveFlag(int &nMark) = 0;

    // 参数配置文件保存标示
    virtual int writeFileSaveFlag(int nMark) = 0;

#pragma endregion

#pragma region 网络设置

    // 保存网络配置
    virtual int saveEthConfig(ControllerEthCfg &EthCfg) = 0;

    // 获取网络IP
    virtual int getEthConfig(ControllerEthCfg &EthCfg) = 0;

    // 获取当前的总线类型
    virtual int getCurFieldBusType(int &curType) = 0;

#pragma endregion

#pragma region 通讯服务管理
    // 读取网络配置
    virtual int readCommonNetStatusInfo(CommonNetStatus nCommonNetStatus[TCP_MAX_NUM], int8u &ServerState) = 0;
    // 读取网络配置（V4R24C5之前（不包括V4R24C5）的版本）
    virtual int readCommonNetStatusInfoOld(CommonNetStatus nCommonNetStatus[TCP_MAX_NUM / 2], int8u &ServerState) = 0;

    // 网络参数配置
    virtual int writeEthCommonOperation(CommonNetStatus stCommonNetOp) = 0;

    // 读取视觉应用模式 0，客户端 1 服务器; serverPort:服务器端口号
    virtual int readVisionMode(int16u &VisionMode, int16u &serverPort) = 0;

    // 保存视觉应用模式, 0-客户端,1-服务器
    virtual int saveVisionMode(int16u visionMode, int16u serverPort) = 0;

    // 保存新的端口号
    virtual int saveNewPort(int currPort, int newPort) = 0;

    // 检查通讯服务管理的操作权限
    virtual bool checkOperatePermission() = 0;

    /**
     * @brief 检查端口号是否合法
     * @param netPort 端口号
     * @param tag 服务器or客户端
     * @param errInfo 返回的错误信息
     * @return 0-合法，1-不合法
     */
    virtual int checkNetPortIsValid(int netPort, std::string tag, std::string &errInfo) = 0;
    // 检查通讯服务管理的服务器端口号
    virtual int checkSerPortIsValid(int netPort, std::string tag, std::string &errInfo) = 0;
#pragma endregion

#pragma region 系统参数
    // 读取急停触发方式（0-手持示教器触发 1-PC软急停触发）
    virtual int readEmgTrigMethod(int8u &iMethod) = 0;

    // 保存急停触发方式（0-手持示教器触发 1-PC软急停触发）
    virtual int saveEmgTrigMethod(int16u iMethod) = 0;

    // 保存急停触发方式权限检查
    virtual bool checkPermissionBeforeSaveEmgTrigMethod() = 0;

    // 读取钥匙触发方式（0-本地生效 1-永久生效）
    virtual int readKeyTrigMethod(KeyTrigMethod &iMethod) = 0;

    // 保存钥匙触发方式（0-本地生效 1-永久生效）
    virtual int saveKeyTrigMethod(KeyTrigMethod iMethod) = 0;

    // 保存钥匙触发方式权限检查
    virtual bool checkPermissionBeforeSaveKeyTrigMethod() = 0;

    // 保存急停停机方式(0,0-0类停机； 1,0-1类停机（关节）； 1,1-1类停机（原轨迹）)
    virtual int saveEmgStopMode(int8u nMode, int8u nSecondMode) = 0;

    // 读取急停停机方式(0,0-0类停机； 1,0-1类停机（关节）； 1,1-1类停机（原轨迹）)
    virtual int readEmgStopMode(int8u &nMode, int8u &nSecondMode) = 0;

    // 保存急停停机方式权限检查
    virtual bool checkSaveEmgStopModePermission() = 0;
#pragma endregion

#pragma region 串口开关

    // 保存串口设置
    virtual int saveComSwitch(int nMark) = 0;

    // 读取串口状态
    virtual int readComSwitch(int &nMark) = 0;

    // 检查串口保存权限
    virtual bool checkComSwitchPermission() = 0;

#pragma endregion

#pragma region 飞拍IO

    // 保存飞拍IO设置(14-OUT14；15-OUT15)
    virtual int saveFlyShotIO(int16u outIndex) = 0;

    // 读取飞拍IO设置(14-OUT14；15-OUT15)
    virtual int readFlyShotIO(int16u &outIndex) = 0;

    // 飞拍IO保存权限检查
    virtual bool checkFlyShotIOSavePermission() = 0;

#pragma endregion

#pragma region 安全门
    // 安全门停机方式(0,0-0类停机； 1,0-1类停机（关节）； 1,1-1类停机（原轨迹）； 2,0-2类停机停止；3-2类停机暂停)
    // 读取安全门停机方式
    virtual int readSafeDoorConifg(int8u &nMode, int8u &nSecondMode) = 0;

    // 保存安全门停机方式
    virtual int saveSafeDoorConifg(int8u nMode, int8u nSecondMode) = 0;

    // 旧安全门配置(nSwitch:0-关，1-开；nMode：0-停止，1-暂停)
    virtual int readSafeDoorCfg(int8u &nSwitch, int8u &nMode) = 0;

    // 保存旧安全门配置(nSwitch:0-关，1-开；nMode：0-停止，1-暂停)
    virtual int saveSafeDoorCfg(int8u nSwitch, int8u nMode) = 0;

    // 安全门保存权限检查
    virtual bool checkSafeDoorSavePermission() = 0;

    // 旧安全门保存权限检查
    virtual bool checkOldSafeDoorSavePermission() = 0;
#pragma endregion

#pragma region 恢复出厂设置和格式化存储卡
    // 恢复默认值标识
    // 发送命令
    virtual int writeDefValueMark(int nMark) = 0;

    // 读取状态
    virtual int readDefValueMark(int &nMark) = 0;

    // SD卡格式化, nCmd: 1-格式化,其他值非法(开放参数便于扩展)
    virtual int writeSDFormatCmd(int nCmd = 1) = 0;

    // 读取格式化状态, nState: 0-无操作, 2-格式化完成
    virtual int readSDFormatState(int &nState) = 0;

    // 清除历史报警
    virtual int writeHisWarning(int nLineFlg) = 0;
#pragma endregion

#pragma region 加载点文件
    // 写入.pro以外的文件
    virtual int writeFileOthers(string strFileSrc, string strFileDest) = 0;

    // 删除文件
    virtual int delFile(string strFileName) = 0;
#pragma endregion

#pragma region 系统备份与加载权限检查
    // 检查配置文件备份与加载权限
    virtual bool checkProfileBackupAndLoadPermission() = 0;

    // 检查存储卡加载备份
    virtual bool checkCardBackupAndLoadPermission() = 0;

    // 检查加载点文件权限
    virtual bool checkLoadPointFilePermission() = 0;

    // 检查恢复出厂设置权限
    virtual bool checkRestoreFactoryiPermission() = 0;

    // 检查存储卡格式化权限
    virtual bool checkInitialCardPermission() = 0;

    // 检查系统升级权限
    virtual bool checkUpgradeSystemPermission() = 0;

    // 检查清除历史报警权限
    virtual bool checkClearHisWarningPermission() = 0;

    // 检查控制器USB是否挂载
    virtual bool checkControllerUSBIsConnected() = 0;
#pragma endregion

#pragma region 自学习振动抑制
    /**
     * @brief 获取自学习振动抑制操作对象
     */
    virtual ISelfLearningVibrationSuppression *getSlvsObject() = 0;
#pragma endregion

#pragma region 电柜RS485与工具IORS485配置
    //读末端 485复用模式
    virtual int readCobotToolRs485ReuseMode(std::string &) = 0;

    //设置末端 485复用模式
    virtual int writeCobotToolRs485ReuseMode(const std::string &) = 0;

    //读电柜 485开启状态
    virtual int readCobotRcRs485State(bool &state) = 0;

    //写电柜 485开启状态
    virtual int writeCobotRcRs485State(const bool state) = 0;

    //写485配置 末端+电柜
    virtual int writeCobotToolRs485Config(const std::string &) = 0;

    //读485配置 末端+电柜
    virtual int readCobotToolRs485Config(std::string &) = 0;

    //485调试  末端+电柜
    virtual int writeCobotToolRs485Debugging(int8u* in, int size, std::vector<int8u> &out) = 0;
#pragma endregion

#pragma region 配置文件备份到本地/从本地加载配置文件到控制器
    //检查状态是否OK
    virtual bool checkSystemIsReadyForBackupConfigFile() = 0;
    //导出配置文件到本地
    virtual int exportConfigFileToLocal() = 0;
    //导入配置文件到控制器
    virtual int importConfigFileToController() = 0;
    //读取导出/导入状态 100进行中 1成功 其他失败
    virtual int checkConfigFileStatus(int &flag) = 0;
#pragma endregion
};
}  // namespace InoRobBusiness
