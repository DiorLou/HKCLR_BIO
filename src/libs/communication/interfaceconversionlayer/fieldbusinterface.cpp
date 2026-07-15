#include "fieldbusinterface.h"

#include <QDebug>
#include "IController.h"
#include "InoRobBusiness/Include/GlobalDataTypes.h"
#include "GlobalDataService/DataService/DataSrvGlobal.h"
#include "communicationengine.h"
#include "communicationtr.h"
#include "InoRobBusiness/Controller/Fieldbus/FieldBusSwitch/IEtherCATSwitch.h"
#include "InoRobBusiness/Controller/Peripheral/IndexConfig/IIndexConfig.h"
#include "InoRobBusiness/Controller/Peripheral/IPeripheral.h"
#include "Workstation/WorkstationDefault.h"
#include "cobotlog.h"
#include "modulesutils.h"
bool FieldBusInterface::checkOtherFieldBusIsActive(int currFieldBus)
{
    return _IFieldBus->checkOtherFieldBusIsActive(
        static_cast<InoRobBusiness::FieldBusType>(currFieldBus));
}

void FieldBusInterface::getAddressAssignMsg(AbstractCmd *cmd)
{
    int fieldBusType;
    FIELDBUS_MEM_ASSIGN_CONFIG configTemp;
    ModbusConnectSts modbusSts;
    int ret1 = _IFieldBus->getCurFieldBusType(fieldBusType);
    int ret2 = _IFieldBus->readMemoryAssignConfig(configTemp);
    int ret3 = _IFieldBus->getModbusSwitch()->readModbusConnStatus(modbusSts);

    char filedBusInstallType[4];  // 总线安装标志
    _IMonitor->GetBusInstall(filedBusInstallType);
    if (ret1 != ERR_OK || ret2 != ERR_OK || ret3 != ERR_OK) {
        emit CommunicationEngine::instance()->signal_needMainWidgetWarning(
            CommTr::tr("Failed to get peripheral configuration."));
        return;
    }
    INO_FIELDBUS_MEM_ASSIGN_CONFIG config;
    if (sizeof(INO_FIELDBUS_MEM_ASSIGN_CONFIG) == sizeof(FIELDBUS_MEM_ASSIGN_CONFIG)) {
        memcpy(&config, &configTemp, sizeof(INO_FIELDBUS_MEM_ASSIGN_CONFIG));
        bool isHasEtherCat = (filedBusInstallType[0] >> 0) & 0x01;
        emit CommunicationEngine::instance()->signal_get_fieldBusAddressAssignResult(
            cmd->m_object,
            fieldBusType,
            config,
            modbusSts.ModbusAddrType == 1,
            isHasEtherCat);
        if (!isHasEtherCat) {
            EthcatPara ethcatPara;
            ethcatPara.ActiveCmd = 0;
            ethcatPara.SiteAlias = 1;
            ethcatPara.MaxFramLossTimes = 8;
            // 关闭
            int nRet = _IFieldBus->getEtherCATSwitch()->writeEtherCATSlaveConfig(ethcatPara);
            if (nRet != ERR_OK) {
                emit CommunicationEngine::instance()->signal_needMainWidgetWarning(
                    CommTr::tr("Failed to save EtherCAT parameters."));
                return;
            }
        }
    } else
        emit CommunicationEngine::instance()->signal_needMainWidgetWarning(
            CommTr::tr("An error occurred during data copying due to inconsistent size of the structure."));
}

