#pragma once

#include <QString>
#include "metatype_global.h"

class METATYPE_EXPORT RobotEventInfo
{
public:
    // 示教器内部事件，与服务器无关
    enum UserEventType {
        UserEvent_Invaild = 0,

        // 禁用窗口事件
        UserEvent_RobotShutDown,
        UserEvent_ProgramStart,
        UserEvent_ProgramStartFinish,
        UserEvent_ProgramPause,
        UserEvent_ProgramPauseFinish,
        UserEvent_ProgramContinue,
        UserEvent_ProgramContinueFinish,
        UserEvent_ProgramStop,
        UserEvent_ProgramStopFinish,
        UserEvent_LoadingLanguage,
        UserEvent_LoadLanguageFinish,
        UserEvent_DuringExecuteCmd,
        UserEvent_CmdExecCompleted,
        UserEvent_ConnectController,
        UserEvent_ConnectFinish,
        UserEvent_LoadIdentify,
        UserEvent_LoadIdentifyFinish,
        UserEvent_DownLoadApk,
        UserEvent_DownLoadApkFinish,
        UserEvent_ExportTechpadConfigures,
        UserEvent_ExportTechpadConfiguresFinish,
        UserEvent_DisconnectController,
        UserEvent_DisconnectFinish,
        UserEvent_WriteData,
        UserEvent_WriteDataFinished,
        UserEvent_ReadData,
        UserEvent_ReadDataFinished,
        UserEvent_LoadingFile,
        UserEvent_LoadFileFinish,
        UserEvent_EmergeStop,
        UserEvent_EmergeStopFinish,
        UserEvent_ChangeControlAuthority,
        UserEvent_ChangeControlAuthorityFinish,
        UserEvent_CreateProject,
        UserEvent_CreateProjectFinish,
        UserEvent_DeleteProject,
        UserEvent_DeleteProjectFinish,
        UserEvent_RenameProject,
        UserEvent_RenameProjectFinish,
        UserEvent_PasteProject,
        UserEvent_PasteProjectFinish,
        UserEvent_LoadProject,
        UserEvent_LoadProjectFinish,
        UserEvent_SyncProject,
        UserEvent_SyncProjectFinish,
        UserEvent_ExportProject,
        UserEvent_ExportProjectFinish,
        UserEvent_UpdateApp,
        UserEvent_UpdateAppFinish,
        UserEvent_GeneralMatchSync,
        UserEvent_GeneralMatchSyncFinished,
        UserEvent_LoadRobotModel,
        UserEvent_LoadRobotModelFinished,

        UserEvent_Timeout,
        UserEvent_Error,
        UserEvent_ImportLanguagePackage,
        UserEvent_ImportLanguagePackageFinish,
        UserEvent_Max = 9999,
    };

    RobotEventInfo();
    RobotEventInfo(const UserEventType &eventType,
                   QString eventContent = QString());

    RobotEventInfo(const RobotEventInfo &other);
    RobotEventInfo operator=(const RobotEventInfo &other);
    bool operator==(const RobotEventInfo &other) const;
    bool operator<(const RobotEventInfo &other) const;

    static bool robotEventInfoSort(
        const RobotEventInfo robotEventInfoFirst,
        const RobotEventInfo robotEventInfoSecond);

    void init();
    void initTitleAndContent();

    QString getPrintInfo() const;

    int m_eventType;
    int m_eventCode;
    QString m_eventTitle;
    QString m_eventContent;
    QString m_datetime;
    bool m_isCheckCode;

private:
    void copyOthertoSelf(const RobotEventInfo &other);
};
