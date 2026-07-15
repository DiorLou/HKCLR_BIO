#include "communicationthread.h"
#include <QMutex>
#include <QDebug>
#include <QVariant>
#include <QWaitCondition>
#include "cobotlog.h"
#include "communicationengine.h"
#include "communication.h"
#include "fileutils.h"
#include "projectinterface.h"
#include "project/projectinfo.h"
#include "commandinfo.h"
#include "metatypeconversion.h"
#include "metapath.h"

const char TMP_FILE_NAME[] = "tmp";
const int MAIN_TASK_ID = 0;
const QString MAIN_TASK_NAME = "main";
const QString MAIN_PROGRAM_FILE = "main.lua";

inline QString CONVERT_PARAMETERS_FALID = QObject::tr("An error occurred while converting parameters.");
inline QString SPACE_AND_CONVERT_PARAMETERS_FALID = " " + CONVERT_PARAMETERS_FALID;

std::vector<std::string> getScriptFileList(const QString &sProjectName)
{
    std::vector<std::string> vecScriptFiles;
    if (sProjectName.isEmpty()) {
        return vecScriptFiles;
    }

    QDir currentDir = QDir(CONTROLLER_PROJECT_PATH(sProjectName));
    if (currentDir.exists()) {
        QStringList fileNames = currentDir.entryList(
            QStringList() << QString("*%1")
                                 .arg(SCRIPT_FILE_NAME_SUFFIX),
            QDir::Files, QDir::Name);

        QStringList taskNameList = Communication::instance()->getMultiTaskNameList();
        taskNameList.push_back(MAIN_TASK_NAME);

        std::vector<std::string> programFileNames = Communication::instance()->getProgramFileList();

        for (const QString &name : fileNames) {
            QString baseName = name.left(name.length()-QString(SCRIPT_FILE_NAME_SUFFIX).length());
            if (!taskNameList.contains(baseName)) {
                if (programFileNames.end() == std::find(programFileNames.begin(),
                                                        programFileNames.end(),
                                                        name.toStdString())) {
                    vecScriptFiles.push_back(name.toStdString());
                }
            }
        }
    }

    return vecScriptFiles;
}

std::vector<std::string> getPalletFileList(const QString &sProjectName)
{
    std::vector<std::string> vecScriptFiles;
    if (sProjectName.isEmpty()) {
        return vecScriptFiles;
    }

    QDir currentDir = QDir(CONTROLLER_PROJECT_PATH(sProjectName));
    if (currentDir.exists()) {
        QStringList fileNames = currentDir.entryList(
            QStringList() << QString("*%1")
                                 .arg(".xml"),
            QDir::Files, QDir::Name);
        for (const QString &name : fileNames) {
            if(name.startsWith("Pallet2D_"))
                vecScriptFiles.push_back(("Project_" + name.mid(9) + "(2D)").toStdString());
            else if(name.startsWith("Pallet3D_"))
                vecScriptFiles.push_back(("Project_" + name.mid(9) + "(3D)").toStdString());
            else if(name.startsWith("PalletArmParams_"))
                vecScriptFiles.push_back(("Project_" + name.mid(16) + "(Arm)").toStdString());
        }
    }
    return vecScriptFiles;
}

void CommunicationThread::importLocalProject(AbstractCmd *absCmd)
{
    QString sErrMsg;
    QString sProjectName;
    QString sActiveProjectName;
    bool isOk = true;

    CmdCommonValue *cmd = dynamic_cast<CmdCommonValue *>(absCmd);
    if (!cmd) {
        sErrMsg = tr("Failed to import the local project.") + SPACE_AND_CONVERT_PARAMETERS_FALID;
        isOk = false;
    }

    if (isOk) {
        sProjectName = cmd->m_value.toString();
        // 导入工程需要先删除控制柜中已有同名工程文件目录
        // 模型层不允许删除已经被激活的工程
        // 因此，不允许导入与激活工程同名的工程
        sActiveProjectName = m_commInstance->getActiveProjectName();
        if (!sActiveProjectName.isEmpty() && sProjectName.compare(sActiveProjectName) == 0) {
            sErrMsg = tr("Failed to import the project as its name is the same as the name of the current active project.");
            isOk = false;
        }
    }

    if (isOk) {
        QString sMainXmlFile = LOCAL_PROJECT_MAIN_XML_FILE(sProjectName);
        isOk = FileUtils::isFileExist(sMainXmlFile);
        if (!isOk) {
            sErrMsg = tr("Failed to sync the project to the controller as \"main.xml\" file is missing in the project.");
        }
    }

    if (isOk) {
        QString sMainLuaFile = LOCAL_PROJECT_MAIN_SCRIPT_FILE(sProjectName);
        isOk = FileUtils::isFileExist(sMainLuaFile);
        if (!isOk) {
            sErrMsg = tr("Failed to sync the project to the controller as \"main.lua\" file is missing in the project.");
        }
    }

    if (isOk) {
        QString sPath = LOCAL_PROJECT_FILE_PATH(sProjectName);
        isOk = FileUtils::isFileExist(sPath);
        if (!isOk) {
            sErrMsg = tr("Project sync failed because project file %1.prj does not exist.")
                          .arg(sProjectName);
        }

        if (isOk) {
            isOk = m_commInstance->importProject(sPath);
            if (!isOk) {
                sErrMsg = tr("Failed to sync project.");
            }
        }
    }

    emit CommunicationEngine::instance()
        ->signal_handleProject_result(absCmd->m_object, absCmd->m_cmdType,
                                      sProjectName, isOk, sErrMsg);
}

void CommunicationThread::exportProject(AbstractCmd *absCmd)
{
    QString sErrMsg;
    QVector<QVariant> vecValues;
    QString sProjectName;
    QString sFolderName;
    CmdCommonValue *cmd = nullptr;
    bool isOk = true;

    cmd = dynamic_cast<CmdCommonValue *>(absCmd);
    if (!cmd) {
        sErrMsg = tr("Failed to export project.")
                         + SPACE_AND_CONVERT_PARAMETERS_FALID;
        isOk = false;
    }

    if (isOk) {
        vecValues = cmd->m_value.value<QVector<QVariant>>();
        if (vecValues.count() < 2) {
            sErrMsg = tr("Failed to export project as the parameters are invalid.");
            isOk = false;
        }
    }

    if (isOk) {
        sProjectName = vecValues.at(0).toString();
        sFolderName = vecValues.at(1).toString();
        isOk = m_commInstance->exportProject(sProjectName, sFolderName);
        if (isOk) {
            sErrMsg = tr("Failed to export project.");
        }
    }

    emit CommunicationEngine::instance()
        ->signal_handleProject_result(absCmd->m_object, absCmd->m_cmdType,
                                      sProjectName, isOk, sErrMsg);
}

void CommunicationThread::initTeachPadInfo(AbstractCmd *absCmd)
{
    QString sErrMsg;
    bool isOk = true;

    InoUserMode mode = m_commInstance->getCurrentLoginUserMode();
    if (mode < InoUserMode_Manage) {
        isOk = m_commInstance->userLogin(
            InoUserMode_Factory, FACTORY_MODE_PASSWD);
        if (!isOk) {
            sErrMsg = tr("Login failed.");
        }
    }

    if (isOk) {
        InoCtrlAuthority ctrlAuthority = m_commInstance->getCtlAuthority();
        if (ctrlAuthority != m_commInstance->GetCurCtrlAuthority()) {
            m_commInstance->setCurCtrlAuthority(ctrlAuthority);

            emit CommunicationEngine::instance()
                ->signal_controlAuthorityChanged(ctrlAuthority);
        }
    }

    emit CommunicationEngine::instance()->signal_initTeachPadInfo_result(
        absCmd->m_object, isOk, sErrMsg);
}

void CommunicationThread::userLogin(AbstractCmd *absCmd)
{
    QString sErrMsg;
    bool isOk = true;

    CmdUserLogin *cmd = dynamic_cast<CmdUserLogin *>(absCmd);
    if (!cmd) {
        sErrMsg = tr("Login failed.") + SPACE_AND_CONVERT_PARAMETERS_FALID;
        isOk = false;
    }

    if (isOk) {
        InoUserMode mode = m_commInstance->getCurrentLoginUserMode();
        if (mode < InoUserMode_Manage) {
            isOk = m_commInstance->userLogin(cmd->m_userMode, cmd->m_sPasswd);
            if (!isOk) {
                sErrMsg = tr("Login failed.");
            }
        }
    }

    emit CommunicationEngine::instance()->signal_userLogin_result(
        absCmd->m_object, isOk, sErrMsg);
}

void CommunicationThread::setCtlAuthority(AbstractCmd *absCmd)
{
    QString sErrMsg;
    bool isOk = true;

    CmdSetCtrlAuthority *cmd = dynamic_cast<CmdSetCtrlAuthority *>(absCmd);
    if (!cmd) {
        sErrMsg = tr("Failed to set control permission.") + SPACE_AND_CONVERT_PARAMETERS_FALID;
        isOk = false;
    }

    if (isOk) {
        InoCtrlAuthority ctrlAuthority = m_commInstance->getCtlAuthority();
        if (InoCtrlAuthority_TeachPad != ctrlAuthority) {
            isOk = m_commInstance->setCtlAuthority(cmd->m_ctrlAuthority);
            if (!isOk) {
                sErrMsg = tr("Failed to set control permission.");
            }
        }
    }

    emit CommunicationEngine::instance()->signal_setCtrlAuthority_result(
        absCmd->m_object, isOk, sErrMsg);
}

void CommunicationThread::refreshProjectDatas(AbstractCmd *absCmd)
{
    QString sErrMsg;
    int nProjectCount = 0;
    ProjectSortType sortType;
    QVector<InoProjectInfo> vecProjectInfos;
    CmdCommonValue *cmd = nullptr;

    bool isOk = m_commInstance->isConnected();
    if (isOk) {
        nProjectCount = m_commInstance->getProjectCount();
        if (nProjectCount < 0) {
            isOk = false;
        }
    }

    if (isOk) {
        cmd = dynamic_cast<CmdCommonValue *>(absCmd);
        if (!cmd) {
            sErrMsg = tr("Failed to get project list. ") + SPACE_AND_CONVERT_PARAMETERS_FALID;
            isOk = false;
        }
    }

    if (isOk) {
        sortType = cmd->m_value.value<ProjectSortType>();
        vecProjectInfos = m_commInstance->getProjectList(sortType);
        if (vecProjectInfos.isEmpty()) {
            sErrMsg = tr("Failed to get project list. ");
            isOk = false;
        }
    }

#ifdef INOCOBOTTP_MSVC_QT5
    qRegisterMetaType<QVector<InoProjectInfo>>("QVector<InoProjectInfo>");
#endif
    emit CommunicationEngine::instance()->signal_handleProject_result(
        absCmd->m_object, absCmd->m_cmdType,
        isOk ? QVariant::fromValue(vecProjectInfos) : QVariant(),
        isOk, sErrMsg);
}

void CommunicationThread::getProjectList(AbstractCmd *absCmd)
{
    qDebug() << "getProjectList(AbstractCmd *absCmd)";
    QString sErrMsg;
    ProjectSortType sortType;
    QVector<InoProjectInfo> vecProjectInfos;
    CmdCommonValue *cmd = nullptr;

    bool isOk = m_commInstance->isConnected();
    if (isOk) {
        cmd = dynamic_cast<CmdCommonValue *>(absCmd);
        if (!cmd) {
            sErrMsg = tr("Failed to get project list. ") + SPACE_AND_CONVERT_PARAMETERS_FALID;
            isOk = false;
        }
    }

    if (isOk) {
        sortType = cmd->m_value.value<ProjectSortType>();
        vecProjectInfos = m_commInstance->getProjectList(sortType);
        if (vecProjectInfos.isEmpty()) {
            sErrMsg = tr("Project list is empty.");
            isOk = false;
        }
    }
#ifdef INOCOBOTTP_MSVC_QT5
    if (CommunicationEngine *engine = CommunicationEngine::instance()) {
        QMetaObject::invokeMethod(engine, [=]() {
            emit engine->signal_handleProject_result(
                absCmd ? absCmd->m_object : nullptr,
                absCmd ? absCmd->m_cmdType : AbstractCmd::CmdType_GetProjectList,
                isOk ? QVariant::fromValue(vecProjectInfos) : QVariant(),
                isOk, sErrMsg);
        }, Qt::QueuedConnection);
    }
#else
    emit CommunicationEngine::instance()->signal_handleProject_result(
        absCmd->m_object, absCmd->m_cmdType,
        isOk ? QVariant::fromValue(vecProjectInfos) : QVariant(),
        isOk, sErrMsg);
#endif

}

void CommunicationThread::setActiveProject(AbstractCmd *absCmd)
{
    QString sErrMsg;
    QString sProjectName;
    bool isOk = true;

    CmdCommonValue *cmd = dynamic_cast<CmdCommonValue *>(absCmd);
    if (!cmd) {
        sErrMsg = tr("Failed to activate project.") + SPACE_AND_CONVERT_PARAMETERS_FALID;
        isOk = false;
    }

    if (isOk) {
        sProjectName = cmd->m_value.toString();
        isOk = m_commInstance->setActiveProject(sProjectName);
        if (!isOk) {
            sErrMsg = tr("Failed to activate project.");
        }
    }

    emit CommunicationEngine::instance()->signal_handleProject_result(
        absCmd->m_object, absCmd->m_cmdType, QVariant(sProjectName),
        isOk, sErrMsg);
}

void CommunicationThread::readProject(AbstractCmd *absCmd)
{
    QString sErrMsg;
    QString sProjectName;
    bool isOk = true;

    CmdCommonValue *cmd = dynamic_cast<CmdCommonValue *>(absCmd);
    if (!cmd) {
        sErrMsg = tr("Failed to read project.") + CONVERT_PARAMETERS_FALID;
        isOk = false;
    }

    if (isOk) {
        sProjectName = cmd->m_value.toString();
        int ret = m_commInstance->readProject(sProjectName);
        if (Err_Success != ret) {
            isOk = false;
            m_commInstance->setProgramFinished();
        }
        qDebug() << "readProject ret = " << ret;
        if (Err_ReadProject == ret) {
            sErrMsg = tr("Failed to load project.");
        } else if (Err_ActiveProject == ret) {
            sErrMsg = tr("Failed to read project due to an error in the current active project.");
        } else if (Err_Incomplete == ret) {
            sErrMsg = tr("The current active project does not support collaborative robots, please load or synchronize a project adapted to collaborative robots.");
        }
    }

    if (isOk) {
        updateRoadPointInfo();
        getAllLabelsForVirtualKeyBoard();
    }

    if (isOk) {
        std::vector<std::string> vecProgramFiles = m_commInstance->getProgramFileList();
        for (const std::string &programFile : vecProgramFiles) {
            m_commInstance->addProgramFile(QString::fromStdString(programFile));
        }
    }

    emit CommunicationEngine::instance()->signal_handleProject_result(
        absCmd->m_object, absCmd->m_cmdType, QVariant(sProjectName),
        isOk, sErrMsg);
}