void FieldBusInterface::setAddressAssignMsg(AbstractCmd *cmd)
{
    auto [config] = ((CmdDatas<INO_FIELDBUS_MEM_ASSIGN_CONFIG> *)cmd)->m_data;
    if (sizeof(INO_FIELDBUS_MEM_ASSIGN_CONFIG) != sizeof(FIELDBUS_MEM_ASSIGN_CONFIG)) {
        emit CommunicationEngine::instance()->signal_needMainWidgetWarning(
            CommTr::tr("An error occurred during data copying due to inconsistent size of the structure."));
        return;
    } else {
        FIELDBUS_MEM_ASSIGN_CONFIG configTemp;
        memcpy(&configTemp, &config, sizeof(INO_FIELDBUS_MEM_ASSIGN_CONFIG));

        if (_IRobotArm->checkFileSaveFlag() == false) {
            return;
        }
        int nRet = _IFieldBus->writeMemoryAssignConfig(configTemp);
        if (nRet != ERR_OK) {
            emit CommunicationEngine::instance()->signal_needMainWidgetWarning(
                CommTr::tr("Failed to save address allocation configuration."));
            return;
        } else {
            bool ok = false;
            _IRobotArm->saveFileCommond(&ok);
            if (!ok)
                emit CommunicationEngine::instance()->signal_needMainWidgetWarning(
                    CommTr::tr("Failed to save file."));
            else{
                emit CommunicationEngine::instance()->signal_needMainWidgetWarning(
                    CommTr::tr("The bus configuration has been modified and takes effect upon system reboot."));
                PRINT_MSG(CommTr::tr("Bus address allocation config successfully sent to controller."));
            }
        }
    }
}

void FieldBusInterface::getProjectNoAssign(AbstractCmd *cmd)
{
    InoRobBusiness::IIndexConfig *config = _IPeripheral->getProjectIndexConfigObject();
    config->initConfigArr();
    bool isExisted = false;
    int ret = config->downloadConfigFile(isExisted, config->configFileLocalPath(), config->configFileCtrlPath());
    if (ret != ERROR_OK && ret != -4) {
        emit CommunicationEngine::instance()->signal_needMainWidgetWarning(
            CommTr::tr("Failed to get config file."));
        return;
    }
    QStringList projectConfiged;
    QList<int> indexConfiged;
    QStringList projectsAll;

    std::vector<ProjectFolderInfo> prjInofs;
    int nRet = InoRobBusiness::gs_Workstation.GetObject()->GetProject()->ReadProjectList(prjInofs, _IConnection->GetIp());
    if (nRet != ERR_OK) {
        emit CommunicationEngine::instance()->signal_needMainWidgetWarning(
            CommTr::tr("Failed to get project list."));
        return;
    }
    unsigned int size = prjInofs.size();
    for (int i = 0; i < size; ++i) {
        projectsAll.push_back(QString::fromStdString(prjInofs[i].projectName));
    }

    if (isExisted) {
        int ret2 = config->analysisConfigFile(config->configFileLocalPath());
        if (ret2 == ERROR_OK) {
            std::vector<InoRobBusiness::IndexConfig> configs = config->getConfigArr();
            unsigned int size = configs.size();
            for (int i = 0; i < size; ++i) {
                projectConfiged.push_back(QString::fromStdString(configs[i].name));
                indexConfiged.push_back(configs[i].index);
            }
        } else {
            emit CommunicationEngine::instance()->signal_needMainWidgetWarning(
                CommTr::tr("Failed to parse the config file."));
            return;
        }
    }
    if (indexConfiged.size() == projectConfiged.size())
        emit CommunicationEngine::instance()->signal_get_projectNoConfig(cmd->m_object,
                                                                         indexConfiged,
                                                                         projectConfiged,
                                                                         projectsAll);
    // qDebug() << indexConfiged << projectConfiged << indexAvilable << projectsAll;
}

void FieldBusInterface::setProjectNoAssign(AbstractCmd *cmd)
{
    InoRobBusiness::IIndexConfig *instance = _IPeripheral->getProjectIndexConfigObject();
    auto [indexConfiged, projectConfiged] = ((CmdDatas<QList<int>, QStringList> *)cmd)->m_data;
    std::vector<InoRobBusiness::IndexConfig> configs = instance->getConfigArr();
    int oldSize = configs.size();
    int newSize = indexConfiged.size();
    for (int i = 0; i < oldSize; ++i) {
        instance->delConfig(configs[i]);
    }
    int ret = 0;
    for (int i = 0; i < newSize; ++i) {
        instance->addConfig();
        InoRobBusiness::IndexConfig temp;
        temp.index = indexConfiged[i];
        std::string projetTemp = projectConfiged[i].toStdString();
        temp.name = std::string(projetTemp.c_str());
        configs = instance->getConfigArr();
        if(temp.name != configs[i].name || temp.index != configs[i].index)
            ret = instance->modifyConfig(configs[i], temp);
        if(ret != ERR_OK){
            emit CommunicationEngine::instance()->signal_needMainWidgetWarning(
                CommTr::tr("Failed to save the config file."));
            return;
        }
    }
    if (instance->saveConfigFile(instance->configFileLocalPath(), instance->configFileCtrlPath()) != ERROR_OK)
        emit CommunicationEngine::instance()->signal_needMainWidgetWarning(
            CommTr::tr("Failed to save the config file."));
}

