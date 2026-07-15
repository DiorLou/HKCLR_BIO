#pragma once

enum InoTaskState
{
    Task_Falid = -1,  //失败
    Task_UnknowState,      // 未定义状态
    Task_InProcess,         // 正在进行
    Task_FineshedSuccess, //成功结束
    Task_WasForciblyTerminated //强行终止
};

