#pragma once
#include <string>
#include <queue>
#include "IInoRobBusiness.h"

namespace InoRobBusiness
{
class INOROBBUSINESS_CLASS DebugerDefault : public IDebuger
{
    Q_OBJECT

public:
    DebugerDefault(string name, IDataSrvBase *dataService, QObject *parent = nullptr);
    virtual ~DebugerDefault();
    void init() override;

public:
    virtual void setDebugMode(DebugMode mode) override;
    virtual DebugMode getDebugMode() override;

    virtual int startRunningInDebug(TrajectoryRecoveryFlag &flag) override;
    virtual int startRunningInAuto(TrajectoryRecoveryFlag &flag) override;
    virtual int writeStartRunning() override;
    virtual int stopRunningInDebug(bool isRmtIoEnable, bool isCheck = true) override;
    virtual int stopRunningInAuto(bool isRmtIoEnable, bool isCheck = true) override;
    virtual int writeStopRunning() override;
    virtual int backStep() override;
    virtual int nextStep(TrajectoryRecoveryFlag &flag) override;
    virtual int writeNextStep() override;
    virtual int pause() override;

    virtual int trajectoryRecoveryFlag(TrajectoryRecoveryFlag &flag) override;
    virtual int trajectoryRecoveryExcute(TrajectoryRecoveryExcuteMode mode) override;

    virtual int writeStartReleaseMode(const StartReleaseObjType &objType, const StartReleaseMode &mode) override;
    virtual int readStartReleaseMode(const StartReleaseObjType &objType, StartReleaseMode &mode) override;
    virtual void setCurStartReleaseMode(const StartReleaseObjType &objType, const StartReleaseMode &mode) override;
    virtual StartReleaseMode getCurStartReleaseMode(const StartReleaseObjType &objType) override;
    virtual bool checkStartReleaseSavePermission() override;

    virtual int modifyCmdPoint(const std::string &programFileName, int taskId, PointType pointType, int pointNo,
                               int toolNo, int wobjNo, const std::vector<string> &proArr = std::vector<string>()) override;
    virtual int modifyPointRT(const std::string &fileName, const MRobPosItem &point, PointType pointType,
                              const std::vector<string> &proArr = std::vector<string>()) override;
    virtual std::string getRunningTime() override;

    virtual int writeControllerLogSwitchInfo(ControllerLogSwitchInfo infos[CONTROLLER_LOG_TYPE_COUNT]) override;
    virtual int readControllerLogSwitchInfo(ControllerLogSwitchInfo infos[CONTROLLER_LOG_TYPE_COUNT]) override;

    virtual ICmdMessageBox *getCmdMessageBox() override;

    virtual bool checkModifyRange(std::vector<double> &pos1, std::vector<double> &pos2) override;

    virtual bool checkUSBFlashDrive() override;

    virtual int readProgramCursorMode() override;
    virtual bool writeProgramCursorMode(int mode, bool isNeedPrint = true) override;

#pragma endregion

private:
    /// <summary>
    /// 判断状态，如连接、控制权、使能等
    /// </summary>
    bool checkMoveState();
    /// <summary>
    /// 检查轨迹恢复状态标识
    /// </summary>
    bool checkTrajectoryRecoveryFlag(TrajectoryRecoveryFlag &flag, int &ret);
    /// <summary>
    /// 响应连接状态改变事件
    /// </summary>
    /// <param name="status">连接状态</param>
    void onConnectionStatusChanged(ControllerConnectionStatus status);
    /**
     * @brief 文件读写指令响应事件
     */
    void onFileReadWriteCmdStart();
    /**
     * @brief 文件读写指令
     * @param curFrameId 当前帧号
     * @param fileNum 文件数量
     * @param filePath 文件信息
     * @return
     */
    int interFileReadWriteInfo(int32u curFrameId, int32u &fileNum, FileReadAndWriteInfo &fileReadAndWriteInfo);
    /**
     * @brief InterFileReadWriteInfoResult 文件读写结果
     * @param taskID 任务号
     * @param fileTimes 文件上传次数
     * @param status 状态
     * @return
     */
    int interFileReadWriteInfoResult(int32u taskID, int32u fileTimes, int32u status);
    /**
     * @brief 文件FTP传输
     */
    void fileFtpTranslate();
    /**
     * @brief 执行系统命令
     * @param cmdstring 要执行的命令
     * @return 执行返回状态
     */
    int osSystem(const std::string &cmdString);
    /**
     * @brief 读取程序光标跟随参数
     * @param followMode 输出参数，用于存储读取到的跟随模式
     */
    void readProgramCursorParameter(int &followMode);
    /**
     * @brief 写入程序光标跟随参数
     * @param followMode 写入参数，用于写入当前的跟随模式
     * @return 是否写入成功，true:成功，false:失败
     */
    bool writeProgramCursorParameter(int followMode);

private:
    IDataSrvBase *_pDataSrv = nullptr;
    IProject *_pProject = nullptr;
    IConnection *_pConnection = nullptr;
    ITransfor *_pTransfor = nullptr;
    IMonitor *_pMonitor = nullptr;
    IControl *_pControl = nullptr;
    ITask *_pTask = nullptr;
    IRCConfig *_pRCConfig = nullptr;
    IMotion *_pMotion = nullptr;
    IPosition *_pPosition = nullptr;
    IRobotControllerEvents *_pRobotEvents = nullptr;
    ICmdMessageBox *_pCmdMessageBox = nullptr;

    DebugMode _debugMode;                         // 当前调试模式
    StartReleaseMode _pcStartReleaseMode;         // PC当前启动释放策略
    StartReleaseMode _tpStartReleaseMode;         // TP当前启动释放策略
    std::queue<Upload_File_Info> _filePathQueue;  // 待传输的文件路径
};

}  // namespace InoRobBusiness