void FieldBusInterface::getPointFileNoAssign(AbstractCmd *cmd)
{
    InoRobBusiness::IIndexConfig *config = _IPeripheral->getRPFileIndexConfigObject();
    config->initConfigArr();
    bool isExisted = false;
    int ret = config->downloadConfigFile(isExisted, config->configFileLocalPath(), config->configFileCtrlPath());
    if (ret != ERROR_OK && ret != -4) {
        emit CommunicationEngine::instance()->signal_needMainWidgetWarning(
            CommTr::tr("Failed to get config file."));
        return;
    }
    QStringList pointfileConfiged;
    QList<int> indexConfiged;
    QStringList pointsFileAll;

    std::vector<ProjectFolderInfo> prjInofs;
    std::vector<string> files = InoRobBusiness::gs_Workstation.GetObject()->GetProject()->GetInfo().robPointFileArr;
    unsigned int size = files.size();
    for (int i = 0; i < size; ++i) {
        pointsFileAll.push_back(QString::fromStdString(files[i]));
    }

    if (isExisted) {
        int ret2 = config->analysisConfigFile(config->configFileLocalPath());
        if (ret2 == ERROR_OK) {
            std::vector<InoRobBusiness::IndexConfig> configs = config->getConfigArr();
            unsigned int size = configs.size();
            for (int i = 0; i < size; ++i) {
                pointfileConfiged.push_back(QString::fromStdString(configs[i].name));
                indexConfiged.push_back(configs[i].index);
            }
        } else {
            emit CommunicationEngine::instance()->signal_needMainWidgetWarning(
                CommTr::tr("Failed to parse the config file."));
            return;
        }
    }
    if (indexConfiged.size() == pointfileConfiged.size())
        emit CommunicationEngine::instance()->signal_get_PointNoConfig(cmd->m_object,
                                                                       indexConfiged,
                                                                       pointfileConfiged,
                                                                       pointsFileAll);
    // qDebug() << indexConfiged << indexConfiged << pointsFileAll;
}

void FieldBusInterface::setPointFileNoAssign(AbstractCmd *cmd)
{
    InoRobBusiness::IIndexConfig *instance = _IPeripheral->getRPFileIndexConfigObject();
    auto [indexConfiged, projectConfiged] = ((CmdDatas<QList<int>, QStringList> *)cmd)->m_data;
    std::vector<InoRobBusiness::IndexConfig> configs = instance->getConfigArr();
    int oldSize = configs.size();
    int newSize = indexConfiged.size();
    for (int i = 1; i < oldSize; ++i) {
        instance->delConfig(configs[i]);
    }

    int ret = 0;
    for (int i = 1; i < newSize; ++i) {
        instance->addConfig();
        InoRobBusiness::IndexConfig temp;
        temp.index = indexConfiged[i];
        std::string projectTemp = projectConfiged[i].toStdString();
        temp.name = std::string(projectTemp.c_str());
        configs = instance->getConfigArr();
        if(temp.name != configs[i].name || temp.index != configs[i].index) {
            ret = instance->modifyConfig(configs[i], temp);
            if(ret != ERR_OK){
                emit CommunicationEngine::instance()->signal_needMainWidgetWarning(
                    CommTr::tr("Failed to save the config file."));
                return;
            }
        }
    }

    if (instance->saveConfigFile(instance->configFileLocalPath(), instance->configFileCtrlPath()) != ERROR_OK)
        emit CommunicationEngine::instance()->signal_needMainWidgetWarning(
            CommTr::tr("Failed to save the config file."));
}

