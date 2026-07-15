#include "projectinterface.h"
#include "communication.h"
#include "fileutils.h"
#include "IController.h"
#include "InoRobBusiness/Controller/Resource/IResource.h"
#include "InoRobBusiness/Controller/Resource/ResourceDefault.h"
#include "metatypeconversion.h"
#include "cobotlogex.h"
#include <QThread>
#include "metapath.h"
#include "modulesutils.h"

int ProjectInterface::getProjectCount()
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
    std::string tempIP = comm()->getIP().toStdString();
    const std::string ip = tempIP.c_str();
    if (ip.empty()) {
        return -1;
    }

    FREQ_LOG_PRINT_TIMESTAMP
    return comm()->project()->getProjectCount(ip);
}

bool ProjectInterface::setActiveProject(const QString &projectName)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
    bool isOk = false;

    int nReqRetryTimes = REQUEST_RETRY_TIMES;
    while (nReqRetryTimes--) {
        int ret = comm()->project()->setActiveProject(projectName.toStdString());
        if (ret == ERR_OK) {
            isOk = true;
            nReqRetryTimes = 0;
            break;
        }

        QThread::msleep(300);
    }

    qDebug() << "ProjectInterface::setActiveProject ret = " << isOk
             << ", name = " << projectName;
    FREQ_LOG_PRINT_TIMESTAMP
    return isOk;
}

bool ProjectInterface::setProjectOperateMode(const InoFileType &mode)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    comm()->project()->setProjectOperateMode(
        MetaTypeConversion::inoApi2tp_projectFileOperateMode(mode));

    FREQ_LOG_PRINT_TIMESTAMP
    return true;
}

void ProjectInterface::setProjectType(const InoProjectType &type)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    comm()->project()->setCurrentProjectType(
        MetaTypeConversion::inoApi2tp_projectType(type));

    if (comm()->project()->GetProgram()) {
        comm()->project()->GetProgram()->setProjectType(
            MetaTypeConversion::inoApi2tp_projectType(type));
    }

    FREQ_LOG_PRINT_TIMESTAMP
    return;
}

QString ProjectInterface::getCurrentProjectName()
{
    return QString::fromStdString(comm()->project()->GetName());
}

QString ProjectInterface::getActiveProjectName()
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    int nReqRetryTimes = REQUEST_RETRY_TIMES;
    std::string sProjectName = "";

    while (nReqRetryTimes--) {
        int nRet = comm()->project()->getActiveProject(sProjectName);
        if (nRet == ERR_OK && !sProjectName.empty()) {
            nReqRetryTimes = 0;
            break;
        }

        QThread::msleep(300);
    }

    FREQ_LOG_PRINT_TIMESTAMP
    return QString::fromStdString(sProjectName);
}

std::vector<struct _ProjectFolderInfo> ProjectInterface::readProjectList()
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    std::vector<struct _ProjectFolderInfo> infos;
    infos.clear();

    const std::string ip = comm()->getIP().toStdString();
    if (ip.empty()) {
        return infos;
    }

    comm()->project()->ReadProjectList(infos, ip);

    FREQ_LOG_PRINT_TIMESTAMP
    return infos;
}

QVector<InoProjectInfo> ProjectInterface::getProjectList(
    const ProjectSortType sortType)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    std::vector<struct _ProjectFolderInfo> infos = readProjectList();
    FREQ_LOG_PRINT_TIMESTAMP
    return sortProjectList(sortType, infos);
}

QVector<InoProjectInfo> ProjectInterface::sortProjectList(
    const ProjectSortType sortType,
    std::vector<struct _ProjectFolderInfo> &infos)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    // 如果连接了控制器，则获取当前激活的工程名称，排序前将其剔除在外
    struct _ProjectFolderInfo activeInfo = extractActiveProject(infos);

    // 排序
    if (ProjectSortType_DascendingByTime == sortType) {
        comm()->project()->SortProjectsByTime(infos);
    } else if (ProjectSortType_AscendingByWord == sortType) {
        comm()->project()->SortProjectsByWord(infos);
    }

    // 如果当前激活的不为空，则插入到数组第一个
    if (!activeInfo.projectName.empty()) {
        infos.insert(infos.begin(), activeInfo);
    }

    FREQ_LOG_PRINT_TIMESTAMP
    return MetaTypeConversion::tp2InoApi_projectInfos(infos);
}