void CommunicationThread::readLocalProject(AbstractCmd *absCmd)
{
    QString sErrMsg;
    QString sProjectName;
    bool isOk = true;

    CmdCommonValue *cmd = dynamic_cast<CmdCommonValue *>(absCmd);
    if (!cmd) {
        sErrMsg = tr("Failed to read local project.") + CONVERT_PARAMETERS_FALID;
        isOk = false;
    }

    if (isOk) {
        sProjectName = cmd->m_value.toString();
        int ret = m_commInstance->readLocalProject(sProjectName);
        if (Err_Success != ret) {
            isOk = false;
        }

        if (Err_ReadProject == ret) {
            sErrMsg = tr("Failed to load project.");
        } else if (Err_Incomplete == ret) {
            sErrMsg = tr("The current active project does not support collaborative robots, please load or synchronize a project adapted to collaborative robots.");
        }
    }

    if (isOk) {
        updateRoadPointInfo();
        getAllLabelsForVirtualKeyBoard();
    }

    if (isOk) {
        std::vector<std::string> vecProgramFiles = m_commInstance->getProgramFileList();
        for (const std::string &programFile : vecProgramFiles) {
            m_commInstance->addProgramFile(QString::fromStdString(programFile));
        }
    }

    emit CommunicationEngine::instance()->signal_handleProject_result(
        absCmd->m_object, absCmd->m_cmdType, QVariant(sProjectName),
        isOk, sErrMsg);
}

void CommunicationThread::getDefaultProjectName(AbstractCmd *absCmd)
{
    QString sErrMsg;
    QString sBaseName;
    QString sDefaultProjectName;
    bool isOk = true;

    CmdCommonValue *cmd = dynamic_cast<CmdCommonValue *>(absCmd);
    if (!cmd) {
        sErrMsg = tr("Failed to get default project.") + SPACE_AND_CONVERT_PARAMETERS_FALID;
        isOk = false;
    }

    if (isOk) {
        sBaseName = cmd->m_value.toString();
        sDefaultProjectName = m_commInstance->getDefaultProjectName(sBaseName);
        isOk = !sDefaultProjectName.isEmpty();
    }

    emit CommunicationEngine::instance()->signal_handleProject_result(
        absCmd->m_object, absCmd->m_cmdType, sDefaultProjectName,
        isOk, sErrMsg);
}

void CommunicationThread::createLocalProject(AbstractCmd *absCmd)
{
    QString sErrMsg;
    QString sProjectName;
    bool isOk = true;

    CmdCommonValue *cmd = dynamic_cast<CmdCommonValue *>(absCmd);
    if (!cmd) {
        sErrMsg = tr("Failed to create local project.") + SPACE_AND_CONVERT_PARAMETERS_FALID;
        isOk = false;
    }

    if (isOk) {
        isOk = m_commInstance->setProjectOperateMode(InoFileType_Local);
        if (!isOk) {
            sErrMsg = tr("Failed to create local project due to an error in setting project mode.");
        }
    }

    if (isOk) {
        sProjectName = cmd->m_value.toString();
        sErrMsg = m_commInstance->isProjectNameValid(sProjectName);
        if (!sErrMsg.isEmpty()) {
            isOk = false;
            sErrMsg = tr("Failed to create local project as the project name is invalid.");
        }
    }

    if (isOk) {
        isOk = m_commInstance->createLocalProject(LOCAL_PROJECT_DIR_PATH,
                                                  sProjectName);
        if (!isOk) {
            sErrMsg = tr("Failed to create local project.");
        }
    }

    emit CommunicationEngine::instance()->signal_handleProject_result(
        absCmd->m_object, absCmd->m_cmdType, QVariant(sProjectName),
        isOk, sErrMsg);
}

void CommunicationThread::createProject(AbstractCmd *absCmd)
{
    QString sErrMsg;
    QString sProjectName;
    bool isOk = true;

    CmdCommonValue *cmd = dynamic_cast<CmdCommonValue *>(absCmd);
    if (!cmd) {
        sErrMsg = tr("Failed to create project.") + SPACE_AND_CONVERT_PARAMETERS_FALID;
        isOk = false;
    }

    if (isOk) {
        isOk = m_commInstance->setProjectOperateMode(InoFileType_Controller);
        if (!isOk) {
            sErrMsg = tr("Failed to create project due to an error in setting project mode.");
        }
    }

    if (isOk) {
        sProjectName = cmd->m_value.toString();
        sErrMsg = m_commInstance->isProjectNameValid(sProjectName);
        if (!sErrMsg.isEmpty()) {
            isOk = false;
            sErrMsg = tr("Failed to create project as the project name is invalid.");
        }
    }

    if (isOk) {
        sProjectName = cmd->m_value.toString();
        bool isExist = m_commInstance->isProjectExisted(sProjectName);
        if (isExist) {
            sErrMsg = tr("Failed to create project as the project already exsits.");
            isOk = false;
        }
    }

    if (isOk) {
        isOk = m_commInstance->createProject(sProjectName);
        if (!isOk) {
            sErrMsg = tr("Failed to create project.");
        }
    }

    if (isOk) {
        sProjectName = cmd->m_value.toString();
        int ret = m_commInstance->readProject(sProjectName);
        if (Err_Success != ret) {
            isOk = false;
            sErrMsg = tr("Failed to load project.");
        }
    }

    if (isOk) {
        updateRoadPointInfo();
        getAllLabelsForVirtualKeyBoard();
    }

    emit CommunicationEngine::instance()->signal_handleProject_result(
        absCmd->m_object, absCmd->m_cmdType, QVariant(sProjectName),
        isOk, sErrMsg);
}

void CommunicationThread::deleteProject(AbstractCmd *absCmd)
{
    QString sErrMsg;
    QString sProjectName;
    QString sActiveProjectName;
    bool isOk = true;

    CmdCommonValue *cmd = dynamic_cast<CmdCommonValue *>(absCmd);
    if (!cmd) {
        sErrMsg = tr("Failed to delete project.") + SPACE_AND_CONVERT_PARAMETERS_FALID;
        isOk = false;
    }

    if (isOk) {
        sProjectName = cmd->m_value.toString();
        // 模型层不允许删除已经被激活的工程
        sActiveProjectName = m_commInstance->getActiveProjectName();
        if (!sActiveProjectName.isEmpty()
            && sProjectName.compare(sActiveProjectName) == 0) {
            sErrMsg = tr("Active project is not allowed to be deleted.");
            isOk = false;
        }
    }

    if (isOk) {
        isOk = m_commInstance->deleteProject(sProjectName);
        if (isOk) {
            sErrMsg = tr("Failed to delete project.");
        }
    }

    emit CommunicationEngine::instance()->signal_handleProject_result(
        absCmd->m_object, absCmd->m_cmdType, QVariant(sProjectName),
        isOk, sErrMsg);
}

void CommunicationThread::copyProject(AbstractCmd *absCmd)
{
    QString sErrMsg;
    QString sProjectName;
    bool isOk = true;

    CmdCommonValue *cmd = dynamic_cast<CmdCommonValue *>(absCmd);
    if (!cmd) {
        sErrMsg = tr("Failed to copy project.") + SPACE_AND_CONVERT_PARAMETERS_FALID;
        isOk = false;
    }

    if (isOk) {
        sProjectName = cmd->m_value.toString();
        isOk = m_commInstance->copyProject(sProjectName);
        if (!isOk) {
            sErrMsg = tr("Failed to copy project.");
        }
    }

    emit CommunicationEngine::instance()->signal_handleProject_result(
        absCmd->m_object, absCmd->m_cmdType, QVariant(sProjectName),
        isOk, sErrMsg);
}

void CommunicationThread::genPasteProjectName(AbstractCmd *absCmd)
{
    QString sErrMsg;
    QString sProjectName;
    bool isOk = true;

    sProjectName = m_commInstance->getCopiedProjectName();
    if (sProjectName.isEmpty()) {
        isOk = false;
    }

    if (isOk) {
        sProjectName = m_commInstance->getDefaultProjectName(sProjectName + '_');
        if (sProjectName.isEmpty()) {
            isOk = false;
        }
    }

    emit CommunicationEngine::instance()->signal_handleProject_result(
        absCmd->m_object, absCmd->m_cmdType, QVariant(sProjectName),
        isOk, sErrMsg);
}

void CommunicationThread::pasteProject(AbstractCmd *absCmd)
{
    QString sErrMsg;
    QString sProjectName;
    bool isOk = true;

    CmdCommonValue *cmd = dynamic_cast<CmdCommonValue *>(absCmd);
    if (!cmd) {
        sErrMsg = tr("Failed to paste project.") + SPACE_AND_CONVERT_PARAMETERS_FALID;
        isOk = false;
    }

    if (isOk) {
        sProjectName = cmd->m_value.toString();
        sErrMsg = m_commInstance->isProjectNameValid(sProjectName);
        if (!sErrMsg.isEmpty()) {
            isOk = false;
            sErrMsg = tr("Failed to paste project as the project name is invalid.");
        }
    }

    if (isOk) {
        bool isExist = m_commInstance->isProjectExisted(sProjectName);
        if (isExist) {
            sErrMsg = tr("The project already exists.");
            isOk = false;
        }
    }

    if (isOk) {
        isOk = m_commInstance->pasteProject(sProjectName);
        if (isOk) {
            sErrMsg = tr("Failed to paste project.");
        }
    }

    emit CommunicationEngine::instance()->signal_handleProject_result(
        absCmd->m_object, absCmd->m_cmdType, QVariant(sProjectName),
        isOk, sErrMsg);
}

void CommunicationThread::renameProject(AbstractCmd *absCmd)
{
    QString sErrMsg;
    QVector<QVariant> vecValues;
    QString sProjectName;
    QString sNewProjectName;
    QString sActiveProjectName;
    bool isActiveProject = false;
    bool isOk = true;

    CmdCommonValue *cmd = dynamic_cast<CmdCommonValue *>(absCmd);
    if (!cmd) {
        sErrMsg = tr("Failed to rename project.") + SPACE_AND_CONVERT_PARAMETERS_FALID;
        isOk = false;
    }

    if (isOk) {
        vecValues = cmd->m_value.value<QVector<QVariant>>();
        if (vecValues.count() < 2) {
            sErrMsg = tr("Failed to rename project as the parameters are illegal.");
            isOk = false;
        }
    }

    if (isOk) {
        sProjectName = vecValues.at(0).toString();
        sNewProjectName = vecValues.at(1).toString();
        sErrMsg = m_commInstance->isProjectNameValid(sNewProjectName);
        if (!sErrMsg.isEmpty()) {
            isOk = false;
            sErrMsg = tr("Failed to rename project as the project name is invalid.");
        }
    }

    if (isOk) {
        bool isExist = m_commInstance->isProjectExisted(sNewProjectName);
        if (isExist) {
            sErrMsg = tr("The project already exists.");
            isOk = false;
        }
    }

    if (isOk) {
        isOk = m_commInstance->renameProject(sProjectName, sNewProjectName);
        if (!isOk) {
            sErrMsg = tr("Failed to rename project.");
        }
    }

    if (isOk) {
        sActiveProjectName = m_commInstance->getActiveProjectName();
        if (!sActiveProjectName.isEmpty()
            && sActiveProjectName.compare(sNewProjectName) == 0) {
            isActiveProject = true;
            int ret = m_commInstance->readProject(sNewProjectName);
            if (Err_Success != ret) {
                isOk = false;
                sErrMsg = tr("Project renamed successfully but failed to be loaded.");
            }
        }
    }


#ifdef INOCOBOTTP_MSVC_QT5
    QVariantList resultList;
    if (isOk) {
        resultList << sNewProjectName;
    } else {
        resultList << QVariant();
    }
    resultList << isActiveProject;

    emit CommunicationEngine::instance()->signal_handleProject_result(
        absCmd->m_object,
        absCmd->m_cmdType,
        resultList,
        isOk,
        sErrMsg
        );
#else
    emit CommunicationEngine::instance()->signal_handleProject_result(
        absCmd->m_object, absCmd->m_cmdType,
        QVector<QVariant>() << (isOk ? QVariant(sNewProjectName) : QVariant())
                            << QVariant(isActiveProject),
        isOk, sErrMsg);
#endif
}

void CommunicationThread::uploadFilesToController(AbstractCmd *absCmd)
{
    QString sErrMsg;
    QString sProjectName;
    QStringList srcFileList;
    bool isProject = false;
    bool isOk = true;

    CmdPutFilesToController *cmd = dynamic_cast<CmdPutFilesToController *>(absCmd);
    if (!cmd) {
        sErrMsg = tr("Failed to upload files to controller.") + SPACE_AND_CONVERT_PARAMETERS_FALID;
        isOk = false;
    }

    if (isOk) {
        sProjectName = cmd->m_projectName;
        srcFileList = cmd->m_srcFileList;
        isProject = cmd->m_isProject;

        isOk = m_commInstance->putFilesToController(srcFileList,
                                                    cmd->m_destFileList);
        if (!isOk) {
            sErrMsg = tr("Failed to upload files to controller.");
            isOk = false;
        }
    }

    if (isOk) {
        if (isProject) {
            QStringList fileNameList;
            std::vector<std::string> vecFileNames =
                m_commInstance->getProgramFileList();
            for (const std::string &fileName : vecFileNames) {
                fileNameList.append(QString::fromStdString(fileName));
            }

            QStringList taskNameList = m_commInstance->getMultiTaskNameList();
            taskNameList.append(MAIN_TASK_NAME);
            QStringList scriptNameList = m_commInstance->getScriptNameList();
            for (int i = 0; i < srcFileList.count(); i++) {
                QFileInfo fi(srcFileList.at(i));
                if (!fileNameList.contains(fi.fileName())
                    && fi.suffix().compare("xml")) {
                    if (taskNameList.contains(fi.baseName())
                        || scriptNameList.contains(fi.fileName())) {
                        // delete program file from *.prj
                        // which is similar to script file name
                        for (const QString &sFileName : fileNameList) {
                            if (0 == sFileName.compare(fi.fileName(), Qt::CaseInsensitive)
                                     && 0 != sFileName.compare(fi.fileName(), Qt::CaseSensitive)) {
                                m_commInstance->deleteProgramConfig(sFileName);
                                break;
                            }
                        }

                        m_commInstance->addProgramConfig(fi.fileName());
                    } else {
                        for (const QString &sFileName : fileNameList) {
                            if (0 == sFileName.compare(fi.fileName(), Qt::CaseInsensitive)) {
                                m_commInstance->deleteProgramConfig(sFileName);
                                break;
                            }
                        }
                    }
                } else if (fileNameList.contains(fi.fileName())
                           && fi.suffix().compare("xml")) {
                    if (!taskNameList.contains(fi.baseName())
                        && !scriptNameList.contains(fi.fileName())) {
                        m_commInstance->deleteProgramConfig(fi.fileName());
                    }
                }
            }
        }
    }

    if (isOk) {
        if (isProject) {
            isOk = m_commInstance->saveProject(InoSyncProjcetInfoType_ProgramFiles, sProjectName);
            if (!isOk) {
                sErrMsg = tr("Failed to save project.");
            }
        }
    }

#ifdef INOCOBOTTP_MSVC_QT5
    QVariantList list;
    list << QVariant(sProjectName) << srcFileList;
    emit CommunicationEngine::instance()->signal_handleProject_result(
        absCmd->m_object,
        absCmd->m_cmdType,
        list,
        isOk,
        sErrMsg
        );
#else
    emit CommunicationEngine::instance()->signal_handleProject_result(
        absCmd->m_object, absCmd->m_cmdType,
        QVector<QVariant>() << QVariant(sProjectName) << srcFileList,
        isOk, sErrMsg);
#endif

}

