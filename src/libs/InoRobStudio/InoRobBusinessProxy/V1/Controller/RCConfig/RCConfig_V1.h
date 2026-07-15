#pragma once
#include "dllspec.h"
#include "IInoRobBusiness.h"
#include "SelfLearningVibrationSuppression/SelfLearningVibrationSuppression_V1.h"
#include "../../DataService/DataSrvGlobal_V1.h"
#include "../../InoRobUtil/CommonEnum_V1.h"
using namespace InoRobBusiness;

namespace InoRobBusinessProxy
{
class INOROBBUSINESSPROXY_CLASS RCConfig_V1
{
#pragma region 构造与析构

private:
    IRCConfig *_rcConfig = nullptr;

public:
    RCConfig_V1(IRCConfig *rcConfig);
    ~RCConfig_V1();

#pragma endregion

#pragma region 子模型

private:
    SelfLearningVibrationSuppression_V1 *_selfLearningVibrationSuppression_V1 = nullptr;

public:
    SelfLearningVibrationSuppression_V1 *GetSelfLearningVibrationSuppression();
    bool SetSelfLearningVibrationSuppression(SelfLearningVibrationSuppression_V1 *selfLearningVibrationSuppression_V1);

#pragma endregion

public:
    // 常用的权限检查
    bool checkCommonPermission();

#pragma region PF文件

    // 判断PF是否允许PF保存
    bool CheckIsAllowPfSave(bool showMsg = false);
    // 等待PF保存完成(超时时间10秒)
    bool WaitPfSaveFinish(int64u timeout = 10000);
    // 保存Pf文件
    bool SavePf();

    // 读取文件的保存标志
    int readFileSaveFlag(int &nMark);

    // 参数配置文件保存标示
    int writeFileSaveFlag(int nMark);

#pragma endregion

#pragma region 网络设置

    // 保存网络配置
    int saveEthConfig(ControllerEthCfg_V1 &EthCfg);

    // 获取网络IP
    int getEthConfig(ControllerEthCfg_V1 &EthCfg);

    // 获取当前的总线类型
    int getCurFieldBusType(int &curType);

#pragma endregion

#pragma region 通讯服务管理

    // 读取网络配置
    int readCommonNetStatusInfo(CommonNetStatus_V1 nCommonNetStatus[TCP_MAX_NUM_V1], int8u &ServerState);

    // 网络参数配置
    int writeEthCommonOperation(CommonNetStatus_V1 stCommonNetOp);

    // 读取视觉应用模式 0，客户端 1 服务器; serverPort:服务器端口号
    int readVisionMode(int16u &VisionMode, int16u &serverPort);

    // 保存视觉应用模式, 0-客户端,1-服务器
    int saveVisionMode(int16u visionMode);

    // 保存新的端口号
    int saveNewPort(int currPort, int newPort);

    // 检查通讯服务管理的操作权限
    bool checkOperatePermission();

    /**
     * @brief 检查端口号是否合法
     * @param netPort 端口号
     * @param tag 服务器or客户端
     * @param errInfo 返回的错误信息
     * @return 0-合法，1-不合法
     */
    int checkNetPortIsValid(int netPort, std::string tag, std::string &errInfo);

#pragma endregion

#pragma region 系统参数

    // 读取急停触发方式（0-手持示教器触发 1-PC软急停触发）
    int readEmgTrigMethod(int8u &iMethod);

    // 保存急停触发方式（0-手持示教器触发 1-PC软急停触发）
    int saveEmgTrigMethod(int16u iMethod);

    // 保存急停触发方式权限检查
    bool checkPermissionBeforeSaveEmgTrigMethod();

    // 保存急停停机方式(0,0-0类停机； 1,0-1类停机（关节）； 1,1-1类停机（原轨迹）)
    int saveEmgStopMode(int8u nMode, int8u nSecondMode);

    // 读取急停停机方式(0,0-0类停机； 1,0-1类停机（关节）； 1,1-1类停机（原轨迹）)
    int readEmgStopMode(int8u &nMode, int8u &nSecondMode);