bool ProjectInterface::isProjectExisted(const QString &name)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    // 获取当前工程列表
    std::vector<struct _ProjectFolderInfo> infos = readProjectList();

    FREQ_LOG_PRINT_TIMESTAMP
    return comm()->project()->IsProjectExisted(name.toStdString(), infos);
}

QString ProjectInterface::isProjectNameValid(const QString &name)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    std::string errMsg = "";
    if (comm()->project()->IsProjectNameValid(errMsg, name.toStdString())) {
        return QString();
    }

    FREQ_LOG_PRINT_TIMESTAMP
    return QString::fromStdString(errMsg);
}

bool ProjectInterface::createLocalProject(
    const QString &folder, const QString &name, InoProjectType type)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    // 创建工程
    int nRet = comm()->project()->CreateLocalProject(
        folder.toStdString(), name.toStdString(),
        MetaTypeConversion::inoApi2tp_projectType(type));

    FREQ_LOG_PRINT_TIMESTAMP

    return nRet == ERR_OK;
}

bool ProjectInterface::createProject(const QString &name, InoProjectType type)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    // 创建工程
    int nRet = comm()->project()->CreateProject(
        name.toStdString(),
        MetaTypeConversion::inoApi2tp_projectType(type));
    qDebug() << "ProjectInterface::createProject ret = " << nRet
             << " ,name = " << name;

    FREQ_LOG_PRINT_TIMESTAMP
    return nRet == ERR_OK;
}

QString ProjectInterface::getDefaultProjectName(QString baseName)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    std::vector<struct _ProjectFolderInfo> infos = readProjectList();
    return QString::fromStdString(
        comm()->project()->NewProjectDefaultName(
            infos, baseName.toStdString()));
    FREQ_LOG_PRINT_TIMESTAMP
}

bool ProjectInterface::deleteProject(const QString &name)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    int ret = comm()->project()->DelProject(name.toStdString());
    FREQ_LOG_PRINT_TIMESTAMP
    return (ret == ERR_OK);
}

bool ProjectInterface::renameProject(QString oldName, QString newName)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    int ret = comm()->project()->RenameProject(
        oldName.toStdString(), newName.toStdString());
    FREQ_LOG_PRINT_TIMESTAMP
    return (ret == ERR_OK);
}

bool ProjectInterface::copyProject(const QString &name)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    comm()->project()->CopyProject(name.toStdString());

    FREQ_LOG_PRINT_TIMESTAMP

    return true;
}

QString ProjectInterface::getCopiedProjectName()
{
    return QString::fromStdString(comm()->project()->GetCopiedProjectName());
}

bool ProjectInterface::pasteProject(const QString &name)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    int ret = comm()->project()->PasteProject(name.toStdString());
    FREQ_LOG_PRINT_TIMESTAMP
    return (ret == ERR_OK);
}

bool ProjectInterface::importProject(QString path)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    const std::string ip = comm()->getIP().toStdString();
    if (ip.empty()) {
        return false;
    }

    path = QDir::fromNativeSeparators(path);
    int ret = comm()->project()->ImportProject(ip, path.toStdString());
    qDebug() << "ProjectInterface::importProject ret = " << ret
             << ", path = " << path;
    if (ret != ERROR_OK) {
        return false;
    }

    FREQ_LOG_PRINT_TIMESTAMP
    return (ret == ERR_OK);
}

bool ProjectInterface::exportProject(const QString &name, QString folder)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    const std::string ip = comm()->getIP().toStdString();
    if (ip.empty()) {
        return false;
    }

    folder = QDir::fromNativeSeparators(folder);
    int ret = comm()->project()->ExportProject(
        ip, name.toStdString(), folder.toStdString());

    FREQ_LOG_PRINT_TIMESTAMP

    return (ret == ERR_OK);
}

QString ProjectInterface::projectName(ProjectSortType type, int index)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    QVector<InoProjectInfo> iInfos = getProjectList(type);
    if (index >= iInfos.count()) {
        return QString();
    }

    FREQ_LOG_PRINT_TIMESTAMP

    return (iInfos.at(index).name);
}

struct _ProjectFolderInfo ProjectInterface::extractActiveProject(
    std::vector<struct _ProjectFolderInfo> &infos)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    struct _ProjectFolderInfo info;

    QString sProjectName = getCurrentProjectName();
    if (sProjectName.isEmpty()) {
        return info;
    }

    bool isExisted = false;
    for (size_t i = 0; i < infos.size(); i++) {
        if (!sProjectName.compare(
                QString::fromStdString(infos.at(i).projectName))) {
            info = infos.at(i);
            isExisted = true;
            break;
        }
    }

    // remove project temporarily
    if (isExisted) {
        std::vector<ProjectFolderInfo>::iterator it = std::find(infos.begin(), infos.end(), info);
        infos.erase(it);
    }

    FREQ_LOG_PRINT_TIMESTAMP

    return info;
}