void CommunicationThread::deleteFilesFromController(AbstractCmd *absCmd)
{
    QString sErrMsg;
    QString sProjectName;
    QStringList fileNameList;
    bool isOk = true;

    CmdRemoveFilesFromController *cmd = dynamic_cast<CmdRemoveFilesFromController *>(absCmd);
    if (!cmd) {
        sErrMsg = tr("Failed to delete files from controller.") + SPACE_AND_CONVERT_PARAMETERS_FALID;
        isOk = false;
    }

    if (isOk) {
        sProjectName = cmd->m_projectName;
        fileNameList = cmd->m_fileNameList;
        if (!fileNameList.empty()) {
            FileUtils::delFiles(CONTROLLER_TMP_DIR_PATH);
        }

        std::vector<std::string> vecFilePath;
        for (const QString &fileName : fileNameList) {
            QFileInfo fi(fileName);
            QString suffix = fi.suffix();
            suffix = fileName.right(suffix.length() + 1);
            if (!suffix.compare(XML_FILE_NAME_SUFFIX)) {
                // xml 带路径
                qDebug() << __FUNCTION__ << "xml: " << fileName;
                vecFilePath.push_back(fileName.toStdString());
            } else {
                // script 不带路径
                qDebug() << __FUNCTION__ << "lua : " << fileName;
                isOk = m_commInstance->deleteProgram(fi.fileName());
                if (!isOk) {
                    sErrMsg = tr("Failed to delete script file.");
                    break;
                }
            }
        }

        if (isOk && !vecFilePath.empty()) {
            // 删除额外的xml文件
            isOk = m_commInstance->deleteFilesFromController(vecFilePath);
            if (!isOk) {
                sErrMsg = tr("Failed to delete files from controller.");
                isOk = false;
            }
        }
    }

#ifdef INOCOBOTTP_MSVC_QT5
    QVariantList list;
    list << QVariant(sProjectName) << fileNameList;
    emit CommunicationEngine::instance()->signal_handleProject_result(
        absCmd->m_object,
        absCmd->m_cmdType,
        list,
        isOk,
        sErrMsg
        );
#else
    emit CommunicationEngine::instance()->signal_handleProject_result(
        absCmd->m_object, absCmd->m_cmdType,
        QVector<QVariant>() << QVariant(sProjectName) << fileNameList,
        isOk, sErrMsg);
#endif
}

void CommunicationThread::saveProject(AbstractCmd *absCmd)
{
    QString sErrMsg;
    QString sProjectName;
    bool isOk = true;

    CmdCommonValue *cmd = dynamic_cast<CmdCommonValue *>(absCmd);
    if (!cmd) {
        sErrMsg = tr("Failed to save project.") + SPACE_AND_CONVERT_PARAMETERS_FALID;
        isOk = false;
    }

    if (isOk) {
        sProjectName = cmd->m_value.toString();
    }

    if (isOk) {
        isOk = m_commInstance->saveProject(InoSyncProjcetInfoType_ProgramFiles, sProjectName);
        if (!isOk) {
            sErrMsg = tr("Failed to save project.");
        }
    }

    emit CommunicationEngine::instance()->signal_handleProject_result(
        absCmd->m_object, absCmd->m_cmdType, QVariant(sProjectName),
        isOk, sErrMsg);
}

void CommunicationThread::saveAsProject(AbstractCmd *absCmd)
{
    QString sErrMsg;
    QVector<QVariant> vecValues;
    QString sProjectName;
    QString sNewProjectName;
    QString sActiveProjectName;    
    bool isOk = true;

    CmdCommonValue *cmd = dynamic_cast<CmdCommonValue *>(absCmd);
    if (!cmd) {
        sErrMsg = tr("Failed to rename project.") + SPACE_AND_CONVERT_PARAMETERS_FALID;
        isOk = false;
    }

    if (isOk) {
        vecValues = cmd->m_value.value<QVector<QVariant>>();
        if (vecValues.count() < 2) {
            sErrMsg = tr("Failed to save project as the parameters are invalid.");
            isOk = false;
        }
    }

    if (isOk) {
        sProjectName = vecValues.at(0).toString();
        sNewProjectName = vecValues.at(1).toString();
        sErrMsg = m_commInstance->isProjectNameValid(sNewProjectName);
        if (!sErrMsg.isEmpty()) {
            isOk = false;
            sErrMsg = tr("Failed to save project as the project name is invalid.");
        }
    }

    if (isOk) {
        bool isExist = m_commInstance->isProjectExisted(sNewProjectName);
        if (isExist) {
            sErrMsg = tr("The project already exists.");
            isOk = false;
        }
    }

    if (isOk) {
        isOk = m_commInstance->copyProject(sProjectName);
        if (isOk) {
            sErrMsg = tr("Failed to save project for copy error.");
        }
    }

    if (isOk) {
        isOk = m_commInstance->pasteProject(sNewProjectName);
        if (isOk) {
            sErrMsg = tr("Failed to save project for paste error.");
        }
    }

    emit CommunicationEngine::instance()->signal_handleProject_result(
        absCmd->m_object, absCmd->m_cmdType,
        isOk ? QVariant(sNewProjectName) : QVariant(), isOk, sErrMsg);
}

void CommunicationThread::getProjectFileList(AbstractCmd *absCmd)
{
    QString sErrMsg;
    QString sProjectName;
    QVector<InoProjectFileInfo> vecProjectFiles;
    bool isOk = true;

    CmdCommonValue *cmd = dynamic_cast<CmdCommonValue *>(absCmd);
    if (!cmd) {
        sErrMsg = tr("Failed to get project file list.") + SPACE_AND_CONVERT_PARAMETERS_FALID;
        isOk = false;
    }

    if (isOk) {
        sProjectName = cmd->m_value.toString();
        if (sProjectName.isEmpty()) {
            isOk = false;
        }
    }

    if (isOk) {
        // program file
        vecProjectFiles.append(
            {InoProjectFileInfo::ProjectFile_ProgramFile,
             QString(":/programming/image/programming/icon/main.png"),
             m_commInstance->getProgramFileList()});

        // point file
        vecProjectFiles.append(
            {InoProjectFileInfo::ProjectFile_RobotPointFile,
             QString(":/programming/image/programming/icon/robot_point.png"),
             m_commInstance->getRPointFileList()});
        vecProjectFiles.append(
            {InoProjectFileInfo::ProjectFile_JointPointFile,
             QString(":/programming/image/programming/icon/joint_point.png"),
             m_commInstance->getJPointFileList()});

        // labels
        std::vector<std::string> vecLabelFiles;
        vecLabelFiles.push_back("Labels.jsn");
        vecProjectFiles.append(
            {InoProjectFileInfo::ProjectFile_LabelFile,
             QString(":/programming/image/programming/icon/label.png"),
             std::move(vecLabelFiles)});

        // user define warning
        vecProjectFiles.append(
            {InoProjectFileInfo::ProjectFile_UserDefineWarningFile,
             QString(":/programming/image/programming/icon/warning.png"),
             m_commInstance->getDefineWarningFileList()});

        // script
        vecProjectFiles.append(
            {InoProjectFileInfo::ProjectFile_ScriptFile,
             QString(":/programming/image/programming/icon/script.png"),
             getScriptFileList(sProjectName)});

        vecProjectFiles.append(
            {InoProjectFileInfo::ProjectFile_PalletFile,
             QString(":/programming/image/programming/icon/pallet.svg"),
             getPalletFileList(sProjectName)});

        //tempVariable
        std::vector<std::string> vecTempVariableFiles;
        vecLabelFiles.push_back("LuaVariables.jsn");
        vecProjectFiles.append(
            {InoProjectFileInfo::ProjectFile_TempVarFile,
             QString(":/programming/image/programming/icon/label.png"),
             std::move(vecLabelFiles)});
    }

    emit CommunicationEngine::instance()->signal_handleProject_result(
        absCmd->m_object, absCmd->m_cmdType,
        isOk ? QVariant::fromValue(vecProjectFiles) : QVariant(),
        isOk, sErrMsg);
}

void CommunicationThread::reloadActiveProject(AbstractCmd *absCmd)
{
    QString sErrMsg;
    QString sProjectName;
    QString sActiveProjectName;
    bool isOk = true;

    CmdCommonValue *cmd = dynamic_cast<CmdCommonValue *>(absCmd);
    if (!cmd) {
        isOk = false;
    }

    if (isOk) {
        sProjectName = cmd->m_value.toString();
        sActiveProjectName = m_commInstance->getActiveProjectName();
        if (sProjectName.isEmpty() && sActiveProjectName.isEmpty()) {
            isOk = false;
            sErrMsg = tr("Project is not loaded, please load a project or try to reconnect to the controller.");
        }
    }

    if (isOk) {
        if (0 == sProjectName.compare(sActiveProjectName)) {
            isOk = false;
        }
    }

    emit CommunicationEngine::instance()->signal_handleProject_result(
        absCmd->m_object, absCmd->m_cmdType, sActiveProjectName,
        isOk, QString());
}

void CommunicationThread::getRobotPointFileList(AbstractCmd *absCmd)
{
    QStringList listFiles;

    std::vector<std::string> vecFiles = m_commInstance->getRPointFileList();
    for (const std::string &file : vecFiles) {
        listFiles << QString::fromStdString(file);
    }

    emit CommunicationEngine::instance()->signal_handleProject_result(
        absCmd->m_object, absCmd->m_cmdType, QVariant(listFiles),
        true, QString());
}

void CommunicationThread::setCurRobotPointFile(AbstractCmd *absCmd)
{
    QString sErrMsg;
    bool isOk = true;

    CmdCommonValue *cmd = dynamic_cast<CmdCommonValue *>(absCmd);
    if (!cmd) {
        sErrMsg = tr("Failed to set current point file.") + SPACE_AND_CONVERT_PARAMETERS_FALID;
        isOk = false;
    }

    if (isOk) {
        m_commInstance->setCurRPointFile(cmd->m_value.toString());
    }

    emit CommunicationEngine::instance()->signal_handleProject_result(
        absCmd->m_object, absCmd->m_cmdType, QVariant(), isOk, sErrMsg);
}

void CommunicationThread::getDefaultRPointFileName(AbstractCmd *absCmd)
{
    QString sErrMsg;
    QString sFileName;
    bool isOk = true;

    bool isUpperLimit = m_commInstance->isRPointFileUpperLimit();
    if (isUpperLimit) {
        sErrMsg = tr("The number of point files reaches the limit.");
        isOk = false;
    }

    if (isOk) {
        sFileName = m_commInstance->getDefaultRPFileName();
    }

    emit CommunicationEngine::instance()->signal_handleProject_result(
        absCmd->m_object, absCmd->m_cmdType, sFileName, isOk, sErrMsg);
}

void CommunicationThread::createRobotPointFile(AbstractCmd *absCmd)
{
    QString sErrMsg;
    QString sFileName;
    bool isOk = true;

    CmdCommonValue *cmd = dynamic_cast<CmdCommonValue *>(absCmd);
    if (!cmd) {
        sErrMsg = tr("Failed to create point file.") + SPACE_AND_CONVERT_PARAMETERS_FALID;
        isOk = false;
    }

    if (isOk) {
        sFileName = cmd->m_value.toString();
        std::string msg;
        isOk = m_commInstance->isRPointFileNameValid(sFileName, msg);
        if (!isOk) {
            sErrMsg = tr("Illegal point file name.");
        }
    }

    if (isOk) {
        bool isUpperLimit = m_commInstance->isRPointFileUpperLimit();
        if (isUpperLimit) {
            sErrMsg = tr("The number of point files reaches the limit.");
            isOk = false;
        }
    }

    if (isOk) {
        bool isExist = m_commInstance->isRPointFileExist(sFileName);
        if (isExist) {
            sErrMsg = tr("Point file has already exists.");
            isOk = false;
        }
    }

    if (isOk) {
        isOk = m_commInstance->createRPointFile(sFileName);
        if (!isOk) {
            sErrMsg = tr("Failed to create point file.");
        }
    }

    if (isOk) {
        isOk = m_commInstance->saveProject(InoSyncProjcetInfoType_GlobalRPoint);
        if (!isOk) {
            // 移除未保存成功的点文件
            FileUtils::delFile(CONTROLLER_TMP_DIR_PATH);
            m_commInstance->deleteRPointFile(sFileName);
            sErrMsg = tr("Failed to save point file.");
        }
    }

    if(isOk){
        emit CommunicationEngine::instance()->signal_pPorintFileChanged(QStringList()<<(sFileName + ".pts"), AddPointFile);
    }

    emit CommunicationEngine::instance()->signal_handleProject_result(
        absCmd->m_object, absCmd->m_cmdType,
        isOk ? QVariant(sFileName) : QVariant(), isOk, sErrMsg);
}

void CommunicationThread::deleteRobotPointFile(AbstractCmd *absCmd)
{
    QString sErrMsg;
    QString sFileName;
    bool isOk = true;

    CmdCommonValue *cmd = dynamic_cast<CmdCommonValue *>(absCmd);
    if (!cmd) {
        sErrMsg = tr("Failed to delete point file.") + SPACE_AND_CONVERT_PARAMETERS_FALID;
        isOk = false;
    }

    if (isOk) {
        sFileName = cmd->m_value.toString();
        if (sFileName.compare(DEFAULT_ROBOT_POINT_FILE) == 0) {
            sErrMsg = tr("P.pts is not allowed to delete.");
            isOk = false;
        }
    }

    if (isOk) {
        std::string msg;
        isOk = m_commInstance->isRPointFileNameValid(sFileName, msg);
        if (!isOk) {
            sErrMsg = tr("The file name is invalid.");
        }
    }

    if (isOk) {
        isOk = m_commInstance->isRPointFileExist(sFileName);
        if (!isOk) {
            sErrMsg = tr("Point file [%1] does not exist.").arg(sFileName);
        }
    }

    if (isOk) {
        isOk = m_commInstance->deleteRPointFile(sFileName);
        if (!isOk) {
            sErrMsg = tr("Failed to delete point file.");
        }
    }

    if (isOk) {
        isOk = m_commInstance->saveProject(InoSyncProjcetInfoType_GlobalRPoint);
        if (!isOk) {
            m_commInstance->addRobotPointConfig(sFileName);
            sErrMsg = tr("Failed to delete point file from the project.");
        }
    }
    if(isOk){
        emit CommunicationEngine::instance()->signal_pPorintFileChanged(QStringList()<<sFileName, DeletePointFile);
    }

    emit CommunicationEngine::instance()->signal_handleProject_result(
        absCmd->m_object, absCmd->m_cmdType,
        isOk ? QVariant(sFileName) : QVariant(), isOk, sErrMsg);
}

