#pragma once

#include <QThread>
#include <QQueue>
#include "communicationengine.h"

class Communication;
class QMutex;
class IOInterface;
class QWaitCondition;
class AbstractCmd;
class QTimer;
class IOInterface;
class QXmlStreamWriter;
class QBuffer;
namespace Utils
{
class TreeItem;
}

class CommunicationThread : public QThread
{
    Q_OBJECT

public:
    enum ThreadType{
      Thread_Communication,
      Thread_LocalTask,
    };
    explicit CommunicationThread(ThreadType threadType);
    ~CommunicationThread();
    Communication *m_commInstance;

    AbstractCmd * enqueueCmdInfo(AbstractCmd *absCmd);

    void stopThread();

    ThreadType getThreadType();
protected:
    void run();

private:
    void processTasks(AbstractCmd *absCmd);
    bool needDealTrajectoryRecovery();
    void parseGeneralMatchParam(const std::string &sJsonText);

    // template <typename T, typename funClass>
    // void getListDatas(const QVariant customData,
    //                   const QList<T> &oldData,
    //                   bool (funClass::*fun)(QList<T> &),
    //                   void (CommunicationEngine::*signal)(const QVariant, const QList<int>, const QList<T>),
                      // bool ignoreSizeDifferent = false);

    // template <typename T, typename funClass>
    // void getListDatas(const QVariant customData,
    //                   const QList<QList<T>> &oldData,
    //                   const QList<int> &colIndex,
    //                   bool (funClass::*fun)(QList<QList<T>>&),
    //                   void (CommunicationEngine::*signal)
    //                   (const QVariant,const int, const QList<int>,const QList<T>),
    //                   bool ignoreSizeDifferent = false);

    // template <typename T>
    // bool compareAndObtainDifferentDatas(const QList<T> &oldData,
    //                                     const QList<T> &newData,
    //                                     QList<int> &differentIndex,
    //                                     QList<T> &differentValues,
    //                                     bool ignoreSizeDifferent = false);

    void processNewStr(AbstractCmd *absCmd);
    void setQStringListSource(AbstractCmd *absCmd);
    void getAllLabelsForVirtualKeyBoard();

    // 工程管理
    void importLocalProject(AbstractCmd *absCmd);
    void exportProject(AbstractCmd *absCmd);

    void initTeachPadInfo(AbstractCmd *absCmd);
    void userLogin(AbstractCmd *absCmd);
    void setCtlAuthority(AbstractCmd *absCmd);

    void refreshProjectDatas(AbstractCmd *absCmd);
    void getProjectList(AbstractCmd *absCmd);
    void setActiveProject(AbstractCmd *absCmd);
    void readProject(AbstractCmd *absCmd);
    void readLocalProject(AbstractCmd *absCmd);
    void getDefaultProjectName(AbstractCmd *absCmd);
    void createLocalProject(AbstractCmd *absCmd);
    void createProject(AbstractCmd *absCmd);
    void deleteProject(AbstractCmd *absCmd);
    void copyProject(AbstractCmd *absCmd);
    void genPasteProjectName(AbstractCmd *absCmd);
    void pasteProject(AbstractCmd *absCmd);
    void renameProject(AbstractCmd *absCmd);
    void uploadFilesToController(AbstractCmd *absCmd);
    void deleteFilesFromController(AbstractCmd *absCmd);
    void saveProject(AbstractCmd *absCmd);
    void saveAsProject(AbstractCmd *absCmd);
    void getProjectFileList(AbstractCmd *absCmd);
    void reloadActiveProject(AbstractCmd *absCmd);

