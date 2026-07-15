#pragma once

#include <QVector>
#include "communication_global.h"
#include "projectdata.h"
#include "roadpoint.h"

#define CONTROLLER_PROJECT_MAIN_XML_FILE(projectName) \
    QDir::cleanPath(CONTROLLER_PROJECT_PATH(projectName) + "/main" + XML_FILE_NAME_SUFFIX)

namespace InoRobBusiness
{
class IWorkstation;
class IController;
class IProject;
class IResource;
}  // namespace InoRobBusiness

class Communication;

struct _ProjectFolderInfo;

class COMMUNICATION_EXPORT ProjectInterface
{
public:
    ProjectInterface()
    {
    }

    virtual Communication *comm() = 0;
    virtual InoRobBusiness::IController *controller() = 0;

    int getProjectCount();
    bool setActiveProject(const QString &projectName = QString());
    bool setProjectOperateMode(const InoFileType &mode);
    void setProjectType(const InoProjectType &type);

    QString getCurrentProjectName();
    QString getActiveProjectName();

    // project list
    std::vector<struct _ProjectFolderInfo> readProjectList();
    QVector<InoProjectInfo> getProjectList(
        const ProjectSortType sortType = ProjectSortType_DascendingByTime);

    // create project
    bool createLocalProject(const QString &folder, const QString &name,
                            InoProjectType type = InoProjectType_Lua);
    bool createProject(const QString &name,
                       InoProjectType type = InoProjectType_Lua);
    // default project name
    QString getDefaultProjectName(QString baseName = QString());

    bool isProjectExisted(const QString &name);
    QString isProjectNameValid(const QString &name);

    bool deleteProject(const QString &name);
    bool renameProject(QString oldName, QString newName);

    bool copyProject(const QString &name);
    QString getCopiedProjectName();
    bool pasteProject(const QString &name);

    // import/export project
    bool importProject(QString path);
    bool exportProject(const QString &name, QString folder);
    // get project name from index
    QString projectName(ProjectSortType type, int index);
    // sort
    QVector<InoProjectInfo> sortProjectList(
        const ProjectSortType sortType,
        std::vector<_ProjectFolderInfo> &infos);
    // label exist
    bool isLabelExisted(const QString &sLabel);

    // program
    int readProject(const QString &name);
    int readLocalProject(const QString &name);
    std::vector<std::string> getProgramFileList();
    std::vector<std::string> getRPointFileList();
    std::vector<std::string> getJPointFileList();
    std::vector<std::string> getLabelTypeList();
    std::vector<std::string> getDefineWarningFileList();

    // default program name
    QString getDefaultProgramName(QString baseName = "");

    bool isProgramFileUpperLimit();
    bool isProgramExisted(const QString &name);
    QString isProgramNameValid(const QString &name);

    // create program
    bool createProgram(const QString &name, bool isFunc = false);
    bool deleteProgram(const QString &name);
    bool renameProgram(QString oldName, QString newName);
    QString getProgramNameWithoutExtension(const QString &name);

    void copyProgram(QString name);
    QString getCopiedProgramName();
    bool pasteProgram(const QString &name);

    // import/export program
    bool importLocalProgram(QString path);
    bool exportProgram(QString name, QString folder);

    void addProgramConfig(const QString &sFileName);
    void deleteProgramConfig(const QString &sFileName);

    bool saveProject(const InoSyncProjcetInfoType &type,
                     const QString &sProjectName = QString());

    bool getRoadPointByLabel(const QString &sLabel, bool &isJoint, RoadPoint &pt);
    bool getRoadPointByIndex(const QString &type, int index, RoadPoint &pt);

    bool deleteFileFromController(const std::string &filePath);
    bool deleteFilesFromController(const std::vector<std::string> &filePathList);

    int isFileNameRepeat(const QString &fileName);

private:
    // convert project folder name to array
    QVariantList convertProjcetFolderInfos(
        const std::vector<struct _ProjectFolderInfo> &infos);

    // get project from folder list
    struct _ProjectFolderInfo extractActiveProject(
        std::vector<struct _ProjectFolderInfo> &infos);

    int readActiveProject(const QString &name, bool isReadSameProject = false);
};