void CommunicationThread::copyRobotPointFile(AbstractCmd *absCmd)
{
    QString sErrMsg;
    QString sFileName;
    bool isOk = true;

    CmdCommonValue *cmd = dynamic_cast<CmdCommonValue *>(absCmd);
    if (!cmd) {
        sErrMsg = tr("Failed to copy point file.") + SPACE_AND_CONVERT_PARAMETERS_FALID;
        isOk = false;
    }

    if (isOk) {
        sFileName = cmd->m_value.toString();
        isOk = m_commInstance->isRPointFileExist(sFileName);
        if (!isOk) {
            sErrMsg = tr("Point file does not exist.");
        }
    }

    if (isOk) {
        isOk = m_commInstance->copyRPointFile(sFileName);
        if (!isOk) {
            sErrMsg = tr("Failed to copy point file.");
        }
    }

    emit CommunicationEngine::instance()->signal_handleProject_result(
        absCmd->m_object, absCmd->m_cmdType, QVariant(sFileName), isOk, sErrMsg);
}

void CommunicationThread::genPasteRobotFileName(AbstractCmd *absCmd)
{
    QString sErrMsg;
    QString sFileName;
    bool isOk = true;

    bool isUpperLimit = m_commInstance->isRPointFileUpperLimit();
    if (isUpperLimit) {
        sErrMsg = tr("The number of point files reaches the limit.");
        isOk = false;
    }

    if (isOk) {
        QString sRPointFileName = m_commInstance->getCopiedRPointFileName();
        if (!sRPointFileName.isEmpty()) {
            sFileName = m_commInstance->getDefaultRPFileName(sRPointFileName);
        }
    }

    emit CommunicationEngine::instance()->signal_handleProject_result(
        absCmd->m_object, absCmd->m_cmdType, QVariant(sFileName), isOk, sErrMsg);
}

void CommunicationThread::pasteRobotPointFile(AbstractCmd *absCmd)
{
    QString sErrMsg;
    QString sFileName;
    bool isOk = true;

    CmdCommonValue *cmd = dynamic_cast<CmdCommonValue *>(absCmd);
    if (!cmd) {
        sErrMsg = tr("Failed to paste point file.") + SPACE_AND_CONVERT_PARAMETERS_FALID;
        isOk = false;
    }

    if (isOk) {
        sFileName = cmd->m_value.toString();
        if (sFileName.compare(DEFAULT_ROBOT_POINT_FILE) == 0) {
            sErrMsg = tr("P.pts is not allowed to paste.");
            isOk = false;
        }
    }

    if (isOk) {
        std::string errMsg;
        isOk = m_commInstance->isRPointFileNameValid(sFileName, errMsg);
        if (!isOk) {
            sErrMsg = tr("The point file name is invalid.");
            isOk = false;
        }
    }

    if (isOk) {
        bool isExist = m_commInstance->isRPointFileExist(sFileName);
        if (isExist) {
            sErrMsg = tr("The point file already exists.");
            isOk = false;
        }
    }

    if (isOk) {
        isOk = m_commInstance->pasteRPointFile(sFileName);
        if (!isOk) {
            m_commInstance->deleteRPointFile(sFileName);
            sErrMsg = tr("Failed to paste point file.");
        }
    }

    if (isOk) {
        isOk = m_commInstance->saveProject(InoSyncProjcetInfoType_GlobalRPoint);
        if (!isOk) {
            // 移除未保存成功的点文件
            m_commInstance->deleteRPointFile(sFileName);
            sErrMsg = tr("Failed to save point file to the project.");
        }
    }
    if(isOk){
        emit CommunicationEngine::instance()->signal_pPorintFileChanged(QStringList()<<(sFileName + ".pts"), AddPointFile);
    }
    emit CommunicationEngine::instance()->signal_handleProject_result(
        absCmd->m_object, absCmd->m_cmdType,
        isOk ? QVariant(sFileName) : QVariant(), isOk, sErrMsg);
}

void CommunicationThread::readRobotPoints(AbstractCmd *absCmd)
{
    QVector<InoRPointInfo> vecRPointInfos = m_commInstance->readRPoints();

    emit CommunicationEngine::instance()->signal_handleProject_result(
        absCmd->m_object, absCmd->m_cmdType,
        QVariant::fromValue(vecRPointInfos), true,
        dynamic_cast<CmdCommonValue *>(absCmd)->m_value.toString());
}

void CommunicationThread::checkRobotPointIsExist(AbstractCmd *absCmd)
{
    int nIndex = INVALID_INDEX;
    QString sErrMsg;
    bool isOk = true;

    CmdCommonValue *cmd = dynamic_cast<CmdCommonValue *>(absCmd);
    if (!cmd) {
        sErrMsg = tr("Failed to check whether the point file exists.") + SPACE_AND_CONVERT_PARAMETERS_FALID;
        isOk = false;
    }

    if (isOk) {
        nIndex = cmd->m_value.toInt();
        isOk = m_commInstance->findRPoint(nIndex);
        if (!isOk) {
            sErrMsg = tr("The point does not exist.");
        }
    }

    emit CommunicationEngine::instance()->signal_handleProject_result(
        absCmd->m_object, absCmd->m_cmdType,
        isOk ? QVariant(nIndex) : QVariant(), isOk, sErrMsg);
}

void CommunicationThread::addRobotPoint(AbstractCmd *abcCmd)
{
    int nIndex = INVALID_INDEX;
    QString sErrMsg;

    auto [sLabelName] = ((CmdDatas<std::string> *)abcCmd)->m_data;

    bool isOk = m_commInstance->addRPoint(nIndex, sLabelName);
    if (!isOk || nIndex <= INVALID_INDEX) {
        isOk = false;
        sErrMsg = tr("Failed to add the point.");
    }

    if (isOk) {
        isOk = m_commInstance->saveRPoints();
        if (!isOk) {
            m_commInstance->deleteRPoint(nIndex);
            sErrMsg = tr("Failed to add the point due to save error.");
        }
    }
    if(isOk){
        emit CommunicationEngine::instance()->
            signal_virtualKeyBoard_LabelChanged(
                LabelType_GlobalVar_P, "", QString::number(nIndex));
        emit CommunicationEngine::instance()->
            signal_virtualKeyBoard_LabelChanged(
            LabelType_GlobalVar_P, "", QString::fromStdString(sLabelName));
    }
    emit CommunicationEngine::instance()->signal_handleProject_result(
        abcCmd->m_object, abcCmd->m_cmdType, QVariant(nIndex), isOk, sErrMsg);
}

void CommunicationThread::addRobotPointByIndex(AbstractCmd *absCmd)
{
    int nIndex = INVALID_INDEX;
    QString sErrMsg;

    auto [nNewIndex] = ((CmdDatas<int> *)absCmd)->m_data;
    bool isOk = false;

    bool isExist = m_commInstance->findRPoint(nNewIndex);
    if(isExist){
        sErrMsg = tr("P[%1] already exists.").arg(nNewIndex, 4, 10, QLatin1Char('0'));
        isOk = false;
    }
    else{
        isOk = true;
    }

    if(isOk){
        isOk = m_commInstance->addRPoint(nIndex, "");
        if (!isOk || nIndex <= INVALID_INDEX) {
            isOk = false;
            sErrMsg = tr("Failed to add the point.");
        }
    }

    if (isOk) {
        isOk = m_commInstance->renameRPoint(nIndex, nNewIndex);
        if (!isOk) {
            m_commInstance->deleteRPoint(nIndex);
            sErrMsg = tr("Failed to rename point.");
        }
    }

    if (isOk) {
        isOk = m_commInstance->saveRPoints();
        if (!isOk) {;
            m_commInstance->deleteRPoint(nNewIndex);
            sErrMsg = tr("Failed to add the point due to save error.");
        }
    }

    emit CommunicationEngine::instance()->signal_handleProject_result(
        absCmd->m_object, absCmd->m_cmdType, QVariant(nNewIndex), isOk, sErrMsg);
}

void CommunicationThread::copyRobotPoint(AbstractCmd *absCmd)
{
    QString sErrMsg;
    bool isOk = true;

    CmdCommonValue *cmd = dynamic_cast<CmdCommonValue *>(absCmd);
    if (!cmd) {
        sErrMsg = tr("Failed to copy point.") + SPACE_AND_CONVERT_PARAMETERS_FALID;
        isOk = false;
    }

    if (isOk) {
        QList<int> copiedRPIndexs = cmd->m_value.value<QList<int>>();

        std::vector<int> indexs;
        for (const int &index : copiedRPIndexs) {
            indexs.push_back(index);
        }

        isOk = m_commInstance->copyRPoint(indexs);
        if (!isOk) {
            sErrMsg = tr("Failed to copy point.");
        }
    }

    emit CommunicationEngine::instance()->signal_handleProject_result(
        absCmd->m_object, absCmd->m_cmdType, QVariant(), isOk, sErrMsg);
}

void CommunicationThread::pasteRobotPoint(AbstractCmd *absCmd)
{
    QString sErrMsg;
    std::vector<int> indexs;
    bool isOk = true;

    if (isOk) {
        isOk = m_commInstance->pasteRPoint(indexs);
        if (!isOk) {
            sErrMsg = tr("Failed to paste point.");
        }
    }

    if (isOk) {
        isOk = m_commInstance->saveRPoints();
        if (!isOk) {
            for (const int &index : indexs) {
                m_commInstance->deleteRPoint(index);
            }

            sErrMsg = tr("Failed to add the point due to save error.");
        }
    }
    if(isOk){
        for (const int &index : indexs) {
            emit CommunicationEngine::instance()->
                signal_virtualKeyBoard_LabelChanged(
                LabelType_GlobalVar_P, "", QString::number(index));
        }
    }

    emit CommunicationEngine::instance()->signal_handleProject_result(
        absCmd->m_object, absCmd->m_cmdType, QVariant::fromValue(indexs), isOk, sErrMsg);
}

void CommunicationThread::deleteRobotPoint(AbstractCmd *absCmd)
{
    QString sErrMsg;
    int nIndex = INVALID_INDEX;
    QString sLabel;
    QVector<QVariant> vecValues;
    bool isOk = true;

    QMap<int,QString> indexAndLabelMap;
    QMap<int,QString> deletedIndexAndLabelMap;

    CmdCommonValue *cmd = dynamic_cast<CmdCommonValue *>(absCmd);
    if (!cmd) {
        sErrMsg = tr("Failed to delete point.") + SPACE_AND_CONVERT_PARAMETERS_FALID;
        isOk = false;
    }

    if (isOk) {
        vecValues = cmd->m_value.value<QVector<QVariant>>();
        if (vecValues.count() < 1) {
            sErrMsg = tr("Failed to delete point as the paranmeters are invalid.");
            isOk = false;
        }
    }

    if(isOk){
        indexAndLabelMap = vecValues.at(0).value<QMap<int,QString>>();
        QMap<int,QString>::const_iterator it;
        for (it = indexAndLabelMap.constBegin(); it != indexAndLabelMap.constEnd(); ++it) {
            nIndex = it.key();
            isOk = m_commInstance->findRPoint(nIndex);
            if (!isOk) {
                sErrMsg = tr("P[%1] is invalid.").arg(nIndex, 4, 10, QLatin1Char('0'));
                break;
            }
        }
    }

    if (isOk) {
        QMap<int,QString>::const_iterator it;
        for (it = indexAndLabelMap.constBegin(); it != indexAndLabelMap.constEnd(); ++it) {
            nIndex = it.key();
            sLabel = it.value();
            isOk = m_commInstance->deleteRPoint(nIndex);
            if (!isOk) {
                sErrMsg = tr("Failed to delete point.");
                break;
            }
            else{
                deletedIndexAndLabelMap.insert(nIndex,sLabel);
            }
        }

    }

    if (isOk) {
        isOk = m_commInstance->saveRPoints();
        if (!isOk) {
            QMap<int,QString>::const_iterator it;
            for (it = deletedIndexAndLabelMap.constBegin(); it != deletedIndexAndLabelMap.constEnd(); ++it){
                nIndex = it.key();
                sLabel = it.value();
                m_commInstance->addRPoint(nIndex,QString(sLabel).toStdString());
            }
            sErrMsg = tr("Failed to delete point due to save error.");
        }
    }

    emit CommunicationEngine::instance()->signal_handleProject_result(
        absCmd->m_object, absCmd->m_cmdType, QVariant(), isOk, sErrMsg);
    if(isOk){
        QMap<int,QString>::const_iterator it;
        for (it = deletedIndexAndLabelMap.constBegin(); it != deletedIndexAndLabelMap.constEnd(); ++it){
            sLabel = it.value();
            emit CommunicationEngine::instance()->
                signal_virtualKeyBoard_LabelChanged(LabelType_GlobalVar_P,
                                                    sLabel,
                                                    "");
        }

    }

}

void CommunicationThread::changeRobotPoint(AbstractCmd *absCmd)
{
    QString sErrMsg;
    InoRPointInfo robotPointInfo;
    QString sOriginLabel;
    QVector<QVariant> vecValues;
    bool isOk = true;

    CmdCommonValue *cmd = dynamic_cast<CmdCommonValue *>(absCmd);
    if (!cmd) {
        sErrMsg = tr("Failed to change point.") + SPACE_AND_CONVERT_PARAMETERS_FALID;
        isOk = false;
    }

    if (isOk) {
        vecValues = cmd->m_value.value<QVector<QVariant>>();
        if (vecValues.count() < 2) {
            sErrMsg = tr("Failed to modify the point as the parameters are invalid.");
            isOk = false;
        }
    }

    if (isOk) {
        robotPointInfo = vecValues.at(0).value<InoRPointInfo>();
        QString curRPointFile = m_commInstance->curRPointFile();
        if (!curRPointFile.isEmpty() && curRPointFile.compare(DEFAULT_ROBOT_POINT_FILE)
            && !robotPointInfo.label.isEmpty()) {
            sErrMsg = tr("Labels are not supported for modification in %1.").arg(curRPointFile);
            isOk = false;
        }
    }

    if (isOk) {
        sOriginLabel = vecValues.at(1).toString();
        if (!robotPointInfo.label.isEmpty() && sOriginLabel.compare(robotPointInfo.label)) {
            bool isExist = m_commInstance->isLabelExisted(robotPointInfo.label);
            if (isExist) {
                sErrMsg = tr("Failed to edit the label as it already exists.");
                isOk = false;
            }
        }
    }

    if (isOk) {
        isOk = m_commInstance->changeRPoint(robotPointInfo);
        if (!isOk) {
            sErrMsg = tr("Failed to change point.");
        }
    }

    if (isOk) {
        isOk = m_commInstance->saveRPoints();
        if (!isOk) {
            sErrMsg = tr("Failed to modify the point due to save error.");
        }
    }

    emit CommunicationEngine::instance()->signal_handleProject_result(
        absCmd->m_object, absCmd->m_cmdType,
        isOk ? QVariant::fromValue(robotPointInfo) : QVariant(), isOk, sErrMsg);

    if (isOk && sOriginLabel.compare(robotPointInfo.label)) {
        emit CommunicationEngine::instance()->signal_virtualKeyBoard_LabelChanged(
            LabelType_GlobalVar_P, sOriginLabel, robotPointInfo.label);
    }

}