void FieldBusInterface::sendMasterConfigFile(AbstractCmd *cmd)
{
    auto[zipFileList, temDesFilePath] = BIND(cmd, const QStringList, const QString);
    QString msg;

    bool bCanOpenFile = false;          // 是否存在CanOpen文件
    bool bDeviceNetFile = false;        // 是否存在DeviceNet文件
    bool bFollowCraftCaliCfg = false;   // 是否存在视觉一拖多文件
    bool bFBusMasterParaCfg = false;    // 是否存在主站总线配置必须文件
    bool bEip = false;                  // 是否存在Eip文件

    if (zipFileList.size() == 0) {
        return;
    }

    // 检测压缩包所包含的文件
    for (size_t i = 0; i < zipFileList.size(); i++)
    {
        if (zipFileList[i] == CANOPEN_FILENNAMME)
        {
            bCanOpenFile = true;
        }

        if (zipFileList[i] == DEVICENET_FILENAME)
        {
            bDeviceNetFile = true;
        }

        if (zipFileList[i] == ETHERNETIP_FILENAME)
        {
            bEip = true;
        }

        if (zipFileList[i] == FOLLOWCRAFT_FILENAME)
        {
            bFollowCraftCaliCfg = true;
        }

        if (zipFileList[i] == FBUSMASTERPARACFG_FILENAME)
        {
            bFBusMasterParaCfg = true;
        }

        // 判断导入的组态文件是否匹配当前控制器
        if (zipFileList[i].contains(MASTER_FILE_NAME_SUFFIX))
        {
            string masterFile = zipFileList[i].toStdString();
            if (_IFieldBus->getEtherCATSwitch()->isMatchedCurrentBox(masterFile) != ERR_OK)
            {
                msg = CommTr::tr("The imported configuration file does not match the current controller.");
                CommunicationEngine::instance()->signal_sendMasterConfigZipFile_result(cmd->m_object, false, msg);
                return;
            }
        }
    }

    if (!bFBusMasterParaCfg)
    {
        msg = CommTr::tr("The main station bus configuration file is missing necessary files, and the import failed.");
        CommunicationEngine::instance()->
            signal_sendMasterConfigZipFile_result(cmd->m_object, false, msg);
        return;
    }

    if (bDeviceNetFile)
    {
        // 检验文件的json格式是否正确
        string deviceFilePath = (temDesFilePath + "/" + DEVICENET_FILENAME).toStdString();
        if (!_IFieldBus->getEtherCATSwitch()->checkDeviceNetFile(deviceFilePath))
        {
            msg = CommTr::tr("The JSON format of the file is incorrect.");
            CommunicationEngine::instance()->
                signal_sendMasterConfigZipFile_result(cmd->m_object, false, msg);
            return;
        }
    }

    // 放置文件至控制器
    int nRet = _IFieldBus->putFieldBusMasterCfgToController(temDesFilePath.toStdString(), bDeviceNetFile, bCanOpenFile, bFollowCraftCaliCfg, bEip);
    if (nRet != ERR_OK)
    {
        msg = CommTr::tr("Failed to put the file to the controller.");
        CommunicationEngine::instance()->
            signal_sendMasterConfigZipFile_result(cmd->m_object, false, msg);
        return;
    }

    // 通知控制器组态配置文件已导入
    nRet = _IFieldBus->networkFieldBusImportWrite();
    if (nRet != ERR_OK) {
        msg = CommTr::tr("The import of the main station bus configuration failed. Please try again.");
        CommunicationEngine::instance()->
            signal_sendMasterConfigZipFile_result(cmd->m_object, false, msg);
    }

    msg = CommTr::tr("The main station bus configuration has been successfully imported, and a restart of the controller will take effect");
    CommunicationEngine::instance()->
        signal_sendMasterConfigZipFile_result(cmd->m_object, true, msg);

    // 通知ethercat解析文件

}
