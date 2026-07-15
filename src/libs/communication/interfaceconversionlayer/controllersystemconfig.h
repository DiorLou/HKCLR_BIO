#pragma once

#include "communication_global.h"
#include "metatype.h"

namespace InoRobBusiness
{
class IController;
}

class Communication;
class AbstractCmd;

namespace Internal
{
class ControllerSystemConfigPrivate;
}

class COMMUNICATION_EXPORT ControllerSystemConfig
{
public:
    ControllerSystemConfig();
    ~ControllerSystemConfig();

    virtual Communication *comm() = 0;
    virtual InoRobBusiness::IController *controller() = 0;

    // 保存网络配置
    int saveEthConfig(const InoControllerEthCfg &EthCfg);

    // 获取网络IP
    void getEthConfig(AbstractCmd *cmd);

    // 读取网络配置
    int readCommonNetStatusInfo(QList<InoCommonNetStatus> &data,
                                unsigned char &serverState);

    // 网络参数配置
    void writeEthCommonOperation(AbstractCmd *cmd);

    // 读取视觉应用模式 0，客户端 1 服务器; serverPort:服务器端口号
    int readVisionMode(unsigned short &VisionMode, unsigned short &serverPort);

    // 保存视觉应用模式, 0-客户端,1-服务器
    int saveVisionMode(unsigned short visionMode, unsigned short port);

    // 保存新的端口号
    void saveNewPort(AbstractCmd *cmd);

    // 获取版本信息
    void getVersionInfo(AbstractCmd *);

    // 是否需要本地时间同步到控制器
    void isNeedTimeSynToController();
    // 写控制器时间
    void setControllerTime(AbstractCmd *cmd);

    // 删除文件夹
    int delDir(const std::string &dir);
    // 创建文件夹
    int createDir(const std::string &dir);

    // 系统升级
    int systemUpgrade(bool isUpdateBsp = true);
    // 读取系统升级过程信息
    int readSystemUpdateInfo(CobotSystemUpdateInfo &info);

    // void readToolReuseModel(AbstractCmd *cmd);
    void readRs485Config(AbstractCmd *cmd);

    void writeToolReuseModel(AbstractCmd *cmd);
    void writeRs485Config(AbstractCmd *cmd);
    void writeRs485Debugging(AbstractCmd *cmd);


    void startRestoreFactory(AbstractCmd *cmd);
    void readRestoreFactoryState(AbstractCmd *cmd);

    void startConfigFilesStateToUsb(AbstractCmd *cmd);
    void readConfigFilesBackupStateToUsb(AbstractCmd *cmd);

    void startLoadConfigFilesFromUsb(AbstractCmd *cmd);
    void readLoadConfigFilesStateFromUsb(AbstractCmd *cmd);

    void startExportConfigFileToLocal(AbstractCmd *cmd);
    void startImportConfigFileFromLocal(AbstractCmd *cmd);
    void readExportConfigFileOperateStatusToLocal(AbstractCmd *cmd);
    void readImportConfigFileOperateStatusFromLocal(AbstractCmd *cmd);

    void setModelLayerLanguage(AbstractCmd *cmd);
    void setControllerLanguage(AbstractCmd *cmd);

    void importLanguagePackageForController(AbstractCmd *cmd);
    void importLanguagePackageFromLocal(AbstractCmd *cmd);
    void importLanguagePackageFromController(AbstractCmd *cmd);
    
    int autoRecordPoint(int status);
    int getFirstBootStatus(bool &status);

private:
    Internal::ControllerSystemConfigPrivate *d;
    friend class Internal::ControllerSystemConfigPrivate;
};