void CommunicationThread::changeRobotPointPos(AbstractCmd *absCmd)
{
    QString sErrMsg;
    RoadPoint roadPoint;
    int nIndex = INVALID_INDEX;
    QVector<QVariant> vecValues;
    MRobPosItem item;
    bool isOk = true;

    CmdCommonValue *cmd = dynamic_cast<CmdCommonValue *>(absCmd);
    if (!cmd) {
        sErrMsg = tr("Failed to change point.") + SPACE_AND_CONVERT_PARAMETERS_FALID;
        isOk = false;
    }

    if (isOk) {
        vecValues = cmd->m_value.value<QVector<QVariant>>();
        if (vecValues.count() < 2) {
            sErrMsg = tr("Failed to modify the point as the parameters are invalid.");
            isOk = false;
        }

        roadPoint = vecValues.at(1).value<RoadPoint>();
    }

    if (isOk) {
        nIndex = vecValues.at(0).toInt();
        if (nIndex <= INVALID_INDEX) {
            sErrMsg = tr("index is invalid.");
            isOk = false;
        }
    }

    QString curLoadedRPFileName = m_commInstance->curLoadedRPointFile();
    if (curLoadedRPFileName.isEmpty()) {
        curLoadedRPFileName = m_commInstance->curRPointFile();
    }

    if (isOk) {
        item = m_commInstance->getRobotMRobPosItem(nIndex);
        if (item.PointNo < 0) {
            sErrMsg = tr("P[%1] is not exists.").arg(nIndex, 4, 10, QLatin1Char('0'));
            isOk = false;
        }

        item.PData = MetaTypeConversion::tp2InoApi_roadPoint2RobPos(roadPoint);
    }

    if (isOk) {
        if (m_commInstance->isProgramNotRunning()) {
            isOk = m_commInstance->changeRPoint(item);
            if (isOk) {
                isOk = m_commInstance->saveProject(InoSyncProjcetInfoType_GlobalRPoint);
            }
        } else {
            isOk = m_commInstance->changeRPointInDebug(MAIN_PROGRAM_FILE,
                                                       MAIN_TASK_ID, item);
        }

        if (!isOk) {
            sErrMsg = tr("Failed to change point.");
        }
    }

#ifdef INOCOBOTTP_MSVC_QT5
    qRegisterMetaType<RoadPoint>("RoadPoint");
#endif
    emit CommunicationEngine::instance()->signal_handleProject_result(
        absCmd->m_object, absCmd->m_cmdType,
        isOk ? QVariant::fromValue(roadPoint) : QVariant(), isOk, sErrMsg);
}

void CommunicationThread::replaceRobotPoint(AbstractCmd *absCmd)
{
    QString sErrMsg;
    int nIndex = INVALID_INDEX;
    InoRPointInfo robotPointInfo;
    bool isOk = true;

    CmdCommonValue *cmd = dynamic_cast<CmdCommonValue *>(absCmd);
    if (!cmd) {
        sErrMsg = tr("Failed to replace point.") + SPACE_AND_CONVERT_PARAMETERS_FALID;
        isOk = false;
    }

    if (isOk) {
        nIndex = cmd->m_value.toInt();
        isOk = m_commInstance->replaceRPointCoordValue(nIndex);
        if (!isOk) {
            sErrMsg = tr("Failed to replace point.");
        }
    }

    if (isOk) {
        isOk = m_commInstance->saveRPoints();
        if (!isOk) {
            sErrMsg = tr("Failed to replace the point due to save error.");
        }
    }

    if (isOk) {
        robotPointInfo = m_commInstance->getRPoint(nIndex);
    }

    emit CommunicationEngine::instance()->signal_handleProject_result(
        absCmd->m_object, absCmd->m_cmdType,
        isOk ? QVariant::fromValue(robotPointInfo) : QVariant(), isOk, sErrMsg);
}

void CommunicationThread::renameRobotPoint(AbstractCmd *absCmd)
{
    QString sErrMsg;
    int nIndex = INVALID_INDEX;
    int nNewIndex = INVALID_INDEX;
    QVector<QVariant> vecValues;
    InoRPointInfo robotPointInfo;
    bool isOk = true;

    CmdCommonValue *cmd = dynamic_cast<CmdCommonValue *>(absCmd);
    if (!cmd) {
        sErrMsg = tr("Failed to rename point.") + SPACE_AND_CONVERT_PARAMETERS_FALID;
        isOk = false;
    }

    if (isOk) {
        vecValues = cmd->m_value.value<QVector<QVariant>>();
        if (vecValues.count() < 2) {
            sErrMsg = tr("Failed to rename the point as the parameters are invalid.");
            isOk = false;
        }
    }

    if (isOk) {
        nIndex = vecValues.at(0).toInt();
        nNewIndex = vecValues.at(1).toInt();
        bool isExist = Communication::instance()->findRPoint(nNewIndex);
        if (isExist) {
            sErrMsg = tr("P[%1] already exists.").arg(nNewIndex, 4, 10, QLatin1Char('0'));
            isOk = false;
        }
    }

    if (isOk) {
        isOk = m_commInstance->renameRPoint(nIndex, nNewIndex);
        if (!isOk) {
            sErrMsg = tr("Failed to rename point.");
        }
    }

    if (isOk) {
        isOk = m_commInstance->saveRPoints();
        if (!isOk) {
            m_commInstance->renameRPoint(nNewIndex, nIndex);
            sErrMsg = tr("Failed to rename the point due to save error.");
        }
    }

    if (isOk) {
        robotPointInfo = m_commInstance->getRPoint(nNewIndex);
        emit CommunicationEngine::instance()->
            signal_virtualKeyBoard_LabelChanged(LabelType_GlobalVar_P,
                                                QString::number(nIndex),
                                                QString::number(nNewIndex));
    }

    emit CommunicationEngine::instance()->signal_handleProject_result(
        absCmd->m_object, absCmd->m_cmdType,
        isOk ? QVariant::fromValue(robotPointInfo) : QVariant(), isOk, sErrMsg);
}

void CommunicationThread::importRobotPointFile(AbstractCmd *absCmd)
{
    QString sErrMsg;
    QVector<QString> fileNames;
    QVector<QString> filePaths;
    QVector<QVariant> vecValues;
    bool isOk = true;

    CmdCommonValue *cmd = dynamic_cast<CmdCommonValue *>(absCmd);
    if (!cmd) {
        sErrMsg = tr("Failed to import point file.") + SPACE_AND_CONVERT_PARAMETERS_FALID;
        isOk = false;
    }

    if (isOk) {
        vecValues = cmd->m_value.value<QVector<QVariant>>();
        if (vecValues.count() < 2) {
            sErrMsg = tr("Failed to import the point file as the parameters are invalid.");
            isOk = false;
        }
    }

    if (isOk) {
        fileNames = vecValues.at(0).value<QVector<QString>>();
        if (fileNames.isEmpty()) {
            sErrMsg = tr("Failed to parse point file name.");
            isOk = false;
        }
    }

    if (isOk) {
        filePaths = vecValues.at(1).value<QVector<QString>>();
        if (filePaths.isEmpty()) {
            sErrMsg = tr("Failed to parse point file path.");
            isOk = false;
        }
    }

    if (isOk) {
        std::string msg;
        for (const QString &fileName : fileNames) {
            isOk = m_commInstance->isRPointFileNameValid(fileName, msg);
            if (!isOk) {
                sErrMsg = tr("The point file name is invalid.");
                isOk = false;
                break;
            }
        }
    }

    if (isOk) {
        bool isUpperLimit = m_commInstance->isRPointFileUpperLimit(fileNames.count());
        if (isUpperLimit) {
            sErrMsg = tr("The number of point files reaches the limit.");
            isOk = false;
        }
    }

    if (isOk) {
        for (const QString &fileName : fileNames) {
            bool isExist = m_commInstance->isRPointFileExist(fileName);
            if (isExist) {
                sErrMsg = tr("The point file is exist.");
                isOk = false;
                break;
            }
        }
    }

    if (isOk) {
        for (int i = 0; i < fileNames.count(); i++) {
            isOk = m_commInstance->importLocalRPointFile(fileNames.at(i), filePaths.at(i));
            if (!isOk) {
                sErrMsg = tr("Failed to import point file.");
                break;
            }

            emit CommunicationEngine::instance()->signal_pPorintFileChanged(QStringList()<<(fileNames.at(i) + ".pts"), AddPointFile);
        }
    }

    if (isOk) {
        isOk = m_commInstance->saveProject(InoSyncProjcetInfoType_GlobalRPoint);
        if (!isOk) {
            sErrMsg = tr("Failed to import point file to the project.");
        }
    }

    emit CommunicationEngine::instance()->signal_handleProject_result(
        absCmd->m_object, absCmd->m_cmdType,
        isOk ? QVariant::fromValue(fileNames) : QVariant(), isOk, sErrMsg);
}

void CommunicationThread::exportRobotPointFile(AbstractCmd *absCmd)
{
    QString sErrMsg;
    QString sRPointFileName = QString();
    QString sExportFilePath = QString();
    QVector<QVariant> vecValues;
    bool isOk = true;

    CmdCommonValue *cmd = dynamic_cast<CmdCommonValue *>(absCmd);
    if (!cmd) {
        sErrMsg = tr("Failed to export point file.") + SPACE_AND_CONVERT_PARAMETERS_FALID;
        isOk = false;
    }

    if (isOk) {
        vecValues = cmd->m_value.value<QVector<QVariant>>();
        if (vecValues.count() < 2) {
            sErrMsg = tr("Failed to export the point file as the parameters are invalid.");
            isOk = false;
        }
    }

    if (isOk) {
        sRPointFileName = vecValues.at(0).toString();
        if (sRPointFileName.isEmpty()) {
            sErrMsg = tr("Failed to parse point file name.");
            isOk = false;
        }
    }

    if (isOk) {
        sExportFilePath = vecValues.at(1).toString();
        if (sExportFilePath.isEmpty()) {
            sErrMsg = tr("Failed to parse export file path.");
            isOk = false;
        }
    }

    if (isOk) {
        isOk = m_commInstance->exportRPointFile(sRPointFileName, sExportFilePath);
        if (!isOk) {
            sErrMsg = tr("Failed to export point file.");
        }
    }

    emit CommunicationEngine::instance()->signal_handleProject_result(
        absCmd->m_object, absCmd->m_cmdType,
        isOk ? QVariant(sRPointFileName) : QVariant(), isOk, sErrMsg);
}

void CommunicationThread::getJointPointFileList(AbstractCmd *absCmd)
{
    QStringList listFiles;

    std::vector<std::string> vecFiles = m_commInstance->getJPointFileList();
    for (const std::string &file : vecFiles) {
        listFiles << QString::fromStdString(file);
    }

    if (!vecFiles.empty()) {
        m_commInstance->setCurJPointFile(QString::fromStdString(vecFiles.at(0)));
    }

    emit CommunicationEngine::instance()->signal_handleProject_result(
        absCmd->m_object, absCmd->m_cmdType, QVariant(listFiles), true, QString());
}

void CommunicationThread::setCurJointPointFile(AbstractCmd *absCmd)
{
    QString sErrMsg;
    bool isOk = true;

    CmdCommonValue *cmd = dynamic_cast<CmdCommonValue *>(absCmd);
    if (!cmd) {
        sErrMsg = tr("Failed to set current joint point file.") + SPACE_AND_CONVERT_PARAMETERS_FALID;
        isOk = false;
    }

    if (isOk) {
        m_commInstance->setCurJPointFile(cmd->m_value.toString());
    }

    emit CommunicationEngine::instance()->signal_handleProject_result(
        absCmd->m_object, absCmd->m_cmdType, QVariant(), isOk, sErrMsg);
}

void CommunicationThread::readJointPoints(AbstractCmd *absCmd)
{
    QVector<InoJPointInfo> vecJPointInfos = m_commInstance->readJPoints();

    emit CommunicationEngine::instance()->signal_handleProject_result(
        absCmd->m_object, absCmd->m_cmdType,
        QVariant::fromValue(vecJPointInfos), true,
        dynamic_cast<CmdCommonValue *>(absCmd)->m_value.toString());
}

void CommunicationThread::checkJointPointIsExist(AbstractCmd *absCmd)
{
    int nIndex = INVALID_INDEX;
    QString sErrMsg;
    bool isOk = true;

    CmdCommonValue *cmd = dynamic_cast<CmdCommonValue *>(absCmd);
    if (!cmd) {
        sErrMsg = tr("Failed to check wherther the joint point exists.") + SPACE_AND_CONVERT_PARAMETERS_FALID;
        isOk = false;
    }

    if (isOk) {
        nIndex = cmd->m_value.toInt();
        isOk = m_commInstance->findJPoint(nIndex);
        if (!isOk) {
            sErrMsg = tr("The joint point does not exist.");
        }
    }

    emit CommunicationEngine::instance()->signal_handleProject_result(
        absCmd->m_object, absCmd->m_cmdType,
        isOk ? QVariant(nIndex) : QVariant(), isOk, sErrMsg);
}

void CommunicationThread::addJointPoint(AbstractCmd *abcCmd)
{
    int nIndex = INVALID_INDEX;
    QString sErrMsg;

    auto [sLabelName] = ((CmdDatas<std::string> *)abcCmd)->m_data;

    bool isOk = m_commInstance->addJPoint(nIndex, sLabelName);
    if (!isOk || nIndex <= INVALID_INDEX) {
        isOk = false;
        sErrMsg = tr("Failed to add joint point.");
    }

    if (isOk) {
        isOk = m_commInstance->saveJPoints();
        if (!isOk) {
            m_commInstance->deleteJPoint(nIndex);
            sErrMsg = tr("Failed to save joint point file.");
        }

    }
    if(isOk){
        emit CommunicationEngine::instance()->signal_virtualKeyBoard_LabelChanged(
            LabelType_GlobalVar_JP,"",QString::number(nIndex));
        emit CommunicationEngine::instance()->
            signal_virtualKeyBoard_LabelChanged(
                LabelType_GlobalVar_JP, "", QString::fromStdString(sLabelName));
    }
    emit CommunicationEngine::instance()->signal_handleProject_result(
        abcCmd->m_object, abcCmd->m_cmdType, QVariant(nIndex), isOk, sErrMsg);
}