    void getRobotPointFileList(AbstractCmd *absCmd);
    void setCurRobotPointFile(AbstractCmd *absCmd);
    void getDefaultRPointFileName(AbstractCmd *absCmd);
    void createRobotPointFile(AbstractCmd *absCmd);
    void deleteRobotPointFile(AbstractCmd *absCmd);
    void copyRobotPointFile(AbstractCmd *absCmd);
    void genPasteRobotFileName(AbstractCmd *absCmd);
    void pasteRobotPointFile(AbstractCmd *absCmd);
    void readRobotPoints(AbstractCmd *absCmd);
    void checkRobotPointIsExist(AbstractCmd *absCmd);
    void addRobotPoint(AbstractCmd *absCmd);
    void addRobotPointByIndex(AbstractCmd *absCmd);
    void copyRobotPoint(AbstractCmd *absCmd);
    void pasteRobotPoint(AbstractCmd *absCmd);
    void deleteRobotPoint(AbstractCmd *absCmd);
    void changeRobotPoint(AbstractCmd *absCmd);
    void changeRobotPointPos(AbstractCmd *absCmd);
    void replaceRobotPoint(AbstractCmd *absCmd);
    void renameRobotPoint(AbstractCmd *absCmd);
    void importRobotPointFile(AbstractCmd *absCmd);
    void exportRobotPointFile(AbstractCmd *absCmd);
    // 关节点文件
    void getJointPointFileList(AbstractCmd *absCmd);
    void setCurJointPointFile(AbstractCmd *absCmd);
    void readJointPoints(AbstractCmd *absCmd);
    void checkJointPointIsExist(AbstractCmd *absCmd);
    void addJointPoint(AbstractCmd *absCmd);
    void addJointPointByIndex(AbstractCmd *absCmd);
    void copyJointPoint(AbstractCmd *absCmd);
    void pasteJointPoint(AbstractCmd *absCmd);
    void deleteJointPoint(AbstractCmd *absCmd);
    void changeJointPoint(AbstractCmd *absCmd);
    void changeJointPointPos(AbstractCmd *absCmd);
    void replaceJointPoint(AbstractCmd *absCmd);
    void renameJointPoint(AbstractCmd *absCmd);

    void getLabelTypeList(AbstractCmd *absCmd);
    void genInitIoItems(AbstractCmd *absCmd);
    void getIoItems(AbstractCmd *absCmd);
    void genInitAdDaItems(AbstractCmd *absCmd);
    void getAdDaItems(AbstractCmd *absCmd);
    void genInitOtherItems(AbstractCmd *absCmd);
    void getOtherItems(AbstractCmd *absCmd);
    void modifyIoItem(AbstractCmd *absCmd);
    void modifyAdDaItem(AbstractCmd *absCmd);
    void modifyOtherItem(AbstractCmd *absCmd);
    void updateToolIOItemDesc(AbstractCmd *absCmd);

    void getUserDefineWaringFileList(AbstractCmd *absCmd);
    void getUserDefineWarnings(AbstractCmd *absCmd);
    void modifyUserDefineWarnig(AbstractCmd *absCmd);

    void getTaskList(AbstractCmd *absCmd);
    void getTaskStatus(AbstractCmd *absCmd);
    void activeTask(AbstractCmd *absCmd);
    void manageTaskInfos(AbstractCmd *absCmd);

    void updateRoadPointInfo();

    void calLineNum(AbstractCmd *absCmd);
    void logicTreeBreakPointOperation(AbstractCmd *absCmd);
    void setEnabledAllBreakPoints(AbstractCmd *absCmd);
    void getEnabledAllBreakPoints(AbstractCmd *absCmd);

    void getAllTreeItems(AbstractCmd *absCmd);
    void checkLogicTreeNodes(AbstractCmd *absCmd);

    void createLogicTreeNodesXmlCache(AbstractCmd *absCmd);
    void readLogicTreeNodes(AbstractCmd *absCmd);
    void readLogicTreeLevel(AbstractCmd *absCmd);
    void sortLogicTreeNodes(AbstractCmd *absCmd);
    void clearLogicTreeNodesWhenReadXmlFalid(AbstractCmd *absCmd);

    void wirteLogicTreeNodes(AbstractCmd *absCmd);
    void wirteLogicTreeLevel(AbstractCmd *absCmd);

    void setLogicTreeStartLine(AbstractCmd *absCmd);
    void getLogicTreeStartLine(AbstractCmd *absCmd);

    void setRGB(AbstractCmd *absCmd);

    void loadRobotModel(AbstractCmd *absCmd);
    void loadRobotModelSegment(AbstractCmd *absCmd);

private:
    QMutex *m_waitConditionMutex;
    QWaitCondition *m_waitCondition;

    QMutex *m_queueMutex;
    QList<AbstractCmd *> m_cmdQueue;
    //QQueue<AbstractCmd *> m_cmdQueue;

    QMutex *m_quitConditionMutex;
    QWaitCondition *m_quitCondition;

    bool m_isQuitThread;
    QSet<int> m_hashCmdCannotRepeat;

    //键：AbstractCmdType 值：old线程池存放数量
    //0代表不筛重
    QHash<int,int> m_hash_Type_MapTo_MaxCount;
    //哈希表 键：parir :int AbstractCmd QObject 对象，值：当前队列有几个
    QHash<QPair<int,QObject*>,int> m_Hash_TypeAndObject_MapTo_QueueCount;
    int m_lastTasktype = -1;
    QObject *m_lastTaskObject = nullptr;
    ThreadType m_threadType = Thread_Communication;

};
