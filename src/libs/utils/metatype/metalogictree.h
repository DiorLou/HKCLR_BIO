#pragma once

#include <QObject>
#include <QHash>
#include "metatype_global.h"

const char ConditionType_ProjectRoot[] = "ConditionType_ProjectRoot";

const char AsyncTaskType_SetBreakPoint[] = "SetBreakPoint";
const char AsyncTaskType_CheckLogictree[] = "CheckLogictree";
const char AsyncTaskType_WriteXmlBlock[] = "WriteXmlBlock";
const char AsyncTaskType_ReadXmlBlock[] = "ReadXmlBlock";
const char AsyncTaskType_ReadXmlInAsync[] = "ReadXmlInAsync";
const char AsyncTaskType_UpdateLineNumbers[] = "UpdateLineNumbers";

const int LogicTreeNodeMaxCount = 30000;

class METATYPE_EXPORT LogictreeMetaType
{
public:
    static const int LogicTreeNodeChipSize = 500;
    enum LogicTreeThreadIndex {
        Thread_WriteTreeNode = 0,
        Thread_MinThreadNeed = 2,
        Thread_ReadAndWriteTreeStructure = -1,
    };

    enum LogicTreeColumn {
        Column_Node = 0,
        Column_LineNumbers = 1,
        Column_CondType = 2,
        Column_Alias = 3,
        Column_CondInfo = 4,
        Column_Uuid = 5,
        Column_ItemCheckRes = 6,
        Column_Comment = 7,
        Column_ModifyEnable = 8,
        Column_AddState = 9,
        Column_ManagedByOthers
    };
    enum CheckLogicTreeType {
        CheckLogicTreeType_AfterRead_Proeject,
        CheckLogicTreeType_BeforeSave_Proeject,
        CheckLogicTreeType_Switch_Language
    };
    enum LogicTreeBreakPointsType {
        LogicTreeBreakPointsType_Remove_Done = 0,
        LogicTreeBreakPointsType_Remove_WaitControllerResponse,
        LogicTreeBreakPointsType_Remove_FailedButNotInModel,

        LogicTreeBreakPointsType_Add_Done,
        LogicTreeBreakPointsType_Add_WaitControllerResponse,
        LogicTreeBreakPointsType_Add_FailedButNotInModel,

        LogicTreeBreakPointsType_RequireStateReverse,
    };
    enum DataRoleExpansion
    {
        Role_MetaData_IsExpand = Qt::UserRole,
        Role_MetaData_ConditionType = Qt::UserRole,
        Role_BreakPointsState
    };
    static void resigerCondNameAndType(const QString &name, const QString &type);
    static QString condName2Type(const QString &condName);
    static QString condType2Name(const QString &condtype);

private:
    LogictreeMetaType(){};
};