int ProjectInterface::readActiveProject(const QString &name, bool isReadSameProject)
{
    int nReqRetryTimes = REQUEST_RETRY_TIMES;
    int ret = Err_Unknown;

    const std::string ip = comm()->getIP().toStdString();
    if (ip.empty()) {
        return Err_Disconnect;
    }

    if (name.isEmpty()) {
        return Err_Unknown;
    }

    ret = comm()->project()->ReadProject(ip, name.toStdString(), isReadSameProject);
    if (ERR_OK == ret) {
        comm()->getTaskList();
    }

    return ret;
}

int ProjectInterface::readProject(const QString &name)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
    
    if (name.isEmpty()) {
        return Err_ReadProject;
    }

    const std::string ip = comm()->getIP().toStdString();
    if (ip.empty()) {
        return Err_Disconnect;
    }

    // 读取工程
    // 先记录切换前的工程名称
    QString originPrjName = getActiveProjectName();
    qDebug() << "current active project name = " << originPrjName;

    // 设置工程类型
    setProjectType(InoProjectType_Lua);

    // 加载工程
    int nRet = readActiveProject(name);
    qDebug() << "project load ret = " << nRet << ", name = " << name;
    if (nRet != ERR_OK) {
        qDebug() << "Err_ReadProject is readActiveProject" << Err_ReadProject;
        return Err_ReadProject;
    }

    QString sMainXmlFile = CONTROLLER_PROJECT_MAIN_XML_FILE(name);
    if (!FileUtils::isFileExist(sMainXmlFile)) {
        if (!originPrjName.isEmpty()) {
            nRet = readActiveProject(originPrjName);
            qDebug() << "project load origin ret = " << nRet << ", name = " << originPrjName;
        }
        return Err_Incomplete;
    }

    // 设置当前激活的工程
    if (0 != name.compare(originPrjName)) {
        bool isOk = setActiveProject(name);
        qDebug() << "set project Active ret = " << isOk << ", name = " << name;
        if (!isOk) {
            return Err_ActiveProject;
        }
    }

    // 工具IO默认描述语言不匹配，重新加载工程
    if (!Communication::instance()->isToolIoItemDescLangCorrect()) {
        // 加载工程
        nRet = readActiveProject(name, true);
        qDebug() << "project load ret = " << nRet << ", name = " << name;
        if (nRet != ERR_OK) {
            qDebug() << "Err_ReadProject is isToolIoItemDescLangCorrect" << Err_ReadProject;
            return Err_ReadProject;
        }
    }


    return Err_Success;
}

int ProjectInterface::readLocalProject(const QString &name)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    if (name.isEmpty()) {
        return Err_ReadProject;
    }

    // 设置工程类型
    setProjectType(InoProjectType_Lua);

    QString sMainXmlFile = CONTROLLER_PROJECT_MAIN_XML_FILE(name);
    if (!FileUtils::isFileExist(sMainXmlFile)) {
        return Err_Incomplete;
    }

    // 读取工程
    QString path = CONTROLLER_PROJECT_FILE_PATH(name);
    if (path.isEmpty()) {
        return Err_ReadProject;
    }

    int nRet = comm()->project()->ReadLocalProjcet(path.toStdString());
    if (nRet != ERR_OK) {
        return Err_ReadProject;
    }

    FREQ_LOG_PRINT_TIMESTAMP
    return Err_Success;
}

bool ProjectInterface::isLabelExisted(const QString &sLabel)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    if (sLabel.isEmpty()) {
        return false;
    }

    FREQ_LOG_PRINT_TIMESTAMP
    return comm()->project()->isLabelExisted(sLabel.toStdString());
}

std::vector<std::string> ProjectInterface::getProgramFileList()
{
    return comm()->project()->GetProgramFileList();
}

std::vector<std::string> ProjectInterface::getRPointFileList()
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    std::vector<std::string> fileNames = comm()->project()->GetRPointFileList();
    FREQ_LOG_PRINT_TIMESTAMP
    return fileNames;
}