void CommunicationThread::addJointPointByIndex(AbstractCmd *absCmd)
{
    int nIndex = INVALID_INDEX;
    QString sErrMsg;

    auto [nNewIndex] = ((CmdDatas<int> *)absCmd)->m_data;
    bool isOk = false;

    bool isExist = Communication::instance()->findJPoint(nNewIndex);
    if (isExist) {
        sErrMsg = tr("JP[%1] already exists.").arg(nNewIndex, 4, 10, QLatin1Char('0'));
        isOk = false;
    }
    else{
        isOk = true;
    }

    if(isOk){
        isOk = m_commInstance->addJPoint(nIndex, "");
        if (!isOk || nIndex <= INVALID_INDEX) {
            isOk = false;
            sErrMsg = tr("Failed to add joint point.");
        }
    }

    if (isOk) {
        isOk = m_commInstance->renameJPoint(nIndex, nNewIndex);
        if (!isOk) {
            m_commInstance->deleteJPoint(nIndex);
            sErrMsg = tr("Failed to rename joint point.");
        }
    }

    if (isOk) {
        isOk = m_commInstance->saveJPoints();
        if (!isOk) {
            m_commInstance->deleteJPoint(nNewIndex);
            sErrMsg = tr("Failed to rename joint point due to save error.");
        }
    }

    emit CommunicationEngine::instance()->signal_handleProject_result(
        absCmd->m_object, absCmd->m_cmdType, QVariant(nNewIndex), isOk, sErrMsg);

}

void CommunicationThread::copyJointPoint(AbstractCmd *absCmd)
{
    QString sErrMsg;
    bool isOk = true;

    CmdCommonValue *cmd = dynamic_cast<CmdCommonValue *>(absCmd);
    if (!cmd) {
        sErrMsg = tr("Failed to copy point.") + SPACE_AND_CONVERT_PARAMETERS_FALID;
        isOk = false;
    }

    if (isOk) {
        QList<int> copiedJPIndexs = cmd->m_value.value<QList<int>>();

        std::vector<int> indexs;
        for (const int &index : copiedJPIndexs) {
            indexs.push_back(index);
        }

        isOk = m_commInstance->copyJPoint(indexs);
        if (!isOk) {
            sErrMsg = tr("Failed to copy joint point.");
        }
    }

    emit CommunicationEngine::instance()->signal_handleProject_result(
        absCmd->m_object, absCmd->m_cmdType, QVariant(), isOk, sErrMsg);
}

void CommunicationThread::pasteJointPoint(AbstractCmd *absCmd)
{
    QString sErrMsg;
    std::vector<int> indexs;
    bool isOk = true;

    if (isOk) {
        isOk = m_commInstance->pasteJPoint(indexs);
        if (!isOk) {
            sErrMsg = tr("Failed to paste joint point.");
        }
    }

    if (isOk) {
        isOk = m_commInstance->saveJPoints();
        if (!isOk) {
            for (const int &index : indexs) {
                m_commInstance->deleteJPoint(index);
            }

            sErrMsg = tr("Failed to paste joint point due to save error.");
        }
    }
    if(isOk){
        for (const int &index : indexs) {
            emit CommunicationEngine::instance()->
                signal_virtualKeyBoard_LabelChanged(
                  LabelType_GlobalVar_JP,"", QString::number(index));
        }
    }
    emit CommunicationEngine::instance()->signal_handleProject_result(
        absCmd->m_object, absCmd->m_cmdType, QVariant::fromValue(indexs), isOk, sErrMsg);
}

void CommunicationThread::deleteJointPoint(AbstractCmd *absCmd)
{
    QString sErrMsg;
    int nIndex = INVALID_INDEX;
    QString sLabel;
    QVector<QVariant> vecValues;

    QMap<int,QString> indexAndLabelMap;

    QMap<int,QString> deletedIndexAndLabelMap;

    bool isOk = true;
    CmdCommonValue *cmd = dynamic_cast<CmdCommonValue *>(absCmd);
    if (!cmd) {
        sErrMsg = tr("Failed to delete joint point.") + SPACE_AND_CONVERT_PARAMETERS_FALID;
        isOk = false;
    }

    if (isOk) {
        vecValues = cmd->m_value.value<QVector<QVariant>>();
        if (vecValues.count() < 1) {
            sErrMsg = tr("Failed to delete joint point as the parameters are invalid.");
            isOk = false;
        }
    }

    if(isOk){
        indexAndLabelMap = vecValues.at(0).value<QMap<int,QString>>();
        QMap<int,QString>::const_iterator it;
        for (it = indexAndLabelMap.constBegin(); it != indexAndLabelMap.constEnd(); ++it) {
            nIndex = it.key();
            isOk = m_commInstance->findJPoint(nIndex);
            if (!isOk) {
                sErrMsg = tr("JP[%1] is illegal.").arg(nIndex, 4, 10, QLatin1Char('0'));
                break;
            }
        }
    }

    if (isOk) {
        QMap<int,QString>::const_iterator it;
        for (it = indexAndLabelMap.constBegin(); it != indexAndLabelMap.constEnd(); ++it) {
            nIndex = it.key();
            sLabel = it.value();
            isOk = m_commInstance->deleteJPoint(nIndex);
            if (!isOk) {
                sErrMsg = tr("Failed to delete joint point.");
                break;
            }
            else{
                deletedIndexAndLabelMap.insert(nIndex,sLabel);
            }
        }

    }

    if (isOk) {
        isOk = m_commInstance->saveJPoints();
        if (!isOk) {
            QMap<int,QString>::const_iterator it;
            for (it = deletedIndexAndLabelMap.constBegin(); it != deletedIndexAndLabelMap.constEnd(); ++it){
                nIndex = it.key();
                sLabel = it.value();
                m_commInstance->addJPoint(nIndex,QString(sLabel).toStdString());
            }
            sErrMsg = tr("Failed to delete joint point due to save error.");
        }
    }

    emit CommunicationEngine::instance()->signal_handleProject_result(
        absCmd->m_object, absCmd->m_cmdType, QVariant(), isOk, sErrMsg);
    if(isOk){
        QMap<int,QString>::const_iterator it;
        for (it = deletedIndexAndLabelMap.constBegin(); it != deletedIndexAndLabelMap.constEnd(); ++it){
            sLabel = it.value();
            emit CommunicationEngine::instance()->
                signal_virtualKeyBoard_LabelChanged(LabelType_GlobalVar_JP,
                                                    sLabel,
                                                    "");
        }

    }

}

void CommunicationThread::replaceJointPoint(AbstractCmd *absCmd)
{
    QString sErrMsg;
    int nIndex = INVALID_INDEX;
    InoJPointInfo jointPointInfo;
    bool isOk = true;

    CmdCommonValue *cmd = dynamic_cast<CmdCommonValue *>(absCmd);
    if (!cmd) {
        sErrMsg = tr("Failed to replace joint point.") + SPACE_AND_CONVERT_PARAMETERS_FALID;
        isOk = false;
    }

    if (isOk) {
        nIndex = cmd->m_value.toInt();
        isOk = m_commInstance->replaceJPointCoordValue(nIndex);
        if (!isOk) {
            sErrMsg = tr("Failed to replace joint point.");
        }
    }

    if (isOk) {
        isOk = m_commInstance->saveJPoints();
        if (!isOk) {
            sErrMsg = tr("Failed to replace joint point due to save error.");
        }
    }

    if (isOk) {
        jointPointInfo = m_commInstance->getJPoint(nIndex);
    }

    emit CommunicationEngine::instance()->signal_handleProject_result(
        absCmd->m_object, absCmd->m_cmdType,
        isOk ? QVariant::fromValue(jointPointInfo) : QVariant(), isOk, sErrMsg);
}

void CommunicationThread::renameJointPoint(AbstractCmd *absCmd)
{
    QString sErrMsg;
    int nIndex = INVALID_INDEX;
    int nNewIndex = INVALID_INDEX;
    QVector<QVariant> vecValues;
    InoJPointInfo jointPointInfo;
    bool isOk = true;

    CmdCommonValue *cmd = dynamic_cast<CmdCommonValue *>(absCmd);
    if (!cmd) {
        sErrMsg = tr("Failed to rename joint point.") + SPACE_AND_CONVERT_PARAMETERS_FALID;
        isOk = false;
    }

    if (isOk) {
        vecValues = cmd->m_value.value<QVector<QVariant>>();
        if (vecValues.count() < 2) {
            sErrMsg = tr("Failed to rename joint point as the parameters are invalid.");
            isOk = false;
        }
    }

    if (isOk) {
        nIndex = vecValues.at(0).toInt();
        nNewIndex = vecValues.at(1).toInt();
        bool isExist = Communication::instance()->findJPoint(nNewIndex);
        if (isExist) {
            sErrMsg = tr("JP[%1] already exists.").arg(nNewIndex, 4, 10, QLatin1Char('0'));
            isOk = false;
        }
    }

    if (isOk) {
        isOk = m_commInstance->renameJPoint(nIndex, nNewIndex);
        if (!isOk) {
            sErrMsg = tr("Failed to rename joint point.");
        }
    }

    if (isOk) {
        isOk = m_commInstance->saveJPoints();
        if (!isOk) {
            m_commInstance->renameJPoint(nNewIndex, nIndex);
            sErrMsg = tr("Failed to rename joint point due to save error.");
        }
    }

    if (isOk) {
        jointPointInfo = m_commInstance->getJPoint(nNewIndex);
        emit CommunicationEngine::instance()->
            signal_virtualKeyBoard_LabelChanged(LabelType_GlobalVar_JP,
                                                QString::number(nIndex),
                                                QString::number(nNewIndex));
    }

    emit CommunicationEngine::instance()->signal_handleProject_result(
        absCmd->m_object, absCmd->m_cmdType,
        isOk ? QVariant::fromValue(jointPointInfo) : QVariant(), isOk, sErrMsg);
}

void CommunicationThread::changeJointPoint(AbstractCmd *absCmd)
{
    QString sErrMsg;
    InoJPointInfo jointPointInfo;
    QString sOriginLabel;
    QVector<QVariant> vecValues;
    bool isOk = true;

    CmdCommonValue *cmd = dynamic_cast<CmdCommonValue *>(absCmd);
    if (!cmd) {
        sErrMsg = tr("Failed to modify joint point.") + SPACE_AND_CONVERT_PARAMETERS_FALID;
        isOk = false;
    }

    if (isOk) {
        vecValues = cmd->m_value.value<QVector<QVariant>>();
        if (vecValues.count() < 2) {
            sErrMsg = tr("Failed to modify joint point as the parameters are invalid.");
            isOk = false;
        }
    }

    if (isOk) {
        jointPointInfo = vecValues.at(0).value<InoJPointInfo>();
        sOriginLabel = vecValues.at(1).toString();
        if (!jointPointInfo.label.isEmpty() && sOriginLabel.compare(jointPointInfo.label)) {
            bool isExist = m_commInstance->isLabelExisted(jointPointInfo.label);
            if (isExist) {
                sErrMsg = tr("Edit failed as the label already exists. ");
                isOk = false;
            }
        }
    }

    if (isOk) {
        isOk = m_commInstance->changeJPoint(jointPointInfo);
        if (!isOk) {
            sErrMsg = tr("Failed to change joint point.");
        }
    }

    if (isOk) {
        isOk = m_commInstance->saveJPoints();
        if (!isOk) {
            sErrMsg = tr("Failed to modify joint point due to save error.");
        }
    }

    emit CommunicationEngine::instance()->signal_handleProject_result(
        absCmd->m_object, absCmd->m_cmdType,
        isOk ? QVariant::fromValue(jointPointInfo) : QVariant(), isOk, sErrMsg);

    if (isOk && sOriginLabel.compare(jointPointInfo.label)) {
        emit CommunicationEngine::instance()->
            signal_virtualKeyBoard_LabelChanged(
            LabelType_GlobalVar_JP, sOriginLabel, jointPointInfo.label);
    }
}

void CommunicationThread::changeJointPointPos(AbstractCmd *absCmd)
{
    QString sErrMsg;
    RoadPoint roadPoint;
    int nIndex = INVALID_INDEX;
    QVector<QVariant> vecValues;
    MJPosItem item;
    bool isOk = true;

    CmdCommonValue *cmd = dynamic_cast<CmdCommonValue *>(absCmd);
    if (!cmd) {
        sErrMsg = tr("Failed to modify joint point.") + SPACE_AND_CONVERT_PARAMETERS_FALID;
        isOk = false;
    }

    if (isOk) {
        vecValues = cmd->m_value.value<QVector<QVariant>>();
        if (vecValues.count() < 2) {
            sErrMsg = tr("Failed to modify joint point as the parameters are invalid.");
            isOk = false;
        }
    }

    if (isOk) {
        nIndex = vecValues.at(0).toInt();
        if (nIndex <= INVALID_INDEX) {
            sErrMsg = tr("index is invalid.");
            isOk = false;
        }

        roadPoint = vecValues.at(1).value<RoadPoint>();
    }

    if (isOk) {
        item = m_commInstance->getJointMJPosItem(nIndex);
        if (item.PointNo < 0) {
            sErrMsg = tr("JP[%1] is not exists.").arg(nIndex, 4, 10, QLatin1Char('0'));
            isOk = false;
        }

        item.JData = MetaTypeConversion::tp2InoApi_roadPoint(roadPoint);
    }

    if (isOk) {
        if (m_commInstance->isProgramNotRunning()) {
            isOk = m_commInstance->changeJPoint(item);
            if (isOk) {
                isOk = m_commInstance->saveProject(InoSyncProjcetInfoType_GlobalJPoint);
            }
        } else {
            isOk = m_commInstance->changeJPointInDebug(MAIN_PROGRAM_FILE,
                                                       MAIN_TASK_ID, item);
        }

        if (!isOk) {
            sErrMsg = tr("Failed to change joint point.");
        }
    }

    emit CommunicationEngine::instance()->signal_handleProject_result(
        absCmd->m_object, absCmd->m_cmdType,
        isOk ? QVariant::fromValue(roadPoint) : QVariant(), isOk, sErrMsg);
}

