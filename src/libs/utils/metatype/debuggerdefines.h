#ifndef DEBUGGERDEFINES_H
#define DEBUGGERDEFINES_H

enum TrajRecvFlag
{
    /// 当前处于运行中，不允许清除轨迹，也不允许发启动命令
    TrajRecvFlag_INVALID = -1,
    /// 已设置过了轨迹恢复的执行策略，后者不需要执行轨迹恢复
    TrajRecvFlag_SETTED_OR_NEEDLESS = 0,
    /// 需要轨迹恢复，且在运动行
    TrajRecvFlag_IN_MOVELINE = 1,
    /// 需要轨迹恢复，但不在运动行
    TrajRecvFlag_NOT_IN_MOVELINE = 2,
    /// ARM缓存区有数据，但DSP未保存轨迹信息
    TrajRecvFlag_DSP_NOT_HAVE_MSG = 3,
};

enum TrajRecvExecMode
{
    TrajRecvExecMode_GIVEUP = 0,
    TrajRecvExecMode_EXCUTE,
};

#endif  // DEBUGGERDEFINES_H