    // 保存急停停机方式权限检查
    bool checkSaveEmgStopModePermission();

#pragma endregion

#pragma region 串口开关

    // 保存串口设置
    int saveComSwitch(int nMark);

    // 读取串口状态
    int readComSwitch(int &nMark);

    // 检查串口保存权限
    bool checkComSwitchPermission();

#pragma endregion

#pragma region 飞拍IO

    // 保存飞拍IO设置(14-OUT14；15-OUT15)
    int saveFlyShotIO(int16u outIndex);

    // 读取飞拍IO设置(14-OUT14；15-OUT15)
    int readFlyShotIO(int16u &outIndex);

    // 飞拍IO保存权限检查
    bool checkFlyShotIOSavePermission();

#pragma endregion

#pragma region 安全门

    // 安全门停机方式(0,0-0类停机； 1,0-1类停机（关节）； 1,1-1类停机（原轨迹）； 2,0-2类停机停止；3-2类停机暂停)
    // 读取安全门停机方式
    int readSafeDoorConifg(int8u &nMode, int8u &nSecondMode);

    // 保存安全门停机方式
    int saveSafeDoorConifg(int8u nMode, int8u nSecondMode);

    // 旧安全门配置(nSwitch:0-关，1-开；nMode：0-停止，1-暂停)
    int readSafeDoorCfg(int8u &nSwitch, int8u &nMode);

    // 保存旧安全门配置(nSwitch:0-关，1-开；nMode：0-停止，1-暂停)
    int saveSafeDoorCfg(int8u nSwitch, int8u nMode);

    // 安全门保存权限检查
    bool checkSafeDoorSavePermission();

    // 旧安全门保存权限检查
    bool checkOldSafeDoorSavePermission();

#pragma endregion

#pragma region 恢复出厂设置和格式化存储卡

    // 恢复默认值标识
    // 发送命令
    int writeDefValueMark(int nMark);

    // 读取状态
    int readDefValueMark(int &nMark);

    // SD卡格式化, nCmd: 1-格式化,其他值非法(开放参数便于扩展)
    int writeSDFormatCmd(int nCmd = 1);

    // 读取格式化状态, nState: 0-无操作, 2-格式化完成
    int readSDFormatState(int &nState);

    // 清除历史报警
    int writeHisWarning(int nLineFlg);

#pragma endregion

#pragma region 加载点文件

    // 写入.pro以外的文件
    int writeFileOthers(string strFileSrc, string strFileDest);

    // 删除文件
    int delFile(string strFileName);

#pragma endregion

#pragma region 系统备份与加载权限检查

    // 检查配置文件备份与加载权限
    bool checkProfileBackupAndLoadPermission();

    // 检查存储卡加载备份
    bool checkCardBackupAndLoadPermission();

    // 检查加载点文件权限
    bool checkLoadPointFilePermission();

    // 检查恢复出厂设置权限
    bool checkRestoreFactoryiPermission();

    // 检查存储卡格式化权限
    bool checkInitialCardPermission();

    // 检查系统升级权限
    bool checkUpgradeSystemPermission();

    // 检查清除历史报警权限
    bool checkClearHisWarningPermission();

#pragma endregion

#pragma region 电柜RS485与工具IORS485配置

    // 读末端 485复用模式
    int readCobotToolRs485ReuseMode(std::string &data);

    // 设置末端 485复用模式
    int writeCobotToolRs485ReuseMode(const std::string &data);

    // 读电柜 485开启状态
    int readCobotRcRs485State(bool &state);

    // 写电柜 485开启状态
    int writeCobotRcRs485State(const bool state);

    // 写485配置 末端+电柜
    int writeCobotToolRs485Config(const std::string &data);

    // 读485配置 末端+电柜
    int readCobotToolRs485Config(std::string &data);

    // 485调试  末端+电柜
    int writeCobotToolRs485Debugging(int8u *in, int size, std::vector<int8u> &out);

#pragma endregion
};
}  // namespace InoRobBusinessProxy