void CommunicationThread::getLabelTypeList(AbstractCmd *absCmd)
{
    QStringList listTypes;

    std::vector<std::string> types = m_commInstance->getLabelTypeList();
    for (const std::string &type : types) {
        // 暂不支持IRLink和EtherCAT AD、DA标签
        if (std::string::npos != type.find("AD")
            || std::string::npos != type.find("DA")) {
            continue;
        }

        listTypes << QString::fromStdString(type);
    }

    emit CommunicationEngine::instance()->signal_handleProject_result(
        absCmd->m_object, absCmd->m_cmdType, QVariant(listTypes), true, QString());
}

void CommunicationThread::genInitIoItems(AbstractCmd *absCmd)
{
    QString sErrMsg;
    QVector<QVariant> vecValues;
    InoLabelType labelType;
    InoLabelIOType ioType;
    ShowType dataType;
    QVector<InoLabelItem> items;
    bool isOk = true;

    CmdCommonValue *cmd = dynamic_cast<CmdCommonValue *>(absCmd);
    if (!cmd) {
        sErrMsg = tr("Failed to init label.") + SPACE_AND_CONVERT_PARAMETERS_FALID;
        isOk = false;
    }

    if (isOk) {
        vecValues = cmd->m_value.value<QVector<QVariant>>();
        if (vecValues.count() < 3) {
            sErrMsg = tr("Failed to load the label as the parameters are invalid.");
            isOk = false;
        }
    }

    if (isOk) {
        labelType = vecValues.at(0).value<InoLabelType>();
        ioType = vecValues.at(1).value<InoLabelIOType>();
#ifdef INOCOBOTTP_MSVC_QT5
        qRegisterMetaType<ShowType>("ShowType");
        qRegisterMetaType<ShowType>("ShowType&");
#endif
        dataType = vecValues.at(2).value<ShowType>();
        items = m_commInstance->genInitIoItems(labelType, ioType, dataType);
    }

    emit CommunicationEngine::instance()->signal_handleProject_result(
        absCmd->m_object, absCmd->m_cmdType,
        isOk ? QVariant::fromValue(items) : QVariant(), isOk, sErrMsg);
}

void CommunicationThread::getIoItems(AbstractCmd *absCmd)
{
    QString sErrMsg;
    QVector<QVariant> vecValues;
    InoLabelType labelType;
    InoLabelIOType ioType;
    ShowType dataType;
    QVector<InoLabelItem> items;
    bool isOk = true;

    CmdCommonValue *cmd = dynamic_cast<CmdCommonValue *>(absCmd);
    if (!cmd) {
        sErrMsg = tr("Failed to get label.") + SPACE_AND_CONVERT_PARAMETERS_FALID;
        isOk = false;
    }

    if (isOk) {
        vecValues = cmd->m_value.value<QVector<QVariant>>();
        if (vecValues.count() < 3) {
            sErrMsg = tr("Failed to modify the label as the parameters are invalid.");
            isOk = false;
        }
    }

    if (isOk) {
        labelType = vecValues.at(0).value<InoLabelType>();
        ioType = vecValues.at(1).value<InoLabelIOType>();
        dataType = vecValues.at(2).value<ShowType>();
        items = m_commInstance->getIoItems(labelType, ioType, dataType);
    }

    emit CommunicationEngine::instance()->signal_handleProject_result(
        absCmd->m_object, absCmd->m_cmdType,
        isOk ? QVariant::fromValue(items) : QVariant(), isOk, sErrMsg);
}

void CommunicationThread::genInitAdDaItems(AbstractCmd *absCmd)
{
    QString sErrMsg;
    QVector<QVariant> vecValues;
    InoLabelType labelType;
    InoAdDaType addaType;
    QVector<InoLabelItem> items;
    bool isOk = true;

    CmdCommonValue *cmd = dynamic_cast<CmdCommonValue *>(absCmd);
    if (!cmd) {
        sErrMsg = tr("Failed to init label.") + SPACE_AND_CONVERT_PARAMETERS_FALID;
        isOk = false;
    }

    if (isOk) {
        vecValues = cmd->m_value.value<QVector<QVariant>>();
        if (vecValues.count() < 2) {
            sErrMsg = tr("Failed to load the label as the parameters are invalid.");
            isOk = false;
        }
    }

    if (isOk) {
        labelType = vecValues.at(0).value<InoLabelType>();
        addaType = vecValues.at(1).value<InoAdDaType>();
        items = m_commInstance->genInitAaDaItems(labelType, addaType);
    }

    emit CommunicationEngine::instance()->signal_handleProject_result(
        absCmd->m_object, absCmd->m_cmdType,
        isOk ? QVariant::fromValue(items) : QVariant(), isOk, sErrMsg);
}

void CommunicationThread::getAdDaItems(AbstractCmd *absCmd)
{
    QString sErrMsg;
    QVector<QVariant> vecValues;
    InoLabelType labelType;
    InoAdDaType addaType;
    QVector<InoLabelItem> items;
    bool isOk = true;

    CmdCommonValue *cmd = dynamic_cast<CmdCommonValue *>(absCmd);
    if (!cmd) {
        sErrMsg = tr("Failed to get label.") + SPACE_AND_CONVERT_PARAMETERS_FALID;
        isOk = false;
    }

    if (isOk) {
        vecValues = cmd->m_value.value<QVector<QVariant>>();
        if (vecValues.count() < 2) {
            sErrMsg = tr("Failed to modify the label as the parameters are invalid.");
            isOk = false;
        }
    }

    if (isOk) {
        labelType = vecValues.at(0).value<InoLabelType>();
        addaType = vecValues.at(1).value<InoAdDaType>();
        items = m_commInstance->getAdDaItems(labelType, addaType);
    }

    emit CommunicationEngine::instance()->signal_handleProject_result(
        absCmd->m_object, absCmd->m_cmdType,
        isOk ? QVariant::fromValue(items) : QVariant(), isOk, sErrMsg);
}

void CommunicationThread::genInitOtherItems(AbstractCmd *absCmd)
{
    QString sErrMsg;
    QVector<InoLabelItem> items;
    bool isOk = true;

    CmdCommonValue *cmd = dynamic_cast<CmdCommonValue *>(absCmd);
    if (!cmd) {
        sErrMsg = tr("Failed to init label.") + SPACE_AND_CONVERT_PARAMETERS_FALID;
        isOk = false;
    }

    if (isOk) {
        items = m_commInstance->genInitOtherItems(
            cmd->m_value.value<InoLabelType>());
    }

    emit CommunicationEngine::instance()->signal_handleProject_result(
        absCmd->m_object, absCmd->m_cmdType,
        isOk ? QVariant::fromValue(items) : QVariant(), isOk, sErrMsg);
}

void CommunicationThread::getOtherItems(AbstractCmd *absCmd)
{
    QString sErrMsg;
    QVector<InoLabelItem> items;
    bool isOk = true;

    CmdCommonValue *cmd = dynamic_cast<CmdCommonValue *>(absCmd);
    if (!cmd) {
        sErrMsg = tr("Failed to modify label.") + SPACE_AND_CONVERT_PARAMETERS_FALID;
        isOk = false;
    }

    if (isOk) {
        items = m_commInstance->getOtherItems(
            cmd->m_value.value<InoLabelType>());
    }

    emit CommunicationEngine::instance()->signal_handleProject_result(
        absCmd->m_object, absCmd->m_cmdType,
        isOk ? QVariant::fromValue(items) : QVariant(), isOk, sErrMsg);
}

void CommunicationThread::modifyIoItem(AbstractCmd *absCmd)
{
    QString sErrMsg;
    QVector<QVariant> vecValues;
    InoLabelType labelType;
    InoLabelIOType ioType;
    ShowType dataType;
    InoLabelItem labelItem;
    QString sOldLabel;
    QString sOldDescri;
    InoLabelAndDescriItem oldLabelAndDescriItem;
    bool isOk = true;

    CmdCommonValue *cmd = dynamic_cast<CmdCommonValue *>(absCmd);
    if (!cmd) {
        sErrMsg = tr("Failed to modify label.") + SPACE_AND_CONVERT_PARAMETERS_FALID;
        isOk = false;
    }

    if (isOk) {
        vecValues = cmd->m_value.value<QVector<QVariant>>();
        if (vecValues.count() < 5) {
            sErrMsg = tr("Failed to modify the label as parameters are invalid.");
            isOk = false;
        }
    }

    if (isOk) {
        labelType = vecValues.at(0).value<InoLabelType>();
        ioType = vecValues.at(1).value<InoLabelIOType>();
        dataType = vecValues.at(2).value<ShowType>();
        labelItem = vecValues.at(3).value<InoLabelItem>();
        sOldLabel = vecValues.at(4).toString();
        sOldDescri = vecValues.at(5).toString();
        oldLabelAndDescriItem = InoLabelAndDescriItem(labelItem.nIndex,sOldLabel,sOldDescri);

        if (!labelItem.sLabel.isEmpty() && labelItem.sLabel.compare(sOldLabel)) {
            bool isExist = m_commInstance->isLabelExisted(labelItem.sLabel);
            if (isExist) {
                sErrMsg = tr("The label already exists.");
                isOk = false;
            }
        }
    }

    if (isOk) {
        isOk = m_commInstance->modifyIoItem(labelType, ioType,
                                            dataType, labelItem);
        if (!isOk) {
            sErrMsg = tr("Failed to modify the label.");
        }
    }

    if (isOk) {
        isOk = m_commInstance->saveAllLabels();
        if (!isOk) {
            sErrMsg = tr("Failed to save label.");
            // 撤销保存失败的修改
            InoLabelItem item = labelItem;
            item.sLabel = sOldLabel;
            m_commInstance->modifyIoItem(labelType, ioType, dataType, item);
        }
    }

    emit CommunicationEngine::instance()->signal_handleProject_result(
        absCmd->m_object, absCmd->m_cmdType,
        isOk ? QVariant::fromValue(QVector<InoLabelItem>() << labelItem) : QVariant(), isOk, sErrMsg);

    if (isOk && labelItem.sLabel.compare(sOldLabel)) {
        AllLabelType enumOffset = LabelType_None;
        switch (labelType) {
        case IO_INPUT_BIT:
        case IO_INPUT_BYTE:
        case IO_INPUT_WORD:
            enumOffset = LabelType_Input_Start;
            break;
        case IO_OUTPUT_BIT:
        case IO_OUTPUT_BYTE:
        case IO_OUTPUT_WORD:
            enumOffset = LabelType_Output_Start;
            break;
        default:
            break;
        }

        if (enumOffset != LabelType_None){
            InoIOType type;
            if(ioType == InoLabelIOType_StandardIO )
                type = InoIOType_StandardIO;
            else if (ioType == InoLabelIOType_ToolIO)
                type = InoIOType_ToolIO;
            else if(ioType == InoLabelIOType_SlaveFiledbusIO)
                type = InoIOType_FieldbusIO;
            else if(ioType == InoLabelIOType_MemoryIO)
                type = InoIOType_MemoryIO;
            else
                return;
            emit CommunicationEngine::instance()
                ->signal_virtualKeyBoard_LabelChanged(
                    (AllLabelType)(enumOffset + type * ShowType_Size + dataType),
                    sOldLabel, labelItem.sLabel);  // oldLabel
            emit CommunicationEngine::instance()
                ->signal_virtualKeyBoard_LabelChanged(
                    (AllLabelType)(enumOffset + InoIOType_CommonIO * ShowType_Size + dataType),
                    sOldLabel, labelItem.sLabel);  // oldLabel
        }

    }

    if (isOk&& (labelItem.sLabel.compare(sOldLabel)||labelItem.sDescription.compare(sOldDescri))) {
        AllLabelType enumOffset = LabelType_None;
        switch (labelType) {
        case IO_INPUT_BIT:
        case IO_INPUT_BYTE:
        case IO_INPUT_WORD:
            enumOffset = LabelType_Input_Start;
            break;
        case IO_OUTPUT_BIT:
        case IO_OUTPUT_BYTE:
        case IO_OUTPUT_WORD:
            enumOffset = LabelType_Output_Start;
            break;
        default:
            break;
        }
        if (enumOffset != LabelType_None){
            InoIOType type;
            if(ioType == InoLabelIOType_StandardIO )
                type = InoIOType_StandardIO;
            else if (ioType == InoLabelIOType_ToolIO)
                type = InoIOType_ToolIO;
            else if(ioType == InoLabelIOType_SlaveFiledbusIO)
                type = InoIOType_FieldbusIO;
            else if(ioType == InoLabelIOType_MemoryIO)
                type = InoIOType_MemoryIO;
            else
                return;
            InoLabelAndDescriItem newLabelAndDescriItem(labelItem.nIndex,labelItem.sLabel,labelItem.sDescription);
            emit CommunicationEngine::instance()
                ->signal_virtualKeyBoard_LabelOrDescriChanged(
                    (AllLabelType)(enumOffset + type * ShowType_Size + dataType),
                    oldLabelAndDescriItem,newLabelAndDescriItem);
            emit CommunicationEngine::instance()
                ->signal_virtualKeyBoard_LabelOrDescriChanged(
                    (AllLabelType)(enumOffset + InoIOType_CommonIO * ShowType_Size + dataType),
                    oldLabelAndDescriItem,newLabelAndDescriItem);
        }
    }
}

void CommunicationThread::modifyAdDaItem(AbstractCmd *absCmd)
{
    QString sErrMsg;
    QVector<QVariant> vecValues;
    InoLabelType labelType;
    InoAdDaType addaType;
    InoLabelItem labelItem;
    QString sOldLabel;
    QString sOldDescri;
    InoLabelAndDescriItem oldLabelAndDescriItem;
    bool isOk = true;

    CmdCommonValue *cmd = dynamic_cast<CmdCommonValue *>(absCmd);
    if (!cmd) {
        sErrMsg = tr("Failed to modify label.") + SPACE_AND_CONVERT_PARAMETERS_FALID;
        isOk = false;
    }

    if (isOk) {
        vecValues = cmd->m_value.value<QVector<QVariant>>();
        if (vecValues.count() < 5) {
            sErrMsg = tr("Failed to modify the label as parameters are invalid.");
            isOk = false;
        }
    }

    if (isOk) {
        labelType = vecValues.at(0).value<InoLabelType>();
        addaType = vecValues.at(1).value<InoAdDaType>();
        labelItem = vecValues.at(2).value<InoLabelItem>();
        sOldLabel = vecValues.at(3).toString();
        sOldDescri = vecValues.at(4).toString();
        oldLabelAndDescriItem = InoLabelAndDescriItem(labelItem.nIndex,
                                                      sOldLabel, sOldDescri);

        if (!labelItem.sLabel.isEmpty() && labelItem.sLabel.compare(sOldLabel)) {
            bool isExist = m_commInstance->isLabelExisted(labelItem.sLabel);
            if (isExist) {
                sErrMsg = tr("The label already exists.");
                isOk = false;
            }
        }
    }

    if (isOk) {
        isOk = m_commInstance->modifyAdDaItem(labelType, addaType, labelItem);
        if (!isOk) {
            sErrMsg = tr("Failed to modify the label.");
        }
    }

    if (isOk) {
        isOk = m_commInstance->saveAllLabels();
        if (!isOk) {
            sErrMsg = tr("Failed to save label.");
            // 撤销保存失败的修改
            InoLabelItem item = labelItem;
            item.sLabel = sOldLabel;
            m_commInstance->modifyAdDaItem(labelType, addaType, item);
        }
    }

    emit CommunicationEngine::instance()->signal_handleProject_result(
        absCmd->m_object, absCmd->m_cmdType,
        isOk ? QVariant::fromValue(QVector<InoLabelItem>() << labelItem) : QVariant(), isOk, sErrMsg);

    if (isOk && labelItem.sLabel.compare(sOldLabel)) {
        emit CommunicationEngine::instance()
            ->signal_virtualKeyBoard_LabelChanged(
                (AllLabelType)(LabelType_DA_Start + labelType),
                sOldLabel, labelItem.sLabel);  // oldLabel1
    }
}