std::vector<std::string> ProjectInterface::getJPointFileList()
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    std::vector<std::string> fileNames = comm()->project()->GetJPointFileList();

    FREQ_LOG_PRINT_TIMESTAMP

    return fileNames;
}

std::vector<std::string> ProjectInterface::getLabelTypeList()
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    std::vector<std::string> fileNames = comm()->project()->GetLabelTypeList();
    FREQ_LOG_PRINT_TIMESTAMP

    return fileNames;
}

std::vector<std::string> ProjectInterface::getDefineWarningFileList()
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    std::vector<std::string> fileNames
        = comm()->project()->GetDefineWarningFileList();

    FREQ_LOG_PRINT_TIMESTAMP

    return fileNames;
}

QString ProjectInterface::getDefaultProgramName(QString baseName)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    std::vector<std::string> fileNames = getProgramFileList();

    QString name;
    if (baseName.isEmpty()) {
        name = QString::fromStdString(
            comm()->project()->GetProgram()->NewProgramDefaultName(fileNames));
    } else {
        name = QString::fromStdString(
            comm()->project()->GetProgram()->NewProgramDefaultName(
                fileNames, baseName.toStdString()));
    }

    FREQ_LOG_PRINT_TIMESTAMP   
    return name;
}

/**
 * @brief 新建程序文件或者通用子程序文件
 * @param name : 文件名
 * @param isFunc: true: 通用程序  false: 完整程序
 * @return true: 成功  fail: 失败
 */
bool ProjectInterface::createProgram(const QString &name, bool isFunc)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    if (comm()->project()->IsProgramFileUpperLimit()) {
        return false;
    }

    int ret = ERR_OK;
    if (isFunc) {
        ret = comm()->project()->GetProgram()->NewFile(
            name.toStdString(), ProgramType::START_END);
    } else {
        ret = comm()->project()->GetProgram()->NewFile(
            name.toStdString(), ProgramType::FUNCTION);
    }

    if (ret != ERR_OK) {
        return false;
    }

    this->addProgramConfig(name);

    FREQ_LOG_PRINT_TIMESTAMP   

    return true;
}

bool ProjectInterface::isProgramFileUpperLimit()
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    std::vector<std::string> vecProgramFileList = getProgramFileList();
    FREQ_LOG_PRINT_TIMESTAMP   
    return (vecProgramFileList.size() > MAX_NUM_PROGRAMFILE);
}

bool ProjectInterface::isProgramExisted(const QString &name)
{
    return comm()->project()->IsProgramFileExisted(name.toStdString());
}

QString ProjectInterface::isProgramNameValid(const QString &name)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    std::string errMsg = "";
    if (comm()->project()->GetProgram()->IsProgramFileNameValid(
            errMsg, name.toStdString())) {
        return QString();
    }

    FREQ_LOG_PRINT_TIMESTAMP  

    return QString::fromStdString(errMsg);
}

bool ProjectInterface::deleteProgram(const QString &name)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    int ret = comm()->project()->GetProgram()->DelFile(name.toStdString());
    if (ERR_OK != ret) {
        return false;
    }

    this->deleteProgramConfig(name);

    FREQ_LOG_PRINT_TIMESTAMP  
    return true;
}

bool ProjectInterface::renameProgram(QString oldName, QString newName)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    int ret = comm()->project()->GetProgram()->RenameFile(
        oldName.toStdString(), newName.toStdString());
    if (ret != ERR_OK) {
        return false;
    }

    this->deleteProgramConfig(oldName);
    this->addProgramConfig(newName);

    FREQ_LOG_PRINT_TIMESTAMP  
    return true;
}

QString ProjectInterface::getProgramNameWithoutExtension(const QString &name)
{
    return QString::fromStdString(
        comm()->project()->GetProgram()->FileNameWithoutExtension(
            name.toStdString()));
}

void ProjectInterface::copyProgram(QString name)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    comm()->project()->GetProgram()->SetCopyFile(name.toStdString());

    FREQ_LOG_PRINT_TIMESTAMP  
}

QString ProjectInterface::getCopiedProgramName()
{
    return QString::fromStdString(
        comm()->project()->GetProgram()->GetCopiedName());
}

bool ProjectInterface::pasteProgram(const QString &name)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    if (comm()->project()->IsProgramFileUpperLimit()) {
        return false;
    }

    std::string srcProgramName = comm()->project()->GetProgram()->GetCopiedName();
    if (srcProgramName.empty()) {
        return false;
    }

    int ret = comm()->project()->GetProgram()->PasteFile(
        srcProgramName, name.toStdString());
    if (ERR_OK != ret) {
        return false;
    }

    this->addProgramConfig(name);

    FREQ_LOG_PRINT_TIMESTAMP 
    return true;
}

