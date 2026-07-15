#pragma once
#include <QString>
#include <QVariant>

// error code
const int Err_Unknown = -1;
const int Err_Success = 0;
const int Err_Disconnect = 1;
const int Err_ReadProject = 2;
const int Err_Incomplete = 3;
const int Err_ActiveProject = 4;

const QString FACTORY_MODE_PASSWD = "297995";

enum InoFileType {
    InoFileType_Local = 0,  // 先操作本地再同步电柜，如PC编程平台
    InoFileType_Controller  // 操作电柜和本地，如示教器1.0/2.0
};

enum InoProjectType {
    InoProjectType_Pro = 0,  // pro工程(程序文件为.pro)
    InoProjectType_Lua       // lua工程(程序文件为.lua)
};

enum ProjectSortType {
    ProjectSortType_DascendingByTime = 0,  // 时间降序排列
    ProjectSortType_AscendingByWord        // 首字母升序排列
};
Q_DECLARE_METATYPE(ProjectSortType)

enum InoUserMode {
    InoUserMode_Unknown = -1,
    InoUserMode_Customer = 1,
    InoUserMode_Edit,
    InoUserMode_Manage,
    InoUserMode_Factory
};

enum PointFileChangeType {
    ActiveNewProject,
    AddPointFile,
    DeletePointFile
};

// 译码类型
enum InoSyncProjcetInfoType
{
    InoSyncProjcetInfoType_ProjectInfo = 0,     // 工程配置文件信息(包括静态任务)
    InoSyncProjcetInfoType_ProgramFiles,        // 程序文件
    InoSyncProjcetInfoType_GlobalRPoint,        // 全局P点位
    InoSyncProjcetInfoType_GlobalJPoint,        // 全局JP点位
    InoSyncProjcetInfoType_LabelInfo,           // 标签信息
    InoSyncProjcetInfoType_UserDefineWarning,   // 用户自定义报警
    SYNC_PROGRAM_COMPILE = 15                   //程序是否译码，0-不编译，1-非静态任务编译（示教器编程切调试/自动，全部保存），2-全部编译
};

// 工程列表数据
typedef struct InoProjectInfo {
    QString index = "0";  // 下标
    QString name = "";    // 工程名
    QString modifyTime;   // 修改时间
    int memorySize;       // 大小

    // 根据下标获取对应数据
    QVariant getData(int index) const
    {
        switch (index) {
        case 0:
            return this->index;
        case 1:
            return this->name;
        case 2:
            return this->modifyTime;
        case 3:
            return this->memorySize;
        default:
            break;
        }
        return QString();
    }

    // 根据下标设置对应数据
    void setData(int index, QString value)
    {
        switch (index) {
        case 0:
            this->index = value;
            break;
        case 1:
            this->name = value;
            break;
        case 2:
            this->modifyTime = value;
            break;
        case 3:
            this->memorySize = value.toInt();
            break;
        default:
            break;
        }
    }

    InoProjectInfo &operator=(const InoProjectInfo &other)
    {
        if (this != &other) {
            this->index = other.index;
            this->name = other.name;
            this->modifyTime = other.modifyTime;
            this->memorySize = other.memorySize;
        }

        return *this;
    }
} InoProjectInfo;
#ifdef INOCOBOTTP_MSVC_QT5
Q_DECLARE_METATYPE(InoProjectInfo)
#endif

typedef struct InoProjectFileInfo {
    enum ProjectFileType {
        ProjectFile_ProgramFile = 0,
        ProjectFile_RobotPointFile,
        ProjectFile_JointPointFile,
        ProjectFile_LabelFile,
        ProjectFile_UserDefineWarningFile,
        ProjectFile_ScriptFile,
        ProjectFile_PalletFile,
        ProjectFile_TempVarFile
    };

    ProjectFileType fileType;
    QString sIcon;
    std::vector<std::string> vecFiles;
} InoProjectFileInfo;
Q_DECLARE_METATYPE(InoProjectFileInfo)