void CommunicationThread::modifyOtherItem(AbstractCmd *absCmd)
{
    QString sErrMsg;
    QVector<QVariant> vecValues;
    InoLabelType labelType;
    InoLabelItem labelItem;
    QString sOldLabel;
    bool isOk = true;

    CmdCommonValue *cmd = dynamic_cast<CmdCommonValue *>(absCmd);
    if (!cmd) {
        sErrMsg = tr("Failed to modify label.") + SPACE_AND_CONVERT_PARAMETERS_FALID;
        isOk = false;
    }

    if (isOk) {
        vecValues = cmd->m_value.value<QVector<QVariant>>();
        if (vecValues.count() < 3) {
            sErrMsg = tr("Failed to modify the label as parameters are invalid.");
            isOk = false;
        }
    }

    if (isOk) {
        labelType = vecValues.at(0).value<InoLabelType>();
        labelItem = vecValues.at(1).value<InoLabelItem>();
        sOldLabel = vecValues.at(2).toString();

        if (!labelItem.sLabel.isEmpty() && labelItem.sLabel.compare(sOldLabel)) {
            bool isExist = m_commInstance->isLabelExisted(labelItem.sLabel);
            if (isExist) {
                sErrMsg = tr("The label already exists.");
                isOk = false;
            }
        }
    }

    if (isOk) {
        isOk = m_commInstance->modifyOtherItem(labelType, labelItem);
        if (!isOk) {
            sErrMsg = tr("Failed to modify label.");
        }
    }

    if (isOk) {
        isOk = m_commInstance->saveAllLabels();
        if (!isOk) {
            sErrMsg = tr("Failed to save label.");
            // 撤销保存失败的修改
            InoLabelItem item = labelItem;
            item.sLabel = sOldLabel;
            m_commInstance->modifyOtherItem(labelType, item);
        }
    }

    emit CommunicationEngine::instance()->signal_handleProject_result(
        absCmd->m_object, absCmd->m_cmdType,
        isOk ? QVariant::fromValue(QVector<InoLabelItem>() << labelItem) : QVariant(), isOk, sErrMsg);

    if (isOk && labelItem.sLabel.compare(sOldLabel)) {
        emit CommunicationEngine::instance()
            ->signal_virtualKeyBoard_LabelChanged(
                (AllLabelType)(LabelType_DA_Start + labelType),
                sOldLabel, labelItem.sLabel);  // oldLabel1
    }
}

void CommunicationThread::updateToolIOItemDesc(AbstractCmd *absCmd)
{
    QString content;
    QString sErrMsg;
    bool isOk = true;

    CmdCommonValue *cmd = dynamic_cast<CmdCommonValue *>(absCmd);
    if (!cmd) {
        sErrMsg = tr("Failed to update label.") + SPACE_AND_CONVERT_PARAMETERS_FALID;
        isOk = false;
    }

    if (isOk) {
        content = cmd->m_value.toString();
        if (content.isEmpty()) {
            sErrMsg = tr("Failed to update label as the tool I/O description is empty.");
            isOk = false;
        }

        if (Communication::instance()->isToolIoItemDescLangCorrect()) {
            isOk = false;
        }
    }

    if (isOk) {
        QStringList toolDescInfos = content.split("|");
        if (toolDescInfos.isEmpty()) {
            sErrMsg = tr("Failed to get tool I/O description.");
            isOk = false;
        }

        for (const QString &toolDescs : toolDescInfos) {
            QStringList toolDesc = toolDescs.split(":");
            if (toolDesc.count() != 2) {
                sErrMsg = QString("Tool IO description:%1 is invalid.").arg(toolDescs);
                continue;
            }

            QString toolIOName = toolDesc.at(0);
            int index = toolIOName.mid(toolIOName.indexOf("[") + 1, toolIOName.indexOf("]")
                                                                        - toolIOName.indexOf("[") - 1).toInt();
            InoLabelType labelType = m_commInstance->getLabelType(toolIOName.left(toolIOName.indexOf("[")));

            m_commInstance->updateIoItemDescription(labelType, index, toolDesc.at(1));
        }
    }

    if (isOk) {
        isOk = m_commInstance->saveAllLabels();
        if (!isOk) {
            sErrMsg = tr("Failed to save label.");
        }
    }

    if (!isOk) {
        LOG_INFO(sErrMsg);
        sErrMsg.clear();
    }

    emit CommunicationEngine::instance()->signal_handleProject_result(
        absCmd->m_object, absCmd->m_cmdType, QVariant(), isOk, QString());
}

void CommunicationThread::getUserDefineWaringFileList(AbstractCmd *absCmd)
{
    QStringList listFiles;

    std::vector<std::string> files = m_commInstance->getDefineWarningFileList();
    for (const std::string &file : files) {
        listFiles << QString::fromStdString(file);
    }

    emit CommunicationEngine::instance()->signal_handleProject_result(
        absCmd->m_object, absCmd->m_cmdType, QVariant(listFiles), true, QString());
}

void CommunicationThread::getUserDefineWarnings(AbstractCmd *absCmd)
{
    QString sErrMsg;
    QStringList listWarnings;

    bool isOk = m_commInstance->readWarnings();
    if (!isOk) {
        sErrMsg = tr("Failed to get user alarms data.");
    }

    if (isOk) {
        std::vector<std::string> vecWarnings = m_commInstance->getWarnings();
        for (const std::string &warning : vecWarnings) {
            listWarnings << QString::fromStdString(warning);
        }
    }

    emit CommunicationEngine::instance()->signal_handleProject_result(
        absCmd->m_object, absCmd->m_cmdType,
        isOk ? QVariant::fromValue(listWarnings) : QVariant(), isOk, sErrMsg);
}

void CommunicationThread::modifyUserDefineWarnig(AbstractCmd *absCmd)
{
    QString sErrMsg;
    int nIndex = INVALID_INDEX;
    QVector<QVariant> vecValues;
    QString sOriginWarnigContent;
    QString sWarnigContent;
    bool isOk = true;

    CmdCommonValue *cmd = dynamic_cast<CmdCommonValue *>(absCmd);
    if (!cmd) {
        sErrMsg = tr("Failed to modify user alarms.") + SPACE_AND_CONVERT_PARAMETERS_FALID;
        isOk = false;
    }

    if (isOk) {
        vecValues = cmd->m_value.value<QVector<QVariant>>();
        if (vecValues.count() < 3) {
            sErrMsg = tr("Failed to modify user alarms as the parameters are invalid.");
            isOk = false;
        }
    }

    if (isOk) {
        nIndex = vecValues.at(0).toInt();
        sOriginWarnigContent = vecValues.at(1).toString();
        sWarnigContent = vecValues.at(2).toString();

        isOk = m_commInstance->isWarningValid(sWarnigContent);
        if (!isOk) {
            sErrMsg = tr("The user alarm content is invalid.");
        }
    }

    if (isOk) {
        isOk = m_commInstance->modifyWarning(nIndex, sWarnigContent);
        if (!isOk) {
            sErrMsg = tr("Failed to modify user alarms.");
        }
    }

    if (isOk) {
        isOk = m_commInstance->saveWarnings();
        if (!isOk) {
            sErrMsg = tr("Failed to save user alarms.");
            // 撤销保存失败的修改
            m_commInstance->modifyWarning(nIndex, sOriginWarnigContent);
        }
    }

    emit CommunicationEngine::instance()->signal_handleProject_result(
        absCmd->m_object, absCmd->m_cmdType, QVariant(), isOk, sErrMsg);
}

void CommunicationThread::getTaskList(AbstractCmd *absCmd)
{
    QString sErrMsg;
    QVector<InoTaskInfo> vecTasks;

    vecTasks = m_commInstance->getTaskList();
    if (!vecTasks.isEmpty()) {
        // 插入主任务
        vecTasks.prepend({MAIN_TASK_ID, MAIN_TASK_NAME, TaskCondType_Main,
                          MAIN_PROGRAM_FILE, true, TaskStatus_Finished});
    }

    for (int i = 0; i < vecTasks.count(); i++) {
        const InoTaskInfo taskInfo = vecTasks.at(i);
        vecTasks[i].status = m_commInstance->getTaskStatus(taskInfo.nTaskId);
        if (i == 0 && vecTasks[i].status == TaskStatus_InActived) {  // 主任务
            vecTasks[i].isActive = false;
        }
    }

    emit CommunicationEngine::instance()->signal_handleProject_result(
        absCmd->m_object, absCmd->m_cmdType, QVariant::fromValue(vecTasks),
        true, sErrMsg);
}

void CommunicationThread::activeTask(AbstractCmd *absCmd)
{
    QString sErrMsg;
    int nTaskId = INVALID_INDEX;
    bool isActive = false;
    InoTaskStatus status;
    QVector<QVariant> vecValues;
    bool isOk = true;

    CmdCommonValue *cmd = dynamic_cast<CmdCommonValue *>(absCmd);
    if (!cmd) {
        sErrMsg = tr("Failed to activate task.") + SPACE_AND_CONVERT_PARAMETERS_FALID;
        isOk = false;
    }

    if (isOk) {
        vecValues = cmd->m_value.value<QVector<QVariant>>();
        if (vecValues.count() < 2) {
            sErrMsg = tr("Failed to activate task as the parameters are invalid.");
            isOk = false;
        }
    }

    if (isOk) {
        nTaskId = vecValues.at(0).toInt();
        isActive = vecValues.at(1).toBool();
        isOk = m_commInstance->activeTask(nTaskId, isActive);
        if (!isOk) {
            sErrMsg = tr("Failed to activate task.");
        }
    }

    if (isOk) {
        status = m_commInstance->getTaskStatus(nTaskId);
    }

#ifdef INOCOBOTTP_MSVC_QT5
    qRegisterMetaType<InoTaskStatus>("TaskStatus");
    emit CommunicationEngine::instance()->signal_handleProject_result(
        absCmd->m_object,
        absCmd->m_cmdType,
        QVariantList() << nTaskId << isActive << QVariant::fromValue(status),
        isOk,
        sErrMsg
        );
#else

    emit CommunicationEngine::instance()->signal_handleProject_result(
        absCmd->m_object, absCmd->m_cmdType,
        QVector<QVariant>() << nTaskId << isActive << QVariant::fromValue(status),
        isOk, sErrMsg);
#endif
}

void CommunicationThread::manageTaskInfos(AbstractCmd *absCmd)
{
    QString sErrMsg;
    QString sProjectName;
#ifdef INOCOBOTTP_MSVC_QT5
    QVector<InoTaskInfo> taskInfoList;
#else
    QList<InoTaskInfo> taskInfoList;
#endif

    QVector<QVariant> vecValues;
    bool isOk = true;

    CmdCommonValue *cmd = dynamic_cast<CmdCommonValue *>(absCmd);
    if (!cmd) {
        sErrMsg = tr("Failed to manage task.") + SPACE_AND_CONVERT_PARAMETERS_FALID;
        isOk = false;
    }

    if (isOk) {
        vecValues = cmd->m_value.value<QVector<QVariant>>();
        if (vecValues.count() < 2) {
            sErrMsg = tr("Failed to manage tasks as the parameters are invalid.");
            isOk = false;
        }
    }

    if (isOk) {
        sProjectName = vecValues.at(0).toString();
        taskInfoList = vecValues.at(1).value<QVector<InoTaskInfo>>();
#ifdef INOCOBOTTP_MSVC_QT5
        QVector<InoTaskInfo> curTaskInfoList = m_commInstance->getTaskList();
#else
        QList<InoTaskInfo> curTaskInfoList = m_commInstance->getTaskList();
#endif
        for (const InoTaskInfo &taskInfo : taskInfoList) {
            if (curTaskInfoList.contains(taskInfo)) {
                continue;
            }

            isOk = m_commInstance->addTask(taskInfo.nTaskId,
                                           taskInfo.nTaskType,
                                           taskInfo.sTaskFileName);
            if (!isOk) {
                sErrMsg = tr("Failed to manage task.");
                break;
            }
        }

        curTaskInfoList.clear();
        curTaskInfoList = m_commInstance->getTaskList();
        for (const InoTaskInfo &taskInfo : curTaskInfoList) {
            if (taskInfoList.contains(taskInfo)) {
                continue;
            }

            if (m_commInstance->isTaskExist(taskInfo.nTaskId)) {
                isOk = m_commInstance->deleteTask(taskInfo.nTaskId);
                if (!isOk) {
                    sErrMsg = tr("Failed to manage task.");
                    break;
                }
            }
        }
    }

    emit CommunicationEngine::instance()->signal_handleProject_result(
        absCmd->m_object, absCmd->m_cmdType, sProjectName, isOk, sErrMsg);
}

void CommunicationThread::updateRoadPointInfo()
{
    ProjectRoadPointInfo::instance()->clearPointInfos();

    // JP
    QVector<InoJPointInfo> vecJPointInfos = m_commInstance->readAllJPoints();
    for (const InoJPointInfo &item : vecJPointInfos) {
        RoadPoint pt;
        pt.setJointAngle(const_cast<double *>(item.pos.JointData));
        ProjectRoadPointInfo::instance()->updateRoadPointInfo(PREFIX_JP, item.pointNo,
                                                     item.label, pt);
    }

    // P
    QVector<InoRPointInfo> vecRPointInfos = m_commInstance->readAllRPoints();
    for (const InoRPointInfo &item : vecRPointInfos) {
        RoadPoint pt;
        pt.m_position.m_x = item.pos.RPosData[0];
        pt.m_position.m_y = item.pos.RPosData[1];
        pt.m_position.m_z = item.pos.RPosData[2];
        pt.m_orientation.m_rz = item.pos.RPosData[3];
        pt.m_orientation.m_ry = item.pos.RPosData[4];
        pt.m_orientation.m_rx = item.pos.RPosData[5];

        pt.setArmAgrs(const_cast<int *>(item.pos.ArmParm), ROBOT_ARM_NUM);
        ProjectRoadPointInfo::instance()->updateRoadPointInfo(PREFIX_P, item.pointNo,
                                                     item.label, pt);
    }
}