bool ProjectInterface::importLocalProgram(QString path)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    path = QDir::fromNativeSeparators(path);

    std::vector<std::string> paths;
    paths.push_back(path.toStdString());
    int ret = comm()->project()->GetProgram()->ImportFiles(paths);
    if (ret != ERR_OK) {
        return false;
    }

    this->addProgramConfig(path);

    FREQ_LOG_PRINT_TIMESTAMP 
    return true;
}

bool ProjectInterface::exportProgram(QString name, QString folder)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    std::vector<std::string> names;
    names.push_back(name.toStdString());

    folder = QDir::fromNativeSeparators(folder);
    int ret = comm()->project()->GetProgram()->ExportFiles(
        names, folder.toStdString());

    FREQ_LOG_PRINT_TIMESTAMP 
    return (ret == ERR_OK);
}

void ProjectInterface::addProgramConfig(const QString &sFileName)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
    if (sFileName.isEmpty()) {
        return;
    }

    comm()->project()->AddProgramConfig(sFileName.toStdString());
    comm()->addProgramFile(sFileName);

    FREQ_LOG_PRINT_TIMESTAMP
}

void ProjectInterface::deleteProgramConfig(const QString &sFileName)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
    if (sFileName.isEmpty()) {
        return;
    }

    comm()->project()->DelProgramConfig(sFileName.toStdString());
    comm()->removeProgramFile(sFileName);

    FREQ_LOG_PRINT_TIMESTAMP
}

bool ProjectInterface::saveProject(const InoSyncProjcetInfoType &type,
                                   const QString &sProjectName)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
    int nRet = ERR_OK;
    if (InoSyncProjcetInfoType_ProgramFiles == type
        || InoSyncProjcetInfoType_ProjectInfo == type) {
        nRet = comm()->project()->SaveProjectConfig();
    } else {
        nRet = comm()->project()->saveProject();
    }

    if (nRet != ERR_OK) {
        return false;
    }

    if (!sProjectName.isEmpty()) {
        std::string sPrjCtrlPath = ProjectHelper::ControllerActiveProjectFolder(sProjectName.toStdString());
        signed char flags[SYNC_TYPE_NUMBER] = {0};
        flags[(int)InoSyncProjcetInfoType::InoSyncProjcetInfoType_ProjectInfo] = 1;
        flags[(int)InoSyncProjcetInfoType::SYNC_PROGRAM_COMPILE] = 3;
        _ITransfor->syncProjectInfo(sPrjCtrlPath, flags);
    } else {
        comm()->project()->sendSyncFlag(static_cast<int>(type), true);
    }

    FREQ_LOG_PRINT_TIMESTAMP
    return (nRet == ERR_OK);
}

bool ProjectInterface::getRoadPointByLabel(
    const QString &sLabel, bool &isJoint, RoadPoint &pt)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
    std::vector<std::string> rpFiles = getRPointFileList();
    if (rpFiles.size() == 0) return false;

    for (auto &sName : rpFiles) {
        std::vector<MRobPosItem> rpts = comm()->project()->GetRPoint()->GetPoints(sName);
        for (auto &rpt : rpts) {
            if (rpt.LabelName.compare(sLabel.toStdString()) == 0) {
                isJoint = false;
                pt.m_position.m_x = rpt.PData.RPosData[0];
                pt.m_position.m_y = rpt.PData.RPosData[1];
                pt.m_position.m_z = rpt.PData.RPosData[2];
                pt.m_orientation.m_rx = rpt.PData.RPosData[3];
                pt.m_orientation.m_ry = rpt.PData.RPosData[4];
                pt.m_orientation.m_rz = rpt.PData.RPosData[5];
                return true;
            }
        }
    }

    std::vector<std::string> jpFiles = getJPointFileList();
    if (jpFiles.size() == 0) return false;

    for (auto &sName : jpFiles) {
        std::vector<MJPosItem> jpts = comm()->project()->GetJPoint()->GetPoints(sName);
        for (auto &jpt : jpts) {
            if (jpt.LabelName.compare(sLabel.toStdString()) == 0) {
                isJoint = true;
                pt.setJointAngle(jpt.JData.JointData);
                return true;
            }
        }
    }

    FREQ_LOG_PRINT_TIMESTAMP

    return true;
}

bool ProjectInterface::getRoadPointByIndex(const QString &type, int index, RoadPoint &pt)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
    int pageIdx = index / 5;
    int numIdx = index % 5;
    if (type.compare("P")) {
        std::vector<InoRobBusiness::GlobalPData> datas(5);
        bool bRet = _IResource->getGlobalPDatas(datas, pageIdx, 5);
        if (!bRet) return false;
        pt.m_position.m_x = datas[numIdx].globalP.Pos.RPosData[0];
        pt.m_position.m_y = datas[numIdx].globalP.Pos.RPosData[1];
        pt.m_position.m_z = datas[numIdx].globalP.Pos.RPosData[2];
        pt.m_orientation.m_rx = datas[numIdx].globalP.Pos.RPosData[3];
        pt.m_orientation.m_ry = datas[numIdx].globalP.Pos.RPosData[4];
        pt.m_orientation.m_rz = datas[numIdx].globalP.Pos.RPosData[5];
    } else {
        std::vector<InoRobBusiness::GlobalJPData> datas(5);
        bool bRet = _IResource->getGlobalJPDatas(datas, pageIdx, 5);
        if (!bRet) return false;
        pt.setJointAngle(datas[numIdx].globalJP.Pos.JointData);
    }
    FREQ_LOG_PRINT_TIMESTAMP
    return true;
}

bool ProjectInterface::deleteFileFromController(const std::string &filePath)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
    const std::string ip = comm()->getIP().toStdString();
    if (ip.empty() || filePath.empty()) {
        return false;
    }

    // 本地文件路径
    QFileInfo fi(filePath.c_str());
    std::string tmpPath = QString("%1%2.tmp")
                              .arg(ProjectHelper::LocalTempFolder().c_str(),
                                   fi.fileName())
                              .toStdString();

    // 本地文件是否存在
    if (!FileExist(filePath)) {
        return true;
    }

    // 先备份一个源文件
    FileCopy(filePath, tmpPath);

    // 删除本地文件
    FileDelete(filePath);

    // 删除控制器中的文件
    QString ctrlPath = FileUtils::getControllerFilePath(
        QString::fromStdString(filePath), ABSOLUTE_DATA_PATH);

    if (comm()->isConnectVirtualController()) {
        ctrlPath = QString::fromStdString(ProjectHelper::VirtualControllerSDCardFolder()) + ctrlPath;
    }

    qDebug() << __FUNCTION__ << "controller file : " << ctrlPath;
    int nRet = ProjectHelper::DelFileInController(ip, ctrlPath.toStdString());
    if (nRet != ERR_OK) {
        // 如果失败，则还原回本地的
        FileCopy(tmpPath, filePath);

        return false;
    } else {
        FileDelete(tmpPath);
    }

    FREQ_LOG_PRINT_TIMESTAMP

    return (nRet == ERR_OK);
}

bool ProjectInterface::deleteFilesFromController(
    const std::vector<std::string> &filePathList)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
    bool bRet = false;
    if (filePathList.empty()) {
        return bRet;
    }

    for (size_t i = 0; i < filePathList.size(); i++) {
        bRet = deleteFileFromController(filePathList.at(i));
    }

    FREQ_LOG_PRINT_TIMESTAMP
    return bRet;
}

int ProjectInterface::isFileNameRepeat(const QString &fileName)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
    if (fileName.isEmpty()) {
        return -1;
    }

    ftp::client ftpClient;
    std::string serverIp = comm()->getIP().toStdString();

    if (!ftpClient.connect(serverIp, FTP_PORT, FTP_USER, FTP_PASSWORD).is_positive()) {
        return -2;
    }

    if (!ftpClient.exist_directory(POINT_FILE_FOLDER)) {
        return -3;
    }
#ifdef INOCOBOTTP_MSVC_QT5
    QString localFileName = fileName.toLocal8Bit();
#endif

    vector<std::string> fileList;
    fileList = ftpClient.get_file_list(POINT_FILE_FOLDER, true).get_file_list();
    for (int i = 0; i < fileList.size(); i++) {
#ifdef INOCOBOTTP_MSVC_QT5
        if (localFileName.compare(QString::fromStdString(fileList.at(i))) == 0) {
            return 1;
        }
#else
        if (0 == fileName.toLocal8Bit().compare(fileList.at(i))) {
            return 1;
        }
#endif
    }

    FREQ_LOG_PRINT_TIMESTAMP

    return 0;
}
